/*
 * @file TReplaceIDProcessor.cc
 * @date  Created : 2021.05.22 JST
 *  Last Modified : 2021.05.22 JST (Ota)
 *--------------------------------------------------------
 *
 *--------------------------------------------------------
 *    Copyright (C) Shinsuke OTA
 */
#include "TReplaceIDProcessor.h"
#include "TDataObject.h"

using art::TReplaceIDProcessor;

ClassImp(TReplaceIDProcessor)


TReplaceIDProcessor::TReplaceIDProcessor() 
{
  Register(fInput("Input","name of input collection (TDataObject)","input"));
}


TReplaceIDProcessor::~TReplaceIDProcessor()
{
}

void TReplaceIDProcessor::Process()
{
  for (int i = 0, n = fInput->GetEntriesFast(); i < n; ++i) {
    TDataObject* data = static_cast<TDataObject*>(fInput->UncheckedAt(i));
    data->SetID(0);
  }

}
