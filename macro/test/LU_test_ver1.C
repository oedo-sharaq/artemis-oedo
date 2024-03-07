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


void LU_test_ver1(){

//  const Int_t Nrun = 250;  //the number of runs
  const Int_t Nrun = 2;  //the number of runs
  const Int_t Nref =  2;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nprm = 2;  //the number of parameters

 TMatrixD A(Nevt,Nprm);
// TMatrixD At(Nprm,Nevt);
//          At.Transpose(A);
 TMatrixD b(Nevt,1);

 A(0,0) = 1.; 
 A(0,1) = 2.;
 A(1,0) = 2.; 
 A(1,1) = 1.;
 A(2,0) = 4.;
 A(2,1) = 4.;
 A(3,0) = 4.;
 A(3,1) = 5.;

 b(0,0) = 2.;
 b(1,0) = 1.;
 b(2,0) = 1.;
 b(3,0) = 6.;

 TMatrixD At(Nprm,Nevt);
          At.Transpose(A);


// for(int i = 0; i < Nevt; i++){
//      for(int j = 0; j < Nprm; j ++){
//     int r1 = gRandom->Uniform(-5,5);
//     int r2 = gRandom->Uniform(-100,100);
//  
//   //  A(i,j) = 0.1*r1*r2-0.01;
//     A(i,j) = r1*0.5;
//	}
//   int r3 = gRandom->Uniform(18,26);
// //  b(i,0) = 0.09*r3;
//   b(i,0) = 0.1*r3;
//
//  }


  TMatrixD Cov(Nprm,Nprm);
  Cov.Mult(At,A);


 ofstream fout("/home/sh13/art_analysis/user/hanai/prm/calib_test/set_matrix.dat");
 if (fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	fout << "b" << "(" << n << "): " << b(n,0) << " | ";

	for(int m = 0; m < Nprm; m++){
		fout << "A" <<  "(" << n << "," << m << "): " <<A(n,m) << " | " ;
	}
	fout << "\n";
}

	fout.close();

 for(int l=0;l<Nprm;l++){
 for(int v=0;v<Nprm;v++){
	 cout << "Cov" << "(" << l << "," << v << ") : " <<Cov(l,v) << endl;
 }

 }

 for(int nn=0;nn<Nprm;nn++){
 for(int mm=0;mm<Nevt;mm++){
	 cout << "At" << "(" << nn << "," << mm << ") : " << At(nn,mm) << endl;
 }

 }

//// Set Matrix
////
//  TMatrixD Cov(Nprm,Nprm);
//  Cov.Mult(At,A);

  TMatrixD Atb(Nprm,1);
  Atb.Mult(At,b);

  TVectorD Atb_v = TMatrixDColumn(Atb,0);
  
// Solve Normal Equation

  TDecompLU lu(Cov);
  Bool_t ok;

  TVectorD Theta(Nprm);
  Theta = lu.Solve(Atb_v,ok);


// Save the results of LU decompose
  Double_t d1, d2;
  lu.Det(d1,d2);
  cout << "cond: " << lu.Condition() << endl;
  cout << "det: "  << d1*TMath::Power(2, d2) << endl;
  cout << "tol: " << lu.GetTol() << endl;
  Theta.Print();

   char foutname[50];
//   ofstream fout("output/mass/lu_out.dat");
//   sprintf(foutname, "output/mass/lu_out.dat");
   std::ofstream foutmtr("output/calib_test/lu_test_out.dat");
//   fout.open(foutname, std::ios::out);
   foutmtr << "cond: " << lu.Condition() << endl;
   foutmtr << "det: "  << d1*TMath::Power(2, d2) << endl;
   foutmtr << "tol: " << lu.GetTol() << endl;
//   foutmtr << Theta.Print() << endl;

   foutmtr.close();


}

