#ifndef TTinaDATA_H
#define TTinaDATA_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TTinaData;
}

class art::TTinaData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TTinaData();
   virtual ~TTinaData();
   TTinaData(const TTinaData& rhs);
   TTinaData& operator=(const TTinaData& rhs);

   Double_t GetEnergy() const {return fEnergy;}
   void SetEnergy(Double_t arg) { fEnergy = arg; }
   Double_t GetDeltaE() const {return fDeltaE;}
   void SetDeltaE(Double_t arg) { fDeltaE = arg; }
   Double_t GetTheta() const {return fTheta;}
   void SetTheta(Double_t arg) { fTheta = arg; }
   Double_t GetPhi() const {return fPhi;}
   void SetPhi(Double_t arg) { fPhi = arg; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

protected:
   Double_t fEnergy;
   Double_t fDeltaE;
   Double_t fTheta;
   Double_t fPhi;

   ClassDef(TTinaData,1)
};

#endif // TTinaDATA_H
