#ifndef TDIATIMINGDATA_H
#define TDIATIMINGDATA_H

#include "TDataObject.h"
#include "ITiming.h"

namespace art {
   class TDiaTimingData;
}


class art::TDiaTimingData :public TDataObject, public ITiming {
public:
   // Default constructor
   TDiaTimingData();
   // destructor
   virtual ~TDiaTimingData();
   // Copy constructor
   TDiaTimingData(const TDiaTimingData& rhs);
   // Assignment operator
   TDiaTimingData& operator=(const TDiaTimingData& rhs);
   using ITiming::operator=;

   // set sort order. order must be among ETimingSortType.
   static void SetSortOrder(Int_t order) {fSortOrder = order;}
   // set sort order. type must be among ETimingSortOrder.
   static void SetSortType(Int_t type){fSortType = type;}

   virtual Bool_t IsSortable() const {return kTRUE;}

   virtual Double_t GetTiming() const { return fTiming;}
   virtual void SetTiming(Double_t val) { fTiming = val; }
   virtual void SetTiming(const ITiming &obj) { SetTiming(obj.GetTiming()); }

   // obsolete. use TDataObject::SetID()
   virtual void SetDetID(Int_t val) { SetID(val); }
   // obsolete. use TDataObject::GetID()
   virtual Int_t GetDetID() const {return GetID();}

   virtual void Clear(Option_t* opt = "");

   virtual void Copy(TObject& dest) const {
      TDataObject::Copy(dest);
      TDiaTimingData &cobj = *(TDiaTimingData*)&dest;
      cobj.SetTiming(GetTiming());
   }

   virtual Int_t Compare(const TObject *obj) const;

   virtual void Print(Option_t*) const;

   typedef enum {kID, kTiming} ETimingSortType; //!
   typedef enum {kASC, kDESC} ETimingSortOrder; //!
   
protected:
   Double_t fTiming;

   static Int_t fSortType; //!
   static Int_t fSortOrder; //!

   ClassDef(TDiaTimingData,1) // container for timing information
};

#endif // TDIATIMINGDATA_H
