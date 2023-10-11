#ifndef INCLUDE_GUARD_TDSSDPROC
#define INCLUDE_GUARD_TDSSDPROC

#include "TProcessor.h"

namespace art {
   class TDssdProcessor;
}

class art::TDssdProcessor : public TProcessor {
public:
   TDssdProcessor();
   virtual ~TDssdProcessor();
   void Process();

protected:
   TString        fSiXName;
   TClonesArray **fSix;
   //   TString        fSiYName;
   //   TClonesArray **fSiy;
   TString        fXIDName;
   TClonesArray **fXID;
   //   TString        fYIDName;
   //   TClonesArray **fYID;
   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TDssdProcessor(const TDssdProcessor&);
   TDssdProcessor& operator=(const TDssdProcessor&);

   ClassDef(TDssdProcessor,0)
};

#endif
