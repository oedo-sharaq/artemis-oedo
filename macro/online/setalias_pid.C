{


//tree->SetAlias("tof30","sr0_a_cal.fTiming - dia3pad[0].fTiming");
//tree->SetAlias("tof32","((dias2pad_tc842.fCharge-dia3pad_tc842.fCharge)+5.0e4)*1.e-3+2441.31");
tree->SetAlias("tof32v","(dias2pad[0].fTiming-dia3pad[0].fTiming)");
tree->SetAlias("s0.fX","sr0_xc0[0].fPosition + 49.28");
//tree->SetAlias("s0xc","s0.fX-24.0*(tof30-1066.)");
tree->SetAlias("s2de","1.03827*S2ssd.fEx*0.866");
tree->SetAlias("s2brho","4.4147*(1-sr0_xc0[0].fPosition/14856)");
tree->SetAlias("s2beta","103499.78 / ( 299.79 * tof32v - 299.79 * 1455. )");
tree->SetAlias("s2gamma","1./TMath::Sqrt(1-(s2beta)*(s2beta))");
tree->SetAlias("s2aq","s2brho * 299.79 / (s2gamma * s2beta * 931.49)");
tree->SetAlias("de_v","TMath::Log(5907.5*s2beta*s2beta)-TMath::Log(1.-s2beta*s2beta)-s2beta*s2beta");
tree->SetAlias("s2z"," -0.0513 + 7.451*TMath::Sqrt(s2de/de_v) * s2beta");
//tree->SetAlias("window","TMath::Abs(trig_s2w.fTiming-11)<10");

}
