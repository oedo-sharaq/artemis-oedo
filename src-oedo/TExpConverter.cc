#include "TExpConverter.h"
#include <TROOT.h>
#include <TClass.h>

using art::TExpConverter;

ClassImp(TExpConverter)

TExpConverter::TExpConverter() : TFixedNumberParameter(4) {}

TExpConverter::~TExpConverter() {}

TExpConverter::TExpConverter(const TExpConverter& rhs) : TFixedNumberParameter(rhs) {}

TExpConverter& TExpConverter::operator=(const TExpConverter& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TExpConverter::Print(Option_t * /* opt */) const
{
   const TString indent(' ', gROOT->GetDirLevel());
   printf("OBJ: %s\t%s\n", IsA()->GetName(), GetName());
 //  printf("%s f(x) = TMath::Exp((x + %lf) / %lf)\n", indent.Data(), fParam[0], fParam[1]);
   printf("%s f(x) =  %lf * TMath::Exp((x - %lf) / %lf) + %f\n", indent.Data(), fParam[0], fParam[1], fParam[2], fParam[3]);
}
