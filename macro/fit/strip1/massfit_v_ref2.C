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

void massfit_v_ref2(){

 const Double_t ref_43v = 1.86818142;
 const Double_t ref_44v = 1.91138485;
 const Double_t ref_47v = 2.04097018;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 23;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_43v = ref_43v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_44v = ref_44v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_47v = ref_47v * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_43v = tof_func(L,ele,z,Brho,c,mref_43v); // [ps]
  Double_t t_ref_44v = tof_func(L,ele,z,Brho,c,mref_44v); // [ps]
  Double_t t_ref_47v = tof_func(L,ele,z,Brho,c,mref_47v); // [ps]



// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_maxz_nooff.eventstore.43v.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.43v.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.43v.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref3_fitting_st1_3step_old.eventstore.43v.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_nooff.eventstore.44v.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.44v.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.44v.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref3_fitting_st1_3step_old.eventstore.44v.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_nooff.eventstore.45v.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4step_ssdpla_nooff.eventstore.47v.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_st1_4.5step_ssdpla_nooff.eventstore.47v.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref3_fitting_st1_3step_old.eventstore.47v.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_ref3_3step_unit2_old.eventstore.170272.hist.root");
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

TH1D *h43v = (TH1D*)gDirectory->Get("h43v_aq");
 Int_t nh43v = h43v->GetEntries();
// if( nh43v < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43v << endl;
//  delete gROOT->Get("h43v");
// }else{
 h43v->Fit("gaus","L","",1.8670829,1.8689171);
 TF1 *f1 = h43v->GetFunction("gaus");
 const Double_t *prm1 = f1->GetParameters();
 const Double_t *error1 = f1->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h43v->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h43v->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1_keV_error = error1[1] * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t mass1_error = error1[1] * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_43v;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t t_43v = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_43v_error = tof_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_43v - t_ref_43v;
 fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout1 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh43v << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << tdiff1 << "  " << t_43v_error << endl;
 

 delete gROOT->Get("h43v");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h44v = (TH1D*)gDirectory->Get("h44v_aq");
 Int_t nh44v = h44v->GetEntries();
 h44v->Fit("gaus","L","",1.910004,1.911996);
// if( nh44v < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh44v << endl;
// delete gROOT->Get("h44v");
// }else{
 TF1 *f2 = h44v->GetFunction("gaus");
 const Double_t *prm2 = f2->GetParameters();
 const Double_t *error2 = f2->GetParErrors();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h44v->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h44v->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2_keV_error = error2[1] * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t mass2_error = error2[1] * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_44v;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t t_44v = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_44v_error = tof_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_44v - t_ref_44v;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh44v  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << tdiff2 << "  " << t_44v_error << endl;
 
 delete gROOT->Get("h44v");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h47v = (TH1D*)gDirectory->Get("h47v_aq");
 Int_t nh47v = h47v->GetEntries();
 h47v->Fit("gaus","L","",2.04,2.0415);
// if( nh47v < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh47v <<  endl;
// delete gROOT->Get("h47v");
//}else{
 TF1 *f3 = h47v->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h47v->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h47v->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_47v;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t t_47v = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_47v_error = tof_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_47v - t_ref_47v;
 fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh47v << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << tdiff3 << "  " << t_47v_error << endl;
 

 delete gROOT->Get("h47v");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}

// gROOT->ProcessLine("cd ..");
//
// }

 fout1.close();
 fout2.close();
 fout3.close();

 file->Close();


}

