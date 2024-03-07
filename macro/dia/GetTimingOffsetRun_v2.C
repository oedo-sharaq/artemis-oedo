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

void GetTimingOffsetRun_v2(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ti.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.

 TClonesArray *array_dia_strip = NULL;
 TClonesArray *array_dia_tof32stm = NULL;
 TClonesArray *array_mass_corstm = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("tcal_dia_strip",&array_dia_strip);
 tree->SetBranchAddress("dia_tof32stm",&array_dia_tof32stm);
 tree->SetBranchAddress("mass_corstm_BLD_6th",&array_mass_corstm);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("tcal_dia_strip",1);
 tree->SetBranchStatus("dia_tof32stm",1);
 tree->SetBranchStatus("mass_corstm_BLD_6th",1);
 tree->SetBranchStatus("eventheader",1);


 Int_t nData = tree->GetEntries();

 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/dia/F3S2StripOffsetRun_v2_1.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile *ofv = new TFile("output/dia/GetTimingOffsetRun_v2_1.root","recreate");

 const Int_t Nhist = 30;
 
 TH1D *tf3st1run[Nhist];
 TH1D *ts2st1run[Nhist];
 TH1D *ts2st2run[Nhist];
 TH1D *tofrun[Nhist];  
 TH1D *aqrun[Nhist]; 


for(int i = 0; i < 103; i++){

 Int_t run = i +170;

  tf3st1run[i] = new TH1D(Form("\"tf3st1run_%04d\"",run),Form("\"tf3st1run_%04d\"",run),300,323,330);
  ts2st1run[i] = new TH1D(Form("\"ts2st1run_%04d\"",run),Form("\"ts2st1run_%04d\"",run),300,223,227);
  ts2st2run[i] = new TH1D(Form("\"ts2st2run_%04d\"",run),Form("\"ts2st2run_%04d\"",run),300,223,227);
  tofrun[i] = new TH1D(Form("\"tofrun_%04d\"",run),Form("\"tofrun_%04d\"",run),300,2020,2030);
  aqrun[i] = new TH1D(Form("\"aqrun_%04d\"",run),Form("\"aqrun_%04d\"",run),300,1.86,1.865);
}




//for(int r = 170; r < 273; r++){
for(int r = 170; r < 200; r++){

 cout << "Start sampling Run" << r << endl; 

 Int_t j = r - 170;

//Set Histgram

//  TH2D *tf3st1run = new TH2D(Form("\"tf3st1run_%04d\",\"tf3st1run_%04d\",300,323,330,103,169.5,272.5",r));
//  TH2D *ts2st1run = new TH2D(Form("\"ts2st1run_%04d\",\"ts2st1run_%04d\",300,223,227,103,169.5,272.5",r));
//  TH2D *ts2st2run = new TH2D(Form("\"ts2st2run_%04d\",\"ts2st2run_%04d\",300,223,227,103,169.5,272.5",r));
//  TH2D *tofrun = new TH2D(Form("\"tofrun_%04d\",\"tofrun_%04d\",300,2020,2030,103,169.5,272.5",r));
//  TH2D *aqrun = new TH2D(Form("\"aqrun_%04d\",\"aqrun_%04d\",300,1.86,1.865,103,169.5,272.5",r));

//  tf3st1run[i] = new TH1D(Form("\"tf3st1run_%d\",\"tf3st1run_%d\",300,323,330",r,r));
//  tf3st1run[i] = new TH1D(Form("\"tf3st1run_%04d\"",r),Form("\"tf3st1run_%04d\"",r),300,323,330);
//  ts2st1run[i] = new TH1D(Form("\"ts2st1run_%04d\"",r),Form("\"ts2st1run_%04d\"",r),300,223,227);
//  ts2st2run[i] = new TH1D(Form("\"ts2st2run_%04d\"",r),Form("\"ts2st2run_%04d\"",r),300,223,227);
//  tofrun[i] = new TH1D(Form("\"tofrun_%04d\"",r),Form("\"tofrun_%04d\"",r),300,2020,2030);
//  aqrun[i] = new TH1D(Form("\"aqrun_%04d\"",r),Form("\"aqrun_%04d\"",r),300,1.86,1.865);


// Fill data to hist

   for(int p = 0; p < nData; p++){
     tree->GetEntry(p);
     Int_t runnum = array_eventheader->GetRunNumber();
  if(r == runnum){

//     cout  << "MelonRice&GumRice" << endl;

   Int_t hit_t_strip = array_dia_strip->GetEntriesFast();
   Int_t hit_tof = array_dia_tof32stm->GetEntriesFast();
   Int_t hit_mass_corstm = array_mass_corstm->GetEntriesFast();

 if( hit_t_strip > 0 && hit_tof > 0 && hit_mass_corstm > 0){

	 art::TDiaStripData *t_strip_f3st1 = (art::TDiaStripData*) array_dia_strip->UncheckedAt(1);
	 art::TDiaStripData *t_strip_s2st1 = (art::TDiaStripData*) array_dia_strip->UncheckedAt(3);
	 art::TDiaStripData *t_strip_s2st2 = (art::TDiaStripData*) array_dia_strip->UncheckedAt(4);
	 
	 art::TDiaTimingData *dia_tof32stm = (art::TDiaTimingData*) array_dia_tof32stm->UncheckedAt(0);
	 art::TMassData *mass_corstm = (art::TMassData*) array_mass_corstm->UncheckedAt(0);


     Double_t t3st1 = t_strip_f3st1->GetTiming();
     Double_t t2st1 = t_strip_s2st1->GetTiming();
     Double_t t2st2 = t_strip_s2st2->GetTiming();
     Double_t tof = dia_tof32stm->GetTiming();
     Double_t aq = mass_corstm->GetAq();

     tf3st1run[j]->Fill(t3st1);
     ts2st1run[j]->Fill(t2st1);
     ts2st2run[j]->Fill(t2st2);
     tofrun[j]->Fill(tof);
     aqrun[j]->Fill(aq);

  }else{
  	continue;
  }


  }else{
	  continue;
  }
 }

 cout << "Calculate mean" << endl; 

//   TH1D *h1 = (TH1D*)gROOT->FindObject("tf3st1run");
//   TH1D *h2 = (TH1D*)gROOT->FindObject("ts2st1run");
//   TH1D *h3 = (TH1D*)gROOT->FindObject("ts2st2run");
//   TH1D *h4 = (TH1D*)gROOT->FindObject("tofrun");
//   TH1D *h5 = (TH1D*)gROOT->FindObject("aqrun");

   Double_t tf3st1mean = tf3st1run[j]->GetMean();
   Double_t ts2st1mean = ts2st1run[j]->GetMean();
   Double_t ts2st2mean = ts2st2run[j]->GetMean();
   Double_t tofmean    = tofrun[j]->GetMean();
   Double_t aqmean     = aqrun[j]->GetMean();

   fout << r << "  " << tf3st1mean << "  " << ts2st1mean  << "  " << ts2st2mean << "  " << tofmean << "  " << aqmean << endl;
 
     tf3st1run[j]->Write();
     ts2st1run[j]->Write();
     ts2st2run[j]->Write();
     tofrun[j]->Write();
     aqrun[j]->Write();

 }

  ofv->Close();
  fout.close();



}
