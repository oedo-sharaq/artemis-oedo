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

void massfit_ti_allrun(){

 const Double_t ref_40ti = 1.81719569;
 const Double_t ref_41ti = 1.86232290;
 const Double_t ref_43ti = 1.95256747;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 22;
// const Double_t mc = 3.734; //[keV/q]
 const Double_t mc = -2.5409125; //[keV/q]

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

//  Double_t mref_40ti = ref_40ti * amu * z * ele * 1.e3; //mass [J]
//  Double_t mref_41ti = ref_41ti * amu * z * ele * 1.e3; //mass [J]
//  Double_t mref_43ti = ref_43ti * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_40ti = (ref_40ti * amu + mc) * z * ele * 1.e3; //mass [J]
  Double_t mref_41ti = (ref_41ti * amu + mc) * z * ele * 1.e3; //mass [J]
  Double_t mref_43ti = (ref_43ti * amu + mc) * z * ele * 1.e3; //mass [J]

  Double_t t_ref_40ti = tof_func(L,ele,z,Brho,c,mref_40ti); // [ps]
  Double_t t_ref_41ti = tof_func(L,ele,z,Brho,c,mref_41ti); // [ps]
  Double_t t_ref_43ti = tof_func(L,ele,z,Brho,c,mref_43ti); // [ps]



// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.40ti.170272.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.40ti_aq.170272.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step_unit.40ti_aq.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.41ti.170272.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.41ti_aq.170272.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step_unit.41ti_aq.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.43ti.170272.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.43ti_aq.170272.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step_unit.43ti_aq.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st1_2step.170272.ti.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_BLD_3rd_all.170272.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_BLD_3rd_unit_all.170272.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

//TH1F *h40ti = (TH1F*)gDirectory->Get(Form("mass_st1_40ti_2nd_%d",i));
TH1F *h40ti = (TH1F*)gDirectory->Get(Form("h40ti_aq_%d",i));
 Int_t nh40ti = h40ti->GetEntries();
// if( nh40ti < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh40ti << endl;
//  delete gROOT->Get("h40ti");
// }else{
 h40ti->Fit("gaus","L","",1.81581718, 1.818562812);
 TF1 *f1 = h40ti->GetFunction("gaus");
 const Double_t *prm1 = f1->GetParameters();
 const Double_t *error1 = f1->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h40ti->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h40ti->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1_keV_error = error1[1] * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t mass1_error = error1[1] * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_40ti;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t t_40ti = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_40ti_error = tof_error_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_40ti - t_ref_40ti;
  fout1 << "[Run Number]    [Run error dummy]    [fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [Mass mean fit error (keV)]   [3sigma (keV)]   [aq diff]   [mass diff (keV)]   [TOF diff (ps)]   [TOF fit error (ps)]" << endl;  
//if(nh40ti < 200){
//	fout1 << i << "  " << 0 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << nh40ti << "  " << 3.14 << " " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14  << "  " << 3.14 << endl;
//	}else{
	fout1 << i << "  " << 0 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh40ti << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << tdiff1 << "  " << t_40ti_error << endl;
// }


 delete gROOT->Get("h40ti");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

//TH1F *h41ti = (TH1F*)gDirectory->Get(Form("mass_st1_41ti_2nd_%d",i));
TH1F *h41ti = (TH1F*)gDirectory->Get(Form("h41ti_aq_%d",i));
 Int_t nh41ti = h41ti->GetEntries();
 h41ti->Fit("gaus","L","",1.861448594,1.863211406);
// if( nh41ti < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh41ti << endl;
// delete gROOT->Get("h41ti");
// }else{
 TF1 *f2 = h41ti->GetFunction("gaus");
 const Double_t *prm2 = f2->GetParameters();
 const Double_t *error2 = f2->GetParErrors();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h41ti->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h41ti->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2_keV_error = error2[1] * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t mass2_error = error2[1] * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_41ti;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t t_41ti = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_41ti_error = tof_error_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_41ti - t_ref_41ti;
fout2 << "[Run Number]    [Run error dummy]   [fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [Mass mean fit error (keV)]   [3sigma (keV)]    [aq diff]  [mass diff (keV)]    [TOF diff (ps)]   [TOF fit error (ps)]" << endl;  
//if(nh41ti < 200 ){
//fout2 << i  << "  " << 0 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << nh41ti  << "  " << 3.14  << "  " << 3.14 << " " << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << endl;
//}else{
fout2 << i  << "  " << 0 << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh41ti  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << tdiff2 << "  " << t_41ti_error << endl;
// }
 delete gROOT->Get("h41ti");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

//TH1F *h43ti = (TH1F*)gDirectory->Get(Form("mass_st1_43ti_2nd_%d",i));
TH1F *h43ti = (TH1F*)gDirectory->Get(Form("h43ti_aq_%d",i));
 Int_t nh43ti = h43ti->GetEntries();
 h43ti->Fit("gaus","L","",1.951258828,1.953381172);
// if( nh43ti < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43ti <<  endl;
// delete gROOT->Get("h43ti");
//}else{
 TF1 *f3 = h43ti->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h43ti->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h43ti->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_43ti;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t t_43ti = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_43ti_error = tof_error_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_43ti - t_ref_43ti;
  fout3 << "[Run Number]     [Run error dummy]   [fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [Mass mean fit error (keV)]   [3sigma (keV)]    [aq diff]   [mass diff (keV)]   [TOF diff (ps)]   [TOF fit error (ps)]" << endl;  
//if(nh43ti < 200){
//fout3 << i << "  " << 0 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << nh43ti << "  " << 3.14 << "  " << 3.14 << "  " << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << "  " << 3.14 << endl;
//}else{
fout3 << i << "  " << 0 << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh43ti << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << tdiff3 << "  " << t_43ti_error << endl;
// }
 delete gROOT->Get("h43ti");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}

 gROOT->ProcessLine("cd ..");

 }

 fout1.close();
 fout2.close();
 fout3.close();

 file->Close();


}

