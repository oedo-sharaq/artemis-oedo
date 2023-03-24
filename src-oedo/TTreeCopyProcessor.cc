// K.Okawa created <okawa@cns.s.u-tokyo.ac.jp>

#include "TTreeCopyProcessor.h"

#include <TClonesArray.h>
#include <TClass.h>

#include "TDataObject.h"
#include "TSRPPACPlaneData.h"
#include "constant.h"

using art::TTreeCopyProcessor;

ClassImp(TTreeCopyProcessor)

TTreeCopyProcessor::TTreeCopyProcessor()
  : fInData(NULL), fOutData(NULL) {
  RegisterInputCollection("InputCollection","name of the origin branch",
			  fInputColName,TString("origin"));
  RegisterOutputCollection("OutputCollection","output collection name",
			   fOutputColName,TString("copy"));
}

TTreeCopyProcessor::~TTreeCopyProcessor()
{
  delete fOutData;
  fOutData = NULL;
}

void TTreeCopyProcessor::Init(TEventCollection *col)
{
  Info("Init", "%s => %s copy", fInputColName.Data(), fOutputColName.Data());

  fInData = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fInputColName.Data()));
  if(!fInData){
    SetStateError(TString::Format("input not found: %s",fInputColName.Data()));
    return;
  }

  const TClass *const cl = (*fInData)->GetClass();
  fOutData = new TClonesArray(cl);
  fOutData->SetName(fOutputColName);
  col->Add(fOutputColName,fOutData,fOutputIsTransparent);
}

void TTreeCopyProcessor::Process()
{
  fOutData->Clear("C");

  //for(Int_t iData=0; iData<(*fInData)->GetEntriesFast(); iData++){
  //  const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(iData));
  //  TDataObject *outData = static_cast<TDataObject*>(fOutData->ConstructedAt(iData));

  //  inData->Copy(*outData);
  //}

  if ((*fInData)->GetEntriesFast() == 0) return;

  const TDataObject *const inData = static_cast<TDataObject*>((*fInData)->At(0));
 
  const TClass *const cl = (*fInData)->GetClass();
  Bool_t isSRPPAC = cl->InheritsFrom(art::TSRPPACPlaneData::Class());
  
  if(!isSRPPAC){
    TDataObject *outData = static_cast<TDataObject*>(fOutData->ConstructedAt(0));
    inData->Copy(*outData);
  }
  
  else{
    TSRPPACPlaneData *outData = static_cast<TSRPPACPlaneData*>(fOutData->ConstructedAt(0));
    inData->Copy(*outData);
   
    const TSRPPACPlaneData *const srData = dynamic_cast<const TSRPPACPlaneData*>(inData);
    outData->SetPosition(srData->GetPosition());
  }

}

