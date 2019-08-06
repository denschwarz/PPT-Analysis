#include "../include/Plot.h"

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
  Plotter plotter("plots");
  plotter.Unblind();
  // Hier können noch Farben eingestellt werden
  plotter.SetHiggsColor(kRed);
  plotter.SetZZColor(kAzure-9);
  plotter.SetDYColor(kGreen+2);


  // Parameter: Hist-Vektor, Name der Datei, X-Achsen Titel, x_min, x_max, y_max
  plotter.CreatePlot(h_EventCount, "EventCount", " ", 0, 2, 600);
  plotter.CreatePlot(h_muonNUMBER, "MuonNUMBER", "number of muons", -0.5, 5.5, 300);
  plotter.CreatePlot(h_muonPT, "MuonPT", "Muon p_{T}", 0, 200, 200);
  plotter.CreatePlot(h_muonETA, "MuonETA", "Muon #eta", -3, 3, 200);
  plotter.CreatePlot(h_muonPHI, "MuonPHI", "Muon #Phi", -4, 4, 200);
  plotter.CreatePlot(h_muonCHARGE, "MuonCHARGE", "Muon charge", -2.5, 2.5, 600);
  plotter.CreatePlot(h_elecPT, "ElectronPT", "Electron p_{T}", 0, 200, 200);
  plotter.CreatePlot(h_Zmass, "Zmass", "Z mass", 0, 150, 360);

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
