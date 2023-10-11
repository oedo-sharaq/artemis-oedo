#include "TMergerProcessor.h"
#include "TMergerData.h"
#include "TTwoSidedPlasticData.h"
#include "TTimingChargeData.h"
#include "TSRPPACPlaneData.h"
#include "TDssdData.h"

#include <TCategorizedData.h>
#include <TClonesArray.h>
#include <TRawDataSimple.h>

#include "constant.h"


using art::TMergerProcessor;

ClassImp(art::TMergerProcessor)

TMergerProcessor::TMergerProcessor()
  : fInputCollection1(NULL), fInputCollection2(NULL), fInputCollection3(NULL), fInputCollection4(NULL), fInputCollection5(NULL)
{
   RegisterInputCollection("Input","rawdata object returned by TRIDFEventStore",fInputName,TString("catdata"),
			   &fInput,"art::TCategorizedData");

   RegisterInputCollection("InputCollection1","veto plastic s2",fInputName1,TString("vetopla"));
   RegisterInputCollection("InputCollection2","dia f3 pad",fInputName2,TString("dia3pad"));
   RegisterInputCollection("InputCollection3","dia s2 pad",fInputName3,TString("dias2pad"));
   RegisterInputCollection("InputCollection4","srppac s0 x",fInputName4,TString("sr0_x"));
   RegisterInputCollection("InputCollection5","s2 ssd",fInputName5,TString("S2ssd"));

   RegisterOutputCollection("Output","name of output rootfile of pid_data",fOutputName,TString("pid_data"),
			   &fOutput, "TClonesArray", "art::TMergerData");
   RegisterProcessorParameter("CatID","Category ID of plastic",fCatID,150);

   RegisterProcessorParameter("Sparse","hit will be inserted at the index corresponding to its id if sparse is 0, otherwize hit will be added ordinaly (default: 1)",
                              fIsSparse,kTRUE);

}

TMergerProcessor::~TMergerProcessor()
{
   delete fOutput;
}

TMergerProcessor::TMergerProcessor(const TMergerProcessor& rhs)
{
}

TMergerProcessor& TMergerProcessor::operator=(const TMergerProcessor& rhs)
{
   if(this != &rhs){
   }
   return *this;
}

void TMergerProcessor::Init(TEventCollection *col)
{
   Info("Init","%s",fInputName1.Data());
   fInputCollection1 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName1.Data()));
   if (!fInputCollection1) {
      SetStateError(TString::Format("input not found: %s",fInputName1.Data()));
      return;
   }
   Info("Init","%s",fInputName2.Data());
   fInputCollection2 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName2.Data()));
   if (!fInputCollection2) {
      SetStateError(TString::Format("input not found: %s",fInputName2.Data()));
      return;
   }
   Info("Init","%s",fInputName3.Data());
   fInputCollection3 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName3.Data()));
   if (!fInputCollection3) {
      SetStateError(TString::Format("input not found: %s",fInputName3.Data()));
      return;
   }
   Info("Init","%s",fInputName4.Data());
   fInputCollection4 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName4.Data()));
   if (!fInputCollection4) {
      SetStateError(TString::Format("input not found: %s",fInputName4.Data()));
      return;
   }
   Info("Init","%s",fInputName5.Data());
   fInputCollection5 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputName5.Data()));
   if (!fInputCollection5) {
      SetStateError(TString::Format("input not found: %s",fInputName5.Data()));
      return;
   }

   Info("Init","Timestamp CatID: %d", fCatID);
   if (!fIsSparse) Info("Init","Not sparse.");
}

void TMergerProcessor::Process()
{
   fOutput->Clear("C");

   const TObjArray *const cat = (*fInput)->FindCategory(fCatID);
   if (!cat){
     printf("cannot find category\n");
     return;
   }

   //std::cout << cat->GetEntriesFast() << std::endl;
   for(Int_t i = 0, n = cat->GetEntriesFast(); i != n ; ++i){
      const TObjArray *const det = static_cast<TObjArray*>(cat->At(i));
      const TObjArray *const qArray = static_cast<TObjArray*>(det->At(0));
      if (!qArray || qArray->IsEmpty()) continue;
      //std::cout << "\t" << i << std::endl;
      StoreMain(qArray);
   }

   if (fIsSparse) {
      TMergerData::SetSortType(TMergerData::kTiming);
      TMergerData::SetSortOrder(TMergerData::kASC);
      fOutput->Sort();
      fOutput->Compress();
   } else {
      for (Int_t i = 0, n = fOutput->GetEntriesFast(); i != n; ++i) {
         fOutput->ConstructedAt(i);
      }
   }
}

void TMergerProcessor::StoreMain(const TObjArray *qArray)
{
   if (!qArray || qArray->IsEmpty()) return;

   TMergerData *data = NULL;
   //std::cout << qArray->GetEntriesFast() << std::endl;
   for(Int_t iHit = 0, nHit = qArray->GetEntriesFast(); iHit != nHit; ++iHit) {
   //for(Int_t iHit = 0; iHit < 1; ++iHit) {
      const TRawDataSimple<ULong64_t> *const hit
         = static_cast<TRawDataSimple<ULong64_t>*>(qArray->At(iHit));
      const ULong64_t ts = hit->Get();
      if(ts < 10000) continue; //cut strange data

      const Int_t detID = hit->GetDetID();
      const Int_t idx = fIsSparse ? fOutput->GetEntriesFast() : detID;
      //std::cout << idx << std::endl;
      data = static_cast<TMergerData*>(fOutput->ConstructedAt(idx));

      //for pid data
      if(!(*fInputCollection1)->GetEntriesFast() || !(*fInputCollection2)->GetEntriesFast() || !(*fInputCollection3)->GetEntriesFast() || !(*fInputCollection4)->GetEntriesFast() || !(*fInputCollection5)->GetEntriesFast()){
         data->SetS2z(0.0);
         data->SetS2aq(0.0);
         data->SetVeto_tave(0.0);
         data->SetVeto_qave(0.0);
      }else{
         Double_t veto_t  = (dynamic_cast<TTwoSidedPlasticData*>((*fInputCollection1)->At(0)))->GetTAve();
         Double_t veto_q  = (dynamic_cast<TTwoSidedPlasticData*>((*fInputCollection1)->At(0)))->GetQAve();
         Double_t dia3_t  = (dynamic_cast<TTimingChargeData*>   ((*fInputCollection2)->At(0)))->GetTiming();
         Double_t dias2_t = (dynamic_cast<TTimingChargeData*>   ((*fInputCollection3)->At(0)))->GetTiming();
         Double_t sr0x_p  = (dynamic_cast<TSRPPACPlaneData*>    ((*fInputCollection4)->At(0)))->GetPosition();
         Double_t s2ssd_e = (dynamic_cast<TDssdData*>           ((*fInputCollection5)->At(0)))->GetEx();

         Double_t tof32 = dias2_t - dia3_t;
         Double_t s2brho = 4.4147*(1-sr0x_p/14856);
         Double_t s2beta=103499.78/(tof32-1455.)/299.79;
         Double_t s2gamma = 1/TMath::Sqrt(1-(s2beta)*(s2beta));
         Double_t s2de=1.03827*s2ssd_e;
         Double_t de_v = TMath::Log(5907.5*s2beta*s2beta)-TMath::Log(1.-s2beta*s2beta)-s2beta*s2beta;

         Double_t s2aq = s2brho * 299.79 / (s2gamma * s2beta * 931.49);
         Double_t s2z = -0.0513 + 7.451*TMath::Sqrt(s2de/de_v) * s2beta;

         data->SetS2z(s2z);
         data->SetS2aq(s2aq);
         data->SetVeto_tave(veto_t);
         data->SetVeto_qave(veto_q);

         //data->Setdias2t(dias2_t);
         //data->Setdia3t(dia3_t);
         //data->SetS2x(sr0x_p);
         //data->SetS2ssde(s2ssd_e);
      }

      //std::cout << ts << std::endl;
      data->SetULongTimestamp(ts);
      data->SetfTimestamp((Double_t)ts*10.0);

      data = NULL;
   }
}

