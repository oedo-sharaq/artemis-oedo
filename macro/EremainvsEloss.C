{
  gROOT->ProcessLine("z");
  tree->Draw("tina3.fEcsi:tina3.fDeltaE>>aa(200,0,30,200,0,40)","","colz");
  gROOT->ProcessLine(".x EnergyLossClass/csi.cpp");
}
