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


void massfit_sc_allrun(){

 const Double_t ref_40Sc = 1.90316521;
 const Double_t ref_41Sc = 1.95036921;
 const Double_t ref_43Sc = 2.04522156;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 21;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_40Sc = ref_40Sc * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_41Sc = ref_41Sc * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_43Sc = ref_43Sc * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_40Sc = tof_func(L,ele,z,Brho,c,mref_40Sc); // [ps]
  Double_t t_ref_41Sc = tof_func(L,ele,z,Brho,c,mref_41Sc); // [ps]
  Double_t t_ref_43Sc = tof_func(L,ele,z,Brho,c,mref_43Sc); // [ps]


 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.40sc.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.41sc.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.43sc.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st3_2step.170272.sc.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h40sc = (TH1F*)gDirectory->Get(Form("mass_st3_40sc_2nd_%d",i));
 Int_t nh40sc = h40sc->GetEntries();
 if( nh40sc < 200 ){
  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh40sc << endl;
  delete gROOT->Get("h40sc");
 }else{
 h40sc->Fit("gaus","L","",1.9021,1.90414);
 TF1 *f1 = h40sc->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h40sc->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h40sc->GetMean();
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t diff1 = mean1 - ref_40Sc;
 Double_t massdiff1 = diff1 * amu * z;
 Double_t t_40Sc = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_40Sc - t_ref_40Sc;
  fout1 << i << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[12] << "  " << nh40sc << "  " << mean1 << "  " << diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;

 delete gROOT->Get("h40sc");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
}

TH1F *h41sc = (TH1F*)gDirectory->Get(Form("mass_st3_41sc_2nd_%d",i));
 Int_t nh41sc = h41sc->GetEntries();
 h41sc->Fit("gaus","L","",1.949,1.95119);
 if( nh41sc < 200 ){
  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh41sc  << endl;
 delete gROOT->Get("h41sc");
 }else{
 TF1 *f2 = h41sc->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h41sc->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h41sc->GetMean();
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t diff2 = mean2 - ref_41Sc;
 Double_t massdiff2 = diff2 * amu * z;
 Double_t t_41Sc = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_41Sc - t_ref_41Sc;
  fout2 << i << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh41sc  << "  " << mean2  << "  " << diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;

 delete gROOT->Get("h41sc");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
}

TH1F *h43sc = (TH1F*)gDirectory->Get(Form("mass_st3_43sc_2nd_%d",i));
 Int_t nh43sc = h43sc->GetEntries();
 h43sc->Fit("gaus","L","",2.044,2.04651);
 if( nh43sc < 200 ){
  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43sc <<  endl;
 delete gROOT->Get("h43sc");
}else{
 TF1 *f3 = h43sc->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h43sc->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h43sc->GetMean();
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t diff3 = mean3 - ref_43Sc;
 Double_t massdiff3 = diff3 * amu * z;
 Double_t t_43Sc = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_43Sc - t_ref_43Sc;
  fout3 << i << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh43sc << "  " << mean3 << "  " << diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;

 delete gROOT->Get("h43sc");
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

