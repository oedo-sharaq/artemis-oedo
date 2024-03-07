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


void select_event2(const char *reference){


  enum ref_name ref;
  ref = reference;


switch(ref){
	case ca:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.ca.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.ca.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case sc:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.sc.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.sc.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
 	ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case ti:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.ti.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.ti.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
    case v:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.v.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.v.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case cr:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.cr.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.cr.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case mn:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.mn.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.mn.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case fe:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.fe.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.fe.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case co:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.co.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.co.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 
	case ni:
	 TFile* file = TFile::Open("sh13_analysis/hanai/phys/merge/physics_merge_ref.ni.170272.root");
	 TFile* ofile = new TFile("sh13_analysis/hanai/phys/merge/physics_merge_ref_half.ni.root","RECREATE");

	 ((TTree*)file->Get("tree"))->CopyTree("Entry$%2==0");
	 ofile->Write();
	 ofile->Close();

	 ofile->Delete();
 

 }

 



}


