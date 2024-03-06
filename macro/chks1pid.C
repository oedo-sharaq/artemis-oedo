{
  tree->SetAlias("x1","(550*sr11_xc0[0].fPosition-200*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x2","(515*sr11_xc0[0].fPosition-165*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x3","(480*sr11_xc0[0].fPosition-130*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x4","(445*sr11_xc0[0].fPosition-95*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x5","(410*sr11_xc0[0].fPosition-60*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x6","(375*sr11_xc0[0].fPosition-25*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x7","(340*sr11_xc0[0].fPosition+10*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x8","(305*sr11_xc0[0].fPosition+45*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x9","(270*sr11_xc0[0].fPosition+80*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x10","(235*sr11_xc0[0].fPosition+115*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x11","(200*sr11_xc0[0].fPosition+150*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x12","(165*sr11_xc0[0].fPosition+185*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x13","(130*sr11_xc0[0].fPosition+220*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x14","(95*sr11_xc0[0].fPosition+255*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x15","(60*sr11_xc0[0].fPosition+290*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x16","(25*sr11_xc0[0].fPosition+325*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x17","(-10*sr11_xc0[0].fPosition+360*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x18","(-45*sr11_xc0[0].fPosition+395*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x19","(-80*sr11_xc0[0].fPosition+430*sr12_xc0[0].fPosition)/350.");
  tree->SetAlias("x20","(-115*sr11_xc0[0].fPosition+465*sr12_xc0[0].fPosition)/350.");
  /*for (Int_t i = 1; i<=20; i++){
    tree->Draw(Form("x%d:tof12s1[0].fTiming>>S1pid%d(200,130,180,500,-200,200)",i,i),"fe9.pid56Ni","colz");
  }

  for (Int_t i = 1; i<=20; i++){
    tree->Draw(Form("0.0807711293476*x%d+0.996732674624*tof12s1[0].fTiming>>rot%d(200,130,180)",i,i),"fe9.pid56Ni","colz");
  }*/

  for (Int_t i = 1; i<=20; i++){
    tree->Draw(Form("x%d:tof912[0].fTiming>>S1pid%d(200,260,300,500,-200,200)",i,i),"fe9.pid56Ni","colz");
  }

  for (Int_t i = 1; i<=20; i++){
    tree->Draw(Form("0.0884392934507*x%d+0.996081568635*tof912[0].fTiming>>rot%d(200,260,300)",i,i),"fe9.pid56Ni","colz");
  }

}
