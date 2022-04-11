void chksreff(){

   TH1D *huxent = (TH1D*)gROOT->FindObject("src1_x_ent"); 
   TH1D *huyent = (TH1D*)gROOT->FindObject("src1_y_ent"); 
   TH1D *hdxent = (TH1D*)gROOT->FindObject("src2_x_ent"); 
   TH1D *hdyent = (TH1D*)gROOT->FindObject("src2_y_ent"); 


   double uxeff0 = 1.- huxent->GetBinContent(1)/huxent->GetEntries();
   double uxeff1 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2))/huxent->GetEntries();
   double uxeff2 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2)+huxent->GetBinContent(3))/huxent->GetEntries();
  
   double uyeff0 = 1.- huyent->GetBinContent(1)/huyent->GetEntries();
   double uyeff1 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2))/huyent->GetEntries();
   double uyeff2 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2)+huyent->GetBinContent(3))/huyent->GetEntries();

   double dxeff0 = 1.- hdxent->GetBinContent(1)/hdxent->GetEntries();
   double dxeff1 = 1.-(hdxent->GetBinContent(1)+hdxent->GetBinContent(2))/hdxent->GetEntries();
   double dxeff2 = 1.-(hdxent->GetBinContent(1)+hdxent->GetBinContent(2)+hdxent->GetBinContent(3))/hdxent->GetEntries();
  
   double dyeff0 = 1.- hdyent->GetBinContent(1)/hdyent->GetEntries();
   double dyeff1 = 1.-(hdyent->GetBinContent(1)+hdyent->GetBinContent(2))/hdyent->GetEntries();
   double dyeff2 = 1.-(hdyent->GetBinContent(1)+hdyent->GetBinContent(2)+hdyent->GetBinContent(3))/hdyent->GetEntries();

 
    cout << "# -- Efficiency of X upstream --" << endl;
    cout << "src1xeff0:"  << "  " <<  uxeff0  << endl;
    cout << "src1x1eff1:" << "  " <<  uxeff1 << endl;
    cout << "src1x1eff2:" << "  " <<  uxeff2 << endl;
  
  
    cout << "# -- Efficiency of Y upstream --" << endl;
    cout << "src1yeff0:" << "  " <<  uyeff0 << endl;
    cout << "src1yeff1:" << "  " <<  uyeff1 << endl;
    cout << "src1yeff2:" << "  " <<  uyeff2 << endl;
  
  
    cout << "# -- Efficiency of X downstream --" << endl;
    cout << "src2xeff0:" << "  " <<  dxeff0 << endl;
    cout << "src2xeff1:" << "  " <<  dxeff1 << endl;
    cout << "src2xeff2:" << "  " <<  dxeff2 << endl;
  
  
    cout << "# -- Efficiency of Y downstream --" << endl;
    cout << "src2xeff0:" << "  " <<  dyeff0 << endl;
    cout << "src2yeff1:" << "  " <<  dyeff1 << endl;
    cout << "src2yeff2:" << "  " <<  dyeff2 << endl;
   
 
}

