#include "TTinaData3.h"
#include "TConverterBase.h"

using art::TTinaData3;

ClassImp(art::TTinaData3)

TTinaData3::TTinaData3()
   : fEnergy(kInvalidD), fDeltaE(kInvalidD),
     fTheta(kInvalidD), fPhi(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TTinaData3::~TTinaData3() {}

TTinaData3::TTinaData3(const TTinaData3& rhs)
   : TDataObject(rhs),
     fEnergy(rhs.fEnergy), fDeltaE(rhs.fDeltaE),
     fTheta(rhs.fTheta), fPhi(rhs.fPhi)
{}

TTinaData3& TTinaData3::operator=(const TTinaData3& rhs)
{
   if (this != &rhs) {
      ((TTinaData3&)rhs).Copy(*this);
   }
   return *this;
}

void TTinaData3::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TTinaData3 &cobj = *(TTinaData3*)&dest;
   cobj.fEnergy = this->GetEnergy();
   cobj.fDeltaE = this->GetDeltaE();
   cobj.fTheta  = this->GetTheta();
   cobj.fPhi    = this->GetPhi();
}

void TTinaData3::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fEnergy = kInvalidD;
   fDeltaE = kInvalidD;
   fTheta  = kInvalidD;
   fPhi    = kInvalidD;
}

