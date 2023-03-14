void csi_calib(TH2 *h2) {
  gStyle->SetStatX(0.95);
  Int_t nmax = h2->GetNbinsX();
  Int_t min  = h2->GetXaxis()->GetBinUpEdge(0);
  Int_t max  = h2->GetXaxis()->GetBinUpEdge(nmax);
  Int_t bin  = (max-min)/nmax;
  printf("%d %d %d %d\n",nmax,min,max,bin);
  for(Int_t i=0; i<nmax; i++) {
    TH1 *h1 = h2->ProjectionY(Form("h%02d",i+1),i+1,i+1);
	h1->SetTitle("");
    h1->SetTitle(Form("ProjectionY of %s [x=%d,%d]",h2->GetTitle(),i*bin,(i+1)*bin));
  }
}
