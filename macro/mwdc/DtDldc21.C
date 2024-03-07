void DtDldc21(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/mwdc/dc21/dt2dl/%s",runnumber);

  gROOT->ProcessLine(mkdu);


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

}
