#include "TDiaTimingSubtractionProcessor.h"
#include <TClonesArray.h>
#include <TMath.h>
#include "TDiaTimingData.h"

using art::TDiaTimingSubtractionProcessor;

ClassImp(TDiaTimingSubtractionProcessor)

TDiaTimingSubtractionProcessor::TDiaTimingSubtractionProcessor()
{
  RegisterInputCollection("InputCollection1","input collection including start timing information",fInputColName1,TString("input1"),
			  &fInput1,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
  RegisterInputCollection("InputCollection2","input collection including stop timing information",fInputColName2,TString("input2"),
			  &fInput2,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());

  RegisterProcessorParameter("Toffset","parameter for adjusting the offset",fToffset,Double_t(0));
  RegisterOutputCollection("OutputCollection","name of output collection",fOutputColName,TString("output"),
			   &fOutput,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
}

TDiaTimingSubtractionProcessor::~TDiaTimingSubtractionProcessor()
{
}

TDiaTimingSubtractionProcessor::TDiaTimingSubtractionProcessor(const TDiaTimingSubtractionProcessor& rhs)
{
}

TDiaTimingSubtractionProcessor& TDiaTimingSubtractionProcessor::operator=(const TDiaTimingSubtractionProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TDiaTimingSubtractionProcessor::Process()
{
   fOutput->Clear("C");
   TDiaTimingData *data1 = (TDiaTimingData*) (*fInput1)->At(0);
   TDiaTimingData *data2 = (TDiaTimingData*) (*fInput2)->At(0);

  
   Double_t start_timing = data1->GetTiming(); // strip
   Double_t stop_timing  = data2->GetTiming(); // strip
   Double_t dia_tof;
   
//   Double_t start_timing_pad = data1->GetPadTiming(); // pad
//   Double_t stop_timing_pad  = data2->GetPadTiming(); // pad
//   Double_t dia_tof_pad;

//// validate timing
// f3 valid 
   if( TMath::Abs(start_timing) > 1000 || TMath::Abs(start_timing) < 0.1){
	   return;
   }

// s2 valid
   if( TMath::Abs(stop_timing - 225.) > 100){
	   return;
   }


   dia_tof = (stop_timing - start_timing) - fToffset; 
//   dia_tof_pad = stop_timing_pad - start_timing_pad;
   //   printf("start=%lf, stop=%lf\n",start_timing,stop_timing);

   //   printf("%d\n",fOutput->GetEntriesFast());
   TDiaTimingData *out  = (TDiaTimingData*) fOutput->ConstructedAt(fOutput->GetEntriesFast());
   out->SetTiming(dia_tof);  
//   out->SetPadTiming(dia_tof_pad);  


}
