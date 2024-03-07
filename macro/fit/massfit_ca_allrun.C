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


void massfit_ca_allrun(){

 const Double_t ref_39Ca = 1.94798796; // A/Q
 const Double_t ref_40Ca = 1.99758196; // A/Q
 const Double_t ref_41Ca = 2.04756631; // A/Q
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 20;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_39Ca = ref_39Ca * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_40Ca = ref_40Ca * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_41Ca = ref_41Ca * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_39Ca = tof_func(L,ele,z,Brho,c,mref_39Ca); // [ps]
  Double_t t_ref_40Ca = tof_func(L,ele,z,Brho,c,mref_40Ca); // [ps]
  Double_t t_ref_41Ca = tof_func(L,ele,z,Brho,c,mref_41Ca); // [ps]


 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.39ca_aq.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.40ca_aq.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.41ca_aq.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.ca.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst2_2nd_all.170272.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h39ca = (TH1F*)gDirectory->Get(Form("mass_st2_39ca_2step_%d",i));
 Int_t nh39ca = h39ca->GetEntries();
 if( nh39ca < 200 ){
  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh39ca << endl;
 delete gROOT->Get("h39ca");
 }else{
 h39ca->Fit("gaus","L","",1.946,1.9489);
 TF1 *f1 = h39ca->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h39ca->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h39ca->GetMean();
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t diff1 = mean1 - ref_39Ca;
 Double_t massdiff1 = diff1 * amu * z;
 Double_t t_39Ca = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_39Ca - t_ref_39Ca;
  fout1 << i << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[12] << "  " << nh39ca << "  " << mean1 << "  " << diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;
 
 delete gROOT->Get("h39ca");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
}

TH1F *h40ca = (TH1F*)gDirectory->Get(Form("mass_st2_40ca_2step_%d",i));
 Int_t nh40ca = h40ca->GetEntries();
 h40ca->Fit("gaus","L","",1.996,1.9983);
 if( nh40ca < 200 ){
  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh40ca  << endl;
 delete gROOT->Get("h40ca");
}else{
 TF1 *f2 = h40ca->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
 Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 3 * prm2[2];
 h40ca->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h40ca->GetMean();
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t diff2 = mean2 - ref_40Ca;
 Double_t massdiff2 = diff2 * amu * z;
 Double_t t_40Ca = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_40Ca - t_ref_40Ca;
  fout2 << i << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh40ca  << "  " << mean2  << "  " << diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;
 
 delete gROOT->Get("h40ca");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
}

TH1F *h41ca = (TH1F*)gDirectory->Get(Form("mass_st2_41ca_2step_%d",i));
 Int_t nh41ca = h41ca->GetEntries();
 h41ca->Fit("gaus","L","",2.046,2.0488);
 if( nh41ca < 200 ){
  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh41ca <<  endl;
 delete gROOT->Get("h41ca");
}else{
 TF1 *f3 = h41ca->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
 Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 3 * prm3[2];
 h41ca->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h41ca->GetMean();
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t diff3 = mean3 - ref_41Ca;
 Double_t massdiff3 = diff3 * amu * z;
 Double_t t_41Ca = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_41Ca - t_ref_41Ca;
  fout3 << i << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh41ca << "  " << mean3 << "  " << diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;
 
 delete gROOT->Get("h41ca");
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

