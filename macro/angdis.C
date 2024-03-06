{

  for (int i = 1; i<=5;i++){
    tree->Draw(Form("theta>>ang1%d(100,90,180)",i),Form("coins0&&pid9&&tinaxy&&tgate&&pgate1&&pid1&&abs(ex2-%d)<1",2*i-1),"colz");
    tree->Draw(Form("theta>>ang2%d(100,90,180)",i),Form("coins0&&pid9&&tinaxy&&tgate&&pgate2&&pid1&&abs(ex2-%d)<1",2*i-1),"colz");
    gROOT->ProcessLine(Form("ang2%d->SetLineColor(kRed)",i)); 
  }
  TCanvas *c1 = new TCanvas();
  c1->Divide(2,3);
  c1->cd(1);
  ang21->Draw();
  ang11->Draw("same");
  c1->cd(2);
  ang22->Draw();
  ang12->Draw("same");
  c1->cd(3);
  ang23->Draw();
  ang13->Draw("same");
  c1->cd(4);
  ang24->Draw();
  ang14->Draw("same");
  c1->cd(5);
  ang25->Draw();
  ang15->Draw("same");
}
