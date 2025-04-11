/**
 * @file   TCatGETChargeValidator.h
 * @brief find hits within whole beam hits,  produsing the corresponding recoil particle
 *
 * @date   Created       : 2023-12-17 17:25:00 JST
 * @author Fumitaka ENDO <fendo@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2023 Fumitaka ENDO
 */

#ifndef INCLUDE_GUARD_UUID_f661cb84_8a4a_46bf_a833_f4f94ed764a8
#define INCLUDE_GUARD_UUID_f661cb84_8a4a_46bf_a833_f4f94ed764a8

#include "TProcessor.h"

namespace art {
   class TCatGETChargeValidator;
}

class TClonesArray;

class art::TCatGETChargeValidator : public TProcessor {
public:
   TCatGETChargeValidator();
   virtual ~TCatGETChargeValidator();

   TCatGETChargeValidator(const TCatGETChargeValidator& rhs);
   TCatGETChargeValidator& operator=(const TCatGETChargeValidator& rhs);

   virtual void Process();

protected:
   TString fNameInput; // name of input beam hits collection
   TClonesArray** fInput; //! input beam hits
 
   TString fNameOutput; // name of output beam hits collection
   TClonesArray* fOutput; //! output beam hits

   Double_t fThreshold;
private:

   ClassDef(TCatGETChargeValidator,1) //
};

#endif // INCLUDE_GUARD_UUID_1a87dd47_3d06_43d1_ac6d_dcfc4a2157d8
