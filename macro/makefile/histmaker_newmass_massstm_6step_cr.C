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


void histmaker_newmass_massstm_6step_cr(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.74,1.76);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.78,1.80);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.825,1.845);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.87,1.89);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.90,1.92);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,1.94,1.96);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,1.99,2.01);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,2.03,2.05);
TH1D*  hnewaq_i = new TH1D("hnewaq_i","hnewaq_i",1000,2.07,2.09);
TH1D*  hnewaq_j = new TH1D("hnewaq_j","hnewaq_j",1000,2.11,2.13);


 cout << " Filling events in Z = 24 region " << endl;

 TFile* file_cr = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.cr.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_corstm_6th_cr = array_mass_corstm_6th_cr->GetEntriesFast();

if( hit_mass_corstm_6th_cr > 0){

 art::TMassData *mass_corstm_6th_cr = (art::TMassData*) array_mass_corstm_6th_cr->UncheckedAt(0);

 Double_t aq_select_cr = mass_corstm_6th_cr->GetAq();

 hnewaq_a->Fill(aq_select_cr); 
 hnewaq_b->Fill(aq_select_cr); 
 hnewaq_c->Fill(aq_select_cr); 
 hnewaq_d->Fill(aq_select_cr); 
 hnewaq_e->Fill(aq_select_cr); 
 hnewaq_f->Fill(aq_select_cr); 
 hnewaq_g->Fill(aq_select_cr); 
 hnewaq_h->Fill(aq_select_cr); 
 hnewaq_i->Fill(aq_select_cr); 
 hnewaq_j->Fill(aq_select_cr); 

}  }

   file_cr->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_cr.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 
 hnewaq_i->Write(); 
 hnewaq_j->Write(); 
 ofile->Close();



}


