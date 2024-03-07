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


void histmaker_newmass_massstm_6step_fe(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.72,1.74);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.76,1.78);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.79,1.81);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.83,1.85);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.87,1.89);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,1.92,1.94);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,1.95,1.97);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,1.98,2.0);


 cout << " Filling events in Z = 28 region " << endl;

 TFile* file_fe = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.fe.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_corstm_6th_fe = array_mass_corstm_6th_fe->GetEntriesFast();

if( hit_mass_corstm_6th_fe > 0){

 art::TMassData *mass_corstm_6th_fe = (art::TMassData*) array_mass_corstm_6th_fe->UncheckedAt(0);

 Double_t aq_select_fe = mass_corstm_6th_fe->GetAq();

 hnewaq_a->Fill(aq_select_fe); 
 hnewaq_b->Fill(aq_select_fe); 
 hnewaq_c->Fill(aq_select_fe); 
 hnewaq_d->Fill(aq_select_fe); 
 hnewaq_e->Fill(aq_select_fe); 
 hnewaq_f->Fill(aq_select_fe); 
 hnewaq_g->Fill(aq_select_fe); 
 hnewaq_h->Fill(aq_select_fe); 

}  }

   file_fe->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_fe.eventstore.170272.hist.root","recreate");

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


