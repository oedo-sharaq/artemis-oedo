#ifndef INCLUDE_TDIASTRIPTIMINGPROCESSOR
#define INCLUDE_TDIASTRIPTIMINGPROCESSOR

#include "TProcessor.h"
#include <vector>

namespace art {
   class TDiaStripTimingProcessor;
}

class art::TDiaStripTimingProcessor : public TProcessor {
public:
   TDiaStripTimingProcessor();
   virtual ~TDiaStripTimingProcessor();

   TDiaStripTimingProcessor(const TDiaStripTimingProcessor& rhs);
   TDiaStripTimingProcessor& operator=(const TDiaStripTimingProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputColName1;
   TString fInputColName2;
   TString fQTCStripLName;
   TString fQTCStripRName;
   TString fOutputColName;


   TClonesArray **fInput1; //! input collection
   TClonesArray **fInput2; //! input collection
   TClonesArray **fQTCStripL; //! input collection
   TClonesArray **fQTCStripR; //! input collection
   TClonesArray  *fOutput; //! output collection

   IntVec_t        fDetIDRange_strip;
   Int_t           fDetID_pad;
   Int_t           fNDet;       // number of detectors

   Int_t fUseTDiffStripPadGate;

   Int_t fMultiStripAnalysis;

   Int_t fUseTDiffStripGate;
   IntVec_t        fTDiffStrip1;
   IntVec_t        fTDiffStrip2;
   IntVec_t        fTDiffStrip3;
   IntVec_t        fTDiffStrip4;
   IntVec_t        fTDiffGateMin;
   IntVec_t        fTDiffGateMax;

   Int_t fUseQGate;
   Float_t fQminStrip1;
   Float_t fQminStrip2;
   Float_t fQminStrip3;
   Float_t fQminStrip4;
   FloatVec_t  fQGateMin;

private:

   ClassDef(TDiaStripTimingProcessor,1)
};

#endif // INCLUDE_TDIASTRIPTIMINGPROCESSOR
