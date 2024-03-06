#include "TTimingChargeCorrectionProcessor.h"

#include "ITiming.h"
#include "ICharge.h"
#include "TConverterBase.h"
#include "TConverterUtil.h"
#include "constant.h"
#include "TDataObject.h"

#include <TClonesArray.h>
#include <TRandom.h>
#include <TClass.h>

using art::TTimingChargeCorrectionProcessor;

namespace
{
    const TString DEFAULT_CONV_NAME("no_conversion");
}

ClassImp(art::TTimingChargeCorrectionProcessor)

    // Default constructor
    TTimingChargeCorrectionProcessor::TTimingChargeCorrectionProcessor()
    : fInDatamain(NULL), fInDatasub(NULL), fOutData(NULL),
      /*fTimingConverterArray(NULL),*/ fChargeConverterArray(NULL),
      fChargeConverterArray0004(NULL), fChargeConverterArray0509(NULL),
      fChargeConverterArray1014(NULL), fChargeConverterArray1519(NULL),
      fChargeConverterArray2024(NULL), fChargeConverterArray2529(NULL),
      fChargeConverterArray3034(NULL), fChargeConverterArray3539(NULL),
      fChargeConverterArray4044(NULL), fChargeConverterArray4549(NULL),
      fChargeConverterArray5054(NULL), fChargeConverterArray5559(NULL),
      fChargeConverterArray6064(NULL), fChargeConverterArray6569(NULL),
      fChargeConverterArray7074(NULL), fChargeConverterArray7579(NULL),
      fChargeConverterArray8084(NULL), fChargeConverterArray8589(NULL),
      fChargeConverterArray9093(NULL),
      fInputHasTiming(kFALSE), fInputHasCharge(kFALSE)
{
    RegisterInputCollection("InputCollectionmain",
                            "array of objects inheriting from art::ITiming and/or art::ICharge",
                            fInputColNamemain, TString("plastic_raw"));
    RegisterInputCollection("InputCollectionsub",
                            "array of objects inheriting from art::ITiming and/or art::ICharge",
                            fInputColNamesub, TString("plastic_raw"));
    RegisterOutputCollection("OutputCollection", "output class will be the same as input",
                             fOutputColName, TString("plastic"));
    // RegisterProcessorParameter("TimingConverterArray",
    //		      "normally output of TAffineConverterArrayGenerator",
    //		      fTimingConverterArrayName,DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray0004",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName0004, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray0509",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName0509, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray1014",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName1014, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray1519",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName1519, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray2024",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName2024, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray2529",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName2529, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray3034",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName3034, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray3539",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName3539, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray4044",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName4044, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray4549",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName4549, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray5054",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName5054, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray5559",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName5559, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray6064",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName6064, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray6569",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName6569, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray7074",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName7074, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray7579",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName7579, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray8084",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName8084, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray8589",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName8589, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("ChargeConverterArray9093",
                               "normally output of TAffineConverterArrayGenerator",
                               fChargeConverterArrayName9093, DEFAULT_CONV_NAME);
    RegisterProcessorParameter("InputIsDigital", "whether input is digital or not",
                               fInputIsDigital, kTRUE);
}

TTimingChargeCorrectionProcessor::~TTimingChargeCorrectionProcessor()
{
    delete fOutData;
    // delete fTimingConverterArray;
    delete fChargeConverterArray;
    delete fChargeConverterArray0004;
    delete fChargeConverterArray0509;
    delete fChargeConverterArray1014;
    delete fChargeConverterArray1519;
    delete fChargeConverterArray2024;
    delete fChargeConverterArray2529;
    delete fChargeConverterArray3034;
    delete fChargeConverterArray3539;
    delete fChargeConverterArray4044;
    delete fChargeConverterArray4549;
    delete fChargeConverterArray5054;
    delete fChargeConverterArray5559;
    delete fChargeConverterArray6064;
    delete fChargeConverterArray6569;
    delete fChargeConverterArray7074;
    delete fChargeConverterArray7579;
    delete fChargeConverterArray8084;
    delete fChargeConverterArray8589;
    delete fChargeConverterArray9093;
}

void TTimingChargeCorrectionProcessor::Init(TEventCollection *col)
{
    Info("Init", "%s => %s", fInputColNamemain.Data(), fOutputColName.Data());
    fInDatamain = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColNamemain.Data()));
    if (!fInDatamain)
    {
        SetStateError(TString::Format("input not found: %s", fInputColNamemain.Data()));
        return;
    }

    fInDatasub = reinterpret_cast<TClonesArray **>(col->GetObjectRef(fInputColNamesub.Data()));
    if (!fInDatasub)
    {
        SetStateError(TString::Format("input not found: %s", fInputColNamesub.Data()));
        return;
    }

    const TClass *const cl = (*fInDatamain)->GetClass();
    fInputHasTiming = cl->InheritsFrom(art::ITiming::Class());
    fInputHasCharge = cl->InheritsFrom(art::ICharge::Class());

    if (!fInputHasTiming && !fInputHasCharge)
    {
        SetStateError("contents of input array must inherit from art::ITiming and/or art::ICharge");
        return;
    }

    // if(fInputHasTiming && fTimingConverterArrayName.CompareTo(DEFAULT_CONV_NAME)) {
    //    TConverterUtil::SetConverterArray(&fTimingConverterArray,fTimingConverterArrayName,col);
    // }

    if (fInputHasCharge && fChargeConverterArrayName.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray, fChargeConverterArrayName, col);
    }

    if (fInputHasCharge && fChargeConverterArrayName0004.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray0004, fChargeConverterArrayName0004, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName0509.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray0509, fChargeConverterArrayName0509, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName1014.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray1014, fChargeConverterArrayName1014, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName1519.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray1519, fChargeConverterArrayName1519, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName2024.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray2024, fChargeConverterArrayName2024, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName2529.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray2529, fChargeConverterArrayName2529, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName3034.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray3034, fChargeConverterArrayName3034, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName3539.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray3539, fChargeConverterArrayName3539, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName4044.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray4044, fChargeConverterArrayName4044, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName4549.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray4549, fChargeConverterArrayName4549, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName5054.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray5054, fChargeConverterArrayName5054, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName5559.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray5559, fChargeConverterArrayName5559, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName6064.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray6064, fChargeConverterArrayName6064, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName6569.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray6569, fChargeConverterArrayName6569, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName7074.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray7074, fChargeConverterArrayName7074, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName7579.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray7579, fChargeConverterArrayName7579, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName8084.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray8084, fChargeConverterArrayName8084, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName8589.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray8589, fChargeConverterArrayName8589, col);
    }
    if (fInputHasCharge && fChargeConverterArrayName9093.CompareTo(DEFAULT_CONV_NAME))
    {
        TConverterUtil::SetConverterArray(&fChargeConverterArray9093, fChargeConverterArrayName9093, col);
    }

    if (!fChargeConverterArray0004 || !fChargeConverterArray0509 ||
        !fChargeConverterArray1014 || !fChargeConverterArray1519 ||
        !fChargeConverterArray2024 || !fChargeConverterArray2529 ||
        !fChargeConverterArray3034 || !fChargeConverterArray3539 ||
        !fChargeConverterArray4044 || !fChargeConverterArray4549 ||
        !fChargeConverterArray5054 || !fChargeConverterArray5559 ||
        !fChargeConverterArray6064 || !fChargeConverterArray6569 ||
        !fChargeConverterArray7074 || !fChargeConverterArray7579 ||
        !fChargeConverterArray8084 || !fChargeConverterArray8589 ||
        !fChargeConverterArray9093 || !fChargeConverterArray)
    {
        SetStateError("no converter registered.");
        return;
    }

    fOutData = new TClonesArray(cl);
    fOutData->SetName(fOutputColName);
    col->Add(fOutputColName, fOutData, fOutputIsTransparent);
}

void TTimingChargeCorrectionProcessor::Process()
{
    fOutData->Clear("C");

    const Int_t ndata = (*fInDatasub)->GetEntriesFast();
    Int_t detIDsub[ndata];
    for (Int_t iData = 0; iData < ndata; iData++)
    {
        const TDataObject *const inDatasub = static_cast<TDataObject *>((*fInDatasub)->At(iData));
        detIDsub[iData] = inDatasub->GetID();
    }
    // std::cout << "subID" << detIDsub[0] << std::endl;

    for (Int_t iData = 0, nData = (*fInDatamain)->GetEntriesFast();
         iData != nData; ++iData)
    {

        const TDataObject *const inDatamain = static_cast<TDataObject *>((*fInDatamain)->At(iData));
        TObject *const outData = fOutData->ConstructedAt(iData);
        const Int_t detIDmain = inDatamain->GetID();
        if (!IsValid(detIDmain))
            continue;
        inDatamain->Copy(*outData);
        // std::cout << "mainID" << detIDmain << std::endl;

        /*
        int ndata = (*fInDatasub)->GetEntriesFast();
        Int_t detIDsub = 0;
        if(iData < ndata){
           const TDataObject *const inDatasub = static_cast<TDataObject*>((*fInDatasub)->At(iData));
           detIDsub = inDatasub->GetID();
           if(!IsValid(detIDsub)) continue;
           std::cout << "subID" << detIDsub << std::endl;
        }else{
           detIDsub = -1;
           //std::cout << "subID" << detIDsub << std::endl;
        }
        */

        if (fInputHasTiming)
        {
            const ITiming *const inDatamainT = dynamic_cast<const ITiming *>(inDatamain);
            const Double_t timing = inDatamainT->GetTiming() + (fInputIsDigital ? gRandom->Uniform() : 0);
            // if ( fTimingConverterArray && detIDmain >= (Int_t)fTimingConverterArray->size()) {
            //    SetStateError(TString::Format("size of TimingConverterArray (%d) is smaller than detIDmain (%d)",(Int_t)fTimingConverterArray->size(), detIDmain));
            //    return;
            // }
            // const Double_t outputT =
            // fTimingConverterArray ? fTimingConverterArray->at(detIDmain)->Convert(timing) : timing;
            const Double_t outputT = timing;
            ITiming *const outDataT = dynamic_cast<ITiming *>(outData);
            outDataT->SetTiming(outputT);
        }

        if (fInputHasCharge)
        {
            const ICharge *const inDatamainQ = dynamic_cast<const ICharge *>(inDatamain);
            const Double_t charge = inDatamainQ->GetCharge() + (fInputIsDigital ? gRandom->Uniform() : 0);

            if (fChargeConverterArray && detIDmain >= (Int_t)fChargeConverterArray->size())
            {
                SetStateError(TString::Format("size of ChargeConverterArray (%d) is smaller than detIDmain (%d)", (Int_t)fChargeConverterArray->size(), detIDmain));
                return;
            }

            Double_t outputQ = 0.;
            if (detIDsub[0] >= 0 && detIDsub[0] <= 4)
            {
                outputQ =
                    fChargeConverterArray0004 ? fChargeConverterArray0004->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 5 && detIDsub[0] <= 9)
            {
                outputQ =
                    fChargeConverterArray0509 ? fChargeConverterArray0509->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 10 && detIDsub[0] <= 14)
            {
                outputQ =
                    fChargeConverterArray1014 ? fChargeConverterArray1014->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 15 && detIDsub[0] <= 19)
            {
                outputQ =
                    fChargeConverterArray1519 ? fChargeConverterArray1519->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 20 && detIDsub[0] <= 24)
            {
                outputQ =
                    fChargeConverterArray2024 ? fChargeConverterArray2024->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 25 && detIDsub[0] <= 29)
            {
                outputQ =
                    fChargeConverterArray2529 ? fChargeConverterArray2529->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 30 && detIDsub[0] <= 34)
            {
                outputQ =
                    fChargeConverterArray3034 ? fChargeConverterArray3034->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 35 && detIDsub[0] <= 39)
            {
                outputQ =
                    fChargeConverterArray3539 ? fChargeConverterArray3539->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 40 && detIDsub[0] <= 44)
            {
                outputQ =
                    fChargeConverterArray4044 ? fChargeConverterArray4044->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 45 && detIDsub[0] <= 49)
            {
                outputQ =
                    fChargeConverterArray4549 ? fChargeConverterArray4549->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 50 && detIDsub[0] <= 54)
            {
                outputQ =
                    fChargeConverterArray5054 ? fChargeConverterArray5054->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 55 && detIDsub[0] <= 59)
            {
                outputQ =
                    fChargeConverterArray5559 ? fChargeConverterArray5559->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 60 && detIDsub[0] <= 64)
            {
                outputQ =
                    fChargeConverterArray6064 ? fChargeConverterArray6064->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 65 && detIDsub[0] <= 69)
            {
                outputQ =
                    fChargeConverterArray6569 ? fChargeConverterArray6569->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 70 && detIDsub[0] <= 74)
            {
                outputQ =
                    fChargeConverterArray7074 ? fChargeConverterArray7074->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 75 && detIDsub[0] <= 79)
            {
                outputQ =
                    fChargeConverterArray7579 ? fChargeConverterArray7579->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 80 && detIDsub[0] <= 84)
            {
                outputQ =
                    fChargeConverterArray8084 ? fChargeConverterArray8084->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 85 && detIDsub[0] <= 89)
            {
                outputQ =
                    fChargeConverterArray8589 ? fChargeConverterArray8589->at(detIDmain)->Convert(charge) : charge;
            }
            else if (detIDsub[0] >= 90 && detIDsub[0] <= 93)
            {
                outputQ =
                    fChargeConverterArray9093 ? fChargeConverterArray9093->at(detIDmain)->Convert(charge) : charge;
            }
            else
            {
                outputQ =
                    fChargeConverterArray ? fChargeConverterArray->at(detIDmain)->Convert(charge) : charge;
            }

            ICharge *const outDataQ = dynamic_cast<ICharge *>(outData);
            outDataQ->SetCharge(outputQ);
        }
    }
}
