
{

  // gStyle->SetPalette(1);

  //  TString filename = Form("shift/%s%04d/%s%04d.pdf",name,run,name,run);
  //gSystem->mkdir(TString(gSystem->DirName(filename)),kTRUE);
 
  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("ht 0/0 col");
  gROOT->ProcessLine("ht 0/1 col");
  gROOT->ProcessLine("ht 0/3 col");
  gROOT->ProcessLine("ht 0/5 col");
  

}
