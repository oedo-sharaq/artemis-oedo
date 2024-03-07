/**
 * @file   TTimingChargeAPV8008Processor.h
 * @brief
 *
 * @date   Created:       2013-08-12 12:36:40
 *         Last Modified: 2014-06-18 11:03:41 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro All rights reserved
 */

#ifndef TTIMINGCHARGEAPV8008PROCESSOR_H
#define TTIMINGCHARGEAPV8008PROCESSOR_H

#include <TProcessor.h>

namespace art{
   class TTimingChargeAPV8008Processor;
   class TCategorizedData;
}

class art::TTimingChargeAPV8008Processor : public TProcessor {

public:
   // Default constructor
   TTimingChargeAPV8008Processor();
   virtual ~TTimingChargeAPV8008Processor();

   virtual void Init(TEventCollection*);
   virtual void Process();

protected:
   TString            fInputColName;
   TString            fOutputColName;
   TCategorizedData **fCategorizedData; //!
   TClonesArray      *fPlastic;

   Int_t  fCatID;        // default: 21 (spla in anapaw)
   Int_t  fChargeType;   // 0: V1190 width (default), 1: QDC (V792 etc)
   Int_t  fChargeTypeID; // used only when fChargeType is QDC
   Int_t  fTimingTypeID; // Typeid for timing (& width when fChargeType is V1190width)
   Bool_t fTrailingComesFirst; // F: TL->TT (default), T: TT->TL (for QTC etc.)

   Bool_t fIsSparse;

   Double_t fCh1gain;
   Double_t fCh2gain;
   Double_t fCh3gain;
   Double_t fCh4gain;
   Double_t fCh1offset;
   Double_t fCh2offset;
   Double_t fCh3offset;
   Double_t fCh4offset;

private:
   // Copy constructor (prohibited)
   TTimingChargeAPV8008Processor(const TTimingChargeAPV8008Processor&);
   // Assignment operator (prohibited)
   TTimingChargeAPV8008Processor& operator=(const TTimingChargeAPV8008Processor&);

   void ChargeWithTS(const TObjArray*);

   ClassDef(TTimingChargeAPV8008Processor,0) // processor for mapping timine and charge data
};

#endif // TTIMINGCHARGEAPV8008PROCESSOR_H
