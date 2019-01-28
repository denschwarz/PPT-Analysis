#include "../include/Particle.h"



Particle::Particle(TLorentzVector v4_){
  v4 = v4_;
}

Particle Particle::Combine(Particle other_particle){
  TLorentzVector new_v4 = v4 + other_particle.V4();
  Particle newParticle(new_v4);
  int charge = charge + other_particle.Charge();
  newParticle.SetCharge(charge);
  return newParticle;
}

void Particle::SetVector(TLorentzVector v4_){
  v4 = v4_;
  return;
}

void Particle::SetCharge(Int_t charge_){
  charge = charge_;
  return;
}
