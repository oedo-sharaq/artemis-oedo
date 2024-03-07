

void tchain_chkAQ_all(){
 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/physics.chkAQ.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.ca.170272.root");
 cout<< "Chain Ca " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.sc.170272.root");
 cout<< "Chain Sc " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.ti.170272.root");
 cout<< "Chain Ti " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.v.170272.root");
 cout<< "Chain V " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.cr.170272.root");
 cout<< "Chain Cr " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.mn.170272.root");
 cout<< "Chain Mn " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_eachstrip_checkAQ.fe.170272.root");
 cout<< "Chain Fe " << endl;
 ch->Write();




}









