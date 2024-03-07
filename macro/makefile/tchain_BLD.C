


void tchain_BLD(){

 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD.%04d.all.root",i));
 cout<< "Chain Run" << i << endl;
}

 ch->Write();




}




