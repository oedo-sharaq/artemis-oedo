/**
 * @file   TCatTpcHitClusterProcessor.h
 * @brief  make cluster of tpc hits
 *
 * @date   Created       : 2016-04-17 04:45:26 JST
 *         Last Modified : 2018-07-18 13:27:58 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_EDE8B975_71B1_4949_BC32_A749251709CD_1
#define INCLUDE_GUARD_UUID_EDE8B975_71B1_4949_BC32_A749251709CD_1

#include "TProcessor.h"
#include <TCatTpcTrackUpdateHelper.h>

namespace art {
   class TCatTpcHitClusterProcessor;
   class TCatReadoutPadArray;
}

class TVector3;
class TClonesArray;

class art::TCatTpcHitClusterProcessor : public TProcessor {
public:
   TCatTpcHitClusterProcessor();
   virtual ~TCatTpcHitClusterProcessor();

   TCatTpcHitClusterProcessor(const TCatTpcHitClusterProcessor& rhs);
   TCatTpcHitClusterProcessor& operator=(const TCatTpcHitClusterProcessor& rhs);

   virtual void Process();

   virtual void Init(TEventCollection *col);

protected:

   TString               fInputName;      // name of input collection
   TClonesArray        **fInput;          //! input array
   TString               fOutputName;     // name of output collection
   TClonesArray         *fOutput;         //! output array
   TString               fReadoutPadArrayName; // name of readout pad array 
   TCatReadoutPadArray **fReadoutPadArray;     //! readout pad array

   TString               fNameInertia; // name of output moment of inertia
   Double_t             *fInertia; //!
   TString               fNamePrincipalAxis; // name of output principal axis
   TVector3             *fPrincipalAxis;  //!
   TString               fNameDeviation; // deviation
   TVector3             *fDeviation; //!

   
   DoubleVec_t fClusterRadius; // size of cluster (mm)
   
   Double_t fMinClusterSize; // required minimum cluster size
   Bool_t fIsSingle; // select maximum size cluster if 1 (default:0)
   Int_t fReadoutPadType; // select readout pad type 2 if 2 (default:2)

   Double_t fMinHeight;
   DoubleVec_t fPulseLengthRange;
   Int_t fSelectIf; // case for usage of selected region: 0 never, 1 accept, 2 reject
   DoubleVec_t fSelectedRegion; // rectangular region for selection

   Bool_t fDoTrackUpdate;
   TCatTpcTrackUpdateHelper fTrackUpdateHelper;

   Double_t fChargeWeightPower; //charge weight power

   Double_t fDriftVelocity; // drift velocity (cm/us)

private:
   

   ClassDef(TCatTpcHitClusterProcessor,1) // select recoil candidate
};

#endif // INCLUDE_GUARD_UUID_EDE8B975_71B1_4949_BC32_A749251709CD_1
