#include "TDiaStripCalibrationProcessor.h"
#include "TDiaStripData.h"
#include "TMultiHitArray.h"
#include "TConverterBase.h"
#include "TConverterUtil.h"
#include "TParameterArrayLoader.h"

#include <TSystem.h>
#include <TClonesArray.h>
#include <TRunInfo.h>
#include <TDataObject.h>
#include <TEventHeader.h>

#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <TMath.h>
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TVectorD.h>


using art::TDiaStripCalibrationProcessor;
using std::vector;
using namespace std;

ClassImp(art::TDiaStripCalibrationProcessor);

namespace {
   const TString defaultRunHeaderName = "runheader";
}


TDiaStripCalibrationProcessor::TDiaStripCalibrationProcessor()
   : fDiaStripIn1(NULL), fDiaStripIn2(NULL),fStartTimingData(NULL),fDiaStripOut(NULL),
     fHits1(NULL), fHits2(NULL), fRunNumber(NULL)
{
   const IntVec_t defDetIDRange(2,1); // [1,1]

   RegisterInputCollection("InputCollection1","input of 1st side",
			   fInputColName1,TString("diastrip1"),
			   &fDiaStripIn1,"TClonesArray","art::TDiaTimingData");
   RegisterInputCollection("InputCollection2","input of 2nd side",
			   fInputColName2,TString("diastrip2"),
			   &fDiaStripIn2,"TClonesArray","art::TDiaTimingData");
   RegisterInputInfo("RunHeaderName","name of run header",fRunHeaderName,defaultRunHeaderName,
                     &fRunHeader,TList::Class_Name());


   RegisterProcessorParameter("UseTOffset","use timing offset for strips",fUseTOffset,0);
   RegisterProcessorParameter("RunNumber","run number input for toffset",fRunNumber,170);
   RegisterInputCollection("StartTimingCollection","collection including start timing information",fStartTimingColName,TString("start"),
			   &fStartTimingData,"TClonesArray","art::TDiaTimingData");
   RegisterOutputCollection("OutputCollection","output diastrip calibrated array",
			    fOutputColName,TString("plastic_cal"),
			    &fDiaStripOut,"TClonesArray","art::TDiaStripData");
   RegisterProcessorParameter("DetIDRange","range of detector ID",
			      fDetIDRange,defDetIDRange);

   RegisterProcessorParameter("ParameterFile","file of timing offset",fFileName,TString("theta.dat"));
   const DoubleVec_t range(6,0);
   RegisterProcessorParameter("LRPadDiffConst","constant of LR ave minus Pad",
			      fLRPConst,range);
}

TDiaStripCalibrationProcessor::~TDiaStripCalibrationProcessor()
{
   delete fDiaStripOut;
   delete fHits1;
   delete fHits2;
}

void TDiaStripCalibrationProcessor::Init(TEventCollection *col)
{
   Info("Init","(%s, %s) => %s",
	fInputColName1.Data(),fInputColName2.Data(),fStartTimingColName.Data(),fOutputColName.Data());

// TODO: remove fDetIDRange

   fNDet = fDetIDRange[1] - fDetIDRange[0] + 1;
   if (fNDet>0) {
      Info("Init","ID range: [%d:%d], ndet = %d",fDetIDRange[0],fDetIDRange[1],fNDet);
   } else {
      SetStateError("invalid ID range!");
      return;
   }

   fHits1 = new TMultiHitArray;
   fHits2 = new TMultiHitArray;

//   // get run information
//   if ((*fRunHeader)->GetEntries() == 0) {
//      SetStateError("run header does not exist");
//      return;
//   }
//   TRunInfo *runinfo = static_cast<TRunInfo*>((*fRunHeader)->At(0));
//   Int_t runNumber = runinfo->GetRunNumber();
//   Long64_t eventNumber = runinfo->GetEventNumber();
//   
//   if (eventNumber == 0) {
//      SetStateError("Please use TTreeEventStore to find the number of events");
//      return;
//   }
//
//   fRunNumber = &runNumber;
  
//  int run_tmp;
//  double s2st1off_tmp,s2st2off_tmp; 
//  double s2st1off,s2st2off; 
//  std::vector<int> Run; 
//  std::vector<double> S2St1Off; 
//  std::vector<double> S2St2Off; 
//  std::string buff;
//
//   std::ifstream fin(fFileName.Data());
//   if (!fin.is_open()) {
//      Error("Init", "Cannot open file: %s", fFileName.Data());
//      return;
//   }
//   while(getline(fin,buff)) {
//	   stringstream ss(buff);
//	   ss >> run_tmp >> s2st1off_tmp >> s2st2off_tmp;
//       Run.push_back(run_tmp);
//       S2St1Off.push_back(s2st1off_tmp);
//       S2St2Off.push_back(s2st2off_tmp);
//	  }
//   fin.close();
// 
//  Int_t Nvec = Run.size();
//
//for (int i = 0; i < Nvec; i++){
//	if (Run[i] == runNumber){
//		s2st1off = S2St1Off[i];
//		s2st2off = S2St2Off[i];
//     }else {
//	 s2st1off = 0.;
//	 s2st2off = 0.;
//    }
// }
// 
//   if (Nvec != Nrum ) {
//      SetStateError("The number of parameters is not equal to the number of runs");
//      return;
//   }

}

void TDiaStripCalibrationProcessor::FillHitArray(Int_t id)
{
   TMultiHitArray *const hitArray    = id ? fHits2 : fHits1;
   const TClonesArray *const inArray = id ? *fDiaStripIn2 : *fDiaStripIn1;

   hitArray->Clear();
   for(Int_t iHit=0, nHit = inArray->GetEntriesFast(); iHit != nHit; ++iHit) {
      TDiaTimingData *const data = static_cast<TDiaTimingData*>(inArray->At(iHit));
      hitArray->Add(data);
   }
}

void TDiaStripCalibrationProcessor::Process()
{
   fDiaStripOut->Clear("C");

   FillHitArray(0);
   FillHitArray(1);

//   // get run information
//   if ((*fRunHeader)->GetEntries() == 0) {
//      SetStateError("run header does not exist");
//      return;
//   }
//   TRunInfo *runinfo = static_cast<TRunInfo*>((*fRunHeader)->At(0));
//   Int_t runNumber = runinfo->GetRunNumber();
//   Long64_t eventNumber = runinfo->GetEventNumber();
//   
//   if (eventNumber == 0) {
//      SetStateError("Please use TTreeEventStore to find the number of events");
//      return;
//   }
//
//   fRunNumber = &runNumber;

  int run_tmp;
  double s2st1off_tmp,s2st2off_tmp; 
  double s2st1off,s2st2off; 
  std::vector<int> Run; 
  std::vector<double> S2St1Off; 
  std::vector<double> S2St2Off; 
  std::string buff;

   std::ifstream fin(fFileName.Data());
   if (!fin.is_open()) {
      Error("Init", "Cannot open file: %s", fFileName.Data());
      return;
   }
   while(getline(fin,buff)) {
	   stringstream ss(buff);
	   ss >> run_tmp >> s2st1off_tmp >> s2st2off_tmp;
       Run.push_back(run_tmp);
       S2St1Off.push_back(s2st1off_tmp);
       S2St2Off.push_back(s2st2off_tmp);
	  }
   fin.close();
 
  Int_t Nvec = Run.size();
  Int_t runindex = fRunNumber - 170; 

  s2st1off = S2St1Off[runindex];
  s2st2off = S2St2Off[runindex];

//for (int i = 0; i < Nvec; i++){
//	if (Run[i] == runNumber){
//		s2st1off = S2St1Off[i];
//		s2st2off = S2St2Off[i];
//     }else {
//	 s2st1off = 0.;
//	 s2st2off = 0.;
//    }
// }

   // data1,2 are should be filtered out by some timing, charge gate (TODO)
   for(Int_t iDet=0, nDets = fHits1->GetEntriesFast(); iDet!=nDets; ++iDet) {
      const TObjArray *const hitArray1 = fHits1->At(iDet);
      const Int_t size1 = hitArray1->GetEntriesFast();
      if (!size1) continue;
      const Int_t detID = static_cast<TDataObject*>(hitArray1->At(0))->GetID();

      const TObjArray *const hitArray2 = fHits2->GetHits(detID);
      if (!hitArray2) continue;
      const Int_t size2 = hitArray2->GetEntriesFast();

      //      printf("%d\n",detID); // 0,1,2,...,9
      //      printf("%d\n",fHits1->GetEntriesFast()); // 10
      //      printf("size1=%d, size2=%d\n",size1,size2); // 1

      for(Int_t iHit=0, nHit = std::max(size1,size2); iHit != nHit; ++iHit) {
	 TDiaStripData *const output =
	    static_cast<TDiaStripData*>(fDiaStripOut->ConstructedAt(fDiaStripOut->GetEntriesFast()));

	 output->SetDetID(detID);
	 //	 output->SetHitID(iHit + HITID_ORIGIN);

	 /* process input for 1st side */
	 if (iHit < size1) {
	    const TDiaTimingData* const hit1 =
	       static_cast<TDiaTimingData*>(hitArray1->At(iHit));
	    output->SetSide1(hit1);
	    if (IsValid(hit1->GetTiming())) {
	       output->ValidateHit(TDiaStripData::kT1);
	    }
	 }

	 /* process input for 2nd side */
	 if (iHit < size2) {
	    const TDiaTimingData* const hit2 =
	       static_cast<TDiaTimingData*>(hitArray2->At(iHit));
	    output->SetSide2(hit2);
	    if (IsValid(hit2->GetTiming())) {
	       output->ValidateHit(TDiaStripData::kT2);
	    }
	 }

	 /* process timing information */
	 Double_t t1_strip_each[6];
	 Double_t t2_strip_each[6];
	 Double_t t1_strip_each_cal[6];
	 Double_t t2_strip_each_cal[6];

if (output->HasValidHit(TDiaStripData::kT1)
     && output->HasValidHit(TDiaStripData::kT2)) {

     TDiaTimingData *data1 = (TDiaTimingData*) (*fDiaStripIn1)->At(iDet);
	 TDiaTimingData *data2 = (TDiaTimingData*) (*fDiaStripIn2)->At(iDet);
     t1_strip_each[iDet] = data1->GetTiming()*0.001;
     t2_strip_each[iDet] = data2->GetTiming()*0.001;
     

/////20230427/////

     /* calib for F3 */
   if(iDet < 2){
	    const TDiaTimingData* const hit0 = static_cast<TDiaTimingData*>((*fStartTimingData)->At(0));
       Double_t t0 = hit0->GetTiming();
	   if (TMath::Abs((t1_strip_each[iDet] + t2_strip_each[iDet])/2 - t0 - fLRPConst[iDet]) < 5.){

	     t1_strip_each_cal[iDet] = t1_strip_each[iDet];
	     t2_strip_each_cal[iDet] = t2_strip_each[iDet];

	Double_t t10_val = t1_strip_each_cal[iDet];
	Double_t t20_val = t2_strip_each_cal[iDet];
    Double_t timing1 = (t10_val + t20_val) * 0.5;
    Double_t tdiff1 = (t10_val - t20_val);
    
	output -> SetTiming(timing1);
	output -> SetTDiff(tdiff1);
    }else{
		continue;
	}}
	else if(iDet == 2 || iDet == 5){
     const TDiaTimingData* const hit1 = static_cast<TDiaTimingData*>((*fStartTimingData)->At(1));
         Double_t t1 = hit1->GetTiming();
	     t1_strip_each_cal[iDet] = t1_strip_each[iDet];
	     t2_strip_each_cal[iDet] = t2_strip_each[iDet];
 	Double_t t11_val = t1_strip_each_cal[iDet]; 
	Double_t t21_val = t2_strip_each_cal[iDet];
	Double_t timing2, tdiff2; 
	     timing2 = (t11_val + t21_val) * 0.5;
  	     tdiff2 = (t11_val - t21_val);
   	output -> SetTiming(timing2);
	output -> SetTDiff(tdiff2);
	}	
	else{
     const TDiaTimingData* const hit1 = static_cast<TDiaTimingData*>((*fStartTimingData)->At(1));
         Double_t t1 = hit1->GetTiming();
	   if (TMath::Abs((t1_strip_each[iDet] + t2_strip_each[iDet])/2 - t1 - fLRPConst[iDet]) < 0.3){
	     t1_strip_each_cal[iDet] = t1_strip_each[iDet];
	     t2_strip_each_cal[iDet] = t2_strip_each[iDet];
 	Double_t t11_val = t1_strip_each_cal[iDet]; 
	Double_t t21_val = t2_strip_each_cal[iDet];
	Double_t timing2, tdiff2;

 if(fUseTOffset){
	if(iDet == 3){
//	     timing2 = (t11_val + t21_val) * 0.5 - s2st1off;
	     timing2 = (t11_val + t21_val) * 0.5 - s2st1off;
  	     tdiff2 = (t11_val - t21_val);
	}else if(iDet == 4){
         timing2 = (t11_val + t21_val) * 0.5 - s2st2off;
  	     tdiff2 = (t11_val - t21_val);
	}
   	output -> SetTiming(timing2);
	output -> SetTDiff(tdiff2);
  }else {  
    timing2 = (t11_val + t21_val) * 0.5;
    tdiff2 = (t11_val - t21_val);
 	output -> SetTiming(timing2);
	output -> SetTDiff(tdiff2);
   }
 }else {
		continue;
	}
  }

   }
  }
 }
}

