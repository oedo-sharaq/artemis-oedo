//void ChkFffF3mwdc()
{
// gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 23");
 
  double eff31x1 = 1. - eff_x1->GetBinContent(1)/eff_x1->GetEntries();
  double eff31x2 = 1. - eff_x2->GetBinContent(1)/eff_x2->GetEntries();
  double eff31y1 = 1. - eff_y1->GetBinContent(1)/eff_y1->GetEntries();
  double eff31y2 = 1. - eff_y2->GetBinContent(1)/eff_y2->GetEntries();
  double eff31x3 = 1. - eff_x3->GetBinContent(1)/eff_x3->GetEntries();
  double eff31x4 = 1. - eff_x4->GetBinContent(1)/eff_x4->GetEntries();
  double eff31y3 = 1. - eff_y3->GetBinContent(1)/eff_y3->GetEntries();
  double eff31y4 = 1. - eff_y4->GetBinContent(1)/eff_y4->GetEntries();

  cout <<  "# --- Efficiency of DC31 --- #" << endl;
  cout <<  "# x1 x2 y1 y2 x3 x4 y3 y4" <<  endl;
  cout << eff31x1 << " " 
       << eff31x2 << " "
       << eff31y1 << " "
       << eff31y2 << " "
       << eff31x3 << " "
       << eff31x4 << " "
       << eff31y3 << " "
       << eff31y4 << " " << endl;

  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 24");
 
  double eff32x1 = 1. - eff_x1->GetBinContent(1)/eff_x1->GetEntries();
  double eff32x2 = 1. - eff_x2->GetBinContent(1)/eff_x2->GetEntries();
  double eff32y1 = 1. - eff_y1->GetBinContent(1)/eff_y1->GetEntries();
  double eff32y2 = 1. - eff_y2->GetBinContent(1)/eff_y2->GetEntries();

  cout <<  "# --- Efficiency of DC32 --- #" << endl;
  cout <<  "# x1 x2 y1 y2" <<  endl;
  cout << eff32x1 << " " 
       << eff32x2 << " "
       << eff32y1 << " "
       << eff32y2 << " " << endl;

  gROOT->ProcessLine("cd");

}

