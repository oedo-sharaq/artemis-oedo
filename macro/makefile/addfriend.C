
void addfriend(){
 
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.all.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ni.root"); // Load file. Basically BLD file.
//  TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.sc.root"); // Load file. Basically BLD file.
//  TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.mn.root"); // Load file. Basically BLD file.
 TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.ti.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld_stm.170272.co.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.ti.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_ssdpla/ca/BLD_ssdpla.170272.ca.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/physics.bld.170272.all.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/BLD_tofoffset.170272.all.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/sc/BLD_tofoffset.170272.sc.root"); // Load file. Basically BLD file.
// TFile* file_load = TFile::Open("sh13_analysis/hanai/phys/bld_file/BLD_tofoffset/ca/BLD_tofoffset.170272.ca.root"); // Load file. Basically BLD file.
 TTree *tree = (TTree*) gDirectory->Get("tree");

// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_2step.eventstore.170272.ca.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st2_ref3_3step_unit2.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_ref4.eventstore.170272.all.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4_BVar.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.
//  tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_3step_ref4.eventstore.170272.v.root"); // Add file. Basically mass calibration file

// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.all.root");
 tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_reflise_plsmahala.eventstore.170272.ti.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_8step_reflise_plsmahala.eventstore.170272.sc.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_reflise_plsmahala.eventstore.170272.all.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_7step_reflise.eventstore.170272.mn.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ti.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6_Step0.eventstore.170272.ti.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.all.root"); // Add file. Basically mass calibration file.

// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_1step_ssdpla.eventstore.170272.ca.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st3_2step.eventstore.170272.all.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_3step_for4th_unit2.170272.ca.root"); // Add file. Basically mass calibration file.
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/BLD_tofoffset_plsmass/sc/physics.chkmass_st1_3step_for4th_unit2.170272.sc.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st1_4step.eventstore.170272.ca.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_st2_3step.eventstore.170272.sc.root");
 //tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_2step_ref4.eventstore.170272.ti.root");
// tree->AddFriend("tree1 = tree","sh13_analysis/hanai/phys/mass_calib/physics.chkmass_stm2_6step_ref6.eventstore.170272.co.root");

}




