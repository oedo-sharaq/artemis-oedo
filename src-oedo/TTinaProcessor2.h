#ifndef INCLUDE_GUARD_TTINAPROC2
#define INCLUDE_GUARD_TTINAPROC2

#include "TProcessor.h"

namespace art {
   class TTinaProcessor2;
}

class art::TTinaProcessor2 : public TProcessor {
public:
   TTinaProcessor2();
   virtual ~TTinaProcessor2();
   void Process();

protected:
   TString        fSiName;
   TClonesArray **fSi;
   TString        fCsIName;
   TClonesArray **fCsI;
   TString        fTinaTName;
   TClonesArray **fTinaT;
   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TTinaProcessor2(const TTinaProcessor2&);
   TTinaProcessor2& operator=(const TTinaProcessor2&);

   ClassDef(TTinaProcessor2,0)
};

#endif
