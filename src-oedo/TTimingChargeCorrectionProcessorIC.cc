#include "TTimingChargeCorrectionProcessorIC.h"

#include "ITiming.h"
#include "ICharge.h"
#include "TConverterBase.h"
#include "TConverterUtil.h"
#include "constant.h"
#include "TDataObject.h"

#include <TClonesArray.h>
#include <TRandom.h>
#include <TClass.h>

#include "TSRPPACPlaneProcessor.h"
#include "TSRPPACParameter.h"

using art::TTimingChargeCorrectionProcessorIC;

namespace {
   const TString DEFAULT_CONV_NAME("no_conversion");
}

ClassImp(art::TTimingChargeCorrectionProcessorIC)

// Default constructor
TTimingChargeCorrectionProcessorIC::TTimingChargeCorrectionProcessorIC()
   : fInData(NULL), fInData1(NULL),  fInData2(NULL), fInData3(NULL), fInData4(NULL), fOutData(NULL),
   /*fTimingConverterArray(NULL), fChargeConverterArray(NULL),*/
   fChargeConverterArray1(NULL), fChargeConverterArray2(NULL),
   fChargeConverterArray3(NULL), fChargeConverterArray4(NULL),
   fChargeConverterArray5(NULL), fChargeConverterArray6(NULL),
   fChargeConverterArray7(NULL), fChargeConverterArray8(NULL),
   fChargeConverterArray9(NULL), fChargeConverterArray10(NULL),
   fChargeConverterArray11(NULL), fChargeConverterArray12(NULL),
   fChargeConverterArray13(NULL), fChargeConverterArray14(NULL),
   fChargeConverterArray15(NULL), fChargeConverterArray16(NULL),
   fChargeConverterArray17(NULL), fChargeConverterArray18(NULL),
   fChargeConverterArray19(NULL), fChargeConverterArray20(NULL),
   fChargeConverterArray21(NULL), fChargeConverterArray22(NULL),
   fChargeConverterArray23(NULL), fChargeConverterArray24(NULL),
   fChargeConverterArray25(NULL), fChargeConverterArray26(NULL),
   fChargeConverterArray27(NULL), fChargeConverterArray28(NULL),
   fChargeConverterArray29(NULL), fChargeConverterArray30(NULL),
   fChargeConverterArray31(NULL), fChargeConverterArray32(NULL),
   fChargeConverterArray33(NULL), fChargeConverterArray34(NULL),
   fInputHasTiming(kFALSE), fInputHasCharge(kFALSE)
{
   RegisterInputCollection("InputCollection",
			   "array of objects inheriting from art::ITiming and/or art::ICharge",
			   fInputColName,TString("plastic_raw"));
   RegisterInputCollection("InputCollection1","name of sr-ppacS1 1x",
                           fInputColName1,TString("sr11_x"));
   RegisterInputCollection("InputCollection2","name of sr-ppacS1 1y",
                           fInputColName2,TString("sr11_y"));
   RegisterInputCollection("InputCollection3","name of sr-ppacS1 2x",
                           fInputColName3,TString("sr12_x"));
   RegisterInputCollection("InputCollection4","name of sr-ppacS1 2y",
                           fInputColName4,TString("sr12_y"));
   RegisterOutputCollection("OutputCollection","output class will be the same as input",
			    fOutputColName,TString("plastic"));
   //RegisterProcessorParameter("TimingConverterArray",
	//		      "normally output of TAffineConverterArrayGenerator",
	//		      fTimingConverterArrayName,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray1",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName1,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray2",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName2,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray3",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName3,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray4",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName4,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray5",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName5,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray6",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName6,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray7",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName7,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray8",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName8,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray9",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName9,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray10",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName10,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray11",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName11,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray12",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName12,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray13",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName13,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray14",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName14,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray15",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName15,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray16",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName16,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray17",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName17,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray18",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName18,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray19",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName19,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray20",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName20,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray21",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName21,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray22",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName22,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray23",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName23,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray24",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName24,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray25",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName25,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray26",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName26,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray27",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName27,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray28",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName28,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray29",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName29,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray30",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName30,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray31",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName31,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray32",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName32,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray33",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName33,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("ChargeConverterArray34",
			      "normally output of TAffineConverterArrayGenerator",
			      fChargeConverterArrayName34,DEFAULT_CONV_NAME);
   RegisterProcessorParameter("InputIsDigital","whether input is digital or not",
			      fInputIsDigital,kTRUE);
   
}

TTimingChargeCorrectionProcessorIC::~TTimingChargeCorrectionProcessorIC()
{
   delete fOutData;
   //delete fTimingConverterArray;
   delete fChargeConverterArray1;
   delete fChargeConverterArray2;
   delete fChargeConverterArray3;
   delete fChargeConverterArray4;
   delete fChargeConverterArray5;
   delete fChargeConverterArray6;
   delete fChargeConverterArray7;
   delete fChargeConverterArray8;
   delete fChargeConverterArray9;
   delete fChargeConverterArray10;
   delete fChargeConverterArray11;
   delete fChargeConverterArray12;
   delete fChargeConverterArray13;
   delete fChargeConverterArray14;
   delete fChargeConverterArray15;
   delete fChargeConverterArray16;
   delete fChargeConverterArray17;
   delete fChargeConverterArray18;
   delete fChargeConverterArray19;
   delete fChargeConverterArray20;
   delete fChargeConverterArray21;
   delete fChargeConverterArray22;
   delete fChargeConverterArray23;
   delete fChargeConverterArray24;
   delete fChargeConverterArray25;
   delete fChargeConverterArray26;
   delete fChargeConverterArray27;
   delete fChargeConverterArray28;
   delete fChargeConverterArray29;
   delete fChargeConverterArray30;
   delete fChargeConverterArray31;
   delete fChargeConverterArray32;
   delete fChargeConverterArray33;
   delete fChargeConverterArray34;
   
}

void TTimingChargeCorrectionProcessorIC::Init(TEventCollection *col)
{
   Info("Init","%s => %s",fInputColName.Data(),fOutputColName.Data());
   fInData = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName.Data()));
   if (!fInData) {
      SetStateError(TString::Format("input not found: %s",fInputColName.Data()));
      return;
   }
   fInData1 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName1.Data()));
   if (!fInData1) {
      SetStateError(TString::Format("input not found: %s",fInputColName1.Data()));
      return;
   }
   fInData2 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName2.Data()));
   if (!fInData2) {
      SetStateError(TString::Format("input not found: %s",fInputColName2.Data()));
      return;
   }
   fInData3 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName3.Data()));
   if (!fInData3) {
      SetStateError(TString::Format("input not found: %s",fInputColName3.Data()));
      return;
   }
   fInData4 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName4.Data()));
   if (!fInData4) {
      SetStateError(TString::Format("input not found: %s",fInputColName4.Data()));
      return;
   }

   const TClass *const cl = (*fInData)->GetClass();
   fInputHasTiming = cl->InheritsFrom(art::ITiming::Class());
   fInputHasCharge = cl->InheritsFrom(art::ICharge::Class());

   if(!fInputHasTiming && !fInputHasCharge){
      SetStateError("contents of input array must inherit from art::ITiming and/or art::ICharge");
      return;
   }

   //if(fInputHasTiming && fTimingConverterArrayName.CompareTo(DEFAULT_CONV_NAME)) {
   //   TConverterUtil::SetConverterArray(&fTimingConverterArray,fTimingConverterArrayName,col);
   //}

   if(fInputHasCharge && fChargeConverterArrayName1.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray1,fChargeConverterArrayName1,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName2.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray2,fChargeConverterArrayName2,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName3.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray3,fChargeConverterArrayName3,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName4.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray4,fChargeConverterArrayName4,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName5.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray5,fChargeConverterArrayName5,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName6.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray6,fChargeConverterArrayName6,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName7.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray7,fChargeConverterArrayName7,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName8.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray8,fChargeConverterArrayName8,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName9.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray9,fChargeConverterArrayName9,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName10.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray10,fChargeConverterArrayName10,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName11.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray11,fChargeConverterArrayName11,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName12.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray12,fChargeConverterArrayName12,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName13.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray13,fChargeConverterArrayName13,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName14.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray14,fChargeConverterArrayName14,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName15.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray15,fChargeConverterArrayName15,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName16.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray16,fChargeConverterArrayName16,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName17.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray17,fChargeConverterArrayName17,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName18.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray18,fChargeConverterArrayName18,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName19.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray19,fChargeConverterArrayName19,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName20.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray20,fChargeConverterArrayName20,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName21.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray21,fChargeConverterArrayName21,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName22.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray22,fChargeConverterArrayName22,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName23.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray23,fChargeConverterArrayName23,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName24.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray24,fChargeConverterArrayName24,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName25.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray25,fChargeConverterArrayName25,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName26.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray26,fChargeConverterArrayName26,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName27.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray27,fChargeConverterArrayName27,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName28.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray28,fChargeConverterArrayName28,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName29.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray29,fChargeConverterArrayName29,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName30.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray30,fChargeConverterArrayName30,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName31.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray31,fChargeConverterArrayName31,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName32.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray32,fChargeConverterArrayName32,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName33.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray33,fChargeConverterArrayName33,col);
   }
   if(fInputHasCharge && fChargeConverterArrayName34.CompareTo(DEFAULT_CONV_NAME)) {
      TConverterUtil::SetConverterArray(&fChargeConverterArray34,fChargeConverterArrayName34,col);
   }


   if(!fChargeConverterArray1 || !fChargeConverterArray2 ||
      !fChargeConverterArray3 || !fChargeConverterArray4 ||
      !fChargeConverterArray5 || !fChargeConverterArray6 ||
      !fChargeConverterArray7 || !fChargeConverterArray8 ||
      !fChargeConverterArray9 || !fChargeConverterArray10 ||
      !fChargeConverterArray11 || !fChargeConverterArray12 ||
      !fChargeConverterArray13 || !fChargeConverterArray14 ||
      !fChargeConverterArray15 || !fChargeConverterArray16 ||
      !fChargeConverterArray17 || !fChargeConverterArray18 ||
      !fChargeConverterArray19 || !fChargeConverterArray20 ||
      !fChargeConverterArray21 || !fChargeConverterArray22 ||
      !fChargeConverterArray23 || !fChargeConverterArray24 ||
      !fChargeConverterArray25 || !fChargeConverterArray26 ||
      !fChargeConverterArray27 || !fChargeConverterArray28 ||
      !fChargeConverterArray29 || !fChargeConverterArray30 ||
      !fChargeConverterArray31 || !fChargeConverterArray32 ||
      !fChargeConverterArray33 || !fChargeConverterArray34){
      SetStateError("no converter registered.");
      return;
   }

   fOutData = new TClonesArray(cl);
   fOutData->SetName(fOutputColName);
   col->Add(fOutputColName,fOutData,fOutputIsTransparent);
}

void TTimingChargeCorrectionProcessorIC::Process()
{
   fOutData->Clear("C");

   if((*fInData1)->GetEntriesFast()==0 ||
      (*fInData2)->GetEntriesFast()==0 ||
      (*fInData3)->GetEntriesFast()==0 ||
      (*fInData4)->GetEntriesFast()==0
     ) return;

   const art::TSRPPACPlaneData* const sr11x = dynamic_cast<art::TSRPPACPlaneData*>((*fInData1)->At(0));
   const art::TSRPPACPlaneData* const sr11y = dynamic_cast<art::TSRPPACPlaneData*>((*fInData2)->At(0));
   const art::TSRPPACPlaneData* const sr12x = dynamic_cast<art::TSRPPACPlaneData*>((*fInData3)->At(0));
   const art::TSRPPACPlaneData* const sr12y = dynamic_cast<art::TSRPPACPlaneData*>((*fInData4)->At(0));

   Double_t s1_1_x = sr11x->GetPosition();
   Double_t s1_1_y = sr11y->GetPosition();
   Double_t s1_2_x = sr12x->GetPosition();
   Double_t s1_2_y = sr12y->GetPosition();
   Double_t s1a = (s1_2_x - s1_1_x)/350.;
   Double_t s1b = (s1_2_y - s1_1_y)/350.;

   if(isnan(s1a) || isnan(s1b)) return;

   for(Int_t iData = 0, nData = (*fInData)->GetEntriesFast();
       iData != nData; ++iData) {

      const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(iData));
      TObject *const outData = fOutData->ConstructedAt(iData);
      const Int_t detID = inData->GetID();
      if(!IsValid(detID)) continue;
      inData->Copy(*outData);
      //std::cout << "ID" << detID << std::endl;

      Double_t ICz = 778.75+25.25*detID+12.625;
      Double_t ICy = s1_1_y+s1b*ICz*sqrt(1+pow(s1a, 2));

      if(isnan(ICy)) return;

      if (fInputHasTiming) {
	 const ITiming *const inDataT = dynamic_cast<const ITiming*>(inData);
	 const Double_t timing = inDataT->GetTiming() + (fInputIsDigital ? gRandom->Uniform() : 0);
	 //if ( fTimingConverterArray && detID >= (Int_t)fTimingConverterArray->size()) {
	 //   SetStateError(TString::Format("size of TimingConverterArray (%d) is smaller than detID (%d)",(Int_t)fTimingConverterArray->size(), detID));
	 //   return;
	 //}
	 //const Double_t outputT =
	    //fTimingConverterArray ? fTimingConverterArray->at(detID)->Convert(timing) : timing;
    const Double_t outputT = timing;
	 ITiming *const outDataT = dynamic_cast<ITiming*>(outData);
	 outDataT->SetTiming( outputT );
      }

    if (fInputHasCharge) {
      const ICharge *const inDataQ = dynamic_cast<const ICharge*>(inData);
      const Double_t charge = inDataQ->GetCharge() + (fInputIsDigital ? gRandom->Uniform() : 0);
      
      if ( fChargeConverterArray1 && detID >= (Int_t)fChargeConverterArray1->size()) {
         SetStateError(TString::Format("size of ChargeConverterArray (%d) is smaller than detID (%d)",(Int_t)fChargeConverterArray1->size(), detID));
         return;
      }
      

      Double_t outputQ = 0.;
      if(ICy < -80){
          outputQ =
            fChargeConverterArray1 ? fChargeConverterArray1->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -80 && ICy < -75){
          outputQ =
            fChargeConverterArray2 ? fChargeConverterArray2->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -75 && ICy < -70){
          outputQ =
            fChargeConverterArray3 ? fChargeConverterArray3->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -70 && ICy < -65){
          outputQ =
            fChargeConverterArray4 ? fChargeConverterArray4->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -65 && ICy < -60){
          outputQ =
            fChargeConverterArray5 ? fChargeConverterArray5->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -60 && ICy < -55){
          outputQ =
            fChargeConverterArray6 ? fChargeConverterArray6->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -55 && ICy < -50){
          outputQ =
            fChargeConverterArray7 ? fChargeConverterArray7->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -50 && ICy < -45){
          outputQ =
            fChargeConverterArray8 ? fChargeConverterArray8->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -45 && ICy < -40){
          outputQ =
            fChargeConverterArray9 ? fChargeConverterArray9->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -40 && ICy < -35){
          outputQ =
            fChargeConverterArray10 ? fChargeConverterArray10->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -35 && ICy < -30){
          outputQ =
            fChargeConverterArray11 ? fChargeConverterArray11->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -30 && ICy < -25){
          outputQ =
            fChargeConverterArray12 ? fChargeConverterArray12->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -25 && ICy < -20){
          outputQ =
            fChargeConverterArray13 ? fChargeConverterArray13->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -20 && ICy < -15){
          outputQ =
            fChargeConverterArray14 ? fChargeConverterArray14->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -15 && ICy < -10){
          outputQ =
            fChargeConverterArray15 ? fChargeConverterArray15->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -10 && ICy < -5){
          outputQ =
            fChargeConverterArray16 ? fChargeConverterArray16->at(detID)->Convert(charge) : charge;
      }else if(ICy >= -5 && ICy < 0){
          outputQ =
            fChargeConverterArray17 ? fChargeConverterArray17->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 0 && ICy < 5){
          outputQ =
            fChargeConverterArray18 ? fChargeConverterArray18->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 5 && ICy < 10){
          outputQ =
            fChargeConverterArray19 ? fChargeConverterArray19->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 10 && ICy < 15){
          outputQ =
            fChargeConverterArray20 ? fChargeConverterArray20->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 15 && ICy < 20){
          outputQ =
            fChargeConverterArray21 ? fChargeConverterArray21->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 20 && ICy < 25){
          outputQ =
            fChargeConverterArray22 ? fChargeConverterArray22->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 25 && ICy < 30){
          outputQ =
            fChargeConverterArray23 ? fChargeConverterArray23->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 30 && ICy < 35){
          outputQ =
            fChargeConverterArray24 ? fChargeConverterArray24->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 35 && ICy < 40){
          outputQ =
            fChargeConverterArray25 ? fChargeConverterArray25->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 40 && ICy < 45){
          outputQ =
            fChargeConverterArray26 ? fChargeConverterArray26->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 45 && ICy < 50){
          outputQ =
            fChargeConverterArray27 ? fChargeConverterArray27->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 50 && ICy < 55){
          outputQ =
            fChargeConverterArray28 ? fChargeConverterArray28->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 55 && ICy < 60){
          outputQ =
            fChargeConverterArray29 ? fChargeConverterArray29->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 60 && ICy < 65){
          outputQ =
            fChargeConverterArray30 ? fChargeConverterArray30->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 65 && ICy < 70){
          outputQ =
            fChargeConverterArray31 ? fChargeConverterArray31->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 70 && ICy < 75){
          outputQ =
            fChargeConverterArray32 ? fChargeConverterArray32->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 75 && ICy < 80){
          outputQ =
            fChargeConverterArray33 ? fChargeConverterArray33->at(detID)->Convert(charge) : charge;
      }else if(ICy >= 80){
          outputQ =
            fChargeConverterArray34 ? fChargeConverterArray34->at(detID)->Convert(charge) : charge;
      }

      ICharge *const outDataQ = dynamic_cast<ICharge*>(outData);
      outDataQ->SetCharge( outputQ );
    }
   }
}
