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
TH1F* hist_EventCount_data;
TH1F* hist_EventCount_higgs;
TH1F* hist_EventCount_ZZ;
TH1F* hist_EventCount_DY;
TH1F* hist_Mass4l_data;
TH1F* hist_Mass4l_higgs;
TH1F* hist_Mass4l_ZZ;
TH1F* hist_Mass4l_DY;
TH1F* hist_leptonPT_data;
TH1F* hist_leptonPT_higgs;
TH1F* hist_leptonPT_ZZ;
TH1F* hist_leptonPT_DY;
TH1F* hist_leptonETA_data;
TH1F* hist_leptonETA_higgs;
TH1F* hist_leptonETA_ZZ;
TH1F* hist_leptonETA_DY;

TFile* outputFile;

// einige konstante Werte

// Luminositaet 2012 und 2011
// (ist ein Maß wie viele Ereignisse mit dem Detektor aufgezeichnet wurden)
Double_t lumi12 = 11580.;
Double_t lumi11 = 2330.;
// MC Wirkungsquerschnitt
// (so etwas wie die Wahrscheinlichkeit, dass ein Prozess stattfindet)
Double_t xsecZZ412 = 0.077;
Double_t xsecZZ2mu2e12 = 0.18;
Double_t xsecZZ411 = 0.067;
Double_t xsecZZ2mu2e11 = 0.15;
Double_t xsecDY5012 = 2955.;
Double_t xsecDY1012 = 10.742;
Double_t xsecDY5011 = 2475.;
Double_t xsecDY1011 = 9507.;
// Higgs  Wirkungsquerschnitt
Double_t xsecHZZ12 = 0.0065;
Double_t xsecHZZ11 = 0.0057;
// Zusatzlicher Faktor fuer ZZ und DY
// ( im Ramen der vollen Analyse gemessen)
Double_t sfZZ = 1.3;
Double_t sfDY = 1.12;
// Anzahl an simulierten Ereignissen
Int_t nevtZZ4mu12 = 1499064;
Int_t nevtZZ4e12 = 1499093;
Int_t nevtZZ2mu2e12 = 1497445;
Int_t nevtHZZ12 = 299973;
Int_t nevtDY5012 = 29426492;
Int_t nevtDY1012 = 6462290;
Int_t nevtZZ4mu11 = 1447136;
Int_t nevtZZ4e11 = 1493308;
Int_t nevtZZ2mu2e11 = 1479879;
Int_t nevtHZZ11 = 299683;
Int_t nevtDY5011 = 36408225;
Int_t nevtDY1011 = 39909640;
