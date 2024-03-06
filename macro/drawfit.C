{
  double slope;
  double inter;
  cin >> inter;
  cin >> slope;
  TF1 *f1 =new TF1("f1","pol1");
  f1->SetParameters(inter,slope);
  f1->SetRange(0,4000);
  f1->Draw("same");
}
