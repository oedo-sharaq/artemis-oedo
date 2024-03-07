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

void massfit_cr_ref6(){

 const Double_t ref_44cr = 1.83218575;
 const Double_t ref_45cr = 1.87358000;
 const Double_t ref_46cr = 1.91480106;
 const Double_t ref_47cr = 1.95624000;
 const Double_t ref_51cr = 2.12215126;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 24;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_44cr = ref_44cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_45cr = ref_45cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_46cr = ref_46cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_47cr = ref_47cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_51cr = ref_51cr * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_44cr = tof_func(L,ele,z,Brho,c,mref_44cr); // [ps]
  Double_t t_ref_45cr = tof_func(L,ele,z,Brho,c,mref_45cr); // [ps]
  Double_t t_ref_46cr = tof_func(L,ele,z,Brho,c,mref_46cr); // [ps]
  Double_t t_ref_47cr = tof_func(L,ele,z,Brho,c,mref_47cr); // [ps]
  Double_t t_ref_51cr = tof_func(L,ele,z,Brho,c,mref_51cr); // [ps]


// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.44cr.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.44cr.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.44cr.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.44cr.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.44cr.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.45cr.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.45cr.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.45cr.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.45cr.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.45cr.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.46cr.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.46cr.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.46cr.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.46cr.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.46cr.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.47cr.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.47cr.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.47cr.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.47cr.dat");
 ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.47cr.dat");
 if(fout4.fail()){
	 cout << "Error; Could not open output file4.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout5("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.49cr.dat");
// ofstream fout5("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.49cr.dat");
// ofstream fout5("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.49cr.dat");
// ofstream fout5("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.49cr.dat");
 ofstream fout5("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.49cr.dat");
 if(fout5.fail()){
	 cout << "Error; Could not open output file5.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream foutall("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.all.dat",ios::app);
// ofstream foutall("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.all.dat",ios::app);
// ofstream foutall("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.all.dat",ios::app);
// ofstream foutall("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.all.dat",ios::app);
 ofstream foutall("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.all.dat",ios::app);
 if(foutall.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream foutfitgate("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fitgate_ref6_stm2_5step.dat",ios::app);
// ofstream foutfitgate("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fitgate_ref6_stm2_6step.dat",ios::app);
// ofstream foutfitgate("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fitgate_ref6_stm2_6step_posmod.dat",ios::app);
// ofstream foutfitgate("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fitgate_ref6_stm2_7step_posmod.dat",ios::app);
 ofstream foutfitgate("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fitgate_ref6_stm2_8step_posmod.dat",ios::app);
 if(foutfitgate.fail()){
	 cout << "Error; Could not open fit gate output file all.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_5step_ref6.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_posmod.eventstore.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_8step_ref6_posmod.eventstore.170272.hist.root");
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

TH1D *h44cr = (TH1D*)gDirectory->Get("h44cr_aq");
 Int_t nh44cr = h44cr->GetEntries();
// if( nh44cr < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh44cr << endl;
//  delete gROOT->Get("h44cr");
// }else{
 h44cr->Fit("gaus","L","",1.83145,1.83288);
 TF1 *f1 = h44cr->GetFunction("gaus");
 const Double_t *prm1 = f1->GetParameters();
 const Double_t *error1 = f1->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h44cr->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h44cr->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1_keV_error = error1[1] * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t mass1_error = error1[1] * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_44cr;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t massdiff1oq = aq_diff1 * amu;
 Double_t t_44cr = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_44cr_error = tof_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_44cr - t_ref_44cr;
 fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]   [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout1 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh44cr << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << massdiff1oq << "  " << tdiff1 << "  " << t_44cr_error << endl;
  foutall << massdiff1oq << endl;

  Double_t xmin12sigma = prm1[1] - 2 * prm1[2];
  Double_t xmax12sigma = prm1[1] + 2 * prm1[2];
  foutfitgate << prm1[1] << "  " << prm1[2] << "  " << xmin12sigma << "  " << xmax12sigma << endl;


 delete gROOT->Get("h44cr");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h45cr = (TH1D*)gDirectory->Get("h45cr_aq");
 Int_t nh45cr = h45cr->GetEntries();
// h45cr->Fit("gaus","L","",1.87381,1.87414);
 h45cr->Fit("gaus","L","",1.873,1.87414);
// if( nh45cr < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh45cr << endl;
// delete gROOT->Get("h45cr");
// }else{
 TF1 *f2 = h45cr->GetFunction("gaus");
 const Double_t *prm2 = f2->GetParameters();
 const Double_t *error2 = f2->GetParErrors();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h45cr->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h45cr->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2_keV_error = error2[1] * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t mass2_error = error2[1] * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_45cr;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t massdiff2oq = aq_diff2 * amu;
 Double_t t_45cr = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_45cr_error = tof_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_45cr - t_ref_45cr;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh45cr  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << massdiff2oq << "  " << tdiff2 << "  " << t_45cr_error << endl;
  foutall << massdiff2oq << endl; 

  Double_t xmin22sigma = prm2[1] - 2 * prm2[2];
  Double_t xmax22sigma = prm2[1] + 2 * prm2[2];
  foutfitgate << prm2[1] << "  " << prm2[2] << "  " << xmin22sigma << "  " << xmax22sigma << endl;


 delete gROOT->Get("h45cr");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h46cr = (TH1D*)gDirectory->Get("h46cr_aq");
 Int_t nh46cr = h46cr->GetEntries();
 h46cr->Fit("gaus","L","",1.91411,1.91538);
// if( nh46cr < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh46cr <<  endl;
// delete gROOT->Get("h46cr");
//}else{
 TF1 *f3 = h46cr->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h46cr->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h46cr->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_46cr;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t massdiff3oq = aq_diff3 * amu;
 Double_t t_46cr = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_46cr_error = tof_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_46cr - t_ref_46cr;
 fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh46cr << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << massdiff3oq << "  "<< tdiff3 << "  " << t_46cr_error << endl;
  foutall << massdiff3oq << endl;

  Double_t xmin32sigma = prm3[1] - 2 * prm3[2];
  Double_t xmax32sigma = prm3[1] + 2 * prm3[2];
  foutfitgate << prm3[1] << "  " << prm3[2] << "  " << xmin32sigma << "  " << xmax32sigma << endl;


 delete gROOT->Get("h46cr");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}
//
// gROOT->ProcessLine("cd ..");
//
// }

TH1D *h47cr = (TH1D*)gDirectory->Get("h47cr_aq");
 Int_t nh47cr = h47cr->GetEntries();
 h47cr->Fit("gaus","L","",1.95564,1.95670);
// if( nh47cr < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh47cr <<  endl;
// delete gROOT->Get("h47cr");
//}else{
 TF1 *f4 = h47cr->GetFunction("gaus");
 const Double_t *prm4 = f4->GetParameters();
 const Double_t *error4 = f4->GetParErrors();
 Double_t xmin4 = prm4[1] - 3 * prm4[2];
 Double_t xmax4 = prm4[1] + 3 * prm4[2];
 h47cr->GetXaxis()->SetRangeUser(xmin4,xmax4);
 Double_t mean4 = h47cr->GetMean();
 Double_t mass4_keV = mean4 * amu * z;
 Double_t mass4_keV_error = error4[1] * amu * z;
 Double_t mass4 = mean4 * amu * z * ele *1.e3;
 Double_t mass4_error = error4[1] * amu * z * ele *1.e3;
 Double_t reso4 = 3 * prm4[2] * amu * z;
 Double_t aq_diff4 = mean4 - ref_47cr;
 Double_t massdiff4 = aq_diff4 * amu * z;
 Double_t massdiff4oq = aq_diff4 * amu;
 Double_t t_47cr = tof_func(L,ele,z,Brho,c,mass4); // [ps]
 Double_t t_47cr_error = tof_func(L,ele,z,Brho,c,mass4) * mass4_error; // [ps]
 Double_t tdiff4 = t_47cr - t_ref_47cr;
 fout4 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout4  << "  " << prm4[0] << "  " << prm4[1] << "  " << prm4[2] << "  " << nh47cr << "  " << mean4 << "  " << mass4_keV << "  " << "  " << mass4_keV_error << "  " << reso4 << "  " << aq_diff4 << "  " << massdiff4 << "  " << massdiff4oq << "  "<< tdiff4 << "  " << t_47cr_error << endl;
  foutall << massdiff4oq << endl;

  Double_t xmin42sigma = prm4[1] - 2 * prm4[2];
  Double_t xmax42sigma = prm4[1] + 2 * prm4[2];
  foutfitgate << prm4[1] << "  " << prm4[2] << "  " << xmin42sigma << "  " << xmax42sigma << endl;


 delete gROOT->Get("h47cr");
 delete gROOT->Get("f4");
 delete gROOT->Get("prm4");


TH1D *h51cr = (TH1D*)gDirectory->Get("h51cr_aq");
 Int_t nh51cr = h51cr->GetEntries();
 h51cr->Fit("gaus","L","",2.12,2.124);
// if( nh51cr < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh51cr <<  endl;
// delete gROOT->Get("h51cr");
//}else{
 TF1 *f5 = h51cr->GetFunction("gaus");
 const Double_t *prm5 = f5->GetParameters();
 const Double_t *error5 = f5->GetParErrors();
 Double_t xmin5 = prm5[1] - 3 * prm5[2];
 Double_t xmax5 = prm5[1] + 3 * prm5[2];
 h51cr->GetXaxis()->SetRangeUser(xmin5,xmax5);
 Double_t mean5 = h51cr->GetMean();
 Double_t mass5_keV = mean5 * amu * z;
 Double_t mass5_keV_error = error5[1] * amu * z;
 Double_t mass5 = mean5 * amu * z * ele *1.e3;
 Double_t mass5_error = error5[1] * amu * z * ele *1.e3;
 Double_t reso5 = 3 * prm5[2] * amu * z;
 Double_t aq_diff5 = mean5 - ref_51cr;
 Double_t massdiff5 = aq_diff5 * amu * z;
 Double_t massdiff5oq = aq_diff5 * amu;
 Double_t t_51cr = tof_func(L,ele,z,Brho,c,mass5); // [ps]
 Double_t t_51cr_error = tof_func(L,ele,z,Brho,c,mass5) * mass5_error; // [ps]
 Double_t tdiff5 = t_51cr - t_ref_51cr;
 fout5 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout5  << "  " << prm5[0] << "  " << prm5[1] << "  " << prm5[2] << "  " << nh51cr << "  " << mean5 << "  " << mass5_keV << "  " << "  " << mass5_keV_error << "  " << reso5 << "  " << aq_diff5 << "  " << massdiff5 << "  " << massdiff5oq << "  "<< tdiff5 << "  " << t_51cr_error << endl;
  foutall << massdiff5oq << endl << endl;

  Double_t xmin52sigma = prm5[1] - 2 * prm5[2];
  Double_t xmax52sigma = prm5[1] + 2 * prm5[2];
  foutfitgate << prm5[1] << "  " << prm5[2] << "  " << xmin52sigma << "  " << xmax52sigma << endl;


 delete gROOT->Get("h51cr");
 delete gROOT->Get("f5");
 delete gROOT->Get("prm5");



 fout1.close();
 fout2.close();
 fout3.close();
 fout4.close();
 fout5.close();
 foutall.close();
 foutfitgate.close();

 file->Close();


}

