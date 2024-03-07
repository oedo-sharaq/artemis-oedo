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
#endif

void mass_calib3step_svd_st3(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st3_2step.eventstore.170272.all.root"); // Add file. Basically mass calibration file.


//  const Int_t Nrun = 250;  //the number of runs
  const Int_t Nrun = 2500;  //the number of runs
//  const Int_t Nrun = 2300;  //the number of runs
  const Int_t Nref =  21;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nprm =  1001;  //the number of parameters 3rd order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_dia_tof32st3 = NULL;
 TClonesArray *array_mass_corst3 = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_trackd = NULL;
 TClonesArray *array_s0 = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("dia_tof32st3",&array_dia_tof32st3);
 tree->SetBranchAddress("mass_corst3_BLD_2nd",&array_mass_corst3);
// tree->SetBranchAddress("mass_corst3_BLD_3rd",&array_mass_corst3);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("dia_tof32st3",1);
 tree->SetBranchStatus("mass_corst3_BLD_2nd",1);
// tree->SetBranchStatus("mass_corst3_BLD_3rd",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2",1);
 tree->SetBranchStatus("sr0_xcw",1);
 tree->SetBranchStatus("eventheader",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;

 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_3step_st1_ref4.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

  while(!fin.eof()){
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);
		}
 fin.close();

 TMatrixD A(Nevt,Nprm);
 TMatrixD b(Nevt,1);
 TMatrixD value(Nevt,14); // output the fitting value 

 Int_t nrow = A.GetNrows();
 Int_t nrow_b = b.GetNrows();
// Int_t nrow_at = At.GetNrows();
 cout << "Number of rows of A is " << nrow << endl;
 cout << "Number of rows of b is " << nrow_b << endl;
// cout << "Number of rows of At is " << nrow_at << endl;


//// Fill date 

 int ievt = 0;
 Bool_t HasEvents = true;
 Int_t nData = tree->GetEntries();

for (int iref = 0; iref < Nref; iref++){
    vector<Int_t> irandm;
	int n_tmp = 0;

  for(int i = 0; i < nData; i++){
	  tree->GetEntry(i);

      Int_t hit_mass = array_mass->GetEntriesFast();
      Int_t hit_mass_corst3 = array_mass_corst3->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_trackd = array_trackd->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_mass_corst3 > 0 && hit_tracku > 0 && hit_trackd > 0 && hit_s0 > 0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMassData *mass_corst3_tmp = (art::TMassData*) array_mass_corst3->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_corst3_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsGood();
     Bool_t trackd_ok = trackd_tmp->IsGood();
     Double_t ssrd = trackd_tmp->GetSSR();

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok && ssrd < 0.1)
    {
      irandm.push_back(i);
      n_tmp++;
     }else {
       continue;
    	}
    }else{
	  continue;
       }
   }

  if (n_tmp < Nrun){
    cout << "Caution!! Reference No." << iref << " does not have enough number of events.\n";
    HasEvents = false;  
	continue;
    }else{
      cout << "Sampling events of Reference No." << iref << " was finished.\n";
    }

//// Generate random run number
     for (int r = 0; r < Nrun; r++){
         int j = gRandom->Uniform(r,n_tmp);
		 int randm_tmp = irandm[r];
		 irandm[r] = irandm[j];
       	 irandm[j] = randm_tmp;
     }

//// Fill data in matrix for each Ref	 
   for(int p = 0; p < Nrun; p++){
     int k = irandm[p];
     tree->GetEntry(k);
	 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32st3 = (art::TDiaTimingData*) array_dia_tof32st3->UncheckedAt(0);
	 art::TMassData *mass_corst3 = (art::TMassData*) array_mass_corst3->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t z_select = mass->GetZ();
     Double_t aq_select = mass_corst3->GetAq();
     Int_t runnumber = array_eventheader->GetRunNumber();

     Double_t ti = dia_tof32st3->GetTiming();
     Double_t x3i = tracku->GetX();
     Double_t a3i = tracku->GetA() * 1000.;
     Double_t y3i = tracku->GetY();
     Double_t b3i = tracku->GetB() * 1000.;
     Double_t x0i = sr0->GetPosition();
     Double_t x2i = trackd->GetX();
     Double_t a2i = trackd->GetA() * 1000.;
     Double_t y2i = trackd->GetY();
     Double_t b2i = trackd->GetB() * 1000.;
     Double_t ssrd = trackd->GetSSR();

// unit orientation
//     Double_t t = (ti - 2042.) * 0.25;  
//     Double_t x3 = x3i * 0.1; 
//     Double_t a3 = a3i * 0.1;
//     Double_t y3 = y3i * 0.1;
//     Double_t b3 = b3i * 0.1;
//     Double_t x0 = x0i * 0.1; 
//     Double_t x2 = x2i * 0.1; 
//     Double_t a2 = a2i * 0.1;
//     Double_t y2 = y2i * 0.1;
//     Double_t b2 = b2i * 0.1;

//     Double_t t = (ti - 2042.) * 0.125;  
//     Double_t x3 = x3i * 0.1; 
//     Double_t a3 = a3i * 0.1;
//     Double_t y3 = y3i;
//     Double_t b3 = b3i * 0.1 + 1;
//     Double_t x0 = x0i * 0.05; 
//     Double_t x2 = x2i * 0.1; 
//     Double_t a2 = a2i * 0.05;
//     Double_t y2 = y2i * 0.05 - 1;
//     Double_t b2 = b2i * 0.05 - 0.2;

     Double_t t = (ti - 2042.) * 0.125;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1;
     Double_t y3 = y3i + 2;
     Double_t b3 = b3i * 0.05 + 0.5;
     Double_t x0 = x0i * 0.015; 
     Double_t x2 = x2i * 0.1; 
     Double_t a2 = a2i * 0.025;
     Double_t y2 = y2i * 0.05 - 1;
     Double_t b2 = b2i * 0.05 - 0.2;

// constant
     A(ievt,0) = 1.; 
// 1st order
     A(ievt,1)  = t;
     A(ievt,2)  = x3;
     A(ievt,3)  = a3;
     A(ievt,4)  = y3;
     A(ievt,5)  = b3;
     A(ievt,6)  = x0;
     A(ievt,7)  = x2;
     A(ievt,8)  = a2;
     A(ievt,9)  = y2;
     A(ievt,10) = b2;
// 2nd order       
     A(ievt,11) = t * t;
     A(ievt,12) = x3 * x3;
     A(ievt,13) = a3 * a3;
     A(ievt,14) = y3 * y3;
     A(ievt,15) = b3 * b3;
     A(ievt,16) = x0 * x0;
     A(ievt,17) = x2 * x2;
     A(ievt,18) = a2 * a2;
     A(ievt,19) = y2 * y2;
     A(ievt,20) = b2 * b2;
 
     A(ievt,21) = t * x3;
     A(ievt,22) = t * a3;
     A(ievt,23) = t * y3;
     A(ievt,24) = t * b3;
     A(ievt,25) = t * x0;
     A(ievt,26) = t * x2;
     A(ievt,27) = t * a2;
     A(ievt,28) = t * y2;
     A(ievt,29) = t * b2;
 
     A(ievt,30) = x3 * a3;
     A(ievt,31) = x3 * y3;
     A(ievt,32) = x3 * b3;
     A(ievt,33) = x3 * x0;
     A(ievt,34) = x3 * x2;
     A(ievt,35) = x3 * a2;
     A(ievt,36) = x3 * y2;
     A(ievt,37) = x3 * b2;
 
     A(ievt,38) = a3 * y3;
     A(ievt,39) = a3 * b3;
     A(ievt,40) = a3 * x0;
     A(ievt,41) = a3 * x2;
     A(ievt,42) = a3 * a2;
     A(ievt,43) = a3 * y2;
     A(ievt,44) = a3 * b2;
 
     A(ievt,45) = y3 * b3;
     A(ievt,46) = y3 * x0;
     A(ievt,47) = y3 * x2;
     A(ievt,48) = y3 * a2;
     A(ievt,49) = y3 * y2;
     A(ievt,50) = y3 * b2;
 
     A(ievt,51) = b3 * x0;
     A(ievt,52) = b3 * x2;
     A(ievt,53) = b3 * a2;
     A(ievt,54) = b3 * y2;
     A(ievt,55) = b3 * b2;
 
     A(ievt,56) = x0 * x2;
     A(ievt,57) = x0 * a2;
     A(ievt,58) = x0 * y2;
     A(ievt,59) = x0 * b2;
 
     A(ievt,60) = x2 * a2;
     A(ievt,61) = x2 * y2;
     A(ievt,62) = x2 * b2;
 
     A(ievt,63) = a2 * y2;
     A(ievt,64) = a2 * b2;
 
     A(ievt,65) = y2 * b2;
// 3rd order
     A(ievt,66) = t * t * t;
     A(ievt,67) = x3 * x3 * x3;
     A(ievt,68) = a3 * a3 * a3;
     A(ievt,69) = y3 * y3 * y3;
     A(ievt,70) = b3 * b3 * b3;
     A(ievt,71) = x0 * x0 * x0;
     A(ievt,72) = x2 * x2 * x2;
     A(ievt,73) = a2 * a2 * a2;
     A(ievt,74) = y2 * y2 * y2;
     A(ievt,75) = b2 * b2 * b2;
 
     A(ievt,76) = t * t * x3;
     A(ievt,77) = t * t * a3;
     A(ievt,78) = t * t * y3;
     A(ievt,79) = t * t * b3;
     A(ievt,80) = t * t * x0;
     A(ievt,81) = t * t * x2;
     A(ievt,82) = t * t * a2;
     A(ievt,83) = t * t * y2;
     A(ievt,84) = t * t * b2;
 
     A(ievt,85) = x3 * x3 * t;
     A(ievt,86) = x3 * x3 * a3;
     A(ievt,87) = x3 * x3 * y3;
     A(ievt,88) = x3 * x3 * b3;
     A(ievt,89) = x3 * x3 * x0;
     A(ievt,90) = x3 * x3 * x2;
     A(ievt,91) = x3 * x3 * a2;
     A(ievt,92) = x3 * x3 * y2;
     A(ievt,93) = x3 * x3 * b2;
 
     A(ievt,94) = a3 * a3 * t;
     A(ievt,95) = a3 * a3 * x3;
     A(ievt,96) = a3 * a3 * y3;
     A(ievt,97) = a3 * a3 * b3;
     A(ievt,98) = a3 * a3 * x0;
     A(ievt,99) = a3 * a3 * x2;
     A(ievt,100) = a3 * a3 * a2;
     A(ievt,101) = a3 * a3 * y2;
     A(ievt,102) = a3 * a3 * b2;
 
     A(ievt,103) = y3 * y3 * t;
     A(ievt,104) = y3 * y3 * x3;
     A(ievt,105) = y3 * y3 * a3;
     A(ievt,106) = y3 * y3 * b3;
     A(ievt,107) = y3 * y3 * x0;
     A(ievt,108) = y3 * y3 * x2;
     A(ievt,109) = y3 * y3 * a2;
     A(ievt,110) = y3 * y3 * y2;
     A(ievt,111) = y3 * y3 * b2;
 
     A(ievt,112) = b3 * b3 * t;
     A(ievt,113) = b3 * b3 * x3;
     A(ievt,114) = b3 * b3 * a3;
     A(ievt,115) = b3 * b3 * y3;
     A(ievt,116) = b3 * b3 * x0;
     A(ievt,117) = b3 * b3 * x2;
     A(ievt,118) = b3 * b3 * a2;
     A(ievt,119) = b3 * b3 * y2;
     A(ievt,120) = b3 * b3 * b2;
 
     A(ievt,121) = x0 * x0 * t;
     A(ievt,122) = x0 * x0 * x3;
     A(ievt,123) = x0 * x0 * a3;
     A(ievt,124) = x0 * x0 * y3;
     A(ievt,125) = x0 * x0 * b3;
     A(ievt,126) = x0 * x0 * x2;
     A(ievt,127) = x0 * x0 * a2;
     A(ievt,128) = x0 * x0 * y2;
     A(ievt,129) = x0 * x0 * b2;
 
     A(ievt,130) = x2 * x2 * t;
     A(ievt,131) = x2 * x2 * x3;
     A(ievt,132) = x2 * x2 * a3;
     A(ievt,133) = x2 * x2 * y3;
     A(ievt,134) = x2 * x2 * b3;
     A(ievt,135) = x2 * x2 * x0;
     A(ievt,136) = x2 * x2 * a2;
     A(ievt,137) = x2 * x2 * y2;
     A(ievt,138) = x2 * x2 * b2;
 
     A(ievt,139) = a2 * a2 * t;
     A(ievt,140) = a2 * a2 * x3;
     A(ievt,141) = a2 * a2 * a3;
     A(ievt,142) = a2 * a2 * y3;
     A(ievt,143) = a2 * a2 * b3;
     A(ievt,144) = a2 * a2 * x0;
     A(ievt,145) = a2 * a2 * x2;
     A(ievt,146) = a2 * a2 * y2;
     A(ievt,147) = a2 * a2 * b2;
 
     A(ievt,148) = y2 * y2 * t;
     A(ievt,149) = y2 * y2 * x3;
     A(ievt,150) = y2 * y2 * a3;
     A(ievt,151) = y2 * y2 * y3;
     A(ievt,152) = y2 * y2 * b3;
     A(ievt,153) = y2 * y2 * x0;
     A(ievt,154) = y2 * y2 * x2;
     A(ievt,155) = y2 * y2 * a2;
     A(ievt,156) = y2 * y2 * b2;
 
     A(ievt,157) = b2 * b2 * t;
     A(ievt,158) = b2 * b2 * x3;
     A(ievt,159) = b2 * b2 * a3;
     A(ievt,160) = b2 * b2 * y3;
     A(ievt,161) = b2 * b2 * b3;
     A(ievt,162) = b2 * b2 * x0;
     A(ievt,163) = b2 * b2 * x2;
     A(ievt,164) = b2 * b2 * a2;
     A(ievt,165) = b2 * b2 * y2;
 
     A(ievt,166) = t * x3 * a3;
     A(ievt,167) = t * x3 * y3;
     A(ievt,168) = t * x3 * b3;
     A(ievt,169) = t * x3 * x0;
     A(ievt,170) = t * x3 * x2;
     A(ievt,171) = t * x3 * a2;
     A(ievt,172) = t * x3 * y2;
     A(ievt,173) = t * x3 * b2;
 
     A(ievt,174) = t * a3 * y3;
     A(ievt,175) = t * a3 * b3;
     A(ievt,176) = t * a3 * x0;
     A(ievt,177) = t * a3 * x2;
     A(ievt,178) = t * a3 * a2;
     A(ievt,179) = t * a3 * y2;
     A(ievt,180) = t * a3 * b2;
 
     A(ievt,181) = t * y3 * b3;
     A(ievt,182) = t * y3 * x0;
     A(ievt,183) = t * y3 * x2;
     A(ievt,184) = t * y3 * a2;
     A(ievt,185) = t * y3 * y2;
     A(ievt,186) = t * y3 * b2;
 
     A(ievt,187) = t * b3 * x0;
     A(ievt,188) = t * b3 * x2;
     A(ievt,189) = t * b3 * a2;
     A(ievt,190) = t * b3 * y2;
     A(ievt,192) = t * b3 * b2;
 
     A(ievt,193) = t * x0 * x2;
     A(ievt,194) = t * x0 * a2;
     A(ievt,195) = t * x0 * y2;
     A(ievt,196) = t * x0 * b2;
 
     A(ievt,197) = t * x2 * a2;
     A(ievt,198) = t * x2 * y2;
     A(ievt,199) = t * x2 * b2;
 
     A(ievt,200) = t * a2 * y2;
     A(ievt,201) = t * a2 * b2;
 
     A(ievt,202) = t * y2 * b2;
 
     A(ievt,203) = x3 * a3 * y3;
     A(ievt,204) = x3 * a3 * b3;
     A(ievt,205) = x3 * a3 * x0;
     A(ievt,206) = x3 * a3 * x2;
     A(ievt,207) = x3 * a3 * a2;
     A(ievt,208) = x3 * a3 * y2;
     A(ievt,209) = x3 * a3 * b2;
 
     A(ievt,210) = x3 * y3 * b3;
     A(ievt,211) = x3 * y3 * x0;
     A(ievt,212) = x3 * y3 * x2;
     A(ievt,213) = x3 * y3 * a2;
     A(ievt,214) = x3 * y3 * y2;
     A(ievt,215) = x3 * y3 * b2;
 
     A(ievt,216) = x3 * b3 * x0;
     A(ievt,217) = x3 * b3 * x2;
     A(ievt,217) = x3 * b3 * a2;
     A(ievt,218) = x3 * b3 * y2;
     A(ievt,219) = x3 * b3 * b2;
 
     A(ievt,220) = x3 * x0 * x2;
     A(ievt,221) = x3 * x0 * a2;
     A(ievt,222) = x3 * x0 * y2;
     A(ievt,223) = x3 * x0 * b2;
        
     A(ievt,224) = x3 * x2 * a2;
     A(ievt,225) = x3 * x2 * y2;
     A(ievt,226) = x3 * x2 * b2;
        
     A(ievt,227) = x3 * a2 * y2;
     A(ievt,228) = x3 * a2 * b2;
 
     A(ievt,229) = x3 * y2 * b2;
 
     A(ievt,230) = a3 * y3 * b3;
     A(ievt,231) = a3 * y3 * x0;
     A(ievt,232) = a3 * y3 * x2;
     A(ievt,233) = a3 * y3 * a2;
     A(ievt,234) = a3 * y3 * y2;
     A(ievt,235) = a3 * y3 * b2;
 
     A(ievt,236) = a3 * b3 * x0;
     A(ievt,237) = a3 * b3 * x2;
     A(ievt,238) = a3 * b3 * a2;
     A(ievt,239) = a3 * b3 * y2;
     A(ievt,240) = a3 * b3 * b2;
 
     A(ievt,241) = a3 * x0 * x2;
     A(ievt,242) = a3 * x0 * a2;
     A(ievt,243) = a3 * x0 * y2;
     A(ievt,244) = a3 * x0 * b2;
 
     A(ievt,245) = a3 * x2 * a2;
     A(ievt,246) = a3 * x2 * y2;
     A(ievt,247) = a3 * x2 * b2;
 
     A(ievt,248) = a3 * a2 * y2;
     A(ievt,249) = a3 * a2 * b2;
 
     A(ievt,250) = a3 * y2 * b2;
 
     A(ievt,251) = y3 * b3 * x0;
     A(ievt,252) = y3 * b3 * x2;
     A(ievt,253) = y3 * b3 * a2;
     A(ievt,254) = y3 * b3 * y2;
     A(ievt,255) = y3 * b3 * b2;
 
     A(ievt,256) = y3 * x0 * x2;
     A(ievt,257) = y3 * x0 * a2;
     A(ievt,258) = y3 * x0 * y2;
     A(ievt,259) = y3 * x0 * b2;
 
     A(ievt,260) = y3 * x2 * a2;
     A(ievt,261) = y3 * x2 * y2;
     A(ievt,262) = y3 * x2 * b2;
 
     A(ievt,263) = y3 * a2 * y2;
     A(ievt,264) = y3 * a2 * b2;
 
     A(ievt,265) = y3 * y2 * b2;
 
     A(ievt,266) = b3 * x0 * x2;
     A(ievt,267) = b3 * x0 * a2;
     A(ievt,268) = b3 * x0 * y2;
     A(ievt,269) = b3 * x0 * b2;
 
     A(ievt,270) = b3 * x2 * a2;
     A(ievt,271) = b3 * x2 * y2;
     A(ievt,272) = b3 * x2 * b2;
 
     A(ievt,273) = b3 * a2 * y2;
     A(ievt,274) = b3 * a2 * b2;
 
     A(ievt,275) = b3 * y2 * b2;
 
     A(ievt,276) = x0 * x2 * a2;
     A(ievt,277) = x0 * x2 * y2;
     A(ievt,278) = x0 * x2 * b2;
 
     A(ievt,279) = x0 * a2 * y2;
     A(ievt,280) = x0 * a2 * b2;
 
     A(ievt,281) = x0 * y2 * b2;
 
     A(ievt,282) = x2 * a2 * y2;
     A(ievt,283) = x2 * a2 * b2;
 
     A(ievt,284) = x2 * y2 * b2;
 
     A(ievt,285) = a2 * y2 * b2;
// 4th order
     A(ievt,286) = t * t * t * t;
     A(ievt,287) = x3 * x3 * x3 * x3;
     A(ievt,288) = a3 * a3 * a3 * a3;
     A(ievt,289) = y3 * y3 * y3 * y3;
     A(ievt,290) = b3 * b3 * b3 * b3;
     A(ievt,291) = x0 * x0 * x0 * x0;
     A(ievt,292) = x2 * x2 * x2 * x2;
     A(ievt,293) = a2 * a2 * a2 * a2;
     A(ievt,294) = y2 * y2 * y2 * y2;
     A(ievt,295) = b2 * b2 * b2 * b2;

     A(ievt,296) = t * t * t * x3;
     A(ievt,297) = t * t * t * a3;
     A(ievt,298) = t * t * t * y3;
     A(ievt,299) = t * t * t * b3;
     A(ievt,300) = t * t * t * x0;
     A(ievt,301) = t * t * t * x2;
     A(ievt,302) = t * t * t * a2;
     A(ievt,303) = t * t * t * y2;
     A(ievt,304) = t * t * t * b2;

     A(ievt,305) = x3 * x3 * x3 * t;
     A(ievt,306) = x3 * x3 * x3 * a3;
     A(ievt,307) = x3 * x3 * x3 * y3;
     A(ievt,308) = x3 * x3 * x3 * b3;
     A(ievt,309) = x3 * x3 * x3 * x0;
     A(ievt,310) = x3 * x3 * x3 * x2;
     A(ievt,311) = x3 * x3 * x3 * a2;
     A(ievt,312) = x3 * x3 * x3 * y2;
     A(ievt,313) = x3 * x3 * x3 * b2;

     A(ievt,314) = a3 * a3 * a3 * t;
     A(ievt,315) = a3 * a3 * a3 * x3;
     A(ievt,316) = a3 * a3 * a3 * y3;
     A(ievt,317) = a3 * a3 * a3 * b3;
     A(ievt,318) = a3 * a3 * a3 * x0;
     A(ievt,319) = a3 * a3 * a3 * x2;
     A(ievt,320) = a3 * a3 * a3 * a2;
     A(ievt,321) = a3 * a3 * a3 * y2;
     A(ievt,322) = a3 * a3 * a3 * b2;

     A(ievt,323) = y3 * y3 * y3 * t;
     A(ievt,324) = y3 * y3 * y3 * x3;
     A(ievt,325) = y3 * y3 * y3 * a3;
     A(ievt,326) = y3 * y3 * y3 * b3;
     A(ievt,327) = y3 * y3 * y3 * x0;
     A(ievt,328) = y3 * y3 * y3 * x2;
     A(ievt,329) = y3 * y3 * y3 * a2;
     A(ievt,330) = y3 * y3 * y3 * y2;
     A(ievt,331) = y3 * y3 * y3 * b2;

     A(ievt,332) = b3 * b3 * b3 * t;
     A(ievt,333) = b3 * b3 * b3 * x3;
     A(ievt,334) = b3 * b3 * b3 * a3;
     A(ievt,335) = b3 * b3 * b3 * y3;
     A(ievt,336) = b3 * b3 * b3 * x0;
     A(ievt,337) = b3 * b3 * b3 * x2;
     A(ievt,338) = b3 * b3 * b3 * a2;
     A(ievt,339) = b3 * b3 * b3 * y2;
     A(ievt,340) = b3 * b3 * b3 * b2;

     A(ievt,341) = x0 * x0 * x0 * t;
     A(ievt,342) = x0 * x0 * x0 * x3;
     A(ievt,343) = x0 * x0 * x0 * a3;
     A(ievt,344) = x0 * x0 * x0 * y3;
     A(ievt,345) = x0 * x0 * x0 * b3;
     A(ievt,346) = x0 * x0 * x0 * x2;
     A(ievt,347) = x0 * x0 * x0 * a2;
     A(ievt,348) = x0 * x0 * x0 * y2;
     A(ievt,349) = x0 * x0 * x0 * b2;

     A(ievt,350) = x2 * x2 * x2 * t;
     A(ievt,351) = x2 * x2 * x2 * x3;
     A(ievt,352) = x2 * x2 * x2 * a3;
     A(ievt,353) = x2 * x2 * x2 * y3;
     A(ievt,354) = x2 * x2 * x2 * b3;
     A(ievt,355) = x2 * x2 * x2 * x0;
     A(ievt,356) = x2 * x2 * x2 * a2;
     A(ievt,357) = x2 * x2 * x2 * y2;
     A(ievt,358) = x2 * x2 * x2 * b2;

     A(ievt,359) = a2 * a2 * a2 * t;
     A(ievt,360) = a2 * a2 * a2 * x3;
     A(ievt,361) = a2 * a2 * a2 * a3;
     A(ievt,362) = a2 * a2 * a2 * y3;
     A(ievt,363) = a2 * a2 * a2 * b3;
     A(ievt,364) = a2 * a2 * a2 * x0;
     A(ievt,365) = a2 * a2 * a2 * x2;
     A(ievt,366) = a2 * a2 * a2 * y2;
     A(ievt,367) = a2 * a2 * a2 * b2;

     A(ievt,368) = y2 * y2 * y2 * t;
     A(ievt,369) = y2 * y2 * y2 * x3;
     A(ievt,370) = y2 * y2 * y2 * a3;
     A(ievt,371) = y2 * y2 * y2 * y3;
     A(ievt,372) = y2 * y2 * y2 * b3;
     A(ievt,373) = y2 * y2 * y2 * x0;
     A(ievt,374) = y2 * y2 * y2 * x2;
     A(ievt,375) = y2 * y2 * y2 * a2;
     A(ievt,376) = y2 * y2 * y2 * b2;

     A(ievt,377) = b2 * b2 * b2 * t;
     A(ievt,378) = b2 * b2 * b2 * x3;
     A(ievt,379) = b2 * b2 * b2 * a3;
     A(ievt,380) = b2 * b2 * b2 * y3;
     A(ievt,381) = b2 * b2 * b2 * b3;
     A(ievt,382) = b2 * b2 * b2 * x0;
     A(ievt,383) = b2 * b2 * b2 * x2;
     A(ievt,384) = b2 * b2 * b2 * a2;
     A(ievt,385) = b2 * b2 * b2 * y2;

     A(ievt,386) = t * t * x3 * x3;
     A(ievt,387) = t * t * a3 * a3;
     A(ievt,388) = t * t * y3 * y3;
     A(ievt,389) = t * t * b3 * b3;
     A(ievt,390) = t * t * x0 * x0;
     A(ievt,391) = t * t * x2 * x2;
     A(ievt,392) = t * t * a2 * a2;
     A(ievt,393) = t * t * y2 * y2;
     A(ievt,394) = t * t * b2 * b2;

     A(ievt,395) = x3 * x3 * a3 * a3;
     A(ievt,396) = x3 * x3 * y3 * y3;
     A(ievt,397) = x3 * x3 * b3 * b3;
     A(ievt,398) = x3 * x3 * x0 * x0;
     A(ievt,399) = x3 * x3 * x2 * x2;
     A(ievt,400) = x3 * x3 * a2 * a2;
     A(ievt,401) = x3 * x3 * y2 * y2;
     A(ievt,402) = x3 * x3 * b2 * b2;

     A(ievt,403) = a3 * a3 * y3 * y3;
     A(ievt,404) = a3 * a3 * b3 * b3;
     A(ievt,405) = a3 * a3 * x0 * x0;
     A(ievt,406) = a3 * a3 * x2 * x2;
     A(ievt,407) = a3 * a3 * a2 * a2;
     A(ievt,408) = a3 * a3 * y2 * y2;
     A(ievt,409) = a3 * a3 * b2 * b2;

     A(ievt,410) = y3 * y3 * b3 * b3;
     A(ievt,411) = y3 * y3 * x0 * x0;
     A(ievt,412) = y3 * y3 * x2 * x2;
     A(ievt,413) = y3 * y3 * a2 * a2;
     A(ievt,414) = y3 * y3 * y2 * y2;
     A(ievt,415) = y3 * y3 * b2 * b2;

     A(ievt,416) = b3 * b3 * x0 * x0;
     A(ievt,417) = b3 * b3 * x2 * x2;
     A(ievt,418) = b3 * b3 * a2 * a2;
     A(ievt,419) = b3 * b3 * y2 * y2;
     A(ievt,420) = b3 * b3 * b2 * b2;

     A(ievt,421) = x0 * x0 * x2 * x2;
     A(ievt,422) = x0 * x0 * a2 * a2;
     A(ievt,423) = x0 * x0 * y2 * y2;
     A(ievt,424) = x0 * x0 * b2 * b2;

     A(ievt,425) = x2 * x2 * a2 * a2;
     A(ievt,426) = x2 * x2 * y2 * y2;
     A(ievt,427) = x2 * x2 * b2 * b2;

     A(ievt,428) = a2 * a2 * y2 * y2;
     A(ievt,429) = a2 * a2 * b2 * b2;

     A(ievt,430) = y2 * y2 * b2 * b2;

     A(ievt,431) = t * t * x3 * a3;
     A(ievt,432) = t * t * x3 * y3;
     A(ievt,433) = t * t * x3 * b3;
     A(ievt,434) = t * t * x3 * x0;
     A(ievt,435) = t * t * x3 * x2;
     A(ievt,436) = t * t * x3 * a2;
     A(ievt,437) = t * t * x3 * y2;
     A(ievt,438) = t * t * x3 * b2;

     A(ievt,439) = t * t * a3 * y3;
     A(ievt,440) = t * t * a3 * b3;
     A(ievt,441) = t * t * a3 * x0;
     A(ievt,442) = t * t * a3 * x2;
     A(ievt,443) = t * t * a3 * a2;
     A(ievt,444) = t * t * a3 * y2;
     A(ievt,445) = t * t * a3 * b2;

     A(ievt,446) = t * t * y3 * b3;
     A(ievt,447) = t * t * y3 * x0;
     A(ievt,448) = t * t * y3 * x2;
     A(ievt,449) = t * t * y3 * a2;
     A(ievt,450) = t * t * y3 * y2;
     A(ievt,451) = t * t * y3 * b2;

     A(ievt,452) = t * t * b3 * x0;
     A(ievt,453) = t * t * b3 * x2;
     A(ievt,454) = t * t * b3 * a2;
     A(ievt,455) = t * t * b3 * y2;
     A(ievt,456) = t * t * b3 * b2;

     A(ievt,457) = t * t * x0 * x2;
     A(ievt,458) = t * t * x0 * a2;
     A(ievt,459) = t * t * x0 * y2;
     A(ievt,460) = t * t * x0 * b2;

     A(ievt,461) = t * t * x2 * a2;
     A(ievt,462) = t * t * x2 * y2;
     A(ievt,463) = t * t * x2 * b2;

     A(ievt,464) = t * t * a2 * y2;
     A(ievt,465) = t * t * a2 * b2;

     A(ievt,466) = t * t * y2 * b2;

     A(ievt,467) = x3 * x3 * t * a3;
     A(ievt,468) = x3 * x3 * t * y3;
     A(ievt,469) = x3 * x3 * t * b3;
     A(ievt,470) = x3 * x3 * t * x0;
     A(ievt,471) = x3 * x3 * t * x2;
     A(ievt,472) = x3 * x3 * t * a2;
     A(ievt,473) = x3 * x3 * t * y2;
     A(ievt,474) = x3 * x3 * t * b2;

     A(ievt,475) = x3 * x3 * a3 * y3;
     A(ievt,476) = x3 * x3 * a3 * b3;
     A(ievt,477) = x3 * x3 * a3 * x0;
     A(ievt,478) = x3 * x3 * a3 * x2;
     A(ievt,479) = x3 * x3 * a3 * a2;
     A(ievt,480) = x3 * x3 * a3 * y2;
     A(ievt,481) = x3 * x3 * a3 * b2;

     A(ievt,482) = x3 * x3 * y3 * b3;
     A(ievt,483) = x3 * x3 * y3 * x0;
     A(ievt,484) = x3 * x3 * y3 * x2;
     A(ievt,485) = x3 * x3 * y3 * a2;
     A(ievt,486) = x3 * x3 * y3 * y2;
     A(ievt,487) = x3 * x3 * y3 * b2;

     A(ievt,488) = x3 * x3 * b3 * x0;
     A(ievt,489) = x3 * x3 * b3 * x2;
     A(ievt,490) = x3 * x3 * b3 * a2;
     A(ievt,491) = x3 * x3 * b3 * y2;
     A(ievt,492) = x3 * x3 * b3 * b2;

     A(ievt,493) = x3 * x3 * x0 * x2;
     A(ievt,494) = x3 * x3 * x0 * a2;
     A(ievt,495) = x3 * x3 * x0 * y2;
     A(ievt,496) = x3 * x3 * x0 * b2;

     A(ievt,497) = x3 * x3 * x2 * a2;
     A(ievt,498) = x3 * x3 * x2 * y2;
     A(ievt,499) = x3 * x3 * x2 * b2;

     A(ievt,500) = x3 * x3 * a2 * y2;
     A(ievt,501) = x3 * x3 * a2 * b2;

     A(ievt,502) = x3 * x3 * y2 * b2;


     A(ievt,503) = a3 * a3 * t * x3;
     A(ievt,504) = a3 * a3 * t * y3;
     A(ievt,505) = a3 * a3 * t * b3;
     A(ievt,506) = a3 * a3 * t * x0;
     A(ievt,507) = a3 * a3 * t * x2;
     A(ievt,508) = a3 * a3 * t * a2;
     A(ievt,509) = a3 * a3 * t * y2;
     A(ievt,510) = a3 * a3 * t * b2;

     A(ievt,511) = a3 * a3 * x3 * y3;
     A(ievt,512) = a3 * a3 * x3 * b3;
     A(ievt,513) = a3 * a3 * x3 * x0;
     A(ievt,514) = a3 * a3 * x3 * x2;
     A(ievt,515) = a3 * a3 * x3 * a2;
     A(ievt,516) = a3 * a3 * x3 * y2;
     A(ievt,517) = a3 * a3 * x3 * b2;

     A(ievt,518) = a3 * a3 * y3 * b3;
     A(ievt,519) = a3 * a3 * y3 * x0;
     A(ievt,520) = a3 * a3 * y3 * x2;
     A(ievt,521) = a3 * a3 * y3 * a2;
     A(ievt,522) = a3 * a3 * y3 * y2;
     A(ievt,523) = a3 * a3 * y3 * b2;

     A(ievt,524) = a3 * a3 * b3 * x0;
     A(ievt,525) = a3 * a3 * b3 * x2;
     A(ievt,526) = a3 * a3 * b3 * a2;
     A(ievt,527) = a3 * a3 * b3 * y2;
     A(ievt,528) = a3 * a3 * b3 * b2;

     A(ievt,529) = a3 * a3 * x0 * x2;
     A(ievt,530) = a3 * a3 * x0 * a2;
     A(ievt,531) = a3 * a3 * x0 * y2;
     A(ievt,532) = a3 * a3 * x0 * b2;

     A(ievt,533) = a3 * a3 * x2 * a2;
     A(ievt,534) = a3 * a3 * x2 * y2;
     A(ievt,535) = a3 * a3 * x2 * b2;

     A(ievt,536) = a3 * a3 * a2 * y2;
     A(ievt,537) = a3 * a3 * a2 * b2;

     A(ievt,538) = a3 * a3 * y2 * b2;

     A(ievt,539) = y3 * y3 * t * x3;
     A(ievt,540) = y3 * y3 * t * a3;
     A(ievt,541) = y3 * y3 * t * b3;
     A(ievt,542) = y3 * y3 * t * x0;
     A(ievt,543) = y3 * y3 * t * x2;
     A(ievt,544) = y3 * y3 * t * a2;
     A(ievt,545) = y3 * y3 * t * y2;
     A(ievt,546) = y3 * y3 * t * b2;

     A(ievt,547) = y3 * y3 * x3 * a3;
     A(ievt,548) = y3 * y3 * x3 * b3;
     A(ievt,549) = y3 * y3 * x3 * x0;
     A(ievt,550) = y3 * y3 * x3 * x2;
     A(ievt,551) = y3 * y3 * x3 * a2;
     A(ievt,552) = y3 * y3 * x3 * y2;
     A(ievt,553) = y3 * y3 * x3 * b2;

     A(ievt,554) = y3 * y3 * a3 * b3;
     A(ievt,555) = y3 * y3 * a3 * x0;
     A(ievt,556) = y3 * y3 * a3 * x2;
     A(ievt,557) = y3 * y3 * a3 * a2;
     A(ievt,558) = y3 * y3 * a3 * y2;
     A(ievt,559) = y3 * y3 * a3 * b2;

     A(ievt,560) = y3 * y3 * b3 * x0;
     A(ievt,561) = y3 * y3 * b3 * x2;
     A(ievt,562) = y3 * y3 * b3 * a2;
     A(ievt,563) = y3 * y3 * b3 * y2;
     A(ievt,564) = y3 * y3 * b3 * b2;

     A(ievt,565) = y3 * y3 * x0 * x2;
     A(ievt,566) = y3 * y3 * x0 * a2;
     A(ievt,567) = y3 * y3 * x0 * y2;
     A(ievt,568) = y3 * y3 * x0 * b2;

     A(ievt,569) = y3 * y3 * x2 * a2;
     A(ievt,570) = y3 * y3 * x2 * y2;
     A(ievt,571) = y3 * y3 * x2 * b2;

     A(ievt,572) = y3 * y3 * a2 * y2;
     A(ievt,573) = y3 * y3 * a2 * b2;

     A(ievt,574) = y3 * y3 * y2 * b2;

     A(ievt,575) = b3 * b3 * t * x3;
     A(ievt,576) = b3 * b3 * t * a3;
     A(ievt,577) = b3 * b3 * t * y3;
     A(ievt,578) = b3 * b3 * t * x0;
     A(ievt,579) = b3 * b3 * t * x2;
     A(ievt,580) = b3 * b3 * t * a2;
     A(ievt,581) = b3 * b3 * t * y2;
     A(ievt,582) = b3 * b3 * t * b2;

     A(ievt,583) = b3 * b3 * x3 * a3;
     A(ievt,584) = b3 * b3 * x3 * y3;
     A(ievt,585) = b3 * b3 * x3 * x0;
     A(ievt,586) = b3 * b3 * x3 * x2;
     A(ievt,587) = b3 * b3 * x3 * a2;
     A(ievt,588) = b3 * b3 * x3 * y2;
     A(ievt,589) = b3 * b3 * x3 * b2;

     A(ievt,590) = b3 * b3 * a3 * y3;
     A(ievt,591) = b3 * b3 * a3 * x0;
     A(ievt,592) = b3 * b3 * a3 * x2;
     A(ievt,593) = b3 * b3 * a3 * a2;
     A(ievt,594) = b3 * b3 * a3 * y2;
     A(ievt,595) = b3 * b3 * a3 * b2;

     A(ievt,596) = b3 * b3 * y3 * x0;
     A(ievt,597) = b3 * b3 * y3 * x2;
     A(ievt,598) = b3 * b3 * y3 * a2;
     A(ievt,599) = b3 * b3 * y3 * y2;
     A(ievt,600) = b3 * b3 * y3 * b2;

     A(ievt,601) = b3 * b3 * x0 * x2;
     A(ievt,602) = b3 * b3 * x0 * a2;
     A(ievt,603) = b3 * b3 * x0 * y2;
     A(ievt,604) = b3 * b3 * x0 * b2;

     A(ievt,605) = b3 * b3 * x2 * a2;
     A(ievt,606) = b3 * b3 * x2 * y2;
     A(ievt,607) = b3 * b3 * x2 * b2;

     A(ievt,608) = b3 * b3 * a2 * y2;
     A(ievt,609) = b3 * b3 * a2 * b2;

     A(ievt,610) = b3 * b3 * y2 * b2;

     A(ievt,611) = x0 * x0 * t * x3;
     A(ievt,612) = x0 * x0 * t * a3;
     A(ievt,613) = x0 * x0 * t * y3;
     A(ievt,614) = x0 * x0 * t * b3;
     A(ievt,615) = x0 * x0 * t * x2;
     A(ievt,616) = x0 * x0 * t * a2;
     A(ievt,617) = x0 * x0 * t * y2;
     A(ievt,618) = x0 * x0 * t * b2;

     A(ievt,619) = x0 * x0 * x3 * a3;
     A(ievt,620) = x0 * x0 * x3 * y3;
     A(ievt,621) = x0 * x0 * x3 * b3;
     A(ievt,622) = x0 * x0 * x3 * x2;
     A(ievt,623) = x0 * x0 * x3 * a2;
     A(ievt,624) = x0 * x0 * x3 * y2;
     A(ievt,625) = x0 * x0 * x3 * b2;

     A(ievt,626) = x0 * x0 * a3 * y3;
     A(ievt,627) = x0 * x0 * a3 * b3;
     A(ievt,628) = x0 * x0 * a3 * x2;
     A(ievt,629) = x0 * x0 * a3 * a2;
     A(ievt,630) = x0 * x0 * a3 * y2;
     A(ievt,631) = x0 * x0 * a3 * b2;

     A(ievt,632) = x0 * x0 * y3 * b3;
     A(ievt,633) = x0 * x0 * y3 * x2;
     A(ievt,634) = x0 * x0 * y3 * a2;
     A(ievt,635) = x0 * x0 * y3 * y2;
     A(ievt,636) = x0 * x0 * y3 * b2;

     A(ievt,637) = x0 * x0 * b3 * x2;
     A(ievt,638) = x0 * x0 * b3 * a2;
     A(ievt,639) = x0 * x0 * b3 * y2;
     A(ievt,640) = x0 * x0 * b3 * b2;

     A(ievt,641) = x0 * x0 * x2 * a2;
     A(ievt,642) = x0 * x0 * x2 * y2;
     A(ievt,643) = x0 * x0 * x2 * b2;

     A(ievt,644) = x0 * x0 * a2 * y2;
     A(ievt,645) = x0 * x0 * a2 * b2;

     A(ievt,646) = x0 * x0 * y2 * b2;

     A(ievt,647) = x2 * x2 * t * x3;
     A(ievt,648) = x2 * x2 * t * a3;
     A(ievt,649) = x2 * x2 * t * y3;
     A(ievt,650) = x2 * x2 * t * b3;
     A(ievt,651) = x2 * x2 * t * x0;
     A(ievt,652) = x2 * x2 * t * a2;
     A(ievt,653) = x2 * x2 * t * y2;
     A(ievt,654) = x2 * x2 * t * b2;

     A(ievt,655) = x2 * x2 * x3 * a3;
     A(ievt,656) = x2 * x2 * x3 * y3;
     A(ievt,657) = x2 * x2 * x3 * b3;
     A(ievt,658) = x2 * x2 * x3 * x0;
     A(ievt,659) = x2 * x2 * x3 * a2;
     A(ievt,660) = x2 * x2 * x3 * y2;
     A(ievt,661) = x2 * x2 * x3 * b2;

     A(ievt,662) = x2 * x2 * a3 * y3;
     A(ievt,663) = x2 * x2 * a3 * b3;
     A(ievt,664) = x2 * x2 * a3 * x0;
     A(ievt,665) = x2 * x2 * a3 * a2;
     A(ievt,666) = x2 * x2 * a3 * y2;
     A(ievt,667) = x2 * x2 * a3 * b2;

     A(ievt,668) = x2 * x2 * y3 * b3;
     A(ievt,669) = x2 * x2 * y3 * x0;
     A(ievt,670) = x2 * x2 * y3 * a2;
     A(ievt,671) = x2 * x2 * y3 * y2;
     A(ievt,672) = x2 * x2 * y3 * b2;

     A(ievt,673) = x2 * x2 * b3 * x0;
     A(ievt,674) = x2 * x2 * b3 * a2;
     A(ievt,675) = x2 * x2 * b3 * y2;
     A(ievt,676) = x2 * x2 * b3 * b2;

     A(ievt,677) = x2 * x2 * x0 * a2;
     A(ievt,678) = x2 * x2 * x0 * y2;
     A(ievt,679) = x2 * x2 * x0 * b2;

     A(ievt,680) = x2 * x2 * a2 * y2;
     A(ievt,681) = x2 * x2 * a2 * b2;

     A(ievt,682) = x2 * x2 * y2 * b2;

     A(ievt,683) = a2 * a2 * t * x3;
     A(ievt,684) = a2 * a2 * t * a3;
     A(ievt,685) = a2 * a2 * t * y3;
     A(ievt,686) = a2 * a2 * t * b3;
     A(ievt,687) = a2 * a2 * t * x0;
     A(ievt,688) = a2 * a2 * t * x2;
     A(ievt,689) = a2 * a2 * t * y2;
     A(ievt,691) = a2 * a2 * t * b2;

     A(ievt,692) = a2 * a2 * x3 * a3;
     A(ievt,694) = a2 * a2 * x3 * y3;
     A(ievt,695) = a2 * a2 * x3 * b3;
     A(ievt,696) = a2 * a2 * x3 * x0;
     A(ievt,697) = a2 * a2 * x3 * x2;
     A(ievt,698) = a2 * a2 * x3 * y2;
     A(ievt,699) = a2 * a2 * x3 * b2;

     A(ievt,700) = a2 * a2 * a3 * y3;
     A(ievt,701) = a2 * a2 * a3 * b3;
     A(ievt,702) = a2 * a2 * a3 * x0;
     A(ievt,703) = a2 * a2 * a3 * x2;
     A(ievt,704) = a2 * a2 * a3 * y2;
     A(ievt,705) = a2 * a2 * a3 * b2;

     A(ievt,706) = a2 * a2 * y3 * b3;
     A(ievt,707) = a2 * a2 * y3 * x0;
     A(ievt,708) = a2 * a2 * y3 * x2;
     A(ievt,709) = a2 * a2 * y3 * y2;
     A(ievt,710) = a2 * a2 * y3 * b2;

     A(ievt,712) = a2 * a2 * b3 * x0;
     A(ievt,713) = a2 * a2 * b3 * x2;
     A(ievt,714) = a2 * a2 * b3 * y2;
     A(ievt,715) = a2 * a2 * b3 * b2;

     A(ievt,716) = a2 * a2 * x0 * x2;
     A(ievt,717) = a2 * a2 * x0 * y2;
     A(ievt,718) = a2 * a2 * x0 * b2;

     A(ievt,719) = a2 * a2 * x2 * y2;
     A(ievt,720) = a2 * a2 * x2 * b2;

     A(ievt,721) = a2 * a2 * y2 * b2;

     A(ievt,722) = y2 * y2 * t * x3;
     A(ievt,723) = y2 * y2 * t * a3;
     A(ievt,724) = y2 * y2 * t * y3;
     A(ievt,725) = y2 * y2 * t * b3;
     A(ievt,726) = y2 * y2 * t * x0;
     A(ievt,727) = y2 * y2 * t * x2;
     A(ievt,728) = y2 * y2 * t * a2;
     A(ievt,729) = y2 * y2 * t * b2;

     A(ievt,730) = y2 * y2 * x3 * a3;
     A(ievt,731) = y2 * y2 * x3 * y3;
     A(ievt,732) = y2 * y2 * x3 * b3;
     A(ievt,733) = y2 * y2 * x3 * x0;
     A(ievt,734) = y2 * y2 * x3 * x2;
     A(ievt,735) = y2 * y2 * x3 * a2;
     A(ievt,736) = y2 * y2 * x3 * b2;

     A(ievt,737) = y2 * y2 * a3 * y3;
     A(ievt,734) = y2 * y2 * a3 * b3;
     A(ievt,735) = y2 * y2 * a3 * x0;
     A(ievt,736) = y2 * y2 * a3 * x2;
     A(ievt,737) = y2 * y2 * a3 * a2;
     A(ievt,738) = y2 * y2 * a3 * b2;

     A(ievt,739) = y2 * y2 * y3 * b3;
     A(ievt,740) = y2 * y2 * y3 * x0;
     A(ievt,741) = y2 * y2 * y3 * x2;
     A(ievt,742) = y2 * y2 * y3 * a2;
     A(ievt,743) = y2 * y2 * y3 * b2;

     A(ievt,744) = y2 * y2 * b3 * x0;
     A(ievt,745) = y2 * y2 * b3 * x2;
     A(ievt,746) = y2 * y2 * b3 * a2;
     A(ievt,747) = y2 * y2 * b3 * b2;

     A(ievt,748) = y2 * y2 * x0 * x2;
     A(ievt,749) = y2 * y2 * x0 * a2;
     A(ievt,750) = y2 * y2 * x0 * b2;

     A(ievt,751) = y2 * y2 * x2 * a2;
     A(ievt,752) = y2 * y2 * x2 * b2;

     A(ievt,753) = y2 * y2 * a2 * b2;

     A(ievt,754) = b2 * b2 * t * x3;
     A(ievt,755) = b2 * b2 * t * a3;
     A(ievt,756) = b2 * b2 * t * y3;
     A(ievt,757) = b2 * b2 * t * b3;
     A(ievt,758) = b2 * b2 * t * x0;
     A(ievt,759) = b2 * b2 * t * x2;
     A(ievt,760) = b2 * b2 * t * a2;
     A(ievt,761) = b2 * b2 * t * y2;

     A(ievt,762) = b2 * b2 * x3 * a3;
     A(ievt,763) = b2 * b2 * x3 * y3;
     A(ievt,764) = b2 * b2 * x3 * b3;
     A(ievt,765) = b2 * b2 * x3 * x0;
     A(ievt,766) = b2 * b2 * x3 * x2;
     A(ievt,767) = b2 * b2 * x3 * a2;
     A(ievt,768) = b2 * b2 * x3 * y2;

     A(ievt,769) = b2 * b2 * a3 * y3;
     A(ievt,770) = b2 * b2 * a3 * b3;
     A(ievt,771) = b2 * b2 * a3 * x0;
     A(ievt,772) = b2 * b2 * a3 * x2;
     A(ievt,773) = b2 * b2 * a3 * a2;
     A(ievt,774) = b2 * b2 * a3 * y2;

     A(ievt,775) = b2 * b2 * y3 * b3;
     A(ievt,776) = b2 * b2 * y3 * x0;
     A(ievt,778) = b2 * b2 * y3 * x2;
     A(ievt,779) = b2 * b2 * y3 * a2;
     A(ievt,780) = b2 * b2 * y3 * y2;

     A(ievt,781) = b2 * b2 * b3 * x0;
     A(ievt,782) = b2 * b2 * b3 * x2;
     A(ievt,783) = b2 * b2 * b3 * a2;
     A(ievt,784) = b2 * b2 * b3 * y2;

     A(ievt,785) = b2 * b2 * x0 * x2;
     A(ievt,786) = b2 * b2 * x0 * a2;
     A(ievt,787) = b2 * b2 * x0 * y2;

     A(ievt,788) = b2 * b2 * x2 * a2;
     A(ievt,789) = b2 * b2 * x2 * y2;

     A(ievt,790) = b2 * b2 * a2 * y2;

     A(ievt,791) = t * x3 * a3 * y3;
     A(ievt,792) = t * x3 * a3 * b3;
     A(ievt,793) = t * x3 * a3 * x0;
     A(ievt,794) = t * x3 * a3 * x2;
     A(ievt,795) = t * x3 * a3 * a2;
     A(ievt,796) = t * x3 * a3 * y2;
     A(ievt,797) = t * x3 * a3 * b2;

     A(ievt,798) = t * x3 * y3 * b3;
     A(ievt,799) = t * x3 * y3 * x0;
     A(ievt,800) = t * x3 * y3 * x2;
     A(ievt,801) = t * x3 * y3 * a2;
     A(ievt,802) = t * x3 * y3 * y2;
     A(ievt,803) = t * x3 * y3 * b2;

     A(ievt,804) = t * x3 * b3 * x0;
     A(ievt,805) = t * x3 * b3 * x2;
     A(ievt,806) = t * x3 * b3 * a2;
     A(ievt,807) = t * x3 * b3 * y2;
     A(ievt,808) = t * x3 * b3 * b2;

     A(ievt,809) = t * x3 * x0 * x2;
     A(ievt,810) = t * x3 * x0 * a2;
     A(ievt,811) = t * x3 * x0 * y2;
     A(ievt,812) = t * x3 * x0 * b2;

     A(ievt,813) = t * x3 * x2 * a2;
     A(ievt,814) = t * x3 * x2 * y2;
     A(ievt,815) = t * x3 * x2 * b2;
     A(ievt,816) = t * x3 * a2 * y2;
     A(ievt,817) = t * x3 * a2 * b2;

     A(ievt,818) = t * x3 * y2 * b2;

     A(ievt,819) = t * a3 * y3 * b3;
     A(ievt,820) = t * a3 * y3 * x0;
     A(ievt,821) = t * a3 * y3 * x2;
     A(ievt,822) = t * a3 * y3 * a2;
     A(ievt,823) = t * a3 * y3 * y2;
     A(ievt,824) = t * a3 * y3 * b2;

     A(ievt,825) = t * a3 * b3 * x0;
     A(ievt,826) = t * a3 * b3 * x2;
     A(ievt,827) = t * a3 * b3 * a2;
     A(ievt,828) = t * a3 * b3 * y2;
     A(ievt,829) = t * a3 * b3 * b2;

     A(ievt,830) = t * a3 * x0 * x2;
     A(ievt,831) = t * a3 * x0 * a2;
     A(ievt,832) = t * a3 * x0 * y2;
     A(ievt,833) = t * a3 * x0 * b2;

     A(ievt,834) = t * a3 * x2 * a2;
     A(ievt,835) = t * a3 * x2 * y2;
     A(ievt,836) = t * a3 * x2 * b2;

     A(ievt,837) = t * a3 * a2 * y2;
     A(ievt,838) = t * a3 * a2 * b2;

     A(ievt,839) = t * a3 * y2 * b2;

     A(ievt,840) = t * y3 * b3 * x0;
     A(ievt,841) = t * y3 * b3 * x2;
     A(ievt,842) = t * y3 * b3 * a2;
     A(ievt,843) = t * y3 * b3 * y2;
     A(ievt,844) = t * y3 * b3 * b2;

     A(ievt,845) = t * y3 * x0 * x2;
     A(ievt,846) = t * y3 * x0 * a2;
     A(ievt,847) = t * y3 * x0 * y2;
     A(ievt,848) = t * y3 * x0 * b2;

     A(ievt,849) = t * y3 * x2 * a2;
     A(ievt,850) = t * y3 * x2 * y2;
     A(ievt,851) = t * y3 * x2 * b2;

     A(ievt,852) = t * y3 * a2 * y2;
     A(ievt,853) = t * y3 * a2 * b2;

     A(ievt,854) = t * y3 * y2 * b2;

     A(ievt,855) = t * b3 * x0 * x2;
     A(ievt,856) = t * b3 * x0 * a2;
     A(ievt,857) = t * b3 * x0 * y2;
     A(ievt,858) = t * b3 * x0 * b2;

     A(ievt,859) = t * b3 * x2 * a2;
     A(ievt,860) = t * b3 * x2 * y2;
     A(ievt,861) = t * b3 * x2 * b2;

     A(ievt,862) = t * b3 * a2 * y2;
     A(ievt,863) = t * b3 * a2 * b2;

     A(ievt,864) = t * b3 * y2 * b2;

     A(ievt,865) = t * x0 * x2 * a2;
     A(ievt,866) = t * x0 * x2 * y2;
     A(ievt,867) = t * x0 * x2 * b2;

     A(ievt,868) = t * x0 * a2 * y2;
     A(ievt,869) = t * x0 * a2 * b2;

     A(ievt,870) = t * x0 * y2 * b2;

     A(ievt,871) = t * x2 * a2 * y2;
     A(ievt,872) = t * x2 * a2 * b2;

     A(ievt,873) = t * x2 * y2 * b2;

     A(ievt,874) = t * a2 * y2 * b2;

     A(ievt,875) = x3 * a3 * y3 * b3;
     A(ievt,876) = x3 * a3 * y3 * x0;
     A(ievt,877) = x3 * a3 * y3 * x2;
     A(ievt,878) = x3 * a3 * y3 * a2;
     A(ievt,879) = x3 * a3 * y3 * y2;
     A(ievt,880) = x3 * a3 * y3 * b2;

     A(ievt,881) = x3 * a3 * b3 * x0;
     A(ievt,882) = x3 * a3 * b3 * x2;
     A(ievt,883) = x3 * a3 * b3 * a2;
     A(ievt,884) = x3 * a3 * b3 * y2;
     A(ievt,885) = x3 * a3 * b3 * b2;

     A(ievt,886) = x3 * a3 * x0 * x2;
     A(ievt,887) = x3 * a3 * x0 * a2;
     A(ievt,888) = x3 * a3 * x0 * y2;
     A(ievt,889) = x3 * a3 * x0 * b2;

     A(ievt,890) = x3 * a3 * x2 * a2;
     A(ievt,891) = x3 * a3 * x2 * y2;
     A(ievt,892) = x3 * a3 * x2 * b2;

     A(ievt,893) = x3 * a3 * a2 * y2;
     A(ievt,894) = x3 * a3 * a2 * b2;

     A(ievt,895) = x3 * a3 * y2 * b2;

     A(ievt,896) = x3 * y3 * b3 * x0;
     A(ievt,897) = x3 * y3 * b3 * x2;
     A(ievt,898) = x3 * y3 * b3 * a2;
     A(ievt,899) = x3 * y3 * b3 * y2;
     A(ievt,900) = x3 * y3 * b3 * b2;

     A(ievt,901) = x3 * y3 * x0 * x2;
     A(ievt,902) = x3 * y3 * x0 * a2;
     A(ievt,903) = x3 * y3 * x0 * y2;
     A(ievt,904) = x3 * y3 * x0 * b2;

     A(ievt,905) = x3 * y3 * x2 * a2;
     A(ievt,906) = x3 * y3 * x2 * y2;
     A(ievt,907) = x3 * y3 * x2 * b2;

     A(ievt,908) = x3 * y3 * a2 * y2;
     A(ievt,909) = x3 * y3 * a2 * b2;

     A(ievt,910) = x3 * y3 * y2 * b2;

     A(ievt,911) = x3 * b3 * x0 * x2;
     A(ievt,912) = x3 * b3 * x0 * a2;
     A(ievt,913) = x3 * b3 * x0 * y2;
     A(ievt,914) = x3 * b3 * x0 * b2;

     A(ievt,915) = x3 * b3 * x2 * a2;
     A(ievt,916) = x3 * b3 * x2 * y2;
     A(ievt,917) = x3 * b3 * x2 * b2;

     A(ievt,918) = x3 * b3 * a2 * y2;
     A(ievt,919) = x3 * b3 * a2 * b2;

     A(ievt,920) = x3 * b3 * y2 * b2;

     A(ievt,921) = x3 * x0 * x2 * a2;
     A(ievt,922) = x3 * x0 * x2 * y2;
     A(ievt,923) = x3 * x0 * x2 * b2;

     A(ievt,924) = x3 * x0 * a2 * y2;
     A(ievt,925) = x3 * x0 * a2 * b2;

     A(ievt,926) = x3 * x0 * y2 * b2;

     A(ievt,927) = x3 * x2 * a2 * y2;
     A(ievt,928) = x3 * x2 * a2 * b2;

     A(ievt,929) = x3 * x2 * y2 * b2;

     A(ievt,930) = x3 * a2 * y2 * b2;

     A(ievt,931) = a3 * y3 * b3 * x0;
     A(ievt,932) = a3 * y3 * b3 * x2;
     A(ievt,933) = a3 * y3 * b3 * a2;
     A(ievt,934) = a3 * y3 * b3 * y2;
     A(ievt,935) = a3 * y3 * b3 * b2;

     A(ievt,936) = a3 * y3 * x0 * x2;
     A(ievt,937) = a3 * y3 * x0 * a2;
     A(ievt,938) = a3 * y3 * x0 * y2;
     A(ievt,939) = a3 * y3 * x0 * b2;

     A(ievt,940) = a3 * y3 * x2 * a2;
     A(ievt,941) = a3 * y3 * x2 * y2;
     A(ievt,942) = a3 * y3 * x2 * b2;
     A(ievt,943) = a3 * y3 * a2 * y2;
     A(ievt,944) = a3 * y3 * a2 * b2;

     A(ievt,945) = a3 * y3 * y2 * b2;

     A(ievt,946) = a3 * b3 * x0 * x2;
     A(ievt,947) = a3 * b3 * x0 * a2;
     A(ievt,948) = a3 * b3 * x0 * y2;
     A(ievt,949) = a3 * b3 * x0 * b2;

     A(ievt,950) = a3 * b3 * x2 * a2;
     A(ievt,951) = a3 * b3 * x2 * y2;
     A(ievt,952) = a3 * b3 * x2 * b2;

     A(ievt,953) = a3 * b3 * a2 * y2;
     A(ievt,954) = a3 * b3 * a2 * b2;

     A(ievt,955) = a3 * b3 * y2 * b2;

     A(ievt,956) = a3 * x0 * x2 * a2;
     A(ievt,957) = a3 * x0 * x2 * y2;
     A(ievt,958) = a3 * x0 * x2 * b2;

     A(ievt,959) = a3 * x0 * a2 * y2;
     A(ievt,960) = a3 * x0 * a2 * b2;

     A(ievt,961) = a3 * x0 * y2 * b2;

     A(ievt,962) = a3 * x2 * a2 * y2;
     A(ievt,963) = a3 * x2 * a2 * b2;

     A(ievt,964) = a3 * x2 * y2 * b2;

     A(ievt,965) = a3 * a2 * y2 * b2;

     A(ievt,966) = y3 * b3 * x0 * x2;
     A(ievt,967) = y3 * b3 * x0 * a2;
     A(ievt,968) = y3 * b3 * x0 * y2;
     A(ievt,969) = y3 * b3 * x0 * b2;

     A(ievt,970) = y3 * b3 * x2 * a2;
     A(ievt,971) = y3 * b3 * x2 * y2;
     A(ievt,972) = y3 * b3 * x2 * b2;

     A(ievt,973) = y3 * b3 * a2 * y2;
     A(ievt,974) = y3 * b3 * a2 * b2;

     A(ievt,975) = y3 * b3 * y2 * b2;

     A(ievt,976) = y3 * x0 * x2 * a2;
     A(ievt,977) = y3 * x0 * x2 * y2;
     A(ievt,978) = y3 * x0 * x2 * b2;

     A(ievt,979) = y3 * x0 * a2 * y2;
     A(ievt,980) = y3 * x0 * a2 * b2;

     A(ievt,981) = y3 * x0 * y2 * b2;

     A(ievt,982) = y3 * x2 * a2 * y2;
     A(ievt,983) = y3 * x2 * a2 * b2;

     A(ievt,984) = y3 * x2 * y2 * b2;

     A(ievt,985) = y3 * a2 * y2 * b2;

     A(ievt,986) = b3 * x0 * x2 * a2;
     A(ievt,987) = b3 * x0 * x2 * y2;
     A(ievt,988) = b3 * x0 * x2 * b2;

     A(ievt,989) = b3 * x0 * a2 * y2;
     A(ievt,990) = b3 * x0 * a2 * b2;

     A(ievt,991) = b3 * x0 * y2 * b2;

     A(ievt,992) = b3 * x2 * a2 * y2;
     A(ievt,993) = b3 * x2 * a2 * b2;

     A(ievt,994) = b3 * x2 * y2 * b2;

     A(ievt,995) = b3 * a2 * y2 * b2;

     A(ievt,996) = x0 * x2 * a2 * y2;
     A(ievt,997) = x0 * x2 * a2 * b2;

     A(ievt,998) = x0 * x2 * y2 * b2;

     A(ievt,999) = x0 * a2 * y2 * b2;

     A(ievt,1000) = x2 * a2 * y2 * b2;

     b(ievt,0) = Ref_m[iref];
  
     value(ievt,0) = z_select;
     value(ievt,1) = aq_select;
     value(ievt,2) = t;
     value(ievt,3) = x3;
     value(ievt,4) = a3;
     value(ievt,5) = y3;
     value(ievt,6) = b3;
     value(ievt,7) = x0;
     value(ievt,8) = x2;
     value(ievt,9) = a2;
     value(ievt,10) = y2;
     value(ievt,11) = b2;
     value(ievt,12) = runnumber;
     value(ievt,13) = ssrd;

     ievt++;

	 }
	
}
 if(ievt != Nevt){
	 cout << "The number of events is " << ievt << " Not equal to " << Nevt << endl;
 }else{
	 cout << "The number of events is " << ievt << " " << endl;
	 }
 if(!HasEvents){
    cout << "Some species has not enough number of events,\n";
	return; 
 }


 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/set_matrix_svd4th_eachstripst3_ref4_3step_unit2_SSR.dat");
 if (fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	fout << b(n,0) << " | ";

	for(int m = 0; m < Nprm; m++){
		fout << A(n,m) << "  " ;
	}
	fout << "\n";
}

	fout.close();

 ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_eachstripst3_ref4_3step_unit2_SSR.dat");
 if (foutselect.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	for(int m = 0; m < 14; m++){
		foutselect << value(n,m) << "  "  << " | ";
	}
	foutselect << "\n";
}

	foutselect.close();


   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref4_3step.hist_selected_unit2_SSR.root","recreate");

  TH1D *tof_selected = new TH1D("tof_selected","tof_selected",1000,-10,10);
  TH2D *tofaq_selected = new TH2D("tofaq_selected","tofaq_selected",1000,1.8,2.2,1000,-10,10);
  TH1D *x3_selected = new TH1D("x3_selected","x3_selected",300,-5,5);
  TH2D *x3aq_selected = new TH2D("x3aq_selected","x3aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *a3_selected = new TH1D("a3_selected","a3_selected",300,-5,5);
  TH2D *a3aq_selected = new TH2D("a3aq_selected","a3aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *y3_selected = new TH1D("y3_selected","y3_selected",300,-5,5);
  TH2D *y3aq_selected = new TH2D("y3aq_selected","y3aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *b3_selected = new TH1D("b3_selected","b3_selected",300,-5,5);
  TH2D *b3aq_selected = new TH2D("b3aq_selected","b3aq_selected",100,1.8,2.2,300,-5,5);
  TH1D *x0_selected = new TH1D("x0_selected","x0_selected",300,-5,5);
  TH2D *x0aq_selected = new TH2D("x0aq_selected","x0aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *x2_selected = new TH1D("x2_selected","x2_selected",300,-5,5);
  TH2D *x2aq_selected = new TH2D("x2aq_selected","x2aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *a2_selected = new TH1D("a2_selected","a2_selected",300,-5,5);
  TH2D *a2aq_selected = new TH2D("a2aq_selected","a2aq_selected",1000,1.8,2.2,300,-5,5);
  TH1D *y2_selected = new TH1D("y2_selected","y2_selected",300,-5,5);
  TH2D *y2aq_selected = new TH2D("y2aq_selected","y2aq_selected",1000,1.8,2.2,300,-5,5);
  TH2D *y2ssr_selected = new TH2D("y2ssr_selected","y2ssr_select5ed",300,-5,5,300,0,5);
  TH1D *b2_selected = new TH1D("b2_selected","b2_selected",300,-5,5);
  TH2D *b2ssr_selected = new TH2D("b2ssr_selected","b2ssr_selected",300,-5,5,300,0,5);
  TH1D *event_selected = new TH1D("event_selected","event_selected",102,169.5,271.5);

 for(int nn = 0; nn < Nevt; nn++){
  tof_selected->Fill(value(nn,2));
  tofaq_selected->Fill(value(nn,1),value(nn,2));
  x3_selected->Fill(value(nn,3));
  x3aq_selected->Fill(value(nn,1),value(nn,3));
  a3_selected->Fill(value(nn,4));
  a3aq_selected->Fill(value(nn,1),value(nn,4));
  y3_selected->Fill(value(nn,5));
  y3aq_selected->Fill(value(nn,1),value(nn,5));
  b3_selected->Fill(value(nn,6));
  b3aq_selected->Fill(value(nn,1),value(nn,6));
  x0_selected->Fill(value(nn,7));
  x0aq_selected->Fill(value(nn,1),value(nn,7));
  x2_selected->Fill(value(nn,8));
  x2aq_selected->Fill(value(nn,1),value(nn,8));
  a2_selected->Fill(value(nn,9));
  a2aq_selected->Fill(value(nn,1),value(nn,9));
  y2_selected->Fill(value(nn,10));
  y2aq_selected->Fill(value(nn,1),value(nn,10));
  y2ssr_selected->Fill(value(nn,10),value(nn,13));
  b2_selected->Fill(value(nn,11));
  b2ssr_selected->Fill(value(nn,11),value(nn,13));
  event_selected->Fill(value(nn,12));
}

 tof_selected->Write();
 tofaq_selected->Write();
 x3_selected->Write(); 
 x3aq_selected->Write(); 
 a3_selected->Write();
 a3aq_selected->Write();
 y3_selected->Write();
 y3aq_selected->Write();
 b3_selected->Write();
 b3aq_selected->Write();
 x0_selected->Write();
 x0aq_selected->Write();
 x2_selected->Write();
 x2aq_selected->Write();
 a2_selected->Write();
 a2aq_selected->Write();
 y2_selected->Write();
 y2aq_selected->Write();
 y2ssr_selected->Write();
 b2_selected->Write();
 b2ssr_selected->Write();
 event_selected->Write();

 ofv->Close();



//// Set Matrix
////
 TMatrixD At(Nprm,Nevt);
          At.Transpose(A);

  TMatrixD Cov(Nprm,Nprm);
  Cov.Mult(At,A);

  TMatrixD Atb(Nprm,1);
  Atb.Mult(At,b);

  TVectorD Atb_v = TMatrixDColumn(Atb,0);
  
//// Solve Normal Equation

  TDecompSVD svd(Cov);
  Bool_t ok;

  TVectorD Theta(Nprm);
  Theta = svd.Solve(Atb_v,ok);


//// Save the results of SVD
  Double_t d1, d2;
  svd.Det(d1,d2);
  cout << "cond: " << svd.Condition() << endl;
  cout << "det: "  << d1*TMath::Power(2, d2) << endl;
  cout << "tol: " << svd.GetTol() << endl;
  Theta.Print();

   char foutname[50];
   std::ofstream foutmtr("output/mass/svd4th_out_st3_ref4_3step_unit2_SSR.dat");
   foutmtr << "cond: " << svd.Condition() << endl;
   foutmtr << "det: "  << d1*TMath::Power(2, d2) << endl;
   foutmtr << "tol: " << svd.GetTol() << endl;

   foutmtr.close();

   std::ofstream foutmtrth("output/mass/theta_st3_ref4_3step_unit2_SSR.dat");
 if (foutmtrth.fail()){
	 cout << "Error; Could not open output file for Theta matrix..." << endl << endl;
	 return;
  }
for (int itheta = 0; itheta < Nprm; itheta++){
   foutmtrth <<  Theta(itheta) << endl;
}
   foutmtrth.close();


////// Comfirm the condition of decomposition
//
//Double_t cond = svd.Condition();
//
//int p = 0;
//while( p < 1){
//printf("The condition is %f.\n Would you like to continue?(y/n)\n",cond);
//char ans[256];
//cin >> ans;
//
//if(strcmp(ans,"y")==0){
//   	printf("Generating histograms\n");
//	p++;
//}else if (strcmp(ans,"n")==0){
//    return 0;
//}else{
//   printf("please answer y/n \n");
//   p = 0;
//}}


//// AoQ cor

   vector<Double_t> Aq_cor;
   TVectorD Rd(Nprm);
   vector<Int_t>evt_valid;
   
  for (Int_t iData = 0; iData < nData; iData++){
    double sum = 0.;

     tree->GetEntry(iData);
	 art::TDiaTimingData *dia_tof32st3cor = (art::TDiaTimingData*) array_dia_tof32st3->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku_cor = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd_cor = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0_cor = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

    Int_t hit_dia_tof32st3cor = array_dia_tof32st3->GetEntriesFast();
    Int_t hit_tracku_cor = array_tracku->GetEntriesFast();
    Int_t hit_trackd_cor = array_trackd->GetEntriesFast();
    Int_t hit_s0_cor = array_s0->GetEntriesFast();

     if ( hit_dia_tof32st3cor > 0 && hit_tracku_cor > 0 && hit_trackd_cor > 0 && hit_s0_cor >0){
 
     Double_t ti_cor = dia_tof32st3cor->GetTiming();
     Double_t x3i_cor = tracku_cor->GetX();
     Double_t a3i_cor = tracku_cor->GetA() * 1000.;
     Double_t y3i_cor = tracku_cor->GetY();
     Double_t b3i_cor = tracku_cor->GetB() * 1000.;
     Double_t x0i_cor = sr0_cor->GetPosition();
     Double_t x2i_cor = trackd_cor->GetX();
     Double_t a2i_cor = trackd_cor->GetA() * 1000.;
     Double_t y2i_cor = trackd_cor->GetY();
     Double_t b2i_cor = trackd_cor->GetB() * 1000.;
// unit orientation
//     Double_t t_cor = (ti_cor - 2042.) * 0.25;  
//     Double_t x3_cor = x3i_cor * 0.1; 
//     Double_t a3_cor = a3i_cor * 0.1;
//     Double_t y3_cor = y3i_cor * 0.1;
//     Double_t b3_cor = b3i_cor * 0.1;
//     Double_t x0_cor = x0i_cor * 0.1; 
//     Double_t x2_cor = x2i_cor * 0.1; 
//     Double_t a2_cor = a2i_cor * 0.1;
//     Double_t y2_cor = y2i_cor * 0.1;
//     Double_t b2_cor = b2i_cor * 0.1;

//     Double_t t_cor = (ti_cor - 2042.) * 0.125;  
//     Double_t x3_cor = x3i_cor * 0.1; 
//     Double_t a3_cor = a3i_cor * 0.1;
//     Double_t y3_cor = y3i_cor;
//     Double_t b3_cor = b3i_cor * 0.1 + 1;
//     Double_t x0_cor = x0i_cor * 0.05; 
//     Double_t x2_cor = x2i_cor * 0.1; 
//     Double_t a2_cor = a2i_cor * 0.05;
//     Double_t y2_cor = y2i_cor * 0.05 - 1;
//     Double_t b2_cor = b2i_cor * 0.05 -0.2;

     Double_t t_cor = (ti_cor - 2042.) * 0.125;  
     Double_t x3_cor = x3i_cor * 0.1; 
     Double_t a3_cor = a3i_cor * 0.1;
     Double_t y3_cor = y3i_cor + 2;
     Double_t b3_cor = b3i_cor * 0.05 + 0.5;
     Double_t x0_cor = x0i_cor * 0.015; 
     Double_t x2_cor = x2i_cor * 0.1; 
     Double_t a2_cor = a2i_cor * 0.025;
     Double_t y2_cor = y2i_cor * 0.05 - 1;
     Double_t b2_cor = b2i_cor * 0.05 - 0.2;

     Rd(0) = 1.; 

     Rd(1)  = t_cor;
     Rd(2)  = x3_cor;
     Rd(3)  = a3_cor;
     Rd(4)  = y3_cor;
     Rd(5)  = b3_cor;
     Rd(6)  = x0_cor;
     Rd(7)  = x2_cor;
     Rd(8)  = a2_cor;
     Rd(9)  = y2_cor;
     Rd(10) = b2_cor;
 
     Rd(11) = t_cor * t_cor;
     Rd(12) = x3_cor * x3_cor;
     Rd(13) = a3_cor * a3_cor;
     Rd(14) = y3_cor * y3_cor;
     Rd(15) = b3_cor * b3_cor;
     Rd(16) = x0_cor * x0_cor;
     Rd(17) = x2_cor * x2_cor;
     Rd(18) = a2_cor * a2_cor;
     Rd(19) = y2_cor * y2_cor;
     Rd(20) = b2_cor * b2_cor;
 
     Rd(21) = t_cor * x3_cor;
     Rd(22) = t_cor * a3_cor;
     Rd(23) = t_cor * y3_cor;
     Rd(24) = t_cor * b3_cor;
     Rd(25) = t_cor * x0_cor;
     Rd(26) = t_cor * x2_cor;
     Rd(27) = t_cor * a2_cor;
     Rd(28) = t_cor * y2_cor;
     Rd(29) = t_cor * b2_cor;
 
     Rd(30) = x3_cor * a3_cor;
     Rd(31) = x3_cor * y3_cor;
     Rd(32) = x3_cor * b3_cor;
     Rd(33) = x3_cor * x0_cor;
     Rd(34) = x3_cor * x2_cor;
     Rd(35) = x3_cor * a2_cor;
     Rd(36) = x3_cor * y2_cor;
     Rd(37) = x3_cor * b2_cor;
 
     Rd(38) = a3_cor * y3_cor;
     Rd(39) = a3_cor * b3_cor;
     Rd(40) = a3_cor * x0_cor;
     Rd(41) = a3_cor * x2_cor;
     Rd(42) = a3_cor * a2_cor;
     Rd(43) = a3_cor * y2_cor;
     Rd(44) = a3_cor * b2_cor;
 
     Rd(45) = y3_cor * b3_cor;
     Rd(46) = y3_cor * x0_cor;
     Rd(47) = y3_cor * x2_cor;
     Rd(48) = y3_cor * a2_cor;
     Rd(49) = y3_cor * y2_cor;
     Rd(50) = y3_cor * b2_cor;
 
     Rd(51) = b3_cor * x0_cor;
     Rd(52) = b3_cor * x2_cor;
     Rd(53) = b3_cor * a2_cor;
     Rd(54) = b3_cor * y2_cor;
     Rd(55) = b3_cor * b2_cor;
 
     Rd(56) = x0_cor * x2_cor;
     Rd(57) = x0_cor * a2_cor;
     Rd(58) = x0_cor * y2_cor;
     Rd(59) = x0_cor * b2_cor;
 
     Rd(60) = x2_cor * a2_cor;
     Rd(61) = x2_cor * y2_cor;
     Rd(62) = x2_cor * b2_cor;
 
     Rd(63) = a2_cor * y2_cor;
     Rd(64) = a2_cor * b2_cor;
 
     Rd(65) = y2_cor * b2_cor;
 
     Rd(66) = t_cor * t_cor * t_cor;
     Rd(67) = x3_cor * x3_cor * x3_cor;
     Rd(68) = a3_cor * a3_cor * a3_cor;
     Rd(69) = y3_cor * y3_cor * y3_cor;
     Rd(70) = b3_cor * b3_cor * b3_cor;
     Rd(71) = x0_cor * x0_cor * x0_cor;
     Rd(72) = x2_cor * x2_cor * x2_cor;
     Rd(73) = a2_cor * a2_cor * a2_cor;
     Rd(74) = y2_cor * y2_cor * y2_cor;
     Rd(75) = b2_cor * b2_cor * b2_cor;
 
     Rd(76) = t_cor * t_cor * x3_cor;
     Rd(77) = t_cor * t_cor * a3_cor;
     Rd(78) = t_cor * t_cor * y3_cor;
     Rd(79) = t_cor * t_cor * b3_cor;
     Rd(80) = t_cor * t_cor * x0_cor;
     Rd(81) = t_cor * t_cor * x2_cor;
     Rd(82) = t_cor * t_cor * a2_cor;
     Rd(83) = t_cor * t_cor * y2_cor;
     Rd(84) = t_cor * t_cor * b2_cor;
 
     Rd(85) = x3_cor * x3_cor * t_cor;
     Rd(86) = x3_cor * x3_cor * a3_cor;
     Rd(87) = x3_cor * x3_cor * y3_cor;
     Rd(88) = x3_cor * x3_cor * b3_cor;
     Rd(89) = x3_cor * x3_cor * x0_cor;
     Rd(90) = x3_cor * x3_cor * x2_cor;
     Rd(91) = x3_cor * x3_cor * a2_cor;
     Rd(92) = x3_cor * x3_cor * y2_cor;
     Rd(93) = x3_cor * x3_cor * b2_cor;
 
     Rd(94) = a3_cor * a3_cor * t_cor;
     Rd(95) = a3_cor * a3_cor * x3_cor;
     Rd(96) = a3_cor * a3_cor * y3_cor;
     Rd(97) = a3_cor * a3_cor * b3_cor;
     Rd(98) = a3_cor * a3_cor * x0_cor;
     Rd(99) = a3_cor * a3_cor * x2_cor;
     Rd(100) = a3_cor * a3_cor * a2_cor;
     Rd(101) = a3_cor * a3_cor * y2_cor;
     Rd(102) = a3_cor * a3_cor * b2_cor;
 
     Rd(103) = y3_cor * y3_cor * t_cor;
     Rd(104) = y3_cor * y3_cor * x3_cor;
     Rd(105) = y3_cor * y3_cor * a3_cor;
     Rd(106) = y3_cor * y3_cor * b3_cor;
     Rd(107) = y3_cor * y3_cor * x0_cor;
     Rd(108) = y3_cor * y3_cor * x2_cor;
     Rd(109) = y3_cor * y3_cor * a2_cor;
     Rd(110) = y3_cor * y3_cor * y2_cor;
     Rd(111) = y3_cor * y3_cor * b2_cor;
 
     Rd(112) = b3_cor * b3_cor * t_cor;
     Rd(113) = b3_cor * b3_cor * x3_cor;
     Rd(114) = b3_cor * b3_cor * a3_cor;
     Rd(115) = b3_cor * b3_cor * y3_cor;
     Rd(116) = b3_cor * b3_cor * x0_cor;
     Rd(117) = b3_cor * b3_cor * x2_cor;
     Rd(118) = b3_cor * b3_cor * a2_cor;
     Rd(119) = b3_cor * b3_cor * y2_cor;
     Rd(120) = b3_cor * b3_cor * b2_cor;
 
     Rd(121) = x0_cor * x0_cor * t_cor;
     Rd(122) = x0_cor * x0_cor * x3_cor;
     Rd(123) = x0_cor * x0_cor * a3_cor;
     Rd(124) = x0_cor * x0_cor * y3_cor;
     Rd(125) = x0_cor * x0_cor * b3_cor;
     Rd(126) = x0_cor * x0_cor * x2_cor;
     Rd(127) = x0_cor * x0_cor * a2_cor;
     Rd(128) = x0_cor * x0_cor * y2_cor;
     Rd(129) = x0_cor * x0_cor * b2_cor;
 
     Rd(130) = x2_cor * x2_cor * t_cor;
     Rd(131) = x2_cor * x2_cor * x3_cor;
     Rd(132) = x2_cor * x2_cor * a3_cor;
     Rd(133) = x2_cor * x2_cor * y3_cor;
     Rd(134) = x2_cor * x2_cor * b3_cor;
     Rd(135) = x2_cor * x2_cor * x0_cor;
     Rd(136) = x2_cor * x2_cor * a2_cor;
     Rd(137) = x2_cor * x2_cor * y2_cor;
     Rd(138) = x2_cor * x2_cor * b2_cor;
 
     Rd(139) = a2_cor * a2_cor * t_cor;
     Rd(140) = a2_cor * a2_cor * x3_cor;
     Rd(141) = a2_cor * a2_cor * a3_cor;
     Rd(142) = a2_cor * a2_cor * y3_cor;
     Rd(143) = a2_cor * a2_cor * b3_cor;
     Rd(144) = a2_cor * a2_cor * x0_cor;
     Rd(145) = a2_cor * a2_cor * x2_cor;
     Rd(146) = a2_cor * a2_cor * y2_cor;
     Rd(147) = a2_cor * a2_cor * b2_cor;
 
     Rd(148) = y2_cor * y2_cor * t_cor;
     Rd(149) = y2_cor * y2_cor * x3_cor;
     Rd(150) = y2_cor * y2_cor * a3_cor;
     Rd(151) = y2_cor * y2_cor * y3_cor;
     Rd(152) = y2_cor * y2_cor * b3_cor;
     Rd(153) = y2_cor * y2_cor * x0_cor;
     Rd(154) = y2_cor * y2_cor * x2_cor;
     Rd(155) = y2_cor * y2_cor * a2_cor;
     Rd(156) = y2_cor * y2_cor * b2_cor;
 
     Rd(157) = b2_cor * b2_cor * t_cor;
     Rd(158) = b2_cor * b2_cor * x3_cor;
     Rd(159) = b2_cor * b2_cor * a3_cor;
     Rd(160) = b2_cor * b2_cor * y3_cor;
     Rd(161) = b2_cor * b2_cor * b3_cor;
     Rd(162) = b2_cor * b2_cor * x0_cor;
     Rd(163) = b2_cor * b2_cor * x2_cor;
     Rd(164) = b2_cor * b2_cor * a2_cor;
     Rd(165) = b2_cor * b2_cor * y2_cor;
 
     Rd(166) = t_cor * x3_cor * a3_cor;
     Rd(167) = t_cor * x3_cor * y3_cor;
     Rd(168) = t_cor * x3_cor * b3_cor;
     Rd(169) = t_cor * x3_cor * x0_cor;
     Rd(170) = t_cor * x3_cor * x2_cor;
     Rd(171) = t_cor * x3_cor * a2_cor;
     Rd(172) = t_cor * x3_cor * y2_cor;
     Rd(173) = t_cor * x3_cor * b2_cor;
 
     Rd(174) = t_cor * a3_cor * y3_cor;
     Rd(175) = t_cor * a3_cor * b3_cor;
     Rd(176) = t_cor * a3_cor * x0_cor;
     Rd(177) = t_cor * a3_cor * x2_cor;
     Rd(178) = t_cor * a3_cor * a2_cor;
     Rd(179) = t_cor * a3_cor * y2_cor;
     Rd(180) = t_cor * a3_cor * b2_cor;
 
     Rd(181) = t_cor * y3_cor * b3_cor;
     Rd(182) = t_cor * y3_cor * x0_cor;
     Rd(183) = t_cor * y3_cor * x2_cor;
     Rd(184) = t_cor * y3_cor * a2_cor;
     Rd(185) = t_cor * y3_cor * y2_cor;
     Rd(186) = t_cor * y3_cor * b2_cor;
 
     Rd(187) = t_cor * b3_cor * x0_cor;
     Rd(188) = t_cor * b3_cor * x2_cor;
     Rd(189) = t_cor * b3_cor * a2_cor;
     Rd(190) = t_cor * b3_cor * y2_cor;
     Rd(192) = t_cor * b3_cor * b2_cor;
 
     Rd(193) = t_cor * x0_cor * x2_cor;
     Rd(194) = t_cor * x0_cor * a2_cor;
     Rd(195) = t_cor * x0_cor * y2_cor;
     Rd(196) = t_cor * x0_cor * b2_cor;
 
     Rd(197) = t_cor * x2_cor * a2_cor;
     Rd(198) = t_cor * x2_cor * y2_cor;
     Rd(199) = t_cor * x2_cor * b2_cor;
 
     Rd(200) = t_cor * a2_cor * y2_cor;
     Rd(201) = t_cor * a2_cor * b2_cor;
 
     Rd(202) = t_cor * y2_cor * b2_cor;
 
     Rd(203) = x3_cor * a3_cor * y3_cor;
     Rd(204) = x3_cor * a3_cor * b3_cor;
     Rd(205) = x3_cor * a3_cor * x0_cor;
     Rd(206) = x3_cor * a3_cor * x2_cor;
     Rd(207) = x3_cor * a3_cor * a2_cor;
     Rd(208) = x3_cor * a3_cor * y2_cor;
     Rd(209) = x3_cor * a3_cor * b2_cor;
 
     Rd(210) = x3_cor * y3_cor * b3_cor;
     Rd(211) = x3_cor * y3_cor * x0_cor;
     Rd(212) = x3_cor * y3_cor * x2_cor;
     Rd(213) = x3_cor * y3_cor * a2_cor;
     Rd(214) = x3_cor * y3_cor * y2_cor;
     Rd(215) = x3_cor * y3_cor * b2_cor;
 
     Rd(216) = x3_cor * b3_cor * x0_cor;
     Rd(217) = x3_cor * b3_cor * x2_cor;
     Rd(217) = x3_cor * b3_cor * a2_cor;
     Rd(218) = x3_cor * b3_cor * y2_cor;
     Rd(219) = x3_cor * b3_cor * b2_cor;
 
     Rd(220) = x3_cor * x0_cor * x2_cor;
     Rd(221) = x3_cor * x0_cor * a2_cor;
     Rd(222) = x3_cor * x0_cor * y2_cor;
     Rd(223) = x3_cor * x0_cor * b2_cor;
        
     Rd(224) = x3_cor * x2_cor * a2_cor;
     Rd(225) = x3_cor * x2_cor * y2_cor;
     Rd(226) = x3_cor * x2_cor * b2_cor;
        
     Rd(227) = x3_cor * a2_cor * y2_cor;
     Rd(228) = x3_cor * a2_cor * b2_cor;
 
     Rd(229) = x3_cor * y2_cor * b2_cor;
 
     Rd(230) = a3_cor * y3_cor * b3_cor;
     Rd(231) = a3_cor * y3_cor * x0_cor;
     Rd(232) = a3_cor * y3_cor * x2_cor;
     Rd(233) = a3_cor * y3_cor * a2_cor;
     Rd(234) = a3_cor * y3_cor * y2_cor;
     Rd(235) = a3_cor * y3_cor * b2_cor;
 
     Rd(236) = a3_cor * b3_cor * x0_cor;
     Rd(237) = a3_cor * b3_cor * x2_cor;
     Rd(238) = a3_cor * b3_cor * a2_cor;
     Rd(239) = a3_cor * b3_cor * y2_cor;
     Rd(240) = a3_cor * b3_cor * b2_cor;
 
     Rd(241) = a3_cor * x0_cor * x2_cor;
     Rd(242) = a3_cor * x0_cor * a2_cor;
     Rd(243) = a3_cor * x0_cor * y2_cor;
     Rd(244) = a3_cor * x0_cor * b2_cor;
 
     Rd(245) = a3_cor * x2_cor * a2_cor;
     Rd(246) = a3_cor * x2_cor * y2_cor;
     Rd(247) = a3_cor * x2_cor * b2_cor;
 
     Rd(248) = a3_cor * a2_cor * y2_cor;
     Rd(249) = a3_cor * a2_cor * b2_cor;
 
     Rd(250) = a3_cor * y2_cor * b2_cor;
 
     Rd(251) = y3_cor * b3_cor * x0_cor;
     Rd(252) = y3_cor * b3_cor * x2_cor;
     Rd(253) = y3_cor * b3_cor * a2_cor;
     Rd(254) = y3_cor * b3_cor * y2_cor;
     Rd(255) = y3_cor * b3_cor * b2_cor;
 
     Rd(256) = y3_cor * x0_cor * x2_cor;
     Rd(257) = y3_cor * x0_cor * a2_cor;
     Rd(258) = y3_cor * x0_cor * y2_cor;
     Rd(259) = y3_cor * x0_cor * b2_cor;
 
     Rd(260) = y3_cor * x2_cor * a2_cor;
     Rd(261) = y3_cor * x2_cor * y2_cor;
     Rd(262) = y3_cor * x2_cor * b2_cor;
 
     Rd(263) = y3_cor * a2_cor * y2_cor;
     Rd(264) = y3_cor * a2_cor * b2_cor;
 
     Rd(265) = y3_cor * y2_cor * b2_cor;
 
     Rd(266) = b3_cor * x0_cor * x2_cor;
     Rd(267) = b3_cor * x0_cor * a2_cor;
     Rd(268) = b3_cor * x0_cor * y2_cor;
     Rd(269) = b3_cor * x0_cor * b2_cor;
 
     Rd(270) = b3_cor * x2_cor * a2_cor;
     Rd(271) = b3_cor * x2_cor * y2_cor;
     Rd(272) = b3_cor * x2_cor * b2_cor;
 
     Rd(273) = b3_cor * a2_cor * y2_cor;
     Rd(274) = b3_cor * a2_cor * b2_cor;
 
     Rd(275) = b3_cor * y2_cor * b2_cor;
 
     Rd(276) = x0_cor * x2_cor * a2_cor;
     Rd(277) = x0_cor * x2_cor * y2_cor;
     Rd(278) = x0_cor * x2_cor * b2_cor;
 
     Rd(279) = x0_cor * a2_cor * y2_cor;
     Rd(280) = x0_cor * a2_cor * b2_cor;
 
     Rd(281) = x0_cor * y2_cor * b2_cor;
 
     Rd(282) = x2_cor * a2_cor * y2_cor;
     Rd(283) = x2_cor * a2_cor * b2_cor;
 
     Rd(284) = x2_cor * y2_cor * b2_cor;
 
     Rd(285) = a2_cor * y2_cor * b2_cor;
 
     Rd(286) = t_cor * t_cor * t_cor * t_cor;
     Rd(287) = x3_cor * x3_cor * x3_cor * x3_cor;
     Rd(288) = a3_cor * a3_cor * a3_cor * a3_cor;
     Rd(289) = y3_cor * y3_cor * y3_cor * y3_cor;
     Rd(290) = b3_cor * b3_cor * b3_cor * b3_cor;
     Rd(291) = x0_cor * x0_cor * x0_cor * x0_cor;
     Rd(292) = x2_cor * x2_cor * x2_cor * x2_cor;
     Rd(293) = a2_cor * a2_cor * a2_cor * a2_cor;
     Rd(294) = y2_cor * y2_cor * y2_cor * y2_cor;
     Rd(295) = b2_cor * b2_cor * b2_cor * b2_cor;
 
     Rd(296) = t_cor * t_cor * t_cor * x3_cor;
     Rd(297) = t_cor * t_cor * t_cor * a3_cor;
     Rd(298) = t_cor * t_cor * t_cor * y3_cor;
     Rd(299) = t_cor * t_cor * t_cor * b3_cor;
     Rd(300) = t_cor * t_cor * t_cor * x0_cor;
     Rd(301) = t_cor * t_cor * t_cor * x2_cor;
     Rd(302) = t_cor * t_cor * t_cor * a2_cor;
     Rd(303) = t_cor * t_cor * t_cor * y2_cor;
     Rd(304) = t_cor * t_cor * t_cor * b2_cor;
 
     Rd(305) = x3_cor * x3_cor * x3_cor * t_cor;
     Rd(306) = x3_cor * x3_cor * x3_cor * a3_cor;
     Rd(307) = x3_cor * x3_cor * x3_cor * y3_cor;
     Rd(308) = x3_cor * x3_cor * x3_cor * b3_cor;
     Rd(309) = x3_cor * x3_cor * x3_cor * x0_cor;
     Rd(310) = x3_cor * x3_cor * x3_cor * x2_cor;
     Rd(311) = x3_cor * x3_cor * x3_cor * a2_cor;
     Rd(312) = x3_cor * x3_cor * x3_cor * y2_cor;
     Rd(313) = x3_cor * x3_cor * x3_cor * b2_cor;
 
     Rd(314) = a3_cor * a3_cor * a3_cor * t_cor;
     Rd(315) = a3_cor * a3_cor * a3_cor * x3_cor;
     Rd(316) = a3_cor * a3_cor * a3_cor * y3_cor;
     Rd(317) = a3_cor * a3_cor * a3_cor * b3_cor;
     Rd(318) = a3_cor * a3_cor * a3_cor * x0_cor;
     Rd(319) = a3_cor * a3_cor * a3_cor * x2_cor;
     Rd(320) = a3_cor * a3_cor * a3_cor * a2_cor;
     Rd(321) = a3_cor * a3_cor * a3_cor * y2_cor;
     Rd(322) = a3_cor * a3_cor * a3_cor * b2_cor;
 
     Rd(323) = y3_cor * y3_cor * y3_cor * t_cor;
     Rd(324) = y3_cor * y3_cor * y3_cor * x3_cor;
     Rd(325) = y3_cor * y3_cor * y3_cor * a3_cor;
     Rd(326) = y3_cor * y3_cor * y3_cor * b3_cor;
     Rd(327) = y3_cor * y3_cor * y3_cor * x0_cor;
     Rd(328) = y3_cor * y3_cor * y3_cor * x2_cor;
     Rd(329) = y3_cor * y3_cor * y3_cor * a2_cor;
     Rd(330) = y3_cor * y3_cor * y3_cor * y2_cor;
     Rd(331) = y3_cor * y3_cor * y3_cor * b2_cor;
 
     Rd(332) = b3_cor * b3_cor * b3_cor * t_cor;
     Rd(333) = b3_cor * b3_cor * b3_cor * x3_cor;
     Rd(334) = b3_cor * b3_cor * b3_cor * a3_cor;
     Rd(335) = b3_cor * b3_cor * b3_cor * y3_cor;
     Rd(336) = b3_cor * b3_cor * b3_cor * x0_cor;
     Rd(337) = b3_cor * b3_cor * b3_cor * x2_cor;
     Rd(338) = b3_cor * b3_cor * b3_cor * a2_cor;
     Rd(339) = b3_cor * b3_cor * b3_cor * y2_cor;
     Rd(340) = b3_cor * b3_cor * b3_cor * b2_cor;
 
     Rd(341) = x0_cor * x0_cor * x0_cor * t_cor;
     Rd(342) = x0_cor * x0_cor * x0_cor * x3_cor;
     Rd(343) = x0_cor * x0_cor * x0_cor * a3_cor;
     Rd(344) = x0_cor * x0_cor * x0_cor * y3_cor;
     Rd(345) = x0_cor * x0_cor * x0_cor * b3_cor;
     Rd(346) = x0_cor * x0_cor * x0_cor * x2_cor;
     Rd(347) = x0_cor * x0_cor * x0_cor * a2_cor;
     Rd(348) = x0_cor * x0_cor * x0_cor * y2_cor;
     Rd(349) = x0_cor * x0_cor * x0_cor * b2_cor;
 
     Rd(350) = x2_cor * x2_cor * x2_cor * t_cor;
     Rd(351) = x2_cor * x2_cor * x2_cor * x3_cor;
     Rd(352) = x2_cor * x2_cor * x2_cor * a3_cor;
     Rd(353) = x2_cor * x2_cor * x2_cor * y3_cor;
     Rd(354) = x2_cor * x2_cor * x2_cor * b3_cor;
     Rd(355) = x2_cor * x2_cor * x2_cor * x0_cor;
     Rd(356) = x2_cor * x2_cor * x2_cor * a2_cor;
     Rd(357) = x2_cor * x2_cor * x2_cor * y2_cor;
     Rd(358) = x2_cor * x2_cor * x2_cor * b2_cor;
 
     Rd(359) = a2_cor * a2_cor * a2_cor * t_cor;
     Rd(360) = a2_cor * a2_cor * a2_cor * x3_cor;
     Rd(361) = a2_cor * a2_cor * a2_cor * a3_cor;
     Rd(362) = a2_cor * a2_cor * a2_cor * y3_cor;
     Rd(363) = a2_cor * a2_cor * a2_cor * b3_cor;
     Rd(364) = a2_cor * a2_cor * a2_cor * x0_cor;
     Rd(365) = a2_cor * a2_cor * a2_cor * x2_cor;
     Rd(366) = a2_cor * a2_cor * a2_cor * y2_cor;
     Rd(367) = a2_cor * a2_cor * a2_cor * b2_cor;
 
     Rd(368) = y2_cor * y2_cor * y2_cor * t_cor;
     Rd(369) = y2_cor * y2_cor * y2_cor * x3_cor;
     Rd(370) = y2_cor * y2_cor * y2_cor * a3_cor;
     Rd(371) = y2_cor * y2_cor * y2_cor * y3_cor;
     Rd(372) = y2_cor * y2_cor * y2_cor * b3_cor;
     Rd(373) = y2_cor * y2_cor * y2_cor * x0_cor;
     Rd(374) = y2_cor * y2_cor * y2_cor * x2_cor;
     Rd(375) = y2_cor * y2_cor * y2_cor * a2_cor;
     Rd(376) = y2_cor * y2_cor * y2_cor * b2_cor;
 
     Rd(377) = b2_cor * b2_cor * b2_cor * t_cor;
     Rd(378) = b2_cor * b2_cor * b2_cor * x3_cor;
     Rd(379) = b2_cor * b2_cor * b2_cor * a3_cor;
     Rd(380) = b2_cor * b2_cor * b2_cor * y3_cor;
     Rd(381) = b2_cor * b2_cor * b2_cor * b3_cor;
     Rd(382) = b2_cor * b2_cor * b2_cor * x0_cor;
     Rd(383) = b2_cor * b2_cor * b2_cor * x2_cor;
     Rd(384) = b2_cor * b2_cor * b2_cor * a2_cor;
     Rd(385) = b2_cor * b2_cor * b2_cor * y2_cor;
 
     Rd(386) = t_cor * t_cor * x3_cor * x3_cor;
     Rd(387) = t_cor * t_cor * a3_cor * a3_cor;
     Rd(388) = t_cor * t_cor * y3_cor * y3_cor;
     Rd(389) = t_cor * t_cor * b3_cor * b3_cor;
     Rd(390) = t_cor * t_cor * x0_cor * x0_cor;
     Rd(391) = t_cor * t_cor * x2_cor * x2_cor;
     Rd(392) = t_cor * t_cor * a2_cor * a2_cor;
     Rd(393) = t_cor * t_cor * y2_cor * y2_cor;
     Rd(394) = t_cor * t_cor * b2_cor * b2_cor;
 
     Rd(395) = x3_cor * x3_cor * a3_cor * a3_cor;
     Rd(396) = x3_cor * x3_cor * y3_cor * y3_cor;
     Rd(397) = x3_cor * x3_cor * b3_cor * b3_cor;
     Rd(398) = x3_cor * x3_cor * x0_cor * x0_cor;
     Rd(399) = x3_cor * x3_cor * x2_cor * x2_cor;
     Rd(400) = x3_cor * x3_cor * a2_cor * a2_cor;
     Rd(401) = x3_cor * x3_cor * y2_cor * y2_cor;
     Rd(402) = x3_cor * x3_cor * b2_cor * b2_cor;
 
     Rd(403) = a3_cor * a3_cor * y3_cor * y3_cor;
     Rd(404) = a3_cor * a3_cor * b3_cor * b3_cor;
     Rd(405) = a3_cor * a3_cor * x0_cor * x0_cor;
     Rd(406) = a3_cor * a3_cor * x2_cor * x2_cor;
     Rd(407) = a3_cor * a3_cor * a2_cor * a2_cor;
     Rd(408) = a3_cor * a3_cor * y2_cor * y2_cor;
     Rd(409) = a3_cor * a3_cor * b2_cor * b2_cor;
 
     Rd(410) = y3_cor * y3_cor * b3_cor * b3_cor;
     Rd(411) = y3_cor * y3_cor * x0_cor * x0_cor;
     Rd(412) = y3_cor * y3_cor * x2_cor * x2_cor;
     Rd(413) = y3_cor * y3_cor * a2_cor * a2_cor;
     Rd(414) = y3_cor * y3_cor * y2_cor * y2_cor;
     Rd(415) = y3_cor * y3_cor * b2_cor * b2_cor;
 
     Rd(416) = b3_cor * b3_cor * x0_cor * x0_cor;
     Rd(417) = b3_cor * b3_cor * x2_cor * x2_cor;
     Rd(418) = b3_cor * b3_cor * a2_cor * a2_cor;
     Rd(419) = b3_cor * b3_cor * y2_cor * y2_cor;
     Rd(420) = b3_cor * b3_cor * b2_cor * b2_cor;
 
     Rd(421) = x0_cor * x0_cor * x2_cor * x2_cor;
     Rd(422) = x0_cor * x0_cor * a2_cor * a2_cor;
     Rd(423) = x0_cor * x0_cor * y2_cor * y2_cor;
     Rd(424) = x0_cor * x0_cor * b2_cor * b2_cor;
 
     Rd(425) = x2_cor * x2_cor * a2_cor * a2_cor;
     Rd(426) = x2_cor * x2_cor * y2_cor * y2_cor;
     Rd(427) = x2_cor * x2_cor * b2_cor * b2_cor;
 
     Rd(428) = a2_cor * a2_cor * y2_cor * y2_cor;
     Rd(429) = a2_cor * a2_cor * b2_cor * b2_cor;
 
     Rd(430) = y2_cor * y2_cor * b2_cor * b2_cor;
 
     Rd(431) = t_cor * t_cor * x3_cor * a3_cor;
     Rd(432) = t_cor * t_cor * x3_cor * y3_cor;
     Rd(433) = t_cor * t_cor * x3_cor * b3_cor;
     Rd(434) = t_cor * t_cor * x3_cor * x0_cor;
     Rd(435) = t_cor * t_cor * x3_cor * x2_cor;
     Rd(436) = t_cor * t_cor * x3_cor * a2_cor;
     Rd(437) = t_cor * t_cor * x3_cor * y2_cor;
     Rd(438) = t_cor * t_cor * x3_cor * b2_cor;
 
     Rd(439) = t_cor * t_cor * a3_cor * y3_cor;
     Rd(440) = t_cor * t_cor * a3_cor * b3_cor;
     Rd(441) = t_cor * t_cor * a3_cor * x0_cor;
     Rd(442) = t_cor * t_cor * a3_cor * x2_cor;
     Rd(443) = t_cor * t_cor * a3_cor * a2_cor;
     Rd(444) = t_cor * t_cor * a3_cor * y2_cor;
     Rd(445) = t_cor * t_cor * a3_cor * b2_cor;
 
     Rd(446) = t_cor * t_cor * y3_cor * b3_cor;
     Rd(447) = t_cor * t_cor * y3_cor * x0_cor;
     Rd(448) = t_cor * t_cor * y3_cor * x2_cor;
     Rd(449) = t_cor * t_cor * y3_cor * a2_cor;
     Rd(450) = t_cor * t_cor * y3_cor * y2_cor;
     Rd(451) = t_cor * t_cor * y3_cor * b2_cor;
 
     Rd(452) = t_cor * t_cor * b3_cor * x0_cor;
     Rd(453) = t_cor * t_cor * b3_cor * x2_cor;
     Rd(454) = t_cor * t_cor * b3_cor * a2_cor;
     Rd(455) = t_cor * t_cor * b3_cor * y2_cor;
     Rd(456) = t_cor * t_cor * b3_cor * b2_cor;
 
     Rd(457) = t_cor * t_cor * x0_cor * x2_cor;
     Rd(458) = t_cor * t_cor * x0_cor * a2_cor;
     Rd(459) = t_cor * t_cor * x0_cor * y2_cor;
     Rd(460) = t_cor * t_cor * x0_cor * b2_cor;
 
     Rd(461) = t_cor * t_cor * x2_cor * a2_cor;
     Rd(462) = t_cor * t_cor * x2_cor * y2_cor;
     Rd(463) = t_cor * t_cor * x2_cor * b2_cor;
 
     Rd(464) = t_cor * t_cor * a2_cor * y2_cor;
     Rd(465) = t_cor * t_cor * a2_cor * b2_cor;
 
     Rd(466) = t_cor * t_cor * y2_cor * b2_cor;
 
     Rd(467) = x3_cor * x3_cor * t_cor * a3_cor;
     Rd(468) = x3_cor * x3_cor * t_cor * y3_cor;
     Rd(469) = x3_cor * x3_cor * t_cor * b3_cor;
     Rd(470) = x3_cor * x3_cor * t_cor * x0_cor;
     Rd(471) = x3_cor * x3_cor * t_cor * x2_cor;
     Rd(472) = x3_cor * x3_cor * t_cor * a2_cor;
     Rd(473) = x3_cor * x3_cor * t_cor * y2_cor;
     Rd(474) = x3_cor * x3_cor * t_cor * b2_cor;
 
     Rd(475) = x3_cor * x3_cor * a3_cor * y3_cor;
     Rd(476) = x3_cor * x3_cor * a3_cor * b3_cor;
     Rd(477) = x3_cor * x3_cor * a3_cor * x0_cor;
     Rd(478) = x3_cor * x3_cor * a3_cor * x2_cor;
     Rd(479) = x3_cor * x3_cor * a3_cor * a2_cor;
     Rd(480) = x3_cor * x3_cor * a3_cor * y2_cor;
     Rd(481) = x3_cor * x3_cor * a3_cor * b2_cor;
 
     Rd(482) = x3_cor * x3_cor * y3_cor * b3_cor;
     Rd(483) = x3_cor * x3_cor * y3_cor * x0_cor;
     Rd(484) = x3_cor * x3_cor * y3_cor * x2_cor;
     Rd(485) = x3_cor * x3_cor * y3_cor * a2_cor;
     Rd(486) = x3_cor * x3_cor * y3_cor * y2_cor;
     Rd(487) = x3_cor * x3_cor * y3_cor * b2_cor;
 
     Rd(488) = x3_cor * x3_cor * b3_cor * x0_cor;
     Rd(489) = x3_cor * x3_cor * b3_cor * x2_cor;
     Rd(490) = x3_cor * x3_cor * b3_cor * a2_cor;
     Rd(491) = x3_cor * x3_cor * b3_cor * y2_cor;
     Rd(492) = x3_cor * x3_cor * b3_cor * b2_cor;
 
     Rd(493) = x3_cor * x3_cor * x0_cor * x2_cor;
     Rd(494) = x3_cor * x3_cor * x0_cor * a2_cor;
     Rd(495) = x3_cor * x3_cor * x0_cor * y2_cor;
     Rd(496) = x3_cor * x3_cor * x0_cor * b2_cor;
 
     Rd(497) = x3_cor * x3_cor * x2_cor * a2_cor;
     Rd(498) = x3_cor * x3_cor * x2_cor * y2_cor;
     Rd(499) = x3_cor * x3_cor * x2_cor * b2_cor;
 
     Rd(500) = x3_cor * x3_cor * a2_cor * y2_cor;
     Rd(501) = x3_cor * x3_cor * a2_cor * b2_cor;
 
     Rd(502) = x3_cor * x3_cor * y2_cor * b2_cor;
 
 
     Rd(503) = a3_cor * a3_cor * t_cor * x3_cor;
     Rd(504) = a3_cor * a3_cor * t_cor * y3_cor;
     Rd(505) = a3_cor * a3_cor * t_cor * b3_cor;
     Rd(506) = a3_cor * a3_cor * t_cor * x0_cor;
     Rd(507) = a3_cor * a3_cor * t_cor * x2_cor;
     Rd(508) = a3_cor * a3_cor * t_cor * a2_cor;
     Rd(509) = a3_cor * a3_cor * t_cor * y2_cor;
     Rd(510) = a3_cor * a3_cor * t_cor * b2_cor;
 
     Rd(511) = a3_cor * a3_cor * x3_cor * y3_cor;
     Rd(512) = a3_cor * a3_cor * x3_cor * b3_cor;
     Rd(513) = a3_cor * a3_cor * x3_cor * x0_cor;
     Rd(514) = a3_cor * a3_cor * x3_cor * x2_cor;
     Rd(515) = a3_cor * a3_cor * x3_cor * a2_cor;
     Rd(516) = a3_cor * a3_cor * x3_cor * y2_cor;
     Rd(517) = a3_cor * a3_cor * x3_cor * b2_cor;
 
     Rd(518) = a3_cor * a3_cor * y3_cor * b3_cor;
     Rd(519) = a3_cor * a3_cor * y3_cor * x0_cor;
     Rd(520) = a3_cor * a3_cor * y3_cor * x2_cor;
     Rd(521) = a3_cor * a3_cor * y3_cor * a2_cor;
     Rd(522) = a3_cor * a3_cor * y3_cor * y2_cor;
     Rd(523) = a3_cor * a3_cor * y3_cor * b2_cor;
 
     Rd(524) = a3_cor * a3_cor * b3_cor * x0_cor;
     Rd(525) = a3_cor * a3_cor * b3_cor * x2_cor;
     Rd(526) = a3_cor * a3_cor * b3_cor * a2_cor;
     Rd(527) = a3_cor * a3_cor * b3_cor * y2_cor;
     Rd(528) = a3_cor * a3_cor * b3_cor * b2_cor;
 
     Rd(529) = a3_cor * a3_cor * x0_cor * x2_cor;
     Rd(530) = a3_cor * a3_cor * x0_cor * a2_cor;
     Rd(531) = a3_cor * a3_cor * x0_cor * y2_cor;
     Rd(532) = a3_cor * a3_cor * x0_cor * b2_cor;
 
     Rd(533) = a3_cor * a3_cor * x2_cor * a2_cor;
     Rd(534) = a3_cor * a3_cor * x2_cor * y2_cor;
     Rd(535) = a3_cor * a3_cor * x2_cor * b2_cor;
 
     Rd(536) = a3_cor * a3_cor * a2_cor * y2_cor;
     Rd(537) = a3_cor * a3_cor * a2_cor * b2_cor;
 
     Rd(538) = a3_cor * a3_cor * y2_cor * b2_cor;
 
     Rd(539) = y3_cor * y3_cor * t_cor * x3_cor;
     Rd(540) = y3_cor * y3_cor * t_cor * a3_cor;
     Rd(541) = y3_cor * y3_cor * t_cor * b3_cor;
     Rd(542) = y3_cor * y3_cor * t_cor * x0_cor;
     Rd(543) = y3_cor * y3_cor * t_cor * x2_cor;
     Rd(544) = y3_cor * y3_cor * t_cor * a2_cor;
     Rd(545) = y3_cor * y3_cor * t_cor * y2_cor;
     Rd(546) = y3_cor * y3_cor * t_cor * b2_cor;
 
     Rd(547) = y3_cor * y3_cor * x3_cor * a3_cor;
     Rd(548) = y3_cor * y3_cor * x3_cor * b3_cor;
     Rd(549) = y3_cor * y3_cor * x3_cor * x0_cor;
     Rd(550) = y3_cor * y3_cor * x3_cor * x2_cor;
     Rd(551) = y3_cor * y3_cor * x3_cor * a2_cor;
     Rd(552) = y3_cor * y3_cor * x3_cor * y2_cor;
     Rd(553) = y3_cor * y3_cor * x3_cor * b2_cor;
 
     Rd(554) = y3_cor * y3_cor * a3_cor * b3_cor;
     Rd(555) = y3_cor * y3_cor * a3_cor * x0_cor;
     Rd(556) = y3_cor * y3_cor * a3_cor * x2_cor;
     Rd(557) = y3_cor * y3_cor * a3_cor * a2_cor;
     Rd(558) = y3_cor * y3_cor * a3_cor * y2_cor;
     Rd(559) = y3_cor * y3_cor * a3_cor * b2_cor;
 
     Rd(560) = y3_cor * y3_cor * b3_cor * x0_cor;
     Rd(561) = y3_cor * y3_cor * b3_cor * x2_cor;
     Rd(562) = y3_cor * y3_cor * b3_cor * a2_cor;
     Rd(563) = y3_cor * y3_cor * b3_cor * y2_cor;
     Rd(564) = y3_cor * y3_cor * b3_cor * b2_cor;
 
     Rd(565) = y3_cor * y3_cor * x0_cor * x2_cor;
     Rd(566) = y3_cor * y3_cor * x0_cor * a2_cor;
     Rd(567) = y3_cor * y3_cor * x0_cor * y2_cor;
     Rd(568) = y3_cor * y3_cor * x0_cor * b2_cor;
 
     Rd(569) = y3_cor * y3_cor * x2_cor * a2_cor;
     Rd(570) = y3_cor * y3_cor * x2_cor * y2_cor;
     Rd(571) = y3_cor * y3_cor * x2_cor * b2_cor;
 
     Rd(572) = y3_cor * y3_cor * a2_cor * y2_cor;
     Rd(573) = y3_cor * y3_cor * a2_cor * b2_cor;
 
     Rd(574) = y3_cor * y3_cor * y2_cor * b2_cor;
 
     Rd(575) = b3_cor * b3_cor * t_cor * x3_cor;
     Rd(576) = b3_cor * b3_cor * t_cor * a3_cor;
     Rd(577) = b3_cor * b3_cor * t_cor * y3_cor;
     Rd(578) = b3_cor * b3_cor * t_cor * x0_cor;
     Rd(579) = b3_cor * b3_cor * t_cor * x2_cor;
     Rd(580) = b3_cor * b3_cor * t_cor * a2_cor;
     Rd(581) = b3_cor * b3_cor * t_cor * y2_cor;
     Rd(582) = b3_cor * b3_cor * t_cor * b2_cor;
 
     Rd(583) = b3_cor * b3_cor * x3_cor * a3_cor;
     Rd(584) = b3_cor * b3_cor * x3_cor * y3_cor;
     Rd(585) = b3_cor * b3_cor * x3_cor * x0_cor;
     Rd(586) = b3_cor * b3_cor * x3_cor * x2_cor;
     Rd(587) = b3_cor * b3_cor * x3_cor * a2_cor;
     Rd(588) = b3_cor * b3_cor * x3_cor * y2_cor;
     Rd(589) = b3_cor * b3_cor * x3_cor * b2_cor;
 
     Rd(590) = b3_cor * b3_cor * a3_cor * y3_cor;
     Rd(591) = b3_cor * b3_cor * a3_cor * x0_cor;
     Rd(592) = b3_cor * b3_cor * a3_cor * x2_cor;
     Rd(593) = b3_cor * b3_cor * a3_cor * a2_cor;
     Rd(594) = b3_cor * b3_cor * a3_cor * y2_cor;
     Rd(595) = b3_cor * b3_cor * a3_cor * b2_cor;
 
     Rd(596) = b3_cor * b3_cor * y3_cor * x0_cor;
     Rd(597) = b3_cor * b3_cor * y3_cor * x2_cor;
     Rd(598) = b3_cor * b3_cor * y3_cor * a2_cor;
     Rd(599) = b3_cor * b3_cor * y3_cor * y2_cor;
     Rd(600) = b3_cor * b3_cor * y3_cor * b2_cor;
 
     Rd(601) = b3_cor * b3_cor * x0_cor * x2_cor;
     Rd(602) = b3_cor * b3_cor * x0_cor * a2_cor;
     Rd(603) = b3_cor * b3_cor * x0_cor * y2_cor;
     Rd(604) = b3_cor * b3_cor * x0_cor * b2_cor;
 
     Rd(605) = b3_cor * b3_cor * x2_cor * a2_cor;
     Rd(606) = b3_cor * b3_cor * x2_cor * y2_cor;
     Rd(607) = b3_cor * b3_cor * x2_cor * b2_cor;
 
     Rd(608) = b3_cor * b3_cor * a2_cor * y2_cor;
     Rd(609) = b3_cor * b3_cor * a2_cor * b2_cor;
 
     Rd(610) = b3_cor * b3_cor * y2_cor * b2_cor;
 
     Rd(611) = x0_cor * x0_cor * t_cor * x3_cor;
     Rd(612) = x0_cor * x0_cor * t_cor * a3_cor;
     Rd(613) = x0_cor * x0_cor * t_cor * y3_cor;
     Rd(614) = x0_cor * x0_cor * t_cor * b3_cor;
     Rd(615) = x0_cor * x0_cor * t_cor * x2_cor;
     Rd(616) = x0_cor * x0_cor * t_cor * a2_cor;
     Rd(617) = x0_cor * x0_cor * t_cor * y2_cor;
     Rd(618) = x0_cor * x0_cor * t_cor * b2_cor;
 
     Rd(619) = x0_cor * x0_cor * x3_cor * a3_cor;
     Rd(620) = x0_cor * x0_cor * x3_cor * y3_cor;
     Rd(621) = x0_cor * x0_cor * x3_cor * b3_cor;
     Rd(622) = x0_cor * x0_cor * x3_cor * x2_cor;
     Rd(623) = x0_cor * x0_cor * x3_cor * a2_cor;
     Rd(624) = x0_cor * x0_cor * x3_cor * y2_cor;
     Rd(625) = x0_cor * x0_cor * x3_cor * b2_cor;
 
     Rd(626) = x0_cor * x0_cor * a3_cor * y3_cor;
     Rd(627) = x0_cor * x0_cor * a3_cor * b3_cor;
     Rd(628) = x0_cor * x0_cor * a3_cor * x2_cor;
     Rd(629) = x0_cor * x0_cor * a3_cor * a2_cor;
     Rd(630) = x0_cor * x0_cor * a3_cor * y2_cor;
     Rd(631) = x0_cor * x0_cor * a3_cor * b2_cor;
 
     Rd(632) = x0_cor * x0_cor * y3_cor * b3_cor;
     Rd(633) = x0_cor * x0_cor * y3_cor * x2_cor;
     Rd(634) = x0_cor * x0_cor * y3_cor * a2_cor;
     Rd(635) = x0_cor * x0_cor * y3_cor * y2_cor;
     Rd(636) = x0_cor * x0_cor * y3_cor * b2_cor;
 
     Rd(637) = x0_cor * x0_cor * b3_cor * x2_cor;
     Rd(638) = x0_cor * x0_cor * b3_cor * a2_cor;
     Rd(639) = x0_cor * x0_cor * b3_cor * y2_cor;
     Rd(640) = x0_cor * x0_cor * b3_cor * b2_cor;
 
     Rd(641) = x0_cor * x0_cor * x2_cor * a2_cor;
     Rd(642) = x0_cor * x0_cor * x2_cor * y2_cor;
     Rd(643) = x0_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(644) = x0_cor * x0_cor * a2_cor * y2_cor;
     Rd(645) = x0_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(646) = x0_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(647) = x2_cor * x2_cor * t_cor * x3_cor;
     Rd(648) = x2_cor * x2_cor * t_cor * a3_cor;
     Rd(649) = x2_cor * x2_cor * t_cor * y3_cor;
     Rd(650) = x2_cor * x2_cor * t_cor * b3_cor;
     Rd(651) = x2_cor * x2_cor * t_cor * x0_cor;
     Rd(652) = x2_cor * x2_cor * t_cor * a2_cor;
     Rd(653) = x2_cor * x2_cor * t_cor * y2_cor;
     Rd(654) = x2_cor * x2_cor * t_cor * b2_cor;
 
     Rd(655) = x2_cor * x2_cor * x3_cor * a3_cor;
     Rd(656) = x2_cor * x2_cor * x3_cor * y3_cor;
     Rd(657) = x2_cor * x2_cor * x3_cor * b3_cor;
     Rd(658) = x2_cor * x2_cor * x3_cor * x0_cor;
     Rd(659) = x2_cor * x2_cor * x3_cor * a2_cor;
     Rd(660) = x2_cor * x2_cor * x3_cor * y2_cor;
     Rd(661) = x2_cor * x2_cor * x3_cor * b2_cor;
 
     Rd(662) = x2_cor * x2_cor * a3_cor * y3_cor;
     Rd(663) = x2_cor * x2_cor * a3_cor * b3_cor;
     Rd(664) = x2_cor * x2_cor * a3_cor * x0_cor;
     Rd(665) = x2_cor * x2_cor * a3_cor * a2_cor;
     Rd(666) = x2_cor * x2_cor * a3_cor * y2_cor;
     Rd(667) = x2_cor * x2_cor * a3_cor * b2_cor;
 
     Rd(668) = x2_cor * x2_cor * y3_cor * b3_cor;
     Rd(669) = x2_cor * x2_cor * y3_cor * x0_cor;
     Rd(670) = x2_cor * x2_cor * y3_cor * a2_cor;
     Rd(671) = x2_cor * x2_cor * y3_cor * y2_cor;
     Rd(672) = x2_cor * x2_cor * y3_cor * b2_cor;
 
     Rd(673) = x2_cor * x2_cor * b3_cor * x0_cor;
     Rd(674) = x2_cor * x2_cor * b3_cor * a2_cor;
     Rd(675) = x2_cor * x2_cor * b3_cor * y2_cor;
     Rd(676) = x2_cor * x2_cor * b3_cor * b2_cor;
 
     Rd(677) = x2_cor * x2_cor * x0_cor * a2_cor;
     Rd(678) = x2_cor * x2_cor * x0_cor * y2_cor;
     Rd(679) = x2_cor * x2_cor * x0_cor * b2_cor;
 
     Rd(680) = x2_cor * x2_cor * a2_cor * y2_cor;
     Rd(681) = x2_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(682) = x2_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(683) = a2_cor * a2_cor * t_cor * x3_cor;
     Rd(684) = a2_cor * a2_cor * t_cor * a3_cor;
     Rd(685) = a2_cor * a2_cor * t_cor * y3_cor;
     Rd(686) = a2_cor * a2_cor * t_cor * b3_cor;
     Rd(687) = a2_cor * a2_cor * t_cor * x0_cor;
     Rd(688) = a2_cor * a2_cor * t_cor * x2_cor;
     Rd(689) = a2_cor * a2_cor * t_cor * y2_cor;
     Rd(691) = a2_cor * a2_cor * t_cor * b2_cor;
 
     Rd(692) = a2_cor * a2_cor * x3_cor * a3_cor;
     Rd(694) = a2_cor * a2_cor * x3_cor * y3_cor;
     Rd(695) = a2_cor * a2_cor * x3_cor * b3_cor;
     Rd(696) = a2_cor * a2_cor * x3_cor * x0_cor;
     Rd(697) = a2_cor * a2_cor * x3_cor * x2_cor;
     Rd(698) = a2_cor * a2_cor * x3_cor * y2_cor;
     Rd(699) = a2_cor * a2_cor * x3_cor * b2_cor;
 
     Rd(700) = a2_cor * a2_cor * a3_cor * y3_cor;
     Rd(701) = a2_cor * a2_cor * a3_cor * b3_cor;
     Rd(702) = a2_cor * a2_cor * a3_cor * x0_cor;
     Rd(703) = a2_cor * a2_cor * a3_cor * x2_cor;
     Rd(704) = a2_cor * a2_cor * a3_cor * y2_cor;
     Rd(705) = a2_cor * a2_cor * a3_cor * b2_cor;
 
     Rd(706) = a2_cor * a2_cor * y3_cor * b3_cor;
     Rd(707) = a2_cor * a2_cor * y3_cor * x0_cor;
     Rd(708) = a2_cor * a2_cor * y3_cor * x2_cor;
     Rd(709) = a2_cor * a2_cor * y3_cor * y2_cor;
     Rd(710) = a2_cor * a2_cor * y3_cor * b2_cor;
 
     Rd(712) = a2_cor * a2_cor * b3_cor * x0_cor;
     Rd(713) = a2_cor * a2_cor * b3_cor * x2_cor;
     Rd(714) = a2_cor * a2_cor * b3_cor * y2_cor;
     Rd(715) = a2_cor * a2_cor * b3_cor * b2_cor;
 
     Rd(716) = a2_cor * a2_cor * x0_cor * x2_cor;
     Rd(717) = a2_cor * a2_cor * x0_cor * y2_cor;
     Rd(718) = a2_cor * a2_cor * x0_cor * b2_cor;
 
     Rd(719) = a2_cor * a2_cor * x2_cor * y2_cor;
     Rd(720) = a2_cor * a2_cor * x2_cor * b2_cor;
 
     Rd(721) = a2_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(722) = y2_cor * y2_cor * t_cor * x3_cor;
     Rd(723) = y2_cor * y2_cor * t_cor * a3_cor;
     Rd(724) = y2_cor * y2_cor * t_cor * y3_cor;
     Rd(725) = y2_cor * y2_cor * t_cor * b3_cor;
     Rd(726) = y2_cor * y2_cor * t_cor * x0_cor;
     Rd(727) = y2_cor * y2_cor * t_cor * x2_cor;
     Rd(728) = y2_cor * y2_cor * t_cor * a2_cor;
     Rd(729) = y2_cor * y2_cor * t_cor * b2_cor;
 
     Rd(730) = y2_cor * y2_cor * x3_cor * a3_cor;
     Rd(731) = y2_cor * y2_cor * x3_cor * y3_cor;
     Rd(732) = y2_cor * y2_cor * x3_cor * b3_cor;
     Rd(733) = y2_cor * y2_cor * x3_cor * x0_cor;
     Rd(734) = y2_cor * y2_cor * x3_cor * x2_cor;
     Rd(735) = y2_cor * y2_cor * x3_cor * a2_cor;
     Rd(736) = y2_cor * y2_cor * x3_cor * b2_cor;
 
     Rd(737) = y2_cor * y2_cor * a3_cor * y3_cor;
     Rd(734) = y2_cor * y2_cor * a3_cor * b3_cor;
     Rd(735) = y2_cor * y2_cor * a3_cor * x0_cor;
     Rd(736) = y2_cor * y2_cor * a3_cor * x2_cor;
     Rd(737) = y2_cor * y2_cor * a3_cor * a2_cor;
     Rd(738) = y2_cor * y2_cor * a3_cor * b2_cor;
 
     Rd(739) = y2_cor * y2_cor * y3_cor * b3_cor;
     Rd(740) = y2_cor * y2_cor * y3_cor * x0_cor;
     Rd(741) = y2_cor * y2_cor * y3_cor * x2_cor;
     Rd(742) = y2_cor * y2_cor * y3_cor * a2_cor;
     Rd(743) = y2_cor * y2_cor * y3_cor * b2_cor;
 
     Rd(744) = y2_cor * y2_cor * b3_cor * x0_cor;
     Rd(745) = y2_cor * y2_cor * b3_cor * x2_cor;
     Rd(746) = y2_cor * y2_cor * b3_cor * a2_cor;
     Rd(747) = y2_cor * y2_cor * b3_cor * b2_cor;
 
     Rd(748) = y2_cor * y2_cor * x0_cor * x2_cor;
     Rd(749) = y2_cor * y2_cor * x0_cor * a2_cor;
     Rd(750) = y2_cor * y2_cor * x0_cor * b2_cor;
 
     Rd(751) = y2_cor * y2_cor * x2_cor * a2_cor;
     Rd(752) = y2_cor * y2_cor * x2_cor * b2_cor;
 
     Rd(753) = y2_cor * y2_cor * a2_cor * b2_cor;
 
     Rd(754) = b2_cor * b2_cor * t_cor * x3_cor;
     Rd(755) = b2_cor * b2_cor * t_cor * a3_cor;
     Rd(756) = b2_cor * b2_cor * t_cor * y3_cor;
     Rd(757) = b2_cor * b2_cor * t_cor * b3_cor;
     Rd(758) = b2_cor * b2_cor * t_cor * x0_cor;
     Rd(759) = b2_cor * b2_cor * t_cor * x2_cor;
     Rd(760) = b2_cor * b2_cor * t_cor * a2_cor;
     Rd(761) = b2_cor * b2_cor * t_cor * y2_cor;
 
     Rd(762) = b2_cor * b2_cor * x3_cor * a3_cor;
     Rd(763) = b2_cor * b2_cor * x3_cor * y3_cor;
     Rd(764) = b2_cor * b2_cor * x3_cor * b3_cor;
     Rd(765) = b2_cor * b2_cor * x3_cor * x0_cor;
     Rd(766) = b2_cor * b2_cor * x3_cor * x2_cor;
     Rd(767) = b2_cor * b2_cor * x3_cor * a2_cor;
     Rd(768) = b2_cor * b2_cor * x3_cor * y2_cor;
 
     Rd(769) = b2_cor * b2_cor * a3_cor * y3_cor;
     Rd(770) = b2_cor * b2_cor * a3_cor * b3_cor;
     Rd(771) = b2_cor * b2_cor * a3_cor * x0_cor;
     Rd(772) = b2_cor * b2_cor * a3_cor * x2_cor;
     Rd(773) = b2_cor * b2_cor * a3_cor * a2_cor;
     Rd(774) = b2_cor * b2_cor * a3_cor * y2_cor;
 
     Rd(775) = b2_cor * b2_cor * y3_cor * b3_cor;
     Rd(776) = b2_cor * b2_cor * y3_cor * x0_cor;
     Rd(778) = b2_cor * b2_cor * y3_cor * x2_cor;
     Rd(779) = b2_cor * b2_cor * y3_cor * a2_cor;
     Rd(780) = b2_cor * b2_cor * y3_cor * y2_cor;
 
     Rd(781) = b2_cor * b2_cor * b3_cor * x0_cor;
     Rd(782) = b2_cor * b2_cor * b3_cor * x2_cor;
     Rd(783) = b2_cor * b2_cor * b3_cor * a2_cor;
     Rd(784) = b2_cor * b2_cor * b3_cor * y2_cor;
 
     Rd(785) = b2_cor * b2_cor * x0_cor * x2_cor;
     Rd(786) = b2_cor * b2_cor * x0_cor * a2_cor;
     Rd(787) = b2_cor * b2_cor * x0_cor * y2_cor;
 
     Rd(788) = b2_cor * b2_cor * x2_cor * a2_cor;
     Rd(789) = b2_cor * b2_cor * x2_cor * y2_cor;
 
     Rd(790) = b2_cor * b2_cor * a2_cor * y2_cor;
 
     Rd(791) = t_cor * x3_cor * a3_cor * y3_cor;
     Rd(792) = t_cor * x3_cor * a3_cor * b3_cor;
     Rd(793) = t_cor * x3_cor * a3_cor * x0_cor;
     Rd(794) = t_cor * x3_cor * a3_cor * x2_cor;
     Rd(795) = t_cor * x3_cor * a3_cor * a2_cor;
     Rd(796) = t_cor * x3_cor * a3_cor * y2_cor;
     Rd(797) = t_cor * x3_cor * a3_cor * b2_cor;
 
     Rd(798) = t_cor * x3_cor * y3_cor * b3_cor;
     Rd(799) = t_cor * x3_cor * y3_cor * x0_cor;
     Rd(800) = t_cor * x3_cor * y3_cor * x2_cor;
     Rd(801) = t_cor * x3_cor * y3_cor * a2_cor;
     Rd(802) = t_cor * x3_cor * y3_cor * y2_cor;
     Rd(803) = t_cor * x3_cor * y3_cor * b2_cor;
 
     Rd(804) = t_cor * x3_cor * b3_cor * x0_cor;
     Rd(805) = t_cor * x3_cor * b3_cor * x2_cor;
     Rd(806) = t_cor * x3_cor * b3_cor * a2_cor;
     Rd(807) = t_cor * x3_cor * b3_cor * y2_cor;
     Rd(808) = t_cor * x3_cor * b3_cor * b2_cor;
 
     Rd(809) = t_cor * x3_cor * x0_cor * x2_cor;
     Rd(810) = t_cor * x3_cor * x0_cor * a2_cor;
     Rd(811) = t_cor * x3_cor * x0_cor * y2_cor;
     Rd(812) = t_cor * x3_cor * x0_cor * b2_cor;
 
     Rd(813) = t_cor * x3_cor * x2_cor * a2_cor;
     Rd(814) = t_cor * x3_cor * x2_cor * y2_cor;
     Rd(815) = t_cor * x3_cor * x2_cor * b2_cor;
     Rd(816) = t_cor * x3_cor * a2_cor * y2_cor;
     Rd(817) = t_cor * x3_cor * a2_cor * b2_cor;
 
     Rd(818) = t_cor * x3_cor * y2_cor * b2_cor;
 
     Rd(819) = t_cor * a3_cor * y3_cor * b3_cor;
     Rd(820) = t_cor * a3_cor * y3_cor * x0_cor;
     Rd(821) = t_cor * a3_cor * y3_cor * x2_cor;
     Rd(822) = t_cor * a3_cor * y3_cor * a2_cor;
     Rd(823) = t_cor * a3_cor * y3_cor * y2_cor;
     Rd(824) = t_cor * a3_cor * y3_cor * b2_cor;
 
     Rd(825) = t_cor * a3_cor * b3_cor * x0_cor;
     Rd(826) = t_cor * a3_cor * b3_cor * x2_cor;
     Rd(827) = t_cor * a3_cor * b3_cor * a2_cor;
     Rd(828) = t_cor * a3_cor * b3_cor * y2_cor;
     Rd(829) = t_cor * a3_cor * b3_cor * b2_cor;
 
     Rd(830) = t_cor * a3_cor * x0_cor * x2_cor;
     Rd(831) = t_cor * a3_cor * x0_cor * a2_cor;
     Rd(832) = t_cor * a3_cor * x0_cor * y2_cor;
     Rd(833) = t_cor * a3_cor * x0_cor * b2_cor;
 
     Rd(834) = t_cor * a3_cor * x2_cor * a2_cor;
     Rd(835) = t_cor * a3_cor * x2_cor * y2_cor;
     Rd(836) = t_cor * a3_cor * x2_cor * b2_cor;
 
     Rd(837) = t_cor * a3_cor * a2_cor * y2_cor;
     Rd(838) = t_cor * a3_cor * a2_cor * b2_cor;
 
     Rd(839) = t_cor * a3_cor * y2_cor * b2_cor;
 
     Rd(840) = t_cor * y3_cor * b3_cor * x0_cor;
     Rd(841) = t_cor * y3_cor * b3_cor * x2_cor;
     Rd(842) = t_cor * y3_cor * b3_cor * a2_cor;
     Rd(843) = t_cor * y3_cor * b3_cor * y2_cor;
     Rd(844) = t_cor * y3_cor * b3_cor * b2_cor;
 
     Rd(845) = t_cor * y3_cor * x0_cor * x2_cor;
     Rd(846) = t_cor * y3_cor * x0_cor * a2_cor;
     Rd(847) = t_cor * y3_cor * x0_cor * y2_cor;
     Rd(848) = t_cor * y3_cor * x0_cor * b2_cor;
 
     Rd(849) = t_cor * y3_cor * x2_cor * a2_cor;
     Rd(850) = t_cor * y3_cor * x2_cor * y2_cor;
     Rd(851) = t_cor * y3_cor * x2_cor * b2_cor;
 
     Rd(852) = t_cor * y3_cor * a2_cor * y2_cor;
     Rd(853) = t_cor * y3_cor * a2_cor * b2_cor;
 
     Rd(854) = t_cor * y3_cor * y2_cor * b2_cor;
 
     Rd(855) = t_cor * b3_cor * x0_cor * x2_cor;
     Rd(856) = t_cor * b3_cor * x0_cor * a2_cor;
     Rd(857) = t_cor * b3_cor * x0_cor * y2_cor;
     Rd(858) = t_cor * b3_cor * x0_cor * b2_cor;
 
     Rd(859) = t_cor * b3_cor * x2_cor * a2_cor;
     Rd(860) = t_cor * b3_cor * x2_cor * y2_cor;
     Rd(861) = t_cor * b3_cor * x2_cor * b2_cor;
 
     Rd(862) = t_cor * b3_cor * a2_cor * y2_cor;
     Rd(863) = t_cor * b3_cor * a2_cor * b2_cor;
 
     Rd(864) = t_cor * b3_cor * y2_cor * b2_cor;
 
     Rd(865) = t_cor * x0_cor * x2_cor * a2_cor;
     Rd(866) = t_cor * x0_cor * x2_cor * y2_cor;
     Rd(867) = t_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(868) = t_cor * x0_cor * a2_cor * y2_cor;
     Rd(869) = t_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(870) = t_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(871) = t_cor * x2_cor * a2_cor * y2_cor;
     Rd(872) = t_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(873) = t_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(874) = t_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(875) = x3_cor * a3_cor * y3_cor * b3_cor;
     Rd(876) = x3_cor * a3_cor * y3_cor * x0_cor;
     Rd(877) = x3_cor * a3_cor * y3_cor * x2_cor;
     Rd(878) = x3_cor * a3_cor * y3_cor * a2_cor;
     Rd(879) = x3_cor * a3_cor * y3_cor * y2_cor;
     Rd(880) = x3_cor * a3_cor * y3_cor * b2_cor;
 
     Rd(881) = x3_cor * a3_cor * b3_cor * x0_cor;
     Rd(882) = x3_cor * a3_cor * b3_cor * x2_cor;
     Rd(883) = x3_cor * a3_cor * b3_cor * a2_cor;
     Rd(884) = x3_cor * a3_cor * b3_cor * y2_cor;
     Rd(885) = x3_cor * a3_cor * b3_cor * b2_cor;
 
     Rd(886) = x3_cor * a3_cor * x0_cor * x2_cor;
     Rd(887) = x3_cor * a3_cor * x0_cor * a2_cor;
     Rd(888) = x3_cor * a3_cor * x0_cor * y2_cor;
     Rd(889) = x3_cor * a3_cor * x0_cor * b2_cor;
 
     Rd(890) = x3_cor * a3_cor * x2_cor * a2_cor;
     Rd(891) = x3_cor * a3_cor * x2_cor * y2_cor;
     Rd(892) = x3_cor * a3_cor * x2_cor * b2_cor;
 
     Rd(893) = x3_cor * a3_cor * a2_cor * y2_cor;
     Rd(894) = x3_cor * a3_cor * a2_cor * b2_cor;
 
     Rd(895) = x3_cor * a3_cor * y2_cor * b2_cor;
 
     Rd(896) = x3_cor * y3_cor * b3_cor * x0_cor;
     Rd(897) = x3_cor * y3_cor * b3_cor * x2_cor;
     Rd(898) = x3_cor * y3_cor * b3_cor * a2_cor;
     Rd(899) = x3_cor * y3_cor * b3_cor * y2_cor;
     Rd(900) = x3_cor * y3_cor * b3_cor * b2_cor;
 
     Rd(901) = x3_cor * y3_cor * x0_cor * x2_cor;
     Rd(902) = x3_cor * y3_cor * x0_cor * a2_cor;
     Rd(903) = x3_cor * y3_cor * x0_cor * y2_cor;
     Rd(904) = x3_cor * y3_cor * x0_cor * b2_cor;
 
     Rd(905) = x3_cor * y3_cor * x2_cor * a2_cor;
     Rd(906) = x3_cor * y3_cor * x2_cor * y2_cor;
     Rd(907) = x3_cor * y3_cor * x2_cor * b2_cor;
 
     Rd(908) = x3_cor * y3_cor * a2_cor * y2_cor;
     Rd(909) = x3_cor * y3_cor * a2_cor * b2_cor;
 
     Rd(910) = x3_cor * y3_cor * y2_cor * b2_cor;
 
     Rd(911) = x3_cor * b3_cor * x0_cor * x2_cor;
     Rd(912) = x3_cor * b3_cor * x0_cor * a2_cor;
     Rd(913) = x3_cor * b3_cor * x0_cor * y2_cor;
     Rd(914) = x3_cor * b3_cor * x0_cor * b2_cor;
 
     Rd(915) = x3_cor * b3_cor * x2_cor * a2_cor;
     Rd(916) = x3_cor * b3_cor * x2_cor * y2_cor;
     Rd(917) = x3_cor * b3_cor * x2_cor * b2_cor;
 
     Rd(918) = x3_cor * b3_cor * a2_cor * y2_cor;
     Rd(919) = x3_cor * b3_cor * a2_cor * b2_cor;
 
     Rd(920) = x3_cor * b3_cor * y2_cor * b2_cor;
 
     Rd(921) = x3_cor * x0_cor * x2_cor * a2_cor;
     Rd(922) = x3_cor * x0_cor * x2_cor * y2_cor;
     Rd(923) = x3_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(924) = x3_cor * x0_cor * a2_cor * y2_cor;
     Rd(925) = x3_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(926) = x3_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(927) = x3_cor * x2_cor * a2_cor * y2_cor;
     Rd(928) = x3_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(929) = x3_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(930) = x3_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(931) = a3_cor * y3_cor * b3_cor * x0_cor;
     Rd(932) = a3_cor * y3_cor * b3_cor * x2_cor;
     Rd(933) = a3_cor * y3_cor * b3_cor * a2_cor;
     Rd(934) = a3_cor * y3_cor * b3_cor * y2_cor;
     Rd(935) = a3_cor * y3_cor * b3_cor * b2_cor;
 
     Rd(936) = a3_cor * y3_cor * x0_cor * x2_cor;
     Rd(937) = a3_cor * y3_cor * x0_cor * a2_cor;
     Rd(938) = a3_cor * y3_cor * x0_cor * y2_cor;
     Rd(939) = a3_cor * y3_cor * x0_cor * b2_cor;
 
     Rd(940) = a3_cor * y3_cor * x2_cor * a2_cor;
     Rd(941) = a3_cor * y3_cor * x2_cor * y2_cor;
     Rd(942) = a3_cor * y3_cor * x2_cor * b2_cor;
     Rd(943) = a3_cor * y3_cor * a2_cor * y2_cor;
     Rd(944) = a3_cor * y3_cor * a2_cor * b2_cor;
 
     Rd(945) = a3_cor * y3_cor * y2_cor * b2_cor;
 
     Rd(946) = a3_cor * b3_cor * x0_cor * x2_cor;
     Rd(947) = a3_cor * b3_cor * x0_cor * a2_cor;
     Rd(948) = a3_cor * b3_cor * x0_cor * y2_cor;
     Rd(949) = a3_cor * b3_cor * x0_cor * b2_cor;
 
     Rd(950) = a3_cor * b3_cor * x2_cor * a2_cor;
     Rd(951) = a3_cor * b3_cor * x2_cor * y2_cor;
     Rd(952) = a3_cor * b3_cor * x2_cor * b2_cor;
 
     Rd(953) = a3_cor * b3_cor * a2_cor * y2_cor;
     Rd(954) = a3_cor * b3_cor * a2_cor * b2_cor;
 
     Rd(955) = a3_cor * b3_cor * y2_cor * b2_cor;
 
     Rd(956) = a3_cor * x0_cor * x2_cor * a2_cor;
     Rd(957) = a3_cor * x0_cor * x2_cor * y2_cor;
     Rd(958) = a3_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(959) = a3_cor * x0_cor * a2_cor * y2_cor;
     Rd(960) = a3_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(961) = a3_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(962) = a3_cor * x2_cor * a2_cor * y2_cor;
     Rd(963) = a3_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(964) = a3_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(965) = a3_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(966) = y3_cor * b3_cor * x0_cor * x2_cor;
     Rd(967) = y3_cor * b3_cor * x0_cor * a2_cor;
     Rd(968) = y3_cor * b3_cor * x0_cor * y2_cor;
     Rd(969) = y3_cor * b3_cor * x0_cor * b2_cor;
 
     Rd(970) = y3_cor * b3_cor * x2_cor * a2_cor;
     Rd(971) = y3_cor * b3_cor * x2_cor * y2_cor;
     Rd(972) = y3_cor * b3_cor * x2_cor * b2_cor;
 
     Rd(973) = y3_cor * b3_cor * a2_cor * y2_cor;
     Rd(974) = y3_cor * b3_cor * a2_cor * b2_cor;
 
     Rd(975) = y3_cor * b3_cor * y2_cor * b2_cor;
 
     Rd(976) = y3_cor * x0_cor * x2_cor * a2_cor;
     Rd(977) = y3_cor * x0_cor * x2_cor * y2_cor;
     Rd(978) = y3_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(979) = y3_cor * x0_cor * a2_cor * y2_cor;
     Rd(980) = y3_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(981) = y3_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(982) = y3_cor * x2_cor * a2_cor * y2_cor;
     Rd(983) = y3_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(984) = y3_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(985) = y3_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(986) = b3_cor * x0_cor * x2_cor * a2_cor;
     Rd(987) = b3_cor * x0_cor * x2_cor * y2_cor;
     Rd(988) = b3_cor * x0_cor * x2_cor * b2_cor;
 
     Rd(989) = b3_cor * x0_cor * a2_cor * y2_cor;
     Rd(990) = b3_cor * x0_cor * a2_cor * b2_cor;
 
     Rd(991) = b3_cor * x0_cor * y2_cor * b2_cor;
 
     Rd(992) = b3_cor * x2_cor * a2_cor * y2_cor;
     Rd(993) = b3_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(994) = b3_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(995) = b3_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(996) = x0_cor * x2_cor * a2_cor * y2_cor;
     Rd(997) = x0_cor * x2_cor * a2_cor * b2_cor;
 
     Rd(998) = x0_cor * x2_cor * y2_cor * b2_cor;
 
     Rd(999) = x0_cor * a2_cor * y2_cor * b2_cor;
 
     Rd(1000) = x2_cor * a2_cor * y2_cor * b2_cor;
  
  for (int ii = 0; ii < Nprm; ii++){
   sum += Rd(ii) * Theta(ii);
  }
    
 	Aq_cor.push_back(sum);
    evt_valid.push_back(iData);

   }else{
	   continue;
   }
}

//// Check results for selected events

 TVectorD b_re(Nevt);
// b_re = Mult(A,Theta);

for(int ic = 0; ic < Nevt; ic++ ){

 Double_t b_re_elem = 0.;

	for(int ir = 0; ir < Nprm; ir++ ){

 	   b_re_elem += A(ic,ir) * Theta(ir);

	}

	b_re(ic) = b_re_elem;
}

 TH1D *h_aq_sol = new TH1D("aq_sol", "aq_sol",1000,1.7,2.3);

// TH1D *h_38Ca_sol = new TH1D("h38Ca_sol", "h38Ca_sol",1000,1.89,1.91);
 TH1D *h_39Ca_sol = new TH1D("h39Ca_sol", "h39Ca_sol",1000,1.940,1.960);
 TH1D *h_40Ca_sol = new TH1D("h40Ca_sol", "h40Ca_sol",1000,1.990,2.01);
 TH1D *h_41Ca_sol = new TH1D("h41Ca_sol", "h41Ca_sol",1000,2.040,2.060);
                                    
 TH1D *h_40Sc_sol = new TH1D("h40Sc_sol", "h40Sc_sol",1000,1.900,1.92);
 TH1D *h_41Sc_sol = new TH1D("h41Sc_sol", "h41Sc_sol",1000,1.945,1.965);
 TH1D *h_43Sc_sol = new TH1D("h43Sc_sol", "h43Sc_sol",1000,2.04,2.060);
                                
 TH1D *h_40Ti_sol = new TH1D("h40Ti_sol", "h40Ti_sol",1000,1.81,1.83);
 TH1D *h_41Ti_sol = new TH1D("h41Ti_sol", "h41Ti_sol",1000,1.86,1.88);
// TH1D *h_43Ti_sol = new TH1D("h43Ti_sol", "h43Ti_sol",1000,1.940,1.960);
// TH1D *h_47Ti_sol = new TH1D("h47Ti_sol", "h47Ti_sol",1000,2.125,2.145);
 TH1D *h_42Ti_sol = new TH1D("h42Ti_sol", "h42Ti_sol",1000,1.895,1.915);
                                         
 TH1D *h_43V_sol  = new TH1D("h43V_sol", "h43V_sol",1000,1.86,1.880);
 TH1D *h_44V_sol  = new TH1D("h44V_sol", "h44V_sol",1000,1.90,1.92);
// TH1D *h_45V_sol  = new TH1D("h45V_sol", "h45V_sol",1000,1.945,1.965);
// TH1D *h_47V_sol  = new TH1D("h47V_sol", "h47V_sol",1000,2.03,2.05);
 TH1D *h_46V_sol  = new TH1D("h46V_sol", "h46V_sol",1000,1.985,2.005);
                                    
 TH1D *h_44Cr_sol = new TH1D("h44Cr_sol", "h44Cr_sol",1000,1.83,1.85);
 TH1D *h_45Cr_sol = new TH1D("h45Cr_sol", "h45Cr_sol",1000,1.865,1.885);
 TH1D *h_46Cr_sol = new TH1D("h46Cr_sol", "h46Cr_sol",1000,1.90,1.925);
                                    
 TH1D *h_46Mn_sol = new TH1D("h46Mn_sol", "h46Mn_sol",1000,1.83,1.85);
 TH1D *h_47Mn_sol = new TH1D("h47Mn_sol", "h47Mn_sol",1000,1.87,1.897);
 TH1D *h_48Mn_sol = new TH1D("h48Mn_sol", "h48Mn_sol",1000,1.91,1.930);
                                    
 TH1D *h_48Fe_sol = new TH1D("h48Fe_sol", "h48Fe_sol",1000,1.835,1.855);
 TH1D *h_49Fe_sol = new TH1D("h49Fe_sol", "h49Fe_sol",1000,1.87,1.89);
 TH1D *h_50Fe_sol = new TH1D("h50Fe_sol", "h50Fe_sol",1000,1.91,1.930);

 Int_t Nrun_2  = 2 * Nrun;
 Int_t Nrun_3  = 3 * Nrun;
 Int_t Nrun_4  = 4 * Nrun;
 Int_t Nrun_5  = 5 * Nrun;
 Int_t Nrun_6  = 6 * Nrun;
 Int_t Nrun_7  = 7 * Nrun;
 Int_t Nrun_8  = 8 * Nrun;
 Int_t Nrun_9  = 9 * Nrun;
 Int_t Nrun_10 = 10 * Nrun;
 Int_t Nrun_11 = 11 * Nrun;
 Int_t Nrun_12 = 12 * Nrun;
 Int_t Nrun_13 = 13 * Nrun;
 Int_t Nrun_14 = 14 * Nrun;
 Int_t Nrun_15 = 15 * Nrun;
 Int_t Nrun_16 = 16 * Nrun;
 Int_t Nrun_17 = 17 * Nrun;
 Int_t Nrun_18 = 18 * Nrun;
 Int_t Nrun_19 = 19 * Nrun;
 Int_t Nrun_20 = 20 * Nrun;
 Int_t Nrun_21 = 21 * Nrun;

 for (int isol = 0; isol < Nevt; isol++){
  h_aq_sol->Fill(b_re[isol]);
	 
	if(0 <= isol && isol  < Nrun){
//	 h_38Ca_sol->Fill(b_re(isol));
	 h_39Ca_sol->Fill(b_re(isol));
 } else if(Nrun <= isol && isol  < Nrun_2){
//	 h_39Ca_sol->Fill(b_re(isol));
	 h_40Ca_sol->Fill(b_re(isol));
 } else if(Nrun_2 <= isol && isol  < Nrun_3){
	 h_41Ca_sol->Fill(b_re(isol));
 } else if(Nrun_3 <= isol && isol  < Nrun_4){
	 h_40Sc_sol->Fill(b_re(isol));
 } else if(Nrun_4 <= isol && isol  < Nrun_5){
	 h_41Sc_sol->Fill(b_re(isol));
 } else if(Nrun_5 <= isol && isol  < Nrun_6){
	 h_43Sc_sol->Fill(b_re(isol));
 } else if(Nrun_6 <= isol && isol  < Nrun_7){
	 h_40Ti_sol->Fill(b_re(isol));
 } else if(Nrun_7 <= isol && isol  < Nrun_8){
	 h_41Ti_sol->Fill(b_re(isol));
 } else if(Nrun_8 <= isol && isol  < Nrun_9){
	 h_42Ti_sol->Fill(b_re(isol));
//	 h_47Ti_sol->Fill(b_re(isol));
//	 h_43Ti_sol->Fill(b_re(isol));
 } else if(Nrun_9 <= isol && isol  < Nrun_10){
	 h_43V_sol->Fill(b_re(isol));
 } else if(Nrun_10 <= isol && isol  < Nrun_11){
	 h_44V_sol->Fill(b_re(isol));
 } else if(Nrun_11 <= isol && isol  < Nrun_12){
	 h_46V_sol->Fill(b_re(isol));
//	 h_47V_sol->Fill(b_re(isol));
//	 h_45V_sol->Fill(b_re(isol));
 } else if(Nrun_12 <= isol && isol  < Nrun_13){
	 h_44Cr_sol->Fill(b_re(isol));
 } else if(Nrun_13 <= isol && isol  < Nrun_14){
	 h_45Cr_sol->Fill(b_re(isol));
 } else if(Nrun_14 <= isol && isol  < Nrun_15){
	 h_46Cr_sol->Fill(b_re(isol));
 } else if(Nrun_15 <= isol && isol  < Nrun_16){
	 h_46Mn_sol->Fill(b_re(isol));
 } else if(Nrun_16 <= isol && isol  < Nrun_17){
	 h_47Mn_sol->Fill(b_re(isol));
 } else if(Nrun_17 <= isol && isol  < Nrun_18){
	 h_48Mn_sol->Fill(b_re(isol));
 } else if(Nrun_18 <= isol && isol  < Nrun_19){
	 h_48Fe_sol->Fill(b_re(isol));
 } else if(Nrun_19 <= isol && isol  < Nrun_20){
	 h_49Fe_sol->Fill(b_re(isol));
 } else if(Nrun_20 <= isol && isol  < Nrun_21){
	 h_50Fe_sol->Fill(b_re(isol));
 }
}


// Output

 TH1D *h_aq_cor = new TH1D("aq_cor", "aq_cor",500,1.7,2.3);
 TH1D *h_aq_cor_wr = new TH1D("aq_cor_wr", "aq_cor_wr",500,-10,10);

// TH1D *h_38Ca = new TH1D("h38Ca", "h38Ca",1000,1.89,1.91);
 TH1D *h_39Ca = new TH1D("h39Ca", "h39Ca",1000,1.940,1.960);
 TH1D *h_40Ca = new TH1D("h40Ca", "h40Ca",1000,1.990,2.01);
 TH1D *h_41Ca = new TH1D("h41Ca", "h41Ca",1000,2.040,2.060);
                                                            
 TH1D *h_40Sc = new TH1D("h40Sc", "h40Sc",1000,1.900,1.92);
 TH1D *h_41Sc = new TH1D("h41Sc", "h41Sc",1000,1.945,1.965);
 TH1D *h_43Sc = new TH1D("h43Sc", "h43Sc",1000,2.04,2.060);
                                                            
 TH1D *h_40Ti = new TH1D("h40Ti", "h40Ti",1000,1.805,1.825);
 TH1D *h_41Ti = new TH1D("h41Ti", "h41Ti",1000,1.855,1.875);
// TH1D *h_43Ti = new TH1D("h43Ti", "h43Ti",1000,1.940,1.960);
// TH1D *h_47Ti = new TH1D("h47Ti", "h47Ti",1000,2.125,2.145);
 TH1D *h_42Ti = new TH1D("h42Ti", "h42Ti",1000,1.895,1.915);
                                                            
 TH1D *h_43V  = new TH1D("h43V", "h43V",1000,1.865,1.885);
 TH1D *h_44V  = new TH1D("h44V", "h44V",1000,1.90,1.92);
// TH1D *h_45V  = new TH1D("h45V", "h45V",1000,1.945,1.965);
// TH1D *h_47V  = new TH1D("h47V", "h47V",1000,2.03,2.05);
 TH1D *h_46V  = new TH1D("h46V", "h46V",1000,1.985,2.005);
                                                            
 TH1D *h_44Cr = new TH1D("h44Cr", "h44Cr",1000,1.825,1.845);
 TH1D *h_45Cr = new TH1D("h45Cr", "h45Cr",1000,1.865,1.885);
 TH1D *h_46Cr = new TH1D("h46Cr", "h46Cr",1000,1.90,1.925);
                                                            
 TH1D *h_46Mn = new TH1D("h46Mn", "h46Mn",1000,1.832,1.852);
 TH1D *h_47Mn = new TH1D("h47Mn", "h47Mn",1000,1.87,1.897);
 TH1D *h_48Mn = new TH1D("h48Mn", "h48Mn",1000,1.91,1.930);
                                                            
 TH1D *h_48Fe = new TH1D("h48Fe", "h48Fe",1000,1.8355,1.8555);
 TH1D *h_49Fe = new TH1D("h49Fe", "h49Fe",1000,1.875,1.895);
 TH1D *h_50Fe = new TH1D("h50Fe", "h50Fe",1000,1.91,1.930);

 TH2D *h_zaq_cor = new TH2D("zaq_col", "zaq_col",500,1.7,2.3,500,18,30);

   Int_t Nevt_valid = evt_valid.size();

//   Double_t aq_cor_br;
//   tree->Branch("Aq_cor",&aq_cor_br,"Aq_cor/D");

  for (Int_t iData = 0; iData < Nevt_valid; iData++){

    int itmp = evt_valid[iData];
    tree->GetEntry(itmp);

     h_aq_cor->Fill(Aq_cor[iData]);
     h_aq_cor_wr->Fill(Aq_cor[iData]);

     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
 
      h_zaq_cor->Fill(Aq_cor[iData],z_tmpt);
//	  aq_cor_br = Aq_cor[iData];
//	  tree->Fill();

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

//      h_38Ca->Fill(Aq_cor[iData]);
      h_39Ca->Fill(Aq_cor[iData]);
      h_40Ca->Fill(Aq_cor[iData]); 
      h_41Ca->Fill(Aq_cor[iData]);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc->Fill(Aq_cor[iData]);
      h_41Sc->Fill(Aq_cor[iData]);
      h_43Sc->Fill(Aq_cor[iData]);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti->Fill(Aq_cor[iData]);
      h_41Ti->Fill(Aq_cor[iData]);
//      h_43Ti->Fill(Aq_cor[iData]);
//      h_47Ti->Fill(Aq_cor[iData]);
      h_42Ti->Fill(Aq_cor[iData]);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V->Fill(Aq_cor[iData]);
      h_44V->Fill(Aq_cor[iData]);
//      h_45V->Fill(Aq_cor[iData]);
//      h_47V->Fill(Aq_cor[iData]);
      h_46V->Fill(Aq_cor[iData]);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr->Fill(Aq_cor[iData]);
      h_45Cr->Fill(Aq_cor[iData]);
      h_46Cr->Fill(Aq_cor[iData]);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn->Fill(Aq_cor[iData]);
      h_47Mn->Fill(Aq_cor[iData]);
      h_48Mn->Fill(Aq_cor[iData]);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe->Fill(Aq_cor[iData]);
      h_49Fe->Fill(Aq_cor[iData]);
      h_50Fe->Fill(Aq_cor[iData]);

  }else {
	  continue;
  }
}


//// Draw original histogram

 TH1D *h_aq_cor_org = new TH1D("aq_cor_org", "aq_cor_org",500,1.7,2.3);

// TH1D *h_38Ca_org = new TH1D("h38Ca_org", "h38Ca_org",1000,1.89,1.91);
 TH1D *h_39Ca_org = new TH1D("h39Ca_org", "h39Ca_org",1000,1.940,1.960);
 TH1D *h_40Ca_org = new TH1D("h40Ca_org", "h40Ca_org",1000,1.990,2.01);
 TH1D *h_41Ca_org = new TH1D("h41Ca_org", "h41Ca_org",1000,2.040,2.060);
                                                                        
 TH1D *h_40Sc_org = new TH1D("h40Sc_org", "h40Sc_org",1000,1.900,1.92);
 TH1D *h_41Sc_org = new TH1D("h41Sc_org", "h41Sc_org",1000,1.945,1.965);
 TH1D *h_43Sc_org = new TH1D("h43Sc_org", "h43Sc_org",1000,2.04,2.060);
                                                                        
 TH1D *h_40Ti_org = new TH1D("h40Ti_org", "h40Ti_org",1000,1.81,1.83);
 TH1D *h_41Ti_org = new TH1D("h41Ti_org", "h41Ti_org",1000,1.86,1.88);
// TH1D *h_43Ti_org = new TH1D("h43Ti_org", "h43Ti_org",1000,1.940,1.960);
// TH1D *h_47Ti_org = new TH1D("h47Ti_org", "h47Ti_org",1000,2.125,2.145);
 TH1D *h_42Ti_org = new TH1D("h47Ti_org", "h47Ti_org",1000,1.895,1.915);
                                                                        
 TH1D *h_43V_org = new TH1D("h43V_org", "h43V_org",1000,1.86,1.880);
 TH1D *h_44V_org = new TH1D("h44V_org", "h44V_org",1000,1.90,1.92);
// TH1D *h_45V_org = new TH1D("h45V_org", "h45V_org",51000,1.945,1.965);
// TH1D *h_47V_org = new TH1D("h47V_org", "h47V_org",51000,2.01,2.21);
 TH1D *h_46V_org = new TH1D("h46V_org", "h46V_org",1000,1.985,2.005);
                                                                        
 TH1D *h_44Cr_org = new TH1D("h44Cr_org", "h44Cr_org",1000,1.83,1.85);
 TH1D *h_45Cr_org = new TH1D("h45Cr_org", "h45Cr_org",1000,1.865,1.885);
 TH1D *h_46Cr_org = new TH1D("h46Cr_org", "h46Cr_org",1000,1.90,1.925);
                                                                        
 TH1D *h_46Mn_org = new TH1D("h46Mn_org", "h46Mn_org",1000,1.83,1.85);
 TH1D *h_47Mn_org = new TH1D("h47Mn_org", "h47Mn_org",1000,1.87,1.897);
 TH1D *h_48Mn_org = new TH1D("h48Mn_org", "h48Mn_org",1000,1.91,1.930);
                                                                        
 TH1D *h_48Fe_org = new TH1D("h48Fe_org", "h48Fe_org",1000,1.835,1.855);
 TH1D *h_49Fe_org = new TH1D("h49Fe_org", "h49Fe_org",1000,1.87,1.89);
 TH1D *h_50Fe_org = new TH1D("h50Fe_org", "h50Fe_org",1000,1.91,1.930);

 TH2D *h_zaq_org = new TH2D("zaq_org", "zaq_org",500,1.7,2.3,500,18,30);

  for (Int_t iData = 0; iData < nData; iData++){
     tree->GetEntry(iData);
     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     art::TMassData *mass_corst3_tmpt = (art::TMassData*) array_mass_corst3->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t aq_tmpt = mass_corst3_tmpt->GetAq();
 
     h_aq_cor_org->Fill(aq_tmpt);
     h_zaq_org->Fill(aq_tmpt,z_tmpt);

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

//      h_38Ca_org->Fill(aq_tmpt);
      h_39Ca_org->Fill(aq_tmpt);
      h_40Ca_org->Fill(aq_tmpt); 
      h_41Ca_org->Fill(aq_tmpt);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc_org->Fill(aq_tmpt);
      h_41Sc_org->Fill(aq_tmpt);
      h_43Sc_org->Fill(aq_tmpt);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti_org->Fill(aq_tmpt);
      h_41Ti_org->Fill(aq_tmpt);
//      h_43Ti_org->Fill(aq_tmpt);
//      h_47Ti_org->Fill(aq_tmpt);
      h_42Ti_org->Fill(aq_tmpt);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V_org->Fill(aq_tmpt);
      h_44V_org->Fill(aq_tmpt);
//      h_45V_org->Fill(aq_tmpt);
//      h_47V_org->Fill(aq_tmpt);
      h_46V_org->Fill(aq_tmpt);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr_org->Fill(aq_tmpt);
      h_45Cr_org->Fill(aq_tmpt);
      h_46Cr_org->Fill(aq_tmpt);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn_org->Fill(aq_tmpt);
      h_47Mn_org->Fill(aq_tmpt);
      h_48Mn_org->Fill(aq_tmpt);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe_org->Fill(aq_tmpt);
      h_49Fe_org->Fill(aq_tmpt);
      h_50Fe_org->Fill(aq_tmpt);

  }
 }


//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref1_3step.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref1_3step_unit2.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref3_3step_unit2.hist.root","recreate");
   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref4_3step_unit2_SSR.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st3_ref5_3step_unit2_SSR.hist.root","recreate");

 h_aq_sol->Write();
// h_38Ca_sol->Write();   
 h_39Ca_sol->Write();   
 h_40Ca_sol->Write();
 h_41Ca_sol->Write();
 h_40Sc_sol->Write();
 h_41Sc_sol->Write();
 h_43Sc_sol->Write();
 h_40Ti_sol->Write();
 h_41Ti_sol->Write();
// h_43Ti_sol->Write();
// h_47Ti_sol->Write();
 h_42Ti_sol->Write();
 h_43V_sol->Write(); 
 h_44V_sol->Write(); 
// h_45V_sol->Write();
// h_47V_sol->Write();
 h_46V_sol->Write();
 h_44Cr_sol->Write();   
 h_45Cr_sol->Write();
 h_46Cr_sol->Write();
 h_46Mn_sol->Write();
 h_47Mn_sol->Write();
 h_48Mn_sol->Write();
 h_48Fe_sol->Write();
 h_49Fe_sol->Write();
 h_50Fe_sol->Write();

 h_aq_cor->Write(); 
 h_aq_cor_wr->Write();
// h_38Ca->Write(); 
 h_39Ca->Write(); 
 h_40Ca->Write(); 
 h_41Ca->Write(); 
 h_40Sc->Write(); 
 h_41Sc->Write(); 
 h_43Sc->Write(); 
 h_40Ti->Write(); 
 h_41Ti->Write(); 
// h_43Ti->Write(); 
// h_47Ti->Write(); 
 h_42Ti->Write(); 
 h_43V->Write(); 
 h_44V->Write(); 
// h_45V->Write(); 
// h_47V->Write(); 
 h_46V->Write(); 
 h_44Cr->Write(); 
 h_45Cr->Write(); 
 h_46Cr->Write(); 
 h_46Mn->Write(); 
 h_47Mn->Write(); 
 h_48Mn->Write(); 
 h_48Fe->Write(); 
 h_49Fe->Write(); 
 h_50Fe->Write(); 
 h_zaq_cor->Write();

 h_aq_cor_org->Write();
// h_38Ca_org->Write();  
 h_39Ca_org->Write();  
 h_40Ca_org->Write();
 h_41Ca_org->Write();
 h_40Sc_org->Write();
 h_41Sc_org->Write();
 h_43Sc_org->Write();
 h_40Ti_org->Write();
 h_41Ti_org->Write();
// h_43Ti_org->Write();
// h_47Ti_org->Write();
 h_42Ti_org->Write();
 h_43V_org->Write();
 h_44V_org->Write();
// h_45V_org->Write();
// h_47V_org->Write();
 h_46V_org->Write();
 h_44Cr_org->Write();
 h_45Cr_org->Write();
 h_46Cr_org->Write();
 h_46Mn_org->Write();
 h_47Mn_org->Write();
 h_48Mn_org->Write();
 h_48Fe_org->Write();
 h_49Fe_org->Write();
 h_50Fe_org->Write();
 h_zaq_org->Write();



 ofile->Close(); 
 

}
