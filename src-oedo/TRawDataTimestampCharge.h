/**
 * for APV8008 okawa
 *
 * @file   TRawDataTimestampCharge.h
 * @brief  raw data with timing and charge
 *
 * @date   Created       : 2015-10-04 17:57:15 JST
 *         Last Modified : 2015-10-04 18:26:02 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#ifndef _TRAWDATARIMESTAMPCHARGE_H_ 
#define _TRAWDATARIMESTAMPCHARGE_H_ 

#include "TRawDataObject.h"

namespace art {
   class TRawDataTimestampCharge;
}

class art::TRawDataTimestampCharge : public TRawDataObject {
public:
   TRawDataTimestampCharge();
   virtual ~TRawDataTimestampCharge();

   TRawDataTimestampCharge(const TRawDataTimestampCharge& rhs);
   TRawDataTimestampCharge& operator=(const TRawDataTimestampCharge& rhs);

   Double_t GetTiming() const { return fTiming; }
   Double_t GetCharge() const { return fCharge; }
   ULong64_t GetABS() const { return fABS; }
   UInt_t GetABSdeci() const { return fABSdeci; }
   UShort_t GetfChannel() const { return fCh; }
   
   void SetTiming(Double_t timing) { fTiming = timing; }
   void SetCharge(Double_t charge) { fCharge = charge; }
   void SetABS(ULong64_t abs) { fABS = abs; }
   void SetABSdeci(UInt_t absdeci) { fABSdeci = absdeci; }
   void SetfChannel(UShort_t ch) { fCh = ch; }
     
      
protected:
   Double_t fCharge;
   Double_t fTiming;
   ULong64_t fABS;
   UInt_t fABSdeci;
   UShort_t fCh;

private:

   ClassDef(TRawDataTimestampCharge,1) // raw data with timing and charge
};

#endif // _TRAWDATARIMESTAMPCHARGE_H_
