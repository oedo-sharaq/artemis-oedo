#ifndef TDIASTRIPDATA_H
#define TDIASTRIPDATA_H

#include "TDiaTimingData.h"
#include "constant.h"

namespace art{
   class TDiaStripData;
   class TDiaTimingData;
}

class art::TDiaStripData : public art::TDiaTimingData {
public:
   // Default constructor
   TDiaStripData();
   virtual ~TDiaStripData();
   // Copy constructor
   TDiaStripData(const TDiaStripData& rhs);
   // Assignment operator
   TDiaStripData& operator=(const TDiaStripData& rhs);

   virtual void Copy(TObject& dest) const;

   Double_t GetT1() const { return fSide1->GetTiming(); };
   Double_t GetT2() const { return fSide2->GetTiming(); };

   virtual void SetSide1(const TDiaTimingData *side1) { fSide1 = side1; }
   virtual void SetSide2(const TDiaTimingData *side2) { fSide2 = side2; }
   virtual const TDiaTimingData* GetSide1() const { return fSide1; }
   virtual const TDiaTimingData* GetSide2() const { return fSide2; }

   Double_t GetTAve() const {return GetTiming();}

   virtual void SetTDiff(Double_t val) {fTDiff = val;}
   Double_t GetTDiff() const {return fTDiff;}

   virtual void Clear(Option_t *opt);
//   virtual Int_t Compare(const TObject *obj) const; // inherits TTimingChargeData::Compare

   void InvalidateHit(UInt_t ich) { if (ich < kNumCh) ResetQualityBit(1 << ich); }
   void ValidateHit(UInt_t ich) { if (ich < kNumCh) SetQualityBit(1 << ich); }
   Bool_t HasValidHit(UInt_t ich) const { return ich < kNumCh ? TestQualityBit(1 << ich) : kFALSE; }

   enum EStatusBits { kT1 = 0, kQ1 = 1, kT2 = 2, kQ2 = 3 };

   void ValidateHitStripL() { fIsHitStripL=true; }
   void ValidateHitStripR() { fIsHitStripR=true; }
   void ValidateHitStrip() { fIsHitStrip=true; }

   Bool_t IsHitStripL() const { return fIsHitStripL; }
   Bool_t IsHitStripR() const { return fIsHitStripR; }
   Bool_t IsHitStrip() const { return fIsHitStrip; }

protected:
   Double_t fTDiff; //time difference between two sides

   const TDiaTimingData *fSide1; //->timing data of 1st side (not owned by this)
   const TDiaTimingData *fSide2; //->timing data of 2nd side (not owned by this)

   static const Int_t kNumCh = 4; //!

   Bool_t fIsHitStripL;
   Bool_t fIsHitStripR;
   Bool_t fIsHitStrip;

   ClassDef(TDiaStripData,1) // Dia Strip  data container
};

#endif // TDIASTRIPDATA_H
