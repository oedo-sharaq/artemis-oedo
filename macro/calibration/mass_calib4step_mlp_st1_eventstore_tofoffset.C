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

void mass_calib4step_svd_st1_eventstore_tofoffset(){

// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset_for4th.170272.all.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root"); // Load file. Basically BLD file.
 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_ssdpla_tofoffset.170272.all.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step.eventstore.170272.all.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.170272.all.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/physics.chkmass_st1_3step_for4th_unit2.170272.all.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/physics.chkmass_st1_3step_for4th_ssdpla.170272.all.root"); // Add file. Basically mass calibration file.
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.all.root"); // Add file. Basically mass calibration file.

//  const Int_t Nrun = 250;  //the number of runs
//  const Int_t Nrun = 2500;  //the number of runs
  const Int_t Nrun = 1800;  //the number of runs
//  const Int_t Nrun = 2000;  //the number of runs
  const Int_t Nref =  21;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nprm =  1001;  //the number of parameters 3rd order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_dia_tof32st1 = NULL;
// TClonesArray *array_dia_tof32st1_off = NULL;
 TClonesArray *array_mass_corst1 = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_trackd = NULL;
 TClonesArray *array_s0 = NULL;
 art::TEventHeader *array_eventheader = NULL;

// tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_zcal",&array_mass);
 tree->SetBranchAddress("dia_tof32st1",&array_dia_tof32st1);
// tree->SetBranchAddress("dia_tof32st1_off",&array_dia_tof32st1_off);
 tree->SetBranchAddress("dia_tof32st1",&array_dia_tof32st1);
 tree->SetBranchAddress("mass_corst1_BLD_3rd",&array_mass_corst1);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("s2",&array_trackd);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
// tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_zcal",1);
 tree->SetBranchStatus("dia_tof32st1",1);
// tree->SetBranchStatus("dia_tof32st1_off",1);
 tree->SetBranchStatus("dia_tof32st1",1);
 tree->SetBranchStatus("mass_corst1_BLD_3rd",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2",1);
 tree->SetBranchStatus("sr0_xcw",1);
 tree->SetBranchStatus("eventheader",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;

// ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_3step_st1.dat");
 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_3step_st1_ref2.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

  while(!fin.eof()){
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);
		}
 fin.close();

  TNtuple* anntree = new TNtuple("anntree","anntree","c0:c1:c2:c3:c4:c5,c6,c7,c8,c9:f");


//// Fill date 

 int ievt = 0;
 Bool_t HasEvents = true;
 Int_t nData = tree->GetEntries();

for (int iref = 0; iref < Nref; iref++){
    vector<Int_t> irandm;
	int n_tmp = 0;

  for(int i = 0; i < nData; i++){
	  tree->GetEntry(i);

      Int_t hit_mass = array_mass->GetEntriesFast();
      Int_t hit_mass_corst1 = array_mass_corst1->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_trackd = array_trackd->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_mass_corst1 > 0 && hit_tracku > 0 && hit_trackd > 0 && hit_s0 > 0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMassData *mass_corst1_tmp = (art::TMassData*) array_mass_corst1->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_corst1_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     art::TMWDCTrackingResult *trackd_tmp = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsGood();
     Bool_t trackd_ok = trackd_tmp->IsGood();

//     Int_t runnumber_tmp = array_eventheader->GetRunNumber();
//     if (runnumber_tmp == 181 || runnumber_tmp == 198 || runnumber_tmp == 217 || runnumber_tmp == 218 || runnumber_tmp == 219 || runnumber_tmp == 220 || runnumber_tmp == 221 || runnumber_tmp == 255) continue;

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok && trackd_ok)
    {
      irandm.push_back(i);
      n_tmp++;
     }else {
       continue;
    	}
    }else{
	  continue;
       }
   }

  if (n_tmp < Nrun){
    cout << "Caution!! Reference No." << iref << " does not have enough number of events.\n";
    HasEvents = false;  
	continue;
    }else{
      cout << "Sampling events of Reference No." << iref << " was finished.\n";
    }

//// Generate random run number
     for (int r = 0; r < Nrun; r++){
         int j = gRandom->Uniform(r,n_tmp);
		 int randm_tmp = irandm[r];
		 irandm[r] = irandm[j];
       	 irandm[j] = randm_tmp;
     }

//// Fill data in matrix for each Ref	 
   for(int p = 0; p < Nrun; p++){
     int k = irandm[p];
     tree->GetEntry(k);
	 art::TMassData *mass = (art::TMassData*) array_mass->UncheckedAt(0);
//	 art::TDiaTimingData *dia_tof32st1_off = (art::TDiaTimingData*) array_dia_tof32st1_off->UncheckedAt(0);
	 art::TDiaTimingData *dia_tof32st1 = (art::TDiaTimingData*) array_dia_tof32st1->UncheckedAt(0);
	 art::TMassData *mass_corst1 = (art::TMassData*) array_mass_corst1->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TMWDCTrackingResult *trackd = (art::TMWDCTrackingResult*) array_trackd->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t z_select = mass->GetZ();
     Double_t aq_select = mass_corst1->GetAq();
     Int_t runnumber = array_eventheader->GetRunNumber();

//     Double_t ti = dia_tof32st1_off->GetTiming();
     Double_t ti = dia_tof32st1->GetTiming();
     Double_t x3i = tracku->GetX();
     Double_t a3i = tracku->GetA() * 1000.;
     Double_t y3i = tracku->GetY();
     Double_t b3i = tracku->GetB() * 1000.;
     Double_t x0i = sr0->GetPosition();
     Double_t x2i = trackd->GetX();
     Double_t a2i = trackd->GetA() * 1000.;
     Double_t y2i = trackd->GetY();
     Double_t b2i = trackd->GetB() * 1000.;
     Double_t ssrd = trackd->GetSSR();

// unit orientation
//     Double_t t = (ti - 2042.) * 0.25;  
//     Double_t x3 = x3i * 0.1; 
//     Double_t a3 = a3i * 0.1;
//     Double_t y3 = y3i * 0.1;
//     Double_t b3 = b3i * 0.1;
//     Double_t x0 = x0i * 0.1; 
//     Double_t x2 = x2i * 0.1; 
//     Double_t a2 = a2i * 0.1;
//     Double_t y2 = y2i * 0.1;
//     Double_t b2 = b2i * 0.1;

//     Double_t t = (ti - 2042.) * 0.125;  
//     Double_t x3 = x3i * 0.1; 
//     Double_t a3 = a3i * 0.1;
//     Double_t y3 = y3i;
//     Double_t b3 = b3i * 0.1 + 1;
//     Double_t x0 = x0i * 0.05; 
//     Double_t x2 = x2i * 0.1; 
//     Double_t a2 = a2i * 0.05;
//     Double_t y2 = y2i * 0.05 - 1;
//     Double_t b2 = b2i * 0.05 - 0.2;

     Double_t t = (ti - 2042.) * 0.125;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1;
     Double_t y3 = y3i + 2;
     Double_t b3 = b3i * 0.05 + 0.5;
     Double_t x0 = x0i * 0.015; 
     Double_t x2 = x2i * 0.1; 
     Double_t a2 = a2i * 0.025;
     Double_t y2 = y2i * 0.05 - 1;
     Double_t b2 = b2i * 0.05 - 0.2;


     Double_t c0 = t;
     Double_t c1 = x3;
     Double_t c2 = a3;
     Double_t c3 = y3;
     Double_t c4 = b3;
     Double_t c5 = x0;
     Double_t c6 = x2;
     Double_t c7 = a2;
     Double_t c8 = y2;
     Double_t c9 = b2;
     Double_t f = Ref_m[iref];
	  
	 anntree->Fill(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,f);
  
     value(ievt,0) = z_select;
     value(ievt,1) = aq_select;
     value(ievt,2) = t;
     value(ievt,3) = x3;
     value(ievt,4) = a3;
     value(ievt,5) = y3;
     value(ievt,6) = b3;
     value(ievt,7) = x0;
     value(ievt,8) = x2;
     value(ievt,9) = a2;
     value(ievt,10) = y2;
     value(ievt,11) = b2;
     value(ievt,12) = runnumber;
     value(ievt,13) = ssrd;

     ievt++;

	 }
	
}
 if(ievt != Nevt){
	 cout << "The number of events is " << ievt << " Not equal to " << Nevt << endl;
 }else{
	 cout << "The number of events is " << ievt << " " << endl;
	 }
 if(!HasEvents){
    cout << "Some species has not enough number of events,\n";
	return; 
 }

// ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_eachstripst1_ref1_4step.dat");
// ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_eachstripst1_ref2_4step.dat");
// ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_eachstripst1_ref2_4step_nooff.dat");
 ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_svd4th_eachstripst1_ref2_4.5step_nooff.dat");
 if (foutselect.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	for(int m = 0; m < 14; m++){
		foutselect << value(n,m) << "  "  << " | ";
	}
	foutselect << "\n";
}

	foutselect.close();


//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref1_4step.hist_selected.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref2_4step.hist_selected.root","recreate");
//   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref2_4step_nooff.hist_selected.root","recreate");
   TFile *ofv = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref2_4.5step_nooff.hist_selected.root","recreate");

  TH1D *tof_selected = new TH1D("tof_selected","tof_selected",1000,-10,10);
  TH1D *x3_selected = new TH1D("x3_selected","x3_selected",300,-5,5);
  TH1D *a3_selected = new TH1D("a3_selected","a3_selected",300,-5,5);
  TH1D *y3_selected = new TH1D("y3_selected","y3_selected",300,-5,5);
  TH1D *b3_selected = new TH1D("b3_selected","b3_selected",300,-5,5);
  TH1D *x0_selected = new TH1D("x0_selected","x0_selected",300,-5,5);
  TH1D *x2_selected = new TH1D("x2_selected","x2_selected",300,-5,5);
  TH1D *a2_selected = new TH1D("a2_selected","a2_selected",300,-5,5);
  TH1D *y2_selected = new TH1D("y2_selected","y2_selected",300,-5,5);
  TH2D *y2ssr_selected = new TH2D("y2ssr_selected","y2ssr_select5ed",300,-5,5,300,0,5);
  TH1D *b2_selected = new TH1D("b2_selected","b2_selected",300,-5,5);
  TH2D *b2ssr_selected = new TH2D("b2ssr_selected","b2ssr_selected",300,-5,5,300,0,5);
  TH1D *event_selected = new TH1D("event_selected","event_selected",102,169.5,271.5);

 for(int nn = 0; nn < Nevt; nn++){
  tof_selected->Fill(value(nn,2));
  x3_selected->Fill(value(nn,3));
  a3_selected->Fill(value(nn,4));
  y3_selected->Fill(value(nn,5));
  b3_selected->Fill(value(nn,6));
  x0_selected->Fill(value(nn,7));
  x2_selected->Fill(value(nn,8));
  a2_selected->Fill(value(nn,9));
  y2_selected->Fill(value(nn,10));
  y2ssr_selected->Fill(value(nn,10),value(nn,13));
  b2_selected->Fill(value(nn,11));
  b2ssr_selected->Fill(value(nn,11),value(nn,13));
  event_selected->Fill(value(nn,12));
}

 tof_selected->Write();
 x3_selected->Write(); 
 a3_selected->Write();
 y3_selected->Write();
 b3_selected->Write();
 x0_selected->Write();
 x2_selected->Write();
 a2_selected->Write();
 y2_selected->Write();
 y2ssr_selected->Write();
 b2_selected->Write();
 b2ssr_selected->Write();
 event_selected->Write();
 
 ofv->Close();

//// Set ANN

  TMultiLayerPerceptron* mlp = new TMultiLayerPerceptron("c0,c1,c2,c3,c4,c5,c6,c7,c8,c9:12:10:f", anntree,  "Entry$%2","(Entry$%2)==0");
   mlp->Train(1000, "graph update=10");

   TMLPAnalyzer* mlpa = new TMLPAnalyzer(mlp);
   mlpa->GatherInformations();
   mlpa->CheckNetwork();
   mlpa->DrawDInputs();


   gROOT->ProcessLine("zone 1 2");
   gROOT->ProcessLine("pcd 1");
   mlp->Draw();

   gROOT->ProcessLine("pcd 2");
   mlpa->DrawTruthDeviations();


//// Check results for selected events
 TH1D *h_aq_sol = new TH1D("aq_sol", "aq_sol",1000,1.7,2.3);

 TH1D *h_38Ca_sol = new TH1D("h38Ca_sol", "h38Ca_sol",1000,1.89,1.91);
 TH1D *h_39Ca_sol = new TH1D("h39Ca_sol", "h39Ca_sol",1000,1.940,1.960);
// TH1D *h_40Ca_sol = new TH1D("h40Ca_sol", "h40Ca_sol",1000,1.990,2.01);
 TH1D *h_41Ca_sol = new TH1D("h41Ca_sol", "h41Ca_sol",1000,2.040,2.060);
                                    
 TH1D *h_40Sc_sol = new TH1D("h40Sc_sol", "h40Sc_sol",1000,1.900,1.92);
 TH1D *h_41Sc_sol = new TH1D("h41Sc_sol", "h41Sc_sol",1000,1.945,1.965);
 TH1D *h_43Sc_sol = new TH1D("h43Sc_sol", "h43Sc_sol",1000,2.04,2.060);
                                
 TH1D *h_40Ti_sol = new TH1D("h40Ti_sol", "h40Ti_sol",1000,1.81,1.83);
 TH1D *h_41Ti_sol = new TH1D("h41Ti_sol", "h41Ti_sol",1000,1.86,1.88);
// TH1D *h_43Ti_sol = new TH1D("h43Ti_sol", "h43Ti_sol",1000,1.940,1.960);
 TH1D *h_47Ti_sol = new TH1D("h47Ti_sol", "h47Ti_sol",1000,2.125,2.145);
                                         
 TH1D *h_43V_sol  = new TH1D("h43V_sol", "h43V_sol",1000,1.86,1.880);
 TH1D *h_44V_sol  = new TH1D("h44V_sol", "h44V_sol",1000,1.90,1.92);
// TH1D *h_45V_sol  = new TH1D("h45V_sol", "h45V_sol",1000,1.945,1.965);
 TH1D *h_47V_sol  = new TH1D("h47V_sol", "h47V_sol",1000,2.01,2.21);
                                    
 TH1D *h_44Cr_sol = new TH1D("h44Cr_sol", "h44Cr_sol",1000,1.83,1.85);
 TH1D *h_45Cr_sol = new TH1D("h45Cr_sol", "h45Cr_sol",1000,1.865,1.885);
 TH1D *h_46Cr_sol = new TH1D("h46Cr_sol", "h46Cr_sol",1000,1.90,1.925);
                                    
 TH1D *h_46Mn_sol = new TH1D("h46Mn_sol", "h46Mn_sol",1000,1.83,1.85);
 TH1D *h_47Mn_sol = new TH1D("h47Mn_sol", "h47Mn_sol",1000,1.87,1.897);
 TH1D *h_48Mn_sol = new TH1D("h48Mn_sol", "h48Mn_sol",1000,1.91,1.930);
                                    
 TH1D *h_48Fe_sol = new TH1D("h48Fe_sol", "h48Fe_sol",1000,1.835,1.855);
 TH1D *h_49Fe_sol = new TH1D("h49Fe_sol", "h49Fe_sol",1000,1.87,1.89);
 TH1D *h_50Fe_sol = new TH1D("h50Fe_sol", "h50Fe_sol",1000,1.91,1.930);

 Int_t Nrun_2  = 2 * Nrun;
 Int_t Nrun_3  = 3 * Nrun;
 Int_t Nrun_4  = 4 * Nrun;
 Int_t Nrun_5  = 5 * Nrun;
 Int_t Nrun_6  = 6 * Nrun;
 Int_t Nrun_7  = 7 * Nrun;
 Int_t Nrun_8  = 8 * Nrun;
 Int_t Nrun_9  = 9 * Nrun;
 Int_t Nrun_10 = 10 * Nrun;
 Int_t Nrun_11 = 11 * Nrun;
 Int_t Nrun_12 = 12 * Nrun;
 Int_t Nrun_13 = 13 * Nrun;
 Int_t Nrun_14 = 14 * Nrun;
 Int_t Nrun_15 = 15 * Nrun;
 Int_t Nrun_16 = 16 * Nrun;
 Int_t Nrun_17 = 17 * Nrun;
 Int_t Nrun_18 = 18 * Nrun;
 Int_t Nrun_19 = 19 * Nrun;
 Int_t Nrun_20 = 20 * Nrun;
 Int_t Nrun_21 = 21 * Nrun;

 for (int isol = 0; isol < Nevt; isol++){
  h_aq_sol->Fill(b_re[isol]);

      Double_t c0_tmp = value(isol,2);
      Double_t c1_tmp = value(isol,3);
      Double_t c2_tmp = value(isol,4);
      Double_t c3_tmp = value(isol,5);
      Double_t c4_tmp = value(isol,6);
      Double_t c5_tmp = value(isol,7);
      Double_t c6_tmp = value(isol,8);
      Double_t c7_tmp = value(isol,9);
      Double_t c8_tmp = value(isol,10);
      Double_t c9_tmp = value(isol,11);

     Double_t mlp_prm[10];
     mlp_prm[0] = c0_tmp;
     mlp_prm[1] = c1_tmp;
     mlp_prm[2] = c2_tmp;
     mlp_prm[3] = c3_tmp;
     mlp_prm[4] = c4_tmp;
     mlp_prm[5] = c5_tmp;
     mlp_prm[6] = c6_tmp;
     mlp_prm[7] = c7_tmp;
     mlp_prm[8] = c8_tmp;
     mlp_prm[9] = c9_tmp;

     Double_t mass_calib_sol = mlp->Evaluate(0,mlp_prm);
     
	 h_aq_sol->Fill(mass_calib_sol);


	if(0 <= isol && isol  < Nrun){
	 h_38Ca_sol->Fill(b_re(isol));
//	 h_39Ca_sol->Fill(b_re(isol));
 } else if(Nrun <= isol && isol  < Nrun_2){
	 h_39Ca_sol->Fill(b_re(isol));
//	 h_40Ca_sol->Fill(b_re(isol));
 } else if(Nrun_2 <= isol && isol  < Nrun_3){
	 h_41Ca_sol->Fill(b_re(isol));
 } else if(Nrun_3 <= isol && isol  < Nrun_4){
	 h_40Sc_sol->Fill(b_re(isol));
 } else if(Nrun_4 <= isol && isol  < Nrun_5){
	 h_41Sc_sol->Fill(b_re(isol));
 } else if(Nrun_5 <= isol && isol  < Nrun_6){
	 h_43Sc_sol->Fill(b_re(isol));
 } else if(Nrun_6 <= isol && isol  < Nrun_7){
	 h_40Ti_sol->Fill(b_re(isol));
 } else if(Nrun_7 <= isol && isol  < Nrun_8){
	 h_41Ti_sol->Fill(b_re(isol));
 } else if(Nrun_8 <= isol && isol  < Nrun_9){
	 h_47Ti_sol->Fill(b_re(isol));
//	 h_43Ti_sol->Fill(b_re(isol));
 } else if(Nrun_9 <= isol && isol  < Nrun_10){
	 h_43V_sol->Fill(b_re(isol));
 } else if(Nrun_10 <= isol && isol  < Nrun_11){
	 h_44V_sol->Fill(b_re(isol));
 } else if(Nrun_11 <= isol && isol  < Nrun_12){
	 h_47V_sol->Fill(b_re(isol));
//	 h_45V_sol->Fill(b_re(isol));
 } else if(Nrun_12 <= isol && isol  < Nrun_13){
	 h_44Cr_sol->Fill(b_re(isol));
 } else if(Nrun_13 <= isol && isol  < Nrun_14){
	 h_45Cr_sol->Fill(b_re(isol));
 } else if(Nrun_14 <= isol && isol  < Nrun_15){
	 h_46Cr_sol->Fill(b_re(isol));
 } else if(Nrun_15 <= isol && isol  < Nrun_16){
	 h_46Mn_sol->Fill(b_re(isol));
 } else if(Nrun_16 <= isol && isol  < Nrun_17){
	 h_47Mn_sol->Fill(b_re(isol));
 } else if(Nrun_17 <= isol && isol  < Nrun_18){
	 h_48Mn_sol->Fill(b_re(isol));
 } else if(Nrun_18 <= isol && isol  < Nrun_19){
	 h_48Fe_sol->Fill(b_re(isol));
 } else if(Nrun_19 <= isol && isol  < Nrun_20){
	 h_49Fe_sol->Fill(b_re(isol));
 } else if(Nrun_20 <= isol && isol  < Nrun_21){
	 h_50Fe_sol->Fill(b_re(isol));
 }
}


// Output

 TH1D *h_aq_cor = new TH1D("aq_cor", "aq_cor",500,1.7,2.3);
 TH1D *h_aq_cor_wr = new TH1D("aq_cor_wr", "aq_cor_wr",500,-10,10);

 TH1D *h_38Ca = new TH1D("h38Ca", "h38Ca",1000,1.89,1.91);
 TH1D *h_39Ca = new TH1D("h39Ca", "h39Ca",1000,1.940,1.960);
// TH1D *h_40Ca = new TH1D("h40Ca", "h40Ca",1000,1.990,2.01);
 TH1D *h_41Ca = new TH1D("h41Ca", "h41Ca",1000,2.040,2.060);
                                                            
 TH1D *h_40Sc = new TH1D("h40Sc", "h40Sc",1000,1.900,1.92);
 TH1D *h_41Sc = new TH1D("h41Sc", "h41Sc",1000,1.945,1.965);
 TH1D *h_43Sc = new TH1D("h43Sc", "h43Sc",1000,2.04,2.060);
                                                            
 TH1D *h_40Ti = new TH1D("h40Ti", "h40Ti",1000,1.805,1.825);
 TH1D *h_41Ti = new TH1D("h41Ti", "h41Ti",1000,1.855,1.875);
// TH1D *h_43Ti = new TH1D("h43Ti", "h43Ti",1000,1.940,1.960);
 TH1D *h_47Ti = new TH1D("h47Ti", "h47Ti",1000,2.125,2.145);
                                                            
 TH1D *h_43V  = new TH1D("h43V", "h43V",1000,1.865,1.885);
 TH1D *h_44V  = new TH1D("h44V", "h44V",1000,1.90,1.92);
// TH1D *h_45V  = new TH1D("h45V", "h45V",1000,1.945,1.965);
 TH1D *h_47V  = new TH1D("h47V", "h47V",1000,2.025,2.045);
                                                            
 TH1D *h_44Cr = new TH1D("h44Cr", "h44Cr",1000,1.825,1.845);
 TH1D *h_45Cr = new TH1D("h45Cr", "h45Cr",1000,1.865,1.885);
 TH1D *h_46Cr = new TH1D("h46Cr", "h46Cr",1000,1.90,1.925);
                                                            
 TH1D *h_46Mn = new TH1D("h46Mn", "h46Mn",1000,1.832,1.852);
 TH1D *h_47Mn = new TH1D("h47Mn", "h47Mn",1000,1.87,1.897);
 TH1D *h_48Mn = new TH1D("h48Mn", "h48Mn",1000,1.91,1.930);
                                                            
 TH1D *h_48Fe = new TH1D("h48Fe", "h48Fe",1000,1.8355,1.8555);
 TH1D *h_49Fe = new TH1D("h49Fe", "h49Fe",1000,1.875,1.895);
 TH1D *h_50Fe = new TH1D("h50Fe", "h50Fe",1000,1.91,1.930);

 TH2D *h_zaq_cor = new TH2D("zaq_col", "zaq_col",500,1.7,2.3,500,18,30);

   Int_t Nevt_valid = evt_valid.size();

//   Double_t aq_cor_br;
//   tree->Branch("Aq_cor",&aq_cor_br,"Aq_cor/D");

  for (Int_t iData = 0; iData < Nevt_valid; iData++){

    int itmp = evt_valid[iData];
    tree->GetEntry(itmp);

     h_aq_cor->Fill(Aq_cor[iData]);
     h_aq_cor_wr->Fill(Aq_cor[iData]);

     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
 
      h_zaq_cor->Fill(Aq_cor[iData],z_tmpt);
//	  aq_cor_br = Aq_cor[iData];
//	  tree->Fill();

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_38Ca->Fill(Aq_cor[iData]);
      h_39Ca->Fill(Aq_cor[iData]);
//      h_40Ca->Fill(Aq_cor[iData]); 
      h_41Ca->Fill(Aq_cor[iData]);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc->Fill(Aq_cor[iData]);
      h_41Sc->Fill(Aq_cor[iData]);
      h_43Sc->Fill(Aq_cor[iData]);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti->Fill(Aq_cor[iData]);
      h_41Ti->Fill(Aq_cor[iData]);
//      h_43Ti->Fill(Aq_cor[iData]);
      h_47Ti->Fill(Aq_cor[iData]);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V->Fill(Aq_cor[iData]);
      h_44V->Fill(Aq_cor[iData]);
//      h_45V->Fill(Aq_cor[iData]);
      h_47V->Fill(Aq_cor[iData]);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr->Fill(Aq_cor[iData]);
      h_45Cr->Fill(Aq_cor[iData]);
      h_46Cr->Fill(Aq_cor[iData]);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn->Fill(Aq_cor[iData]);
      h_47Mn->Fill(Aq_cor[iData]);
      h_48Mn->Fill(Aq_cor[iData]);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe->Fill(Aq_cor[iData]);
      h_49Fe->Fill(Aq_cor[iData]);
      h_50Fe->Fill(Aq_cor[iData]);

  }else {
	  continue;
  }
}


//// Draw original histogram

 TH1D *h_aq_cor_org = new TH1D("aq_cor_org", "aq_cor_org",500,1.7,2.3);

 TH1D *h_38Ca_org = new TH1D("h38Ca_org", "h38Ca_org",1000,1.89,1.91);
 TH1D *h_39Ca_org = new TH1D("h39Ca_org", "h39Ca_org",1000,1.940,1.960);
// TH1D *h_40Ca_org = new TH1D("h40Ca_org", "h40Ca_org",1000,1.990,2.01);
 TH1D *h_41Ca_org = new TH1D("h41Ca_org", "h41Ca_org",1000,2.040,2.060);
                                                                        
 TH1D *h_40Sc_org = new TH1D("h40Sc_org", "h40Sc_org",1000,1.900,1.92);
 TH1D *h_41Sc_org = new TH1D("h41Sc_org", "h41Sc_org",1000,1.945,1.965);
 TH1D *h_43Sc_org = new TH1D("h43Sc_org", "h43Sc_org",1000,2.04,2.060);
                                                                        
 TH1D *h_40Ti_org = new TH1D("h40Ti_org", "h40Ti_org",1000,1.81,1.83);
 TH1D *h_41Ti_org = new TH1D("h41Ti_org", "h41Ti_org",1000,1.86,1.88);
// TH1D *h_43Ti_org = new TH1D("h43Ti_org", "h43Ti_org",1000,1.940,1.960);
 TH1D *h_47Ti_org = new TH1D("h47Ti_org", "h47Ti_org",1000,2.125,2.145);
                                                                        
 TH1D *h_43V_org = new TH1D("h43V_org", "h43V_org",51000,1.86,1.880);
 TH1D *h_44V_org = new TH1D("h44V_org", "h44V_org",51000,1.90,1.92);
// TH1D *h_45V_org = new TH1D("h45V_org", "h45V_org",51000,1.945,1.965);
 TH1D *h_47V_org = new TH1D("h47V_org", "h47V_org",51000,2.01,2.21);
                                                                        
 TH1D *h_44Cr_org = new TH1D("h44Cr_org", "h44Cr_org",1000,1.83,1.85);
 TH1D *h_45Cr_org = new TH1D("h45Cr_org", "h45Cr_org",1000,1.865,1.885);
 TH1D *h_46Cr_org = new TH1D("h46Cr_org", "h46Cr_org",1000,1.90,1.925);
                                                                        
 TH1D *h_46Mn_org = new TH1D("h46Mn_org", "h46Mn_org",1000,1.83,1.85);
 TH1D *h_47Mn_org = new TH1D("h47Mn_org", "h47Mn_org",1000,1.87,1.897);
 TH1D *h_48Mn_org = new TH1D("h48Mn_org", "h48Mn_org",1000,1.91,1.930);
                                                                        
 TH1D *h_48Fe_org = new TH1D("h48Fe_org", "h48Fe_org",1000,1.835,1.855);
 TH1D *h_49Fe_org = new TH1D("h49Fe_org", "h49Fe_org",1000,1.87,1.89);
 TH1D *h_50Fe_org = new TH1D("h50Fe_org", "h50Fe_org",1000,1.91,1.930);

 TH2D *h_zaq_org = new TH2D("zaq_org", "zaq_org",500,1.7,2.3,500,18,30);

  for (Int_t iData = 0; iData < nData; iData++){
     tree->GetEntry(iData);
     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     art::TMassData *mass_corst1_tmpt = (art::TMassData*) array_mass_corst1->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t aq_tmpt = mass_corst1_tmpt->GetAq();
 
     h_aq_cor_org->Fill(aq_tmpt);
     h_zaq_org->Fill(aq_tmpt,z_tmpt);

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_38Ca_org->Fill(aq_tmpt);
      h_39Ca_org->Fill(aq_tmpt);
//      h_40Ca_org->Fill(aq_tmpt); 
      h_41Ca_org->Fill(aq_tmpt);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc_org->Fill(aq_tmpt);
      h_41Sc_org->Fill(aq_tmpt);
      h_43Sc_org->Fill(aq_tmpt);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti_org->Fill(aq_tmpt);
      h_41Ti_org->Fill(aq_tmpt);
//      h_43Ti_org->Fill(aq_tmpt);
      h_47Ti_org->Fill(aq_tmpt);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V_org->Fill(aq_tmpt);
      h_44V_org->Fill(aq_tmpt);
//      h_45V_org->Fill(aq_tmpt);
      h_47V_org->Fill(aq_tmpt);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr_org->Fill(aq_tmpt);
      h_45Cr_org->Fill(aq_tmpt);
      h_46Cr_org->Fill(aq_tmpt);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn_org->Fill(aq_tmpt);
      h_47Mn_org->Fill(aq_tmpt);
      h_48Mn_org->Fill(aq_tmpt);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe_org->Fill(aq_tmpt);
      h_49Fe_org->Fill(aq_tmpt);
      h_50Fe_org->Fill(aq_tmpt);

  }
 }


//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref1_4step.hist.root","recreate");
//   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref2_4step.hist.root","recreate");
   TFile *ofile = new TFile("output/mass/mass_calib_svd_4th_eachstrip_st1_ref2_4.5step.hist.root","recreate");
   
 h_aq_sol->Write();
 h_38Ca_sol->Write();   
 h_39Ca_sol->Write();   
// h_40Ca_sol->Write();
 h_41Ca_sol->Write();
 h_40Sc_sol->Write();
 h_41Sc_sol->Write();
 h_43Sc_sol->Write();
 h_40Ti_sol->Write();
 h_41Ti_sol->Write();
// h_43Ti_sol->Write();
 h_47Ti_sol->Write();
 h_43V_sol->Write(); 
 h_44V_sol->Write(); 
// h_45V_sol->Write();
 h_47V_sol->Write();
 h_44Cr_sol->Write();   
 h_45Cr_sol->Write();
 h_46Cr_sol->Write();
 h_46Mn_sol->Write();
 h_47Mn_sol->Write();
 h_48Mn_sol->Write();
 h_48Fe_sol->Write();
 h_49Fe_sol->Write();
 h_50Fe_sol->Write();

 h_aq_cor->Write(); 
 h_aq_cor_wr->Write();
 h_38Ca->Write(); 
 h_39Ca->Write(); 
// h_40Ca->Write(); 
 h_41Ca->Write(); 
 h_40Sc->Write(); 
 h_41Sc->Write(); 
 h_43Sc->Write(); 
 h_40Ti->Write(); 
 h_41Ti->Write(); 
// h_43Ti->Write(); 
 h_47Ti->Write(); 
 h_43V->Write(); 
 h_44V->Write(); 
// h_45V->Write(); 
 h_47V->Write(); 
 h_44Cr->Write(); 
 h_45Cr->Write(); 
 h_46Cr->Write(); 
 h_46Mn->Write(); 
 h_47Mn->Write(); 
 h_48Mn->Write(); 
 h_48Fe->Write(); 
 h_49Fe->Write(); 
 h_50Fe->Write(); 
 h_zaq_cor->Write();

 h_aq_cor_org->Write();
 h_38Ca_org->Write();  
 h_39Ca_org->Write();  
// h_40Ca_org->Write();
 h_41Ca_org->Write();
 h_40Sc_org->Write();
 h_41Sc_org->Write();
 h_43Sc_org->Write();
 h_40Ti_org->Write();
 h_41Ti_org->Write();
// h_43Ti_org->Write();
 h_47Ti_org->Write();
 h_43V_org->Write();
 h_44V_org->Write();
// h_45V_org->Write();
 h_47V_org->Write();
 h_44Cr_org->Write();
 h_45Cr_org->Write();
 h_46Cr_org->Write();
 h_46Mn_org->Write();
 h_47Mn_org->Write();
 h_48Mn_org->Write();
 h_48Fe_org->Write();
 h_49Fe_org->Write();
 h_50Fe_org->Write();
 h_zaq_org->Write();

 ofile->Close(); 
 

}
