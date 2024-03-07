


void tchain_ref_all_eachstrip(){

 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref2_eachstrip.all.170272.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref2_eachstrip.ca.170272.root");
 cout<< "Chain Ca " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.sc.170272.root");
 cout<< "Chain Sc " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.ti.170272.root");
 cout<< "Chain Ti " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.v.170272.root");
 cout<< "Chain V " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.cr.170272.root");
 cout<< "Chain Cr " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.mn.170272.root");
 cout<< "Chain Mn " << endl;
 ch->Add("sh13_analysis/hanai/phys/merge/physics_merge_ref_eachstrip.fe.170272.root");
 cout<< "Chain Fe " << endl;
 ch->Write();




}




