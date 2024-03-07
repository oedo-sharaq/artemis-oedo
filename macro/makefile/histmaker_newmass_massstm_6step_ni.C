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


void histmaker_newmass_massstm_6step_ni(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.70,1.72);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.74,1.76);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.78,1.80);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.81,1.83);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.85,1.87);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,1.89,1.91);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,1.91,1.93);


 cout << " Filling events in Z = 28 region " << endl;

 TFile* file_ni = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ni.root"); // Load file. Basically BLD file.
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

 hnewaq_a->Fill(aq_select_ni); 
 hnewaq_b->Fill(aq_select_ni); 
 hnewaq_c->Fill(aq_select_ni); 
 hnewaq_d->Fill(aq_select_ni); 
 hnewaq_e->Fill(aq_select_ni); 
 hnewaq_f->Fill(aq_select_ni); 
 hnewaq_g->Fill(aq_select_ni); 

}  }

   file_ni->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_ni.eventstore.170272.hist.root","recreate");

 hnewaq_a->Write(); 
 hnewaq_b->Write(); 
 hnewaq_c->Write(); 
 hnewaq_d->Write(); 
 hnewaq_e->Write(); 
 hnewaq_f->Write(); 
 hnewaq_g->Write(); 

 ofile->Close();



}


