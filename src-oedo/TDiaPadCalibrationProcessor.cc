#include "TDiaPadCalibrationProcessor.h"
#include "TDiaPadData.h"
#include "TMultiHitArray.h"
#include "TConverterBase.h"
#include "TConverterUtil.h"

#include <TSystem.h>
#include <TClonesArray.h>

using art::TDiaPadCalibrationProcessor;
using std::vector;

ClassImp(art::TDiaPadCalibrationProcessor);

TDiaPadCalibrationProcessor::TDiaPadCalibrationProcessor()
   : fDiaPadIn1(NULL), fDiaPadOut(NULL),
     fHits1(NULL)
{
   const IntVec_t defDetIDRange(2,1); // [1,1]

   RegisterInputCollection("InputCollection","input of dia pad",
			   fInputColName1,TString("diapad"),
			   &fDiaPadIn1,"TClonesArray","art::TDiaTimingData");
   RegisterOutputCollection("OutputCollection","output diapad calibrated array",
			    fOutputColName,TString("diapad_cal"),
			    &fDiaPadOut,"TClonesArray","art::TDiaPadData");
   RegisterProcessorParameter("DetIDRange","range of detector ID",
			      fDetIDRange,defDetIDRange);
}

TDiaPadCalibrationProcessor::~TDiaPadCalibrationProcessor()
{
   delete fDiaPadOut;
   delete fHits1;
}

void TDiaPadCalibrationProcessor::Init(TEventCollection *col)
{
   Info("Init","%s => %s",
	fInputColName1.Data(),fOutputColName.Data());

// TODO: remove fDetIDRange

   fNDet = fDetIDRange[1] - fDetIDRange[0] + 1;
   if (fNDet>0) {
      Info("Init","ID range: [%d:%d], ndet = %d",fDetIDRange[0],fDetIDRange[1],fNDet);
   } else {
      SetStateError("invalid ID range!");
      return;
   }

   fHits1 = new TMultiHitArray;
}

void TDiaPadCalibrationProcessor::FillHitArray()
{
  TMultiHitArray *const hitArray  = fHits1;
  const TClonesArray *const inArray = *fDiaPadIn1;
  
  hitArray->Clear();
  for(Int_t iHit=0, nHit = inArray->GetEntriesFast(); iHit != nHit; ++iHit) {
    TDiaTimingData *const data = static_cast<TDiaTimingData*>(inArray->At(iHit));
    hitArray->Add(data);
  }
}

void TDiaPadCalibrationProcessor::Process()
{
   fDiaPadOut->Clear("C");

   FillHitArray();
   
   for(Int_t iDet=0, nDets = fHits1->GetEntriesFast(); iDet!=nDets; ++iDet) {
      const TObjArray *const hitArray1 = fHits1->At(iDet);
      const Int_t size1 = hitArray1->GetEntriesFast();
      if (!size1) continue;
      const Int_t detID = static_cast<TDataObject*>(hitArray1->At(0))->GetID();

      for(Int_t iHit=0, nHit = size1; iHit != nHit; ++iHit) {
	TDiaPadData *const output =
	  static_cast<TDiaPadData*>(fDiaPadOut->ConstructedAt(fDiaPadOut->GetEntriesFast()));
	
	output->SetDetID(detID);
	//	 output->SetHitID(iHit + HITID_ORIGIN);
	
	if (iHit < size1) {
	  const TDiaTimingData* const hit1 =
	    static_cast<TDiaTimingData*>(hitArray1->At(iHit));
	  output->SetPad(hit1);
	  if (IsValid(hit1->GetTiming())) {
	    output->ValidateHit(TDiaPadData::kT1);
	  }
	}
	
	//	printf("T=%lf\n",output->GetT1());
	/* process timing information */
	if (output->HasValidHit(TDiaPadData::kT1)) {
	  const Double_t t1 = output->GetT1()*0.001; // !! [ps] to [ns]
	  
	  // invalid hit -> 2147483648 (2.1e09)
	  // 1000ns = 1e6 ps
	  if (t1 < 1.0e+5) { 
	    output -> ValidateHitPad();
	  }
	  
	  const Double_t timing = t1;
	  
	  output -> SetTiming(timing);
	}
      }
   }
}
