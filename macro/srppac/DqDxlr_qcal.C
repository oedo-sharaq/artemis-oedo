void DqDxlr_qcal(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/srppac/sr0/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdu);

//upstream L

  TH1D *hsruxl = (TH1D*)gROOT->FindObject("sr0_x_q0qlqcal");

  double totsruxl=hsruxl->Integral();
  hsruxl->Scale(1./totsruxl);

  char filenamesruxl[50];
  sprintf(filenamesruxl,"prm/srppac/sr0/dq2dx/%s/xcl_qcal.dat",runnumber);
  std::ofstream outfilesruxl;
  outfilesruxl.open(filenamesruxl, std::ios::out);
  outfilesruxl << 900 << "\n";
  for(int i=1;i<901;i++){
     double tsruxl = hsruxl->Integral(1,i);
     double asruxl =    0.9/900 *i;
     outfilesruxl << asruxl << " " << tsruxl << "\n";
   }
   outfilesruxl.close();


//  TH1D *hsruyl = (TH1D*)gROOT->FindObject("sr0_y_q0ql");
//
//  double totsruyl=hsruyl->Integral();
//  hsruyl->Scale(1./totsruyl);
//
//  char filenamesruyl[50];
//  sprintf(filenamesruyl,"prm/srppac/sr0/dq2dx/%s/ycl.dat",runnumber);
//  std::ofstream outfilesruyl;
//  outfilesruyl.open(filenamesruyl, std::ios::out);
//  outfilesruyl << 800 << "\n";
//  for(int i=1;i<801;i++){
//     double tsruyl = hsruyl->Integral(1,i);
//     double asruyl =    0.8/800 *i;
//     outfilesruyl << asruyl << " " << tsruyl << "\n";
//   }
//   outfilesruyl.close();


//upstream R

  TH1D *hsruxr = (TH1D*)gROOT->FindObject("sr0_x_q0qrqcal");

  double totsruxr=hsruxr->Integral();
  hsruxr->Scale(1./totsruxr);

  char filenamesruxr[50];
  sprintf(filenamesruxr,"prm/srppac/sr0/dq2dx/%s/xcr_qcal.dat",runnumber);
  std::ofstream outfilesruxr;
  outfilesruxr.open(filenamesruxr, std::ios::out);
  outfilesruxr << 900 << "\n";
  for(int i=1;i<901;i++){
     double tsruxr = hsruxr->Integral(1,i);
     double asruxr =    0.9/900 *i;
     outfilesruxr << asruxr << " " << tsruxr << "\n";
   }
   outfilesruxr.close();


//  TH1D *hsruyr = (TH1D*)gROOT->FindObject("sr0_y_q0qr");
//
//  double totsruyr=hsruyr->Integral();
//  hsruyr->Scale(1./totsruyr);
//
//  char filenamesruyr[50];
//  sprintf(filenamesruyr,"prm/srppac/sr0/dq2dx/%s/ycr.dat",runnumber);
//  std::ofstream outfilesruyr;
//  outfilesruyr.open(filenamesruyr, std::ios::out);
//  outfilesruyr << 800 << "\n";
//  for(int i=1;i<801;i++){
//     double tsruyr = hsruyr->Integral(1,i);
//     double asruyr =    0.8/800 *i;
//     outfilesruyr << asruyr << " " << tsruyr << "\n";
//   }
//   outfilesruyr.close();


}
