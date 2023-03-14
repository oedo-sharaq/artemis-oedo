#ifndef INCLUDE_GUARD_TTINAPROC3
#define INCLUDE_GUARD_TTINAPROC3

#include "TProcessor.h"

namespace art {
   class TTinaProcessor3;
}

class art::TTinaProcessor3 : public TProcessor {
public:
   TTinaProcessor3();
   virtual ~TTinaProcessor3();
   void Process();

protected:
   TString        fSifName;
   TClonesArray **fSif;
   TString        fSibName;
   TClonesArray **fSib;
   TString        fCsIName;
   TClonesArray **fCsI;
   TString        fX1Name;
   TClonesArray **fX1;
   TString        fY1Name;
   TClonesArray **fY1;
   TString        fX2Name;
   TClonesArray **fX2;
   TString        fY2Name;
   TClonesArray **fY2;
   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TTinaProcessor3(const TTinaProcessor3&);
   TTinaProcessor3& operator=(const TTinaProcessor3&);

   ClassDef(TTinaProcessor3,0)
};

#endif
