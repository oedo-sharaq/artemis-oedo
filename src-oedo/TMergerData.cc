#include "TMergerData.h"
#include "TConverterBase.h"

using art::TMergerData;

ClassImp(art::TMergerData)

Int_t TMergerData::fSortType  = TMergerData::kID;
Int_t TMergerData::fSortOrder = TMergerData::kDESC;

TMergerData::TMergerData()
   : fTimestamp(kInvalidI), fS2z(kInvalidD), fS2aq(kInvalidD), fVeto_tave(kInvalidD), fVeto_qave(kInvalidD)
//     fdias2t(kInvalidD), fdia3t(kInvalidD), fS2x(kInvalidD), fS2ssde(kInvalidD)
{
   TDataObject::SetID(kInvalidI);
}

TMergerData::~TMergerData() {}

TMergerData::TMergerData(const TMergerData& rhs)
   : TDataObject(rhs),
     fTimestamp(rhs.fTimestamp), fS2z(rhs.fS2z), fS2aq(rhs.fS2aq), fVeto_tave(rhs.fVeto_tave), fVeto_qave(rhs.fVeto_qave) 
//     fdias2t(rhs.fdias2t), fdia3t(rhs.fdia3t), fS2x(rhs.fS2x), fS2ssde(rhs.fS2ssde)
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
   cobj.fS2z = this->GetS2z();
   cobj.fS2aq = this->GetS2aq();
   cobj.fVeto_tave = this->GetVeto_tave();
   cobj.fVeto_qave = this->GetVeto_qave();
//   cobj.fdias2t = this->Getdias2t();
//   cobj.fdia3t = this->Getdia3t();
//   cobj.fS2x = this->GetS2x();
//   cobj.fS2ssde = this->GetS2ssde();
}

void TMergerData::Clear(Option_t *opt)
{
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   fTimestamp = kInvalidI;
   fS2z = kInvalidD;
   fS2aq = kInvalidD;
   fVeto_tave = kInvalidD;
   fVeto_qave = kInvalidD;
//   fdias2t = kInvalidD;
//   fdia3t = kInvalidD;
//   fS2x = kInvalidD;
//   fS2ssde = kInvalidD;
}

