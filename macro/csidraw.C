{
  int j;
  cin >> j; 
  for (int i = 1; i <= 12; i++){
    tree->Draw(Form("tina3.fEcsi>>h%d(30,0,20)",i),Form("abs(csiS%d.fCharge-%d)<125&&tgate",j,125+(i-1)*250));
  }
  gROOT->ProcessLine("z 3 4");
  for (int j = 1; j<=12; j++){
    gROOT->ProcessLine(Form("ht %d",j));
  }
}
