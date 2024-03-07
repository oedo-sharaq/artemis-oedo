#ifndef INCLUDE_GUARD_TMERGERPROCESSOR
#define INCLUDE_GUARD_TMERGERPROCESSOR

#include "TProcessor.h"

namespace art {
   class TMergerProcessor;
   class TCategorizedData;
}

//class TClonesArray;

class art::TMergerProcessor : public TProcessor {
public:
   TMergerProcessor();
   virtual ~TMergerProcessor();

   TMergerProcessor(const TMergerProcessor& rhs);
   TMergerProcessor& operator=(const TMergerProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputName;
   TCategorizedData **fInput;

   TString fOutputName;
   TClonesArray *fOutput;

   Bool_t fIsSparse;

   //needed value for pid
   Int_t fCatID;
   ULong64_t fTimestamp;

   //from yaml parameters?
   Int_t ftest_prm1;

private:

   void TSProcess();
   void TSStoreMain(const TObjArray*);

   ClassDef(TMergerProcessor,0)
};

#endif //INCLUDE_GUARD_TMERGERPROCESSOR
