/**
 * @file   TCatTrackingProcessor.h
 * @brief  tracking processor for CAT
 *
 * @date   Created       : 2014-12-02 09:28:49 JST
 *         Last Modified : 2018-02-04 13:10:28 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_CB5BF3FF_1B3C_4BFB_B993_BAE57E720A51
#define INCLUDE_GUARD_UUID_CB5BF3FF_1B3C_4BFB_B993_BAE57E720A51

#include "TProcessor.h"
#include <TH2Poly.h>
#include <TVector2.h>
#include <TSimpleData.h>
namespace art {
   class TCatTrackingProcessor;
   class TCatReadoutPadArray;
   class TCatTrackMinuit;
   class TEventHeader;
}

class TGraph;
class TCanvas;
class TVector3;
class TClonesArray;

class art::TCatTrackingProcessor : public TProcessor {
public:
   TCatTrackingProcessor();
   virtual ~TCatTrackingProcessor();

   TCatTrackingProcessor(const TCatTrackingProcessor& rhs);
   TCatTrackingProcessor& operator=(const TCatTrackingProcessor& rhs);

   void Init(TEventCollection* col);
   void Process();
   

protected:
   TString fInputColName;
   TClonesArray** fInputArray; //!
   TString fOutputColName;
   TClonesArray* fOutputArray; //!
   TString fResultHitsName;
   TClonesArray* fResultHitsArray; //!
   TString fFitResultName;
   TClonesArray* fFitResult; //!
   TString fReadoutPadName;
   art::TCatReadoutPadArray** fPadArray; //!
   TObjArray *fValidHits; //!

   TString fRangeTableFile;
   TString fRangeTableFormat;
   TGraph *fRangeTable;
   TGraph *fRange2EnergyTable;
   TGraph *fRange2EnergyLoss;
   TCatTrackMinuit *fTrackMinuit;

   // for checking the tracking result
   TH2Poly* fHistPad; //!
   TCanvas* fCheckCanvas; //!

   Float_t fGlobalEnergyCorrection; // [optional] global energy correction coefficient. Ecalc_cor = Ecalc * fGlobalEnergyCorrection
   Float_t fDriftVelocity; // drift velocity (cm/us)
   Float_t fWorkFunction; // work funtion (eV)
   Bool_t  fDrawFitResultFlag; // draw fit result when true
   Bool_t  fSaveFigFlag; // save drawn figure when true
   Int_t   fWaitTimeForFitResult; // time period (ms) until next event is drawn
   // helper members
   TF1 *fFunXY; //! 
   TF1 *fFunXZ; //!

   TString fNameRunHeaders;
   TList  **fRunHeaders; //!
   TString fNameEventHeader;
   TEventHeader **fEventHeader; //!
   TString fSaveFigDir; // directory for saving figure if directory

   TString fNameEx; // name of excitation energy
   TSimpleData *fEx; //!
   TString fNameThetaCM; // name of thetaCM
   TSimpleData *fThetaCM; //!

   // track starting point from outside
   TString fNameBeamMomentum;
   TString fNameBeamPosition;
   TClonesArray **fBeamMomentum; //!
   TClonesArray **fBeamPosition; //!

   TString fNameTrackStart;
   TString fNameTrackEnd;
   TVector3 *fTrackStart; //!
   TVector3 *fTrackEnd; //!

   // table lookup
   Bool_t fTableLookupFlag; // flag to use TCatTrackMinuit (flag = 0, default), or to use TCatTrackDiffusedMinuit (flag = 1)
   TString fChargeDistribusionTable; // path to the file containing the charge distribution histgram
   Float_t fAttachment; // attachment(cm^{-1})
   Float_t fFieldCageOffset; // field cage offset (mm)
   
   
   
private:

   ClassDef(TCatTrackingProcessor,0) // tracking processor for CAT
};

#endif // INCLUDE_GUARD_UUID_CB5BF3FF_1B3C_4BFB_B993_BAE57E720A51
