#ifndef TMERGERDATA_H
#define TMERGERDATA_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TMergerData;
}

class art::TMergerData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TMergerData();
   virtual ~TMergerData();
   TMergerData(const TMergerData& rhs);
   TMergerData& operator=(const TMergerData& rhs);

   ULong64_t GetULongTimestamp() const {return fTimestamp;}
   void SetTimestamp(ULong64_t ts) { fTimestamp = ts; }
   Int_t GetTestdata() const {return fTestdata;}
   void SetTestdata(Int_t testdata) { fTestdata = testdata; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   static void SetSortOrder(Int_t order){fSortOrder = order;}
   static void SetSortType(Int_t type){fSortType = type;}

protected:
   ULong64_t fTimestamp;
   Int_t fTestdata;
   //add object below?


   static Int_t fSortType;  //!
   static Int_t fSortOrder; //!

   ClassDef(TMergerData,1)
};

#endif // TMERGERDATA_H
