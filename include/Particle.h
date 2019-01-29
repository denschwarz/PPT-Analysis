#pragma once
#include <vector>
#include <TLorentzVector.h>

class Particle{
public:
  Particle(): m_v4(TLorentzVector()), m_charge(0){};
  Particle(TLorentzVector v4_);
  // Particle Combine(Particle other_particle);
  void SetVector(TLorentzVector);
  void SetCharge(Int_t);
  TLorentzVector V4(){return m_v4;};  // gibt 4er-Vektor aus
  Int_t Charge(){return m_charge;};   // gibt Ladung aus
  Double_t Mass(){return m_v4.M();};  // gibt Masse aus
  Double_t Pt(){return m_v4.Pt();};   // gibt pT aus
  Double_t Eta(){return m_v4.Eta();}; // gibt Eta aus
  Double_t Phi(){return m_v4.Phi();}; // gibt Phi aus

  // Overload + operator to add two Particle objects.
  Particle operator+(const Particle& other) {
    Particle p;
    p.m_v4 = this->m_v4 + other.m_v4;
    p.m_charge = this->m_charge + other.m_charge;
    return p;
  }



private:
  TLorentzVector m_v4;
  Int_t m_charge;
};

Particle Combine(Particle p1, Particle p2);
