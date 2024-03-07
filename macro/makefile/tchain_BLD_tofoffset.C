


void tchain_BLD_tofoffset(){

// This root file is for mass calibration !!!
 
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/ca/BLD_tofoffset.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/sc/BLD_tofoffset.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/ti/BLD_tofoffset.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/v/BLD_tofoffset.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/cr/BLD_tofoffset.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/mn/BLD_tofoffset.170272.mn.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/fe/BLD_tofoffset.170272.fe.root","recreate");


 TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.170272.all.root","recreate");

 TChain *ch = new TChain("tree","");

 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.ca.root");
 cout<< "Chain Ca Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.sc.root");
 cout<< "Chain Sc Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.ti.root");
 cout<< "Chain Ti Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.v.root");
 cout<< "Chain V Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.cr.root");
 cout<< "Chain Cr Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.mn.root");
 cout<< "Chain Mn Run" << endl;
 ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.eventstore.170272.fe.root");
 cout<< "Chain Fe Run" << endl;


//for(int i = 170; i < 273; i++){
//
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/ca/BLD_tofoffset.%04d.ca.root",i));
// cout<< "Chain Ca Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/sc/BLD_tofoffset.%04d.sc.root",i));
// cout<< "Chain Sc Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/ti/BLD_tofoffset.%04d.ti.root",i));
// cout<< "Chain Ti Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/v/BLD_tofoffset.%04d.v.root",i));
// cout<< "Chain V Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/cr/BLD_tofoffset.%04d.cr.root",i));
// cout<< "Chain Cr Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/mn/BLD_tofoffset.%04d.mn.root",i));
// cout<< "Chain Mn Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/fe/BLD_tofoffset.%04d.fe.root",i));
// cout<< "Chain Fe Run" << i << endl;
//}

 ch->Write();




}




