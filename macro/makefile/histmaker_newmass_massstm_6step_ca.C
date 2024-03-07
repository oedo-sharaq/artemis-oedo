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


void histmaker_newmass_massstm_6step_ca(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.79,1.81);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.84,1.86);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.88,1.90);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.94,1.96);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.99,2.01);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,2.03,2.05);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,2.08,2.10);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,2.13,2.15);
TH1D*  hnewaq_i = new TH1D("hnewaq_i","hnewaq_i",1000,2.19,2.21);


 cout << " Filling events in Z = 20 region " << endl;

 TFile* file_ca = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ca.root"); // Load file. Basically BLD file.
  if(!file_ca){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ca = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_mass_corstm_6th_ca = NULL;

 tree_ca->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm_6th_ca);
 tree_ca->SetBranchStatus("*",0);
 tree_ca->SetBranchStatus("mass_corstm_BLD_6th",1);


 Int_t nData_ca = tree_ca->GetEntries();

for (int i = 0; i < nData_ca; i++){
 tree_ca->GetEntry(i);

 Int_t hit_mass_corstm_6th_ca = array_mass_corstm_6th_ca->GetEntriesFast();

if( hit_mass_corstm_6th_ca > 0){

 art::TMassData *mass_corstm_6th_ca = (art::TMassData*) array_mass_corstm_6th_ca->UncheckedAt(0);

 Double_t aq_select_ca = mass_corstm_6th_ca->GetAq();

 hnewaq_a->Fill(aq_select_ca); 
 hnewaq_b->Fill(aq_select_ca); 
 hnewaq_c->Fill(aq_select_ca); 
 hnewaq_d->Fill(aq_select_ca); 
 hnewaq_e->Fill(aq_select_ca); 
 hnewaq_f->Fill(aq_select_ca); 
 hnewaq_g->Fill(aq_select_ca); 
 hnewaq_h->Fill(aq_select_ca); 
 hnewaq_i->Fill(aq_select_ca); 

}  }

   file_ca->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_ca.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 
 hnewaq_h->Write(); 
 hnewaq_i->Write(); 
 ofile->Close();



}


