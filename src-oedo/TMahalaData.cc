#include "TMahalaData.h"

#include "constant.h"

using art::TMahalaData;

ClassImp(art::TMahalaData)

// Default constructor
TMahalaData::TMahalaData() 
: fZ(kInvalidD), fAq(kInvalidD), 
fTof(kInvalidD), fX(kInvalidD), fEx(kInvalidD), fMd(kInvalidD)

{
}

TMahalaData::~TMahalaData() {}

// Copy constructor
TMahalaData::TMahalaData(const TMahalaData& rhs) 
  : TDataObject(rhs),
 fZ(rhs.fZ),fAq(rhs.fAq),
fTof(rhs.fTof), fX(rhs.fX), fEx(rhs.fEx), fMd(rhs.fMd)
 {
}

// Assignment operator
TMahalaData& TMahalaData::operator=(const TMahalaData& rhs) {
   if (this != &rhs) {
      ((TMahalaData&)rhs).Copy(*this);
   }
   return *this;
}

void TMahalaData::Copy(TObject &obj) const {
   TDataObject::Copy(obj);
   TMahalaData &cobj = (TMahalaData&)obj;
   cobj.fZ = fZ;
   cobj.fAq = fAq;
   cobj.fTof = fTof;
   cobj.fX = fX;
   cobj.fEx = fEx;
   cobj.fMd = fMd;
//   cobj.fF3A = fF3A;
//   cobj.fF3Y = fF3Y;
//   cobj.fF3B = fF3B;
}

void TMahalaData::Clear(Option_t *opt) {
   TDataObject::Clear(opt);
   fZ = kInvalidD;
   fAq = kInvalidD;
   fTof = kInvalidD;
   fX = kInvalidD;
   fEx = kInvalidD;
   fMd = kInvalidD;
//   fF3A = kInvalidD;
//   fF3Y = kInvalidD;
//   fF3B = kInvalidD;
}
