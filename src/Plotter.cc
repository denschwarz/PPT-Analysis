#include "../include/Plotter.h"

/*
In diesem Programm lest ihr die Output Datei aus 'Analysis' ein.
Darin befinden sich Histogramme getrannt nach den verschiedenen Prozessen.
Hier fuegt ihr diese in einen Plot zusammen, waehlt Farben aus, beschriftet Achsen
und fertigt eine Legende an.
*/

int main(int argc, char* argv[]){

  // Datei mit Histogrammen einlesen
  file = new TFile("Histograms.root");

  // Histogramme aus Datei auslesen
  // und ein einzelnes Histogramm fuer jedes Signal/Untergrund erstellen
  vector<TH1F*> h_EventCount = ReadHistograms("EventCount");
  vector<TH1F*> h_muonNUMBER = ReadHistograms("muonNUMBER");
  vector<TH1F*> h_muonPT = ReadHistograms("muonPT");
  vector<TH1F*> h_muonPHI = ReadHistograms("muonPHI");
  vector<TH1F*> h_muonETA = ReadHistograms("muonETA");
  vector<TH1F*> h_muonCHARGE = ReadHistograms("muonCHARGE");
  vector<TH1F*> h_elecPT = ReadHistograms("elecPT");
  vector<TH1F*> h_Zmass = ReadHistograms("Zmass");

  // Hier wird der eigentliche Plot erstellt
  // Parameter: Hist-Vektor, Name der Datei, X-Achsen Titel, x_min, x_max, y_max
  CreatePlot(h_EventCount, "EventCount", " ", 0, 2, 600);
  CreatePlot(h_muonNUMBER, "MuonNUMBER", "number of muons", -0.5, 5.5, 300);
  CreatePlot(h_muonPT, "MuonPT", "Muon p_{T}", 0, 200, 200);
  CreatePlot(h_muonETA, "MuonETA", "Muon #eta", -3, 3, 200);
  CreatePlot(h_muonPHI, "MuonPHI", "Muon #Phi", -4, 4, 200);
  CreatePlot(h_muonCHARGE, "MuonCHARGE", "Muon charge", -2.5, 2.5, 600);
  CreatePlot(h_elecPT, "ElectronPT", "Electron p_{T}", 0, 200, 200);
  CreatePlot(h_Zmass, "Zmass", "Z mass", 0, 150, 200);

  return 0;
}


// -----------------------------------------------------------------------------
// Funktion um Histogramme aus Root Datei zu lesen -----------------------------
vector<TH1F*> ReadHistograms(TString histname){
  vector<TH1F*> hists;
  vector<TString> processes = {"data", "higgs", "ZZ", "DY"};
  for(auto process: processes){
    hists.push_back( (TH1F*)file->Get("hist_"+histname+"_"+process) );
  }
  return hists;
}

// -----------------------------------------------------------------------------
// Hier passiert das eigentliche plotten ---------------------------------------
void CreatePlot(vector<TH1F*> hists, TString filename, TString xtitle, double xmin, double xmax, double ymax){
  gStyle->SetOptStat(kFALSE);            // allgemeine Style Option
  gStyle->SetPadTickY(1);                //
  gStyle->SetPadTickX(1);                //
  hists[0]->SetMarkerStyle(20);          // Marker Style für Daten
  hists[0]->SetMarkerSize(0.8);          // Größe des Markers
  hists[0]->SetLineColor(1);             // Farbe des Markers
  hists[1]->SetFillColor(kWhite);        // Flächenfarbe Higgs
  hists[1]->SetLineColor(kRed);          // Linienfarbe Higgs
  hists[1]->SetLineWidth(2);             // Linienbreite Higgs
  hists[2]->SetFillColor(kAzure-9);      // Flächenfarbe ZZ
  hists[2]->SetLineColor(kBlack);        // Linienfarbe ZZ
  hists[2]->SetLineWidth(2);             // Linienbreite ZZ
  hists[3]->SetFillColor(kGreen+2);      // Flächenfarbe DY
  hists[3]->SetLineColor(kBlack);        // Linienfarbe DY
  hists[3]->SetLineWidth(2);             // Linienbreite DY

  // Background stapeln
  THStack *stack = new THStack("","");
  stack->Add(hists[3]);
  stack->Add(hists[2]);
  stack->Add(hists[1]);
  // Canvas erzeugen
  TCanvas* C = new TCanvas("c","c",600,600);
  gPad->SetLeftMargin(0.15);
  stack->Draw("HIST");
  // Achsen
  stack->GetXaxis()->SetRangeUser(xmin, xmax);
  stack->SetMaximum(ymax);
  stack->GetXaxis()->SetTitle(xtitle);
  stack->GetYaxis()->SetTitle("events");
  stack->GetXaxis()->SetTitleSize(0.04);
  stack->GetXaxis()->SetTitleOffset(0.9);
  stack->GetYaxis()->SetTitleSize(0.05);
  stack->GetYaxis()->SetTitleOffset(1.1);
  stack->GetXaxis()->SetNdivisions(505);
  stack->GetYaxis()->SetNdivisions(505);
  // Plotten
  stack->Draw("HIST");
  hists[0]->Draw("E1 SAME");
  // Legende
  TLegend* leg_count = new TLegend(0.60,0.60,0.87,0.85);
  leg_count->SetFillStyle(0);
  leg_count->AddEntry(hists[0],"data","pl");
  leg_count->AddEntry(hists[2],"ZZ","f");
  leg_count->AddEntry(hists[3],"Z/#gamma + X","f");
  leg_count->AddEntry(hists[1],"Higgs","f");
  leg_count->Draw();
  // speichern
  C->SaveAs("plots/"+filename+".pdf");
  delete C;
  return;
}
