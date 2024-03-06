
{
  TChain *mychain = new TChain("tree");
  mychain->Add("output/ttt/test136_2.root/tree");
  mychain->Add("output/ttt/test137_2.root/tree");
  // mychain->Merge("output/ttt/testm_3.root");
}
