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



void massfit_all_refliseS_epsilon(){

 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/stm/fit.refliseS_8step_unitlise_SSSR_mahala.dat");
 if(fout.fail()){
	 cout << "Error; Could not open output file1.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 TFile* file = TFile::Open("output/mass/mass_calib_svd_4th_eachstrip_stm2_refliseS_8step_unitlise_SSR_mahala.hist.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }


 Int_t Nref = 20;
 
 char hname[10];
 Double_t fmin;
 Double_t fmax;
 Double_t ref;


for (int i = 0; i < Nref; i++){
switch(i){
	case 0:
		sprintf(hname,"h38Ca");
		fmin = 1.8974;
		fmax = 1.899;
		ref = 1.89826838;
		break;
	case 1:
		sprintf(hname,"h39Ca");
		fmin = 1.9472;
		fmax = 1.9485;
		ref = 1.94798796;
     	break;
	case 2:
		sprintf(hname,"h40Sc");
		fmin = 1.9024;
		fmax = 1.904;
		ref = 1.90316521;
		break;
	case 3:
		sprintf(hname,"h41Sc");
		fmin = 1.94961;
		fmax = 1.9512;
		ref = 1.95036921;
		break;
	case 4:
		sprintf(hname,"h40Ti");
		fmin = 1.816;
		fmax = 1.818;
		ref =  1.81719569;
		break;
	case 5:
		sprintf(hname,"h41Ti");
		fmin = 1.86161;
		fmax = 1.863;
		ref = 1.86232290;
		break;
	case 6:
		sprintf(hname,"h42Ti");
		fmin = 1.90661;
		fmax = 1.908;
		ref = 1.90731844;
		break;
	case 7:
		sprintf(hname,"h43V");
		fmin = 1.8674;
		fmax = 1.869;
		ref = 1.86818142;
		break;
	case 8:
		sprintf(hname,"h44V");
		fmin = 1.91;
		fmax = 1.912;
		ref = 1.91138485;
		break;
	case 9:
		sprintf(hname,"h44Cr");
		fmin = 1.831;
		fmax = 1.833;
		ref = 1.83218575;
		break;
	case 10:
		sprintf(hname,"h45Cr");
		fmin = 1.8728;
		fmax = 1.874;
		ref = 1.87358000;
		break;
	case 11:
		sprintf(hname,"h46Cr");
		fmin = 1.914;
		fmax = 1.9155;
		ref = 1.91480106;
		break;
	case 12:
		sprintf(hname,"h47Cr");
		fmin = 1.9555;
		fmax = 1.9565;
		break;
	case 13:
		sprintf(hname,"h46Mn");
		fmin = 1.838;
		fmax = 1.84;
		ref = 1.83891945;
		break;
	case 14:
		sprintf(hname,"h47Mn");
		fmin = 1.8775;
		fmax = 1.879;
		ref = 1.87848359;
		break;
	case 15:
		sprintf(hname,"h48Mn");
		fmin = 1.9175;
		fmax = 1.9185;
		ref = 1.91819472;
		break;
	case 16:
		sprintf(hname,"h48Fe");
		fmin = 1.844;
		fmax = 1.8455;
		ref = 1.84486307;
		break;
	case 17:
		sprintf(hname,"h49Fe");
		fmin = 1.882;
		fmax = 1.8835;
		ref = 1.88304627;
		break;
	case 18:
		sprintf(hname,"h50Co");
		fmin = 1.85;
		fmax = 1.851;
		ref = 1.85060539;
		break;
	case 19:
		sprintf(hname,"h52Ni");
		fmin = 1.855;
		fmax = 1.856;
		ref = 1.85573090;
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
// Double_t xmin1 = prm1[1] - 2 * prm1[2];
 Double_t xmax1 = prm1[1] + 3 * prm1[2];
// Double_t xmax1 = prm1[1] + 2 * prm1[2];
 h->GetXaxis()->SetRangeUser(xmin1,xmax1);
 Double_t mean1 = h->GetMean();
 Double_t integral = h->Integral();

  fout.precision(8);

  fout << hname << ":  "<< mean1 <<  "  " << prm1[0] << "  " << prm1[1] << "  " << prm1[2] << "  " << nh << "  " << " " << xmin1 << "  " << xmax1 <<  "  " << integral << endl;

  cout << mean1 << endl;


 h->Draw();
 TLine *l = new TLine(ref,0,ref,100000);
 l->Draw("same");

 delete gROOT->Get("h");
 delete gROOT->Get("l");
 delete gROOT->Get("func");
 delete gROOT->Get("prm1"); 
 

}

 fout.close();



}

