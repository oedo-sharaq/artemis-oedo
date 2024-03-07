#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"


void select_event(){

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.sc.170272.root");
 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.sc.root","RECREATE");

 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
 ofile->Write();
 ofile->Close();

 ofile->Delete();
 



}


