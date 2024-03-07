#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"


void selectroot(){

// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/chkbld_physics_merge.ca.170272.root");
// TTree* itree = (TTree*)gDirectory->Get("tree");
// 
// art::TEventHeader *array_evtnum = NULL;
// 
// itree->SetBranchAddress("eventheader",&array_evtnum);
// Int_t run = array_evtnum->GetRunNumber();
// 
//// itree->Draw(">>elist","run==170");
//// TEventList *elist = (TEventList*)gROOT->FindObject("elist");
//// int N = elist->GetN();
//// for(int i=0; i < N; i++ ){
////	 tree->GetEntry(elist->GetEntry(i));
////
////}
//for(int i=170; i < 273; i++){
// TTree* otree = itree->CopyTree(Form("run==%d",i));
//
// TFile* ofile = new TFile(Form("sh13_analysis/hanai/phys/merge/chkbld_phys%d.ca.root",i),"RECREATE");
//
// ofile->cd();
// otree->Write();
// ofile->Close();
//
// ofile->Delete();
// otree->Delete();
//
//
//}


// TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/chkbld_physics_merge.ca.170272.root");
//
// TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/chkbld_physics170.ca.root","RECREATE");
//
//
// ((TTree*)file->Get("tree"))->CopyTree("eventheader.fRunNumber==170");
// ofile->Write();
// ofile->Close();


 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/chkbld_physics_merge.ca.170272.root");

for(int i = 170; i < 273; i++){
 TFile* ofile = new TFile(Form("sh13_analysis/hanai/phys/merge/chkbld_physics%d.ca.root",i),"RECREATE");

 ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
 ofile->Write();
 ofile->Close();

 ofile->Delete();
 
}


}


