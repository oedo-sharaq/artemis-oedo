void Drawhist(){

 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ca/BLD_maxz_stm.170272.ca.hist.root"); // Load file. Basically BLD file.
  if(!file_load){
	 printf("Cannot open the file!\n");
	 return;
 }

 TTree *tree = (TTree*) gDirectory->Get("tree");


 TClonesArray *array_dc31_x1 = NULL;
 TClonesArray *array_dc31_x1 = NULL;
 TClonesArray *array_dc31_x2 = NULL;
 TClonesArray *array_dc31_x3 = NULL;
 TClonesArray *array_dc31_x4 = NULL;
 TClonesArray *array_dc31_y1 = NULL;
 TClonesArray *array_dc31_y2 = NULL;
 TClonesArray *array_dc31_y3 = NULL;
 TClonesArray *array_dc31_y4 = NULL;
 TClonesArray *array_dc32_x1 = NULL;
 TClonesArray *array_dc32_x2 = NULL;
 TClonesArray *array_dc32_y1 = NULL;
 TClonesArray *array_dc32_y2 = NULL;
 TClonesArray *array_dc21_x1 = NULL;
 TClonesArray *array_dc21_x2 = NULL;
 TClonesArray *array_dc21_u = NULL;
 TClonesArray *array_dc21_v = NULL;
 TClonesArray *array_dc22_x1 = NULL;
 TClonesArray *array_dc22_x2 = NULL;
 TClonesArray *array_dc22_u = NULL;
 TClonesArray *array_dc22_v = NULL;

 
 art::TEventHeader *array_eventheader = NULL;

 tree->SetBranchAddress("dc31_x1",&array_dc31_x1);
 tree->SetBranchAddress("dc31_x2",&array_dc31_x2);
 tree->SetBranchAddress("dc31_x3",&array_dc31_x3);
 tree->SetBranchAddress("dc31_x4",&array_dc31_x4);
 tree->SetBranchAddress("dc31_y1",&array_dc31_y1);
 tree->SetBranchAddress("dc31_y2",&array_dc31_y2);
 tree->SetBranchAddress("dc31_y3",&array_dc31_y3);
 tree->SetBranchAddress("dc31_y4",&array_dc31_y4);
 tree->SetBranchAddress("dc32_x1",&array_dc32_x1);
 tree->SetBranchAddress("dc32_x2",&array_dc32_x2);
 tree->SetBranchAddress("dc32_y1",&array_dc32_y1);
 tree->SetBranchAddress("dc32_y2",&array_dc32_y2);
 tree->SetBranchAddress("dc21_x1",&array_dc21_x1);
 tree->SetBranchAddress("dc21_x2",&array_dc21_x2);
 tree->SetBranchAddress("dc21_u",&array_dc21_u);
 tree->SetBranchAddress("dc21_v",&array_dc21_v);
 tree->SetBranchAddress("dc22_x1",&array_dc22_x1);
 tree->SetBranchAddress("dc22_x2",&array_dc22_x2);
 tree->SetBranchAddress("dc22_u",&array_dc22_u);
 tree->SetBranchAddress("dc22_v",&array_dc22_v);


// tree->SetBranchStatus("mass_corst1_BLD_3rd",1);
 tree->SetBranchStatus("f3",1);
 tree->SetBranchStatus("s2",1);
 tree->SetBranchStatus("sr0_xcw",1);
 tree->SetBranchStatus("eventheader",1);

 tree->SetBranchStatus("dc31_x1",1);
 tree->SetBranchStatus("dc31_x2",1);
 tree->SetBranchStatus("dc31_x3",1);
 tree->SetBranchStatus("dc31_x4",1);
 tree->SetBranchStatus("dc31_y1",1);
 tree->SetBranchStatus("dc31_y2",1);
 tree->SetBranchStatus("dc31_y3",1);
 tree->SetBranchStatus("dc31_y4",1);
 tree->SetBranchStatus("dc32_x1",1);
 tree->SetBranchStatus("dc32_x2",1);
 tree->SetBranchStatus("dc32_y1",1);
 tree->SetBranchStatus("dc32_y2",1);
 tree->SetBranchStatus("dc21_x1",1);
 tree->SetBranchStatus("dc21_x2",1);
 tree->SetBranchStatus("dc21_u",1);
 tree->SetBranchStatus("dc21_v",1);
 tree->SetBranchStatus("dc22_x1",1);
 tree->SetBranchStatus("dc22_x2",1);
 tree->SetBranchStatus("dc22_u",1);
 tree->SetBranchStatus("dc22_v",1);


 TH1D *dc31_x1 = new TH1D("dc31_x1_dtdl","dc31_x1_dtdl",260,-53,0);
 TH1D *dc31_x2 = new TH1D("dc31_x2_dtdl","dc31_x2_dtdl",260,-53,0);
 TH1D *dc31_x3 = new TH1D("dc31_x3_dtdl","dc31_x3_dtdl",260,-53,0);
 TH1D *dc31_x4 = new TH1D("dc31_x4_dtdl","dc31_x4_dtdl",260,-53,0);
 TH1D *dc31_y1 = new TH1D("dc31_y1_dtdl","dc31_y1_dtdl",260,-53,0);
 TH1D *dc31_y2 = new TH1D("dc31_y2_dtdl","dc31_y2_dtdl",260,-53,0);
 TH1D *dc31_y3 = new TH1D("dc31_y3_dtdl","dc31_y3_dtdl",260,-53,0);
 TH1D *dc31_y4 = new TH1D("dc31_y4_dtdl","dc31_y4_dtdl",260,-53,0);

 TH1D *dc32_x1 = new TH1D("dc32_x1_dtdl","dc32_x1_dtdl",370,-42,32);
 TH1D *dc32_x2 = new TH1D("dc32_x2_dtdl","dc32_x2_dtdl",370,-42,32);
 TH1D *dc32_y1 = new TH1D("dc32_y1_dtdl","dc32_y1_dtdl",370,-42,32);
 TH1D *dc32_y2 = new TH1D("dc32_y2_dtdl","dc32_y2_dtdl",370,-42,32);

 TH1D *dc21_x1 = new TH1D("dc21_x1_dtdl","dc21_x1_dtdl",800,-40,120);
 TH1D *dc21_x2 = new TH1D("dc21_x2_dtdl","dc21_x2_dtdl",800,-40,120);
 TH1D *dc21_u = new TH1D("dc21_u_dtdl","dc21_u_dtdl",800,-40,120);
 TH1D *dc21_v = new TH1D("dc21_v_dtdl","dc21_v_dtdl",800,-40,120);

 TH1D *dc22_x1 = new TH1D("dc22_x1_dtdl","dc22_x1_dtdl",800,-30,150);
 TH1D *dc22_x2 = new TH1D("dc22_x2_dtdl","dc22_x2_dtdl",800,-30,150);
 TH1D *dc22_u = new TH1D("dc22_u_dtdl","dc22_u_dtdl",800,-30,150);
 TH1D *dc22_v = new TH1D("dc22_v_dtdl","dc22_v_dtdl",800,-30,150);

 cout << "Making histgrams" <<endl;

 Int_t nData = tree->GetEntries();

 for(int i = 0; i < nData; i++){
   tree->GetEntry(i);

  art::TMWDCHitData *dc31_x1_tmp = (art::TMWDCHitData*) array_dc31_x1->UncheckedAt(0);
  art::TMWDCHitData *dc31_x2_tmp = (art::TMWDCHitData*) array_dc31_x2->UncheckedAt(0);
  art::TMWDCHitData *dc31_x3_tmp = (art::TMWDCHitData*) array_dc31_x3->UncheckedAt(0);
  art::TMWDCHitData *dc31_x4_tmp = (art::TMWDCHitData*) array_dc31_x4->UncheckedAt(0);
  art::TMWDCHitData *dc31_y1_tmp = (art::TMWDCHitData*) array_dc31_y1->UncheckedAt(0);
  art::TMWDCHitData *dc31_y2_tmp = (art::TMWDCHitData*) array_dc31_y2->UncheckedAt(0);
  art::TMWDCHitData *dc31_y3_tmp = (art::TMWDCHitData*) array_dc31_y3->UncheckedAt(0);
  art::TMWDCHitData *dc31_y4_tmp = (art::TMWDCHitData*) array_dc31_y4->UncheckedAt(0);
  art::TMWDCHitData *dc32_x1_tmp = (art::TMWDCHitData*) array_dc32_x1->UncheckedAt(0);
  art::TMWDCHitData *dc32_x2_tmp = (art::TMWDCHitData*) array_dc32_x2->UncheckedAt(0);
  art::TMWDCHitData *dc32_y1_tmp = (art::TMWDCHitData*) array_dc32_y1->UncheckedAt(0);
  art::TMWDCHitData *dc32_y2_tmp = (art::TMWDCHitData*) array_dc32_y2->UncheckedAt(0);
  art::TMWDCHitData *dc21_x1_tmp = (art::TMWDCHitData*) array_dc21_x1->UncheckedAt(0);
  art::TMWDCHitData *dc21_x2_tmp = (art::TMWDCHitData*) array_dc21_x2->UncheckedAt(0);
  art::TMWDCHitData *dc21_u_tmp  = (art::TMWDCHitData*) array_dc21_u->UncheckedAt(0);
  art::TMWDCHitData *dc21_v_tmp  = (art::TMWDCHitData*) array_dc21_v->UncheckedAt(0);
  art::TMWDCHitData *dc22_x1_tmp = (art::TMWDCHitData*) array_dc22_x1->UncheckedAt(0);
  art::TMWDCHitData *dc22_x2_tmp = (art::TMWDCHitData*) array_dc22_x2->UncheckedAt(0);
  art::TMWDCHitData *dc22_u_tmp  = (art::TMWDCHitData*) array_dc22_u->UncheckedAt(0);
  art::TMWDCHitData *dc22_v_tmp  = (art::TMWDCHitData*) array_dc22_v->UncheckedAt(0);


 Double_t dc31_x1_charge = dc31_x1_tmp->GetCharge(); 
 Double_t dc31_x2_charge = dc31_x2_tmp->GetCharge(); 
 Double_t dc31_x3_charge = dc31_x3_tmp->GetCharge(); 
 Double_t dc31_x4_charge = dc31_x4_tmp->GetCharge(); 
 Double_t dc31_y1_charge = dc31_y1_tmp->GetCharge(); 
 Double_t dc31_y2_charge = dc31_y2_tmp->GetCharge(); 
 Double_t dc31_y3_charge = dc31_y3_tmp->GetCharge(); 
 Double_t dc31_y4_charge = dc31_y4_tmp->GetCharge(); 
 Double_t dc32_x1_charge = dc32_x1_tmp->GetCharge(); 
 Double_t dc32_x2_charge = dc32_x2_tmp->GetCharge(); 
 Double_t dc32_y1_charge = dc32_y1_tmp->GetCharge(); 
 Double_t dc32_y2_charge = dc32_y2_tmp->GetCharge(); 
 Double_t dc21_x1_charge = dc21_x1_tmp->GetCharge(); 
 Double_t dc21_x2_charge = dc21_x2_tmp->GetCharge(); 
 Double_t dc21_u_charge  = dc21_u_tmp->GetCharge(); 
 Double_t dc21_v_charge  = dc21_v_tmp->GetCharge(); 
 Double_t dc22_x1_charge = dc22_x1_tmp->GetCharge(); 
 Double_t dc22_x2_charge = dc22_x2_tmp->GetCharge(); 
 Double_t dc22_u_charge  = dc22_u_tmp->GetCharge(); 
 Double_t dc22_v_charge  = dc22_v_tmp->GetCharge(); 

 Double_t dc31_x1_timing = dc31_x1_tmp->GetTiming(); 
 Double_t dc31_x2_timing = dc31_x2_tmp->GetTiming(); 
 Double_t dc31_x3_timing = dc31_x3_tmp->GetTiming(); 
 Double_t dc31_x4_timing = dc31_x4_tmp->GetTiming(); 
 Double_t dc31_y1_timing = dc31_y1_tmp->GetTiming(); 
 Double_t dc31_y2_timing = dc31_y2_tmp->GetTiming(); 
 Double_t dc31_y3_timing = dc31_y3_tmp->GetTiming(); 
 Double_t dc31_y4_timing = dc31_y4_tmp->GetTiming(); 
 Double_t dc32_x1_timing = dc32_x1_tmp->GetTiming(); 
 Double_t dc32_x2_timing = dc32_x2_tmp->GetTiming(); 
 Double_t dc32_y1_timing = dc32_y1_tmp->GetTiming(); 
 Double_t dc32_y2_timing = dc32_y2_tmp->GetTiming(); 
 Double_t dc21_x1_timing = dc21_x1_tmp->GetTiming(); 
 Double_t dc21_x2_timing = dc21_x2_tmp->GetTiming(); 
 Double_t dc21_u_timing  = dc21_u_tmp->GetTiming(); 
 Double_t dc21_v_timing  = dc21_v_tmp->GetTiming(); 
 Double_t dc22_x1_timing = dc22_x1_tmp->GetTiming(); 
 Double_t dc22_x2_timing = dc22_x2_tmp->GetTiming(); 
 Double_t dc22_u_timing  = dc22_u_tmp->GetTiming(); 
 Double_t dc22_v_timing  = dc22_v_tmp->GetTiming(); 

 if(TMath::Abs(dc31_x1_charge-500)<=500){
  dc31_x1->Fill(dc31_x1_timing);
 }
 if(TMath::Abs(dc31_x2_charge-500)<=500){
  dc31_x2->Fill(dc31_x2_timing);
 }
 if(TMath::Abs(dc31_x3_charge-500)<=500){
  dc31_x3->Fill(dc31_x3_timing);
 }
 if(TMath::Abs(dc31_x4_charge-500)<=500){
  dc31_x4->Fill(dc31_x4_timing);
 }
 if(TMath::Abs(dc31_y1_charge-500)<=500){
  dc31_y1->Fill(dc31_y1_timing);
 }
 if(TMath::Abs(dc31_y2_charge-500)<=500){
  dc31_y2->Fill(dc31_y2_timing);
 }
 if(TMath::Abs(dc31_y3_charge-500)<=500){
  dc31_y3->Fill(dc31_y3_timing);
 }
 if(TMath::Abs(dc31_y4_charge-500)<=500){
  dc31_y4->Fill(dc31_y4_timing);
 }
 
 if(TMath::Abs(dc32_x1_charge-500)<=500){
  dc32_x1->Fill(dc32_x1_timing);
 }
 if(TMath::Abs(dc32_x2_charge-500)<=500){
  dc32_x2->Fill(dc32_x2_timing);
 }
 if(TMath::Abs(dc32_y1_charge-500)<=500){
  dc32_y1->Fill(dc32_y1_timing);
 }
 if(TMath::Abs(dc32_y2_charge-500)<=500){
  dc32_y2->Fill(dc32_y2_timing);
 }

 if(TMath::Abs(dc21_x1_charge-60)<=60){
  dc21_x1->Fill(dc21_x1_timing);
 }
 if(TMath::Abs(dc21_x2_charge-60)<=60){
  dc21_x2->Fill(dc21_x2_timing);
 }
 if(TMath::Abs(dc21_u_charge-60)<=60){
  dc21_u->Fill(dc21_u_timing);
 }
 if(TMath::Abs(dc21_v_charge-60)<=60){
  dc21_v->Fill(dc21_v_timing);
 }

 if(TMath::Abs(dc22_x1_charge-60)<=60){
  dc22_x1->Fill(dc22_x1_timing);
 }
 if(TMath::Abs(dc22_x2_charge-60)<=60){
  dc22_x2->Fill(dc22_x2_timing);
 }
 if(TMath::Abs(dc22_u_charge-60)<=60){
  dc22_u->Fill(dc22_u_timing);
 }
 if(TMath::Abs(dc22_v_charge-60)<=60){
  dc22_v->Fill(dc22_v_timing);
 }

}

 cout << "Making hist was finished" << endl;

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/mwdc/dc31/dt2dl/%s",runnumber);

  gROOT->ProcessLine(mkdu);


  TH1D *hdc31x1 = (TH1D*)gROOT->FindObject("dc31_x1_dtdl");

  double totdc31x1=hdc31x1->Integral();
  hdc31x1->Scale(1./totdc31x1);

  char filenamedc31x1[50];
  sprintf(filenamedc31x1,"prm/mwdc/dc31/dt2dl/%s/x1.dat",runnumber);
  std::ofstream outfiledc31x1;
  outfiledc31x1.open(filenamedc31x1, std::ios::out);
  outfiledc31x1 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31x1 = hdc31x1->Integral(1,i);
     double adc31x1 =    hdc31x1->GetXaxis()->GetBinCenter(i);
     outfiledc31x1 << adc31x1 << " " << tdc31x1 << "\n";
   }
   outfiledc31x1.close();


 TH1D *hdc31x2 = (TH1D*)gROOT->FindObject("dc31_x2_dtdl");

  double totdc31x2=hdc31x2->Integral();
  hdc31x2->Scale(1./totdc31x2);

  char filenamedc31x2[50];
  sprintf(filenamedc31x2,"prm/mwdc/dc31/dt2dl/%s/x2.dat",runnumber);
  std::ofstream outfiledc31x2;
  outfiledc31x2.open(filenamedc31x2, std::ios::out);
  outfiledc31x2 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31x2 = hdc31x2->Integral(1,i);
     double adc31x2 =    hdc31x2->GetXaxis()->GetBinCenter(i);
     outfiledc31x2 << adc31x2 << " " << tdc31x2 << "\n";
   }
   outfiledc31x2.close();


 TH1D *hdc31x3 = (TH1D*)gROOT->FindObject("dc31_x3_dtdl");

  double totdc31x3=hdc31x3->Integral();
  hdc31x3->Scale(1./totdc31x3);

  char filenamedc31x3[50];
  sprintf(filenamedc31x3,"prm/mwdc/dc31/dt2dl/%s/x3.dat",runnumber);
  std::ofstream outfiledc31x3;
  outfiledc31x3.open(filenamedc31x3, std::ios::out);
  outfiledc31x3 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31x3 = hdc31x3->Integral(1,i);
     double adc31x3 =    hdc31x3->GetXaxis()->GetBinCenter(i);
     outfiledc31x3 << adc31x3 << " " << tdc31x3 << "\n";
   }
   outfiledc31x3.close();


 TH1D *hdc31x4 = (TH1D*)gROOT->FindObject("dc31_x4_dtdl");

  double totdc31x4=hdc31x4->Integral();
  hdc31x4->Scale(1./totdc31x4);

  char filenamedc31x4[50];
  sprintf(filenamedc31x4,"prm/mwdc/dc31/dt2dl/%s/x4.dat",runnumber);
  std::ofstream outfiledc31x4;
  outfiledc31x4.open(filenamedc31x4, std::ios::out);
  outfiledc31x4 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31x4 = hdc31x4->Integral(1,i);
     double adc31x4 =    hdc31x4->GetXaxis()->GetBinCenter(i);
     outfiledc31x4 << adc31x4 << " " << tdc31x4 << "\n";
   }
   outfiledc31x4.close();


 TH1D *hdc31y1 = (TH1D*)gROOT->FindObject("dc31_y1_dtdl");

  double totdc31y1=hdc31y1->Integral();
  hdc31y1->Scale(1./totdc31y1);

  char filenamedc31y1[50];
  sprintf(filenamedc31y1,"prm/mwdc/dc31/dt2dl/%s/y1.dat",runnumber);
  std::ofstream outfiledc31y1;
  outfiledc31y1.open(filenamedc31y1, std::ios::out);
  outfiledc31y1 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31y1 = hdc31y1->Integral(1,i);
     double adc31y1 =    hdc31y1->GetXaxis()->GetBinCenter(i);
     outfiledc31y1 << adc31y1 << " " << tdc31y1 << "\n";
   }
   outfiledc31y1.close();


 TH1D *hdc31y2 = (TH1D*)gROOT->FindObject("dc31_y2_dtdl");

  double totdc31y2=hdc31y2->Integral();
  hdc31y2->Scale(1./totdc31y2);

  char filenamedc31y2[50];
  sprintf(filenamedc31y2,"prm/mwdc/dc31/dt2dl/%s/y2.dat",runnumber);
  std::ofstream outfiledc31y2;
  outfiledc31y2.open(filenamedc31y2, std::ios::out);
  outfiledc31y2 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31y2 = hdc31y2->Integral(1,i);
     double adc31y2 =    hdc31y2->GetXaxis()->GetBinCenter(i);
     outfiledc31y2 << adc31y2 << " " << tdc31y2 << "\n";
   }
   outfiledc31y2.close();


 TH1D *hdc31y3 = (TH1D*)gROOT->FindObject("dc31_y3_dtdl");

  double totdc31y3=hdc31y3->Integral();
  hdc31y3->Scale(1./totdc31y3);

  char filenamedc31y3[50];
  sprintf(filenamedc31y3,"prm/mwdc/dc31/dt2dl/%s/y3.dat",runnumber);
  std::ofstream outfiledc31y3;
  outfiledc31y3.open(filenamedc31y3, std::ios::out);
  outfiledc31y3 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31y3 = hdc31y3->Integral(1,i);
     double adc31y3 =    hdc31y3->GetXaxis()->GetBinCenter(i);
     outfiledc31y3 << adc31y3 << " " << tdc31y3 << "\n";
   }
   outfiledc31y3.close();


 TH1D *hdc31y4 = (TH1D*)gROOT->FindObject("dc31_y4_dtdl");

  double totdc31y4=hdc31y4->Integral();
  hdc31y4->Scale(1./totdc31y4);

  char filenamedc31y4[50];
  sprintf(filenamedc31y4,"prm/mwdc/dc31/dt2dl/%s/y4.dat",runnumber);
  std::ofstream outfiledc31y4;
  outfiledc31y4.open(filenamedc31y4, std::ios::out);
  outfiledc31y4 << 260 << "\n";
  for(int i=1;i<261;i++){
     double tdc31y4 = hdc31y4->Integral(1,i);
     double adc31y4 =    hdc31y4->GetXaxis()->GetBinCenter(i);
     outfiledc31y4 << adc31y4 << " " << tdc31y4 << "\n";
   }
   outfiledc31y4.close();


  TH1D *hdc32x1 = (TH1D*)gROOT->FindObject("dc32_x1_dtdl");

  double totdc32x1=hdc32x1->Integral();
  hdc32x1->Scale(1./totdc32x1);

  char filenamedc32x1[50];
  sprintf(filenamedc32x1,"prm/mwdc/dc32/dt2dl/%s/x1.dat",runnumber);
  std::ofstream outfiledc32x1;
  outfiledc32x1.open(filenamedc32x1, std::ios::out);
  outfiledc32x1 << 370 << "\n";
  for(int i=1;i<371;i++){
     double tdc32x1 = hdc32x1->Integral(1,i);
     double adc32x1 =    hdc32x1->GetXaxis()->GetBinCenter(i);
     outfiledc32x1 << adc32x1 << " " << tdc32x1 << "\n";
   }
   outfiledc32x1.close();


 TH1D *hdc32x2 = (TH1D*)gROOT->FindObject("dc32_x2_dtdl");

  double totdc32x2=hdc32x2->Integral();
  hdc32x2->Scale(1./totdc32x2);

  char filenamedc32x2[50];
  sprintf(filenamedc32x2,"prm/mwdc/dc32/dt2dl/%s/x2.dat",runnumber);
  std::ofstream outfiledc32x2;
  outfiledc32x2.open(filenamedc32x2, std::ios::out);
  outfiledc32x2 << 370 << "\n";
  for(int i=1;i<371;i++){
     double tdc32x2 = hdc32x2->Integral(1,i);
     double adc32x2 =    hdc32x2->GetXaxis()->GetBinCenter(i);
     outfiledc32x2 << adc32x2 << " " << tdc32x2 << "\n";
   }
   outfiledc32x2.close();


 TH1D *hdc32y1 = (TH1D*)gROOT->FindObject("dc32_y1_dtdl");

  double totdc32y1=hdc32y1->Integral();
  hdc32y1->Scale(1./totdc32y1);

  char filenamedc32y1[50];
  sprintf(filenamedc32y1,"prm/mwdc/dc32/dt2dl/%s/y1.dat",runnumber);
  std::ofstream outfiledc32y1;
  outfiledc32y1.open(filenamedc32y1, std::ios::out);
  outfiledc32y1 << 370 << "\n";
  for(int i=1;i<371;i++){
     double tdc32y1 = hdc32y1->Integral(1,i);
     double adc32y1 =    hdc32y1->GetXaxis()->GetBinCenter(i);
     outfiledc32y1 << adc32y1 << " " << tdc32y1 << "\n";
   }
   outfiledc32y1.close();


 TH1D *hdc32y2 = (TH1D*)gROOT->FindObject("dc32_y2_dtdl");

  double totdc32y2=hdc32y2->Integral();
  hdc32y2->Scale(1./totdc32y2);

  char filenamedc32y2[50];
  sprintf(filenamedc32y2,"prm/mwdc/dc32/dt2dl/%s/y2.dat",runnumber);
  std::ofstream outfiledc32y2;
  outfiledc32y2.open(filenamedc32y2, std::ios::out);
  outfiledc32y2 << 370 << "\n";
  for(int i=1;i<371;i++){
     double tdc32y2 = hdc32y2->Integral(1,i);
     double adc32y2 =    hdc32y2->GetXaxis()->GetBinCenter(i);
     outfiledc32y2 << adc32y2 << " " << tdc32y2 << "\n";
   }
   outfiledc32y2.close();


  TH1D *hdc21x1 = (TH1D*)gROOT->FindObject("dc21_x1_dtdl");

  double totdc21x1=hdc21x1->Integral();
  hdc21x1->Scale(1./totdc21x1);

  char filenamedc21x1[50];
  sprintf(filenamedc21x1,"prm/mwdc/dc21/dt2dl/%s/x1.dat",runnumber);
  std::ofstream outfiledc21x1;
  outfiledc21x1.open(filenamedc21x1, std::ios::out);
  outfiledc21x1 << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc21x1 = hdc21x1->Integral(1,i);
     double adc21x1 =    hdc21x1->GetXaxis()->GetBinCenter(i);
     outfiledc21x1 << adc21x1 << " " << tdc21x1 << "\n";
   }
   outfiledc21x1.close();


 TH1D *hdc21x2 = (TH1D*)gROOT->FindObject("dc21_x2_dtdl");

  double totdc21x2=hdc21x2->Integral();
  hdc21x2->Scale(1./totdc21x2);

  char filenamedc21x2[50];
  sprintf(filenamedc21x2,"prm/mwdc/dc21/dt2dl/%s/x2.dat",runnumber);
  std::ofstream outfiledc21x2;
  outfiledc21x2.open(filenamedc21x2, std::ios::out);
  outfiledc21x2 << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc21x2 = hdc21x2->Integral(1,i);
     double adc21x2 =    hdc21x2->GetXaxis()->GetBinCenter(i);
     outfiledc21x2 << adc21x2 << " " << tdc21x2 << "\n";
   }
   outfiledc21x2.close();


 TH1D *hdc21u = (TH1D*)gROOT->FindObject("dc21_u_dtdl");

  double totdc21u=hdc21u->Integral();
  hdc21u->Scale(1./totdc21u);

  char filenamedc21u[50];
  sprintf(filenamedc21u,"prm/mwdc/dc21/dt2dl/%s/u.dat",runnumber);
  std::ofstream outfiledc21u;
  outfiledc21u.open(filenamedc21u, std::ios::out);
  outfiledc21u << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc21u = hdc21u->Integral(1,i);
     double adc21u =    hdc21u->GetXaxis()->GetBinCenter(i);
     outfiledc21u << adc21u << " " << tdc21u << "\n";
   }
   outfiledc21u.close();


 TH1D *hdc21v = (TH1D*)gROOT->FindObject("dc21_v_dtdl");

  double totdc21v=hdc21v->Integral();
  hdc21v->Scale(1./totdc21v);

  char filenamedc21v[50];
  sprintf(filenamedc21v,"prm/mwdc/dc21/dt2dl/%s/v.dat",runnumber);
  std::ofstream outfiledc21v;
  outfiledc21v.open(filenamedc21v, std::ios::out);
  outfiledc21v << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc21v = hdc21v->Integral(1,i);
     double adc21v =    hdc21v->GetXaxis()->GetBinCenter(i);
     outfiledc21v << adc21v << " " << tdc21v << "\n";
   }
   outfiledc21v.close();



  TH1D *hdc22x1 = (TH1D*)gROOT->FindObject("dc22_x1_dtdl");

  double totdc22x1=hdc22x1->Integral();
  hdc22x1->Scale(1./totdc22x1);

  char filenamedc22x1[50];
  sprintf(filenamedc22x1,"prm/mwdc/dc22/dt2dl/%s/x1.dat",runnumber);
  std::ofstream outfiledc22x1;
  outfiledc22x1.open(filenamedc22x1, std::ios::out);
  outfiledc22x1 << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc22x1 = hdc22x1->Integral(1,i);
     double adc22x1 =    hdc22x1->GetXaxis()->GetBinCenter(i);
     outfiledc22x1 << adc22x1 << " " << tdc22x1 << "\n";
   }
   outfiledc22x1.close();


 TH1D *hdc22x2 = (TH1D*)gROOT->FindObject("dc22_x2_dtdl");

  double totdc22x2=hdc22x2->Integral();
  hdc22x2->Scale(1./totdc22x2);

  char filenamedc22x2[50];
  sprintf(filenamedc22x2,"prm/mwdc/dc22/dt2dl/%s/x2.dat",runnumber);
  std::ofstream outfiledc22x2;
  outfiledc22x2.open(filenamedc22x2, std::ios::out);
  outfiledc22x2 << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc22x2 = hdc22x2->Integral(1,i);
     double adc22x2 =    hdc22x2->GetXaxis()->GetBinCenter(i);
     outfiledc22x2 << adc22x2 << " " << tdc22x2 << "\n";
   }
   outfiledc22x2.close();


 TH1D *hdc22u = (TH1D*)gROOT->FindObject("dc22_u_dtdl");

  double totdc22u=hdc22u->Integral();
  hdc22u->Scale(1./totdc22u);

  char filenamedc22u[50];
  sprintf(filenamedc22u,"prm/mwdc/dc22/dt2dl/%s/u.dat",runnumber);
  std::ofstream outfiledc22u;
  outfiledc22u.open(filenamedc22u, std::ios::out);
  outfiledc22u << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc22u = hdc22u->Integral(1,i);
     double adc22u =    hdc22u->GetXaxis()->GetBinCenter(i);
     outfiledc22u << adc22u << " " << tdc22u << "\n";
   }
   outfiledc22u.close();


 TH1D *hdc22v = (TH1D*)gROOT->FindObject("dc22_v_dtdl");

  double totdc22v=hdc22v->Integral();
  hdc22v->Scale(1./totdc22v);

  char filenamedc22v[50];
  sprintf(filenamedc22v,"prm/mwdc/dc22/dt2dl/%s/v.dat",runnumber);
  std::ofstream outfiledc22v;
  outfiledc22v.open(filenamedc22v, std::ios::out);
  outfiledc22v << 800 << "\n";
  for(int i=1;i<801;i++){
     double tdc22v = hdc22v->Integral(1,i);
     double adc22v =    hdc22v->GetXaxis()->GetBinCenter(i);
     outfiledc22v << adc22v << " " << tdc22v << "\n";
   }
   outfiledc22v.close();










}

