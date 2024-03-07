
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

#include "TPIDwTOFPPACSSDProcessor.h"
#include "TDiaTimingData.h"
#include "TMWDCTrackingProcessor.h"
#include "TMWDCTrackingResult.h"
#include "TSRPPACPlaneDqdxProcessor.h"

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

void mass_calib_svd_3rd_kai(){

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.all.170272.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }
//  const Int_t Nrun = 250;  //the number of runs
  const Int_t Nrun = 2500;  //the number of runs
  const Int_t Nref =  21;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nprm =  168;  //the number of parameters

 TClonesArray *array_mass = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_s0 = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");
// TTree *tree = dynamic_cast<TTree*>(gDirectory->Get("tree"));
// if(!tree){
//	 printf("No tree named 'tree' exists\n");
//	 return;
// }

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("sr0_xcw",1);

//// Load a input file
// std::vector<TString> Tag[Nref];
 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;
// vector<Double_t> Ref_m[Nref], Z_low[Nref], Z_up[Nref], Aq_low[Nref], Aq_up[Nref];
// double Ref_m, Z_low, Z_up, Aq_low, Aq_up;
// double Ref_m = new double[Nref],
// double Z_low  = new double[Nref];
// double Z_up   = new double[Nref];
// double Aq_low = new double[Nref];
// double Aq_up = new double[Nref];


 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_try.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

//  int i = 0;
// char come;
//  while(getline(fin,come)){
  while(!fin.eof()){
//	  if(come[0]=='#'){
//		  continue;
//	  }else{
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);

		}
//  }
 fin.close();


//   if(i != Nref){
//	 cout << "The nuber of events is" << i << "Not equal to" << Nref << endl;
// }
 
// for (int j = 0; j <= Nref; j++){
// 
////  cout << Tag[j] << Ref_m[j] << Z_low[j] << Z_up[j] << Aq_low[j] << Aq_up[j] << endl;
//  cout << "Reference N0." << j << " = " << Ref_m[j] << " " << Z_low[j] << " " << Z_up[j] << " " << Aq_low[j] << " " << Aq_up[j] << endl;
// 
// }

 TMatrixD A(Nevt,Nprm);
 TMatrixD b(Nevt,1);
 TMatrixD value(Nevt,8); // output the fitting value 

 Int_t nrow = A.GetNrows();
 Int_t nrow_b = b.GetNrows();
// Int_t nrow_at = At.GetNrows();
 cout << "Number of rows of A is " << nrow << endl;
 cout << "Number of rows of b is " << nrow_b << endl;
// cout << "Number of rows of At is " << nrow_at << endl;

//// Fill date 

 int ievt = 0;
 Bool_t HasEvents = true;
 Int_t nData = tree->GetEntries();

for (int iref = 0; iref < Nref; iref++){
    vector<Int_t> irandm;
	int n_tmp = 0;

  for(int i = 0; i < nData; i++){
	  tree->GetEntry(i);

      Int_t hit_mass = array_mass->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_tracku > 0 && hit_s0 >0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsProcessed();

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok)
    {
      irandm.push_back(i);
      n_tmp++;
     }else {
       continue;
    	}
    }else{
	  continue;
       }
   }

  if (n_tmp < Nrun){
    cout << "Caution!! Reference No." << iref << " does not have enough number of events.\n";
    HasEvents = false;  
	continue;
    }else{
      cout << "Sampling events of Reference No." << iref << " was finished.\n";
    }

//// Generate random run number
     for (int r = 0; r < Nrun; r++){
         int j = gRandom->Uniform(r,n_tmp);
		 int randm_tmp = irandm[r];
		 irandm[r] = irandm[j];
       	 irandm[j] = randm_tmp;
     }

//// Fill data in matrix for each Ref	 
   for(int p = 0; p < Nrun; p++){
     int k = irandm[p];
     tree->GetEntry(k);
	 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t z_select = mass->GetZ();
     Double_t aq_select = mass->GetAq();

//     Double_t t = mass->GetTof();
//     Double_t x3 = tracku->GetX();
//     Double_t a3 = tracku->GetA() * 1000.;
//     Double_t y3 = tracku->GetY();
//     Double_t b3 = tracku->GetB() * 1000.;
//     Double_t x0 = sr0->GetPosition();
 
     Double_t ti = mass->GetTof();
     Double_t x3i = tracku->GetX();
     Double_t a3i = tracku->GetA() * 1000.;
     Double_t y3i = tracku->GetY();
     Double_t b3i = tracku->GetB() * 1000.;
     Double_t x0i = sr0->GetPosition();
// unit orientation
     Double_t t = (ti - 2042.) * 0.25;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1;
     Double_t y3 = y3i * 0.1;
     Double_t b3 = b3i * 0.1;
     Double_t x0 = x0i * 0.1; 

     A(ievt,0) = 1.; 
     A(ievt,1) = x3;
     A(ievt,2) = a3;
     A(ievt,3) = y3;
     A(ievt,4) = b3;
     A(ievt,5) = x0;
     A(ievt,6) = x3 * a3;
     A(ievt,7) = x3 * y3;
     A(ievt,8) = x3 * b3;
     A(ievt,9) = x3 * x0;
     A(ievt,10) = a3 * y3; 
     A(ievt,11) = a3 * b3; 
     A(ievt,12) = a3 * x0; 
     A(ievt,13) = y3 * b3; 
     A(ievt,14) = y3 * x0; 
     A(ievt,15) = b3 * x0; 
     A(ievt,16) = x3 * x3; 
     A(ievt,17) = a3 * a3; 
     A(ievt,18) = y3 * y3; 
     A(ievt,19) = b3 * b3; 
     A(ievt,20) = x0 * x0; 
     A(ievt,21) = x3 * a3 * y3; 
     A(ievt,22) = x3 * a3 * b3; 
     A(ievt,23) = x3 * a3 * x0; 
     A(ievt,24) = x3 * y3 * b3; 
     A(ievt,25) = x3 * y3 * x0; 
     A(ievt,26) = x3 * b3 * x0; 
     A(ievt,27) = a3 * y3 * b3; 
     A(ievt,28) = a3 * y3 * x0; 
     A(ievt,29) = a3 * b3 * x0; 
     A(ievt,30) = y3 * b3 * x0; 
     A(ievt,31) = x3 * x3 * a3; 
     A(ievt,32) = x3 * x3 * y3; 
     A(ievt,33) = x3 * x3 * b3; 
     A(ievt,34) = x3 * x3 * x0; 
     A(ievt,35) = a3 * a3 * x3; 
     A(ievt,36) = a3 * a3 * y3; 
     A(ievt,37) = a3 * a3 * b3; 
     A(ievt,38) = a3 * a3 * x0; 
     A(ievt,39) = y3 * y3 * x3; 
     A(ievt,40) = y3 * y3 * a3; 
     A(ievt,41) = y3 * y3 * b3; 
     A(ievt,42) = y3 * y3 * x0; 
     A(ievt,43) = b3 * b3 * x3; 
     A(ievt,44) = b3 * b3 * a3; 
     A(ievt,45) = b3 * b3 * y3; 
     A(ievt,46) = b3 * b3 * x0; 
     A(ievt,47) = x0 * x0 * x3; 
     A(ievt,48) = x0 * x0 * a3; 
     A(ievt,49) = x0 * x0 * y3; 
     A(ievt,50) = x0 * x0 * b3; 
     A(ievt,51) = x3 * x3 * x3; 
     A(ievt,52) = a3 * a3 * a3; 
     A(ievt,53) = y3 * y3 * y3; 
     A(ievt,54) = b3 * b3 * b3; 
     A(ievt,55) = x0 * x0 * x0; 

     A(ievt,56) = 1. * t; 
     A(ievt,57) = x3 * t;
     A(ievt,58) = a3 * t;
     A(ievt,59) = y3 * t;
     A(ievt,60) = b3 * t;
     A(ievt,61) = x0 * t;
     A(ievt,62) = x3 * a3 * t;
     A(ievt,63) = x3 * y3 * t;
     A(ievt,64) = x3 * b3 * t;
     A(ievt,65) = x3 * x0 * t;
     A(ievt,66) = a3 * y3 * t; 
     A(ievt,67) = a3 * b3 * t; 
     A(ievt,68) = a3 * x0 * t; 
     A(ievt,69) = y3 * b3 * t; 
     A(ievt,70) = y3 * x0 * t; 
     A(ievt,71) = b3 * x0 * t; 
     A(ievt,72) = x3 * x3 * t; 
     A(ievt,73) = a3 * a3 * t; 
     A(ievt,74) = y3 * y3 * t; 
     A(ievt,75) = b3 * b3 * t; 
     A(ievt,76) = x0 * x0 * t; 
     A(ievt,77) = x3 * a3 * y3 * t; 
     A(ievt,78) = x3 * a3 * b3 * t; 
     A(ievt,79) = x3 * a3 * x0 * t; 
     A(ievt,80) = x3 * y3 * b3 * t; 
     A(ievt,81) = x3 * y3 * x0 * t; 
     A(ievt,82) = x3 * b3 * x0 * t; 
     A(ievt,83) = a3 * y3 * b3 * t; 
     A(ievt,84) = a3 * y3 * x0 * t; 
     A(ievt,85) = a3 * b3 * x0 * t; 
     A(ievt,86) = y3 * b3 * x0 * t; 
     A(ievt,87) = x3 * x3 * a3 * t; 
     A(ievt,88) = x3 * x3 * y3 * t; 
     A(ievt,89) = x3 * x3 * b3 * t; 
     A(ievt,90) = x3 * x3 * x0 * t; 
     A(ievt,91) = a3 * a3 * x3 * t; 
     A(ievt,92) = a3 * a3 * y3 * t; 
     A(ievt,93) = a3 * a3 * b3 * t; 
     A(ievt,94) = a3 * a3 * x0 * t; 
     A(ievt,95) = y3 * y3 * x3 * t; 
     A(ievt,96) = y3 * y3 * a3 * t; 
     A(ievt,97) = y3 * y3 * b3 * t; 
     A(ievt,98) = y3 * y3 * x0 * t; 
     A(ievt,99) = b3 * b3 * x3 * t; 
     A(ievt,100) = b3 * b3 * a3 * t; 
     A(ievt,101) = b3 * b3 * y3 * t; 
     A(ievt,102) = b3 * b3 * x0 * t; 
     A(ievt,103) = x0 * x0 * x3 * t; 
     A(ievt,104) = x0 * x0 * a3 * t; 
     A(ievt,105) = x0 * x0 * y3 * t; 
     A(ievt,106) = x0 * x0 * b3 * t; 
     A(ievt,107) = x3 * x3 * x3 * t; 
     A(ievt,108) = a3 * a3 * a3 * t; 
     A(ievt,109) = y3 * y3 * y3 * t; 
     A(ievt,110) = b3 * b3 * b3 * t; 
     A(ievt,111) = x0 * x0 * x0 * t; 

     A(ievt,112) = 1. * t * t; 
     A(ievt,113) = x3 * t * t;
     A(ievt,114) = a3 * t * t;
     A(ievt,115) = y3 * t * t;
     A(ievt,116) = b3 * t * t;
     A(ievt,117) = x0 * t * t;
     A(ievt,118) = x3 * a3 * t * t;
     A(ievt,119) = x3 * y3 * t * t;
     A(ievt,120) = x3 * b3 * t * t;
     A(ievt,121) = x3 * x0 * t * t;
     A(ievt,122) = a3 * y3 * t * t; 
     A(ievt,123) = a3 * b3 * t * t; 
     A(ievt,124) = a3 * x0 * t * t; 
     A(ievt,125) = y3 * b3 * t * t; 
     A(ievt,126) = y3 * x0 * t * t; 
     A(ievt,127) = b3 * x0 * t * t; 
     A(ievt,128) = x3 * x3 * t * t; 
     A(ievt,129) = a3 * a3 * t * t; 
     A(ievt,130) = y3 * y3 * t * t; 
     A(ievt,131) = b3 * b3 * t * t; 
     A(ievt,132) = x0 * x0 * t * t; 
     A(ievt,133) = x3 * a3 * y3 * t * t; 
     A(ievt,134) = x3 * a3 * b3 * t * t; 
     A(ievt,135) = x3 * a3 * x0 * t * t; 
     A(ievt,136) = x3 * y3 * b3 * t * t; 
     A(ievt,137) = x3 * y3 * x0 * t * t; 
     A(ievt,138) = x3 * b3 * x0 * t * t; 
     A(ievt,139) = a3 * y3 * b3 * t * t; 
     A(ievt,140) = a3 * y3 * x0 * t * t; 
     A(ievt,141) = a3 * b3 * x0 * t * t; 
     A(ievt,142) = y3 * b3 * x0 * t * t; 
     A(ievt,143) = x3 * x3 * a3 * t * t; 
     A(ievt,144) = x3 * x3 * y3 * t * t; 
     A(ievt,145) = x3 * x3 * b3 * t * t; 
     A(ievt,146) = x3 * x3 * x0 * t * t; 
     A(ievt,147) = a3 * a3 * x3 * t * t; 
     A(ievt,148) = a3 * a3 * y3 * t * t; 
     A(ievt,149) = a3 * a3 * b3 * t * t; 
     A(ievt,150) = a3 * a3 * x0 * t * t; 
     A(ievt,151) = y3 * y3 * x3 * t * t; 
     A(ievt,152) = y3 * y3 * a3 * t * t; 
     A(ievt,153) = y3 * y3 * b3 * t * t; 
     A(ievt,154) = y3 * y3 * x0 * t * t; 
     A(ievt,155) = b3 * b3 * x3 * t * t; 
     A(ievt,156) = b3 * b3 * a3 * t * t; 
     A(ievt,157) = b3 * b3 * y3 * t * t; 
     A(ievt,158) = b3 * b3 * x0 * t * t; 
     A(ievt,159) = x0 * x0 * x3 * t * t; 
     A(ievt,160) = x0 * x0 * a3 * t * t; 
     A(ievt,161) = x0 * x0 * y3 * t * t; 
     A(ievt,162) = x0 * x0 * b3 * t * t; 
     A(ievt,163) = x3 * x3 * x3 * t * t; 
     A(ievt,164) = a3 * a3 * a3 * t * t; 
     A(ievt,165) = y3 * y3 * y3 * t * t; 
     A(ievt,166) = b3 * b3 * b3 * t * t; 
     A(ievt,167) = x0 * x0 * x0 * t * t; 

     b(ievt,0) = Ref_m[iref];
  
     value(ievt,0) = z_select;
     value(ievt,1) = aq_select;
     value(ievt,2) = t;
     value(ievt,3) = x3;
     value(ievt,4) = a3;
     value(ievt,5) = y3;
     value(ievt,6) = b3;
     value(ievt,7) = x0;

	// cout << "Filling the data of evtnumber: " << ievt  << " was finished." << endl;

     ievt++;

	 }
	
}
 if(ievt != Nevt){
	 cout << "The number of events is " << ievt << " Not equal to " << Nevt << endl;
 }else{
	 cout << "The number of events is " << ievt << " " << endl;
	 }
 if(!HasEvents){
    cout << "Some species has not enough number of events,\n";
	return; 
 }




 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/mass/set_matrix_svd3rd.dat");
 if (fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	fout << b(n,0) << " | ";

	for(int m = 0; m < Nprm; m++){
		fout << A(n,m) << "  " ;
	}
	fout << "\n";
}

	fout.close();

 ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd3rd.dat");
 if (foutselect.fail()){
	 cout << "Error; Could not open output file for selected values..." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	for(int m = 0; m < 8; m++){
		foutselect << value(n,m) << "  "  << " | ";
	}
	foutselect << "\n";
}

	foutselect.close();


//// Set Matrix
////
 TMatrixD At(Nprm,Nevt);
          At.Transpose(A);

  TMatrixD Cov(Nprm,Nprm);
  Cov.Mult(At,A);

  TMatrixD Atb(Nprm,1);
  Atb.Mult(At,b);

  TVectorD Atb_v = TMatrixDColumn(Atb,0);
  
// Solve Normal Equation

  TDecompSVD svd(Cov);
  Bool_t ok;

  TVectorD Theta(Nprm);
  Theta = svd.Solve(Atb_v,ok);


// Save the results of LU decompose
  Double_t d1, d2;
  svd.Det(d1,d2);
  cout << "cond: " << svd.Condition() << endl;
  cout << "det: "  << d1*TMath::Power(2, d2) << endl;
  cout << "tol: " << svd.GetTol() << endl;
  Theta.Print();

   char foutname[50];
//   ofstream fout("output/mass/lu_out.dat");
//   sprintf(foutname, "output/mass/lu_out.dat");
   std::ofstream foutmtr("output/mass/svd3rd_out.dat");
 if (foutmtr.fail()){
	 cout << "Error; Could not open output file for SVD condition..." << endl << endl;
	 return;
  }
   foutmtr << "cond: " << svd.Condition() << endl;
   foutmtr << "det: "  << d1*TMath::Power(2, d2) << endl;
   foutmtr << "tol: " << svd.GetTol() << endl;
//   foutmtr << Theta.Print() << endl;

   foutmtr.close();

//   char foutnametheta[50];
//   ofstream fout("output/mass/lu_out.dat");
//   sprintf(foutname, "output/mass/lu_out.dat");
   std::ofstream foutmtrth("output/mass/theta.dat");
//   fout.open(foutname, std::ios::out);
 if (foutmtrth.fail()){
	 cout << "Error; Could not open output file for Theta matrix..." << endl << endl;
	 return;
  }
for (int itheta = 0; itheta < Nprm; itheta++){
   foutmtrth <<  Theta(itheta) << endl;
}
   foutmtrth.close();


//// Comfirm the condition of decomposition

Double_t cond = svd.Condition();

int p = 0;
while( p < 1){
printf("The condition is %f.\n Would you like to continue?(y/n)\n",cond);
char ans[256];
//scanf("%s",ans);
cin >> ans;

if(strcmp(ans,"y")==0){
   	printf("Generating histograms\n");
	p++;
}else if (strcmp(ans,"n")==0){
    return 0;
}else{
   printf("please answer y/n \n");
   p = 0;
}}



//// Check the solution

 TVectorD b_re(Nevt);
// b_re = Mult(A,Theta);

for(int ic = 0; ic < Nevt; ic++ ){

 Double_t b_re_elem = 0.;

	for(int ir = 0; ir < Nprm; ir++ ){

 	   b_re_elem += A(ic,ir) * Theta(ir);

	}

	b_re(ic) = b_re_elem;
}

// b_re.Print();


 TH1D *h_aq_sol = new TH1D("aq_sol", "aq_sol",500,1.7,2.3);

 TH1D *h_39Ca_sol = new TH1D("h39Ca_sol", "h39Ca_sol",500,1.940,1.980);
 TH1D *h_40Ca_sol = new TH1D("h40Ca_sol", "h40Ca_sol",500,1.990,2.02);
 TH1D *h_41Ca_sol = new TH1D("h41Ca_sol", "h41Ca_sol",500,2.040,2.0650);
                                    
 TH1D *h_40Sc_sol = new TH1D("h40Sc_sol", "h40Sc_sol",500,1.900,1.925);
 TH1D *h_41Sc_sol = new TH1D("h41Sc_sol", "h41Sc_sol",500,1.940,1.970);
 TH1D *h_43Sc_sol = new TH1D("h43Sc_sol", "h43Sc_sol",500,2.035,2.060);
                                
 TH1D *h_40Ti_sol = new TH1D("h40Ti_sol", "h40Ti_sol",500,1.805,1.826);
 TH1D *h_41Ti_sol = new TH1D("h41Ti_sol", "h41Ti_sol",500,1.855,1.885);
 TH1D *h_43Ti_sol = new TH1D("h43Ti_sol", "h43Ti_sol",500,1.940,1.980);
                                         
 TH1D *h_43V_sol  = new TH1D("h43V_sol ", "h43V_sol ",500,1.865,1.890);
 TH1D *h_44V_sol  = new TH1D("h44V_sol ", "h44V_sol ",500,1.90,1.94);
 TH1D *h_45V_sol  = new TH1D("h45V_sol ", "h45V_sol ",500,1.941,1.983);
                                    
 TH1D *h_44Cr_sol = new TH1D("h44Cr_sol", "h44Cr_sol",500,1.825,1.858);
 TH1D *h_45Cr_sol = new TH1D("h45Cr_sol", "h45Cr_sol",500,1.855,1.90);
 TH1D *h_46Cr_sol = new TH1D("h46Cr_sol", "h46Cr_sol",500,1.90,1.940);
                                    
 TH1D *h_46Mn_sol = new TH1D("h46Mn_sol", "h46Mn_sol",500,1.832,1.855);
 TH1D *h_47Mn_sol = new TH1D("h47Mn_sol", "h47Mn_sol",500,1.860,1.897);
 TH1D *h_49Mn_sol = new TH1D("h49Mn_sol", "h49Mn_sol",500,1.90,1.940);
                                    
 TH1D *h_48Fe_sol = new TH1D("h48Fe_sol", "h48Fe_sol",500,1.8355,1.855);
 TH1D *h_49Fe_sol = new TH1D("h49Fe_sol", "h49Fe_sol",500,1.865,1.897);
 TH1D *h_50Fe_sol = new TH1D("h50Fe_sol", "h50Fe_sol",500,1.90,1.940);


 for (int isol = 0; isol < Nevt; isol++){
  h_aq_sol->Fill(b_re[isol]);
	 
	if(0 <= isol && isol  < 250){
	 h_39Ca_sol->Fill(b_re(isol));
 } else if(250 <= isol && isol  < 500){
	 h_40Ca_sol->Fill(b_re(isol));
 } else if(500 <= isol && isol  < 750){
	 h_41Ca_sol->Fill(b_re(isol));
 } else if(750 <= isol && isol  < 1000){
	 h_40Sc_sol->Fill(b_re(isol));
 } else if(1000 <= isol && isol  < 1250){
	 h_41Sc_sol->Fill(b_re(isol));
 } else if(1250 <= isol && isol  < 1500){
	 h_43Sc_sol->Fill(b_re(isol));
 } else if(1500 <= isol && isol  < 1750){
	 h_40Ti_sol->Fill(b_re(isol));
 } else if(1750 <= isol && isol  < 2000){
	 h_41Ti_sol->Fill(b_re(isol));
 } else if(2000 <= isol && isol  < 2250){
	 h_43Ti_sol->Fill(b_re(isol));
 } else if(2250 <= isol && isol  < 2500){
	 h_43V_sol->Fill(b_re(isol));
 } else if(2500 <= isol && isol  < 2750){
	 h_44V_sol->Fill(b_re(isol));
 } else if(2750 <= isol && isol  < 3000){
	 h_45V_sol->Fill(b_re(isol));
 } else if(3000 <= isol && isol  < 3250){
	 h_44Cr_sol->Fill(b_re(isol));
 } else if(3250 <= isol && isol  < 3500){
	 h_45Cr_sol->Fill(b_re(isol));
 } else if(3500 <= isol && isol  < 3750){
	 h_46Cr_sol->Fill(b_re(isol));
 } else if(3750 <= isol && isol  < 4000){
	 h_46Mn_sol->Fill(b_re(isol));
 } else if(4000 <= isol && isol  < 4250){
	 h_47Mn_sol->Fill(b_re(isol));
 } else if(4250 <= isol && isol  < 4500){
	 h_49Mn_sol->Fill(b_re(isol));
 } else if(4500 <= isol && isol  < 4750){
	 h_48Fe_sol->Fill(b_re(isol));
 } else if(4750 <= isol && isol  < 5000){
	 h_49Fe_sol->Fill(b_re(isol));
 } else if(5000 <= isol && isol  < 5250){
	 h_50Fe_sol->Fill(b_re(isol));
 }
}

	 


//// AoQ cor
   vector<Double_t> Aq_cor;
   TVectorD Rd(Nprm);
   vector<Int_t>evt_valid;

// TTree *new_tree = new TTree("new_tree","new_tree","recreate");
// Double_t mass_calib;
// new_tree->Branch("mass_calib",&mass_calib,"mass_calib/D");

   
  for (Int_t iData = 0; iData < nData; iData++){
    double sum = 0.;

     tree->GetEntry(iData);
	 art::TMassData *mass_cor = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku_cor = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0_cor = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

    Int_t hit_mass_cor = array_mass->GetEntriesFast();
    Int_t hit_tracku_cor = array_tracku->GetEntriesFast();
    Int_t hit_s0_cor = array_s0->GetEntriesFast();

     if ( hit_mass_cor > 0 && hit_tracku_cor > 0 && hit_s0_cor >0){
 
     Double_t ti_cor = mass_cor->GetTof();
     Double_t x3i_cor = tracku_cor->GetX();
     Double_t a3i_cor = tracku_cor->GetA() * 1000.;
     Double_t y3i_cor = tracku_cor->GetY();
     Double_t b3i_cor = tracku_cor->GetB() * 1000.;
     Double_t x0i_cor = sr0_cor->GetPosition();
// unit orientation
     Double_t t_cor = (ti_cor - 2042.) * 0.25;  
     Double_t x3_cor = x3i_cor * 0.1; 
     Double_t a3_cor = a3i_cor * 0.1;
     Double_t y3_cor = y3i_cor * 0.1;
     Double_t b3_cor = b3i_cor * 0.1;
     Double_t x0_cor = x0i_cor * 0.1; 


     Rd(0) = 1.; 
     Rd(1) = x3_cor;
     Rd(2) = a3_cor;
     Rd(3) = y3_cor;
     Rd(4) = b3_cor;
     Rd(5) = x0_cor;
     Rd(6) = x3_cor * a3_cor;
     Rd(7) = x3_cor * y3_cor;
     Rd(8) = x3_cor * b3_cor;
     Rd(9) = x3_cor * x0_cor;
     Rd(10) = a3_cor * y3_cor; 
     Rd(11) = a3_cor * b3_cor; 
     Rd(12) = a3_cor * x0_cor; 
     Rd(13) = y3_cor * b3_cor; 
     Rd(14) = y3_cor * x0_cor; 
     Rd(15) = b3_cor * x0_cor; 
     Rd(16) = x3_cor * x3_cor; 
     Rd(17) = a3_cor * a3_cor; 
     Rd(18) = y3_cor * y3_cor; 
     Rd(19) = b3_cor * b3_cor; 
     Rd(20) = x0_cor * x0_cor; 
     Rd(21) = x3_cor * a3_cor * y3_cor; 
     Rd(22) = x3_cor * a3_cor * b3_cor; 
     Rd(23) = x3_cor * a3_cor * x0_cor; 
     Rd(24) = x3_cor * y3_cor * b3_cor; 
     Rd(25) = x3_cor * y3_cor * x0_cor; 
     Rd(26) = x3_cor * b3_cor * x0_cor; 
     Rd(27) = a3_cor * y3_cor * b3_cor; 
     Rd(28) = a3_cor * y3_cor * x0_cor; 
     Rd(29) = a3_cor * b3_cor * x0_cor; 
     Rd(30) = y3_cor * b3_cor * x0_cor; 
     Rd(31) = x3_cor * x3_cor * a3_cor; 
     Rd(32) = x3_cor * x3_cor * y3_cor; 
     Rd(33) = x3_cor * x3_cor * b3_cor; 
     Rd(34) = x3_cor * x3_cor * x0_cor; 
     Rd(35) = a3_cor * a3_cor * x3_cor; 
     Rd(36) = a3_cor * a3_cor * y3_cor; 
     Rd(37) = a3_cor * a3_cor * b3_cor; 
     Rd(38) = a3_cor * a3_cor * x0_cor; 
     Rd(39) = y3_cor * y3_cor * x3_cor; 
     Rd(40) = y3_cor * y3_cor * a3_cor; 
     Rd(41) = y3_cor * y3_cor * b3_cor; 
     Rd(42) = y3_cor * y3_cor * x0_cor; 
     Rd(43) = b3_cor * b3_cor * x3_cor; 
     Rd(44) = b3_cor * b3_cor * a3_cor; 
     Rd(45) = b3_cor * b3_cor * y3_cor; 
     Rd(46) = b3_cor * b3_cor * x0_cor; 
     Rd(47) = x0_cor * x0_cor * x3_cor; 
     Rd(48) = x0_cor * x0_cor * a3_cor; 
     Rd(49) = x0_cor * x0_cor * y3_cor; 
     Rd(50) = x0_cor * x0_cor * b3_cor; 
     Rd(51) = x3_cor * x3_cor * x3_cor; 
     Rd(52) = a3_cor * a3_cor * a3_cor; 
     Rd(53) = y3_cor * y3_cor * y3_cor; 
     Rd(54) = b3_cor * b3_cor * b3_cor; 
     Rd(55) = x0_cor * x0_cor * x0_cor; 

     Rd(56) = 1. * t_cor; 
     Rd(57) = x3_cor * t_cor;
     Rd(58) = a3_cor * t_cor;
     Rd(59) = y3_cor * t_cor;
     Rd(60) = b3_cor * t_cor;
     Rd(61) = x0_cor * t_cor;
     Rd(62) = x3_cor * a3_cor * t_cor;
     Rd(63) = x3_cor * y3_cor * t_cor;
     Rd(64) = x3_cor * b3_cor * t_cor;
     Rd(65) = x3_cor * x0_cor * t_cor;
     Rd(66) = a3_cor * y3_cor * t_cor; 
     Rd(67) = a3_cor * b3_cor * t_cor; 
     Rd(68) = a3_cor * x0_cor * t_cor; 
     Rd(69) = y3_cor * b3_cor * t_cor; 
     Rd(70) = y3_cor * x0_cor * t_cor; 
     Rd(71) = b3_cor * x0_cor * t_cor; 
     Rd(72) = x3_cor * x3_cor * t_cor; 
     Rd(73) = a3_cor * a3_cor * t_cor; 
     Rd(74) = y3_cor * y3_cor * t_cor; 
     Rd(75) = b3_cor * b3_cor * t_cor; 
     Rd(76) = x0_cor * x0_cor * t_cor; 
     Rd(77) = x3_cor * a3_cor * y3_cor * t_cor; 
     Rd(78) = x3_cor * a3_cor * b3_cor * t_cor; 
     Rd(79) = x3_cor * a3_cor * x0_cor * t_cor; 
     Rd(80) = x3_cor * y3_cor * b3_cor * t_cor; 
     Rd(81) = x3_cor * y3_cor * x0_cor * t_cor; 
     Rd(82) = x3_cor * b3_cor * x0_cor * t_cor; 
     Rd(83) = a3_cor * y3_cor * b3_cor * t_cor; 
     Rd(84) = a3_cor * y3_cor * x0_cor * t_cor; 
     Rd(85) = a3_cor * b3_cor * x0_cor * t_cor; 
     Rd(86) = y3_cor * b3_cor * x0_cor * t_cor; 
     Rd(87) = x3_cor * x3_cor * a3_cor * t_cor; 
     Rd(88) = x3_cor * x3_cor * y3_cor * t_cor; 
     Rd(89) = x3_cor * x3_cor * b3_cor * t_cor; 
     Rd(90) = x3_cor * x3_cor * x0_cor * t_cor; 
     Rd(91) = a3_cor * a3_cor * x3_cor * t_cor; 
     Rd(92) = a3_cor * a3_cor * y3_cor * t_cor; 
     Rd(93) = a3_cor * a3_cor * b3_cor * t_cor; 
     Rd(94) = a3_cor * a3_cor * x0_cor * t_cor; 
     Rd(95) = y3_cor * y3_cor * x3_cor * t_cor; 
     Rd(96) = y3_cor * y3_cor * a3_cor * t_cor; 
     Rd(97) = y3_cor * y3_cor * b3_cor * t_cor; 
     Rd(98) = y3_cor * y3_cor * x0_cor * t_cor; 
     Rd(99) = b3_cor * b3_cor * x3_cor * t_cor; 
     Rd(100) = b3_cor * b3_cor * a3_cor * t_cor; 
     Rd(101) = b3_cor * b3_cor * y3_cor * t_cor; 
     Rd(102) = b3_cor * b3_cor * x0_cor * t_cor; 
     Rd(103) = x0_cor * x0_cor * x3_cor * t_cor; 
     Rd(104) = x0_cor * x0_cor * a3_cor * t_cor; 
     Rd(105) = x0_cor * x0_cor * y3_cor * t_cor; 
     Rd(106) = x0_cor * x0_cor * b3_cor * t_cor; 
     Rd(107) = x3_cor * x3_cor * x3_cor * t_cor; 
     Rd(108) = a3_cor * a3_cor * a3_cor * t_cor; 
     Rd(109) = y3_cor * y3_cor * y3_cor * t_cor; 
     Rd(110) = b3_cor * b3_cor * b3_cor * t_cor; 
     Rd(111) = x0_cor * x0_cor * x0_cor * t_cor; 

     Rd(112) = 1. * t_cor * t_cor; 
     Rd(113) = x3_cor * t_cor * t_cor;
     Rd(114) = a3_cor * t_cor * t_cor;
     Rd(115) = y3_cor * t_cor * t_cor;
     Rd(116) = b3_cor * t_cor * t_cor;
     Rd(117) = x0_cor * t_cor * t_cor;
     Rd(118) = x3_cor * a3_cor * t_cor * t_cor;
     Rd(119) = x3_cor * y3_cor * t_cor * t_cor;
     Rd(120) = x3_cor * b3_cor * t_cor * t_cor;
     Rd(121) = x3_cor * x0_cor * t_cor * t_cor;
     Rd(122) = a3_cor * y3_cor * t_cor * t_cor; 
     Rd(123) = a3_cor * b3_cor * t_cor * t_cor; 
     Rd(124) = a3_cor * x0_cor * t_cor * t_cor; 
     Rd(125) = y3_cor * b3_cor * t_cor * t_cor; 
     Rd(126) = y3_cor * x0_cor * t_cor * t_cor; 
     Rd(127) = b3_cor * x0_cor * t_cor * t_cor; 
     Rd(128) = x3_cor * x3_cor * t_cor * t_cor; 
     Rd(129) = a3_cor * a3_cor * t_cor * t_cor; 
     Rd(130) = y3_cor * y3_cor * t_cor * t_cor; 
     Rd(131) = b3_cor * b3_cor * t_cor * t_cor; 
     Rd(132) = x0_cor * x0_cor * t_cor * t_cor; 
     Rd(133) = x3_cor * a3_cor * y3_cor * t_cor * t_cor; 
     Rd(134) = x3_cor * a3_cor * b3_cor * t_cor * t_cor; 
     Rd(135) = x3_cor * a3_cor * x0_cor * t_cor * t_cor; 
     Rd(136) = x3_cor * y3_cor * b3_cor * t_cor * t_cor; 
     Rd(137) = x3_cor * y3_cor * x0_cor * t_cor * t_cor; 
     Rd(138) = x3_cor * b3_cor * x0_cor * t_cor * t_cor; 
     Rd(139) = a3_cor * y3_cor * b3_cor * t_cor * t_cor; 
     Rd(140) = a3_cor * y3_cor * x0_cor * t_cor * t_cor; 
     Rd(141) = a3_cor * b3_cor * x0_cor * t_cor * t_cor; 
     Rd(142) = y3_cor * b3_cor * x0_cor * t_cor * t_cor; 
     Rd(143) = x3_cor * x3_cor * a3_cor * t_cor * t_cor; 
     Rd(144) = x3_cor * x3_cor * y3_cor * t_cor * t_cor; 
     Rd(145) = x3_cor * x3_cor * b3_cor * t_cor * t_cor; 
     Rd(146) = x3_cor * x3_cor * x0_cor * t_cor * t_cor; 
     Rd(147) = a3_cor * a3_cor * x3_cor * t_cor * t_cor; 
     Rd(148) = a3_cor * a3_cor * y3_cor * t_cor * t_cor; 
     Rd(149) = a3_cor * a3_cor * b3_cor * t_cor * t_cor; 
     Rd(150) = a3_cor * a3_cor * x0_cor * t_cor * t_cor; 
     Rd(151) = y3_cor * y3_cor * x3_cor * t_cor * t_cor; 
     Rd(152) = y3_cor * y3_cor * a3_cor * t_cor * t_cor; 
     Rd(153) = y3_cor * y3_cor * b3_cor * t_cor * t_cor; 
     Rd(154) = y3_cor * y3_cor * x0_cor * t_cor * t_cor; 
     Rd(155) = b3_cor * b3_cor * x3_cor * t_cor * t_cor; 
     Rd(156) = b3_cor * b3_cor * a3_cor * t_cor * t_cor; 
     Rd(157) = b3_cor * b3_cor * y3_cor * t_cor * t_cor; 
     Rd(158) = b3_cor * b3_cor * x0_cor * t_cor * t_cor; 
     Rd(159) = x0_cor * x0_cor * x3_cor * t_cor * t_cor; 
     Rd(160) = x0_cor * x0_cor * a3_cor * t_cor * t_cor; 
     Rd(161) = x0_cor * x0_cor * y3_cor * t_cor * t_cor; 
     Rd(162) = x0_cor * x0_cor * b3_cor * t_cor * t_cor; 
     Rd(163) = x3_cor * x3_cor * x3_cor * t_cor * t_cor; 
     Rd(164) = a3_cor * a3_cor * a3_cor * t_cor * t_cor; 
     Rd(165) = y3_cor * y3_cor * y3_cor * t_cor * t_cor; 
     Rd(166) = b3_cor * b3_cor * b3_cor * t_cor * t_cor; 
     Rd(167) = x0_cor * x0_cor * x0_cor * t_cor * t_cor; 

  for (int ii = 0; ii < Nprm; ii++){
   sum += Rd(ii) * Theta(ii);
  }
    
 	Aq_cor.push_back(sum);
    evt_valid.push_back(iData);
//    mass_calib = sum;
//	new_tree->Fill();

   }else{
	   continue;
   }
}


//  tree->Addfriend("new_tree");

// Output

 TH1D *h_aq_cor = new TH1D("aq_cor", "aq_cor",500,1.7,2.3);
 TH1D *h_aq_cor_wr = new TH1D("aq_cor_wr", "aq_cor_wr",500,-10,10);

 TH1D *h_39Ca = new TH1D("h39Ca", "h39Ca",500,1.940,1.980);
 TH1D *h_40Ca = new TH1D("h40Ca", "h40Ca",500,1.990,2.02);
 TH1D *h_41Ca = new TH1D("h41Ca", "h41Ca",500,2.040,2.0650);
                            
 TH1D *h_40Sc = new TH1D("h40Sc", "h40Sc",500,1.900,1.925);
 TH1D *h_41Sc = new TH1D("h41Sc", "h41Sc",500,1.940,1.970);
 TH1D *h_43Sc = new TH1D("h43Sc", "h43Sc",500,2.035,2.060);
                                            
 TH1D *h_40Ti = new TH1D("h40Ti", "h40Ti",500,1.805,1.826);
 TH1D *h_41Ti = new TH1D("h41Ti", "h41Ti",500,1.855,1.885);
 TH1D *h_43Ti = new TH1D("h43Ti", "h43Ti",500,1.940,1.980);
                                             
 TH1D *h_43V  = new TH1D("h43V ", "h43V ",500,1.865,1.890);
 TH1D *h_44V  = new TH1D("h44V ", "h44V ",500,1.90,1.94);
 TH1D *h_45V  = new TH1D("h45V ", "h45V ",500,1.941,1.983);
                            
 TH1D *h_44Cr = new TH1D("h44Cr", "h44Cr",500,1.825,1.858);
 TH1D *h_45Cr = new TH1D("h45Cr", "h45Cr",500,1.855,1.90);
 TH1D *h_46Cr = new TH1D("h46Cr", "h46Cr",500,1.90,1.940);
                            
 TH1D *h_46Mn = new TH1D("h46Mn", "h46Mn",500,1.832,1.855);
 TH1D *h_47Mn = new TH1D("h47Mn", "h47Mn",500,1.860,1.897);
 TH1D *h_49Mn = new TH1D("h49Mn", "h49Mn",500,1.90,1.940);
                            
 TH1D *h_48Fe = new TH1D("h48Fe", "h48Fe",500,1.8355,1.855);
 TH1D *h_49Fe = new TH1D("h49Fe", "h49Fe",500,1.865,1.897);
 TH1D *h_50Fe = new TH1D("h50Fe", "h50Fe",500,1.90,1.940);

 TH2D *h_zaq_cor = new TH2D("zaq_col", "zaq_col",500,1.7,2.3,500,18,30);

   Int_t Nevt_valid = evt_valid.size();

//   Double_t aq_cor_br;
//   tree->Branch("Aq_cor",&aq_cor_br,"Aq_cor/D");

  for (Int_t iData = 0; iData < Nevt_valid; iData++){

    int itmp = evt_valid[iData];
    tree->GetEntry(itmp);

     h_aq_cor->Fill(Aq_cor[iData]);
     h_aq_cor_wr->Fill(Aq_cor[iData]);

     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
 
      h_zaq_cor->Fill(Aq_cor[iData],z_tmpt);
//	  aq_cor_br = Aq_cor[iData];
//	  tree->Fill();

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_39Ca->Fill(Aq_cor[iData]);
      h_40Ca->Fill(Aq_cor[iData]); 
      h_41Ca->Fill(Aq_cor[iData]);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc->Fill(Aq_cor[iData]);
      h_41Sc->Fill(Aq_cor[iData]);
      h_43Sc->Fill(Aq_cor[iData]);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti->Fill(Aq_cor[iData]);
      h_41Ti->Fill(Aq_cor[iData]);
      h_43Ti->Fill(Aq_cor[iData]);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V ->Fill(Aq_cor[iData]);
      h_44V ->Fill(Aq_cor[iData]);
      h_45V ->Fill(Aq_cor[iData]);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr->Fill(Aq_cor[iData]);
      h_45Cr->Fill(Aq_cor[iData]);
      h_46Cr->Fill(Aq_cor[iData]);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn->Fill(Aq_cor[iData]);
      h_47Mn->Fill(Aq_cor[iData]);
      h_49Mn->Fill(Aq_cor[iData]);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe->Fill(Aq_cor[iData]);
      h_49Fe->Fill(Aq_cor[iData]);
      h_50Fe->Fill(Aq_cor[iData]);

  }else {
	  continue;
  }
}


//// Draw original histogram

 TH1D *h_aq_cor_org = new TH1D("aq_cor_org", "aq_cor_org",500,1.7,2.3);

 TH1D *h_39Ca_org = new TH1D("h39Ca_org", "h39Ca_org",500,1.940,1.980);
 TH1D *h_40Ca_org = new TH1D("h40Ca_org", "h40Ca_org",500,1.990,2.02);
 TH1D *h_41Ca_org = new TH1D("h41Ca_org", "h41Ca_org",500,2.040,2.0650);
                   
 TH1D *h_40Sc_org = new TH1D("h40Sc_org", "h40Sc_org",500,1.900,1.925);
 TH1D *h_41Sc_org = new TH1D("h41Sc_org", "h41Sc_org",500,1.940,1.970);
 TH1D *h_43Sc_org = new TH1D("h43Sc_org", "h43Sc_org",500,2.035,2.060);
                        
 TH1D *h_40Ti_org = new TH1D("h40Ti_org", "h40Ti_org",500,1.805,1.826);
 TH1D *h_41Ti_org = new TH1D("h41Ti_org", "h41Ti_org",500,1.855,1.885);
 TH1D *h_43Ti_org = new TH1D("h43Ti_org", "h43Ti_org",500,1.940,1.980);
                                        
 TH1D *h_43V_org = new TH1D("h43V_org ", "4h3V_org ",500,1.865,1.890);
 TH1D *h_44V_org = new TH1D("h44V_org ", "4h4V_org ",500,1.90,1.94);
 TH1D *h_45V_org = new TH1D("h45V_org ", "4h5V_org ",500,1.941,1.983);
                                    
 TH1D *h_44Cr_org = new TH1D("h44Cr_org", "h44Cr_org",500,1.825,1.858);
 TH1D *h_45Cr_org = new TH1D("h45Cr_org", "h45Cr_org",500,1.855,1.90);
 TH1D *h_46Cr_org = new TH1D("h46Cr_org", "h46Cr_org",500,1.90,1.940);
                   
 TH1D *h_46Mn_org = new TH1D("h46Mn_org", "h46Mn_org",500,1.832,1.855);
 TH1D *h_47Mn_org = new TH1D("h47Mn_org", "h47Mn_org",500,1.860,1.897);
 TH1D *h_49Mn_org = new TH1D("h49Mn_org", "h49Mn_org",500,1.90,1.940);
                
 TH1D *h_48Fe_org = new TH1D("h48Fe_org", "h48Fe_org",500,1.8355,1.855);
 TH1D *h_49Fe_org = new TH1D("h49Fe_org", "h49Fe_org",500,1.865,1.897);
 TH1D *h_50Fe_org = new TH1D("h50Fe_org", "h50Fe_org",500,1.90,1.940);

 TH2D *h_zaq_org = new TH2D("zaq_org", "zaq_org",500,1.7,2.3,500,18,30);

  for (Int_t iData = 0; iData < nData; iData++){
     tree->GetEntry(iData);
     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t aq_tmpt = mass_tmpt->GetAq();
 
     h_aq_cor_org->Fill(aq_tmpt);
     h_zaq_org->Fill(aq_tmpt,z_tmpt);

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_39Ca_org->Fill(aq_tmpt);
      h_40Ca_org->Fill(aq_tmpt); 
      h_41Ca_org->Fill(aq_tmpt);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc_org->Fill(aq_tmpt);
      h_41Sc_org->Fill(aq_tmpt);
      h_43Sc_org->Fill(aq_tmpt);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti_org->Fill(aq_tmpt);
      h_41Ti_org->Fill(aq_tmpt);
      h_43Ti_org->Fill(aq_tmpt);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V_org->Fill(aq_tmpt);
      h_44V_org->Fill(aq_tmpt);
      h_45V_org->Fill(aq_tmpt);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr_org->Fill(aq_tmpt);
      h_45Cr_org->Fill(aq_tmpt);
      h_46Cr_org->Fill(aq_tmpt);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn_org->Fill(aq_tmpt);
      h_47Mn_org->Fill(aq_tmpt);
      h_49Mn_org->Fill(aq_tmpt);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe_org->Fill(aq_tmpt);
      h_49Fe_org->Fill(aq_tmpt);
      h_50Fe_org->Fill(aq_tmpt);

  }
 }




}






