/**
 * @file   linkdef_user.h
 * @brief
 *
 * @date   Created:       2013-08-12 14:48:07
 *         Last Modified: 2019-08-30 19:45:02 JST (ota)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro, OTA Shinsuke All rights reserved
 */
#ifndef LINKDEF_USER_H
#define LINKDEF_USER_H


#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// segment and category
#pragma link C++ class art::TSRPPACPlaneData+;
#pragma link C++ class art::TSRPPACPlaneProcessor;
#pragma link C++ class art::TSRPPACPlaneDqdxProcessor;
#pragma link C++ class art::TSRPPACPlaneSideDqdxProcessor;
#pragma link C++ class art::TSRPPACParameter;
#pragma link C++ class art::TSRPPACPlaneCalibrationTask;
#pragma link C++ class art::TGSRPPACCalibration;
#pragma link C++ class art::TSRPPACCalibrationProcessor;
#endif // __CINT__

#endif // LINKDEF_USER_H

