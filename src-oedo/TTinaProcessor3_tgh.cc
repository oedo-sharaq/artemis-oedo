#include "TTinaProcessor3.h"
#include "TTinaData3.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>

#include <TGraph.h>
#include <TVector3.h>

#include "TSRPPACPlaneData.h"

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

void TTinaProcessor3::Process()
{

  fOutput->Clear("C");

  // look for front side TTT max
  //  if ((*fSif)->GetEntriesFast() == 0) return;
  if (((*fSif)->GetEntriesFast() == 0) || ((*fSif)->GetEntriesFast() > 2))
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

  // look for back side TTT max
  //  if ((*fSib)->GetEntriesFast() == 0) return;
  if (((*fSib)->GetEntriesFast() == 0) || ((*fSib)->GetEntriesFast() > 2))
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

  if (*tttf_maxit < 0.1)
    return;
  TTinaData3 *out = static_cast<TTinaData3 *>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
  out->SetDeltaE(*tttf_maxit);
  out->SetEnergy(*tttf_maxit);
  Int_t x_stripid = tttf_maxid % 128;
  Int_t z_stripid = tttb_maxid % 128;
  Int_t detid = tttb_maxid / 128;

  Double_t colx = 0.;
  Double_t coly = 0.;
  Double_t colz = 0.;

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
  //  Double_t z1 = -1962.;
  Double_t z1 = -2017.; // 55 mm
  Double_t x2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX2)->At(0)))->GetPosition();
  Double_t y2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fY2)->At(0)))->GetPosition();
  //  Double_t z2 = -1462.;
  Double_t z2 = -1517.; // 55 mm

  colx = (-z1 * x2 + z2 * x1) / (z2 - z1);
  coly = (-z1 * (y2 - 30.) + z2 * (y1 - 30.)) / (z2 - z1);
  colz = 0.;
  out->SetX(colx);
  out->SetY(coly);

  // hit point at TTT, strip pitch 0.76 mm, width 0.70 mm, length 97.22 mm
  Double_t hitx = 0.;
  Double_t hity = 0.;
  Double_t hitz = 0.;

  if (detid == 0)
  {
    hitx = -55.;
    hity = x_stripid * 0.76 + (gRandom->Uniform()) * 0.70 - 48.61;
    // hity = -(x_stripid*0.76+(gRandom->Uniform())*0.70-48.61);
  }
  if (detid == 1)
  {
    hitx = -(x_stripid * 0.76 + (gRandom->Uniform()) * 0.70) + 48.61;
    // hitx = -(-(x_stripid*0.76+(gRandom->Uniform())*0.70)+48.61);
    hity = -55.;
  }
  if (detid == 2)
  {
    hitx = x_stripid * 0.76 + (gRandom->Uniform()) * 0.70 - 48.61;
    // hitx = -(x_stripid*0.76+(gRandom->Uniform())*0.70-48.61);
    hity = 55.;
  }
  if (detid == 3)
  {
    hitx = 55.;
    hity = -(x_stripid * 0.76 + (gRandom->Uniform()) * 0.70) + 48.61;
    // hity = -(-(x_stripid*0.76+(gRandom->Uniform())*0.70)+48.61);
  }

  hitz = -(z_stripid * 0.76 + (gRandom->Uniform()) * 0.70) - 14.14;
  // hitz = -((127-z_stripid)*0.76+(gRandom->Uniform())*0.70)-14.14;

  TVector3 vsrc(x2 - x1, y2 - y1, z2 - z1);
  TVector3 vcol(colx, coly, colz);
  TVector3 vhit(hitx, hity, hitz);
  TVector3 v0(0, 0, 1);

  const Double_t PI = 4.0 * atan(1.0);
  Double_t scat = vsrc.Angle(vhit - vcol) / PI * 180.;
  //  Double_t scat0 = v0.Angle(vhit-vcol)/PI*180.;
  //  printf("%f, %f, %f\n", scat,scat0,scat-scat0);
  out->SetTheta(scat);
  //  Double_t phi;
  if (hity - coly >= 0)
  {
    out->SetPhi(atan2(hity - coly, hitx - colx) / PI * 180.);
    //  phi = atan2(hity-coly,hitx-colx)/PI*180.;
  }
  else
  {
    out->SetPhi(atan2(hity - coly, hitx - colx) / PI * 180. + 360.);
    //  phi = atan2(hity-coly,hitx-colx)/PI*180.+360.;
  }
  //  printf("bid: %d, detid: %d, sa: %f, phi: %f\n", tttb_maxid, detid, sa, phi);
  out->SetDefid(tttf_maxid);
  out->SetDebid(tttb_maxid);

  // look for csi max
  if ((*fCsI)->GetEntriesFast() == 0)
    return;

  std::vector<Double_t> csiarr(16, 0);
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
      { // id=0,1,2
        const art::ICharge *const ic = dynamic_cast<art::ICharge *>((*fCsI)->At(i));
        csiarr[id] = ic->GetCharge();
      }
    }
  }
  if (csiarr.empty())
    return;

  std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
  Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);

  // TString fInputd,fInputu;
  // Double_t scat = acos((hitz-colz)/sqrt((hitx-colx)*(hitx-colx)+(hity-coly)*(hity-coly)+(hitz-colz)*(hitz-colz)))/PI*180.;

  // 0.1 deg ver.
  // fInputd.Form("/home/sakura01/art_analysis/user/tgh/atima_data/dee_%3.1fdeg.dat",floor(scat*10)/10); // round down
  // fInputu.Form("/home/sakura01/art_analysis/user/tgh/atima_data/dee_%3.1fdeg.dat",ceil(scat*10)/10);  // round up

  // TGraph *fDE2Ed = new TGraph(fInputd,"%lg %lg %*lg");
  // TGraph *fDE2Eu = new TGraph(fInputu,"%lg %lg %*lg");
  // Double_t ed = fDE2Ed->Eval(*tttf_maxit);
  // Double_t eu = fDE2Eu->Eval(*tttf_maxit);

  // Double_t eremain = (eu-ed)/0.1*(scat-floor(scat*10)/10)+ed;
  // if(eremain>0) out->SetEnergy(*tttf_maxit + eremain);

  if (*csimaxit > 4000)
    return;

  out->SetEnergy(*tttf_maxit + *csimaxit);
  out->SetEid(csimaxidx);
}
