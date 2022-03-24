/**
 * @file   TPIDSingleSectionProcessor.cc
 * @brief  reconstruct Brho35, Brho57 using F3, F5, F7 information
 *
 * @date   Created       : 2015-04-15 15:31:28 JST
 *         Last Modified : Jun 07, 2015 06:37:49 JST
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 Shinsuke OTA
 */

#include "TPIDSingleSectionProcessor.h"
#include <TClonesArray.h>
#include <TMWDCTrackingResult.h>
#include <TSimpleData.h>
#include <TMath.h>
#include <TArtSystemOfUnit.h>
#include <ICharge.h>


using art::TPIDSingleSectionProcessor;
using namespace TArtSystemOfUnit;

ClassImp(TPIDSingleSectionProcessor)

TPIDSingleSectionProcessor::TPIDSingleSectionProcessor()
{
   RegisterInputCollection("InputNameBrho","name of brho",
                           fInputNameBrho,"brho35",
                           &fInputBrho,TClonesArray::Class_Name(),TSimpleData::Class_Name());
   RegisterInputCollection("InputNameBeta","name of beta",
                           fInputNameBeta,"beta35",
                           &fInputBeta,TClonesArray::Class_Name(),TSimpleData::Class_Name());
   RegisterInputCollection("InputNameDE","name of de at f3 si",
                           fInputNameDE,"de35",
                           &fInputDE,TClonesArray::Class_Name(),ICharge::Class_Name());
   RegisterOutputCollection("OutputNameAQ","name of output a/q",
                            fOutputNameAQ,"aq35",
                            &fOutputAQ,TClonesArray::Class_Name(),TSimpleData::Class_Name());
   RegisterOutputCollection("OutputNameZ","name of output z",
                            fOutputNameZ,"z35",
                            &fOutputZ,TClonesArray::Class_Name(),TSimpleData::Class_Name());
}

TPIDSingleSectionProcessor::~TPIDSingleSectionProcessor()
{
}

TPIDSingleSectionProcessor::TPIDSingleSectionProcessor(const TPIDSingleSectionProcessor& rhs)
{
}

TPIDSingleSectionProcessor& TPIDSingleSectionProcessor::operator=(const TPIDSingleSectionProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}
void TPIDSingleSectionProcessor::Init(TEventCollection* )
{

}

void TPIDSingleSectionProcessor::Process()
{

   const Double_t  mass = 931.494; // MeV
   const Double_t  wf = 5907.5;

   fOutputAQ->Clear("C");
   fOutputZ->Clear("C");
   TClonesArray *aBrho = *fInputBrho;
   TClonesArray *aBeta  = *fInputBeta;
   TClonesArray *aDE  = *fInputDE;
   if (!aBrho->GetEntriesFast() ||
       !aBeta->GetEntriesFast() ||
       !aDE->GetEntriesFast() ) return;
   Double_t brho = (static_cast<TSimpleData*>(aBrho->At(0)))->GetValue();
   Double_t beta = (static_cast<TSimpleData*>(aBeta->At(0)))->GetValue();
   Double_t de = (dynamic_cast<ICharge*>(aDE->At(0)))->GetCharge();
   Double_t aq   = brho * TMath::Sqrt(1-beta*beta) / beta * TMath::C()/1e6/mass;
   Double_t de_v = TMath::Log(wf * beta * beta) - TMath::Log(1-beta*beta) - beta*beta;
   Double_t Zed  = 1.623  + 7.45113 *TMath::Sqrt(de/de_v) * beta; // OEDO com 107Pd
//   Double_t Zed  = 0.79532  + 7.45113 *TMath::Sqrt(de/de_v) * beta; // OEDO com 79Se
//   Double_t Zed  = 0.59605  + 7.40131 *TMath::Sqrt(charge/de_v) * beta;
      
   TSimpleData *data = (TSimpleData*)fOutputAQ->ConstructedAt(0);
   data->SetValue(aq);
   TSimpleData *dataZ = (TSimpleData*)fOutputZ->ConstructedAt(0);
   dataZ->SetValue(Zed);
}
