#include "../include/Plotter.h"

/*
 In diesem Programm lest ihr die Output Datei aus 'Analyse' ein.
 Darin befinden sich Histogramme getrannt nach den verschiedenen Prozessen.
 Hier fuegt ihr diese in einen Plot zusammen, waehlt Farben aus, beschriftet Achsen
 und fertigt eine Legende an.
*/

int main(int argc, char* argv[]){

  // Datei mit Histogrammen einlesen
  TFile * file = new TFile("Histograms.root");

  // Histogramme aus Datei auslesen und ein einzelnes Histogramm fuer jedes Signal/Untergrund erstellen
  TH1F* h_EventCount_data = (TH1F*)file->Get("hist_EventCount_data");
  TH1F* h_EventCount_higgs = (TH1F*)file->Get("hist_EventCount_higgs");
  TH1F* h_EventCount_ZZ = (TH1F*)file->Get("hist_EventCount_ZZ");
  TH1F* h_EventCount_DY = (TH1F*)file->Get("hist_EventCount_DY");

  TH1F* h_Mass4l_data = (TH1F*)file->Get("hist_Mass4l_data");
  TH1F* h_Mass4l_higgs = (TH1F*)file->Get("hist_Mass4l_higgs");
  TH1F* h_Mass4l_ZZ = (TH1F*)file->Get("hist_Mass4l_ZZ");
  TH1F* h_Mass4l_DY = (TH1F*)file->Get("hist_Mass4l_DY");

  TH1F* h_leptonPT_data = (TH1F*)file->Get("hist_leptonPT_data");
  TH1F* h_leptonPT_higgs = (TH1F*)file->Get("hist_leptonPT_higgs");
  TH1F* h_leptonPT_ZZ = (TH1F*)file->Get("hist_leptonPT_ZZ");
  TH1F* h_leptonPT_DY = (TH1F*)file->Get("hist_leptonPT_DY");

  TH1F* h_leptonETA_data = (TH1F*)file->Get("hist_leptonETA_data");
  TH1F* h_leptonETA_higgs = (TH1F*)file->Get("hist_leptonETA_higgs");
  TH1F* h_leptonETA_ZZ = (TH1F*)file->Get("hist_leptonETA_ZZ");
  TH1F* h_leptonETA_DY = (TH1F*)file->Get("hist_leptonETA_DY");

  // ein paar Optionen fuer Farben und Linien der einzelnen Histogramme
  h_EventCount_data->SetMarkerStyle(20);
  h_EventCount_data->SetMarkerSize(0.8);
  h_EventCount_data->SetLineColor(1);
  h_EventCount_ZZ->SetFillColor(kAzure-9);
  h_EventCount_ZZ->SetLineColor(kBlack);
  h_EventCount_ZZ->SetLineWidth(2);
  h_EventCount_DY->SetFillColor(kGreen+2);
  h_EventCount_DY->SetLineColor(kBlack);
  h_EventCount_DY->SetLineWidth(2);
  h_EventCount_higgs->SetFillColor(kWhite);
  h_EventCount_higgs->SetLineColor(kRed);
  h_EventCount_higgs->SetLineWidth(2);

  h_Mass4l_data->SetMarkerStyle(20);
  h_Mass4l_data->SetMarkerSize(0.8);
  h_Mass4l_data->SetLineColor(1);
  h_Mass4l_ZZ->SetFillColor(kAzure-9);
  h_Mass4l_ZZ->SetLineColor(kBlack);
  h_Mass4l_ZZ->SetLineWidth(2);
  h_Mass4l_DY->SetFillColor(kGreen+2);
  h_Mass4l_DY->SetLineColor(kBlack);
  h_Mass4l_DY->SetLineWidth(2);
  h_Mass4l_higgs->SetFillColor(kWhite);
  h_Mass4l_higgs->SetLineColor(kRed);
  h_Mass4l_higgs->SetLineWidth(2);

  h_leptonPT_data->SetMarkerStyle(20);
  h_leptonPT_data->SetMarkerSize(0.8);
  h_leptonPT_data->SetLineColor(1);
  h_leptonPT_ZZ->SetFillColor(kAzure-9);
  h_leptonPT_ZZ->SetLineColor(kBlack);
  h_leptonPT_ZZ->SetLineWidth(2);
  h_leptonPT_DY->SetFillColor(kGreen+2);
  h_leptonPT_DY->SetLineColor(kBlack);
  h_leptonPT_DY->SetLineWidth(2);
  h_leptonPT_higgs->SetFillColor(kWhite);
  h_leptonPT_higgs->SetLineColor(kRed);
  h_leptonPT_higgs->SetLineWidth(2);

  h_leptonETA_data->SetMarkerStyle(20);
  h_leptonETA_data->SetMarkerSize(0.8);
  h_leptonETA_data->SetLineColor(1);
  h_leptonETA_ZZ->SetFillColor(kAzure-9);
  h_leptonETA_ZZ->SetLineColor(kBlack);
  h_leptonETA_ZZ->SetLineWidth(2);
  h_leptonETA_DY->SetFillColor(kGreen+2);
  h_leptonETA_DY->SetLineColor(kBlack);
  h_leptonETA_DY->SetLineWidth(2);
  h_leptonETA_higgs->SetFillColor(kWhite);
  h_leptonETA_higgs->SetLineColor(kRed);
  h_leptonETA_higgs->SetLineWidth(2);

  // nun sollen alle Simulationen "gestapelt" werden
  THStack *stack_EventCount = new THStack("","");
  stack_EventCount->Add(h_EventCount_DY);
  stack_EventCount->Add(h_EventCount_ZZ);
  stack_EventCount->Add(h_EventCount_higgs);

  THStack *stack_Mass4l = new THStack("","");
  stack_Mass4l->Add(h_Mass4l_DY);
  stack_Mass4l->Add(h_Mass4l_ZZ);
  stack_Mass4l->Add(h_Mass4l_higgs);

  THStack *stack_leptonPT = new THStack("","");
  stack_leptonPT->Add(h_leptonPT_DY);
  stack_leptonPT->Add(h_leptonPT_ZZ);
  stack_leptonPT->Add(h_leptonPT_higgs);

  THStack *stack_leptonETA = new THStack("","");
  stack_leptonETA->Add(h_leptonETA_DY);
  stack_leptonETA->Add(h_leptonETA_ZZ);
  stack_leptonETA->Add(h_leptonETA_higgs);

  // ein paar allgemeine Style Optionen
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTickX(1);


  // Hier wird der eigentliche Plot erstellt
  TCanvas* Canvas0 = new TCanvas("count","count",600,600);
  gPad->SetLeftMargin(0.15);
  stack_EventCount->Draw("HIST");
  // Achsen
  stack_EventCount->GetXaxis()->SetRangeUser(0, 2);
  stack_EventCount->SetMaximum(600);
  stack_EventCount->GetXaxis()->SetTitle("Mass 4l [GeV]");
  stack_EventCount->GetYaxis()->SetTitle("events");
  stack_EventCount->GetXaxis()->SetTitleSize(0.04);
  stack_EventCount->GetXaxis()->SetTitleOffset(0.9);
  stack_EventCount->GetYaxis()->SetTitleSize(0.05);
  stack_EventCount->GetYaxis()->SetTitleOffset(1.1);
  //Draw
  stack_EventCount->Draw("HIST");
  h_EventCount_data->Draw("E1 SAME");
  // Legende
  TLegend* leg_count = new TLegend(0.60,0.60,0.87,0.85);
  leg_count->SetFillStyle(0);
  leg_count->AddEntry(h_leptonETA_data,"data","pl");
  leg_count->AddEntry(h_leptonETA_ZZ,"ZZ","f");
  leg_count->AddEntry(h_leptonETA_DY,"Z/#gamma + X","f");
  leg_count->AddEntry(h_leptonETA_higgs,"Higgs","f");
  leg_count->Draw();
  //speichern
  Canvas0->SaveAs("plots/EventCount.pdf");


  TCanvas* Canvas = new TCanvas("mass","mass",600,600);
  gPad->SetLeftMargin(0.15);
  stack_Mass4l->Draw("HIST");
  // Achsen
  stack_Mass4l->GetXaxis()->SetRangeUser(70, 181);
  stack_Mass4l->SetMaximum(31);
  stack_Mass4l->GetXaxis()->SetTitle("Mass 4l [GeV]");
  stack_Mass4l->GetYaxis()->SetTitle("events");
  stack_Mass4l->GetXaxis()->SetTitleSize(0.04);
  stack_Mass4l->GetXaxis()->SetTitleOffset(0.9);
  stack_Mass4l->GetYaxis()->SetTitleSize(0.05);
  stack_Mass4l->GetYaxis()->SetTitleOffset(1.1);
  //Draw
  stack_Mass4l->Draw("HIST");
  h_Mass4l_data->Draw("E1 SAME");
  // Legende
  TLegend* leg_mass = new TLegend(0.60,0.60,0.87,0.85);
  leg_mass->SetFillStyle(0);
  leg_mass->AddEntry(h_leptonETA_data,"data","pl");
  leg_mass->AddEntry(h_leptonETA_ZZ,"ZZ","f");
  leg_mass->AddEntry(h_leptonETA_DY,"Z/#gamma + X","f");
  leg_mass->AddEntry(h_leptonETA_higgs,"Higgs","f");
  leg_mass->Draw();
  //speichern
  Canvas->SaveAs("plots/Mass4l.pdf");

  TCanvas* Canvas2 = new TCanvas("pt","pt",600,600);
  gPad->SetLeftMargin(0.15);
  stack_leptonPT->Draw("HIST");
  // Achsen
  stack_leptonPT->GetXaxis()->SetRangeUser( 0, 200);
  stack_leptonPT->SetMaximum(400);
  stack_leptonPT->GetXaxis()->SetTitle("Lepton p_{T} [GeV]");
  stack_leptonPT->GetYaxis()->SetTitle("events");
  stack_leptonPT->GetXaxis()->SetTitleSize(0.04);
  stack_leptonPT->GetXaxis()->SetTitleOffset(0.9);
  stack_leptonPT->GetYaxis()->SetTitleSize(0.05);
  stack_leptonPT->GetYaxis()->SetTitleOffset(1.1);
  // Draw
  stack_leptonPT->Draw("HIST");
  h_leptonPT_data->Draw("E1 SAME");
  // Legende
  TLegend* leg_pt = new TLegend(0.60,0.60,0.87,0.85);
  leg_pt->SetFillStyle(0);
  leg_pt->AddEntry(h_leptonPT_data,"data","pl");
  leg_pt->AddEntry(h_leptonPT_ZZ,"ZZ","f");
  leg_pt->AddEntry(h_leptonPT_DY,"Z/#gamma + X","f");
  leg_pt->AddEntry(h_leptonPT_higgs,"Higgs","f");
  leg_pt->Draw();
  //speichern
  Canvas2->SaveAs("plots/LeptonPT.pdf");

  TCanvas* Canvas3 = new TCanvas("eta","eta",600,600);
  gPad->SetLeftMargin(0.15);
  stack_leptonETA->Draw("HIST");
  // Achsen
  stack_leptonETA->GetXaxis()->SetRangeUser(-3, 3);
  stack_leptonETA->SetMaximum(150);
  stack_leptonETA->GetXaxis()->SetTitle("Lepton #eta [GeV]");
  stack_leptonETA->GetYaxis()->SetTitle("events");
  stack_leptonETA->GetXaxis()->SetTitleSize(0.04);
  stack_leptonETA->GetXaxis()->SetTitleOffset(0.9);
  stack_leptonETA->GetYaxis()->SetTitleSize(0.05);
  stack_leptonETA->GetYaxis()->SetTitleOffset(1.1);
  // Draw
  stack_leptonETA->Draw("HIST");
  h_leptonETA_data->Draw("E1 SAME");
  // Legende
  TLegend* leg_eta = new TLegend(0.60,0.60,0.87,0.85);
  leg_eta->SetFillStyle(0);
  leg_eta->AddEntry(h_leptonETA_data,"data","pl");
  leg_eta->AddEntry(h_leptonETA_ZZ,"ZZ","f");
  leg_eta->AddEntry(h_leptonETA_DY,"Z/#gamma + X","f");
  leg_eta->AddEntry(h_leptonETA_higgs,"Higgs","f");
  leg_eta->Draw();
  //speichern
  Canvas3->SaveAs("plots/LeptonETA.pdf");

  return 0;
}

TH1F* SB(TH1F* Signal, TH1F* Background){
  int nbins = Signal->GetSize()-2;
  TH1F* h_SB = (TH1F*) Signal->Clone();
  h_SB->Reset();
  for(int i=1; i<=nbins; i++){
    double sig = Signal->GetBinContent(i);
    double bkg = Background->GetBinContent(i);
    h_SB->SetBinContent(i, sig/sqrt(sig+bkg));
  }
  return h_SB;
}
