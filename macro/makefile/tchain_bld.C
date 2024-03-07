


void tchain_bld(){

 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ca.root");
 cout<< "Chain Ca " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.sc.root");
 cout<< "Chain Sc " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ti.root");
 cout<< "Chain Ti " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.v.root");
 cout<< "Chain V " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.cr.root");
 cout<< "Chain Cr " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.mn.root");
 cout<< "Chain Mn " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.fe.root");
 cout<< "Chain Fe " << endl;
 ch->Write();




}




