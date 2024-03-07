#ifndef __CINT__
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TTree.h>
#include <TString.h>
#include <TF1.h>
#include <TH2F.h>
#include <TH2Poly.h>
#include <TDirectory.h>
#include <TGraph.h>
#include <TRandom.h>
#include <TMath.h>
#include "TRandomGraph.h"
#include <TROOT.h>
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

void GetTimingOffsetRun(){

  TH1D *htmean1 = (TH1D*)gROOT->FindObject("hs2st1run_1");
  TH1D *htmean2 = (TH1D*)gROOT->FindObject("hs2st2run_1");
  TH1D *htmean3 = (TH1D*)gROOT->FindObject("hf3st1run_1");

//  Int_t Nbins = hq0up->GetXaxis()->GetNbins();
  Int_t Nbins = 103;

 Double_t meanst1[Nbins];
 Double_t meanst2[Nbins];
 Double_t meanf3st1[Nbins];

// ofstream fout("/home/sh13/art_analysis/user/hanai/prm/dia/S2StripOffsetRun.dat");
 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/dia/F3S2StripOffsetRun.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


for(int i = 1; i < Nbins+1; i++){

 Int_t j = i + 169;

 Double_t mean1 = htmean1->GetBinContent(i);
 meanst1[i] = mean1;

 Double_t mean2 = htmean2->GetBinContent(i);
 meanst2[i] = mean2;

 Double_t mean3 = htmean3->GetBinContent(i);
 meanf3st1[i] = mean3;

// Double_t tdiff = mean2 - mean1;

// fout << j << "  " << mean1 << "  " << mean2 << "  " << tdiff << endl;
 fout << j << "  " << mean1 << "  " << mean2 << "  " << mean3 << endl;


}



 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/dia/S2StripOffsetRun_cal.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


for(int i = 1; i < Nbins+1; i++){

 Int_t j = i + 169;

 Double_t mean1_cal = meanst1[i] - meanst1[66];
 Double_t mean2_cal = meanst2[i] - meanst2[66];

// Double_t tdiff_cal = mean2_cal - mean1_cal;

// fout1 << j << "  " << mean1_cal << "  " << mean2_cal << "  " << tdiff_cal << endl;
 fout1 << j << "  " << mean1_cal << "  " << mean2_cal  << endl;


}







}
