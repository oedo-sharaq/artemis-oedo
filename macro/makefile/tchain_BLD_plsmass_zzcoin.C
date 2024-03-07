


void tchain_BLD_plsmass_zzcoin(){

// This root file is for fitting after mass calibration !!!

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/ca/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/sc/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/ti/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/v/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/cr/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/mn/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.mn.root","recreate");
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_zzcoin/fe/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.170272.fe.root","recreate");


TChain *ch = new TChain("tree","");


//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/ca/BLD_ssdpla.170272.ca.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.ca.root");
// cout << "Chain Ca" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/sc/BLD_ssdpla.170272.sc.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.sc.root");
// cout << "Chain Sc" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/ti/BLD_ssdpla.170272.ti.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.ti.root");
// cout << "Chain Ti" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/v/BLD_ssdpla.170272.v.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.v.root");
// cout << "Chain V" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/cr/BLD_ssdpla.170272.cr.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.cr.root");
// cout << "Chain Cr" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/mn/BLD_ssdpla.170272.mn.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.mn.root");
// cout << "Chain Mn" << endl;
////
//// ch->Add("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/fe/BLD_ssdpla.170272.fe.root");
// ch->Add("sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.fe.root");
// cout << "Chain Fe" << endl;




//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/ca/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.ca.root",i));
// cout<< "Chain Ca Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/sc/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.sc.root",i));
// cout<< "Chain Sc Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/ti/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.ti.root",i));
// cout<< "Chain Ti Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/v/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.v.root",i));
// cout<< "Chain V Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/cr/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.cr.root",i));
// cout<< "Chain Cr Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/mn/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.mn.root",i));
// cout<< "Chain Mn Run" << i << endl;
//}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_zzcoin/fe/physics.chkmass_stm2_6step_ref6_posmod_zzcoin.eventstore.%04d.fe.root",i));
 cout<< "Chain Fe Run" << i << endl;
}

 ch->Write();




}




