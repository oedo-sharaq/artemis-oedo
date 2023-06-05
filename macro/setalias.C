{

tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming");
//tree->SetAlias("pidgate","abs(f5track.fX+23.9*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-1414-32369)<9");
//tree->SetAlias("pidgate","abs(f5track.fX+25.5*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-36040)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37595)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37611)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-1250)-37606)<10");
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1073.2))<10"); // physics 130Sn
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1071))<10"); // optics0419
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-1250)-37636)<10"); // optics0419
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1074))<10"); //optics0439 124Sn FE9
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1075.8))<10"); //optics0439 124Sn FE9
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1078.2))<10");// physics 124Sn
  tree->SetAlias("f5.fT","(f5ppac1a.fTAnode+f5ppac1b.fTAnode+f5ppac2a.fTAnode+f5ppac2b.fTAnode)/4.");
  tree->SetAlias("f5.pid","0.0427*f5track.fX+0.999*(f5.fT-2709)+2720-3.6");
// tree->SetAlias("fe9.pid","0.1463*sr9.fX+0.999*fe9.fT+1500+53");
// tree->SetAlias("fe9.pid","0.1463*sr9.fX+0.999*fe9.fT+1500+53-11"); // tuning F3 ting
// tree->SetAlias("fe9.pid","0.1463*sr9.fX+0.999*fe9.fT+1500+53-11+4.3"); // phys S0 ting
 tree->SetAlias("fe9.pid","sr9.fX+4.086*fe9.fT+6335-2.6-43+11.35-1.342"); // tuning Ni58 0195
//tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1064))<10");
tree->SetAlias("pidgate","abs(fe9.pid)<8");
tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");
//
tree->SetAlias("src.fX","(1972*src2_x[0].fPosition-1452*src1_x[0].fPosition)/520.");
tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/520.");
tree->SetAlias("src.fY","(1972*(src2_y[0].fPosition-31)-1452*(src1_y[0].fPosition-31))/520.");
tree->SetAlias("src.fB","((src2_y[0].fPosition-31)-(src1_y[0].fPosition-31))/520.");

tree->SetAlias("sr1.fX","(560.8*sr12_x[0].fPosition-210.8*sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fA","(sr12_x[0].fPosition-sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fY","(560.8*sr12_y[0].fPosition-210.8*sr11_y[0].fPosition)/350.");
tree->SetAlias("sr1.fB","(sr12_y[0].fPosition-sr11_y[0].fPosition)/350.");

tree->SetAlias("fe9.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe12.fT","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");

//tree->SetAlias("tof3c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-fdiapad[0].fTiming");
tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-vf3dia[0].fTiming-1073");
tree->SetAlias("pid","tof39*0.99+0.12*sr9.fX");
tree->SetAlias("tof9c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("tofcs","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-579.95");
//tree->SetAlias("tof8s","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe10.fT","fe9.fT+(fe12.fT-fe9.fT)*4753.75/(4753.75+9687.93)");

}

