void chksreffQ2(){

 Int_t nData = tree->GetEntries();

 Double_t sr91x_nHitTwo = tree->GetEntries("TMath::Abs(sr91_x_cal[0].fID - sr91_x_cal[1].fID) < 2");
 Double_t sr91x_nHitThree = tree->GetEntries("(sr91_x_cal[1].fID + sr91_x_cal[2].fID) == sr91_x_cal[0].fID*2");


 Double_t effsr91x = 100. * (sr91x_nHitThree / sr91x_nHitTwo);
    cout << " -- Q2 Efficiency of sr91 X --" << endl;
    cout << "  "  << effsr91x << " % " << endl ;

 Double_t sr91y_nHitTwo = tree->GetEntries("TMath::Abs(sr91_y_cal[0].fID - sr91_y_cal[1].fID) < 2");
 Double_t sr91y_nHitThree = tree->GetEntries("(sr91_y_cal[1].fID + sr91_y_cal[2].fID) == sr91_y_cal[0].fID*2");


 Double_t effsr91y = 100. * (sr91y_nHitThree / sr91y_nHitTwo);
    cout << " -- Q2 Efficiency of sr91 Y --" << endl;
    cout << "  "  << effsr91y  << " % " << endl;
  
 Double_t sr92x_nHitTwo = tree->GetEntries("TMath::Abs(sr92_x_cal[0].fID - sr92_x_cal[1].fID) < 2");
 Double_t sr92x_nHitThree = tree->GetEntries("(sr92_x_cal[1].fID + sr92_x_cal[2].fID) == sr92_x_cal[0].fID*2");


 Double_t effsr92x = 100. * (sr92x_nHitThree / sr92x_nHitTwo);
    cout << " -- Q2 Efficiency of sr92 X --" << endl;
    cout << "  "  << effsr92x << " % "  << endl;
 
 Double_t sr92y_nHitTwo = tree->GetEntries("TMath::Abs(sr92_y_cal[0].fID - sr92_y_cal[1].fID) < 2");
 Double_t sr92y_nHitThree = tree->GetEntries("(sr92_y_cal[1].fID + sr92_y_cal[2].fID) == sr92_y_cal[0].fID*2");

 Double_t effsr92y = 100. * (sr92y_nHitThree / sr92y_nHitTwo);
    cout << " -- Q2 Efficiency of sr92 Y --" << endl;
    cout << "  "  << effsr92y << " % " << endl;
 
 Double_t src1x_nHitTwo = tree->GetEntries("TMath::Abs(src1_x_cal[0].fID - src1_x_cal[1].fID) < 2");
 Double_t src1x_nHitThree = tree->GetEntries("(src1_x_cal[1].fID + src1_x_cal[2].fID) == src1_x_cal[0].fID*2");

 Double_t effsrc1x = 100. * (src1x_nHitThree / src1x_nHitTwo);
    cout << " -- Q2 Efficiency of src1 X --" << endl;
    cout << "  "  << effsrc1x << " % " << endl;
 

 Double_t src1y_nHitTwo = tree->GetEntries("TMath::Abs(src1_y_cal[0].fID - src1_y_cal[1].fID) < 2");
 Double_t src1y_nHitThree = tree->GetEntries("(src1_y_cal[1].fID + src1_y_cal[2].fID) == src1_y_cal[0].fID*2");


 Double_t effsrc1y = 100. * (src1y_nHitThree / src1y_nHitTwo);
    cout << " -- Q2 Efficiency of src1 Y --" << endl;
    cout << "  "  << effsrc1y << " % " << endl;

 Double_t src2x_nHitTwo = tree->GetEntries("TMath::Abs(src2_x_cal[0].fID - src2_x_cal[1].fID) < 2");
 Double_t src2x_nHitThree = tree->GetEntries("(src2_x_cal[1].fID + src2_x_cal[2].fID) == src2_x_cal[0].fID*2");

 Double_t effsrc2x = 100. * (src2x_nHitThree / src2x_nHitTwo);
    cout << " -- Q2 Efficiency of src2 X --" << endl;
    cout << "  "  << effsrc2x << " % " << endl;
 
 Double_t src2y_nHitTwo = tree->GetEntries("TMath::Abs(src2_y_cal[0].fID - src2_y_cal[1].fID) < 2");
 Double_t src2y_nHitThree = tree->GetEntries("(src2_y_cal[1].fID + src2_y_cal[2].fID) == src2_y_cal[0].fID*2");

 Double_t effsrc2y = 100. * (src2y_nHitThree / src2y_nHitTwo);
    cout << " -- Q2 Efficiency of src2 Y --" << endl;
    cout << "  "  << effsrc2y << " % " << endl;


 Double_t sr11x_nHitTwo = tree->GetEntries("TMath::Abs(sr11_x_cal[0].fID - sr11_x_cal[1].fID) < 2");
 Double_t sr11x_nHitThree = tree->GetEntries("(sr11_x_cal[1].fID + sr11_x_cal[2].fID) == sr11_x_cal[0].fID*2");

 Double_t effsr11x = 100. * (sr11x_nHitThree / sr11x_nHitTwo);
    cout << " -- Q2 Efficiency of sr11 X --" << endl;
    cout << "  "  << effsr11x << " % " << endl;
 
 Double_t sr11y_nHitTwo = tree->GetEntries("TMath::Abs(sr11_y_cal[0].fID - sr11_y_cal[1].fID) < 2");
 Double_t sr11y_nHitThree = tree->GetEntries("(sr11_y_cal[1].fID + sr11_y_cal[2].fID) == sr11_y_cal[0].fID*2");

 Double_t effsr11y = 100. * (sr11y_nHitThree / sr11y_nHitTwo);
    cout << " -- Q2 Efficiency of sr11 Y --" << endl;
    cout << "  "  << effsr11y << " % " << endl;
 
 Double_t sr12x_nHitTwo = tree->GetEntries("TMath::Abs(sr12_x_cal[0].fID - sr12_x_cal[1].fID) < 2");
 Double_t sr12x_nHitThree = tree->GetEntries("(sr12_x_cal[1].fID + sr12_x_cal[2].fID) == sr12_x_cal[0].fID*2");

 Double_t effsr12x = 100. * (sr12x_nHitThree / sr12x_nHitTwo);
    cout << " -- Q2 Efficiency of sr12 X --" << endl;
    cout << "  "  << effsr12x << " % " << endl;
 
 Double_t sr12y_nHitTwo = tree->GetEntries("TMath::Abs(sr12_y_cal[0].fID - sr12_y_cal[1].fID) < 2");
 Double_t sr12y_nHitThree = tree->GetEntries("(sr12_y_cal[1].fID + sr12_y_cal[2].fID) == sr12_y_cal[0].fID*2");

 Double_t effsr12y = 100. * (sr12y_nHitThree / sr12y_nHitTwo);
    cout << " -- Q2 Efficiency of sr12 Y --" << endl;
    cout << "  "  << effsr12y << " % " << endl;



}

