/**
 * @file   TModuleDecoderTimestamp.cc
 * @brief  APV8008 decoder
 *
 * @date   Created       : 2014-05-18 23:53:50 JST
 *         Last Modified :
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 KAWASE Shoichiro
 */

#include "TModuleDecoderTimestamp.h"

#include <TObjArray.h>
//#include <TRawDataTimingCharge.h>
#include <TRawDataSimple.h>

using art::TModuleDecoderTimestamp;

typedef art::TRawDataSimple<ULong64_t> TimestampRaw_t;

ClassImp(TModuleDecoderTimestamp)

TModuleDecoderTimestamp::TModuleDecoderTimestamp()
  : TModuleDecoder(kID, TimestampRaw_t::Class()){
  fHitData = new TObjArray;
}

TModuleDecoderTimestamp::~TModuleDecoderTimestamp()
{
  delete fHitData;
  fHitData = NULL;
}

Int_t TModuleDecoderTimestamp::Decode(char* buf, const Int_t &size, TObjArray *seg)
{
  UShort_t *evtdata = reinterpret_cast<UShort_t*>(buf);
  UInt_t evtsize = size/sizeof(UShort_t);
  Int_t       igeo, ich;
  ULong64_t	ts;
  TimestampRaw_t *data;

  // clear old hits
  fHitData->Clear();

  igeo = 1;
  ich = 0;

  ts =  (ULong64_t)evtdata[3] << 48;
  ts += (ULong64_t)evtdata[2] << 32;
  ts += (ULong64_t)evtdata[1] << 16;
  ts += (ULong64_t)evtdata[0];

  // check if the data object exists.
  if (fHitData->GetEntriesFast() <= ich || !fHitData->At(ich)) {
    // if no data object is available, create one
    TimestampRaw_t *obj = static_cast<TimestampRaw_t*>(this->New());
    obj->SetSegInfo(seg->GetUniqueID(),igeo,ich);
    fHitData->AddAtAndExpand(obj,ich);
    seg->Add(obj);
  }

  data = static_cast<TimestampRaw_t*>(fHitData->At(ich));
  data->Set(ts);
  //printf("%lld\n", ts);

  fHitData->AddAt(NULL,ich);

  return 0;
}

//TModuleDecoderTimestamp::TModuleDecoderTimestamp(const TModuleDecoderTimestamp& rhs)
//{
//}
//
//TModuleDecoderTimestamp& TModuleDecoderTimestamp::operator=(const TModuleDecoderTimestamp& rhs)
//{
//  if (this != &rhs) {
//
//  }
//  return *this;
//}
