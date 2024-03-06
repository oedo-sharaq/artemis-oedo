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
  TF1 *f[20000];
  TH2F* h1 = new TH2F("h1","",200,-200,200,200,-200,200);
  Int_t i;
  for (i = 0; i<N; i++){
    tree->GetEntry(i);
    if (sr11_xc0->IsEmpty()||sr12_xc0->IsEmpty()||tof39->IsEmpty()||tof12s1->IsEmpty())
      //if (sr11_xc0->IsEmpty()||sr12_xc0->IsEmpty()||tof39->IsEmpty())
      continue;
    art::TTimeDifference *tof_cont = ((art::TTimeDifference *)(tof39->First()));
    art::TTimeDifference *tof_cont1 = ((art::TTimeDifference *)(tof12s1->First()));
    tof_39 = tof_cont->GetTiming();
    tof_12s1 = tof_cont1->GetTiming();
    art::TSRPPACPlaneData *s91x = ((art::TSRPPACPlaneData*)(sr91_xc0->First()));
    art::TSRPPACPlaneData *s92x = ((art::TSRPPACPlaneData*)(sr92_xc0->First()));
    sr91x = s91x->GetPosition();
    sr92x = s92x->GetPosition();
    sr9x = (542.25*sr91x-122.5*sr92x)/419.75;
    if (abs(0.987494493767*tof_39+0.15765349593*sr9x-524)<2.5){
      if (sr11_xc0->IsEmpty()||sr12_xc0->IsEmpty())
	continue;
      art::TSRPPACPlaneData *s11x = ((art::TSRPPACPlaneData*)(sr11_xc0->First()));
      art::TSRPPACPlaneData *s12x = ((art::TSRPPACPlaneData*)(sr12_xc0->First()));
      sr11x = s11x->GetPosition();
      sr12x = s12x->GetPosition();
      sr1x = (240*sr12x+110*sr11x)/350.;
      if (abs(0.996732674624*tof_12s1+0.0807711293476*sr1x-148.5)<2.5){ //H-like
      //if (abs(0.996732674624*tof_12s1+0.0807711293476*sr1x-148.5)>2.5){
	x.emplace_back(sr11x);
	x.emplace_back(sr12x);
	//h1->Fill(x[0],x[1]);
	//    TGraph *g = new TGraph(2, &z[0], &x[0]);
	//    g->SetMarkerColor(4);
	//    g->SetMarkerSize(2);
	//    g->Draw("ap*");
	f[j] = new TF1(Form("f%d",j),"pol1");
	f[j]->SetParameters((x[0]*z[1]-x[1]*z[0])/(z[1]-z[0]),(x[1]-x[0])/(z[1]-z[0]));
	f[j]->SetRange(-250,500);
	f[j]->SetMinimum(-500);
	f[j]->SetMaximum(500);
	f[j]->SetLineWidth(1);
	if (j==0){
	  f[j]->GetXaxis()->SetTitle("Z");
	  f[j]->GetYaxis()->SetTitle("X");
	  f[j]->Draw();
	}
	else{
	  //if (abs((x[1]-x[0])/(z[1]-z[0]))>0.1)
	  //{
	  f[j]->Draw("same");
	  //}
	}
	x.clear();
	j++;
	//cout << j << endl;
	if (j > 50)
	  break;
	}
    }    
  }
  cout <<"total: " << i << endl;
  //h1->Draw("colz");
}
