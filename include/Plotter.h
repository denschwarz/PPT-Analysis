#include <iostream>
#include <map>
#include <cmath>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TAxis.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <vector>
#include <TLorentzVector.h>

using namespace std;
TFile* file;
vector<TH1F*> ReadHistograms(TString);
void CreatePlot(vector<TH1F*>, TString, TString, double, double, double);
