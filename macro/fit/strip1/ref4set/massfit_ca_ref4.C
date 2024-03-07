#ifndef __CINT__
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
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


Double_t tof_func(Double_t ll, Double_t ee, Double_t zz, Double_t b, Double_t cc, Double_t x){
 

 Double_t t =  (1.e12) * ll * TMath::Sqrt(1+TMath::Power(x/(ee*zz*b*cc),2))/cc;

  return t;

}

Double_t tof_error_func(Double_t ll, Double_t ee, Double_t zz, Double_t b, Double_t cc, Double_t x){

 Double_t coeff = 1 / TMath::Power(ee*zz*b*cc,2);
 
 Double_t t_err =  (1.e12) * ll * x * coeff * TMath::Power(1 + x * x * coeff,-0.5)/cc;

  return t_err;

}


void massfit_ca_ref4(){

 const Double_t ref_38ca = 1.89826838; // A/Q
 const Double_t ref_39ca = 1.94798796; // A/Q
 const Double_t ref_41ca = 2.04756631; // A/Q
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 20;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_38ca = ref_38ca * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_39ca = ref_39ca * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_41ca = ref_41ca * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_38ca = tof_func(L,ele,z,Brho,c,mref_38ca); // [ps]
  Double_t t_ref_39ca = tof_func(L,ele,z,Brho,c,mref_39ca); // [ps]
  Double_t t_ref_41ca = tof_func(L,ele,z,Brho,c,mref_41ca); // [ps]


 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref4_fitting_st1_3step_SSR.eventstore.38ca.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref4_fitting_st1_3step_SSR.eventstore.39ca.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref4_fitting_st1_3step_SSR.eventstore.41ca.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_unit2_ref4_SSR.eventstore.170272.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

//for(int i = 170; i < 273; i++){
//
// int j = i - 169;
// 
// gROOT->ProcessLine(Form("cd %d",j));
//
// cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1D *h38ca = (TH1D*)gDirectory->Get("h38ca_aq");
 Int_t nh38ca = h38ca->GetEntries();
// if( nh39ca < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh39ca << endl;
// delete gROOT->Get("h39ca");
// }else{
 h38ca->Fit("gaus","L","",1.897,1.899);
 TF1 *f1 = h38ca->GetFunction("gaus");
 const Double_t *prm1 = f1->GetParameters();
 const Double_t *error1 = f1->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h38ca->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h38ca->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1_keV_error = error1[1] * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t mass1_error = error1[1] * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_38ca;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t t_38ca = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_38ca_error = tof_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_38ca - t_ref_38ca;
  fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout1 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh38ca << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << tdiff1 << "  " << t_38ca_error << endl;
 
 delete gROOT->Get("h38ca");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h39ca = (TH1D*)gDirectory->Get("h39ca_aq");
 Int_t nh39ca = h39ca->GetEntries();
 h39ca->Fit("gaus","L","",1.946,1.9489);
// if( nh40ca < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh40ca  << endl;
// delete gROOT->Get("h40ca");
//}else{
 TF1 *f2 = h39ca->GetFunction("gaus");
 const Double_t *prm2 = f2->GetParameters();
 const Double_t *error2 = f2->GetParErrors();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h39ca->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h39ca->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2_keV_error = error2[1] * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t mass2_error = error2[1] * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_39ca;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t t_39ca = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_39ca_error = tof_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_39ca - t_ref_39ca;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh39ca  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << tdiff2 << "  " << t_39ca_error << endl;
 
 delete gROOT->Get("h39ca");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h41ca = (TH1D*)gDirectory->Get("h41ca_aq");
 Int_t nh41ca = h41ca->GetEntries();
 h41ca->Fit("gaus","L","",2.046,2.0488);
// if( nh41ca < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh41ca <<  endl;
// delete gROOT->Get("h41ca");
//}else{
 TF1 *f3 = h41ca->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h41ca->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h41ca->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_41ca;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t t_41ca = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_41ca_error = tof_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_41ca - t_ref_41ca;
  fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh41ca << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << tdiff3 << "  " << t_41ca_error << endl;
 
 delete gROOT->Get("h41ca");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}

// gROOT->ProcessLine("cd ..");

// }

 fout1.close();
 fout2.close();
 fout3.close();

 file->Close();


}

