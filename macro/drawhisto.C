{
  int num;
  cin >> num;
  gROOT->ProcessLine("z 3 4");
  gROOT->ProcessLine(Form("ht %d",num));
  for (int i = 1; i<12; i++){
    gROOT->ProcessLine("hn");
  }

}
