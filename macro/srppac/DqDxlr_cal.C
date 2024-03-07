void DqDxlr_cal(){

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

  TH1D *hsruxl = (TH1D*)gROOT->FindObject("sr0_x_q0ql_qcal");

  double totsruxl=hsruxl->Integral();
  hsruxl->Scale(1./totsruxl);

  char filenamesruxl[50];
  sprintf(filenamesruxl,"prm/srppac/sr0/dq2dx/%s/xcl_qcal.dat",runnumber);
  std::ofstream outfilesruxl;
  outfilesruxl.open(filenamesruxl, std::ios::out);
  outfilesruxl << 990 << "\n";
  for(int i=1;i<991;i++){
     double tsruxl = hsruxl->Integral(1,i);
     double asruxl =    0.99/990 *i;
     outfilesruxl << asruxl << " " << tsruxl << "\n";
   }
   outfilesruxl.close();


//  TH1D *hsruyl = (TH1D*)gROOT->FindObject("sr0_y_q0ql_qcal");
//
//  double totsruyl=hsruyl->Integral();
//  hsruyl->Scale(1./totsruyl);
//
//  char filenamesruyl[50];
//  sprintf(filenamesruyl,"prm/srppac/sr0/dq2dx/%s/ycl_qcal.dat",runnumber);
//  std::ofstream outfilesruyl;
//  outfilesruyl.open(filenamesruyl, std::ios::out);
//  outfilesruyl << 700 << "\n";
//  for(int i=1;i<701;i++){
//     double tsruyl = hsruyl->Integral(1,i);
//     double asruyl =    0.7/700 *i;
//     outfilesruyl << asruyl << " " << tsruyl << "\n";
//   }
//   outfilesruyl.close();


//upstream R

  TH1D *hsruxr = (TH1D*)gROOT->FindObject("sr0_x_q0qr_qcal");

  double totsruxr=hsruxr->Integral();
  hsruxr->Scale(1./totsruxr);

  char filenamesruxr[50];
  sprintf(filenamesruxr,"prm/srppac/sr0/dq2dx/%s/xcr_qcal.dat",runnumber);
  std::ofstream outfilesruxr;
  outfilesruxr.open(filenamesruxr, std::ios::out);
  outfilesruxr << 990 << "\n";
  for(int i=1;i<991;i++){
     double tsruxr = hsruxr->Integral(1,i);
     double asruxr =    0.99/990 *i;
     outfilesruxr << asruxr << " " << tsruxr << "\n";
   }
   outfilesruxr.close();


//  TH1D *hsruyr = (TH1D*)gROOT->FindObject("sr0_y_q0qr_cal");
//
//  double totsruyr=hsruyr->Integral();
//  hsruyr->Scale(1./totsruyr);
//
//  char filenamesruyr[50];
//  sprintf(filenamesruyr,"prm/srppac/sr0/dq2dx/%s/ycr_cal.dat",runnumber);
//  std::ofstream outfilesruyr;
//  outfilesruyr.open(filenamesruyr, std::ios::out);
//  outfilesruyr << 700 << "\n";
//  for(int i=1;i<701;i++){
//     double tsruyr = hsruyr->Integral(1,i);
//     double asruyr =    0.7/700 *i;
//     outfilesruyr << asruyr << " " << tsruyr << "\n";
//   }
//   outfilesruyr.close();


}
