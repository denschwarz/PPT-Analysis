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
  // für jede Variable (z.B. Lepton pT) und jeden Prozess (daten, ZZ, DY, ..) wird ein eigenes Histogramm gefüllt
  hist_EventCount.push_back(new TH1F("hist_EventCount_data", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_higgs", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_ZZ", " ", 1, 0, 2));
  hist_EventCount.push_back(new TH1F("hist_EventCount_DY", " ", 1, 0, 2));

  hist_Mass4l.push_back(new TH1F("hist_Mass4l_data", "Mass 4l", 37, 70, 181));
  hist_Mass4l.push_back(new TH1F("hist_Mass4l_higgs", "Mass 4l", 37, 70, 181));
  hist_Mass4l.push_back(new TH1F("hist_Mass4l_ZZ", "Mass 4l", 37, 70, 181));
  hist_Mass4l.push_back(new TH1F("hist_Mass4l_DY", "Mass 4l", 37, 70, 181));

  hist_muonPT.push_back(new TH1F("hist_muonPT_data", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_higgs", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_ZZ", "Muon p_{T}", 20, 0, 300));
  hist_muonPT.push_back(new TH1F("hist_muonPT_DY", "Muon p_{T}", 20, 0, 300));

  hist_elecPT.push_back(new TH1F("hist_elecPT_data", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_higgs", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_ZZ", "Electron p_{T}", 20, 0, 300));
  hist_elecPT.push_back(new TH1F("hist_elecPT_DY", "Electron p_{T}", 20, 0, 300));

  // -----------------------------------------------------------------------------
  //
  int Nsamples = sample_names.size();
  for(int isample=0; isample<Nsamples; isample++){ // loop over all samples
    for(auto channel: sample_channels[isample]){   // loop over all possible channels (4mu, 4el, 2mu,2el)
      // read out files and get Muons and Electrons
      ReadLeptons reader(sample_names[isample], channel);
      vector< vector<Lepton> > Muons = reader.GetMuons();
      vector< vector<Lepton> > Elecs = reader.GetElectrons();

      // now loop over every event
      for(int ievent=0; ievent<Muons.size(); ievent++){
        // fill hists with Muons
        for(int i=0; i<Muons[ievent].size(); i++){
          hist_muonPT[sample_histindex[isample]]->Fill(Muons[ievent][i].Pt(), sample_weights[isample]);
        }
        // fill hists with electrons
        for(int i=0; i<Elecs[ievent].size(); i++){
          hist_elecPT[sample_histindex[isample]]->Fill(Elecs[ievent][i].Pt(), sample_weights[isample]);
        }
      }
    }
  }
  outputFile->Write();
  return 0;
}
