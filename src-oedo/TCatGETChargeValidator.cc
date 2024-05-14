/**
 * @file   TCatGETChargeValidator.cc
 * @brief find hits within whole beam hits,  produsing the corresponding recoil particle
 *
 * @date   Created       : 2023-12-17 17:25:00 JST
 * @author Fumitaka ENDO <fendo@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2023 Fumitaka ENDO
 */

#include "TCatGETChargeValidator.h"
#include <TClonesArray.h>
#include <TTimingChargeData.h>
#include <TCatPulseShape.h>
#include <TCatTpcTrack.h>

using art::TCatGETChargeValidator;

ClassImp(TCatGETChargeValidator)

TCatGETChargeValidator::TCatGETChargeValidator()
{
   RegisterInputCollection("Input","name of input beam hits",fNameInput,"atbeamhits",&fInput,TClonesArray::Class_Name(),art::TCatPulseShape::Class_Name());
   RegisterOutputCollection("Output","name of output beam hits",fNameOutput,"atbeamhits",&fOutput,TClonesArray::Class_Name(),art::TCatPulseShape::Class_Name());
   RegisterProcessorParameter("Threshold","threshold of charge",fThreshold,0.);
}

TCatGETChargeValidator::~TCatGETChargeValidator()
{
}

TCatGETChargeValidator::TCatGETChargeValidator(const TCatGETChargeValidator& rhs)
{
}

TCatGETChargeValidator& TCatGETChargeValidator::operator=(const TCatGETChargeValidator& rhs)
{
   if (this != &rhs) {

   }   
   return *this;
}

void TCatGETChargeValidator::Process()
{
   fOutput->Clear("C");
   if ((*fInput)->GetEntriesFast() == 0) return;
   TClonesArray *input = *fInput;

   for (Int_t i = 0, n = input->GetEntriesFast(); i < n; ++i) {
      TCatPulseShape *pulse = static_cast<TCatPulseShape*>((input)->UncheckedAt(i));
      Double_t Qval = pulse->GetCharge();

      if ( Qval < fThreshold  ) continue;

      TCatPulseShape *out = static_cast<TCatPulseShape*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
      pulse->Copy(*out);
   }   
}
