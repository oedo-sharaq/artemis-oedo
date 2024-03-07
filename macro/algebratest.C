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


void algebratest(){
 Int_t Nprm = 6;

 TMatrixD A(Nprm,Nprm);


for(int i = 0; i < Nprm; i++){
 for(int j = 0; j < Nprm; j++){

 double x = gRandom->Uniform(-1,1);

 A(i,j) = x;
 }
}

 TDecompSVD svd(A);

// TMatrixD Ai(Nprm,Nprm);
//          Ai = A.Invert();
 TMatrixD Ai = svd.Invert();

 TMatrixD AiA(Nprm,Nprm);
          AiA.Mult(A,Ai);

 cout << "Matrix A " << endl;
 A.Print();


 cout << "Matrix A inverse (Ai)  " << endl;
 Ai.Print();


 cout << "Matrix A times Ai  " << endl;
 AiA.Print();
 
 TMatrixD b(Nprm,1);

for(int s = 0; s < Nprm; s++){

 double y = gRandom->Uniform(-10,10);

 b(s,0) = y;
}

 TMatrixD bt(1,Nprm);
          bt.Transpose(b);

  cout << "Matrix b " << endl;
   b.Print();


 cout << "Matrix bt "  << endl;
 bt.Print();


 TMatrixD D_tmp_t(bt,TMatrixD::kMult,Ai);

 cout << "Matrix D_tmp_t "  << endl;
 D_tmp_t.Print();



 TMatrixD D_tmp(D_tmp_t,TMatrixD::kMult,b);
 cout << "Matrix D_tmp "  << endl;
 D_tmp.Print();

 Int_t nrow = D_tmp.GetNrows();
 Int_t ncol = D_tmp.GetNcols();


 cout << "nrow = " << nrow << "  " <<  "ncol = "  << ncol << endl;

if( nrow != 1 || ncol != 1 ){
  cout << "Error! Something wrong in matrix calculation" << endl;
}else{
 cout << "matrix ok " << endl;
 }

}

