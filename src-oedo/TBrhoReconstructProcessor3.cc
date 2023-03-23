/**
 * @file		TBrhoReconstProcessor3.cc
 * @brief		S1 Brho reconstruction with SR-PPACs, and simple matrix elements
 *
 * @date		Created				: 2023-Jan-24 
 *
 * @author T. Chillery
 *
 */

#include "TBrhoReconstructProcessor3.h"
#include <TClonesArray.h>
#include <TMWDCTrackingResult.h>
#include <TSimpleData.h>
#include <TMath.h>
#include <TArtSystemOfUnit.h>
#include "TSRPPACPlaneProcessor.h"
#include "TSRPPACParameter.h"


using art::TBrhoReconstructProcessor3;
using namespace TArtSystemOfUnit;

ClassImp(TBrhoReconstructProcessor3)

TBrhoReconstructProcessor3::TBrhoReconstructProcessor3()
{
   RegisterInputCollection("InputName1","name of sr-ppac12 1x",
                           fInputName1,TString("src1_x"),
                           &fInPut1,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName2","name of sr-ppac12 1y",
                           fInputName2,TString("src1_y"),
                           &fInPut2,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName3","name of sr-ppac12 2x",
                           fInputName3,TString("src2_x"),
                           &fInPut3,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName4","name of sr-ppac12 2y",
                           fInputName4,TString("src2_y"),
                           &fInPut4,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName5","name of sr-ppacS1 1x",
                           fInputName5,TString("sr11_x"),
                           &fInPut5,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName6","name of sr-ppacS1 1y",
                           fInputName6,TString("sr11_y"),
                           &fInPut6,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName7","name of sr-ppacS1 2x",
                           fInputName7,TString("src21_x"),
                           &fInPut7,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("InputName8","name of sr-ppacS1 2y",
                           fInputName8,TString("src21_y"),
                           &fInPut8,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());

   RegisterOutputCollection("OutputName","name of output collection",
                            fOutputName,TString("brhos1Simple"),
                            &fOutput,TClonesArray::Class_Name(),TSimpleData::Class_Name());

   RegisterProcessorParameter("Brho0","brho of central ray",
                              fBrho0,(Float_t)0.);

   RegisterProcessorParameter("Z","z position of focus of exit (mode 1) or entrance (mode 2)",
                              fZ,(Float_t)0.);

   RegisterProcessorParameter("Mode","0: both tracks on focus, 1: only entrance track on focus, 2: only exit track on focus",
                              fMode,(Int_t)0);

}

TBrhoReconstructProcessor3::~TBrhoReconstructProcessor3()
{
}

TBrhoReconstructProcessor3::TBrhoReconstructProcessor3(const TBrhoReconstructProcessor3& rhs)
{
}

TBrhoReconstructProcessor3& TBrhoReconstructProcessor3::operator=(const TBrhoReconstructProcessor3& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TBrhoReconstructProcessor3::Init(TEventCollection* )
{
}

void TBrhoReconstructProcessor3::Process()
{
  //   TMWDCTrackingResult *track1 = ((TMWDCTrackingResult*) (*fInput1)->At(0));
  //   TMWDCTrackingResult *track2 = ((TMWDCTrackingResult*) (*fInput2)->At(0));

  fOutput->Clear("C");

  if((*fInPut1)->GetEntriesFast()==0 ||
     (*fInPut2)->GetEntriesFast()==0 ||
     (*fInPut3)->GetEntriesFast()==0 ||
     (*fInPut4)->GetEntriesFast()==0 ||
     (*fInPut5)->GetEntriesFast()==0 ||
     (*fInPut6)->GetEntriesFast()==0 ||
     (*fInPut7)->GetEntriesFast()==0 ||
     (*fInPut8)->GetEntriesFast()==0 ) return;

   //   const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSi)->At(i));
   const art::TSRPPACPlaneData* const src1x = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut1)->At(0));
   const art::TSRPPACPlaneData* const src1y = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut2)->At(0));
   const art::TSRPPACPlaneData* const src2x = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut3)->At(0));
   const art::TSRPPACPlaneData* const src2y = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut4)->At(0));
   const art::TSRPPACPlaneData* const sr11x = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut5)->At(0));
   const art::TSRPPACPlaneData* const sr11y = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut6)->At(0));
   const art::TSRPPACPlaneData* const sr12x = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut7)->At(0));
   const art::TSRPPACPlaneData* const sr12y = dynamic_cast<art::TSRPPACPlaneData*>((*fInPut8)->At(0));

  // obtain brhos1
  Double_t fe12_1_x = src1x->GetPosition();
  Double_t fe12_1_y = src1y->GetPosition();
  Double_t fe12_2_x = src2x->GetPosition();
  Double_t fe12_2_y = src2y->GetPosition();
  Double_t s1_1_x = sr11x->GetPosition();
  Double_t s1_1_y = sr11y->GetPosition();
  Double_t s1_2_x = sr12x->GetPosition();
  Double_t s1_2_y = sr12y->GetPosition();

  Double_t s0x = (1972.*fe12_2_x - 1452.*fe12_1_x)/520.;
  Double_t s0a = (fe12_2_x-fe12_1_x)/520. * 1000.;
  Double_t s0y = (1972.*fe12_2_y - 1452.*fe12_1_y)/520.;
  Double_t s0b = (fe12_2_y-fe12_1_y)/520. * 1000.;
  Double_t s0z = 1972.;
  Double_t s0l = fZ - s0z;
  Double_t s1x = (560.8*s1_2_x - 210.8*s1_1_x)/350.;
  Double_t s1a = (s1_2_x - s1_1_x)/350.*1000.;
  Double_t s1y = (560.8*s1_2_y-210.8*s1_1_y)/350.;
  Double_t s1b = (s1_2_y-s1_1_y)/350.;
  Double_t s1z = 560.8;
  Double_t s1l = fZ - s1z;
      
  Double_t xd  = -2222; // [mm]
  Double_t xad =   50.; // [mm/mrad]
  Double_t xx  =  -0.4;

  Double_t dlt = (s1x - xx*s0x)/(xd + xad*s0a);

  TSimpleData *data = (TSimpleData*)fOutput->ConstructedAt(fOutput->GetEntriesFast());
  data->SetValue(fBrho0 * (1+dlt));
      
  //      std::cout<< fBrho0*(1+dlt) << std::endl;

  //   return;

      
}
