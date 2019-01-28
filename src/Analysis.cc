#include "../include/Analysis.h"

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
  TFile* outputFile=new TFile(outputName,"recreate");

  // -----------------------------------------------------------------------------
  // Hier werden Histogramme definiert.
  // Dabei ist für jede Größe ein Vektor definiert.
  // Dieser Vektor enthält je ein Histogramm für jeden Prozess (Daten, Higgs, ZZ, DY)
  vector<TH1F*> hist_EventCount = CreateHistograms("EventCount",1, 0, 2);
  vector<TH1F*> hist_muonNUMBER = CreateHistograms("muonNUMBER", 6, -0.5, 5.5);
  vector<TH1F*> hist_muonPT = CreateHistograms("muonPT", 20, 0, 300);
  vector<TH1F*> hist_muonPHI = CreateHistograms("muonPHI", 20, -4, 4);
  vector<TH1F*> hist_muonETA = CreateHistograms("muonETA", 20, -3, 3);
  vector<TH1F*> hist_muonCHARGE = CreateHistograms("muonCHARGE", 5, -2.5, 2.5);
  vector<TH1F*> hist_elecNUMBER = CreateHistograms("elecNUMBER", 6, -0.5, 5.5);
  vector<TH1F*> hist_elecPT = CreateHistograms("elecPT", 20, 0, 300);
  vector<TH1F*> hist_Z1 = CreateHistograms("Z1", 20, 0, 300);
  vector<TH1F*> hist_Z2 = CreateHistograms("Z2", 20, 0, 300);

  // -----------------------------------------------------------------------------
  // Hier findet die eigentliche Analyse statt.
  // Dabei wird jede Root-Datei geöffnet und ausgelesen.
  // Daraus erhält man je eine Liste an Elektronen und Myonen.
  // Diese werden dann für die Analyse ausgewertet

  int Nsamples = sample_names.size(); // Anzahl an Root-Dateien
  for(int isample=0; isample<Nsamples; isample++){ // Schleife über alle Root-Dateien
    for(auto channel: sample_channels[isample]){   // Schleife über alle möglichen Kanäle einer Datei
      // mögliche Kanäle: "4el", "4mu", "2mu2el"
      cout << "Analising " << sample_names[isample] << "..." << endl;

      // Hier werden die Dateien ausgelesen und Vektoren von Myonen und Elektronen erstellt
      ReadLeptons reader(sample_names[isample], channel);
      int Nevents = reader.GetEventCount();
      vector< vector<Particle> > allMuons = reader.GetMuons();
      vector< vector<Particle> > allElecs = reader.GetElectrons();
      ////

      // Gewicht, Histindex auslesen
      TString process =  sample_process[isample];
      double weight = sample_weights[isample];
      ////


      // In der eigentlichen Analyse führen wir für jedes Ereignis aus.
      // Da wir immer das gleiche für jedes Ereignis tun, benutzen wir hier eine Schleife.
      for(int ievent=0; ievent<Nevents; ievent++){
        vector<Particle> Muons = allMuons[ievent]; // Myonen für dieses Ereignis
        vector<Particle> Elecs = allElecs[ievent]; // Elektronen für dieses Ereignis

        // dieses Hist zählt Ereignisse
        FillHistogram(hist_EventCount, 1, weight, process);

        // So wird z.B. ein Z rekostruiert:
        if(channel == "2mu2el"){
          Particle Z1;
          Z1 = Muons[0].Combine(Muons[1]);
          Particle Z2;
          Z2 = Elecs[0].Combine(Elecs[1]);
          if( fabs(Z1.Mass() - 90) < fabs(Z2.Mass() - 90) ){
            FillHistogram(hist_Z1, Z1.Mass(), weight, process);
            FillHistogram(hist_Z2, Z2.Mass(), weight, process);
          }
          else{
            FillHistogram(hist_Z1, Z2.Mass(), weight, process);
            FillHistogram(hist_Z2, Z1.Mass(), weight, process);
          }
        }

        // Anzahl an Elektronen bzw. Myonen
        int numberMUONS = Muons.size();
        int numberELECS = Elecs.size();
        FillHistogram(hist_muonNUMBER, numberMUONS, weight, process);
        FillHistogram(hist_elecNUMBER, numberELECS, weight, process);

        // Schleife über alle Myonen in einem Ereignis
        for(int i=0; i<Muons.size(); i++){
          // Variablen von Myon auslesen
          double pt = Muons[i].Pt();
          double eta = Muons[i].Eta();
          double phi = Muons[i].Phi();
          int charge = Muons[i].Charge();
          // in Histogramme füllen
          FillHistogram(hist_muonPT, pt, weight, process);
          FillHistogram(hist_muonETA, eta, weight, process);
          FillHistogram(hist_muonPHI, phi, weight, process);
          FillHistogram(hist_muonCHARGE, charge, weight, process);
        }
        ////

        // Schleife über alle Electronen in einem Ereignis
        for(int i=0; i<Elecs.size(); i++){
          double pt = Elecs[i].Pt();
          FillHistogram(hist_elecPT, pt, weight, process);
        }
        ////
      }
    }
  }
  // Abspeichern in einer neuen Datei.
  outputFile->Write();
  return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Hier werden Histogramme kreiert
vector<TH1F*> CreateHistograms(TString histname, int nbins, double min, double max){
  vector<TH1F*> hists;
  vector<TString> processes = {"data", "higgs", "ZZ", "DY"};
  for(auto process: processes){
    hists.push_back(new TH1F("hist_"+histname+"_"+process, " ", nbins, min, max));
  }
  return hists;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// mit dieser Funtion werden Histogramme gefüllt
void FillHistogram(vector<TH1F*> hists, double value, double weight, TString process){
  int index;
  if(process == "data") index = 0;
  else if (process == "higgs") index = 1;
  else if (process == "ZZ") index = 2;
  else if (process == "DY") index = 3;
  else cout << "[ERROR] the process name '" << process << "' does not exist!" << endl;
  hists[index]->Fill(value, weight);
  return;
}
