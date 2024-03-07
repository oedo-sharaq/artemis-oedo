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

void srppac_qcalib(){

  TH1D *hq0up = (TH1D*)gROOT->FindObject("hq0idup_1");
  TH1D *hq0low = (TH1D*)gROOT->FindObject("hq0idlow_1");

//  Int_t Nbins = hq0up->GetXaxis()->GetNbins();
  Int_t Nbins = 53;

 Double_t ave_up = 0;
 Double_t ave_low = 0;
// vector<Double_t> meanup[Nbins],meanlow[Nbins];
 Double_t meanup[Nbins];
 Double_t meanlow[Nbins];
// TArrayD(Nbins) meanup;
// TArrayD(Nbins) meanlow;

//for(int i = 0; i < Nbins+1; i++){
for(int i = 0; i < Nbins; i++){

 Int_t j = i + 5;

 Double_t mean1 = hq0up->GetBinContent(j);
 meanup[i] = mean1;
 ave_up += mean1/Nbins;

 Double_t mean2 = hq0low->GetBinContent(j);
 meanlow[i] = mean2;
 ave_low += mean2/Nbins;

}

// cout << "Nbins =" << Nbins << ", ave_up =" << ave_up << ", ave_low =" << ave_low << endl;
 cout << "Nbins = " << Nbins << ", ave_up = " << ave_up << ", ave_low = " << ave_low << endl;
// cout << "meanup[40] " << meanup[40] << " meanup[50] " << meanup[50] << " meanup[60] " << meanup[60] << endl;

//vector<Double_t> con[Nbins],lin[Nbins];
 Double_t con[Nbins];
 Double_t lin[Nbins];
// TArrayD(Nbins) con;
// TArrayD(Nbins) lin;

 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/srppac/qcalib_x_41ti_ref6_6th.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


for(int i = 0; i < Nbins; i++){

 lin[i] = (ave_up - ave_low) / (meanup[i] - meanlow[i]);

 con[i] = ave_up - lin[i] * meanup[i];

 fout << con[i] << "  " << lin[i] << endl;

  }


}
