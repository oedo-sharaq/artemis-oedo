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

void tofslew(){

  TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm_2step_ref4.eventstore.170272.all.root"); // Add file. Basically mass calibration file.

  const Int_t Nref =  21;  // the number of species for reference

 TClonesArray *array_mass = NULL;
 TClonesArray *array_dia_tof32stm = NULL;
 TClonesArray *array_mass_corstm = NULL;
 TClonesArray *array_dia3pad = NULL;
 TClonesArray *array_dias2pad = NULL;
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("mass",&array_mass);
 tree->SetBranchAddress("dia_tof32stm",&array_dia_tof32stm);
 tree->SetBranchAddress("mass_corstm_BLD_2nd",&array_mass_corstm);
 tree->SetBranchAddress("dia3pad",&array_dia3pad);
 tree->SetBranchAddress("dias2pad",&array_dias2pad);
 tree->SetBranchAddress("eventheader",&array_eventheader);
 tree->SetBranchStatus("*",0);
 tree->SetBranchStatus("mass",1);
 tree->SetBranchStatus("dia_tof32stm",1);
 tree->SetBranchStatus("mass_corstm_BLD_2nd",1);
 tree->SetBranchStatus("dia3pad",1);
 tree->SetBranchStatus("dias2pad",1);
 tree->SetBranchStatus("eventheader",1);

 Double_t Ref_m_tmp, Z_low_tmp, Z_up_tmp, Aq_low_tmp, Aq_up_tmp, TofOff_tmp;
 vector<Double_t> Ref_m, Z_low, Z_up, Aq_low, Aq_up, TofOff;

 ifstream fin("/home/sh13/art_analysis/user/hanai/prm/mass/input_tofslew_2step_stm_ref4.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << " " << "is not found." << endl << endl;
	 return;
  }

  while(!fin.eof()){
	    fin >> Ref_m_tmp >> Z_low_tmp >> Z_up_tmp >> Aq_low_tmp >> Aq_up_tmp >> TofOff_tmp;
		Ref_m.push_back(Ref_m_tmp);
		Z_low.push_back(Z_low_tmp);
		Z_up.push_back(Z_up_tmp);
		Aq_low.push_back(Aq_low_tmp);
		Aq_up.push_back(Aq_up_tmp);
		TofOff.push_back(TofOff_tmp);
		}
 fin.close();

 cout << "Input was finished" << endl;


 TH2D *tofq3 = new TH2D("tofq3","tofq3",300,-20,20,300,0,700);
 TH2D *tofq2 = new TH2D("tofq2","tofq2",300,-20,20,300,0,700);

 TH1D *h_38Ca_tof = new TH1D("h38Ca_tof", "h38Ca_tof",300,1900,2120);
 TH1D *h_39Ca_tof = new TH1D("h39Ca_tof", "h39Ca_tof",300,1900,2120);
 TH1D *h_41Ca_tof = new TH1D("h41Ca_tof", "h41Ca_tof",300,1900,2120);
                                                                       
 TH1D *h_40Sc_tof = new TH1D("h40Sc_tof", "h40Sc_tof",300,1900,2120);
 TH1D *h_41Sc_tof = new TH1D("h41Sc_tof", "h41Sc_tof",300,1900,2120);
 TH1D *h_43Sc_tof = new TH1D("h43Sc_tof", "h43Sc_tof",300,1900,2120);
                                                            
 TH1D *h_40Ti_tof = new TH1D("h40Ti_tof", "h40Ti_tof",300,1900,2120);
 TH1D *h_41Ti_tof = new TH1D("h41Ti_tof", "h41Ti_tof",300,1900,2120);
 TH1D *h_42Ti_tof = new TH1D("h47Ti_tof", "h47Ti_tof",300,1900,2120);
                                                                        
 TH1D *h_43V_tof = new TH1D("h43V_tof", "h43V_tof",300,1900,2120);
 TH1D *h_44V_tof = new TH1D("h44V_tof", "h44V_tof",300,1900,2120);
 TH1D *h_46V_tof = new TH1D("h46V_tof", "h46V_tof",300,1900,2120);
                                                                        
 TH1D *h_44Cr_tof = new TH1D("h44Cr_tof", "h44Cr_tof",300,1900,2120);
 TH1D *h_45Cr_tof = new TH1D("h45Cr_tof", "h45Cr_tof",300,1900,2120);
 TH1D *h_46Cr_tof = new TH1D("h46Cr_tof", "h46Cr_tof",300,1900,2120);
                                                          
 TH1D *h_46Mn_tof = new TH1D("h46Mn_tof", "h46Mn_tof",300,1900,2120);
 TH1D *h_47Mn_tof = new TH1D("h47Mn_tof", "h47Mn_tof",300,1900,2120);
 TH1D *h_48Mn_tof = new TH1D("h48Mn_tof", "h48Mn_tof",300,1900,2120);
                                                       
 TH1D *h_48Fe_tof = new TH1D("h48Fe_tof", "h48Fe_tof",300,1900,2120);
 TH1D *h_49Fe_tof = new TH1D("h49Fe_tof", "h49Fe_tof",300,1900,2120);
 TH1D *h_50Fe_tof = new TH1D("h50Fe_tof", "h50Fe_tof",300,1900,2120);

 int ievt = 0;
 Bool_t HasEvents = true;
 Int_t nData = tree->GetEntries();
 
 cout << "Start looping" << endl;

for (int iref = 0; iref < Nref; iref++){

 cout << "Start sampling Ref" << iref << endl;

  for(int i = 0; i < nData; i++){
	  tree->GetEntry(i);

	 art::TMassData *mass_tmp = (art::TMassData*) array_mass->UncheckedAt(0);
	 art::TMassData *mass_corstm_tmp = (art::TMassData*) array_mass_corstm->UncheckedAt(0);
     Double_t z_tmp = mass_tmp->GetZ();
     Double_t aq_tmp = mass_corstm_tmp->GetAq();
  
    if(Z_low[iref] < z_tmp && z_tmp < Z_up[iref] 
    	 && Aq_low[iref] < aq_tmp && aq_tmp < Aq_up[iref])
    {
  
     Double_t tofoffset = 2030 - TofOff[0] + TofOff[iref];

     art::TDiaData *dia_tof32stm_tmp = (art::TDiaData*) array_dia_tof32stm->UncheckedAt(0);
     art::TTimingChargeData *dia_f3pad_tmp = (art::TTimingChargeData*) array_dia3pad->UncheckedAt(0);
     art::TTimingChargeData *dia_s2pad_tmp = (art::TTimingChargeData*) array_dias2pad->UncheckedAt(0);
     Double_t tof = dia_tof32stm_tmp->GetTiming();
	 Double_t tof_cal = tof - tofoffset;

     Double_t dia3q = dia_f3pad_tmp->GetCharge(); 
     Double_t dias2q = dia_s2pad_tmp->GetCharge(); 

     tofq3->Fill(tof_cal,dia3q);     
     tofq2->Fill(tof_cal,dias2q);     
 

     if(iref == 0){
		 h_38Ca_tof->Fill(tof);
	 }else if(iref == 1){
		 h_39Ca_tof->Fill(tof);
	 }else if(iref == 2){
		 h_41Ca_tof->Fill(tof);
	 }else if(iref == 3){
		 h_40Sc_tof->Fill(tof);
	 }else if(iref == 4){
		 h_41Sc_tof->Fill(tof);
	 }else if(iref == 5){
		 h_43Sc_tof->Fill(tof);
	 }else if(iref == 6){
		 h_40Ti_tof->Fill(tof);
	 }else if(iref == 7){
		 h_41Ti_tof->Fill(tof);
	 }else if(iref == 8){
		 h_42Ti_tof->Fill(tof);
	 }else if(iref == 9){
		 h_43V_tof->Fill(tof);
	 }else if(iref == 10){
		 h_44V_tof->Fill(tof);
	 }else if(iref == 11){
		 h_46V_tof->Fill(tof);
	 }else if(iref == 12){
		 h_44Cr_tof->Fill(tof);
	 }else if(iref == 13){
		 h_45Cr_tof->Fill(tof);
	 }else if(iref == 14){
		 h_46Cr_tof->Fill(tof);
	 }else if(iref == 15){
		 h_46Mn_tof->Fill(tof);
	 }else if(iref == 16){
		 h_47Mn_tof->Fill(tof);
	 }else if(iref == 17){
		 h_48Mn_tof->Fill(tof);
	 }else if(iref == 18){
		 h_48Fe_tof->Fill(tof);
	 }else if(iref == 19){
		 h_49Fe_tof->Fill(tof);
	 }else if(iref == 20){
		 h_50Fe_tof->Fill(tof);
    }


      
    }else{
	  continue;
       }
   }
  }

 
 TFile *ofile = new TFile("output/tofslew_2step_stm_ref4.root","recreate");
 
  tofq3->Write();
  tofq2->Write();

  h_38Ca_tof->Write();  
  h_39Ca_tof->Write();
  h_41Ca_tof->Write();
        
  h_40Sc_tof->Write();
  h_41Sc_tof->Write();
  h_43Sc_tof->Write();
            
  h_40Ti_tof->Write();
  h_41Ti_tof->Write();
  h_42Ti_tof->Write();
            
  h_43V_tof ->Write();
  h_44V_tof ->Write();
  h_46V_tof ->Write();
            
  h_44Cr_tof->Write();
  h_45Cr_tof->Write();
  h_46Cr_tof->Write();
            
  h_46Mn_tof->Write();
  h_47Mn_tof->Write();
  h_48Mn_tof->Write();
            
  h_48Fe_tof->Write();
  h_49Fe_tof->Write();
  h_50Fe_tof->Write();

  ofile->Close();






}
