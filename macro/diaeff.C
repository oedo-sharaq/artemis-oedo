void chkdiaeff(){

   TH1D *dia3ent = (TH1D*)gROOT->FindObject("dia3_ent"); 
   TH1D *dias2ent = (TH1D*)gROOT->FindObject("dias2_ent"); 

   double dia3eff = 1.- dia3ent->GetBinContent(1)/dia3ent->GetEntries();
   double dias2eff = 1.- dias2ent->GetBinContent(1)/dias2ent->GetEntries();

   cout << " --- Efficiency of Diamond --- " << endl;
   cout << "DIAMOND F3 Efficiency:"  << "  " <<  dia3eff  << endl;
   cout << "DIAMOND S2 Efficiency:"  << "  " <<  dias2eff << endl;
 
}
