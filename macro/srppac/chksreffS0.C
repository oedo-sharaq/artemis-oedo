void chksreffS0(){

   TH1D *huxent = (TH1D*)gROOT->FindObject("sr0_x_ent"); 
   TH1D *huyent = (TH1D*)gROOT->FindObject("sr0_y_ent"); 
  
   double uxeff0 = 1.- huxent->GetBinContent(1)/huxent->GetEntries();
  double uxeff1 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2))/huxent->GetEntries();
   double uxeff2 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2)+huxent->GetBinContent(3))/huxent->GetEntries();
  
   double uyeff0 = 1.- huyent->GetBinContent(1)/huyent->GetEntries();
   double uyeff1 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2))/huyent->GetEntries();
   double uyeff2 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2)+huyent->GetBinContent(3))/huyent->GetEntries();


  cout << "# -- Efficiency of X upstream --" << endl;
  cout << "sr0xeff0:"  << "  " <<  uxeff0  << endl;
    cout << "sr0x1eff1:" << "  " <<  uxeff1 << endl;
    cout << "sr0x1eff2:" << "  " <<  uxeff2 << endl;
  
  
    cout << "# -- Efficiency of Y upstream --" << endl;
    cout << "sr0yeff0:" << "  " <<  uyeff0 << endl;
    cout << "sr0yeff1:" << "  " <<  uyeff1 << endl;
    cout << "sr0yeff2:" << "  " <<  uyeff2 << endl;
  
  
  
 
}

