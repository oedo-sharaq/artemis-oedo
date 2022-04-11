void extrapolation(){

 TClonesArray *srppacu_xc0 = NULL;
 TClonesArray *srppacu_yc0 = NULL;
 TClonesArray *srppacd_xc0 = NULL;
 TClonesArray *srppacd_yc0 = NULL;

 tree->SetBranchAddress("srppacu_xc0",&srppacu_xc0);
 tree->SetBranchAddress("srppacu_yc0",&srppacu_yc0);
 tree->SetBranchAddress("srppacd_xc0",&srppacd_xc0);
 tree->SetBranchAddress("srppacd_yc0",&srppacd_yc0);

 Double_t srux,sruy,srdx,srdy;
 Int_t n = tree->GetEntries(); 

 //from upstreamPPAC to  extrapolation position 
 double z = 1199;  //center of CAT
 double zu = 0;
 double zd = 474;

 double kx[n];
 double ky[n];
 double xex[n];
 double yex[n];

 TH2D *hexCAT = new TH2D("hexcat","hexcat",200,-20,20,200,-20,20);
for (int i=0; i != n; i++){

 srux = -1000;
 sruy = -1000;
 srdx = -1000;
 srdy = -1000;

 tree->GetEntry(i);

  if (srppacu_xc0 && !srppacu_xc0->IsEmpty()){
   Int_t nHits = srppacu_xc0->GetEntriesFast();
  for (Int_t iHit = 0; iHit < nHits; iHit++){
   if(iHit == 0){ 
     srux = ((art::TSRPPACPlaneData*)(srppacu_xc0->At(iHit)))->GetPosition();
       }
    }
  }

  if (srppacu_yc0 && !srppacu_yc0->IsEmpty()){
   Int_t nHits = srppacu_yc0->GetEntriesFast();
  for (Int_t iHit = 0; iHit < nHits; iHit++){
   if(iHit == 0){ 
     sruy = ((art::TSRPPACPlaneData*)(srppacu_yc0->At(iHit)))->GetPosition();
       }
    }
  }

  if (srppacd_xc0 && !srppacd_xc0->IsEmpty()){
   Int_t nHits = srppacd_xc0->GetEntriesFast();
  for (Int_t iHit = 0; iHit < nHits; iHit++){
   if(iHit == 0){ 
     srdx = ((art::TSRPPACPlaneData*)(srppacd_xc0->At(iHit)))->GetPosition();
       }
    }
  }

  if (srppacd_yc0 && !srppacd_yc0->IsEmpty()){
   Int_t nHits = srppacd_yc0->GetEntriesFast();
  for (Int_t iHit = 0; iHit < nHits; iHit++){
   if(iHit == 0){ 
     srdy = ((art::TSRPPACPlaneData*)(srppacd_yc0->At(iHit)))->GetPosition();
       }
    }
  }
 
 kx[i] = (srdx - srux) / (zd - zu);
 ky[i] = (srdy - srdy) / (zd - zu);

 xex[i] = kx[i] * z + srux;
 yex[i] = ky[i] * z + sruy;
       
 hexCAT->Fill(xex[i],yex[i]);
 
 kx[i] = 0;
 ky[i] = 0;
 xex[i] = 0;
 yex[i] = 0;
 
 }

 hexCAT->Draw();

}


