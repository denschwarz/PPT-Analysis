#pragma once
#include <vector>
#include <TLorentzVector.h>

class Particle{
public:
  Particle(): v4(TLorentzVector()), charge(0){};
  Particle(TLorentzVector v4_);
  Particle Combine(Particle other_particle);
  void SetVector(TLorentzVector);
  void SetCharge(Int_t);
  TLorentzVector V4(){return v4;};  // gibt 4er-Vektor aus
  Int_t Charge(){return charge;};   // gibt Ladung aus
  Double_t Mass(){return v4.M();};  // gibt Masse aus
  Double_t Pt(){return v4.Pt();};   // gibt pT aus
  Double_t Eta(){return v4.Eta();}; // gibt Eta aus
  Double_t Phi(){return v4.Phi();}; // gibt Phi aus

  // Overload + operator to add two Particle objects.
  Particle operator+(const Particle& other) {
    Particle p;
    p.v4 = this->v4 + other.v4;
    p.charge = this->charge + other.charge;
    return p;
  }



private:
  TLorentzVector v4;
  Int_t charge;
};
