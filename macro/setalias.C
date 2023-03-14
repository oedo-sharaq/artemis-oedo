{

//tree->SetAlias("pidgate","abs(f5track.fX+23.9*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-1414-32369)<9");
//tree->SetAlias("pidgate","abs(f5track.fX+25.5*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-36040)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37595)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37611)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-1250)-37606)<10");
//tree->SetAlias("pidgate","abs((f5track.fX+4.5)+22.437*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-2663.9))<10"); // optics 0156 130Sn

//tree->SetAlias("pidgate","abs(sr9.fX+sr9.fA*200+6.8265*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1060))<10"); // optics0119 130Sn
//tree->SetAlias("pidgate","abs(sr9.fX+sr9.fA*200+7.7889*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1071))<10"); // optics0156, optics0166, optics0171 130Sn
tree->SetAlias("pidgate","abs(sr9.fX+sr9.fA*200+7.33651*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1073.5))<10"); // optics0181 130Sn
//tree->SetAlias("pidgate","abs(sr9.fX+sr9.fA*200+7.35667*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1073))<10"); // optics0239 130Sn

//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1073.2))<10"); // physics 130Sn
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1071))<10"); // optics0419
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-1250)-37636)<10"); // optics0419
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1074))<10"); //optics0439 124Sn FE9
//tree->SetAlias("pidgate","abs(sr9.fX+7.742*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1075.7))<10"); //optics0442 124Sn FE9
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1078.2))<10");// physics 124Sn
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1064))<10");
tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");
//
tree->SetAlias("src.fX","(1972*src2_x[0].fPosition-1452*src1_x[0].fPosition)/520.");
tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/520.");
tree->SetAlias("src.fY","(1972*(src2_y[0].fPosition-31)-1452*(src1_y[0].fPosition-31))/520.");
tree->SetAlias("src.fB","((src2_yc0[0].fPosition-31)-(src1_yc0[0].fPosition-31))/520");

tree->SetAlias("sr1.fX","(560.8*sr12_x[0].fPosition-210.8*sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fA","(sr12_x[0].fPosition-sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fY","(560.8*sr12_y[0].fPosition-210.8*sr11_y[0].fPosition)/350.");
tree->SetAlias("sr1.fB","(sr12_y[0].fPosition-sr11_y[0].fPosition)/350.");

tree->SetAlias("fe9.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe12.fT","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");
tree->SetAlias("S1.fT","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2");

//tree->SetAlias("tof3c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-fdiapad[0].fTiming");
//tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-vf3dia[0].fTiming-1073"); // defined online
tree->SetAlias("tof_39","tof39.fTiming");
tree->SetAlias("pid","tof39*0.99+0.12*sr9.fX");
tree->SetAlias("tof9c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("tofcs","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-579.06");
//tree->SetAlias("tof8s","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe10.fT","fe9.fT+(fe12.fT-fe9.fT)*4753.75/(4753.75+9687.93)");

tree->SetAlias("targ1","((src.fX+2.2)**2+(src.fY+0.9)**2)<45**2"); // optics0239 130Sn

tree->SetAlias("fe12","abs(src1_a_raw.fTiming+14960)<3000 && @src1_a_raw.GetEntriesFast() == 1"); // optics0239 130Sn
tree->SetAlias("s1","(abs(sr11_a_raw.fTiming+7786) < 700) && @sr11_a_raw.GetEntriesFast() == 1"); // optics0239 130Sn

tree->SetAlias("s1brho","1.9271*(1-src.fX/1000) "); //B_0, optics0239 130Sn
tree->SetAlias("s1beta","7813/tofcs/299.79"); //L
tree->SetAlias("s1gamma","1/TMath::Sqrt(1-(s1beta)*(s1beta)) ");
tree->SetAlias("s1aq","s1brho * 299.79 / (s1gamma * s1beta * 931.49) ");

// Imai-san alias 

  // for 130Te
  tree->SetAlias("tof39c","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2 - diapad[0].fTiming - 1064.");
  tree->SetAlias("pidc","tof39c*0.99+0.125*sr9.fX");
  // for 130Sn
  tree->SetAlias("tof39a","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2 - vf3dia[0].fTiming - 1073.");
  tree->SetAlias("pid1","tof39a*0.99+0.125*sr9.fX");
  // for 124Sn
  tree->SetAlias("tof39b","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2 - diapad[0].fTiming - 1079.");

  tree->SetAlias("tof12s1","S1.fT-fe12.fT");
  tree->SetAlias("pids1","sr1.fX*0.0565+0.9984*(tof12s1-698)");

  tree->SetAlias("pidg","abs(pidc)<1.8");
  tree->SetAlias("pos","sqrt(src.fX * src.fX + src.fY * src.fY) < 20.");
  tree->SetAlias("yy1true","abs(tinat[0].fTiming+200.)<300&& tinat[0].fID < 6");
  tree->SetAlias("tinaT","tinat.fTiming > 200");
  //  tree->SetAlias("beta1","16.62/tof912[0].fTiming/2.99*10.");
  tree->SetAlias("beta1","16.62/(fe12.fT-fe9.fT+111.4)*10./2.99");
  tree->SetAlias("gamma1","1./TMath::Sqrt(1.0-beta1*beta1)");
  tree->SetAlias("ene1","(gamma1 -1.0)*931.494");
  // for 130Sn, 2.98 is Q-value of 130Sn(d,p)131Sn
  //tree->SetAlias("Ex","(ene1*130. - tina2[0].fDeltaE-(2.*ene1*130. *130. *931.494 - 2.*sqrt(2.*ene1*130. *130. *931.494)*sqrt(2.*tina2[0].fDeltaE*931.494)*cos(tina2[0].fTheta/180.*3.14)+2.*tina2[0].fDeltaE*931.494)/2./131./931.494)+2.98");
  // for 130Te, 3.705 is Q-value of 130Te(d,p)131Te
  tree->SetAlias("Ex","(ene1*130. - tina2[0].fDeltaE-(2.*ene1*130. *130. *931.494 - 2.*sqrt(2.*ene1*130. *130. *931.494)*sqrt(2.*tina2[0].fDeltaE*931.494)*cos(tina2[0].fTheta/180.*3.14)+2.*tina2[0].fDeltaE*931.494)/2./131./931.494)+3.705");

}

