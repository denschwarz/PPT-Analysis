#include "../include/Root2CSV.h"
#include "../include/Samples.h"

int main(int argc, char* argv[]){
  TString dir = "rootfiles/";
  for(unsigned int i=0; i<sample_names.size(); i++){
    TFile * file = new TFile(dir+sample_names[i]+".root");
    std::ofstream csvfile;
    csvfile.open("csvfiles/"+sample_names[i]+".csv");
    for(auto channel: sample_channels[i]){
      TTree * tree;
      if(channel == "2mu2el") tree = (TTree *) file->Get("demo/tree2mu2e");
      if(channel == "4el") tree = (TTree *) file->Get("demo/tree4e");
      if(channel == "4mu") tree = (TTree *) file->Get("demo/tree4mu");

      if(channel == "2mu2el"){
        int Nevents = tree->GetEntriesFast();
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
          csvfile << px_mu1 << "," << py_mu1 << "," << pz_mu1 << "," << E_mu1 << ",";
          csvfile << px_mu2 << "," << py_mu2 << "," << pz_mu2 << "," << E_mu2 << ",";
          csvfile << px_el1 << "," << py_el1 << "," << pz_el1 << "," << E_el1 << ",";
          csvfile << px_el2 << "," << py_el2 << "," << pz_el2 << "," << E_el2 << "\n";
        }
      }
      else if(channel == "4el"){
        int Nevents = tree->GetEntriesFast();
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
        tree->SetBranchStatus("*",1);
        for(Int_t ievent=0; ievent < Nevents; ievent++) {
          if(tree->GetEntry(ievent)<=0) break;
          csvfile << px_el1 << "," << py_el1 << "," << pz_el1 << "," << E_el1 << ",";
          csvfile << px_el2 << "," << py_el2 << "," << pz_el2 << "," << E_el2 << ",";
          csvfile << px_el3 << "," << py_el3 << "," << pz_el3 << "," << E_el3 << ",";
          csvfile << px_el4 << "," << py_el4 << "," << pz_el4 << "," << E_el4 << "\n";
        }
      }
      else if(channel == "4mu"){
        int Nevents = tree->GetEntriesFast();
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
        tree->SetBranchStatus("*",1);
        for(Int_t ievent=0; ievent < Nevents; ievent++) {
          if(tree->GetEntry(ievent)<=0) break;
          csvfile << px_mu1 << "," << py_mu1 << "," << pz_mu1 << "," << E_mu1 << ",";
          csvfile << px_mu2 << "," << py_mu2 << "," << pz_mu2 << "," << E_mu2 << ",";
          csvfile << px_mu3 << "," << py_mu3 << "," << pz_mu3 << "," << E_mu3 << ",";
          csvfile << px_mu4 << "," << py_mu4 << "," << pz_mu4 << "," << E_mu4 << "\n";
        }
      }
    }
    csvfile.close();
  }
  return 0;
}
