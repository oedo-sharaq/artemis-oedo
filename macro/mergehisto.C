{
  tree->Draw("ttt_front_pulse.fCharge:ttt_front_hit.fID>>all(129,0,129,150,1000,8000)","","colz");
  tree->Draw("ttt_front_pulse.fCharge:ttt_front_hit.fID>>h2(383,129,512,110,1000,8000)","","colz");
  all->Add(h2,1);
  all->Draw("colz");


}
