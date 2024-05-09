/**
 * @file   TSRPPACPlaneDqdxProcessor.cc
 * @brief  sr-ppac plane processor with dqdx
 *
 * @date   Created       : 2019-08-30 19:38:25 JST
 *         Last Modified :
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2019 Shinsuke OTA
 */

#include "TSRPPACPlaneQ1Q2Q0Q2Processor.h"
#include "TMonotoneTableConverter.h"
#include "TMath.h"

using art::TSRPPACPlaneQ1Q2Q0Q2Processor;

ClassImp(TSRPPACPlaneQ1Q2Q0Q2Processor)

TSRPPACPlaneQ1Q2Q0Q2Processor::TSRPPACPlaneQ1Q2Q0Q2Processor()
{

   RegisterProcessorParameter("nStrip", "Number of strip",fNStrip,(Int_t)0);
   RegisterProcessorParameter("stripWidth", "strip width (mm)", fStripWidth, (Double_t)0.);
   RegisterProcessorParameter("center", "center of ID", fCenter,(Double_t)0.);
   RegisterProcessorParameter("detoffset", "detector offset", fDetOffset, (Double_t)0.);
   RegisterProcessorParameter("z", "z postion from a focul plane (mm)", fZ, (Double_t)0.);
   RegisterProcessorParameter("turned","1: detector is turned", fTurned, (Bool_t)kFALSE);
}

TSRPPACPlaneQ1Q2Q0Q2Processor::~TSRPPACPlaneQ1Q2Q0Q2Processor()
{
}

void TSRPPACPlaneQ1Q2Q0Q2Processor::Process()
{
   (fOutput)->Clear("C");
   if ((*fInput)->GetEntriesFast() < 2) return;

   double pos = 0.;
   double c0 = 0.;
   double c1 = 0.;
   double c2 = 0.;
   int id0 = 0;
   int id1 = 0;
   int id2 = 0;
   TTimingChargeData* inData0;   
   TTimingChargeData* inData1;   
   TTimingChargeData* inData2;  

// make suer id1 and id2 are next to id0
//

   if ((*fInput)->GetEntriesFast() > 1) {
      inData0 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(0));
      inData1 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(1));
      inData2 = static_cast<TTimingChargeData*>((*fInput)->UncheckedAt(2));
      id0 = inData0->GetID();
      id1 = inData1->GetID();
      id2 = inData2->GetID();
      c0 = inData0->GetCharge();
      c1 = inData1->GetCharge();
      c2 = inData2->GetCharge();
	  if (id1+id2 - 2*id0 != 0) return; // confirm id order
      if (TMath::IsNaN(c0) || TMath::IsNaN(c1) || TMath::IsNaN(c2)) return;
      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter +  (c1 - c2)/(c0 - c2) * ( id0 < id1 ? 1 : -1) * 0.5) * fStripWidth  - fDetOffset);
    } else {
         return;
      }

   TSRPPACPlaneData *outData = static_cast<TSRPPACPlaneData*>(fOutput->ConstructedAt(0));
   outData->SetID(id0);
   outData->SetCharge(c0);
   outData->SetPosition(pos);
   outData->SetProcessed(kTRUE);
 

}

