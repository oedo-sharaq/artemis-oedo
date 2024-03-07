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

void massfit_v_ref6(){

 const Double_t ref_43v = 1.86818142;
 const Double_t ref_44v = 1.91138485;
 const Double_t ref_46v = 1.99772208;
 const Double_t ref_47v = 2.04097018;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 23;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_43v = ref_43v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_44v = ref_44v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_46v = ref_46v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_47v = ref_47v * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_43v = tof_func(L,ele,z,Brho,c,mref_43v); // [ps]
  Double_t t_ref_44v = tof_func(L,ele,z,Brho,c,mref_44v); // [ps]
  Double_t t_ref_46v = tof_func(L,ele,z,Brho,c,mref_46v); // [ps]
  Double_t t_ref_47v = tof_func(L,ele,z,Brho,c,mref_47v); // [ps]


// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.43v.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.43v.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.43v.dat");
// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.43v.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.43v.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.44v.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.44v.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.44v.dat");
// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.44v.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.44v.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step_SSRBVar.eventstore.46v.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_SSRBVar.eventstore.46v.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.46v.dat");
// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.46v.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.46v.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_5step.eventstore.47v.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step.eventstore.47v.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_6step_posmod.eventstore.47v.dat");
// ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_7step_posmod.eventstore.47v.dat");
 ofstream fout4("/home/sh13/art_analysis/user/hanai/prm/mass/stm/ref6_fitting_stm2_8step_posmod.eventstore.47v.dat");
 if(fout4.fail()){
	 cout << "Error; Could not open output file4.." << endl << endl;
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

TH1D *h43v = (TH1D*)gDirectory->Get("h43v_aq");
 Int_t nh43v = h43v->GetEntries();
// if( nh43v < 200 ){
//  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43v << endl;
//  delete gROOT->Get("h43v");
// }else{
 h43v->Fit("gaus","L","",1.8674,1.8689);
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
 Double_t massdiff1oq = aq_diff1 * amu;
 Double_t t_43v = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t t_43v_error = tof_func(L,ele,z,Brho,c,mass1) * mass1_error; // [ps]
 Double_t tdiff1 = t_43v - t_ref_43v;
 fout1 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout1 << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh43v << "  " << mean1 << " " << mass1_keV << "  " << mass1_keV_error << "  " << reso1 << "  " << aq_diff1 << "  " << massdiff1 << "  " << massdiff1oq << "  " << tdiff1 << "  " << t_43v_error << endl;
 foutall << massdiff1oq << endl; 

  Double_t xmin12sigma = prm1[1] - 2 * prm1[2];
  Double_t xmax12sigma = prm1[1] + 2 * prm1[2];
  foutfitgate << prm1[1] << "  " << prm1[2] << "  " << xmin12sigma << "  " << xmax12sigma << endl;


 delete gROOT->Get("h43v");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
//}

TH1D *h44v = (TH1D*)gDirectory->Get("h44v_aq");
 Int_t nh44v = h44v->GetEntries();
// h44v->Fit("gaus","L","",1.91076,1.91115);
 h44v->Fit("gaus","L","",1.91076,1.912);
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
 Double_t massdiff2oq = aq_diff2 * amu;
 Double_t t_44v = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t t_44v_error = tof_func(L,ele,z,Brho,c,mass2) * mass2_error; // [ps]
 Double_t tdiff2 = t_44v - t_ref_44v;
  fout2 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout2  << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh44v  << "  " << mean2  << "  " << mass2_keV << " " << "  " << mass2_keV_error << "  " << reso2 << "  " << aq_diff2 << "  " << massdiff2 << "  " << massdiff2oq << "  " << tdiff2 << "  " << t_44v_error << endl;
  foutall << massdiff2oq << endl;

  Double_t xmin22sigma = prm2[1] - 2 * prm2[2];
  Double_t xmax22sigma = prm2[1] + 2 * prm2[2];
  foutfitgate << prm2[1] << "  " << prm2[2] << "  " << xmin22sigma << "  " << xmax22sigma << endl;

 delete gROOT->Get("h44v");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
//}

TH1D *h46v = (TH1D*)gDirectory->Get("h46v_aq");
 Int_t nh46v = h46v->GetEntries();
 h46v->Fit("gaus","L","",1.99682,1.99843);
// if( nh46v < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh46v <<  endl;
// delete gROOT->Get("h46v");
//}else{
 TF1 *f3 = h46v->GetFunction("gaus");
 const Double_t *prm3 = f3->GetParameters();
 const Double_t *error3 = f3->GetParErrors();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h46v->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h46v->GetMean();
 Double_t mass3_keV = mean3 * amu * z;
 Double_t mass3_keV_error = error3[1] * amu * z;
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t mass3_error = error3[1] * amu * z * ele *1.e3;
 Double_t reso3 = 3 * prm3[2] * amu * z;
 Double_t aq_diff3 = mean3 - ref_46v;
 Double_t massdiff3 = aq_diff3 * amu * z;
 Double_t massdiff3oq = aq_diff3 * amu;
 Double_t t_46v = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t t_46v_error = tof_func(L,ele,z,Brho,c,mass3) * mass3_error; // [ps]
 Double_t tdiff3 = t_46v - t_ref_46v;
 fout3 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout3  << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh46v << "  " << mean3 << "  " << mass3_keV << "  " << "  " << mass3_keV_error << "  " << reso3 << "  " << aq_diff3 << "  " << massdiff3 << "  " << massdiff3oq << "  " << tdiff3 << "  " << t_46v_error << endl;
  foutall << massdiff3oq << endl; 

  Double_t xmin32sigma = prm3[1] - 2 * prm3[2];
  Double_t xmax32sigma = prm3[1] + 2 * prm3[2];
  foutfitgate << prm3[1] << "  " << prm3[2] << "  " << xmin32sigma << "  " << xmax32sigma << endl;


 delete gROOT->Get("h46v");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
//}

// gROOT->ProcessLine("cd ..");
//
// }


TH1D *h47v = (TH1D*)gDirectory->Get("h47v_aq");
 Int_t nh47v = h47v->GetEntries();
 h47v->Fit("gaus","L","",2.04034,2.04143);
// if( nh47v < 200 ){
//  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh47v <<  endl;
// delete gROOT->Get("h47v");
//}else{
 TF1 *f4 = h47v->GetFunction("gaus");
 const Double_t *prm4 = f4->GetParameters();
 const Double_t *error4 = f4->GetParErrors();
 Double_t xmin4 = prm4[1] - 3 * prm4[2];
 Double_t xmax4 = prm4[1] + 3 * prm4[2];
 h47v->GetXaxis()->SetRangeUser(xmin4,xmax4);
 Double_t mean4 = h47v->GetMean();
 Double_t mass4_keV = mean4 * amu * z;
 Double_t mass4_keV_error = error4[1] * amu * z;
 Double_t mass4 = mean4 * amu * z * ele *1.e3;
 Double_t mass4_error = error4[1] * amu * z * ele *1.e3;
 Double_t reso4 = 3 * prm4[2] * amu * z;
 Double_t aq_diff4 = mean4 - ref_47v;
 Double_t massdiff4 = aq_diff4 * amu * z;
 Double_t massdiff4oq = aq_diff4 * amu;
 Double_t t_47v = tof_func(L,ele,z,Brho,c,mass4); // [ps]
 Double_t t_47v_error = tof_func(L,ele,z,Brho,c,mass4) * mass4_error; // [ps]
 Double_t tdiff4 = t_47v - t_ref_47v;
 fout4 << "[fit scale]    [fit mean]    [fit sigma]   [Entry]    [A/Q mean +- 3sigma]    [Mass mean +- 3sigma (keV)] [Mass mean fit error (keV)]  [3sigma (keV)]   [aq diff]  [mass diff (keV)]  [mass diff (keV/q)]  [TOF diff (ps)] [TOF fit error (ps)]" << endl;  
  fout4  << "  " << prm4[0] << "  " << prm4[1] << "  " << prm4[2] << "  " << nh47v << "  " << mean4 << "  " << mass4_keV << "  " << "  " << mass4_keV_error << "  " << reso4 << "  " << aq_diff4 << "  " << massdiff4 << "  " << massdiff4oq << "  " << tdiff4 << "  " << t_47v_error << endl;
  foutall << massdiff4oq << endl << endl; 

  Double_t xmin42sigma = prm4[1] - 2 * prm4[2];
  Double_t xmax42sigma = prm4[1] + 2 * prm4[2];
  foutfitgate << prm4[1] << "  " << prm4[2] << "  " << xmin42sigma << "  " << xmax42sigma << endl;


 delete gROOT->Get("h47v");
 delete gROOT->Get("f4");
 delete gROOT->Get("prm4");


 fout1.close();
 fout2.close();
 fout3.close();
 fout4.close();
 foutall.close();
 foutfitgate.close();

 file->Close();


}

