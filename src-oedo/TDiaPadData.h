#ifndef TDIAPADDATA_H
#define TDIAPADDATA_H

#include "TDiaTimingData.h"
#include "constant.h"

namespace art{
   class TDiaPadData;
   class TDiaTimingData;
}

class art::TDiaPadData : public art::TDiaTimingData {
public:
   // Default constructor
   TDiaPadData();
   virtual ~TDiaPadData();
   // Copy constructor
   TDiaPadData(const TDiaPadData& rhs);
   // Assignment operator
   TDiaPadData& operator=(const TDiaPadData& rhs);

   virtual void Copy(TObject& dest) const;

   Double_t GetT1() const {return fPad->GetTiming();}

   virtual void SetPad(const TDiaTimingData *pad) { fPad = pad; }

   virtual void Clear(Option_t *opt);
//   virtual Int_t Compare(const TObject *obj) const; // inherits TTimingChargeData::Compare


   void InvalidateHit(UInt_t ich) { if (ich < kNumCh) ResetQualityBit(1 << ich); }
   void ValidateHit(UInt_t ich) { if (ich < kNumCh) SetQualityBit(1 << ich); }
   Bool_t HasValidHit(UInt_t ich) const { return ich < kNumCh ? TestQualityBit(1 << ich) : kFALSE; }

   enum EStatusBits { kT1 = 0, kQ1 = 1 };

   void ValidateHitPad() { fIsHitPad=true; }

   Bool_t IsHitPad() const { return fIsHitPad; }

protected:
   const TDiaTimingData *fPad; //->timing data of pad (not owned by this)

   static const Int_t kNumCh = 2; //!

   Bool_t fIsHitPad;

   ClassDef(TDiaPadData,1) // Dia Pad  data container
};

#endif // TDIAPADDATA_H
