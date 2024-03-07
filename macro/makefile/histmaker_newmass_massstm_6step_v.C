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


void histmaker_newmass_massstm_6step_v(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.85,1.87);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.9,1.92);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.94,1.96);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.99,2.01);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,2.03,2.05);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,2.07,2.09);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,2.11,2.13);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,2.16,2.18);
TH1D*  hnewaq_i = new TH1D("hnewaq_i","hnewaq_i",1000,2.2,2.22);
TH1D*  hnewaq_j = new TH1D("hnewaq_j","hnewaq_j",1000,2.25,2.27);


 cout << " Filling events in Z = 23 region " << endl;

 TFile* file_v = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.v.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_corstm_6th_v = array_mass_corstm_6th_v->GetEntriesFast();

if( hit_mass_corstm_6th_v > 0){

 art::TMassData *mass_corstm_6th_v = (art::TMassData*) array_mass_corstm_6th_v->UncheckedAt(0);

 Double_t aq_select_v = mass_corstm_6th_v->GetAq();

 hnewaq_a->Fill(aq_select_v); 
 hnewaq_b->Fill(aq_select_v); 
 hnewaq_c->Fill(aq_select_v); 
 hnewaq_d->Fill(aq_select_v); 
 hnewaq_e->Fill(aq_select_v); 
 hnewaq_f->Fill(aq_select_v); 
 hnewaq_g->Fill(aq_select_v); 
 hnewaq_h->Fill(aq_select_v); 
 hnewaq_i->Fill(aq_select_v); 
 hnewaq_j->Fill(aq_select_v); 

}  }

   file_v->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_v.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 
 hnewaq_h->Write(); 
 hnewaq_i->Write(); 
 hnewaq_j->Write(); 
 ofile->Close();



}


