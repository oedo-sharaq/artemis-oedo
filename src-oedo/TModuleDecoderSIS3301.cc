/*
 * @file TModuleDecoderSIS3301.cc
 * @date  Created : 
 *  Last Modified : Jul 15, 2014 13:51:30 JST
 *--------------------------------------------------------
 *    Comment :
 *              
 *    only for oedo commissioning
 *--------------------------------------------------------
 *    Copyright (C)2008-2013 by Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 */
#include "TModuleDecoderSIS3301.h"

#include <TObjArray.h>
#include <TRawDataFadc.h>

using art::TModuleDecoderSIS3301;

TModuleDecoderSIS3301::TModuleDecoderSIS3301()
   : TModuleDecoder(kID,TRawDataFadc::Class()) {
}

TModuleDecoderSIS3301::~TModuleDecoderSIS3301()
{
}

Int_t TModuleDecoderSIS3301::Decode(char* buf, const int &size, TObjArray *seg)
{
//   seg->Dump();
   UInt_t *evtdata = (UInt_t*) buf;
   UInt_t evtsize = size/sizeof(UInt_t);
   UInt_t ih;
   Int_t igeo, ich;
   UInt_t hf, tf;
   UInt_t pagesize, evtid, clock;
   Int_t data1st,data2nd;
   Int_t sumsample1st,sumsample2nd;
   hf = tf = 0;
   igeo = -1;
   ich = -1;
   pagesize = -1;
   TRawDataFadc* data = NULL;

   //printf("evtsize = %d\n",evtsize);
   for (UInt_t i=0; i<evtsize;) {
      //printf("evtdata[%d] = 0x%08x\n",i,evtdata[i]);
     ih = (evtdata[i]&0xc0000000)>>30;
     if ((hf == 0) && (tf == 0) && (ih == 0x3)) {
        hf = 1;
        igeo = (evtdata[i] & kMaskGeometry) >> kShiftGeometry;
        ich  = (evtdata[i] & kMaskChannel) >>  kShiftChannel;
        //printf("igeo = %d, ich = %d\n",igeo,ich);
        sumsample1st = 0.;
        sumsample2nd = 0.;
        data = (TRawDataFadc*) New();
        data->Clear("C");
        data->SetSegInfo(seg->GetUniqueID(),igeo,ich);
        i += 1;
     } else if ((hf == 1) && (tf == 0) && (ih == 0x2)) {
        tf = 1;
        //pagesize = (evtdata[i] & kMaskPagesize) >> kShiftPagesize;
        pagesize = (evtdata[i] & 0x3fffffff) >> 0;
        //evtid = (evtdata[i] & kMaskEventID) >> kShiftEventID;
        evtid = 0;
        //clock = (evtdata[i] & kMaskClock) >> kShiftClock;
        clock = 0;
        //printf("pagesize = %d, evtid = %d, clock = %d\n",pagesize,evtid,clock);
        //TRawDataFadc* data = (TRawDataFadc*) New();
        if(!data) {
           printf("no data\n");
           continue;
        }
        data->SetFadcInfo(pagesize,evtid,clock);
        i += 1;
     } else if ((hf == 1) && (tf == 1)){
        //printf("ch %d : {",ich);
        for (UInt_t j=i;j<i+pagesize/2;) {
           data1st = (evtdata[j] & kMaskData1st) >> kShiftData1st;
           data2nd = (evtdata[j] & kMaskData2nd) >> kShiftData2nd;
           sumsample1st += data1st;
           sumsample2nd += data2nd;
           //printf("ich = %2d, data1st = 0x%04x, data2nd = 0x%04x\n",
           //       ich,data1st,data2nd);
           //printf(" 0x%04x 0x%04x",data1st,data2nd);
           if(!data) {
              printf("no data\n");
              continue;
           }
           data->Add(data1st);
           data->Add(data2nd);
           j++;
        }
        seg->Add(data);
        //printf(" }\n");
        i += pagesize/2;
        hf = tf = 0;
     } else {
        printf("Decode""Unknown Header 0x%08x\n",evtdata[i]);
        return 0;
     }
   }
   return 0;
}
