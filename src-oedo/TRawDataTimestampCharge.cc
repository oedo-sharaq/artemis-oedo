/**
 * @file   TRawDataTimestampCharge.cc
 * @brief  timing charge raw data
 *
 * @date   Created       : 2015-10-04 17:59:25 JST
 *         Last Modified : 2015-10-04 18:24:24 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#include "TRawDataTimestampCharge.h"

using art::TRawDataTimestampCharge;

ClassImp(TRawDataTimestampCharge)

TRawDataTimestampCharge::TRawDataTimestampCharge()
{
}

TRawDataTimestampCharge::~TRawDataTimestampCharge()
{
}

TRawDataTimestampCharge::TRawDataTimestampCharge(const TRawDataTimestampCharge& rhs)
   : TRawDataObject(rhs)
{
}

TRawDataTimestampCharge& TRawDataTimestampCharge::operator=(const TRawDataTimestampCharge& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}
