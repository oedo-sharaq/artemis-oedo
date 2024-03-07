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



void massfit_all_ref8_epsilon(){

// ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fit.ref7_8step_unit2.5_SSSR.dat");
// ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fit.ref7_8step_unit2.5_SSSR_epsilon.dat");
 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fit.ref7_8step_reunit.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file1.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

// TFile* file = TFile::Open("output/mass/mass_calib_svd_4th_eachstrip_stm2_ref7_8step_unit2.5_SSR.hist.root");
 TFile* file = TFile::Open("output/mass/mass_calib_svd_4th_eachstrip_stm2_ref7_8step_reunit.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }


 Int_t Nref = 28;
 
 char hname[10];
 Double_t fmin;
 Double_t fmax;


for (int i = 0; i < Nref; i++){
switch(i){
	case 0:
		sprintf(hname,"h38Ca");
		fmin = 1.8975;
		fmax = 1.899;
		break;
	case 1:
		sprintf(hname,"h39Ca");
		fmin = 1.94651;
		fmax = 1.9485;
     	break;
	case 2:
		sprintf(hname,"h41Ca");
		fmin = 2.0465;
		fmax = 2.0485;
		break;
	case 3:
		sprintf(hname,"h40Sc");
		fmin = 1.902;
		fmax = 1.904;
		break;
	case 4:
		sprintf(hname,"h41Sc");
		fmin = 1.9495;
		fmax = 1.951;
		break;
	case 5:
		sprintf(hname,"h43Sc");
		fmin = 2.0445;
		fmax = 2.046;
		break;
	case 6:
		sprintf(hname,"h40Ti");
		fmin = 1.816;
		fmax = 1.818;
		break;
	case 7:
		sprintf(hname,"h41Ti");
		fmin = 1.861;
		fmax = 1.863;
		break;
	case 8:
		sprintf(hname,"h42Ti");
		fmin = 1.906;
		fmax = 1.908;
		break;
	case 9:
		sprintf(hname,"h43V");
		fmin = 1.867;
		fmax = 1.869;
		break;
	case 10:
		sprintf(hname,"h44V");
		fmin = 1.91;
		fmax = 1.912;
		break;
	case 11:
		sprintf(hname,"h46V");
		fmin = 1.997;
		fmax = 1.9985;
		break;
	case 12:
		sprintf(hname,"h47V");
		fmin = 2.04;
		fmax = 2.0414;
		break;
	case 13:
		sprintf(hname,"h44Cr");
		fmin = 1.831;
		fmax = 1.833;
		break;
	case 14:
		sprintf(hname,"h45Cr");
		fmin = 1.872;
		fmax = 1.874;
		break;
	case 15:
		sprintf(hname,"h46Cr");
		fmin = 1.914;
		fmax = 1.9155;
		break;
	case 16:
		sprintf(hname,"h47Cr");
		fmin = 1.9555;
		fmax = 1.9565;
		break;
	case 17:
		sprintf(hname,"h51Cr");
		fmin = 2.121;
		fmax = 2.123;
		break;
	case 18:
		sprintf(hname,"h46Mn");
		fmin = 1.838;
		fmax = 1.84;
		break;
	case 19:
		sprintf(hname,"h47Mn");
		fmin = 1.8775;
		fmax = 1.879;
		break;
	case 20:
		sprintf(hname,"h48Mn");
		fmin = 1.917;
		fmax = 1919;
		break;
	case 21:
		sprintf(hname,"h49Mn");
		fmin = 1.957;
		fmax = 1.958;
		break;
	case 22:
		sprintf(hname,"h48Fe");
		fmin = 1.844;
		fmax = 1.8455;
		break;
	case 23:
		sprintf(hname,"h49Fe");
		fmin = 1.882;
		fmax = 1.8835;
		break;
	case 24:
		sprintf(hname,"h50Fe");
		fmin = 1.9205;
		fmax = 1.9215;
		break;
	case 25:
		sprintf(hname,"h50Co");
		fmin = 1.85;
		fmax = 1.851;
		break;
	case 26:
		sprintf(hname,"h51Co");
		fmin = 1.8865;
		fmax = 1.8875;
		break;
	case 27:
		sprintf(hname,"h52Ni");
		fmin = 1.855;
		fmax = 1.856;
		break;
	default:
		sprintf(hname,"h38Ca");
		fmin = 1.8975;
		fmax = 1.899;
		break;
}

 TH1D *h = (TH1D*)gDirectory->Get(Form("%s",hname));
 Int_t nh = h->GetEntries();
 h->Fit("gaus","L","",fmin,fmax);
 TF1 *func = h->GetFunction("gaus");
 const Double_t *prm1 = func->GetParameters();
 const Double_t *error1 = func->GetParErrors();
 Double_t xmin1 = prm1[1] - 3 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
 h->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h->GetMean();
 Double_t integral = h->Integral();

  fout.precision(8);

  fout << hname << ":  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh << "  " << mean1 << " " << xmin1 << "  " << xmax1 <<  "  " << integral << endl;

  cout << mean1 << endl;

 delete gROOT->Get("h");
 delete gROOT->Get("func");
 delete gROOT->Get("prm1"); 
 

}

 fout.close();

// file->Close();


}

