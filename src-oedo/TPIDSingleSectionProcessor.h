/**
 * @file   TPIDSingleSectionProcessor.h
 * @brief  reconstruct Brho35, Brho57 using F3, F5, F7 information
 *
 * @date   Created       : 2015-04-15 14:55:13 JST
 *         Last Modified : Apr 15, 2015 21:36:10 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B71
#define INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B71

#include "TProcessor.h"
#include <TMatrixD.h>

namespace art {
   class TPIDSingleSectionProcessor;
}



class art::TPIDSingleSectionProcessor : public TProcessor {
public:
   TPIDSingleSectionProcessor();
   virtual ~TPIDSingleSectionProcessor();

   TPIDSingleSectionProcessor(const TPIDSingleSectionProcessor& rhs);
   TPIDSingleSectionProcessor& operator=(const TPIDSingleSectionProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

protected:
   TString fInputNameBrho; // name of tracking result at entrance focus
   TClonesArray **fInputBrho; //! input collection of tracking result at entrance focus

   TString fInputNameBeta; // name of tof input
   TClonesArray **fInputBeta; //!

   TString fInputNameDE; // name of tof input
   TClonesArray **fInputDE; //!

   TString fOutputNameAQ; 
   TClonesArray *fOutputAQ; //!

   TString fOutputNameZ; 
   TClonesArray *fOutputZ; //!



private:

   ClassDef(TPIDSingleSectionProcessor,1) // reconstruct Brho35, Brho57 using F3, F5, F7 information
};

#endif // INCLUDE_GUARD_UUID_F18756D7_A443_440A_8285_6CD7C5C849B71
