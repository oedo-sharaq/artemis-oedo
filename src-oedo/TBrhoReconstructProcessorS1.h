
/**
 * @file		TBrhoReconstProcessorS1.cc
 * @brief		S1 Brho reconstruction
 *
 * @date		Created				: 2018-1-5 (dozono)
 *
 * @author DOZONO Masanori <dozno@cns.s.u-tokyo.ac.jp>
 *
 */

#ifndef TBrhoReconstProcessorS1_H
#define TBrhoReconstProcessorS1_H

#include "TProcessor.h"
#include <TMatrixD.h>

namespace art {
   class TBrhoReconstructProcessorS1;
}



class art::TBrhoReconstructProcessorS1 : public TProcessor {
public:
   TBrhoReconstructProcessorS1();
   virtual ~TBrhoReconstructProcessorS1();

   TBrhoReconstructProcessorS1(const TBrhoReconstructProcessorS1& rhs);
   TBrhoReconstructProcessorS1& operator=(const TBrhoReconstructProcessorS1& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputName1; // name of tracking result at entrance focus
   TString fInputName2; // name of tracking result at exit focus
   TClonesArray **fInput1; //! input collection of tracking result at entrance focus
   TClonesArray **fInput2; //! input collection of tracking result at exit focus

   TString fOutputName; // name of output collection (brho)
   TClonesArray *fOutput; // output collection of brho
#if 0 // currently not used
   TMatrixD **fGlobalMatrix1; //! global optical matrix element at entrance focus (LISE)
   TMatrixD **fGlobalMatrix2; //! global optical matrix element at exit focus (LISE)
#endif // #if 0

   TMatrixD *fMatrix; // optical matrix element from entrance to exit

   Float_t fBrho0; // central Brho

   Float_t fZ; // z position of focus of exit (mode 1) or entrance (mode 2)

   Int_t fMode; // 0: both tracks on focus, 1: only entrance track on focus, 2: only exit track on focus

//   Int_t fSection; // section 35: F3-F5, 57: F5-F7


private:

   ClassDef(TBrhoReconstructProcessorS1,1) // S1 Brho reconstruction
};

#endif // TBrhoReconstProcessorS1_H

