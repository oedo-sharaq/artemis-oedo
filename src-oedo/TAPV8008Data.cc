/**
 * @file   TAPV8008Data.cc
 * @brief
 *
 * @date   Created:       2013-08-14 10:34:09
 *         Last Modified: 2014-01-08 12:56:45
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved.
 */

#include "TAPV8008Data.h"
#include "constant.h"

#include <iostream>
#include <TClass.h>

using art::TAPV8008Data;

ClassImp(art::TAPV8008Data)

Int_t TAPV8008Data::fSortType  = TAPV8008Data::kID;
Int_t TAPV8008Data::fSortOrder = TAPV8008Data::kDESC;

// Default constructor
TAPV8008Data::TAPV8008Data() 
   : fTiming(kInvalidD), fCharge(kInvalidD) {
   TDataObject::SetID(kInvalidI);
}

TAPV8008Data::~TAPV8008Data() {
}

// Copy constructor
TAPV8008Data::TAPV8008Data(const TAPV8008Data& rhs)
   : TDataObject(rhs), fTiming(rhs.fTiming), fCharge(rhs.fCharge) {
}

// Assignment operator
TAPV8008Data& TAPV8008Data::operator=(const TAPV8008Data& rhs) {
   if (this != &rhs) {
      ((TAPV8008Data&)rhs).Copy(*this);
   }
   return *this;
}

void TAPV8008Data::Clear(Option_t *opt) {
   TDataObject::Clear(opt);
   TDataObject::SetID(kInvalidI);
   this->SetTiming(kInvalidD);
   this->SetCharge(kInvalidD);
}

Int_t TAPV8008Data::Compare(const TObject *obj) const{
   using art::IsValid;

   TAPV8008Data *data= (TAPV8008Data*) obj;
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
	 case kCharge:
	    if (!IsValid(this->GetCharge())) {
	       if (!IsValid(data->GetCharge())) {
		  return 0;
	       }
	       return 1;
	    } else if (!IsValid(data->GetCharge())) {
	       return -1;
	    }
	    if (this->GetCharge() > data->GetCharge()) {
	       ret = 1;
	    } else if (this->GetCharge() == data->GetCharge()) {
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

void TAPV8008Data::Print(Option_t*) const {
   std::cout << "OBJ: " << IsA()->GetName() << "\t"
	     << "ID: " << GetID() << "\t"
	     << "Timing: " << GetTiming() << "\t"
	     << "Charge: " << GetCharge() << std::endl;
}
