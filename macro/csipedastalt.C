{
  for (int i = 0; i<16; i++){
    tree->Draw(Form("csiT%d.fCharge>>h%d(500,0,500)",i+1,i+1),"");
  }
  h1->Fit("gaus","","",0,300);
  h2->Fit("gaus","","",0,300);
  h3->Fit("gaus","","",0,300);
  h4->Fit("gaus","","",0,300);
  h5->Fit("gaus","","",0,300);
  h6->Fit("gaus","","",0,300);
  h7->Fit("gaus","","",0,300);
  h8->Fit("gaus","","",0,300);
  h9->Fit("gaus","","",0,300);
  h10->Fit("gaus","","",0,300);
  h11->Fit("gaus","","",0,300);
  h12->Fit("gaus","","",0,300);
  h13->Fit("gaus","","",0,300);
  h14->Fit("gaus","","",0,300);
  h15->Fit("gaus","","",0,300);
  h16->Fit("gaus","","",0,300);

  gROOT->ProcessLine("z 4 4");
  for (int j = 1; j<=16; j++){
    gROOT->ProcessLine(Form("ht %d",j));
  }
}
