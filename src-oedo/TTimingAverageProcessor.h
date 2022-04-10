/*
 * @file TTimingAverageProcessor.h
 * @date  Created : 2021.05.22 JST
 *  Last Modified : 2021.05.22 JST (Ota)
 *--------------------------------------------------------
 *
 *--------------------------------------------------------
 *    Copyright (C) Shinsuke OTA
 */
#ifndef TTIMINGAVERAGEPROCESSOR_H
#define TTIMINGAVERAGEPROCESSOR_H
#include "TProcessor.h"

namespace art {
   class TTimingAverageProcessor;
   class TDataObject;
}

class art::TTimingAverageProcessor  : public TProcessor {
public:
   TTimingAverageProcessor();         // constructor with default id = kID for compatibility

   virtual ~TTimingAverageProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();


protected:
   StringVec_t fInputName;
   std::vector<TClonesArray**> fInput;

   TString fOutputName;
   TClonesArray *fOutput;

   ClassDef(TTimingAverageProcessor,0); // decoder for module AMTTDC
};
#endif // end of #ifdef TMODULEDECODERAMTTDC_H
