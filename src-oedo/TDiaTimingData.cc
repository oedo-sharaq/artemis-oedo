#include "TDiaTimingData.h"
#include "constant.h"

#include <iostream>

#include <TClass.h>

using art::TDiaTimingData;

ClassImp(art::TDiaTimingData)

Int_t TDiaTimingData::fSortType  = TDiaTimingData::kID;
Int_t TDiaTimingData::fSortOrder = TDiaTimingData::kASC;

// Default constructor
TDiaTimingData::TDiaTimingData() 
   : fTiming(kInvalidD) {
   this->SetID(kInvalidI);
}

TDiaTimingData::~TDiaTimingData() {
}

// Copy constructor
TDiaTimingData::TDiaTimingData(const TDiaTimingData& rhs) 
   : TDataObject(rhs), fTiming(rhs.fTiming) {
}

// Assignment operator
TDiaTimingData& TDiaTimingData::operator=(const TDiaTimingData& rhs) {
   if (this != &rhs) {
      rhs.Copy(*this);
   }
   return *this;
}

void TDiaTimingData::Clear(Option_t*) {
   TDataObject::Clear();
   this->SetTiming(kInvalidD);
   this->SetID(kInvalidI);
}

Int_t TDiaTimingData::Compare(const TObject *obj) const {
   using art::IsValid;

   TDiaTimingData *data= (TDiaTimingData*) obj;
   Int_t ret = 0;
   if(!obj) {
      return -1;
   } else {
      switch (fSortType) {
	 case kTiming:
	    if (!IsValid(this->GetTiming())) {
	       if (!IsValid(data->GetTiming())) {
		  return 0;
	       }
	       return 1;
	    } else if (!IsValid(data->GetTiming())) {
	       return -1;
	    }
	    if (this->GetTiming() > data->GetTiming()) {
	       ret = 1;
	    } else if (this->GetTiming() == data->GetTiming()) {
	       ret = 0;
	    } else {
	       ret = -1;
	    }
	    break;
	 case kID:
	    if (!IsValid(this->GetID())) {
	       if (!IsValid(data->GetID())) {
		  return 0;
	       }
	       return 1;
	    } else if (!IsValid(data->GetID())) {
	       return -1;
	    }
	    if (this->GetID() > data->GetID()) {
	       ret = 1;
	    } else if (this->GetID() == data->GetID()) {
	       ret = 0;
	    } else {
	       ret = -1;
	    }
	    break;
      }
   }
   switch (fSortOrder) {
      case kASC:
	 return ret;
      case kDESC:
	 return -ret;
   }

   return 0;
}

void TDiaTimingData::Print(Option_t*) const {
   std::cout << "OBJ: " << IsA()->GetName() << "\t"
	     << "ID: " << GetID() << "\t"
	     << "Timing: " << GetTiming() << std::endl;
}
