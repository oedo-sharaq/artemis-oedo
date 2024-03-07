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



void halflife(){

 Double_t Z = 22;
 Double_t N = 17;
 Double_t A = Z + N;

 Double_t m_core = 34441.9419;
 Double_t E_f = 2;
 Double_t l = 1;
 Double_t R = 1.27 * TMath::Power(A,0.3333);

 Double_t ele = 1.60217663e-19;
 Double_t k = 8987552000;
 Double_t Zpp = 2;

 Double_t hbar = 6.582119569e-22;
 Double_t m_pp = 938.2720813*2;
 Double_t u = (m_core * m_pp) / (m_core + m_pp);
 Double_t c = 299792458;

 Double_t a = 0.67;
 Double_t V0 = -51 + 33 * (N - Z) / (N + Z);


 Double_t step = 0.0001;
 Double_t b = 32.0209;
 Double_t nStep = b / step;
 
 Double_t V_int = 0;
 Double_t count = 0;
 
 for(int i=0; i < nStep; i++){
 
  Double_t x = i * step;
 
  Double_t Vc = (k * Z * Zpp * ele * ele) / ((x+R) * 1.e-15 * 1.e6 * ele);
  Double_t Vl = c * c * ( l * ( l + 1 )* hbar * hbar) / (2 * u * ((x+R) * 1.e-15) * ((x+R) * 1.e-15));
  Double_t Vws = V0 / (1 + TMath::Exp(((x+R)-R)/a));
  Double_t Vtot = Vc + Vl + Vws;
 
  V_int += TMath::Sqrt(Vtot - E_f) * step;
   
   count += i;

 }
 
 Double_t G = V_int * TMath::Sqrt(2 * m_pp * c * c) / hbar;
 
 Double_t T_half = TMath::Sqrt(2 * m_pp)* R * TMath::Log(2) * TMath::Exp(2*G)/TMath::Sqrt(E_f);
 
 
 cout << "39Ti" << "l = " << l << endl;
 cout << "count = " << count<< endl;
 cout << "V_int = " << V_int << endl;
 cout << "T 1/2 = " << T_half << endl;





}
