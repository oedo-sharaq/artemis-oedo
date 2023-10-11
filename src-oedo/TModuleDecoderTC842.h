#ifndef TARTDECODERTC842_H
#define TARTDECODERTC842_H

#include "TModuleDecoder.h"

namespace art {
  class TModuleDecoderTC842;
}

class art::TModuleDecoderTC842 : public TModuleDecoder {
 public:
  static const int kID = 30;
  TModuleDecoderTC842();
  virtual ~TModuleDecoderTC842();
  virtual Int_t Decode(char* buffer, const Int_t &size,
		       TObjArray *seg);

  //  TModuleDecoderTC842(const TModuleDecoderTC842& rhs);
  //  TModuleDecoderTC842& operator=(const TModuleDecoderTC842& rhs);

 protected:
  TObjArray *fHitData; // array to tomprally store the data for the aggregation

  ClassDef(TModuleDecoderTC842,0) // TC842 decoder
};
#endif // TARTDECODERTC842_H
