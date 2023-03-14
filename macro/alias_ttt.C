{
tree->SetAlias("tof39pre","tof39_pre.fTiming");
tree->SetAlias("tof39","tof39_pre.fTiming-1064."); // 130Te
tree->SetAlias("pid","0.99*tof39+0.14*sr9.fX");
tree->SetAlias("pidgate","abs(pid)<1.2&&abs(sr9.fX)<20."); // 130Te

tree->SetAlias("sr9.fX","(541.*sr91_x[0].fPosition-122.5*sr92_x[0].fPosition)/418.5");
tree->SetAlias("sr9.fA","(sr92_x[0].fPosition-sr91_x[0].fPosition)/418.5");
tree->SetAlias("sr9.fY","(541.*sr91_y[0].fPosition-122.5*sr92_y[0].fPosition)/418.5");
tree->SetAlias("sr9.fB","(sr92_y[0].fPosition-sr91_y[0].fPosition)/418.5");

// tree->SetAlias("src.fX","(2017.*src2_x[0].fPosition-1517.*src1_x[0].fPosition)/500.");
// tree->SetAlias("src.fY","(2017.*(src2_y[0].fPosition-30.)-1517.*(src1_y[0].fPosition-30.))/500.");
// tree->SetAlias("src.fA","(src2_x.fPosition-src1_x[0].fPosition)/500.");
// tree->SetAlias("src.fB","((src2_y[0].fPosition-30.)-(src1_y[0].fPosition-30.))/500.");

tree->SetAlias("src.fX","(2017.*src2_xc0_strip2[0].fPosition-1517.*src1_xc0_strip2[0].fPosition)/500.");
tree->SetAlias("src.fY","(2017.*(src2_yc0_strip2[0].fPosition-30.)-1517.*(src1_yc0_strip2[0].fPosition-30.))/500.");
tree->SetAlias("src.fA","(src2_xc0_strip2[0].fPosition-src1_xc0_strip2[0].fPosition)/500.");
tree->SetAlias("src.fB","((src2_yc0_strip2[0].fPosition-30.)-(src1_yc0_strip2[0].fPosition-30.))/500.");

tree->SetAlias("colix","(1293.*src2_xc0_strip2[0].fPosition-793.*src1_xc0_strip2[0].fPosition)/500.");
tree->SetAlias("coliy","(1293.*(src2_yc0_strip2[0].fPosition-30.)-793.*(src1_yc0_strip2[0].fPosition-30.))/500.");
tree->SetAlias("colixy","(colix*colix+coliy*coliy)<25.*25.");

tree->SetAlias("sr1.fX","(560.8*sr12_x[0].fPosition-210.8*sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fA","(sr12_x[0].fPosition-sr11_x[0].fPosition)/350.");
tree->SetAlias("sr1.fY","(560.8*sr12_y[0].fPosition-210.8*sr11_y[0].fPosition)/350.");
tree->SetAlias("sr1.fB","(sr12_y[0].fPosition-sr11_y[0].fPosition)/350.");

tree->SetAlias("tttgate", "abs(vf3dia.fTiming+3100.)<200.&&abs(sr91_a_val.fTiming+21000.)<2000.&&abs(sr92_a_val.fTiming+21000.)<2000.&&abs(src1_a_val.fTiming+19500.)<2000.&&abs(src2_a_val.fTiming+19500.)<2000.");
tree->SetAlias("sr1tgate", "abs(sr11_a_val.fTiming+12500)<2000&&abs(sr12_a_val.fTiming+12500)<2000");
tree->SetAlias("tgate", "abs(vf3dia.fTiming+3100.)<200.&&abs(sr91_a_val.fTiming+21000.)<2000.&&abs(sr92_a_val.fTiming+21000.)<2000.&&abs(src1_a_val.fTiming+19500.)<2000.&&abs(src2_a_val.fTiming+19500.)<2000.&&abs(sr11_a_val.fTiming+12500)<2000&&abs(sr12_a_val.fTiming+12500)<2000");

tree->SetAlias("de","tina3.fDeltaE");
tree->SetAlias("scat","tina3.fTheta");
tree->SetAlias("phi","tina3.fPhi");
tree->SetAlias("de'","de*sin(scat*3.141592/180.)");
tree->SetAlias("tke","tina3.fEnergy");
tree->SetAlias("ecsi","tke-de");
tree->SetAlias("ef","sqrt(de'*(de'+ecsi))");
tree->SetAlias("fid","tina3.fDefid");
tree->SetAlias("bid","tina3.fDebid");
tree->SetAlias("csiid","tina3.fEid");
tree->SetAlias("tinax","tina3.fX");
tree->SetAlias("tinay","tina3.fY");
tree->SetAlias("tinaxy","(tinax*tinax+tinay*tinay)<20.*20.");
tree->SetAlias("tinain","(tinax*tinax+tinay*tinay)<25.*25.");
tree->SetAlias("tinaout","(tinax*tinax+tinay*tinay)>25.*25.");
    
tree->SetAlias("pgate","ef>4.6&&ef<6.&&ecsi>0.5");
tree->SetAlias("ppgate","ef<6.&&ecsi==0.");

tree->SetAlias("beta","14.53993/tof912.fTiming/2.99792458*10.");
tree->SetAlias("gamma","1./sqrt(1.-beta*beta)");
tree->SetAlias("beam","(gamma-1.)*931.49410242");

tree->SetAlias("e1","129.8795*(931.49410242+beam)");
tree->SetAlias("p1","129.8795*sqrt(beam*(beam+2*931.49410242))");
tree->SetAlias("e3","1.0073*931.49410242+tke");
tree->SetAlias("p3","sqrt(tke*(tke+2*1.0073*931.49410242))");

tree->SetAlias("ex","sqrt(pow(e1+2.0136*931.49410242-e3,2)-(p1*p1+p3*p3-2*p1*p3*cos(scat*3.141592/180.)))-130.8817*931.49410242");

}