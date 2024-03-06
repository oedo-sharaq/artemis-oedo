{
  int j;
  cin >> j; 
  for (int i = 1; i <= 2; i++){
    tree->Draw(Form("tina3.fEcsi>>h%d(50,0,20)",i),Form("abs(csiS%d.fCharge-%d)<125",j,125+(i-1)*250));
  }
  gROOT->ProcessLine("z 1 2");
  gROOT->ProcessLine("ht 1");
  gROOT->ProcessLine("ht 2");
}
