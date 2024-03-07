#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TTree.h>
#include <TDecompLU.h>
#include <TDecompChol.h>
#include <TString.h>
#include <TClonesArray.h>

#include "TPIDwTOFPPACSSDProcessor.h"
#include "TDiaTimingData.h"
#include "TMWDCTrackingProcessor.h"
#include "TMWDCTrackingResult.h"
#include "TSRPPACPlaneDqdxProcessor.h"

#include <TF1.h>
#include <TH2F.h>
#include <TH2Poly.h>
#include <TDirectory.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TMath.h>
#include "TRandomGraph.h"
#include <TROOT.h>
#include <TSystem.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TNArray.h>
#include <TFile.h>
#include <TArtSystemOfUnit.h>
#include <TStopwatch.h>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_massstm_3step_ref4(){

TH1D*  h_38ca = new TH1D("h38ca_aq","h38ca_aq",5000,1.89,1.91);
TH1D*  h_39ca = new TH1D("h39ca_aq","h39ca_aq",5000,1.94,1.96);
TH1D*  h_41ca = new TH1D("h41ca_aq","h41ca_aq",5000,2.04,2.06);
 
TH1D*  h_40sc = new TH1D("h40sc_aq","h40sc_aq",5000,1.89,1.91);
TH1D*  h_41sc = new TH1D("h41sc_aq","h41sc_aq",5000,1.945,1.965);
TH1D*  h_43sc = new TH1D("h43sc_aq","h43sc_aq",5000,2.035,2.055);
 
TH1D*  h_40ti = new TH1D("h40ti_aq","h40ti_aq",5000,1.805,1.825);
TH1D*  h_41ti = new TH1D("h41ti_aq","h41ti_aq",5000,1.855,1.875);
TH1D*  h_42ti = new TH1D("h42ti_aq","h42ti_aq",5000,1.895,1.915);
 
TH1D*  h_43v  = new TH1D("h43v_aq","h43v_aq",5000,1.855,1.875);
TH1D*  h_44v  = new TH1D("h44v_aq","h44v_aq",5000,1.897,1.917);
TH1D*  h_46v  = new TH1D("h46v_aq","h46v_aq",5000,1.985,2.005);
 
TH1D*  h_44cr = new TH1D("h44cr_aq","h44cr_aq",5000,1.825,1.845);
TH1D*  h_45cr = new TH1D("h45cr_aq","h45cr_aq",5000,1.865,1.885);
TH1D*  h_46cr = new TH1D("h46cr_aq","h46cr_aq",5000,1.90,1.920);
 
TH1D*  h_46mn = new TH1D("h46mn_aq","h46mn_aq",5000,1.83,1.85);
TH1D*  h_47mn = new TH1D("h47mn_aq","h47mn_aq",5000,1.865,1.885);
TH1D*  h_48mn = new TH1D("h48mn_aq","h48mn_aq",5000,1.91,1.93);
 
TH1D*  h_48fe = new TH1D("h48fe_aq","h48fe_aq",5000,1.8355,1.8555);
TH1D*  h_49fe = new TH1D("h49fe_aq","h49fe_aq",5000,1.875,1.895);
TH1D*  h_50fe = new TH1D("h50fe_aq","h50fe_aq",5000,1.91,1.930);


for (int j =0; j < 7; j++){

if(j==0){

 cout << " Filling events in Z = 20 region " << endl;

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.ca.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");

 TClonesArray *array_mass_corstm_3rd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select = mass_corstm_3rd->GetAq();

 h_38ca->Fill(aq_select); 
 h_39ca->Fill(aq_select);
 h_41ca->Fill(aq_select);
// h_40sc->Fill(aq_select);
// h_41sc->Fill(aq_select);
// h_43sc->Fill(aq_select);
// h_40ti->Fill(aq_select);
// h_41ti->Fill(aq_select);
// h_42ti->Fill(aq_select);
//  h_43v->Fill(aq_select);
//  h_44v->Fill(aq_select);
//  h_46v->Fill(aq_select);
// h_44cr->Fill(aq_select);
// h_45cr->Fill(aq_select);
// h_46cr->Fill(aq_select);
// h_46mn->Fill(aq_select);
// h_47mn->Fill(aq_select);
// h_48mn->Fill(aq_select);
// h_48fe->Fill(aq_select);
// h_49fe->Fill(aq_select);
// h_50fe->Fill(aq_select);
     }
   }
 
  file->Close();
}else if(j==1){

 cout << " Filling events in Z = 21 region " << endl;

 TFile* file_sc = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.sc.root"); // Load file. Basically BLD file.
  if(!file_sc){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_sc = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_sc = NULL;

 tree_sc->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass_corstm_BLD_3rd",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_corstm_3rd_sc = array_mass_corstm_3rd_sc->GetEntriesFast();

if( hit_mass_corstm_3rd_sc > 0){

 art::TMassData *mass_corstm_3rd_sc = (art::TMassData*) array_mass_corstm_3rd_sc->UncheckedAt(0);

 Double_t aq_select_sc = mass_corstm_3rd_sc->GetAq();

// h_38ca->Fill(aq_select_sc); 
// h_39ca->Fill(aq_select_sc);
// h_41ca->Fill(aq_select_sc);
 h_40sc->Fill(aq_select_sc);
 h_41sc->Fill(aq_select_sc);
 h_43sc->Fill(aq_select_sc);
// h_40ti->Fill(aq_select_sc);
// h_41ti->Fill(aq_select_sc);
// h_42ti->Fill(aq_select_sc);
//  h_43v->Fill(aq_select_sc);
//  h_44v->Fill(aq_select_sc);
//  h_46v->Fill(aq_select_sc);
// h_44cr->Fill(aq_select_sc);
// h_45cr->Fill(aq_select_sc);
// h_46cr->Fill(aq_select_sc);
// h_46mn->Fill(aq_select_sc);
// h_47mn->Fill(aq_select_sc);
// h_48mn->Fill(aq_select_sc);
// h_48fe->Fill(aq_select_sc);
// h_49fe->Fill(aq_select_sc);
// h_50fe->Fill(aq_select_sc);


} }

   file_sc->Close();  
}else if(j==2){

 cout << " Filling events in Z = 22 region " << endl;

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.ti.root"); // Load file. Basically BLD file.
  if(!file_ti){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ti = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_ti = NULL;

 tree_ti->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_corstm_3rd_ti = array_mass_corstm_3rd_ti->GetEntriesFast();

if( hit_mass_corstm_3rd_ti > 0){

 art::TMassData *mass_corstm_3rd_ti = (art::TMassData*) array_mass_corstm_3rd_ti->UncheckedAt(0);

 Double_t aq_select_ti = mass_corstm_3rd_ti->GetAq();

// h_38ca->Fill(aq_select_ti); 
// h_39ca->Fill(aq_select_ti);
// h_41ca->Fill(aq_select_ti);
// h_40sc->Fill(aq_select_ti);
// h_41sc->Fill(aq_select_ti);
// h_43sc->Fill(aq_select_ti);
 h_40ti->Fill(aq_select_ti);
 h_41ti->Fill(aq_select_ti);
 h_42ti->Fill(aq_select_ti);
//  h_43v->Fill(aq_select_ti);
//  h_44v->Fill(aq_select_ti);
//  h_46v->Fill(aq_select_ti);
// h_44cr->Fill(aq_select_ti);
// h_45cr->Fill(aq_select_ti);
// h_46cr->Fill(aq_select_ti);
// h_46mn->Fill(aq_select_ti);
// h_47mn->Fill(aq_select_ti);
// h_48mn->Fill(aq_select_ti);
// h_48fe->Fill(aq_select_ti);
// h_49fe->Fill(aq_select_ti);
// h_50fe->Fill(aq_select_ti);


}  }

   file_ti->Close();  
}else if(j==3){

 cout << " Filling events in Z = 23 region " << endl;

 TFile* file_v = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.v.root"); // Load file. Basically BLD file.
  if(!file_v){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_v = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_v = NULL;

 tree_v->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_v);
 tree_v->SetBranchStatus("*",0);
 tree_v->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData_v = tree_v->GetEntries();

for (int i=0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_corstm_3rd_v = array_mass_corstm_3rd_v->GetEntriesFast();

if( hit_mass_corstm_3rd_v > 0){

 art::TMassData *mass_corstm_3rd_v = (art::TMassData*) array_mass_corstm_3rd_v->UncheckedAt(0);

 Double_t aq_select_v = mass_corstm_3rd_v->GetAq();

// h_38ca->Fill(aq_select_v); 
// h_39ca->Fill(aq_select_v);
// h_41ca->Fill(aq_select_v);
// h_40sc->Fill(aq_select_v);
// h_41sc->Fill(aq_select_v);
// h_43sc->Fill(aq_select_v);
// h_40ti->Fill(aq_select_v);
// h_41ti->Fill(aq_select_v);
// h_42ti->Fill(aq_select_v);
  h_43v->Fill(aq_select_v);
  h_44v->Fill(aq_select_v);
  h_46v->Fill(aq_select_v);
// h_44cr->Fill(aq_select_v);
// h_45cr->Fill(aq_select_v);
// h_46cr->Fill(aq_select_v);
// h_46mn->Fill(aq_select_v);
// h_47mn->Fill(aq_select_v);
// h_48mn->Fill(aq_select_v);
// h_48fe->Fill(aq_select_v);
// h_49fe->Fill(aq_select_v);
// h_50fe->Fill(aq_select_v);

}  }

   file_v->Close();  
}else if(j==4){

 cout << " Filling events in Z = 24 region " << endl;

 TFile* file_cr = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.cr.root"); // Load file. Basically BLD file.
  if(!file_cr){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_cr = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_cr = NULL;

 tree_cr->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_cr);
 tree_cr->SetBranchStatus("*",0);
 tree_cr->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData_cr = tree_cr->GetEntries();

for (int i=0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_corstm_3rd_cr = array_mass_corstm_3rd_cr->GetEntriesFast();

if( hit_mass_corstm_3rd_cr > 0){

 art::TMassData *mass_corstm_3rd_cr = (art::TMassData*) array_mass_corstm_3rd_cr->UncheckedAt(0);

 Double_t aq_select_cr = mass_corstm_3rd_cr->GetAq();

// h_38ca->Fill(aq_select_cr); 
// h_39ca->Fill(aq_select_cr);
// h_41ca->Fill(aq_select_cr);
// h_40sc->Fill(aq_select_cr);
// h_41sc->Fill(aq_select_cr);
// h_43sc->Fill(aq_select_cr);
// h_40ti->Fill(aq_select_cr);
// h_41ti->Fill(aq_select_cr);
// h_42ti->Fill(aq_select_cr);
//  h_43v->Fill(aq_select_cr);
//  h_44v->Fill(aq_select_cr);
//  h_46v->Fill(aq_select_cr);
 h_44cr->Fill(aq_select_cr);
 h_45cr->Fill(aq_select_cr);
 h_46cr->Fill(aq_select_cr);
// h_46mn->Fill(aq_select_cr);
// h_47mn->Fill(aq_select_cr);
// h_48mn->Fill(aq_select_cr);
// h_48fe->Fill(aq_select_cr);
// h_49fe->Fill(aq_select_cr);
// h_50fe->Fill(aq_select_cr);



}  }

   file_cr->Close();  
}else if(j==5){

 cout << " Filling events in Z = 25 region " << endl;

 TFile* file_mn = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.mn.root"); // Load file. Basically BLD file.
  if(!file_mn){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_mn = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_mn = NULL;

 tree_mn->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_mn);
 tree_mn->SetBranchStatus("*",0);
 tree_mn->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData_mn = tree_mn->GetEntries();

for (int i=0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_corstm_3rd_mn = array_mass_corstm_3rd_mn->GetEntriesFast();

if(  hit_mass_corstm_3rd_mn > 0){

 art::TMassData *mass_corstm_3rd_mn = (art::TMassData*) array_mass_corstm_3rd_mn->UncheckedAt(0);

 Double_t aq_select_mn = mass_corstm_3rd_mn->GetAq();

// h_38ca->Fill(aq_select_mn); 
// h_39ca->Fill(aq_select_mn);
// h_41ca->Fill(aq_select_mn);
// h_40sc->Fill(aq_select_mn);
// h_41sc->Fill(aq_select_mn);
// h_43sc->Fill(aq_select_mn);
// h_40ti->Fill(aq_select_mn);
// h_41ti->Fill(aq_select_mn);
// h_42ti->Fill(aq_select_mn);
//  h_43v->Fill(aq_select_mn);
//  h_44v->Fill(aq_select_mn);
//  h_46v->Fill(aq_select_mn);
// h_44cr->Fill(aq_select_mn);
// h_45cr->Fill(aq_select_mn);
// h_46cr->Fill(aq_select_mn);
 h_46mn->Fill(aq_select_mn);
 h_47mn->Fill(aq_select_mn);
 h_48mn->Fill(aq_select_mn);
// h_48fe->Fill(aq_select_mn);
// h_49fe->Fill(aq_select_mn);
// h_50fe->Fill(aq_select_mn);


 
}  }

   file_mn->Close();  
}else if(j==6){

 cout << " Filling events in Z = 26 region " << endl;

 TFile* file_fe = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.fe.root"); // Load file. Basically BLD file.
  if(!file_fe){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_fe = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_3rd_fe = NULL;

 tree_fe->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd_fe);
 tree_fe->SetBranchStatus("*",0);
 tree_fe->SetBranchStatus("mass_corstm_BLD_3rd",1);


 Int_t nData_fe = tree_fe->GetEntries();

for (int i=0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_corstm_3rd_fe = array_mass_corstm_3rd_fe->GetEntriesFast();

if( hit_mass_corstm_3rd_fe > 0){

 art::TMassData *mass_corstm_3rd_fe = (art::TMassData*) array_mass_corstm_3rd_fe->UncheckedAt(0);

 Double_t aq_select_fe = mass_corstm_3rd_fe->GetAq();

// h_38ca->Fill(aq_select_fe); 
// h_39ca->Fill(aq_select_fe);
// h_41ca->Fill(aq_select_fe);
// h_40sc->Fill(aq_select_fe);
// h_41sc->Fill(aq_select_fe);
// h_43sc->Fill(aq_select_fe);
// h_40ti->Fill(aq_select_fe);
// h_41ti->Fill(aq_select_fe);
// h_42ti->Fill(aq_select_fe);
//  h_43v->Fill(aq_select_fe);
//  h_44v->Fill(aq_select_fe);
//  h_46v->Fill(aq_select_fe);
// h_44cr->Fill(aq_select_fe);
// h_45cr->Fill(aq_select_fe);
// h_46cr->Fill(aq_select_fe);
// h_46mn->Fill(aq_select_fe);
// h_47mn->Fill(aq_select_fe);
// h_48mn->Fill(aq_select_fe);
 h_48fe->Fill(aq_select_fe);
 h_49fe->Fill(aq_select_fe);
 h_50fe->Fill(aq_select_fe);


}  }

   file_fe->Close();  

}}

 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.hist.root","recreate");

 h_38ca->Write(); 
 h_39ca->Write();
 h_41ca->Write();
 h_40sc->Write();
 h_41sc->Write();
 h_43sc->Write();
 h_40ti->Write();
 h_41ti->Write();
 h_42ti->Write();
  h_43v->Write();
  h_44v->Write();
  h_46v->Write();
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


