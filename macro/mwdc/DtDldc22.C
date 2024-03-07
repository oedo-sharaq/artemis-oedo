void DtDldc22(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/mwdc/dc22/dt2dl/%s",runnumber);

  gROOT->ProcessLine(mkdu);


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
