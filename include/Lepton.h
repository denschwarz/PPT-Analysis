#pragma once
#include <vector>
#include <TLorentzVector.h>

class Lepton{
public:
  void SetVector(TLorentzVector);
  void SetCharge(Int_t);
  TLorentzVector V4(){return v4;};  // gibt 4er-Vektor aus
  Int_t Charge(){return charge;};   // gibt Ladung aus
  Double_t Mass(){return v4.M();};  // gibt Masse aus
  Double_t Pt(){return v4.Pt();};   // gibt pT aus
  Double_t Eta(){return v4.Eta();}; // gibt Eta aus

private:
  TLorentzVector v4;
  Int_t charge;
};
