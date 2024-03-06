#include "TTinaProcessor2.h"
#include "TTinaData2.h"

#include <algorithm>
#include <numeric>
#include <functional>
#include <TGraphPainter.h>
#include <TGraph.h>
#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>
#include <ITiming.h>
#include "TSRPPACPlaneData.h"
#include "EnergyLoss.h"

using art::TTinaProcessor2;

// for sorting energy deposit keeping ID
struct data_t
{
   int ex_pos;
   Double_t val;
   bool operator<(const data_t &right) const
   {
      return val == right.val ? ex_pos < right.ex_pos : val > right.val;
   }
};

ClassImp(TTinaProcessor2)

    TTinaProcessor2::TTinaProcessor2()
    : fOutput(NULL)
{
   RegisterInputCollection("SiName", "name of input collection for Si",
                           fSiName, TString("tinasi"),
                           &fSi, TClonesArray::Class_Name(), art::ICharge::Class_Name());
   RegisterInputCollection("CsIName", "name of input collection for CsI",
                           fCsIName, TString("tinacsi"),
                           &fCsI, TClonesArray::Class_Name(), art::ICharge::Class_Name());
   RegisterInputCollection("TinaTName", "name of input collection for TinaT",
                           fTinaTName, TString("tinat"),
                           &fTinaT, TClonesArray::Class_Name(), art::ICharge::Class_Name());
   RegisterInputCollection("X1Name", "name of input collection for X1",
                           fX1Name, TString("x1"),
                           &fX1, TClonesArray::Class_Name(), art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("Y1Name", "name of input collection for Y1",
                           fY1Name, TString("y1"),
                           &fY1, TClonesArray::Class_Name(), art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("X2Name", "name of input collection for X2",
                           fX2Name, TString("x2"),
                           &fX2, TClonesArray::Class_Name(), art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("Y2Name", "name of input collection for Y2",
                           fY2Name, TString("y2"),
                           &fY2, TClonesArray::Class_Name(), art::TSRPPACPlaneData::Class_Name());
   RegisterOutputCollection("OutputName", "name of output collection",
                            fOutputName, TString("tina"),
                            &fOutput, TClonesArray::Class_Name(), art::TTinaData2::Class_Name());
}

TTinaProcessor2::~TTinaProcessor2()
{
}

Double_t GetEremain2(Double_t track, Double_t DeltaE)
{ // mm, MeV
   EnergyLoss *p_in_Si = new EnergyLoss();
   p_in_Si->ReadLISEdEdx("/home/sh19post/art_analysis/user/li/EnergyLossTable/p_in_Si.lise", 1.0, 2.3212, 4);
   std::vector<Double_t> Eloss{};
   std::vector<Double_t> Eremain{};
   Double_t Eout;        // Eremain
   Double_t Ein;         // incident energy MeV
   Double_t Estep = 0.2; // MeV
   Double_t Emin = 0, Emax = 50;
   Emin = p_in_Si->AddBack(0, track);
   if (DeltaE >= Emin || Emin >= Emax)
   {
      return -100;
   }
   else
   {
      for (int i = 0; i <= (Emax - Emin) / Estep; i++)
      {
         Ein = Emin + i * Estep;
         Eremain.push_back(p_in_Si->CalcRemainder(Ein, track)); // MeV  mm
         Eloss.push_back(Ein - Eremain.at(i));
      }
      TGraph *g = new TGraph(Eloss.size(), &Eloss[0], &Eremain[0]);
      Eout = g->Eval(DeltaE);
      //  std::cout << "returned: " << Eout << " ";
      return Eout;
   }
}

void TTinaProcessor2::Process()
{
   // ch    strip   theta   coverage
   // 15	0	150.6	3.4
   // 13	1	147.1	3.5
   // 11	2	143.6	3.6
   // 9	3	140	3.5
   // 14	4	136.5	3.6
   // 12	5	133	3.5
   // 10	6	129.5	3.4
   // 8	7	126.1	3.4
   // 6	8	122.8	3.2
   // 4	9	119.6	3.2
   // 2	10	116.5	3.0
   // 0	11	113.6	2.8
   // 7	12	110.8	2.7
   // 5	13	108.1	2.6
   // 3	14	105.6	2.5
   // 1	15	103.3	2.2
   //  id-angle conversion tables
   static double thetaconv[] =
       {
           /*     170.8, 169.8, 168.8, 167.8,
           166.7, 165.7, 164.6, 163.5,
           162.3, 161.2, 160.0, 158.9,
           157.7, 156.5, 154.2, 154.0 */
           168.8, 170.8, 164.6, 166.7,
           167.8, 169.8, 163.5, 165.7,
           157.7, 154.2, 162.3, 160.0,
           156.5, 154.0, 161.2, 158.9};

   // according to thetaconv
   static double correctedstripid[] = {
       2, 0, 6, 4, 3, 1, 7, 5,
       12, 14, 8, 10, 13, 15, 9, 11};
   static double thetacoverage[] =
       {
           /*1.0, 1.0, 1.0, 1.0,
           1.0, 1.0, 1.1, 1.1,
           1.1, 1.1, 1.2, 1.2,
           1.2, 1.2, 1.2, 1.2*/
           1.0, 1.0, 1.1, 1.0,
           1.0, 1.0, 1.1, 1.0,
           1.2, 1.2, 1.1, 1.2,
           1.2, 1.2, 1.1, 1.2};
   static double phiconv[] =
       {
           /*75.0, 135.0, 195.0, 255.0, 315.0, 375.0*/
           90.0, 30.0, 330.0, 270.0, 210.0, 150.0};
   // angular coverage tables

   static double phicoverage[] =
       {
           /*60.0, 60.0, 60.0, 60.0, 60.0, 60.0*/
           42.0, 42.0, 42.0, 42.0, 42.0, 42.0};

   fOutput->Clear("C");

   // look for si max
   if ((*fSi)->GetEntriesFast() == 0)
      return;

   //   std::vector<Double_t> siarr(6*16, 0);
   std::vector<data_t> siarr(6 * 16);

   for (int i = 0; i < 96; i++)
   {
      siarr[i].ex_pos = i;
      siarr[i].val = 0.;
   }

   for (Int_t i = 0, n = (*fSi)->GetEntriesFast(); i != n; ++i)
   {
      const Int_t id = dynamic_cast<art::TDataObject *>((*fSi)->At(i))->GetID();
      if (id < 6 * 16)
      {
         const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fSi)->At(i));
         siarr[id].val = ic->GetCharge();
      }
   }
   if (siarr.empty())
      return;

   //   std::vector<Double_t> tinatarr(6, -10000.);
   std::vector<Double_t> tinatarr(6, -10000.);
   for (Int_t i = 0, n = (*fTinaT)->GetEntriesFast(); i != n; ++i)
   {
      const Int_t id = dynamic_cast<art::TDataObject *>((*fTinaT)->At(i))->GetID();
      // if(id < 6){
      if (id < 6)
      {
         const art::ITiming *const it = dynamic_cast<art::ITiming *>((*fTinaT)->At(i));
         tinatarr[id] = it->GetTiming();
      }
   }

   //   std::vector<Double_t>::iterator simaxit = std::max_element(siarr.begin(), siarr.end());
   //   Int_t simaxidx = std::distance(siarr.begin(), simaxit);
   std::sort(siarr.begin(), siarr.end());

   if (siarr[0].ex_pos < 0.5)
      return;

   TTinaData2 *out = static_cast<TTinaData2 *>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   out->SetDeltaE(siarr[0].val);
   out->SetEnergy(siarr[0].val);
   Int_t stripid = siarr[0].ex_pos % 16;
   Int_t detid = siarr[0].ex_pos / 16;
   out->SetTiming(tinatarr[detid]);
   // out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   // out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);
   out->SetDeid(siarr[0].ex_pos);

   Double_t colx = 0.;
   Double_t coly = 0.;
   Double_t colz = 0.;
   Double_t scat = 0;
   const Double_t PI = TMath::Pi();
   // collision point at taraget by tracking from fe12
   if ((*fX1)->GetEntriesFast() == 0)
      return;
   if ((*fY1)->GetEntriesFast() == 0)
      return;
   if ((*fX2)->GetEntriesFast() == 0)
      return;
   if ((*fY2)->GetEntriesFast() == 0)
      return;

   Double_t x1 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX1)->At(0)))->GetPosition();
   Double_t y1 = (dynamic_cast<art::TSRPPACPlaneData *>((*fY1)->At(0)))->GetPosition();
   // Double_t z1 = -1962.;
   Double_t z1 = -2017.; // 55 mm
   Double_t x2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX2)->At(0)))->GetPosition();
   Double_t y2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fY2)->At(0)))->GetPosition();
   // Double_t z2 = -1462;
   Double_t z2 = -1517.; // 55 mm

   Double_t x0, y0, z0; // fe12 chamber center
   x0 = 0.5 * (x1 + x2);
   y0 = 0.5 * (y1 + y2) - 30;
   z0 = -1767.;
   // colx = coly = 0.;
   colx = (-z1 * x2 + z2 * x1) / (z2 - z1);
   coly = (-z1 * (y2 - 30.) + z2 * (y1 - 30.)) / (z2 - z1);
   colz = 0.;
   // scat = acos((z2-z1)/(sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2))))/PI*180.; //beam scattering angle
   out->SetX(colx);
   out->SetY(coly);

   // hit point at YY1, strip pitch 0.5 mm
   Double_t hitx = 0.;
   Double_t hity = 0.;
   Double_t hitz = 0.;

   // 4.0*atan(1.0);
   const Double_t a = 50. * PI / 180.; // YY1 tilt from beam axis
   const Double_t z_90 = 224.39;       // target to YY1 center at r = 90 mm
   // Double_t r = (stripid+gRandom->Uniform())*5.0+50.;
   // Double_t r = (correctedstripid[stripid]+gRandom->Uniform())*5.0+50.;
   // Double_t h = r * sin(a);
   // Double_t z = z_90-(r-90)*cos(a);

   // Double_t R = sqrt(h*h+z*z); // distance from target center to YY1 hit strip
   // Double_t theta0 = 180-atan(h/z)/PI*180.;
   Double_t theta0 = thetaconv[stripid] + (gRandom->Uniform() - 0.5) * thetacoverage[stripid];
   Double_t phi = phiconv[detid] + (gRandom->Uniform() - 0.5) * phicoverage[detid];
   Double_t theta0yz = PI - atan(tan(theta0 * PI / 180.) * sin(phi * PI / 180.));
   Double_t R = ((z_90 + 90 * cos(a)) * sin(a) / sin(theta0yz - a)) / (sqrt(1 - pow(sin(theta0 * PI / 180.) * cos(phi * PI / 180.), 2)));
   hitx = R * sin(theta0 * PI / 180.) * cos(phi * PI / 180.);
   hity = R * sin(theta0 * PI / 180.) * sin(phi * PI / 180.);
   hitz = R * cos(theta0 * PI / 180.);

   // Double_t theta = theta0yz/PI*180.;
   Double_t theta = acos(hitz / sqrt(pow(colx - hitx, 2) + pow(coly - hity, 2) + pow(hitz, 2))) / PI * 180.; // with respect to beam axis

   Double_t r1 = sqrt(pow(x0 - colx, 2) + pow(y0 - coly, 2) + pow(z0 - colz, 2));
   Double_t r2 = sqrt(pow(hitx - colx, 2) + pow(hity - coly, 2) + pow(hitz - colz, 2));
   Double_t r3 = sqrt(pow(x0 - hitx, 2) + pow(y0 - hity, 2) + pow(z0 - hitz, 2));
   scat = 180 - acos((r1 * r1 + r2 * r2 - r3 * r3) / (2 * r1 * r2)) / PI * 180.;
   out->SetTheta(theta);
   out->SetScat(scat);
   // out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   /*if (y2-y1>0&&phi>0&&phi<180){
      out->SetTheta(theta-scat);
   }
   else if (y2-y1<0&&phi>180&&phi<360){
      out->SetTheta(theta-scat);
   }
   else if (y2-y1>0&&phi>180&&phi<360){
      out->SetTheta(theta+scat);
   }
   else if (y2-y1<0&&phi>0&&phi<180){
      out->SetTheta(theta+scat);
   }
   else{
      out->SetTheta(theta);
   }*/
   out->SetPhi(phi);
   //   // get rid of ID=40 less than 1 MeV  2021/08/28
   //   if (siarr[0].ex_pos==40&&siarr[0].val<1.0) return;

   // track in YY1, penetrating events
   Double_t track_yz, track;
   Double_t thetayz;
   Double_t Rr, zr;
   Double_t zr_90 = z_90 + (90 + 0.3 * (tan(a) + 1 / tan(a))) * cos(a);
   // Rr = (z_90 + (90+0.3*(tan(a)+1/tan(a)))*cos(a))*sin(a)/sin(theta0*PI/180.-a);
   // zr = Rr*cos(theta0*PI/180.);
   // track = abs((zr-hitz)/cos(theta*PI/180.));
   thetayz = atan(tan(theta * PI / 180.) * sin(phi * PI / 180.));
   track_yz = 0.3 / (sin(thetayz - a));
   track = abs(track_yz / (sqrt(1 - pow(sin(theta * PI / 180.) * cos(phi * PI / 180.), 2))));
   if (track < 0.3)
   {
      // std::cout << " track: " << track  <<" hitz: " << hitz << " theta: " << theta << " theta0: " << theta0 << std::endl;
   }
   out->SetTrack(track);
   // out->SetCsIE(GetEremain2(track,siarr[0].val));
   // look for csi max
   if ((*fCsI)->GetEntriesFast() == 0)
      return;

   std::vector<Double_t> csiarr(16, 0);
   for (Int_t i = 0, n = (*fCsI)->GetEntriesFast(); i != n; ++i)
   {
      const Int_t id = dynamic_cast<art::TDataObject *>((*fCsI)->At(i))->GetID();
      if (id < 6 * 2)
      {
         const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
         csiarr[id] = ic->GetCharge();
      }
   }
   if (csiarr.empty())
      return;

   std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
   Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);

   if (*csimaxit > 4000)
      return;

   // out->SetEnergy(siarr[0].val + out->GetCsIE());
   out->SetEnergy(siarr[0].val + *csimaxit);
   out->SetCsIE(*csimaxit);
   out->SetEid(csimaxidx);
}
