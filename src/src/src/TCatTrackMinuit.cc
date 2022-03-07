/**
 * @file   TCatTrackMinuit.cc
 * @brief  minuit routine for the CAT tracking
 *
 * @date   Created       : 2014-12-04 06:59:03 JST
 *         Last Modified : 2016-11-11 23:33:58 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 * Data
 *  
 * Parameter
 *  y0 : y of vertex
 *  z0 : z of vertex
 *  vx : x of direction 
 *  vy : y of direction
 *  vz : z of direction
 *
 * Norm of a(ax,ay,az) gives range.
 *    (C) 2014 Shinsuke OTA
 */

#include "TCatTrackMinuit.h"
#include <TMath.h>
#include <TVector3.h>
#include <TObjArray.h>
#include <TGraph.h>
#include "TCatPulseShape.h"
#include "TCatTrackResultPulse.h"
#include "TCatReadoutPad.h"
#include "TCatReadoutPadArray.h"
#include "TArtSystemOfUnit.h"
#include <TClonesArray.h>

#define POLAR 0

using art::TCatTrackMinuit;

ClassImp(TCatTrackMinuit)

TCatTrackMinuit::TCatTrackMinuit()
: fRange2EnergyTable(NULL)
{
   fDriftVelocity = 1. * TArtSystemOfUnit::cm / TArtSystemOfUnit::us;
   fWorkFunction = 40. * TArtSystemOfUnit::eV;
   Int_t p = 0;
//   if (isQuiet) {
      p = -1;
//   } else {
//      p = 0;
//   }
      SetPrintLevel(p);
   
}

TCatTrackMinuit::~TCatTrackMinuit()
{
#if 0
   if (fRange2EnergyTable) {
      delete fRange2EnergyTable;
   }
#endif
}

TCatTrackMinuit::TCatTrackMinuit(const TCatTrackMinuit& rhs)
{
}

TCatTrackMinuit& TCatTrackMinuit::operator=(const TCatTrackMinuit& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

Int_t TCatTrackMinuit:: Eval(Int_t npar, Double_t *grad, Double_t &fval, Double_t *par, Int_t flag)
{

#if POLAR
   const Double_t &r     = par[2];
   const Double_t &theta = par[3];
   const Double_t &phi   = par[4];

   
   Double_t vx = r * TMath::Sin(theta) * TMath::Cos(phi);
   Double_t vy = r * TMath::Sin(theta) * TMath::Sin(phi);
   Double_t vz = r * TMath::Cos(theta);
   fval = CalcResidual(par[0],par[1],vx,vy,vz);
#else
   fval = CalcResidual(par[0],par[1],par[2],par[3],par[4]);
#endif
   return 0;
}


void TCatTrackMinuit::GetParameters(Double_t &y0, Double_t &z0,
                                    Double_t &vx, Double_t &vy, Double_t &vz)
{
   Int_t ierr = 0;
   TString pname;
   Double_t verr,vlow,vhigh;

#if POLAR   
   Double_t r, theta, phi;
   mnpout(0, pname,y0,verr,vlow,vhigh,ierr);
   mnpout(1, pname,z0,verr,vlow,vhigh,ierr);
   mnpout(2, pname,r,verr,vlow,vhigh,ierr);
   mnpout(3, pname,theta,verr,vlow,vhigh,ierr);
   mnpout(4, pname,phi,verr,vlow,vhigh,ierr);

   vx = r * TMath::Sin(theta) * TMath::Cos(phi);
   vy = r * TMath::Sin(theta) * TMath::Sin(phi);
   vz = r * TMath::Cos(theta);
#else
   mnpout(0, pname,y0,verr,vlow,vhigh,ierr);
   mnpout(1, pname,z0,verr,vlow,vhigh,ierr);
   mnpout(2, pname,vx,verr,vlow,vhigh,ierr);
   mnpout(3, pname,vy,verr,vlow,vhigh,ierr);
   mnpout(4, pname,vz,verr,vlow,vhigh,ierr);
#endif   
}

void TCatTrackMinuit::SetParameters(Double_t y0, Double_t z0,
                                    Double_t vx, Double_t vy, Double_t vz)
{
   Int_t ier = 0;
#if POLAR   
   TVector3 vec(vx,vy,vz);

   mnparm(0,"Y0",y0,1000,0.,0.,ier);
   mnparm(1,"Z0",z0,1000,0.,0.,ier);
   mnparm(2,"R", vec.Mag(),1000.,0.,0.,ier);
   mnparm(3,"Theta", vec.Theta(),1000,0.,0.,ier);
   mnparm(4,"Phi", vec.Phi(),1000,0.,0.,ier);
#else
#if 0   
   mnparm(0,"Y0", y0, 2000.,0.,0.,ier);
   mnparm(1,"Z0", z0, 2000.,0.,0.,ier);
   mnparm(2,"VX", vx, 2000.,0.,0.,ier);
   mnparm(3,"VY", vy, 2000.,0.,0.,ier);
   mnparm(4,"VZ", vz, 2000.,0.,0.,ier);
#else   
   mnparm(0,"Y0", y0, 2.,0.,0.,ier);
   mnparm(1,"Z0", z0, 2.,0.,0.,ier);
   mnparm(2,"VX", vx, 2.,0.,0.,ier);
   mnparm(3,"VY", vy, 2.,0.,0.,ier);
   mnparm(4,"VZ", vz, 2.,0.,0.,ier);
#endif   
#endif   
}

// TCatTrackMinuit::SetData
// @param input should be an array of TCatPulseShape for the moment
void TCatTrackMinuit::SetData(TObjArray *input) 
{

   fHits = input;
   Int_t ier = 0;

   Double_t Xsum = 0.;
   Double_t Ysum = 0.;
   Double_t Zsum = 0.;
   Double_t XXsum = 0.;
   Double_t XYsum = 0.;
   Double_t XZsum = 0.;
   Double_t y0 = 0. ,z0 = 0.,vx = 0., vy = 0., vz = 0.;
   Int_t idend;
   Double_t xend = 0.;
   Double_t xend2 = 0.;
   Double_t qend = 0;
   Double_t qend2 = 0;
   Double_t x0 = 0;
   Double_t w = 0.;   
   // for input
   fNumData = input->GetEntriesFast();
   TVector2 vtrack;
   {   
      for (Int_t i = 0; i != fNumData; i++) {
         TCatPulseShape *pulse = (TCatPulseShape*)input->UncheckedAt(i);
         Double_t x = pulse->GetX();
         Double_t y = pulse->GetOffset() * fDriftVelocity;
         Double_t z = pulse->GetZ();
         Double_t c = pulse->GetCharge();
         w += c;
         printf("id = %d, (%5.3f,%5.3f,%5.3f), %7.5f\n",pulse->GetID(),x,y,z,c);
         x0 = (z - fP0) / fP1;
         Xsum += x * c;
         Ysum += y * c;
         Zsum += z * c;
         XXsum += x * x * c;
         XYsum += x * y * c;
         XZsum += x * z * c;
#if 1
         // calculate distance from beam
         if (TMath::Abs(xend-x0) < TMath::Abs(x-x0)) {
            xend = x;
            qend = pulse->GetCharge();
         idend = pulse->GetID();
         }
#else // alpha source
         if (xend > x) {
            xend = x;
            idend = pulse->GetID();
         }
#endif
      }
      for (Int_t i = 0; i != fNumData; i++) {
         TCatPulseShape *pulse = (TCatPulseShape*)input->UncheckedAt(i);
         Double_t x = pulse->GetX();
         if (TMath::Abs(xend2-x0) < TMath::Abs(x-x0) && TMath::Abs(x-x0) < TMath::Abs(xend - x0)) {
            xend2 = x;
            qend2 = pulse->GetCharge();
         }
      }
      xend = (qend2 * xend2 + qend * xend) /  (qend2 + qend);
   
      // estimate an initial parameter
      y0 = (XXsum * Ysum - XYsum * Xsum) / (w * XXsum -  Xsum * Xsum);
      z0 = (XXsum * Zsum - XZsum * Xsum) / (w * XXsum -  Xsum * Xsum);
      vy = (w * XYsum  - Xsum * Ysum) / (w * XXsum -  Xsum * Xsum);
      vz = (w * XZsum  - Xsum * Zsum) / (w * XXsum -  Xsum * Xsum);
      z0 = vz * x0 + z0;
      y0 = vy * x0 + y0;
      vx = xend;
      vy *= vx;
      vz *= vx;
      vtrack.Set(vx,vz);

      
   }


   const Double_t nextDistance = 6.;
   std::vector<Double_t> pairX;
   std::vector<Double_t> pairZ;
   std::vector<Double_t> pairCharge;
   for (Int_t i = 0; i != fNumData; i++) {
      for (Int_t j=i+1; j != fNumData; j++) {
         TCatPulseShape *pulse1 = (TCatPulseShape*)input->UncheckedAt(i);
         TCatPulseShape *pulse2 = (TCatPulseShape*)input->UncheckedAt(j);
         Double_t x1 = pulse1->GetX();
         Double_t z1 = pulse1->GetZ();
         Double_t x2 = pulse2->GetX();
         Double_t z2 = pulse2->GetZ();
         if ((x1-x2)*(x1-x2) + (z1-z2)*(z1-z2) > nextDistance * nextDistance)  {
            continue;
         }
         Double_t c1 = pulse1->GetCharge();
         Double_t c2 = pulse2->GetCharge();
         Double_t ratio = (c2-c1)/(c1+c2);
         Double_t xm = (x1+x2) * 0.5;
         Double_t zm = (z1+z2) * 0.5;
         Double_t xd = (x2- x1);
         Double_t zd = (z2- z1);
         TVector2 vmean(xm,zm);
         TVector2 v12(xd,zd);
         Double_t phi = v12.DeltaPhi(vtrack);
         if (phi < -TMath::Pi()/2.) {
            v12 = v12.Rotate(90./180.*TMath::Pi());
         } else if (phi < 0) {
            v12 = v12.Rotate(-90./180.*TMath::Pi());
         } else if (phi < TMath::Pi()) {
            v12 = v12.Rotate(-90./180.*TMath::Pi());
         } else {
            v12 = v12.Rotate(90./180.*TMath::Pi());
         }
         TVector2 pos1 = vmean + ratio * 10./2. * v12.Unit();
         TVector2 pos2 = vmean - ratio * 10./2. * v12.Unit();
         pairX.push_back(pos1.X());
         pairZ.push_back(pos1.Y());
         pairCharge.push_back(c1+c2);
         pairX.push_back(pos2.X());
         pairZ.push_back(pos2.Y());
         pairCharge.push_back(c1+c2);
         // printf("id = %d id = %d x = %f y = %f c = %f\n",pulse1->GetID(),pulse2->GetID(),pos.X(),pos.Y(),c1+c2);
      }
   }


   
   if (0) {
      
      Double_t Xsum = 0.;
      Double_t Ysum = 0.;
      Double_t Zsum = 0.;
      Double_t XXsum = 0.;
      Double_t XYsum = 0.;
      Double_t XZsum = 0.;
      Double_t xend = 0.;
      Double_t xend2 = 0.;
      Double_t qend = 0;
      Double_t qend2 = 0;
      Int_t fNumData = pairX.size();
      w = 0;
      for (Int_t i = 0; i != fNumData; i++) {
         Double_t x = pairX[i];
         Double_t z = pairZ[i];
         Double_t c = pairCharge[i];
         // printf("x = %f z = %f c = %f\n",x,z,c);
         w += c;
         x0 = 0.;
         Xsum += x * c;
         Zsum += z * c;
         XXsum += x * x * c;
         XZsum += x * z * c;
      
         // calculate distance from beam
         if (TMath::Abs(xend-x0) < TMath::Abs(x-x0)) {
            xend = x;
            qend = pairCharge[i];
         }
      }
      for (Int_t i = 0; i != fNumData; i++) {
         Double_t x = pairX[i];
         if (TMath::Abs(xend2-x0) < TMath::Abs(x-x0) && TMath::Abs(x-x0) < TMath::Abs(xend - x0)) {
            xend2 = x;
            qend2 = pairCharge[i];
         }
      }      
      xend = (qend2 * xend2 + qend * xend) /  (qend2 + qend);
   
      // estimate an initial parameter
      z0 = (XXsum * Zsum - XZsum * Xsum) / (w * XXsum -  Xsum * Xsum);
      vz = (w * XZsum  - Xsum * Zsum) / (w * XXsum -  Xsum * Xsum);
      z0 = vz * x0 + z0;
      vx = xend;
      vz *= vx;

   }
#if 0
   Double_t step = 5.;
   Double_t chi2;
   Double_t chi2min = TMath::Limits<Double_t>::Max();
   Double_t vxmin = 0;
   Double_t vzmin = 0;
   Double_t z0min = 0;

   for (Int_t ix = 0; ix != 2; ++ix) {
      for (Int_t iz = 0; iz != 2; ++iz) {
         for (Int_t iz2 = 0; iz2 != 2; ++iz2) {
            chi2 = CalcResidual(y0,z0+(iz2-1)*step,vx+(ix-1)*step,vy,vz+(iz-1)*step);
            if (chi2 > chi2min) continue;
            chi2min = chi2;
            vxmin = vx +(ix-1)*step;
            vzmin = vz +(iz-1)*step;
            z0min = z0+(iz2-1)*step;
         }
      }
   }
   vx = vxmin;
   vz = vzmin;
   z0 = z0min;
#endif      
   
#if 0
   Double_t chi2;
   Double_t chi2min = TMath::Limits<Double_t>::Max();
   Double_t vxmin = 0;
   Double_t vzmin = 0;
   for (Int_t i=0; i!=11; ++i) {
      chi2 = CalcResidual(y0,z0,vx+i-5,vy,vz+i-5) ;
      if (chi2 < chi2min) {
         chi2min = chi2;
         vxmin = vx+i-5;
         vzmin = vz+1-5;
      }
   }
   vx = vxmin;
   vz = vzmin;
   chi2min = TMath::Limits<Double_t>::Max();   
   for (Int_t i=0; i!=11; ++i) {
      chi2 = CalcResidual(y0,z0,vx+i-5,vy,vz-i+5) ;
      if (chi2 < chi2min) {
         chi2min = chi2;
         vxmin = vx+i-5;
         vzmin = vz-i+5;
      }
   }
   vx = vxmin;
   vz = vzmin;
   chi2min = TMath::Limits<Double_t>::Max();   
   for (Int_t i=0; i!=11; ++i) {
      Double_t diff = (i-5) * 0.1;
      printf("diff = %f\n",diff);
      chi2 = CalcResidual(y0,z0+diff,vx,vy,vz-diff) ;
      if (chi2 < chi2min) {
         chi2min = chi2;
         vxmin = z0+diff;
         vzmin = vz-diff;
      }
   }
   z0 = vxmin;
   vz = vzmin;
#endif         
   Double_t arglist[10];
   arglist[0] = 1;
   mnexcm("SET ERR",arglist,1,ier);
   arglist[0] = 1;
   mnexcm("SET STR",arglist,1,ier);
   arglist[0] = 1;
   mnexcm("SET EPS",arglist,1,ier);
   SetParameters(y0,z0,vx,vy,vz);

//   mnparm(2,"Vx",vx,10.,0.,0.,ier);
//   mnparm(3,"Vy",vy,TMath::Abs(0.1*vy)+0.0001,0.,0.,ier);
//   mnparm(4,"Vz",vz,10.,0.,0.,ier);

#if 1
   printf("Init: Y0, Z0, vx Vy, Vz = %f %f %f %f %f\n",y0,z0,vx,vy,vz);
#endif
   
}

void TCatTrackMinuit::SetReadoutPadArray(TCatReadoutPadArray *array)
{
   fPadArray = array;
}

void TCatTrackMinuit::SetRangeTable(TGraph *table)
{
   fRangeTable = table;
   fRange2EnergyTable = new TGraph(table->GetN());
   for (Int_t i=0; i!=table->GetN(); i++) {
      fRange2EnergyTable->SetPoint(i,table->GetY()[i],table->GetX()[i]);
   }
   fRange2EnergyTable->Print();
}
 

Double_t TCatTrackMinuit::CalcResidual(Double_t y0, Double_t z0, Double_t vx, Double_t vy, Double_t vz, TClonesArray *output)
{
   // printf("#### calc ####\n");
   static TGraph gr(4);
   static std::vector<Double_t> trackE;
   static std::vector<Double_t> trackY;
   static std::vector<TVector3*> vertex;
   if (output) output->Clear("C");
   Double_t x0 = (z0 - fP0) / fP1;
   TVector3 va(vx,vy,vz); // direction
//   va *= vx;
   TVector3 a1(x0,y0,z0);
   TVector3 a2 = a1 + va;
   Double_t length = 0;
   Int_t    nHits = fHits->GetEntriesFast();
   Double_t fcn = 0.;
   TVector3 outputv[10];
   printf("nHits = %d\n",nHits);
   for (Int_t iHit = 0; iHit != nHits; ++iHit) {
      trackE.clear();
      trackY.clear();
      vertex.clear();
      TCatPulseShape *pulse = (TCatPulseShape*) fHits->UncheckedAt(iHit);
      TCatReadoutPad *pad = (TCatReadoutPad*) fPadArray->At(pulse->GetID());
      TCatTrackResultPulse *outpulse = (TCatTrackResultPulse*) ((output) ? output->ConstructedAt(output->GetEntriesFast()): NULL);
      if (outpulse) {
         pulse->Copy(*(TCatPulseShape*)outpulse);
      }
      if (!pad) {
         Error("Eval","pad %p for pad id = %d\n",pad,pulse->GetID());
         return 1e10; // large value. is this ok?
      }
      Int_t nP = (pad->GetNumPoints() -1);
      const Double_t *x = pad->VertexX();
      const Double_t *y = pad->VertexY();
      for (Int_t iP=0; iP!=nP; iP++) {
         TVector3 b1(x[iP],0,y[iP]);
         TVector3 b2(x[iP+1],0,y[iP+1]);
         if (FindVertex(a1,a2,b1,b2,outputv[iP])){
            vertex.push_back(&outputv[iP]);
         }
      }
      if (vertex.size() > 2) {
         UniqueVector3(vertex);
      }
      Double_t edep = 0.;
      Double_t yhit = 0.;
      gr.SetPoint(0,x[0],y[0]);
      gr.SetPoint(1,x[1],y[1]);
      gr.SetPoint(2,x[2],y[2]);
      gr.SetPoint(3,x[3],y[3]);
      switch (vertex.size()) {
      case 0:
         // No crossing point is found. Diffusion or noise may cause this hit.
         // calculate the error from poisson for energy
         break;
      case 1:
         // a1 or a2 exist in this pad
         if (gr.IsInside(a1.X(),a1.Z())) {
            // first point
            edep = fRange2EnergyTable->Eval((a2-a1).Mag()) - fRange2EnergyTable->Eval((a2- *vertex[0]).Mag());
            yhit = TMath::Min(vertex[0]->Y(),a1.Y());
            length = (a1 - *vertex[0]).Mag();
         } else if (gr.IsInside(a2.X(),a2.Z())) {
            // last point
            edep = fRange2EnergyTable->Eval((a2- *vertex[0]).Mag());
            yhit = TMath::Min(vertex[0]->Y(),a2.Y());
            length = (a2-*vertex[0]).Mag();
         } else {
            Error("CalcResidual","NP = 1: Position was not extracted correctly");
            edep = 0;
            yhit = 0;
         }
         break;
      case 2:
         edep = TMath::Abs(fRange2EnergyTable->Eval((a2- *vertex[0]).Mag()) - fRange2EnergyTable->Eval((a2- *vertex[1]).Mag()));
         yhit = TMath::Min(vertex[0]->Y(),vertex[1]->Y());
         length = (*vertex[0] - *vertex[1]).Mag();
         break;
      default:
         Error("CalcResidual","Unexpected vertex points (N = %d)",(Int_t)vertex.size());
         vertex[0]->Print();
         vertex[1]->Print();
         vertex[2]->Print();
         break;
      }
//      Double_t dEdep = TMath::Sqrt(fWorkFunction * pulse->GetCharge());
      Double_t dEdep = 0.1 * pulse->GetCharge();
      Double_t fcnE = (pulse->GetCharge() - edep) / dEdep;
      /* TODO
       * Standard error for y direction should be variable
       */
      Double_t fcnY = ((pulse->GetOffset() * fDriftVelocity) - yhit) / 0.05; // mm
      fcn += fcnE * fcnE + fcnY * fcnY;
      if (outpulse) {
         outpulse->SetCharge(edep);
         outpulse->SetOffset(yhit/fDriftVelocity);
         outpulse->SetTrackLength(length);
         outpulse->SetDEDX(edep/length);
      }
      if (output != NULL) {
         printf("%f %f %f \n",fcn,fcnE,fcnY);
         printf("id = %d e : (%f %f) y: (%f %f)\n",
                pulse->GetID(),
                edep, pulse->GetCharge(), yhit, pulse->GetOffset()*fDriftVelocity);
      }
   }
   // printf("#### calc done ####\n");
   return fcn;
}

Bool_t TCatTrackMinuit::FindVertex(const TVector3 &a1, const TVector3 &a2,
                const TVector3 &b1, const TVector3 &b2,
                TVector3 &output)
{
   const Double_t EPS = TMath::Limits<Double_t>::Epsilon();
   TVector3 va = a2 - a1;
   TVector3 vb = b2 - b1;
   if (!(va.Cross(b1-a1).Y() * va.Cross(b2-a1).Y() < EPS)  || 
       !(vb.Cross(a1-b1).Y() * vb.Cross(a2-b1).Y() < EPS)) {
      // two line segments do not cross each other
      return kFALSE;
   }
   Double_t d1 = TMath::Abs(vb.Cross(a1-b1).Y());
   Double_t d2 = TMath::Abs(vb.Cross(a2-b1).Y());
   Double_t t = d1/(d1+d2);
   output.SetX(a1.X() + t *va.X());
   output.SetY(a1.Y() + t *va.Y());
   output.SetZ(a1.Z() + t *va.Z());
   return kTRUE;
}

// @TODO!!! what does 'erase' do?
void TCatTrackMinuit::UniqueVector3(std::vector<TVector3*> &vec) {
   std::vector<TVector3*>::iterator it = vec.begin();
   while (it != vec.begin()) {
      std::vector<TVector3*>::iterator it2 = it + 1;
      while (it2 != vec.end()) {
         if ((**it2 - **it).Mag() < TMath::Limits<Double_t>::Epsilon()) {
            it2 = vec.erase(it2);
         } else {
            ++it2;
         }
      }
      ++it;
   }
}
