{
  tree->Draw("ttt_back_hit.fCharge>>back_hit(150,2,8)","ttt_back_hit.fID!=118&&ttt_back_hit.fID!=117&&ttt_back_hit.fID!=119");
  tree->Draw("ttt_back_hit.fCharge:ttt_back_hit.fID>>back_hit2d(512,0,512,150,2,8)","ttt_back_hit.fID!=118&&ttt_back_hit.fID!=117&&ttt_back_hit.fID!=119","colz");
  tree->Draw("ttt_front_hit.fCharge>>front_hit(150,2,8)","");
  tree->Draw("ttt_front_hit.fCharge:ttt_front_hit.fID>>front_hit2d(512,0,512,150,2,8)","","colz");
  
  //back_hit->SetLineColor(2);
  /*TF1 *f1 = new TF1("f1", "gaus(0)+gaus(3)+gaus(6)");
  f1->SetParameters(100,3.18,0.1,100,5.48,0.1,100,5.9,0.1);
  back_hit->Fit("f1","","",2,7);
  f1->SetParameters(100,3.18,0.1,100,5.48,0.1,100,5.9,0.1);
  front_hit->Fit("f1","","",2,7);
  */
}
