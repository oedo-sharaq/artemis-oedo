{
  int j;
  cin >> j; 
  for (int i = 1; i <= 10; i++){
    tree->Draw(Form("tina2.fCsIE>>h%d(30,0,20)",i),Form("abs(csiT%d.fCharge-%d)<125",j,125+(i-1)*250));
  }
  gROOT->ProcessLine("z 2 5");
  for (int j = 1; j<=10; j++){
    gROOT->ProcessLine(Form("ht %d",j));
  }
}
