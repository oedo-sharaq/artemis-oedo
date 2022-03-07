void corrDCC1() {

  TCanvas *cOrig = new TCanvas("cOrig","cOrig");
  cOrig->cd();
  tree->Draw("dcc1.fX:dcc2.fX>>hist(200,-10,30,200,-30,10)","","colz");
  TH2F *histOrig = (TH2F*)gDirectory->Get("hist");

  TCanvas *cProfile = new TCanvas("cProfile","cProfile");
  cProfile->cd(); 
  TProfile *profX = histOrig->ProfileX();
  profX->Draw();  
  TF1 *fit = new TF1("fit","pol1",5,20);
  fit->SetParameters(-24., 1.);
  profX->Fit("fit","MR");
  double offset = fit->GetParameter(0);
  
  TCanvas *cCorr = new TCanvas("cCorr","cCorr");
  cCorr->cd();
  tree->Draw(Form("(dcc1.fX-%.*f):dcc2.fX>>hist2(200,-10,30,200,-10,30)",2,offset),"","colz");
  TH2F *histCorr = (TH2F*)gDirectory->Get("hist2");

}
