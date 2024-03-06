#ifndef TTinaDATA3_H
#define TTinaDATA3_H

#include "TDataObject.h"
#include "constant.h"

namespace art
{
   class TTinaData3;
}

class art::TTinaData3 : public TDataObject
{
public:
   typedef enum
   {
      kID,
      kTiming
   } ESortType;
   typedef enum
   {
      kASC,
      kDESC
   } ESortOrder;

   TTinaData3();
   virtual ~TTinaData3();
   TTinaData3(const TTinaData3 &rhs);
   TTinaData3 &operator=(const TTinaData3 &rhs);

   Double_t GetEnergy() const { return fEnergy; }
   void SetEnergy(Double_t arg) { fEnergy = arg; }
   Double_t GetEcsi() const { return fEcsi; }
   void SetEcsi(Double_t arg) { fEcsi = arg; }
   Double_t GetEcsicalc() const { return fEcsicalc; } // calculated value from atima
   void SetEcsicalc(Double_t arg) { fEcsicalc = arg; }
   Double_t GetDeltaE() const { return fDeltaE; }
   void SetDeltaE(Double_t arg) { fDeltaE = arg; }
   Double_t GetTheta() const { return fTheta; }
   void SetTheta(Double_t arg) { fTheta = arg; }
   Double_t GetPhi() const { return fPhi; }
   void SetPhi(Double_t arg) { fPhi = arg; }
   Double_t GetX() const { return fX; }
   void SetX(Double_t arg) { fX = arg; }
   Double_t GetY() const { return fY; }
   void SetY(Double_t arg) { fY = arg; }
   Double_t GetTrack() const { return fTrack; }
   void SetTrack(Double_t arg) { fTrack = arg; }
   Double_t GetScat() const { return fScat; }
   void SetScat(Double_t arg) { fScat = arg; }

   virtual void Copy(TObject &dest) const;
   virtual void Clear(Option_t *opt = "");

protected:
   Double_t fEnergy;
   Double_t fDeltaE;
   Double_t fTheta;
   Double_t fPhi;
   Double_t fEcsi;
   Double_t fEcsicalc;
   Double_t fX;
   Double_t fY;
   Double_t fTrack;
   Double_t fScat;

   ClassDef(TTinaData3, 4)
};

#endif // TTinaDATA3_H
