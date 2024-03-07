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


void massfit_v_allrun(){

 const Double_t ref_43v = 1.86818142;
 const Double_t ref_44v = 1.91138485;
 const Double_t ref_45v = 1.95448605;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 23;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_43v = ref_43v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_44v = ref_44v * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_45v = ref_45v * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_43v = tof_func(L,ele,z,Brho,c,mref_43v); // [ps]
  Double_t t_ref_44v = tof_func(L,ele,z,Brho,c,mref_44v); // [ps]
  Double_t t_ref_45v = tof_func(L,ele,z,Brho,c,mref_45v); // [ps]



 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.43v.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.44v.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.45v.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st0_2step.170272.v.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h43v = (TH1F*)gDirectory->Get(Form("mass_st0_43v_2nd_%d",i));
 Int_t nh43v = h43v->GetEntries();
 if( nh43v < 200 ){
  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43v << endl;
  delete gROOT->Get("h43v");
 }else{
 h43v->Fit("gaus","L","",1.8670829,1.8689171);
 TF1 *f1 = h43v->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h43v->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h43v->GetMean();
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t diff1 = mean1 - ref_43v;
 Double_t massdiff1 = diff1 * amu * z;
 Double_t t_43v = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_43v - t_ref_43v;
  fout1 << i << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[12] << "  " << nh43v << "  " << mean1 << "  " << diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;


 delete gROOT->Get("h43v");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
}

TH1F *h44v = (TH1F*)gDirectory->Get(Form("mass_st0_44v_2nd_%d",i));
 Int_t nh44v = h44v->GetEntries();
 h44v->Fit("gaus","L","",1.910004,1.911996);
 if( nh44v < 200 ){
  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh44v << endl;
 delete gROOT->Get("h44v");
 }else{
 TF1 *f2 = h44v->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h44v->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h44v->GetMean();
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t diff2 = mean2 - ref_44v;
 Double_t massdiff2 = diff2 * amu * z;
 Double_t t_44v = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_44v - t_ref_44v;
  fout2 << i << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh44v  << "  " << mean2  << "  " << diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;

 delete gROOT->Get("h44v");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
}

TH1F *h45v = (TH1F*)gDirectory->Get(Form("mass_st0_45v_2nd_%d",i));
 Int_t nh45v = h45v->GetEntries();
 h45v->Fit("gaus","L","",1.95286123,1.95513877);
 if( nh45v < 200 ){
  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh45v <<  endl;
 delete gROOT->Get("h45v");
}else{
 TF1 *f3 = h45v->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h45v->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h45v->GetMean();
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t diff3 = mean3 - ref_45v;
 Double_t massdiff3 = diff3 * amu * z;
 Double_t t_45v = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_45v - t_ref_45v;
  fout3 << i << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh45v << "  " << mean3 << "  " << diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;

 delete gROOT->Get("h45v");
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

