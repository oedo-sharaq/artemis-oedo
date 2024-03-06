{
  for (int i = 0; i<16; i++){
    tree->Draw(Form("csiraw.fCharge>>h%d(500,0,500)",i+1),Form("csiraw.fID==%d",i));
  }
  h1->Fit("gaus","","",0,30);
  h2->Fit("gaus","","",0,50);
  h3->Fit("gaus","","",0,50);
  h4->Fit("gaus","","",0,50);
  h5->Fit("gaus","","",0,50);
  h6->Fit("gaus","","",0,50);
  h7->Fit("gaus","","",0,50);
  h8->Fit("gaus","","",0,50);
  h9->Fit("gaus","","",0,50);
  h10->Fit("gaus","","",0,50);
  h11->Fit("gaus","","",0,50);
  h12->Fit("gaus","","",0,50);
  h13->Fit("gaus","","",0,50);
  h14->Fit("gaus","","",0,50);
  h15->Fit("gaus","","",0,50);
  h16->Fit("gaus","","",0,50);

  gROOT->ProcessLine("z 4 4");
  for (int j = 1; j<=16; j++){
    gROOT->ProcessLine(Form("ht %d",j));
  }
}
