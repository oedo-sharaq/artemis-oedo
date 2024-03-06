{
  tree->Draw("AoverQ4:sr9.fX>>aq9x(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr9.fY>>aq9y(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr9.fA*1000>>aq9a(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr9.fB*1000>>aq9b(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:src.fX>>aqcx(200,-30,30,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:src.fY>>aqcy(200,-30,30,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:src.fA*1000>>aqca(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:src.fB*1000>>aqcb(200,-50,50,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr1.fXcor2>>aq1x(200,-200,200,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr1.fY>>aq1y(200,-200,200,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr1.fA*1000>>aq1a(200,-100,100,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:sr1.fB*1000>>aq1b(200,-30,30,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:tof39[0].fTiming>>aqtof39(200,520,540,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:tof912[0].fTiming>>aqtof912(200,260,300,200,1.8,2.4)", "fe9.pid56Ni", "colz");
  tree->Draw("AoverQ4:tofc1>>aqtof12s1(200,130,180,200,1.8,2.4)", "fe9.pid56Ni", "colz");
}
