#ifndef __CINT__
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TFile.h>

#include <TTimingChargeData.h>

#include <fstream>
#include <string>

#endif


void chksrppac_multihit(){

// TFile* file_load = TFile::Open("output/srppac/optics/0923/chksrppac_newprocoptics0923.root");
// TFile* file_load = TFile::Open("output/srppac/calib/1030/chksrppac_newproccalib1030.root");
 TFile* file_load = TFile::Open("output/srppac/calib/1030/chksrppac_newproccalib1030.tval.root");
 TTree *tree = (TTree*) gDirectory->Get("tree");
 
 TClonesArray *array_src = NULL;
 
// tree->SetBranchAddress("src1_x_cal",&array_src);
 tree->SetBranchAddress("sr91_x_cal",&array_src);
 tree->SetBranchStatus("*",0); 
// tree->SetBranchStatus("src1_x_cal",1);
 tree->SetBranchStatus("sr91_x_cal",1);
 
 Int_t nData = tree->GetEntries();
  
 Double_t nEvtthree = 0;
 Double_t nEvttwoN01series = 0;
 Double_t nEvtthreeN01series = 0;
 Double_t nEvtthreeN012series = 0;

 Int_t id0;
 Int_t id1;
 Int_t id2;

vector<Int_t> EntNumberN01serial;
vector<Int_t> EntNumberN012serial;

 cout << "Start " << endl;

for(int i = 0; i != nData; i++){
  tree->GetEntry(i);
  Int_t ent =  array_src->GetEntriesFast();

 if (ent == 2) {
   art::TTimingChargeData *src0 = (art::TTimingChargeData*) array_src->UncheckedAt(0);
   art::TTimingChargeData *src1 = (art::TTimingChargeData*) array_src->UncheckedAt(1);

   id0 = src0->GetID();
   id1 = src1->GetID();
  if(!(TMath::Abs(id0 - id1) < 2)){
	 nEvttwoN01series++;
  }
 }else if(ent > 2){

   nEvtthree++;

   art::TTimingChargeData *src0 = (art::TTimingChargeData*) array_src->UncheckedAt(0);
   art::TTimingChargeData *src1 = (art::TTimingChargeData*) array_src->UncheckedAt(1);
   art::TTimingChargeData *src2 = (art::TTimingChargeData*) array_src->UncheckedAt(2);

   id0 = src0->GetID();
   id1 = src1->GetID();
   id2 = src2->GetID();
  
  if(!(TMath::Abs(id0 - id1) < 2)){
    nEvtthreeN01series++;
    EntNumberN01serial.push_back(i);
  }
 
//  if(!((id1 + id2) == 2*id0)){ 
  if(!( ((id1 + id2) == 2*id0)&&(TMath::Abs(id0 - id1) < 2) )){ 
    nEvtthreeN012series++;
    EntNumberN012serial.push_back(i);
  }

}else{
	continue;
}
}

// ofstream fout1("Chksrppac_multihit_TreeEvent_01Serial.calib1030.dat");
// ofstream fout1("Chksrppac_multihit_TreeEvent_01Serial.calib1030_sr91.dat");
 ofstream fout1("Chksrppac_multihit_TreeEvent_01Serial.calib1030_sr91_tval.dat");
 if (fout1.fail()){
	 cout << "Error; Could not open output file1" << endl;
	 return;
 }
 for(int k = 0; k < nEvtthreeN01series; k++){
	 fout1 << EntNumberN01serial[k] << endl;
 }


// ofstream fout2("Chksrppac_multihit_TreeEvent_012Serial.calib1030.dat");
// ofstream fout2("Chksrppac_multihit_TreeEvent_012Serial.calib1030_sr91.dat");
 ofstream fout2("Chksrppac_multihit_TreeEvent_012Serial.calib1030_sr91_tval.dat");
 if (fout2.fail()){
	 cout << "Error; Could not open output file1" << endl;
	 return;
 }
 for(int k = 0; k < nEvtthreeN012series; k++){
	 fout2 << EntNumberN012serial[k] << endl;
 }


 Double_t  rEvttwoN01series = 100 * (nEvttwoN01series / nData);
 Double_t  rEvtthreeN01series = 100 *  (nEvtthreeN01series / nData);
 Double_t  rEvtthreeN012series = 100 * (nEvtthreeN012series / nData);


  cout << "Total Number of events  " << nData << endl;
  cout << "Number of events 2Hit & ID0ID1 not serial " << nEvttwoN01series << " (" << rEvttwoN01series << " %) "<< endl;
  cout << "Number of events 3+Hits & ID0ID1 not serial " << nEvtthreeN01series << " (" <<  rEvtthreeN01series << " %) " << endl;
  cout << "Number of events 3+Hits & ID0ID1ID2 not serial " << nEvtthreeN012series << " (" << rEvtthreeN012series << " %) "<< endl;
  cout << "See also output file to check the events more detail" << endl;


}

