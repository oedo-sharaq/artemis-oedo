/**
 * @file   TModuleDecoderAPV8008.cc
 * @brief  APV8008 decoder
 *
 * @date   Created       : 2014-05-18 23:53:50 JST
 *         Last Modified :
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 KAWASE Shoichiro
 */

#include "TModuleDecoderAPV8008.h"

#include <TObjArray.h>
//#include <TRawDataTimingCharge.h>
#include <TRawDataTimestampCharge.h>

using art::TModuleDecoderAPV8008;

//typedef art::TRawDataTimingCharge APV8008Raw_t;
typedef art::TRawDataTimestampCharge APV8008Raw_t;

ClassImp(TModuleDecoderAPV8008)

TModuleDecoderAPV8008::TModuleDecoderAPV8008()
  : TModuleDecoder(kID, APV8008Raw_t::Class()){
  fHitData = new TObjArray;
}

TModuleDecoderAPV8008::~TModuleDecoderAPV8008()
{
  delete fHitData;
  fHitData = NULL;
}

Int_t TModuleDecoderAPV8008::Decode(char* buf, const Int_t &size, TObjArray *seg)
{
  UShort_t *evtdata = reinterpret_cast<UShort_t*>(buf);
  UInt_t evtsize = size/sizeof(UShort_t);
  Int_t       igeo, ich;
  UInt_t	charge;
  Double_t	timing;
  ULong64_t	abs;
  UInt_t	absdeci;
  UShort_t	channel;
  APV8008Raw_t *data;

  // clear old hits
  fHitData->Clear();

  igeo = 0;
  for(UInt_t i=0; i<evtsize; ++i){
    evtdata[i] = ((evtdata[i] & 0xff00) >> 8) | ((evtdata[i] & 0x00ff) << 8);
    //evtdata[i] = ((evtdata[i] & 0xf0f0) >> 4) | ((evtdata[i] & 0x0f0f) << 4);
    //evtdata[i] = ((evtdata[i] & 0xcccc) >> 2) | ((evtdata[i] & 0x3333) << 2);
    //evtdata[i] = ((evtdata[i] & 0xaaaa) >> 1) | ((evtdata[i] & 0x5555) << 1);
  }

  ich = evtdata[4] & 0x0007;
  channel = ich;
  charge = evtdata[3] & 0x1fff;
  timing = (((ULong64_t)evtdata[0] << 28) + ((ULong64_t)evtdata[1] << 12) + ((evtdata[2] & 0xfff0) >> 4))*10.0 + (evtdata[2] & 0x000f)*0.625;
  abs = ((ULong64_t)evtdata[0] << 28) + ((ULong64_t)evtdata[1] << 12) + ((evtdata[2] & 0xfff0) >> 4);
  absdeci = evtdata[2] & 0x000f;

  //printf("\n");
  //printf("%llx, %llx, %llx, %llx, %lld, %f\n", (ULong64_t)evtdata[0]<<28, (ULong64_t)evtdata[1]<<12, (ULong64_t)(evtdata[2]&0xfff0)>>4, abs, abs, timing);
  //printf("\n");

  // check if the data object exists.
  if (fHitData->GetEntriesFast() <= ich || !fHitData->At(ich)) {
    // if no data object is available, create one
    APV8008Raw_t *obj = static_cast<APV8008Raw_t*>(this->New());
    obj->SetSegInfo(seg->GetUniqueID(),igeo,ich);
    fHitData->AddAtAndExpand(obj,ich);
    seg->Add(obj);
  }

  data = static_cast<APV8008Raw_t*>(fHitData->At(ich));
  //data->SetTiming(tdc);
  //data->SetCharge(adc);
  data->SetTiming(timing);
  data->SetCharge(charge);
  data->SetABS(abs);
  data->SetABSdeci(absdeci);
  data->SetfChannel(channel);

  fHitData->AddAt(NULL,ich);

  //for (Int_t i=0; i < evtsize; ++i) {
  //  if ((evtdata[i] & 0x60000000) == 0x60000000) {
  //    igeo = 1;
  //    continue;
  //  }

  //  ich = (evtdata[i] & 0x0003c000) >> 14;
  //  measure = evtdata[i] & 0x1fff;

  //  // check if the data object exists.
  //  if (fHitData->GetEntriesFast() <= ich || !fHitData->At(ich)) {
  //    // if no data object is available, create one
  //    APV8008Raw_t *obj = static_cast<APV8008Raw_t*>(this->New());
  //    obj->SetSegInfo(seg->GetUniqueID(),igeo,ich);
  //    fHitData->AddAtAndExpand(obj,ich);
  //    seg->Add(obj);
  //  }

  //  //data = static_cast<APV8008Raw_t*>(fHitData->At(ich));
  //  //data->Set(measure);
  //  obj->SetTiming(0);
  //  obj->SetCharge(0);

  //  fHitData->AddAt(NULL,ich);
  //}

  return 0;
}

//TModuleDecoderAPV8008::TModuleDecoderAPV8008(const TModuleDecoderAPV8008& rhs)
//{
//}
//
//TModuleDecoderAPV8008& TModuleDecoderAPV8008::operator=(const TModuleDecoderAPV8008& rhs)
//{
//  if (this != &rhs) {
//
//  }
//  return *this;
//}
