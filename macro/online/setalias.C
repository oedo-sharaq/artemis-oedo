{

// definition of tracking and timing
tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");

//tree->SetAlias("src.fX","(1810*src2_x[0].fPosition-1290*src1_x[0].fPosition)/520.");
//tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/520.");
//tree->SetAlias("src.fY","(1810*(src2_y[0].fPosition-31)-1290*(src1_y[0].fPosition-31))/520.");
//tree->SetAlias("src.fB","((src2_yc0[0].fPosition-1)-(src1_yc0[0].fPosition-1))/520");

tree->SetAlias("src.fX","(1440*src2_xc0[0].fPosition-940*src1_xc0[0].fPosition)/500.");
tree->SetAlias("src.fA","(src2_xc0[0].fPosition-src1_xc0[0].fPosition)/500.");
tree->SetAlias("src.fY","(1440*(src2_yc0[0].fPosition-31)-940*(src1_yc0[0].fPosition-31))/500.");
tree->SetAlias("src.fB","((src2_yc0[0].fPosition-31)-(src1_yc0[0].fPosition-31))/500");



tree->SetAlias("fe9.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe12.fT","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");
tree->SetAlias("fe10.fT","fe9.fT+(fe12.fT-fe9.fT)*4753.75/(4753.75+9687.93)");


// for pid
tree->SetAlias("tof35.fT","f5pla[0].fTiming-dia3pad[0].fTiming)");
//tree->SetAlias("tof36.fT","f6ppac.fTAnode-dia3pad[0].fTiming");
//tree->SetAlias("tof39.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-dia3pad[0].fTiming");
//tree->SetAlias("tof30.fT","sr0_a_cal[0].fTiming-dia3pad[0].fTiming");
tree->SetAlias("tof32","dias2pad[0].fTiming-dia3pad[0].fTiming");

//tree->SetAlias("tof32p","-(tc842_raw.fCharge-dias2pad_5ps_raw.fCharge)*1e-3-2.146e6+1239.3");
//tree->SetAlias("tof32p","((dias2pad_5ps_raw.fCharge-tc842_raw.fCharge)+5.0e4)*1.e-3+2444.31");
tree->SetAlias("tof32p","((dias2pad_5ps_raw.fCharge-tc842_raw.fCharge)+5.0e4)*1.e-3+2444.31");



tree->SetAlias("pidgate","abs(sr0_x[0].fPosition+50-25*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1066))<30"); // optics0058

//tree->SetAlias("f5.brho","B_0*(1-f5track.fX/14600) "); //B_0, D
//tree->SetAlias("f5.beta","23283.19/(300*(tof35+t_off)) "); // L,t_off
//tree->SetAlias("f5.gamma","1/TMath::Sqrt(1-(f5.beta)*(f5.beta)) "); 
//tree->SetAlias("f5.aq","f5.brho / (f5.gamma * f5.beta * 300) ");
//tree->SetAlias("fe9.beta","68543.07./(tof39+t_off) "); // L, t_off
//tree->SetAlias("fe9.gamma","1/TMath::Sqrt(1-(fe9.beta)*(fe9.beta)) ");
//tree->SetAlias("fe9.aq","fe9.brho / (fe9.gamma * fe9.beta * 300) ");
//
//tree->SetAlias("s0.brho","B_0*(1-sr0_x[0].fPosition/14600) "); //B_0, D
//tree->SetAlias("s0.beta","84764.75./(tof30+t_off) "); //L, t_off
//tree->SetAlias("s0.gamma","1/TMath::Sqrt(1-(s0.beta)*(s0.beta)) ");
//tree->SetAlias("s0.aq","s0.brho / (s0.gamma * s0.beta * 300) ");
//
tree->SetAlias("s2brho","4.4147*(1-sr0_x[0].fPosition/14856) "); //B_0, D
tree->SetAlias("s2betap","103499.78/(tof32p-1455.)/299.79"); //L, t_off
tree->SetAlias("s2beta","103499.78/(tof32-1455.)/299.79"); //L, t_off
tree->SetAlias("s2gammap","1/TMath::Sqrt(1-(s2betap)*(s2betap)) ");
tree->SetAlias("s2gamma","1/TMath::Sqrt(1-(s2beta)*(s2beta)) ");
tree->SetAlias("s2aqp","s2brho * 299.79 / (s2gammap * s2betap * 931.49) ");
tree->SetAlias("s2aq","s2brho * 299.79 / (s2gamma * s2beta * 931.49) ");


//tree->SetAlias("fe7.fX","(2894.75+250.)*(fe7ppac1.GetX()-fe7ppac2.GetX())/500.");  
//tree->SetAlias("fe7.fY","(2894.75+250.)*(fe7ppac1.GetY()-fe7ppac2.GetY())/500.");  
//tree->SetAlias("fe7.fX","(2894.75+250.)*(fe7ppac1.GetX()-fe7ppac2.GetX())/500.");  
//tree->SetAlias("fe7.fY","(2894.75+250.)*(fe7ppac1.GetY()-fe7ppac2.GetY())/500.");  
tree->SetAlias("s0.fX","sr0_xc0[0].fPosition+49.28");  
tree->SetAlias("s0.fY","sr0_yc0[0].fPosition");  
tree->SetAlias("tof30","sr0_a_cal.fTiming-dia3pad[0].fTiming");  
tree->SetAlias("pidgate","abs(s0.fX)<20&&abs(tof30-1066)<2");  
//tree->SetAlias("pidgate","abs(s0.fX)<60&&abs(tof30-1066)<2");  

tree->SetAlias("pidfe","abs(s0.fX)<60&&abs(tof30-1066)<2");  
tree->SetAlias("pidv","abs(s0.fX)<60&&abs(tof30-1093)<3");  

tree->SetAlias("s0xc","s0.fX-24.0*(tof30-1066.)");  

// tree->SetAlias("s2de","S2ssd.fEx");
//// tree->SetAlias("s2de","-144.158 + 1.53178 * S2ssd.fEx");
// tree->SetAlias("s2de","(S2ssd.fEx-7.1)*0.9783"); // optics0097
 tree->SetAlias("s2de","1.03827*S2ssd.fEx*0.866"); // optics0111
 tree->SetAlias("de_vp","TMath::Log(5907.5*s2betap*s2betap)-TMath::Log(1.-s2betap*s2betap)-s2betap*s2betap");
 tree->SetAlias("de_v","TMath::Log(5907.5*s2beta*s2beta)-TMath::Log(1.-s2beta*s2beta)-s2beta*s2beta");

 //tree->SetAlias("s2z","TMath::Sqrt(s2de/de_v) * s2beta");
 //// tree->SetAlias("s2z","7.2379 + 5.38095*TMath::Sqrt(s2de/de_v) * s2beta");
 // tree->SetAlias("s2z","1.08678 + 7.29327*TMath::Sqrt(s2de/de_v) * s2beta"); // optics0097
 tree->SetAlias("s2zp","-0.0513 + 7.451*TMath::Sqrt(s2de/de_vp) * s2betap"); // optics0111
 tree->SetAlias("s2z","-0.0513 + 7.451*TMath::Sqrt(s2de/de_v) * s2beta"); // optics0111

//tree->SetAlias("fe7.fX","(2894.75+250.)*(fe7ppac1.GetX()-fe7ppac2.GetX())/500.");  
//tree->SetAlias("fe7.fY","(2894.75+250.)*(fe7ppac1.GetY()-fe7ppac2.GetY())/500.");  
tree->SetAlias("fe7.fX","(2894.75+250.)*(fe7ppac1.GetX()-fe7ppac2.GetX())/500.");  
tree->SetAlias("fe7.fY","(2894.75+250.)*(fe7ppac1.GetY()-fe7ppac2.GetY())/500.");  
tree->SetAlias("s0.fX","sr0_xc0[0].fPosition+49.28");  
tree->SetAlias("tof30","sr0_a_cal.fTiming-dia3pad[0].fTiming");  
tree->SetAlias("triggate","abs(trig_raw.fCharge-254000)<500");  


// added by mtanaka
 tree->SetAlias("pltof","s2pla.GetTAve()-dia3pad[0].fTiming");
 tree->SetAlias("pltofvalid","2020 < s2pla.GetTAve()-dia3pad[0].fTiming && s2pla.GetTAve()-dia3pad[0].fTiming < 2150");
 tree->SetAlias("gpltof2","2020 < s2pla.GetTAve()-dia3pad[0].fTiming && s2pla.GetTAve()-dia3pad[0].fTiming < 2080");
 tree->SetAlias("plz","S2ssd.GetEx()-(0.60*pltof-1061.49)");
 tree->SetAlias("gs2xy","-5<s2.fX&&s2.fX<5 && 5<s2.fY && s2.fY<45");
 tree->SetAlias("gs2xy_2","-5<s2.fX&&s2.fX<-1 && 5<s2.fY && s2.fY<45");

 tree->SetAlias("g1","2065<pltof&&pltof<2070 && 170<S2ssd.GetEx()&&S2ssd.GetEx()<180"); // 39Ca on TOF(F3Dia-S2PL) vs dE(Si)
 tree->SetAlias("g2","2040<pltof&&pltof<2043 && 180<S2ssd.GetEx()&&S2ssd.GetEx()<210"); // 40Ti on TOF(F3Dia-S2PL) vs dE(Si)
 tree->SetAlias("g3","2034<pltof&&pltof<2039 && 220<S2ssd.GetEx()&&S2ssd.GetEx()<240"); // 43Cr on TOF(F3Dia-S2PL) vs dE(Si)
 tree->SetAlias("g4","2037<pltof&&pltof<2041 && 265<S2ssd.GetEx()&&S2ssd.GetEx()<290"); // 47Fe on TOF(F3Dia-S2PL) vs dE(Si)

}

