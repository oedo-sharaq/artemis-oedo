void DqDx(){

//set dir  

  printf("set runname\n");
  char runname[10];
  scanf("%s",runname);
  char runname2[10];
  sprintf(runname2,"%s",runname);
  char mkdu[30];
  sprintf(mkdu,".! mkdir -p prm/srppac/sr91/dq2dx/%s",runname);

  gROOT->ProcessLine(mkdu);

//upstream

  TH1D *hsrux = (TH1D*)gROOT->FindObject("sr91_x_q0q1");

  double totsrux=hsrux->Integral();
  hsrux->Scale(1./totsrux);

  char filenamesrux[50];
  sprintf(filenamesrux,"prm/srppac/sr91/dq2dx/%s/xc0.dat",runname);
  std::ofstream outfilesrux;
  outfilesrux.open(filenamesrux, std::ios::out);
  outfilesrux << 250 << "\n";
  for(int i=1;i<251;i++){
     double tsrux = hsrux->Integral(1,i);
     double asrux =    0.25/250 *i;
     outfilesrux << asrux << " " << tsrux << "\n";
   }
   outfilesrux.close();


  TH1D *hsruy = (TH1D*)gROOT->FindObject("sr91_y_q0q1");

  double totsruy=hsruy->Integral();
  hsruy->Scale(1./totsruy);

  char filenamesruy[50];
  sprintf(filenamesruy,"prm/srppac/sr91/dq2dx/%s/yc0.dat",runname);
  std::ofstream outfilesruy;
  outfilesruy.open(filenamesruy, std::ios::out);
  outfilesruy << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsruy = hsruy->Integral(1,i);
     double asruy =    0.4/400 *i;
     outfilesruy << asruy << " " << tsruy << "\n";
   }
   outfilesruy.close();



//downstream

  char mkdd[30];
  sprintf(mkdd,".! mkdir -p prm/srppac/sr92/dq2dx/%s",runname);

  gROOT->ProcessLine(mkdd);


  TH1D *hsrdx = (TH1D*)gROOT->FindObject("sr92_x_q0q1");

  double totsrdx=hsrdx->Integral();
  hsrdx->Scale(1./totsrdx);

  char filenamesrdx[50];
  sprintf(filenamesrdx,"prm/srppac/sr92/dq2dx/%s/xc0.dat",runname);
  std::ofstream outfilesrdx;
  outfilesrdx.open(filenamesrdx, std::ios::out);
  outfilesrdx << 300 << "\n";
  for(int i=1;i<301;i++){
     double tsrdx = hsrdx->Integral(1,i);
     double asrdx =    0.3/300 *i;
     outfilesrdx << asrdx << " " << tsrdx << "\n";
   }
   outfilesrdx.close();


  TH1D *hsrdy = (TH1D*)gROOT->FindObject("sr92_y_q0q1");

  double totsrdy=hsrdy->Integral();
  hsrdy->Scale(1./totsrdy);

  char filenamesrdy[50];
  sprintf(filenamesrdy,"prm/srppac/sr92/dq2dx/%s/yc0.dat",runname);
  std::ofstream outfilesrdy;
  outfilesrdy.open(filenamesrdy, std::ios::out);
  outfilesrdy << 400 << "\n";
  for(int i=1;i<401;i++){
     double tsrdy = hsrdy->Integral(1,i);
     double asrdy =    0.4/400 *i;
     outfilesrdy << asrdy << " " << tsrdy << "\n";
   }
   outfilesrdy.close();





 }
