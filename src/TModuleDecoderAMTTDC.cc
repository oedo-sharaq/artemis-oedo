/*
 * @file TModuleDecoderAMTTDC.cc
 * @date  Created : 
 *  Last Modified : 2021.05.13 HJKT
 *--------------------------------------------------------
 *    Comment : 
 *              
 *
 *--------------------------------------------------------
 *    Copyright (C) by Yuto HIJIKATA 
 */
#include "TModuleDecoderAMTTDC.h"
#include <TRawTimingWithEdge.h>
#include <TObjArray.h>

using art::TModuleDecoderAMTTDC;
using art::TRawTimingWithEdge;

typedef TRawTimingWithEdge AMTTDCRaw_t;

ClassImp(TModuleDecoderAMTTDC)

TModuleDecoderAMTTDC::TModuleDecoderAMTTDC()
   : TModuleDecoder(kID,AMTTDCRaw_t::Class()) {
  fHitData = new TObjArray;
}

TModuleDecoderAMTTDC::TModuleDecoderAMTTDC(Int_t id)
   : TModuleDecoder(id,AMTTDCRaw_t::Class()) {
  fHitData = new TObjArray;
}

TModuleDecoderAMTTDC::~TModuleDecoderAMTTDC()
{
  if (fHitData) delete fHitData;
  fHitData = NULL;
}

Int_t TModuleDecoderAMTTDC::Decode(char* buf, const int &size, TObjArray *seg)
{
  //   printf("amsc start\n");
   UInt_t *evtdata = (UInt_t*) buf;
   UInt_t evtsize = size/sizeof(UInt_t);
   Int_t ih, igeo, ich;
   Int_t ghf, thf, bncid, evtid, edge, idx;
   AMTTDCRaw_t *data;
   Int_t measure;
   ghf = thf = 0;

   Int_t total, mdlid, wdsel, egdct, msctr, cmn, fr, hdata;

   // clear old hits
   fHitData->Clear();

   for(Int_t i=0; i<evtsize; ++i) {
     ih = evtdata[i]&kHeaderMask;
   
     switch (ih) {
     case kRecordingDataStatus:
//       printf("kRecordingDataStatus\n");
       total =  (evtdata[i]&kMaskTotalRecordingData) >> 16;
       evtid =  (evtdata[i]&kMaskEventNumber) >> 0;
       break;
     case kStartStopTime:
//       printf("kStartStopTime\n");
       total =  (evtdata[i]&kMaskTotalRecordingData) >> 16;
       mdlid =  (evtdata[i]&kMaskModuleID) >> 24;
       igeo = mdlid;
       wdsel  =  (evtdata[i]&kMaskWidthSelect) >> 20;
       egdct  =  (evtdata[i]&kMaskEdgeDetection) >> 18;
       msctr  =  (evtdata[i]&kMaskMeasurementControl) >> 17;
       cmn    =  (evtdata[i]&kMaskCommonTime) >> 0;
       break;
     case kHitData:
       fr     =  (evtdata[i]&kMaskFallOrRise) >> 28;
       ich    =  (evtdata[i]&kMaskChannelNumber) >>20;
       idx    = igeo * 128 + ich;
       hdata  =  (evtdata[i]&kMaskHitTimeData) >> 0;
  //     printf("amsc check1,idx = %x, ich = %x, igeo = %x, hdata = %x , fr = %x\n",idx,ich,igeo,hdata,fr);
       // check if the data object exists.
       if (fHitData->GetEntriesFast() <= idx || !fHitData->At(idx)) {
//          printf("amsc check1',idx = %x\n",idx);
          // if no data object is available, create one
          AMTTDCRaw_t *obj = static_cast<AMTTDCRaw_t*>(this->New());
          obj->SetSegInfo(seg->GetUniqueID(),igeo,ich);
          fHitData->AddAtAndExpand(obj,idx);
          seg->Add(obj);
       }
//	  printf("geo:%d,ch:%d,data%d,isleading? %d\n",igeo,ich,-hdata,fr);
       hdata= -hdata;
       data = static_cast<AMTTDCRaw_t*>(fHitData->At(idx));
       data->Set(hdata);
       data->SetEdge(!fr); // definition of edge is opposite to that in TRawTimingWithEdge
       fHitData->AddAt(NULL,idx);
//       printf("amsc check2");
       break;
     case kErrorReport:
       //printf("AMTTDC [TDC Error    ] : 0x%08x\n", evtdata[i]);
       break;
     case kEndOfData:
       break;
     }
   }
   return 0;
}
