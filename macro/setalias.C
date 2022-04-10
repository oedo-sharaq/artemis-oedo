{

//tree->SetAlias("pidgate","abs(f5track.fX+23.9*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-1414-32369)<9");
//tree->SetAlias("pidgate","abs(f5track.fX+25.5*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-36040)<10");
//tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37595)<10");
tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37611)<10");

tree->SetAlias("sr9.fX","(542.25*sr91_x.fPosition-122.5*sr92_x.fPosition)/419.75");
tree->SetAlias("sr9.fA","(sr91_x.fPosition-sr92_x.fPosition)/419.75");
tree->SetAlias("sr9.fY","(542.25*sr91_y.fPosition-122.5*sr92_y.fPosition)/419.75");
tree->SetAlias("sr9.fB","(sr91_y.fPosition-sr92_y.fPosition)/419.75");
//
//tree->SetAlias("src.fX","(1972*src2_x.fPosition-1452*src1_x.fPosition)/520.");
//tree->SetAlias("src.fA","(src1_x.fPosition-src2_x.fPosition)/520.");
//tree->SetAlias("src.fY","(1972*src2_y.fPosition-1452*src1_y.fPosition)/520.");
//tree->SetAlias("src.fB","(src1_y.fPosition-src2_y.fPosition)/520");

//tree->SetAlias("sr1.fX","(560.8*sr12_x.fPosition-210.8*sr11_x.fPosition)/350.";)
//tree->SetAlias("sr1.fA","(sr11_x.fPosition-sr12_x.fPosition)/350.");
//tree->SetAlias("sr1.fY","(560.8*sr12_y.fPosition-210.8*sr11_y.fPosition)/350.");
//tree->SetAlias("sr1.fB","(sr11_y.fPosition-sr12_y.fPosition)/350.");


//tree->SetAlias("tof3c","(src1_a_raw.fTiming+src2_a_raw.fTiming)/2-fdiapad.fTiming");
//tree->SetAlias("tof39","(sr91_a_raw.fTiming+sr92_a_raw.fTiming)/2-diapad.fTiming");
//tree->SetAlias("tof9c","(src1_a_raw.fTiming+src2_a_raw.fTiming)/2-(sr91_a_raw.fTiming+sr92_a_raw.fTiming)/2");
//tree->SetAlias("tof9s","(sr11_a_raw.fTiming+sr12_a_raw.fTiming)/2-(sr91_a_raw.fTiming+sr92_a_raw.fTiming)/2");

}

