//#ifndef INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR
//#define INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR

#include "TProcessor.h"
//#include "TSRPPACParameter.h"
//#include "TSRPPACPlaneData.h"

namespace art {
   class TMassCalibrationConverter;
   class TSRPPACPlaneData;
   class TDssdData;
   class TDiaTimingData;
   class TMassData;
   class TTwoSidedPlasticData;
   
}

class TClonesArray;

class art::TMassCalibrationConverter : public TProcessor {
public:
   TMassCalibrationConverter();
   virtual ~TMassCalibrationConverter();

   TMassCalibrationConverter(const TMassCalibrationConverter& rhs);
   TMassCalibrationConverter& operator=(const TMassCalibrationConverter& rhs);

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

   TString fS0PPACYName; // input name (x)
   TClonesArray **fS0PPACY; //!


   TString fFileName;
   Int_t fOrder;
   Int_t fUnitOri;
   Int_t fUsetwoMWDCs;
   Int_t fUseS0Y;

   TString fTypeName;
   TClonesArray *fParameterArray; //!->

private:

   ClassDef(TMassCalibrationConverter,1) // pid with srppac single plane
};

//#endif // INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR
