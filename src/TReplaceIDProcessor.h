/*
 * @file TReplaceIDProcessor.h
 * @date  Created : 2021.05.22 JST
 *  Last Modified : 2021.05.22 JST (Ota)
 *--------------------------------------------------------
 *
 *--------------------------------------------------------
 *    Copyright (C) Shinsuke OTA
 */
#ifndef TREPLACEIDPROCESSOR_H
#define TREPLACEIDPROCESSOR_H
#include "TProcessor.h"

namespace art {
   class TReplaceIDProcessor;
   class TDataObject;
}

class art::TReplaceIDProcessor  : public TProcessor {
public:
   TReplaceIDProcessor();         // constructor with default id = kID for compatibility
   TReplaceIDProcessor(Int_t id); // constructor with id
   virtual ~TReplaceIDProcessor();
   
   virtual void Process();


protected:
   InputData<TClonesArray,TDataObject> fInput;

   ClassDef(TReplaceIDProcessor,0); // decoder for module AMTTDC
};
#endif // end of #ifdef TMODULEDECODERAMTTDC_H
