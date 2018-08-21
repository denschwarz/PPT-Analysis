#include "Plot.h"

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
  TH1F* h_leptonPT_data = (TH1F*)file->Get("hist_leptonPT_data");
  TH1F* h_leptonPT_higgs = (TH1F*)file->Get("hist_leptonPT_higgs");
  TH1F* h_leptonPT_ZZ = (TH1F*)file->Get("hist_leptonPT_ZZ");
  TH1F* h_leptonPT_DY = (TH1F*)file->Get("hist_leptonPT_DY");

  TH1F* h_leptonETA_data = (TH1F*)file->Get("hist_leptonETA_data");
  TH1F* h_leptonETA_higgs = (TH1F*)file->Get("hist_leptonETA_higgs");
  TH1F* h_leptonETA_ZZ = (TH1F*)file->Get("hist_leptonETA_ZZ");
  TH1F* h_leptonETA_DY = (TH1F*)file->Get("hist_leptonETA_DY");

  // ein paar Optionen fuer Farben und Linien der einzelnen Histogramme
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
  TCanvas* Canvas_leptonPT = new TCanvas("","",600,600);
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
  Canvas_leptonPT->SaveAs("LeptonPT.pdf");

  TCanvas* Canvas_leptonETA = new TCanvas("","",600,600);
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
  Canvas_leptonETA->SaveAs("LeptonETA.pdf");

  return 0;
}
