// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#ifndef _TTREECOPYPROCESSOR_H_
#define _TTREECOPYPROCESSOR_H_ 

#include <TProcessor.h>

namespace art {
  class TTreeCopyProcessor;
}

class TClonesArray;

class art::TTreeCopyProcessor : public TProcessor {
 public:
  TTreeCopyProcessor();
  virtual ~TTreeCopyProcessor();

  virtual void Init(TEventCollection *col);
  virtual void Process();

 protected:
  TString            fInputColName;
  TString            fOutputColName;
  TClonesArray     **fInData; //!
  TClonesArray      *fOutData; //!

 private:
  TTreeCopyProcessor(const TTreeCopyProcessor&);
  TTreeCopyProcessor& operator=(const TTreeCopyProcessor&);

  ClassDef(TTreeCopyProcessor,0) // simple data mapper
};

#endif // _TTREECOPYPROCESSOR_H_

