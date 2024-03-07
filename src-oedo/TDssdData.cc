#include "TDssdData.h"
#include "TConverterBase.h"

using art::TDssdData;

ClassImp(art::TDssdData)

TDssdData::TDssdData()
   : fEx(kInvalidD), fXID(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TDssdData::~TDssdData() {}

TDssdData::TDssdData(const TDssdData& rhs)
   : TDataObject(rhs),
     fEx(rhs.fEx), 
     fXID(rhs.fXID)
{}

TDssdData& TDssdData::operator=(const TDssdData& rhs)
{
   if (this != &rhs) {
      ((TDssdData&)rhs).Copy(*this);
   }
   return *this;
}

void TDssdData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TDssdData &cobj = *(TDssdData*)&dest;
   cobj.fEx = this->GetEx();
   cobj.fXID  = this->GetXID();
}

void TDssdData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fEx = kInvalidD;
   fXID = kInvalidD;
}

