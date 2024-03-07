#ifndef INCLUDE_TDIATIMINGSUBTRACTIONPROCESSOR
#define INCLUDE_TDIATIMINGSUBTRACTIONPROCESSOR

#include "TProcessor.h"

namespace art {
   class TDiaTimingSubtractionProcessor;
}

class art::TDiaTimingSubtractionProcessor : public TProcessor {
public:
   TDiaTimingSubtractionProcessor();
   virtual ~TDiaTimingSubtractionProcessor();

   TDiaTimingSubtractionProcessor(const TDiaTimingSubtractionProcessor& rhs);
   TDiaTimingSubtractionProcessor& operator=(const TDiaTimingSubtractionProcessor& rhs);

   virtual void Process();

protected:
   TString fInputColName1;
   TString fInputColName2;
   TString fOutputColName;

   TClonesArray **fInput1; //! input collection
   TClonesArray **fInput2; //! input collection
   TClonesArray  *fOutput; //! output collection

   Double_t fToffset;

private:

   ClassDef(TDiaTimingSubtractionProcessor,1)
};

#endif // INCLUDE_TDIATIMINGSUBTRACTIONPROCESSOR
