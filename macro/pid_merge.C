void pid_merge(TString bldfilename="/home/sh13/art_analysis/user/okawa/output/physics/0130/chkbldphysics0130.root", TString tsfilename="/home/sh13/art_analysis/user/okawa/output/merge/pid_physics0130.root")
{
   TFile* f_bld = TFile::Open(bldfilename);
   TFile* f_ts  = TFile::Open(tsfilename);

   TTree* tree_bld = (TTree*) f_bld->Get("tree");
   TTree* tree_ts  = (TTree*) f_ts->Get("tree");

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

   TClonesArray* pid_data = NULL;//new TClonesArray();

   tree_ts->SetBranchAddress("pid_data", &pid_data);

   TFile *fout = new TFile("/home/sh13/art_analysis/user/okawa/output/test.root","RECREATE");
   TTree *tree = new TTree("tree","tree");

   ULong64_t s2ts;
   Double_t s2aq, s2z;
   Double_t veto_tave, veto_qave;

   tree->Branch("S2TS", &s2ts, "S2TS/l");
   tree->Branch("S2AQ", &s2aq, "S2AQ/D");
   tree->Branch("S2Z",  &s2z, "S2TS/D");
   tree->Branch("VETO_TAve", &veto_tave, "veto_tave/D");
   tree->Branch("VETO_QAve", &veto_qave, "veto_qave/D");


   Int_t n_bld = tree_bld->GetEntries();
   Int_t n_ts  = tree_ts ->GetEntries();

   if(n_bld != n_ts){
	std::cout << "event number is different!!" << std::endl;
	exit(0);
   }

   for(Int_t i=0; i<n_bld; i++){
      s2ts = 1;
      s2aq = 0.0;
      s2z = 0.0;
      veto_tave = 0.0;
      veto_qave = 0.0;

      tree_bld->GetEntry(i);
      tree_ts ->GetEntry(i);
      
      s2ts = ((art::TMergerData*)pid_data->At(0))->GetULongTimestamp();

      if(!dias2pad->GetEntriesFast()){
          tree->Fill();
          continue;
      }
      if(!dia3pad->GetEntriesFast()){
          tree->Fill();
          continue;
      }
      if(!sr0_x->GetEntriesFast()){
          tree->Fill();
          continue;
      }
      if(!S2ssd->GetEntriesFast()){
          tree->Fill();
          continue;
      }
      if(!vetopla->GetEntriesFast()){
          tree->Fill();
          continue;
      }

      Double_t tof32=((art::TTimingChargeData*)dias2pad->At(0))->GetTiming()-((art::TTimingChargeData*)dia3pad->At(0))->GetTiming();
      Double_t s2brho = 4.4147*(1-((art::TSRPPACPlaneData*)sr0_x->At(0))->GetPosition()/14856);
      Double_t s2beta=103499.78/(tof32-1455.)/299.79;
      Double_t s2gamma = 1/TMath::Sqrt(1-(s2beta)*(s2beta));
      Double_t s2de=1.03827*((art::TDssdData*)S2ssd->At(0))->GetEx();
      Double_t de_v = TMath::Log(5907.5*s2beta*s2beta)-TMath::Log(1.-s2beta*s2beta)-s2beta*s2beta;

      s2aq = s2brho * 299.79 / (s2gamma * s2beta * 931.49);
      s2z = -0.0513 + 7.451*TMath::Sqrt(s2de/de_v) * s2beta;
      //std::cout << s2aq << " " << s2z << std::endl;

      //for(Int_t j=0; j<vetopla->GetEntriesFast(); j++){
      //}
      Double_t veto_tave0 = ((art::TTwoSidedPlasticData*)vetopla->At(0))->GetTAve();
      Double_t veto_qave0 = ((art::TTwoSidedPlasticData*)vetopla->At(0))->GetQAve();
      //std::cout << veto_tave << " " << veto_qave << std::endl;
      if(std::isnan(veto_qave)){
         tree->Fill();
         continue;
      }

      veto_tave = veto_tave0;
      veto_qave = veto_qave0;

      tree->Fill();
   }

   tree->Write();
   fout->Write();
   fout->Close();
}
