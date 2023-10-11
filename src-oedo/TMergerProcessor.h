#ifndef INCLUDE_GUARD_TMERGERPROCESSOR
#define INCLUDE_GUARD_TMERGERPROCESSOR

#include "TProcessor.h"

namespace art {
   class TMergerProcessor;
   class TCategorizedData;
   class TDssdData;
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

   TString fInputName1;
   TString fInputName2;
   TString fInputName3;
   TString fInputName4;
   TString fInputName5;
   TClonesArray **fInputCollection1;
   TClonesArray **fInputCollection2;
   TClonesArray **fInputCollection3;
   TClonesArray **fInputCollection4;
   TClonesArray **fInputCollection5;

   TString fOutputName;
   TClonesArray *fOutput;

   Bool_t fIsSparse;

   Int_t fCatID;

private:

   void StoreMain(const TObjArray*);

   ClassDef(TMergerProcessor,0)
};

#endif //INCLUDE_GUARD_TMERGERPROCESSOR
