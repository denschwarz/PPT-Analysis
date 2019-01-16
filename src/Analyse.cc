#include "../include/Analyse.h"

/*
Dies ist der eigentliche Analyse-Code.
Hier werden die rohen Root Dateien jedes Prozesses eingelesen und verarbeitet.
Ihr koennt hier Variablen zusammensetzen und Histogramme fuellen.
Der Output wird gesammelt in einer weiteren Root Datei abgespeichert.
*/


int main(int argc, char* argv[]){

  // -----------------------------------------------------------------------------
  // Hier wird der Name der Output Datei vergeben
  TString outputName = "Histograms.root";
  outputFile=new TFile(outputName,"recreate");

  // -----------------------------------------------------------------------------
  // Hier werden Histogramme definiert.
  // Dabei ist für jede Größe ein Vektor definiert.
  // Dieser Vektor enthält je ein Histogramm für jeden Prozess (Daten, Higgs, ZZ, DY)
  hist_EventCount.push_back(new TH1F("hist_EventCount_data", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_higgs", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_ZZ", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_DY", " ", 1, 0, 2));

  hist_muonPT.push_back(new TH1F("hist_muonPT_data", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_higgs", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_ZZ", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_DY", "Muon p_{T}", 20, 0, 300));

  hist_elecPT.push_back(new TH1F("hist_elecPT_data", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_higgs", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_ZZ", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_DY", "Electron p_{T}", 20, 0, 300));

  // -----------------------------------------------------------------------------
  // Hier findet die eigentliche Analyse statt.
  // Dabei wird jede Root-Datei geöffnet und ausgelesen.
  // Daraus erhält man je eine Liste an Elektronen und Myonen.
  // Diese werden dann für die Analyse ausgewertet

  int Nsamples = sample_names.size(); // Anzahl an Root-Dateien
  for(int isample=0; isample<Nsamples; isample++){ // Schleife über alle Root-Dateien
    for(auto channel: sample_channels[isample]){   // Schleife über alle möglichen Kanäle einer Datei
      cout << "Analising " << sample_names[isample] << "..." << endl;

      // Hier werden die Dateien ausgelesen und Vektoren von Myonen und Elektronen erstellt
      ReadLeptons reader(sample_names[isample], channel);
      int Nevents = reader.GetEventCount();
      vector< vector<Particle> > Muons = reader.GetMuons();
      vector< vector<Particle> > Elecs = reader.GetElectrons();
      ////

      // Gewicht, Histindex auslesen
      int ihist =  sample_histindex[isample];
      double weight = sample_weights[isample];
      ////

      // In der eigentlichen Analyse führen wir für jedes Ereignis aus.
      // Da wir immer das gleiche für jedes Ereignis tun, benutzen wir hier eine Schleife.
      for(int ievent=0; ievent<Nevents; ievent++){
        hist_EventCount[ihist]->Fill(1, weight);    // dieses Hist zählt Ereignisse
        // Schleife über alle Myonen in einem Ereignis
        for(int i=0; i<Muons[ievent].size(); i++){
          double pt = Muons[ievent][i].Pt();        // pT von Myon auslesen
          hist_muonPT[ihist]->Fill(pt, weight);     // in Histogramm füllen
        }
        ////

        // Schleife über alle Electronen in einem Ereignis
        for(int i=0; i<Elecs[ievent].size(); i++){
          double pt = Elecs[ievent][i].Pt();
          hist_elecPT[ihist]->Fill(pt, weight);
        }
        ////
      }
    }
  }
  // Abspeichern in einer neuen Datei.
  outputFile->Write();
  return 0;
}
