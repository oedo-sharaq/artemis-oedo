{
  for (int i = 0; i<8; i++){
    tree->Draw(Form("sr91_a_raw[%d].fTiming:csiS1.fCharge>>h%d(100,0,50,100,-25000,-15000)",i,i+1),Form("abs(sr91_a_raw[%d].fTiming+21000)<1500",i),"colz");
}
}
