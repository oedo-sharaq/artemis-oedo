

void tchain_BLD_stm(){

 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ca.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.ca.root");
 cout<< "Chain Ca " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.sc.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.sc.root");
 cout<< "Chain Sc " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ti.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.ti.root");
 cout<< "Chain Ti " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.v.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.v.root");
 cout<< "Chain V " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.cr.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.cr.root");
 cout<< "Chain Cr " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.mn.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.mn.root");
 cout<< "Chain Mn " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.fe.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.fe.root");
 cout<< "Chain Fe " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.co.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.co.root");
 cout<< "Chain Co " << endl;
 ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ni.root");
// ch->Add("sh13_analysis/hanai/phys/bld_file/physics.bld_stm_v2.170272.ni.root");
 cout<< "Chain Ni " << endl;
ch->Write();




}




