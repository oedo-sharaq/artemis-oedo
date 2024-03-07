#ifndef INCLUDE_TDIASTRIPTIMINGEACHMERGETOFFSETPROCESSOR
#define INCLUDE_TDIASTRIPTIMINGEACHMERGETOFFSETPROCESSOR

#include "TProcessor.h"
#include <vector>

namespace art {
   class TDiaStripTimingEachMergeToffsetProcessor;
}

class art::TDiaStripTimingEachMergeToffsetProcessor : public TProcessor {
public:
   TDiaStripTimingEachMergeToffsetProcessor();
   virtual ~TDiaStripTimingEachMergeToffsetProcessor();

   TDiaStripTimingEachMergeToffsetProcessor(const TDiaStripTimingEachMergeToffsetProcessor& rhs);
   TDiaStripTimingEachMergeToffsetProcessor& operator=(const TDiaStripTimingEachMergeToffsetProcessor& rhs);

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
   Int_t              fRunNumber;
   TString fFileName;

   TString fMWDCName; // input name (x)
   TClonesArray **fMWDC; //!


private:

   ClassDef(TDiaStripTimingEachMergeToffsetProcessor,1)
};

#endif // INCLUDE_TDIASTRIPTIMINGEACHMERGETOFFSETPROCESSOR
