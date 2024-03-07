#ifndef INCLUDE_TDIASTRIPTIMINGEACHMERGEPROCESSOR
#define INCLUDE_TDIASTRIPTIMINGEACHMERGEPROCESSOR

#include "TProcessor.h"
#include <vector>

namespace art {
   class TDiaStripTimingEachMergeProcessor;
}

class art::TDiaStripTimingEachMergeProcessor : public TProcessor {
public:
   TDiaStripTimingEachMergeProcessor();
   virtual ~TDiaStripTimingEachMergeProcessor();

   TDiaStripTimingEachMergeProcessor(const TDiaStripTimingEachMergeProcessor& rhs);
   TDiaStripTimingEachMergeProcessor& operator=(const TDiaStripTimingEachMergeProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputColName1;
   TString fInputColName2;
//   TString fInputColName3;
   TString fOutputColName;

   TClonesArray **fInput1; //! input collection
   TClonesArray **fInput2; //! input collection
//   TClonesArray **fInput3; //! input collection
   TClonesArray  *fOutput; //! output collection

   DoubleVec_t        fTimeValidRange;
   DoubleVec_t        fToffset;
   Int_t              fUseYvalid;

   TString fMWDCName; // input name (x)
   TClonesArray **fMWDC; //!


private:

   ClassDef(TDiaStripTimingEachMergeProcessor,1)
};

#endif // INCLUDE_TDIASTRIPTIMINGEACHMERGEPROCESSOR
