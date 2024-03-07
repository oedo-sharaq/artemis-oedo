#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TTree.h>
#include <TDecompLU.h>
#include <TString.h>
#include <TMinuit.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>



void mass_calib_chi(){

  

  Int_t N_evt = 1500;  //the number of events
  Int_t N_ref =   26;  // the number of reference masses
  Int_t N_par =   56;  //the number of parameters

// prepare the fitting data
  Double_t data[n*r][np]; // matrix of data
  
  TFileOpen *file =       // open root file

for(int i =0; i < N_ref; i++){              // select a spece


 for (int j=0; j < N_evt; j++){

  Int_t run = gRandom->Uniform(170,272)  // pick up run randomly, (runnumber min, runnumber max)
  Int_t evt = gRandom->Uniform(170,272)  // pick up event randomly, (runnumber min, runnumber max)
 
  }
    
}


// prepare the parameters
  Double_t par[N_par];    // paramter 




// definition of function and chi square

  func = c00 * x + c01 * a + ... + c33 * xab; // c00, c01, ... are parameters, x,a,b... are data;

  chisq += TMath::Pow((data[i][1] - func) / data[i][2],2); //data[i][1] will be mass_ref














 
























}
