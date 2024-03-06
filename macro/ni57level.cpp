#include <iostream>

void ni57level(){
  vector <Double_t> theta;
  vector <Double_t> Ep;
  Double_t val1,val2,val3,val4;
  ifstream ifs;

  const Int_t N = 3;
  TGraph* g[10];
  int num = 1;
  for (int i = 1; i<=N; i++){
    Int_t l = 0;
    ifs.open(Form("/home/sh19post/art_analysis/user/li/LISEcute/dpkinematics_Ex%d.txt",i-1));
    while (ifs >> val1 >> val2 >> val3 >> val4){
      theta.push_back(val3);
      Ep.push_back(val4);
      l++;
    }
    g[num] = new TGraph(l,&theta[0],&Ep[0]);
    g[num]->SetLineColor(2);
    g[num]->SetLineWidth(2);
    g[num]->Draw("same");
    num++;
    theta.clear();
    Ep.clear();
    ifs.close();
  }
}
