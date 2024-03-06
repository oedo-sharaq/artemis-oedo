{
    tree->SetAlias("sr9.fX", "(542.25*sr91_xc0[0].fPosition-122.5*sr92_xc0[0].fPosition)/419.75");
    tree->SetAlias("sr9.fA", "(sr92_xc0[0].fPosition-sr91_xc0[0].fPosition)/419.75");
    tree->SetAlias("sr9.fY", "(542.25*sr91_yc0[0].fPosition-122.5*sr92_yc0[0].fPosition)/419.75");
    tree->SetAlias("sr9.fB", "(sr92_yc0[0].fPosition-sr91_yc0[0].fPosition)/419.75");
    tree->SetAlias("src.fX", "(1972*src2_xc0[0].fPosition-1452*src1_xc0[0].fPosition)/520.");
    tree->SetAlias("src.fA", "(src2_xc0[0].fPosition-src1_xc0[0].fPosition)/520.");
    tree->SetAlias("src.fY", "(1972*(src2_yc0[0].fPosition-31)-1452*(src1_yc0[0].fPosition-31))/520.");
    tree->SetAlias("src.fB", "((src2_yc0[0].fPosition-31)-(src1_yc0[0].fPosition-31))/520");
    // tree->SetAlias("sr1.fX", "(560.8*sr12_xc0[0].fPosition-210.8*sr11_xc0[0].fPosition)/350.");
    tree->SetAlias("sr1.fX", "sr11_xc0[0].fPosition");
    tree->SetAlias("sr1.fA", "(sr12_xc0[0].fPosition-sr11_xc0[0].fPosition)/350.");
    tree->SetAlias("sr1.fY", "(560.8*sr12_yc0[0].fPosition-210.8*sr11_yc0[0].fPosition)/350.");
    tree->SetAlias("sr1.fB", "(sr12_yc0[0].fPosition-sr11_yc0[0].fPosition)/350.");

    tree->SetAlias("betas0s1", "7.813/tof12s1[0].fTiming/2.99792458*10.");

    // 56Ni
    ////////////////////////////////////////////////////////////////////////////////////////////////
    tree->SetAlias("fe9.pid", "tof39[0].fTiming*0.98848568+sr9.fX*0.15131442");
    tree->SetAlias("fe9.pid56Ni", "abs(tof39[0].fTiming*0.98848568+sr9.fX*0.15131442-525)<4");   // Ni
    tree->SetAlias("fe9.pid55Co", "abs(tof39[0].fTiming*0.98848568+sr9.fX*0.15131442-532.5)<4"); // Co
    tree->SetAlias("fe9.pid54Fe", "abs(tof39[0].fTiming*0.98848568+sr9.fX*0.15131442-541.2)<4"); // Fe
    tree->SetAlias("fe9.pidNibld", "abs(tof39[0].fTiming*0.98848568+sr9.fX*0.15131442-520)<4");  // run0048

    tree->SetAlias("S1.pid", "tof12s1[0].fTiming-(-0.0850653*sr1.fX+0.00012864*sr1.fX^2)");
    tree->SetAlias("AoverQ", "S1.pid*0.0151889125293099-0.173823503447266");
    tree->SetAlias("AoverQa", "AoverQ-(-0.325338*src.fA+27.3295*src.fA^2)");
    tree->SetAlias("AoverQaa", "AoverQa-(-0.037351*sr1.fA-4.3895*sr1.fA^2)");

    // IC
    tree->SetAlias("dEb", "icde[0].fValue-(3.37879e+06*(betas0s1^2-0.008427)^2-12144.2*(betas0s1^2-0.008427))"); // prm wrong, need change
    tree->SetAlias("yid1", "sr1.fX+sr1.fB*(778.75+25.25*1+12.625)*sqrt(1+sr1.fA^2)");                            // y at pad id = 1
    tree->SetAlias("dEy", "dEb-(0.000162935*yid1^2+0.015278*yid1)");                                             // prm wrong, need change

    // fitTree = after using AnaSakuraIC.cc
    // fitTree->SetAlias("ycal","s1y+s1b*(778.75+25.25*fitres+12.625)*sqrt(1+s0a^2)");//y at peak pad
    // fitTree->SetAlias("peaky","peak-(0.000650846*ycal+2.51869e-06*ycal^2)");
    // fitTree->SetAlias("rangeb","range-1/2.48245e-06*(betas0s1^2-0.008467)"); //prm wrong, need change

    // 58Ni
    ///////////////////////////////////////////////////////////////////////////////////////////
    // tree->SetAlias("fe9.pid", "tof39[0].fTiming");
    // tree->SetAlias("fe9.pid59Cu", "abs(tof39[0].fTiming-525)<3");   // Cu
    // tree->SetAlias("fe9.pid58Ni", "abs(tof39[0].fTiming-532.8)<3"); // Ni
    // tree->SetAlias("fe9.pid57Co", "abs(tof39[0].fTiming-541.2)<3"); // Co

    // // S1.pid
    // tree->SetAlias("S1.pid", "tof12s1[0].fTiming-sr1.fX*(-7.908043e-02)");
    // tree->SetAlias("S1.pida", "S1.pid-(15.5421*sr1.fA-260.167*sr1.fA^2)");
    // tree->SetAlias("S1.pidax", "S1.pida-src.fX*0.0569355");
    // tree->SetAlias("S1.pidaxy", "S1.pidax-(0.0629224*src.fY-0.00352941*src.fY^2)");
    // tree->SetAlias("AoverQ", "S1.pidaxy*0.0141402126381743-0.106428264616341");

    // // IC
    // tree->SetAlias("dEb", "icde[0].fValue-(82178.4*(betas0s1^2-0.0267)^2-1709.92*(betas0s1^2-0.0267))"); // beta calibration
    // tree->SetAlias("Z", "0.440528634361251*dEb+19.6211453744492");                                       // dEb → Z

    // // fitTree->SetAlias("rangeb","range-6.941370e+04*(beta^2-0.02635)");

    // // A/Q gate
    // tree->SetAlias("59Ni", "(AoverQ>2.085&&AoverQ<2.12)||(AoverQ>2.165&&AoverQ<2.205)||(AoverQ>2.245&&AoverQ<2.29)||(AoverQ>2.34&&AoverQ<2.38)");
    // tree->SetAlias("58NiCo", "(AoverQ>2.12&&AoverQ<2.165)||(AoverQ>2.205&&AoverQ<2.25)||(AoverQ>2.29&&AoverQ<2.34)");
    // tree->SetAlias("58Ni", "AoverQ>2.03&&AoverQ<2.085");
}