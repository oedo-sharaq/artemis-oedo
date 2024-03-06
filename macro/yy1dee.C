{
  TCanvas* c1 = new TCanvas();
  for (int i = 1; i<=16; i++){
    //    tree->Draw(Form("yy1f[0].fCharge:csiT%d.fCharge>>h%d(100,0,4000,100,0,15)",i,i),"","colz");
    tree->Draw(Form("yy1f[0].fCharge:csiT%d.fCharge>>h%d(100,0,10,100,0,15)",i,i),"","colz");
  }
  c1->Delete();
  gROOT->ProcessLine("zone 4 4");
  gROOT->ProcessLine("ht 1 colz");
  //char* s;
  for (int j = 1; j<=15; j++){
    //s = Form("ht %d colz",i);
    gROOT->ProcessLine("hn colz");
  }
}
