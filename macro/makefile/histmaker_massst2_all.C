#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_massst2_all(){


 TH2D *hzaq = new TH2D("hzaq","hzaq",1000,1.7,2.3,300,18,30);

for (int j =0; j < 7; j++){

if(j==0){
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.ca.root");

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mass_corst2 = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_corst2",&array_mass_corst2);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_corst2",1);


 Int_t nData = tree->GetEntries();
 cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass = array_mass->GetEntriesFast();
 Int_t hit_mass_corst2 = array_mass_corst2->GetEntriesFast();

if( hit_mass > 0 && hit_mass_corst2 > 0){

 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
 art::TMassData *mass_corst2 = (art::TMassData*) array_mass_corst2->UncheckedAt(0);

Double_t z_select = mass->GetZ();
 Double_t aq_select = mass_corst2->GetAq();

  hzaq->Fill(aq_select,z_select);
  }
 }

 cout << "End Ca" << endl; 
  file->Close();
}else if(j==1){

 cout << "Start Sc" << endl; 
 TFile* file_sc = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.sc.root");

 TClonesArray *array_mass_sc = NULL;
 TClonesArray *array_mass_corst2_sc = NULL;
 TTree *tree_sc = (TTree*) gDirectory->Get("tree");

 tree_sc->SetBranchAddress("mass",&array_mass_sc);
 tree_sc->SetBranchAddress("mass_corst2",&array_mass_corst2_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass",1);
 tree_sc->SetBranchStatus("mass_corst2",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_sc = array_mass_sc->GetEntriesFast();
 Int_t hit_mass_corst2_sc = array_mass_corst2_sc->GetEntriesFast();

if( hit_mass_sc > 0 && hit_mass_corst2_sc > 0){

 art::TMassData *mass_sc = (art::TMassData*) array_mass_sc->UncheckedAt(0);
 art::TMassData *mass_corst2_sc = (art::TMassData*) array_mass_corst2_sc->UncheckedAt(0);

 Double_t z_select_sc = mass_sc->GetZ();
 Double_t aq_select_sc = mass_corst2_sc->GetAq();

   hzaq->Fill(aq_select_sc,z_select_sc);
} }

   file_sc->Close();  
}else if(j==2){

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.ti.root");

 TClonesArray *array_mass_ti = NULL;
 TClonesArray *array_mass_corst2_ti = NULL;
 TTree *tree_ti = (TTree*) gDirectory->Get("tree");

 tree_ti->SetBranchAddress("mass",&array_mass_ti);
 tree_ti->SetBranchAddress("mass_corst2",&array_mass_corst2_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass",1);
 tree_ti->SetBranchStatus("mass_corst2",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_ti = array_mass_ti->GetEntriesFast();
 Int_t hit_mass_corst2_ti = array_mass_corst2_ti->GetEntriesFast();

if( hit_mass_ti > 0 && hit_mass_corst2_ti > 0){

 art::TMassData *mass_ti = (art::TMassData*) array_mass_ti->UncheckedAt(0);
 art::TMassData *mass_corst2_ti = (art::TMassData*) array_mass_corst2_ti->UncheckedAt(0);

 Double_t z_select_ti = mass_ti->GetZ();
 Double_t aq_select_ti = mass_corst2_ti->GetAq();

   hzaq->Fill(aq_select_ti,z_select_ti);
}  }

   file_ti->Close();  
}else if(j==3){

 TFile* file_v = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.v.root");

 TClonesArray *array_mass_v = NULL;
 TClonesArray *array_mass_corst2_v = NULL;
 TTree *tree_v = (TTree*) gDirectory->Get("tree");

 tree_v->SetBranchAddress("mass",&array_mass_v);
 tree_v->SetBranchAddress("mass_corst2",&array_mass_corst2_v);
 tree_v->SetBranchStatus("*",0);
 tree_v->SetBranchStatus("mass",1);
 tree_v->SetBranchStatus("mass_corst2",1);


 Int_t nData_v = tree_v->GetEntries();

for (int i=0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_v = array_mass_v->GetEntriesFast();
 Int_t hit_mass_corst2_v = array_mass_corst2_v->GetEntriesFast();

if( hit_mass_v > 0 && hit_mass_corst2_v > 0){

 art::TMassData *mass_v = (art::TMassData*) array_mass_v->UncheckedAt(0);
 art::TMassData *mass_corst2_v = (art::TMassData*) array_mass_corst2_v->UncheckedAt(0);

 Double_t z_select_v = mass_v->GetZ();
 Double_t aq_select_v = mass_corst2_v->GetAq();

   hzaq->Fill(aq_select_v,z_select_v);
}  }

   file_v->Close();  
}else if(j==4){

 TFile* file_cr = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.cr.root");

 TClonesArray *array_mass_cr = NULL;
 TClonesArray *array_mass_corst2_cr = NULL;
 TTree *tree_cr = (TTree*) gDirectory->Get("tree");

 tree_cr->SetBranchAddress("mass",&array_mass_cr);
 tree_cr->SetBranchAddress("mass_corst2",&array_mass_corst2_cr);
 tree_cr->SetBranchStatus("*",0);
 tree_cr->SetBranchStatus("mass",1);
 tree_cr->SetBranchStatus("mass_corst2",1);


 Int_t nData_cr = tree_cr->GetEntries();

for (int i=0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_cr = array_mass_cr->GetEntriesFast();
 Int_t hit_mass_corst2_cr = array_mass_corst2_cr->GetEntriesFast();

if( hit_mass_cr > 0 && hit_mass_corst2_cr > 0){

 art::TMassData *mass_cr = (art::TMassData*) array_mass_cr->UncheckedAt(0);
 art::TMassData *mass_corst2_cr = (art::TMassData*) array_mass_corst2_cr->UncheckedAt(0);

 Double_t z_select_cr = mass_cr->GetZ();
 Double_t aq_select_cr = mass_corst2_cr->GetAq();

   hzaq->Fill(aq_select_cr,z_select_cr);
}  }

   file_cr->Close();  
}else if(j==5){

 TFile* file_mn = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.mn.root");

 TClonesArray *array_mass_mn = NULL;
 TClonesArray *array_mass_corst2_mn = NULL;
 TTree *tree_mn = (TTree*) gDirectory->Get("tree");

 tree_mn->SetBranchAddress("mass",&array_mass_mn);
 tree_mn->SetBranchAddress("mass_corst2",&array_mass_corst2_mn);
 tree_mn->SetBranchStatus("*",0);
 tree_mn->SetBranchStatus("mass",1);
 tree_mn->SetBranchStatus("mass_corst2",1);


 Int_t nData_mn = tree_mn->GetEntries();

for (int i=0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_mn = array_mass_mn->GetEntriesFast();
 Int_t hit_mass_corst2_mn = array_mass_corst2_mn->GetEntriesFast();

if( hit_mass_mn > 0 && hit_mass_corst2_mn > 0){

 art::TMassData *mass_mn = (art::TMassData*) array_mass_mn->UncheckedAt(0);
 art::TMassData *mass_corst2_mn = (art::TMassData*) array_mass_corst2_mn->UncheckedAt(0);

 Double_t z_select_mn = mass_mn->GetZ();
 Double_t aq_select_mn = mass_corst2_mn->GetAq();

   hzaq->Fill(aq_select_mn,z_select_mn);
}  }

   file_mn->Close();  
}else if(j==6){

 TFile* file_fe = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.fe.root");

 TClonesArray *array_mass_fe = NULL;
 TClonesArray *array_mass_corst2_fe = NULL;
 TTree *tree_fe = (TTree*) gDirectory->Get("tree");

 tree_fe->SetBranchAddress("mass",&array_mass_fe);
 tree_fe->SetBranchAddress("mass_corst2",&array_mass_corst2_fe);
 tree_fe->SetBranchStatus("*",0);
 tree_fe->SetBranchStatus("mass",1);
 tree_fe->SetBranchStatus("mass_corst2",1);


 Int_t nData_fe = tree_fe->GetEntries();

for (int i=0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_fe = array_mass_fe->GetEntriesFast();
 Int_t hit_mass_corst2_fe = array_mass_corst2_fe->GetEntriesFast();

if( hit_mass_fe > 0 && hit_mass_corst2_fe > 0){

 art::TMassData *mass_fe = (art::TMassData*) array_mass_fe->UncheckedAt(0);
 art::TMassData *mass_corst2_fe = (art::TMassData*) array_mass_corst2_fe->UncheckedAt(0);

 Double_t z_select_fe = mass_fe->GetZ();
 Double_t aq_select_fe = mass_corst2_fe->GetAq();

   hzaq->Fill(aq_select_fe,z_select_fe);
}  }

   file_fe->Close();  
}}

 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/mass_corst2_all.170272.hist.root","recreate");
 hzaq->Write();
 ofile->Close();



}


