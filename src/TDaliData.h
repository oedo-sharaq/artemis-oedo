#ifndef TDaliDATA_H
#define TDaliDATA_H

#include "TDataObject.h"
#include "constant.h"

namespace art {
   class TDaliData;
}

class art::TDaliData : public TDataObject {
public:
   typedef enum {kID, kTiming} ESortType;
   typedef enum {kASC, kDESC} ESortOrder;
   
   TDaliData();
   virtual ~TDaliData();
   TDaliData(const TDaliData& rhs);
   TDaliData& operator=(const TDaliData& rhs);

   Double_t GetEnergy1() const {return fEnergy1;}
   void SetEnergy1(Double_t arg) { fEnergy1 = arg; }
   Double_t GetEnergy2() const {return fEnergy2;}
   void SetEnergy2(Double_t arg) { fEnergy2 = arg; }
   Double_t GetTiming1() const {return fTiming1;}
   void SetTiming1(Double_t arg) { fTiming1 = arg; }
   Double_t GetTiming2() const {return fTiming2;}
   void SetTiming2(Double_t arg) { fTiming2 = arg; }
   Double_t GetTotalE() const {return fTotalE;}
   void SetTotalE(Double_t arg) { fTotalE = arg; }
   Double_t GetTheta() const {return fTheta;}
   void SetTheta(Double_t arg) { fTheta = arg; }
   Int_t GetPos1() const {return fPos1;}
   void SetPos1(Int_t arg){fPos1 = arg;}
   Int_t GetPos2() const {return fPos2;}
   void SetPos2(Int_t arg){fPos2 = arg;}

   virtual void Copy(TObject& dest) const;
   virtual void Clear(Option_t *opt="");

protected:
   Double_t fEnergy1;
   Double_t fEnergy2;
   Double_t fTiming1;
   Double_t fTiming2;
   Int_t fPos1;
   Int_t fPos2;
   Double_t fTheta;
   Double_t fTotalE;

   ClassDef(TDaliData,1)
};

#endif // TDaliDATA_H
