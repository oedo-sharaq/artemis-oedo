#include "TDiaStripData.h"

using art::TDiaStripData;

ClassImp(art::TDiaStripData);

// Default constructor
TDiaStripData::TDiaStripData()
   : fTDiff(kInvalidD),
     fSide1(NULL), fSide2(NULL),
     fIsHitStripL(false),fIsHitStripR(false),fIsHitStrip(false)
{
   TDiaTimingData::SetID(kInvalidI);    // detID
   TDiaTimingData::SetAuxID(kInvalidI); // hitID
}

TDiaStripData::~TDiaStripData() {}

// Copy constructor
TDiaStripData::TDiaStripData(const TDiaStripData& rhs)
   : TDiaTimingData(rhs),
     fTDiff(rhs.fTiming),
     fSide1(rhs.fSide1), fSide2(rhs.fSide2),
     fIsHitStripL(rhs.fIsHitStripL),fIsHitStripR(rhs.fIsHitStripR),fIsHitStrip(rhs.fIsHitStrip){}

// Assignment operator
TDiaStripData& TDiaStripData::operator=(const TDiaStripData& rhs) {
   if (this != &rhs) {
      ((TDiaStripData&)rhs).Copy(*this);
   }
   return *this;
 }

void TDiaStripData::Copy(TObject& dest) const {
   TDiaTimingData::Copy(dest);
   TDiaStripData &cobj = *(TDiaStripData*)&dest;
   cobj.fTDiff  = fTDiff;
   cobj.fSide1  = fSide1;
   cobj.fSide2  = fSide2;
   cobj.fIsHitStripL = fIsHitStripL;
   cobj.fIsHitStripR = fIsHitStripR;
   cobj.fIsHitStrip = fIsHitStrip;
}

void TDiaStripData::Clear(Option_t *opt="") {
   TDiaTimingData::Clear(opt);
   TDiaTimingData::SetID(kInvalidI);
   TDiaTimingData::SetAuxID(kInvalidI);
   fTDiff  = kInvalidD;
   fSide1 = NULL;
   fSide2 = NULL;
   fIsHitStripL = false;
   fIsHitStripR = false;
   fIsHitStrip  = false;
}

