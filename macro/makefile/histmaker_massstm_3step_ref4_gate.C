#ifndef __CINT__
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
#endif



void histmaker_massstm_3step_ref4_gate(){

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

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.ca.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.ca.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);


 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){


 h_38ca->Fill(aq_select); 
 h_39ca->Fill(aq_select);
 h_41ca->Fill(aq_select);
     }
   }
 }

  file->Close();
}else if(j==1){

 cout << " Filling events in Z = 21 region " << endl;

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.sc.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.sc.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_sc = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_sc = mass_corstm_3rd_sc->GetAq();

 h_40sc->Fill(aq_select_sc);
 h_41sc->Fill(aq_select_sc);
 h_43sc->Fill(aq_select_sc);

   } 
  }
}
   file->Close();  
}else if(j==2){

 cout << " Filling events in Z = 22 region " << endl;

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_ti = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_ti = mass_corstm_3rd_ti->GetAq();

 h_40ti->Fill(aq_select_ti);
 h_41ti->Fill(aq_select_ti);
 h_42ti->Fill(aq_select_ti);

   } 
  }
}

   file->Close();  
}else if(j==3){

 cout << " Filling events in Z = 23 region " << endl;

TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.v.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.v.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_v = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_v = mass_corstm_3rd_v->GetAq();

  h_43v->Fill(aq_select_v);
  h_44v->Fill(aq_select_v);
  h_46v->Fill(aq_select_v);

   } 
  }
}
   file->Close();  
}else if(j==4){

 cout << " Filling events in Z = 24 region " << endl;

TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.cr.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.cr.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_cr = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_cr = mass_corstm_3rd_cr->GetAq();

 h_44cr->Fill(aq_select_cr);
 h_45cr->Fill(aq_select_cr);
 h_46cr->Fill(aq_select_cr);

   } 
  }
}
   file->Close();  
}else if(j==5){

 cout << " Filling events in Z = 25 region " << endl;

TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.mn.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.mn.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_mn = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_mn = mass_corstm_3rd_mn->GetAq();

 h_46mn->Fill(aq_select_mn);
 h_47mn->Fill(aq_select_mn);
 h_48mn->Fill(aq_select_mn);

   } 
  }
}
   file->Close();  
}else if(j==6){

 cout << " Filling events in Z = 26 region " << endl;


TFile* file = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.fe.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.fe.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_mass_corstm_3rd = NULL;
 TClonesArray *array_trackd = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_3rd",&array_mass_corstm_3rd);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_3rd",1);
 tree->SetBranchStatus("s2",1);

 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_3rd = array_mass_corstm_3rd->GetEntriesFast();
 Int_t hit_trackd = array_trackd->GetEntriesFast();

if( hit_mass_corstm_3rd > 0 && hit_trackd > 0){

 art::TMassData *mass_corstm_3rd = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);
 art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);

Double_t aq_select = mass_corstm_3rd->GetAq();
Bool_t trackd_ok = trackd_tmp->IsGood();
Double_t ssrd = trackd_tmp->GetSSR();
Double_t var3d = trackd_tmp->GetVar(3) * 1000;
Double_t y2 = trackd_tmp->GetY();

 if (trackd_ok && var3d < 0.002 && ssrd < 0.1 && 15 < y2 && y2 < 24){

 art::TMassData *mass_corstm_3rd_fe = (art::TMassData*) array_mass_corstm_3rd->UncheckedAt(0);

 Double_t aq_select_fe = mass_corstm_3rd_fe->GetAq();

 h_48fe->Fill(aq_select_fe);
 h_49fe->Fill(aq_select_fe);
 h_50fe->Fill(aq_select_fe);


   } 
  }
}
   file->Close();  

}}

// TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref_BVar.eventstore.170272.hist.root","recreate");
 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVarY.eventstore.170272.hist.root","recreate");

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


