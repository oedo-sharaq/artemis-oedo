

#ifndef TTIMINGCHARGECORRECTIONPROCESSORIC_H
#define TTIMINGCHARGECORRECTIONPROCESSORIC_H

#include <TProcessor.h>

#include <vector>

namespace art {
   class TTimingChargeCorrectionProcessorIC;
   class TConverterBase;
}

class TClonesArray;

class art::TTimingChargeCorrectionProcessorIC : public TProcessor {
public:
   // Default constructor
   TTimingChargeCorrectionProcessorIC();
   virtual ~TTimingChargeCorrectionProcessorIC();

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString        fInputColName;
   TString        fInputColName1;
   TString        fInputColName2;
   TString        fInputColName3;
   TString        fInputColName4;
   TString        fOutputColName;
   TClonesArray **fInData; //!
   TClonesArray **fInData1; //!
   TClonesArray **fInData2; //!
   TClonesArray **fInData3; //!
   TClonesArray **fInData4; //!
   TClonesArray  *fOutData; //!

   //TString        fTimingConverterArrayName;
   TString        fChargeConverterArrayName1;
   TString        fChargeConverterArrayName2;
   TString        fChargeConverterArrayName3;
   TString        fChargeConverterArrayName4;
   TString        fChargeConverterArrayName5;
   TString        fChargeConverterArrayName6;
   TString        fChargeConverterArrayName7;
   TString        fChargeConverterArrayName8;
   TString        fChargeConverterArrayName9;
   TString        fChargeConverterArrayName10;
   TString        fChargeConverterArrayName11;
   TString        fChargeConverterArrayName12;
   TString        fChargeConverterArrayName13;
   TString        fChargeConverterArrayName14;
   TString        fChargeConverterArrayName15;
   TString        fChargeConverterArrayName16;
   TString        fChargeConverterArrayName17;
   TString        fChargeConverterArrayName18;
   TString        fChargeConverterArrayName19;
   TString        fChargeConverterArrayName20;
   TString        fChargeConverterArrayName21;
   TString        fChargeConverterArrayName22;
   TString        fChargeConverterArrayName23;
   TString        fChargeConverterArrayName24;
   TString        fChargeConverterArrayName25;
   TString        fChargeConverterArrayName26;
   TString        fChargeConverterArrayName27;
   TString        fChargeConverterArrayName28;
   TString        fChargeConverterArrayName29;
   TString        fChargeConverterArrayName30;
   TString        fChargeConverterArrayName31;
   TString        fChargeConverterArrayName32;
   TString        fChargeConverterArrayName33;
   TString        fChargeConverterArrayName34;


   //std::vector<TConverterBase*> *fTimingConverterArray; //!
   std::vector<TConverterBase*> *fChargeConverterArray1; //!
   std::vector<TConverterBase*> *fChargeConverterArray2; //!
   std::vector<TConverterBase*> *fChargeConverterArray3; //!
   std::vector<TConverterBase*> *fChargeConverterArray4; //!
   std::vector<TConverterBase*> *fChargeConverterArray5; //!
   std::vector<TConverterBase*> *fChargeConverterArray6; //!
   std::vector<TConverterBase*> *fChargeConverterArray7; //!
   std::vector<TConverterBase*> *fChargeConverterArray8; //!
   std::vector<TConverterBase*> *fChargeConverterArray9; //!
   std::vector<TConverterBase*> *fChargeConverterArray10; //!
   std::vector<TConverterBase*> *fChargeConverterArray11; //!
   std::vector<TConverterBase*> *fChargeConverterArray12; //!
   std::vector<TConverterBase*> *fChargeConverterArray13; //!
   std::vector<TConverterBase*> *fChargeConverterArray14; //!
   std::vector<TConverterBase*> *fChargeConverterArray15; //!
   std::vector<TConverterBase*> *fChargeConverterArray16; //!
   std::vector<TConverterBase*> *fChargeConverterArray17; //!
   std::vector<TConverterBase*> *fChargeConverterArray18; //!
   std::vector<TConverterBase*> *fChargeConverterArray19; //!
   std::vector<TConverterBase*> *fChargeConverterArray20; //!
   std::vector<TConverterBase*> *fChargeConverterArray21; //!
   std::vector<TConverterBase*> *fChargeConverterArray22; //!
   std::vector<TConverterBase*> *fChargeConverterArray23; //!
   std::vector<TConverterBase*> *fChargeConverterArray24; //!
   std::vector<TConverterBase*> *fChargeConverterArray25; //!
   std::vector<TConverterBase*> *fChargeConverterArray26; //!
   std::vector<TConverterBase*> *fChargeConverterArray27; //!
   std::vector<TConverterBase*> *fChargeConverterArray28; //!
   std::vector<TConverterBase*> *fChargeConverterArray29; //!
   std::vector<TConverterBase*> *fChargeConverterArray30; //!
   std::vector<TConverterBase*> *fChargeConverterArray31; //!
   std::vector<TConverterBase*> *fChargeConverterArray32; //!
   std::vector<TConverterBase*> *fChargeConverterArray33; //!
   std::vector<TConverterBase*> *fChargeConverterArray34; //!
   Bool_t         fInputHasTiming;
   Bool_t         fInputHasCharge;
   Bool_t         fInputIsDigital;

private:
   // Copy constructor (prohibited)
   TTimingChargeCorrectionProcessorIC(const TTimingChargeCorrectionProcessorIC& rhs);
   // Assignment operator (prohibited)
   TTimingChargeCorrectionProcessorIC& operator=(const TTimingChargeCorrectionProcessorIC& rhs);

   ClassDef(TTimingChargeCorrectionProcessorIC,0) // processor for calibration of timing and charge data
};

#endif // TTIMINGCHARGECorrectionPROCESSORIC_H
