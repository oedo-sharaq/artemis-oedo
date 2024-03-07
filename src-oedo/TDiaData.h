#ifndef TDIADATA_H
#define TDIADATA_H

#include "TDiaTimingData.h"
#include "constant.h"

namespace art{
   class TDiaData;
   class TDiaTimingData;
}

class art::TDiaData : public art::TDiaTimingData {
public:
   // Default constructor
   TDiaData();
   virtual ~TDiaData();
   // Copy constructor
   TDiaData(const TDiaData& rhs);
   // Assignment operator
   TDiaData& operator=(const TDiaData& rhs);

   virtual void Copy(TObject& dest) const;

   virtual void Clear(Option_t *opt);

   virtual void SetIDHitStrip(Int_t val) { fIDHitStrip = val; }
   Int_t GetIDHitStrip() const { return fIDHitStrip; }

   virtual void SetnHitStrip(Int_t val) { fnHitStrip = val; }

   virtual void SetPadTiming(Double_t val) { fPadTiming = val; }
   Double_t GetPadTiming() const { return fPadTiming; }

   virtual void SetTDiffStripPad(Double_t val) { fTDiffStripPad = val; }
   Double_t GetTDiffStripPadTiming() const { return fTDiffStripPad; }

   virtual void ValidatePadHit() { fIsHitPad = true; }
   virtual void ValidateOneStripHit() { fIsHitOneStrip = true; }

   virtual void ValidateGoodTDiffStripPad() { fIsGoodTDiffStripPad = true; }
   Bool_t  IsGoodTDiffStripPad() const { return fIsGoodTDiffStripPad; }

protected:
   Double_t fPadTiming;
   Bool_t fIsHitOneStrip;
   Bool_t fIsHitPad;
   Int_t  fnHitStrip;
   Int_t  fIDHitStrip;
   Double_t fTDiffStripPad;
   Bool_t fIsGoodTDiffStripPad;

   ClassDef(TDiaData,1) // Dia data container
};

#endif // TDIADATA_H
