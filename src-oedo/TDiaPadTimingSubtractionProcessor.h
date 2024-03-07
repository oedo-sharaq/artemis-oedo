#ifndef INCLUDE_TDIAPADTIMINGSUBTRACTIONPROCESSOR
#define INCLUDE_TDIAPADTIMINGSUBTRACTIONPROCESSOR

#include "TProcessor.h"

namespace art {
   class TDiaPadTimingSubtractionProcessor;
}

class art::TDiaPadTimingSubtractionProcessor : public TProcessor {
public:
   TDiaPadTimingSubtractionProcessor();
   virtual ~TDiaPadTimingSubtractionProcessor();

   TDiaPadTimingSubtractionProcessor(const TDiaPadTimingSubtractionProcessor& rhs);
   TDiaPadTimingSubtractionProcessor& operator=(const TDiaPadTimingSubtractionProcessor& rhs);

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

   ClassDef(TDiaPadTimingSubtractionProcessor,1)
};

#endif // INCLUDE_TDIAPADTIMINGSUBTRACTIONPROCESSOR
