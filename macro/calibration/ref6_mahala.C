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

void ref6_mahala(){

// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/mass_cor_maxz/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_5step_ref6.eventstore.170272.all.root"); // Add file. Basically mass calibration file.


  const Int_t Nrun = 1000;  //the number of runs
  const Int_t Nref =  25;  // the number of species for reference
  const Int_t Nref_pop =  20;  // the number of species for reference
  const Int_t Nref_tgt =  Nref - Nref_pop;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nevt_pop =  Nref_pop * Nrun;  // the number of events
  const Int_t Nevt_tgt =  Nref_tgt * Nrun;  // the number of events
  const Int_t Nprm =  1001;  //the number of parameters 4th order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_dia_tof32stm = NULL;
 TClonesArray *array_mass_corstm = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_trackd = NULL;
 TClonesArray *array_s0 = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass_maxz",&array_mass);
 tree->SetBranchAddress("dia_tof32stm",&array_dia_tof32stm);
 tree->SetBranchAddress("mass_corstm_BLD_6th_maxz",&array_mass_corstm);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("s2_a",&array_trackd);
 tree->SetBranchAddress("sr0_xcw_qcal",&array_s0);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_maxz",1);
 tree->SetBranchStatus("dia_tof32stm",1);
 tree->SetBranchStatus("mass_corstm_BLD_6th_maxz",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2_a",1);
 tree->SetBranchStatus("sr0_xcw_qcal",1);
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

 TMatrixD A(Nevt_pop,Nprm);
 TMatrixD b(Nevt_pop,1);
 TMatrixD value(Nevt_pop,14); // output the fitting value 
 TMatrixD value_mahala_pop(Nevt_pop,10); // output the fitting value 
 TMatrixD value_mahala_tgt1(Nrun,10); // output the fitting value 
 TMatrixD value_mahala_tgt2(Nrun,10); // output the fitting value 
 TMatrixD value_mahala_tgt3(Nrun,10); // output the fitting value 
 TMatrixD value_mahala_tgt4(Nrun,10); // output the fitting value 
 TMatrixD value_mahala_tgt5(Nrun,10); // output the fitting value 

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
    Int_t itgt1 = 0;
    Int_t itgt2 = 0;
    Int_t itgt3 = 0;
    Int_t itgt4 = 0;
    Int_t itgt5 = 0;

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
     Double_t a2_tmp = trackd_tmp->GetA() * 1000;
     Double_t b2_tmp = trackd_tmp->GetB() * 1000;
     Double_t tofid = tof_tmp->GetID();

     Bool_t anglegate = (b2_tmp < a2_tmp*0.0933248 + 7.43125) && (b2_tmp > a2_tmp*0.0796714 + 3.04052);
     Bool_t anglegate2 = (b2_tmp < a2_tmp*0.131251 + 5.28908) && (b2_tmp > a2_tmp*0.104814 + 0.855838);

     Bool_t angleok = (anglegate && tofid==1) || (anglegate2 && tofid==2);

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok && angleok)
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

// angle gate
//
     Double_t t = (ti - 2042.) * 0.03125;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1 + 0.2;
     Double_t y3 = y3i * 0.6 + 1.2;
     Double_t b3 = b3i * 0.05 + 0.5;
     Double_t x0 = x0i * 0.015; 
     Double_t x2 = x2i * 0.1 + 0.3; 
     Double_t a2 = a2i * 0.025;
     Double_t y2 = y2i * 0.15 - 3.;
     Double_t b2 = b2i * 0.15 - 0.6;



if ( iref < Nref_pop){

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

}else if( iref == 20){
 
     value_mahala_tgt1(itgt1,0) = t;
     value_mahala_tgt1(itgt1,1) = x3;
     value_mahala_tgt1(itgt1,2) = a3;
     value_mahala_tgt1(itgt1,3) = y3;
     value_mahala_tgt1(itgt1,4) = b3;
     value_mahala_tgt1(itgt1,5) = x0;
     value_mahala_tgt1(itgt1,6) = x2;
     value_mahala_tgt1(itgt1,7) = a2;
     value_mahala_tgt1(itgt1,8) = y2;
     value_mahala_tgt1(itgt1,9) = b2;
   
     itgt1++;

}else if(iref == 21){

     value_mahala_tgt2(itgt2,0) = t;
     value_mahala_tgt2(itgt2,1) = x3;
     value_mahala_tgt2(itgt2,2) = a3;
     value_mahala_tgt2(itgt2,3) = y3;
     value_mahala_tgt2(itgt2,4) = b3;
     value_mahala_tgt2(itgt2,5) = x0;
     value_mahala_tgt2(itgt2,6) = x2;
     value_mahala_tgt2(itgt2,7) = a2;
     value_mahala_tgt2(itgt2,8) = y2;
     value_mahala_tgt2(itgt2,9) = b2;

     itgt2++;

}else if(iref ==22){

     value_mahala_tgt3(itgt3,0) = t;
     value_mahala_tgt3(itgt3,1) = x3;
     value_mahala_tgt3(itgt3,2) = a3;
     value_mahala_tgt3(itgt3,3) = y3;
     value_mahala_tgt3(itgt3,4) = b3;
     value_mahala_tgt3(itgt3,5) = x0;
     value_mahala_tgt3(itgt3,6) = x2;
     value_mahala_tgt3(itgt3,7) = a2;
     value_mahala_tgt3(itgt3,8) = y2;
     value_mahala_tgt3(itgt3,9) = b2;

     itgt3++;

}else if(iref == 23){

     value_mahala_tgt4(itgt4,0) = t;
     value_mahala_tgt4(itgt4,1) = x3;
     value_mahala_tgt4(itgt4,2) = a3;
     value_mahala_tgt4(itgt4,3) = y3;
     value_mahala_tgt4(itgt4,4) = b3;
     value_mahala_tgt4(itgt4,5) = x0;
     value_mahala_tgt4(itgt4,6) = x2;
     value_mahala_tgt4(itgt4,7) = a2;
     value_mahala_tgt4(itgt4,8) = y2;
     value_mahala_tgt4(itgt4,9) = b2;

     itgt4++;

}else if(iref == 24){

     value_mahala_tgt5(itgt5,0) = t;
     value_mahala_tgt5(itgt5,1) = x3;
     value_mahala_tgt5(itgt5,2) = a3;
     value_mahala_tgt5(itgt5,3) = y3;
     value_mahala_tgt5(itgt5,4) = b3;
     value_mahala_tgt5(itgt5,5) = x0;
     value_mahala_tgt5(itgt5,6) = x2;
     value_mahala_tgt5(itgt5,7) = a2;
     value_mahala_tgt5(itgt5,8) = y2;
     value_mahala_tgt5(itgt5,9) = b2;

     itgt5++;

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

 ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_pop.dat");
 if (foutselect.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt_pop; n++){
	for(int m = 0; m < 10; m++){
		foutselect << value_mahala_pop(n,m) << "  "  << " | ";
	}
	foutselect << "\n";
}

	foutselect.close();

 ofstream foutselect_tgt1("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_tgt1.dat");
 if (foutselect_tgt1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nrun; n++){
	for(int m = 0; m < 10; m++){
		foutselect_tgt1 << value_mahala_tgt1(n,m) << "  "  << " | ";
	}
	foutselect_tgt1 << "\n";
}

	foutselect_tgt1.close();

 ofstream foutselect_tgt2("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_tgt2.dat");
 if (foutselect_tgt2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nrun; n++){
	for(int m = 0; m < 10; m++){
		foutselect_tgt2 << value_mahala_tgt2(n,m) << "  "  << " | ";
	}
	foutselect_tgt2 << "\n";
}

	foutselect_tgt2.close();

 ofstream foutselect_tgt3("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_tgt3.dat");
 if (foutselect_tgt3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nrun; n++){
	for(int m = 0; m < 10; m++){
		foutselect_tgt3 << value_mahala_tgt3(n,m) << "  "  << " | ";
	}
	foutselect_tgt3 << "\n";
}

	foutselect_tgt3.close();

 ofstream foutselect_tgt4("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_tgt4.dat");
 if (foutselect_tgt4.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nrun; n++){
	for(int m = 0; m < 10; m++){
		foutselect_tgt4 << value_mahala_tgt4(n,m) << "  "  << " | ";
	}
	foutselect_tgt4 << "\n";
}

	foutselect_tgt4.close();

 ofstream foutselect_tgt5("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_stm2_ref6_6step_Mahara_tgt5.dat");
 if (foutselect_tgt5.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nrun; n++){
	for(int m = 0; m < 10; m++){
		foutselect_tgt5 << value_mahala_tgt5(n,m) << "  "  << " | ";
	}
	foutselect_tgt5 << "\n";
}

	foutselect_tgt5.close();



// Standarlize popuration martix

 cout << "=== Maharanobis distance calculation ===" << endl;

 Int_t Nopt = 10;

 vector<Double_t> mean_pop(Nopt);
 vector<Double_t> var_pop(Nopt);
 vector<Double_t> sdv_pop(Nopt);
 vector<Double_t> varstand_pop(Nopt);
 TMatrixD  valuestand_pop(Nevt_pop,Nopt);
 TMatrixD  cov_pop(Nopt,Nopt);
 TMatrixD  R_pop(Nopt,Nopt);


// ofstream foutmeanpop("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/value_selected_svd4th_stm2_ref6_6step_unit2.5_SSR_Mahala2_mean_pop.dat");
// ofstream foutvarpop("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/value_selected_svd4th_stm2_ref6_6step_unit2.5_SSR_Mahala2_value_pop.dat");

//for(int s = 0; s < Nevt_pop; s++){
// for(int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nevt_pop; n++){
//
//   mean_pop[k] =+ value_mahala_pop(n,k) / Nevt_pop;
//  
//  }
// 
// for(int nn = 0; nn < Nevt_pop; nn++){
//
// var_pop[k]  =+ ( (value_mahala_pop(nn,k) - mean_pop[k]) * (value_mahala_pop(nn,k) - mean_pop[k]) ) / Nevt_pop;
//
//  }
//
// sdv_pop[k] = TMath::Sqrt(var_pop[k]);
//
// valuestand_pop(s,k) =  (value_mahala_pop(s,k) - mean_pop[k]) / sdv_pop[k];
//
//  if(s==0){
//   foutmeanpop << mean_pop[k] << endl;
//   foutvarpop  << var_pop[k] << endl;
//  }
//
// }
//}

/////// R matrix old //////
//for(int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nevt_pop; n++){
//
//   mean_pop[k] =+ value_mahala_pop(n,k) / Nevt_pop;
//  
//  }
//}
//
//
//for(int k = 0; k < Nopt; k++){
// for(int s = 0; s < Nevt_pop; s++){
//
// valuestand_pop(s,k) = value_mahala_pop(s,k) - mean_pop[k];
//
//  }
//}
//
//
//// covariance matrix
//
//for(int p = 0; p < Nopt; p++){
// for(int k = 0; k < Nopt; k++){
//  for (int m = 0; m < Nevt_pop; m++){
//
//	cov_pop(k,p) = valuestand_pop(m,k) * valuestand_pop(m,p);
//
//  }
// }
//}
//
//
//for(int k = 0; k < Nopt; k++){
// for (int m = 0; m < Nevt_pop; m++){
//
//   varstand_pop[k] = valuestand_pop(m,k) * valuestand_pop(m,k);
//    
// }
//}
//
//
//// relation matrix
//
//for(int pp = 0; pp < Nopt; pp++){
// for(int p = 0; p < Nopt; p++){
// 
// R_pop(pp,p) = cov_pop(pp,p) / TMath::Sqrt( varstand_pop[pp] * varstand_pop[p] );
//
// } 
//}


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

for(int k = 0; k < Nevt_pop; k++){

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

  TFile *ofv = new TFile("sh13_analysis/hanai/output/Mahala_correlation.hist.root","recreate");

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


 ofstream foutmahalaR("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_Rmatrix.dat");

for(int i = 0; i < Nopt; i++){

 foutmahalaR << R_pop(i,0) << "  "<< R_pop(i,1)  <<"  " << R_pop(i,2) << "  "  << R_pop(i,3) <<"  "<< R_pop(i,4) << "  "<< R_pop(i,5) << "  "<< R_pop(i,6) << "  "<< R_pop(i,7) << "  "<< R_pop(i,8) << "  " << R_pop(i,9) << endl;

}

 TDecompSVD svd_R(R_pop);
 TMatrixD Ri = svd_R.Invert();

 TMatrixD RiR(Nopt,Nopt);
          RiR.Mult(R_pop,Ri);
   
 cout << " Popuration matrix created. " << endl;

// Standarization target matrix

 vector<Double_t> mean_1tgt(Nopt);
 vector<Double_t> var_1tgt(Nopt);
 vector<Double_t> sdv_1tgt(Nopt);
 TMatrixD  value_1tgt(Nrun,Nopt);

 vector<Double_t> mean_2tgt(Nopt);
 vector<Double_t> var_2tgt(Nopt);
 vector<Double_t> sdv_2tgt(Nopt);
 TMatrixD  value_2tgt(Nrun,Nopt);

 vector<Double_t> mean_3tgt(Nopt);
 vector<Double_t> var_3tgt(Nopt);
 vector<Double_t> sdv_3tgt(Nopt);
 TMatrixD  value_3tgt(Nrun,Nopt);

 vector<Double_t> mean_4tgt(Nopt);
 vector<Double_t> var_4tgt(Nopt);
 vector<Double_t> sdv_4tgt(Nopt);
 TMatrixD  value_4tgt(Nrun,Nopt);

 vector<Double_t> mean_5tgt(Nopt);
 vector<Double_t> var_5tgt(Nopt);
 vector<Double_t> sdv_5tgt(Nopt);
 TMatrixD  value_5tgt(Nrun,Nopt);

 Int_t Ntgt1 =  Nrun;
 Int_t Ntgt2 =  2 * Nrun;
 Int_t Ntgt3 =  3 * Nrun;
 Int_t Ntgt4 =  4 * Nrun;
 Int_t Ntgt5 =  5 * Nrun;

//// Standalization for target1
//
//for(int s = 0; s < Nrun; s++){
// for (int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nrun; n++){
//
//   mean_1tgt[k] =+ value_mahala_tgt1(n,k) / Nrun;
//
// }
// 
// for(int nn = 0; nn < Ntgt1; nn++){
//
// var_1tgt[k]  =+ ( (value_mahala_tgt1(nn,k) - mean_1tgt[k]) * (value_mahala_tgt1(nn,k) - mean_1tgt[k]) ) / Nrun;
//
// } 
//
// sdv_1tgt[k] = TMath::Sqrt(var_1tgt[k]);
//
// value_1tgt(s,k) =  (value_mahala_tgt1(s,k) - mean_1tgt[k]) / sdv_1tgt[k];
//
// }
//}
//
//// Standalization for target2
//
//for(int s = 0; s < Nrun; s++){
// for (int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nrun; n++){
//
//   mean_2tgt[k] =+ value_mahala_tgt2(n,k) / Nrun;
//
// }
// 
// for(int nn = 0; nn < Nrun; nn++){
//
// var_2tgt[k]  =+ ( (value_mahala_tgt2(nn,k) - mean_2tgt[k]) * (value_mahala_tgt2(nn,k) - mean_2tgt[k]) ) / Nrun;
//
// }
//
//
// sdv_2tgt[k] = TMath::Sqrt(var_2tgt[k]);
//
// value_2tgt(s,k) =  (value_mahala_tgt2(s,k) - mean_2tgt[k]) / sdv_2tgt[k];
//
// }
//}
//
//
//// Standalization for target3
//
//for(int s = 0; s < Nrun; s++){
// for (int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nrun; n++){
//
//   mean_3tgt[k] =+ value_mahala_tgt3(n,k) / Nrun;
//
// }
// 
// for(int nn = 0; nn < Nrun; nn++){
//
// var_3tgt[k]  =+ ( (value_mahala_tgt3(nn,k) - mean_3tgt[k]) * (value_mahala_tgt3(nn,k) - mean_3tgt[k]) ) / Nrun;
//
// }
//
//
// sdv_3tgt[k] = TMath::Sqrt(var_3tgt[k]);
//
// value_3tgt(s,k) =  (value_mahala_tgt3(s,k) - mean_3tgt[k]) / sdv_3tgt[k];
//
// }
//}
//
//// Standalization for target4
//
//for(int s = 0; s < Nrun; s++){
// for (int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nrun; n++){
//
//   mean_4tgt[k] =+ value_mahala_tgt4(n,k) / Nrun;
//
// }
// 
// for(int nn = 0; nn < Nrun; nn++){
//
// var_4tgt[k]  =+ ( (value_mahala_tgt4(nn,k) - mean_4tgt[k]) * (value_mahala_tgt4(nn,k) - mean_4tgt[k]) ) / Nrun;
//
// }
//
//
// sdv_4tgt[k] = TMath::Sqrt(var_4tgt[k]);
//
// value_4tgt(s,k) =  (value_mahala_tgt4(s,k) - mean_4tgt[k]) / sdv_4tgt[k];
//
// }
//}
//
//// Standalization for target5
//
//for(int s = 0; s < Nrun; s++){
// for (int k = 0; k < Nopt; k++){
//  for(int n = 0; n < Nrun; n++){
//
//   mean_5tgt[k] =+ value_mahala_tgt5(n,k) / Nrun;
//
// }
// 
// for(int nn = 0; nn < Nrun; nn++){
//
// var_5tgt[k]  =+ ( (value_mahala_tgt5(nn,k) - mean_5tgt[k]) * (value_mahala_tgt5(nn,k) - mean_5tgt[k]) ) / Nrun;
//
// }
//
//
// sdv_5tgt[k] = TMath::Sqrt(var_5tgt[k]);
//
// value_5tgt(s,k) =  (value_mahala_tgt5(s,k) - mean_5tgt[k]) / sdv_5tgt[k];
//
// }
//}
//
//
// cout << " Target matrix created. " << endl;

// Fill the distance to hist

// ofstream foutmahalaR("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_Rinv.dat");
//
//for(int i = 0; i < Nopt; i++){
//
// foutmahalaR << R_pop(i,0) << "  "<< R_pop(i,1)  <<"  " << R_pop(i,2) << "  "  << R_pop(i,3) <<"  "<< R_pop(i,4) << "  "<< R_pop(i,5) << "  "<< R_pop(i,6) << "  "<< R_pop(i,7) << "  "<< R_pop(i,8) << "  " << R_pop(i,9) << endl;
//
//}

 Int_t k_fact = Nopt;

 TH1D *hmahala1 = new TH1D("hmahala1","Mahala 41Ca",1000,0,10);

 ofstream foutmahala1tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_tgt1.dat");

 TMatrixD tgt1(Nopt,1);

for(int qq = 0; qq < Nrun; qq++){
 for(int q = 0; q < Nopt; q++){

//	tgt1(q,0) = value_1tgt(qq,q);
	tgt1(q,0) = value_mahala_tgt1(qq,q);
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

  foutmahala1tgt << d1 << endl;
  hmahala1->Fill(d1);
  }
// }
}
 cout << "Distance Calcutation for target1 is finished." << endl;


 TH1D *hmahala2 = new TH1D("hmahala2","Mahara 43Sc",1000,0,10);
 ofstream foutmahala2tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_tgt2.dat");

 TMatrixD tgt2(Nopt,1);

for(int qq = 0; qq < Nrun; qq++){
 for(int q = 0; q < Nopt; q++){

//	tgt2(q,0) = value_2tgt(qq,q);
	tgt2(q,0) = value_mahala_tgt2(qq,q);
  }
 TMatrixD tgt2t(1,Nopt);
          tgt2t.Transpose(tgt2);

 TMatrixD D2_tmp_t(tgt2t,TMatrixD::kMult,Ri);
 TMatrixD D2_tmp(D2_tmp_t,TMatrixD::kMult,tgt2);
 
  Int_t nrow2 = D2_tmp.GetNrows();
  Int_t ncol2 = D2_tmp.GetNcols();
 if( nrow2 != 1 || ncol2 != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt2" << endl;
  return;
 }else{
  Double_t D2 = D2_tmp(0,0) / k_fact;
  Double_t d2 = TMath::Sqrt(D2);

  foutmahala2tgt << d2 << endl;
  hmahala2->Fill(d2);
  }
// }
}

 cout << "Distance Calcutation for target2 is finished." << endl;


 TH1D *hmahala3 = new TH1D("hmaraha2","Mahara 46V",1000,0,10);
 ofstream foutmahala3tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_tgt3.dat");

 TMatrixD tgt3(Nopt,1);

for(int qq = 0; qq < Nrun; qq++){
 for(int q = 0; q < Nopt; q++){

//	tgt3(q,0) = value_3tgt(qq,q);
	tgt3(q,0) = value_mahala_tgt3(qq,q);
  }
 TMatrixD tgt3t(1,Nopt);
          tgt3t.Transpose(tgt3);

 TMatrixD D3_tmp_t(tgt3t,TMatrixD::kMult,Ri);
 TMatrixD D3_tmp(D3_tmp_t,TMatrixD::kMult,tgt3);
 
  Int_t nrow3 = D3_tmp.GetNrows();
  Int_t ncol3 = D3_tmp.GetNcols();
 if( nrow3 != 1 || ncol3 != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt3" << endl;
  return;
 }else{
  Double_t D3 = D3_tmp(0,0) / k_fact;
  Double_t d3 = TMath::Sqrt(D3);

  foutmahala3tgt << d3 << endl;
  hmahala3->Fill(d3);
  }
// }
}

 cout << "Distance Calcutation for target3 is finished." << endl;


 TH1D *hmahala4 = new TH1D("hmaraha4","Mahara 47V",1000,0,10);
 ofstream foutmahala4tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_tgt4.dat");

 TMatrixD tgt4(Nopt,1);

for(int qq = 0; qq < Nrun; qq++){
 for(int q = 0; q < Nopt; q++){

//	tgt4(q,0) = value_4tgt(qq,q);
	tgt4(q,0) = value_mahala_tgt4(qq,q);
  }
 TMatrixD tgt4t(1,Nopt);
          tgt4t.Transpose(tgt4);

 TMatrixD D4_tmp_t(tgt4t,TMatrixD::kMult,Ri);
 TMatrixD D4_tmp(D4_tmp_t,TMatrixD::kMult,tgt4);
 
  Int_t nrow4 = D4_tmp.GetNrows();
  Int_t ncol4 = D4_tmp.GetNcols();
 if( nrow4 != 1 || ncol4 != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt4" << endl;
  return;
 }else{
  Double_t D4 = D4_tmp(0,0) / k_fact;
  Double_t d4 = TMath::Sqrt(D4);

  foutmahala4tgt << d4 << endl;
  hmahala4->Fill(d4);
  }
// }
}

 cout << "Distance Calcutation for target4 is finished." << endl;


 TH1D *hmahala5 = new TH1D("hmaraha5","Mahara 51Cr",1000,0,10);
 ofstream foutmahala5tgt("/home/sh13/art_analysis/user/hanai/prm/mass/mahala/stm2_ref6_6step_Mahala_angle_tgt5.dat");

 TMatrixD tgt5(Nopt,1);

for(int qq = 0; qq < Nrun; qq++){
 for(int q = 0; q < Nopt; q++){

//	tgt5(q,0) = value_5tgt(qq,q);
	tgt5(q,0) = value_mahala_tgt5(qq,q);
  }
 TMatrixD tgt5t(1,Nopt);
          tgt5t.Transpose(tgt5);

 TMatrixD D5_tmp_t(tgt5t,TMatrixD::kMult,Ri);
 TMatrixD D5_tmp(D5_tmp_t,TMatrixD::kMult,tgt5);
 
  Int_t nrow5 = D5_tmp.GetNrows();
  Int_t ncol5 = D5_tmp.GetNcols();
 if( nrow5 != 1 || ncol5 != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt5" << endl;
  return;
 }else{
  Double_t D5 = D5_tmp(0,0) / k_fact;
  Double_t d5 = TMath::Sqrt(D5);

  foutmahala5tgt << d5 << endl;
  hmahala5->Fill(d5);
  }
// }
}

 cout << "Distance Calcutation for target5 is finished." << endl;

// Write matrix

 TFile *ofile = new TFile("output/mass/mahala/mahala_stm2_6step_ref6_angle.hist.root","recreate");
 hmahala1->Write();
 hmahala2->Write();
 hmahala3->Write();
 hmahala4->Write();
 hmahala5->Write();

 ofile->Close();

////// Set Matrix
//////
// TMatrixD At(Nprm,Nevt_pop);
//          At.Transpose(A);
//
//  TMatrixD Cov(Nprm,Nprm);
//  Cov.Mult(At,A);
//
//  TMatrixD Atb(Nprm,1);
//  Atb.Mult(At,b);
//
//  TVectorD Atb_v = TMatrixDColumn(Atb,0);
//  
////// Solve Normal Equation
//
//  TDecompSVD svd(Cov);
//  Bool_t ok;
//
//  TVectorD Theta(Nprm);
//  Theta = svd.Solve(Atb_v,ok);
//
//
////// Save the results of SVD
//  Double_t d1, d2;
//  svd.Det(d1,d2);
//  cout << "cond: " << svd.Condition() << endl;
//  cout << "det: "  << d1*TMath::Power(2, d2) << endl;
//  cout << "tol: " << svd.GetTol() << endl;
//  Theta.Print();
//
//   char foutname[50];
//   std::ofstream foutmtr("output/mass/svd4th_out_stm2_ref6_6step_angle_Mahara2.dat");
//   foutmtr << "cond: " << svd.Condition() << endl;
//   foutmtr << "det: "  << d1*TMath::Power(2, d2) << endl;
//   foutmtr << "tol: " << svd.GetTol() << endl;
//
//   foutmtr.close();
//
//   std::ofstream foutmtrth("output/mass/theta_stm2_ref6_6step_angle_Mahara2.dat");
// if (foutmtrth.fail()){
//	 cout << "Error; Could not open output file for Theta matrix..." << endl << endl;
//	 return;
//  }
//for (int itheta = 0; itheta < Nprm; itheta++){
//   foutmtrth <<  Theta(itheta) << endl;
//}
//   foutmtrth.close();




}
