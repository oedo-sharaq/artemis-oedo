/**
 * @file   TAPV8008Data.h
 * @brief
 *
 * @date   Created:       2013-08-14 10:19:28
 *         Last Modified: 2014-02-24 14:39:51
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved
 */

#ifndef TAPV8008DATA_H
#define TAPV8008DATA_H

#include "TDataObject.h"
#include "ITiming.h"
#include "ICharge.h"

namespace art{
   class TAPV8008Data;
}

class art::TAPV8008Data : public TDataObject, public ITiming, public ICharge {
public:
   typedef enum {kID, kCharge, kTiming} ETimingChargeSortType; //!
   typedef enum {kASC, kDESC} ESortOrder; //!

   // Default constructor
   TAPV8008Data();
   virtual ~TAPV8008Data();
   // Copy constructor
   TAPV8008Data(const TAPV8008Data& rhs);
   // Assignment operator
   virtual TAPV8008Data& operator=(const TAPV8008Data& rhs);

   virtual Int_t Compare(const TObject*) const;

   virtual Double_t GetTiming() const {return fTiming;}
   virtual void     SetTiming(Double_t val){fTiming = val;}
   virtual void     SetTiming(const ITiming& obj){SetTiming(obj.GetTiming());}

   virtual Double_t GetCharge() const {return fCharge;}
   virtual void     SetCharge(Double_t val){fCharge = val;}
   virtual void     SetCharge(const ICharge& obj){SetCharge(obj.GetCharge());}

   virtual ULong64_t GetABS() const {return fABS;}
   virtual void     SetABS(ULong64_t val){fABS = val;}
   //virtual void     SetABS(const ICharge& obj){SetCharge(obj.GetCharge());}

   virtual UInt_t GetABSdeci() const {return fABSdeci;}
   virtual void     SetABSdeci(UInt_t val){fABSdeci = val;}
   //virtual void     SetCharge(const ICharge& obj){SetCharge(obj.GetCharge());}

   virtual UShort_t GetfChannel() const {return fCh;}
   virtual void     SetfChannel(UShort_t val){fCh = val;}

   virtual Double_t GetCalibCharge() const {return fCalib_Charge;}
   virtual void     SetCalibCharge(Double_t val){fCalib_Charge = val;}

   // obsolete. use TDataObject::GetID()
   virtual Int_t GetDetID() const {return GetID();}
   // obsolete. use TDataObject::SetID()
   virtual void  SetDetID(Int_t val){ SetID(val);}

   static void SetSortOrder(Int_t order){fSortOrder = order;}
   static void SetSortType(Int_t type){fSortType = type;}

   virtual Bool_t IsSortable() const {return kTRUE;}

   virtual void Copy(TObject& dest) const {
      TDataObject::Copy(dest);
      TAPV8008Data &cobj = *(TAPV8008Data*)&dest;
      cobj.SetTiming(this->GetTiming());
      cobj.SetCharge(this->GetCharge());
   }

   virtual void Clear(Option_t *opt="");

   virtual void Print(Option_t *) const;

protected:
   UShort_t fCh;
   Double_t fTiming;
   Double_t fCharge;
   Double_t fCalib_Charge;
   ULong64_t fABS;
   UInt_t fABSdeci;

   static Int_t fSortType;  //!
   static Int_t fSortOrder; //!

   ClassDef(TAPV8008Data,1) // container for timing information with charge
};

#endif // TAPV8008DATA_H
