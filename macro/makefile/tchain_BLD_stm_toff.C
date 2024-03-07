

void tchain_BLD_stm_toff(){

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/chkdiaoff_physics.bld_stm_qcal_7step.265266.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/physics.bld_stm_qcal_toff_7step.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/physics.bld_stm_qcal_toff_6step.170272.all.root","recreate");
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/physics.bld_stm_qcal_toff_7step.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/physics.bld_stm_qcal_toff_6step.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/sc/physics.bld_stm_qcal_toff_6step.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ca/physics.bld_stm_qcal_toff_6step.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/chks2mwdc_physics.bld_stm_qcal_toff_6step.240245.ti.root","recreate");

 TChain *ch = new TChain("tree","");

//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ca/physics.bld_stm_qcal_toff_7step.%04d.ca.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ca/physics.bld_stm_qcal_toff_6step.%04d.ca.root",i));
// cout<< "Chain Ca Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/sc/physics.bld_stm_qcal_toff_7step.%04d.sc.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/sc/physics.bld_stm_qcal_toff_6step.%04d.sc.root",i));
// cout<< "Chain Sc Run" << i << endl;
//}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/physics.bld_stm_qcal_toff_7step.%04d.ti.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/physics.bld_stm_qcal_toff_6step.%04d.ti.root",i));
 cout<< "Chain Ti Run" << i << endl;
}

//////for(int i = 240; i < 246; i++){
////// 
////// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/ti/chks2mwdc_physics.bld_stm_qcal_toff_6step.%04d.ti.root",i));
////// cout<< "Chain Ti Run" << i << endl;
//////}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/v/physics.bld_stm_qcal_toff_7step.%04d.v.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/v/physics.bld_stm_qcal_toff_6step.%04d.v.root",i));
// cout<< "Chain V Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/cr/physics.bld_stm_qcal_toff_7step.%04d.cr.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/cr/physics.bld_stm_qcal_toff_6step.%04d.cr.root",i));
// cout<< "Chain Cr Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/mn/physics.bld_stm_qcal_toff_7step.%04d.mn.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/mn/physics.bld_stm_qcal_toff_6step.%04d.mn.root",i));
// cout<< "Chain Mn Run" << i << endl;
//}
//
//for(int i = 170; i < 273; i++){
// 
//// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/fe/physics.bld_stm_qcal_toff_7step.%04d.fe.root",i));
// ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_stm_tofoffset/fe/physics.bld_stm_qcal_toff_6step.%04d.fe.root",i));
// cout<< "Chain Fe Run" << i << endl;
//}





ch->Write();




}




