#include <iostream>
#include <cmath>
#include <TMath.h>
#include <TString.h>
#include <vector>

using namespace std;

// Lumi 2012 und 2011
Double_t lumi12 = 11580.;
Double_t lumi11 = 2330.;
// MC Wirkungsquerschnitt
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

// Gewichte fuer die MC Simulationen errechnen
double weight_Higgs_12   = (lumi12 * xsecHZZ12) / nevtHZZ12;
double weight_Higgs_11   = (lumi11 * xsecHZZ11) / nevtHZZ11;
double weight_ZZ4mu_12   = (lumi12 * xsecZZ412 * sfZZ) / nevtZZ4mu12;
double weight_ZZ4e_12    = (lumi12 * xsecZZ412 * sfZZ) / nevtZZ4e12;
double weight_ZZ2mu2e_12 = (lumi12 * xsecZZ2mu2e12 * sfZZ) / nevtZZ2mu2e12;
double weight_ZZ4mu_11   = (lumi11 * xsecZZ411 * sfZZ) / nevtZZ4mu11;
double weight_ZZ4e_11    = (lumi11 * xsecZZ411 * sfZZ) / nevtZZ4e11;
double weight_ZZ2mu2e_11 = (lumi11 * xsecZZ2mu2e11 * sfZZ) / nevtZZ2mu2e11;
double weight_DY10_12   = (lumi12 * xsecDY1012 * sfDY) / nevtDY1012;
double weight_DY50_12   = (lumi12 * xsecDY5012 * sfDY) / nevtDY5012;
double weight_DY10_11   = (lumi11 * xsecDY1011 * sfDY) / nevtDY1011;
double weight_DY50_11   = (lumi11 * xsecDY5011 * sfDY) / nevtDY5011;

// Liste aller Dateinamen
vector<TString> sample_names = {
  "DATA_Elektron_2011",
  "DATA_Elektron_2012",
  "DATA_Myon_2011",
  "DATA_Myon_2012",
  "MC_DY10_2011",
  "MC_DY10_2012",
  "MC_DY50_2011",
  "MC_DY50_2012",
  "MC_ZZ_4el_2011",
  "MC_ZZ_4el_2012",
  "MC_ZZ_4mu_2011",
  "MC_ZZ_4mu_2012",
  "MC_ZZ_2el2mu_2011",
  "MC_ZZ_2el2mu_2012",
  "MC_Higgs_2011",
  "MC_Higgs_2012"
};

// Gewichte für alle Prozesse
vector<double> sample_weights = {
  1,
  1,
  1,
  1,
  weight_DY10_11,
  weight_DY10_12,
  weight_DY50_11,
  weight_DY50_12,
  weight_ZZ4e_11,
  weight_ZZ4e_12,
  weight_ZZ4mu_11,
  weight_ZZ4mu_12,
  weight_ZZ2mu2e_11,
  weight_ZZ2mu2e_12,
  weight_Higgs_11,
  weight_Higgs_12
};

// Hier sind mögliche Kanäle für jede Datei angegeben
vector<vector<TString>> sample_channels = {
  // data (nur Myon Datei für 2mu2el benutzen, weil sonst doppelt gezählt wird)
  {"4el"},
  {"4el"},
  {"4mu", "2mu2el"},
  {"4mu", "2mu2el"},
  // DY
  {"4el", "4mu", "2mu2el"},
  {"4el", "4mu", "2mu2el"},
  {"4el", "4mu", "2mu2el"},
  {"4el", "4mu", "2mu2el"},
  // ZZ
  {"4el"},
  {"4el"},
  {"4mu"},
  {"4mu"},
  {"2mu2el"},
  {"2mu2el"},
  // Higgs
  {"4el", "4mu", "2mu2el"},
  {"4el", "4mu", "2mu2el"}
};

// Histogramm Index gibt an zu welchem Prozess eine Datei gehört
// (data 0, Higgs 1, ZZ 2, DY 3)
vector<int> sample_histindex = {
  // data
  0,
  0,
  0,
  0,
  // DY
  3,
  3,
  3,
  3,
  // ZZ
  2,
  2,
  2,
  2,
  2,
  2,
  // Higgs
  1,
  1
};
