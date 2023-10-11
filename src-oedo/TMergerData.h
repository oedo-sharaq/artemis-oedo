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
   void SetULongTimestamp(ULong64_t ts) { fTimestamp = ts; }

   Double_t GetfTimestamp() const {return fTiming;}
   void SetfTimestamp(Double_t ts) { fTiming = ts; }

   Double_t GetS2z() const {return fS2z;}
   void SetS2z(Double_t s2z) { fS2z = s2z; }

   Double_t GetS2aq() const {return fS2aq;}
   void SetS2aq(Double_t s2aq) { fS2aq = s2aq; }

   Double_t GetVeto_tave() const {return fVeto_tave;}
   void SetVeto_tave(Double_t tave) { fVeto_tave = tave; }

   Double_t GetVeto_qave() const {return fVeto_qave;}
   void SetVeto_qave(Double_t qave) { fVeto_qave = qave; }

//   Double_t Getdias2t() const {return fdias2t;}
//   void Setdias2t(Double_t val) { fdias2t = val; }
//
//   Double_t Getdia3t() const {return fdia3t;}
//   void Setdia3t(Double_t val) { fdia3t = val; }
//
//   Double_t GetS2x() const {return fS2x;}
//   void SetS2x(Double_t val) { fS2x = val; }
//
//   Double_t GetS2ssde() const {return fS2ssde;}
//   void SetS2ssde(Double_t val) { fS2ssde = val; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

   static void SetSortOrder(Int_t order){fSortOrder = order;}
   static void SetSortType(Int_t type){fSortType = type;}

protected:
   ULong64_t fTimestamp;
   Double_t fTiming;
   Double_t fS2z;
   Double_t fS2aq;
   Double_t fVeto_tave;
   Double_t fVeto_qave;

//   Double_t fdias2t;
//   Double_t fdia3t;
//   Double_t fS2x;
//   Double_t fS2ssde;


   static Int_t fSortType;  //!
   static Int_t fSortOrder; //!

   ClassDef(TMergerData,3)
};

#endif // TMERGERDATA_H
