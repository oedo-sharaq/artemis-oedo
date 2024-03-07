void DtDldc31(){

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

}
