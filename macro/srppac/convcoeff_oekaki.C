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

void convcoeff_oekaki(){

 double x_array[400];
 double content_array[400];


 ifstream fin("/home/sh13/art_analysis/user/hanai/xc0_copy_oekaki.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

   for(int i = 0; i < 400; i++){
//	    fin >> x_array[i] >> content_array[i];
	    fin >>  content_array[i];
		}
 
 fin.close();


 TH1D *h = new TH1D("convcoeff","convcoeff",400,0,0.4);

 for(int j = 0; j < 400; j++){
   h->SetBinContent(j+1,content_array[j]);
   }

gROOT->ProcessLine("zon");
h->Draw();


}
