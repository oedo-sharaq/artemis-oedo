/**
 * @file   TCatTrackingWithDiffusedChargeProcessor.h
 * @brief  tracking with diffused charge
 *
 * @date   Created       : 2016-07-24 08:47:59 JST
 *         Last Modified : 2018-05-11 17:39:14 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_DC1CAC73_0C7A_4BEE_AF14_7D7642728654
#define INCLUDE_GUARD_UUID_DC1CAC73_0C7A_4BEE_AF14_7D7642728654

#include "TProcessor.h"
#include <TCatDiffusedChargeResponseHelper.h>
#include <TCatFunctionChargeResidual.h>
#include "TEventDisplayProcessorHelper.h"
#include <Minuit2/Minuit2Minimizer.h>
#include <vector>

namespace art {
   class TCatTrackingWithDiffusedChargeProcessor;
   class TCatTpcTrack;
}

class TClonesArray;
class TH2F;
class TH1;


class art::TCatTrackingWithDiffusedChargeProcessor : public TProcessor {
public:
   enum { kAxisX, kAxisY, kAxisZ};
   TCatTrackingWithDiffusedChargeProcessor();
   virtual ~TCatTrackingWithDiffusedChargeProcessor();

   TCatTrackingWithDiffusedChargeProcessor(const TCatTrackingWithDiffusedChargeProcessor& rhs);
   TCatTrackingWithDiffusedChargeProcessor& operator=(const TCatTrackingWithDiffusedChargeProcessor& rhs);

   virtual void Init(TEventCollection *col);
   virtual void Process();

   virtual void ReconstructTrack(const TCatTpcTrack* input_track);

   
protected:
   TString fNameInput;// name of input collection
   TClonesArray **fInput; //!

   TString fNameOutput; // name of output collection
   TClonesArray *fOutput; //!

   TClonesArray *fResuts; //!
   
   TClonesArray *fIntersection; //!

   Int_t fIndependentVariable; // axis X: 0, Y: 1, Z: 2

   Double_t fFixedOrigin;  // origin

   Double_t fInitialRange; // initial range

   TCatDiffusedChargeResponseHelper fChargeResponseHelper; //!
   TCatFunctionChargeResidual       fFunctionChargeResidual; //!
   Double_t *fCpuTime; //! cpu time to minimize
   TString fNameCpuTime; // name of cpu time output


   // helpers todo mesh search
   Bool_t fDoMeshSearch; // flag to do mesh search
   std::vector<TCatDiffusedChargeResponseHelper> fChargeResponses;
   std::vector<TCatFunctionChargeResidual> fFunctions;
   IntVec_t fMeshDim;
   DoubleVec_t fMeshStep;
   DoubleVec_t fSigmaCoeff;

   TEventDisplayProcessorHelper fEventDisplayHelper;

   std::vector<TH1*> fHists;

   ROOT::Minuit2::EMinimizerType fEMinuitMinType; // type of minimizer of minuit2
   TString fMinuitMinTypeName; // name of minimizer type of minuit2

   Double_t fOffset; // offset for X (Z) for independent variable of Z (X)

private:

   ClassDef(TCatTrackingWithDiffusedChargeProcessor,1) // tracking with diffused charge
};

#endif // INCLUDE_GUARD_UUID_DC1CAC73_0C7A_4BEE_AF14_7D7642728654
