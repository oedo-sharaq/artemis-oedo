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

void fiterror_mass_calib8step_svd_stm_reflise_eventstore(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_reflise_plsmahala.eventstore.170272.all.root"); // Add file. Basically mass calibration file.


//  const Int_t Nrun = 2000;  //the number of runs
//  const Int_t Nrun = 1000;  //the number of runs
  const Int_t Nrun = 3000;  //the number of runs
  const Int_t Nrun_ni = 90;  //the number of runs
  const Int_t Nref =  19;  // the number of species for reference
  const Int_t Nevt =  (Nref - 1) * Nrun + Nrun_ni;  // the number of events
  const Int_t Nprm =  1001;  //the number of parameters 4th order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mahala = NULL;
 TClonesArray *array_dia_tof32stm = NULL;
 TClonesArray *array_mass_corstm = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_trackd = NULL;
 TClonesArray *array_s0 = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mahala",&array_mahala);
 tree->SetBranchAddress("dia_tof32stm",&array_dia_tof32stm);
 tree->SetBranchAddress("mass_corstm_BLD_7th",&array_mass_corstm);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mahala",1);
 tree->SetBranchStatus("dia_tof32stm",1);
 tree->SetBranchStatus("mass_corstm_BLD_7th",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2",1);
 tree->SetBranchStatus("sr0_xcw",1);
 tree->SetBranchStatus("eventheader",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp, Errorref_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up, Errorref;

// ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_8step_stm_reflise.dat");
 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_8step_stm_reflise_errorinc.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

  while(!fin.eof()){
	    fin.precision(10);
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp >> Errorref_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);
		Errorref.push_back(Errorref_tmp);
		}
 fin.close();

 TMatrixD A(Nevt,Nprm);
 TMatrixD b(Nevt,1);
 TMatrixD value(Nevt,14); // output the fitting value 
 TMatrixD value_mahala_pop(Nevt,10); // output the fitting value 

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
 int Nrun_tmp;

for (int iref = 0; iref < Nref; iref++){
    vector<Int_t> irandm;
	int n_tmp = 0;
  if( iref < 18){  
     Nrun_tmp = Nrun;
  }else{
  	Nrun_tmp = Nrun_ni;
  }

  for(int i = 0; i < nData; i++){
	  tree->GetEntry(i);

      Int_t hit_mass = array_mass->GetEntriesFast();
      Int_t hit_mass_corstm = array_mass_corstm->GetEntriesFast();
      Int_t hit_mahala = array_mahala->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_trackd = array_trackd->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_mass_corstm > 0 && hit_tracku > 0 && hit_trackd > 0 && hit_s0 > 0 && hit_mahala > 0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMassData *mass_corstm_tmp = (art::TMassData*) array_mass_corstm->UncheckedAt(0);
	 art::TMahalaData *mahala_tmp = (art::TMahalaData*) array_mahala->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_corstm_tmp->GetAq();
     Double_t md = mahala_tmp->GetMd();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TDiaTimingData *tof_tmp = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsGood();
     Bool_t trackd_ok = trackd_tmp->IsGood();
     Double_t ssrd = trackd_tmp->GetSSR();

     Bool_t mahala_ok = md < 1;
 

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok && mahala_ok)
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

  if (n_tmp < Nrun_tmp){
    cout << "Caution!! Reference No." << iref << " does not have enough number of events.\n";
    HasEvents = false;  
	continue;
    }else{
      cout << "Sampling events of Reference No." << iref << " was finished.\n";
    }

//// Generate random run number
     for (int r = 0; r < Nrun_tmp; r++){
         int j = gRandom->Uniform(r,n_tmp);
		 int randm_tmp = irandm[r];
		 irandm[r] = irandm[j];
       	 irandm[j] = randm_tmp;
     }

//// Fill data in matrix for each Ref	 
   for(int p = 0; p < Nrun_tmp; p++){
     int k = irandm[p];
     tree->GetEntry(k);
	 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32stm = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
	 art::TMassData *mass_corstm = (art::TMassData*) array_mass_corstm->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t z_select = mass->GetZ();
     Double_t aq_select = mass_corstm->GetAq();
     Int_t runnumber = array_eventheader->GetRunNumber();

     Double_t ti = dia_tof32stm->GetTiming();
     Double_t x3i = tracku->GetX();
     Double_t a3i = tracku->GetA() * 1000.;
     Double_t y3i = tracku->GetY();
     Double_t b3i = tracku->GetB() * 1000.;
     Double_t x0i = sr0->GetPosition();
     Double_t x2i = trackd->GetX(-49.5);
     Double_t a2i = trackd->GetA() * 1000.;
     Double_t y2i = trackd->GetY(-49.5);
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

////     Double_t t = (ti - 2042.) * 0.125;  
//     Double_t t = (ti - 2042.) * 0.025;  
//     Double_t x3 = x3i * 0.1; 
//     Double_t a3 = a3i * 0.1;
//     Double_t y3 = y3i + 2;
//     Double_t b3 = b3i * 0.05 + 0.5;
//     Double_t x0 = x0i * 0.015; 
//     Double_t x2 = x2i * 0.1; 
//     Double_t a2 = a2i * 0.025;
//     Double_t y2 = y2i * 0.05 - 1;
//     Double_t b2 = b2i * 0.05 - 0.2;

//     Double_t t = (ti - 2042.) * 0.025;  
//     Double_t x3 = x3i * 0.1 + 1; 
//     Double_t a3 = a3i * 0.1 + 1;
//     Double_t y3 = y3i + 2 + 1;
//     Double_t b3 = b3i * 0.05 + 0.5 +1;
//     Double_t x0 = x0i * 0.015 + 1; 
//     Double_t x2 = x2i * 0.1 + 1; 
//     Double_t a2 = a2i * 0.025 + 1;
//     Double_t y2 = y2i * 0.05 - 1 + 1;
//     Double_t b2 = b2i * 0.05 - 0.2 + 1;

// reflise
     Double_t t = ((ti - 2042.) * 0.025 + 0.35) * 3;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1;
     Double_t y3 = y3i + 2;
     Double_t b3 = b3i * 0.05 + 0.5;
     Double_t x0 = x0i * 0.015; 
     Double_t x2 = x2i * 0.1; 
     Double_t a2 = a2i * 0.025;
     Double_t y2 = y2i * 0.05 - 1;
     Double_t b2 = b2i * 0.05 - 0.2;

//// reflise2
//     Double_t t = ((ti - 2042.) * 0.025 + 0.35) * 3 + 1;  
//     Double_t x3 = x3i * 0.1 + 1; 
//     Double_t a3 = a3i * 0.1 + 1.5;
//     Double_t y3 = (y3i + 2) * 0.5 + 1;
//     Double_t b3 = b3i * 0.05 + 0.5 + 1;
//     Double_t x0 = x0i * 0.015 + 1; 
//     Double_t x2 = x2i * 0.1 + 1.5; 
//     Double_t a2 = a2i * 0.025 + 1;
//     Double_t y2 = (y2i * 0.05 - 1) * 0.5 + 1;
//     Double_t b2 = (b2i * 0.05 - 0.2) * 0.5 + 1;


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
// 4th order
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

//     b(ievt,0) = Ref_m[iref];
     b(ievt,0) = Ref_m[iref] * Ref_m[iref];
  
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

     value_mahala_pop(ievt,0) = t;
     value_mahala_pop(ievt,1) = x3;
     value_mahala_pop(ievt,2) = a3;
     value_mahala_pop(ievt,3) = y3;
     value_mahala_pop(ievt,4) = b3;
     value_mahala_pop(ievt,5) = x0;
     value_mahala_pop(ievt,6) = x2;
     value_mahala_pop(ievt,7) = a2;
     value_mahala_pop(ievt,8) = y2;
     value_mahala_pop(ievt,9) = b2;

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

// ofstream foutefit("sh13_analysis/hanai/output/efit_stm_reflise_8step.dat");
//
//TMatrixD efit(Nref,Nrun);
//Double_t efit_tmp;
//
//for(int n = 0; n < Nref; n ++){  //begining
//  
//  if( n < 18){  
//     Nrun_tmp = Nrun;
//  }else{
//  	Nrun_tmp = Nrun_ni;
//  }
//
//  TMatrixD V(Nrun_tmp,Nrun_tmp);
//  
//  Double_t sigsum = 0;
//
//
// for(int m = 0; m < Nrun_tmp; m++){
//     sigsum += TMath::Power(Errorref[n],-2);
//    }
//
//
//for(int k = 0; k < Nrun_tmp; k++){
//
//   int N_i;
//   int kk;
//
//   N_i = Nrun_tmp * n;
//   kk = N_i + k;
//
// for(int i = 0; i < Nprm; i++){
//  for(int j = 0; j < Nprm; j++){
//
//          V(i,j) = sigsum * A(kk,i) * A(kk,j);
//     
//	 }
//   } 
// 
// TDecompSVD svd_V(V);
// TMatrixD Vi = svd_V.Invert();
// TMatrixD var(Nprm,Nprm);
//
// for(int s = 0; s < Nprm; s++){
//  for(int t = 0; t < Nprm; t++){
//
//    
//    var(s,t) = Vi(s,t);
//
//  efit_tmp += var(s,t) * A(kk,s) * A(kk,t);
// 
//  }
// }
//
//  efit(n,k) = TMath::Sqrt(efit_tmp);
//  foutefit << efit(n,k) << "  " ; 
//
// }
//
// foutefit << endl;
//
//}


// Standarlize popuration martix

 cout << "=== Maharanobis distance calculation ===" << endl;

 Int_t Nopt = 10;

 vector<Double_t> mean_pop(Nopt);
 vector<Double_t> var_pop(Nopt);
 vector<Double_t> sdv_pop(Nopt);
 vector<Double_t> varstand_pop(Nopt);
 TMatrixD  valuestand_pop(Nevt,Nopt);
 TMatrixD  cov_pop(Nopt,Nopt);
 TMatrixD  R_pop(Nopt,Nopt);

 TH2D *tx3_hist  = new TH2D("tx3_hist","tx3_hist",300,-2,2,300,-2,2);
 TH2D *ta3_hist  = new TH2D("ta3_hist","ta3_hist",300,-2,2,300,-2,2);
 TH2D *ty3_hist  = new TH2D("ty3_hist","ty3_hist",300,-2,2,300,-2,2);
 TH2D *tb3_hist  = new TH2D("tb3_hist","tb3_hist",300,-2,2,300,-2,2);
 TH2D *tx0_hist  = new TH2D("tx0_hist","tx0_hist",300,-2,2,300,-2,2);
 TH2D *tx2_hist  = new TH2D("tx2_hist","tx2_hist",300,-2,2,300,-2,2);
 TH2D *ta2_hist  = new TH2D("ta2_hist","ta2_hist",300,-2,2,300,-2,2);
 TH2D *ty2_hist  = new TH2D("ty2_hist","ty2_hist",300,-2,2,300,-2,2);
 TH2D *tb2_hist  = new TH2D("tb2_hist","tb2_hist",300,-2,2,300,-2,2);

 TH2D *x3a3_hist = new TH2D("x3a3_hist","x3a3_hist",300,-2,2,300,-2,2);
 TH2D *x3y3_hist = new TH2D("x3y3_hist","x3y3_hist",300,-2,2,300,-2,2);
 TH2D *x3b3_hist = new TH2D("x3b3_hist","x3b3_hist",300,-2,2,300,-2,2);
 TH2D *x3x0_hist = new TH2D("x3x0_hist","x3x0_hist",300,-2,2,300,-2,2);
 TH2D *x3x2_hist = new TH2D("x3x2_hist","x3x2_hist",300,-2,2,300,-2,2);
 TH2D *x3a2_hist = new TH2D("x3a2_hist","x3a2_hist",300,-2,2,300,-2,2);
 TH2D *x3y2_hist = new TH2D("x3y2_hist","x3y2_hist",300,-2,2,300,-2,2);
 TH2D *x3b2_hist = new TH2D("x3b2_hist","x3b2_hist",300,-2,2,300,-2,2);

 TH2D *a3y3_hist = new TH2D("a3y3_hist","a3y3_hist",300,-2,2,300,-2,2);
 TH2D *a3b3_hist = new TH2D("a3b3_hist","a3b3_hist",300,-2,2,300,-2,2);
 TH2D *a3x0_hist = new TH2D("a3x0_hist","a3x0_hist",300,-2,2,300,-2,2);
 TH2D *a3x2_hist = new TH2D("a3x2_hist","a3x2_hist",300,-2,2,300,-2,2);
 TH2D *a3a2_hist = new TH2D("a3a2_hist","a3a2_hist",300,-2,2,300,-2,2);
 TH2D *a3y2_hist = new TH2D("a3y2_hist","a3y2_hist",300,-2,2,300,-2,2);
 TH2D *a3b2_hist = new TH2D("a3b2_hist","a3b2_hist",300,-2,2,300,-2,2);

 TH2D *y3b3_hist = new TH2D("y3b3_hist","y3b3_hist",300,-2,2,300,-2,2);
 TH2D *y3x0_hist = new TH2D("y3x0_hist","y3x0_hist",300,-2,2,300,-2,2);
 TH2D *y3x2_hist = new TH2D("y3x2_hist","y3x2_hist",300,-2,2,300,-2,2);
 TH2D *y3a2_hist = new TH2D("y3a2_hist","y3a2_hist",300,-2,2,300,-2,2);
 TH2D *y3y2_hist = new TH2D("y3y2_hist","y3y2_hist",300,-2,2,300,-2,2);
 TH2D *y3b2_hist = new TH2D("y3b2_hist","y3b2_hist",300,-2,2,300,-2,2);

 TH2D *b3x0_hist = new TH2D("b3x0_hist","b3x0_hist",300,-2,2,300,-2,2);
 TH2D *b3x2_hist = new TH2D("b3x2_hist","b3x2_hist",300,-2,2,300,-2,2);
 TH2D *b3a2_hist = new TH2D("b3a2_hist","b3a2_hist",300,-2,2,300,-2,2);
 TH2D *b3y2_hist = new TH2D("b3y2_hist","b3y2_hist",300,-2,2,300,-2,2);
 TH2D *b3b2_hist = new TH2D("b3b2_hist","b3b2_hist",300,-2,2,300,-2,2);

 TH2D *x0x2_hist = new TH2D("x0x2_hist","x0x2_hist",300,-2,2,300,-2,2);
 TH2D *x0a2_hist = new TH2D("x0a2_hist","x0a2_hist",300,-2,2,300,-2,2);
 TH2D *x0y2_hist = new TH2D("x0y2_hist","x0y2_hist",300,-2,2,300,-2,2);
 TH2D *x0b2_hist = new TH2D("x0b2_hist","x0b2_hist",300,-2,2,300,-2,2);

 TH2D *x2a2_hist = new TH2D("x2a2_hist","x2a2_hist",300,-2,2,300,-2,2);
 TH2D *x2y2_hist = new TH2D("x2y2_hist","x2y2_hist",300,-2,2,300,-2,2);
 TH2D *x2b2_hist = new TH2D("x2b2_hist","x2b2_hist",300,-2,2,300,-2,2);

 TH2D *a2y2_hist = new TH2D("a2y2_hist","a2y2_hist",300,-2,2,300,-2,2);
 TH2D *a2b2_hist = new TH2D("a2b2_hist","a2b2_hist",300,-2,2,300,-2,2);

 TH2D *y2b2_hist = new TH2D("y2b2_hist","y2b2_hist",300,-2,2,300,-2,2);

for(int k = 0; k < Nevt; k++){

   tx3_hist->Fill(value_mahala_pop(k,1),value_mahala_pop(k,0)); 
   ta3_hist->Fill(value_mahala_pop(k,2),value_mahala_pop(k,0)); 
   ty3_hist->Fill(value_mahala_pop(k,3),value_mahala_pop(k,0)); 
   tb3_hist->Fill(value_mahala_pop(k,4),value_mahala_pop(k,0)); 
   tx0_hist->Fill(value_mahala_pop(k,5),value_mahala_pop(k,0)); 
   tx2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,0)); 
   ta2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,0)); 
   ty2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,0)); 
   tb2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,0)); 
  x3a3_hist->Fill(value_mahala_pop(k,2),value_mahala_pop(k,1));
  x3y3_hist->Fill(value_mahala_pop(k,3),value_mahala_pop(k,1));
  x3b3_hist->Fill(value_mahala_pop(k,4),value_mahala_pop(k,1));
  x3x0_hist->Fill(value_mahala_pop(k,5),value_mahala_pop(k,1));
  x3x2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,1));
  x3a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,1));
  x3y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,1));
  x3b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,1));
  a3y3_hist->Fill(value_mahala_pop(k,3),value_mahala_pop(k,2));
  a3b3_hist->Fill(value_mahala_pop(k,4),value_mahala_pop(k,2));
  a3x0_hist->Fill(value_mahala_pop(k,5),value_mahala_pop(k,2));
  a3x2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,2));
  a3a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,2));
  a3y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,2));
  a3b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,2));
  y3b3_hist->Fill(value_mahala_pop(k,4),value_mahala_pop(k,3));
  y3x0_hist->Fill(value_mahala_pop(k,5),value_mahala_pop(k,3));
  y3x2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,3));
  y3a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,3));
  y3y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,3));
  y3b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,3));
  b3x0_hist->Fill(value_mahala_pop(k,5),value_mahala_pop(k,4));
  b3x2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,4));
  b3a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,4));
  b3y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,4));
  b3b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,4));
  x0x2_hist->Fill(value_mahala_pop(k,6),value_mahala_pop(k,5));
  x0a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,5));
  x0y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,5));
  x0b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,5));
  x2a2_hist->Fill(value_mahala_pop(k,7),value_mahala_pop(k,6));
  x2y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,6));
  x2b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,6));
  a2y2_hist->Fill(value_mahala_pop(k,8),value_mahala_pop(k,7));
  a2b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,7));
  y2b2_hist->Fill(value_mahala_pop(k,9),value_mahala_pop(k,8));

}

  TFile *ofv = new TFile("sh13_analysis/hanai/output/Mahala_correlation_tinc.hist.root","recreate");

   tx3_hist->Write();
   ta3_hist->Write();   
   ty3_hist->Write();
   tb3_hist->Write();
   tx0_hist->Write();
   tx2_hist->Write();
   ta2_hist->Write();
   ty2_hist->Write();
   tb2_hist->Write();
  x3a3_hist->Write();
  x3y3_hist->Write();
  x3b3_hist->Write();
  x3x0_hist->Write();
  x3x2_hist->Write();
  x3a2_hist->Write();
  x3y2_hist->Write();
  x3b2_hist->Write();
  a3y3_hist->Write();
  a3b3_hist->Write();
  a3x0_hist->Write();
  a3x2_hist->Write();
  a3a2_hist->Write();
  a3y2_hist->Write();
  a3b2_hist->Write();
  y3b3_hist->Write();
  y3x0_hist->Write();
  y3x2_hist->Write();
  y3a2_hist->Write();
  y3y2_hist->Write();
  y3b2_hist->Write();
  b3x0_hist->Write();
  b3x2_hist->Write();
  b3a2_hist->Write();
  b3y2_hist->Write();
  b3b2_hist->Write();
  x0x2_hist->Write();
  x0a2_hist->Write();
  x0y2_hist->Write();
  x0b2_hist->Write();
  x2a2_hist->Write();
  x2y2_hist->Write();
  x2b2_hist->Write();
  a2y2_hist->Write();
  a2b2_hist->Write();
  y2b2_hist->Write();

 ofv->Close();

 Double_t  corr_tx3 =   tx3_hist->GetCorrelationFactor();
 Double_t  corr_ta3 =   ta3_hist->GetCorrelationFactor();
 Double_t  corr_ty3 =   ty3_hist->GetCorrelationFactor();
 Double_t  corr_tb3 =   tb3_hist->GetCorrelationFactor();
 Double_t  corr_tx0 =   tx0_hist->GetCorrelationFactor();
 Double_t  corr_tx2 =   tx2_hist->GetCorrelationFactor();
 Double_t  corr_ta2 =   ta2_hist->GetCorrelationFactor();
 Double_t  corr_ty2 =   ty2_hist->GetCorrelationFactor();
 Double_t  corr_tb2 =   tb2_hist->GetCorrelationFactor();
 Double_t corr_x3a3 =  x3a3_hist->GetCorrelationFactor();
 Double_t corr_x3y3 =  x3y3_hist->GetCorrelationFactor();
 Double_t corr_x3b3 =  x3b3_hist->GetCorrelationFactor();
 Double_t corr_x3x0 =  x3x0_hist->GetCorrelationFactor();
 Double_t corr_x3x2 =  x3x2_hist->GetCorrelationFactor();
 Double_t corr_x3a2 =  x3a2_hist->GetCorrelationFactor();
 Double_t corr_x3y2 =  x3y2_hist->GetCorrelationFactor();
 Double_t corr_x3b2 =  x3b2_hist->GetCorrelationFactor();
 Double_t corr_a3y3 =  a3y3_hist->GetCorrelationFactor();
 Double_t corr_a3b3 =  a3b3_hist->GetCorrelationFactor();
 Double_t corr_a3x0 =  a3x0_hist->GetCorrelationFactor();
 Double_t corr_a3x2 =  a3x2_hist->GetCorrelationFactor();
 Double_t corr_a3a2 =  a3a2_hist->GetCorrelationFactor();
 Double_t corr_a3y2 =  a3y2_hist->GetCorrelationFactor();
 Double_t corr_a3b2 =  a3b2_hist->GetCorrelationFactor();
 Double_t corr_y3b3 =  y3b3_hist->GetCorrelationFactor();
 Double_t corr_y3x0 =  y3x0_hist->GetCorrelationFactor();
 Double_t corr_y3x2 =  y3x2_hist->GetCorrelationFactor();
 Double_t corr_y3a2 =  y3a2_hist->GetCorrelationFactor();
 Double_t corr_y3y2 =  y3y2_hist->GetCorrelationFactor();
 Double_t corr_y3b2 =  y3b2_hist->GetCorrelationFactor();
 Double_t corr_b3x0 =  b3x0_hist->GetCorrelationFactor();
 Double_t corr_b3x2 =  b3x2_hist->GetCorrelationFactor();
 Double_t corr_b3a2 =  b3a2_hist->GetCorrelationFactor();
 Double_t corr_b3y2 =  b3y2_hist->GetCorrelationFactor();
 Double_t corr_b3b2 =  b3b2_hist->GetCorrelationFactor();
 Double_t corr_x0x2 =  x0x2_hist->GetCorrelationFactor();
 Double_t corr_x0a2 =  x0a2_hist->GetCorrelationFactor();
 Double_t corr_x0y2 =  x0y2_hist->GetCorrelationFactor();
 Double_t corr_x0b2 =  x0b2_hist->GetCorrelationFactor();
 Double_t corr_x2a2 =  x2a2_hist->GetCorrelationFactor();
 Double_t corr_x2y2 =  x2y2_hist->GetCorrelationFactor();
 Double_t corr_x2b2 =  x2b2_hist->GetCorrelationFactor();
 Double_t corr_a2y2 =  a2y2_hist->GetCorrelationFactor();
 Double_t corr_a2b2 =  a2b2_hist->GetCorrelationFactor();
 Double_t corr_y2b2 =  y2b2_hist->GetCorrelationFactor();


 R_pop(0,1) = corr_tx3;
 R_pop(1,0) = corr_tx3;

 R_pop(0,2) = corr_ta3;
 R_pop(2,0) = corr_ta3;

 R_pop(0,3) = corr_ty3;
 R_pop(3,0) = corr_ty3;

 R_pop(0,4) = corr_tb3;
 R_pop(4,0) = corr_tb3;

 R_pop(0,5) = corr_tx0;
 R_pop(5,0) = corr_tx0;

 R_pop(0,6) = corr_tx2;
 R_pop(6,0) = corr_tx2;

 R_pop(0,7) = corr_ta2;
 R_pop(7,0) = corr_ta2;

 R_pop(0,8) = corr_ty2;
 R_pop(8,0) = corr_ty2;

 R_pop(0,9) = corr_tb2;
 R_pop(9,0) = corr_tb2;

 R_pop(1,2) = corr_x3a3;
 R_pop(2,1) = corr_x3a3;

 R_pop(1,3) = corr_x3y3;
 R_pop(3,1) = corr_x3y3;

 R_pop(1,4) = corr_x3b3;
 R_pop(4,1) = corr_x3b3;

 R_pop(1,5) = corr_x3x0;
 R_pop(5,1) = corr_x3x0;

 R_pop(1,6) = corr_x3x2;
 R_pop(6,1) = corr_x3x2;

 R_pop(1,7) = corr_x3a2;
 R_pop(7,1) = corr_x3a2;

 R_pop(1,8) = corr_x3y2;
 R_pop(8,1) = corr_x3y2;

 R_pop(1,9) = corr_x3b2;
 R_pop(9,1) = corr_x3b2;

 R_pop(2,3) = corr_a3y3;
 R_pop(3,2) = corr_a3y3;

 R_pop(2,4) = corr_a3b3;
 R_pop(4,2) = corr_a3b3;

 R_pop(2,5) = corr_a3x0;
 R_pop(5,2) = corr_a3x0;

 R_pop(2,6) = corr_a3x2;
 R_pop(6,2) = corr_a3x2;

 R_pop(2,7) = corr_a3a2;
 R_pop(7,2) = corr_a3a2;

 R_pop(2,8) = corr_a3y2;
 R_pop(8,2) = corr_a3y2;

 R_pop(2,9) = corr_a3b2;
 R_pop(9,2) = corr_a3b2;

 R_pop(3,4) = corr_y3b3;
 R_pop(4,3) = corr_y3b3;

 R_pop(3,5) = corr_y3x0;
 R_pop(5,3) = corr_y3x0;

 R_pop(3,6) = corr_y3x2;
 R_pop(6,3) = corr_y3x2;

 R_pop(3,7) = corr_y3a2;
 R_pop(7,3) = corr_y3a2;

 R_pop(3,8) = corr_y3y2;
 R_pop(8,3) = corr_y3y2;

 R_pop(3,9) = corr_y3b2;
 R_pop(9,3) = corr_y3b2;

 R_pop(4,5) = corr_b3x0;
 R_pop(5,4) = corr_b3x0;

 R_pop(4,6) = corr_b3x2;
 R_pop(6,4) = corr_b3x2;

 R_pop(4,7) = corr_b3a2;
 R_pop(7,4) = corr_b3a2;

 R_pop(4,8) = corr_b3y2;
 R_pop(8,4) = corr_b3y2;

 R_pop(4,9) = corr_b3b2;
 R_pop(9,4) = corr_b3b2;

 R_pop(5,6) = corr_x0x2;
 R_pop(6,5) = corr_x0x2;

 R_pop(5,7) = corr_x0a2;
 R_pop(7,5) = corr_x0a2;

 R_pop(5,8) = corr_x0y2;
 R_pop(8,5) = corr_x0y2;

 R_pop(5,9) = corr_x0b2;
 R_pop(9,5) = corr_x0b2;

 R_pop(6,7) = corr_x2a2;
 R_pop(7,6) = corr_x2a2;

 R_pop(6,8) = corr_x2y2;
 R_pop(8,6) = corr_x2y2;

 R_pop(6,9) = corr_x2b2;
 R_pop(9,6) = corr_x2b2;

 R_pop(7,8) = corr_a2y2;
 R_pop(8,7) = corr_a2y2;

 R_pop(7,9) = corr_a2b2;
 R_pop(9,7) = corr_a2b2;

 R_pop(8,9) = corr_y2b2;
 R_pop(9,8) = corr_y2b2;

for(int i = 0; i < Nopt; i++){
   R_pop(i,i) = 1;

}



// Fill the distance to hist

 ofstream foutmahalaR("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/mahalaR_stm_reflise_tinc.dat");

for(int i = 0; i < Nopt; i++){

 foutmahalaR << R_pop(i,0) << "  "<< R_pop(i,1)  <<"  " << R_pop(i,2) << "  "  << R_pop(i,3) <<"  "<< R_pop(i,4) << "  "<< R_pop(i,5) << "  "<< R_pop(i,6) << "  "<< R_pop(i,7) << "  "<< R_pop(i,8) << "  "  << R_pop(i, 9) << endl;

}

 TDecompSVD svd_R(R_pop);
 TMatrixD Ri = svd_R.Invert();

 ofstream foutmahalaRi("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/mahalaRi_stm_reflise_tinc.dat");

for(int i = 0; i < Nopt; i++){

 foutmahalaRi << Ri(i,0) << "  "<< Ri(i,1)  <<"  " << Ri(i,2) << "  "  << Ri(i,3) <<"  "<< Ri(i,4) << "  "<< Ri(i,5) << "  "<< Ri(i,6) << "  "<< Ri(i,7) << "  "<< Ri(i,8) << "  " << Ri(i,9) << endl;

}


 TMatrixD RiR(Nopt,Nopt);
          RiR.Mult(R_pop,Ri);
   
 cout << " Popuration matrix created. " << endl;

//// Standarization target matrix
//
// TFile *ofile = new TFile("output/mass/mahala/mahala_stm_reflise_tinc.hist.root","recreate");
//
//for(int j = 0; j < Nref; j++){
//
//// Standalization for target1
//
// int N_i;
// int N_f;
//
//if( j < 18){
//   N_i = 0 + Nrun * j;
//   N_f = N_i + Nrun;
//}else if( j == 18){
//	N_i = Nrun * j;
//	N_f = N_i + Nrun_ni;
//}else{
//	N_i = Nevt_pop + Nrun * (j - 19);
//    N_f = N_i + Nrun;
//}
//
// int N_leng = N_f - N_i;
//
// vector<Double_t> mean_1tgt(Nopt);
// vector<Double_t> var_1tgt(Nopt);
// vector<Double_t> sdv_1tgt(Nopt);
// TMatrixD  value_1tgt(N_leng,Nopt);
//
// Int_t k_fact = Nopt;
//
// TH1D *hmahala1 = new TH1D(Form("hmahala%d",j),Form("hmahala%d",j),400,-0.5,3.5);
//
// TMatrixD tgt1(Nopt,1);
//
//for(int qq = N_i; qq < N_f; qq++){
// for(int q = 0; q < Nopt; q++){
//
//	tgt1(q,0) = value_mahala_tgt(qq,q);
//  }
//
//  TMatrixD tgt1t(1,Nopt);
//           tgt1t.Transpose(tgt1);
//
//
// TMatrixD D1_tmp_t(tgt1t,TMatrixD::kMult,Ri);
// TMatrixD D1_tmp(D1_tmp_t,TMatrixD::kMult,tgt1);
// 
//  Int_t nrow1 = D1_tmp.GetNrows();
//  Int_t ncol1 = D1_tmp.GetNcols();
// if( nrow1 != 1 || ncol1 != 1 ){
//   cout << Form("Error! Something wrong in matrix calculation tgt%d",j) << endl;
//  return;
// }else{
//  Double_t D1 = D1_tmp(0,0) / k_fact;
//  Double_t d1 = TMath::Sqrt(D1);
//
////  foutmahala1tgt << d1 << endl;
//  hmahala1->Fill(d1);
//  }
// }
// cout << Form("Distance Calcutation for target%d is finished.",j) << endl;
//
//// Write matrix
//
// hmahala1->Write();
//
// delete gROOT->Get("hmahala1");
//
//}
//
// ofile->Close();


}

