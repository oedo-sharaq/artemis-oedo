#ifndef __CINT__ 
#include "TMath.h"
#include "TF1.h"
#endif
#include "TH2.h"

#include "TMinuit.h"

void extract_hist(){
 
 ofstream fout1("AoQ_corst2_2nd.dat");
   if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


  TFile *file = TFile::Open(Form("sh13_analysis/hanai/phys/merge/mass_corst2_2nd_all.170272.hist.root"));

  TH1D *hist = (TH1D*)gROOT->FindObject("haq_all"); // calibration histgram

  TAxis *xaxis = hist->GetXaxis();

  int nxbins = xaxis->GetNbins();
  
   for(int i = 1; i < nxbins + 1; i++){

     int count = hist->GetBinContent(i);
     double xc = xaxis->GetBinCenter(i);
     
     fout1 << xc << "  " << count << endl;

  }









 }




