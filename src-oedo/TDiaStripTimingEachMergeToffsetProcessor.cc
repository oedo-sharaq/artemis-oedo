#include "TDiaStripTimingEachMergeToffsetProcessor.h"
#include <TClonesArray.h>
#include "TDiaTimingData.h"
#include <TMWDCTrackingResult.h>
#include "TDiaPadData.h"
#include "TDiaData.h"
#include <TTimingChargeData.h>

#include "constant.h"
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>


using art::TDiaStripTimingEachMergeToffsetProcessor;

using namespace std;

ClassImp(TDiaStripTimingEachMergeToffsetProcessor)


TDiaStripTimingEachMergeToffsetProcessor::TDiaStripTimingEachMergeToffsetProcessor()
{

   const DoubleVec_t defTimeValidRange(2,1); // [1,1]
//   const DoubleVec_t defToffset(3,1); // [1,1]
   const DoubleVec_t defToffset(2,1); // [1,1]

  RegisterInputCollection("InputCollection1","name of input collection (dia strip1)",fInputColName1,TString("input1"),
			  &fInput1,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
  RegisterInputCollection("InputCollection2","name of input collection (dia strip2)",fInputColName2,TString("input2"),
			  &fInput2,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
//  RegisterInputCollection("InputCollection3","name of input collection (dia strip3)",fInputColName3,TString("input3"),
//			  &fInput3,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
  RegisterProcessorParameter("MWDC","output from mwdc",fMWDCName,TString("s2"));
  RegisterOutputCollection("OutputCollection","name of output collection",fOutputColName,TString("output"),
			   &fOutput,TClonesArray::Class_Name(),TDiaData::Class_Name());
  RegisterProcessorParameter("TimeValidRange","range of detector ID (dia strip)",
			     fTimeValidRange,defTimeValidRange);
  RegisterProcessorParameter("Timeoffset","tof offset [st1, st2, st3]",
			     fToffset,defToffset);

   RegisterProcessorParameter("UseYvalid","use position validation",fUseYvalid,0);
   RegisterProcessorParameter("ParameterFile","file of timing offset",fFileName,TString("theta.dat"));
   RegisterProcessorParameter("RunNumber","run number input for toffset",fRunNumber,170);
}

TDiaStripTimingEachMergeToffsetProcessor::~TDiaStripTimingEachMergeToffsetProcessor()
{
}

TDiaStripTimingEachMergeToffsetProcessor::TDiaStripTimingEachMergeToffsetProcessor(const TDiaStripTimingEachMergeToffsetProcessor& rhs)
{
}

TDiaStripTimingEachMergeToffsetProcessor& TDiaStripTimingEachMergeToffsetProcessor::operator=(const TDiaStripTimingEachMergeToffsetProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TDiaStripTimingEachMergeToffsetProcessor::Init(TEventCollection *col)
{ 

 fMWDC = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fMWDCName.Data()));
 if (!fMWDC) return;

}


void TDiaStripTimingEachMergeToffsetProcessor::Process()
{
   fOutput->Clear("C");
   Int_t nHit1 = (*fInput1)->GetEntriesFast();
   Int_t nHit2 = (*fInput2)->GetEntriesFast();
//   Int_t nHit3 = (*fInput3)->GetEntriesFast();

  int run_tmp;
  double tofoffset_tmp; 
  double tofoffset; 
  std::vector<int> Run; 
  std::vector<double> TofOffset; 
  std::string buff;

   std::ifstream fin(fFileName.Data());
   if (!fin.is_open()) {
      Error("Init", "Cannot open file: %s", fFileName.Data());
      return;
   }
   while(getline(fin,buff)) {
	   stringstream ss(buff);
	   ss >> run_tmp >> tofoffset_tmp;
       Run.push_back(run_tmp);
       TofOffset.push_back(tofoffset_tmp);
	  }
   fin.close();
 
  Int_t Nvec = Run.size();
  Int_t runindex = fRunNumber - 170; 

  tofoffset = TofOffset[runindex];

   Double_t t_strip_merge_tmp,t_strip_merge,t1,t2,t3;
   Double_t t1_tmp,t2_tmp,t3_tmp;
   Int_t id_strip_merge;

if (nHit1 > 0){
   TDiaTimingData *data1 = (TDiaTimingData*) (*fInput1)->At(0);
    t1_tmp = data1->GetTiming();
}else{
	t1_tmp = -1000;
}

if (nHit2 > 0){
   TDiaTimingData *data2 = (TDiaTimingData*) (*fInput2)->At(0);
    t2_tmp = data2->GetTiming();
}else{
	t2_tmp = -1000;
}

//if (nHit3 > 0){
//   TDiaTimingData *data3 = (TDiaTimingData*) (*fInput3)->At(0);
//    t3_tmp = data3->GetTiming();
//}else{
//	t3_tmp = -1000;
//}

   t1 = t1_tmp - fToffset[0];
   t2 = t2_tmp - fToffset[1];
//   t3 = t3_tmp + fToffset[2];

   Bool_t t1_valid = fTimeValidRange[0] < t1 && t1 < fTimeValidRange[1];
   Bool_t t2_valid = fTimeValidRange[0] < t2 && t2 < fTimeValidRange[1];
//   Bool_t t3_valid = fTimeValidRange[0] < t3 && t3 < fTimeValidRange[1];


 // s2 position validation

if(fUseYvalid){
 		 const TMWDCTrackingResult *const trackd = static_cast<TMWDCTrackingResult*>((*fMWDC)->At(0));
         if(!trackd) return;

         Bool_t trackd_ok = trackd->IsGood();
		 if(!trackd_ok) return;

	     Double_t y2 = trackd->GetY();

//   Bool_t st1_y2valid = TMath::Abs(y2-22) < 2.5;
   Bool_t st1_y2valid =  19.5 <= y2  && y2 <= 25;
//   Bool_t st2_y2valid = TMath::Abs(y2-17) < 2.5;
   Bool_t st2_y2valid =  15 <= y2 && y2 <= 19.5;
//   Bool_t st3_y2valid = TMath::Abs(y2-10) < 4.5;


 if( t1_valid && st1_y2valid){
	 t_strip_merge_tmp = t1;
	 id_strip_merge = 1;
 }else if(t2_valid && st2_y2valid){
	 t_strip_merge_tmp = t2;
	 id_strip_merge = 2;
// }else if (t3_valid && st3_y2valid){
//	 t_strip_merge = t3;
//	 id_strip_merge = 3;
//} else if(t1_valid && t2_valid && TMath::Abs(y2-19.5) < 0.5){
//     if (t1 < t2){
//		 t_strip_merge = t1;
//		 id_strip_merge = 1;
//	 }else{
//		 t_strip_merge = t2;
//		 id_strip_merge = 2;
//     }
} else {
   return;
}

}

 if(!fUseYvalid){

 if(t1_valid && !t2_valid){
	 t_strip_merge_tmp = t1;
	 id_strip_merge = 1;
 }else if(t2_valid && !t1_valid){
	 t_strip_merge_tmp = t2;
	 id_strip_merge = 2;
// }else if (t3_valid && st3_y2valid){
//	 t_strip_merge = t3;
//	 id_strip_merge = 3;
} else if(t1_valid && t2_valid){
     if (t1 < t2){
		 t_strip_merge_tmp = t1;
		 id_strip_merge = 1;
	 }else{
		 t_strip_merge_tmp = t2;
		 id_strip_merge = 2;
     }
} else {
   return;
}

}


  t_strip_merge = t_strip_merge_tmp - tofoffset; 

   TDiaTimingData *out  = (TDiaTimingData*) fOutput->ConstructedAt(fOutput->GetEntriesFast());
     out->SetTiming(t_strip_merge);
     out->SetDetID(id_strip_merge);
   
}
