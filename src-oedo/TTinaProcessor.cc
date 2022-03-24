#include "TTinaProcessor.h"
#include "TTinaData.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>

using art::TTinaProcessor;

ClassImp(TTinaProcessor)

TTinaProcessor::TTinaProcessor()
  : fOutput(NULL)
{
   RegisterInputCollection("SiName","name of input collection for Si",
			   fSiName,TString("tinasi"),
			   &fSi,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("CsIName","name of input collection for CsI",
			   fCsIName,TString("tinacsi"),
			   &fCsI,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("tina"),
			    &fOutput,TClonesArray::Class_Name(),art::TTinaData::Class_Name());
}

TTinaProcessor::~TTinaProcessor()
{
}

void TTinaProcessor::Process()
{
   // id-angle conversion tables
   static double thetaconv[] =
   {
     9.19, 10.18, 11.19, 12.21,
     13.26, 14.33,15.42, 16.52,
     17.65,18.79,19.95,21.13,
     22.32,23.54,24.77,26.00
   };
   // tekitou do not trust
   static double phiconv[] =
   {
     0.0, 60.0, 120.0, 180.0, 240.0, 300.0
   };
   // angular coverage tables
   static double thetacoverage[] =
   {
     1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.1, 1.1,
     1.1, 1.1, 1.2, 1.2,
     1.2, 1.2, 1.2, 1.2
   };
   static double phicoverage[] =
   {
      60.0, 60.0, 60.0, 60.0, 60.0, 60.0
   };

   fOutput->Clear("C");

   // look for si max
   if ((*fSi)->GetEntriesFast() == 0) return;

   std::vector<Double_t> siarr(6*16, 0);
   for(Int_t i = 0, n = (*fSi)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSi)->At(i))->GetID();
      if(id < 6*16){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSi)->At(i));
	 siarr[id] = ic->GetCharge();
      }
   }
   if (siarr.empty()) return;

   std::vector<Double_t>::iterator simaxit = std::max_element(siarr.begin(), siarr.end());
   Int_t simaxidx = std::distance(siarr.begin(), simaxit);

   //   if(*simaxit < 0.5) return;
   if(*simaxit < 0.1) return;

   TTinaData* out = static_cast<TTinaData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   out->SetDeltaE(*simaxit);
   out->SetEnergy(*simaxit);
   Int_t stripid = simaxidx%16;
   Int_t detid = simaxidx/16;
   out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);


   // look for csi max
   if ((*fCsI)->GetEntriesFast() == 0) return;

   std::vector<Double_t> csiarr(32, 0);
   for(Int_t i = 0, n = (*fCsI)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fCsI)->At(i))->GetID();
      if(id < 32){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fCsI)->At(i));
	 csiarr[id] = ic->GetCharge();
      }
   }
   if (csiarr.empty()) return;

   std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
   Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);

   if(*csimaxit > 4000) return;

   out->SetEnergy(*simaxit + *csimaxit);
}
