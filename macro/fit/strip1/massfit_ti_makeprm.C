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

void massfit_ti_makeprm(){

 const Double_t ref_41ti = 1.86232290;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 22;
// const Double_t mc = 3.734; //[keV/q]
 const Double_t mc = -2.5409125; //[keV/q]

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_41ti = ref_41ti * amu * z * ele * 1.e3; //mass [J]
//  Double_t mref_41ti = (ref_41ti * amu + mc) * z * ele * 1.e3; //mass [J]

  Double_t t_ref_41ti = tof_func(L,ele,z,Brho,c,mref_41ti); // [ps]


for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 ofstream fout2(Form("/home/sh13/art_analysis/user/hanai/prm/dia/strip1/tof_offset_%04d.dat",i));
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_BLD_3rd_all.170272.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

 TH1F *h41ti = (TH1F*)gDirectory->Get(Form("h41ti_aq_%d",i));
 Int_t nh41ti = h41ti->GetEntries();
 h41ti->Fit("gaus","L","",1.861448594,1.863211406);
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
// fout2 << "[Run Number]    [TOF diff (ps)]   [TOF fit error (ps)]" << endl;  
// fout2 << i  << "  "  << tdiff2 << "  " << t_41ti_error << "  " << nh41ti << endl;
 fout2 <<  tdiff2 << endl;
 delete gROOT->Get("h41ti");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");

 gROOT->ProcessLine("cd ..");
 fout2.close();
 file->Close();
// gROOT->ProcessLine(".q");
 }



}

