#include "../include/Particle.h"

void Particle::SetVector(TLorentzVector v4_){
  v4 = v4_;
  return;
}

void Particle::SetCharge(Int_t charge_){
  charge = charge_;
  return;
}
