#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void hadd_merge_pidhist(){


// std::string s = "hadd BLD.170272.all.hist.root";
 TString s = "hadd sh13_analysis/hanai/phys/bld_fiel/BLD.170272.all.hist.root";

 for (int i = 170; i < 273; i++){
   TString ch = Form(" sh13_analysis/hanai/phys/bld_fiel/BLD.%04d.all.hist.root",i);
   s += ch;
 }


 cout << s << endl;

// gROOT->ProcessLine(Form("%s",s));



}
