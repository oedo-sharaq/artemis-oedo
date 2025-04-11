
void tchain_calib(){


 TFile *ofile = new TFile("output/srppac/calib/chksrppac_newproccalib10291030.root","recreate");
 TChain *ch = new TChain("tree","");

ch->Add(Form("output/srppac/calib/1029/chksrppac_newproccalib1029.root"));
ch->Add(Form("output/srppac/calib/1030/chksrppac_newproccalib1030.root"));

ch->Write();








}
