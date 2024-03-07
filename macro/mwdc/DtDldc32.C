void DtDldc32(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/mwdc/dc32/dt2dl/%s",runnumber);

  gROOT->ProcessLine(mkdu);


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

}
