void chkplaeff(){

   TH1D *s2plaent = (TH1D*)gROOT->FindObject("s2pla_ent"); 

   double s2plaeff = 1.- s2plaent->GetBinContent(1)/s2plaent->GetEntries();

   cout << " --- Efficiency of S2 pla --- " << endl;
   cout << "Plastic S2 Efficiency:"  << "  " <<  s2plaeff  << endl;
 
}
