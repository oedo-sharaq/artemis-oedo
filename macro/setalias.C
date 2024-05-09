{

tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming");
tree->SetAlias("f5.fT","(f5ppac1a[0].fTAnode+f5ppac1b[0].fTAnode+f5ppac2a[0].fTAnode+f5ppac2b[0].fTAnode)/4.");
tree->SetAlias("tof35","f5.fT-diapad[0].fTiming");

tree->SetAlias("pidgate","abs(f5track.fX-23.676*(tof35-2658)+20)<15"); 
//tree->SetAlias("pidgate","abs(sr9.fX+3.07655*tof39-3310)<15"); 

tree->SetAlias("sr9.fX","(542.25*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/419.75");

//tree->SetAlias("src.fX","50.0+(1962*src2_x[0].fPosition-1462*src1_x[0].fPosition)/500.");
tree->SetAlias("src.fX","50.0+(1655*src2_x[0].fPosition-1100*src1_x[0].fPosition)/500.");
tree->SetAlias("src.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/500.");
//tree->SetAlias("src.fY","(1962*(src2_y[0].fPosition-31)-1462*(src1_y[0].fPosition-31))/500.");
tree->SetAlias("src.fY","(1655*(src2_y[0].fPosition-31)-1100 *(src1_y[0].fPosition-31))/500.");
tree->SetAlias("src.fB","((src2_y[0].fPosition-31)-(src1_y[0].fPosition-31))/500.");

//tree->SetAlias("hole.fX","50.0+(1242*src2_x[0].fPosition-742*src1_x[0].fPosition)/500.");
tree->SetAlias("hole.fX","50.0+(1297*src2_x[0].fPosition-742*src1_x[0].fPosition)/500.");
tree->SetAlias("hole.fA","(src2_x[0].fPosition-src1_x[0].fPosition)/500.");
//tree->SetAlias("hole.fY","(1242*(src2_y[0].fPosition-31)-742*(src1_y[0].fPosition-31))/500.");
tree->SetAlias("hole.fY","(1297*(src2_y[0].fPosition-31)-742*(src1_y[0].fPosition-31))/500.");
tree->SetAlias("hole.fB","((src2_y[0].fPosition-31)-(src1_y[0].fPosition-31))/500.");

tree->SetAlias("sr1.fX","(560.8*sr12_x[0].fPosition-210.8*sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fA","(sr12_x[0].fPosition-sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fY","(560.8*sr12_y[0].fPosition-210.8*sr11_y[0].fPosition)/350.");
tree->SetAlias("sr1.fB","(sr12_y[0].fPosition-sr11_y[0].fPosition)/350.");

tree->SetAlias("fe9.fT","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe12.fT","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");

//tree->SetAlias("tof3c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-fdiapad[0].fTiming");
tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-diapad[0].fTiming");
tree->SetAlias("tof9c","(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-715.279"); //offset=706.928
tree->SetAlias("tofcs","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2-579.95");
//tree->SetAlias("tof8s","(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2-(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
tree->SetAlias("fe10.fT","fe9.fT+(fe12.fT-fe9.fT)*4753.75/(4753.75+9687.93)");


//tree->SetAlias("pidgate","abs(sr9.fX+3.07655*(tof39-3310)<15");  // pidgate w/ fe9


}

