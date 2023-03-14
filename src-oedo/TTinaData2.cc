#include "TTinaData2.h"
#include "TConverterBase.h"

using art::TTinaData2;

ClassImp(art::TTinaData2)

TTinaData2::TTinaData2()
   : fEnergy(kInvalidD), fDeltaE(kInvalidD),
     fTheta(kInvalidD), fPhi(kInvalidD), 
	 fDeid(kInvalidD), fEid(kInvalidD),
    fX(kInvalidD), fY(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TTinaData2::~TTinaData2() {}

TTinaData2::TTinaData2(const TTinaData2& rhs)
   : TDataObject(rhs),
     fEnergy(rhs.fEnergy), fDeltaE(rhs.fDeltaE),
     fTiming(rhs.fTiming),
     fTheta(rhs.fTheta), fPhi(rhs.fPhi),
     fDeid(rhs.fDeid), fEid(rhs.fEid),
     fX(rhs.fX), fY(rhs.fY)
{}

TTinaData2& TTinaData2::operator=(const TTinaData2& rhs)
{
   if (this != &rhs) {
      ((TTinaData2&)rhs).Copy(*this);
   }
   return *this;
}

void TTinaData2::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TTinaData2 &cobj = *(TTinaData2*)&dest;
   cobj.fEnergy = this->GetEnergy();
   cobj.fDeltaE = this->GetDeltaE();
   cobj.fTiming = this->GetTiming();
   cobj.fTheta  = this->GetTheta();
   cobj.fPhi    = this->GetPhi();
   cobj.fDeid   = this->GetDeid();
   cobj.fEid    = this->GetEid();
   cobj.fX      = this->GetX();
   cobj.fY      = this->GetY();
}

void TTinaData2::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fEnergy = kInvalidD;
   fDeltaE = kInvalidD;
   fTiming = kInvalidD;
   fTheta  = kInvalidD;
   fPhi    = kInvalidD;
   fDeid   = kInvalidD;
   fEid    = kInvalidD;
   fX      = kInvalidD;
   fY      = kInvalidD;
}

