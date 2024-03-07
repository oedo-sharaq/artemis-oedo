
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

   virtual Double_t Convert(Double_t val) const { return TMath::Exp((val - fParam[0])/ fParam[1])+ fParam[2]; }
   virtual void Print(Option_t *opt = "") const;

   ClassDef(TExpConverter,1) // TAffineConverter
};

