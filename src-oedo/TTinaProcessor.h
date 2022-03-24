#ifndef INCLUDE_GUARD_TTINAPROC
#define INCLUDE_GUARD_TTINAPROC

#include "TProcessor.h"

namespace art {
   class TTinaProcessor;
}

class art::TTinaProcessor : public TProcessor {
public:
   TTinaProcessor();
   virtual ~TTinaProcessor();
   void Process();

protected:
   TString        fSiName;
   TClonesArray **fSi;
   TString        fCsIName;
   TClonesArray **fCsI;
   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TTinaProcessor(const TTinaProcessor&);
   TTinaProcessor& operator=(const TTinaProcessor&);

   ClassDef(TTinaProcessor,0)
};

#endif
