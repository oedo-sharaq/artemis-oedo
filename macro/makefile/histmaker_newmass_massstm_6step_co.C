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


void histmaker_newmass_massstm_6step_co(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.80,1.82);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.82,1.84);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.84,1.86);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.86,1.88);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.88,1.90);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,1.90,1.92);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,1.92,1.94);


 cout << " Filling events in Z = 27 region " << endl;

 TFile* file_co = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.co.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_co; i++){
 tree_co->GetEntry(i);

 Int_t hit_mass_corstm_6th_co = array_mass_corstm_6th_co->GetEntriesFast();

if( hit_mass_corstm_6th_co > 0){

 art::TMassData *mass_corstm_6th_co = (art::TMassData*) array_mass_corstm_6th_co->UncheckedAt(0);

 Double_t aq_select_co = mass_corstm_6th_co->GetAq();

 hnewaq_a->Fill(aq_select_co); 
 hnewaq_b->Fill(aq_select_co); 
 hnewaq_c->Fill(aq_select_co); 
 hnewaq_d->Fill(aq_select_co); 
 hnewaq_e->Fill(aq_select_co); 
 hnewaq_f->Fill(aq_select_co); 
 hnewaq_g->Fill(aq_select_co); 

}  }

   file_co->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_co.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 

 ofile->Close();



}


