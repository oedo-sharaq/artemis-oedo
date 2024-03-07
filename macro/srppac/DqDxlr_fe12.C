void DqDxlr_fe12(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/srppac/src1/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdu);

//upstream L

  TH1D *hsruxl = (TH1D*)gROOT->FindObject("src1_x_q0ql");

  double totsruxl=hsruxl->Integral();
  hsruxl->Scale(1./totsruxl);

  char filenamesruxl[50];
  sprintf(filenamesruxl,"prm/srppac/src1/dq2dx/%s/xcl.dat",runnumber);
  std::ofstream outfilesruxl;
  outfilesruxl.open(filenamesruxl, std::ios::out);
  outfilesruxl << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsruxl = hsruxl->Integral(1,i);
     double asruxl =    0.7/700 *i;
     outfilesruxl << asruxl << " " << tsruxl << "\n";
   }
   outfilesruxl.close();


  TH1D *hsruyl = (TH1D*)gROOT->FindObject("src1_y_q0ql");

  double totsruyl=hsruyl->Integral();
  hsruyl->Scale(1./totsruyl);

  char filenamesruyl[50];
  sprintf(filenamesruyl,"prm/srppac/src1/dq2dx/%s/ycl.dat",runnumber);
  std::ofstream outfilesruyl;
  outfilesruyl.open(filenamesruyl, std::ios::out);
  outfilesruyl << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsruyl = hsruyl->Integral(1,i);
     double asruyl =    0.7/700 *i;
     outfilesruyl << asruyl << " " << tsruyl << "\n";
   }
   outfilesruyl.close();


//upstream R

  TH1D *hsruxr = (TH1D*)gROOT->FindObject("src1_x_q0qr");

  double totsruxr=hsruxr->Integral();
  hsruxr->Scale(1./totsruxr);

  char filenamesruxr[50];
  sprintf(filenamesruxr,"prm/srppac/src1/dq2dx/%s/xcr.dat",runnumber);
  std::ofstream outfilesruxr;
  outfilesruxr.open(filenamesruxr, std::ios::out);
  outfilesruxr << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsruxr = hsruxr->Integral(1,i);
     double asruxr =    0.7/700 *i;
     outfilesruxr << asruxr << " " << tsruxr << "\n";
   }
   outfilesruxr.close();


  TH1D *hsruyr = (TH1D*)gROOT->FindObject("src1_y_q0qr");

  double totsruyr=hsruyr->Integral();
  hsruyr->Scale(1./totsruyr);

  char filenamesruyr[50];
  sprintf(filenamesruyr,"prm/srppac/src1/dq2dx/%s/ycr.dat",runnumber);
  std::ofstream outfilesruyr;
  outfilesruyr.open(filenamesruyr, std::ios::out);
  outfilesruyr << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsruyr = hsruyr->Integral(1,i);
     double asruyr =    0.7/700 *i;
     outfilesruyr << asruyr << " " << tsruyr << "\n";
   }
   outfilesruyr.close();



  char mkdd[30];
  sprintf(mkdd,".! mkdir -p prm/srppac/src2/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdu);

//upstream L

  TH1D *hsrdxl = (TH1D*)gROOT->FindObject("src2_x_q0ql");

  double totsrdxl=hsrdxl->Integral();
  hsrdxl->Scale(1./totsrdxl);

  char filenamesrdxl[50];
  sprintf(filenamesrdxl,"prm/srppac/src2/dq2dx/%s/xcl.dat",runnumber);
  std::ofstream outfilesrdxl;
  outfilesrdxl.open(filenamesrdxl, std::ios::out);
  outfilesrdxl << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsrdxl = hsrdxl->Integral(1,i);
     double asrdxl =    0.7/700 *i;
     outfilesrdxl << asrdxl << " " << tsrdxl << "\n";
   }
   outfilesrdxl.close();


  TH1D *hsrdyl = (TH1D*)gROOT->FindObject("src2_y_q0ql");

  double totsrdyl=hsrdyl->Integral();
  hsrdyl->Scale(1./totsrdyl);

  char filenamesrdyl[50];
  sprintf(filenamesrdyl,"prm/srppac/src2/dq2dx/%s/ycl.dat",runnumber);
  std::ofstream outfilesrdyl;
  outfilesrdyl.open(filenamesrdyl, std::ios::out);
  outfilesrdyl << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsrdyl = hsrdyl->Integral(1,i);
     double asrdyl =    0.7/700 *i;
     outfilesrdyl << asrdyl << " " << tsrdyl << "\n";
   }
   outfilesrdyl.close();


//upstream R

  TH1D *hsrdxr = (TH1D*)gROOT->FindObject("src2_x_q0qr");

  double totsrdxr=hsrdxr->Integral();
  hsrdxr->Scale(1./totsrdxr);

  char filenamesrdxr[50];
  sprintf(filenamesrdxr,"prm/srppac/src2/dq2dx/%s/xcr.dat",runnumber);
  std::ofstream outfilesrdxr;
  outfilesrdxr.open(filenamesrdxr, std::ios::out);
  outfilesrdxr << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsrdxr = hsrdxr->Integral(1,i);
     double asrdxr =    0.7/700 *i;
     outfilesrdxr << asrdxr << " " << tsrdxr << "\n";
   }
   outfilesrdxr.close();


  TH1D *hsrdyr = (TH1D*)gROOT->FindObject("src2_y_q0qr");

  double totsrdyr=hsrdyr->Integral();
  hsrdyr->Scale(1./totsrdyr);

  char filenamesrdyr[50];
  sprintf(filenamesrdyr,"prm/srppac/src2/dq2dx/%s/ycr.dat",runnumber);
  std::ofstream outfilesrdyr;
  outfilesrdyr.open(filenamesrdyr, std::ios::out);
  outfilesrdyr << 700 << "\n";
  for(int i=1;i<701;i++){
     double tsrdyr = hsrdyr->Integral(1,i);
     double asrdyr =    0.7/700 *i;
     outfilesrdyr << asrdyr << " " << tsrdyr << "\n";
   }
   outfilesrdyr.close();







}
