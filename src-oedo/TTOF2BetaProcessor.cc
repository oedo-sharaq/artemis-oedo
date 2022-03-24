/**
 * @file   TTOF2BetaProcessor.cc
 * @brief  calculate beta from TOF and flight length
 *
 * @date   Created       : 2016-05-26 18:12:38 JST
 *         Last Modified : 2016-06-01 10:38:32 JST (kawase)
 * @author KAWASE Shoichiro <kawase@aees.kyushu-u.ac.jp>
 *
 *    (C) 2016 KAWASE Shoichiro
 */

#include "TTOF2BetaProcessor.h"

#include <TClonesArray.h>
#include <TMath.h>
#include <TSimpleData.h>
#include <TTimeDifference.h>

using art::TTOF2BetaProcessor;

ClassImp(TTOF2BetaProcessor)

TTOF2BetaProcessor::TTOF2BetaProcessor()
//: fInput(NULL), fOutput(NULL), fFlightLengthMap(NULL), fFlightLength(NULL) {
: fInput(NULL), fOutput(NULL) {
   RegisterInputCollection("Input","name of input collection for TOF",
                           fInputName,TString("tof37"),
			   &fInput,TClonesArray::Class_Name(),
			   art::TTimeDifference::Class_Name());
   RegisterOutputCollection("Output","name of output collection for beta",
                           fOutputName,TString("beta37"),
			   &fOutput,TClonesArray::Class_Name(),
			    art::TSimpleData::Class_Name());
   RegisterProcessorParameter("FlightLength","flight length in mm",
			      fFlightLength,1.f);
//   RegisterInputInfo("FlightLengthMap","name of flight length parameter map",
//		     fFlightLengthMapName, TString("prm:flight_length"),
//		     &fFlightLengthMap,PrmMapFloat_t::Class_Name());
//   RegisterProcessorParameter("FlightLengthKey","key of flight length parameter map",
//			      fFlightLengthKey, TString("f3-f7"));
}


TTOF2BetaProcessor::~TTOF2BetaProcessor()
{
}

void TTOF2BetaProcessor::Init(TEventCollection*)
{
//   fFlightLength = fFlightLengthMap->FindValue(fFlightLengthKey);
//   if (!fFlightLength) {
//      SetStateError(TString::Format("key '%s' not found in the map '%s'.",
//				    fFlightLengthKey.Data(),
//				    fFlightLengthMapName.Data()));
//   }
   printf("Flight Length for %s: %f\n",fOutputName.Data(),fFlightLength);
}

void TTOF2BetaProcessor::Process()
{
   fOutput->Clear("C");

   if ((*fInput)->GetEntriesFast() == 0) {
      return;
   }

   const Double_t tof =
      static_cast<TTimeDifference*>((*fInput)->ConstructedAt(0))->GetTiming();

   const Double_t beta = fFlightLength / (tof * TMath::C()) * 1e+6;
//   const Double_t beta = *fFlightLength / (tof * TMath::C()) * 1e+6;

   TSimpleData *const out = static_cast<TSimpleData*>(fOutput->ConstructedAt(0));

   out->SetValue(beta);
}
