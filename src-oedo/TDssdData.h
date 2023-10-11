#ifndef TDssdDATA_H
#define TDssdDATA_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TDssdData;
}

class art::TDssdData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TDssdData();
   virtual ~TDssdData();
   TDssdData(const TDssdData& rhs);
   TDssdData& operator=(const TDssdData& rhs);

   Double_t GetEx() const {return fEx;}
   void SetEx(Double_t arg) { fEx = arg; }
   Double_t GetXID() const {return fXID;}
   void SetXID(Double_t arg) { fXID = arg; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

protected:
   Double_t fEx;
   Double_t fXID;

   ClassDef(TDssdData,1)
};

#endif // TDssdDATA_H
