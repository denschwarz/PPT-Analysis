#include "../include/ReadLeptons.h"

ReadLeptons::ReadLeptons(TString name, TString channel){
  TString dir = "rootfiles/";
  TFile * file = new TFile(dir+name+".root");
  TTree * tree;
  if(channel == "2mu2el") tree = (TTree *) file->Get("demo/tree2mu2e");
  if(channel == "4el") tree = (TTree *) file->Get("demo/tree4e");
  if(channel == "4mu") tree = (TTree *) file->Get("demo/tree4mu");
  if(channel == "2mu2el"){
    Nevents = tree->GetEntriesFast();
    tree->ResetBranchAddresses();
    tree->SetBranchAddress("px_2mu1",&px_mu1);
    tree->SetBranchAddress("py_2mu1",&py_mu1);
    tree->SetBranchAddress("pz_2mu1",&pz_mu1);
    tree->SetBranchAddress("E_2mu1",&E_mu1);
    tree->SetBranchAddress("px_2mu2",&px_mu2);
    tree->SetBranchAddress("py_2mu2",&py_mu2);
    tree->SetBranchAddress("pz_2mu2",&pz_mu2);
    tree->SetBranchAddress("E_2mu2",&E_mu2);
    tree->SetBranchAddress("px_2e1",&px_el1);
    tree->SetBranchAddress("py_2e1",&py_el1);
    tree->SetBranchAddress("pz_2e1",&pz_el1);
    tree->SetBranchAddress("E_2e1",&E_el1);
    tree->SetBranchAddress("px_2e2",&px_el2);
    tree->SetBranchAddress("py_2e2",&py_el2);
    tree->SetBranchAddress("pz_2e2",&pz_el2);
    tree->SetBranchAddress("E_2e2",&E_el2);
    tree->SetBranchStatus("*",1);
    for(Int_t ievent=0; ievent < Nevents; ievent++) {
      if(tree->GetEntry(ievent)<=0) break;
      TLorentzVector Mu1, Mu2, El1, El2;
      Mu1.SetPxPyPzE(px_mu1, py_mu1, pz_mu1, E_mu1);
      Mu2.SetPxPyPzE(px_mu2, py_mu2, pz_mu2, E_mu2);
      El1.SetPxPyPzE(px_el1, py_el1, pz_el1, E_el1);
      El2.SetPxPyPzE(px_el2, py_el2, pz_el2, E_el2);
      Particle Muon1, Muon2, Elec1, Elec2;
      Muon1.SetVector(Mu1);
      Muon1.SetCharge(-1);
      Muon2.SetVector(Mu2);
      Muon2.SetCharge(1);
      Elec1.SetVector(El1);
      Elec1.SetCharge(-1);
      Elec2.SetVector(El2);
      Elec2.SetCharge(1);
      Muons.push_back( {Muon1, Muon2} );
      Electrons.push_back( {Elec1, Elec2} );
    }
  }
  else if(channel == "4el"){
    Nevents = tree->GetEntriesFast();
    tree->ResetBranchAddresses();
    tree->SetBranchAddress("px_e1",&px_el1);
    tree->SetBranchAddress("py_e1",&py_el1);
    tree->SetBranchAddress("pz_e1",&pz_el1);
    tree->SetBranchAddress("E_e1",&E_el1);
    tree->SetBranchAddress("px_e2",&px_el2);
    tree->SetBranchAddress("py_e2",&py_el2);
    tree->SetBranchAddress("pz_e2",&pz_el2);
    tree->SetBranchAddress("E_e2",&E_el2);
    tree->SetBranchAddress("px_e3",&px_el3);
    tree->SetBranchAddress("py_e3",&py_el3);
    tree->SetBranchAddress("pz_e3",&pz_el3);
    tree->SetBranchAddress("E_e3",&E_el3);
    tree->SetBranchAddress("px_e4",&px_el4);
    tree->SetBranchAddress("py_e4",&py_el4);
    tree->SetBranchAddress("pz_e4",&pz_el4);
    tree->SetBranchAddress("E_e4",&E_el4);
    tree->SetBranchAddress("charge_e1",&charge_el1);
    tree->SetBranchAddress("charge_e2",&charge_el2);
    tree->SetBranchAddress("charge_e3",&charge_el3);
    tree->SetBranchAddress("charge_e4",&charge_el4);
    tree->SetBranchStatus("*",1);
    for(Int_t ievent=0; ievent < Nevents; ievent++) {
      if(tree->GetEntry(ievent)<=0) break;
      TLorentzVector El1, El2, El3, El4;
      El1.SetPxPyPzE(px_el1, py_el1, pz_el1, E_el1);
      El2.SetPxPyPzE(px_el2, py_el2, pz_el2, E_el2);
      El3.SetPxPyPzE(px_el3, py_el3, pz_el3, E_el3);
      El4.SetPxPyPzE(px_el4, py_el4, pz_el4, E_el4);
      Particle Elec1, Elec2, Elec3, Elec4;
      Elec1.SetVector(El1);
      Elec2.SetVector(El2);
      Elec3.SetVector(El3);
      Elec4.SetVector(El4);
      Elec1.SetCharge(charge_el1);
      Elec2.SetCharge(charge_el2);
      Elec3.SetCharge(charge_el3);
      Elec4.SetCharge(charge_el4);
      Muons.push_back( { } );
      Electrons.push_back( {Elec1, Elec2, Elec3, Elec4} );
    }
  }
  else if(channel == "4mu"){
    Nevents = tree->GetEntriesFast();
    tree->ResetBranchAddresses();
    tree->SetBranchAddress("px_mu1",&px_mu1);
    tree->SetBranchAddress("py_mu1",&py_mu1);
    tree->SetBranchAddress("pz_mu1",&pz_mu1);
    tree->SetBranchAddress("E_mu1",&E_mu1);
    tree->SetBranchAddress("px_mu2",&px_mu2);
    tree->SetBranchAddress("py_mu2",&py_mu2);
    tree->SetBranchAddress("pz_mu2",&pz_mu2);
    tree->SetBranchAddress("E_mu2",&E_mu2);
    tree->SetBranchAddress("px_mu3",&px_mu3);
    tree->SetBranchAddress("py_mu3",&py_mu3);
    tree->SetBranchAddress("pz_mu3",&pz_mu3);
    tree->SetBranchAddress("E_mu3",&E_mu3);
    tree->SetBranchAddress("px_mu4",&px_mu4);
    tree->SetBranchAddress("py_mu4",&py_mu4);
    tree->SetBranchAddress("pz_mu4",&pz_mu4);
    tree->SetBranchAddress("E_mu4",&E_mu4);
    tree->SetBranchAddress("charge_mu1",&charge_mu1);
    tree->SetBranchAddress("charge_mu2",&charge_mu2);
    tree->SetBranchAddress("charge_mu3",&charge_mu3);
    tree->SetBranchAddress("charge_mu4",&charge_mu4);
    tree->SetBranchStatus("*",1);
    for(Int_t ievent=0; ievent < Nevents; ievent++) {
      if(tree->GetEntry(ievent)<=0) break;
      TLorentzVector Mu1, Mu2, Mu3, Mu4;
      Mu1.SetPxPyPzE(px_mu1, py_mu1, pz_mu1, E_mu1);
      Mu2.SetPxPyPzE(px_mu2, py_mu2, pz_mu2, E_mu2);
      Mu3.SetPxPyPzE(px_mu3, py_mu3, pz_mu3, E_mu3);
      Mu4.SetPxPyPzE(px_mu4, py_mu4, pz_mu4, E_mu4);
      Particle Muon1, Muon2, Muon3, Muon4;
      Muon1.SetVector(Mu1);
      Muon2.SetVector(Mu2);
      Muon3.SetVector(Mu3);
      Muon4.SetVector(Mu4);
      Muon1.SetCharge(charge_mu1);
      Muon2.SetCharge(charge_mu2);
      Muon3.SetCharge(charge_mu3);
      Muon4.SetCharge(charge_mu4);
      Muons.push_back( {Muon1, Muon2, Muon3, Muon4 } );
      Electrons.push_back( { } );
    }
  }
}
