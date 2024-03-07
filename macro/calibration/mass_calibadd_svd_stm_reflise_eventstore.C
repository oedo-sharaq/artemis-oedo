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

void mass_calibadd_svd_stm_reflise_eventstore(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.all.root"); // Add file. Basically mass calibration file.


//  const Int_t Nrun = 2000;  //the number of runs
  const Int_t Nrun = 1000;  //the number of runs
  const Int_t Nrun_ni = 150;  //the number of runs
  const Int_t Nref =  19;  // the number of species for reference
  const Int_t Nevt =  (Nref - 1) * Nrun + Nrun_ni;  // the number of events
  const Int_t Nprm =  70;  //the number of parameters 4th order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_dia_tof32stm = NULL;
 TClonesArray *array_mass_corstm = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_trackd = NULL;
 TClonesArray *array_s0 = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("dia_tof32stm",&array_dia_tof32stm);
 tree->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("dia_tof32stm",1);
 tree->SetBranchStatus("mass_corstm_BLD_6th",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2",1);
 tree->SetBranchStatus("sr0_xcw",1);
 tree->SetBranchStatus("eventheader",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;

// ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_7step_stm_ref8.dat");
 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_7step_stm_reflise.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

  while(!fin.eof()){
	    fin.precision(10);
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
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_trackd = array_trackd->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_mass_corstm > 0 && hit_tracku > 0 && hit_trackd > 0 && hit_s0 > 0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMassData *mass_corstm_tmp = (art::TMassData*) array_mass_corstm->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_corstm_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TDiaTimingData *tof_tmp = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsGood();
     Bool_t trackd_ok = trackd_tmp->IsGood();
     Double_t ssrd = trackd_tmp->GetSSR();
//     Double_t var3d = trackd_tmp->GetVar(3) * 1000;
//     Double_t y2_tmp = trackd_tmp->GetY();

//angle gate
     Double_t a2_tmp = trackd_tmp->GetA()*1000;
     Double_t b2_tmp = trackd_tmp->GetB() * 1000;
     Double_t tofid = tof_tmp->GetID();

     Bool_t anglegate = (b2_tmp < a2_tmp*0.0933248 + 7.43125) && (b2_tmp > a2_tmp*0.0796714 + 3.04052);
     Bool_t anglegate2 = (b2_tmp < a2_tmp*0.131251 + 5.28908) && (b2_tmp > a2_tmp*0.104814 + 0.855838);

     Bool_t angle_ok = (anglegate && tofid==1) || (anglegate2 && tofid==2);

     Bool_t s2bg = TMath::Abs(b2_tmp-5)<5;


    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
//    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok && angle_ok)
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok && s2bg)
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

//const
     A(ievt,0) = 1.; 
//1st order	 
     A(ievt,1)  = x2;
     A(ievt,2)  = a2;
     A(ievt,3)  = y2;
     A(ievt,4) = b2;
//2nd order	 
     A(ievt,5) = x2 * x2;
     A(ievt,6) = a2 * a2;
     A(ievt,7) = y2 * y2;
     A(ievt,8) = b2 * b2;
     A(ievt,9) = x2 * a2;
     A(ievt,10) = x2 * y2;
     A(ievt,11) = x2 * b2;
     A(ievt,12) = a2 * y2;
     A(ievt,13) = a2 * b2;
     A(ievt,14) = y2 * b2;
//3rd order
     A(ievt,15) = x2 * x2 * x2;
     A(ievt,16) = a2 * a2 * a2;
     A(ievt,17) = y2 * y2 * y2;
     A(ievt,18) = b2 * b2 * b2;
     A(ievt,19) = x2 * x2 * a2;
     A(ievt,20) = x2 * x2 * y2;
     A(ievt,21) = x2 * x2 * b2;
     A(ievt,22) = a2 * a2 * x2;
     A(ievt,23) = a2 * a2 * y2;
     A(ievt,24) = a2 * a2 * b2;
     A(ievt,25) = y2 * y2 * x2;
     A(ievt,26) = y2 * y2 * a2;
     A(ievt,27) = y2 * y2 * b2;
     A(ievt,28) = b2 * b2 * x2;
     A(ievt,29) = b2 * b2 * a2;
     A(ievt,30) = b2 * b2 * y2;
     A(ievt,31) = x2 * a2 * y2;
     A(ievt,32) = x2 * a2 * b2;
     A(ievt,33) = x2 * y2 * b2;
     A(ievt,34) = a2 * y2 * b2;
//4th order
     A(ievt,35) = x2 * x2 * x2 * x2;
     A(ievt,36) = a2 * a2 * a2 * a2;
     A(ievt,37) = y2 * y2 * y2 * y2;
     A(ievt,38) = b2 * b2 * b2 * b2;
     A(ievt,39) = x2 * x2 * x2 * a2;
     A(ievt,40) = x2 * x2 * x2 * y2;
     A(ievt,41) = x2 * x2 * x2 * b2;
     A(ievt,42) = a2 * a2 * a2 * x2;
     A(ievt,43) = a2 * a2 * a2 * y2;
     A(ievt,44) = a2 * a2 * a2 * b2;
     A(ievt,45) = y2 * y2 * y2 * x2;
     A(ievt,46) = y2 * y2 * y2 * a2;
     A(ievt,47) = y2 * y2 * y2 * b2;
     A(ievt,48) = b2 * b2 * b2 * x2;
     A(ievt,49) = b2 * b2 * b2 * a2;
     A(ievt,50) = b2 * b2 * b2 * y2;
     A(ievt,51) = x2 * x2 * a2 * a2;
     A(ievt,52) = x2 * x2 * y2 * y2;
     A(ievt,53) = x2 * x2 * b2 * b2;
     A(ievt,54) = a2 * a2 * y2 * y2;
     A(ievt,55) = a2 * a2 * b2 * b2;
     A(ievt,56) = y2 * y2 * b2 * b2;
     A(ievt,57) = x2 * x2 * a2 * y2;
     A(ievt,58) = x2 * x2 * a2 * b2;
     A(ievt,59) = x2 * x2 * y2 * b2;
     A(ievt,60) = a2 * a2 * x2 * y2;
     A(ievt,61) = a2 * a2 * x2 * b2;
     A(ievt,62) = a2 * a2 * y2 * b2;
     A(ievt,63) = y2 * y2 * x2 * a2;
     A(ievt,64) = y2 * y2 * x2 * b2;
     A(ievt,65) = y2 * y2 * a2 * b2;
     A(ievt,66) = b2 * b2 * x2 * a2;
     A(ievt,67) = b2 * b2 * x2 * y2;
     A(ievt,68) = b2 * b2 * a2 * y2;
     A(ievt,69) = x2 * a2 * y2 * b2;


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


//// ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/set_matrix_svd4th_stm2_ref6_6step_unit2.5_SSR.dat");
// ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/set_matrix_svd4th_stm2_ref6_6step_unit2.5_SSR_posmod.dat");
// if (fout.fail()){
//	 cout << "Error; Could not open output file.." << endl << endl;
//	 return;
//  }
//
//for(int n = 0; n < Nevt; n++){
//	fout << b(n,0) << " | ";
//
//	for(int m = 0; m < Nprm; m++){
//		fout << A(n,m) << "  " ;
//	}
//	fout << "\n";
//}
//
//	fout.close();
//
//// ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_unit2.5_SSR.dat");
// ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_unit2.5_SSR_posmod.dat");
// if (foutselect.fail()){
//	 cout << "Error; Could not open output file.." << endl << endl;
//	 return;
//  }
//
//for(int n = 0; n < Nevt; n++){
//	for(int m = 0; m < 14; m++){
//		foutselect << value(n,m) << "  "  << " | ";
//	}
//	foutselect << "\n";
//}
//
//	foutselect.close();


//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_ref8_7step.hist_selected_unit2.5_SSR.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_ref8_7step.hist_selected_unit2.5_SSR.root_epsilon","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_reflise_7step.hist_selected_unit2.5_SSR_epsilon.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_reflise_7step.hist_selected_unitlise_SSR_epsilon.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_reflise_7step.hist_selected_unitlise_SSR_epsilon_angle.root","recreate");
   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_reflise_7step.hist_selected_unitlise_SSR_epsilon_s2bg.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_ref6_6step.hist_selected_unit2.5_SSR_posmod.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_ref6_6step.hist_selected_nogate.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_stm2_ref6_6step.hist_selected_ngate_sqrt.root","recreate");

  TH1D *tof_selected = new TH1D("tof_selected","tof_selected",1000,-2,2);
  TH2D *tofaq_selected = new TH2D("tofaq_selected","tofaq_selected",1000,1.8,2.15,1000,-2,2);
  TH1D *x3_selected = new TH1D("x3_selected","x3_selected",300,-2,2);
  TH2D *x3aq_selected = new TH2D("x3aq_selected","x3aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *a3_selected = new TH1D("a3_selected","a3_selected",300,-2,2);
  TH2D *a3aq_selected = new TH2D("a3aq_selected","a3aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *y3_selected = new TH1D("y3_selected","y3_selected",300,-2,2);
  TH2D *y3aq_selected = new TH2D("y3aq_selected","y3aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *b3_selected = new TH1D("b3_selected","b3_selected",300,-2,2);
  TH2D *b3aq_selected = new TH2D("b3aq_selected","b3aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *x0_selected = new TH1D("x0_selected","x0_selected",300,-2,2);
  TH2D *x0aq_selected = new TH2D("x0aq_selected","x0aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *x2_selected = new TH1D("x2_selected","x2_selected",300,-2,2);
  TH2D *x2aq_selected = new TH2D("x2aq_selected","x2aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *a2_selected = new TH1D("a2_selected","a2_selected",300,-2,2);
  TH2D *a2aq_selected = new TH2D("a2aq_selected","a2aq_selected",1000,1.8,2.15,300,-2,2);
  TH1D *y2_selected = new TH1D("y2_selected","y2_selected",300,-2,2);
  TH2D *y2aq_selected = new TH2D("y2aq_selected","y2aq_selected",1000,1.8,2.15,300,-2,2);
  TH2D *y2ssr_selected = new TH2D("y2ssr_selected","y2ssr_select5ed",300,-2,2,300,0,1);
  TH1D *b2_selected = new TH1D("b2_selected","b2_selected",300,-2,2);
  TH2D *b2aq_selected = new TH2D("b2aq_selected","b2aq_selected",1000,1.8,2.15,300,-2,2);
  TH2D *b2ssr_selected = new TH2D("b2ssr_selected","b2ssr_selected",300,-2,2,300,0,1);
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
  b2aq_selected->Fill(value(nn,1),value(nn,11));
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
 b2aq_selected->Write();
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
//   std::ofstream foutmtr("output/mass/svd4th_out_stm2_reflise_8step_unit2.5_SSR_epsilon.dat");
//   std::ofstream foutmtr("output/mass/svd4th_out_stm2_reflise_8step_unitlise_SSR_epsilon.dat");
//   std::ofstream foutmtr("output/mass/svd4th_out_stm2_reflise_8step_unitlise_SSR_epsilon_angle.dat");
   std::ofstream foutmtr("output/mass/svd4th_out_stm2_reflise_8step_unitlise_SSR_epsilon_s2bg.dat");
   foutmtr << "cond: " << svd.Condition() << endl;
   foutmtr << "det: "  << d1*TMath::Power(2, d2) << endl;
   foutmtr << "tol: " << svd.GetTol() << endl;

   foutmtr.close();

//   std::ofstream foutmtrth("output/mass/theta_stm2_reflise_8step_unit2.5_SSR_epsilon.dat");
//   std::ofstream foutmtrth("output/mass/theta_stm2_reflise_8step_unitlise_SSR_epsilon.dat");
//   std::ofstream foutmtrth("output/mass/theta_stm2_reflise_8step_unitlise_SSR_epsilon_angle.dat");
   std::ofstream foutmtrth("output/mass/theta_stm2_reflise_8step_unitlise_SSR_epsilon_s2bg.dat");
 if (foutmtrth.fail()){
	 cout << "Error; Could not open output file for Theta matrix..." << endl << endl;
	 return;
  }
for (int itheta = 0; itheta < Nprm; itheta++){
   foutmtrth.precision(10);
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
    double sum_tmp = 0.;
    double sum = 0.;

     tree->GetEntry(iData);
	 art::TDiaTimingData *dia_tof32stmcor = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku_cor = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd_cor = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0_cor = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

    Int_t hit_dia_tof32stmcor = array_dia_tof32stm->GetEntriesFast();
    Int_t hit_tracku_cor = array_tracku->GetEntriesFast();
    Int_t hit_trackd_cor = array_trackd->GetEntriesFast();
    Int_t hit_s0_cor = array_s0->GetEntriesFast();

     if ( hit_dia_tof32stmcor > 0 && hit_tracku_cor > 0 && hit_trackd_cor > 0 && hit_s0_cor >0){
 
	 art::TDiaTimingData *dia_tof32stmcor = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku_cor = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd_cor = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0_cor = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Bool_t tracku_cor_ok = tracku_cor->IsGood();
     Bool_t trackd_cor_ok = trackd_cor->IsGood();

// anglegate
     Double_t a2_cor_tmp = trackd_cor->GetA()*1000;
     Double_t b2_cor_tmp = trackd_cor->GetB()*1000;
     Double_t tofid = dia_tof32stmcor->GetID();

     Bool_t anglegate = (b2_cor_tmp < a2_cor_tmp*0.0933248 + 7.43125) && (b2_cor_tmp > a2_cor_tmp*0.0796714 + 3.04052);
     Bool_t anglegate2 = (b2_cor_tmp < a2_cor_tmp*0.131251 + 5.28908) && (b2_cor_tmp > a2_cor_tmp*0.104814 + 0.855838);

     Bool_t angle_ok = (anglegate && tofid==1) || (anglegate2 && tofid==2);

     Double_t ssrd = trackd_cor->GetSSR();

	 Bool_t s2bg = TMath::Abs(b2_cor_tmp-5)<5;

    if( tracku_cor_ok && trackd_cor_ok  && angle_ok && s2bg){

     Double_t ti_cor = dia_tof32stmcor->GetTiming();
     Double_t x3i_cor = tracku_cor->GetX();
     Double_t a3i_cor = tracku_cor->GetA() * 1000.;
     Double_t y3i_cor = tracku_cor->GetY();
     Double_t b3i_cor = tracku_cor->GetB() * 1000.;
     Double_t x0i_cor = sr0_cor->GetPosition();
     Double_t x2i_cor = trackd_cor->GetX(-49.5);
     Double_t a2i_cor = trackd_cor->GetA() * 1000.;
     Double_t y2i_cor = trackd_cor->GetY(-49.5);
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
//     Double_t b2_cor = b2i_cor * 0.05 - 0.2;

//     Double_t t_cor = (ti_cor - 2042.) * 0.025;  
//     Double_t x3_cor = x3i_cor * 0.1 + 1; 
//     Double_t a3_cor = a3i_cor * 0.1 + 1;
//     Double_t y3_cor = y3i_cor + 2 + 1;
//     Double_t b3_cor = b3i_cor * 0.05 + 0.5 +1;
//     Double_t x0_cor = x0i_cor * 0.015 + 1; 
//     Double_t x2_cor = x2i_cor * 0.1 + 1; 
//     Double_t a2_cor = a2i_cor * 0.025 + 1;
//     Double_t y2_cor = y2i_cor * 0.05 - 1 + 1;
//     Double_t b2_cor = b2i_cor * 0.05 - 0.2 + 1;

// reflise
     Double_t t_cor = ((ti_cor - 2042.) * 0.025 + 0.35) * 3;  
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
   sum_tmp += Rd(ii) * Theta(ii);
//   sum += Rd(ii) * Theta(ii);
  }

    sum = TMath::Sqrt(sum_tmp);
 	Aq_cor.push_back(sum);
    evt_valid.push_back(iData);
}else {
	continue;
}
   }else{
	   continue;
   }
}

//// Check results for selected events

 TVectorD b_re(Nevt);
// b_re = Mult(A,Theta);

for(int ic = 0; ic < Nevt; ic++ ){

 Double_t b_re_elem_tmp = 0.;
 Double_t b_re_elem = 0.;

	for(int ir = 0; ir < Nprm; ir++ ){

// 	   b_re_elem += A(ic,ir) * Theta(ir);
 	   b_re_elem_tmp += A(ic,ir) * Theta(ir);

	}

    b_re_elem = TMath::Sqrt(b_re_elem_tmp);
	b_re(ic) = b_re_elem;
}

 TH1D *h_aq_sol = new TH1D("aq_sol", "aq_sol",5000,1.7,2.3);

 TH1D *h_38Ca_sol = new TH1D("h38Ca_sol", "h38Ca_sol",5000,1.89,1.91);
 TH1D *h_39Ca_sol = new TH1D("h39Ca_sol", "h39Ca_sol",5000,1.940,1.960);
                                    
 TH1D *h_40Sc_sol = new TH1D("h40Sc_sol", "h40Sc_sol",5000,1.900,1.92);
 TH1D *h_41Sc_sol = new TH1D("h41Sc_sol", "h41Sc_sol",5000,1.945,1.965);
                                
 TH1D *h_40Ti_sol = new TH1D("h40Ti_sol", "h40Ti_sol",5000,1.81,1.83);
 TH1D *h_41Ti_sol = new TH1D("h41Ti_sol", "h41Ti_sol",5000,1.86,1.88);
 TH1D *h_42Ti_sol = new TH1D("h42Ti_sol", "h42Ti_sol",5000,1.895,1.915);
                                         
 TH1D *h_43V_sol  = new TH1D("h43V_sol", "h43V_sol",5000,1.86,1.880);
 TH1D *h_44V_sol  = new TH1D("h44V_sol", "h44V_sol",5000,1.90,1.92);
                                    
 TH1D *h_44Cr_sol = new TH1D("h44Cr_sol", "h44Cr_sol",5000,1.83,1.85);
 TH1D *h_45Cr_sol = new TH1D("h45Cr_sol", "h45Cr_sol",5000,1.865,1.885);
 TH1D *h_46Cr_sol = new TH1D("h46Cr_sol", "h46Cr_sol",5000,1.905,1.925);
                                    
 TH1D *h_46Mn_sol = new TH1D("h46Mn_sol", "h46Mn_sol",5000,1.83,1.85);
 TH1D *h_47Mn_sol = new TH1D("h47Mn_sol", "h47Mn_sol",5000,1.87,1.897);
 TH1D *h_48Mn_sol = new TH1D("h48Mn_sol", "h48Mn_sol",5000,1.91,1.930);
                                    
 TH1D *h_48Fe_sol = new TH1D("h48Fe_sol", "h48Fe_sol",5000,1.835,1.855);
 TH1D *h_49Fe_sol = new TH1D("h49Fe_sol", "h49Fe_sol",5000,1.87,1.89);

 TH1D *h_50Co_sol = new TH1D("h50Co_sol", "h50Co_sol",5000,1.84,1.86);

 TH1D *h_52Ni_sol = new TH1D("h52Ni_sol", "h52Ni_sol",5000,1.84,1.86);

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
 Int_t Nrun_19 = Nrun_18 + Nrun_ni;

 for (int isol = 0; isol < Nevt; isol++){
  h_aq_sol->Fill(b_re[isol]);
	 
	if(0 <= isol && isol  < Nrun){
	 h_38Ca_sol->Fill(b_re(isol));
 } else if(Nrun <= isol && isol  < Nrun_2){
	 h_39Ca_sol->Fill(b_re(isol));
 } else if(Nrun_2 <= isol && isol  < Nrun_3){
	 h_40Sc_sol->Fill(b_re(isol));
 } else if(Nrun_3 <= isol && isol  < Nrun_4){
	 h_41Sc_sol->Fill(b_re(isol));
 } else if(Nrun_4 <= isol && isol  < Nrun_5){
	 h_40Ti_sol->Fill(b_re(isol));
 } else if(Nrun_5 <= isol && isol  < Nrun_6){
	 h_41Ti_sol->Fill(b_re(isol));
 } else if(Nrun_6 <= isol && isol  < Nrun_7){
	 h_42Ti_sol->Fill(b_re(isol));
 } else if(Nrun_7 <= isol && isol  < Nrun_8){
	 h_43V_sol->Fill(b_re(isol));
 } else if(Nrun_8 <= isol && isol  < Nrun_9){
	 h_44V_sol->Fill(b_re(isol));
 } else if(Nrun_9 <= isol && isol  < Nrun_10){
	 h_44Cr_sol->Fill(b_re(isol));
 } else if(Nrun_10 <= isol && isol  < Nrun_11){
	 h_45Cr_sol->Fill(b_re(isol));
 } else if(Nrun_11 <= isol && isol  < Nrun_12){
	 h_46Cr_sol->Fill(b_re(isol));
 } else if(Nrun_12 <= isol && isol  < Nrun_13){
	 h_46Mn_sol->Fill(b_re(isol));
 } else if(Nrun_13 <= isol && isol  < Nrun_14){
	 h_47Mn_sol->Fill(b_re(isol));
 } else if(Nrun_14 <= isol && isol  < Nrun_15){
	 h_48Mn_sol->Fill(b_re(isol));
 } else if(Nrun_15 <= isol && isol  < Nrun_16){
	 h_48Fe_sol->Fill(b_re(isol));
 } else if(Nrun_16 <= isol && isol  < Nrun_17){
	 h_49Fe_sol->Fill(b_re(isol));
 } else if(Nrun_17 <= isol && isol  < Nrun_18){
	 h_50Co_sol->Fill(b_re(isol));
 } else if(Nrun_18 <= isol && isol  < Nrun_19){
	 h_52Ni_sol->Fill(b_re(isol));
 }
}


// Output

 TH1D *h_aq_cor = new TH1D("aq_cor", "aq_cor",5000,1.7,2.3);
 TH1D *h_aq_cor_wr = new TH1D("aq_cor_wr", "aq_cor_wr",5000,-10,10);

 TH1D *h_38Ca = new TH1D("h38Ca", "h38Ca",5000,1.89,1.91);
 TH1D *h_39Ca = new TH1D("h39Ca", "h39Ca",5000,1.940,1.960);
                                                            
 TH1D *h_40Sc = new TH1D("h40Sc", "h40Sc",5000,1.900,1.92);
 TH1D *h_41Sc = new TH1D("h41Sc", "h41Sc",5000,1.945,1.965);
                                                            
 TH1D *h_40Ti = new TH1D("h40Ti", "h40Ti",5000,1.805,1.825);
 TH1D *h_41Ti = new TH1D("h41Ti", "h41Ti",5000,1.855,1.875);
 TH1D *h_42Ti = new TH1D("h42Ti", "h42Ti",5000,1.895,1.915);
                                                            
 TH1D *h_43V  = new TH1D("h43V", "h43V",5000,1.865,1.885);
 TH1D *h_44V  = new TH1D("h44V", "h44V",5000,1.90,1.92);
                                                            
 TH1D *h_44Cr = new TH1D("h44Cr", "h44Cr",5000,1.825,1.845);
 TH1D *h_45Cr = new TH1D("h45Cr", "h45Cr",5000,1.865,1.885);
 TH1D *h_46Cr = new TH1D("h46Cr", "h46Cr",5000,1.90,1.925);
                                                           
 TH1D *h_46Mn = new TH1D("h46Mn", "h46Mn",5000,1.832,1.852);
 TH1D *h_47Mn = new TH1D("h47Mn", "h47Mn",5000,1.87,1.897);
 TH1D *h_48Mn = new TH1D("h48Mn", "h48Mn",5000,1.91,1.930);
                                                            
 TH1D *h_48Fe = new TH1D("h48Fe", "h48Fe",5000,1.8355,1.8555);
 TH1D *h_49Fe = new TH1D("h49Fe", "h49Fe",5000,1.875,1.895);

 TH1D *h_50Co = new TH1D("h50Co", "h50Co",5000,1.84,1.86);

 TH1D *h_52Ni = new TH1D("h52Ni", "h52Ni",5000,1.84,1.86);

 TH2D *h_zaq_cor = new TH2D("zaq_col", "zaq_col",1000,1.7,2.3,1000,18,30);

   Int_t Nevt_valid = evt_valid.size();

//   Double_t aq_cor_br;
//   tree->Branch("Aq_cor",&aq_cor_br,"Aq_cor/D");

  for (Int_t iData = 0; iData < Nevt_valid; iData++){

    int itmp = evt_valid[iData];
    tree->GetEntry(itmp);

     h_aq_cor->Fill(Aq_cor[iData]);
     h_aq_cor_wr->Fill(Aq_cor[iData]);

     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
     
	 Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t ssrd = trackd_tmp->GetSSR();
     Bool_t tracku_tmp_ok = tracku_tmp->IsGood();
     Bool_t trackd_tmp_ok = trackd_tmp->IsGood();
     Double_t x2 = trackd_tmp->GetX(-49.5);

// if (ssrd < 0.1){
 if (tracku_tmp_ok && trackd_tmp_ok){
      h_zaq_cor->Fill(Aq_cor[iData],z_tmpt);
//	  aq_cor_br = Aq_cor[iData];
//	  tree->Fill();

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_38Ca->Fill(Aq_cor[iData]);
      h_39Ca->Fill(Aq_cor[iData]);

 }else if(Z_low[2] < z_tmpt && z_tmpt < Z_up[2]){

      h_40Sc->Fill(Aq_cor[iData]);
      h_41Sc->Fill(Aq_cor[iData]);
 
 }else if(Z_low[4] < z_tmpt && z_tmpt < Z_up[4]){

      h_40Ti->Fill(Aq_cor[iData]);
      h_41Ti->Fill(Aq_cor[iData]);
      h_42Ti->Fill(Aq_cor[iData]);

 }else if(Z_low[7] < z_tmpt && z_tmpt < Z_up[7]){

      h_43V->Fill(Aq_cor[iData]);
      h_44V->Fill(Aq_cor[iData]);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_44Cr->Fill(Aq_cor[iData]);
      h_45Cr->Fill(Aq_cor[iData]);
      h_46Cr->Fill(Aq_cor[iData]);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_46Mn->Fill(Aq_cor[iData]);
      h_47Mn->Fill(Aq_cor[iData]);
      h_48Mn->Fill(Aq_cor[iData]);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_48Fe->Fill(Aq_cor[iData]);
      h_49Fe->Fill(Aq_cor[iData]);

 }else if(Z_low[17] < z_tmpt && z_tmpt < Z_up[17]){

      h_50Co->Fill(Aq_cor[iData]);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_52Ni->Fill(Aq_cor[iData]);

  }else {
	  continue;
  }
 }else {
	 continue;
 }

}


//// Draw original histogram

 TH1D *h_aq_cor_org = new TH1D("aq_cor_org", "aq_cor_org",5000,1.7,2.3);

 TH1D *h_38Ca_org = new TH1D("h38Ca_org", "h38Ca_org",5000,1.89,1.91);
 TH1D *h_39Ca_org = new TH1D("h39Ca_org", "h39Ca_org",5000,1.940,1.960);
                                                                        
 TH1D *h_40Sc_org = new TH1D("h40Sc_org", "h40Sc_org",5000,1.900,1.92);
 TH1D *h_41Sc_org = new TH1D("h41Sc_org", "h41Sc_org",5000,1.945,1.965);
                                                                        
 TH1D *h_40Ti_org = new TH1D("h40Ti_org", "h40Ti_org",5000,1.81,1.83);
 TH1D *h_41Ti_org = new TH1D("h41Ti_org", "h41Ti_org",5000,1.86,1.88);
 TH1D *h_42Ti_org = new TH1D("h47Ti_org", "h47Ti_org",5000,1.895,1.915);
                                                                        
 TH1D *h_43V_org = new TH1D("h43V_org", "h43V_org",5000,1.86,1.880);
 TH1D *h_44V_org = new TH1D("h44V_org", "h44V_org",5000,1.90,1.92);
                                                                        
 TH1D *h_44Cr_org = new TH1D("h44Cr_org", "h44Cr_org",5000,1.83,1.85);
 TH1D *h_45Cr_org = new TH1D("h45Cr_org", "h45Cr_org",5000,1.865,1.885);
 TH1D *h_46Cr_org = new TH1D("h46Cr_org", "h46Cr_org",5000,1.90,1.925);
                                                                  
 TH1D *h_46Mn_org = new TH1D("h46Mn_org", "h46Mn_org",5000,1.83,1.85);
 TH1D *h_47Mn_org = new TH1D("h47Mn_org", "h47Mn_org",5000,1.87,1.897);
 TH1D *h_48Mn_org = new TH1D("h48Mn_org", "h48Mn_org",5000,1.91,1.930);
                                                                        
 TH1D *h_48Fe_org = new TH1D("h48Fe_org", "h48Fe_org",5000,1.835,1.855);
 TH1D *h_49Fe_org = new TH1D("h49Fe_org", "h49Fe_org",5000,1.87,1.89);

 TH1D *h_50Co_org = new TH1D("h50Co_org", "h50Co_org",5000,1.84,1.86);

 TH1D *h_52Ni_org = new TH1D("h52Ni_org", "h52Ni_org",5000,1.84,1.86);

 TH2D *h_zaq_org = new TH2D("zaq_org", "zaq_org",1000,1.7,2.3,1000,18,30);

  for (Int_t iData = 0; iData < nData; iData++){
     tree->GetEntry(iData);
     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     art::TMassData *mass_corstm_tmpt = (art::TMassData*) array_mass_corstm->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t aq_tmpt = mass_corstm_tmpt->GetAq();
 
     h_aq_cor_org->Fill(aq_tmpt);
     h_zaq_org->Fill(aq_tmpt,z_tmpt);

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_38Ca_org->Fill(aq_tmpt);
      h_39Ca_org->Fill(aq_tmpt);

 }else if(Z_low[2] < z_tmpt && z_tmpt < Z_up[2]){

      h_40Sc_org->Fill(aq_tmpt);
      h_41Sc_org->Fill(aq_tmpt);
 
 }else if(Z_low[4] < z_tmpt && z_tmpt < Z_up[4]){

      h_40Ti_org->Fill(aq_tmpt);
      h_41Ti_org->Fill(aq_tmpt);
      h_42Ti_org->Fill(aq_tmpt);

 }else if(Z_low[7] < z_tmpt && z_tmpt < Z_up[7]){

      h_43V_org->Fill(aq_tmpt);
      h_44V_org->Fill(aq_tmpt);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_44Cr_org->Fill(aq_tmpt);
      h_45Cr_org->Fill(aq_tmpt);
      h_46Cr_org->Fill(aq_tmpt);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_46Mn_org->Fill(aq_tmpt);
      h_47Mn_org->Fill(aq_tmpt);
      h_48Mn_org->Fill(aq_tmpt);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_48Fe_org->Fill(aq_tmpt);
      h_49Fe_org->Fill(aq_tmpt);

 }else if(Z_low[17] < z_tmpt && z_tmpt < Z_up[17]){

      h_50Co_org->Fill(aq_tmpt);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_52Ni_org->Fill(aq_tmpt);

  }
 }


//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_stm2_ref7_8step_unit2.5_SSR.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_stm2_ref7_8step_unit2.5_SSR_epsilon.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_stm2_reflise_8step_unitlise_SSR_epsilon.hist.root","recreate");
 //  TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_stm2_reflise_8step_unitlise_SSR_epsilon_angle.hist.root","recreate");
   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_stm2_reflise_8step_unitlise_SSR_epsilon_s2bg.hist.root","recreate");

 h_aq_sol->Write();
 h_38Ca_sol->Write();   
 h_39Ca_sol->Write();   
 h_40Sc_sol->Write();
 h_41Sc_sol->Write();
 h_40Ti_sol->Write();
 h_41Ti_sol->Write();
 h_42Ti_sol->Write();
 h_43V_sol->Write(); 
 h_44V_sol->Write(); 
 h_44Cr_sol->Write();   
 h_45Cr_sol->Write();
 h_46Cr_sol->Write();
 h_46Mn_sol->Write();
 h_47Mn_sol->Write();
 h_48Mn_sol->Write();
 h_48Fe_sol->Write();
 h_49Fe_sol->Write();
 h_50Co_sol->Write();
 h_52Ni_sol->Write();

 h_aq_cor->Write(); 
 h_aq_cor_wr->Write();
 h_38Ca->Write(); 
 h_39Ca->Write(); 
 h_40Sc->Write(); 
 h_41Sc->Write(); 
 h_40Ti->Write(); 
 h_41Ti->Write(); 
 h_42Ti->Write(); 
 h_43V->Write(); 
 h_44V->Write(); 
 h_44Cr->Write(); 
 h_45Cr->Write(); 
 h_46Cr->Write(); 
 h_46Mn->Write(); 
 h_47Mn->Write(); 
 h_48Mn->Write(); 
 h_48Fe->Write(); 
 h_49Fe->Write(); 
 h_50Co->Write(); 
 h_52Ni->Write(); 
 h_zaq_cor->Write();

 h_aq_cor_org->Write();
 h_38Ca_org->Write();  
 h_39Ca_org->Write();  
 h_40Sc_org->Write();
 h_41Sc_org->Write();
 h_40Ti_org->Write();
 h_41Ti_org->Write();
 h_42Ti_org->Write();
 h_43V_org->Write();
 h_44V_org->Write();
 h_44Cr_org->Write();
 h_45Cr_org->Write();
 h_46Cr_org->Write();
 h_46Mn_org->Write();
 h_47Mn_org->Write();
 h_48Mn_org->Write();
 h_48Fe_org->Write();
 h_49Fe_org->Write();
 h_50Co_org->Write();
 h_52Ni_org->Write();
 h_zaq_org->Write();



 ofile->Close(); 
 

}
