{
  tree->SetAlias("sr91a", "sr91_a_cal");
  tree->SetAlias("sr92a", "sr92_a_cal");
  tree->SetAlias("src1a", "src1_a_cal");
  tree->SetAlias("src2a", "src2_a_cal");
  tree->SetAlias("sr11a", "sr11_a_cal");
  tree->SetAlias("dia", "abs(vf3dia.fTiming+3200)<200");
  tree->SetAlias("sr9a", "abs(sr91a.fTiming+2000)<200&&abs(sr92a.fTiming+2000)<200");
  tree->SetAlias("srca", "abs(src1a.fTiming+1850)<150&&abs(src2a.fTiming+1850)<150");
  tree->SetAlias("sr1a", "abs(sr11a.fTiming+1300)<300");
  tree->SetAlias("tgate0", "dia&&sr9a&&srca");
  tree->SetAlias("tt", "tinat.fID==6&&abs(tinat.fTiming-500)<50");
  tree->SetAlias("tgate", "dia&&sr9a&&srca&&sr1a&&tt");
  // tree->SetAlias("tof39","(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2-vf3dia[0].fTiming");
  // tree->SetAlias("tof39","tof39.fTiming");
  // tree->SetAlias("fe9.fT", "(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming)/2");
  tree->SetAlias("fe9.fT", "(sr91_a_cal[0].fTiming+sr92_a_cal[0].fTiming+sr91_x_cal[0].fTiming+sr92_x_cal[0].fTiming+sr91_y_cal[0].fTiming+sr92_y_cal[0].fTiming)/6");

  // tree->SetAlias("fe12.fT", "(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming)/2.");
  tree->SetAlias("fe12.fT", "(src1_a_cal[0].fTiming+src2_a_cal[0].fTiming+src1_x_cal[0].fTiming+src2_x_cal[0].fTiming+src1_y_cal[0].fTiming+src2_y_cal[0].fTiming)/6.");
  // tree->SetAlias("s1.fT", "(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming)/2.");
  tree->SetAlias("s1.fT", "(sr11_a_cal[0].fTiming+sr12_a_cal[0].fTiming+sr11_x_cal[0].fTiming+sr12_x_cal[0].fTiming+sr11_y_cal[0].fTiming+sr12_y_cal[0].fTiming)/6.");

  tree->SetAlias("tof39a", "fe9.fT-vf3dia.fTiming");

  // tofc1
  tree->SetAlias("t1", "sr11_a_cal[0].fTiming-src1_a_cal[0].fTiming-574.561819");
  tree->SetAlias("t2", "sr11_a_cal[0].fTiming-src1_x_cal[0].fTiming-609.811377");
  tree->SetAlias("t3", "sr11_a_cal[0].fTiming-src1_y_cal[0].fTiming-614.148327");
  tree->SetAlias("t4", "sr12_a_cal[0].fTiming-src1_a_cal[0].fTiming-582.498150");
  tree->SetAlias("t5", "sr12_a_cal[0].fTiming-src1_x_cal[0].fTiming-617.713225");
  tree->SetAlias("t6", "sr12_a_cal[0].fTiming-src1_y_cal[0].fTiming-622.133998");
  tree->SetAlias("t7", "sr11_x_cal[0].fTiming-src1_a_cal[0].fTiming-562.427502");
  tree->SetAlias("t8", "sr11_x_cal[0].fTiming-src1_x_cal[0].fTiming-597.503947");
  tree->SetAlias("t9", "sr11_x_cal[0].fTiming-src1_y_cal[0].fTiming-601.974311");
  tree->SetAlias("t10", "sr12_x_cal[0].fTiming-src1_a_cal[0].fTiming-548.813072");
  tree->SetAlias("t11", "sr12_x_cal[0].fTiming-src1_x_cal[0].fTiming-583.781565");
  tree->SetAlias("t12", "sr12_x_cal[0].fTiming-src1_y_cal[0].fTiming-588.237274");
  tree->SetAlias("t13", "sr11_y_cal[0].fTiming-src1_a_cal[0].fTiming-555.473732");
  tree->SetAlias("t14", "sr11_y_cal[0].fTiming-src1_x_cal[0].fTiming-590.567106");
  tree->SetAlias("t15", "sr11_y_cal[0].fTiming-src1_y_cal[0].fTiming-594.905498");
  tree->SetAlias("t16", "sr12_y_cal[0].fTiming-src1_a_cal[0].fTiming-558.546560");
  tree->SetAlias("t17", "sr12_y_cal[0].fTiming-src1_x_cal[0].fTiming-593.744353");
  tree->SetAlias("t18", "sr12_y_cal[0].fTiming-src1_y_cal[0].fTiming-598.137554");
  tree->SetAlias("t19", "sr11_a_cal[0].fTiming-src2_a_cal[0].fTiming-575.915231"); // best resolution
  tree->SetAlias("t20", "sr11_a_cal[0].fTiming-src2_x_cal[0].fTiming-599.286191");
  tree->SetAlias("t21", "sr11_a_cal[0].fTiming-src2_y_cal[0].fTiming-605.701367");
  tree->SetAlias("t22", "sr12_a_cal[0].fTiming-src2_a_cal[0].fTiming-583.902072");
  tree->SetAlias("t23", "sr12_a_cal[0].fTiming-src2_x_cal[0].fTiming-607.261279");
  tree->SetAlias("t24", "sr12_a_cal[0].fTiming-src2_y_cal[0].fTiming-613.741849");
  tree->SetAlias("t25", "sr11_x_cal[0].fTiming-src2_a_cal[0].fTiming-563.733997");
  tree->SetAlias("t26", "sr11_x_cal[0].fTiming-src2_x_cal[0].fTiming-587.068288");
  tree->SetAlias("t27", "sr11_x_cal[0].fTiming-src2_y_cal[0].fTiming-593.337300");
  tree->SetAlias("t28", "sr12_x_cal[0].fTiming-src2_a_cal[0].fTiming-550.147042");
  tree->SetAlias("t29", "sr12_x_cal[0].fTiming-src2_x_cal[0].fTiming-573.385461");
  tree->SetAlias("t30", "sr12_x_cal[0].fTiming-src2_y_cal[0].fTiming-579.682603");
  tree->SetAlias("t31", "sr11_y_cal[0].fTiming-src2_a_cal[0].fTiming-556.853850");
  tree->SetAlias("t32", "sr11_y_cal[0].fTiming-src2_x_cal[0].fTiming-579.991432");
  tree->SetAlias("t33", "sr11_y_cal[0].fTiming-src2_y_cal[0].fTiming-586.297266");
  tree->SetAlias("t34", "sr12_y_cal[0].fTiming-src2_a_cal[0].fTiming-559.899643");
  tree->SetAlias("t35", "sr12_y_cal[0].fTiming-src2_x_cal[0].fTiming-583.240278");
  tree->SetAlias("t36", "sr12_y_cal[0].fTiming-src2_y_cal[0].fTiming-589.707862");
  tree->SetAlias("tofc1", "s1.fT-fe12.fT-585.479");
  tree->SetAlias("tofc1_2", "(t1+t2+t3+t4+t5+t6+t7+t8+t9+t10+t11+t12+t13+t14+t15+t16+t17+t18+t19+t20+t21+t22+t23+t24+t25+t26+t27+t28+t29+t30+t31+t32+t33+t34+t35+t36)/36.");
  tree->SetAlias("t_anode", "(t1+t4+t19+t22)/4");
  tree->SetAlias("t_cathode", "(t8+t9+t11+t12+t14+t15+t17+t18+t26+t27+t29+t30+t32+t33+t35+t36)/16");
  // tree->SetAlias("tofc1", "t22");

  tree->SetAlias("tofc1_3", "(t1+t2+t3+t4+t5+t6+t16+t17+t18+t19+t20+t21+t22+t23+t24+t34+t35+t36)/18.");
  tree->SetAlias("tofc1_4", "(t7+t8+t9+t10+t11+t12+t13+t14+t15+t25+t26+t27+t28+t29+t30+t31+t32+t33)/18.");

  // tree->SetAlias("sr9.fX", "(541*sr91_xc0[0].fPosition-122.5*sr92_xc0[0].fPosition)/418.5");
  tree->SetAlias("sr9.fX", "(542.25*sr91_xc0[0].fPosition-122.5*sr92_xc0[0].fPosition)/419.75");
  tree->SetAlias("sr9.fA", "(sr92_xc0[0].fPosition-sr91_xc0[0].fPosition)/419.75");
  tree->SetAlias("sr9.fY", "(542.25*sr91_yc0[0].fPosition-122.5*sr92_yc0[0].fPosition)/419.75");
  tree->SetAlias("sr9.fB", "(sr92_yc0[0].fPosition-sr91_yc0[0].fPosition)/419.75");
  tree->SetAlias("src.fX", "(1972*src2_xc0[0].fPosition-1452*src1_xc0[0].fPosition)/520.");
  tree->SetAlias("src.fA", "(src2_xc0[0].fPosition-src1_xc0[0].fPosition)/520.");
  tree->SetAlias("src.fY", "(1972*(src2_yc0[0].fPosition-31)-1452*(src1_yc0[0].fPosition-31))/520.");
  tree->SetAlias("src.fB", "((src2_yc0[0].fPosition-31)-(src1_yc0[0].fPosition-31))/520");
  tree->SetAlias("sr1.fX", "(560.8*sr12_xc0[0].fPosition-210.8*sr11_xc0[0].fPosition)/350.");
  tree->SetAlias("sr1.fXcor", "(190.762*sr12_xc0[0].fPosition+159.238*sr11_xc0[0].fPosition)/350.");
  tree->SetAlias("sr1.fXcor2", "(236.205*sr12_xc0[0].fPosition+113.795*sr11_xc0[0].fPosition)/350."); //<s1> - <fe12>
  tree->SetAlias("sr1.fXcor3", "(235.581*sr12_xc0[0].fPosition+114.491*sr11_xc0[0].fPosition)/350."); // <s1-fe12>
  tree->SetAlias("sr1.fXcor4", "(140.246*sr12_xc0[0].fPosition+209.754*sr11_xc0[0].fPosition)/350."); // t22

  // tree->SetAlias("sr1.fXcor2", "0.945007806854*sr1.fXcor+0.327047771717*sr1.fA*1000");
  // tree->SetAlias("sr1.fXcor2", "-0.945007806854*sr1.fA*1000+0.327047771717*sr1.fXcor");
  // tree->SetAlias("sr1.fXcor", "0.309453825214*sr1.fX-0.950914470423*sr1.fA*1000");
  // tree->SetAlias("sr1.fX", "sr11_xc0[0].fPosition");
  tree->SetAlias("sr1.fA", "(sr12_xc0[0].fPosition-sr11_xc0[0].fPosition)/350.");
  tree->SetAlias("sr1.fY", "(560.8*sr12_yc0[0].fPosition-210.8*sr11_yc0[0].fPosition)/350.");
  tree->SetAlias("sr1.fB", "(sr12_yc0[0].fPosition-sr11_yc0[0].fPosition)/350.");

  tree->SetAlias("s1beta", "7.813/tof12s1[0].fTiming/2.99792458*10.");
  // tree->SetAlias("sr1.fX", "sr11_xc0[0].fPosition");
  // tree->SetAlias("sr1.fX", "(560.8*sr12_xc0[0].fPosition-210.8*sr11_xc0[0].fPosition)/350.");
  // tree->SetAlias("sr1.fY", "sr11_yc0[0].fPosition");
  tree->SetAlias("fe9.pid", "0.987494493767*tof39[0].fTiming+0.15765349593*sr9.fX");
  tree->SetAlias("fe9.pid56Ni", "abs(fe9.pid-524)<2.5");
  tree->SetAlias("pid1", "abs(tofc1-730)<20");
  tree->SetAlias("S1.pid", "0.996716791378*tof12s1[0].fTiming+0.0809668931441*sr1.fXcor"); // anode timing
  tree->SetAlias("S1.pid2", "0.996460817614*tofc1+0.0840585448375*sr1.fXcor2");            // anode & cathode
  tree->SetAlias("S1.pid3", "0.996460817614*tofc1_2+0.0840585448375*sr1.fXcor3");          // anode & cathode
  tree->SetAlias("S1.pid4", "0.99637176564*t22+0.0851076062154*sr1.fXcor4");
  tree->SetAlias("S1.pid5", "0.996460817614*tofc1_3+0.0840585448375*sr1.fXcor2");
  tree->SetAlias("AoverQ", "0.015122*S1.pid-0.160662");

  // tree->SetAlias("S1.pidcor", "0.996732674624*tof12s1[0].fTiming+0.0807711293476*sr1.fXcor");
  // tree->SetAlias("AoverQcor", "0.014975*S1.pidcor-0.139161");
  tree->SetAlias("AoverQcor", "AoverQ+7.09278e-6*src.fA*1000-2.77791e-5*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQcor2", "AoverQcor-3.86099e-6*sr1.fXcor-1.15423e-6*pow(sr1.fXcor,2)");
  tree->SetAlias("AoverQcor3", "AoverQcor2+5.981e-5*sr1.fY+1.04652e-6*pow(sr1.fY,2)");
  tree->SetAlias("AoverQcor4", "AoverQcor3-5.63609e-5*sr1.fA*1000+4.2966e-6*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQcor5", "AoverQcor4+0.0179878*tof12s1[0].fTiming-6.15812e-5*pow(tof12s1[0].fTiming,2)");

  tree->SetAlias("AQ", "1.0189171*AoverQcor5-1.3744196");
  // tof12s1: anode + cathode timing  <s1> - <fe12>
  tree->SetAlias("AoverQ2", "0.0142785*S1.pid2-0.0347269");
  /*tree->SetAlias("AoverQ2cor", "AoverQ2-0.000110515*src.fA*1000-2.90098e-5*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ2cor2", "AoverQ2cor+6.19531e-06*sr1.fXcor2-7.0951e-07*pow(sr1.fXcor2,2)");
  tree->SetAlias("AoverQ2cor3", "AoverQ2cor2-0.000176646*sr1.fY+5.69038e-07*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ2cor4", "AoverQ2cor3-7.11126e-05*sr1.fA*1000+3.81137e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ2cor5", "AoverQ2cor4+0.0147119*tofc1-4.97237e-05*pow(tofc1,2)");
  tree->SetAlias("AoverQ2cor6", "1.0299128*AoverQ2cor5-1.1757907");
  tree->SetAlias("AoverQ2cor7", "AoverQ2cor6-0.0496553*tof39[0].fTiming+4.48113e-05*pow(tof39[0].fTiming,2)");
  tree->SetAlias("AQ2", "1.0108157*AoverQ2cor7+13.8579405");*/

  tree->SetAlias("AoverQ2cor", "AoverQ2-0.000110515*src.fA*1000-2.90098e-5*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ2cor2", "AoverQ2cor+6.19531e-06*sr1.fXcor2-7.0951e-07*pow(sr1.fXcor2,2)");
  tree->SetAlias("AoverQ2cor3", "AoverQ2cor2-0.000176646*sr1.fY+5.69038e-07*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ2cor4", "AoverQ2cor3-7.11126e-05*sr1.fA*1000+3.81137e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ2cor5", "AoverQ2cor4+0.0147119*tofc1-4.97237e-05*pow(tofc1,2)");
  tree->SetAlias("AoverQ2cor6", "1.0299128*AoverQ2cor5-1.1757907");
  tree->SetAlias("AoverQ2cor7", "AoverQ2cor6 +13.7 -0.0496553*tof39[0].fTiming+4.48113e-05*pow(tof39[0].fTiming,2)");
  tree->SetAlias("AoverQ2cor8", "AoverQ2cor7 +0.0118129*tof912[0].fTiming-2.04847e-05*pow(tof912[0].fTiming,2)");

  // tree->SetAlias("AoverQ2cor9", "AoverQ2cor8-5.9157e-05*src.fX+1.01246e-05*pow(src.fX,2)");
  tree->SetAlias("AQ2", "0.9998738*AoverQ2cor8 - 1.669164");

  // tofc1: <s1-fe12>
  tree->SetAlias("AoverQ3", "0.0142785*S1.pid3-0.0347269");
  tree->SetAlias("AoverQ3cor", "AoverQ3-0.000110515*src.fA*1000-2.90098e-5*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ3cor2", "AoverQ3cor+6.19531e-06*sr1.fXcor2-7.0951e-07*pow(sr1.fXcor2,2)");
  tree->SetAlias("AoverQ3cor3", "AoverQ3cor2-0.000176646*sr1.fY+5.69038e-07*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ3cor4", "AoverQ3cor3-7.11126e-05*sr1.fA*1000+3.81137e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ3cor5", "AoverQ3cor4+0.0147119*tofc1_2-4.97237e-05*pow(tofc1_2,2)");
  tree->SetAlias("AoverQ3cor6", "1.0299128*AoverQ3cor5-1.1757907");
  tree->SetAlias("AoverQ3cor7", "AoverQ3cor6 +13.7 -0.0496553*tof39[0].fTiming+4.48113e-05*pow(tof39[0].fTiming,2)");
  tree->SetAlias("AoverQ3cor8", "AoverQ3cor7 +0.0118129*tof912[0].fTiming-2.04847e-05*pow(tof912[0].fTiming,2)");
  tree->SetAlias("AQ3", "0.9981701*AoverQ3cor8 - 1.6599778");

  /*tree->SetAlias("AoverQ3", "0.0142655*S1.pid2-0.0301105");
  tree->SetAlias("AoverQ3cor", "AoverQ3+0.00026958*sr9.fA*1000-1.4635e-05*pow(sr9.fA*1000,2)");
  tree->SetAlias("AoverQ3cor2", "AoverQ3cor+0.000335457*sr9.fB*1000+1.24808e-05*pow(sr9.fB*1000,2)");
  tree->SetAlias("AoverQ3cor3", "AoverQ3cor2-0.000269532*src.fX+2.73652e-05*pow(src.fX,2)");
  tree->SetAlias("AoverQ3cor4", "AoverQ3cor3+7.18041e-05*src.fA*1000-1.98024e-05*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ3cor5", "AoverQ3cor4+2.29609e-05*sr1.fXcor3-7.76118e-07*pow(sr1.fXcor3,2)");
  tree->SetAlias("AoverQ3cor6", "AoverQ3cor5-0.000140936*sr1.fY+1.9842e-07*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ3cor7", "AoverQ3cor6-2.65024e-05*sr1.fA*1000+3.10842e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ3cor8", "AoverQ3cor7 +9.17 -0.0334171*tof39[0].fTiming+3.04722e-05*pow(tof39[0].fTiming,2)");
  tree->SetAlias("AoverQ3cor9", "AoverQ3cor8 +0.0268017*tof912[0].fTiming-4.70953e-05*pow(tof912[0].fTiming,2)");
  tree->SetAlias("AQ3", "0.9941553*AoverQ3cor9 - 3.7935328");*/

  // tof12s1: t22
  tree->SetAlias("AoverQ4", "0.0149515*S1.pid4-0.1346105");
  tree->SetAlias("AoverQ4cor", "AoverQ4-0.000305466*src.fX + 2.44379e-05*pow(src.fX,2)");
  tree->SetAlias("AoverQ4cor2", "AoverQ4cor+0.00032334*src.fA*1000 - 2.70455e-05*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ4cor3", "AoverQ4cor2 - 1.9073e-05*sr1.fXcor4 - 9.21555e-07*pow(sr1.fXcor4,2)");
  tree->SetAlias("AoverQ4cor4", "AoverQ4cor3 + 5.95676e-05*sr1.fY + 8.8435e-07*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ4cor5", "AoverQ4cor4 - 2.18451e-05*sr1.fA*1000 + 2.65353e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ4cor6", "AoverQ4cor5  + 0.0137276*t22 - 4.71204e-05*pow(t22,2)");
  tree->SetAlias("AQ4", "0.9936189*AoverQ4cor6 - 0.9788020");

  // tof12s1: w/o sr11_x,sr12_x,sr11_y as stop time
  tree->SetAlias("AoverQ5", "0.0143254*S1.pid5-0.0398932");
  tree->SetAlias("AoverQ5cor", "AoverQ5-0.000399685*src.fX + 1.5529e-05*pow(src.fX,2)");
  tree->SetAlias("AoverQ5cor2", "AoverQ5cor+4.3722e-05*src.fA*1000 - 2.78598e-05*pow(src.fA*1000,2)");
  tree->SetAlias("AoverQ5cor3", "AoverQ5cor2 + 1.72401e-05*sr1.fXcor2 - 7.44146e-07*pow(sr1.fXcor2,2)");
  tree->SetAlias("AoverQ5cor4", "AoverQ5cor3 + 1.0438e-05*sr1.fY + 1.07135e-06*pow(sr1.fY,2)");
  tree->SetAlias("AoverQ5cor5", "AoverQ5cor4 - 1.39775e-05*sr1.fA*1000 + 2.90419e-06*pow(sr1.fA*1000,2)");
  tree->SetAlias("AoverQ5cor6", "AoverQ5cor5 +0.0269121*tof912[0].fTiming-4.76695e-05*pow(tof912[0].fTiming,2)");
  tree->SetAlias("AQ5", "0.9831843*AoverQ5cor6-3.6971143");

  tree->SetAlias("S1.pid56Ni_He", "abs(AoverQ-2.16)<0.04");
  tree->SetAlias("S1.pid56Ni_H", "abs(AoverQ-2.08)<0.04");
  tree->SetAlias("S1.pid56Ni_0", "abs(AoverQ-1.99)<0.03");

  tree->SetAlias("coins0", "abs(coin_s0.fTiming-43050.)<200.");

  // missing mass
  tree->SetAlias("de", "tina3.fDeltaE");
  tree->SetAlias("theta", "tina3.fScat");
  // tree->SetAlias("theta","tina3.fTheta");
  tree->SetAlias("phi", "tina3.fPhi");
  tree->SetAlias("teff", "tina3.fTrack");
  tree->SetAlias("de'", "de*0.3/teff");
  // tree->SetAlias("ecsi","tina3.fEcsicalc");
  tree->SetAlias("ecsi", "tina3.fEcsi");
  tree->SetAlias("tke", "de+ecsi");
  tree->SetAlias("ef", "sqrt(de'*(de'+ecsi))");
  tree->SetAlias("pgate1", "ef>4&&ef<6.15&&ecsi>0.5"); // penetrate events
  tree->SetAlias("pgate2", "ecsi==0");                 // stopped events
  tree->SetAlias("pgate", "pgate1||pgate2");
  tree->SetAlias("tke2", "de+tina3.fEcsicalc");
  // tree->SetAlias("yy1id","tina3.fDeid");
  // tree->SetAlias("csiid","tina3.fEid");
  tree->SetAlias("tinax", "tina3.fX");
  tree->SetAlias("tinay", "tina3.fY");
  tree->SetAlias("tinaxy", "(tinax*tinax+tinay*tinay)<25.*25.");
  // tree->SetAlias("tinain","(tinax*tinax+tinay*tinay)<25.*25.");
  tree->SetAlias("tinaout", "(tinax*tinax+tinay*tinay)>25.*25.");
  tree->SetAlias("mu", "931.49410242*1"); // amu
  // tree->SetAlias("tof", "tof912.fTiming-(287.553-275.281682971)"); // corrected using centeral  brho at S1
  tree->SetAlias("tof", "tof912.fTiming");
  tree->SetAlias("beta", "14.87168/tof/2.99792458*10.");
  tree->SetAlias("gamma", "1./sqrt(1.-beta*beta)");
  // tree->SetAlias("beam", "(gamma-1.)*mu+1.1202"); // MeV/u all 56Ni
  tree->SetAlias("beam", "(gamma-1.)*mu+0.7459"); // MeV/u 56Ni H-like

  // tree->SetAlias("beam", "(gamma-1.)*mu+0.9791");
  // tree->SetAlias("beam","15.5*1"); // MeV/u
  tree->SetAlias("m1", "55.92681*1");   // beam
  tree->SetAlias("m2", "2.01355*1");    // target
  tree->SetAlias("m3", "1.00728*1");    // recoil
  tree->SetAlias("m4", "56.92448*1");   // residue
  tree->SetAlias("e1", "m1*(mu+beam)"); // MeV
  tree->SetAlias("p1", "m1*sqrt(beam*(beam+2*mu))");
  tree->SetAlias("e3", "m3*mu+tke");                  // MeV
  tree->SetAlias("e32", "m3*mu+tke2");                // MeV
  tree->SetAlias("p3", "sqrt(tke*(tke+2*m3*mu))");    // MeV
  tree->SetAlias("p32", "sqrt(tke2*(tke2+2*m3*mu))"); // MeV
  tree->SetAlias("ex", "sqrt(pow(m1*mu,2)+pow(m2*mu,2)+pow(m3*mu,2)+2*m2*mu*(e1-e3)-2*e1*e3+2*p1*p3*cos(theta*TMath::Pi()/180.))-m4*mu");
  tree->SetAlias("ex2", "sqrt(pow(m1*mu,2)+pow(m2*mu,2)+pow(m3*mu,2)+2*m2*mu*(e1-e32)-2*e1*e32+2*p1*p32*cos(theta*TMath::Pi()/180.))-m4*mu");

  // IC
  // tree->SetAlias("dEb", "icde[0].fValue-(-224810+5.13318e6*s1beta-4.3905e7*s1beta*s1beta+1.66754e8*pow(s1beta,3)-2.37316e8*pow(s1beta,4))");
  tree->SetAlias("dEb", "icde[0].fValue - 122.982 + 755.063*s1beta");
  tree->SetAlias("yid1", "sr1.fX+sr1.fB*(778.75+25.25*1+12.625)*sqrt(1+sr1.fA^2)"); // y at pad id = 1
  tree->SetAlias("dEy", "dEb-(0.000162935*yid1^2+0.015278*yid1)");
}
