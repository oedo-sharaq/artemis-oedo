void ChkFffF5mwdc() {

// gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 6");
  
  double eff51 = 1. - eff_pla->GetBinContent(1)/eff_pla->GetEntries();
 
  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd 7");
 
  double eff52 = 1. - eff_pla->GetBinContent(1)/eff_pla->GetEntries();

  cout <<  "# --- Efficiency of F5 MWDC --- #" << endl;
  cout <<  "dc51 :" <<  eff51 << endl;
  cout <<  "dc52 :" <<  eff52 << endl;

}

