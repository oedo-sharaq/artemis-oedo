#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_mass_2step_stripmerge_all_aq(){

TFile* fst0 = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst0_2nd_all.170272.hist.root");
TH1D *hst0 = (TH1D*)gROOT->FindObject("haq_all"); 


TFile* fst1 = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst1_2nd_all.170272.hist.root");
TH1D *hst1 = (TH1D*)gROOT->FindObject("haq_all"); 


TFile* fst2 = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst2_2nd_all.170272.hist.root");
TH1D *hst2 = (TH1D*)gROOT->FindObject("haq_all"); 


TFile* fst3 = TFile::Open("sh13_analysis/hanai/phys/merge/mass_corst3_2nd_all.170272.hist.root");
TH1D *hst3 = (TH1D*)gROOT->FindObject("haq_all"); 


 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/mass_corallstrip_2nd_all.170272.hist.root","recreate");

 TList *l = new TList;
 l->Add(hst0);
 l->Add(hst1);
 l->Add(hst2);
 l->Add(hst3);

 TH1D *hzaq_allstrip = new TH1D("hzaq_allstrip","hzaq_allstrip",5000,1.7,1.98);
 hzaq_allstrip->Merge(l);
 hzaq_allstrip->Write();
 
 fst0->Close();
 fst1->Close();
 fst2->Close();
 fst3->Close();
 ofile->Close();



}


