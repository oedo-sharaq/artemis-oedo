
#include "TProcessor.h"

namespace art {
   class TMahalanobisDistanceTinc;
   class TSRPPACPlaneData;
   class TDssdData;
   class TDiaTimingData;
   class TMahalaData;
   class TTwoSidedPlasticData;
   
}

class TClonesArray;

class art::TMahalanobisDistanceTinc : public TProcessor {
public:
   TMahalanobisDistanceTinc();
   virtual ~TMahalanobisDistanceTinc();

   TMahalanobisDistanceTinc(const TMahalanobisDistanceTinc& rhs);
   TMahalanobisDistanceTinc& operator=(const TMahalanobisDistanceTinc& rhs);

   virtual void Init(TEventCollection *col);

   virtual void Process();

//virtual void MassCalibrationMatrix3rd(Double_t Rd, Double_t t, Double_t x3, Double_t a3, Double_t y3, Double_t b3, Double_t x0);
   
protected:
   Parameter<Int_t> fDoCheckTimestamp;
   
   TString fOutputName; // tof name
   TClonesArray *fOutput; //!

   TString fTofName; // tof name
   TClonesArray **fTOFs; //!

   TString fS0PPACName; // input name (x)
   TClonesArray **fS0PPAC; //!

   TString fMWDC1Name; // input name (x)
   TClonesArray **fMWDC1; //!

   TString fMWDC2Name; // input name (x)
   TClonesArray **fMWDC2; //!


   TString fFileName;
   Int_t fUnitOri;

   TString fTypeName;
   TClonesArray *fParameterArray; //!->

private:

   ClassDef(TMahalanobisDistanceTinc,1) // pid with srppac single plane
};


