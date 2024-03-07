


void tchain_BLD_tpla(){

// This root file is for mass calibration !!!
 
 TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/BLD_tpla.170272.all.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/ca/BLD_tpla.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/sc/BLD_tpla.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/ti/BLD_tpla.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/v/BLD_tpla.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/cr/BLD_tpla.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/mn/BLD_tpla.170272.mn.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/bld_file/BLD_tpla/fe/BLD_tpla.170272.fe.root","recreate");

 TChain *ch = new TChain("tree","");

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/ca/BLD_tpla.%04d.ca.root",i));
 cout<< "Chain Ca Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/sc/BLD_tpla.%04d.sc.root",i));
 cout<< "Chain Sc Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/ti/BLD_tpla.%04d.ti.root",i));
 cout<< "Chain Ti Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/v/BLD_tpla.%04d.v.root",i));
 cout<< "Chain V Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/cr/BLD_tpla.%04d.cr.root",i));
 cout<< "Chain Cr Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/mn/BLD_tpla.%04d.mn.root",i));
 cout<< "Chain Mn Run" << i << endl;
}

for(int i = 170; i < 273; i++){
 
 ch->Add(Form("sh13_analysis/hanai/phys/bld_file/BLD_tpla/fe/BLD_tpla.%04d.fe.root",i));
 cout<< "Chain Fe Run" << i << endl;
}

 ch->Write();




}




