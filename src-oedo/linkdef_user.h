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
#pragma link C++ class art::TTinaProcessor;
#pragma link C++ class art::TTinaData;
#pragma link C++ class art::TDaliProcessor;
#pragma link C++ class art::TDaliData;
//#pragma link C++ class art::TModuleDecoderA3100;
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
#endif // __CINT__

#endif // LINKDEF_USER_H

