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
#include "Lepton.h"
#include "Samples.h"

using namespace std;

// Funktionen werden hier deklariert
void HistogrammFuellen2mu2el(TTree *, TString, double);
void HistogrammFuellen4el(TTree *, TString, double);
void HistogrammFuellen4mu(TTree *, TString, double);

// Variablen werden hier deklariert
Double_t px_mu1, py_mu1, pz_mu1, E_mu1;
Double_t px_mu2, py_mu2, pz_mu2, E_mu2;
Double_t px_mu3, py_mu3, pz_mu3, E_mu3;
Double_t px_mu4, py_mu4, pz_mu4, E_mu4;
Double_t px_el1, py_el1, pz_el1, E_el1;
Double_t px_el2, py_el2, pz_el2, E_el2;
Double_t px_el3, py_el3, pz_el3, E_el3;
Double_t px_el4, py_el4, pz_el4, E_el4;
Int_t charge_mu1, charge_mu2, charge_mu3, charge_mu4;
Int_t charge_el1, charge_el2, charge_el3, charge_el4;

// Histogramme hier deklarieren
vector<TH1F*> hist_EventCount;
vector<TH1F*> hist_Mass4l;
vector<TH1F*> hist_muonPT;
vector<TH1F*> hist_elecPT;

TFile* outputFile;
