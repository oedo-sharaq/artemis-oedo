/**
 * @file   TBrhoReconstructProcessor3.h
 * @brief  reconstruct BrhoS0S1, using FE12 S1 SR-PPAC info, and very simple matrix elements
 *
 * @date   Created       : 2023-01-24 JST

 * @author T. Chillery
 *
  */

#ifndef INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B7
#define INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B7

#include "TProcessor.h"
//#include <TMatrixD.h>

namespace art {
   class TBrhoReconstructProcessor3;
}



class art::TBrhoReconstructProcessor3 : public TProcessor {
public:
   TBrhoReconstructProcessor3();
   virtual ~TBrhoReconstructProcessor3();

   TBrhoReconstructProcessor3(const TBrhoReconstructProcessor3& rhs);
   TBrhoReconstructProcessor3& operator=(const TBrhoReconstructProcessor3& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputName1; // name of tracking result at entrance focus
   TString fInputName2; // name of tracking result at exit focus
   TString fInputName3; // name of tracking result at entrance focus
   TString fInputName4; // name of tracking result at exit focus
   TString fInputName5; // name of tracking result at entrance focus
   TString fInputName6; // name of tracking result at exit focus
   TString fInputName7; // name of tracking result at entrance focus
   TString fInputName8; // name of tracking result at exit focus
   TClonesArray **fInPut1; //! input collection of tracking result at entrance focus
   TClonesArray **fInPut2; //! input collection of tracking result at exit focus
   TClonesArray **fInPut3; //! input collection of tracking result at entrance focus
   TClonesArray **fInPut4; //! input collection of tracking result at exit focus
   TClonesArray **fInPut5; //! input collection of tracking result at entrance focus
   TClonesArray **fInPut6; //! input collection of tracking result at exit focus
   TClonesArray **fInPut7; //! input collection of tracking result at entrance focus
   TClonesArray **fInPut8; //! input collection of tracking result at exit focus

   TString fOutputName; // name of output collection (brhoSimple)
   TClonesArray *fOutput; // output collection of brho
#if 0 // currently not used
   TMatrixD **fGlobalMatrix1; //! global optical matrix element at entrance focus (LISE)
   TMatrixD **fGlobalMatrix2; //! global optical matrix element at exit focus (LISE)
#endif // #if 0

   //TMatrixD *fMatrix; // optical matrix element from entrance to exit

   Float_t fBrho0; // central Brho

   Float_t fZ; // z position of focus of exit (mode 1) or entrance (mode 2)

   Int_t fMode; // 0: both tracks on focus, 1: only entrance track on focus, 2: only exit track on focus

   Int_t fSection; // section 35: F3-F5, 57: F5-F7


private:

   ClassDef(TBrhoReconstructProcessor3,1) // reconstruct BrhoS1 using FE12, S1 information
};

#endif // INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B7
