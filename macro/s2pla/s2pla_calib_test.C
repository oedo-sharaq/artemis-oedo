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
#include <TMinuit.h>
#endif


//void setparam(Int_t &irun, Double_t *mean, Double_t *error, Bool_t &caution){
//
// Int_t i = irun - 169;
//
//// get information of 39Ca
// TFile* file0 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.ca.hist.root");
// if(!file0){
//	 printf("Cannot open the file!\n");
//	 return;
// }
//  
//  gROOT->ProcessLine("fcd 0");
//  gROOT->ProcessLine(Form("cd %d",i));
//  TH1F *hca = (TH1F*)gROOT->FindObject(Form("plaq39ca_%d",irun));
//  Double_t Nent_ca = hca->GetEntries();
//  if (Nent_ca < 200 ){
//	  caution = 1;
//	  return;
//  }
//   mean[0] = hca->GetMean();
//   error[0] = hca->GetMeanError();
//   caution = 0; 
// file0->Close();
//
//
//// get information of 41Ti
// TFile* file1 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.ti.hist.root");
// if(!file1){
//	 printf("Cannot open the file!\n");
//	 return;
// }
//  
//  gROOT->ProcessLine("fcd 0");
//  gROOT->ProcessLine(Form("cd %d",i));
//  TH1F *hti = (TH1F*)gROOT->FindObject(Form("plaq41ti_%d",irun));
//  Double_t Nent_ti = hti->GetEntries();
//  if (Nent_ti < 200 ){
//	  caution = 1;
//	  return;
//  }
//   mean[1] = hti->GetMean();
//   error[1] = hti->GetMeanError();
//   caution = 0;
// file1->Close();
//
//
//// get information of 44V
// TFile* file2 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.v.hist.root");
// if(!file2){
//	 printf("Cannot open the file!\n");
//	 return;
// }
//  
//  gROOT->ProcessLine("fcd 0");
//  gROOT->ProcessLine(Form("cd %d",i));
//  TH1F *hv = (TH1F*)gROOT->FindObject(Form("plaq44v_%d",irun));
//  Double_t Nent_v = hv->GetEntries();
//  if (Nent_v < 200 ){
//	  caution = 1;
//	  return;
//  }
//   mean[2] = hv->GetMean();
//   error[2] = hv->GetMeanError();
//   caution = 0;
// file2->Close();
//
//// get information of 45Cr
// TFile* file3 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.cr.hist.root");
// if(!file3){
//	 printf("Cannot open the file!\n");
//	 return;
// }
//  
//  gROOT->ProcessLine("fcd 0");
//  gROOT->ProcessLine(Form("cd %d",i));
//  TH1F *hcr = (TH1F*)gROOT->FindObject(Form("plaq45cr_%d",irun));
//  Double_t Nent_cr = hcr->GetEntries();
//  if (Nent_cr < 200 ){
//	  caution = 1;
//	  return;
//  }
//   mean[3] = hcr->GetMean();
//   error[3] = hcr->GetMeanError();
//   caution = 0;
// file3->Close();
//
//
//// get information of 49Fe
// TFile* file4 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.fe.hist.root");
// if(!file4){
//	 printf("Cannot open the file!\n");
//	 return;
// }
//  
//  gROOT->ProcessLine("fcd 0");
//  gROOT->ProcessLine(Form("cd %d",i));
//  TH1F *hfe = (TH1F*)gROOT->FindObject(Form("plaq49fe_%d",irun));
//  Double_t Nent_fe = hfe->GetEntries();
//  if (Nent_fe < 200 ){
//	  caution = 1;
//	  return;
//  }
//   mean[4] = hfe->GetMean();
//   error[4] = hfe->GetMeanError();
//   caution = 0;
// file4->Close();
//
// printf("end of sampling\n"); 
//
//}


 Double_t mean[5],error[5];


void chi2(Int_t &irun, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){

 Int_t i = irun;

 const Double_t ca_ref = 377.6;
 const Double_t ti_ref = 398.5;
 const Double_t v_ref  = 414.;
 const Double_t cr_ref = 422.9;
 const Double_t fe_ref = 445.8;

 Double_t ref[5]={ca_ref,ti_ref,v_ref,cr_ref,fe_ref};
 Double_t chisq = 0.;

// Double_t mean[5];
// Double_t error[5];
// Bool_t caution;

//setparam(i,mean,error,caution);

Int_t ng = iflag;

if(ng == 1){
	f = 1e+5;
}else{

for (int i = 0; i < 5; i++){
	Double_t func = 0;

    func = par[0] + par[1] * mean[i];

	chisq += TMath::Power((ref[i] - func)/error[i],2);

  }
  f = chisq;
 }
}

int s2pla_calib_test(){

//Int_t irun = 171;
Int_t irun = 180;

// start sampling
 Int_t i = irun - 169;
 Int_t caution = 0;
// Double_t mean[5],error[5];


// get information of 39Ca
 TFile* file0 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.ca.hist.root");
 if(!file0){
	 printf("Cannot open the file!\n");
	 return 0;
 }
  
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine(Form("cd %d",i));
  TH1F *hca = (TH1F*)gROOT->FindObject(Form("plaq39ca_%d",irun));
  Double_t Nent_ca = hca->GetEntries();
  if (Nent_ca < 200 ){
	  caution = 1;
	  return 0;
  }
   mean[0] = hca->GetMean();
   error[0] = hca->GetMeanError();
   caution = 0; 
 file0->Close();


// get information of 41Ti
 TFile* file1 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.ti.hist.root");
 if(!file1){
	 printf("Cannot open the file!\n");
	 return 0;
 }
  
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine(Form("cd %d",i));
  TH1F *hti = (TH1F*)gROOT->FindObject(Form("plaq41ti_%d",irun));
  Double_t Nent_ti = hti->GetEntries();
  if (Nent_ti < 200 ){
	  caution = 1;
	  return 0;
  }
   mean[1] = hti->GetMean();
   error[1] = hti->GetMeanError();
   caution = 0;
 file1->Close();


// get information of 44V
 TFile* file2 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.v.hist.root");
 if(!file2){
	 printf("Cannot open the file!\n");
	 return 0;
 }
  
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine(Form("cd %d",i));
  TH1F *hv = (TH1F*)gROOT->FindObject(Form("plaq44v_%d",irun));
  Double_t Nent_v = hv->GetEntries();
  if (Nent_v < 200 ){
	  caution = 1;
	  return 0;
  }
   mean[2] = hv->GetMean();
   error[2] = hv->GetMeanError();
   caution = 0;
 file2->Close();

// get information of 45Cr
 TFile* file3 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.cr.hist.root");
 if(!file3){
	 printf("Cannot open the file!\n");
	 return 0;
 }
  
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine(Form("cd %d",i));
  TH1F *hcr = (TH1F*)gROOT->FindObject(Form("plaq45cr_%d",irun));
  Double_t Nent_cr = hcr->GetEntries();
  if (Nent_cr < 200 ){
	  caution = 1;
	  return 0;
  }
   mean[3] = hcr->GetMean();
   error[3] = hcr->GetMeanError();
   caution = 0;
 file3->Close();


// get information of 49Fe
 TFile* file4 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkplaq.170272.fe.hist.root");
 if(!file4){
	 printf("Cannot open the file!\n");
	 return 0;
 }
  
  gROOT->ProcessLine("fcd 0");
  gROOT->ProcessLine(Form("cd %d",i));
  TH1F *hfe = (TH1F*)gROOT->FindObject(Form("plaq49fe_%d",irun));
  Double_t Nent_fe = hfe->GetEntries();
  if (Nent_fe < 200 ){
	  caution = 1;
	  return 0;
  }
   mean[4] = hfe->GetMean();
   error[4] = hfe->GetMeanError();
   caution = 0;
 file4->Close();

 printf("end of sampling\n"); 
//// end of sampling


Double_t a, b, a_err, b_err;
Double_t f, par[2];
// dummy
Double_t gin[1];
Int_t iflag = caution;

chi2(irun,gin,f,par,iflag);
Double_t f_value = f;

cout << f << endl;

if(f_value == 1.e+5){
   a =  0; 
   b =  1;
   cout<< "The statistics is not sufficient\n" << endl;
}else{
  TMinuit *min = new TMinuit(2);
  min->SetPrintLevel(1);
  min->SetFCN(chi2);
  min->DefineParameter(0,"a",0,0.0001,-300,300);
  min->DefineParameter(1,"b",0,0.0001,-300,300);
  int migrad_stats = min->Migrad();
  min->GetParameter(0,a,a_err);
  min->GetParameter(1,b,b_err);
  cout<<"*******************************************" <<endl;
  cout<<"constant:   " << a << " +/- " << a_err <<endl;
  cout<<"first:      " << b << " +/- " << b_err <<endl;
  cout<<"Status of Migrad: "<< migrad_stats<<endl;

  delete min;
   }
 
    std::ofstream foutmtrth(Form("prm/plastic/ch2ch_%d.dat",irun));
 if (foutmtrth.fail()){
	 cout << "Error; Could not open output file..." << endl << endl;
	 return 0;
     }
   foutmtrth << a << " " << b << endl;
   foutmtrth.close();

return 0;

}




