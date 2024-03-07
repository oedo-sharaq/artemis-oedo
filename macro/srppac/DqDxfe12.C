void DqDxfe12(){

//set dir  

  printf("set runnumber\n");
  char runnumber[10];
  scanf("%s",runnumber);
  char runnumber2[10];
  sprintf(runnumber2,"%s",runnumber);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/srppac/src1/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdu);

//upstream

  TH1D *hsrux = (TH1D*)gROOT->FindObject("src1_x_q0q1");

  double totsrux=hsrux->Integral();
  hsrux->Scale(1./totsrux);

  char filenamesrux[50];
  sprintf(filenamesrux,"prm/srppac/src1/dq2dx/%s/xc0.dat",runnumber);
  std::ofstream outfilesrux;
  outfilesrux.open(filenamesrux, std::ios::out);
//  outfilesrux << 400 << "\n";
//  for(int i=1;i<401;i++){
//     double tsrux = hsrux->Integral(1,i);
//     double asrux =    0.4/400 *i;
//     outfilesrux << asrux << " " << tsrux << "\n";
//   }
  outfilesrux << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsrux = hsrux->Integral(1,i);
     double asrux =    0.4/400 *i;
     outfilesrux << asrux << " " << tsrux << "\n";
   }
 
   outfilesrux.close();


  TH1D *hsruy = (TH1D*)gROOT->FindObject("src1_y_q0q1");

  double totsruy=hsruy->Integral();
  hsruy->Scale(1./totsruy);

  char filenamesruy[50];
  sprintf(filenamesruy,"prm/srppac/src1/dq2dx/%s/yc0.dat",runnumber);
  std::ofstream outfilesruy;
  outfilesruy.open(filenamesruy, std::ios::out);
//  outfilesruy << 400 << "\n";
//  for(int i=1;i<401;i++){
//     double tsruy = hsruy->Integral(1,i);
//     double asruy =    0.4/400 *i;
//     outfilesruy << asruy << " " << tsruy << "\n";
//   }
  outfilesruy << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsruy = hsruy->Integral(1,i);
     double asruy =    0.4/400 *i;
     outfilesruy << asruy << " " << tsruy << "\n";
   }
 

   outfilesruy.close();



//downstream

  char mkdd[30];
  sprintf(mkdd,".! mkdir -p prm/srppac/src2/dq2dx/%s",runnumber);

  gROOT->ProcessLine(mkdd);


  TH1D *hsrdx = (TH1D*)gROOT->FindObject("src2_x_q0q1");

  double totsrdx=hsrdx->Integral();
  hsrdx->Scale(1./totsrdx);

  char filenamesrdx[50];
  sprintf(filenamesrdx,"prm/srppac/src2/dq2dx/%s/xc0.dat",runnumber);
  std::ofstream outfilesrdx;
  outfilesrdx.open(filenamesrdx, std::ios::out);
//  outfilesrdx << 400 << "\n";
//  for(int i=1;i<401;i++){
//     double tsrdx = hsrdx->Integral(1,i);
//     double asrdx =    0.4/400 *i;
//     outfilesrdx << asrdx << " " << tsrdx << "\n";
//   }
  outfilesrdx << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsrdx = hsrdx->Integral(1,i);
     double asrdx =    0.4/400 *i;
     outfilesrdx << asrdx << " " << tsrdx << "\n";
   }
 

   outfilesrdx.close();


  TH1D *hsrdy = (TH1D*)gROOT->FindObject("src2_y_q0q1");

  double totsrdy=hsrdy->Integral();
  hsrdy->Scale(1./totsrdy);

  char filenamesrdy[50];
  sprintf(filenamesrdy,"prm/srppac/src2/dq2dx/%s/yc0.dat",runnumber);
  std::ofstream outfilesrdy;
  outfilesrdy.open(filenamesrdy, std::ios::out);
//  outfilesrdy << 400 << "\n";
//  for(int i=1;i<401;i++){
//     double tsrdy = hsrdy->Integral(1,i);
//     double asrdy =    0.4/400 *i;
//     outfilesrdy << asrdy << " " << tsrdy << "\n";
//   }
  outfilesrdy << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsrdy = hsrdy->Integral(1,i);
     double asrdy =    0.4/400 *i;
     outfilesrdy << asrdy << " " << tsrdy << "\n";
   }
 

   outfilesrdy.close();





}
