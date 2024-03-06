#ifndef TTIMINGCHARGECORRECTIONPROCESSOR_H
#define TTIMINGCHARGECORRECTIONPROCESSOR_H

#include <TProcessor.h>

#include <vector>

namespace art {
   class TTimingChargeCorrectionProcessor;
   class TConverterBase;
}

class TClonesArray;

class art::TTimingChargeCorrectionProcessor : public TProcessor {
public:
   // Default constructor
   TTimingChargeCorrectionProcessor();
   virtual ~TTimingChargeCorrectionProcessor();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString        fInputColNamemain;
   TString        fInputColNamesub;
   TString        fOutputColName;
   TClonesArray **fInDatamain; //!
   TClonesArray **fInDatasub; //!
   TClonesArray  *fOutData; //!

   //TString        fTimingConverterArrayName;
   TString        fChargeConverterArrayName;
   TString        fChargeConverterArrayName0004;
   TString        fChargeConverterArrayName0509;
   TString        fChargeConverterArrayName1014;
   TString        fChargeConverterArrayName1519;
   TString        fChargeConverterArrayName2024;
   TString        fChargeConverterArrayName2529;
   TString        fChargeConverterArrayName3034;
   TString        fChargeConverterArrayName3539;
   TString        fChargeConverterArrayName4044;
   TString        fChargeConverterArrayName4549;
   TString        fChargeConverterArrayName5054;
   TString        fChargeConverterArrayName5559;
   TString        fChargeConverterArrayName6064;
   TString        fChargeConverterArrayName6569;
   TString        fChargeConverterArrayName7074;
   TString        fChargeConverterArrayName7579;
   TString        fChargeConverterArrayName8084;
   TString        fChargeConverterArrayName8589;
   TString        fChargeConverterArrayName9093;

   //std::vector<TConverterBase*> *fTimingConverterArray; //!
   std::vector<TConverterBase*> *fChargeConverterArray; //!
   std::vector<TConverterBase*> *fChargeConverterArray0004; //!
   std::vector<TConverterBase*> *fChargeConverterArray0509; //!
   std::vector<TConverterBase*> *fChargeConverterArray1014; //!
   std::vector<TConverterBase*> *fChargeConverterArray1519; //!
   std::vector<TConverterBase*> *fChargeConverterArray2024; //!
   std::vector<TConverterBase*> *fChargeConverterArray2529; //!
   std::vector<TConverterBase*> *fChargeConverterArray3034; //!
   std::vector<TConverterBase*> *fChargeConverterArray3539; //!
   std::vector<TConverterBase*> *fChargeConverterArray4044; //!
   std::vector<TConverterBase*> *fChargeConverterArray4549; //!
   std::vector<TConverterBase*> *fChargeConverterArray5054; //!
   std::vector<TConverterBase*> *fChargeConverterArray5559; //!
   std::vector<TConverterBase*> *fChargeConverterArray6064; //!
   std::vector<TConverterBase*> *fChargeConverterArray6569; //!
   std::vector<TConverterBase*> *fChargeConverterArray7074; //!
   std::vector<TConverterBase*> *fChargeConverterArray7579; //!
   std::vector<TConverterBase*> *fChargeConverterArray8084; //!
   std::vector<TConverterBase*> *fChargeConverterArray8589; //!
   std::vector<TConverterBase*> *fChargeConverterArray9093; //!
   Bool_t         fInputHasTiming;
   Bool_t         fInputHasCharge;
   Bool_t         fInputIsDigital;

private:
   // Copy constructor (prohibited)
   TTimingChargeCorrectionProcessor(const TTimingChargeCorrectionProcessor& rhs);
   // Assignment operator (prohibited)
   TTimingChargeCorrectionProcessor& operator=(const TTimingChargeCorrectionProcessor& rhs);

   ClassDef(TTimingChargeCorrectionProcessor,0) // processor for calibration of timing and charge data
};

#endif // TTIMINGCHARGECorrectionPROCESSOR_H
