#ifndef INCLUDE_GUARD_TDSSDCALPROC
#define INCLUDE_GUARD_TDSSDCALPROC

#include "TProcessor.h"

namespace art {
   class TDssdCalProcessor;
}

class art::TDssdCalProcessor : public TProcessor {
public:
   TDssdCalProcessor();
   virtual ~TDssdCalProcessor();
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
   TDssdCalProcessor(const TDssdCalProcessor&);
   TDssdCalProcessor& operator=(const TDssdCalProcessor&);

   ClassDef(TDssdCalProcessor,0)
};

#endif
