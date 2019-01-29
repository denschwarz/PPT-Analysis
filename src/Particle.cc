#include "../include/Particle.h"



Particle::Particle(TLorentzVector v4_){
  m_v4 = v4_;
}


void Particle::SetVector(TLorentzVector v4_){
  m_v4 = v4_;
  return;
}

void Particle::SetCharge(Int_t charge_){
  m_charge = charge_;
  return;
}

Particle Combine(Particle p1, Particle p2){
  Particle p = p1 + p2;
  return p;
}
