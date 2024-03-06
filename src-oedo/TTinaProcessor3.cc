#include "TTinaProcessor3.h"
#include "TTinaData3.h"

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

#include "TSRPPACPlaneData.h"
#include "EnergyLoss.h"

using art::TTinaProcessor3;

ClassImp(TTinaProcessor3)

    TTinaProcessor3::TTinaProcessor3()
    : fOutput(NULL)
{
  RegisterInputCollection("SifName", "name of input collection for TTT front",
                          fSifName, TString("ttt_front"),
                          &fSif, TClonesArray::Class_Name(), art::ICharge::Class_Name());
  RegisterInputCollection("SibName", "name of input collection for TTT back",
                          fSibName, TString("ttt_back"),
                          &fSib, TClonesArray::Class_Name(), art::ICharge::Class_Name());
  RegisterInputCollection("CsIName", "name of input collection for CsI",
                          fCsIName, TString("tinacsi"),
                          &fCsI, TClonesArray::Class_Name(), art::ICharge::Class_Name());
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
                           fOutputName, TString("tina3"),
                           &fOutput, TClonesArray::Class_Name(), art::TTinaData3::Class_Name());
}

TTinaProcessor3::~TTinaProcessor3()
{
}

Double_t GetEremain(Double_t track, Double_t DeltaE)
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
Double_t GetRange(Double_t DeltaE)
{ // mm, MeV
  EnergyLoss *p_in_Si = new EnergyLoss();
  p_in_Si->ReadLISEdEdx("/home/sh19post/art_analysis/user/li/EnergyLossTable/p_in_Si.lise", 1.0, 2.3212, 4);
  Double_t range;
  range = p_in_Si->CalcRange(DeltaE, 0); // mm
  return range;
}

void TTinaProcessor3::Process()
{

  fOutput->Clear("C");

  if ((*fX1)->GetEntriesFast() == 0)
    return;
  if ((*fY1)->GetEntriesFast() == 0)
    return;
  if ((*fX2)->GetEntriesFast() == 0)
    return;
  if ((*fY2)->GetEntriesFast() == 0)
    return;

  // look for front side TTT max
  if ((*fSif)->GetEntriesFast() == 0)
    return;

  std::vector<Double_t> ttt_front_arr(512, 0);
  for (Int_t i = 0, n = (*fSif)->GetEntriesFast(); i != n; ++i)
  {
    const Int_t id = dynamic_cast<art::TDataObject *>((*fSif)->At(i))->GetID();
    if (id < 512)
    {
      const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fSif)->At(i));
      ttt_front_arr[id] = ic->GetCharge();
    }
  }
  if (ttt_front_arr.empty())
    return;

  // look for backside TTT max
  if ((*fSib)->GetEntriesFast() == 0)
    return;
  std::vector<Double_t> ttt_back_arr(512, 0);
  for (Int_t i = 0, n = (*fSib)->GetEntriesFast(); i != n; ++i)
  {
    const Int_t id = dynamic_cast<art::TDataObject *>((*fSib)->At(i))->GetID();
    if (id < 512)
    {
      const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fSib)->At(i));
      ttt_back_arr[id] = ic->GetCharge();
    }
  }
  if (ttt_back_arr.empty())
    return;
  //----------------------------------------

  // sorting frontside
  std::vector<Double_t>::iterator tttf_maxit = std::max_element(ttt_front_arr.begin(), ttt_front_arr.end());
  Int_t tttf_maxid = std::distance(ttt_front_arr.begin(), tttf_maxit);
  // sorting backtside
  std::vector<Double_t>::iterator tttb_maxit = std::max_element(ttt_back_arr.begin(), ttt_back_arr.end());
  Int_t tttb_maxid = std::distance(ttt_back_arr.begin(), tttb_maxit);

  //   if(*simaxit < 0.5) return;
  if (*tttf_maxit < 0.1)
    return;
  TTinaData3 *out = static_cast<TTinaData3 *>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
  out->SetDeltaE(*tttf_maxit);
  out->SetEnergy(*tttf_maxit);
  // out->SetEcsi(*tttf_maxit);
  Int_t x_stripid = tttf_maxid % 128;
  Int_t z_stripid = tttb_maxid % 128;
  Int_t detid = tttb_maxid / 128;

  // collision point at taraget by tracking from fe12?
  Double_t colx, coly, colz;

  colx = 0;
  coly = 0;
  colz = 0;

  Double_t x1 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX1)->At(0)))->GetPosition();
  Double_t y1 = (dynamic_cast<art::TSRPPACPlaneData *>((*fY1)->At(0)))->GetPosition();
  //  Double_t z1 = -1962.;
  Double_t z1 = -2017.; // 55 mm
  Double_t x2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX2)->At(0)))->GetPosition();
  Double_t y2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fY2)->At(0)))->GetPosition();
  //  Double_t z2 = -1462.;
  Double_t z2 = -1517.; // 55 mm
  if (x1 != x1 || x2 != x2 || y1 != y1 || y2 != y2)
  {
    return;
  }

  Double_t x0, y0, z0; // fe12 chamber center
  x0 = 0.5 * (x1 + x2);
  y0 = 0.5 * (y1 + y2) - 30; // 20231225
  z0 = -1767.;

  //  colx = coly = 0;
  colx = (-z1 * x2 + z2 * x1) / (z2 - z1);
  coly = (-z1 * (y2 - 30.) + z2 * (y1 - 30.)) / (z2 - z1);
  colz = 0.;
  out->SetX(colx);
  out->SetY(coly);

  // hit point at TTT, strip pitch 0.76 mm, width 0.70 mm, length 97.22 mm
  Double_t hitx, hity, hitz;
  Double_t dx, dy, dz, ttt_track;

  if (detid == 0)
  {
    hitx = -55.;
    hity = x_stripid * 0.76 + (gRandom->Uniform()) * 0.70 - 48.61;
  }
  if (detid == 1)
  {
    hitx = -(x_stripid * 0.76 + (gRandom->Uniform()) * 0.70) + 48.61;
    hity = -55.;
  }
  if (detid == 2)
  {
    hitx = x_stripid * 0.76 + (gRandom->Uniform()) * 0.70 - 48.61;
    hity = 55.;
  }
  if (detid == 3)
  {
    hitx = 55.;
    hity = -(x_stripid * 0.76 + (gRandom->Uniform()) * 0.70) + 48.61;
  }

  hitz = -(z_stripid * 0.76 + (gRandom->Uniform()) * 0.70) - 14.14;

  //   out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
  //   out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);
  const Double_t PI = 4.0 * atan(1.0);
  out->SetTheta(acos((hitz - colz) / sqrt((hitx - colx) * (hitx - colx) + (hity - coly) * (hity - coly) + (hitz - colz) * (hitz - colz))) / PI * 180.);
  if (hity - coly >= 0)
  {
    out->SetPhi(atan2(hity - coly, hitx - colx) / PI * 180.);
  }
  else
  {
    out->SetPhi(atan2(hity - coly, hitx - colx) / PI * 180. + 360.);
  }

  Double_t r1 = sqrt(pow(x0 - colx, 2) + pow(y0 - coly, 2) + pow(z0 - colz, 2));
  Double_t r2 = sqrt(pow(hitx - colx, 2) + pow(hity - coly, 2) + pow(hitz - colz, 2));
  Double_t r3 = sqrt(pow(x0 - hitx, 2) + pow(y0 - hity, 2) + pow(z0 - hitz, 2));
  Double_t scat = 180 - acos((r1 * r1 + r2 * r2 - r3 * r3) / (2 * r1 * r2)) / PI * 180.;

  out->SetScat(scat);

  Double_t thetarad = out->GetTheta() * (TMath::Pi() / 180);
  Double_t phirad = out->GetPhi() * (TMath::Pi() / 180);

  // std::cout << "TotalE: " << *tttf_maxit + out->GetEcsi() << ", DeltaE: " << *tttf_maxit << ", Ecsi: " << out->GetEcsi() << ", track: " << ttt_track << std::endl;
  // look for csi max
  // if ((*fCsI)->GetEntriesFast() == 0)
  // return;

  std::vector<Double_t> csiarr(16, 0);
  if ((*fCsI)->GetEntriesFast() == 0)
  {
    for (int i = 0; i < 16; i++)
    {
      csiarr[i] = 0;
    }
    out->SetTrack(GetRange(*tttf_maxit));
    // std::cout << "empty" << std::endl;
  }
  else
  {
    for (Int_t i = 0, n = (*fCsI)->GetEntriesFast(); i != n; ++i)
    {
      const Int_t id = dynamic_cast<art::TDataObject *>((*fCsI)->At(i))->GetID();
      if (id < 16)
      {
        // const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fCsI)->At(i));
        // csiarr[id] = ic->GetCharge();
        if (detid == 0 && abs(id - 5.5) < 2)
        { // id=4,5,6,7
          const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
          csiarr[id] = ic->GetCharge();
        }
        if (detid == 1 && abs(id - 13.5) < 2)
        { // id=12,13,14,15
          const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
          csiarr[id] = ic->GetCharge();
        }
        if (detid == 2 && abs(id - 9.5) < 2)
        { // id=8,9,10,11
          const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
          csiarr[id] = ic->GetCharge();
          //}if(detid==3&&abs(id-1.5)<2){
        }
        if (detid == 3 && abs(id - 1) <= 2)
        { // id=0,1,2,3
          const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
          csiarr[id] = ic->GetCharge();
        }
      }
    }
  }
  //  if (csiarr.empty())
  // return;

  std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
  Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);
  out->SetEcsi(*csimaxit);

  // if (*csimaxit > 4000)
  // return;

  Double_t range;
  // range = GetRange(*tttf_maxit);
  // get the track in ttt, penetrating events
  if (detid == 0)
  {
    dx = -0.3;
    dz = dx / tan(thetarad) / cos(phirad);
    dy = dz * tan(thetarad) * sin(phirad);
  }
  if (detid == 1)
  {
    dy = -0.3;
    dz = dy / tan(thetarad) / sin(phirad);
    dx = dz * tan(thetarad) * cos(phirad);
  }
  if (detid == 2)
  {

    dy = 0.3;
    dz = dy / tan(thetarad) / sin(phirad);
    dx = dz * tan(thetarad) * cos(phirad);
  }
  if (detid == 3)
  {

    dx = 0.3;
    dz = dx / tan(thetarad) / cos(phirad);
    dy = dz * tan(thetarad) * sin(phirad);
  }
  ttt_track = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
  // if (range <= ttt_track)
  // {
  // out->SetTrack(range);
  // out->SetEcsicalc(0);
  // }
  // else
  // {

  if (*csimaxit == 0)
  {
    out->SetTrack(GetRange(*tttf_maxit));
    out->SetEcsicalc(0);
  }
  else
  {
    out->SetEcsicalc(GetEremain(ttt_track, *tttf_maxit));
    out->SetTrack(ttt_track);
  }
  // }
  if (out->GetTrack() != out->GetTrack())
    std::cout << out->GetDeltaE() << " " << out->GetTrack() << " " << *csimaxit << " " << out->GetTheta() << " " << out->GetPhi() << " " << hitx << " " << colx << " " << x1 << " " << x2 << std::endl;
  out->SetEnergy(*tttf_maxit + *csimaxit);
  // out->SetEnergy(*tttf_maxit + out->GetEcsi());
}
