#include <iostream>
#include "EnergyLoss.h"

void pcurve()
{
  EnergyLoss *p_in_Si = new EnergyLoss();
  p_in_Si->ReadLISEdEdx("/home/sh19post/art_analysis/user/li/EnergyLossTable/p_in_Si.lise", 1.0, 2.3212, 4);
  std::vector<Double_t> Emin{};
  Double_t track;
  Double_t thetamax = 160 * TMath::Pi() / 180.;
  Double_t thetamin = 0.5 * TMath::Pi();
  std::vector<Double_t> theta{};
  Double_t step = 0.01;
  Int_t N = (thetamax * 180 / TMath::Pi() - thetamin * 180 / TMath::Pi()) / step;
  for (int i = 0; i <= N; i++)
  {
    theta.emplace_back(thetamin * 180 / TMath::Pi() + i * step);
    track = 0.3 / cos(theta.at(i) * TMath::Pi() / 180. - thetamin);
    Emin.emplace_back(p_in_Si->AddBack(0, track));
  }
  TGraph *g = new TGraph(N + 1, &theta[0], &Emin[0]);
  // g->GetXaxis()->SetRange(90, 160);
  g->SetLineColor(kBlack);
  g->Draw("same");
}
