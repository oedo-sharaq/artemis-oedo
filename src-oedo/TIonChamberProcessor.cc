
/**
 * @file   TIonChamberProcessor.cc
 * @brief  ion chamber analysis
 *
 * @date   Created       : 2015-05-26 15:11:55 JST
 *         Last Modified : 2015-05-27 13:27:31 JST (kawase)
 * @author KAWASE Shoichiro <kawase@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2015 KAWASE Shoichiro
 */

#include "TIonChamberProcessor.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>

#include <TSimpleData.h>
#include <ICharge.h>

using art::TIonChamberProcessor;

ClassImp(TIonChamberProcessor)

TIonChamberProcessor::TIonChamberProcessor()
  : fOutput(NULL)
{
   RegisterInputCollection("InputName","name of input collection for IC",
			   fInputName,TString("f7ic_raw"),
			   &fInput,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterProcessorParameter("DropRatio","accept if data is greater than ... times of 0ch (default: 0.)",
			      fDropRatio,0.f);
   RegisterProcessorParameter("NumChannel","number of channel of IC",
			      fNumCh,6);
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("f7ic"),
			    &fOutput,TClonesArray::Class_Name(),art::TSimpleData::Class_Name());
}

TIonChamberProcessor::~TIonChamberProcessor()
{
}

void TIonChamberProcessor::Process()
{
   fOutput->Clear("C");
   if ((*fInput)->GetEntriesFast() == 0) return;

   std::vector<Double_t> array(fNumCh,0);

   for(Int_t i = 0, n = (*fInput)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fInput)->At(i))->GetID();
      if(id < fNumCh){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fInput)->At(i));
	 array[id] = ic->GetCharge();
      }
   }

   if (array.empty()) return;

   std::vector<Double_t>::iterator dropped =
      std::find_if(array.begin(),array.end(),
		   std::bind2nd(std::less<Double_t>(),array.front()*fDropRatio));

   const Double_t ave = std::accumulate(array.begin(),dropped,0.,std::plus<Double_t>()) / (dropped - array.begin());

   static_cast<TSimpleData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()))->SetValue(ave);
}
