/**
 * @file   linkdef_user.h
 * @brief
 *
 * @date   Created:       2013-08-12 14:48:07
 *         Last Modified: 2019-11-07 20:00:41 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2021 OTA Shinsuke All rights reserved
 */
#ifndef LINKDEF_USER_H
#define LINKDEF_USER_H


#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class art::TModuleDecoderAMTTDC;
#pragma link C++ class art::TDaliData;
#pragma link C++ class art::TDaliProcessor;
#pragma link C++ class art::TReplaceIDProcessor;
#pragma link C++ class art::TTimingAverageProcessor;

#endif // __CINT__

#endif // LINKDEF_USER_H

