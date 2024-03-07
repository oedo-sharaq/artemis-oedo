

void tchain_chkmass_stm_7step_ref6_all(){

 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6.eventstore.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.ca.root");
 cout<< "Chain Ca " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.sc.root");
 cout<< "Chain Sc " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.ti.root");
 cout<< "Chain Ti " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.v.root");
 cout<< "Chain V " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.cr.root");
 cout<< "Chain Cr " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.mn.root");
 cout<< "Chain Mn " << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_ref6_posmod.eventstore.170272.fe.root");
 cout<< "Chain Fe " << endl;
 ch->Write();




}




