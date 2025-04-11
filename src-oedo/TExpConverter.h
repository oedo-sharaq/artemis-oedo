
#include "TFixedNumberParameter.h"
#include <TMath.h>

namespace art {
   class TExpConverter;
}

class art::TExpConverter : public TFixedNumberParameter {
public:
   TExpConverter();
   virtual ~TExpConverter();

   TExpConverter(const TExpConverter& rhs);
   TExpConverter& operator=(const TExpConverter& rhs);

   virtual Double_t Convert(Double_t val) const { return fParam[0] * TMath::Exp((val - fParam[1])/ fParam[2])+ fParam[3]; }
   virtual void Print(Option_t *opt = "") const;

   ClassDef(TExpConverter,1) // TAffineConverter
};

