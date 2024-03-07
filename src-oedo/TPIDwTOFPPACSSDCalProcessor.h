#include "TProcessor.h"
//#include "TSRPPACParameter.h"
//#include "TSRPPACPlaneData.h"

namespace art {
   class TPIDwTOFPPACSSDCalProcessor;
   class TSRPPACPlaneData;
   class TDssdData;
   class TDiaTimingData;
   class TMassData;
   class TTwoSidedPlasticData;
   
}

class art::TPIDwTOFPPACSSDCalProcessor : public TProcessor {
public:
   TPIDwTOFPPACSSDCalProcessor();
   virtual ~TPIDwTOFPPACSSDCalProcessor();

   TPIDwTOFPPACSSDCalProcessor(const TPIDwTOFPPACSSDCalProcessor& rhs);
   TPIDwTOFPPACSSDCalProcessor& operator=(const TPIDwTOFPPACSSDCalProcessor& rhs);

   virtual void Init(TEventCollection *col);

   virtual void Process();

   virtual void CalcZAQ(Double_t t, Double_t x, Double_t Ex_ssd, Double_t Ex_pla, Double_t& z, Double_t& aq);

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
   Int_t fUseMaxZ;

   Double_t fDispersion;
   Double_t fBrho0; // two brhos
   Double_t fLength; // two brhos
   Double_t fTofoffset; // two brhos

   

private:

   ClassDef(TPIDwTOFPPACSSDCalProcessor,1) // pid with srppac single plane
};

