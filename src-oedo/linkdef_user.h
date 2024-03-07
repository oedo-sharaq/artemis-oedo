/**
 * @file   linkdef_user.h
 * @brief
 *
 * @date   Created:       2013-08-12 14:48:07
 *         Last Modified: Apr 16, 2015 04:19:02 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro, OTA Shinsuke All rights reserved
 */
#ifndef LINKDEF_USER_H
#define LINKDEF_USER_H

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class art::TChargeValidateProcessor;
#pragma link C++ class art::TTimeValidator;
#pragma link C++ class art::TDssdProcessor;
#pragma link C++ class art::TDssdCalProcessor;
#pragma link C++ class art::TDssdData;
#pragma link C++ class art::TTinaProcessor2;
#pragma link C++ class art::TTinaData2;
#pragma link C++ class art::TDaliProcessor;
#pragma link C++ class art::TDaliData;
//#pragma link C++ class art::TModuleDecoderA3100;
#pragma link C++ class art::TRawDataTimestampCharge;
#pragma link C++ class art::TModuleDecoderAPV8008;
#pragma link C++ class art::TModuleDecoderTimestamp;
#pragma link C++ class art::TTimingChargeAPV8008Processor;
#pragma link C++ class art::TAPV8008Data;
#pragma link C++ class art::TMergerData;
#pragma link C++ class art::TMergerProcessor;
#pragma link C++ class art::TModuleDecoderA3100FreeRunTSI;
#pragma link C++ class art::TModuleDecoderSIS3301;
#pragma link C++ class art::TSimpleDataMappingProcessor;
#pragma link C++ class art::TIonChamberProcessor;
#pragma link C++ class art::TS1IonChamberProcessor;
#pragma link C++ class art::TIonChamberProcessor;
#pragma link C++ class art::TPPACAnodeTimingProcessor;
#pragma link C++ class art::TTimingAverageProcessor;
#pragma link C++ class art::TSingleTOFProcessor;
#pragma link C++ class art::TTOF2BetaProcessor;
#pragma link C++ class art::TCmdSave;
#pragma link C++ class art::TCmdPrint;
#pragma link C++ class art::TPPACProcessorQTC;
#pragma link C++ class art::TBrhoReconstructProcessor;
#pragma link C++ class art::TBrhoReconstructProcessorS1;
#pragma link C++ class art::TPIDSingleSectionProcessor;
#pragma link C++ class art::TCmdPadZoom;
#pragma link C++ class art::TModuleDecoderTC842;
#pragma link C++ class art::TRawDataTriggeredList;
#pragma link C++ class art::TTimingChargeTriggeredListMappingProcessor;
#pragma link C++ class art::TExpConverter;
#pragma link C++ class art::TDiaData;
#pragma link C++ class art::TDiaTimingData;
#pragma link C++ class art::TDiaPadData;
#pragma link C++ class art::TDiaStripData;
#pragma link C++ class art::TDiaTimingDataMappingProcessor;
#pragma link C++ class art::TDiaStripCalibrationProcessor;
#pragma link C++ class art::TDiaPadCalibrationProcessor;
#pragma link C++ class art::TDiaTimingProcessor;
#pragma link C++ class art::TDiaStripTimingProcessor;
#pragma link C++ class art::TDiaStripTimingEachProcessor;
#pragma link C++ class art::TDiaTimingSubtractionProcessor;
#pragma link C++ class art::TDiaPadTimingSubtractionProcessor;
#pragma link C++ class art::TMassData;
#pragma link C++ class art::TMahalaData;
#pragma link C++ class art::TPIDwTOFPPACSSDProcessor;
#pragma link C++ class art::TPIDwTOFPPACSSDCalProcessor;
#pragma link C++ class art::TMassCalibrationConverter;
#pragma link C++ class art::TMahalanobisDistance;
#pragma link C++ class art::TMahalanobisDistanceTinc;
#pragma link C++ class art::TTc842TwoSidedCalibrationProcessor;
#pragma link C++ class art::TDiaStripTimingEachMergeProcessor;
#pragma link C++ class art::TDiaStripTimingEachMergeToffsetProcessor;
#pragma link C++ class art::TMWDCTrackingAllLRCombination;
#pragma link C++ class art::TMWDCTrackingAllLRCombinationResult;
#pragma link C++ class art::TQuitProcessor;
//#pragma link C++ class art::TDssdCalibrationProcessor;
#endif // __CINT__

#endif // LINKDEF_USER_H
