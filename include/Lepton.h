#pragma once
#include <vector>
#include <TLorentzVector.h>

class Lepton{
public:
  void SetVector(TLorentzVector);
  void SetCharge(Int_t);
  TLorentzVector V4(){return v4;};
  Int_t Charge(){return charge;};
  Double_t Mass(){return v4.M();};
  Double_t Pt(){return v4.Pt();};
  Double_t Eta(){return v4.Eta();};

private:
  TLorentzVector v4;
  Int_t charge;
};
