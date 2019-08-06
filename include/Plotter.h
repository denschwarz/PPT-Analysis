#include <iostream>
#include <map>
#include <cmath>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TF1.h>
#include <TAxis.h>
#include <TROOT.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <vector>
#include <TLorentzVector.h>
#include <TGaxis.h>
#include <TLatex.h>

using namespace std;

class Plotter{
public:
  Plotter(TString dir);
  void CreatePlot(vector<TH1F*>, TString, TString, double, double, double);
  void SetHiggsColor(Color_t c){ c_Higgs = c;};
  void SetZZColor(Color_t c){ c_ZZ = c;};
  void SetDYColor(Color_t c){ c_DY = c;};
  void Unblind(){ unblinded = true;};
  void Blind(){ unblinded = false;};

private:
  TString directory;
  Color_t c_Higgs = kRed;
  Color_t c_ZZ = kAzure-9;
  Color_t c_DY = kGreen+2;
  bool unblinded = false;
  void ScaleErrors(TH1F* hist, double scale);

};
