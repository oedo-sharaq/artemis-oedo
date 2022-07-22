#include "TTinaProcessor3.h"
#include "TTinaData3.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>

using art::TTinaProcessor3;

ClassImp(TTinaProcessor3)

TTinaProcessor3::TTinaProcessor3()
  : fOutput(NULL)
{
   RegisterInputCollection("SifName","name of input collection for TTT front",
			   fSifName,TString("ttt_front"),
			   &fSif,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("SibName","name of input collection for TTT back",
			   fSibName,TString("ttt_back"),
			   &fSib,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("CsIName","name of input collection for CsI",
			   fCsIName,TString("tinacsi"),
			   &fCsI,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("tina3"),
			    &fOutput,TClonesArray::Class_Name(),art::TTinaData3::Class_Name());
}

TTinaProcessor3::~TTinaProcessor3()
{
}

void TTinaProcessor3::Process()
{

   fOutput->Clear("C");

   // look for front side TTT max
   if ((*fSif)->GetEntriesFast() == 0) return;

   std::vector<Double_t> ttt_front_arr(512, 0);
   for(Int_t i = 0, n = (*fSif)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSif)->At(i))->GetID();
      if(id < 512){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSif)->At(i));
	 ttt_front_arr[id] = ic->GetCharge();
      }
   }
   if (ttt_front_arr.empty()) return;

   // look for backside TTT max
   if ((*fSib)->GetEntriesFast() == 0) return;
   std::vector<Double_t> ttt_back_arr(512, 0);
   for(Int_t i = 0, n = (*fSib)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSib)->At(i))->GetID();
      if(id < 512){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSib)->At(i));
	 ttt_back_arr[id] = ic->GetCharge();
      }
   }
   if (ttt_back_arr.empty()) return;
   //----------------------------------------


   //sorting frontside
   std::vector<Double_t>::iterator tttf_maxit = std::max_element(ttt_front_arr.begin(), ttt_front_arr.end());
   Int_t tttf_maxid = std::distance(ttt_front_arr.begin(), tttf_maxit);
   //sorting backtside
   std::vector<Double_t>::iterator tttb_maxit = std::max_element(ttt_back_arr.begin(), ttt_back_arr.end());
   Int_t tttb_maxid = std::distance(ttt_back_arr.begin(), tttb_maxit);


   //   if(*simaxit < 0.5) return;
   if(*tttf_maxit < 0.1) return;
   TTinaData3* out = static_cast<TTinaData3*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   out->SetDeltaE(*tttf_maxit);
   out->SetEnergy(*tttf_maxit);
   Int_t x_stripid = tttf_maxid%128;
   Int_t z_stripid = tttb_maxid%128;
   Int_t detid = tttb_maxid/128;

   //collision point at taraget by tracking from fe12?
   Double_t colx,coly,colz;

   colx = 0;
   coly = 0;
   colz = 0;

   //hit point at TTT, strip pitch 0.76 mm, width 0.70 mm, length 97.22 mm
   Double_t hitx,hity,hitz;

   if(detid==0){
     hitx = -55.1;
     hity = x_stripid*0.76+(gRandom->Uniform())*0.70-48.61;
   }if(detid==1){
     hitx = -(x_stripid*0.76+(gRandom->Uniform())*0.70)+48.61;
     hity = -55.1;
   }if(detid==2){
     hitx = x_stripid*0.76+(gRandom->Uniform())*0.70-48.61;
     hity = 55.1;
   }if(detid==3){
     hitx = 55.1;
     hity = -(x_stripid*0.76+(gRandom->Uniform())*0.70)+48.61;
   }

     hitz = -(z_stripid*0.76+(gRandom->Uniform())*0.70)-14.14;

   //   out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   //   out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);
   const Double_t PI = 4.0*atan(1.0);
   out->SetTheta(acos((hitz-colz)/sqrt((hitx-colx)*(hitx-colx)+(hity-coly)*(hity-coly)+(hitz-colz)*(hitz-colz)))/PI*180.);
   if(hity-coly>=0){
   	 out->SetPhi(atan2(hity-coly,hitx-colx)/PI*180.);
   }else{out->SetPhi(atan2(hity-coly,hitx-colx)/PI*180.+360.);}

   // look for csi max
   if ((*fCsI)->GetEntriesFast() == 0) return;

   std::vector<Double_t> csiarr(16, 0);
   for(Int_t i = 0, n = (*fCsI)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fCsI)->At(i))->GetID();
      if(id < 16){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fCsI)->At(i));
	 csiarr[id] = ic->GetCharge();
      }
   }
   if (csiarr.empty()) return;

   std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
   Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);

   if(*csimaxit > 4000) return;

   out->SetEnergy(*tttf_maxit + *csimaxit);
}
