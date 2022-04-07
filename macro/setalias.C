{


// gROOT->ProcessLine("tree->SetAlias("sr9.fX","(345*sr91_xc0.fPosition+100*sr92_xc0.fPosition)/(100+345)")");
// gROOT->ProcessLine("tree->SetAlias("sr9.fY","(345*sr91_yc0.fPosition+100*sr92_yc0.fPosition)/(100+345)")");
//
// gROOT->ProcessLine("tree->SetAlias("sr9.fA","445./TMath::Abs(sr91_xc0.fPosition-sr92_xc0.fPosition)")");
// gROOT->ProcessLine("tree->SetAlias("sr9.fB","445./TMath::Abs(sr91_yc0.fPosition-sr92_yc0.fPosition)")");
// 
// gROOT->ProcessLine("tree->SetAlias("tof:","f3pla.fTiming-f2pla.fTiming")");
//
//
//tree->SetAlias("sr9.fX","(345*sr91_xc0.fPosition+100*sr92_xc0.fPosition)/(100+345)")
//tree->SetAlias("sr9.fY","(345*sr91_yc0.fPosition+100*sr92_yc0.fPosition)/(100+345)")
//
//tree->SetAlias("sr9.fA","445./TMath::Abs(sr91_xc0.fPosition-sr92_xc0.fPosition)")
//tree->SetAlias("sr9.fB","445./TMath::Abs(sr91_yc0.fPosition-sr92_yc0.fPosition)")
//
//tree->SetAlias("tof","f3pla.fTiming-f2pla.fTiming")


//tree->SetAlias("pidgate","abs(f5track.fX+23.9*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-1414-32369)<9")
//tree->SetAlias("pidgate","abs(f5track.fX+25.5*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-36040)<10")
tree->SetAlias("pidgate","abs(f5track.fX+26.6*((f5ppac1a.fTAnode+f5ppac2a.fTAnode)/2-diapad.fTiming-1250)-37595)<10")
//tree->SetAlias("sr9x","(542.25*sr91_x.fPosition-122.5*sr92_x.fPosition)/419.75")
//tree->SetAlias("sr9a","(sr91_x.fPosition-sr92_x.fPosition)/419.75")
//tree->SetAlias("sr9y","(542.25*sr91_y.fPosition-122.5*sr92_y.fPosition)/419.75")
//tree->SetAlias("sr9b","(sr91_y.fPosition-sr92_y.fPosition)/419.75")
//
//tree->SetAlias("srcx","(1972*src2_x.fPosition-1452*src1_x.fPosition)/520")
//tree->SetAlias("srca","(src2_x.fPosition-src1_x.fPosition)/520")
//tree->SetAlias("srcy","(1972*src2_y.fPosition-1452*src1_y.fPosition)/520")
//tree->SetAlias("srcb","(src2_y.fPosition-src1_y.fPosition)/520")

}

