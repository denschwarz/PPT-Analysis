#include "../include/Analysis.h"

/*
Dies ist der eigentliche Analyse-Code.
Hier werden die rohen Root Dateien jedes Prozesses eingelesen und verarbeitet.
Ihr koennt hier Variablen zusammensetzen und Histogramme fuellen.
Der Output wird gesammelt in einer weiteren Root Datei abgespeichert.
*/


int main(int argc, char* argv[]){

  // ---------------------------------------------------------------------------
  // Hier wird der Name der Output Datei vergeben
  TString outputName = "Histograms.root";
  TFile* outputFile=new TFile(outputName,"recreate");

  // ---------------------------------------------------------------------------
  // Hier werden Histogramme definiert.
  // Dabei ist für jede Größe ein Vektor definiert.
  // Dieser Vektor enthält je ein Histogramm für jeden Prozess (Daten, Higgs, ZZ, DY)
  vector<TH1F*> hist_EventCount = CreateHistograms("EventCount",1, 0, 2);
  vector<TH1F*> hist_muonNUMBER = CreateHistograms("muonNUMBER", 6, -0.5, 5.5);
  vector<TH1F*> hist_muonPT = CreateHistograms("muonPT", 20, 0, 200);
  vector<TH1F*> hist_muonPHI = CreateHistograms("muonPHI", 20, -4, 4);
  vector<TH1F*> hist_muonETA = CreateHistograms("muonETA", 20, -3, 3);
  vector<TH1F*> hist_muonCHARGE = CreateHistograms("muonCHARGE", 5, -2.5, 2.5);
  vector<TH1F*> hist_elecPT = CreateHistograms("elecPT", 20, 0, 200);
  vector<TH1F*> hist_Zmass = CreateHistograms("Zmass", 20, 0, 150);

  // ---------------------------------------------------------------------------
  // Hier findet die eigentliche Analyse statt.
  // Dabei wird jede Root-Datei geöffnet und ausgelesen.
  // Daraus erhält man je eine Liste an Elektronen und Myonen.
  // Diese werden dann für die Analyse ausgewertet
  int events_2mu2el = 0;

  int Nsamples = sample_names.size();              // Anzahl an Root-Dateien
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

      // events in data zählen
      if(process == "data"){
        if(channel == "2mu2el") events_2mu2el += Nevents;
      }
      ////

      /*
      In der eigentlichen Analyse führen wir für jedes Ereignis aus.
      Da wir immer das gleiche für jedes Ereignis tun, benutzen wir hier eine Schleife.
      */
      for(int ievent=0; ievent<Nevents; ievent++){
        /*
        Für jedes Ereignis wird zunächst eine Liste Myonen und eine Liste
        Elektronen angelegt. Diese können im weiteren Verlauf analysiert werden.
        */
        vector<Particle> Muons = allMuons[ievent];
        vector<Particle> Elecs = allElecs[ievent];

        /*
        In dieses Histogramm wird für ein Ereignis immer für der selber Wert (1)
        eingetragen. Damit enthält es am Ende exakt die Anzahl an Ereignissen.
        */
        FillHistogram(hist_EventCount, 1, weight, process);



        // Anzahl an Elektronen bzw. Myonen
        int numberMUONS = Muons.size();
        FillHistogram(hist_muonNUMBER, numberMUONS, weight, process);

        // Schleife über alle Myonen in einem Ereignis -------------------------
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
        // ---------------------------------------------------------------------


        // Schleife über alle Elektronen in einem Ereignis ---------------------
        for(int i=0; i<Elecs.size(); i++){
          // Variablen von Elektronen auslesen
          double pt = Elecs[i].Pt();
          // in Histogramme füllen
          FillHistogram(hist_elecPT, pt, weight, process);
        }
        // ---------------------------------------------------------------------


        // Aufteilung nach Zerfallskanälen -------------------------------------
        if(channel == "2mu2el"){
          /*
          Hier wird ein Z aus Myonen und ein Z aus Elektronen rekonstruiert
          In dem 2mu2el Kanal ist hier die Zuordnung eindeutig, weil ein Z
          immer in 2 Myonen oder 2 Elektronen zerfällt.
          */
          Particle Z1 = Combine(Muons[0], Muons[1]);
          Particle Z2 = Combine(Elecs[0], Elecs[1]);
          FillHistogram(hist_Zmass, Z1.Mass(), weight, process);
          FillHistogram(hist_Zmass, Z2.Mass(), weight, process);
        }
        else if(channel == "4mu"){
          // Hier können Funktionen speziell für den 4 Myonen Kanal eingefügt werden
        }
        else if(channel == "4el"){
          // Hier können Funktionen speziell für den 4 Myonen Kanal eingefügt werden
        }
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
      }
    }
  }
  cout << "---------------------------------------------" << endl;
  cout << "---------------------------------------------" << endl;
  cout << "Events in 2mu2el: " << events_2mu2el << endl;

  // Am Ende: Abspeichern der Histogramme in der Output Datei
  outputFile->Write();
  return 0;
}


// -----------------------------------------------------------------------------
// Diese Funktion wird aufgerufen um Histogramme zu erstellen ------------------
vector<TH1F*> CreateHistograms(TString histname, int nbins, double min, double max){
  vector<TH1F*> hists;
  vector<TString> processes = {"data", "higgs", "ZZ", "DY"};
  for(auto process: processes){
    hists.push_back(new TH1F("hist_"+histname+"_"+process, " ", nbins, min, max));
  }
  return hists;
}
// -----------------------------------------------------------------------------
// Diese Funktion wird aufgerufen um Histogramme zu füllen ---------------------
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
