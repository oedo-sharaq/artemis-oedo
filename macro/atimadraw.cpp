#include <iostream>
#include <vector>

using namespace std;
void atimadraw(){
  ifstream ifs;
  Double_t eloss,eremain;
  vector <Double_t> Eloss{};
  vector <Double_t> Eremain{};
  Int_t i=0;
  //ifs.open("/home/sh19post/art_analysis/user/li/atima/p_in_Si_725um.dat");
  //ifs.open("/home/sh19post/art_analysis/user/li/atima/p_in_Si_423um.dat");
  //ifs.open("/home/sh19post/art_analysis/user/li/atima/p_in_Si_305um.dat");
  TGraph* g[2];
  for (i = 0; i<=1; i++){
    if (i ==0)
      ifs.open("/home/sh19post/art_analysis/user/li/atima/p_in_Si_300um.dat");
    if (i == 1)
      ifs.open("/home/sh19post/art_analysis/user/li/atima/d_in_Si_300um.dat");
    while (ifs >> eremain >> eloss){
      Eremain.emplace_back(eremain);
      Eloss.emplace_back(eloss);
      //cout << eremain << endl;
    }
    ifs.close();
    g[i] = new TGraph(Eremain.size(),&Eremain[0],&Eloss[0]);
    g[i]->SetLineColor(2);
    g[i]->SetLineWidth(2);
    g[i]->Draw("same");
    Eremain.clear();
    Eloss.clear();
  }
}
