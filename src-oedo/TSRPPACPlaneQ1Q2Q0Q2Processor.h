/*
 * @file   TSRPPACPlaneDqdxProcessor.h
 * @brief  divide SRPPAC TimingChargeData into collection for each plane
 *
 * @date   Created:       2019-08-30 19:28:42 JST (ota)
 *         Last Modified: 2019-08-30 20:18:10 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2019 Shinsuke OTA
 */

#ifndef TSRPPACPLANEQ1Q2Q0Q2PROCESSOR_H
#define TSRPPACPLANEQ1Q2Q0Q2PROCESSOR_H

#include <TProcessor.h>
#include "TSRPPACPlaneProcessor.h"

#include <vector>

namespace art {
   class TSRPPACPlaneQ1Q2Q0Q2Processor;
   class TConverterBase;
}

class TClonesArray;

class art::TSRPPACPlaneQ1Q2Q0Q2Processor : public TSRPPACPlaneProcessor {
public:
   // Default constructor
   TSRPPACPlaneQ1Q2Q0Q2Processor();
   virtual ~TSRPPACPlaneQ1Q2Q0Q2Processor();

   virtual void Process();

protected:
   TConverterBase** fConverter; // converter
   TString	         fConverterName;    // name of dq-to-length converter
   Int_t fCombination;

   ClassDef(TSRPPACPlaneQ1Q2Q0Q2Processor,0) // processor for SRPPAC plane division
};

#endif // TSRPPACPLANEQ1Q2Q0Q2PROCESSOR_H
