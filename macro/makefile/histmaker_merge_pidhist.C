#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_merge_pidhist(){


 TList *l1 = new TList;
 TList *l2 = new TList;
 TList *l3 = new TList;
 TList *l4 = new TList;

 TH2D *hzaq_pid_mass       = new TH2D("hzaq_pid_mass","hzaq_pid_mass",500,1.7,2.3,500,8,30);
 TH2D *hzaq_pid_ssd_cor    = new TH2D("hzaq_pid_ssd_cor","hzaq_pid_ssd_cor",500,1.7,2.3,500,8,30);
 TH2D *hzaq_pid_pla_cor    = new TH2D("hzaq_pid_pla_cor","hzaq_pid_pla_cor",500,1.7,2.3,500,8,30);
 TH2D *hzaq_pid_ssdplacoin = new TH2D("hzaq_pid_ssdplacoin","hzaq_pid_ssdplacoin",500,1.7,2.3,500,8,30);


 for (int i = 170; i < 273; i++){
 
  TFile* file = TFile::Open(Form("sh13_analysis/hanai/phys/bld_fiel/BLD.%04d.all.hist.root",i));
 if(!file){
	 cout << "Error File Number" << i << " cannnot open " << endl;
 }
  cout << "Get hist from" << i << endl;

  gROOT->ProcessLine("cd 0");
 
  TH2D *hst0 = (TH2D*)gROOT->FindObject("pid_mass"); 
  TH2D *hst1 = (TH2D*)gROOT->FindObject("pid_ssd_cor"); 
  TH2D *hst2 = (TH2D*)gROOT->FindObject("pid_pla_cor"); 
  TH2D *hst3 = (TH2D*)gROOT->FindObject("pid_ssdplacoin"); 
 
  l1->Add(hst0);
  l2->Add(hst1);
  l3->Add(hst2);
  l4->Add(hst3);
 
  file->Close();
 
 
 }

  TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_fiel/BLD.170272.all.hist.root","recreate");

   hzaq_pid_mass->Merge(l1);
   hzaq_pid_mass->Write();
//
//   hzaq_pid_ssd_cor->Merge(l2);
//   hzaq_pid_ssd_cor->Write();
//
//   hzaq_pid_pla_cor->Merge(l3);
//   hzaq_pid_pla_cor->Write();
//
//   hzaq_pid_ssdplacoin->Merge(l4);
//   hzaq_pid_ssdplacoin->Write();
//   
   ofile->Close();



}
