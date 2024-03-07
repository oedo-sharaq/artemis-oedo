#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_st2_2step(){


 TH2D *hzaq = new TH2D("hzaq","hzaq",500,1.94,1.96,200,18,23);

for (int j =0; j < 3; j++){

if(j==0){
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.ca.root");

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mass_corst2_2nd = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_corst2_2nd",&array_mass_corst2_2nd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_corst2_2nd",1);


 Int_t nData = tree->GetEntries();
 cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass = array_mass->GetEntriesFast();
 Int_t hit_mass_corst2_2nd = array_mass_corst2_2nd->GetEntriesFast();

if( hit_mass > 0 && hit_mass_corst2_2nd > 0){

 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
 art::TMassData *mass_corst2_2nd = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);

Double_t z_select = mass->GetZ();
 Double_t aq_select = mass_corst2_2nd->GetAq();

  hzaq->Fill(aq_select,z_select);
  }
 }

 cout << "End Ca" << endl; 
  file->Close();
}else if(j==1){

 cout << "Start Sc" << endl; 
 TFile* file_sc = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.sc.root");

 TClonesArray *array_mass_sc = NULL;
 TClonesArray *array_mass_corst2_2nd_sc = NULL;
 TTree *tree_sc = (TTree*) gDirectory->Get("tree");

 tree_sc->SetBranchAddress("mass",&array_mass_sc);
 tree_sc->SetBranchAddress("mass_corst2_2nd",&array_mass_corst2_2nd_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass",1);
 tree_sc->SetBranchStatus("mass_corst2_2nd",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_sc = array_mass_sc->GetEntriesFast();
 Int_t hit_mass_corst2_2nd_sc = array_mass_corst2_2nd_sc->GetEntriesFast();

if( hit_mass_sc > 0 && hit_mass_corst2_2nd_sc > 0){

 art::TMassData *mass_sc = (art::TMassData*) array_mass_sc->UncheckedAt(0);
 art::TMassData *mass_corst2_2nd_sc = (art::TMassData*) array_mass_corst2_2nd_sc->UncheckedAt(0);

 Double_t z_select_sc = mass_sc->GetZ();
 Double_t aq_select_sc = mass_corst2_2nd_sc->GetAq();

   hzaq->Fill(aq_select_sc,z_select_sc);
} }

   file_sc->Close();  
}else{

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.ti.root");

 TClonesArray *array_mass_ti = NULL;
 TClonesArray *array_mass_corst2_2nd_ti = NULL;
 TTree *tree_ti = (TTree*) gDirectory->Get("tree");

 tree_ti->SetBranchAddress("mass",&array_mass_ti);
 tree_ti->SetBranchAddress("mass_corst2_2nd",&array_mass_corst2_2nd_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass",1);
 tree_ti->SetBranchStatus("mass_corst2_2nd",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_ti = array_mass_ti->GetEntriesFast();
 Int_t hit_mass_corst2_2nd_ti = array_mass_corst2_2nd_ti->GetEntriesFast();

if( hit_mass_ti > 0 && hit_mass_corst2_2nd_ti > 0){

 art::TMassData *mass_ti = (art::TMassData*) array_mass_ti->UncheckedAt(0);
 art::TMassData *mass_corst2_2nd_ti = (art::TMassData*) array_mass_corst2_2nd_ti->UncheckedAt(0);

 Double_t z_select_ti = mass_ti->GetZ();
 Double_t aq_select_ti = mass_corst2_2nd_ti->GetAq();

   hzaq->Fill(aq_select_ti,z_select_ti);
}  }

   file_ti->Close();  
  }
}

 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_st2_2step.cascti.170272.hist.root","recreate");
 hzaq->Write();
 ofile->Close();



}


