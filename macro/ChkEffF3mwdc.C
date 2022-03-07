//void ChkFffF3mwdc() {
{
// gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 0");
 
  double eff31 = 1. - eff_pla->GetBinContent(1)/eff_pla->GetEntries();
 
  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 1");
 
  double eff32  = 1. - eff_pla->GetBinContent(1)/eff_pla->GetEntries();

  cout <<  "# --- Efficiency of F3 MWDC --- #" << endl;
  cout <<  "dc31 :" <<  eff31 << endl;
  cout <<  "dc32 :" <<  eff32 << endl;
}

