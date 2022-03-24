/**
 * @file   TSingleTOFProcessor.cc
 * @brief  calculate TOF from a pair of timing information
 *
 * @date   Created       : 2016-05-26 19:31:59 JST
 *         Last Modified : 2016-05-29 15:34:31 JST (kawase)
 * @author KAWASE Shoichiro <kawase@aees.kyushu-u.ac.jp>
 *
 *    (C) 2016 KAWASE Shoichiro
 */

#include "TSingleTOFProcessor.h"

#include <TClonesArray.h>
#include <TTimeDifference.h>

using art::TSingleTOFProcessor;

ClassImp(TSingleTOFProcessor)

namespace{
   const Int_t DEFAULT_ID = kMinInt;
}

TSingleTOFProcessor::TSingleTOFProcessor()
: fStartCollection(NULL), fStopCollection(NULL), fOutput(NULL) {
   RegisterInputCollection("StartCollection","name of input collection for start timing",
			   fStartColName,TString("pla"));
   RegisterOptionalParameter("StartID",
			     "detID of start timing."
			     "if not set, the 1st data in the collection will be used.",
			     fStartID,DEFAULT_ID);
   RegisterInputCollection("StopCollection","name of input collection for stop timing",
			   fStopColName,TString("pla"));
   RegisterOptionalParameter("StopID",
			     "detID of stop timing."
			     "if not set, the 1st data in the collection will be used.",
			     fStopID,DEFAULT_ID);
   RegisterOutputCollection("Output","name of output collection",
			    fOutputName,TString("tof"),
			    &fOutput,TClonesArray::Class_Name(),
			    TTimeDifference::Class_Name());
}

TSingleTOFProcessor::~TSingleTOFProcessor()
{
}


TClonesArray** TSingleTOFProcessor::LoadBranch(TEventCollection* col, const TString& name)
{
   TClonesArray **p
      = reinterpret_cast<TClonesArray**>(col->GetObjectRef(name.Data()));
   if (!p) {
      SetStateError(TString::Format("branch '%s' not found",name.Data()));
      return NULL;
   }

   const TClass *const cl = (*p)->GetClass();

   if (!cl->InheritsFrom(ITiming::Class())) {
      SetStateError(TString::Format("branch '%s' doesn't inherits from 'art::ITiming'",
				    name.Data()));
      return NULL;
   }

   return p;
}

namespace {
   const Int_t BASE = 10;
   inline TString IDToString (Int_t id) {
      return id == DEFAULT_ID ? TString("head") : TString::Itoa(id,BASE);
   }
}

void TSingleTOFProcessor::Init(TEventCollection *col)
{
   const TString &startid = IDToString(fStartID);
   const TString &stopid = IDToString(fStopID);
   Info("Init","%s (%s) -- %s (%s) => %s",
	fStopColName.Data(),stopid.Data(),
	fStartColName.Data(),startid.Data(),
	fOutputName.Data());

   fStartCollection = LoadBranch(col,fStartColName);
   fStopCollection = LoadBranch(col,fStopColName);

   if (!fStartCollection || !fStopCollection) {
      return;
   }
}

namespace{
template <class T>
T* FindDataByID(const TClonesArray* carray, Int_t id)
{ // not considering multihits
   TIter next(carray);
   while(art::TDataObject *const obj
	 = static_cast<art::TDataObject*>(next())) {
      if (obj->GetID() == id) {
	 return dynamic_cast<T*>(obj);
      }
   }
   return NULL;
}
}

void TSingleTOFProcessor::Process()
{
   fOutput->Clear("C");
   const ITiming *const start = FindDataByID<ITiming>(*fStartCollection,fStartID);
   const ITiming *const stop  = FindDataByID<ITiming>(*fStartCollection,fStopID);

   if (!start || !stop) {
      // TOF cannot be determined
      return;
   }

   const Double_t tof = stop->GetTiming() - start->GetTiming();

   TTimeDifference *const out
      = static_cast<TTimeDifference*>(fOutput->ConstructedAt(0));
   out->SetID(0);
   out->SetTiming(tof);
}
