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

void t_calib_mlp_st1(){

 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.all.170272.root");
 if(!file){
	 printf("Cannot open the file!\n");
	 return;
 }
//  const Int_t Nrun = 250;  //the number of runs
  const Int_t Nrun = 2500;  //the number of runs
  const Int_t Nref =  21;  // the number of species for reference
  const Int_t Nevt =  Nref * Nrun;  // the number of events
  const Int_t Nprm =  168;  //the number of parameters 3rd order

 TClonesArray *array_mass = NULL;
 TClonesArray *array_mass_st1 = NULL;
 TClonesArray *array_tracku = NULL;
 TClonesArray *array_s0 = NULL;
 TTree *tree = (TTree*) gDirectory->Get("tree");

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("mass_st1",&array_mass_st1);
 tree->SetBranchAddress("f3",&array_tracku);
 tree->SetBranchAddress("sr0_xcw",&array_s0);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("mass_st1",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("sr0_xcw",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up;

 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_try.dat");
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


 TMatrixD value(Nevt,8); // output the fitting value 
 TNtuple* anntree = new TNtuple("anntree","anntree","c0:c1:c2:c3:c4:c5:f");



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
      Int_t hit_mass_st1 = array_mass_st1->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_mass_st1 > 0 && hit_tracku > 0 && hit_s0 >0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsProcessed();

    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok)
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
	 art::TMassData *mass_st1 = (art::TMassData*) array_mass_st1->UncheckedAt(0);
	 art::TMWDCTrackingResult *tracku = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
	 art::TSRPPACPlaneData *sr0 = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);

     Double_t z_select = mass->GetZ();
     Double_t aq_select = mass_st1->GetAq();
 
     Double_t ti = mass_st1->GetTof();
     Double_t x3i = tracku->GetX();
     Double_t a3i = tracku->GetA() * 1000.;
     Double_t y3i = tracku->GetY();
     Double_t b3i = tracku->GetB() * 1000.;
     Double_t x0i = sr0->GetPosition();
// unit orientation
     Double_t t = (ti - 2042.) * 0.25;  
     Double_t x3 = x3i * 0.1; 
     Double_t a3 = a3i * 0.1;
     Double_t y3 = y3i * 0.1;
     Double_t b3 = b3i * 0.1;
     Double_t x0 = x0i * 0.1; 

     Double_t c0 = t;
     Double_t c1 = x3;
     Double_t c2 = a3;
     Double_t c3 = y3;
     Double_t c4 = b3;
     Double_t c5 = x0;
	 Double_t f = Ref_m[iref];

     anntree->Fill(c0,c1,c2,c3,c4,c5,f);

     value(ievt,0) = z_select;
     value(ievt,1) = aq_select;
     value(ievt,2) = t;
     value(ievt,3) = x3;
     value(ievt,4) = a3;
     value(ievt,5) = y3;
     value(ievt,6) = b3;
     value(ievt,7) = x0;

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


 ofstream foutselect("/home/sh13/art_analysis/user/hanai/prm/mass/value_selected_mlp_eachstripst1.dat");
 if (foutselect.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 return;
  }

for(int n = 0; n < Nevt; n++){
	for(int m = 0; m < 8; m++){
		foutselect << value(n,m) << "  "  << " | ";
	}
	foutselect << "\n";
}

	foutselect.close();

//// Set ANN

   TMultiLayerPerceptron* mlp = new TMultiLayerPerceptron("c0,c1,c2,c3,c4,c5:12:10:f", anntree,  "Entry$%2","(Entry$%2)==0");
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

 TH1D *h_aq_sol = new TH1D("aq_sol", "aq_sol",500,1.7,2.3);

 TH1D *h_39Ca_sol = new TH1D("h39Ca_sol", "h39Ca_sol",500,1.940,1.980);
 TH1D *h_40Ca_sol = new TH1D("h40Ca_sol", "h40Ca_sol",500,1.990,2.02);
 TH1D *h_41Ca_sol = new TH1D("h41Ca_sol", "h41Ca_sol",500,2.040,2.0650);
                                    
 TH1D *h_40Sc_sol = new TH1D("h40Sc_sol", "h40Sc_sol",500,1.900,1.925);
 TH1D *h_41Sc_sol = new TH1D("h41Sc_sol", "h41Sc_sol",500,1.940,1.970);
 TH1D *h_43Sc_sol = new TH1D("h43Sc_sol", "h43Sc_sol",500,2.035,2.060);
                                
 TH1D *h_40Ti_sol = new TH1D("h40Ti_sol", "h40Ti_sol",500,1.805,1.826);
 TH1D *h_41Ti_sol = new TH1D("h41Ti_sol", "h41Ti_sol",500,1.855,1.885);
 TH1D *h_43Ti_sol = new TH1D("h43Ti_sol", "h43Ti_sol",500,1.940,1.980);
                                         
 TH1D *h_43V_sol  = new TH1D("h43V_sol ", "h43V_sol ",500,1.865,1.890);
 TH1D *h_44V_sol  = new TH1D("h44V_sol ", "h44V_sol ",500,1.90,1.94);
 TH1D *h_45V_sol  = new TH1D("h45V_sol ", "h45V_sol ",500,1.941,1.983);
                                    
 TH1D *h_44Cr_sol = new TH1D("h44Cr_sol", "h44Cr_sol",500,1.825,1.858);
 TH1D *h_45Cr_sol = new TH1D("h45Cr_sol", "h45Cr_sol",500,1.855,1.90);
 TH1D *h_46Cr_sol = new TH1D("h46Cr_sol", "h46Cr_sol",500,1.90,1.940);
                                    
 TH1D *h_46Mn_sol = new TH1D("h46Mn_sol", "h46Mn_sol",500,1.832,1.855);
 TH1D *h_47Mn_sol = new TH1D("h47Mn_sol", "h47Mn_sol",500,1.860,1.897);
 TH1D *h_49Mn_sol = new TH1D("h49Mn_sol", "h49Mn_sol",500,1.90,1.940);
                                    
 TH1D *h_48Fe_sol = new TH1D("h48Fe_sol", "h48Fe_sol",500,1.8355,1.855);
 TH1D *h_49Fe_sol = new TH1D("h49Fe_sol", "h49Fe_sol",500,1.865,1.897);
 TH1D *h_50Fe_sol = new TH1D("h50Fe_sol", "h50Fe_sol",500,1.90,1.940);


 for (int isol = 0; isol < Nevt; isol++){
  
      Double_t c0_tmp = value(isol,2);
      Double_t c1_tmp = value(isol,3);
      Double_t c2_tmp = value(isol,4);
      Double_t c3_tmp = value(isol,5);
      Double_t c4_tmp = value(isol,6);
      Double_t c5_tmp = value(isol,7);

     Double_t mlp_prm[6];
     mlp_prm[0] = c0_tmp;
     mlp_prm[1] = c1_tmp;
     mlp_prm[2] = c2_tmp;
     mlp_prm[3] = c3_tmp;
     mlp_prm[4] = c4_tmp;
     mlp_prm[5] = c5_tmp;

     Double_t mass_calib_sol = mlp->Evaluate(0,mlp_prm);

	 
	if(0 <= isol && isol  < 2500){
	 h_39Ca_sol->Fill(mass_calib_sol);
 } else if(2500 <= isol && isol  < 5000){
	 h_40Ca_sol->Fill(mass_calib_sol);
 } else if(5000 <= isol && isol  < 7500){
	 h_41Ca_sol->Fill(mass_calib_sol);
 } else if(7500 <= isol && isol  < 10000){
	 h_40Sc_sol->Fill(mass_calib_sol);
 } else if(10000 <= isol && isol  < 12500){
	 h_41Sc_sol->Fill(mass_calib_sol);
 } else if(12500 <= isol && isol  < 15000){
	 h_43Sc_sol->Fill(mass_calib_sol);
 } else if(15000 <= isol && isol  < 17500){
	 h_40Ti_sol->Fill(mass_calib_sol);
 } else if(17500 <= isol && isol  < 20000){
	 h_41Ti_sol->Fill(mass_calib_sol);
 } else if(20000 <= isol && isol  < 22500){
	 h_43Ti_sol->Fill(mass_calib_sol);
 } else if(22500 <= isol && isol  < 25000){
	 h_43V_sol->Fill(mass_calib_sol);
 } else if(25000 <= isol && isol  < 27500){
	 h_44V_sol->Fill(mass_calib_sol);
 } else if(27500 <= isol && isol  < 30000){
	 h_45V_sol->Fill(mass_calib_sol);
 } else if(30000 <= isol && isol  < 32500){
	 h_44Cr_sol->Fill(mass_calib_sol);
 } else if(32500 <= isol && isol  < 35000){
	 h_45Cr_sol->Fill(mass_calib_sol);
 } else if(35000 <= isol && isol  < 37500){
	 h_46Cr_sol->Fill(mass_calib_sol);
 } else if(37500 <= isol && isol  < 40000){
	 h_46Mn_sol->Fill(mass_calib_sol);
 } else if(40000 <= isol && isol  < 42500){
	 h_47Mn_sol->Fill(mass_calib_sol);
 } else if(42500 <= isol && isol  < 45000){
	 h_49Mn_sol->Fill(mass_calib_sol);
 } else if(45000 <= isol && isol  < 47500){
	 h_48Fe_sol->Fill(mass_calib_sol);
 } else if(47500 <= isol && isol  < 50000){
	 h_49Fe_sol->Fill(mass_calib_sol);
 } else if(50000 <= isol && isol  < 52500){
	 h_50Fe_sol->Fill(mass_calib_sol);
 }
}


//// Check results for all events

 TH1D *h_aq_cor = new TH1D("aq_cor", "aq_cor",500,1.7,2.3);
 TH1D *h_aq_cor_wr = new TH1D("aq_cor_wr", "aq_cor_wr",500,-10,10);

 TH1D *h_39Ca_cor = new TH1D("h39Ca_cor", "h39Ca_cor",500,1.940,1.980);
 TH1D *h_40Ca_cor = new TH1D("h40Ca_cor", "h40Ca_cor",500,1.990,2.02);
 TH1D *h_41Ca_cor = new TH1D("h41Ca_cor", "h41Ca_cor",500,2.040,2.0650);
                            
 TH1D *h_40Sc_cor = new TH1D("h40Sc_cor", "h40Sc_cor",500,1.900,1.925);
 TH1D *h_41Sc_cor = new TH1D("h41Sc_cor", "h41Sc_cor",500,1.940,1.970);
 TH1D *h_43Sc_cor = new TH1D("h43Sc_cor", "h43Sc_cor",500,2.035,2.060);
                                            
 TH1D *h_40Ti_cor = new TH1D("h40Ti_cor", "h40Ti_cor",500,1.805,1.826);
 TH1D *h_41Ti_cor = new TH1D("h41Ti_cor", "h41Ti_cor",500,1.855,1.885);
 TH1D *h_43Ti_cor = new TH1D("h43Ti_cor", "h43Ti_cor",500,1.940,1.980);
                                             
 TH1D *h_43V_cor = new TH1D("h43V_cor", "h43V_cor",500,1.865,1.890);
 TH1D *h_44V_cor = new TH1D("h44V_cor", "h44V_cor",500,1.90,1.94);
 TH1D *h_45V_cor = new TH1D("h45V_cor", "h45V_cor",500,1.941,1.983);
                            
 TH1D *h_44Cr_cor = new TH1D("h44Cr_cor", "h44Cr_cor",500,1.825,1.858);
 TH1D *h_45Cr_cor = new TH1D("h45Cr_cor", "h45Cr_cor",500,1.855,1.90);
 TH1D *h_46Cr_cor = new TH1D("h46Cr_cor", "h46Cr_cor",500,1.90,1.940);
                            
 TH1D *h_46Mn_cor = new TH1D("h46Mn_cor", "h46Mn_cor",500,1.832,1.855);
 TH1D *h_47Mn_cor = new TH1D("h47Mn_cor", "h47Mn_cor",500,1.860,1.897);
 TH1D *h_49Mn_cor = new TH1D("h49Mn_cor", "h49Mn_cor",500,1.90,1.940);
                            
 TH1D *h_48Fe_cor = new TH1D("h48Fe_cor", "h48Fe_cor",500,1.8355,1.855);
 TH1D *h_49Fe_cor = new TH1D("h49Fe_cor", "h49Fe_cor",500,1.865,1.897);
 TH1D *h_50Fe_cor = new TH1D("h50Fe_cor", "h50Fe_cor",500,1.90,1.940);


  for(int iData = 0; iData < nData; iData++){
	  tree->GetEntry(iData);

      Int_t hit_mass = array_mass->GetEntriesFast();
      Int_t hit_tracku = array_tracku->GetEntriesFast();
      Int_t hit_s0 = array_s0->GetEntriesFast();

     if ( hit_mass > 0 && hit_tracku > 0 && hit_s0 >0){

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_tmp->GetAq();
  
     art::TMWDCTrackingResult *tracku_tmp = (art::TMWDCTrackingResult*) array_tracku->UncheckedAt(0);
     Bool_t tracku_ok = tracku_tmp->IsProcessed();

	 art::TSRPPACPlaneData *sr0_tmp = (art::TSRPPACPlaneData*) array_s0->UncheckedAt(0);
  
     Double_t ti_tmp = mass_tmp->GetTof();
     Double_t x3i_tmp = tracku_tmp->GetX();
     Double_t a3i_tmp = tracku_tmp->GetA() * 1000.;
     Double_t y3i_tmp = tracku_tmp->GetY();
     Double_t b3i_tmp = tracku_tmp->GetB() * 1000.;
     Double_t x0i_tmp = sr0_tmp->GetPosition();
// unit orientation
     Double_t t_tmp = (ti_tmp - 2042.) * 0.25;  
     Double_t x3_tmp = x3i_tmp * 0.1; 
     Double_t a3_tmp = a3i_tmp * 0.1;
     Double_t y3_tmp = y3i_tmp * 0.1;
     Double_t b3_tmp = b3i_tmp * 0.1;
     Double_t x0_tmp = x0i_tmp * 0.1; 

     Double_t c0_tmp = t_tmp;
     Double_t c1_tmp = x3_tmp;
     Double_t c2_tmp = a3_tmp;
     Double_t c3_tmp = y3_tmp;
     Double_t c4_tmp = b3_tmp;
     Double_t c5_tmp = x0_tmp;

     Double_t mlp_prm[6];
     mlp_prm[0] = c0_tmp;
     mlp_prm[1] = c1_tmp;
     mlp_prm[2] = c2_tmp;
     mlp_prm[3] = c3_tmp;
     mlp_prm[4] = c4_tmp;
     mlp_prm[5] = c5_tmp;

     Double_t mass_calib = mlp->Evaluate(0,mlp_prm);

for(int iref = 0; iref < Nref; iref++){
    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref] && tracku_ok)
    {
      switch(iref){
		  case 0:
	       h_39Ca_cor->Fill(mass_calib);
		   continue;
		  case 1:
	       h_40Ca_cor->Fill(mass_calib);
		   continue;
		  case 2:
	       h_41Ca_cor->Fill(mass_calib);
		   continue;
		  case 3:
	       h_40Sc_cor->Fill(mass_calib);
		   continue;
		  case 4:
	       h_41Sc_cor->Fill(mass_calib);
		   continue;
		  case 5:
	       h_43Sc_cor->Fill(mass_calib);
		   continue;
		  case 6:
	       h_40Ti_cor->Fill(mass_calib);
		   continue;
		  case 7:
	       h_41Ti_cor->Fill(mass_calib);
		   continue;
		  case 8:
	       h_43Ti_cor->Fill(mass_calib);
		   continue;
		  case 9:
	       h_43V_cor->Fill(mass_calib);
		   continue;
		  case 10:
	       h_44V_cor->Fill(mass_calib);
		   continue;
		  case 11:
	       h_45V_cor->Fill(mass_calib);
		   continue;
		  case 12:
	       h_44Cr_cor->Fill(mass_calib);
		   continue;
		  case 13:
	       h_45Cr_cor->Fill(mass_calib);
		   continue;
		  case 14:
	       h_46Cr_cor->Fill(mass_calib);
		   continue;
		  case 15:
	       h_46Mn_cor->Fill(mass_calib);
		   continue;
		  case 16:
	       h_47Mn_cor->Fill(mass_calib);
		   continue;
		  case 17:
	       h_49Mn_cor->Fill(mass_calib);
		   continue;
		  case 18:
	       h_48Fe_cor->Fill(mass_calib);
		   continue;
		  case 19:
	       h_49Fe_cor->Fill(mass_calib);
		   continue;
		  case 20:
	       h_50Fe_cor->Fill(mass_calib);
		   continue;
       }
	}else{
		continue;
}	}
  }else{
		continue;
	}

}

//// Draw original histogram

 TH1D *h_aq_cor_org = new TH1D("aq_cor_org", "aq_cor_org",500,1.7,2.3);

 TH1D *h_39Ca_org = new TH1D("h39Ca_org", "h39Ca_org",500,1.940,1.980);
 TH1D *h_40Ca_org = new TH1D("h40Ca_org", "h40Ca_org",500,1.990,2.02);
 TH1D *h_41Ca_org = new TH1D("h41Ca_org", "h41Ca_org",500,2.040,2.0650);
                   
 TH1D *h_40Sc_org = new TH1D("h40Sc_org", "h40Sc_org",500,1.900,1.925);
 TH1D *h_41Sc_org = new TH1D("h41Sc_org", "h41Sc_org",500,1.940,1.970);
 TH1D *h_43Sc_org = new TH1D("h43Sc_org", "h43Sc_org",500,2.035,2.060);
                        
 TH1D *h_40Ti_org = new TH1D("h40Ti_org", "h40Ti_org",500,1.805,1.826);
 TH1D *h_41Ti_org = new TH1D("h41Ti_org", "h41Ti_org",500,1.855,1.885);
 TH1D *h_43Ti_org = new TH1D("h43Ti_org", "h43Ti_org",500,1.940,1.980);
                                        
 TH1D *h_43V_org = new TH1D("h43V_org ", "h43V_org ",500,1.865,1.890);
 TH1D *h_44V_org = new TH1D("h44V_org ", "h44V_org ",500,1.90,1.94);
 TH1D *h_45V_org = new TH1D("h45V_org ", "h45V_org ",500,1.941,1.983);
                                    
 TH1D *h_44Cr_org = new TH1D("h44Cr_org", "h44Cr_org",500,1.825,1.858);
 TH1D *h_45Cr_org = new TH1D("h45Cr_org", "h45Cr_org",500,1.855,1.90);
 TH1D *h_46Cr_org = new TH1D("h46Cr_org", "h46Cr_org",500,1.90,1.940);
                   
 TH1D *h_46Mn_org = new TH1D("h46Mn_org", "h46Mn_org",500,1.832,1.855);
 TH1D *h_47Mn_org = new TH1D("h47Mn_org", "h47Mn_org",500,1.860,1.897);
 TH1D *h_49Mn_org = new TH1D("h49Mn_org", "h49Mn_org",500,1.90,1.940);
                
 TH1D *h_48Fe_org = new TH1D("h48Fe_org", "h48Fe_org",500,1.8355,1.855);
 TH1D *h_49Fe_org = new TH1D("h49Fe_org", "h49Fe_org",500,1.865,1.897);
 TH1D *h_50Fe_org = new TH1D("h50Fe_org", "h50Fe_org",500,1.90,1.940);

 TH2D *h_zaq_org = new TH2D("zaq_org", "zaq_org",500,1.7,2.3,500,18,30);

  for (Int_t iData = 0; iData < nData; iData++){
     tree->GetEntry(iData);
     art::TMassData *mass_tmpt = (art::TMassData*) array_mass->UncheckedAt(0);
     Double_t z_tmpt = mass_tmpt->GetZ();
     Double_t aq_tmpt = mass_tmpt->GetAq();
 

	 if(Z_low[0] < z_tmpt && z_tmpt < Z_up[0]){ 

      h_39Ca_org->Fill(aq_tmpt);
      h_40Ca_org->Fill(aq_tmpt); 
      h_41Ca_org->Fill(aq_tmpt);

 }else if(Z_low[3] < z_tmpt && z_tmpt < Z_up[3]){

      h_40Sc_org->Fill(aq_tmpt);
      h_41Sc_org->Fill(aq_tmpt);
      h_43Sc_org->Fill(aq_tmpt);
 
 }else if(Z_low[6] < z_tmpt && z_tmpt < Z_up[6]){

      h_40Ti_org->Fill(aq_tmpt);
      h_41Ti_org->Fill(aq_tmpt);
      h_43Ti_org->Fill(aq_tmpt);

 }else if(Z_low[9] < z_tmpt && z_tmpt < Z_up[9]){

      h_43V_org->Fill(aq_tmpt);
      h_44V_org->Fill(aq_tmpt);
      h_45V_org->Fill(aq_tmpt);

 }else if(Z_low[12] < z_tmpt && z_tmpt < Z_up[12]){

      h_44Cr_org->Fill(aq_tmpt);
      h_45Cr_org->Fill(aq_tmpt);
      h_46Cr_org->Fill(aq_tmpt);

 }else if(Z_low[15] < z_tmpt && z_tmpt < Z_up[15]){

      h_46Mn_org->Fill(aq_tmpt);
      h_47Mn_org->Fill(aq_tmpt);
      h_49Mn_org->Fill(aq_tmpt);

 }else if(Z_low[18] < z_tmpt && z_tmpt < Z_up[18]){

      h_48Fe_org->Fill(aq_tmpt);
      h_49Fe_org->Fill(aq_tmpt);
      h_50Fe_org->Fill(aq_tmpt);

  }
 }


 TFile *ofile = new TFile("output/mass/mass_calib_mlp_eachstrip_st1.hist.root","recreate");

 h_aq_sol->Write();
 h_39Ca_sol->Write();   
 h_40Ca_sol->Write();
 h_41Ca_sol->Write();
 h_40Sc_sol->Write();
 h_41Sc_sol->Write();
 h_43Sc_sol->Write();
 h_40Ti_sol->Write();
 h_41Ti_sol->Write();
 h_43Ti_sol->Write();
 h_43V_sol->Write(); 
 h_44V_sol->Write(); 
 h_45V_sol->Write();
 h_44Cr_sol->Write();   
 h_45Cr_sol->Write();
 h_46Cr_sol->Write();
 h_46Mn_sol->Write();
 h_47Mn_sol->Write();
 h_49Mn_sol->Write();
 h_48Fe_sol->Write();
 h_49Fe_sol->Write();
 h_50Fe_sol->Write();

 h_aq_cor->Write(); 
 h_aq_cor_wr->Write();
 h_39Ca_cor->Write(); 
 h_40Ca_cor->Write(); 
 h_41Ca_cor->Write(); 
 h_40Sc_cor->Write(); 
 h_41Sc_cor->Write(); 
 h_43Sc_cor->Write(); 
 h_40Ti_cor->Write(); 
 h_41Ti_cor->Write(); 
 h_43Ti_cor->Write(); 
 h_43V_cor->Write(); 
 h_44V_cor->Write(); 
 h_45V_cor->Write(); 
 h_44Cr_cor->Write(); 
 h_45Cr_cor->Write(); 
 h_46Cr_cor->Write(); 
 h_46Mn_cor->Write(); 
 h_47Mn_cor->Write(); 
 h_49Mn_cor->Write(); 
 h_48Fe_cor->Write(); 
 h_49Fe_cor->Write(); 
 h_50Fe_cor->Write(); 

 h_aq_cor_org->Write();
 h_39Ca_org->Write();  
 h_40Ca_org->Write();
 h_41Ca_org->Write();
 h_40Sc_org->Write();
 h_41Sc_org->Write();
 h_43Sc_org->Write();
 h_40Ti_org->Write();
 h_41Ti_org->Write();
 h_43Ti_org->Write();
 h_43V_org->Write();
 h_44V_org->Write();
 h_45V_org->Write();
 h_44Cr_org->Write();
 h_45Cr_org->Write();
 h_46Cr_org->Write();
 h_46Mn_org->Write();
 h_47Mn_org->Write();
 h_49Mn_org->Write();
 h_48Fe_org->Write();
 h_49Fe_org->Write();
 h_50Fe_org->Write();
 h_zaq_org->Write();

 ofile->Close(); 
 

}
