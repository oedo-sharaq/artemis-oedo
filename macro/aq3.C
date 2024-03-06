{
  tree->Draw("AoverQ3:src.fX>>aqcx(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:src.fY>>aqcy(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:src.fA*1000>>aqca(200,-50,50,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:src.fB*1000>>aqcb(200,-50,50,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:sr1.fXcor3>>aq1x(200,-200,200,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:sr1.fY>>aq1y(200,-200,200,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:sr1.fA*1000>>aq1a(200,-100,100,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:sr1.fB*1000>>aq1b(200,-30,30,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:tof39[0].fTiming>>aqtof39(200,520,540,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:tof912[0].fTiming>>aqtof912(200,260,300,200,1.8,2.4)","fe9.pid56Ni","colz");
  tree->Draw("AoverQ3:tofc1>>aqtof12s1(200,130,180,200,1.8,2.4)","fe9.pid56Ni","colz");


}
