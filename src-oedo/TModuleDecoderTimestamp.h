/**
 * @file   TModuleDecoderTimestamp.h
 * @brief  APV8008 decoder
 *
 * @date   Created       : 2014-05-18 23:49:27 JST
 *         Last Modified :
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_TMODULEDECODERTIMESTAMP_
#define INCLUDE_GUARD_TMODULEDECODERTIMESTAMP_

#include "TModuleDecoder.h"

namespace art {
  class TModuleDecoderTimestamp;
}

class art::TModuleDecoderTimestamp : public TModuleDecoder {
 public:
  static const int kID = 8;
  TModuleDecoderTimestamp();
  virtual ~TModuleDecoderTimestamp();
  virtual Int_t Decode(char* buffer, const Int_t &size,
		       TObjArray *seg);

  //  TModuleDecoderTimestamp(const TModuleDecoderTimestamp& rhs);
  //  TModuleDecoderTimestamp& operator=(const TModuleDecoderTimestamp& rhs);

 protected:
  TObjArray *fHitData; // array to tomprally store the data for the aggregation

  ClassDef(TModuleDecoderTimestamp,0) // timestamp decoder
};
#endif // INCLUDE_GUARD_TMODULEDECODERTIMESTAMP_
