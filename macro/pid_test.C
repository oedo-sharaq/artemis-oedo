void pid_test(TString bldfilename="/home/sh13/art_analysis/user/okawa/output/physics/0130/pidataphysics0130.root")
{
   TFile* f_bld = TFile::Open(bldfilename);

   TTree* tree_bld = (TTree*) f_bld->Get("tree");

   TClonesArray* dia3pad  = NULL;// new TClonesArray();
   TClonesArray* sr0_x    = NULL;// new TClonesArray();
   TClonesArray* dias2pad = NULL;// new TClonesArray();
   TClonesArray* S2ssd    = NULL;// new TClonesArray();
   TClonesArray* vetopla  = NULL;// new TClonesArray();

   tree_bld->SetBranchAddress("dia3pad", &dia3pad);
   tree_bld->SetBranchAddress("sr0_x", &sr0_x);
   tree_bld->SetBranchAddress("dias2pad", &dias2pad);
   tree_bld->SetBranchAddress("S2ssd", &S2ssd);
   tree_bld->SetBranchAddress("vetopla", &vetopla);


   Int_t n_bld = tree_bld->GetEntries();

   for(Int_t i=0; i<n_bld; i++){
      tree_bld->GetEntry(i);
      std::cout << dias2pad->GetEntriesFast() << " " << dia3pad->GetEntriesFast() << " " << sr0_x->GetEntriesFast() << " " << S2ssd->GetEntriesFast() << " " << vetopla->GetEntriesFast() << " " << std::endl;
   }

}
