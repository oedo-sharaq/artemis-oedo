#ifndef TDIAPadCALIBRATIONPROCESSOR_H
#define TDIAPadCALIBRATIONPROCESSOR_H

#include <TProcessor.h>
#include <vector>

namespace art{
   class TDiaPadCalibrationProcessor;
   class TConverterBase;
   class TMultiHitArray;
}

class art::TDiaPadCalibrationProcessor : public TProcessor {

public:
   TDiaPadCalibrationProcessor();
   virtual ~TDiaPadCalibrationProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString        fInputColName1; //name of input collection of 1st side
   TString        fOutputColName; //name of output collection
   TClonesArray **fDiaPadIn1;    //!input collection of 1st side
   TClonesArray  *fDiaPadOut;    //output collection

   IntVec_t        fDetIDRange;
   Int_t           fNDet;       // number of detectors
   TMultiHitArray *fHits1;

   static const Int_t HITID_ORIGIN = 1;

private:
   // Copy constructor (prohibited)
   TDiaPadCalibrationProcessor(const TDiaPadCalibrationProcessor&);
   // Assignment operator (prohibited)
   TDiaPadCalibrationProcessor& operator=(const TDiaPadCalibrationProcessor&);

   void FillHitArray();

   ClassDef(TDiaPadCalibrationProcessor,0) // processor for two-sided plastic calibration
};

#endif // TDIAPADCALIBRATIONPROCESSOR_H
