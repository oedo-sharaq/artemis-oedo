/**
 * @file   TSingleTOFProcessor.h
 * @brief  calculate TOF from a pair of timing information
 *
 * @date   Created       : 2016-05-26 19:22:50 JST
 *         Last Modified : 2016-05-28 08:51:35 JST (kawase)
 * @author KAWASE Shoichiro <kawase@aees.kyushu-u.ac.jp>
 *
 *    (C) 2016 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_UUID_2C82D39A_A3DF_4D26_873A_F14409B5F98D
#define INCLUDE_GUARD_UUID_2C82D39A_A3DF_4D26_873A_F14409B5F98D

#include "TProcessor.h"

namespace art {
   class TSingleTOFProcessor;
}

class art::TSingleTOFProcessor : public TProcessor {
public:
   TSingleTOFProcessor();
   virtual ~TSingleTOFProcessor();

   void Init(TEventCollection*);
   void Process();

protected:
   TString        fStartColName; // collection name for start timing
   TClonesArray **fStartCollection;     // collection for start timing
   Int_t          fStartID;             // id of start timing
   TString        fStopColName;  // collection name for stop timing
   TClonesArray **fStopCollection;      // collection for stop timing
   Int_t          fStopID;              // id of stop timing

   TString       fOutputName; // name of output
   TClonesArray *fOutput;     // output collection

private:
   TClonesArray** LoadBranch(TEventCollection*,const TString&);

   TSingleTOFProcessor(const TSingleTOFProcessor&);
   TSingleTOFProcessor& operator=(const TSingleTOFProcessor&);

   ClassDef(TSingleTOFProcessor,0) // calculate TOF from a pair of timing information
};

#endif // INCLUDE_GUARD_UUID_2C82D39A_A3DF_4D26_873A_F14409B5F98D
