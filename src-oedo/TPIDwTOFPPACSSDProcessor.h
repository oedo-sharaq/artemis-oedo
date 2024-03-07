#ifndef INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR
#define INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR

#include "TProcessor.h"
//#include "TSRPPACParameter.h"
//#include "TSRPPACPlaneData.h"

namespace art {
   class TPIDwTOFPPACSSDProcessor;
   class TSRPPACPlaneData;
   class TDssdData;
   class TDiaTimingData;
   class TMassData;
   class TTwoSidedPlasticData;
   
}

class art::TPIDwTOFPPACSSDProcessor : public TProcessor {
public:
   TPIDwTOFPPACSSDProcessor();
   virtual ~TPIDwTOFPPACSSDProcessor();

   TPIDwTOFPPACSSDProcessor(const TPIDwTOFPPACSSDProcessor& rhs);
   TPIDwTOFPPACSSDProcessor& operator=(const TPIDwTOFPPACSSDProcessor& rhs);

   virtual void Init(TEventCollection *col);

   virtual void Process();

   virtual void CalcZAQ(Double_t t, Double_t x, Double_t Ex, Double_t& z, Double_t& aq);

protected:
   Parameter<Int_t> fDoCheckTimestamp;
   
   TString fOutputName; // tof name
   TClonesArray *fOutput; //!

   TString fTofName; // tof name
   TClonesArray **fTOFs; //!


   TString fS0PPACName; // input name (x)
   TClonesArray **fS0PPAC; //!
   TString fS2SSDName;  // input name (dE)
   TClonesArray **fS2SSD; //!
   TString fS2PLAName;  // input name (dE)
   TClonesArray **fS2PLA; //!

   Int_t fUseChargeDeltaE;
   Int_t fUseZcoin;

   Double_t fDispersion;
   Double_t fBrho0; // two brhos
   Double_t fLength; // two brhos
   Double_t fTofoffset; // two brhos

   

private:

   ClassDef(TPIDwTOFPPACSSDProcessor,1) // pid with srppac single plane
};

#endif // INCLUDE_GUARD_UUID_EB5C7708_88E9_4600_BBED_A3AC03559621_SR
