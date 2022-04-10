
/**
 * @file		TBrhoReconstProcessorS1.cc
 * @brief		S1 Brho reconstruction
 *
 * @date		Created				: 2018-1-5 (dozono)
 *
 * @author DOZONO Masanori <dozno@cns.s.u-tokyo.ac.jp>
 *
 */

#include "TBrhoReconstructProcessorS1.h"
#include <TClonesArray.h>
#include <TMWDCTrackingResult.h>
#include <TSimpleData.h>
#include <TMath.h>
#include <TArtSystemOfUnit.h>


using art::TBrhoReconstructProcessorS1;
using namespace TArtSystemOfUnit;

ClassImp(TBrhoReconstructProcessorS1)

TBrhoReconstructProcessorS1::TBrhoReconstructProcessorS1()
{
   RegisterInputCollection("InputName1","name of tracking result at entrance focus",
                           fInputName1,TString("f3"),
                           &fInput1,TClonesArray::Class_Name(),TTrack::Class_Name());
   RegisterInputCollection("InputName2","name of tracking result at exit focus",
                           fInputName2,TString("f5"),
                           &fInput2,TClonesArray::Class_Name(),TTrack::Class_Name());

   RegisterOutputCollection("OutputName","name of output collection",
                            fOutputName,TString("brhos1"),
                            &fOutput,TClonesArray::Class_Name(),TSimpleData::Class_Name());

   RegisterProcessorParameter("Brho0","brho of central ray",
                              fBrho0,(Float_t)0.);

   RegisterProcessorParameter("Z","z position of focus of exit (mode 1) or entrance (mode 2)",
                              fZ,(Float_t)0.);

   RegisterProcessorParameter("Mode","0: both tracks on focus, 1: only entrance track on focus, 2: only exit track on focus",
                              fMode,(Int_t)0);

//   RegisterProcessorParameter("Section","section 35: F3-F5, 57: F5-F7",
//                              fSection,(Int_t)35);

   
}

TBrhoReconstructProcessorS1::~TBrhoReconstructProcessorS1()
{
}

TBrhoReconstructProcessorS1::TBrhoReconstructProcessorS1(const TBrhoReconstructProcessorS1& rhs)
{
}

TBrhoReconstructProcessorS1& TBrhoReconstructProcessorS1::operator=(const TBrhoReconstructProcessorS1& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}
/*
  (x|x)         (a|x)         (y|x)         (b|x)         (l|x)
  (x|a)         (a|a)         (y|a)         (b|a)         (l|a)
  (x|y)         (a|y)         (y|y)         (b|y)         (l|y)
  (x|b)         (a|b)         (y|b)         (b|b)         (l|b)
  (x|l)         (a|l)         (y|l)         (b|l)         (l|l)
  (x|d)         (a|d)         (y|d)         (b|d)         (l|d)

  (F3-F5) from http://ribf.riken.jp/BigRIPSInfo/optics/fig/matrix_1st_7Tm.txt
  0.926591E+00 -0.196513E-01  0.            0.           -0.361262E-01  100000
 -0.471245E-02  0.107932E+01  0.            0.            0.194078E+01  010000
  0.            0.            0.103406E+01  0.291468E+00  0.            001000
  0.            0.           -0.222120E-01  0.960798E+00  0.            000100
  0.            0.            0.            0.            0.100000E+01  000010
  0.316690E+02  0.150266E-01  0.            0.            0.785482E+02  000001

  (F5-F7) from http://ribf.riken.jp/BigRIPSInfo/optics/fig/matrix_1st_7Tm.txt
  0.108043E+01 -0.182343E-01  0.            0.           -0.476105E-02  100000
  0.226346E-01  0.925174E+00  0.            0.           -0.179602E+01  010000
  0.            0.            0.962937E+00  0.294048E+00  0.            001000
  0.            0.           -0.269719E-01  0.103025E+01  0.            000100
  0.            0.            0.            0.            0.100000E+01  000010
 -0.341741E+02  0.654360E+00  0.            0.            0.785442E+02  000001  
 */
void TBrhoReconstructProcessorS1::Init(TEventCollection* )
{

   fMatrix = new TMatrixD(6,6);
   TMatrixD &m = *fMatrix;
   m[0][0] = -0.799825; // xx
   m[0][1] = 0.0; // xa
   m[1][0] = -0.88; // ax
   m[1][1] = -1.42; // aa
   m[0][5] = -2055.; // xd
   m[1][5] = -1022.; // ad
   
/*
   if (fSection == 35) {
      m[0][0] = 0.926591; // xx
      m[0][1] = -0.00471245 * mm / mrad; // xa
      m[1][0] = -0.0196513 * mrad / mm; // ax
      m[1][1] = 1.07932; // aa
      m[0][5] = 31.6690; // xd
      m[1][5] = 0.015266; // ad
   } else if (fSection == 57) {
      m[0][0] = 1.08043; // xx
      m[0][1] = 0.0226346 * mm / mrad; // xa
      m[1][0] = -0.0182343 * mrad / mm; // ax
      m[1][1] = 0.925174; // aa
      m[0][5] = -34.1741; // xd
      m[1][5] = 0.654360; // ad
   } else {
      SetStateError(TString::Format("Unknown section %d\n",fSection));
      return;
   }
*/
}

void TBrhoReconstructProcessorS1::Process()
{
   TMWDCTrackingResult *track1 = ((TMWDCTrackingResult*) (*fInput1)->At(0));
   TMWDCTrackingResult *track2 = ((TMWDCTrackingResult*) (*fInput2)->At(0));

   fOutput->Clear("C");
   if (track1 && track2) {
      // obtain brho35
      Double_t s0x = track1->GetTrack()->X();
      Double_t s0a = track1->GetTrack()->A()*1000.;
      Double_t s0y = track1->GetTrack()->Y();
      Double_t s0b = track1->GetTrack()->B()*1000.;
      Double_t s0z = track1->GetTrack()->Z();
      Double_t s0l = fZ - s0z;
      Double_t s1x = track2->GetTrack()->X();
      Double_t s1a = track2->GetTrack()->A()*1000.;
      Double_t s1y = track2->GetTrack()->Y();
      Double_t s1b = track2->GetTrack()->B()*1000.;
      Double_t s1z = track2->GetTrack()->Z();
      Double_t s1l = fZ - s1z;


      Double_t x0 = 0.0;
      Double_t xd = -2055.;
      Double_t xdd = -814.19;
      Double_t xddd = +12795.1;
      Double_t xa = 0.0;
      Double_t xad = 19.2342;
      Double_t xadd = -414.067;
      Double_t xaddd = 4882.33;
      Double_t xx = -0.799825;
      Double_t xxd = 11.402;
      Double_t xyy = -0.0493525;
      Double_t xyyd = -0.350427;
      Double_t xbb = 0.0237474;
      Double_t xbbbb = -0.392603E-05;
      
      Double_t a0 = 0.0;
      Double_t add = 0.0;
      Double_t ad = -1022;
      Double_t aa = -1.42;
      Double_t aad = 7.22942;
      Double_t ax = -0.88;
      Double_t ayy = -0.0163254;
      Double_t abb = 0.011862;
      Double_t abbbb = -1.99647E-05;
      
      Double_t dlt_rec[7];
      Double_t s0a_rec[7];


      dlt_rec[0] = (s1x-x0)/xd;
      s0a_rec[0] = (s1a-a0)/(aa+aad*dlt_rec[0]);
         
      Double_t s0btemp = 5.872;
      Double_t dlt;


      for (Int_t j=0;j<6;j++){
         Double_t d = dlt_rec[j];
         Double_t a = s0a_rec[j];
         Double_t ds1xca = xa * a + xad * a * d + xadd * a * d * d + xaddd * a * d * d * d;
         Double_t ds1xcx = xx * s0x + xxd * s0x * d;
         Double_t ds1xcy = xyy * s0y * s0y + xyyd * s0y * s0y * d;
         Double_t ds1xcb = xbb * s0btemp * s0btemp + xbbbb * s0btemp * s0btemp * s0btemp * s0btemp;
         Double_t coef[4];
         coef[0] = x0-s1x+ds1xca+ds1xcx+ds1xcy+ds1xcb;
         coef[1] = xd;
         coef[2] = xdd;
         coef[3] = xddd;
         
         Double_t roota;
         Double_t rootb;
         Double_t rootc;
         
         TMath::RootsCubic(coef,roota,rootb,rootc);
         dlt_rec[j+1] = rootb;
         
         
         d = dlt_rec[j+1];
         Double_t ds1acd = ad * d + add * d * d;
         Double_t ds1acx = ax * s0x;
         Double_t ds1acy = ayy * s0y * s0y;
         Double_t ds1acb = abb * s0btemp * s0btemp + abbbb * s0btemp * s0btemp * s0btemp * s0btemp;
         
         s0a_rec[j+1] = (s1a-a0-ds1acd-ds1acx-ds1acy-ds1acb)/(aa+aad*d);
         
      }

      dlt = dlt_rec[6];
      

      TSimpleData *data = (TSimpleData*)fOutput->ConstructedAt(fOutput->GetEntriesFast());
      data->SetValue(fBrho0 * (1+dlt));
   }

   return;

      
}
