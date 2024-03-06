{
  tree->SetAlias("sr91a", "sr91_a_cal");
  tree->SetAlias("sr92a", "sr92_a_cal");
  tree->SetAlias("src1a", "src1_a_cal");
  tree->SetAlias("src2a", "src2_a_cal");
  tree->SetAlias("sr11a", "sr11_a_cal");
  // tree->SetAlias("sr12a","sr12_a_cal");
  tree->SetAlias("dia", "abs(vf3dia.fTiming+2425)<125");
  tree->SetAlias("sr9a", "abs(sr91a.fTiming+1300)<100&&abs(sr92a.fTiming+1300)<100");
  tree->SetAlias("srca", "abs(src1a.fTiming+1100)<50&&abs(src2a.fTiming+1100)<50");
  tree->SetAlias("sr1a", "abs(sr11a.fTiming+350)<50");

  tree->SetAlias("yy1t", "tinat.fID<6&&abs(tinat.fTiming-350)<50");
  tree->SetAlias("tgate", "dia&&sr9a&&srca&&sr1a");
  tree->SetAlias("tgate0", "dia&&sr9a&&srca");

  tree->SetAlias("fe9.fT", "(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
  tree->SetAlias("fe12.fT", "(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2");
  tree->SetAlias("s1.fT", "sr11_a_cal[0].fTiming");
  // tree->SetAlias("tof39a","fe9.fT-f3dia2.fTiming");
  tree->SetAlias("tof39a", "fe9.fT-vf3dia.fTiming");
  tree->SetAlias("fe9.pid", "0.987595*tof39a+0.1570236*sr9.fX");
  tree->SetAlias("pid", "abs(fe9.pid-1160)<4");
  tree->SetAlias("Co", "abs(fe9.pid-1168.5)<3.5");
  tree->SetAlias("Fe", "abs(fe9.pid-1177)<4");
  tree->SetAlias("sr9.fX", "(541*sr91_xc0[0].fPosition-122.5*sr92_xc0[0].fPosition)/418.5");
  tree->SetAlias("coins0", "abs(coin_s0.fTiming-43000.)<500.");
  //  tree->SetAlias("coins0","abs(coin_s0.fTiming-43065.)<135.");
  tree->SetAlias("src.fX", "(2017.*src2_x[0].fPosition-1517.*src1_x[0].fPosition)/520.");
  tree->SetAlias("sr1.fX", "(560.8*sr12_xc0[0].fPosition-210.8*sr11_xc0[0].fPosition)/350.");
  tree->SetAlias("yy5", "abs(yy1f.fID-71.5)<8.5");

  // missing mass
  tree->SetAlias("de", "tina2.fDeltaE");
  // tree->SetAlias("theta","tina2.fTheta");
  tree->SetAlias("theta", "tina2.fScat");
  tree->SetAlias("phi", "tina2.fPhi");
  tree->SetAlias("de'", "de*cos((theta-140.)*TMath::Pi()/180.)");
  //  tree->SetAlias("tke","tina2.fEnergy");
  tree->SetAlias("tke", "tina2.fDeltaE");
  tree->SetAlias("ecsi", "tke-de");
  tree->SetAlias("ef", "sqrt(de'*(de'+ecsi))");
  tree->SetAlias("yy1id", "tina2.fDeid");
  tree->SetAlias("csiid", "tina2.fEid");
  tree->SetAlias("tinax", "tina2.fX");
  tree->SetAlias("tinay", "tina2.fY");
  tree->SetAlias("tinaxy", "(tinax*tinax+tinay*tinay)<25.*25.");
  // tree->SetAlias("tinain","(tinax*tinax+tinay*tinay)<25.*25.");
  tree->SetAlias("tinaout", "(tinax*tinax+tinay*tinay)>25.*25.");
  tree->SetAlias("mu", "931.49410242*1"); // amu
  // tree->SetAlias("tof", "tof912.fTiming-(287.553-275.281682971)"); // corrected using centeral  brho at S1
  tree->SetAlias("tof", "tof912.fTiming");
  tree->SetAlias("beta", "14.87168/tof/2.99792458*10.");
  tree->SetAlias("gamma", "1./sqrt(1.-beta*beta)");
  tree->SetAlias("beam", "(gamma-1.)*mu+1.388"); // MeV/u
  // tree->SetAlias("beam","15.5*1"); // MeV/u
  tree->SetAlias("m1", "55.92681*1");   // beam
  tree->SetAlias("m2", "2.01355*1");    // target
  tree->SetAlias("m3", "1.00728*1");    // recoil
  tree->SetAlias("m4", "56.92448*1");   // residue
  tree->SetAlias("e1", "m1*(mu+beam)"); // MeV
  tree->SetAlias("p1", "m1*sqrt(beam*(beam+2*mu))");
  tree->SetAlias("e3", "m3*mu+de");              // MeV
  tree->SetAlias("p3", "sqrt(de*(de+2*m3*mu))"); // MeV
  tree->SetAlias("ex", "sqrt(pow(m1*mu,2)+pow(m2*mu,2)+pow(m3*mu,2)+2*m2*mu*(e1-e3)-2*e1*e3+2*p1*p3*cos(theta*TMath::Pi()/180.))-m4*mu");
  // tree->SetAlias("dex","sqrt(pow(e1+2.0136*mu-de3,2)-(p1*p1+dp3*dp3-2*p1*dp3*cos(theta*TMath::Pi()/180.)))-130.8817*mu");
}
