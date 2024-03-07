#ifndef INCLUDE_TDIASTRIPTIMINGEACHPROCESSOR
#define INCLUDE_TDIASTRIPTIMINGEACHPROCESSOR

#include "TProcessor.h"
#include <vector>

namespace art {
   class TDiaStripTimingEachProcessor;
}

class art::TDiaStripTimingEachProcessor : public TProcessor {
public:
   TDiaStripTimingEachProcessor();
   virtual ~TDiaStripTimingEachProcessor();

   TDiaStripTimingEachProcessor(const TDiaStripTimingEachProcessor& rhs);
   TDiaStripTimingEachProcessor& operator=(const TDiaStripTimingEachProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputColName1;
   TString fInputColName2;
   TString fQTCStripLName;
   TString fQTCStripRName;
   TString fOutputColName;

   TString fFileName;

   TClonesArray **fInput1; //! input collection
   TClonesArray **fInput2; //! input collection
   TClonesArray **fQTCStripL; //! input collection
   TClonesArray **fQTCStripR; //! input collection
   TClonesArray  *fOutput; //! output collection

   IntVec_t        fDetIDRange_strip;
   Int_t           fDetID_pad;
   Int_t           fNDet;       // number of detectors
   Int_t           fWhID;       // number of detectors

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

   ClassDef(TDiaStripTimingEachProcessor,1)
};

#endif // INCLUDE_TDIASTRIPTIMINGEACHPROCESSOR
