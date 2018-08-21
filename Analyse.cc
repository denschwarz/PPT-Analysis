#include "Analyse.h"

/*
Dies ist der eigentliche Analyse-Code.
Hier werden die rohen Root Dateien jedes Prozesses eingelesen und verarbeitet.
Ihr koennt hier Variablen zusammensetzen und Histogramme fuellen.
Der Output wird gesammelt in einer weiteren Root Datei abgespeichert.
*/


int main(int argc, char* argv[]){

  // -----------------------------------------------------------------------------
  // Hier wird der Name der Output Datei vergeben
  TString outputName = "Histograms.root";
  outputFile=new TFile(outputName,"recreate");

  // -----------------------------------------------------------------------------
  // Gewichte fuer die MC Simulationen errechnen

  // Gewichte fuer H->ZZ 2012
  double weight_Higgs_12   = (lumi12 * xsecHZZ12) / nevtHZZ12;

  // Gewichte fuer H->ZZ 2011
  double weight_Higgs_11   = (lumi11 * xsecHZZ11) / nevtHZZ11;

  // Gewichte fuer ZZ->4l 2012
  double weight_ZZ4mu_12   = (lumi12 * xsecZZ412 * sfZZ) / nevtZZ4mu12;
  double weight_ZZ4e_12    = (lumi12 * xsecZZ412 * sfZZ) / nevtZZ4e12;
  double weight_ZZ2mu2e_12 = (lumi12 * xsecZZ2mu2e12 * sfZZ) / nevtZZ2mu2e12;

  // Gewichte fuer ZZ->4l 2012
  double weight_ZZ4mu_11   = (lumi11 * xsecZZ411 * sfZZ) / nevtZZ4mu11;
  double weight_ZZ4e_11    = (lumi11 * xsecZZ411 * sfZZ) / nevtZZ4e11;
  double weight_ZZ2mu2e_11 = (lumi11 * xsecZZ2mu2e11 * sfZZ) / nevtZZ2mu2e11;

  // Gewichte fuer DY 2012
  double weight_DY10_12   = (lumi12 * xsecDY1012 * sfDY) / nevtDY1012;
  double weight_DY50_12   = (lumi12 * xsecDY5012 * sfDY) / nevtDY5012;

  // Gewichte fuer DY 2011
  double weight_DY10_11   = (lumi11 * xsecDY1011 * sfDY) / nevtDY1011;
  double weight_DY50_11   = (lumi11 * xsecDY5011 * sfDY) / nevtDY5011;


  // -----------------------------------------------------------------------------
  // Hier werden Histogramme definiert.
  // für jede Variable (z.B. Lepton pT) und jeden Prozess (daten, ZZ, DY, ..) wird ein eigenes Histogramm gefüllt
  hist_leptonPT_data = new TH1F("hist_leptonPT_data", "Lepton p_{T}", 20, 0, 300);
  hist_leptonPT_higgs = new TH1F("hist_leptonPT_higgs", "Lepton p_{T}", 20, 0, 300);
  hist_leptonPT_ZZ = new TH1F("hist_leptonPT_ZZ", "Lepton p_{T}", 20, 0, 300);
  hist_leptonPT_DY = new TH1F("hist_leptonPT_DY", "Lepton p_{T}", 20, 0, 300);

  hist_leptonETA_data = new TH1F("hist_leptonETA_data", "Lepton eta", 30, -4, 4);
  hist_leptonETA_higgs = new TH1F("hist_leptonETA_higgs", "Lepton eta", 30, -4, 4);
  hist_leptonETA_ZZ = new TH1F("hist_leptonETA_ZZ", "Lepton eta", 30, -4, 4);
  hist_leptonETA_DY = new TH1F("hist_leptonETA_DY", "Lepton eta", 30, -4, 4);

  // -----------------------------------------------------------------------------
  // Files angeben, TTree auswaehlen und Histogramme fuellen
  // WICHTIG: Fuer jede Datei Namen und Gewicht uebergeben
  // Dabei wird fuer jeden Zerfallskanal (4e, 4mu, 2e2mu) eine Funktion 'HistogrammFuellen' aufgerufen,
  // welche weiter unten definiert ist. In dieser findet die eigentliche Auswertung statt.

  TString dir = "rootfiles/"; // Ordner in dem die Root Dateien liegen

  // Daten 2011 (der 2mu2el Kanal kommt nur von dem Myonen Datensatz!)
  TFile * file_elek2011 = new TFile(dir+"DATA_Elektron_2011.root");
  TFile * file_myon2011 = new TFile(dir+"DATA_Myon_2011.root");
  HistogrammFuellen4el((TTree *)    file_elek2011->Get("demo/tree4e"),    "data", 1.0);
  HistogrammFuellen2mu2el((TTree *) file_myon2011->Get("demo/tree2mu2e"), "data", 1.0);
  HistogrammFuellen4mu((TTree *)    file_myon2011->Get("demo/tree4mu"),   "data", 1.0);
  delete file_elek2011;
  delete file_myon2011;

  // Daten 2012 (der 2mu2el Kanal kommt nur von dem Myonen Datensatz!)
  TFile * file_elek2012 = new TFile(dir+"DATA_Elektron_2012.root");
  TFile * file_myon2012 = new TFile(dir+"DATA_Myon_2012.root");
  HistogrammFuellen4el((TTree *)    file_elek2012->Get("demo/tree4e"),    "data", 1.0);
  HistogrammFuellen2mu2el((TTree *) file_myon2012->Get("demo/tree2mu2e"), "data", 1.0);
  HistogrammFuellen4mu((TTree *)    file_myon2012->Get("demo/tree4mu"),   "data", 1.0);
  delete file_elek2012;
  delete file_myon2012;

  // Higgs 2011
  TFile * file_higgs2011 = new TFile(dir+"MC_Higgs_2011.root");
  HistogrammFuellen2mu2el((TTree *) file_higgs2011->Get("demo/tree2mu2e"), "higgs", weight_Higgs_11);
  HistogrammFuellen4el((TTree *)    file_higgs2011->Get("demo/tree4e"),    "higgs", weight_Higgs_11);
  HistogrammFuellen4mu((TTree *)    file_higgs2011->Get("demo/tree4mu"),   "higgs", weight_Higgs_11);
  delete file_higgs2011;

  // Higgs 2012
  TFile * file_higgs2012 = new TFile(dir+"MC_Higgs_2012.root");
  HistogrammFuellen2mu2el((TTree *) file_higgs2012->Get("demo/tree2mu2e"), "higgs", weight_Higgs_12);
  HistogrammFuellen4el((TTree *)    file_higgs2012->Get("demo/tree4e"),    "higgs", weight_Higgs_12);
  HistogrammFuellen4mu((TTree *)    file_higgs2012->Get("demo/tree4mu"),   "higgs", weight_Higgs_12);
  delete file_higgs2012;

  // ZZ 2011
  TFile * file_ZZ2e2m2011 = new TFile(dir+"MC_ZZ_2el2mu_2011.root");
  TFile * file_ZZ4e2011 = new TFile(dir+"MC_ZZ_4el_2011.root");
  TFile * file_ZZ4m2011 = new TFile(dir+"MC_ZZ_4mu_2011.root");
  HistogrammFuellen2mu2el((TTree *) file_ZZ2e2m2011->Get("demo/tree2mu2e"), "ZZ", weight_ZZ2mu2e_11);
  HistogrammFuellen4el((TTree *)    file_ZZ4e2011->Get("demo/tree4e"),      "ZZ", weight_ZZ4e_11);
  HistogrammFuellen4mu((TTree *)    file_ZZ4m2011->Get("demo/tree4mu"),     "ZZ", weight_ZZ4mu_11);
  delete file_ZZ2e2m2011;
  delete file_ZZ4e2011;
  delete file_ZZ4m2011;

  // ZZ 2012
  TFile * file_ZZ2e2m2012 = new TFile(dir+"MC_ZZ_2el2mu_2012.root");
  TFile * file_ZZ4e2012 = new TFile(dir+"MC_ZZ_4el_2012.root");
  TFile * file_ZZ4m2012 = new TFile(dir+"MC_ZZ_4mu_2012.root");
  HistogrammFuellen2mu2el((TTree *) file_ZZ2e2m2012->Get("demo/tree2mu2e"), "ZZ", weight_ZZ2mu2e_12);
  HistogrammFuellen4el((TTree *)    file_ZZ4e2012->Get("demo/tree4e"),      "ZZ", weight_ZZ4e_12);
  HistogrammFuellen4mu((TTree *)    file_ZZ4m2012->Get("demo/tree4mu"),     "ZZ", weight_ZZ4mu_12);
  delete file_ZZ2e2m2012;
  delete file_ZZ4e2012;
  delete file_ZZ4m2012;

  // DY 2011
  TFile * file_DY102011 = new TFile(dir+"MC_DY10_2011.root");
  TFile * file_DY502011 = new TFile(dir+"MC_DY50_2011.root");
  HistogrammFuellen2mu2el((TTree *) file_DY102011->Get("demo/tree2mu2e"), "DY", weight_DY10_11);
  HistogrammFuellen4el((TTree *)    file_DY102011->Get("demo/tree4e"),    "DY", weight_DY10_11);
  HistogrammFuellen4mu((TTree *)    file_DY102011->Get("demo/tree4mu"),   "DY", weight_DY10_11);
  HistogrammFuellen2mu2el((TTree *) file_DY502011->Get("demo/tree2mu2e"), "DY", weight_DY50_11);
  HistogrammFuellen4el((TTree *)    file_DY502011->Get("demo/tree4e"),    "DY", weight_DY50_11);
  HistogrammFuellen4mu((TTree *)    file_DY502011->Get("demo/tree4mu"),   "DY", weight_DY50_11);
  delete file_DY102011;
  delete file_DY502011;

  // DY 2012
  TFile * file_DY102012 = new TFile(dir+"MC_DY10_2012.root");
  TFile * file_DY502012 = new TFile(dir+"MC_DY50_2012.root");
  HistogrammFuellen2mu2el((TTree *) file_DY102012->Get("demo/tree2mu2e"), "DY", weight_DY10_12);
  HistogrammFuellen4el((TTree *)    file_DY102012->Get("demo/tree4e"),    "DY", weight_DY10_12);
  HistogrammFuellen4mu((TTree *)    file_DY102012->Get("demo/tree4mu"),   "DY", weight_DY10_12);
  HistogrammFuellen2mu2el((TTree *) file_DY502012->Get("demo/tree2mu2e"), "DY", weight_DY50_12);
  HistogrammFuellen4el((TTree *)    file_DY502012->Get("demo/tree4e"),    "DY", weight_DY50_12);
  HistogrammFuellen4mu((TTree *)    file_DY502012->Get("demo/tree4mu"),   "DY", weight_DY50_12);
  delete file_DY102012;
  delete file_DY502012;


  outputFile->Write();
  return 0;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Hier werden Histogramme fuer den 2 Myonen + 2 Elektronen Kanal geschrieben
//
void HistogrammFuellen2mu2el(TTree* tree, TString name, double weight){
  if(!tree) cout << "Tree konnte nicht gelesen werden \n";
  else      cout << "Fuelle Histogramme "<< name << "...\n";

  if(tree->GetEntriesFast() == 0){
    cout << "    -- TTree is empty" << endl;
    return;
  }

  outputFile->cd();

  // die Variablen aus der ROOT Datei werden hier Variablen zugewiesen, die im Weiteren benutzt werden koennen
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

  // Ueber alle Ereignisse loopen, Vektoren von Myonen/Elektronen erstellen und Histogramme fuellen
  for(Int_t ievent=0; ievent < tree->GetEntriesFast(); ievent++) {
    if(tree->GetEntry(ievent)<=0) break;

    TLorentzVector Mu1_v4, Mu2_v4, El1_v4, El2_v4;
    Mu1_v4.SetPxPyPzE(px_mu1, py_mu1, pz_mu1, E_mu1);
    Mu2_v4.SetPxPyPzE(px_mu2, py_mu2, pz_mu2, E_mu2);
    El1_v4.SetPxPyPzE(px_el1, py_el1, pz_el1, E_el1);
    El2_v4.SetPxPyPzE(px_el2, py_el2, pz_el2, E_el2);

    // zusammenfassen der 4 Leptonen in einen Vektor
    vector<TLorentzVector> Leptonen = {Mu1_v4, Mu2_v4, El1_v4, El2_v4};

    if(name == "data"){
      for(auto lep: Leptonen){
        hist_leptonPT_data->Fill(lep.Pt(), weight);
        hist_leptonETA_data->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "higgs"){
      for(auto lep: Leptonen){
        hist_leptonPT_higgs->Fill(lep.Pt(), weight);
        hist_leptonETA_higgs->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "ZZ"){
      for(auto lep: Leptonen){
        hist_leptonPT_ZZ->Fill(lep.Pt(), weight);
        hist_leptonETA_ZZ->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "DY"){
      for(auto lep: Leptonen){
        hist_leptonPT_DY->Fill(lep.Pt(), weight);
        hist_leptonETA_DY->Fill(lep.Eta(), weight);
      }
    }
  }

  return;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Hier werden Histogramme fuer den 4 Elektronen Kanal geschrieben
//
void HistogrammFuellen4el(TTree* tree, TString name, double weight){
  if(!tree) cout << "Tree konnte nicht gelesen werden \n";
  else      cout << "Fuelle Histogramme "<< name << "...\n";

  if(tree->GetEntriesFast() == 0){
    cout << "    -- TTree is empty" << endl;
    return;
  }

  outputFile->cd();

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

  for(Int_t ievent=0; ievent < tree->GetEntriesFast(); ievent++) {
    if(tree->GetEntry(ievent)<=0) break;

    TLorentzVector El1_v4, El2_v4, El3_v4, El4_v4;
    El1_v4.SetPxPyPzE(px_el1, py_el1, pz_el1, E_el1);
    El2_v4.SetPxPyPzE(px_el2, py_el2, pz_el2, E_el2);
    El3_v4.SetPxPyPzE(px_el3, py_el3, pz_el3, E_el3);
    El4_v4.SetPxPyPzE(px_el4, py_el4, pz_el4, E_el4);
    vector<TLorentzVector> Leptonen = {El1_v4, El2_v4, El3_v4, El4_v4};

    // Histogramme fuellen:
    if(name == "data"){
      for(auto lep: Leptonen){
        hist_leptonPT_data->Fill(lep.Pt(), weight);
        hist_leptonETA_data->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "higgs"){
      for(auto lep: Leptonen){
        hist_leptonPT_higgs->Fill(lep.Pt(), weight);
        hist_leptonETA_higgs->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "ZZ"){
      for(auto lep: Leptonen){
        hist_leptonPT_ZZ->Fill(lep.Pt(), weight);
        hist_leptonETA_ZZ->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "DY"){
      for(auto lep: Leptonen){
        hist_leptonPT_DY->Fill(lep.Pt(), weight);
        hist_leptonETA_DY->Fill(lep.Eta(), weight);
      }
    }
  }

  return;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Hier werden Histogramme fuer den 4 Myonen Kanal geschrieben
//
void HistogrammFuellen4mu(TTree* tree, TString name, double weight){
  if(!tree) cout << "Tree konnte nicht gelesen werden \n";
  else      cout << "Fuelle Histogramme "<< name << "...\n";

  if(tree->GetEntriesFast() == 0){
    cout << "    -- TTree is empty" << endl;
    return;
  }

  outputFile->cd();

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

  for(Int_t ievent=0; ievent < tree->GetEntriesFast(); ievent++) {
    if(tree->GetEntry(ievent)<=0) break;

    TLorentzVector Mu1_v4, Mu2_v4, Mu3_v4, Mu4_v4;
    Mu1_v4.SetPxPyPzE(px_mu1, py_mu1, pz_mu1, E_mu1);
    Mu2_v4.SetPxPyPzE(px_mu2, py_mu2, pz_mu2, E_mu2);
    Mu3_v4.SetPxPyPzE(px_mu3, py_mu3, pz_mu3, E_mu3);
    Mu4_v4.SetPxPyPzE(px_mu4, py_mu4, pz_mu4, E_mu4);
    vector<TLorentzVector> Leptonen = {Mu1_v4, Mu2_v4, Mu3_v4, Mu4_v4};


    // Histogramme fuellen:
    if(name == "data"){
      for(auto lep: Leptonen){
        hist_leptonPT_data->Fill(lep.Pt(), weight);
        hist_leptonETA_data->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "higgs"){
      for(auto lep: Leptonen){
        hist_leptonPT_higgs->Fill(lep.Pt(), weight);
        hist_leptonETA_higgs->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "ZZ"){
      for(auto lep: Leptonen){
        hist_leptonPT_ZZ->Fill(lep.Pt(), weight);
        hist_leptonETA_ZZ->Fill(lep.Eta(), weight);
      }
    }
    else if(name == "DY"){
      for(auto lep: Leptonen){
        hist_leptonPT_DY->Fill(lep.Pt(), weight);
        hist_leptonETA_DY->Fill(lep.Eta(), weight);
      }
    }
  }

  return;
}
