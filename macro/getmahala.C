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


void getmahala(){

 Double_t aq_tgt1_low = 1.767860227;  //46Fe  // lower value of A/Q for your target
 Double_t aq_tgt1_up  = 1.769759773;  //46Fe  // upper value of A/Q for your target

 Double_t aq_tgt2_low = 2.07951651; //50Cr
 Double_t aq_tgt2_up  = 2.08130349; //50Cr 

 Int_t Nref = 21;
 Int_t Nprm = 6;  // Number of paratemers for mass calibration
 Double_t k = 6.;  // Equal to Nprm
 Int_t Npop = 0;  // Number of events of the population
 Int_t Ntgt1 = 0;  // Number of events of the target
 Int_t Ntgt2 = 0;  // Number of events of the target

//// set histgram

 TH2D *tx3_tmp  = new TH2D("tx3_tmp","tx3",200,-30,30,200,1950,2400);
 TH2D *ta3_tmp  = new TH2D("ta3_tmp","ta3",200,-30,30,200,1950,2400);
 TH2D *ty3_tmp  = new TH2D("ty3_tmp","ty3",200,-30,30,200,1950,2400);
 TH2D *tb3_tmp  = new TH2D("tb3_tmp","tb3",200,-30,30,200,1950,2400);
 TH2D *tx0_tmp  = new TH2D("tx0_tmp","tx0",200,-100,100,200,1950,2400);
 TH2D *x3a3_tmp = new TH2D("x3a3_tmp","x3a3_tmp",200,-30,30,200,-30,30);
 TH2D *x3y3_tmp = new TH2D("x3y3_tmp","x3y3_tmp",200,-30,30,200,-30,30);
 TH2D *x3b3_tmp = new TH2D("x3b3_tmp","x3b3_tmp",200,-30,30,200,-30,30);
 TH2D *x3x0_tmp = new TH2D("x3x0_tmp","x3x0_tmp",200,-100,100,200,-30,30);
 TH2D *a3y3_tmp = new TH2D("a3y3_tmp","a3y3_tmp",200,-30,30,200,-30,30);
 TH2D *a3b3_tmp = new TH2D("a3b3_tmp","a3b3_tmp",200,-30,30,200,-30,30);
 TH2D *a3x0_tmp = new TH2D("a3x0_tmp","a3x0_tmp",200,-30,30,200,-30,30);
 TH2D *y3b3_tmp = new TH2D("y3b3_tmp","y3b3_tmp",200,-30,30,200,-30,30);
 TH2D *y3x0_tmp = new TH2D("y3x0_tmp","y3x0_tmp",200,-100,100,200,-30,30);
 TH2D *b3x0_tmp = new TH2D("b3x0_tmp","b3x0_tmp",200,-100,100,200,-30,30);

 vector<Double_t> t_pop, x3_pop, a3_pop, y3_pop, b3_pop, x0_pop; 
 vector<Double_t> t_pop_nor, x3_pop_nor, a3_pop_nor, y3_pop_nor, b3_pop_nor, x0_pop_nor; 
 vector<Double_t> t_tgt1, x3_tgt1, a3_tgt1, y3_tgt1, b3_tgt1, x0_tgt1; 
 vector<Double_t> t_tgt2, x3_tgt2, a3_tgt2, y3_tgt2, b3_tgt2, x0_tgt2; 

 TH2D *tx3  = new TH2D("tx3","tx3",200,-30,30,200,1950,2400);
 TH2D *ta3  = new TH2D("ta3","ta3",200,-30,30,200,1950,2400);
 TH2D *ty3  = new TH2D("ty3","ty3",200,-30,30,200,1950,2400);
 TH2D *tb3  = new TH2D("tb3","tb3",200,-30,30,200,1950,2400);
 TH2D *tx0  = new TH2D("tx0","tx0",200,-100,100,200,1950,2400);
 TH2D *x3a3 = new TH2D("x3a3","x3a3",200,-30,30,200,-30,30);
 TH2D *x3y3 = new TH2D("x3y3","x3y3",200,-30,30,200,-30,30);
 TH2D *x3b3 = new TH2D("x3b3","x3b3",200,-30,30,200,-30,30);
 TH2D *x3x0 = new TH2D("x3x0","x3x0",200,-100,100,200,-30,30);
 TH2D *a3y3 = new TH2D("a3y3","a3y3",200,-30,30,200,-30,30);
 TH2D *a3b3 = new TH2D("a3b3","a3b3",200,-30,30,200,-30,30);
 TH2D *a3x0 = new TH2D("a3x0","a3x0",200,-30,30,200,-30,30);
 TH2D *y3b3 = new TH2D("y3b3","y3b3",200,-30,30,200,-30,30);
 TH2D *y3x0 = new TH2D("y3x0","y3x0",200,-100,100,200,-30,30);
 TH2D *b3x0 = new TH2D("b3x0","b3x0",200,-100,100,200,-30,30);


//// access to tree

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.all.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }

 TClonesArray *array_mass_corst2_2nd = NULL;
 TClonesArray *array_dia_tof32st2 = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_s0 = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");
 
 tree->SetBranchAddress("mass_corst2_2nd",&array_mass_corst2_2nd);
 tree->SetBranchAddress("dia_tof32st2",&array_dia_tof32st2);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass_corst2_2nd",1);
 tree->SetBranchStatus("dia_tof32st2",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("sr0_xcw",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;

 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_2step.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

//  int i = 0;
// char come;
//  while(getline(fin,come)){
  while(!fin.eof()){
//	  if(come[0]=='#'){
//		  continue;
//	  }else{
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);

		}
//  }
 fin.close();


//// fill data

 Int_t nData = tree->GetEntries();

for (int iref = 0; iref < Nref; iref++){
 for(int idata = 0; idata < nData; idata++){
   tree->GetEntry(idata);

   Int_t hit_mass_corst2_2nd = array_mass_corst2_2nd->GetEntriesFast();
   Int_t hit_tracku = array_tracku->GetEntriesFast();
   Int_t hit_s0 = array_s0->GetEntriesFast();

  if ( hit_mass_corst2_2nd > 0 && hit_tracku > 0 && hit_s0 >0){

  art::TMassData *mass_tmp = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
  Double_t aq_tmp = mass_tmp->GetAq();

  art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
  Bool_t tracku_ok = tracku_tmp->IsProcessed();

 if(Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok)
    {
     art::TMassData *mass = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32st2 = (art::TDiaTimingData*) array_dia_tof32st2->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t tof = dia_tof32st2->GetTiming();
     Double_t x3  = tracku->GetX();
     Double_t a3_tmp  = tracku->GetA();
     Double_t y3  = tracku->GetY();
     Double_t b3_tmp  = tracku->GetB();
     Double_t x0  = sr0->GetPosition();

     Double_t a3 = a3_tmp * 1000;
     Double_t b3 = b3_tmp * 1000;

	 t_tgt1.push_back(tof);
	 x3_tgt1.push_back(x3);
	 a3_tgt1.push_back(a3);
	 y3_tgt1.push_back(y3);
	 b3_tgt1.push_back(b3);
	 x0_tgt1.push_back(x0);

     tx3->Fill(x3,tof);
     ta3->Fill(a3,tof); 
     ty3->Fill(y3,tof);
     tb3->Fill(b3,tof);
     tx0->Fill(x0,tof);
     x3a3->Fill(a3,x3); 
     x3y3->Fill(y3,x3);
     x3b3->Fill(b3,x3);
     x3x0->Fill(x0,x3);
     a3y3->Fill(y3,a3);
     a3b3->Fill(b3,a3);
     a3x0->Fill(x0,a3);
     y3b3->Fill(b3,y3);
     y3x0->Fill(x0,y3);
     b3x0->Fill(x0,b3);
    
     Npop++;

    }else{
	   continue;
	   }
  }else{
	  continue;
  }
 }
      cout << "Sampling events of Reference No." << iref << " was finished.\n";
 }


 TFile *ofile = new TFile("sh13_analysis/hanai/phys/Mahala/mahala_population_events.hist.root","recreate");
 tx3->Write();
 ta3->Write();
 ty3->Write();
 tb3->Write();
 tx0->Write();
 x3a3->Write();
 x3y3->Write();
 x3b3->Write();
 x3x0->Write();
 a3y3->Write();
 a3b3->Write();
 a3x0->Write();
 y3b3->Write();
 y3x0->Write();
 b3x0->Write();
 ofile->Close();

      cout << "Start Sampling target1 " <<endl;

 for(int idata = 0; idata < nData; idata++){
   tree->GetEntry(idata);

   Int_t hit_mass_corst2_2nd = array_mass_corst2_2nd->GetEntriesFast();
   Int_t hit_tracku = array_tracku->GetEntriesFast();
   Int_t hit_s0 = array_s0->GetEntriesFast();

  if ( hit_mass_corst2_2nd > 0 && hit_tracku > 0 && hit_s0 >0){

  art::TMassData *mass_tmp = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
  Double_t aq_tmp = mass_tmp->GetAq();

  art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
  Bool_t tracku_ok = tracku_tmp->IsProcessed();

  if(aq_tgt1_low  < aq_tmp && aq_tmp < aq_tgt1_up){
     art::TMassData *mass = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32st2 = (art::TDiaTimingData*) array_dia_tof32st2->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t tof = dia_tof32st2->GetTiming();
     Double_t x3  = tracku->GetX();
     Double_t a3_tmp  = tracku->GetA();
     Double_t y3  = tracku->GetY();
     Double_t b3_tmp  = tracku->GetB();
     Double_t x0  = sr0->GetPosition();

     Double_t a3 = a3_tmp * 1000;
     Double_t b3 = b3_tmp * 1000;


	 t_tgt1.push_back(tof);
	 x3_tgt1.push_back(x3);
	 a3_tgt1.push_back(a3);
	 y3_tgt1.push_back(y3);
	 b3_tgt1.push_back(b3);
	 x0_tgt1.push_back(x0);

	 Ntgt1++;

    }else{
	   continue;
	   }
  }else{
	  continue;
  }
 }

 cout << "Number of events of the target is " << Ntgt1 << endl;
 
 cout << "Start Sampling target2 " <<endl;

 for(int idata = 0; idata < nData; idata++){
   tree->GetEntry(idata);

   Int_t hit_mass_corst2_2nd = array_mass_corst2_2nd->GetEntriesFast();
   Int_t hit_tracku = array_tracku->GetEntriesFast();
   Int_t hit_s0 = array_s0->GetEntriesFast();

  if ( hit_mass_corst2_2nd > 0 && hit_tracku > 0 && hit_s0 >0){

  art::TMassData *mass_tmp = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
  Double_t aq_tmp = mass_tmp->GetAq();

  art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
  Bool_t tracku_ok = tracku_tmp->IsProcessed();

  if(aq_tgt2_low  < aq_tmp && aq_tmp < aq_tgt2_up){
     art::TMassData *mass = (art::TMassData*) array_mass_corst2_2nd->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32st2 = (art::TDiaTimingData*) array_dia_tof32st2->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t tof = dia_tof32st2->GetTiming();
     Double_t x3  = tracku->GetX();
     Double_t a3_tmp  = tracku->GetA();
     Double_t y3  = tracku->GetY();
     Double_t b3_tmp  = tracku->GetB();
     Double_t x0  = sr0->GetPosition();

     Double_t a3 = a3_tmp * 1000;
     Double_t b3 = b3_tmp * 1000;


	 t_tgt2.push_back(tof);
	 x3_tgt2.push_back(x3);
	 a3_tgt2.push_back(a3);
	 y3_tgt2.push_back(y3);
	 b3_tgt2.push_back(b3);
	 x0_tgt2.push_back(x0);

	 Ntgt2++;

    }else{
	   continue;
	   }
  }else{
	  continue;
  }
 }

 cout << "Number of events of the target2 is " << Ntgt2 << endl;


//// covariance
 Double_t cov_tx3 = tx3->GetCovariance();
 Double_t cov_ta3 = ta3->GetCovariance();
 Double_t cov_ty3 = ty3->GetCovariance();
 Double_t cov_tb3 = tb3->GetCovariance();
 Double_t cov_tx0 = tx0->GetCovariance();

 Double_t cov_x3a3 = x3a3->GetCovariance();
 Double_t cov_x3y3 = x3y3->GetCovariance();
 Double_t cov_x3b3 = x3b3->GetCovariance();
 Double_t cov_x3x0 = x3x0->GetCovariance();

 Double_t cov_a3y3 = a3y3->GetCovariance();
 Double_t cov_a3b3 = a3b3->GetCovariance();
 Double_t cov_a3x0 = a3x0->GetCovariance();

 Double_t cov_y3b3 = y3b3->GetCovariance();
 Double_t cov_y3x0 = y3x0->GetCovariance();

 Double_t cov_b3x0 = b3x0->GetCovariance();


//// standard deviation x-axis
 Double_t sigx_tx3  = tx3->GetStdDev(1);
 Double_t sigx_ta3  = ta3->GetStdDev(1);
 Double_t sigx_ty3  = ty3->GetStdDev(1);
 Double_t sigx_tb3  = tb3->GetStdDev(1);
 Double_t sigx_tx0  = tx0->GetStdDev(1);
                          
 Double_t sigx_x3a3 = x3a3->GetStdDev(1);
 Double_t sigx_x3y3 = x3y3->GetStdDev(1);
 Double_t sigx_x3b3 = x3b3->GetStdDev(1);
 Double_t sigx_x3x0 = x3x0->GetStdDev(1);
                          
 Double_t sigx_a3y3 = a3y3->GetStdDev(1);
 Double_t sigx_a3b3 = a3b3->GetStdDev(1);
 Double_t sigx_a3x0 = a3x0->GetStdDev(1);
                          
 Double_t sigx_y3b3 = y3b3->GetStdDev(1);
 Double_t sigx_y3x0 = y3x0->GetStdDev(1);
                          
 Double_t sigx_b3x0 = b3x0->GetStdDev(1);


//// standard deviation y-axis
 Double_t sigy_tx3  = tx3->GetStdDev(2);
 Double_t sigy_ta3  = ta3->GetStdDev(2);
 Double_t sigy_ty3  = ty3->GetStdDev(2);
 Double_t sigy_tb3  = tb3->GetStdDev(2);
 Double_t sigy_tx0  = tx0->GetStdDev(2);
                          
 Double_t sigy_x3a3 = x3a3->GetStdDev(2);
 Double_t sigy_x3y3 = x3y3->GetStdDev(2);
 Double_t sigy_x3b3 = x3b3->GetStdDev(2);
 Double_t sigy_x3x0 = x3x0->GetStdDev(2);
                          
 Double_t sigy_a3y3 = a3y3->GetStdDev(2);
 Double_t sigy_a3b3 = a3b3->GetStdDev(2);
 Double_t sigy_a3x0 = a3x0->GetStdDev(2);
                          
 Double_t sigy_y3b3 = y3b3->GetStdDev(2);
 Double_t sigy_y3x0 = y3x0->GetStdDev(2);
                          
 Double_t sigy_b3x0 = b3x0->GetStdDev(2);


//// correaltion coefficient
 Double_t corrcoeff_tx3  = cov_tx3 / (TMath::Sqrt(sigx_tx3) * TMath::Sqrt(sigy_tx3)); 
 Double_t corrcoeff_ta3  = cov_ta3 / (TMath::Sqrt(sigx_ta3) * TMath::Sqrt(sigy_ta3));
 Double_t corrcoeff_ty3  = cov_ty3 / (TMath::Sqrt(sigx_ty3) * TMath::Sqrt(sigy_ty3));
 Double_t corrcoeff_tb3  = cov_tb3 / (TMath::Sqrt(sigx_tb3) * TMath::Sqrt(sigy_tb3));
 Double_t corrcoeff_tx0  = cov_tx0 / (TMath::Sqrt(sigx_tx0) * TMath::Sqrt(sigy_tx0));
                          
 Double_t corrcoeff_x3a3 = cov_x3a3 / (TMath::Sqrt(sigx_x3a3) * TMath::Sqrt(sigy_x3a3));
 Double_t corrcoeff_x3y3 = cov_x3y3 / (TMath::Sqrt(sigx_x3y3) * TMath::Sqrt(sigy_x3y3));
 Double_t corrcoeff_x3b3 = cov_x3b3 / (TMath::Sqrt(sigx_x3b3) * TMath::Sqrt(sigy_x3b3));
 Double_t corrcoeff_x3x0 = cov_x3x0 / (TMath::Sqrt(sigx_x3x0) * TMath::Sqrt(sigy_x3x0));
                          
 Double_t corrcoeff_a3y3 = cov_a3y3 / (TMath::Sqrt(sigx_a3y3) * TMath::Sqrt(sigy_a3y3));
 Double_t corrcoeff_a3b3 = cov_a3b3 / (TMath::Sqrt(sigx_a3b3) * TMath::Sqrt(sigy_a3b3));
 Double_t corrcoeff_a3x0 = cov_a3x0 / (TMath::Sqrt(sigx_a3x0) * TMath::Sqrt(sigy_a3x0));
                        
 Double_t corrcoeff_y3b3 = cov_y3b3 / (TMath::Sqrt(sigx_y3b3) * TMath::Sqrt(sigy_y3b3));
 Double_t corrcoeff_y3x0 = cov_y3x0 / (TMath::Sqrt(sigx_y3x0) * TMath::Sqrt(sigy_y3x0));
                          
 Double_t corrcoeff_b3x0 = cov_b3x0 / (TMath::Sqrt(sigx_b3x0) * TMath::Sqrt(sigy_b3x0));

//// make variance-covariance matrix

 TMatrixD A(Nprm,Nprm);

 A(0,0) = 1.;
 A(0,1) = corrcoeff_tx3;
 A(0,2) = corrcoeff_ta3;
 A(0,3) = corrcoeff_ty3;
 A(0,4) = corrcoeff_tb3;
 A(0,5) = corrcoeff_tx0;

 A(1,0) = corrcoeff_tx3;
 A(1,1) = 1.;
 A(1,2) = corrcoeff_x3a3;
 A(1,3) = corrcoeff_x3y3;
 A(1,4) = corrcoeff_x3b3;
 A(1,5) = corrcoeff_x3x0;

 A(2,0) = corrcoeff_ta3;
 A(2,1) = corrcoeff_x3a3;
 A(2,2) = 1.;
 A(2,3) = corrcoeff_a3y3;
 A(2,4) = corrcoeff_a3b3;
 A(2,5) = corrcoeff_a3x0;

 A(3,0) = corrcoeff_ty3;
 A(3,1) = corrcoeff_x3y3;
 A(3,2) = corrcoeff_a3y3;
 A(3,3) = 1.;
 A(3,4) = corrcoeff_y3b3;
 A(3,5) = corrcoeff_y3x0;

 A(4,0) = corrcoeff_tb3;
 A(4,1) = corrcoeff_x3b3;
 A(4,2) = corrcoeff_a3b3;
 A(4,3) = corrcoeff_y3b3;
 A(4,4) = 1.;
 A(4,5) = corrcoeff_b3x0;

 A(5,0) = corrcoeff_tx0;
 A(5,1) = corrcoeff_x3x0;
 A(5,2) = corrcoeff_a3x0;
 A(5,3) = corrcoeff_y3x0;
 A(5,4) = corrcoeff_b3x0;
 A(5,5) = 1.;


 TDecompSVD svd(A);

// TMatrixD Ai(Nprm,Nprm);
//          Ai = A.Invert();
 TMatrixD Ai= svd.Invert();

// TMatrixD Ai(Nprm,Nprm);
//          Ai = A.Invert();

 TMatrixD AiA(Nprm,Nprm);
          AiA.Mult(A,Ai);

 cout << "Matrix A " << endl;
 A.Print();


 cout << "Matrix A inverse (Ai)  " << endl;
 Ai.Print();


 cout << "Matrix A times Ai  " << endl;
 AiA.Print();
 
//// Calculate Mahalanobis distance

 TH1D *hmahala1 = new TH1D("hmahala1","hmahala1",500,0.,450.);
 TH1D *hmahala2 = new TH1D("hmahala2","hmahala2",500,0.,450.);

for(int itgt = 0; itgt < Ntgt1; itgt++){
/// set target vector 

 TMatrixD b(Nprm,1);
   
   b(0,0) = t_tgt1[itgt];
   b(1,0) = x3_tgt1[itgt];
   b(2,0) = a3_tgt1[itgt];
   b(3,0) = y3_tgt1[itgt];
   b(4,0) = b3_tgt1[itgt];
   b(5,0) = x0_tgt1[itgt];

 TMatrixD bt(1,Nprm);
          bt.Transpose(b);

//// calculate Mahatanov distance

 TMatrixD D_tmp_t(bt,TMatrixD::kMult,Ai);
 TMatrixD D_tmp(D_tmp_t,TMatrixD::kMult,b);
 
 Int_t nrow = D_tmp.GetNrows();
 Int_t ncol = D_tmp.GetNcols();
if( nrow != 1 || ncol != 1 ){
  cout << "Error! Something wrong in matrix calculation" << endl;
 return;
}else{
 Double_t D = D_tmp(0,0) / k;
 Double_t d = TMath::Sqrt(D);

 hmahala1->Fill(d);
 }
}

 cout << "Calcutation for target1 is finished" << endl;

for(int itgt = 0; itgt < Ntgt2; itgt++){
/// set target vector 

 TMatrixD b2(Nprm,1);
   
   b2(0,0) = t_tgt2[itgt];
   b2(1,0) = x3_tgt2[itgt];
   b2(2,0) = a3_tgt2[itgt];
   b2(3,0) = y3_tgt2[itgt];
   b2(4,0) = b3_tgt2[itgt];
   b2(5,0) = x0_tgt2[itgt];

 TMatrixD b2t(1,Nprm);
          b2t.Transpose(b2);

//// calculate Mahatanov distance

 TMatrixD D_tmp_t(b2t,TMatrixD::kMult,Ai);
 TMatrixD D_tmp(D_tmp_t,TMatrixD::kMult,b2);
 
 Int_t nrow = D_tmp.GetNrows();
 Int_t ncol = D_tmp.GetNcols();
if( nrow != 1 || ncol != 1 ){
  cout << "Error! Something wrong in matrix calculation" << endl;
 return;
}else{
 Double_t D = D_tmp(0,0) / k;
 Double_t d = TMath::Sqrt(D);

 hmahala2->Fill(d);
 }
}

 cout << "Calcutation for target2 is finished" << endl;




}

