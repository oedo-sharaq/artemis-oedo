#include "TTinaData.h"
#include "TConverterBase.h"

using art::TTinaData;

ClassImp(art::TTinaData)

TTinaData::TTinaData()
   : fEnergy(kInvalidD), fDeltaE(kInvalidD),
     fTheta(kInvalidD), fPhi(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TTinaData::~TTinaData() {}

TTinaData::TTinaData(const TTinaData& rhs)
   : TDataObject(rhs),
     fEnergy(rhs.fEnergy), fDeltaE(rhs.fDeltaE),
     fTheta(rhs.fTheta), fPhi(rhs.fPhi)
{}

TTinaData& TTinaData::operator=(const TTinaData& rhs)
{
   if (this != &rhs) {
      ((TTinaData&)rhs).Copy(*this);
   }
   return *this;
}

void TTinaData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TTinaData &cobj = *(TTinaData*)&dest;
   cobj.fEnergy = this->GetEnergy();
   cobj.fDeltaE = this->GetDeltaE();
   cobj.fTheta  = this->GetTheta();
   cobj.fPhi    = this->GetPhi();
}

void TTinaData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fEnergy = kInvalidD;
   fDeltaE = kInvalidD;
   fTheta  = kInvalidD;
   fPhi    = kInvalidD;
}

