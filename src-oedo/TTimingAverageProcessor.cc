/*
 * @file TTimingAverageProcessor.cc
 * @date  Created : 2021.05.22 JST
 *  Last Modified : 2021.05.22 JST (Ota)
 *--------------------------------------------------------
 *
 *--------------------------------------------------------
 *    Copyright (C) Shinsuke OTA
 */
#include "TTimingAverageProcessor.h"
#include "TDataObject.h"
#include "ITiming.h"

using art::TTimingAverageProcessor;

ClassImp(TTimingAverageProcessor)


TTimingAverageProcessor::TTimingAverageProcessor() 
{
  RegisterInputCollection("InputCollections","names of input collections",fInputName, StringVec_t(0));
  RegisterOutputCollection("OutputCollection","name of output collection",fOutputName,TString(""));
}


TTimingAverageProcessor::~TTimingAverageProcessor()
{
}

void TTimingAverageProcessor::Init(TEventCollection *col)
{
  if (!fInputName.size()) {
    SetStateError(TString::Format("At least one input is required"));
    return;
  }

  for (int i = 0, n = fInputName.size(); i < n; ++i) {
    TClonesArray** array = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName[i].Data()));    
    if (!array) {
      SetStateError(TString::Format("Input collection not found: %s",fInputName[i].Data()));
      return;
    }
    if (!(*array)->GetClass()->InheritsFrom(ITiming::Class())) {
      SetStateError(TString::Format("Input collection does not inherits from ITiming"));
      return;
    }
    fInput.push_back(array);
  }

  fOutput = new TClonesArray((*fInput[0])->GetClass());
  col->Add(fOutputName,fOutput,fOutputIsTransparent);
}

void TTimingAverageProcessor::Process()
{
  fOutput->Clear("C");

  Double_t tsum = 0;
  Int_t nTotalHits = 0;
  for (int iIn = 0, nIn = fInputName.size(); iIn < nIn; ++iIn) {
    Int_t nHits = (*fInput[iIn])->GetEntriesFast();
    if (nHits == 0) return;
    nTotalHits += 1;
    //    for (int iHit = 0; iHit < nHits; ++iHit) {
    ITiming *timingData = dynamic_cast<ITiming*>((*fInput[iIn])->UncheckedAt(0));
    tsum += timingData->GetTiming();
      // }
  }
  
  ITiming *timing = dynamic_cast<ITiming*>(fOutput->ConstructedAt(0));
  TDataObject *obj = dynamic_cast<TDataObject*>(timing);
  obj->SetID(0);
  timing->SetTiming(tsum/nTotalHits);
}
