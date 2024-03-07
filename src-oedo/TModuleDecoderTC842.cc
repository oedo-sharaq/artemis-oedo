#include "TModuleDecoderTC842.h"

#include <TObjArray.h>
#include <TRawDataSimple.h>
#include <string.h>

using art::TModuleDecoderTC842;

typedef art::TRawDataSimple<UInt_t> TC842Raw_t;

ClassImp(TModuleDecoderTC842)

TModuleDecoderTC842::TModuleDecoderTC842()
  : TModuleDecoder(kID, TC842Raw_t::Class()){
  fHitData = new TObjArray;
}

TModuleDecoderTC842::~TModuleDecoderTC842()
{
  delete fHitData;
  fHitData = NULL;
}

Int_t TModuleDecoderTC842::Decode(char* buf, const Int_t &size, TObjArray *seg)
{
  UInt_t *evtdata = reinterpret_cast<UInt_t*>(buf);
  //  UInt_t evtsize = size/sizeof(UInt_t);
  Int_t       igeo, ich;
  Int_t       measure;
  TC842Raw_t *data;

  // clear old hits
  fHitData->Clear();

  Double_t x[48], y = 1.e+12, t;
  Int_t evtsize = size/sizeof(double), it;

  memcpy((char *)x, buf, size);

  igeo = 0;
  for (Int_t i=0; i < evtsize; ++i) {
    t = x[i]*y;
    it = (int)t;
    
    ich = i;
    measure = it;

    //    printf("ich=%d x=%g measure=%d\n", ich, x[i], measure);
    //printf("GetEntriesFast=%d\n", fHitData->GetEntriesFast());
    //    printf("ich=%d,At=%d\n", ich,fHitData->At(ich));

    // check if the data object exists.
    if (fHitData->GetEntriesFast() <= ich || !fHitData->At(ich)) {
      // if no data object is available, create one
      TC842Raw_t *obj = static_cast<TC842Raw_t*>(this->New());
      obj->SetSegInfo(seg->GetUniqueID(),igeo,ich);
      fHitData->AddAtAndExpand(obj,ich);
      seg->Add(obj);
    }

    data = static_cast<TC842Raw_t*>(fHitData->At(ich));
    data->Set(measure);
    
    //    if(measure>0.0 && ich==5){
    //  printf("ich=%d, measure=%d\n", ich, measure);
    //}

    //    printf("GetEntriesFast1=%d\n", fHitData->GetEntriesFast());
    //printf("GetEntries1=%d\n", fHitData->GetEntries());
    //    printf("ich=%d,At=%d\n", ich,fHitData->At(ich));
    fHitData->AddAt(NULL,ich);
    //printf("GetEntriesFast2=%d\n", fHitData->GetEntriesFast());
    //printf("GetEntries2=%d\n", fHitData->GetEntries());
    //printf("ich=%d,At=%d\n", ich,fHitData->At(ich));
  }

  return 0;
}

//TModuleDecoderTC842::TModuleDecoderTC842(const TModuleDecoderTC842& rhs)
//{
//}
//
//TModuleDecoderTC842& TModuleDecoderTC842::operator=(const TModuleDecoderTC842& rhs)
//{
//  if (this != &rhs) {
//
//  }
//  return *this;
//}
