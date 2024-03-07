void Getdqdxhist(){

 TH1F *hqhist = (TH1F*)gROOT->FindObject("hq");
 
  Float_t fXRange[2];
  Float_t fXRangeColor[2];
  Double_t min = hqhist->GetXaxis()->GetXmin();
  Double_t max = hqhist->GetXaxis()->GetXmax();


  fXRange[0] = hqhist->GetXaxis()->GetBinLowEdge(hqhist->GetXaxis()->FindBin(min));
  fXRange[1] = hqhist->GetXaxis()->GetBinLowEdge(hqhist->GetXaxis()->FindBin(max));


  const Int_t minBin = hqhist->GetXaxis()->FindBin(fXRange[0]);
  const Int_t maxBin = hqhist->GetXaxis()->FindBin(fXRange[1]);
  const Int_t nBin = maxBin - minBin + 1; // bin number for hDXDT

  fXRange[0] = hqhist->GetBinLowEdge(minBin);
  fXRange[1] = hqhist->GetBinLowEdge(maxBin+1);


 TH1F *hqx = new TH1F("hqx","hqx_hist",nBin,fXRange[0],fXRange[1]);


   Float_t sum = 0;
  for(Int_t ibin = 0; ibin != nBin; ++ibin){
      sum += hqhist->GetBinContent(minBin + ibin);
      hqx->SetBinContent(ibin+1,sum);
   }

//   hqx->Scale(1./sum);
//   const Double_t sca = 1./ sum;

 TH1F *hqxnew = new TH1F("hqxnew","hqxnew_hist",nBin,fXRange[0],fXRange[1]);

  Float_t n = 0;
  Float_t p = 0;
  for(Int_t ibin = 0; ibin != nBin; ++ibin){
      n = hqx->GetBinContent(ibin);
      p = n / sum;
      hqxnew->SetBinContent(ibin+1,p);
   }

   hqxnew->Draw();


   TH1F *h = (TH1F*)hqxnew->Clone();
   h->GetXaxis()->SetRange(0,70);
   TH1F *hqxcolor = (TH1F*)h->Clone();
   hqxcolor->SetFillColor(46);
   hqxcolor->SetFillStyle(3001);

   hqxcolor->Draw("same");


}
