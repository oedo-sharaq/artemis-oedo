{
  Int_t N;
  N = tree->GetEntries();
  TClonesArray *sr11_xc0;
  TClonesArray *sr12_xc0;
  TClonesArray *tof39;
  TClonesArray *sr91_xc0;
  TClonesArray *sr92_xc0;
  TClonesArray *tof12s1;
  tree->SetBranchAddress("sr11_xc0",&sr11_xc0);
  tree->SetBranchAddress("sr12_xc0",&sr12_xc0);
  tree->SetBranchAddress("sr91_xc0",&sr91_xc0);
  tree->SetBranchAddress("sr92_xc0",&sr92_xc0);
  tree->SetBranchAddress("tof39",&tof39);
  tree->SetBranchAddress("tof12s1",&tof12s1);
  std::vector <Double_t> x;
  std::vector <Double_t> z{0,350};
  Double_t sr91x,sr92x,sr9x,sr11x,sr12x,sr1x;
  Double_t tof_39,tof_12s1;
  Int_t j =0;
  TH2F* h[20];
  for (Int_t i = 0; i<N; i++){
    tree->GetEntry(i);
    if (sr11_xc0->IsEmpty()||sr12_xc0->IsEmpty()||tof39->IsEmpty()||tof12s1->IsEmpty()||sr11_xc0->IsEmpty()||sr12_xc0->IsEmpty())
      continue;
    art::TTimeDifference *tof_cont = ((art::TTimeDifference *)(tof39->First()));
    tof_39 = tof_cont->GetTiming();
    art::TSRPPACPlaneData *s91x = ((art::TSRPPACPlaneData*)(sr91_xc0->First()));
    art::TSRPPACPlaneData *s92x = ((art::TSRPPACPlaneData*)(sr92_xc0->First()));
    sr91x = s91x->GetPosition();
    sr92x = s92x->GetPosition();
    sr9x = (542.25*sr91x-122.5*sr92x)/419.75;
    if (abs(0.987494493767*tof_39+0.15765349593*sr9x-524)<2.5){
      art::TSRPPACPlaneData *s11x = ((art::TSRPPACPlaneData*)(sr11_xc0->First()));
      art::TSRPPACPlaneData *s12x = ((art::TSRPPACPlaneData*)(sr12_xc0->First()));
      art::TTimeDifference *tof_cont1 = ((art::TTimeDifference *)(tof12s1->First()));
      tof_12s1 = tof_cont1->GetTiming();
      sr11x = s11x->GetPosition();
      sr12x = s12x->GetPosition();
      sr1x = (240*sr12x+110*sr11x)/350.;
    }    
  }
}
