{
  for (int i = 1; i<=36; i++){
    tree->Draw(Form("sr1.fXcor2:t%d>>tof%d(200,130,180,500,-200,200)",i,i),"fe9.pid56Ni","colz");
  }
  for (int i = 1; i<=36; i++){
    tree->Draw(Form("0.0830631619726*sr1.fXcor2+0.996544284577*t%d>>rot%d(200,130,180)",i,i),"fe9.pid56Ni","colz");
  }
  for (int i = 1; i<=36; i++){
    tree->Draw(Form("t%d>>t%d(200,0,300)",i,i),"fe9.pid56Ni","colz");
  }
  TH1F* rot[37];
  TH1F* t[37];
  t[1]=t1;
  t[2]=t2;
  t[3]=t3;
  t[4]=t4;
  t[5]=t5;
  t[6]=t6;
  t[7]=t7;
  t[8]=t8;
  t[9]=t9;
  t[10]=t10;
  t[11]=t11;
  t[12]=t12;
  t[13]=t13;
  t[14]=t14;
  t[15]=t15;
  t[16]=t16;
  t[17]=t17;
  t[18]=t18;
  t[19]=t19;
  t[20]=t20;
  t[21]=t21;
  t[22]=t22;
  t[23]=t23;
  t[24]=t24;
  t[25]=t25;
  t[26]=t26;
  t[27]=t27;
  t[28]=t28;
  t[29]=t29;
  t[30]=t30;
  t[31]=t31;
  t[32]=t32;
  t[33]=t33;
  t[34]=t34;
  t[35]=t35;
  t[36]=t36;
  rot[1]=rot1;
  rot[2]=rot2;
  rot[3]=rot3;
  rot[4]=rot4;
  rot[5]=rot5;
  rot[6]=rot6;
  rot[7]=rot7;
  rot[8]=rot8;
  rot[9]=rot9;
  rot[10]=rot10;
  rot[11]=rot11;
  rot[12]=rot12;
  rot[13]=rot13;
  rot[14]=rot14;
  rot[15]=rot15;
  rot[16]=rot16;
  rot[17]=rot17;
  rot[18]=rot18;
  rot[19]=rot19;
  rot[20]=rot20;
  rot[21]=rot21;
  rot[22]=rot22;
  rot[23]=rot23;
  rot[24]=rot24;
  rot[25]=rot25;
  rot[26]=rot26;
  rot[27]=rot27;
  rot[28]=rot28;
  rot[29]=rot29;
  rot[30]=rot30;
  rot[31]=rot31;
  rot[32]=rot32;
  rot[33]=rot33;
  rot[34]=rot34;
  rot[35]=rot35;
  rot[36]=rot36;
  TF1 *f1 = new TF1("f1","gaus(0)+gaus(3)+gaus(6)");
  f1->SetParameters(500,143,1,500,148,1,500,153,1);
  TF1* g1 = new TF1("g1","gaus");
  vector <Double_t> sigmatof{};
  vector <Double_t> sigmapid{};
  for (int i = 2; i<=36; i++){
    t[i]->Fit("g1","q","",0,300);
    sigmatof.emplace_back(g1->GetParameter(2));
    rot[i]->Fit("f1","q","",135,155);
    sigmapid.emplace_back(f1->GetParameter(5));
    cout<< i << " " << f1->GetParameter(5) << endl;
  }
  TGraph* g = new TGraph(36,&sigmatof[0],&sigmapid[0]);
  g->Draw("ap*");
}

