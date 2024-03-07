#include "TDiaTimingDataMappingProcessor.h"

#include <TRawDataSimple.h>
#include <TCategorizedData.h>
#include "TDiaTimingData.h"

#include "constant.h"

using art::TDiaTimingDataMappingProcessor;

ClassImp(TDiaTimingDataMappingProcessor)

TDiaTimingDataMappingProcessor::TDiaTimingDataMappingProcessor()
  : fOutputArray(NULL) {
  RegisterInputCollection("InputCollection","rawdata object returned by TRIDFEventStore",
			  fInputColName,TString("catdata"),
			  reinterpret_cast<void***>(&fCategorizedData),
			  "art::TCategorizedData");
  RegisterOutputCollection("OutputCollection","output collection name",
			   fOutputColName,TString("simple"),
			   reinterpret_cast<void**>(&fOutputArray),
			   "TClonesArray","art::TDiaTimingData");
  RegisterProcessorParameter("CatID","Category ID",fCatID,0);
  RegisterProcessorParameter("DataTypeID","data type id for input",
			     fDataTypeID,0);
  //  RegisterProcessorParameter("OutputType","not yet implemented (always output TChargeData)"
  //			     fOutputType,2);
  RegisterProcessorParameter("Sparse","hit will be inserted at the index corresponding to its id if sparse is 0, otherwise added ordinaly", fIsSparse,kTRUE);
}

TDiaTimingDataMappingProcessor::~TDiaTimingDataMappingProcessor()
{
  delete fOutputArray;
  fOutputArray = NULL;
}

void TDiaTimingDataMappingProcessor::Init(TEventCollection *col)
{
  Info("Init","CatID: %d, DataTypeID: %d => %s",
       fCatID, fDataTypeID, fOutputColName.Data());
  if (!fIsSparse) Info("Init","Not sparse.");
}

void TDiaTimingDataMappingProcessor::Process()
{
  if (!fCategorizedData) return;

  fOutputArray->Clear("C");

  const TObjArray *const cat = (*fCategorizedData)->FindCategory(fCatID);
  if (!cat) return;

  const Int_t n = cat->GetEntriesFast();
  for(Int_t i = 0 ; i != n ; ++i) {
    const TObjArray *const det = static_cast<TObjArray*>(cat->At(i));
    const TObjArray *const dataArray = static_cast<TObjArray*>(det->At(fDataTypeID));
    if (!dataArray) continue;

    const TRawDataSimple<UInt_t> *const hit = 
      dynamic_cast<TRawDataSimple<UInt_t>*>(dataArray->At(0));
    if (!hit) continue;

    const Int_t detID = hit->GetDetID();
    const Int_t idx = fIsSparse ? fOutputArray->GetEntriesFast() : detID;
    TDiaTimingData *const data =
      static_cast<TDiaTimingData*>(fOutputArray->ConstructedAt(idx));
    if (IsValid(data->GetID())) return; // take only the first hit if not sparse

    data->SetID(detID);
    // invalid hit -> 2147483648 (2.1e09)
    // 1000ns = 1e6 ps
    if (hit->Get() > 1.0e+9) {
      data->SetTiming(TMath::QuietNaN());
    } else {
      data->SetTiming(hit->Get());
    }
    
  }

  if(fIsSparse) {
    TDiaTimingData::SetSortType( TDiaTimingData::kTiming);
    TDiaTimingData::SetSortOrder(TDiaTimingData::kASC);
    fOutputArray->UnSort();
    fOutputArray->Sort();
    fOutputArray->Compress();
  } else {
    const Int_t n = fOutputArray->GetEntriesFast();
    for (Int_t i = 0; i!=n; ++i) {
      fOutputArray->ConstructedAt(i);
    }
  }
}
