#ifndef __CINT__
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TTree.h>
#include <TDecompLU.h>
#include <TDecompChol.h>
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

void GetTimingOffsetRun_draw(){


 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/dia/F3S2StripOffsetRun_v2_draw.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 const Int_t Nrun = 103;

for(int i = 1; i <= Nrun; i++){

  Int_t j = i + 169;

  cout << " Get Mean valie Run" << j << endl;

  gROOT->ProcessLine(Form("cd %d",i));

  TH1D *htf3st1run = (TH1D*)gROOT->FindObject(Form("tofff3st1_%d",j));
  TH1D *hts2st1run = (TH1D*)gROOT->FindObject(Form("toffs2st1_%d",j));
  TH1D *hts2st2run = (TH1D*)gROOT->FindObject(Form("toffs2st2_%d",j));
  TH1D *htofrun    = (TH1D*)gROOT->FindObject(Form("tofrun_%d",j));
  TH1D *haqrun     = (TH1D*)gROOT->FindObject(Form("aqrun_%d",j));

   Double_t tf3st1mean = htf3st1run->GetMean();
   Double_t ts2st1mean = hts2st1run->GetMean();
   Double_t ts2st2mean = hts2st2run->GetMean();
   Double_t tofmean    = htofrun->GetMean();
   Double_t aqmean     = haqrun->GetMean();


   fout << j << "  " << tf3st1mean << "  " << ts2st1mean  << "  " << ts2st2mean << "  " << tofmean << "  " << aqmean << endl;

//  delete htf3st1run;
//  delete hts2st1run;
//  delete hts2st2run;
//  delete htofrun;   
//  delete haqrun;     

  gROOT->ProcessLine("cd ..");


}


  fout.close();



}
