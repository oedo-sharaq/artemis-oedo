#ifndef INCLUDE_GUARD_TDALIPROC
#define INCLUDE_GUARD_TDALIPROC

#include "TProcessor.h"

namespace art {
   class TDaliProcessor;
}

class art::TDaliProcessor : public TProcessor {
public:
   TDaliProcessor();
   virtual ~TDaliProcessor();
   void Process();

protected:
   TString        fDaliName;
   TClonesArray **fDali;
   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TDaliProcessor(const TDaliProcessor&);
   TDaliProcessor& operator=(const TDaliProcessor&);

   ClassDef(TDaliProcessor,0)
};

#endif
