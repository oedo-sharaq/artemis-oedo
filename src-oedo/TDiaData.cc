#include "TDiaData.h"

using art::TDiaData;

ClassImp(art::TDiaData);

// Default constructor
TDiaData::TDiaData()
  : fPadTiming(kInvalidD), fIsHitOneStrip(false), fIsHitPad(false), fnHitStrip(0), fIDHitStrip(-1), fTDiffStripPad(kInvalidD), fIsGoodTDiffStripPad(false)
{
   TDiaTimingData::SetID(kInvalidI);    // detID
   TDiaTimingData::SetAuxID(kInvalidI); // hitID
}

TDiaData::~TDiaData() {}

// Copy constructor
TDiaData::TDiaData(const TDiaData& rhs)
   : TDiaTimingData(rhs),
     fPadTiming(rhs.fPadTiming),fIsHitOneStrip(rhs.fIsHitOneStrip),fIsHitPad(rhs.fIsHitPad),fnHitStrip(rhs.fnHitStrip),fIDHitStrip(rhs.fIDHitStrip),fTDiffStripPad(rhs.fTDiffStripPad),
     fIsGoodTDiffStripPad(rhs.fIsGoodTDiffStripPad){}

// Assignment operator
TDiaData& TDiaData::operator=(const TDiaData& rhs) {
   if (this != &rhs) {
      ((TDiaData&)rhs).Copy(*this);
   }
   return *this;
 }

void TDiaData::Copy(TObject& dest) const {
   TDiaTimingData::Copy(dest);
   TDiaData &cobj = *(TDiaData*)&dest;
   cobj.fPadTiming = fPadTiming;
   cobj.fIsHitOneStrip = fIsHitOneStrip;
   cobj.fIsHitPad    = fIsHitPad;
   cobj.fnHitStrip   = fnHitStrip;
   cobj.fIDHitStrip   = fIDHitStrip;
   cobj.fTDiffStripPad = fTDiffStripPad;
   cobj.fIsGoodTDiffStripPad = fIsGoodTDiffStripPad;
}

void TDiaData::Clear(Option_t *opt="") {
   TDiaTimingData::Clear(opt);
   TDiaTimingData::SetID(kInvalidI);
   TDiaTimingData::SetAuxID(kInvalidI);
   fPadTiming = kInvalidD;
   fIsHitOneStrip  = false;
   fIsHitPad       = false;
   fnHitStrip      = 0;
   fIDHitStrip     = -1;
   fTDiffStripPad = kInvalidD;
   fIsGoodTDiffStripPad = false;
}
