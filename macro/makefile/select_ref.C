#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"

enum ref_name {
   ca,
   sc,
   ti,
   v,
   cr,
   mn,
   fe,
   co,
   ni
};


void select_ref(const char *reference){


  enum ref_name ref;
  ref = reference;


switch(ref){
	case ca:

	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.ca.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.ca.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case sc:

	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.sc.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.sc.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case ti:

	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.ti.170272.root");
     TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.ti.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

    case v:

	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.v.170272.root");
     TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.v.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case cr:

	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.cr.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.cr.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case mn:
	
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.mn.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.mn.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case fe:
	
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.fe.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.fe.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case co:
	
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.co.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.co.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

	case ni:
	
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge.ni.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_ref.ni.root","RECREATE");
     ((TTree*)file->Get("tree"))->CopyTree(Form("eventheader.fRunNumber==%d",i));
     ofile->Write();
     ofile->Close();

 }





}


