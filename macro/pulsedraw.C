{
  tree->Draw("ttt_back_pulse.fCharge:ttt_back_hit.fID>>back(512,0,512,150,1000,8000)","ttt_back_hit.fID!=118&&ttt_back_hit.fID!=117&&ttt_back_hit.fID!=119","colz");
  tree->Draw("ttt_front_pulse.fCharge:ttt_front_hit.fID>>front(512,0,512,150,1000,8000)","","colz");
  gROOT->ProcessLine("zone 1 2");
  gROOT->ProcessLine("ht 2 colz");
  gROOT->ProcessLine("lgz");
  gROOT->ProcessLine("hn colz");
  gROOT->ProcessLine("lgz");


}
