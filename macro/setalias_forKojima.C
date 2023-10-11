{

// definition of tracking and timing
tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");

tree->SetAlias("src.fX","(1810*src2_x[0].fPosition-1290*src1_x[0].fPosition)/520.");
tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/520.");
tree->SetAlias("src.fY","(1810*(src2_y[0].fPosition-31)-1290*(src1_y[0].fPosition-31))/520.");
tree->SetAlias("src.fB","((src2_yc0[0].fPosition-1)-(src1_yc0[0].fPosition-1))/520");

tree->SetAlias("fe9.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe12.fT","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");
tree->SetAlias("fe10.fT","fe9.fT+(fe12.fT-fe9.fT)*4753.75/(4753.75+9687.93)");


// for pid
tree->SetAlias("tof35.fT","f5pla[0].fTiming-dia3pad[0].fTiming)");
//tree->SetAlias("tof36.fT","f6ppac.fTAnode-dia3pad[0].fTiming");
//tree->SetAlias("tof39.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-dia3pad[0].fTiming");
//tree->SetAlias("tof30.fT","sr0_a_cal[0].fTiming-dia3pad[0].fTiming");
//tree->SetAlias("tof32.fT","dias2pad[0].fTiming-dia3pad[0].fTiming");

tree->SetAlias("pidgate","abs(sr0_x[0].fPosition+50-25*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1066))<30"); // optics0058
tree->SetAlias("pidgate49Mn","abs(sr0_x[0].fPosition+50-25*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1071.7))<30"); // optics0058
tree->SetAlias("pidgate50Mn","abs(sr0_x[0].fPosition+50-35*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1078))<30"); // optics0058
tree->SetAlias("pidgate49Cr","abs(sr0_x[0].fPosition+50-25*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1085))<30"); // optics0058
tree->SetAlias("pidgate48V","abs(sr0_x[0].fPosition+50-25*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1092.4))<30"); // optics0058
tree->SetAlias("pidgate47Ti","abs(sr0_x[0].fPosition+50-30*(sr0_a_cal.fTiming-dia3pad[0].fTiming-1100.8))<30"); // optics0058


//tree->SetAlias("f5.brho","B_0*(1-f5track.fX/14600) "); //B_0, D
//tree->SetAlias("f5.beta","23283.19/(300*(tof35+t_off)) "); // L,t_off
//tree->SetAlias("f5.gamma","1/TMath::Sqrt(1-(f5.beta)*(f5.beta)) "); 
//tree->SetAlias("f5.aq","f5.brho / (f5.gamma * f5.beta * 300) ");

//tree->SetAlias("fe9.brho","B_0*(1-sr9_x[0].fPosition/14600) "); //B_0, D
//tree->SetAlias("fe9.beta","68543.07./(tof39+t_off) "); // L, t_off
//tree->SetAlias("fe9.gamma","1/TMath::Sqrt(1-(fe9.beta)*(fe9.beta)) ");
//tree->SetAlias("fe9.aq","fe9.brho / (fe9.gamma * fe9.beta * 300) ");
//
//tree->SetAlias("s0.brho","B_0*(1-sr0_x[0].fPosition/14600) "); //B_0, D
//tree->SetAlias("s0.beta","84764.75./(tof30+t_off) "); //L, t_off
//tree->SetAlias("s0.gamma","1/TMath::Sqrt(1-(s0.beta)*(s0.beta)) ");
//tree->SetAlias("s0.aq","s0.brho / (s0.gamma * s0.beta * 300) ");
//
//tree->SetAlias("s2.brho","B_0*(1-sr0_x[0].fPosition/14600) "); //B_0, D
//tree->SetAlias("s2.beta","103499.78./(tof32+t_off) "); //L, t_off
//tree->SetAlias("s2.gamma","1/TMath::Sqrt(1-(s0.beta)*(s0.beta)) ");
//tree->SetAlias("s2.aq","s0.brho / (s0.gamma * s0.beta * 300) ");

tree->SetAlias("fe7.fX","(2894.75+250.)*(fe7ppac2.GetX()-fe7ppac1.GetX())/500.+fe7ppac1.GetX()");
tree->SetAlias("fe7.fY","(2894.75+250.)*(fe7ppac2.GetY()-fe7ppac1.GetY())/500.+fe7ppac1.GetY()");

}

