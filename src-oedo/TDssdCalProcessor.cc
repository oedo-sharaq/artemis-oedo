#include "TDssdCalProcessor.h"
#include "TDssdData.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>

using art::TDssdCalProcessor;

ClassImp(TDssdCalProcessor)

TDssdCalProcessor::TDssdCalProcessor()
  : fOutput(NULL)
{
   RegisterInputCollection("SiXName","name of input collection for Si x",
			   fSiXName,TString("s2wx"),
			   &fSix,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("s2dssd"),
			    &fOutput,TClonesArray::Class_Name(),art::TDssdData::Class_Name());
}

TDssdCalProcessor::~TDssdCalProcessor()
{
}

void TDssdCalProcessor::Process()
{

   fOutput->Clear("C");

   // look for max in DSSDx
   if ((*fSix)->GetEntriesFast() == 0) return;

   std::vector<Double_t> sixarr(16, 0);
   for(Int_t i = 0, n = (*fSix)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSix)->At(i))->GetID();
      if(id < 16){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSix)->At(i));
	 sixarr[id] = ic->GetCharge();
      }
   }
   if (sixarr.empty()) return;

   std::vector<Double_t>::iterator sixmaxit = std::max_element(sixarr.begin(), sixarr.end());
   Int_t sixmaxid = std::distance(sixarr.begin(), sixmaxit);

   //   if(*simaxit < 0.5) return;
   if(*sixmaxit < 0.1) return;

   TDssdData* out = static_cast<TDssdData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   Double_t ssd_cal =  0.9253 * (*sixmaxit) - 12.221;
   out->SetEx(ssd_cal);
   out->SetXID(sixmaxid);

   /*   // look for max in DSSDy
   if ((*fSiy)->GetEntriesFast() == 0) return;

   std::vector<Double_t> siyarr(16, 0);
   for(Int_t i = 0, n = (*fSiy)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSiy)->At(i))->GetID();
      if(id < 16){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSiy)->At(i));
	 siyarr[id] = ic->GetCharge();
      }
   }
   if (siyarr.empty()) return;

   std::vector<Double_t>::iterator siymaxit = std::max_element(siyarr.begin(), siyarr.end());
   Int_t siymaxid = std::distance(siyarr.begin(), siymaxit);

   if(*siymaxit < 0.1) return;

   out->SetEy(*siymaxit);
   out->SetYID(siymaxid);
   */

}
