#include "TMergerProcessor.h"
#include "TMergerData.h"

#include <TCategorizedData.h>
#include <TRawDataSimple.h>

#include "constant.h"


using art::TMergerProcessor;

ClassImp(art::TMergerProcessor)

TMergerProcessor::TMergerProcessor()
  : fOutput(NULL), fTimestamp(1)
{
   RegisterInputCollection("Input","rawdata object returned by TRIDFEventStore",fInputName,TString("catdata"),
			   &fInput,"art::TCategorizedData");
   RegisterOutputCollection("Output","name of output rootfile of pid_data",fOutputName,TString("pid_data"),
			   &fOutput, "TClonesArray", "art::TMergerData");
   RegisterProcessorParameter("CatID","Category ID of plastic",fCatID,250);

   RegisterProcessorParameter("Sparse","hit will be inserted at the index corresponding to its id if sparse is 0, otherwize hit will be added ordinaly (default: 1)",
                              fIsSparse,kTRUE);

//   RegisterProcessParameter("test_prm1","test parameter 1",
//			     ftest_prm1, 0);

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
   Info("Init","CatID: %d", fCatID);
   if (!fIsSparse) Info("Init","Not sparse.");
}

void TMergerProcessor::Process()
{
   fOutput->Clear("C");
   TSProcess();
}


void TMergerProcessor::TSProcess()
{
   const TObjArray *const cat = (*fInput)->FindCategory(fCatID);
   if (!cat){
     printf("cannot find category\n");
     return;
   }

   for(Int_t i = 0, n = cat->GetEntriesFast(); i != n ; ++i){
      const TObjArray *const det = static_cast<TObjArray*>(cat->At(i));
      const TObjArray *const qArray = static_cast<TObjArray*>(det->At(0)); //0 or 1??? fTimingTypeID
      if (!qArray || qArray->IsEmpty()) continue;
      TSStoreMain(qArray);
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

void TMergerProcessor::TSStoreMain(const TObjArray *qArray)
{
   if (!qArray || qArray->IsEmpty()) return;

   TMergerData *data = NULL;
   for(Int_t iHit = 0, nHit = qArray->GetEntriesFast(); iHit != nHit; ++iHit) {
   //for(Int_t iHit = 0; iHit < 1; ++iHit) {
      const TRawDataSimple<ULong64_t> *const hit
         = static_cast<TRawDataSimple<ULong64_t>*>(qArray->At(iHit));
      const ULong64_t ts = hit->Get();
      if(ts < 10000) continue; //cut strange data

      const Int_t detID = hit->GetDetID();
      const Int_t idx = fIsSparse ? fOutput->GetEntriesFast() : detID;
      data = static_cast<TMergerData*>(fOutput->ConstructedAt(idx));


      //std::cout << ts << std::endl;
      data->SetTimestamp(ts);

      data = NULL;
   }
}
