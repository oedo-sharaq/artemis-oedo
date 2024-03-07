/**
 * @file   TTimingChargeAPV8008Processor.cc
 * @brief
 *
 * @date   Created:       2013-08-12 12:45:58
 *         Last Modified: 2016-08-17 15:05:41 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved.
 */

#include "TTimingChargeAPV8008Processor.h"
//#include "TTimingChargeData.h"
#include "TAPV8008Data.h"
#include <TRandom.h>
#include <TCategorizedData.h>
#include <TRawDataTriggeredList.h>
//#include <TRawDataTimingCharge.h>
#include <TRawDataTimestampCharge.h>

#include "constant.h"

using art::TTimingChargeAPV8008Processor;

ClassImp(art::TTimingChargeAPV8008Processor)

// Default constructor
TTimingChargeAPV8008Processor::TTimingChargeAPV8008Processor()
   : fPlastic(NULL) {
   RegisterInputCollection("InputCollection","rawdata object returned by TRIDFEventStore",
			   fInputColName,TString("catdata"),
			   &fCategorizedData, "art::TCategorizedData");
   RegisterOutputCollection("OutputCollection","output collection name",
			    fOutputColName,TString("plastic_raw"),
			    &fPlastic, "TClonesArray", "art::TAPV8008Data");
   RegisterProcessorParameter("CatID","Category ID of plastic",fCatID,21);
   RegisterProcessorParameter("ChargeType","hoge",
			      fChargeType,0);
   RegisterProcessorParameter("ChargeTypeID","data type id for charge information (valid when ChargeType != (0 or 2) , default: 2)",
			      fChargeTypeID,2);
   RegisterProcessorParameter("TimingTypeID","data type id for timing information (default: 1)",
			      fTimingTypeID,1);
   RegisterProcessorParameter("TrailingComesFirst","0: Leading->Trailing (default), 1: Trailing->Leading (for QTC etc.)",
			      fTrailingComesFirst,kFALSE);
   RegisterProcessorParameter("Sparse","hit will be inserted at the index corresponding to its id if sparse is 0, otherwize hit will be added ordinaly (default: 1)",
                              fIsSparse,kTRUE);

   RegisterProcessorParameter("Ch1gain","Ge1 Low gain, gain parameter",
                              fCh1gain,0.0);
   RegisterProcessorParameter("Ch1offset","Ge1 Low gain, offset parameter",
                              fCh1offset,0.0);
   RegisterProcessorParameter("Ch2gain","Ge2 Low gain, gain parameter",
                              fCh2gain,0.0);
   RegisterProcessorParameter("Ch2offset","Ge2 Low gain, offset parameter",
                              fCh2offset,0.0);
   RegisterProcessorParameter("Ch3gain","Ge1 High gain, gain parameter",
                              fCh3gain,0.0);
   RegisterProcessorParameter("Ch3offset","Ge1 High gain, offset parameter",
                              fCh3offset,0.0);
   RegisterProcessorParameter("Ch4gain","Ge2 High gain, gain parameter",
                              fCh4gain,0.0);
   RegisterProcessorParameter("Ch4offset","Ge2 High gain, offset parameter",
                              fCh4offset,0.0);
}

TTimingChargeAPV8008Processor::~TTimingChargeAPV8008Processor()
{
   delete fPlastic;
}

void TTimingChargeAPV8008Processor::Init(TEventCollection*)
{
   const TString &chargeTypeStr =
      TString::Format("ChargeType: %d",fChargeType) +
      (fChargeType ? TString::Format(", ChargeTypeID: %d",fChargeTypeID) : "");

   Info("Init","CatID: %d, TimingTypeID: %d => %s",
	fCatID,fTimingTypeID,fOutputColName.Data());
   Info("Init","%s",chargeTypeStr.Data());
   Info("Init","TrailingComesFirst: %d",fTrailingComesFirst);

   if (!fIsSparse) Info("Init","Not sparse.");
}

void TTimingChargeAPV8008Processor::Process()
{
   fPlastic->Clear("C");

   const TObjArray *const cat = (*fCategorizedData)->FindCategory(fCatID);
   if (!cat){
     printf("cannot find category\n");
     return;
   }

   //std::cout << fCatID << std::endl;
   for(Int_t i = 0, n = cat->GetEntriesFast(); i != n ; ++i){
      const TObjArray *const det = static_cast<TObjArray*>(cat->At(i));
      const TObjArray *const qArray = static_cast<TObjArray*>(det->At(fTimingTypeID));
      if (!qArray || qArray->IsEmpty()) continue;
      ChargeWithTS(qArray);
   }

   if (fIsSparse) {
      // sort data in the same event in ascending order of timing
      TAPV8008Data::SetSortType(TAPV8008Data::kTiming);
      TAPV8008Data::SetSortOrder(TAPV8008Data::kASC);
      fPlastic->Sort();
      fPlastic->Compress();
   } else {
      for (Int_t i = 0, n = fPlastic->GetEntriesFast(); i != n; ++i) {
         fPlastic->ConstructedAt(i);
      }
   }
}

void TTimingChargeAPV8008Processor::ChargeWithTS(const TObjArray *qArray)
{
   if (!qArray || qArray->IsEmpty()) return;

   TAPV8008Data *data = NULL;
   for(Int_t iHit = 0, nHit = qArray->GetEntriesFast(); iHit != nHit; ++iHit) {
//      const TRawDataTriggeredList *const hit
      const TRawDataTimestampCharge *const hit
//	 = static_cast<TRawDataTriggeredList*>(qArray->At(iHit));
	 = static_cast<TRawDataTimestampCharge*>(qArray->At(iHit));
      const Int_t detID = hit->GetDetID();
      const Int_t idx = fIsSparse ? fPlastic->GetEntriesFast() : detID;
      data = static_cast<TAPV8008Data*>(fPlastic->ConstructedAt(idx));
      //if(IsValid(data->GetDetID())) continue;
      //printf("detID %d \n", detID);

      data->SetDetID(detID);
      const Double_t tsi = hit->GetTiming();
      const Double_t adc = hit->GetCharge();
      const ULong64_t abs = hit->GetABS();
      const UInt_t absdeci = hit->GetABSdeci();
      const UShort_t chan = hit->GetfChannel();

      //printf("%f, %f, %lld, %d\n",tsi, adc, abs, absdeci);

      data->SetTiming(tsi);
      data->SetCharge(adc);
      data->SetABS(abs);
      data->SetABSdeci(absdeci);
      data->SetfChannel(chan);

      gRandom->SetSeed(0);
      if(chan == 0){
         Double_t tmp = fCh1gain * (adc + gRandom->Uniform(-0.5, 0.5)) + fCh1offset;
         data->SetCalibCharge(tmp);
      }else if(chan == 1){
         Double_t tmp = fCh2gain * (adc + gRandom->Uniform(-0.5, 0.5)) + fCh2offset;
         data->SetCalibCharge(tmp);
      }else if(chan == 2){
         Double_t tmp = fCh3gain * (adc + gRandom->Uniform(-0.5, 0.5)) + fCh3offset;
         data->SetCalibCharge(tmp);
      }else if(chan == 3){
         Double_t tmp = fCh4gain * (adc + gRandom->Uniform(-0.5, 0.5)) + fCh4offset;
         data->SetCalibCharge(tmp);
      }else{
         data->SetCalibCharge(adc);
      }

      //printf("%f, %f, %lld, %d\n",data->GetTiming(), data->GetCharge(), data->GetABS(), data->GetABSdeci());
      
      data = NULL;
   }
}

