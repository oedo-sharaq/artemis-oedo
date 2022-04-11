void DqDxlr(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
//  char runname[10];
 // sprintf(runname2,"%s",runname);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/srppac/sru/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdu);

  char mkdd[30];
  sprintf(mkdd,".! mkdir -p prm/srppac/srd/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdd);


//upstream L

  TH1D *hsruxl = (TH1D*)gROOT->FindObject("srppacu_x_q0ql");

  double totsruxl=hsruxl->Integral();
  hsruxl->Scale(1./totsruxl);

  char filenamesruxl[50];
  sprintf(filenamesruxl,"prm/srppac/sru/dq2dx/%s/xcl.dat",runnumber);
  std::ofstream outfilesruxl;
  outfilesruxl.open(filenamesruxl, std::ios::out);
  outfilesruxl << 600 << "\n";
  for(int i=1;i<601;i++){
     double tsruxl = hsruxl->Integral(1,i);
     double asruxl =    0.6/600 *i;
     outfilesruxl << asruxl << " " << tsruxl << "\n";
   }
   outfilesruxl.close();


  TH1D *hsruyl = (TH1D*)gROOT->FindObject("srppacu_y_q0ql");

  double totsruyl=hsruyl->Integral();
  hsruyl->Scale(1./totsruyl);

  char filenamesruyl[50];
  sprintf(filenamesruyl,"prm/srppac/sru/dq2dx/%s/ycl.dat",runnumber);
  std::ofstream outfilesruyl;
  outfilesruyl.open(filenamesruyl, std::ios::out);
  outfilesruyl << 500 << "\n";
  for(int i=1;i<501;i++){
     double tsruyl = hsruyl->Integral(1,i);
     double asruyl =    0.5/500 *i;
     outfilesruyl << asruyl << " " << tsruyl << "\n";
   }
   outfilesruyl.close();


//upstream R

  TH1D *hsruxr = (TH1D*)gROOT->FindObject("srppacu_x_q0qr");

  double totsruxr=hsruxr->Integral();
  hsruxr->Scale(1./totsruxr);

  char filenamesruxr[50];
  sprintf(filenamesruxr,"prm/srppac/sru/dq2dx/%s/xcr.dat",runnumber);
  std::ofstream outfilesruxr;
  outfilesruxr.open(filenamesruxr, std::ios::out);
  outfilesruxr << 600 << "\n";
  for(int i=1;i<601;i++){
     double tsruxr = hsruxr->Integral(1,i);
     double asruxr =    0.6/600 *i;
     outfilesruxr << asruxr << " " << tsruxr << "\n";
   }
   outfilesruxr.close();


  TH1D *hsruyr = (TH1D*)gROOT->FindObject("srppacu_y_q0qr");

  double totsruyr=hsruyr->Integral();
  hsruyr->Scale(1./totsruyr);

  char filenamesruyr[50];
  sprintf(filenamesruyr,"prm/srppac/sru/dq2dx/%s/ycr.dat",runnumber);
  std::ofstream outfilesruyr;
  outfilesruyr.open(filenamesruyr, std::ios::out);
  outfilesruyr << 500 << "\n";
  for(int i=1;i<501;i++){
     double tsruyr = hsruyr->Integral(1,i);
     double asruyr =    0.5/500 *i;
     outfilesruyr << asruyr << " " << tsruyr << "\n";
   }
   outfilesruyr.close();



//downstream L

  TH1D *hsrdxl = (TH1D*)gROOT->FindObject("srppacd_x_q0ql");

  double totsrdxl=hsrdxl->Integral();
  hsrdxl->Scale(1./totsrdxl);

  char filenamesrdxl[50];
  sprintf(filenamesrdxl,"prm/srppac/srd/dq2dx/%s/xcl.dat",runnumber);
  std::ofstream outfilesrdxl;
  outfilesrdxl.open(filenamesrdxl, std::ios::out);
  outfilesrdxl << 600 << "\n";
  for(int i=1;i<601;i++){
     double tsrdxl = hsrdxl->Integral(1,i);
     double asrdxl =    0.6/600 *i;
     outfilesrdxl << asrdxl << " " << tsrdxl << "\n";
   }
   outfilesrdxl.close();


  TH1D *hsrdyl = (TH1D*)gROOT->FindObject("srppacd_y_q0ql");

  double totsrdyl=hsrdyl->Integral();
  hsrdyl->Scale(1./totsrdyl);

  char filenamesrdyl[50];
  sprintf(filenamesrdyl,"prm/srppac/srd/dq2dx/%s/ycl.dat",runnumber);
  std::ofstream outfilesrdyl;
  outfilesrdyl.open(filenamesrdyl, std::ios::out);
  outfilesrdyl << 500 << "\n";
  for(int i=1;i<501;i++){
     double tsrdyl = hsrdyl->Integral(1,i);
     double asrdyl =    0.5/500 *i;
     outfilesrdyl << asrdyl << " " << tsrdyl << "\n";
   }
   outfilesrdyl.close();

//downstream R

  TH1D *hsrdxr = (TH1D*)gROOT->FindObject("srppacd_x_q0qr");

  double totsrdxr=hsrdxr->Integral();
  hsrdxr->Scale(1./totsrdxr);

  char filenamesrdxr[50];
  sprintf(filenamesrdxr,"prm/srppac/srd/dq2dx/%s/xcr.dat",runnumber);
  std::ofstream outfilesrdxr;
  outfilesrdxr.open(filenamesrdxr, std::ios::out);
  outfilesrdxr << 600 << "\n";
  for(int i=1;i<601;i++){
     double tsrdxr = hsrdxr->Integral(1,i);
     double asrdxr =    0.6/600 *i;
     outfilesrdxr << asrdxr << " " << tsrdxr << "\n";
   }
   outfilesrdxr.close();


  TH1D *hsrdyr = (TH1D*)gROOT->FindObject("srppacd_y_q0qr");

  double totsrdyr=hsrdyr->Integral();
  hsrdyr->Scale(1./totsrdyr);

  char filenamesrdyr[50];
  sprintf(filenamesrdyr,"prm/srppac/srd/dq2dx/%s/ycr.dat",runnumber);
  std::ofstream outfilesrdyr;
  outfilesrdyr.open(filenamesrdyr, std::ios::out);
  outfilesrdyr << 500 << "\n";
  for(int i=1;i<501;i++){
     double tsrdyr = hsrdyr->Integral(1,i);
     double asrdyr =    0.5/500 *i;
     outfilesrdyr << asrdyr << " " << tsrdyr << "\n";
   }
   outfilesrdyr.close();




}
