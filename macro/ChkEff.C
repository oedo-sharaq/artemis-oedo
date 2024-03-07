void ChkEff(){

  // DC31
  double eff31x1 = 1. - eff_dc31_x1->GetBinContent(1)/eff_dc31_x1->GetEntries();
  double eff31x2 = 1. - eff_dc31_x2->GetBinContent(1)/eff_dc31_x2->GetEntries();
  double eff31y1 = 1. - eff_dc31_y1->GetBinContent(1)/eff_dc31_y1->GetEntries();
  double eff31y2 = 1. - eff_dc31_y2->GetBinContent(1)/eff_dc31_y2->GetEntries();
  double eff31x3 = 1. - eff_dc31_x3->GetBinContent(1)/eff_dc31_x3->GetEntries();
  double eff31x4 = 1. - eff_dc31_x4->GetBinContent(1)/eff_dc31_x4->GetEntries();
  double eff31y3 = 1. - eff_dc31_y3->GetBinContent(1)/eff_dc31_y3->GetEntries();
  double eff31y4 = 1. - eff_dc31_y4->GetBinContent(1)/eff_dc31_y4->GetEntries();

  // DC32
  double eff32x1 = 1. - eff_dc32_x1->GetBinContent(1)/eff_dc32_x1->GetEntries();
  double eff32x2 = 1. - eff_dc32_x2->GetBinContent(1)/eff_dc32_x2->GetEntries();
  double eff32y1 = 1. - eff_dc32_y1->GetBinContent(1)/eff_dc32_y1->GetEntries();
  double eff32y2 = 1. - eff_dc32_y2->GetBinContent(1)/eff_dc32_y2->GetEntries();

  //DC21
  double eff21x1 = 1. - eff_dc21_x1->GetBinContent(1)/eff_dc21_x1->GetEntries();
  double eff21x2 = 1. - eff_dc21_x2->GetBinContent(1)/eff_dc21_x2->GetEntries();
  double eff21u  = 1. - eff_dc21_u->GetBinContent(1)/eff_dc21_u->GetEntries();
  double eff21v  = 1. - eff_dc21_v->GetBinContent(1)/eff_dc21_v->GetEntries();

  //DC22
  double eff22x1 = 1. - eff_dc22_x1->GetBinContent(1)/eff_dc22_x1->GetEntries();
  double eff22x2 = 1. - eff_dc22_x2->GetBinContent(1)/eff_dc22_x2->GetEntries();
  double eff22u  = 1. - eff_dc22_u->GetBinContent(1)/eff_dc22_u->GetEntries();
  double eff22v  = 1. - eff_dc22_v->GetBinContent(1)/eff_dc22_v->GetEntries();

  //SRPPAC-S0
  TH1D *huxent = (TH1D*)gROOT->FindObject("sr0_x_ent"); 
  TH1D *huyent = (TH1D*)gROOT->FindObject("sr0_y_ent"); 
  
  double uxeff0 = 1.- huxent->GetBinContent(1)/huxent->GetEntries();
  double uxeff1 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2))/huxent->GetEntries();
  double uxeff2 = 1.-(huxent->GetBinContent(1)+huxent->GetBinContent(2)+huxent->GetBinContent(3))/huxent->GetEntries();
  
  double uyeff0 = 1.- huyent->GetBinContent(1)/huyent->GetEntries();
  double uyeff1 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2))/huyent->GetEntries();
  double uyeff2 = 1.-(huyent->GetBinContent(1)+huyent->GetBinContent(2)+huyent->GetBinContent(3))/huyent->GetEntries();

  //

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
  cout << " " << endl;

  cout <<  "# --- Efficiency of DC32 --- #" << endl;
  cout <<  "# x1 x2 y1 y2" <<  endl;
  cout << eff32x1 << " " 
       << eff32x2 << " "
       << eff32y1 << " "
       << eff32y2 << " " << endl;
  cout << " " << endl;

  cout <<  "# --- Efficiency of DC21 --- #" << endl;
  cout <<  "# x1 x2 u v" <<  endl;
  cout << eff21x1 << " " 
       << eff21x2 << " "
       << eff21u  << " "
       << eff21v  << " " << endl;
  cout << " " << endl;

  cout <<  "# --- Efficiency of DC22 --- #" << endl;
  cout <<  "# x1 x2 u v" <<  endl;
  cout << eff22x1 << " " 
       << eff22x2 << " "
       << eff22u  << " "
       << eff22v  << " " << endl;
  cout << " " << endl;

  cout <<  "# --- Efficiency of SR0 --- #" << endl;
  cout <<  "# x(q0) x(q1) x(q2) y(q0) y(q1) y(q2)" <<  endl;
  cout << uxeff0 << " " 
       << uxeff1 << " "
       << uxeff2 << " "
       << uyeff0 << " " 
       << uyeff1 << " " 
       << uyeff2 << " " << endl;
  cout << " " << endl;



  cout << eff31x1 << " " 
       << eff31x2 << " "
       << eff31y1 << " "
       << eff31y2 << " "
       << eff31x3 << " "
       << eff31x4 << " "
       << eff31y3 << " "
       << eff31y4 << " "
       << eff32x1 << " "
       << eff32x2 << " "
       << eff32y1 << " "
       << eff32y2 << " "
       << eff21x1 << " "
       << eff21x2 << " "
       << eff21u  << " "
       << eff21v  << " "
       << eff22x1 << " "
       << eff22x2 << " "
       << eff22u  << " "
       << eff22v  << " "
       << uxeff0 << " " 
       << uxeff1 << " "
       << uxeff2 << " "
       << uyeff0 << " " 
       << uyeff1 << " " 
       << uyeff2 << " " << endl;

}
