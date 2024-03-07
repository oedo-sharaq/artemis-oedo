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


void histmaker_a2z4_massstm_6step(){

TH1D*  ha2z4_aq = new TH1D("ha2z4_aq","ha2z4_aq",5000,1.825,1.855);


for (int j =0; j < 9; j++){

if(j==0){

 cout << " Filling events in Z = 20 region " << endl;

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.ca.root"); // Load file. Basically BLD file.
  if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");

 TClonesArray *array_mass_corstm_6th = NULL;

 tree->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData = tree->GetEntries();
// cout << "Nevent Ca =" << nData << endl;
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass_corstm_6th = array_mass_corstm_6th->GetEntriesFast();

if( hit_mass_corstm_6th > 0){

 art::TMassData *mass_corstm_6th = (art::TMassData*) array_mass_corstm_6th->UncheckedAt(0);

 Double_t aq_select = mass_corstm_6th->GetAq();

 ha2z4_aq->Fill(aq_select); 
     }
   }
 
  file->Close();
}else if(j==1){

 cout << " Filling events in Z = 21 region " << endl;

 TFile* file_sc = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.sc.root"); // Load file. Basically BLD file.
  if(!file_sc){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_sc = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_sc = NULL;

 tree_sc->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass_corstm_BLD_6th",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_corstm_6th_sc = array_mass_corstm_6th_sc->GetEntriesFast();

if( hit_mass_corstm_6th_sc > 0){

 art::TMassData *mass_corstm_6th_sc = (art::TMassData*) array_mass_corstm_6th_sc->UncheckedAt(0);

 Double_t aq_select_sc = mass_corstm_6th_sc->GetAq();

 ha2z4_aq->Fill(aq_select_sc);


} }

   file_sc->Close();  
}else if(j==2){

 cout << " Filling events in Z = 22 region " << endl;

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.ti.root"); // Load file. Basically BLD file.
  if(!file_ti){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ti = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_ti = NULL;

 tree_ti->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_corstm_6th_ti = array_mass_corstm_6th_ti->GetEntriesFast();

if( hit_mass_corstm_6th_ti > 0){

 art::TMassData *mass_corstm_6th_ti = (art::TMassData*) array_mass_corstm_6th_ti->UncheckedAt(0);

 Double_t aq_select_ti = mass_corstm_6th_ti->GetAq();

 ha2z4_aq->Fill(aq_select_ti);


}  }

   file_ti->Close();  
}else if(j==3){

 cout << " Filling events in Z = 23 region " << endl;

 TFile* file_v = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.v.root"); // Load file. Basically BLD file.
  if(!file_v){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_v = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_v = NULL;

 tree_v->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_v);
 tree_v->SetBranchStatus("*",0);
 tree_v->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_v = tree_v->GetEntries();

for (int i=0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_corstm_6th_v = array_mass_corstm_6th_v->GetEntriesFast();

if( hit_mass_corstm_6th_v > 0){

 art::TMassData *mass_corstm_6th_v = (art::TMassData*) array_mass_corstm_6th_v->UncheckedAt(0);

 Double_t aq_select_v = mass_corstm_6th_v->GetAq();

 ha2z4_aq->Fill(aq_select_v);

}  }

   file_v->Close();  
}else if(j==4){

 cout << " Filling events in Z = 24 region " << endl;

 TFile* file_cr = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.cr.root"); // Load file. Basically BLD file.
  if(!file_cr){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_cr = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_cr = NULL;

 tree_cr->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_cr);
 tree_cr->SetBranchStatus("*",0);
 tree_cr->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_cr = tree_cr->GetEntries();

for (int i=0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_corstm_6th_cr = array_mass_corstm_6th_cr->GetEntriesFast();

if( hit_mass_corstm_6th_cr > 0){

 art::TMassData *mass_corstm_6th_cr = (art::TMassData*) array_mass_corstm_6th_cr->UncheckedAt(0);

 Double_t aq_select_cr = mass_corstm_6th_cr->GetAq();

 ha2z4_aq->Fill(aq_select_cr);



}  }

   file_cr->Close();  
}else if(j==5){

 cout << " Filling events in Z = 25 region " << endl;

 TFile* file_mn = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.mn.root"); // Load file. Basically BLD file.
  if(!file_mn){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_mn = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_mn = NULL;

 tree_mn->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_mn);
 tree_mn->SetBranchStatus("*",0);
 tree_mn->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_mn = tree_mn->GetEntries();

for (int i=0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_corstm_6th_mn = array_mass_corstm_6th_mn->GetEntriesFast();

if(  hit_mass_corstm_6th_mn > 0){

 art::TMassData *mass_corstm_6th_mn = (art::TMassData*) array_mass_corstm_6th_mn->UncheckedAt(0);

 Double_t aq_select_mn = mass_corstm_6th_mn->GetAq();

 ha2z4_aq->Fill(aq_select_mn);


 
}  }

   file_mn->Close();  
}else if(j==6){

 cout << " Filling events in Z = 26 region " << endl;

 TFile* file_fe = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.fe.root"); // Load file. Basically BLD file.
  if(!file_fe){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_fe = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_fe = NULL;

 tree_fe->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_fe);
 tree_fe->SetBranchStatus("*",0);
 tree_fe->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_fe = tree_fe->GetEntries();

for (int i=0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_corstm_6th_fe = array_mass_corstm_6th_fe->GetEntriesFast();

if( hit_mass_corstm_6th_fe > 0){

 art::TMassData *mass_corstm_6th_fe = (art::TMassData*) array_mass_corstm_6th_fe->UncheckedAt(0);

 Double_t aq_select_fe = mass_corstm_6th_fe->GetAq();

 ha2z4_aq->Fill(aq_select_fe);


}  }

   file_fe->Close();  

}else if(j==7){

 cout << " Filling events in Z = 27 region " << endl;

 TFile* file_co = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.co.root"); // Load file. Basically BLD file.
  if(!file_co){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_co = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_co = NULL;

 tree_co->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_co);
 tree_co->SetBranchStatus("*",0);
 tree_co->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_co = tree_co->GetEntries();

for (int i=0; i < nData_co; i++){
 tree_co->GetEntry(i);

 Int_t hit_mass_corstm_6th_co = array_mass_corstm_6th_co->GetEntriesFast();

if( hit_mass_corstm_6th_co > 0){

 art::TMassData *mass_corstm_6th_co = (art::TMassData*) array_mass_corstm_6th_co->UncheckedAt(0);

 Double_t aq_select_co = mass_corstm_6th_co->GetAq();

 ha2z4_aq->Fill(aq_select_co);


}  }

   file_co->Close();  

}else if(j==8){

 cout << " Filling events in Z = 28 region " << endl;

 TFile* file_ni = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.ni.root"); // Load file. Basically BLD file.
  if(!file_ni){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ni = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_ni = NULL;

 tree_ni->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_ni);
 tree_ni->SetBranchStatus("*",0);
 tree_ni->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_ni = tree_ni->GetEntries();

for (int i = 0; i < nData_ni; i++){
 tree_ni->GetEntry(i);

 Int_t hit_mass_corstm_6th_ni = array_mass_corstm_6th_ni->GetEntriesFast();

if( hit_mass_corstm_6th_ni > 0){

 art::TMassData *mass_corstm_6th_ni = (art::TMassData*) array_mass_corstm_6th_ni->UncheckedAt(0);

 Double_t aq_select_ni = mass_corstm_6th_ni->GetAq();

 ha2z4_aq->Fill(aq_select_ni);


}  }

   file_ni->Close();  

}}

 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/a2z4_stm2_6step.eventstore.170272.hist.root","recreate");

 ha2z4_aq->Write(); 

 ofile->Close();



}


