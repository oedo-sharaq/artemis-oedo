


void tchain_chkmass_st1_4th(){


// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.all.root","recreate");


// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_ssdpla.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.ca.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.ca.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.sc.root","recreate");/
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.sc.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.sc.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.ti.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.ti.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.v.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.v.root","recreate");

// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.cr.root","recreate");
// TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.cr.root","recreate");

//TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.mn.root","recreate");
//TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.mn.root","recreate");
//TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.mn.root","recreate");

//TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4step_maxz_nooff.eventstore.170272.fe.root","recreate");
//TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.170272.fe.root","recreate");
TFile *ofile = new TFile("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.170272.fe.root","recreate");

// TChain *ch = new TChain("tree","");
 TChain ch("tree","");
 

//for(int i = 170; i < 273; i++){
// if(i == 218 || i == 219) continue;
//
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.ca.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.ca.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4step_ssdpla.eventstore.%04d.ca.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ca/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.ca.root",i));
//
// cout<< "Chain Ca Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// if(i == 218 || i == 219) continue;
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.sc.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.sc.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.sc.root",i));
// cout<< "Chain Sc Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// if(i == 218 || i == 219) continue;
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.ti.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.ti.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/ti/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.ti.root",i));
// cout<< "Chain Ti Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// if(i == 218 || i ==219) continue;
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.v.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.v.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/v/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.v.root",i));
// cout<< "Chain V Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// if(i == 218 || i ==219) continue;
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.cr.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.cr.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/cr/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.cr.root",i));
// cout<< "Chain Cr Run" << i << endl;
//}

//for(int i = 170; i < 273; i++){
// if(i == 218 || i ==219) continue;
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.mn.root",i));
//// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.mn.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/mn/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.mn.root",i));
// cout<< "Chain Mn Run" << i << endl;
//}

for(int i = 170; i < 273; i++){
 if(i == 218 || i ==219) continue;
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4step_maxz_nooff.eventstore.%04d.fe.root",i));
// ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4step_ssdpla_nooff.eventstore.%04d.fe.root",i));
 ch.Add(Form("sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/fe/physics.chkmass_st1_4.5step_ssdpla_nooff.eventstore.%04d.fe.root",i));
 cout<< "Chain Fe Run" << i << endl;
}

 TTree* newtree = ch.CloneTree();

 ofile->cd();
 newtree->Write();
 ofile->Close();




}




