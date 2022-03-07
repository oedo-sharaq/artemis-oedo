/**
 * @file   TRangeTableHelper.cc
 * @brief  helper for range table
 *
 * @date   Created       : 2016-07-21 06:39:06 JST
 *         Last Modified : 2018-08-28 10:57:05 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#include "TRangeTableHelper.h"
#include <TProcessor.h>
#include <TGraph.h>
#include <TArtSystemOfUnit.h>
#include <TSpline.h>

using art::TRangeTableHelper;

ClassImp(TRangeTableHelper)

TRangeTableHelper::TRangeTableHelper()
: TNamed(), fDE2R(NULL), fR2DE(NULL), fR2E(NULL), fE2R(NULL)
{
   fRangeStep = TArtSystemOfUnit::um;
   fTKECutoff = 0;
}

TRangeTableHelper::TRangeTableHelper(const char *name, const char *title)
   : TNamed(name,title), fDE2R(NULL), fR2DE(NULL), fR2E(NULL), fE2R(NULL)
{
}

TRangeTableHelper::~TRangeTableHelper()
{
}

TRangeTableHelper::TRangeTableHelper(const TRangeTableHelper& rhs)
{
}

TRangeTableHelper& TRangeTableHelper::operator=(const TRangeTableHelper& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TRangeTableHelper::Init(TEventCollection *col)
{
   fDE2R = new TGraph(fFileName,"%*lg %lg %*lg %lg");
   fR2DE = new TGraph(fDE2R->GetN(),fDE2R->GetY(),fDE2R->GetX());
   fE2R  = new TGraph(fFileName,"%lg %*lg %*lg %lg");
   fR2E  = new TGraph(fE2R->GetN(),fE2R->GetY(),fE2R->GetX());

   fSpDE2R = new TSpline3("spDE2R",fDE2R->GetX(),fDE2R->GetY(),fDE2R->GetN());
   fSpE2R = new TSpline3("spDE2R",fE2R->GetX(),fE2R->GetY(),fE2R->GetN());
   fSpR2E = new TSpline3("spDE2R",fR2E->GetX(),fR2E->GetY(),fR2E->GetN());
   fSpR2DE = new TSpline3("spDE2R",fR2DE->GetX(),fR2DE->GetY(),fR2DE->GetN());
   
   if (fR2E && fE2R->GetN() > 0) {
      printf("fE2R->GetN() = %d\n",fE2R->GetN());
      // table of range to energy
      Int_t np = fR2E->GetN();
      Double_t *ranges = fR2E->GetX();
      Double_t *tkes = fR2E->GetY();
      Double_t *des = fR2DE->GetY();
      fTKEMin = tkes[0];
      fTKEMax = tkes[np -1];
      fRangeMin = ranges[0];
      fRangeMax = ranges[np-1];
      if (fTKECutoff > 0) {
//         Double_t maxRange = fE2R->Eval(fTKECutoff,0,"S");
         Double_t maxRange = fSpE2R->Eval(fTKECutoff);
         
         if (fRangeMax > maxRange) {
            printf("max range = %f <= %f by TKEcut = %f\n",maxRange,fRangeMax,fTKECutoff);
            fRangeMax = maxRange;
//            fTKEMax = fR2E->Eval(maxRange);
            fTKEMax = fSpR2E->Eval(maxRange);
         }
      }
      np = TMath::FloorNint(fRangeMax/fRangeStep);
      Info("Init","Prepare range table with %d points",np);
      fRanges.resize(np);
      fTKEs.resize(np);
      fDEs.resize(np);
      fRangeMaxIdx = np - 2; // in order to calculate the extrapolation
      for (Int_t i = 0; i < np; ++i) {
         fRanges[i] = (i + 0.5) * fRangeStep;
//         fTKEs[i] = fR2E->Eval(fRanges[i],0,"S");
//         fDEs[i] = fR2DE->Eval(fRanges[i],0,"S");
         fTKEs[i] = fSpR2E->Eval(fRanges[i]);
         fDEs[i] = fSpR2DE->Eval(fRanges[i]);
      }
      Info("Init","R2E is available");
   }
   if (col) {
      col->AddInfo(fRangeTableName,this);
   }
}

void TRangeTableHelper::Register(TProcessor *proc)
{
   proc->RegisterProcessorParameter("RangeTableFile","Name of range table file",fFileName,TString("path/to/file"));
   proc->RegisterProcessorParameter("RangeTable","name of range table",fRangeTableName,TString("rangeTable"));
   proc->RegisterProcessorParameter("TKECutoff","cut off energy for the tabulation",fTKECutoff,10.*TArtSystemOfUnit::MeV);
   proc->RegisterProcessorParameter("RangeStep","range step for making table",fRangeStep,1 * TArtSystemOfUnit::um);
}

