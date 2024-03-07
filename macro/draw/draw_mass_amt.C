
//void draw_mass_amt(){
{
   gROOT->ProcessLine("zone");
 // TCanvas *Lw = new TCanvas("Lw","Lw",800,800);
//  TCanvas *c1 = new TCanvas("c1","c1");
//  Lw->SetGrid();
//  Lw->SetGridx();
//  Lw->SetGridy();
//  TPad *pad = new TPad("pad","mass",0,0,1.,1,-1,1,0);
//  pad->Draw();

// TH1F *hist_ca = new TH1F("hist_ca","mass_AMT_ca",310000,1.70,2.01); 
// TH1F *hist_sc = new TH1F("hist_sc","mass_AMT_sc",310000,1.70,2.01); 
// TH1F *hist_ti = new TH1F("hist_ti","mass_AMT_ti",310000,1.70,2.01); 
// TH1F *hist_v  = new TH1F("hist_v","mass_AMT_v",310000,1.70,2.01); 
// TH1F *hist_cr = new TH1F("hist_cr","mass_AMT_cr",310000,1.70,2.01); 
// TH1F *hist_mn = new TH1F("hist_mn","mass_AMT_mn",310000,1.70,2.01); 
// TH1F *hist_fe = new TH1F("hist_fe","mass_AMT_fe",310000,1.70,2.01); 
// TH1F *hist_co = new TH1F("hist_co","mass_AMT_co",310000,1.70,2.01); 
// TH1F *hist_ni = new TH1F("hist_ni","mass_AMT_ni",310000,1.70,2.01); 

// TH1F *hist_ca = new TH1F("hist_ca","mass_AMT_ca",100000,1.70,1.80); 
// TH1F *hist_sc = new TH1F("hist_sc","mass_AMT_sc",100000,1.70,1.80); 
// TH1F *hist_ti = new TH1F("hist_ti","mass_AMT_ti",100000,1.70,1.80); 
// TH1F *hist_v  = new TH1F("hist_v","mass_AMT_v",100000,1.70,1.80); 
// TH1F *hist_cr = new TH1F("hist_cr","mass_AMT_cr",100000,1.70,1.80); 
// TH1F *hist_mn = new TH1F("hist_mn","mass_AMT_mn",100000,1.70,1.80); 
// TH1F *hist_fe = new TH1F("hist_fe","mass_AMT_fe",100000,1.70,1.80); 
// TH1F *hist_co = new TH1F("hist_co","mass_AMT_co",100000,1.70,1.80); 
// TH1F *hist_ni = new TH1F("hist_ni","mass_AMT_ni",100000,1.70,1.80); 

// TH1F *hist_ca = new TH1F("hist_ca","mass_AMT_ca",100000,1.80,1.90); 
// TH1F *hist_sc = new TH1F("hist_sc","mass_AMT_sc",100000,1.80,1.90); 
// TH1F *hist_ti = new TH1F("hist_ti","mass_AMT_ti",100000,1.80,1.90); 
// TH1F *hist_v  = new TH1F("hist_v","mass_AMT_v",100000,1.80,1.90); 
// TH1F *hist_cr = new TH1F("hist_cr","mass_AMT_cr",100000,1.80,1.90); 
// TH1F *hist_mn = new TH1F("hist_mn","mass_AMT_mn",100000,1.80,1.90); 
// TH1F *hist_fe = new TH1F("hist_fe","mass_AMT_fe",100000,1.80,1.90); 
// TH1F *hist_co = new TH1F("hist_co","mass_AMT_co",100000,1.80,1.90); 
// TH1F *hist_ni = new TH1F("hist_ni","mass_AMT_ni",100000,1.80,1.90); 
//
// TH1F *hist_ca = new TH1F("hist_ca","mass_AMT_ca",110000,1.90,2.011); 
// TH1F *hist_sc = new TH1F("hist_sc","mass_AMT_sc",110000,1.90,2.011); 
// TH1F *hist_ti = new TH1F("hist_ti","mass_AMT_ti",110000,1.90,2.011); 
// TH1F *hist_v  = new TH1F("hist_v","mass_AMT_v",110000,1.90,2.011); 
// TH1F *hist_cr = new TH1F("hist_cr","mass_AMT_cr",110000,1.90,2.011); 
// TH1F *hist_mn = new TH1F("hist_mn","mass_AMT_mn",110000,1.90,2.011); 
// TH1F *hist_fe = new TH1F("hist_fe","mass_AMT_fe",110000,1.90,2.011); 
// TH1F *hist_co = new TH1F("hist_co","mass_AMT_co",110000,1.90,2.011); 
// TH1F *hist_ni = new TH1F("hist_ni","mass_AMT_ni",110000,1.90,2.011); 

 TH2F *hist_zaq = new TH2F("hist_zaq","mass_AMT_zaq",110000,1.7,1.8,500,18,30); 

 TH1F *hist_ca = new TH1F("hist_ca","mass_AMT_ca",110000,1.74,1.76); 
 TH1F *hist_sc = new TH1F("hist_sc","mass_AMT_sc",110000,1.74,1.76); 
 TH1F *hist_ti = new TH1F("hist_ti","mass_AMT_ti",110000,1.74,1.76); 
 TH1F *hist_v  = new TH1F("hist_v","mass_AMT_v",110000,1.74,1.76); 
 TH1F *hist_cr = new TH1F("hist_cr","mass_AMT_cr",110000,1.74,1.76); 
 TH1F *hist_mn = new TH1F("hist_mn","mass_AMT_mn",110000,1.74,1.76); 
 TH1F *hist_fe = new TH1F("hist_fe","mass_AMT_fe",110000,1.74,1.76); 
 TH1F *hist_co = new TH1F("hist_co","mass_AMT_co",110000,1.74,1.76); 
 TH1F *hist_ni = new TH1F("hist_ni","mass_AMT_ni",110000,1.74,1.76); 

 hist_ca->GetYaxis()->SetRangeUser(0,52);
 hist_sc->GetYaxis()->SetRangeUser(0,52);
 hist_ti->GetYaxis()->SetRangeUser(0,52);
 hist_v->GetYaxis()->SetRangeUser(0,52);
 hist_cr->GetYaxis()->SetRangeUser(0,52);
 hist_fe->GetYaxis()->SetRangeUser(0,52);
 hist_co->GetYaxis()->SetRangeUser(0,52);
 hist_ni->GetYaxis()->SetRangeUser(0,52);


//// Fill Ni
for(int i=0; i < 51; i++){
 hist_ni->Fill(1.71443577); //unknown
 hist_ni->Fill(1.74978006); //unknown
 hist_ni->Fill(1.78503492); //unknown
 hist_ni->Fill(1.82043492);
 hist_ni->Fill(1.85573090);
 hist_ni->Fill(1.89117408);
 hist_ni->Fill(1.92651849);
 hist_ni->Fill(1.96200051);
 hist_ni->Fill(1.99738615);
 hist_ni->Fill(2.03301699);
}

 hist_ni->SetLineColor(28);
 hist_ni->SetFillColor(28);
 hist_ni->Draw();


//// Fill Co

for(int i=0; i < 46; i++){
//for(int i=0; i < 51; i++){
 hist_co->Fill(1.81387889); //unknown
 hist_co->Fill(1.85060539);
 hist_co->Fill(1.88725476);
 hist_co->Fill(1.92401331);
 hist_co->Fill(1.96071972);
 hist_co->Fill(1.99754401);
 hist_co->Fill(2.03434169);
}

 hist_co->SetLineColor(1);
 hist_co->SetFillColor(1);
 hist_co->Draw("same");


//// Fill Fe

for(int i=0; i < 41; i++){
//for(int i=0; i < 51; i++){
 hist_fe->Fill(1.73081708); //unknown
 hist_fe->Fill(1.76873359); //unknown
 hist_fe->Fill(1.80685077); //unknown
 hist_fe->Fill(1.84486307);
 hist_fe->Fill(1.88304627);
 hist_fe->Fill(1.92110626);
 hist_fe->Fill(1.95933190);
 hist_fe->Fill(1.99745722);
 hist_fe->Fill(2.03581077);
}

 hist_fe->SetLineColor(2);
 hist_fe->SetFillColor(2);
 hist_fe->Draw("same");


//// Fill Mn

for(int i=0; i < 36; i++){
//for(int i=0; i < 51; i++){
 hist_mn->Fill(1.83891945);
 hist_mn->Fill(1.87848359);
 hist_mn->Fill(1.91819472);
 hist_mn->Fill(1.95783732);
 hist_mn->Fill(1.99762231);
 hist_mn->Fill(2.03738113);
}

 hist_mn->SetLineColor(3);
 hist_mn->SetFillColor(3);
 hist_mn->Draw("same");


//// Fill Cr

for(int i=0; i < 31; i++){
//for(int i=0; i < 51; i++){
 hist_cr->Fill(1.74976851); //unknown
 hist_cr->Fill(1.79103125); //unknown
 hist_cr->Fill(1.83218575);
 hist_cr->Fill(1.87358000);
 hist_cr->Fill(1.91480106);
 hist_cr->Fill(1.95624000);
 hist_cr->Fill(1.99753728);
 hist_cr->Fill(2.03909161);
}

 hist_cr->Fill(4);
 hist_cr->Draw("same");


//// Fill V

for(int i=0; i < 26; i++){
//for(int i=0; i < 51; i++){
 hist_v->Fill(1.86818142);
 hist_v->Fill(1.91138485);
 hist_v->Fill(1.95448605);
 hist_v->Fill(1.99772208);
 hist_v->Fill(2.04097018);
}

 hist_v->SetLineColor(6);
 hist_v->SetFillColor(6);
 hist_v->Draw("same");


//// Fill Ti

for(int i=0; i < 21; i++){
//for(int i=0; i < 51; i++){
 hist_ti->Fill(1.77230183); //unknown
 hist_ti->Fill(1.81719569);
 hist_ti->Fill(1.86232290);
 hist_ti->Fill(1.90731844);
 hist_ti->Fill(1.95256747);
 hist_ti->Fill(1.99762028);
 hist_ti->Fill(2.04300350);
}
 hist_ti->SetLineColor(7);
 hist_ti->SetFillColor(7);
 hist_ti->Draw("same");


//// Fill Sc

for(int i=0; i < 16; i++){
//for(int i=0; i < 51; i++){
 hist_sc->Fill(1.80875903); //unknown 
 hist_sc->Fill(1.85587081);
 hist_sc->Fill(1.90316521);
 hist_sc->Fill(1.95036921);
 hist_sc->Fill(1.99781043);
 hist_sc->Fill(2.04522156);
}
 hist_sc->SetLineColor(8);
 hist_sc->SetFillColor(8);
 hist_sc->Draw("same");


//// Fill Ca

for(int i=0; i < 11; i++){
//for(int i=0; i < 51; i++){
 hist_ca->Fill(1.79910620);
 hist_ca->Fill(1.84874731);
 hist_ca->Fill(1.89826838);
 hist_ca->Fill(1.94798796);
 hist_ca->Fill(1.99758196);
 hist_ca->Fill(2.04756631);
}
 hist_ca->SetLineColor(9);
 hist_ca->SetFillColor(9);
 hist_ca->Draw("same");


//for(int i=0; i < 51; i++){
// hist_ni->Fill(1.7149825); //unknown
// hist_ni->Fill(1.7053275); //unknown
// hist_ni->Fill(1.7855815); //unknown
// hist_ni->Fill(1.8209815);
// hist_ni->Fill(1.8562775);
// hist_ni->Fill(1.8917215);
// hist_ni->Fill(1.9270655);
// hist_ni->Fill(1.9625475);
// hist_ni->Fill(1.9979335);
//}
//
// hist_ni->SetLineColor(28);
// hist_ni->SetFillColor(28);
// hist_ni->Draw("same");

// c1->RedrawAxis();

  

//  TLine *l36Ca = new TLine(1.799653,0,1.799653,1);
//  TLine *l37Ca = new TLine(1.849294,0,1.849294,1);
//  TLine *l38Ca = new TLine(1.898815,0,1.898815,1);
//  TLine *l39Ca = new TLine(1.948535,0,1.948535,1);
//  TLine *l40Ca = new TLine(1.998129,0,1.998129,1);
//
//  TLine *l38Sc = new TLine(1.809306,0,1.809306,1); //unknown 
//  TLine *l39Sc = new TLine(1.856418,0,1.856418,1);
//  TLine *l40Sc = new TLine(1.903712,0,1.903712,1);
//  TLine *l41Sc = new TLine(1.950916,0,1.950916,1);
//  TLine *l42Sc = new TLine(1.999835,0,1.999835,1);
//
//  TLine *l39Ti = new TLine(1.772849,0,1.772849,1); //unknown
//  TLine *l40Ti = new TLine(1.817743,0,1.817743,1);
//  TLine *l41Ti = new TLine(1.862870,0,1.862870,1);
//  TLine *l42Ti = new TLine(1.907865,0,1.907865,1);
//  TLine *l43Ti = new TLine(1.953114,0,1.953114,1);
//  TLine *l44Ti = new TLine(1.998167,0,1.998167,1);
//
//  TLine *l43V  = new TLine(1.867033,0,1.867033,1);
//  TLine *l44V  = new TLine(1.911932,0,1.911932,1);
//  TLine *l45V  = new TLine(1.955033,0,1.955033,1);
//  TLine *l46V  = new TLine(1.998269,0,1.998269,1);
//
//  TLine *l42Cr = new TLine(1.750315,0,1.750315,1); //unknown
//  TLine *l43Cr = new TLine(1.791578,0,1.791578,1); //unknown
//  TLine *l44Cr = new TLine(1.832733,0,1.832733,1);
//  TLine *l45Cr = new TLine(1.874127,0,1.874127,1);
//  TLine *l46Cr = new TLine(1.915348,0,1.915348,1);
//  TLine *l47Cr = new TLine(1.956787,0,1.956787,1);
//  TLine *l48Cr = new TLine(1.998084,0,1.998084,1);
//
//  TLine *l46Mn = new TLine(1.839466,0,1.839466,1);
//  TLine *l47Mn = new TLine(1.879030,0,1.879030,1);
//  TLine *l48Mn = new TLine(1.918741,0,1.918741,1);
//  TLine *l49Mn = new TLine(1.958384,0,1.958384,1);
//  TLine *l50Mn = new TLine(1.998169,0,1.998169,1);
//
//  TLine *l45Fe = new TLine(1.731364,0,1.731364,1); //unknown
//  TLine *l46Fe = new TLine(1.769280,0,1.769280,1); //unknown
//  TLine *l47Fe = new TLine(1.807397,0,1.807397,1); //unknown
//  TLine *l48Fe = new TLine(1.845410,0,1.845410,1);
//  TLine *l49Fe = new TLine(1.883593,0,1.883593,1);
//  TLine *l50Fe = new TLine(1.921653,0,1.921653,1);
//  TLine *l51Fe = new TLine(1.959879,0,1.959879,1);
//  TLine *l52Fe = new TLine(1.998004,0,1.998004,1);
//
//  TLine *l49Co = new TLine(1.814425,0,1.814425,1); //unknown
//  TLine *l50Co = new TLine(1.851152,0,1.851152,1);
//  TLine *l51Co = new TLine(1.887801,0,1.887801,1);
//  TLine *l52Co = new TLine(1.924560,0,1.924560,1);
//  TLine *l53Co = new TLine(1.961266,0,1.961266,1);
//  TLine *l54Co = new TLine(1.998091,0,1.998091,1);
//
//  TLine *l48Ni = new TLine(1.714982,0,1.714982,1); //unknown
//  TLine *l49Ni = new TLine(1.705327,0,1.705327,1); //unknown
//  TLine *l50Ni = new TLine(1.785581,0,1.785581,1); //unknown
//  TLine *l51Ni = new TLine(1.820981,0,1.820981,1);
//  TLine *l52Ni = new TLine(1.856277,0,1.856277,1);
//  TLine *l53Ni = new TLine(1.891721,0,1.891721,1);
//  TLine *l54Ni = new TLine(1.927065,0,1.927065,1);
//  TLine *l55Ni = new TLine(1.962547,0,1.962547,1);
//  TLine *l56Ni = new TLine(1.997933,0,1.997933,1);
//
// l36Ca->SetLineWidth(1);
// l37Ca->SetLineWidth(1);
// l38Ca->SetLineWidth(1);
// l39Ca->SetLineWidth(1);
// l40Ca->SetLineWidth(1);
//
// l38Sc->SetLineWidth(1); //unknown 
// l39Sc->SetLineWidth(1);
// l40Sc->SetLineWidth(1);
// l41Sc->SetLineWidth(1);
// l42Sc->SetLineWidth(1);
//
// l39Ti->SetLineWidth(1); //unknown
// l40Ti->SetLineWidth(1);
// l41Ti->SetLineWidth(1);
// l42Ti->SetLineWidth(1);
// l43Ti->SetLineWidth(1);
// l44Ti->SetLineWidth(1);
//
// l43V ->SetLineWidth(1);
// l44V ->SetLineWidth(1);
// l45V ->SetLineWidth(1);
// l46V ->SetLineWidth(1);
//
// l42Cr->SetLineWidth(1); //unknown
// l43Cr->SetLineWidth(1); //unknown
// l44Cr->SetLineWidth(1);
// l45Cr->SetLineWidth(1);
// l46Cr->SetLineWidth(1);
// l47Cr->SetLineWidth(1);
// l48Cr->SetLineWidth(1);
//
// l46Mn->SetLineWidth(1);
// l47Mn->SetLineWidth(1);
// l48Mn->SetLineWidth(1);
// l49Mn->SetLineWidth(1);
// l50Mn->SetLineWidth(1);
//
// l45Fe->SetLineWidth(1); //unknown
// l46Fe->SetLineWidth(1); //unknown
// l47Fe->SetLineWidth(1); //unknown
// l48Fe->SetLineWidth(1);
// l49Fe->SetLineWidth(1);
// l50Fe->SetLineWidth(1);
// l51Fe->SetLineWidth(1);
// l52Fe->SetLineWidth(1);
//
// l49Co->SetLineWidth(1); //unknown
// l50Co->SetLineWidth(1);
// l51Co->SetLineWidth(1);
// l52Co->SetLineWidth(1);
// l53Co->SetLineWidth(1);
// l54Co->SetLineWidth(1);
//
// l48Ni->SetLineWidth(1); //unknown
// l49Ni->SetLineWidth(1); //unknown
// l50Ni->SetLineWidth(1); //unknown
// l51Ni->SetLineWidth(1);
// l52Ni->SetLineWidth(1);
// l53Ni->SetLineWidth(1);
// l54Ni->SetLineWidth(1);
// l55Ni->SetLineWidth(1);
// l56Ni->SetLineWidth(1);
//
//
//
//
//
// l36Ca->SetLineColor(9);
// l37Ca->SetLineColor(9);
// l38Ca->SetLineColor(9);
// l39Ca->SetLineColor(9);
// l40Ca->SetLineColor(9);
//
// l38Sc->SetLineColor(8); //unknown 
// l39Sc->SetLineColor(8);
// l40Sc->SetLineColor(8);
// l41Sc->SetLineColor(8);
// l42Sc->SetLineColor(8);
//
// l39Ti->SetLineColor(7); //unknown
// l40Ti->SetLineColor(7);
// l41Ti->SetLineColor(7);
// l42Ti->SetLineColor(7);
// l43Ti->SetLineColor(7);
// l44Ti->SetLineColor(7);
//
// l43V ->SetLineColor(6);
// l44V ->SetLineColor(6);
// l45V ->SetLineColor(6);
// l46V ->SetLineColor(6);
//
// l42Cr->SetLineColor(4); //unknown
// l43Cr->SetLineColor(4); //unknown
// l44Cr->SetLineColor(4);
// l45Cr->SetLineColor(4);
// l46Cr->SetLineColor(4);
// l47Cr->SetLineColor(4);
// l48Cr->SetLineColor(4);
//
// l46Mn->SetLineColor(3);
// l47Mn->SetLineColor(3);
// l48Mn->SetLineColor(3);
// l49Mn->SetLineColor(3);
// l50Mn->SetLineColor(3);
//
// l45Fe->SetLineColor(2); //unknown
// l46Fe->SetLineColor(2); //unknown
// l47Fe->SetLineColor(2); //unknown
// l48Fe->SetLineColor(2);
// l49Fe->SetLineColor(2);
// l50Fe->SetLineColor(2);
// l51Fe->SetLineColor(2);
// l52Fe->SetLineColor(2);
//
// l49Co->SetLineColor(1); //unknown
// l50Co->SetLineColor(1);
// l51Co->SetLineColor(1);
// l52Co->SetLineColor(1);
// l53Co->SetLineColor(1);
// l54Co->SetLineColor(1);
//
// l48Ni->SetLineColor(28); //unknown
// l49Ni->SetLineColor(28); //unknown
// l50Ni->SetLineColor(28); //unknown
// l51Ni->SetLineColor(28);
// l52Ni->SetLineColor(28);
// l53Ni->SetLineColor(28);
// l54Ni->SetLineColor(28);
// l55Ni->SetLineColor(28);
// l56Ni->SetLineColor(28);
//
// l38Sc->SetLineStyle(4); //unknown 
// l39Ti->SetLineStyle(4); //unknown
// l42Cr->SetLineStyle(4); //unknown
// l43Cr->SetLineStyle(4); //unknown
// l45Fe->SetLineStyle(4); //unknown
// l46Fe->SetLineStyle(4); //unknown
// l47Fe->SetLineStyle(4); //unknown
// l49Co->SetLineStyle(4); //unknown
// l48Ni->SetLineStyle(4); //unknown
// l49Ni->SetLineStyle(4); //unknown
// l50Ni->SetLineStyle(4); //unknown


// l36Ca->Draw();
// l37Ca->Draw();
// l38Ca->Draw();
// l39Ca->Draw();
// l40Ca->Draw();
//
// l38Sc->Draw(); //unknown 
// l39Sc->Draw();
// l40Sc->Draw();
// l41Sc->Draw();
// l42Sc->Draw();
//
// l39Ti->Draw(); //unknown
// l40Ti->Draw();
// l41Ti->Draw();
// l42Ti->Draw();
// l43Ti->Draw();
// l44Ti->Draw();
//
// l43V ->Draw();
// l44V ->Draw();
// l45V ->Draw();
// l46V ->Draw();
//
// l42Cr->Draw(); //unknown
// l43Cr->Draw(); //unknown
// l44Cr->Draw();
// l45Cr->Draw();
// l46Cr->Draw();
// l47Cr->Draw();
// l48Cr->Draw();
//
// l46Mn->Draw();
// l47Mn->Draw();
// l48Mn->Draw();
// l49Mn->Draw();
// l50Mn->Draw();
//
// l45Fe->Draw(); //unknown
// l46Fe->Draw(); //unknown
// l47Fe->Draw(); //unknown
// l48Fe->Draw();
// l49Fe->Draw();
// l50Fe->Draw();
// l51Fe->Draw();
// l52Fe->Draw();
//
// l49Co->Draw(); //unknown
// l50Co->Draw();
// l51Co->Draw();
// l52Co->Draw();
// l53Co->Draw();
// l54Co->Draw();
//
// l48Ni->Draw(); //unknown
// l49Ni->Draw(); //unknown
// l50Ni->Draw(); //unknown
// l51Ni->Draw();
// l52Ni->Draw();
// l53Ni->Draw();
// l54Ni->Draw();
// l55Ni->Draw();
// l56Ni->Draw();
//
// return Lw;
//
//
// TF1 *



}
