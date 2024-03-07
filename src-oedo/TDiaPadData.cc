#include "TDiaPadData.h"

using art::TDiaPadData;

ClassImp(art::TDiaPadData);

// Default constructor
TDiaPadData::TDiaPadData()
  : fPad(NULL),
    fIsHitPad(false)
{
   TDiaTimingData::SetID(kInvalidI);    // detID
   TDiaTimingData::SetAuxID(kInvalidI); // hitID
}

TDiaPadData::~TDiaPadData() {}

// Copy constructor
TDiaPadData::TDiaPadData(const TDiaPadData& rhs)
   : TDiaTimingData(rhs),
     fPad(rhs.fPad),
     fIsHitPad(rhs.fIsHitPad){}

// Assignment operator
TDiaPadData& TDiaPadData::operator=(const TDiaPadData& rhs) {
   if (this != &rhs) {
      ((TDiaPadData&)rhs).Copy(*this);
   }
   return *this;
 }

void TDiaPadData::Copy(TObject& dest) const {
   TDiaTimingData::Copy(dest);
   TDiaPadData &cobj = *(TDiaPadData*)&dest;
   cobj.fPad  = fPad;
   cobj.fIsHitPad = fIsHitPad;
}

void TDiaPadData::Clear(Option_t *opt="") {
   TDiaTimingData::Clear(opt);
   TDiaTimingData::SetID(kInvalidI);
   TDiaTimingData::SetAuxID(kInvalidI);
   fPad = NULL;
   fIsHitPad  = false;
}

