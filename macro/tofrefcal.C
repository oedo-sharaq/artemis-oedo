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


Double_t tof_func(Double_t ll, Double_t ee, Double_t zz, Double_t b, Double_t cc, Double_t x){
 

 Double_t t =  (1.e12) * ll * TMath::Sqrt(1+TMath::Power(x/(ee*zz*b*cc),2))/cc;

  return t;

}

Double_t tof_error_func(Double_t ll, Double_t ee, Double_t zz, Double_t b, Double_t cc, Double_t x){

 Double_t coeff = 1 / TMath::Power(ee*zz*b*cc,2);
 
 Double_t t_err =  (1.e12) * ll * x * coeff * TMath::Power(1 + x * x * coeff,-0.5)/cc;

  return t_err;

}


void tofrefcal(){

 const Double_t ref_38ca = 1.89826838; // A/Q
 const Double_t ref_39ca = 1.94798796; // A/Q
 const Double_t ref_41ca = 2.04756631; // A/Q

 const Double_t ref_40sc = 1.90316521;
 const Double_t ref_41sc = 1.95036921;
 const Double_t ref_43sc = 2.04522156;
 
 const Double_t ref_40ti = 1.81719569;
 const Double_t ref_41ti = 1.86232290;
 const Double_t ref_42ti = 1.90731844;

 const Double_t ref_43v  = 1.86818142;
 const Double_t ref_44v  = 1.91138485;
 const Double_t ref_46v  = 1.99772208;
 
 const Double_t ref_44cr = 1.83218575;
 const Double_t ref_45cr = 1.87358000;
 const Double_t ref_46cr = 1.91480106;
 
 const Double_t ref_46mn = 1.83891945;
 const Double_t ref_47mn = 1.87848359;
 const Double_t ref_48mn = 1.91819472;

 const Double_t ref_48fe = 1.84486307;
 const Double_t ref_49fe = 1.88304627;
 const Double_t ref_50fe = 1.92110626;
 
 const Double_t amu = 9.31494013e5;
 const Int_t z_ca = 20;
 const Int_t z_sc = 21;
 const Int_t z_ti = 22;
 const Int_t z_v  = 23;
 const Int_t z_cr = 24;
 const Int_t z_mn = 25;
 const Int_t z_fe = 26;

 const Double_t L    = 103.49978;
 const Double_t Brho = 4.4147;
 const Double_t c    = 299792458;
 const Double_t ele  = 1.60218e-19;

// mref

  Double_t mref_38ca = ref_38ca * amu * z_ca * ele * 1.e3; //mass [J]
  Double_t mref_39ca = ref_39ca * amu * z_ca * ele * 1.e3; //mass [J]
  Double_t mref_41ca = ref_41ca * amu * z_ca * ele * 1.e3; //mass [J]
                               
  Double_t mref_40sc = ref_40sc * amu * z_sc * ele * 1.e3; //mass [J]
  Double_t mref_41sc = ref_41sc * amu * z_sc * ele * 1.e3; //mass [J]
  Double_t mref_43sc = ref_43sc * amu * z_sc * ele * 1.e3; //mass [J]
                               
  Double_t mref_40ti = ref_40ti * amu * z_ti * ele * 1.e3; //mass [J]
  Double_t mref_41ti = ref_41ti * amu * z_ti * ele * 1.e3; //mass [J]
  Double_t mref_42ti = ref_42ti * amu * z_ti * ele * 1.e3; //mass [J]
                               
  Double_t mref_43v  = ref_43v  * amu * z_v * ele * 1.e3; //mass [J]
  Double_t mref_44v  = ref_44v  * amu * z_v * ele * 1.e3; //mass [J]
  Double_t mref_46v  = ref_46v  * amu * z_v * ele * 1.e3; //mass [J]
                               
  Double_t mref_44cr = ref_44cr * amu * z_cr * ele * 1.e3; //mass [J]
  Double_t mref_45cr = ref_45cr * amu * z_cr * ele * 1.e3; //mass [J]
  Double_t mref_46cr = ref_46cr * amu * z_cr * ele * 1.e3; //mass [J]
                               
  Double_t mref_46mn = ref_46mn * amu * z_mn * ele * 1.e3; //mass [J]
  Double_t mref_47mn = ref_47mn * amu * z_mn * ele * 1.e3; //mass [J]
  Double_t mref_48mn = ref_48mn * amu * z_mn * ele * 1.e3; //mass [J]
                               
  Double_t mref_48fe = ref_48fe * amu * z_fe * ele * 1.e3; //mass [J]
  Double_t mref_49fe = ref_49fe * amu * z_fe * ele * 1.e3; //mass [J]
  Double_t mref_50fe = ref_50fe * amu * z_fe * ele * 1.e3; //mass [J]


// tref 

  Double_t t_ref_38ca = 0.001 * tof_func(L,ele,z_ca,Brho,c,mref_38ca); // [ns]
  Double_t t_ref_39ca = 0.001 * tof_func(L,ele,z_ca,Brho,c,mref_39ca); // [ns]
  Double_t t_ref_41ca = 0.001 * tof_func(L,ele,z_ca,Brho,c,mref_41ca); // [ns]

  Double_t t_ref_40sc = 0.001 * tof_func(L,ele,z_sc,Brho,c,mref_40sc); // [ns]
  Double_t t_ref_41sc = 0.001 * tof_func(L,ele,z_sc,Brho,c,mref_41sc); // [ns]
  Double_t t_ref_43sc = 0.001 * tof_func(L,ele,z_sc,Brho,c,mref_43sc); // [ns]

  Double_t t_ref_40ti = 0.001 * tof_func(L,ele,z_ti,Brho,c,mref_40ti); // [ns]
  Double_t t_ref_41ti = 0.001 * tof_func(L,ele,z_ti,Brho,c,mref_41ti); // [ns]
  Double_t t_ref_42ti = 0.001 * tof_func(L,ele,z_ti,Brho,c,mref_42ti); // [ns]

  Double_t t_ref_43v  = 0.001 * tof_func(L,ele,z_v,Brho,c,mref_43v); // [ns]
  Double_t t_ref_44v  = 0.001 * tof_func(L,ele,z_v,Brho,c,mref_44v); // [ns]
  Double_t t_ref_46v  = 0.001 * tof_func(L,ele,z_v,Brho,c,mref_46v); // [ns]

  Double_t t_ref_44cr = 0.001 * tof_func(L,ele,z_cr,Brho,c,mref_44cr); // [ns]
  Double_t t_ref_45cr = 0.001 * tof_func(L,ele,z_cr,Brho,c,mref_45cr); // [ns]
  Double_t t_ref_46cr = 0.001 * tof_func(L,ele,z_cr,Brho,c,mref_46cr); // [ns]

  Double_t t_ref_46mn = 0.001 * tof_func(L,ele,z_mn,Brho,c,mref_46mn); // [ns]
  Double_t t_ref_47mn = 0.001 * tof_func(L,ele,z_mn,Brho,c,mref_47mn); // [ns]
  Double_t t_ref_48mn = 0.001 * tof_func(L,ele,z_mn,Brho,c,mref_48mn); // [ns]

  Double_t t_ref_48fe = 0.001 * tof_func(L,ele,z_fe,Brho,c,mref_48fe); // [ns]
  Double_t t_ref_49fe = 0.001 * tof_func(L,ele,z_fe,Brho,c,mref_49fe); // [ns]
  Double_t t_ref_50fe = 0.001 * tof_func(L,ele,z_fe,Brho,c,mref_50fe); // [ns]


  cout << "TOF ref 38ca = " << t_ref_38ca << " [ns]" << endl;
  cout << "TOF ref 39ca = " << t_ref_39ca << " [ns]" << endl;
  cout << "TOF ref 41ca = " << t_ref_41ca << " [ns]" << endl;
                                         
  cout << "TOF ref 40sc = " << t_ref_40sc << " [ns]" << endl;
  cout << "TOF ref 41sc = " << t_ref_41sc << " [ns]" << endl;
  cout << "TOF ref 43sc = " << t_ref_43sc << " [ns]" << endl;
                                         
  cout << "TOF ref 40ti = " << t_ref_40ti << " [ns]" << endl;
  cout << "TOF ref 41ti = " << t_ref_41ti << " [ns]" << endl;
  cout << "TOF ref 42ti = " << t_ref_42ti << " [ns]" << endl;
                                         
  cout << "TOF ref 43v  = " << t_ref_43v  << " [ns]" << endl;
  cout << "TOF ref 44v  = " << t_ref_44v  << " [ns]" << endl;
  cout << "TOF ref 46v  = " << t_ref_46v  << " [ns]" << endl;
                                         
  cout << "TOF ref 44cr = " << t_ref_44cr << " [ns]" << endl;
  cout << "TOF ref 45cr = " << t_ref_45cr << " [ns]" << endl;
  cout << "TOF ref 46cr = " << t_ref_46cr << " [ns]" << endl;
                                         
  cout << "TOF ref 46mn = " << t_ref_46mn << " [ns]" << endl;
  cout << "TOF ref 47mn = " << t_ref_47mn << " [ns]" << endl;
  cout << "TOF ref 48mn = " << t_ref_48mn << " [ns]" << endl;
                                         
  cout << "TOF ref 48fe = " << t_ref_48fe << " [ns]" << endl;
  cout << "TOF ref 49fe = " << t_ref_49fe << " [ns]" << endl;
  cout << "TOF ref 50fe = " << t_ref_50fe << " [ns]" << endl;



}

