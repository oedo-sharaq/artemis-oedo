

void tchain_BLD_maxz_stm(){

// This root file is for mass calibration !!!
 
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/BLD_maxz_stm.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ca/BLD_maxz_stm.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/sc/BLD_maxz_stm.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ti/BLD_maxz_stm.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/v/BLD_maxz_stm.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/cr/BLD_maxz_stm.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/cr/BLD_maxz_stm.170272.cr_dc21u.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/mn/BLD_maxz_stm.170272.mn.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/fe/BLD_maxz_stm.170272.fe.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/BLD_maxz_stm.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/physics.chkmass_stm2_2step_ref4_maxz.eventstore.170272.all.root","recreate");
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ti/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/v/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/cr/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/fe/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.fe.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/co/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.co.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ni/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.ni.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/physics.chkmass_stm2_6step_ref6_maxz.eventstore.170272.all.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/sc/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ti/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_1step_ref4_maxz_stmbeta.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/v/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/cr/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/mn/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.mn.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/fe/physics.chkmass_stm2_1step_ref4_maxz.eventstore.170272.fe.root","recreate");


// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_7step_ref7_maxz.eventstore.170272.ca.root","recreate");


 TChain *ch = new TChain("tree","");


//for(int i = 170; i < 273; i++){
//
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ca/BLD_maxz_stm.%04d.ca.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/sc/BLD_maxz_stm.%04d.sc.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ti/BLD_maxz_stm.%04d.ti.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/v/BLD_maxz_stm.%04d.v.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/cr/BLD_maxz_stm.%04d.cr.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/cr/BLD_maxz_stm.%04d.cr_dc21u.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/mn/BLD_maxz_stm.%04d.mn.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/fe/BLD_maxz_stm.%04d.fe.root",i));
//
//// cout<< "Chain Ca Run" << i << endl;
//// cout<< "Chain Sc Run" << i << endl;
//// cout<< "Chain Ti Run" << i << endl;
// cout<< "Chain V Run" << i << endl;
//// cout<< "Chain Cr Run" << i << endl;
//// cout<< "Chain Mn Run" << i << endl;
//// cout<< "Chain Fe Run" << i << endl;
//}



//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ca/BLD_maxz_stm.%04d.ca.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.ca.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.ca.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_1step_ref4_maxz_stmbeta.eventstore.%04d.ca.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.ca.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ca/physics.chkmass_stm2_7step_ref7_maxz.eventstore.%04d.ca.root",i));
// cout<< "Chain Ca Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/sc/BLD_maxz_stm.%04d.sc.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/sc/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.sc.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/sc/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.sc.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/sc/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.sc.root",i));
// cout<< "Chain Sc Run" << i << endl;
//}
//
for(int i = 170; i < 273; i++){
 
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/ti/BLD_maxz_stm.%04d.ti.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ti/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.ti.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ti/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.ti.root",i));
 ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ti/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.ti.root",i));
 cout<< "Chain Ti Run" << i << endl;
}

//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/v/BLD_maxz_stm.%04d.v.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/v/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.v.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/v/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.v.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/v/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.v.root",i));
// cout<< "Chain V Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/cr/BLD_maxz_stm.%04d.cr.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/cr/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.cr.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/cr/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.cr.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/cr/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.cr.root",i));
// cout<< "Chain Cr Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/mn/BLD_maxz_stm.%04d.mn.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/mn/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.mn.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/mn/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.mn.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/mn/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.mn.root",i));
// cout<< "Chain Mn Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_maxz_stm/fe/BLD_maxz_stm.%04d.fe.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/fe/physics.chkmass_stm2_1step_ref4_maxz.eventstore.%04d.fe.root",i));
//// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/fe/physics.chkmass_stm2_2step_ref4_maxz.eventstore.%04d.fe.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/fe/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.fe.root",i));
// cout<< "Chain Fe Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/co/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.co.root",i));
// cout<< "Chain Co Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
// ch->Add(Form("sh13_analysis/hanai/phys/mass_cor_maxz/ni/physics.chkmass_stm2_6step_ref6_maxz.eventstore.%04d.ni.root",i));
// cout<< "Chain Ni Run" << i << endl;
//}

ch->Write();




}




