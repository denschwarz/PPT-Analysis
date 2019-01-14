#include "../include/Lepton.h"

void Lepton::SetVector(TLorentzVector v4_){
  v4 = v4_;
  return;
}

void Lepton::SetCharge(Int_t charge_){
  charge = charge_;
  return;
}
