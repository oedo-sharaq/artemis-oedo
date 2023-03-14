#ifndef TTinaDATA2_H
#define TTinaDATA2_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TTinaData2;
}

class art::TTinaData2 : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TTinaData2();
   virtual ~TTinaData2();
   TTinaData2(const TTinaData2& rhs);
   TTinaData2& operator=(const TTinaData2& rhs);

   Double_t GetEnergy() const {return fEnergy;}
   void SetEnergy(Double_t arg) { fEnergy = arg; }
   Double_t GetDeltaE() const {return fDeltaE;}
   void SetDeltaE(Double_t arg) { fDeltaE = arg; }
   Double_t GetTiming() const {return fTiming;}
   void SetTiming(Double_t arg) { fTiming = arg; }
   Double_t GetTheta() const {return fTheta;}
   void SetTheta(Double_t arg) { fTheta = arg; }
   Double_t GetPhi() const {return fPhi;}
   void SetPhi(Double_t arg) { fPhi = arg; }
   Int_t GetDeid() const {return fDeid;}
   void SetDeid(Int_t arg) { fDeid = arg; }
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
   Double_t fTiming;
   Double_t fTheta;
   Double_t fPhi;
   Int_t fDeid;
   Int_t fEid;
   Double_t fX;
   Double_t fY;

   ClassDef(TTinaData2,1)
};

#endif // TTinaDATA2_H
