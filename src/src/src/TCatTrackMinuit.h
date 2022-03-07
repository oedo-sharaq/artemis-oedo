/**
 * @file   TCatTrackMinuit.h
 * @brief  minuit routine for the tracking of CAT hits
 *
 * @date   Created       : 2014-12-03 06:46:10 JST
 *         Last Modified : 2016-02-04 18:36:42 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 * Data is not copied. Data should not deleted while this class is used
 *
 *    (C) 2014 Shinsuke OTA
 */

#ifndef INCLUDE_GUARD_UUID_AC13E143_1224_465B_AE7E_EE5FDD624674
#define INCLUDE_GUARD_UUID_AC13E143_1224_465B_AE7E_EE5FDD624674

#include "TMinuit.h"
#include <vector>
#include <TArtSystemOfUnit.h>
namespace art {
   class TCatTrackMinuit;
   class TCatReadoutPadArray;
   class TCatPulseShape;
}

class TGraph;
class TVector3;
class TClonesArray;


class art::TCatTrackMinuit : public TMinuit {
public:
   TCatTrackMinuit();
   virtual ~TCatTrackMinuit();

   TCatTrackMinuit(const TCatTrackMinuit& rhs);
   TCatTrackMinuit& operator=(const TCatTrackMinuit& rhs);


   // calculate square residual
   virtual Double_t CalcResidual(Double_t y0, Double_t z0, Double_t vx, Double_t vz, Double_t t, TClonesArray *output = 0);
   
   // override calculate function
   virtual Int_t Eval(Int_t npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag);

   
   
   // SetData
   // set the input array of the data and the calculate initial parameters
   virtual void SetData(TObjArray* fArray);
   virtual void SetReadoutPadArray(TCatReadoutPadArray *array);
   virtual void SetRangeTable(TGraph *table);
   inline virtual void SetDriftVelocity(Double_t velocity);  // set drift velocity in the unit of cm/us
   inline virtual void SetWorkFunction(Double_t workFunction); // set workfunction in the unit of ev

   virtual void SetParameters(Double_t y0, Double_t z0, Double_t vx, Double_t vz, Double_t t);
   virtual void GetParameters(Double_t &y0, Double_t &z0, Double_t &vx, Double_t &vz, Double_t &t);
   virtual void SetLine(Double_t p0, Double_t p1) { fP0 = p0; fP1 = p1; }
   

protected:

   void UniqueVector3(std::vector<TVector3*> &vec);
   Bool_t FindVertex(const TVector3 &a1, const TVector3 &a2,
                     const TVector3 &b1, const TVector3 &b2,
                     TVector3 &output);


   
   Int_t fNumData;
//   std::vector<Double_t> fE;
//   std::vector<Double_t> fY;  // hit position
   Double_t fDriftVelocity;
   Double_t fWorkFunction;
   Double_t fP0; // z = p0 + p1 * x
   Double_t fP1; // z = p0 + p1 * x
   TObjArray *fHits; //!->
   
   TCatReadoutPadArray *fPadArray; //!->
   TGraph *fRangeTable; //!->
   TGraph *fRange2EnergyTable; //!->
private:

   ClassDef(TCatTrackMinuit,0) // minuit routine for the tracking of CAT hits
};

void art::TCatTrackMinuit::SetDriftVelocity(Double_t velocity)
{
   fDriftVelocity = velocity * TArtSystemOfUnit::cm / TArtSystemOfUnit::us / TArtSystemOfUnit::mm;
}

void art::TCatTrackMinuit::SetWorkFunction(Double_t workFunction)
{
   fWorkFunction = workFunction * TArtSystemOfUnit::MeV * 1e-6;
}
#endif // INCLUDE_GUARD_UUID_AC13E143_1224_465B_AE7E_EE5FDD624674
