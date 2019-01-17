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
vector<TH1F*> CreateHistograms(TString, int, double, double);
void FillHistogram(vector<TH1F*>, double, double, TString);
