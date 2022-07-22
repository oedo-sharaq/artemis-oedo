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

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

protected:
   Double_t fEnergy;
   Double_t fDeltaE;
   Double_t fTheta;
   Double_t fPhi;

   ClassDef(TTinaData3,1)
};

#endif // TTinaDATA3_H
