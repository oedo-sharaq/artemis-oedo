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

void massfit_fe_ref(){

 const Double_t ref_48fe = 1.84486307;
 const Double_t ref_49fe = 1.88304627;
 const Double_t ref_50fe = 1.92110626;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 26;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_48fe = ref_48fe * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_49fe = ref_49fe * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_50fe = ref_50fe * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_48fe = tof_func(L,ele,z,Brho,c,mref_48fe); // [ps]
  Double_t t_ref_49fe = tof_func(L,ele,z,Brho,c,mref_49fe); // [ps]
  Double_t t_ref_50fe = tof_func(L,ele,z,Brho,c,mref_50fe); // [ps]



// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step_weight.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step_unit2.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.48fe.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.48fe.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref2_fitting_st1_3step.eventstore.48fe.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step_weight.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step_unit2.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_maxz_nooff.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.49fe.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.49fe.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref2_fitting_st1_3step.eventstore.49fe.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_2step_weight.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_3step_unit2.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_maxz_nooff.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.50fe.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.50fe.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref2_fitting_st1_3step.eventstore.50fe.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_2nd_ref.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_2step.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_2step_weight.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_unit2.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_ref2_3step_unit2.eventstore.170272.hist.root");
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

TH1D *h48fe = (TH1D*)gDirectory->Get("h48fe_aq");
 Int_t nh48fe = h48fe->GetEntries();
// if( nh48fe < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh48fe << endl;
//  delete gROOT->Get("h48fe");
// }else{
 h48fe->Fit("gaus","L","",1.843489827,1.845790173);
 TF1 *f1 = h48fe->GetFunction("gaus");
 const Double_t *prm1 = f1->GetParameters();
 const Double_t *error1 = f1->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h48fe->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h48fe->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1_keV_error = error1[1] * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t mass1_error = error1[1] * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_48fe;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t t_48fe = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_48fe_error = tof_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_48fe - t_ref_48fe;
 fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout1 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh48fe << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << tdiff1 << "  " << t_48fe_error << endl;
 

 delete gROOT->Get("h48fe");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h49fe = (TH1D*)gDirectory->Get("h49fe_aq");
 Int_t nh49fe = h49fe->GetEntries();
 h49fe->Fit("gaus","L","",1.881808004,1.883711996);
// if( nh49fe < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh49fe << endl;
// delete gROOT->Get("h49fe");
// }else{
 TF1 *f2 = h49fe->GetFunction("gaus");
 const Double_t *prm2 = f2->GetParameters();
 const Double_t *error2 = f2->GetParErrors();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h49fe->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h49fe->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2_keV_error = error2[1] * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t mass2_error = error2[1] * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_49fe;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t t_49fe = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_49fe_error = tof_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_49fe - t_ref_49fe;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh49fe  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << tdiff2 << "  " << t_49fe_error << endl;
 
 delete gROOT->Get("h49fe");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h50fe = (TH1D*)gDirectory->Get("h50fe_aq");
 Int_t nh50fe = h50fe->GetEntries();
 h50fe->Fit("gaus","L","",1.920131745,1.922388255);
// if( nh50fe < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh50fe <<  endl;
// delete gROOT->Get("h50fe");
//}else{
 TF1 *f3 = h50fe->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h50fe->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h50fe->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_50fe;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t t_50fe = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_50fe_error = tof_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_50fe - t_ref_50fe;
 fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh50fe << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << tdiff3 << "  " << t_50fe_error << endl;
 

 delete gROOT->Get("h50fe");
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

