#include <iostream>
#include <vector>
struct peaks{
  int Npeaks;
  int b;
};

peaks test(){
    int Npeaks = 2;
    peaks result = {2,3};
    return result;
}

double peaksearch(TH1F* hin, double thre){
  int N = hin->GetNbinsX();  
  return 0;
}


void search(){
  test();
  //cout << test << endl;
  //cout << peaksearch(aa,0.2) << endl;;
}
