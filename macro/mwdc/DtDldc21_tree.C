void DtDldc21_tree(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/mwdc/dc21/dt2dl/%s",runnumber);

  gROOT->ProcessLine(mkdu);


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

}
