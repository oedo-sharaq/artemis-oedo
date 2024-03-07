#include "TMassData.h"

#include "constant.h"

using art::TMassData;

ClassImp(art::TMassData)

// Default constructor
TMassData::TMassData() 
: fZ(kInvalidD), fAq(kInvalidD), 
fTof(kInvalidD), fX(kInvalidD), fEx(kInvalidD)

{
}

TMassData::~TMassData() {}

// Copy constructor
TMassData::TMassData(const TMassData& rhs) 
  : TDataObject(rhs),
 fZ(rhs.fZ),fAq(rhs.fAq),
fTof(rhs.fTof), fX(rhs.fX), fEx(rhs.fEx)
 {
}

// Assignment operator
TMassData& TMassData::operator=(const TMassData& rhs) {
   if (this != &rhs) {
      ((TMassData&)rhs).Copy(*this);
   }
   return *this;
}

void TMassData::Copy(TObject &obj) const {
   TDataObject::Copy(obj);
   TMassData &cobj = (TMassData&)obj;
   cobj.fZ = fZ;
   cobj.fAq = fAq;
   cobj.fTof = fTof;
   cobj.fX = fX;
   cobj.fEx = fEx;
//   cobj.fF3A = fF3A;
//   cobj.fF3Y = fF3Y;
//   cobj.fF3B = fF3B;
}

void TMassData::Clear(Option_t *opt) {
   TDataObject::Clear(opt);
   fZ = kInvalidD;
   fAq = kInvalidD;
   fTof = kInvalidD;
   fX = kInvalidD;
   fEx = kInvalidD;
//   fF3A = kInvalidD;
//   fF3Y = kInvalidD;
//   fF3B = kInvalidD;
}
