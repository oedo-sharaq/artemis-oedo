/**
 * @file   TModuleDecoderAPV8008.h
 * @brief  APV8008 decoder
 *
 * @date   Created       : 2014-05-18 23:49:27 JST
 *         Last Modified :
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_TMODULEDECODERAPV8008_
#define INCLUDE_GUARD_TMODULEDECODERAPV8008_

#include "TModuleDecoder.h"

namespace art {
  class TModuleDecoderAPV8008;
}

class art::TModuleDecoderAPV8008 : public TModuleDecoder {
 public:
  static const int kID = 29;
  TModuleDecoderAPV8008();
  virtual ~TModuleDecoderAPV8008();
  virtual Int_t Decode(char* buffer, const Int_t &size,
		       TObjArray *seg);

  //  TModuleDecoderAPV8008(const TModuleDecoderAPV8008& rhs);
  //  TModuleDecoderAPV8008& operator=(const TModuleDecoderAPV8008& rhs);

 protected:
  TObjArray *fHitData; // array to tomprally store the data for the aggregation

  ClassDef(TModuleDecoderAPV8008,0) // APV8008 decoder
};
#endif // INCLUDE_GUARD_TMODULEDECODERAPV8008_
