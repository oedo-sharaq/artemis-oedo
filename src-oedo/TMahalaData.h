#ifndef TMAHALADATA_H
#define TMAHALADATA_H

#include "TDataObject.h"

namespace art {
    class TMahalaData;
  
}

class TClonesArray;

class art::TMahalaData : public TDataObject {
public:
   // Default constructor
   TMahalaData();
   virtual ~TMahalaData();
   // Copy constructor
   TMahalaData(const TMahalaData& rhs);
   // Assignment operator
   TMahalaData& operator=(const TMahalaData& rhs);

   void Copy(TObject &obj) const;
   void Clear(Option_t *opt = "");

   // TOF(F3-S2) after offset correction
   Double_t GetAq() const { return fAq; }
   void SetAq(Double_t val) { fAq = val; }
   Double_t GetZ() const { return fZ; }
   void SetZ(Double_t val) { fZ = val; }
   Double_t GetTof() const { return fTof; }
   void SetTof(Double_t val) { fTof = val; }
   Double_t GetX() const { return fX; }
   void SetX(Double_t val) { fX = val; }
   Double_t GetEx() const { return fEx; }
   void SetEx(Double_t val) { fEx = val; }
   Double_t GetMd() const { return fMd; }
   void SetMd(Double_t val) { fMd = val; }


//   Double_t GetF3X() const { return fF3X; }
//   void SetF3X(Double_t val) { fF3X = val; }
//   Double_t GetF3A() const { return fF3A; }
//   void SetF3A(Double_t val) { fF3A = val; }
//   Double_t GetF3Y() const { return fF3Y; }
//   void SetF3Y(Double_t val) { fF3Y = val; }
//   Double_t GetF3B() const { return fF3B; }
//   void SetF3B(Double_t val) { fF3B = val; }








protected:
   Double_t fAq;
   Double_t fZ;
   Double_t fTof;
   Double_t fX;
   Double_t fEx;
   Double_t fMd;
//   Double_t fF3X;
//   Double_t fF3A;
//   Double_t fF3Y;
//   Double_t fF3B;
   TClonesArray **fOutput; //!
private:

   ClassDef(TMahalaData,1) // SHARAQ03 mass phys data container

};

#endif // TMAHALADATA_H
