/**
 * @file   TCatDiffusedChargeResponseHelper.h
 * @brief  helper to calculate the pad response for diffused charge
 *
 * @date   Created       : 2016-09-12 10:48:37 JST
 *         Last Modified : 2018-10-03 05:01:30 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_2B53EFAB_DAA5_4A46_A4BA_80103B841B93
#define INCLUDE_GUARD_UUID_2B53EFAB_DAA5_4A46_A4BA_80103B841B93

#include "IProcessorHelper.h"
#include <TVector3.h>
#include <vector>
#include <TRangeTableHelper.h>
#include <TMath.h>
#include <TArtSystemOfUnit.h>
#include <TGraph.h>
#include <TCatReadoutPadArray.h>
#include <TArtTypes.h>
using TArtSystemOfUnit::mm;
using TArtSystemOfUnit::cm;


namespace art {
   class TCatDiffusedChargeResponseHelper;
   class TCatReadoutPadArray;
   class TCatReadoutPad;
   class TNArray;
   class TCatPulseShape;
   class TRandomGraph;
}

class TGraph;
class TH2Poly;


class art::TCatDiffusedChargeResponseHelper : public IProcessorHelper {
public:
   TCatDiffusedChargeResponseHelper();
   virtual ~TCatDiffusedChargeResponseHelper();

   TCatDiffusedChargeResponseHelper(const TCatDiffusedChargeResponseHelper& rhs);
   TCatDiffusedChargeResponseHelper& operator=(const TCatDiffusedChargeResponseHelper& rhs);

   void Init(TEventCollection *col);
   void Register(TProcessor *proc);
   
   void GetResponse(Int_t id, Double_t &charge, Double_t &closest, Double_t &angle, Double_t &rangeToEnd, Double_t& trackLength) const;
   Double_t GetCharge(Int_t id) const {
      Double_t charge, dummy;
      GetResponse(id,charge,dummy,dummy,dummy,dummy);
      return charge;
   }

   Double_t GetSigma(Double_t drift) const;

   
   void SetTrack(const TVector3& start, const TVector3& end);
   void SetHits(TObjArray *hits);
   double GetResidual() const;
   Double_t GetWorkFunction() { return fWorkFunction; }
   const TCatReadoutPadArray* GetReadoutPadArray() const { return *fReadoutPadArray; }
   const TRangeTableHelper* GetRangeTableHelper() const { return *fRangeTable; }
   Double_t GetReadoutPlaneOffset() const { return fReadoutPlaneOffset; }
   Double_t GetAttachment() const { return fAttachment; }
   Double_t GetDiffusionCoefficient() const { return fDiffusionCoefficient; }
   Double_t GetDefaultIntegrateStep() const { return fDefaultIntegrateStep; }
   Double_t GetBaseDiffusion() const { return fBaseDiffusion; }
   const std::vector<Double_t>& GetActiveArea() const { return fActiveArea; }

   //
   void SetAdditionalRange(double range) {fAdditionalRange = range;}

   //  function to calculate active range inside active volume
   void EstimateActiveRange();

   // function to calculate number of electrons inside active volume using active range
   Int_t GetNumOfElectrons() const;

   // function to calculate energy from number of electrons
   Double_t GetEnergyFrom(Double_t nElectrons) const;

   // function to get readout pad
   const TCatReadoutPad* GetReadoutPad(Int_t i) const;

   // set the position of  generate enelection
   // returns false if point is outside of active area
   Bool_t GeneratedElectronAt(TVector3& point);

   // function to get number of readout pads
   Int_t GetNumPads() const { return (*fReadoutPadArray)->GetEntries(); }
   

   // helper parameters
   void SetDefaultIntegrateStep(Double_t step)  { fDefaultIntegrateStep = step; }
   void SetReadoutPadArray(TCatReadoutPadArray **array) { fReadoutPadArray = array; }
   void SetResponseTable(TNArray** table) { fResponseTable = table; }
   void SetDiffusionCoefficient(Double_t coeff) { fDiffusionCoefficient = coeff; }
   void SetReadoutPlaneOffset(Double_t offset) { fReadoutPlaneOffset = offset; }
   void SetWorkFunction(Double_t wf) { fWorkFunction = wf; }
   void SetRangeTableHelper(TRangeTableHelper **rangeTable) { fRangeTable = rangeTable; }
   void SetUseRandom(Bool_t flag) { fUseRandom = flag; }
   void SetAttachment(Double_t attachment) { fAttachment = attachment; }
   void SetBaseDiffusion(Double_t base) { fBaseDiffusion = base; }
   void SetDisplacementTableX(TNArray** table) { fDisplacementTableX = table; }
   void SetDisplacementTableZ(TNArray** table) { fDisplacementTableZ = table; }
   void SetActiveArea(const std::vector<Double_t>& area) { fActiveArea = area; }

   virtual void Copy(TCatDiffusedChargeResponseHelper& object) const;

#if 0
   static void Test(const TVector3& start, const TVector3& end, Double_t step = 0.1);
   static void Test(Int_t id, const TVector3& start, const TVector3& end, Double_t& charge, Double_t &mccharge);
   static void TestConvergenceFor(Int_t id, TVector3 start, TVector3 end, Double_t dc = 0.04);
#endif
protected:
   TVector3 fTrackStart; //! track start point
   TVector3 fTrackEnd;  //! track end point
   TVector3 fDirection; //! direction with magnitude
   TVector3 fUnitDirection; //! unit direction
   Double_t fRange; //! range
   Int_t    fNumStep; //! calculated number of step
   Double_t fStep; //! calculated step

   std::vector<TVector2> fPadCenter; //!
   std::vector<TVector2> fPadVertex; //!


   // processor parameters
   Double_t fDefaultIntegrateStep; //! default integrate step
   Double_t fAttachment; //!
   Double_t fDiffusionCoefficient; //! diffusion coefficient (cm1/2)
   Double_t fReadoutPlaneOffset; //! offset of readout pad relative to the beam axis (the sign is same as the drift time)
   Double_t fWorkFunction; // work function (MeV)

   TString fNameReadoutPadArray; // name of readout pad array
   TCatReadoutPadArray **fReadoutPadArray; //! readout pad array

   TGraph *fR2DE; //!

   TString fResponseTableName; //

   TNArray **fResponseTable; //! response table
   std::vector<TCatPulseShape*> fHits; //!

   TString fRangeTableName;
   TRangeTableHelper **fRangeTable; //!

   TRandomGraph *fRandomBrag; //!

   Bool_t fUseRandom; //!
   Double_t fActiveAreaHalfX; // length in x direction of readout area to the edge from the center
   Double_t fActiveAreaHalfZ; // length in z direction of readout area to the edge from the center
   Double_t fActiveAreaMargin; // active area margine to calculate the chage

   Double_t fBaseDiffusion; // base diffusion to be added to calculated diffusion


   TString fDisplacementTableXName; // name of displacement table for X
   TString fDisplacementTableZName; // name of displacement table for Z
   TNArray **fDisplacementTableX; //!
   TNArray **fDisplacementTableZ; //!

   DoubleVec_t fActiveArea; // active area

   Int_t fUseDisplacement3D; // use 3-d to calculate displacement

   Double_t fAdditionalRange; // range to be added in evaluation of charge
    

private:
   Double_t fShorterRange; //! used for charge calculation inside
   Double_t fLongerRange; //! used for charge calculation inside

   ClassDef(TCatDiffusedChargeResponseHelper,1) // helper to calculate the pad response for diffused charge
};

inline Double_t art::TCatDiffusedChargeResponseHelper::GetSigma(Double_t drift) const
{
   Double_t sigma = TMath::Sqrt(drift/cm) * fDiffusionCoefficient * cm;
   sigma = TMath::Sqrt(sigma * sigma + fBaseDiffusion * fBaseDiffusion);
   return sigma;
}

inline Int_t art::TCatDiffusedChargeResponseHelper::GetNumOfElectrons() const
{
   return TMath::FloorNint(((*fRangeTable)->R2E(fLongerRange) - (*fRangeTable)->R2E(fShorterRange))/fWorkFunction);
}

inline Double_t art::TCatDiffusedChargeResponseHelper::GetEnergyFrom(Double_t nEl) const
{
   return nEl * fWorkFunction;
}

inline const art::TCatReadoutPad* art::TCatDiffusedChargeResponseHelper::GetReadoutPad(Int_t i) const
{
   return (TCatReadoutPad*)((*fReadoutPadArray)->At(i));
}



#endif // INCLUDE_GUARD_UUID_2B53EFAB_DAA5_4A46_A4BA_80103B841B93
