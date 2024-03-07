#ifndef TDIASTRIPCALIBRATIONPROCESSOR_H
#define TDIASTRIPCALIBRATIONPROCESSOR_H

#include <TProcessor.h>
#include <vector>

namespace art{
   class TDiaStripCalibrationProcessor;
   class TConverterBase;
   class TMultiHitArray;
   class TEventHeader;
}

class TList;

class art::TDiaStripCalibrationProcessor : public TProcessor {

public:
   TDiaStripCalibrationProcessor();
   virtual ~TDiaStripCalibrationProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString        fInputColName1; //name of input collection of 1st side
   TString        fInputColName2; //name of input collection of 2st side
   TString        fStartTimingColName; //name of input collection of 2st side
   TString        fOutputColName; //name of output collection
   TClonesArray **fDiaStripIn1;    //!input collection of 1st side
   TClonesArray **fDiaStripIn2;    //!input collection of 2nd side
   TClonesArray **fStartTimingData;    //!input collection of 2nd side
   TClonesArray  *fDiaStripOut;    //output collection
   TString fRunHeaderName; // name of runheader
   TList **fRunHeader; //! list of run header
   TString fFileName;

   IntVec_t        fDetIDRange;
   Int_t           fNDet;       // number of detectors
   Int_t fUseTOffset;
   Int_t fRunNumber;
 //  Double_t        fLRPConst;       
   DoubleVec_t        fLRPConst;       
   TMultiHitArray *fHits1;
   TMultiHitArray *fHits2;

   static const Int_t HITID_ORIGIN = 1;

private:
   // Copy constructor (prohibited)
   TDiaStripCalibrationProcessor(const TDiaStripCalibrationProcessor&);
   // Assignment operator (prohibited)
   TDiaStripCalibrationProcessor& operator=(const TDiaStripCalibrationProcessor&);

   void FillHitArray(Int_t);

   ClassDef(TDiaStripCalibrationProcessor,0) // processor for two-sided plastic calibration
};

#endif // TDIASTRIPCALIBRATIONPROCESSOR_H
