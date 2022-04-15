
{

  // gStyle->SetPalette(1);                                 
  //  TString filename = Form("shift/%s%04d/%s%04d.pdf",name,run,name,run);                                          
//gSystem->mkdir(TString(gSystem->DirName(filename)),kTRUE);                                                         

  gROOT->ProcessLine("zone 2 3");                     
  gROOT->ProcessLine("ht 22/2 colz");
  gROOT->ProcessLine("ht 22/7 col");
  gROOT->ProcessLine("ht 22/4 col");
  gROOT->ProcessLine("ht 22/9 colz");
  gROOT->ProcessLine("ht 22/14 colz");
  gROOT->ProcessLine("ht 22/15 colz");

}

