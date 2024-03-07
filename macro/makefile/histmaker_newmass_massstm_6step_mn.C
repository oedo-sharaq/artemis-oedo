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


void histmaker_newmass_massstm_6step_mn(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.825,1.845);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.87,1.89);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.91,1.93);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.95,1.97);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.99,2.01);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,2.02,2.04);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,2.06,2.08);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,2.1,2.12);


 cout << " Filling events in Z = 28 region " << endl;

 TFile* file_mn = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.mn.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_corstm_6th_mn = array_mass_corstm_6th_mn->GetEntriesFast();

if( hit_mass_corstm_6th_mn > 0){

 art::TMassData *mass_corstm_6th_mn = (art::TMassData*) array_mass_corstm_6th_mn->UncheckedAt(0);

 Double_t aq_select_mn = mass_corstm_6th_mn->GetAq();

 hnewaq_a->Fill(aq_select_mn); 
 hnewaq_b->Fill(aq_select_mn); 
 hnewaq_c->Fill(aq_select_mn); 
 hnewaq_d->Fill(aq_select_mn); 
 hnewaq_e->Fill(aq_select_mn); 
 hnewaq_f->Fill(aq_select_mn); 
 hnewaq_g->Fill(aq_select_mn); 
 hnewaq_h->Fill(aq_select_mn); 

}  }

   file_mn->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_mn.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 
 hnewaq_h->Write(); 
 ofile->Close();



}


