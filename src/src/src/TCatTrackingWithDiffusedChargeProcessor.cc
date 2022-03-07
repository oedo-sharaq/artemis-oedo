/*
 * @file   TCatTrackingWithDiffusedChargeProcessor.cc
 * @brief  tracking with diffused charge
 *
 * @date   Created       : 2016-07-24 08:49:05 JST
 *         Last Modified : 2019-07-04 22:11:29 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#include "TCatTrackingWithDiffusedChargeProcessor.h"
#include <TCatTrackDiffusedMinuitHelper.h>
#include <TCatPulseShape.h>
#include <TCatTrackResult.h>
#include <TCatTrackResultPulse.h>
#include <TClonesArray.h>
#include <TMath.h>
#include <Math/GSLSimAnMinimizer.h>
#include <Math/GSLMinimizer.h>
#include <Math/GSLNLSMinimizer.h>
#include <Math/GeneticMinimizer.h>
#include <Minuit2/Minuit2Minimizer.h>
#include <Minuit2/MnPrint.h>
#include <TCatReadoutPadArray.h>
#include <TCatReadoutPad.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TSystem.h>
#include <TRangeTableHelper.h>
#include <TF1.h>
#include <TH2F.h>
#include <algorithm>
#include <TStopwatch.h>
#include <TDirectory.h>
#include <TCatTpcTrack.h>
#include <TRandom.h>
using art::TCatTrackingWithDiffusedChargeProcessor;

ClassImp(TCatTrackingWithDiffusedChargeProcessor)


TCatTrackingWithDiffusedChargeProcessor::TCatTrackingWithDiffusedChargeProcessor()
: fNameInput(""),fInput(NULL), fNameOutput(""), fOutput(NULL)
{
   DoubleVec_t defSigmaCoeff(3);
   defSigmaCoeff[0] = 0;
   defSigmaCoeff[1] = 1.;
   defSigmaCoeff[2] = 0.;

   RegisterInputCollection("InputCollection","input array name", fNameInput, TString("atpulse"),
                           &fInput,TClonesArray::Class_Name(),TCatTpcTrack::Class_Name());
   RegisterOutputCollection("OutputCollection","tracking result collection", fNameOutput, TString("track"),
                            &fOutput,TClonesArray::Class_Name(),TCatTpcTrack::Class_Name());
   RegisterOutputCollection("NameCpuTime","Cpu Time", fNameCpuTime, TString("cputime"),
                            "D",&fCpuTime);
   RegisterProcessorParameter("IndependentVariable","In order to calculate the initial parameter, this variable is used as a independent variable",
                              fIndependentVariable,(Int_t)kAxisX);
   RegisterProcessorParameter("FixedOrigin","fixed origin parameter of the independent axis (as an assumption)",fFixedOrigin,0.);
   RegisterProcessorParameter("DoMeshSearch","flag to do mesh search (default: 1 to do, 0)",fDoMeshSearch,kTRUE);
   RegisterProcessorParameter("SigmaCoeff","coefficient to calculate sigma in TCatFunctionChargeResidual as sqrt(s0*s0+s1*s1*N*N)",
                              fSigmaCoeff,defSigmaCoeff);
   {
      Int_t dim[] = {20,20,20};
      IntVec_t defaultMeshDim(dim,dim+sizeof(dim)/sizeof(Int_t));
      RegisterProcessorParameter("MeshDim","dimension of mesh search. [range, offset, slope]",fMeshDim,defaultMeshDim);
   }
   {
      Double_t step[] = {10.,1.,0.1};
      DoubleVec_t defaultMeshStep(step,step+sizeof(step)/sizeof(Double_t));
      RegisterProcessorParameter("MeshStep","step of mesh search. secondary search will be performed with 1/10 step. [range, offset, slope]",
                                 fMeshStep,defaultMeshStep);
   }
   RegisterOptionalParameter("InitialRange","set initial range if non zero (default 0), fix range in minuit minimization  if positive ",fInitialRange,0.);

   RegisterOptionalParameter("MinuitMinType",
                             "type of minimizer (simplex (default) or migrad) case insensitive",
                             fMinuitMinTypeName,TString("simplex"));
   RegisterOptionalParameter("Offset","fixed offset for rest of independent axis (other than Y direction) X0 for idependent Z, Z0 for independent X",fOffset,TMath::QuietNaN());
   RegisterHelper(&fEventDisplayHelper);
   RegisterHelper(&fChargeResponseHelper);



   // initialization
   fEMinuitMinType = ROOT::Minuit2::kSimplex;
}

TCatTrackingWithDiffusedChargeProcessor::~TCatTrackingWithDiffusedChargeProcessor()
{

}

TCatTrackingWithDiffusedChargeProcessor::TCatTrackingWithDiffusedChargeProcessor(const TCatTrackingWithDiffusedChargeProcessor& rhs)
{
}

TCatTrackingWithDiffusedChargeProcessor& TCatTrackingWithDiffusedChargeProcessor::operator=(const TCatTrackingWithDiffusedChargeProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

TCanvas *canvas;

void TCatTrackingWithDiffusedChargeProcessor::Init(TEventCollection *col)
{
   // check and assign minuit type
   if (fMinuitMinTypeName.EqualTo("simplex",TString::kIgnoreCase)) {
      fEMinuitMinType = ROOT::Minuit2::kSimplex;
   } else if (fMinuitMinTypeName.EqualTo("migrad",TString::kIgnoreCase)) {
      fEMinuitMinType = ROOT::Minuit2::kMigrad;
   } else if (fMinuitMinTypeName.EqualTo("minimize",TString::kIgnoreCase)) {
      fEMinuitMinType = ROOT::Minuit2::kCombined;
      
   } else {
      // unknown
      SetStateError(TString::Format("Unknown minimization type: %s",fMinuitMinTypeName.Data()));
      return;
   }

   
   if (fSigmaCoeff.size() != 3) {
      SetStateError("SigmaCoeff should have three figures, 0th, 1st and 2nd order coefficient");
      return;
   }
   fFunctionChargeResidual.SetResponseHelper(&fChargeResponseHelper);
   fFunctionChargeResidual.SetSigmaCoeff(fSigmaCoeff);   


   Int_t nTotal = fMeshDim[0] * fMeshDim[1] * fMeshDim[2];
   if (fDoMeshSearch || 1) {
      fChargeResponses.resize(nTotal);
      fFunctions.resize(nTotal);
      for (Int_t i=0; i<nTotal; i++) {
         fChargeResponseHelper.Copy(fChargeResponses[i]);
         fFunctions[i].SetResponseHelper(&fChargeResponses[i]);
         fFunctions[i].SetSigmaCoeff(fSigmaCoeff);
         fFunctions[i].SetUseTotalCharge(false);
      }
      
   }
   
   canvas = new TCanvas;
   if (fEventDisplayHelper.Displays()) {
      // prepare histogram if event display is ready 
      fHists.push_back(new TH2F("hChi2","Chi2 map",100.,0.,100,100,0.,1000.));
      TPad *pad = fEventDisplayHelper.GetMainPad();
      pad->cd();
      fHists[0]->Draw("colz");
   }


   
#if 0
   fHists.push_back(new TH2F("h01","chi2 0 vs 1",100,0.,100,100,0.,100));
   fHists.push_back(new TH2F("h12","chi2 1 vs 2",100,0.,100,100,0.,100));
   fHists.push_back(new TH2F("h23","chi2 2 vs 0",100,0.,100,100,0.,100));
   canvas->Divide(2,2);
   canvas->cd(1);
   fHists[0]->Draw();
   canvas->cd(2);
   fHists[0]->Draw();
   canvas->cd(3);
   fHists[0]->Draw();
#endif   
}

void TCatTrackingWithDiffusedChargeProcessor::Process()
{
   if (fVerboseLevel > 2) {
      Info("Process","======================================================================");
      Info("Process","                             NEW EVENT");
      Info("Process","======================================================================");
   }

   fOutput->Clear("C");
#if 1
   for (Int_t iEntry = 0, nEntry = (*fInput)->GetEntriesFast(); iEntry < nEntry; ++iEntry) {
      ReconstructTrack(static_cast<const TCatTpcTrack*>((*fInput)->UncheckedAt(iEntry)));
   }
#else   
   // initialization
   // parameter for fitting
   // for this fitting the track is assumed to start at X=0
   // y0 : y offset at X=0
   // z0 : z offset at X=0
   // range : range parameter
   // vy : slope in XY plane
   // vz : slope in ZX plane
   Double_t range = 0.;

   //////////////////////////////////////////////////
   // find the initial parameter of start and end position and range
   // In the plane of drift and independent variable, the line is
   // estimated using linear least square. 
   //////////////////////////////////////////////////
   Int_t nHits = (*fInput)->GetEntriesFast();
   if (!nHits) return;
   TCatTpcTrack *input_track = static_cast<TCatTpcTrack*>((*fInput)->UncheckedAt(0));
   const Int_t vIdx = fIndependentVariable;

   // track length in active area along vIdx axis
   // start length is shortest length 
   Double_t startLength = TMath::Limits<Double_t>::Max(); 
   // end length is shortest length 
   Double_t endLength = 0;
   // direction 
   Int_t direction = 1; // 1 or -1 
   Double_t w =0.;
   Double_t sum1[3] = {0.,0.,0.};
   Double_t sum2[3][3] = {{0.,0.,0.},{0.,0.,0.},{0.,0.,0.}};
   TVector3 va;
   TVector3 px;
   px[vIdx] = fFixedOrigin;
#if 0   
   const Double_t &x0 = px[0];
   const Double_t &y0 = px[1];
   const Double_t &z0 = px[2];
#endif   
   const Double_t &vx = va[0];
   const Double_t &vy = va[1];
   const Double_t &vz = va[2];
   nHits = input_track->GetHits().size();
   for (Int_t i = 0; i != nHits; i++) {
      TCatPulseShape *pulse = (TCatPulseShape*)(input_track->GetHits()[i]);
      const TVector3 &pos = pulse->GetPos() - px;
      Double_t c = pulse->GetCharge();
      w += c;
      for (Int_t idx = 0; idx < 3; ++idx) {
         sum1[idx] += c * pos[idx];
         for (Int_t idx2 = 0; idx2 < 3; ++idx2) {
            sum2[idx][idx2] += c * pos[idx] * pos[idx2];
         }
         if (vIdx == idx) {
            Double_t length = TMath::Abs(pos[idx]);
            if (length > endLength) {
               endLength = length;
               if (pos[idx] < 0) {
                  direction = -1;
               } else {
                  direction = 1;
               }
            }
            if (length < startLength) {
               startLength = length;
            }
         }
      }
   }

   const Double_t denominator_inv = 1./ (w * sum2[vIdx][vIdx] - sum1[vIdx] * sum1[vIdx]);
   for (Int_t idx = 0; idx < 3; ++idx) {
      if (idx == vIdx) {
         px[idx] = fFixedOrigin;
         va[idx] = 1.;
      } else {
         px[idx] = (sum2[vIdx][vIdx] * sum1[idx] - sum2[idx][vIdx] * sum1[vIdx]) * denominator_inv;
         va[idx] = (w * sum2[idx][vIdx] - sum1[idx] * sum1[vIdx]) * denominator_inv;
      }
   }
   // estimate range from charge
   // w: total charge
   // get range table helper from response helper

//   Double_t chi2min = 0.;
   if (fInitialRange > 0) {
      range = fInitialRange;
   } else {
      range = endLength * TMath::Sqrt(vx*vx + vy*vy + vz*vz);
      if (endLength > 40) {
         std::vector<Double_t> xval;
         std::vector<Double_t> yval;

         { // range search with total charge
            TGraph *r2e = fChargeResponseHelper.GetRangeTableHelper()->GetR2E();
            Double_t fWorkFunction = fChargeResponseHelper.GetWorkFunction();
            Double_t trackstart = startLength * TMath::Sqrt(vx*vx + vy*vy + vz*vz);
            Double_t trackend = range;
            Double_t rangeorg = range;
            Int_t doLast = 5;
            for (Int_t i = 0; i < 100; i++) {
               range = rangeorg + (i-1) * 10;
               if (range - trackend < 0) continue;
               Double_t estimation  = (r2e->Eval(range - trackstart) - r2e->Eval(range - trackend))/fWorkFunction ;
               Double_t measurement = w/fWorkFunction;
               Double_t diff = (estimation - measurement) * (estimation - measurement) / measurement;
               xval.push_back(range);
               yval.push_back(diff);
               if (fVerboseLevel > 2) {
                  printf("[%02d] range = %f, trackstart = %f, trackend = %f, measurement = %f, estimation = %f, diff2 = %f\n",i,range,trackstart,trackend,measurement,estimation,diff);
               }
               if (diff < 10. || doLast < 5) {
                  doLast--;
               }
               if (doLast < 0) {
                  break;
               }
            }
         }
         TGraph gr(xval.size(),&xval[0],&yval[0]);
         std::vector<Double_t>::iterator  it = std::min_element(yval.begin(),yval.end());
         Int_t minIdx = std::distance(yval.begin(),it);
         Double_t rangeAtMin = xval[minIdx];
         // printf("idx = %d, rangeAtMin = %f\n",minIdx, rangeAtMin);
         if (minIdx == 0) {
            range = rangeAtMin;
         } else {
            Double_t halfWidth = 10 * ((minIdx < 5) ? minIdx : 5);
            TF1 fun("fun","[0]*(x-[1])*(x-[1]) + [2]",rangeAtMin-halfWidth,rangeAtMin+halfWidth);
            fun.SetParameters(1,rangeAtMin,*it);
            gr.Fit(&fun,"Q","",rangeAtMin -halfWidth,rangeAtMin+halfWidth);
            range = fun.GetParameter(1);

         }
      }
      if (fVerboseLevel > 2) {
         printf("Estimated range = %f\n",range);
      }
   }
   range *= direction;
   va = va.Unit();

   

   //////////////////////////////////////////////////
   // display initial values
   //////////////////////////////////////////////////
   if (fVerboseLevel > 2) {
      printf("**************************************************\n");
   
      printf("init: x0 = %f, y0 = %f, z0 = %f, range = %f, vx = %f, vy = %f, vz = %f\n",px[0],px[1],px[2],range,va[0],va[1],va[2]);
   }
   //////////////////////////////////////////////////
   // perform fitting
   //////////////////////////////////////////////////


   std::vector<TCatPulseShape*> hits;
   const TCatReadoutPadArray *padArray = fChargeResponseHelper.GetReadoutPadArray();
   for (Int_t i=0; i<(input_track)->GetHits().size(); i++) {
      TCatPulseShape *pulse = static_cast<TCatPulseShape*>(input_track->GetHits()[i]);
      TCatReadoutPad *pad = static_cast<TCatReadoutPad*>(padArray->UncheckedAt(pulse->GetID()));
      if (!pad->IsBad() && pulse->IsValid()) {
         hits.push_back(pulse);
      }
   }

   // insert null pulse
#if 0 // checking
   {
      TCatReadoutPadArray **fReadoutPadArray = fTrackDiffusedMinuitHelper->GetReadoutPadArray();
      const Double_t clusterRadius = 8.2;
      const Double_t xdistance = 2.5; // distance between x coordinate in the same column
      const Int_t nPads = (*fReadoutPadArray)->GetEntriesFast();
      std::vector<Int_t> used(nPads,0);
      std::vector<TCatPulseShape*> nullpulses;
      Double_t xmin = TMath::Abs(TMath::Limits<Double_t>::Max());
      Double_t xmax = TMath::Abs(TMath::Limits<Double_t>::Min());
      Double_t zmin = TMath::Limits<Double_t>::Max();
      Double_t zmax = TMath::Limits<Double_t>::Min();
      std::vector<TCatPulseShape*> &fHits = hits;
      static TClonesArray *fPulseHelper = new TClonesArray(TCatPulseShape::Class_Name());
      
      for (std::vector<TCatPulseShape*>::iterator it = fHits.begin(), end = fHits.end(); it != end; ++it) {
         TCatPulseShape* pulse = *it;
         const Double_t x = pulse->GetX();
         const Double_t z = pulse->GetZ();
         used[pulse->GetID()] = 1;
         if (TMath::Abs(x) < xmin) xmin = TMath::Abs(x);
         if (TMath::Abs(x) > xmax) xmax = TMath::Abs(x);
         if (z < zmin) zmin = z;
         if (z > zmax) zmax = z;
      }
      xmin = xmin - xdistance;
      xmax = xmax + clusterRadius;
      zmin -= clusterRadius;
      zmax += clusterRadius;
      if (fVerboseLevel > 2) {
         printf("xmin = %5.3f, xmax = %5.3f, zmin = %5.3f, zmax = %5.3f\n",xmin,xmax,zmin,zmax);
      }
      
      for (Int_t i=0; i<nPads; ++i) {
         const TCatReadoutPad* pad = static_cast<TCatReadoutPad*>((*fReadoutPadArray)->UncheckedAt(i));
         if (!pad->IsGood()) continue;
         const Int_t    id = pad->GetID();
         const Double_t x = pad->X();
         const Double_t z = pad->Y();
         if (TMath::Abs(x) < xmin || TMath::Abs(x) > xmax || z < zmin || z > zmax || used[id]) {
            // out of range or already included 
            continue;
         }
         for (std::vector<TCatPulseShape*>::iterator it = fHits.begin(), end = fHits.end(); it != end; ++it) {
            TCatPulseShape* pulse = (*it);
            const Double_t x1 = pulse->GetX();
            const Double_t z1 = pulse->GetZ();
            if (TMath::Sqrt(TMath::Power(x - x1,2.)+TMath::Power(z - z1,2.)) > clusterRadius) {
               continue;
            }
            TCatPulseShape *dummy = static_cast<TCatPulseShape*>(fPulseHelper->ConstructedAt(fPulseHelper->GetEntriesFast()));
            dummy->SetID(id);
            dummy->SetCharge(0);
            dummy->GetPos().SetXYZ(x,pulse->GetY(),z);
            dummy->SetOffset(pulse->GetOffset());
            nullpulses.push_back(dummy);
            used[id] = 1;
            break;         
         }
      }
      std::copy(nullpulses.begin(),nullpulses.end(),std::back_inserter(fHits));
   }      
#endif
   fFunctionChargeResidual.SetHits(hits);

   // minimization with new minimizer framework
//   ROOT::Math::GSLMinimizer min(ROOT::Math::kConjugatePR);

   TStopwatch watch;
   watch.Start();
   ROOT::Minuit2::Minuit2Minimizer min2(ROOT::Minuit2::kScan);
   // mesh search 
   if (fDoMeshSearch) {
      Int_t nRange = fMeshDim[0];
      Int_t n0 = fMeshDim[1];
      Int_t nV = fMeshDim[2];
      Int_t numMeshTotal = nRange * n0 * nV;
      Double_t stepRange = fMeshStep[0];
      Double_t step0 = fMeshStep[1];
      Double_t stepV = fMeshStep[2];
      Double_t min = TMath::Limits<Double_t>::Max();
      Int_t varIdx = (vIdx == 0) ? 2 : 0;
      Double_t minRange = range;
      Double_t min0 = px[varIdx];
      Double_t minV = va[varIdx];
      Double_t xorg[] = {px[0], px[1], px[2],
                         va[0], va[1], va[2],
                         range};
      fFunctionChargeResidual.SetVerboseLevel(0);
      Double_t chi2 = fFunctionChargeResidual.DoEval(xorg);
      fFunctionChargeResidual.SetVerboseLevel(0);
      if (fVerboseLevel > 2) {
         printf("chi2 orginal = %f\n",chi2);
      }
      

      std::vector<Double_t> chi2val(numMeshTotal);
      std::vector<Double_t> val0(numMeshTotal);
      std::vector<Double_t> valV(numMeshTotal);
      std::vector<Double_t> valR(numMeshTotal);

v#pragma omp parallel for
      for (Int_t iRange = 0; iRange < nRange; ++iRange) {
#pragma omp parallel for
         for (Int_t i0 = 0; i0 < n0; ++i0) {
#pragma omp parallel for
            for (Int_t iV = 0; iV < nV; ++iV) {
               Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                                  xorg[3],xorg[4],xorg[5],
                                  range + (iRange - nRange/2.) * stepRange};
               
               xnew[varIdx]   +=  (i0 - n0/2.)*step0;
               xnew[varIdx+3] += (iV - nV/2.)*stepV;
               
	       //               TVector3 p1(xnew[0],xnew[1],xnew[2]);
	       //               TVector3 v1 = TVector3(xnew[3],xnew[4],xnew[5]).Unit();
//               if (TMath::Abs(xnew[1] + (100.+TMath::Abs(fFixedOrigin))/xnew[vIdx] * v1[1] * range / TMath::Abs(range)) > 100.) continue;
               
               // z0
               Int_t idx = (iRange *  n0 + i0) * nV + iV;
               fFunctions[idx].SetHits(hits);
               Double_t chi2 = fFunctions[idx].DoEval(xnew);
               chi2val[idx] = chi2;
               val0[idx] = xnew[varIdx];
               valV[idx] = xnew[varIdx + 3];
               valR[idx] = xnew[6];
            }
         }
      }
      std::vector<Double_t>::iterator it = std::min_element(chi2val.begin(),chi2val.end());
      Int_t idx = std::distance(chi2val.begin(),it);
      min = *it;
      min0 = val0[idx];
      minV = valV[idx];
      minRange = valR[idx];


      if (fVerboseLevel > 2) {
         printf("chi2 first = %f at min0 = %f, minV = %f, minRange = %f\n",min,min0,minV,minRange);
      }
      stepRange = fMeshStep[0]/10.;
      step0 = fMeshStep[1]/10.;
      stepV = fMeshStep[2]/10.;
      xorg[varIdx] = min0;
      xorg[varIdx+3] = minV;
      xorg[6] = minRange;

#pragma omp parallel for
      for (Int_t iRange = 0; iRange < nRange; ++iRange) {
#pragma omp parallel for
         for (Int_t i0 = 0; i0 < n0; ++i0) {
#pragma omp parallel for
            for (Int_t iV = 0; iV < nV; ++iV) {
               Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                                  xorg[3],xorg[4],xorg[5],
                                  xorg[6] + (iRange - nRange/2.) * stepRange};
               xnew[varIdx]   +=  (i0 - n0/2.)*step0;
               xnew[varIdx+3] += (iV - nV/2.)*stepV;
               
	       //               TVector3 p1(xnew[0],xnew[1],xnew[2]);
	       //               TVector3 v1 = TVector3(xnew[3],xnew[4],xnew[5]).Unit();
//               if (TMath::Abs(xnew[1] + (100.+TMath::Abs(fFixedOrigin))/xnew[vIdx] * v1[1] * range / TMath::Abs(range)) > 100.) continue;
               
               // z0 
               Int_t idx = (iRange *  n0 + i0) * nV + iV;
               fFunctions[idx].SetHits(hits);
               Double_t chi2 = fFunctions[idx].DoEval(xnew);
               chi2val[idx] = chi2;
               val0[idx] = xnew[varIdx];
               valV[idx] = xnew[varIdx + 3];
               valR[idx] = xnew[6];
            }
         }
      }
      it = std::min_element(chi2val.begin(),chi2val.end());
      idx = std::distance(chi2val.begin(),it);
      min = *it;
      min0 = val0[idx];
      minV = valV[idx];
      minRange = valR[idx];
      px[varIdx] = min0;
      va[varIdx] = minV;
      range = minRange;
      if (fVerboseLevel > 2) {
         printf("chi2 second = %f at min0 = %f, minV = %f, minRange = %f\n",min,min0,minV,minRange);
      }
      
#if 0
      nRange = 20;
      n0 = 20;
      nV = 20;
      stepRange = 0.1;
      stepV = 0.001;
      printf("chi2 min = %f at p0 = %f, pv = %f, range = %f\n",min,
             px[varIdx],va[varIdx],range);
      Double_t rangeMin = range - nRange/2. * stepRange - stepRange/2.;
      Double_t rangeMax = range + (nRange - 1 - nRange/2.) * stepRange + stepRange/2.;
      Double_t par0min = min0 - n0/2. * step0 - step0/2.;
      Double_t par0max = min0 + (n0 - 1 -  n0/2.) * step0 + step0/2.;
      Double_t parVmin = minV - nV/2. * stepV - stepV/2.;
      Double_t parVmax = minV + (nV - 1 -  nV/2.) * stepV + stepV/2.;
      xorg[varIdx] = min0;
      xorg[varIdx+3] = minV;
      xorg[6] = minRange;
      fHists[0]->GetXaxis()->Set(nRange,rangeMin,rangeMax);
      fHists[0]->GetYaxis()->Set(n0,par0min,par0max);
      fHists[1]->GetXaxis()->Set(n0,par0min,par0max);
      fHists[1]->GetYaxis()->Set(nV,parVmin,parVmax);
      fHists[2]->GetXaxis()->Set(nV,parVmin,parVmax);
      fHists[2]->GetYaxis()->Set(nRange,rangeMin,rangeMax);

      for (iRange = 0; iRange < nRange; ++iRange) {
         for (i0 = 0; i0 < n0; ++i0) {
            Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                               xorg[3],xorg[4],xorg[5],
                               xorg[6] + (iRange - nRange/2.) * stepRange};
            xnew[varIdx]   +=  (i0 - n0/2.)*step0;
            Double_t chi2 = fFunctionChargeResidual.DoEval(xnew);
            fHists[0]->SetBinContent(iRange + 1, i0 + 1,chi2);
         }
      }
      for (i0 = 0; i0 < n0; ++i0) {
         for (iV = 0; iV < nV; ++iV) {            
            Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                               xorg[3],xorg[4],xorg[5],
                               xorg[6]};
            xnew[varIdx]   +=  (i0 - n0/2.)*step0;
            xnew[varIdx+3] += (iV - nV/2.)*stepV;            
            Double_t chi2 = fFunctionChargeResidual.DoEval(xnew);
            fHists[1]->SetBinContent(i0 + 1,iV + 1,chi2);
         }
      }
      for (iRange = 0; iRange < nRange; ++iRange) {
         for (iV = 0; iV < nV; ++iV) {            
            Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                               xorg[3],xorg[4],xorg[5],
                               xorg[6] + (iRange - nRange/2.) * stepRange};
            xnew[varIdx+3] += (iV - nV/2.)*stepV;
            Double_t chi2 = fFunctionChargeResidual.DoEval(xnew);            
            fHists[2]->SetBinContent(iV+1,iRange + 1,chi2);
         }
      }
      
   canvas->cd(1);
   fHists[0]->Draw("colz");
   canvas->cd(2);
   fHists[1]->Draw("colz");
   canvas->cd(3);
   fHists[2]->Draw("colz");
   canvas->Update();
   canvas->Modified();
#endif      
//      Info("Process","Initial = %.10f",fFunctionChargeResidual.DoEval(min.X()));
   }

   watch.Stop();
   (*fCpuTime) = watch.CpuTime();

   if (fVerboseLevel > 1) {
      Info("Process","Mesh search done with time %f",watch.CpuTime());
   }

   
//   ROOT::Math::GSLSimAnnealing *solver = min.GetSolver()
#if 0
   ROOT::Math::GSLSimAnMinimizer min;
   min.Solver().Params().iters_fixed_T = 1000;
   min.Solver().Params().mu = 1.1;
#else   
//   ROOT::Minuit2::Minuit2Minimizer min;
   ROOT::Math::GeneticMinimizer min;
   
#endif   
   
   min.SetMaxFunctionCalls(10000);
   min.SetMaxIterations(10000);
   min.SetTolerance(1);
   min.SetPrintLevel(0);

   
   min.SetFunction(fFunctionChargeResidual);
   fFunctionChargeResidual.SetRangeUnit(TArtSystemOfUnit::mm);
   fFunctionChargeResidual.SetUseTotalCharge(false);

   min.SetVariable(0,"x0",px[0],5);
   min.SetVariable(1,"y0",px[1],1);
   min.SetVariable(2,"z0",px[2],5);
   min.SetVariable(3,"vx",va[0],0.1);
   min.SetVariable(4,"vy",va[1],0.1);
   min.SetVariable(5,"vz",va[2],0.1);
   min.SetVariable(6,"R",range,0.1);
#if 0   
   UInt_t nstep = 100;
   std::vector<double> xxx(nstep);
   std::vector<double> yyy(nstep);
   min.Scan(6,nstep,&xxx[0],&yyy[0]);
   for (Int_t i = 0; i<nstep; i++) {
      printf("xxx[%d] = %f, yyy[%d] = %f\n",i,xxx[i],i,yyy[i]);
   }
   min.SetVariableValue(6,xxx[std::distance(yyy.begin(),std::min_element(yyy.begin(),yyy.end()))]);
#endif

   min.FixVariable(fIndependentVariable);
   min.FixVariable(fIndependentVariable+3);
   min.FixVariable(1);
   min.FixVariable(4);
   if (fInitialRange > 0) {
      min.FixVariable(6);
   }
//   min.FixVariable(2);
//   min.SetVariableLimits(2,px[2]-3.5,px[2]+3.5);
//   min.SetVariableLimits(5,va[2]-0.5,va[2]+0.5);
//   min.SetVariableLimits(6,range-5,range+5);

   if (fVerboseLevel > 2) {
      fFunctionChargeResidual.SetVerboseLevel(0);
      printf("**********************************************************************\n");
      printf("Initial chi2 = %f\n",fFunctionChargeResidual.DoEval(min.X()));
      printf("**********************************************************************\n");
      fFunctionChargeResidual.SetVerboseLevel(0);
   }
   
   std::vector<double> einit;
   Double_t chi2init = 0.;
   for (Int_t i=0; i<hits.size();i++) {
      double diff = 0.;
      double qcalc = fFunctionChargeResidual.GetCharge(hits[i]->GetID());
      diff = (hits[i]->GetCharge() - qcalc) / sqrt(qcalc + 0.000000001);
      chi2init += diff * diff;
      einit.push_back(qcalc);
   }

   if (!fDoMeshSearch) {
      if (fVerboseLevel > 2) {
         min.SetPrintLevel(3);
      } else {
         min.SetPrintLevel(0);
      }
      min.SetPrecision(1e-5);
      min.SetPrintLevel(0);
      min.Minimize();
      if (fVerboseLevel > 2) {
         min.PrintResults();
      }
   }
   if (fVerboseLevel > 2) {
      Info("Process","Min = %f",min.MinValue());
      for (Int_t i=0; i<7; i++) {
         Info("Process","%3s %20f",min.VariableName(i).data(),min.X()[i]);
      }
      fFunctionChargeResidual.SetVerboseLevel(0);
      Info("Process","Last = %.10f",fFunctionChargeResidual.DoEval(min.X()));
      fFunctionChargeResidual.SetVerboseLevel(0);
   }
   
#if 0
   // minimization with minuit
   fTrackDiffusedMinuitHelper->SetData(*fInput);
   fTrackDiffusedMinuitHelper->Release(fIndependentVariable);
   fTrackDiffusedMinuitHelper->Release(fIndependentVariable+3);
   fTrackDiffusedMinuitHelper->SetParameters(x0,y0,z0,vx,vy,vz,range);
   // fix origin of independent variable
   fTrackDiffusedMinuitHelper->FixParameter(fIndependentVariable);
   fTrackDiffusedMinuitHelper->FixParameter(fIndependentVariable+3);
   // fix parameter for y direction since y direction can be estimated by using least square
   fTrackDiffusedMinuitHelper->FixParameter(1);
   fTrackDiffusedMinuitHelper->FixParameter(4);
   if (fInitialRange > 0) {
      fTrackDiffusedMinuitHelper->FixParameter(6);
   }
   // minimize
#if 0   
   Double_t tmp[2] = {1000,3};
   Int_t err;
   fTrackDiffusedMinuitHelper->mnexcm("SEEK",tmp,2,err);
#endif   
//
   fTrackDiffusedMinuitHelper->Migrad();
//   fTrackDiffusedMinuitHelper->CalcResidual(y0,z0,xend,xend*vy,xend*vz);
   
   // get result
   //fTrackDiffusedMinuitHelper->GetParameters(y0,z0,range,vy,vz);

#endif
   //////////////////////////////////////////////////
   // prepare and draw resut
   //////////////////////////////////////////////////
   //printf("y0 = %f, z0 = %f, range = %f, vy = %f, vz = %f\n",y0,z0,range,vy,vz);
   if (fVerboseLevel >2) {
      printf("Z0: %7.3f => %7.3f\n",px[2],min.X()[2]);
      printf("VZ: %7.3f => %7.3f\n",va[2],min.X()[5]);
      printf("R : %7.3f => %7.3f\n",range,min.X()[6]);
   }


//   TCatTrackResult *result = static_cast<TCatTrackResult*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   TCatTpcTrack *result = static_cast<TCatTpcTrack*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   result->Init();
   input_track->Copy(*result);   
   TVector3 startPoint(min.X()[0],min.X()[1],min.X()[2]);
   TVector3 endPoint = min.X()[6] * TVector3(min.X()[3],min.X()[4],min.X()[5]).Unit() + startPoint;
   result->SetResults(hits,startPoint,endPoint,&fChargeResponseHelper);
   result->SetChi2(fFunctionChargeResidual.DoEval(min.X()));
   result->SetStatus(min.Status());
   result->SetEDM(min.Edm());
   double chi2  = 0;
   for (Int_t i=0; i<hits.size();i++) {
      const TCatTrackResultPulse *out = (result->GetHits()[i]);
      double diff = 0.;
      double qcalc = fFunctionChargeResidual.GetCharge(hits[i]->GetID());
//      hits[i]->Copy(*out);
//      out->SetEnergyDeposit(qcalc);
      diff = (hits[i]->GetCharge() - qcalc) / sqrt(qcalc + 0.000000001);
      chi2 += diff * diff;
      if (fVerboseLevel > 2) {
         printf("id = %3d c = %10f e = %10f eini = %10f L = %10.5f R = %10.5f dEdX = %10.5f\n",hits[i]->GetID(),hits[i]->GetCharge(),
                qcalc,einit[i],out->GetTrackLength(),out->GetRange(),out->GetCharge()/out->GetTrackLength());
      }
   }
   if (fVerboseLevel > 2) {
      printf("chi2 = %10f %10f\n",chi2, chi2init);
      printf("Niterations = %u\n",min.NIterations());
   }
#if 0
   for (Int_t i=0; i<400; i++) {
      double c = fFunctionChargeResidual.GetCharge(i);
      if (c > 1e-10) printf("c[%3d] = %15f\n",i,c);
   }
#endif   
//   fTrackDiffusedMinuitHelper->GetTrackResult(result);
#endif   
}
  
void TCatTrackingWithDiffusedChargeProcessor::ReconstructTrack(const TCatTpcTrack* input_track)
{
   TCatTpcTrack *output = static_cast<TCatTpcTrack*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   const Int_t vIdx = fIndependentVariable;
   Double_t px[3], va[3];
   TVector3 start = input_track->GetStartPoint();
   TVector3 end   = input_track->GetEndPoint();
   TVector3 direction = input_track->GetDirection();
   std::vector<TCatPulseShape*> hits;
   for (std::size_t i = 0, n = input_track->GetHits().size(); i < n; ++i) {
      hits.push_back(input_track->GetHits()[i]);
   }

   // initialize track parameters
   if (TMath::Abs(fFixedOrigin - start[vIdx]) > TMath::Abs(fFixedOrigin - end[vIdx])) {
      TVector3 tmp = start;
      start = end;
      end = tmp;
      direction = end - start;
   } 
   start = end - (end[vIdx] - fFixedOrigin) / direction[vIdx] * direction;

   for (Int_t i=0; i<3; ++i) {
      px[i] = start[i];
      va[i] = direction[i]/TMath::Abs(direction[vIdx]);
   }

   Double_t range = TMath::Abs(fInitialRange);
   if (range < TMath::Limits<Double_t>::Epsilon()) {
      range = (end-start).Mag();
   }
//   Double_t rangeUnit = 10*TArtSystemOfUnit::m;
   Double_t rangeUnit = TArtSystemOfUnit::mm;
   fFunctionChargeResidual.SetHits(hits);
   fFunctionChargeResidual.SetRangeUnit(rangeUnit);
   ROOT::Minuit2::Minuit2Minimizer min(fEMinuitMinType);
   fFunctionChargeResidual.SetUseTotalCharge(false);
   min.SetFunction(fFunctionChargeResidual);
   min.SetVariable(0,"x0",px[0],7);
   min.SetVariable(1,"y0",px[1],1);
   min.SetVariable(2,"z0",px[2],7.);
   min.SetVariable(3,"vx",va[0],0.11);
   min.SetVariable(4,"vy",va[1],0.01);
   min.SetVariable(5,"vz",va[2],0.1);
   min.SetVariable(6,"R",range/rangeUnit,range/rangeUnit*0.5);
//   min.SetVariable(6,"R",range/rangeUnit,0.1);


#if 0
   printf("**************************************************\n");
   printf("init: x0 = %f, y0 = %f, z0 = %f, vx = %f, vy = %f, vz = %f,range = %f\n",          min.X()[0],min.X()[1],min.X()[2],min.X()[3],min.X()[4],min.X()[5],min.X()[6]);

   printf("**********************************************************************\n");
   printf("Initial chi2 = %f\n",fFunctionChargeResidual.DoEval(min.X()));
   printf("**********************************************************************\n");
#endif   
//   fFunctionChargeResidual.SetVerboseLevel(2);


   if (!fDoMeshSearch) {
      // find proper range
      if (0 && fInitialRange <= 0) {
         fFunctionChargeResidual.SetUseTotalCharge(true);
         min.SetFunction(fFunctionChargeResidual);
         min.SetPrintLevel(0);
         for (Int_t i = 0; i < 6; ++i) {
            min.FixVariable(i);
         }
         min.Minimize();
         for (Int_t i = 0; i < 6; ++i) {
            min.ReleaseVariable(i);
         }
      }
      
//   printf("range : x0 = %f, y0 = %f, z0 = %f, vx = %f, vy = %f, vz = %f,range = %f\n",          min.X()[0],min.X()[1],min.X()[2],min.X()[3],min.X()[4],min.X()[5],min.X()[6]);
      
      fFunctionChargeResidual.SetUseTotalCharge(true);
      fFunctionChargeResidual.SetVerboseLevel(0);
      min.SetFunction(fFunctionChargeResidual);
      min.FixVariable(fIndependentVariable);
      min.FixVariable(fIndependentVariable+3);
      min.FixVariable(1);
      min.FixVariable(4);
      if (fInitialRange > 0) {
         min.FixVariable(6);
      }
//      min.SetMaxFunctionCalls(100000000);
//      min.SetMaxIterations(1000000);
//      min.SetTolerance(0.);
//      min.SetStrategy(1);
//      min.SetPrecision(1e-8);
      min.SetPrintLevel(0);
      if (!TMath::IsNaN(fOffset)) {
         Int_t idx = fIndependentVariable == 0 ? 2 : 0;
         min.SetVariableValue(idx,fOffset);
         min.FixVariable(idx);
      }
//      min.Minimize();
      fFunctionChargeResidual.SetUseTotalCharge(false);
   Int_t savedLevel = gErrorIgnoreLevel;
   
   if (fVerboseLevel == 0 ) gErrorIgnoreLevel = 1001;
      min.Minimize();
   gErrorIgnoreLevel = savedLevel;
//      min.Minimize();
#if 0      
      printf("**************************************************\n");
      printf("init: x0 = %f, y0 = %f, z0 = %f, vx = %f, vy = %f, vz = %f,range = %f\n",          min.X()[0],min.X()[1],min.X()[2],min.X()[3],min.X()[4],min.X()[5],min.X()[6]);
      
      printf("**********************************************************************\n");
      printf("Initial chi2 = %f\n",fFunctionChargeResidual.DoEval(min.X()));
      printf("**********************************************************************\n");
      
      
#endif      
//      min.PrintResults();
   } else {
      // mesh search
      const Int_t varIdx = (vIdx == 0) ? 2 : 0;
      const Int_t nR = fMeshDim[0];
      const Int_t n0 = fMeshDim[1];
      const Int_t nV = fMeshDim[2];
      const Int_t numMeshTotal = nR * n0 * nV;
      Double_t sR = fMeshStep[0];
      Double_t s0 = fMeshStep[1];
      Double_t sV = fMeshStep[2];
      Double_t min_chi2 = TMath::Limits<Double_t>::Max();
      //    Double_t xorg[] = { px[0], px[1], px[2], va[0], va[1], va[2], range};
      
      Double_t xorg[] = { min.X()[0],min.X()[1],min.X()[2],
                          min.X()[3],min.X()[4],min.X()[5],min.X()[6] };
      Double_t mag = TMath::Sqrt(xorg[3]*xorg[3] + xorg[4]*xorg[4] + xorg[5]*xorg[5]);
      xorg[3] /= mag;
      xorg[4] /= mag;
      xorg[5] /= mag;
      std::vector<Double_t> chi2val(numMeshTotal);
      std::vector<Double_t> val0(numMeshTotal);
      std::vector<Double_t> valV(numMeshTotal);
      std::vector<Double_t> valR(numMeshTotal);
      if (fEventDisplayHelper.Displays()) {
         fHists[0]->GetXaxis()->Set(n0,xorg[varIdx]+s0*(0-TMath::Floor(n0/2.)),xorg[varIdx]+s0*(TMath::Floor(n0/2.)));
         fHists[0]->GetYaxis()->Set(nV,xorg[varIdx+3]+sV*(0-TMath::Floor(nV/2.)),xorg[varIdx+3]+sV*(TMath::Floor(nV/2.)));
      }


      for (Int_t iR = 0; iR < nR; ++iR) {
         Double_t xr = TMath::Tan(gRandom->Uniform(-TMath::Pi()/2.,TMath::Pi()/2.));
         xr = (iR - TMath::Floor(nR/2.));
         for (Int_t i0 = 0; i0 < n0; ++i0) {
            Double_t x0 = TMath::Tan(gRandom->Uniform(-TMath::Pi()/2.,TMath::Pi()/2.));
            x0 = i0 - TMath::Floor(n0/2.);
            for (Int_t iV = 0; iV < nV; ++iV) {
               Double_t xv = TMath::Tan(gRandom->Uniform(-TMath::Pi()/2.,TMath::Pi()/2.));
               xv = iV - TMath::Floor(nV/2.);

               Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                                  xorg[3],xorg[4],xorg[5],xorg[6]};
               xnew[6]    += xr * sR;
               xnew[varIdx] += x0 * s0;
               xnew[varIdx+3] += xv * sV;
               xnew[6]/=rangeUnit;
               
               Int_t idx = (iR *  n0 + i0) * nV + iV;
               fFunctions[idx].SetHits(hits);
               fFunctions[idx].SetRangeUnit(rangeUnit);
               Double_t chi2 = fFunctions[idx].DoEval(xnew);
               chi2val[idx] = chi2;
               val0[idx] = xnew[varIdx];
               valV[idx] = xnew[varIdx + 3];
               valR[idx] = xnew[6];
//               printf("chi2 = %10.5f, R = %f, z0 = %f, vz = %f\n",chi2,valR[idx],val0[idx],valV[idx]);
               if (fEventDisplayHelper.Displays()) {
                  fHists[0]->SetBinContent(i0+1,iV+1,chi2);
               }
            }
         }
      }
      std::vector<Double_t>::iterator it = std::min_element(chi2val.begin(),chi2val.end());
      Int_t idx = std::distance(chi2val.begin(),it);
      min_chi2 = *it;
      px[varIdx] = val0[idx];
      va[varIdx] = valV[idx];
      range    = valR[idx];
      Double_t xnew[] = {xorg[0],xorg[1],xorg[2],
                         xorg[3],xorg[4],xorg[5],xorg[6]};
      xnew[varIdx+3] = va[varIdx];
      min.SetFunction(fFunctionChargeResidual);
      min.SetVariableValue(varIdx,px[varIdx]);
      min.SetVariableValue(3,xnew[3]);
      min.SetVariableValue(4,xnew[4]);
      min.SetVariableValue(5,xnew[5]);
      min.SetVariableValue(6,range);
      if (fVerboseLevel>0) {
         printf("*** chi2 = %10.5f, R = %f, z0 = %f (%f), vz = %f (%f) mag = %f\n",min_chi2,range,px[varIdx],xorg[varIdx],va[varIdx],xorg[varIdx+3],mag);
      }
      if (fEventDisplayHelper.Displays()) {
         fEventDisplayHelper.GetMainPad()->cd();
         fHists[0]->SetXTitle("offset");
         fHists[0]->SetYTitle("slope");
         fHists[0]->Draw("colz");
//      canvas->Update();
//      canvas->Modified();
         fEventDisplayHelper.Process();
      }
   }

         
         
//   min.PrintResults();

   TVector3 startPoint(min.X()[0],min.X()[1],min.X()[2]);
   TVector3 endPoint = min.X()[6] * rangeUnit * TVector3(min.X()[3],min.X()[4],min.X()[5]).Unit() + startPoint;
   input_track->Copy(*output);
   output->Validate();
   output->Init();
   output->SetResults(hits,startPoint,endPoint,&fChargeResponseHelper);
   output->SetChi2(fFunctionChargeResidual.DoEval(min.X()));
   output->SetStatus(min.Status());
   output->SetEDM(min.Edm());
   if (fVerboseLevel > 1) {
      printf("**********************************************************************\n");
      printf("last : chi2 %10.3f (%10.3f) x0 = %f, y0 = %f, z0 = %f, vx = %f, vy = %f, vz = %f,range = %f\n",
             output->GetChi2(),output->GetChi2()/output->GetHits().size(),
             min.X()[0],min.X()[1],min.X()[2],min.X()[3],min.X()[4],min.X()[5],min.X()[6]);
      printf("**********************************************************************\n");
   }
   TH2F* chi2map = NULL;
//\   if (fEventDisplayHelper.Displays()
//\       && (chi2map = dynamic_cast<TH2F*>(fHists[0])) != NULL) {
//\      const Double_t x[7] = {
//\         startPoint.X(),startPoint.Y(),startPoint.Z(),
//\         endPoint.X() - startPoint.X(),endPoint.Y() - startPoint.Y(),
//\         endPoint.Z() - startPoint.Z(), (endPoint - startPoint).Mag() } ;
//\
//\      const Int_t n1 = 51;
//\      const Int_t n2 = 51;
//\      const Double_t s1 = 0.1;
//\      const Double_t s2 = 0.1;
//\      const Double_t min1 = x[2] - (n1-1)/2 * s1;
//\      const Double_t min2 = x[5] - (n2-1)/2 * s2; 
//\      const Double_t max1 = min1 + (n1-1) * s1;
//\      const Double_t max2 = min2 + (n2-1) * s2;
//\      chi2map->GetXaxis()->Set(n1,min1-s1/2.,max1+s1/2.);
//\      chi2map->GetYaxis()->Set(n2,min2-s2/2.,max2+s2/2.);
//\      
//\      
//\      for (Int_t i1 = 0; i1 < n1; i1++) {
//\         for (Int_t i2 = 0; i2 < n2; i2++) {
//\            Double_t z0 = min1 + i1 * s1;
//\            Double_t vz = min2 + i2 * s2;
//\            Double_t xnew[7] = { x[0], x[1], z0,
//\                                 x[3], x[4], vz,
//\                                 x[6] };
//\            chi2map->Fill(z0,vz,fFunctionChargeResidual.DoEval(xnew));
//\         }
//\      }
//\      fEventDisplayHelper.Process();
//\   }
   
}
   
