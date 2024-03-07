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


void massfit_ti_allrun(){

 const Double_t ref_40ti = 1.81719569;
 const Double_t ref_41ti = 1.86232290;
 const Double_t ref_43ti = 1.95256747;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z = 22;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

  Double_t mref_40ti = ref_40ti * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_41ti = ref_41ti * amu * z * ele * 1.e3; //mass [J]
  Double_t mref_43ti = ref_43ti * amu * z * ele * 1.e3; //mass [J]

  Double_t t_ref_40ti = tof_func(L,ele,z,Brho,c,mref_40ti); // [ps]
  Double_t t_ref_41ti = tof_func(L,ele,z,Brho,c,mref_41ti); // [ps]
  Double_t t_ref_43ti = tof_func(L,ele,z,Brho,c,mref_43ti); // [ps]



// ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.40ti.170272.dat");
 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step_5sigma.40ti.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


// ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.41ti.170272.dat");
 ofstream fout2("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step_5sigma.41ti.170272.dat");
 if(fout2.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step.43ti.170272.dat");
 ofstream fout3("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting_2step_5sigma.43ti.170272.dat");
 if(fout3.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2_2step.170272.ti.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h40ti = (TH1F*)gDirectory->Get(Form("mass_st2_40ti_2nd_%d",i));
 Int_t nh40ti = h40ti->GetEntries();
 if( nh40ti < 200 ){
  fout1 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh40ti << endl;
  delete gROOT->Get("h40ti");
 }else{
 h40ti->Fit("gaus","L","",1.81581718, 1.818562812);
 TF1 *f1 = h40ti->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
// Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmin1 = prm1[1] - 2.5 * prm1[2];
// Double_t xmax1 = prm1[1] + 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 2.5 * prm1[2];
 h40ti->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h40ti->GetMean();
 Double_t mass1 = mean1 * amu * z * ele * 1.e3;
 Double_t diff1 = mean1 - ref_40ti;
 Double_t massdiff1 = diff1 * amu * z;
 Double_t t_40ti = tof_func(L,ele,z,Brho,c,mass1); // [ps]
 Double_t tdiff1 = t_40ti - t_ref_40ti;
  fout1 << i << "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[12] << "  " << nh40ti << "  " << mean1 << "  " << diff1 << "  " << massdiff1 << "  " << tdiff1 << endl;


 delete gROOT->Get("h40ti");
 delete gROOT->Get("f1");
 delete gROOT->Get("prm1");
}

TH1F *h41ti = (TH1F*)gDirectory->Get(Form("mass_st2_41ti_2nd_%d",i));
 Int_t nh41ti = h41ti->GetEntries();
 h41ti->Fit("gaus","L","",1.861448594,1.863211406);
 if( nh41ti < 200 ){
  fout2 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh41ti << endl;
 delete gROOT->Get("h41ti");
 }else{
 TF1 *f2 = h41ti->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
// Double_t xmin2 = prm2[1] - 3 * prm2[2];
 Double_t xmin2 = prm2[1] - 2.5 * prm2[2];
// Double_t xmax2 = prm2[1] + 3 * prm2[2];
 Double_t xmax2 = prm2[1] + 2.5 * prm2[2];
 h41ti->GetXaxis()->SetRangeUser(xmin2,xmax2);
 Double_t mean2 = h41ti->GetMean();
 Double_t mass2 = mean2 * amu * z * ele * 1.e3;
 Double_t diff2 = mean2 - ref_41ti;
 Double_t massdiff2 = diff2 * amu * z;
 Double_t t_41ti = tof_func(L,ele,z,Brho,c,mass2); // [ps]
 Double_t tdiff2 = t_41ti - t_ref_41ti;
  fout2 << i << "  " << prm2[0] << "  " << prm2[1] << "  " << prm2[2] << "  " << nh41ti  << "  " << mean2  << "  " << diff2 << "  " << massdiff2 << "  " << tdiff2 << endl;

 delete gROOT->Get("h41ti");
 delete gROOT->Get("f2");
 delete gROOT->Get("prm2");
}

TH1F *h43ti = (TH1F*)gDirectory->Get(Form("mass_st2_43ti_2nd_%d",i));
 Int_t nh43ti = h43ti->GetEntries();
 h43ti->Fit("gaus","L","",1.951258828,1.953381172);
 if( nh43ti < 200 ){
  fout3 << i << " " << 0 << " " << 0 << " " << 0 << " " << nh43ti <<  endl;
 delete gROOT->Get("h43ti");
}else{
 TF1 *f3 = h43ti->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
// Double_t xmin3 = prm3[1] - 3 * prm3[2];
 Double_t xmin3 = prm3[1] - 2.5 * prm3[2];
// Double_t xmax3 = prm3[1] + 3 * prm3[2];
 Double_t xmax3 = prm3[1] + 2.5 * prm3[2];
 h43ti->GetXaxis()->SetRangeUser(xmin3,xmax3);
 Double_t mean3 = h43ti->GetMean();
 Double_t mass3 = mean3 * amu * z * ele *1.e3;
 Double_t diff3 = mean3 - ref_43ti;
 Double_t massdiff3 = diff3 * amu * z;
 Double_t t_43ti = tof_func(L,ele,z,Brho,c,mass3); // [ps]
 Double_t tdiff3 = t_43ti - t_ref_43ti;
  fout3 << i << "  " << prm3[0] << "  " << prm3[1] << "  " << prm3[2] << "  " << nh43ti << "  " << mean3 << "  " << diff3 << "  " << massdiff3 << "  " << tdiff3 << endl;

 delete gROOT->Get("h43ti");
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

