#ifndef TTinaDATA3_H
#define TTinaDATA3_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TTinaData3;
}

class art::TTinaData3 : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TTinaData3();
   virtual ~TTinaData3();
   TTinaData3(const TTinaData3& rhs);
   TTinaData3& operator=(const TTinaData3& rhs);

   Double_t GetEnergy() const {return fEnergy;}
   void SetEnergy(Double_t arg) { fEnergy = arg; }
   Double_t GetDeltaE() const {return fDeltaE;}
   void SetDeltaE(Double_t arg) { fDeltaE = arg; }
   Double_t GetTheta() const {return fTheta;}
   void SetTheta(Double_t arg) { fTheta = arg; }
   Double_t GetPhi() const {return fPhi;}
   void SetPhi(Double_t arg) { fPhi = arg; }
   Int_t GetDefid() const {return fDefid;}
   void SetDefid(Int_t arg) { fDefid = arg; }
   Int_t GetDebid() const {return fDebid;}
   void SetDebid(Int_t arg) { fDebid = arg; }
   Int_t GetEid() const {return fEid;}
   void SetEid(Int_t arg) { fEid = arg; }
   Double_t GetX() const {return fX;}
   void SetX(Double_t arg) { fX = arg; }
   Double_t GetY() const {return fY;}
   void SetY(Double_t arg) { fY = arg; }

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

protected:
   Double_t fEnergy;
   Double_t fDeltaE;
   Double_t fTheta;
   Double_t fPhi;
   Int_t fDefid;
   Int_t fDebid;
   Int_t fEid;
   Double_t fX;
   Double_t fY;

   ClassDef(TTinaData3,1)
};

#endif // TTinaDATA3_H
