#include "TDaliData.h"
#include "TConverterBase.h"

using art::TDaliData;

ClassImp(art::TDaliData)

TDaliData::TDaliData()
: fEnergy1(kInvalidD),fEnergy2(kInvalidD),fTotalE(kInvalidD), fTheta(kInvalidD),fPos1(kInvalidI),fPos2(kInvalidI)
{
   TDataObject::SetID(kInvalidI);
}

TDaliData::~TDaliData() {}

TDaliData::TDaliData(const TDaliData& rhs)
   : TDataObject(rhs),
     fEnergy1(rhs.fEnergy1),
     fEnergy2(rhs.fEnergy2),
     fPos1(rhs.fPos1),
     fPos2(rhs.fPos2),
     fTotalE(rhs.fTotalE),
     fTheta(rhs.fTheta)
{}

TDaliData& TDaliData::operator=(const TDaliData& rhs)
{
   if (this != &rhs) {
      ((TDaliData&)rhs).Copy(*this);
   }
   return *this;
}

void TDaliData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TDaliData &cobj = *(TDaliData*)&dest;
   cobj.fEnergy1 = this->GetEnergy1();
   cobj.fEnergy2 = this->GetEnergy2();
   cobj.fPos1 = this->GetPos1();
   cobj.fPos2 = this->GetPos2();
   cobj.fTotalE = this->GetTotalE();
   cobj.fTheta  = this->GetTheta();
}

void TDaliData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fEnergy1 = kInvalidD;
   fEnergy2 = kInvalidD;
   fPos1 = kInvalidI;
   fPos2 = kInvalidI;
   fTotalE = kInvalidD;
   fTheta  = kInvalidD;
}

