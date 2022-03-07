/**
 * @file   TCatTpcTrack.cc
 * @brief  tpc track
 *
 * @date   Created       : 2016-12-09 09:50:14 JST
 *         Last Modified : 2018-08-09 22:00:17 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#include "TCatTpcTrack.h"
#include <TMath.h>
#include <TVector3.h>
#include <TMatrixDSym.h>
#include <TMatrixDSymEigen.h>
#include <TMatrixD.h>
#include <TClonesArray.h>
#include <TCatTrackResultPulse.h>
#include <TCatDiffusedChargeResponseHelper.h>
#include <TRangeTableHelper.h>
#include <TCatReadoutPadArray.h>
#include <TCatReadoutPad.h>

using art::TCatTpcTrack;

ClassImp(TCatTpcTrack)

TCatTpcTrack::TCatTpcTrack()
{
   fHitsHelper = NULL;
   fIsInitialized = kFALSE;
   fChargeWeightPower = 1.;
   fHits.clear();
}

TCatTpcTrack::~TCatTpcTrack()
{
   if (fHitsHelper) {
      fHits.clear();
      delete fHitsHelper;
      fHitsHelper = NULL;
      
   } else {
      for (Int_t i=0, n = fHits.size(); i< n; ++i) {
         delete fHits[i];
      }
      fHits.clear();
   }
}

TCatTpcTrack::TCatTpcTrack(const TCatTpcTrack& rhs)
{
}

TCatTpcTrack& TCatTpcTrack::operator=(const TCatTpcTrack& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TCatTpcTrack::Init()
{
   if (fHitsHelper) return;
   fHitsHelper = new TClonesArray(TCatTrackResultPulse::Class());
   fIsInitialized = kTRUE;
}

void TCatTpcTrack::Clear(Option_t *opt)
{
   fHits.clear();
   if (fHitsHelper) {
      fHitsHelper->Clear(opt);
   }
   Invalidate();
}

void TCatTpcTrack::Copy(TObject& dest) const
{
   TDataObject::Copy(dest);
   TCatTpcTrack& obj = (TCatTpcTrack&)dest;
   obj.fStartPoint = fStartPoint;
   obj.fEndPoint   = fEndPoint;
   obj.fDirection  = fDirection;
   obj.fPrincipalAxis = fPrincipalAxis;
   obj.fDeviation = fDeviation;
   obj.fCharge = fCharge;
   obj.fEnergyDeposit = fEnergyDeposit;
   obj.fRange = fRange;
   obj.fChi2 = fChi2;
   obj.fInertia = fInertia;
   obj.fStatus = fStatus;
   obj.fEDM = fEDM;
   obj.Init();
   for (Int_t i=0, n=fHits.size(); i<n; ++i) {
      TCatTrackResultPulse *output = obj.NewHit();
      fHits[i]->Copy(*output);
   }
}

void TCatTpcTrack::EstimateFromHits(const std::vector<art::TCatPulseShape*>& cluster)
{
   if (!fIsInitialized || !fHitsHelper) {
      Error("EstimateFromHits","Not Initialized Yet. Please call Init() before use.");
      return;
   }

   if (cluster.size() == 0) return;

   Double_t sumX = 0;
   Double_t sumY = 0;
   Double_t sumZ = 0;
   Double_t sumXX = 0;
   Double_t sumYY = 0;
   Double_t sumZZ = 0;
   Double_t sumXY = 0;
   Double_t sumYZ = 0;
   Double_t sumZX = 0;
   Double_t sum = 0;
   Double_t mx, my,mz;
   for (std::vector<art::TCatPulseShape*>::const_iterator it = cluster.begin(), itend = cluster.end(); it < itend; ++it) {
      TCatPulseShape *pulse = *it;
      TCatTrackResultPulse *out = static_cast<TCatTrackResultPulse*> (fHitsHelper->ConstructedAt(fHitsHelper->GetEntriesFast()));
      pulse->Copy(*out);
      out->Validate();
      fHits.push_back(out);
      
      Double_t c = TMath::Power(pulse->GetCharge(),fChargeWeightPower);
      sum += c;
      sumX += c * pulse->GetX();
      sumY += c * pulse->GetY();
      sumZ += c * pulse->GetZ();
   }

   // set
   fCharge = sum;

   mx = sumX/sum;
   my = sumY/sum;
   mz = sumZ/sum;
   for (std::vector<art::TCatPulseShape*>::const_iterator it = cluster.begin(), itend = cluster.end(); it < itend; ++it) {
      TCatPulseShape *pulse = *it;      
      Double_t c = TMath::Power(pulse->GetCharge(),fChargeWeightPower);
      Double_t dx = pulse->GetX() - mx;
      Double_t dy = pulse->GetY() - my;
      Double_t dz = pulse->GetZ() - mz;
      sumXX += c * dx * dx;
      sumXY += c * dx * dy;
      sumYY += c * dy * dy;
      sumYZ += c * dy * dz;
      sumZZ += c * dz * dz;
      sumZX += c * dz * dx;
   }

   Double_t e[9] = {
      sumYY+sumZZ, -sumXY, -sumZX,
      -sumXY, sumZZ+sumXX,-sumYZ,
      -sumZX, -sumYZ, sumXX+sumYY
   };

   TMatrixDSym mat(3,e);
   TMatrixDSymEigen me(mat);

   TVectorD eigenval = me.GetEigenValues();
   TMatrixD eigenvec = me.GetEigenVectors();
   // set values
   fInertia.SetXYZ(eigenval[2],eigenval[1],eigenval[0]);
   fPrincipalAxis.SetXYZ(eigenvec[0][2],eigenvec[1][2],eigenvec[2][2]);

   // set value
   TVector3 centroid(mx,my,mz);
   TVector3 unit = fPrincipalAxis.Unit();
   Double_t min = TMath::Limits<Double_t>::Max();
   Double_t max = TMath::Limits<Double_t>::Min();
   std::vector<art::TCatPulseShape*>::const_iterator itStartPoint = cluster.begin();
   std::vector<art::TCatPulseShape*>::const_iterator itEndPoint = cluster.begin();
   
   
   for (std::vector<art::TCatPulseShape*>::const_iterator it = cluster.begin(), itend = cluster.end(); it < itend; ++it) {
      // estimate start and end point
      TCatPulseShape *pulse = *it;      

      Double_t t = unit.Dot(pulse->GetPos() - centroid);
      
      if (max < t) {
         max = t;
         itStartPoint = it;
      }
      if (t < min) {
         min = t;
         itEndPoint = it;
      }
   }
   
   fStartPoint = centroid - ((*itStartPoint)->GetPos() - centroid).Mag() * unit;
   fEndPoint   = centroid + ((*itEndPoint)->GetPos() - centroid).Mag() * unit;

   fStartPoint = (*itStartPoint)->GetPos();
   fEndPoint = (*itEndPoint)->GetPos();

   if (fStartPoint.X() * fPrincipalAxis.X() < 0) { // correction for end <-> start event
      TVector3 tmp = fEndPoint;
      fEndPoint = fStartPoint;
      fStartPoint = tmp;
      fPrincipalAxis *= -1;
   }
   fDirection = fEndPoint - fStartPoint;
   fOriginalStartPoint = fStartPoint;

   // calculate rms of XY and XZ distributions
   // y = y0 + p1 * (x - x0)
   Double_t varx = 0; // variance in yz
   Double_t vary = 0; // variance in zx
   Double_t varz = 0; // variance in xy
   Double_t vx = fPrincipalAxis.X();
   Double_t vy = fPrincipalAxis.Y();
   Double_t vz = fPrincipalAxis.Z();
   for (std::vector<art::TCatPulseShape*>::const_iterator it = cluster.begin(), itend = cluster.end(); it < itend; ++it) {
      TCatPulseShape *pulse = *it;      
      const Double_t &c = pulse->GetCharge();
      Double_t x = pulse->GetX();
      Double_t y = pulse->GetY();
      Double_t z = pulse->GetZ();
      Double_t dxy = TMath::Abs(vy * x - vx * y - vy * mx + vx * my) / TMath::Sqrt(vy * vy + vx * vx);
      Double_t dyz = TMath::Abs(vz * y - vy * z - vz * my + vy * mz) / TMath::Sqrt(vz * vz + vy * vy);
      Double_t dzx = TMath::Abs(vx * z - vz * x - vx * mz + vz * mx) / TMath::Sqrt(vx * vx + vz * vz);
      varx += c * dyz * dyz;
      vary += c * dzx * dzx;
      varz += c * dxy * dxy;
   }
   vary = TMath::Sqrt(vary/sum);
   varz = TMath::Sqrt(varz/sum);
   varx = TMath::Sqrt(varx/sum);

   // set values
   fDeviation.SetXYZ(varx,vary,varz);
}


void TCatTpcTrack::SetResults(const std::vector<art::TCatPulseShape*>& input, const TVector3& start, const TVector3& end,
                              TCatDiffusedChargeResponseHelper *helper)
{
   if (!fIsInitialized || !fHitsHelper) {
      Error("SetResults","Not Initialized Yet. Please call Init() before use.");
      return;
   }
   if (!helper) {
      Error("SetResults","Charge response helper is not ready");
      return;
   }
   

   const TCatReadoutPadArray *readoutPadArray = helper->GetReadoutPadArray();
   const TRangeTableHelper *rangeTableHelper = helper->GetRangeTableHelper();
   fHits.clear();
   fHitsHelper->Clear("C");
   fStartPoint = start;
   fOriginalStartPoint = start;
   fEndPoint   = end;
   fDirection  = end - start;
   fRange = fDirection.Mag();
   helper->SetTrack(start,end);
   fCharge = 0;
   fEnergyDeposit  = 0;
   for (std::size_t i = 0, n = input.size(); i < n; i++) {
      const TCatPulseShape *const pulse = input[i];
      const Int_t id = pulse->GetID();
      const TCatReadoutPad *const pad   = static_cast<TCatReadoutPad*> (readoutPadArray->UncheckedAt(id));
      TCatTrackResultPulse *out = NewHit();
      Double_t charge;
      Double_t closest;
      Double_t angle;
      Double_t rangeToEnd;
      Double_t trackLength = 0.;
      Double_t dedx = TMath::QuietNaN();
      Int_t num;
      
      std::vector<TVector3> intersection;
      helper->GetResponse(id,charge,closest,angle, rangeToEnd, trackLength);
      fCharge += pulse->GetCharge();
      fEnergyDeposit += charge;
#if 0      
      pad->GetIntersection(fStartPoint,fEndPoint,intersection);
      num = intersection.size();
      switch (num) {
      case 2: 
         trackLength = (intersection[0]-intersection[1]).Mag();
         {
            Double_t r1 = (fEndPoint - intersection[0]).Mag();
            Double_t r2 = (fEndPoint - intersection[1]).Mag();
            dedx = TMath::Abs(rangeTableHelper->R2E(r1) - rangeTableHelper->R2E(r2));
         }
         break;
      case 1:
         if (!pad->IsInside(fEndPoint.X(),fEndPoint.Z())) break;
         trackLength = (intersection[0] - fEndPoint).Mag();
         dedx = rangeTableHelper->R2E(trackLength);
         break;
      default:
         break;
      }
#endif
      
      pulse->Copy(*out);
      out->Validate();
      out->SetEnergyDeposit(charge);
      out->SetTrackLength(trackLength);
      out->SetDEDX(charge/trackLength);
      out->SetAngle(angle);
      out->SetDistance(closest);
      out->SetRange(rangeToEnd);
   }

   
   
}

art::TCatTrackResultPulse* TCatTpcTrack::NewHit() {
   TCatTrackResultPulse *p = static_cast<TCatTrackResultPulse*>(fHitsHelper->ConstructedAt(fHitsHelper->GetEntriesFast()));
   fHits.push_back(p);
   return p;
}
