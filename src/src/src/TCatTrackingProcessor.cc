/**
 * @file   TCatTrackingProcessor.cc
 * @brief  tracking processor for CAT
 *
 * @date   Created       : 2014-12-02 09:29:35 JST
 *         Last Modified : 2018-02-04 13:11:09 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2014 Shinsuke OTA
 */

#include "TCatTrackingProcessor.h"
#include <TClonesArray.h>
#include <TSimpleData.h>
#include <TCatReadoutPadArray.h>
#include <TCatReadoutPad.h>
#include "TCatTrackMinuit.h"
#include "TCatTrackDiffusedMinuit.h"
#include <TCatPulseShape.h>
#include <TCatTrackResultPulse.h>
#include <TArtParticle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TLine.h>
#include <TVector3.h>
#include <TObjArray.h>
#include <unistd.h>
#include <vector>
#include <TArtSystemOfUnit.h>
#include <TEventHeader.h>
#include <TText.h>
#include <TDirectory.h>
#include <TMatrixDSym.h>

using art::TCatTrackingProcessor;

ClassImp(TCatTrackingProcessor)

TCatTrackingProcessor::TCatTrackingProcessor()
: fInputColName(""),fInputArray(NULL),fReadoutPadName(""),fPadArray(NULL), fValidHits(NULL),
   fRangeTableFile(""),fRangeTableFormat(""),fRangeTable(NULL),
   fHistPad(NULL), fCheckCanvas(NULL),fGlobalEnergyCorrection(1.),fDriftVelocity(1),
   fWorkFunction(37), fDrawFitResultFlag(kFALSE), fSaveFigFlag(kFALSE), fWaitTimeForFitResult(100000),
   fFunXY(NULL),fFunXZ(NULL)
{
   fTrackStart = NULL;
   fTrackEnd = NULL;
   fBeamMomentum = NULL;
   fBeamPosition = NULL;
   RegisterInputCollection("InputCollection","pulse shapes involved in a track",fInputColName,TString("athits"),
                           &fInputArray,TClonesArray::Class_Name(),art::TCatPulseShape::Class_Name());
   RegisterInputCollection("BeamMomentum","beam momentum",fNameBeamMomentum,TString("beamMomentum"),
                           &fBeamMomentum,TClonesArray::Class_Name(),TArtParticle::Class_Name());
   RegisterInputCollection("BeamPosition","beam momentum",fNameBeamPosition,TString("beamPosition"),
                           &fBeamPosition,TClonesArray::Class_Name(),TVector3::Class_Name());
   
   RegisterOutputCollection("OutputCollection","Output array",fOutputColName,TString("track"),
                           &fOutputArray,TClonesArray::Class_Name(),TArtParticle::Class_Name());
   RegisterOutputCollection("ResultHitsCollection","Output array",fResultHitsName,TString("resulthits"),
                            &fResultHitsArray,TClonesArray::Class_Name(),art::TCatTrackResultPulse::Class_Name());
   RegisterOutputCollection("FitResult","fit result",fFitResultName,TString("fitresults"),
                            &fFitResult,TClonesArray::Class_Name(),TSimpleData::Class_Name());
   RegisterOutputCollection("Ex","excitation energy",fNameEx,TString("Ex"),
                            &fEx,TSimpleData::Class_Name());
   RegisterOutputCollection("ThetaCM","Scattering angle",fNameThetaCM,TString("ThetaCM"),
                            &fThetaCM,TSimpleData::Class_Name());
   RegisterOutputCollection("TrackStart","track start point",fNameTrackStart,TString("trackStart"),
                            &fTrackStart,TVector3::Class_Name());
   RegisterOutputCollection("TrackEnd","track end point",fNameTrackEnd,TString("trackEnd"),
                            &fTrackEnd,TVector3::Class_Name());
   RegisterProcessorParameter("RangeTableFile","File name of range talble.",
                              fRangeTableFile,TString("/path/to/rangetable"));
   RegisterProcessorParameter("RangeTableFormat","Format is assumed to be '%lg %*lg %lg' with energy(MeV), dE/dX and range (mm)",
                              fRangeTableFormat,TString("%lg %*lg %lg"));
   RegisterProcessorParameter("DriftVelocity","Constant drift velocity (cm/us). To be variable in user information",
                              fDriftVelocity,(Float_t)1.);
   RegisterProcessorParameter("WorkFunction","Work function (eV)",
                              fWorkFunction,(Float_t)37.);
   RegisterOptionalParameter("GlobalEnergyCorrection","[opt] Rough energy calibration using common coefficient (default = 1)",
                             fGlobalEnergyCorrection,(Float_t)1.);
   RegisterOptionalParameter("DrawFitResultFlag","draw fit result when flag is 1 (default : 0)",
                             fDrawFitResultFlag,kTRUE);
   RegisterOptionalParameter("SaveFigFlag","save drawn figure when 1 (default : 0)",
                             fSaveFigFlag,kTRUE);
   RegisterOptionalParameter("SaveFigDir","Directory for saving figure",
                             fSaveFigDir,TString("figs/tracking"));
   RegisterOptionalParameter("WaitTimeForFitResult","time period (ms) until next event is drawn",
                             fWaitTimeForFitResult,100000);
   RegisterInputCollection("EventHeader","name of event header (default : eventheader)",fNameEventHeader,TString("eventheader"),
                             &fEventHeader,art::TEventHeader::Class_Name());
   RegisterInputInfo("ReadoutPad","Name of readout pad",fReadoutPadName,TString("readoutPad"),&fPadArray,
                     art::TCatReadoutPadArray::Class_Name());
   RegisterInputInfo("RunHeadersName","run headers",fNameRunHeaders,TString("runheader"),&fRunHeaders,"TList");
   RegisterProcessorParameter("TableLookupFlag","flag to use TCatTrackMinuit (flag = 0, default) or TCatTrackDiffusedMinuit (flag = 1)",
                              fTableLookupFlag,kFALSE);
   RegisterProcessorParameter("ChargeDistributionTable","Name of root file containing the histgram",fChargeDistribusionTable,TString(""));
   RegisterProcessorParameter("Attachment","attachment coeffcient (cm^{-1})",
                              fAttachment,(Float_t)0.1);
   // @todo define the coordinate system
   RegisterOptionalParameter("FieldCageOffset","offset of the bottome of the field cage to the beamline in mm (default -50mm)",
                             fFieldCageOffset,(Float_t)-50.);
   
      
   fValidHits = new TObjArray;
}
TCatTrackingProcessor::~TCatTrackingProcessor()
{
   if (fHistPad) {
      delete fHistPad;
      fHistPad = NULL;
   }

   if (fCheckCanvas) {
      delete fCheckCanvas;
      fCheckCanvas = NULL;
   }
   if (fFunXY) {
      delete fFunXY;
      fFunXY = NULL;
   }
   if (fFunXZ) {
      delete fFunXZ;
      fFunXZ = NULL;
   }

   if (fValidHits) {
      fValidHits->Clear();
      delete fValidHits;
      fValidHits = NULL;
   }
      
}

TCatTrackingProcessor::TCatTrackingProcessor(const TCatTrackingProcessor& rhs)
{
}

TCatTrackingProcessor& TCatTrackingProcessor::operator=(const TCatTrackingProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TCatTrackingProcessor::Init(TEventCollection*)
{

   if (!fPadArray) {
      SetStateError("Pad configuration is not initialized");
      return;
   }

   // initialization of range table
   fRangeTable = new TGraph(fRangeTableFile,fRangeTableFormat);
   TGraph *dE2Range = new TGraph("data/DeuteronDeuteron0.4atm.txt.out","%*lg %lg %*lg %lg");
//   Int_t n = dE2Range->GetN();
   Double_t *x = dE2Range->GetX();
   Double_t *y = dE2Range->GetY();
   fRange2EnergyLoss = new TGraph(dE2Range->GetN(),y,x);
   if (!fRangeTable || fRangeTable->GetN() == 0) {
      SetStateError(TString::Format("Range table is not prepared with the file '%s' ('%s')",
                                    fRangeTableFile.Data(),fRangeTableFormat.Data()));
      return;
   }
   fRange2EnergyTable = new TGraph(fRangeTable->GetN());
   for (Int_t i=0; i!=fRangeTable->GetN(); i++) {
      fRange2EnergyTable->SetPoint(i,fRangeTable->GetY()[i],fRangeTable->GetX()[i]);
   }
   

   if (1) {
      // create histgrams for checking the result
      fHistPad = (*fPadArray)->CreateHist("hPad","hPad",-50.,50.,-50.,50.);
      fCheckCanvas = new TCanvas;
      fHistPad->Draw();
      fHistPad->SetMinimum(1e-5);
   }

   // prepare helper
   fFunXY = new TF1("XZ","pol1",-50.,50.);
   fFunXZ = new TF1("XY","pol1",-50.,50.);

   if (fTableLookupFlag) {
      fTrackMinuit = new TCatTrackDiffusedMinuit;
//      ((TCatTrackDiffusedMinuit*)fTrackMinuit)->RegisterHistogram(fChargeDistribusionTable);
      printf("fRange2EnergyLoss %p\n",fRange2EnergyLoss);
      ((TCatTrackDiffusedMinuit*)fTrackMinuit)->LoadResponseTable(fChargeDistribusionTable);
      ((TCatTrackDiffusedMinuit*)fTrackMinuit)->RegisterRange2EnergyLoss(fRange2EnergyLoss);
      ((TCatTrackDiffusedMinuit*)fTrackMinuit)->SetAttachment(fAttachment);
      ((TCatTrackDiffusedMinuit*)fTrackMinuit)->SetFieldCageOffset(fFieldCageOffset);
      
   } else {
      fTrackMinuit = new TCatTrackMinuit;
   }
   fTrackMinuit->SetReadoutPadArray(*fPadArray);
   // range table can be a TGraph
   fTrackMinuit->SetRangeTable(fRangeTable);
   fTrackMinuit->SetDriftVelocity(fDriftVelocity);
   fTrackMinuit->SetWorkFunction(fWorkFunction);

//   fFitResults->ResizeTo(1);
}


void TCatTrackingProcessor::Process()
{
   static TGraph vertexes;
   static TGraph grend;
   static TLine  trackline;
   static TLine  trackline_init;
   Double_t p0, p1; // z = p0 + p1 * x
   Double_t z0 = 0;
   Double_t vz;
   Double_t y0;
   Double_t vy;
   Double_t vx;
//   const Double_t EPS = TMath::Limits<Double_t>::Epsilon();
   std::vector<Double_t> e, y;
   fValidHits->Clear("C");
   fOutputArray->Clear("C");
   fResultHitsArray->Clear("C");
   fFitResult->Clear("C");
   fHistPad->ClearBinContents();
   fEx->Invalidate();
   fEx->SetValue(TMath::QuietNaN());
   fThetaCM->Invalidate();
   fThetaCM->SetValue(TMath::QuietNaN());
   Int_t nHit = (*fInputArray)->GetEntriesFast();
   if (nHit < 5) {
      // printf("nHit < 5\n");
      return;
   }
   TArtParticle *beam = (TArtParticle*) (*fBeamMomentum)->UncheckedAt(0);
   TVector3 *beamPosition = (TVector3*) (*fBeamPosition)->UncheckedAt(0);
   p1 = (beam->Theta()<TMath::Limits<Double_t>::Epsilon()) ? 1e20 : -1./TMath::Tan(beam->Theta());
   p0 = -beamPosition->X() * p1;
   Double_t x0 = (z0-p0)/p1;
   // printf("p0 = %f p1 = %f x0 = %f\n",p0,p1,x0);
   //----------------------------------------------------------------------
   // calculate rough angle and stop position as an initial parameter for minuit
   //----------------------------------------------------------------------
   TCatPulseShape::SetSortType(TCatPulseShape::kID);
   TCatPulseShape::SetSortOrder(TCatPulseShape::kASC);
   (*fInputArray)->Sort();
   //-------
   for (Int_t i=0; i!=nHit; i++) {
      TCatPulseShape *pulse = (TCatPulseShape*)(*fInputArray)->UncheckedAt(i);
      pulse->SetOffset(pulse->GetOffset()*20*TArtSystemOfUnit::ns);
      pulse->SetCharge(pulse->GetCharge() * fGlobalEnergyCorrection);
      // remove validation since this is only for heavy ion case
      // if (abs(pulse->GetX()) < 20) continue;
      fValidHits->Add(pulse);
   }
   if (fValidHits->GetEntriesFast() < 5) return;
   fTrackMinuit->SetLine(p0,p1);
   //----------------------------------------------------------------------
   // set data and initial parameters to minuit routine
   // minuit will be set the direction and stop position
   //----------------------------------------------------------------------
   fTrackMinuit->SetData(fValidHits); // SetData may be called as many as the number of tracks
   fTrackMinuit->GetParameters(y0,z0,vx,vy,vz); // assuming trajectory is nearly parralel to X
//   vy *= vx;
//   vz *= vx;
   trackline_init = TLine(x0,z0,x0+vx,z0+vz);

   //----------------------------------------------------------------------
   // do migrad and get the result of minuit
   //----------------------------------------------------------------------
   if (0) {
      // rough estimation of y0
      fTrackMinuit->GetParameters(y0,z0,vx,vy,vz); // assuming trajectory is nearly parralel to X
      printf("get parameters vx vy vz = (%f %f %f)\n",vx,vy,vz);
      Double_t chi2_init = fTrackMinuit->CalcResidual(y0,z0,vx,vy,vz);
      Double_t chi2_z01 = fTrackMinuit->CalcResidual(y0,z0-5,vx,vy,vz+5);
      Double_t chi2_z02 = fTrackMinuit->CalcResidual(y0,z0+5,vx,vy,vz-5);
      if (chi2_z01 < chi2_init && chi2_z01 < chi2_z02) {
         z0 -= 5;
         vz += 5;
      } else if (chi2_z02 < chi2_init && chi2_z02 < chi2_z01) {
         z0 += 5;
         vz -= 5;
      }
      printf("chi2 %f %f %f\n",chi2_init,chi2_z01,chi2_z02);
      printf("reseting parameters vx vy vz = (%f %f %f)\n",vx,vy,vz);
   }
   fTrackMinuit->SetPrintLevel(1);
//   fTrackMinuit->SetParameters(y0,z0,vx,vy,vz);
   fTrackMinuit->SetParameters(50,z0,vx,vy,vz);
//   fTrackMinuit->SetParameters(50.,-30.,-36.2,0.,37.53);
   fTrackMinuit->SetMaxIterations(1000000);
   Double_t tmp[7];
   Int_t err;
#if 1
   tmp[0] = 1000;
   tmp[1] = 3;
   fTrackMinuit->FixParameter(0);
   fTrackMinuit->FixParameter(3);
   fTrackMinuit->mnexcm("SEEK",tmp,2,err);
   fTrackMinuit->Release(0);
   fTrackMinuit->Release(3);
#endif   
   tmp[0] = 10000;
   fTrackMinuit->mnexcm("MIGRAD",tmp,1,err);
   fTrackMinuit->mnexcm("MINOS",tmp,1,err);
   TMatrixDSym mat(5);
   fTrackMinuit->mnemat(mat.GetMatrixArray(),5);
   mat.Print();
   printf("det = %g\n",mat.Determinant());

//   fTrackMinuit->mnscan();
//   fTrackMinuit->mnmnos();
   

//   Int_t ier;
   fTrackMinuit->GetParameters(y0,z0,vx,vy,vz);
//   Double_t chi2 = fTrackMinuit->CalcResidual(y0,z0,vx,vy,vz,fResultHitsArray);

      
   TSimpleData *chi2out = (TSimpleData*) fFitResult->ConstructedAt(fFitResult->GetEntries());
   TSimpleData *xendout = (TSimpleData*) fFitResult->ConstructedAt(fFitResult->GetEntries());
//   chi2out->SetValue(fTrackMinuit->CalcResidual(y0,z0,vx,vy,vz));
   chi2out->SetValue(fTrackMinuit->CalcResidual(y0,z0,vx,vy,vz,fResultHitsArray));
   xendout->SetValue(vx+x0);
   TVector3 track(vx,vy,vz);
   Double_t energy = fRange2EnergyTable->Eval(track.Mag());
   TArtParticle *p = (TArtParticle*)fOutputArray->ConstructedAt(0);
   p->SetXYZT(vx,vy,vz,energy +1875.613);
   p->SetKineticEnergy(energy,1875.613);
   p->SetAngle(track.Theta(),track.Phi());
   beamPosition->SetY(y0);
   beamPosition->SetZ(z0);
   (fTrackStart)->SetXYZ(x0,y0,z0);
   (fTrackEnd)->SetXYZ(vx+x0,vy+y0,vz+z0);

   TArtParticle target;
   target.SetXYZT(0.,0.,0.,1875.613);

   TLorentzVector cm = (TLorentzVector)(*beam) + (TLorentzVector)target;
   
   TLorentzVector scat;
   scat = cm - *(TLorentzVector*)p;
   scat.Boost(-cm.BoostVector());
   fEx->SetValue(scat.M()-beam->M());
   fThetaCM->SetValue(scat.Theta());
   


// drawing fit result
   if (fDrawFitResultFlag || fSaveFigFlag) {
      fTrackMinuit->GetParameters(y0,z0,vx,vy,vz);
      Int_t n = 10;
      Double_t step = 1.; // ratio;
      fCheckCanvas->Clear();
      fCheckCanvas->Divide(1,2);
#define USE_GR 0
#if USE_GR
      TGraph *gr = new TGraph(2*n+1);
      for (Int_t i = 0; i!=2*n+1; ++i) {
         Double_t vxtmp = vx + step *(i-n);
         Double_t vztmp = vz + step *(i-n);
         gr->SetPoint(i,vxtmp,fTrackMinuit->CalcResidual(y0,z0,vx,vy,vztmp));
      }
      // TGraph *gr = (TGraph*)fTrackMinuit->Contour(20,3,4);
      if (gr) {
         fCheckCanvas->cd(1);
         gr->Draw("AC*");
      }
#else

      Double_t varx = vx;
      Double_t vary = vz;
      if (gDirectory->Get("chi2map")) {
         gDirectory->Get("chi2map")->Delete();
      }
         
      TH2F *h2 = new TH2F("chi2map","chi2 map",2*n+1,varx - step * n, varx + step * n,
                          2*n+1,vary - step * n, vary + step * n);
      for (Int_t i = 0; i!=2*n+1; ++i) {
         for (Int_t j = 0; j!=2*n+1; ++j) {
            Double_t vxtmp = vx + step *(i-n);
//            Double_t z0tmp = z0 + step *(i-n);
            Double_t vztmp = vz + step *(j-n);
            Double_t ret = fTrackMinuit->CalcResidual(y0,z0,vxtmp,vy,vztmp);
            if (ret < TMath::Limits<Double_t>::Max()) h2->Fill(vxtmp,vztmp,ret);
         }
      }
fCheckCanvas->cd(1)->SetLogz();
      h2->Draw("colz");
#endif
//      fTrackMinuit->mnprin(4,chi2out->GetValue());
//      fTrackMinuit->mnprin(2,chi2out->GetValue());
      Int_t nOutput = fResultHitsArray->GetEntriesFast();
      std::vector<Double_t> xx;
      std::vector<Double_t> yy;
      fTrackMinuit->GetParameters(y0,z0,vx,vy,vz);
      for (Int_t i = 0; i != nOutput; ++i) {
         TCatTrackResultPulse *output = (TCatTrackResultPulse*)fResultHitsArray->UncheckedAt(i); 
         fHistPad->Fill(output->GetX(),output->GetZ(),output->GetCharge());

         Int_t nVertex = output->GetNumVertex();
         for (Int_t j = 0; j != nVertex; ++j) {
            xx.push_back(output->GetVertex(j)->X());
            yy.push_back(output->GetVertex(j)->Z());
         }
      }
      // printf("size of vertex = %d\n",xx.size());
      trackline = TLine(x0,z0,x0+vx,z0+vz);
      grend.SetPoint(0,x0+vx,z0+vz);
      grend.SetMarkerStyle(4);
      
      fFunXZ->SetParameters(z0,vz/vx);
      // printf("%f %f\n",z0,vz);
      fCheckCanvas->cd(2);
      //fCheckCanvas->cd();
      fHistPad->Draw("colz");
      // fFunXZ->Draw("same");
      trackline_init.SetLineColor(kBlack);
      trackline_init.SetLineWidth(3);
      trackline_init.Draw();
      trackline.Draw();
      vertexes.Draw("P*");
      grend.Draw("P");
      fCheckCanvas->Update();
      fCheckCanvas->Modified();
      TObjArray arr;
      TText text;
      if (fSaveFigFlag) {
         arr.Add(text.DrawTextNDC(0.10,0.94,Form("Run: %s%04d",
                                                  (*fEventHeader)->GetRunName().Data(),
                                                  (*fEventHeader)->GetRunNumber())));
         arr.Add(text.DrawTextNDC(0.10,0.91,Form("Evt = %10lld",(*fEventHeader)->GetEventNumber())));
         arr.Add(text.DrawTextNDC(0.10,0.87,Form("TKE = %g theta = %5.2f phi = %5.2f",
                                                  p->TKE(),p->Theta()/TMath::Pi()*180,
                                                  p->Phi()/TMath::Pi()*180)));
                                                  
         fCheckCanvas->SaveAs(TString::Format("%s/%04d_%08lld_%d_%d.png",
                                              fSaveFigDir.Data(),
                                              (*fEventHeader)->GetRunNumber(),(*fEventHeader)->GetEventNumber(),
                                              Int_t(TMath::Ceil(p->TKE()/TArtSystemOfUnit::keV)),
                                              Int_t(TMath::Ceil(p->Theta()/TMath::Pi()*180.))
                                 )

            );
      }
      if (fDrawFitResultFlag) {
         usleep(fWaitTimeForFitResult);
      }
      arr.Delete();
#if USE_GR      
      if (gr) delete gr;
#else
//      if (h2) delete h2;
#endif      
   }
   
   
#if 1
   printf("Ex = %f, Theta = %f\n",scat.M() - beam->M(),scat.Theta()/3.14*180);
   printf("chi2 = %g, y0 = %f, z0 = %f, vx = %f, vy = %f, vz = %f\n",chi2out->GetValue(),y0,z0,vx,vy,vz);
#endif   

#if 0
//   Double_t xend = t;
   // checking the result
   TVector3 va(vx,vy,vz); // direction
   TVector3 a1(x0,y0,z0);
   TVector3 a2 = a1 + va;
   TObjArray *fHits = *fInputArray;
   Int_t    nHits = fHits->GetEntriesFast();
   std::vector<Double_t> xx, yy;
   for (Int_t iHit = 0; iHit != nHits; ++iHit) {
      TCatPulseShape *pulse = (TCatPulseShape*) fHits->UncheckedAt(iHit);
      TCatPulseShape *result = (TCatPulseShape*) fResultHitsArray->ConstructedAt(iHit);
      pulse->Copy(*result);
      TCatReadoutPad *pad = (TCatReadoutPad*) (*fPadArray)->At(pulse->GetID());
      if (!pad) {
         Error("Eval","pad %p for pad id = %d\n",pad,pulse->GetID());
         return;
      }
      Int_t nP = (pad->GetNumPoints() -1);
      Double_t *x = pad->VertexX();
      Double_t *y = pad->VertexY();
      std::vector<Double_t> trackE;
      std::vector<Double_t> trackY;
      Double_t fDriftVelocity = 1. * TArtSystemOfUnit::cm / TArtSystemOfUnit::us;

      for (Int_t iP=0; iP!=nP; iP++) {
         TVector3 b1(x[iP],0,y[iP]);
         TVector3 b2(x[iP+1],0,y[iP+1]);
         TVector3 vb = b2-b1;
         // cross test
         if (!(va.Cross(b1-a1).Y() * va.Cross(b2-a1).Y() < EPS)  || 
             !(vb.Cross(a1-b1).Y() * vb.Cross(a2-b1).Y() < EPS)) {
            // two line segments do not cross each other
            printf("%f %f %f %f\n",va.Cross(b1-a1).Y(),
                   va.Cross(b2-a1).Y(),vb.Cross(a1-b1).Y(),vb.Cross(a2-b1).Y());
            continue;
         }
         // if they cross each other, calculate the coordinate of the crossing point
         Double_t d1 = TMath::Abs(vb.Cross(a1-b1).Y());
         Double_t d2 = TMath::Abs(vb.Cross(a2-b1).Y());
         Double_t t = d1/(d1+d2);
         TVector3 p = a1 + t * va;
         Double_t range = (a2 - p).Mag();
         Double_t e = fRange2EnergyTable->Eval(range);
         Double_t py = p.Y();
         trackE.push_back(e);
         trackY.push_back(py);
         // store crossing point
         xx.push_back(p.X());
         yy.push_back(p.Z());
      }
      TGraph gr(4,x,y);
      Double_t edep = 0;
      Double_t yhit = 0;
      switch (trackE.size()) {
      case 0:
         result->Invalidate();
         break;
      case 1:
         // a1 or a2 exist in this pad
         if (gr.IsInside(a1.X(),a1.Z())) {
            // first point
            edep = fRange2EnergyTable->Eval((a2-a1).Mag()) - trackE[0];
            yhit = TMath::Min(trackY[0],a1.Y());
         } else if (gr.IsInside(a2.X(),a2.Z())) {
            // last point
            edep = trackE[0];
            yhit = TMath::Min(trackY[0],a2.Y());
         } else {
            Error("CalcResidual","NP = 1: Position was not extracted correctly");
            edep = 0;
            yhit = 0;
         }
         result->SetCharge(edep);
         result->SetOffset(yhit/fDriftVelocity);
         break;
      case 2:
         edep = TMath::Abs(trackE[0] - trackE[1]);
         yhit = TMath::Min(trackY[0],trackY[1]);
         result->SetCharge(edep);
         result->SetOffset(yhit/fDriftVelocity);
         break;
      case 3:
         if (TMath::Abs(trackE[0]-trackE[1]) < TMath::Max(TMath::Abs(trackE[0]),TMath::Abs(trackE[1]))*EPS) {
            edep = TMath::Abs(trackE[0] - trackE[2]);
            yhit = TMath::Min(trackY[0],trackY[2]);
         } else if (TMath::Abs(trackE[0]-trackE[2]) < TMath::Max(TMath::Abs(trackE[0]),TMath::Abs(trackE[2]))*EPS) {
            edep = TMath::Abs(trackE[0] - trackE[1]);
            yhit = TMath::Min(trackY[0],trackY[1]);
         } else if (TMath::Abs(trackE[1]-trackE[2]) < TMath::Max(TMath::Abs(trackE[1]),TMath::Abs(trackE[2]))*EPS) {
            edep = TMath::Abs(trackE[0] - trackE[1]);
            yhit = TMath::Min(trackY[0],trackY[1]);
         } else {
            Warning("CaclResidual","Unexpected three crossing points are found");
         }
         result->SetCharge(edep);
         result->SetOffset(yhit/fDriftVelocity);
         break;
      }         
#if 1
      Double_t dEdep = TMath::Sqrt(fWorkFunction * pulse->GetCharge());
      if (trackY.size() >1) {
         printf("id = %d e : (%f %f) y: (%f %f)\n",
                pulse->GetID(),
                edep, pulse->GetCharge(), (trackY.size()>1?TMath::Min(trackY[0],trackY[1]):trackY[0]), pulse->GetOffset()*fDriftVelocity);
         printf("dEdep=%f\n",dEdep );
      }
#endif
   }
   if ((fDrawFitResultFlag || fSaveFigFlag) ) {
      TGraph gr(xx.size(),xx.data(),yy.data());
      
      TLine line(x0,z0,x0+vx,z0+vz);
      TGraph grend(1);
      grend.SetPoint(0,x0+vx,z0+vz);
      grend.SetMarkerStyle(4);
      
      fFunXZ->SetParameters(z0,vz/vx);
      // printf("%f %f\n",z0,vz);
      fCheckCanvas->cd();
      fHistPad->Draw("colz");
      // fFunXZ->Draw("same");
      line.Draw();
      gr.Draw("P*");
      grend.Draw("P");
      fCheckCanvas->Update();
      fCheckCanvas->Modified();
      TObjArray arr;
      TText text;
      if (fSaveFigFlag) {
         arr.Add(text.DrawTextNDC(0.10,0.94,Form("Run: %s%04d",
                                                  (*fEventHeader)->GetRunName().Data(),
                                                  (*fEventHeader)->GetRunNumber())));
         arr.Add(text.DrawTextNDC(0.10,0.91,Form("Evt = %10lld",(*fEventHeader)->GetEventNumber())));
         arr.Add(text.DrawTextNDC(0.10,0.87,Form("TKE = %g theta = %5.2f phi = %5.2f",
                                                  p->TKE(),p->Theta()/TMath::Pi()*180,
                                                  p->Phi()/TMath::Pi()*180)));
                                                  
         fCheckCanvas->SaveAs(TString::Format("%s/%04d_%08lld_%d_%d.png",
                                              fSaveFigDir.Data(),
                                              (*fEventHeader)->GetRunNumber(),(*fEventHeader)->GetEventNumber(),
                                              Int_t(TMath::Ceil(p->TKE()/TArtSystemOfUnit::keV)),
                                              Int_t(TMath::Ceil(p->Theta()/TMath::Pi()*180.))
                                 )

            );
      }
      if (fDrawFitResultFlag) {
         usleep(fWaitTimeForFitResult);
      }
      arr.Delete();
   }
#endif
   printf("------- done -------\n");
}
