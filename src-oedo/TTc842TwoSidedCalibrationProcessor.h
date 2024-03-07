#ifndef INCLUDE_TC842TWOSIDEDCALIBRATIONPROCESSOR
#define INCLUDE_TC842TWOSIDEDCALIBRATIONPROCESSOR

#include "TProcessor.h"

namespace art {
   class TTc842TwoSidedCalibrationProcessor;
}

class art::TTc842TwoSidedCalibrationProcessor : public TProcessor {
public:
   TTc842TwoSidedCalibrationProcessor();
   virtual ~TTc842TwoSidedCalibrationProcessor();

   TTc842TwoSidedCalibrationProcessor(const TTc842TwoSidedCalibrationProcessor& rhs);
   TTc842TwoSidedCalibrationProcessor& operator=(const TTc842TwoSidedCalibrationProcessor& rhs);

   virtual void Process();

protected:
   TString fInputColName1;
   TString fInputColName2;
   TString fOutputColName;

   TClonesArray **fInput1; //! input collection
   TClonesArray **fInput2; //! input collection
   TClonesArray  *fOutput; //! output collection


private:

   ClassDef(TTc842TwoSidedCalibrationProcessor,1)
};

#endif // INCLUDE_TTC842TWOSIDEDCALIBRATIONPROCESSOR
