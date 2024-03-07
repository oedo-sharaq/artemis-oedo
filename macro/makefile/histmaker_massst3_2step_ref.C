#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_massst3_2step_ref(){

TH1D*  h_39ca = new TH1D("h39ca_aq","h39ca_aq",1000,1.94,1.96);
TH1D*  h_40ca = new TH1D("h40ca_aq","h40ca_aq",1000,1.99,2.01);
TH1D*  h_41ca = new TH1D("h41ca_aq","h41ca_aq",1000,2.04,2.06);
 
TH1D*  h_40sc = new TH1D("h40sc_aq","h40sc_aq",1000,1.90,1.92);
TH1D*  h_41sc = new TH1D("h41sc_aq","h41sc_aq",1000,1.945,1.965);
TH1D*  h_43sc = new TH1D("h43sc_aq","h43sc_aq",1000,2.04,2.06);
 
TH1D*  h_40ti = new TH1D("h40ti_aq","h40ti_aq",1000,1.805,1.825);
TH1D*  h_41ti = new TH1D("h41ti_aq","h41ti_aq",1000,1.855,1.875);
TH1D*  h_43ti = new TH1D("h43ti_aq","h43ti_aq",1000,1.940,1.960);
 
TH1D*  h_43v  = new TH1D("h43v_aq","h43v_aq",1000,1.865,1.886);
TH1D*  h_44v  = new TH1D("h44v_aq","h44v_aq",1000,1.900,1.920);
TH1D*  h_45v  = new TH1D("h45v_aq","h45v_aq",1000,1.941,1.961);
 
TH1D*  h_44cr = new TH1D("h44cr_aq","h44cr_aq",1000,1.825,1.845);
TH1D*  h_45cr = new TH1D("h45cr_aq","h45cr_aq",1000,1.855,1.875);
TH1D*  h_46cr = new TH1D("h46cr_aq","h46cr_aq",1000,1.90,1.920);
 
TH1D*  h_46mn = new TH1D("h46mn_aq","h46mn_aq",1000,1.832,1.852);
TH1D*  h_47mn = new TH1D("h47mn_aq","h47mn_aq",1000,1.86,1.88);
TH1D*  h_48mn = new TH1D("h48mn_aq","h48mn_aq",1000,1.90,1.92);
 
TH1D*  h_48fe = new TH1D("h48fe_aq","h48fe_aq",1000,1.8355,1.8555);
TH1D*  h_49fe = new TH1D("h49fe_aq","h49fe_aq",1000,1.875,1.895);
TH1D*  h_50fe = new TH1D("h50fe_aq","h50fe_aq",1000,1.91,1.930);



for (int j =0; j < 7; j++){

if(j==0){

 cout << " Filling events in Z = 20 region " << endl;

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.ca.root");

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mass_corst3_2nd = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass = array_mass->GetEntriesFast();
 Int_t hit_mass_corst3_2nd = array_mass_corst3_2nd->GetEntriesFast();

if( hit_mass > 0 && hit_mass_corst3_2nd > 0){

 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd = (art::TMassData*) array_mass_corst3_2nd->UncheckedAt(0);
// art::TEventHeader *eventheader = (art::TEventHeader*) array_eventheader->UncheckedAt(0);

Double_t z_select = mass->GetZ();
Double_t aq_select = mass_corst3_2nd->GetAq();

 h_39ca->Fill(aq_select); 
 h_40ca->Fill(aq_select);
 h_41ca->Fill(aq_select);
 h_40sc->Fill(aq_select);
 h_41sc->Fill(aq_select);
 h_43sc->Fill(aq_select);
 h_40ti->Fill(aq_select);
 h_41ti->Fill(aq_select);
 h_43ti->Fill(aq_select);
 h_43v->Fill(aq_select);
 h_44v->Fill(aq_select);
 h_45v->Fill(aq_select);
 h_44cr->Fill(aq_select);
 h_45cr->Fill(aq_select);
 h_46cr->Fill(aq_select);
 h_46mn->Fill(aq_select);
 h_47mn->Fill(aq_select);
 h_48mn->Fill(aq_select);
 h_48fe->Fill(aq_select);
 h_49fe->Fill(aq_select);
 h_50fe->Fill(aq_select);

   }
 }

//: cout << "End Ca" << endl; 
  file->Close();
}else if(j==1){

 cout << " Filling events in Z = 21 region " << endl;

 TFile* file_sc = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.sc.root");

 TClonesArray *array_mass_sc = NULL;
 TClonesArray *array_mass_corst3_2nd_sc = NULL;
 TTree *tree_sc = (TTree*) gDirectory->Get("tree");

 tree_sc->SetBranchAddress("mass",&array_mass_sc);
 tree_sc->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass",1);
 tree_sc->SetBranchStatus("mass_corst3_2nd",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_sc = array_mass_sc->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_sc = array_mass_corst3_2nd_sc->GetEntriesFast();

if( hit_mass_sc > 0 && hit_mass_corst3_2nd_sc > 0){

 art::TMassData *mass_sc = (art::TMassData*) array_mass_sc->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_sc = (art::TMassData*) array_mass_corst3_2nd_sc->UncheckedAt(0);
// art::TEventHeader *eventheader_sc = (art::TEventHeader*) array_eventheader_sc->UncheckedAt(0);

 Double_t z_select_sc = mass_sc->GetZ();
 Double_t aq_select_sc = mass_corst3_2nd_sc->GetAq();

// h_39ca->Fill(aq_select_sc); 
// h_40ca->Fill(aq_select_sc);
// h_41ca->Fill(aq_select_sc);
 h_40sc->Fill(aq_select_sc);
 h_41sc->Fill(aq_select_sc);
 h_43sc->Fill(aq_select_sc);
 h_40ti->Fill(aq_select_sc);
 h_41ti->Fill(aq_select_sc);
 h_43ti->Fill(aq_select_sc);
  h_43v->Fill(aq_select_sc);
  h_44v->Fill(aq_select_sc);
  h_45v->Fill(aq_select_sc);
 h_44cr->Fill(aq_select_sc);
 h_45cr->Fill(aq_select_sc);
 h_46cr->Fill(aq_select_sc);
 h_46mn->Fill(aq_select_sc);
 h_47mn->Fill(aq_select_sc);
 h_48mn->Fill(aq_select_sc);
 h_48fe->Fill(aq_select_sc);
 h_49fe->Fill(aq_select_sc);
 h_50fe->Fill(aq_select_sc);


} }

   file_sc->Close();  
}else if(j==2){

 cout << " Filling events in Z = 22 region " << endl;

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.ti.root");

 TClonesArray *array_mass_ti = NULL;
 TClonesArray *array_mass_corst3_2nd_ti = NULL;
 TTree *tree_ti = (TTree*) gDirectory->Get("tree");

 tree_ti->SetBranchAddress("mass",&array_mass_ti);
 tree_ti->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass",1);
 tree_ti->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_ti = array_mass_ti->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_ti = array_mass_corst3_2nd_ti->GetEntriesFast();

if( hit_mass_ti > 0 && hit_mass_corst3_2nd_ti > 0){

 art::TMassData *mass_ti = (art::TMassData*) array_mass_ti->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_ti = (art::TMassData*) array_mass_corst3_2nd_ti->UncheckedAt(0);
// art::TEventHeader *eventheader_ti = (art::TEventHeader*) array_eventheader_ti->UncheckedAt(0);

 Double_t z_select_ti = mass_ti->GetZ();
 Double_t aq_select_ti = mass_corst3_2nd_ti->GetAq();

// h_39ca->Fill(aq_select_ti); 
// h_40ca->Fill(aq_select_ti);
// h_41ca->Fill(aq_select_ti);
 h_40sc->Fill(aq_select_ti);
 h_41sc->Fill(aq_select_ti);
 h_43sc->Fill(aq_select_ti);
 h_40ti->Fill(aq_select_ti);
 h_41ti->Fill(aq_select_ti);
 h_43ti->Fill(aq_select_ti);
  h_43v->Fill(aq_select_ti);
  h_44v->Fill(aq_select_ti);
  h_45v->Fill(aq_select_ti);
 h_44cr->Fill(aq_select_ti);
 h_45cr->Fill(aq_select_ti);
 h_46cr->Fill(aq_select_ti);
 h_46mn->Fill(aq_select_ti);
 h_47mn->Fill(aq_select_ti);
 h_48mn->Fill(aq_select_ti);
 h_48fe->Fill(aq_select_ti);
 h_49fe->Fill(aq_select_ti);
 h_50fe->Fill(aq_select_ti);


}  }

   file_ti->Close();  
}else if(j==3){

 cout << " Filling events in Z = 23 region " << endl;

 TFile* file_v = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.v.root");

 TClonesArray *array_mass_v = NULL;
 TClonesArray *array_mass_corst3_2nd_v = NULL;
 TTree *tree_v = (TTree*) gDirectory->Get("tree");

 tree_v->SetBranchAddress("mass",&array_mass_v);
 tree_v->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_v);
 tree_v->SetBranchStatus("*",0);
 tree_v->SetBranchStatus("mass",1);
 tree_v->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData_v = tree_v->GetEntries();

for (int i=0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_v = array_mass_v->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_v = array_mass_corst3_2nd_v->GetEntriesFast();

if( hit_mass_v > 0 && hit_mass_corst3_2nd_v > 0){

 art::TMassData *mass_v = (art::TMassData*) array_mass_v->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_v = (art::TMassData*) array_mass_corst3_2nd_v->UncheckedAt(0);
// art::TEventHeader *eventheader_v = (art::TEventHeader*) array_eventheader_v->UncheckedAt(0);

 Double_t z_select_v = mass_v->GetZ();
 Double_t aq_select_v = mass_corst3_2nd_v->GetAq();

// h_39ca->Fill(aq_select_v); 
// h_40ca->Fill(aq_select_v);
// h_41ca->Fill(aq_select_v);
 h_40sc->Fill(aq_select_v);
 h_41sc->Fill(aq_select_v);
 h_43sc->Fill(aq_select_v);
 h_40ti->Fill(aq_select_v);
 h_41ti->Fill(aq_select_v);
 h_43ti->Fill(aq_select_v);
  h_43v->Fill(aq_select_v);
  h_44v->Fill(aq_select_v);
  h_45v->Fill(aq_select_v);
 h_44cr->Fill(aq_select_v);
 h_45cr->Fill(aq_select_v);
 h_46cr->Fill(aq_select_v);
 h_46mn->Fill(aq_select_v);
 h_47mn->Fill(aq_select_v);
 h_48mn->Fill(aq_select_v);
 h_48fe->Fill(aq_select_v);
 h_49fe->Fill(aq_select_v);
 h_50fe->Fill(aq_select_v);


}  }

   file_v->Close();  
}else if(j==4){

 cout << " Filling events in Z = 24 region " << endl;

 TFile* file_cr = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.cr.root");

 TClonesArray *array_mass_cr = NULL;
 TClonesArray *array_mass_corst3_2nd_cr = NULL;
 TTree *tree_cr = (TTree*) gDirectory->Get("tree");

 tree_cr->SetBranchAddress("mass",&array_mass_cr);
 tree_cr->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_cr);
 tree_cr->SetBranchStatus("*",0);
 tree_cr->SetBranchStatus("mass",1);
 tree_cr->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData_cr = tree_cr->GetEntries();

for (int i=0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_cr = array_mass_cr->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_cr = array_mass_corst3_2nd_cr->GetEntriesFast();

if( hit_mass_cr > 0 && hit_mass_corst3_2nd_cr > 0){

 art::TMassData *mass_cr = (art::TMassData*) array_mass_cr->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_cr = (art::TMassData*) array_mass_corst3_2nd_cr->UncheckedAt(0);
// art::TEventHeader *eventheader_cr = (art::TEventHeader*) array_eventheader_cr->UncheckedAt(0);

 Double_t z_select_cr = mass_cr->GetZ();
 Double_t aq_select_cr = mass_corst3_2nd_cr->GetAq();

// h_39ca->Fill(aq_select_cr); 
// h_40ca->Fill(aq_select_cr);
// h_41ca->Fill(aq_select_cr);
 h_40sc->Fill(aq_select_cr);
 h_41sc->Fill(aq_select_cr);
 h_43sc->Fill(aq_select_cr);
 h_40ti->Fill(aq_select_cr);
 h_41ti->Fill(aq_select_cr);
 h_43ti->Fill(aq_select_cr);
  h_43v->Fill(aq_select_cr);
  h_44v->Fill(aq_select_cr);
  h_45v->Fill(aq_select_cr);
 h_44cr->Fill(aq_select_cr);
 h_45cr->Fill(aq_select_cr);
 h_46cr->Fill(aq_select_cr);
 h_46mn->Fill(aq_select_cr);
 h_47mn->Fill(aq_select_cr);
 h_48mn->Fill(aq_select_cr);
 h_48fe->Fill(aq_select_cr);
 h_49fe->Fill(aq_select_cr);
 h_50fe->Fill(aq_select_cr);


}  }

   file_cr->Close();  
}else if(j==5){

 cout << " Filling events in Z = 25 region " << endl;

 TFile* file_mn = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.mn.root");

 TClonesArray *array_mass_mn = NULL;
 TClonesArray *array_mass_corst3_2nd_mn = NULL;
 TTree *tree_mn = (TTree*) gDirectory->Get("tree");

 tree_mn->SetBranchAddress("mass",&array_mass_mn);
 tree_mn->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_mn);
 tree_mn->SetBranchStatus("*",0);
 tree_mn->SetBranchStatus("mass",1);
 tree_mn->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData_mn = tree_mn->GetEntries();

for (int i=0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_mn = array_mass_mn->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_mn = array_mass_corst3_2nd_mn->GetEntriesFast();

if( hit_mass_mn > 0 && hit_mass_corst3_2nd_mn > 0){

 art::TMassData *mass_mn = (art::TMassData*) array_mass_mn->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_mn = (art::TMassData*) array_mass_corst3_2nd_mn->UncheckedAt(0);
// art::TEventHeader *eventheader_mn = (art::TEventHeader*) array_eventheader_mn->UncheckedAt(0);

 Double_t z_select_mn = mass_mn->GetZ();
 Double_t aq_select_mn = mass_corst3_2nd_mn->GetAq();

// h_39ca->Fill(aq_select_mn); 
// h_40ca->Fill(aq_select_mn);
// h_41ca->Fill(aq_select_mn);
 h_40sc->Fill(aq_select_mn);
 h_41sc->Fill(aq_select_mn);
 h_43sc->Fill(aq_select_mn);
 h_40ti->Fill(aq_select_mn);
 h_41ti->Fill(aq_select_mn);
 h_43ti->Fill(aq_select_mn);
  h_43v->Fill(aq_select_mn);
  h_44v->Fill(aq_select_mn);
  h_45v->Fill(aq_select_mn);
 h_44cr->Fill(aq_select_mn);
 h_45cr->Fill(aq_select_mn);
 h_46cr->Fill(aq_select_mn);
 h_46mn->Fill(aq_select_mn);
 h_47mn->Fill(aq_select_mn);
 h_48mn->Fill(aq_select_mn);
 h_48fe->Fill(aq_select_mn);
 h_49fe->Fill(aq_select_mn);
 h_50fe->Fill(aq_select_mn);


 
}  }

   file_mn->Close();  
}else if(j==6){

 cout << " Filling events in Z = 26 region " << endl;

 TFile* file_fe = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.fe.root");

 TClonesArray *array_mass_fe = NULL;
 TClonesArray *array_mass_corst3_2nd_fe = NULL;
 TTree *tree_fe = (TTree*) gDirectory->Get("tree");

 tree_fe->SetBranchAddress("mass",&array_mass_fe);
 tree_fe->SetBranchAddress("mass_corst3_2nd",&array_mass_corst3_2nd_fe);
 tree_fe->SetBranchStatus("*",0);
 tree_fe->SetBranchStatus("mass",1);
 tree_fe->SetBranchStatus("mass_corst3_2nd",1);


 Int_t nData_fe = tree_fe->GetEntries();

for (int i=0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_fe = array_mass_fe->GetEntriesFast();
 Int_t hit_mass_corst3_2nd_fe = array_mass_corst3_2nd_fe->GetEntriesFast();

if( hit_mass_fe > 0 && hit_mass_corst3_2nd_fe > 0){

 art::TMassData *mass_fe = (art::TMassData*) array_mass_fe->UncheckedAt(0);
 art::TMassData *mass_corst3_2nd_fe = (art::TMassData*) array_mass_corst3_2nd_fe->UncheckedAt(0);
// art::TEventHeader *eventheader_fe = (art::TEventHeader*) array_eventheader_fe->UncheckedAt(0);

 Double_t z_select_fe = mass_fe->GetZ();
 Double_t aq_select_fe = mass_corst3_2nd_fe->GetAq();

// h_39ca->Fill(aq_select_fe); 
// h_40ca->Fill(aq_select_fe);
// h_41ca->Fill(aq_select_fe);
 h_40sc->Fill(aq_select_fe);
 h_41sc->Fill(aq_select_fe);
 h_43sc->Fill(aq_select_fe);
 h_40ti->Fill(aq_select_fe);
 h_41ti->Fill(aq_select_fe);
 h_43ti->Fill(aq_select_fe);
  h_43v->Fill(aq_select_fe);
  h_44v->Fill(aq_select_fe);
  h_45v->Fill(aq_select_fe);
 h_44cr->Fill(aq_select_fe);
 h_45cr->Fill(aq_select_fe);
 h_46cr->Fill(aq_select_fe);
 h_46mn->Fill(aq_select_fe);
 h_47mn->Fill(aq_select_fe);
 h_48mn->Fill(aq_select_fe);
 h_48fe->Fill(aq_select_fe);
 h_49fe->Fill(aq_select_fe);
 h_50fe->Fill(aq_select_fe);



}  }

   file_fe->Close();  

}}

 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/mass_corst3_2nd_ref.170272.hist.root","recreate");

 h_39ca->Write(); 
 h_40ca->Write();
 h_41ca->Write();
 h_40sc->Write();
 h_41sc->Write();
 h_43sc->Write();
 h_40ti->Write();
 h_41ti->Write();
 h_43ti->Write();
 h_43v->Write();
 h_44v->Write();
 h_45v->Write();
 h_44cr->Write();
 h_45cr->Write();
 h_46cr->Write();
 h_46mn->Write();
 h_47mn->Write();
 h_48mn->Write();
 h_48fe->Write();
 h_49fe->Write();
 h_50fe->Write();


 ofile->Close();



}


