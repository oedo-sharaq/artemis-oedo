{
  tree->Draw("AoverQ:src.fX>>aqcx(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:src.fY>>aqcy(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:src.fA*1000>>aqca(200,-50,50,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:src.fB*1000>>aqcb(200,-50,50,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:sr1.fXcor>>aq1x(200,-200,200,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:sr1.fY>>aq1y(200,-200,200,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:sr1.fA*1000>>aq1a(200,-100,100,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:sr1.fB*1000>>aq1b(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:tof39[0].fTiming>>aqtof39(200,520,540,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ:tof12s1[0].fTiming>>aqtof12s1(200,130,180,200,1.8,2.4)","fe9.pid56Ni","colz");


}
