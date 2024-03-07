#include "TMergerData.h"
#include "TConverterBase.h"

using art::TMergerData;

ClassImp(art::TMergerData)

Int_t TMergerData::fSortType  = TMergerData::kID;
Int_t TMergerData::fSortOrder = TMergerData::kDESC;

TMergerData::TMergerData()
   : fTimestamp(kInvalidI), fTestdata(kInvalidI) //add object below?
{
   TDataObject::SetID(kInvalidI);
}

TMergerData::~TMergerData() {}

TMergerData::TMergerData(const TMergerData& rhs)
   : TDataObject(rhs),
     fTimestamp(rhs.fTimestamp), fTestdata(rhs.fTestdata) //add object below?
{}

TMergerData& TMergerData::operator=(const TMergerData& rhs)
{
   if (this != &rhs) {
      ((TMergerData&)rhs).Copy(*this);
   }
   return *this;
}

void TMergerData::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TMergerData &cobj = *(TMergerData*)&dest;
   cobj.fTimestamp = this->GetTimestamp();
   cobj.fTestdata = this->GetTestdata();
   //add object below?
}

void TMergerData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fTimestamp = kInvalidI;
   fTestdata = kInvalidI;
   //add object below?
   //fTiming = kInvalidD;
}

