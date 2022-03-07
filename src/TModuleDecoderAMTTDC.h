/*
 * @file TModuleDecoderAMTTDC.h
 * @date  Created : 2021.05.11 JST
 *  Last Modified : 2021.05.13 JST (HJKT)
 *--------------------------------------------------------
 *    Comment : modified to use data container TRawTimingWithEdge
 *
 *--------------------------------------------------------
 *    Copyright (C) Yuto HIJIAKTA
 */
#ifndef TMODULEDECODERAMTTDC_H
#define TMODULEDECODERAMTTDC_H
#include <TModuleDecoder.h>

namespace art {
   class TModuleDecoderAMTTDC;
}

class art::TModuleDecoderAMTTDC  : public TModuleDecoder {
public:
   static const int kID = 59;

   TModuleDecoderAMTTDC();         // constructor with default id = kID for compatibility
   TModuleDecoderAMTTDC(Int_t id); // constructor with id
   virtual ~TModuleDecoderAMTTDC();
   virtual Int_t Decode(char* buffer, const int &size, TObjArray *seg);
/*
   static const unsigned int kHeaderMask        = 0xf8000000;
   static const unsigned int kGlobalHeader      = 0x40000000;
   static const unsigned int kTDCHeader         = 0x08000000;
   static const unsigned int kTDCMeasurement    = 0x00000000;
   static const unsigned int kTDCTrailer        = 0x18000000;
   static const unsigned int kTDCError          = 0x20000000;
   static const unsigned int kGlobalTrailer     = 0x80000000;
   static const unsigned int kMaskGeometry      = 0x0000001f;
   static const unsigned int kMaskEventCounter  = 0x7ffffe0;
   static const unsigned int kMaskBunchID       = 0x00000fff;
   static const unsigned int kMaskEventID       = 0x00000fff;
   static const unsigned int kMaskChannel       = 0x03f80000;
   static const unsigned int kMaskMeasure       = 0x0007ffff;
   static const unsigned int kMaskEdgeType      = 0x04000000;
   static const int kShiftGeometry     = 0;
   static const int kShiftEventCounter = 5;
   static const int kShiftBunchID      = 0;
   static const int kShiftEventID      = 12;
   static const int kShiftChannel      = 19;
   static const int kShiftMeasure      = 0;
   static const int kShiftEdgeType     = 26;
*/
   static const unsigned int kHeaderMask             = 0xe0000000;
   static const unsigned int kRecordingDataStatus    = 0xa0000000;
   static const unsigned int kStartStopTime          = 0xc0000000;
   static const unsigned int kHitData                = 0x00000000;
   static const unsigned int kErrorReport            = 0x60000000;
   static const unsigned int kEndOfData              = 0x40000000;

   static const unsigned int kMaskTotalRecordingData = 0x1fff0000;
   static const unsigned int kMaskEventNumber        = 0x0000ffff;
   static const unsigned int kMaskModuleID           = 0x1f000000;
   static const unsigned int kMaskWidthSelect        = 0x00700000;
   static const unsigned int kMaskEdgeDetection      = 0x000c0000;
   static const unsigned int kMaskMeasurementControl = 0x00020000;
   static const unsigned int kMaskCommonTime         = 0x0001ffff;
   static const unsigned int kMaskFallOrRise         = 0x10000000;
   static const unsigned int kMaskChannelNumber      = 0x03f00000;
   static const unsigned int kMaskHitTimeData        = 0x000fffff;
   static const unsigned int kMaskOVR                = 0x00020000;
   static const unsigned int kMaskError              = 0x00010000;
   static const unsigned int kMaskAMT                = 0x0000c000;
   static const unsigned int kMaskAMTErrorFlags      = 0x00003000;
   static const unsigned int kMaskEndOfData          = 0xffff0000;

protected:
   TObjArray *fHitData; // array to temporally store the data for the aggregation

   ClassDef(TModuleDecoderAMTTDC,0); // decoder for module AMTTDC
};
#endif // end of #ifdef TMODULEDECODERAMTTDC_H
