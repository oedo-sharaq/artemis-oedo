{
  for (int i = 1; i<=16; i++){
    //tree->Draw(Form("ttt_front_hit[0].fCharge:csiS%d.fCharge>>front_h%d(150,0,4000,150,0,20)",i,i),"","colz");
    //tree->Draw(Form("ttt_front_hit[0].fCharge:csiS%d.fCharge>>front_h%d(150,0,30,150,0,20)",i,i),"timinggate","colz");
    tree->Draw(Form("tina2.fCsIE:csiT%d.fCharge>>front_h%d(30,0,4000,30,0,20)",i,i),"","colz");
  }
  gROOT->ProcessLine("zone 4 4");
  for (Int_t j = 1; j<=16; j++){
    gROOT->ProcessLine(Form("ht %d colz",j));
    gROOT->ProcessLine("lgz");
    }
}
