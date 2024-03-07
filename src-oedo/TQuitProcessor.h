#ifndef TQUITPROCESSOR_H
#define TQUITPROCESSOR_H

#include "TProcessor.h"
namespace art {
   class TQuitProcessor;
}

class art::TQuitProcessor  : public TProcessor {

public:
   TQuitProcessor();
   ~TQuitProcessor();

   virtual void Init(TEventCollection*col);
   virtual void Process();
   
   virtual void PreLoop();
   virtual void PostLoop();

protected:
   ClassDef(TQuitProcessor,1);
};
#endif // end of #ifdef TQUITPROCESSOR_H
