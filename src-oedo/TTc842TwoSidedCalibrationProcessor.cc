#include "TTc842TwoSidedCalibrationProcessor.h"
#include <TClonesArray.h>
#include "TDiaTimingData.h"

using art::TTc842TwoSidedCalibrationProcessor;

ClassImp(TTc842TwoSidedCalibrationProcessor)

TTc842TwoSidedCalibrationProcessor::TTc842TwoSidedCalibrationProcessor()
{
  RegisterInputCollection("InputCollection1","input collection including start timing information",fInputColName1,TString("input1"),
			  &fInput1,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
  RegisterInputCollection("InputCollection2","input collection including stop timing information",fInputColName2,TString("input2"),
			  &fInput2,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());

  RegisterOutputCollection("OutputCollection","name of output collection",fOutputColName,TString("output"),
			   &fOutput,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
}

TTc842TwoSidedCalibrationProcessor::~TTc842TwoSidedCalibrationProcessor()
{
}

TTc842TwoSidedCalibrationProcessor::TTc842TwoSidedCalibrationProcessor(const TTc842TwoSidedCalibrationProcessor& rhs)
{
}

TTc842TwoSidedCalibrationProcessor& TTc842TwoSidedCalibrationProcessor::operator=(const TTc842TwoSidedCalibrationProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TTc842TwoSidedCalibrationProcessor::Process()
{
   fOutput->Clear("C");
   TDiaTimingData *data1 = (TDiaTimingData*) (*fInput1)->At(0);
   TDiaTimingData *data2 = (TDiaTimingData*) (*fInput2)->At(0);

   Double_t t1 = data1->GetTiming()*0.001; // strip
   Double_t t2  = data2->GetTiming()*0.001; // strip
   Double_t dia_tave;
   
//   Double_t start_timing_pad = data1->GetPadTiming(); // pad
//   Double_t stop_timing_pad  = data2->GetPadTiming(); // pad
//   Double_t dia_tof_pad;

   dia_tave = (t1 + t2) * 0.5; 
//   dia_tof_pad = stop_timing_pad - start_timing_pad;
   //   printf("start=%lf, stop=%lf\n",start_timing,stop_timing);

   //   printf("%d\n",fOutput->GetEntriesFast());
   TDiaTimingData *out  = (TDiaTimingData*) fOutput->ConstructedAt(fOutput->GetEntriesFast());
   out->SetTiming(dia_tave);  
//   out->SetPadTiming(dia_tof_pad);  
}
