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


void massfit_cr_allrun(){

 const Double_t ref_44cr = 1.83218575;
 const Double_t ref_45cr = 1.87358000;
 const Double_t ref_46cr = 1.91480106;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 24;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_44cr = ref_44cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_45cr = ref_45cr * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_46cr = ref_46cr * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_44cr = tof_func(L,ele,z,Brho,c,mref_44cr); // [ps]
  Double_t t_ref_45cr = tof_func(L,ele,z,Brho,c,mref_45cr); // [ps]
  Double_t t_ref_46cr = tof_func(L,ele,z,Brho,c,mref_46cr); // [ps]



 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.44cr.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.45cr.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.46cr.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st0_2step.170272.cr.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h44cr = (TH1F*)gDirectory->Get(Form("mass_st0_44cr_2nd_%d",i));
 Int_t nh44cr = h44cr->GetEntries();
 if( nh44cr < 200 ){
  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh44cr << endl;
  delete gROOT->Get("h44cr");
 }else{
 h44cr->Fit("gaus","L","",1.831041138,1.833398862);
 TF1 *f1 = h44cr->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h44cr->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h44cr->GetMean();
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t diff1 = mean1 - ref_44cr;
 Double_t massdiff1 = diff1 * amu * z;
 Double_t t_44cr = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_44cr - t_ref_44cr;
  fout1 << i << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[12] << "  " << nh44cr << "  " << mean1 << "  " << diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;


 delete gROOT->Get("h44cr");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
}

TH1F *h45cr = (TH1F*)gDirectory->Get(Form("mass_st0_45cr_2nd_%d",i));
 Int_t nh45cr = h45cr->GetEntries();
 h45cr->Fit("gaus","L","",1.872615278,1.874364722);
 if( nh45cr < 200 ){
  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh45cr << endl;
 delete gROOT->Get("h45cr");
 }else{
 TF1 *f2 = h45cr->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h45cr->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h45cr->GetMean();
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t diff2 = mean2 - ref_45cr;
 Double_t massdiff2 = diff2 * amu * z;
 Double_t t_45cr = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_45cr - t_ref_45cr;
  fout2 << i << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh45cr  << "  " << mean2  << "  " << diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;

 delete gROOT->Get("h45cr");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
}

TH1F *h46cr = (TH1F*)gDirectory->Get(Form("mass_st0_46cr_2nd_%d",i));
 Int_t nh46cr = h46cr->GetEntries();
 h46cr->Fit("gaus","L","",1.913705668,1.915754332);
 if( nh46cr < 200 ){
  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh46cr <<  endl;
 delete gROOT->Get("h46cr");
}else{
 TF1 *f3 = h46cr->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h46cr->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h46cr->GetMean();
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t diff3 = mean3 - ref_46cr;
 Double_t massdiff3 = diff3 * amu * z;
 Double_t t_46cr = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_46cr - t_ref_46cr;
  fout3 << i << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh46cr << "  " << mean3 << "  " << diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;

 delete gROOT->Get("h46cr");
 delete gROOT->Get("f3");
 delete gROOT->Get("prm3");
}

 gROOT->ProcessLine("cd ..");

 }

 fout1.close();
 fout2.close();
 fout3.close();

 file->Close();


}

