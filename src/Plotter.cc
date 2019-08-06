#include "../include/Plotter.h"
#include <cstdlib>

/*
Mit dieser Klasse könne Plots erstellt werden.
*/


Plotter::Plotter(TString dir){
  directory = dir;
  system("mkdir -p "+dir);
}


// -----------------------------------------------------------------------------
// Hier passiert das eigentliche plotten ---------------------------------------
void Plotter::CreatePlot(vector<TH1F*> hists, TString filename, TString xtitle, double xmin, double xmax, double ymax){

  // checken ob Grenzen mit Bins zusammenpassen
  bool matching_min = false;
  bool matching_max = false;
  int Nbins = hists[0]->GetXaxis()->GetNbins();
  for(int i=1; i<=Nbins; i++){
    if(xmin == hists[0]->GetXaxis()->GetBinLowEdge(i)) matching_min = true;
    if(xmax == hists[0]->GetXaxis()->GetBinUpEdge(i)) matching_max = true;
  }
  if(!matching_min){
    cout << "[ERROR] xmin in " << filename << " nicht möglich!" << endl;
    cout << "        -- xmin muss auf einer Bin-Grenze liegen" << endl;
    cout << "        -- " << filename << " wird nicht erzeugt" << endl;
    return;
  }
  if(!matching_max){
    cout << "[ERROR] xmax in " << filename << " nicht möglich!" << endl;
    cout << "        -- xmin muss auf einer Bin-Grenze liegen" << endl;
    cout << "        -- " << filename << " wird nicht erzeugt" << endl;
    return;
  }

  // jetzt ein paar Style Optionen
  gStyle->SetOptStat(kFALSE);            // allgemeine Style Option
  gStyle->SetPadTickY(1);                //
  gStyle->SetPadTickX(1);                //
  gStyle->SetLegendBorderSize(0);        //
  hists[0]->SetMarkerStyle(20);          // Marker Style für Daten
  hists[0]->SetMarkerSize(0.8);          // Größe des Markers
  hists[0]->SetLineColor(1);             // Farbe des Markers
  hists[1]->SetFillColor(kWhite);        // Flächenfarbe Higgs
  hists[1]->SetLineColor(c_Higgs);          // Linienfarbe Higgs
  hists[1]->SetLineWidth(2);             // Linienbreite Higgs
  hists[2]->SetFillColor(c_ZZ);      // Flächenfarbe ZZ
  hists[2]->SetLineColor(kBlack);        // Linienfarbe ZZ
  hists[2]->SetLineWidth(2);             // Linienbreite ZZ
  hists[3]->SetFillColor(c_DY);      // Flächenfarbe DY
  hists[3]->SetLineColor(kBlack);        // Linienfarbe DY
  hists[3]->SetLineWidth(2);             // Linienbreite DY

  // Background stapeln
  THStack *stack = new THStack("","");
  stack->Add(hists[3]);
  stack->Add(hists[2]);
  stack->Add(hists[1]);
  // und total Background erstellen
  TH1F* background = (TH1F*)hists[2]->Clone("background");
  background->Add(hists[3]);

  // Canvas und oberes pad erzeugen
  TCanvas* c = new TCanvas("c","c",600,600);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0.015);
  pad1->SetLeftMargin(0.15);
  pad1->Draw();
  pad1->cd();

  stack->Draw("HIST");

  // Achsen
  stack->GetXaxis()->SetRangeUser(xmin, xmax);
  stack->SetMaximum(ymax);
  stack->GetYaxis()->SetTitle("events");
  stack->GetYaxis()->SetTitleSize(0.05);
  stack->GetYaxis()->SetTitleOffset(1.1);
  stack->GetXaxis()->SetNdivisions(505);
  stack->GetYaxis()->SetNdivisions(505);
  stack->GetYaxis()->SetTitleSize(20);
  stack->GetYaxis()->SetTitleFont(43);
  stack->GetYaxis()->SetTitleOffset(1.55);
  // Plotten
  stack->Draw("HIST");
  if(unblinded) hists[0]->Draw("E1 SAME");

  // Legende
  TLegend* leg_count = new TLegend(0.60,0.60,0.87,0.85);
  leg_count->SetFillStyle(0);
  if(unblinded) leg_count->AddEntry(hists[0],"data","pl");
  leg_count->AddEntry(hists[2],"ZZ","f");
  leg_count->AddEntry(hists[3],"Z/#gamma + X","f");
  leg_count->AddEntry(hists[1],"Higgs","f");
  leg_count->Draw();

  TLatex *txt1 = new TLatex();
  txt1->DrawTextNDC(0.2,0.8,"CMS Open Data");


  // das hier wird nur gemacht, damit die Achsenbeschriftung da ist
  stack->GetXaxis()->SetLabelSize(0.);
  stack->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( xmin, 0, xmin, ymax, 0, ymax, 505,"");
  axis->SetLabelFont(43);
  axis->SetLabelSize(15);
  axis->Draw();

  // Ratio Plot kommt in unteres pad
  c->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->Draw();
  pad2->cd();

  // Definiere Ratio Plot
  TH1F *ratio = (TH1F*)hists[0]->Clone("ratio");
  ratio->GetXaxis()->SetTitle(xtitle);
  ratio->GetXaxis()->SetTitleSize(20);
  ratio->GetXaxis()->SetTitleFont(43);
  ratio->GetXaxis()->SetTitleOffset(4.);
  ratio->GetXaxis()->SetLabelFont(43);
  ratio->GetXaxis()->SetLabelSize(15);
  ratio->GetXaxis()->SetNdivisions(505);
  ratio->GetXaxis()->SetRangeUser(xmin, xmax);
  ratio->GetYaxis()->SetTitle("#frac{data}{simulation}");
  ratio->GetYaxis()->SetTitleSize(20);
  ratio->GetYaxis()->SetTitleFont(43);
  ratio->GetYaxis()->SetTitleOffset(1.55);
  ratio->GetYaxis()->SetLabelFont(43);
  ratio->GetYaxis()->SetLabelSize(15);
  ratio->GetYaxis()->SetNdivisions(205);
  ratio->GetYaxis()->SetRangeUser(0.1, 3.5);
  ratio->SetLineColor(kBlack);
  ratio->Divide(background);
  if(unblinded){
    ratio->SetMarkerStyle(20);
    ratio->SetMarkerSize(0.8);
    ratio->Draw("EP");
  }
  else{
    ratio->Reset();
    ratio->SetLineWidth(1);
    ratio->SetLineColor(13);
    ratio->Draw("HIST");
  }

  // Auch Signal im Ratio Plot zeichnen
  TH1F *signal = (TH1F*)hists[1]->Clone("signal");
  signal->Reset();
  int nbins = signal->GetXaxis()->GetNbins();
  for(int i=1; i<=nbins; i++){
    double bgr = background->GetBinContent(i);
    if(bgr == 0){
      signal->SetBinContent(i, 1.0);
    }
    else {
      double sig = hists[1]->GetBinContent(i);
      double value = (sig+bgr)/bgr;
      signal->SetBinContent(i, value);
    }
  }
  signal->SetLineWidth(2);
  signal->SetLineColor(c_Higgs);

  // Zeichne Linien
  vector<TLine*> lines;
  lines.push_back(new TLine(xmin,1.0,xmax,1.0));
  lines.push_back(new TLine(xmin,2.0,xmax,2.0));
  lines.push_back(new TLine(xmin,3.0,xmax,3.0));
  for(auto line: lines){
    line->SetLineColor(13);
    line->SetLineWidth(1);
    line->SetLineStyle(7);
  }
  lines[0]->SetLineWidth(3);
  lines[0]->SetLineStyle(1);

  // noch einmal alles in der richtigen Reihenfolge zeichnen
  for(auto line: lines) line->Draw("SAME");
  signal->Draw("HIST SAME");
  lines[0]->Draw("SAME");
  if(unblinded)ratio->Draw("EP SAME");

  // speichern
  c->SaveAs(directory+"/"+filename+".pdf");
  delete c;
  return;
}
