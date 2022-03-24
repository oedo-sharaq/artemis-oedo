/**
 * @file   TIonChamberProcessor.h
 * @brief  ion chamber analysis
 *
 * @date   Created       : 2015-05-26 15:11:29 JST
 *         Last Modified : 2015-05-27 10:40:35 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_UUID_3032E015_6AFF_4C97_9706_A06D8FA631AB
#define INCLUDE_GUARD_UUID_3032E015_6AFF_4C97_9706_A06D8FA631AB

#include "TProcessor.h"

namespace art {
   class TIonChamberProcessor;
}

class art::TIonChamberProcessor : public TProcessor {
public:
   TIonChamberProcessor();
   virtual ~TIonChamberProcessor();

   void Process();

protected:
   TString        fInputName;
   TClonesArray **fInput; //!

   Int_t          fNumCh;
   Float_t        fDropRatio;

   TString        fOutputName;
   TClonesArray  *fOutput;

private:
   TIonChamberProcessor(const TIonChamberProcessor&);
   TIonChamberProcessor& operator=(const TIonChamberProcessor&);

   ClassDef(TIonChamberProcessor,0) // ion chamber analysis
};

#endif // INCLUDE_GUARD_UUID_3032E015_6AFF_4C97_9706_A06D8FA631AB
