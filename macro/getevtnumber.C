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

void getevtnumber(){

 ofstream fout1("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.39ca_aq.170272.dat");
 if(fout1.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st1_2step.170272.ca.hist.root");
// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_2nd_all.170272.hist.root");
 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_BLD_3rd_all.170272.hist.root");
 if(!file){
	 printf("cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

for(int i = 170; i < 273; i++){

 int j = i - 169;
 
 gROOT->ProcessLine(Form("cd %d",j));

 cout << "Fitting run" <<  i << "starts" << endl << endl;

TH1F *h39ca = (TH1F*)gDirectory->Get(Form("h39ca_aq_%d",i));
 Int_t nh39ca = h39ca->GetEntries();
//  fout1 << "[Run Number]    [Entry]" << endl;  
	fout1 << i << "  " <<  nh39ca <<  endl;


 delete gROOT->Get("h39ca");

 fout1.close();
}

 file->Close();


}

