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


void histmaker_newmass_massstm_6step_ti(){

TH1D*  hnewaq_a = new TH1D("hnewaq_a","hnewaq_a",1000,1.77,1.79);
TH1D*  hnewaq_b = new TH1D("hnewaq_b","hnewaq_b",1000,1.8,1.82);
TH1D*  hnewaq_c = new TH1D("hnewaq_c","hnewaq_c",1000,1.85,1.87);
TH1D*  hnewaq_d = new TH1D("hnewaq_d","hnewaq_d",1000,1.89,1.91);
TH1D*  hnewaq_e = new TH1D("hnewaq_e","hnewaq_e",1000,1.94,1.96);
TH1D*  hnewaq_f = new TH1D("hnewaq_f","hnewaq_f",1000,1.99,2.01);
TH1D*  hnewaq_g = new TH1D("hnewaq_g","hnewaq_g",1000,2.03,2.05);
TH1D*  hnewaq_h = new TH1D("hnewaq_h","hnewaq_h",1000,2.08,2.10);
TH1D*  hnewaq_i = new TH1D("hnewaq_i","hnewaq_i",1000,2.12,2.14);
TH1D*  hnewaq_j = new TH1D("hnewaq_j","hnewaq_j",1000,2.17,2.19);


 cout << " Filling events in Z = 22 region " << endl;

 TFile* file_ti = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ti.root"); // Load file. Basically BLD file.
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

for (int i = 0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_corstm_6th_ti = array_mass_corstm_6th_ti->GetEntriesFast();

if( hit_mass_corstm_6th_ti > 0){

 art::TMassData *mass_corstm_6th_ti = (art::TMassData*) array_mass_corstm_6th_ti->UncheckedAt(0);

 Double_t aq_select_ti = mass_corstm_6th_ti->GetAq();

 hnewaq_a->Fill(aq_select_ti); 
 hnewaq_b->Fill(aq_select_ti); 
 hnewaq_c->Fill(aq_select_ti); 
 hnewaq_d->Fill(aq_select_ti); 
 hnewaq_e->Fill(aq_select_ti); 
 hnewaq_f->Fill(aq_select_ti); 
 hnewaq_g->Fill(aq_select_ti); 
 hnewaq_h->Fill(aq_select_ti); 
 hnewaq_i->Fill(aq_select_ti); 
 hnewaq_j->Fill(aq_select_ti); 

}  }

   file_ti->Close();  


 TFile* ofile = TFile::Open("sh13_analysis/hanai/phys/mass_calib/newmass_stm2_6step_ti.eventstore.170272.hist.root","recreate");

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


