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


void massfit_mn_ref(){

 const Double_t ref_46mn = 1.83891945;
 const Double_t ref_47mn = 1.87848359;
 const Double_t ref_48mn = 1.91819472;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 25;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_46mn = ref_46mn * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_47mn = ref_47mn * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_48mn = ref_48mn * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_46mn = tof_func(L,ele,z,Brho,c,mref_46mn); // [ps]
  Double_t t_ref_47mn = tof_func(L,ele,z,Brho,c,mref_47mn); // [ps]
  Double_t t_ref_48mn = tof_func(L,ele,z,Brho,c,mref_48mn); // [ps]



// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step.46mn.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step_5sigma.46mn.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step.47mn.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step_5sigma.47mn.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step.48mn.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/strip0/ref_fitting_st0_2step_5sigma.48mn.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst0_2nd_ref.170272.hist.root");
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

TH1D *h46mn = (TH1D*)gDirectory->Get("h46mn_aq");
 Int_t nh46mn = h46mn->GetEntries();
// if( nh46mn < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh46mn << endl;
//  delete gROOT->Get("h46mn");
// }else{
 h46mn->Fit("gaus","L","",1.837885006,1.840074994);
 TF1 *f1 = h46mn->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
// Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmin1 = prm1[1] - 2.5 * prm1[2];
// Double_t xmax1 = prm1[1] + 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 2.5 * prm1[2];
 h46mn->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h46mn->GetMean();
 Double_t mass1_keV = mean1 * amu * z;
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t reso1 = 3 * prm1[2] * amu * z;
 Double_t aq_diff1 = mean1 - ref_46mn;
 Double_t massdiff1 = aq_diff1 * amu * z;
 Double_t t_46mn = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_46mn - t_ref_46mn;
  fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [3sigma (keV)]     [aq diff]    [mass diff (keV)]    [TOF diff (ps)]" << endl;  
  fout1  << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh46mn << "  " << mean1 << "  " << mass1_keV << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;


 delete gROOT->Get("h46mn");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h47mn = (TH1D*)gDirectory->Get("h47mn_aq");
 Int_t nh47mn = h47mn->GetEntries();
 h47mn->Fit("gaus","L","",1.87754441,1.87921559);
// if( nh47mn < 200 ){
//  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh47mn << endl;
// delete gROOT->Get("h47mn");
// }else{
 TF1 *f2 = h47mn->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
// Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmin2 = prm2[1] - 2.5 * prm2[2];
// Double_t xmax2 = prm2[1] + 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 2.5 * prm2[2];
 h47mn->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h47mn->GetMean();
 Double_t mass2_keV = mean2 * amu * z;
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t reso2 = 3 * prm2[2] * amu * z;
 Double_t aq_diff2 = mean2 - ref_47mn;
 Double_t massdiff2 = aq_diff2 * amu * z;
 Double_t t_47mn = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_47mn - t_ref_47mn;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [3sigma (keV)]     [aq diff]    [mass diff (keV)]    [TOF diff (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh47mn  << "  " << mean2  << "  " << mass2_keV << "  " << reso2 << "  " <<  aq_diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;

 delete gROOT->Get("h47mn");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h48mn = (TH1D*)gDirectory->Get("h48mn_aq");
 Int_t nh48mn = h48mn->GetEntries();
 h48mn->Fit("gaus","L","",1.917219096,1.919300904);
// if( nh48mn < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh48mn <<  endl;
// delete gROOT->Get("h48mn");
//}else{
 TF1 *f3 = h48mn->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
// Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmin3 = prm3[1] - 2.5 * prm3[2];
// Double_t xmax3 = prm3[1] + 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 2.5 * prm3[2];
 h48mn->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h48mn->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_48mn;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t t_48mn = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_48mn - t_ref_48mn;
  fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)]   [3sigma (keV)]     [aq diff]    [mass diff (keV)]    [TOF diff (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh48mn << "  " << mean3 << "  " << mass3_keV << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;

 delete gROOT->Get("h48mn");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}
//
// gROOT->ProcessLine("cd ..");
//
// }

 fout1.close();
 fout2.close();
 fout3.close();

 file->Close();


}

