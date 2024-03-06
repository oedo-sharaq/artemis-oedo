{
  for (int i = 1; i<=16; i++){
    tree->Draw(Form("ttt_back_hit[0].fCharge:csiS%d.fCharge>>back_h%d(150,0,30,150,0,20)",i,i),"","colz");
  }
  gROOT->ProcessLine("zone 4 4");
  for (Int_t j = 1; j<=16; j++){
    gROOT->ProcessLine(Form("ht %d colz",j));
  }
}
