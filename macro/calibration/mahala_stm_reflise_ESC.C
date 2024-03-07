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

void mahala_stm_reflise(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
  } 

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.all.root"); // Add file. Basically mass calibration file.

  const Int_t Nrun = 2000;  //the number of runs
  const Int_t Nrun_ni = 340;  //the number of runs
  const Int_t Nref =  28;  // the number of species for reference
  const Int_t Nref_pop =  19;  // the number of species for reference
  const Int_t Nevt =  (Nref - 1) * Nrun + Nrun_ni;  // the number of events

  const Int_t Nevt_pop =  (Nref_pop - 1) * Nrun + Nrun_ni;  // the number of events
  const Int_t Nevt_tgt =  Nevt;  // the number of events

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

// ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_6step_stm_ref6_forMahara.dat");
 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_6step_stm_ref6_forMahara2.dat");
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

 TMatrixD value_mahala_pop(Nevt_pop,9); // output the fitting value 
 TMatrixD value_mahala_tgt(Nevt_tgt,9); // output the fitting value 


//// Fill date 

 int ievt = 0;
 int ievt_pop = 0;
 Bool_t HasEvents = true;
 Int_t nData = tree->GetEntries();
 int Nrun_tmp;

 cout << "Start sampling" << endl;
 
for (int iref = 0; iref < Nref; iref++){
    vector<Int_t> irandm;
	int n_tmp = 0;
  if( iref != 18){  
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
     Bool_t tracku_ok = tracku_tmp->IsGood();
     Bool_t trackd_ok = trackd_tmp->IsGood();
     Double_t ssrd = trackd_tmp->GetSSR();
//     Double_t var3d = trackd_tmp->GetVar(3) * 1000;
//     Double_t y2_tmp = trackd_tmp->GetY();

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


 if( iref < Nref_pop ){
     value_mahala_pop(ievt,0) = x3;
     value_mahala_pop(ievt,1) = a3;
     value_mahala_pop(ievt,2) = y3;
     value_mahala_pop(ievt,3) = b3;
     value_mahala_pop(ievt,4) = x0;
     value_mahala_pop(ievt,5) = x2;
     value_mahala_pop(ievt,6) = a2;
     value_mahala_pop(ievt,7) = y2;
     value_mahala_pop(ievt,8) = b2;

     value_mahala_tgt(ievt,0) = x3;
     value_mahala_tgt(ievt,1) = a3;
     value_mahala_tgt(ievt,2) = y3;
     value_mahala_tgt(ievt,3) = b3;
     value_mahala_tgt(ievt,4) = x0;
     value_mahala_tgt(ievt,5) = x2;
     value_mahala_tgt(ievt,6) = a2;
     value_mahala_tgt(ievt,7) = y2;
     value_mahala_tgt(ievt,8) = b2;

     ievt_pop++;

}else {

     value_mahala_tgt(ievt,0) = x3;
     value_mahala_tgt(ievt,1) = a3;
     value_mahala_tgt(ievt,2) = y3;
     value_mahala_tgt(ievt,3) = b3;
     value_mahala_tgt(ievt,4) = x0;
     value_mahala_tgt(ievt,5) = x2;
     value_mahala_tgt(ievt,6) = a2;
     value_mahala_tgt(ievt,7) = y2;
     value_mahala_tgt(ievt,8) = b2;
 }
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


 if(ievt_pop != Nevt_pop){
	 cout << "The number of events of ievt_pop is " << ievt_pop << " Not equal to Nevt_pop " << Nevt_pop << endl;
	 return;
 }


// Standarlize popuration martix

 cout << "=== Maharanobis distance calculation ===" << endl;

 Int_t Nopt = 9;

 vector<Double_t> mean_pop(Nopt);
 vector<Double_t> var_pop(Nopt);
 vector<Double_t> sdv_pop(Nopt);
 vector<Double_t> varstand_pop(Nopt);
 TMatrixD  valuestand_pop(Nevt_pop,Nopt);
 TMatrixD  cov_pop(Nopt,Nopt);
 TMatrixD  R_pop(Nopt,Nopt);


for(int k = 0; k < Nopt; k++){
  for(int n = 0; n < Nevt_pop; n++){

   mean_pop[k] =+ value_mahala_pop(n,k) / Nevt_pop;
  
  }
}


for(int k = 0; k < Nopt; k++){
 for(int s = 0; s < Nevt_pop; s++){

 valuestand_pop(s,k) = value_mahala_pop(s,k) - mean_pop[k];

  }
}


// covariance matrix

for(int p = 0; p < Nopt; p++){
 for(int k = 0; k < Nopt; k++){
  for (int m = 0; m < Nevt_pop; m++){

	cov_pop(k,p) = valuestand_pop(m,k) * valuestand_pop(m,p);

  }
 }
}


for(int k = 0; k < Nopt; k++){
 for (int m = 0; m < Nevt_pop; m++){

   varstand_pop[k] = valuestand_pop(m,k) * valuestand_pop(m,k);
    
 }
}

// relation matrix

for(int pp = 0; pp < Nopt; pp++){
 for(int p = 0; p < Nopt; p++){
 
 R_pop(pp,p) = cov_pop(pp,p) / TMath::Sqrt( varstand_pop[pp] * varstand_pop[p] );

 } 
}

// Fill the distance to hist

 ofstream foutmahalaR("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/mahalaR_stm_reflise.dat");

for(int i = 0; i < Nopt; i++){

 foutmahalaR << R_pop(i,0) << "  "<< R_pop(i,1)  <<"  " << R_pop(i,2) << "  "  << R_pop(i,3) <<"  "<< R_pop(i,4) << "  "<< R_pop(i,5) << "  "<< R_pop(i,6) << "  "<< R_pop(i,7) << "  "<< R_pop(i,8) << "  "  << endl;

}

 TDecompSVD svd_R(R_pop);
 TMatrixD Ri = svd_R.Invert();

 TMatrixD RiR(Nopt,Nopt);
          RiR.Mult(R_pop,Ri);
   
 cout << " Popuration matrix created. " << endl;

// Standarization target matrix

 TFile *ofile = new TFile("output/mass/mahala/mahala_stm_reflise.hist.root","recreate");

for(int j = 0; j < Nref; j++){

// Standalization for target1

 int N_i;
 int N_f;

if( j < 18){
   N_i = 0 + Nrun * j;
   N_f = N_i + Nrun;
}else if( j == 18){
	N_i = Nrun * j;
	N_f = N_i + Nrun_ni;
}else{
	N_i = Nevt_pop + Nrun * (j - 19);
    N_f = N_i + Nrun;
}

 int N_leng = N_f - N_i;

 vector<Double_t> mean_1tgt(Nopt);
 vector<Double_t> var_1tgt(Nopt);
 vector<Double_t> sdv_1tgt(Nopt);
 TMatrixD  value_1tgt(N_leng,Nopt);

for(int s = N_i; s < N_f; s++){
 for (int k = 0; k < Nopt; k++){
  for(int n = N_i; n < N_f; n++){

   mean_1tgt[k] =+ value_mahala_tgt(n,k) / N_leng;

 }
 
 for(int nn = N_i; nn < N_f; nn++){

 var_1tgt[k]  =+ ( (value_mahala_tgt(nn,k) - mean_1tgt[k]) * (value_mahala_tgt(nn,k) - mean_1tgt[k]) ) / N_leng;

 } 

 sdv_1tgt[k] = TMath::Sqrt(var_1tgt[k]);

 value_1tgt(s,k) =  (value_mahala_tgt(s,k) - mean_1tgt[k]) / sdv_1tgt[k];

 }
}

 cout << Form(" Target%d matrix created.",j) << endl;

 Int_t k_fact = Nopt;

// TH1D *hmahala1 = new TH1D(Form("\"hmahala%d\",\"Mahala%d\",400,-1,3",j,j));
 TH1D *hmahala1 = new TH1D(Form("hmahala%d",j),Form("hmahala%d",j),400,1,3);

// ofstream foutmahala1tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_tgt1.dat");

 TMatrixD tgt1(Nopt,1);

for(int qq = N_i; qq < N_f; qq++){
 for(int q = 0; q < Nopt; q++){

	tgt1(q,0) = value_1tgt(qq,q);
  }
  TMatrixD tgt1t(1,Nopt);
           tgt1t.Transpose(tgt1);


 TMatrixD D1_tmp_t(tgt1t,TMatrixD::kMult,Ri);
 TMatrixD D1_tmp(D1_tmp_t,TMatrixD::kMult,tgt1);
 
  Int_t nrow1 = D1_tmp.GetNrows();
  Int_t ncol1 = D1_tmp.GetNcols();
 if( nrow1 != 1 || ncol1 != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt1" << endl;
  return;
 }else{
  Double_t D1 = D1_tmp(0,0) / k_fact;
  Double_t d1 = TMath::Sqrt(D1);

//  foutmahala1tgt << d1 << endl;
  hmahala1->Fill(d1);
  }
 }
 cout << Form("Distance Calcutation for target%d is finished.",j) << endl;

// Write matrix

 hmahala1->Write();

 delete gROOT->Get("hmahala1");

}

 ofile->Close();



}
