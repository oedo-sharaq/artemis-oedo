#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2F.h"
#include "TROOT.h"


void histmaker_massst1_4step_all_aq(){

// TH2D *hzaq = new TH2D("hzaq","hzaq",1000,1.7,2.3,300,18,28);
 TH2D *hzaq = new TH2D("hzaq","hzaq",5000,1.7,1.98,300,18,28);

// TH1D *haq_all = new TH1D("haq_all","haq_all",1000,1.7,2.3);
 TH1D *haq_all = new TH1D("haq_all","haq_all",5000,1.7,1.98);
// TH1D *haq_all = new TH1D("haq_all","haq_all",2500,1.7,1.84);
 TH1D *haq1  = new TH1D("haq1","haq1",1000,1.70,1.72);
 TH1D *haq2  = new TH1D("haq2","haq2",1000,1.72,1.74);
 TH1D *haq3  = new TH1D("haq3","haq3",1000,1.74,1.76);
 TH1D *haq4  = new TH1D("haq4","haq4",1000,1.76,1.78);
 TH1D *haq5  = new TH1D("haq5","haq5",1000,1.78,1.80);
 TH1D *haq6  = new TH1D("haq6","haq6",1000,1.80,1.82);
 TH1D *haq7  = new TH1D("haq7","haq7",1000,1.82,1.84);
 TH1D *haq8  = new TH1D("haq8","haq8",1000,1.84,1.86);
 TH1D *haq9  = new TH1D("haq9","haq9",1000,1.86,1.88);
 TH1D *haq10 = new TH1D("haq10","haq10",1000,1.88,1.90);
 TH1D *haq11 = new TH1D("haq11","haq11",1000,1.90,1.92);
 TH1D *haq12 = new TH1D("haq12","haq12",1000,1.92,1.94);
 TH1D *haq13 = new TH1D("haq13","haq13",1000,1.94,1.96);
 TH1D *haq14 = new TH1D("haq14","haq14",1000,1.96,1.98);
 TH1D *haq15 = new TH1D("haq15","haq15",1000,1.98,2.00);
 TH1D *haq16 = new TH1D("haq16","haq16",1000,2.00,2.02);
 TH1D *haq17 = new TH1D("haq17","haq17",1000,2.02,2.04);
 TH1D *haq18 = new TH1D("haq18","haq18",1000,2.04,2.06);
 TH1D *haq19 = new TH1D("haq19","haq19",1000,2.06,2.08);
 TH1D *haq20 = new TH1D("haq20","haq20",1000,2.08,2.10);
 TH1D *haq21 = new TH1D("haq21","haq21",1000,2.10,2.12);
 TH1D *haq22 = new TH1D("haq22","haq22",1000,2.12,2.14);
 TH1D *haq23 = new TH1D("haq23","haq23",1000,2.14,2.16);
 TH1D *haq24 = new TH1D("haq24","haq24",1000,2.16,2.18);
 TH1D *haq25 = new TH1D("haq25","haq25",1000,2.18,2.20);
 TH1D *haq26 = new TH1D("haq26","haq26",1000,2.20,2.22);
 TH1D *haq27 = new TH1D("haq27","haq27",1000,2.22,2.24);
 TH1D *haq28 = new TH1D("haq28","haq28",1000,2.24,2.26);
 TH1D *haq29 = new TH1D("haq29","haq29",1000,2.26,2.28);
 TH1D *haq30 = new TH1D("haq30","haq30",1000,2.28,2.30);

 const Int_t Nhist = 103;

 TH1D *h_39ca[Nhist];
 TH1D *h_40ca[Nhist];
 TH1D *h_41ca[Nhist];
 TH1D *h_40sc[Nhist];
 TH1D *h_41sc[Nhist];
 TH1D *h_43sc[Nhist];
 TH1D *h_40ti[Nhist];
 TH1D *h_41ti[Nhist];
 TH1D *h_43ti[Nhist];
 TH1D *h_43v[Nhist];
 TH1D *h_44v[Nhist];
 TH1D *h_45v[Nhist];
 TH1D *h_44cr[Nhist];
 TH1D *h_45cr[Nhist];
 TH1D *h_46cr[Nhist];
 TH1D *h_46mn[Nhist];
 TH1D *h_47mn[Nhist];
 TH1D *h_48mn[Nhist];
 TH1D *h_48fe[Nhist];
 TH1D *h_49fe[Nhist];
 TH1D *h_50fe[Nhist];



for (Int_t ievt = 170; ievt < 273; ievt++){
 
 Int_t j = ievt - 170;

 h_39ca[j] = new TH1D(Form("h39ca_aq_%d",ievt),Form("h39ca_aq_%d",ievt),1000,1.94,1.96);
 h_40ca[j] = new TH1D(Form("h40ca_aq_%d",ievt),Form("h40ca_aq_%d",ievt),1000,1.99,2.01);
 h_41ca[j] = new TH1D(Form("h41ca_aq_%d",ievt),Form("h41ca_aq_%d",ievt),1000,2.04,2.06);
 h_40sc[j] = new TH1D(Form("h40sc_aq_%d",ievt),Form("h40sc_aq_%d",ievt),1000,1.90,1.92);
 h_41sc[j] = new TH1D(Form("h41sc_aq_%d",ievt),Form("h41sc_aq_%d",ievt),1000,1.945,1.965);
 h_43sc[j] = new TH1D(Form("h43sc_aq_%d",ievt),Form("h43sc_aq_%d",ievt),1000,2.04,2.06);
 h_40ti[j] = new TH1D(Form("h40ti_aq_%d",ievt),Form("h40ti_aq_%d",ievt),1000,1.81,1.83);
 h_41ti[j] = new TH1D(Form("h41ti_aq_%d",ievt),Form("h41ti_aq_%d",ievt),1000,1.86,1.88);
 h_43ti[j] = new TH1D(Form("h43ti_aq_%d",ievt),Form("h43ti_aq_%d",ievt),1000,1.94,1.960);
 h_43v[j]  = new TH1D(Form("h43v_aq_%d",ievt),Form("h43v_aq_%d",ievt),1000,1.865,1.886);
 h_44v[j]  = new TH1D(Form("h44v_aq_%d",ievt),Form("h44v_aq_%d",ievt),1000,1.900,1.920);
 h_45v[j]  = new TH1D(Form("h45v_aq_%d",ievt),Form("h45v_aq_%d",ievt),1000,1.941,1.961);
 h_44cr[j] = new TH1D(Form("h44cr_aq_%d",ievt),Form("h44cr_aq_%d",ievt),1000,1.825,1.845);
 h_45cr[j] = new TH1D(Form("h45cr_aq_%d",ievt),Form("h45cr_aq_%d",ievt),1000,1.855,1.875);  
 h_46cr[j] = new TH1D(Form("h46cr_aq_%d",ievt),Form("h46cr_aq_%d",ievt),1000,1.90,1.920);
 h_46mn[j] = new TH1D(Form("h46mn_aq_%d",ievt),Form("h46mn_aq_%d",ievt),1000,1.832,1.852);
 h_47mn[j] = new TH1D(Form("h47mn_aq_%d",ievt),Form("h47mn_aq_%d",ievt),1000,1.86,1.88);
 h_48mn[j] = new TH1D(Form("h48mn_aq_%d",ievt),Form("h48mn_aq_%d",ievt),1000,1.90,1.92);
 h_48fe[j] = new TH1D(Form("h48fe_aq_%d",ievt),Form("h48fe_aq_%d",ievt),1000,1.8355,1.8555);
 h_49fe[j] = new TH1D(Form("h49fe_aq_%d",ievt),Form("h49fe_aq_%d",ievt),1000,1.875,1.895);
 h_50fe[j] = new TH1D(Form("h50fe_aq_%d",ievt),Form("h50fe_aq_%d",ievt),1000,1.91,1.930);
}



//for (int j =0; j < 9; j++){
for (int j =0; j < 7; j++){

if(j==0){

 cout << " Filling events in Z = 20 region " << endl;

// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.ca.root");

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mass_corst1_BLD_4th = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree->SetBranchStatus("eventheader",1);


 Int_t nData = tree->GetEntries();
for (int i=0; i < nData; i++){
 tree->GetEntry(i);

 Int_t hit_mass = array_mass->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th = array_mass_corst1_BLD_4th->GetEntriesFast();

if( hit_mass > 0 && hit_mass_corst1_BLD_4th > 0){

 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th = (art::TMassData*) array_mass_corst1_BLD_4th->UncheckedAt(0);

 Double_t z_select = mass->GetZ();
 Double_t aq_select = mass_corst1_BLD_4th->GetAq();
 Int_t runnumber = array_eventheader->GetRunNumber();

  Int_t J = runnumber - 170;

  h_39ca[J]->Fill(aq_select);
  h_40ca[J]->Fill(aq_select);
  h_41ca[J]->Fill(aq_select);
  h_40sc[J]->Fill(aq_select);
  h_41sc[J]->Fill(aq_select);
  h_43sc[J]->Fill(aq_select);
  h_40ti[J]->Fill(aq_select);
  h_41ti[J]->Fill(aq_select);
  h_43ti[J]->Fill(aq_select);
  h_43v[J]->Fill(aq_select);
  h_44v[J]->Fill(aq_select);
  h_45v[J]->Fill(aq_select);
  h_44cr[J]->Fill(aq_select);
  h_45cr[J]->Fill(aq_select);
  h_46cr[J]->Fill(aq_select);
  h_46mn[J]->Fill(aq_select);
  h_47mn[J]->Fill(aq_select);
  h_48mn[J]->Fill(aq_select);
  h_48fe[J]->Fill(aq_select);
  h_49fe[J]->Fill(aq_select);
  h_50fe[J]->Fill(aq_select);

  hzaq->Fill(aq_select,z_select);
  haq_all->Fill(aq_select);

  haq1->Fill(aq_select); 
  haq2->Fill(aq_select); 
  haq3->Fill(aq_select); 
  haq4->Fill(aq_select); 
  haq5->Fill(aq_select); 
  haq6->Fill(aq_select); 
  haq7->Fill(aq_select); 
  haq8->Fill(aq_select); 
  haq9->Fill(aq_select); 
  haq10->Fill(aq_select);  
  haq11->Fill(aq_select);
  haq12->Fill(aq_select);
  haq13->Fill(aq_select);
  haq14->Fill(aq_select);
  haq15->Fill(aq_select);
  haq16->Fill(aq_select);
  haq17->Fill(aq_select);
  haq18->Fill(aq_select);
  haq19->Fill(aq_select);
  haq20->Fill(aq_select);
  haq21->Fill(aq_select);
  haq22->Fill(aq_select);
  haq23->Fill(aq_select);
  haq24->Fill(aq_select);
  haq25->Fill(aq_select);
  haq26->Fill(aq_select);
  haq27->Fill(aq_select);
  haq28->Fill(aq_select);
  haq29->Fill(aq_select);
  haq30->Fill(aq_select);

   }
 }

  file_load->Close();
}else if(j==1){

 cout << " Filling events in Z = 21 region " << endl;

// TFile* file_load_sc = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
 TFile* file_load_sc = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_sc){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_sc = (TTree*) gDirectory->Get("tree");
 tree_sc->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.sc.root");

 TClonesArray *array_mass_sc = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_sc = NULL;
 art::TEventHeader *array_eventheader_sc= NULL;

 tree_sc->SetBranchAddress("mass",&array_mass_sc);
 tree_sc->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_sc);
 tree_sc->SetBranchAddress("eventheader",&array_eventheader_sc);
 tree_sc->SetBranchStatus("*",0);
 tree_sc->SetBranchStatus("mass",1);
 tree_sc->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_sc->SetBranchStatus("eventheader",1);

 Int_t nData_sc = tree_sc->GetEntries();

for (int i=0; i < nData_sc; i++){
 tree_sc->GetEntry(i);

 Int_t hit_mass_sc = array_mass_sc->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_sc = array_mass_corst1_BLD_4th_sc->GetEntriesFast();

if( hit_mass_sc > 0 && hit_mass_corst1_BLD_4th_sc > 0){

 art::TMassData *mass_sc = (art::TMassData*) array_mass_sc->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_sc = (art::TMassData*) array_mass_corst1_BLD_4th_sc->UncheckedAt(0);

 Double_t z_select_sc = mass_sc->GetZ();
 Double_t aq_select_sc = mass_corst1_BLD_4th_sc->GetAq();
 Int_t runnumber_sc = array_eventheader_sc->GetRunNumber();

  Int_t J = runnumber_sc - 170;

  h_39ca[J]->Fill(aq_select_sc);
  h_40ca[J]->Fill(aq_select_sc);
  h_41ca[J]->Fill(aq_select_sc);
  h_40sc[J]->Fill(aq_select_sc);
  h_41sc[J]->Fill(aq_select_sc);
  h_43sc[J]->Fill(aq_select_sc);
  h_40ti[J]->Fill(aq_select_sc);
  h_41ti[J]->Fill(aq_select_sc);
  h_43ti[J]->Fill(aq_select_sc);
  h_43v[J]->Fill(aq_select_sc);
  h_44v[J]->Fill(aq_select_sc);
  h_45v[J]->Fill(aq_select_sc);
  h_44cr[J]->Fill(aq_select_sc);
  h_45cr[J]->Fill(aq_select_sc);
  h_46cr[J]->Fill(aq_select_sc);
  h_46mn[J]->Fill(aq_select_sc);
  h_47mn[J]->Fill(aq_select_sc);
  h_48mn[J]->Fill(aq_select_sc);
  h_48fe[J]->Fill(aq_select_sc);
  h_49fe[J]->Fill(aq_select_sc);
  h_50fe[J]->Fill(aq_select_sc);




  hzaq->Fill(aq_select_sc,z_select_sc);
  haq_all->Fill(aq_select_sc);

  haq1->Fill(aq_select_sc); 
  haq2->Fill(aq_select_sc); 
  haq3->Fill(aq_select_sc); 
  haq4->Fill(aq_select_sc); 
  haq5->Fill(aq_select_sc); 
  haq6->Fill(aq_select_sc); 
  haq7->Fill(aq_select_sc); 
  haq8->Fill(aq_select_sc); 
  haq9->Fill(aq_select_sc); 
  haq10->Fill(aq_select_sc);  
  haq11->Fill(aq_select_sc);
  haq12->Fill(aq_select_sc);
  haq13->Fill(aq_select_sc);
  haq14->Fill(aq_select_sc);
  haq15->Fill(aq_select_sc);
  haq16->Fill(aq_select_sc);
  haq17->Fill(aq_select_sc);
  haq18->Fill(aq_select_sc);
  haq19->Fill(aq_select_sc);
  haq20->Fill(aq_select_sc);
  haq21->Fill(aq_select_sc);
  haq22->Fill(aq_select_sc);
  haq23->Fill(aq_select_sc);
  haq24->Fill(aq_select_sc);
  haq25->Fill(aq_select_sc);
  haq26->Fill(aq_select_sc);
  haq27->Fill(aq_select_sc);
  haq28->Fill(aq_select_sc);
  haq29->Fill(aq_select_sc);
  haq30->Fill(aq_select_sc);

} }

   file_load_sc->Close();  
}else if(j==2){

 cout << " Filling events in Z = 22 region " << endl;

// TFile* file_load_ti = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
 TFile* file_load_ti = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_ti){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ti = (TTree*) gDirectory->Get("tree");
 tree_ti->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.ti.root");

 TClonesArray *array_mass_ti = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_ti = NULL;
 art::TEventHeader *array_eventheader_ti= NULL;

 tree_ti->SetBranchAddress("mass",&array_mass_ti);
 tree_ti->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_ti);
 tree_ti->SetBranchAddress("eventheader",&array_eventheader_ti);
 tree_ti->SetBranchStatus("*",0);
 tree_ti->SetBranchStatus("mass",1);
 tree_ti->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_ti->SetBranchStatus("eventheader",1);


 Int_t nData_ti = tree_ti->GetEntries();

for (int i=0; i < nData_ti; i++){
 tree_ti->GetEntry(i);

 Int_t hit_mass_ti = array_mass_ti->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_ti = array_mass_corst1_BLD_4th_ti->GetEntriesFast();

if( hit_mass_ti > 0 && hit_mass_corst1_BLD_4th_ti > 0){

 art::TMassData *mass_ti = (art::TMassData*) array_mass_ti->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_ti = (art::TMassData*) array_mass_corst1_BLD_4th_ti->UncheckedAt(0);

 Double_t z_select_ti = mass_ti->GetZ();
 Double_t aq_select_ti = mass_corst1_BLD_4th_ti->GetAq();
 Int_t runnumber_ti = array_eventheader_ti->GetRunNumber();

  Int_t J = runnumber_ti - 170;
  
  h_39ca[J]->Fill(aq_select_ti);
  h_40ca[J]->Fill(aq_select_ti);
  h_41ca[J]->Fill(aq_select_ti);
  h_40sc[J]->Fill(aq_select_ti);
  h_41sc[J]->Fill(aq_select_ti);
  h_43sc[J]->Fill(aq_select_ti);
  h_40ti[J]->Fill(aq_select_ti);
  h_41ti[J]->Fill(aq_select_ti);
  h_43ti[J]->Fill(aq_select_ti);
  h_43v[J]->Fill(aq_select_ti);
  h_44v[J]->Fill(aq_select_ti);
  h_45v[J]->Fill(aq_select_ti);
  h_44cr[J]->Fill(aq_select_ti);
  h_45cr[J]->Fill(aq_select_ti);
  h_46cr[J]->Fill(aq_select_ti);
  h_46mn[J]->Fill(aq_select_ti);
  h_47mn[J]->Fill(aq_select_ti);
  h_48mn[J]->Fill(aq_select_ti);
  h_48fe[J]->Fill(aq_select_ti);
  h_49fe[J]->Fill(aq_select_ti);
  h_50fe[J]->Fill(aq_select_ti);




  hzaq->Fill(aq_select_ti,z_select_ti);
  haq_all->Fill(aq_select_ti);

  haq1->Fill(aq_select_ti); 
  haq2->Fill(aq_select_ti); 
  haq3->Fill(aq_select_ti); 
  haq4->Fill(aq_select_ti); 
  haq5->Fill(aq_select_ti); 
  haq6->Fill(aq_select_ti); 
  haq7->Fill(aq_select_ti); 
  haq8->Fill(aq_select_ti); 
  haq9->Fill(aq_select_ti); 
  haq10->Fill(aq_select_ti);  
  haq11->Fill(aq_select_ti);
  haq12->Fill(aq_select_ti);
  haq13->Fill(aq_select_ti);
  haq14->Fill(aq_select_ti);
  haq15->Fill(aq_select_ti);
  haq16->Fill(aq_select_ti);
  haq17->Fill(aq_select_ti);
  haq18->Fill(aq_select_ti);
  haq19->Fill(aq_select_ti);
  haq20->Fill(aq_select_ti);
  haq21->Fill(aq_select_ti);
  haq22->Fill(aq_select_ti);
  haq23->Fill(aq_select_ti);
  haq24->Fill(aq_select_ti);
  haq25->Fill(aq_select_ti);
  haq26->Fill(aq_select_ti);
  haq27->Fill(aq_select_ti);
  haq28->Fill(aq_select_ti);
  haq29->Fill(aq_select_ti);
  haq30->Fill(aq_select_ti);
 
}  }

   file_load_ti->Close();  
}else if(j==3){

 cout << " Filling events in Z = 23 region " << endl;

//TFile* file_load_v = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_v = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_v){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_v = (TTree*) gDirectory->Get("tree");
 tree_v->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.v.root");

 TClonesArray *array_mass_corst1_BLD_4th_v = NULL;
 art::TEventHeader *array_eventheader_v= NULL;

 tree_v->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_v);
 tree_v->SetBranchAddress("eventheader",&array_eventheader_v);
 tree_v->SetBranchStatus("*",0);
 tree_v->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_v->SetBranchStatus("eventheader",1);


 Int_t nData_v = tree_v->GetEntries();

for (int i=0; i < nData_v; i++){
 tree_v->GetEntry(i);

 Int_t hit_mass_corst1_BLD_4th_v = array_mass_corst1_BLD_4th_v->GetEntriesFast();

if( hit_mass_corst1_BLD_4th_v > 0){

 art::TMassData *mass_corst1_BLD_4th_v = (art::TMassData*) array_mass_corst1_BLD_4th_v->UncheckedAt(0);

 Double_t aq_select_v = mass_corst1_BLD_4th_v->GetAq();
 Int_t runnumber_v = array_eventheader_v->GetRunNumber();

  Int_t J = runnumber_v - 170;
  
  h_39ca[J]->Fill(aq_select_v);
  h_40ca[J]->Fill(aq_select_v);
  h_41ca[J]->Fill(aq_select_v);
  h_40sc[J]->Fill(aq_select_v);
  h_41sc[J]->Fill(aq_select_v);
  h_43sc[J]->Fill(aq_select_v);
  h_40ti[J]->Fill(aq_select_v);
  h_41ti[J]->Fill(aq_select_v);
  h_43ti[J]->Fill(aq_select_v);
  h_43v[J]->Fill(aq_select_v);
  h_44v[J]->Fill(aq_select_v);
  h_45v[J]->Fill(aq_select_v);
  h_44cr[J]->Fill(aq_select_v);
  h_45cr[J]->Fill(aq_select_v);
  h_46cr[J]->Fill(aq_select_v);
  h_46mn[J]->Fill(aq_select_v);
  h_47mn[J]->Fill(aq_select_v);
  h_48mn[J]->Fill(aq_select_v);
  h_48fe[J]->Fill(aq_select_v);
  h_49fe[J]->Fill(aq_select_v);
  h_50fe[J]->Fill(aq_select_v);



  haq_all->Fill(aq_select_v);

  haq1->Fill(aq_select_v); 
  haq2->Fill(aq_select_v); 
  haq3->Fill(aq_select_v); 
  haq4->Fill(aq_select_v); 
  haq5->Fill(aq_select_v); 
  haq6->Fill(aq_select_v); 
  haq7->Fill(aq_select_v); 
  haq8->Fill(aq_select_v); 
  haq9->Fill(aq_select_v); 
  haq10->Fill(aq_select_v);  
  haq11->Fill(aq_select_v);
  haq12->Fill(aq_select_v);
  haq13->Fill(aq_select_v);
  haq14->Fill(aq_select_v);
  haq15->Fill(aq_select_v);
  haq16->Fill(aq_select_v);
  haq17->Fill(aq_select_v);
  haq18->Fill(aq_select_v);
  haq19->Fill(aq_select_v);
  haq20->Fill(aq_select_v);
  haq21->Fill(aq_select_v);
  haq22->Fill(aq_select_v);
  haq23->Fill(aq_select_v);
  haq24->Fill(aq_select_v);
  haq25->Fill(aq_select_v);
  haq26->Fill(aq_select_v);
  haq27->Fill(aq_select_v);
  haq28->Fill(aq_select_v);
  haq29->Fill(aq_select_v);
  haq30->Fill(aq_select_v);

}  }

   file_load_v->Close();  
}else if(j==4){

 cout << " Filling events in Z = 24 region " << endl;

//TFile* file_load_cr = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_cr = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_cr){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_cr = (TTree*) gDirectory->Get("tree");
 tree_cr->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.cr.root");

 TClonesArray *array_mass_cr = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_cr = NULL;
 art::TEventHeader *array_eventheader_cr= NULL;

 tree_cr->SetBranchAddress("mass",&array_mass_cr);
 tree_cr->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_cr);
 tree_cr->SetBranchAddress("eventheader",&array_eventheader_cr);
 tree_cr->SetBranchStatus("*",0);
 tree_cr->SetBranchStatus("mass",1);
 tree_cr->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_cr->SetBranchStatus("eventheader",1);


 Int_t nData_cr = tree_cr->GetEntries();

for (int i=0; i < nData_cr; i++){
 tree_cr->GetEntry(i);

 Int_t hit_mass_cr = array_mass_cr->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_cr = array_mass_corst1_BLD_4th_cr->GetEntriesFast();

if( hit_mass_cr > 0 && hit_mass_corst1_BLD_4th_cr > 0){

 art::TMassData *mass_cr = (art::TMassData*) array_mass_cr->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_cr = (art::TMassData*) array_mass_corst1_BLD_4th_cr->UncheckedAt(0);

 Double_t z_select_cr = mass_cr->GetZ();
 Double_t aq_select_cr = mass_corst1_BLD_4th_cr->GetAq();
 Int_t runnumber_cr = array_eventheader_cr->GetRunNumber();

  Int_t J = runnumber_cr - 170;

  h_39ca[J]->Fill(aq_select_cr);
  h_40ca[J]->Fill(aq_select_cr);
  h_41ca[J]->Fill(aq_select_cr);
  h_40sc[J]->Fill(aq_select_cr);
  h_41sc[J]->Fill(aq_select_cr);
  h_43sc[J]->Fill(aq_select_cr);
  h_40ti[J]->Fill(aq_select_cr);
  h_41ti[J]->Fill(aq_select_cr);
  h_43ti[J]->Fill(aq_select_cr);
  h_43v[J]->Fill(aq_select_cr);
  h_44v[J]->Fill(aq_select_cr);
  h_45v[J]->Fill(aq_select_cr);
  h_44cr[J]->Fill(aq_select_cr);
  h_45cr[J]->Fill(aq_select_cr);
  h_46cr[J]->Fill(aq_select_cr);
  h_46mn[J]->Fill(aq_select_cr);
  h_47mn[J]->Fill(aq_select_cr);
  h_48mn[J]->Fill(aq_select_cr);
  h_48fe[J]->Fill(aq_select_cr);
  h_49fe[J]->Fill(aq_select_cr);
  h_50fe[J]->Fill(aq_select_cr);



  hzaq->Fill(aq_select_cr,z_select_cr);
  haq_all->Fill(aq_select_cr);

  haq1->Fill(aq_select_cr); 
  haq2->Fill(aq_select_cr); 
  haq3->Fill(aq_select_cr); 
  haq4->Fill(aq_select_cr); 
  haq5->Fill(aq_select_cr); 
  haq6->Fill(aq_select_cr); 
  haq7->Fill(aq_select_cr); 
  haq8->Fill(aq_select_cr); 
  haq9->Fill(aq_select_cr); 
  haq10->Fill(aq_select_cr);  
  haq11->Fill(aq_select_cr);
  haq12->Fill(aq_select_cr);
  haq13->Fill(aq_select_cr);
  haq14->Fill(aq_select_cr);
  haq15->Fill(aq_select_cr);
  haq16->Fill(aq_select_cr);
  haq17->Fill(aq_select_cr);
  haq18->Fill(aq_select_cr);
  haq19->Fill(aq_select_cr);
  haq20->Fill(aq_select_cr);
  haq21->Fill(aq_select_cr);
  haq22->Fill(aq_select_cr);
  haq23->Fill(aq_select_cr);
  haq24->Fill(aq_select_cr);
  haq25->Fill(aq_select_cr);
  haq26->Fill(aq_select_cr);
  haq27->Fill(aq_select_cr);
  haq28->Fill(aq_select_cr);
  haq29->Fill(aq_select_cr);
  haq30->Fill(aq_select_cr);
 
}  }

   file_load_cr->Close();  
}else if(j==5){

 cout << " Filling events in Z = 25 region " << endl;

//TFile* file_load_mn = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_mn = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_mn){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_mn = (TTree*) gDirectory->Get("tree");
 tree_mn->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.mn.root");

 TClonesArray *array_mass_mn = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_mn = NULL;
 art::TEventHeader *array_eventheader_mn= NULL;

 tree_mn->SetBranchAddress("mass",&array_mass_mn);
 tree_mn->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_mn);
 tree_mn->SetBranchAddress("eventheader",&array_eventheader_mn);
 tree_mn->SetBranchStatus("*",0);
 tree_mn->SetBranchStatus("mass",1);
 tree_mn->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_mn->SetBranchStatus("eventheader",1);


 Int_t nData_mn = tree_mn->GetEntries();

for (int i=0; i < nData_mn; i++){
 tree_mn->GetEntry(i);

 Int_t hit_mass_mn = array_mass_mn->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_mn = array_mass_corst1_BLD_4th_mn->GetEntriesFast();

if( hit_mass_mn > 0 && hit_mass_corst1_BLD_4th_mn > 0){

 art::TMassData *mass_mn = (art::TMassData*) array_mass_mn->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_mn = (art::TMassData*) array_mass_corst1_BLD_4th_mn->UncheckedAt(0);

 Double_t z_select_mn = mass_mn->GetZ();
 Double_t aq_select_mn = mass_corst1_BLD_4th_mn->GetAq();
 Int_t runnumber_mn = array_eventheader_mn->GetRunNumber();

  Int_t J = runnumber_mn - 170;

  h_39ca[J]->Fill(aq_select_mn);
  h_40ca[J]->Fill(aq_select_mn);
  h_41ca[J]->Fill(aq_select_mn);
  h_40sc[J]->Fill(aq_select_mn);
  h_41sc[J]->Fill(aq_select_mn);
  h_43sc[J]->Fill(aq_select_mn);
  h_40ti[J]->Fill(aq_select_mn);
  h_41ti[J]->Fill(aq_select_mn);
  h_43ti[J]->Fill(aq_select_mn);
  h_43v[J]->Fill(aq_select_mn);
  h_44v[J]->Fill(aq_select_mn);
  h_45v[J]->Fill(aq_select_mn);
  h_44cr[J]->Fill(aq_select_mn);
  h_45cr[J]->Fill(aq_select_mn);
  h_46cr[J]->Fill(aq_select_mn);
  h_46mn[J]->Fill(aq_select_mn);
  h_47mn[J]->Fill(aq_select_mn);
  h_48mn[J]->Fill(aq_select_mn);
  h_48fe[J]->Fill(aq_select_mn);
  h_49fe[J]->Fill(aq_select_mn);
  h_50fe[J]->Fill(aq_select_mn);



  hzaq->Fill(aq_select_mn,z_select_mn);
  haq_all->Fill(aq_select_mn);

  haq1->Fill(aq_select_mn); 
  haq2->Fill(aq_select_mn); 
  haq3->Fill(aq_select_mn); 
  haq4->Fill(aq_select_mn); 
  haq5->Fill(aq_select_mn); 
  haq6->Fill(aq_select_mn); 
  haq7->Fill(aq_select_mn); 
  haq8->Fill(aq_select_mn); 
  haq9->Fill(aq_select_mn); 
  haq10->Fill(aq_select_mn);  
  haq11->Fill(aq_select_mn);
  haq12->Fill(aq_select_mn);
  haq13->Fill(aq_select_mn);
  haq14->Fill(aq_select_mn);
  haq15->Fill(aq_select_mn);
  haq16->Fill(aq_select_mn);
  haq17->Fill(aq_select_mn);
  haq18->Fill(aq_select_mn);
  haq19->Fill(aq_select_mn);
  haq20->Fill(aq_select_mn);
  haq21->Fill(aq_select_mn);
  haq22->Fill(aq_select_mn);
  haq23->Fill(aq_select_mn);
  haq24->Fill(aq_select_mn);
  haq25->Fill(aq_select_mn);
  haq26->Fill(aq_select_mn);
  haq27->Fill(aq_select_mn);
  haq28->Fill(aq_select_mn);
  haq29->Fill(aq_select_mn);
  haq30->Fill(aq_select_mn);
  
 
}  }

   file_load_mn->Close();  
}else if(j==6){

 cout << " Filling events in Z = 26 region " << endl;

//TFile* file_load_fe = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_fe = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_fe){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_fe = (TTree*) gDirectory->Get("tree");
 tree_fe->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.fe.root");

 TClonesArray *array_mass_fe = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_fe = NULL;
 art::TEventHeader *array_eventheader_fe= NULL;

 tree_fe->SetBranchAddress("mass",&array_mass_fe);
 tree_fe->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_fe);
 tree_fe->SetBranchAddress("eventheader",&array_eventheader_fe);
 tree_fe->SetBranchStatus("*",0);
 tree_fe->SetBranchStatus("mass",1);
 tree_fe->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_fe->SetBranchStatus("eventheader",1);


 Int_t nData_fe = tree_fe->GetEntries();

for (int i=0; i < nData_fe; i++){
 tree_fe->GetEntry(i);

 Int_t hit_mass_fe = array_mass_fe->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_fe = array_mass_corst1_BLD_4th_fe->GetEntriesFast();

if( hit_mass_fe > 0 && hit_mass_corst1_BLD_4th_fe > 0){

 art::TMassData *mass_fe = (art::TMassData*) array_mass_fe->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_fe = (art::TMassData*) array_mass_corst1_BLD_4th_fe->UncheckedAt(0);

 Double_t z_select_fe = mass_fe->GetZ();
 Double_t aq_select_fe = mass_corst1_BLD_4th_fe->GetAq();
 Int_t runnumber_fe = array_eventheader_fe->GetRunNumber();

  Int_t J = runnumber_fe - 170;

  h_39ca[J]->Fill(aq_select_fe);
  h_40ca[J]->Fill(aq_select_fe);
  h_41ca[J]->Fill(aq_select_fe);
  h_40sc[J]->Fill(aq_select_fe);
  h_41sc[J]->Fill(aq_select_fe);
  h_43sc[J]->Fill(aq_select_fe);
  h_40ti[J]->Fill(aq_select_fe);
  h_41ti[J]->Fill(aq_select_fe);
  h_43ti[J]->Fill(aq_select_fe);
  h_43v[J]->Fill(aq_select_fe);
  h_44v[J]->Fill(aq_select_fe);
  h_45v[J]->Fill(aq_select_fe);
  h_44cr[J]->Fill(aq_select_fe);
  h_45cr[J]->Fill(aq_select_fe);
  h_46cr[J]->Fill(aq_select_fe);
  h_46mn[J]->Fill(aq_select_fe);
  h_47mn[J]->Fill(aq_select_fe);
  h_48mn[J]->Fill(aq_select_fe);
  h_48fe[J]->Fill(aq_select_fe);
  h_49fe[J]->Fill(aq_select_fe);
  h_50fe[J]->Fill(aq_select_fe);



  hzaq->Fill(aq_select_fe,z_select_fe);
  haq_all->Fill(aq_select_fe);

  haq1->Fill(aq_select_fe); 
  haq2->Fill(aq_select_fe); 
  haq3->Fill(aq_select_fe); 
  haq4->Fill(aq_select_fe); 
  haq5->Fill(aq_select_fe); 
  haq6->Fill(aq_select_fe); 
  haq7->Fill(aq_select_fe); 
  haq8->Fill(aq_select_fe); 
  haq9->Fill(aq_select_fe); 
  haq10->Fill(aq_select_fe);  
  haq11->Fill(aq_select_fe);
  haq12->Fill(aq_select_fe);
  haq13->Fill(aq_select_fe);
  haq14->Fill(aq_select_fe);
  haq15->Fill(aq_select_fe);
  haq16->Fill(aq_select_fe);
  haq17->Fill(aq_select_fe);
  haq18->Fill(aq_select_fe);
  haq19->Fill(aq_select_fe);
  haq20->Fill(aq_select_fe);
  haq21->Fill(aq_select_fe);
  haq22->Fill(aq_select_fe);
  haq23->Fill(aq_select_fe);
  haq24->Fill(aq_select_fe);
  haq25->Fill(aq_select_fe);
  haq26->Fill(aq_select_fe);
  haq27->Fill(aq_select_fe);
  haq28->Fill(aq_select_fe);
  haq29->Fill(aq_select_fe);
  haq30->Fill(aq_select_fe);
 
}  }

   file_load_fe->Close();  

}else if(j==7){

 cout << " Filling events in Z = 27 region " << endl;

//TFile* file_load_co = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_co = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_co){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_co = (TTree*) gDirectory->Get("tree");
 tree_co->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.co.root");

 TClonesArray *array_mass_co = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_co = NULL;
 art::TEventHeader *array_eventheader_co= NULL;

 tree_co->SetBranchAddress("mass",&array_mass_co);
 tree_co->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_co);
 tree_co->SetBranchAddress("eventheader",&array_eventheader_co);
 tree_co->SetBranchStatus("*",0);
 tree_co->SetBranchStatus("mass",1);
 tree_co->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_co->SetBranchStatus("eventheader",1);


 Int_t nData_co = tree_co->GetEntries();

for (int i=0; i < nData_co; i++){
 tree_co->GetEntry(i);

 Int_t hit_mass_co = array_mass_co->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_co = array_mass_corst1_BLD_4th_co->GetEntriesFast();

if( hit_mass_co > 0 && hit_mass_corst1_BLD_4th_co > 0){

 art::TMassData *mass_co = (art::TMassData*) array_mass_co->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_co = (art::TMassData*) array_mass_corst1_BLD_4th_co->UncheckedAt(0);

 Double_t z_select_co = mass_co->GetZ();
 Double_t aq_select_co = mass_corst1_BLD_4th_co->GetAq();
 Int_t runnumber_co = array_eventheader_co->GetRunNumber();

  Int_t J = runnumber_co - 170;

  h_39ca[J]->Fill(aq_select_co);
  h_40ca[J]->Fill(aq_select_co);
  h_41ca[J]->Fill(aq_select_co);
  h_40sc[J]->Fill(aq_select_co);
  h_41sc[J]->Fill(aq_select_co);
  h_43sc[J]->Fill(aq_select_co);
  h_40ti[J]->Fill(aq_select_co);
  h_41ti[J]->Fill(aq_select_co);
  h_43ti[J]->Fill(aq_select_co);
  h_43v[J]->Fill(aq_select_co);
  h_44v[J]->Fill(aq_select_co);
  h_45v[J]->Fill(aq_select_co);
  h_44cr[J]->Fill(aq_select_co);
  h_45cr[J]->Fill(aq_select_co);
  h_46cr[J]->Fill(aq_select_co);
  h_46mn[J]->Fill(aq_select_co);
  h_47mn[J]->Fill(aq_select_co);
  h_48mn[J]->Fill(aq_select_co);
  h_48fe[J]->Fill(aq_select_co);
  h_49fe[J]->Fill(aq_select_co);
  h_50fe[J]->Fill(aq_select_co);



  hzaq->Fill(aq_select_co,z_select_co);
  haq_all->Fill(aq_select_co);

  haq1->Fill(aq_select_co); 
  haq2->Fill(aq_select_co); 
  haq3->Fill(aq_select_co); 
  haq4->Fill(aq_select_co); 
  haq5->Fill(aq_select_co); 
  haq6->Fill(aq_select_co); 
  haq7->Fill(aq_select_co); 
  haq8->Fill(aq_select_co); 
  haq9->Fill(aq_select_co); 
  haq10->Fill(aq_select_co);  
  haq11->Fill(aq_select_co);
  haq12->Fill(aq_select_co);
  haq13->Fill(aq_select_co);
  haq14->Fill(aq_select_co);
  haq15->Fill(aq_select_co);
  haq16->Fill(aq_select_co);
  haq17->Fill(aq_select_co);
  haq18->Fill(aq_select_co);
  haq19->Fill(aq_select_co);
  haq20->Fill(aq_select_co);
  haq21->Fill(aq_select_co);
  haq22->Fill(aq_select_co);
  haq23->Fill(aq_select_co);
  haq24->Fill(aq_select_co);
  haq25->Fill(aq_select_co);
  haq26->Fill(aq_select_co);
  haq27->Fill(aq_select_co);
  haq28->Fill(aq_select_co);
  haq29->Fill(aq_select_co);
  haq30->Fill(aq_select_co);
 
}  }

   file_load_co->Close();  

}else if(j==8){

 cout << " Filling events in Z = 28 region " << endl;

//TFile* file_load_ni = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root");
TFile* file_load_ni = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root");
  if(!file_load_ni){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree_ni = (TTree*) gDirectory->Get("tree");
 tree_ni->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.ni.root");

 TClonesArray *array_mass_ni = NULL;
 TClonesArray *array_mass_corst1_BLD_4th_ni = NULL;
 art::TEventHeader *array_eventheader_ni= NULL;

 tree_ni->SetBranchAddress("mass",&array_mass_ni);
 tree_ni->SetBranchAddress("mass_corst1_BLD_4th",&array_mass_corst1_BLD_4th_ni);
 tree_ni->SetBranchAddress("eventheader",&array_eventheader_ni);
 tree_ni->SetBranchStatus("*",0);
 tree_ni->SetBranchStatus("mass",1);
 tree_ni->SetBranchStatus("mass_corst1_BLD_4th",1);
 tree_ni->SetBranchStatus("eventheader",1);


 Int_t nData_ni = tree_ni->GetEntries();

for (int i=0; i < nData_ni; i++){
 tree_ni->GetEntry(i);

 Int_t hit_mass_ni = array_mass_ni->GetEntriesFast();
 Int_t hit_mass_corst1_BLD_4th_ni = array_mass_corst1_BLD_4th_ni->GetEntriesFast();

if( hit_mass_ni > 0 && hit_mass_corst1_BLD_4th_ni > 0){

 art::TMassData *mass_ni = (art::TMassData*) array_mass_ni->UncheckedAt(0);
 art::TMassData *mass_corst1_BLD_4th_ni = (art::TMassData*) array_mass_corst1_BLD_4th_ni->UncheckedAt(0);
// art::TEventHeader *eventheader_fe = (art::TEventHeader*) array_eventheader_fe->UncheckedAt(0);

 Double_t z_select_ni = mass_ni->GetZ();
 Double_t aq_select_ni = mass_corst1_BLD_4th_ni->GetAq();
 Int_t runnumber_ni = array_eventheader_ni->GetRunNumber();

  Int_t J = runnumber_ni - 170;

  h_39ca[J]->Fill(aq_select_ni);
  h_40ca[J]->Fill(aq_select_ni);
  h_41ca[J]->Fill(aq_select_ni);
  h_40sc[J]->Fill(aq_select_ni);
  h_41sc[J]->Fill(aq_select_ni);
  h_43sc[J]->Fill(aq_select_ni);
  h_40ti[J]->Fill(aq_select_ni);
  h_41ti[J]->Fill(aq_select_ni);
  h_43ti[J]->Fill(aq_select_ni);
  h_43v[J]->Fill(aq_select_ni);
  h_44v[J]->Fill(aq_select_ni);
  h_45v[J]->Fill(aq_select_ni);
  h_44cr[J]->Fill(aq_select_ni);
  h_45cr[J]->Fill(aq_select_ni);
  h_46cr[J]->Fill(aq_select_ni);
  h_46mn[J]->Fill(aq_select_ni);
  h_47mn[J]->Fill(aq_select_ni);
  h_48mn[J]->Fill(aq_select_ni);
  h_48fe[J]->Fill(aq_select_ni);
  h_49fe[J]->Fill(aq_select_ni);
  h_50fe[J]->Fill(aq_select_ni);



  hzaq->Fill(aq_select_ni,z_select_ni);
  haq_all->Fill(aq_select_ni);

  haq1->Fill(aq_select_ni); 
  haq2->Fill(aq_select_ni); 
  haq3->Fill(aq_select_ni); 
  haq4->Fill(aq_select_ni); 
  haq5->Fill(aq_select_ni); 
  haq6->Fill(aq_select_ni); 
  haq7->Fill(aq_select_ni); 
  haq8->Fill(aq_select_ni); 
  haq9->Fill(aq_select_ni); 
  haq10->Fill(aq_select_ni);  
  haq11->Fill(aq_select_ni);
  haq12->Fill(aq_select_ni);
  haq13->Fill(aq_select_ni);
  haq14->Fill(aq_select_ni);
  haq15->Fill(aq_select_ni);
  haq16->Fill(aq_select_ni);
  haq17->Fill(aq_select_ni);
  haq18->Fill(aq_select_ni);
  haq19->Fill(aq_select_ni);
  haq20->Fill(aq_select_ni);
  haq21->Fill(aq_select_ni);
  haq22->Fill(aq_select_ni);
  haq23->Fill(aq_select_ni);
  haq24->Fill(aq_select_ni);
  haq25->Fill(aq_select_ni);
  haq26->Fill(aq_select_ni);
  haq27->Fill(aq_select_ni);
  haq28->Fill(aq_select_ni);
  haq29->Fill(aq_select_ni);
  haq30->Fill(aq_select_ni);
 
}  }

//   file_ni->Close();  
   file_load_ni->Close();  


}}

 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/mass_corst1_BLD_4th_all.170272.hist.root","recreate");

for (Int_t iievt = 0; iievt < 103; iievt++){
 h_39ca[iievt]->Write();
 h_40ca[iievt]->Write();
 h_41ca[iievt]->Write();
 h_40sc[iievt]->Write();
 h_41sc[iievt]->Write();
 h_43sc[iievt]->Write();
 h_40ti[iievt]->Write();
 h_41ti[iievt]->Write();
 h_43ti[iievt]->Write();
 h_43v[iievt]->Write();
 h_44v[iievt]->Write();
 h_45v[iievt]->Write();
 h_44cr[iievt]->Write();
 h_45cr[iievt]->Write();
 h_46cr[iievt]->Write();
 h_46mn[iievt]->Write();
 h_47mn[iievt]->Write();
 h_48mn[iievt]->Write();
 h_48fe[iievt]->Write();
 h_49fe[iievt]->Write();
 h_50fe[iievt]->Write();

}

 hzaq->Write();
 haq_all->Write();
 haq1->Write(); 
 haq2->Write(); 
 haq3->Write(); 
 haq4->Write(); 
 haq5->Write(); 
 haq6->Write(); 
 haq7->Write(); 
 haq8->Write(); 
 haq9->Write(); 
 haq10->Write();  
 haq11->Write();
 haq12->Write();
 haq13->Write();
 haq14->Write();
 haq15->Write();
 haq16->Write();
 haq17->Write();
 haq18->Write();
 haq19->Write();
 haq20->Write();
 haq21->Write();
 haq22->Write();
 haq23->Write();
 haq24->Write();
 haq25->Write();
 haq26->Write();
 haq27->Write();
 haq28->Write();
 haq29->Write();
 haq30->Write();

 ofile->Close();



}


