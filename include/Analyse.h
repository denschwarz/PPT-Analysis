#include <iostream>
#include <map>
#include <cmath>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <vector>
#include <TLorentzVector.h>
#include "ReadLeptons.h"
#include "Particle.h"
#include "Samples.h"

using namespace std;

// Funktionen deklarieren
void HistogrammFuellen2mu2el(TTree *, TString, double);
void HistogrammFuellen4el(TTree *, TString, double);
void HistogrammFuellen4mu(TTree *, TString, double);

// Vektoren von Histogrammen deklarieren
vector<TH1F*> hist_EventCount;
vector<TH1F*> hist_muonPT;
vector<TH1F*> hist_elecPT;

// Output Datei deklarieren
TFile* outputFile;
