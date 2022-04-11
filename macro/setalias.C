{

//tree->SetAlias("pidgate","abs(f5track.fX+23.9*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-1414-32369)<9");
//tree->SetAlias("pidgate","abs(f5track.fX+25.5*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-36040)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37595)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37611)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad[0].fTiming-1250)-37606)<10");
tree->SetAlias("pidgate","abs(sr9.fX+7.5*((sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming-1073.2))<10");
tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");
//
tree->SetAlias("src.fX","(1972*src2_x[0].fPosition-1452*src1_x[0].fPosition)/520.");
tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/520.");
tree->SetAlias("src.fY","(1972*(src2_y[0].fPosition-31)-1452*(src1_y[0].fPosition-31))/520.");
tree->SetAlias("src.fB","((src2_yc0[0].fPosition-31)-(src1_yc0[0].fPosition-31))/520");

//tree->SetAlias("sr1.fX","(560.8*sr12_x[0].fPosition-210.8*sr11_x[0].fPosition)/350.";)
//tree->SetAlias("sr1.fA","(sr12_x[0].fPosition-sr11_x[0].fPosition)/350.");
//tree->SetAlias("sr1.fY","(560.8*sr12_y[0].fPosition-210.8*sr11_y[0].fPosition)/350.");
//tree->SetAlias("sr1.fB","(sr12_y[0].fPosition-sr11_y[0].fPosition)/350.");

//tree->SetAlias("tof3c","(src1_a_raw.fTiming+src2_a_raw.fTiming)/2-diapad.fTiming");
tree->SetAlias("tof39_4avx","(sr91_a_cal.fTiming+sr92_a_cal.fTiming+sr91_x_cal.fTiming+sr92_x_cal.fTiming)/4.-diapad.fTiming");
tree->SetAlias("tof39_4avy","(sr91_a_cal.fTiming+sr92_a_cal.fTiming+sr91_y_cal.fTiming+sr92_y_cal.fTiming)/4.-diapad.fTiming");
//tree->SetAlias("tof9c","(src1_a_raw.fTiming+src2_a_raw.fTiming)/2-(sr91_a_raw.fTiming+sr92_a_raw.fTiming)/2");
//tree->SetAlias("tof9s","(sr11_a_raw.fTiming+sr12_a_raw.fTiming)/2-(sr91_a_raw.fTiming+sr92_a_raw.fTiming)/2");
//tree->SetAlias("tof3c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-fdiapad[0].fTiming");
//tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming");
//tree->SetAlias("tof9c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
//tree->SetAlias("tof8s","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");

}

