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
#include <TMinuit.h>
#endif

// variable, regerence, error
//double data[5][3] = {
// 8.51737, 20, 0.1,
// 9.505803, 22, 0.1,
// 9.917254, 23, 0.1,
// 10.41622, 24, 0.1,
// 11.33647, 26, 0.1,
//};

void chi2(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){

int Ndata = 10;

double data[10][3] = {
// 8.51737, 20, 0.1,
// 9.505803, 22, 0.1,
// 9.917254, 23, 0.1,
// 10.41622, 24, 0.1,
// 11.33647, 26, 0.1

// 17.07, 17, 0.15,
// 17.98, 18, 0.15,
// 18.95, 19, 0.15,
// 19.93, 20, 0.15,
// 20.9, 21, 0.15,
// 21.91, 22, 0.15,
// 22.91, 23, 0.15,
// 23.93, 24, 0.15,
// 24.92, 25, 0.15,
// 25.96, 26, 0.15

 17.24, 17, 0.15,
 18, 18, 0.15,
 18.84, 19, 0.15,
 19.82, 20, 0.15,
 20.78, 21, 0.15,
 21.8, 22, 0.15,
 22.79, 23, 0.15,
 23.81, 24, 0.15,
 24.8, 25, 0.15,
 25.85, 26, 0.15


};


 Double_t chisq = 0.;


for (int i = 0; i < Ndata; i++){
	Double_t func = 0;

    func = par[0] + par[1] * data[i][0] + par[2] * TMath::Power(data[i][0],2) + par[3] * TMath::Power(data[i][0],3) + par[4] * TMath::Power(data[i][0],4);

	chisq += TMath::Power((data[i][1] - func)/data[i][2],2);

  }
  f = chisq;
 
}

int z_cal_ssd(){

  TMinuit *min = new TMinuit(5);
  min->SetPrintLevel(1);
  min->SetFCN(chi2); 
  int ierflg = 0;

   min->DefineParameter(0,"p0",0,0.001,-10.,10.);
   min->DefineParameter(1,"p1",0,0.001,-10.,10.);
   min->DefineParameter(2,"p2",0,0.001,-10.,10.);
   min->DefineParameter(3,"p3",0,0.001,-10.,10.);
   min->DefineParameter(0,"p4",0,0.001,-10.,10.);
//  min->mnparm(1,"p1",0,0.1,0,0,0);
//  min->mnparm(2,"p2",0,0.1,0,0,0);
//  min->mnparm(3,"p3",0,0.1,0,0,0);
//  min->mnparm(4,"p4",0,0.1,0,0,0);

//  min->Migrad()
  int migrad_stats = min->Migrad();
  Double_t par0,par1,par2,par3,par4;
  Double_t par0_err,par1_err,par2_err,par3_err,par4_err;

  min->GetParameter(0,par0,par0_err);
  min->GetParameter(1,par1,par1_err);
  min->GetParameter(2,par2,par2_err);
  min->GetParameter(3,par3,par3_err);
  min->GetParameter(4,par4,par4_err);
 
  cout<<"*******************************************" <<endl;
  cout<<"constant:   " << par0 << " +/- " << par0_err <<endl;
  cout<<"first:      " << par1 << " +/- " << par1_err <<endl;
  cout<<"second:     " << par2 << " +/- " << par2_err <<endl;
  cout<<"third_up:      " << par3 << " +/- " << par3_err <<endl;
  cout<<"forth_up:      " << par4 << " +/- " << par4_err <<endl;
  cout<<"Status of Migrad: " << migrad_stats<<endl;

//   std::ofstream foutmtrth("/home/sh13/art_analysis/user/hanai/prm/ssd/z_cal_2nd.dat");
   std::ofstream foutmtrth("/home/sh13/art_analysis/user/hanai/prm/plastic/z_cal_2nd.dat");
 if (foutmtrth.fail()){
	 cout << "Error; Could not open output file..." << endl << endl;
	 return 0;
  }
   foutmtrth <<  par0 << " " << par1 << " "  << par2 << " " << par3 << " " << par4  << endl;
   foutmtrth.close();


  return 0;

}








