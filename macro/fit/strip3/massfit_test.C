
void massfit_test(int refnum){

// int refnum = 0;

//for (int refnum=0; refnum < 3; refnum++){

if(refnum==0){
//// Ca
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file1 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.ca.hist.root");
 if(!file1){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h39ca = (TH1F*)gDirectory->Get("mass_st2_39ca");
TH1F *h40ca = (TH1F*)gDirectory->Get("mass_st2_40ca");
TH1F *h41ca = (TH1F*)gDirectory->Get("mass_st2_41ca");

 h39ca->Fit("gaus","","",1.9472,1.9486);
 TF1 *f1 = h39ca->GetFunction("gaus");
 Double_t *prm1 = f1->GetParameters();
  fout << prm1[0] << " " << prm1[1] << " " << prm1[2] << endl;
  gROOT->ProcessLine("save");

 h40ca->Fit("gaus","","",1.9968,1.9982);
 TF1 *f2 = h40ca->GetFunction("gaus");
 Double_t *prm2 = f2->GetParameters();
  fout << prm2[0] << " " << prm2[1] << " " << prm2[2] << endl;
  gROOT->ProcessLine("save");

 h41ca->Fit("gaus","","",2.0468,2.0482);
 TF1 *f3 = h41ca->GetFunction("gaus");
 Double_t *prm3 = f3->GetParameters();
  fout << prm3[0] << " " << prm3[1] << " " << prm3[2] << endl;
  gROOT->ProcessLine("save");

 file1->Close();
// gROOT->ProcessLine(".q");
// return;
}else if(refnum==1){
//// Sc
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file2 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.sc.hist.root");
 if(!file2){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F * h40sc = (TH1F*)gDirectory->Get("mass_st2_40sc");
TH1F * h41sc = (TH1F*)gDirectory->Get("mass_st2_41sc");
TH1F * h43sc = (TH1F*)gDirectory->Get("mass_st2_43sc");

 h40sc->Fit("gaus","","",1.90246,1.9038);
 TF1 *f4 = h40sc->GetFunction("gaus");
 Double_t *prm4 = f4->GetParameters();
  fout << prm4[0] << " " << prm4[1] << " " << prm4[2] << endl;
  gROOT->ProcessLine("save");
  
 h41sc->Fit("gaus","","",1.9496,1.9510);
 TF1 *f5 = h41sc->GetFunction("gaus");
 Double_t *prm5 = f5->GetParameters();
  fout << prm5[0] << " " << prm5[1] << " " << prm5[2] << endl;
  gROOT->ProcessLine("save");

 h43sc->Fit("gaus","","",2.0445,2.0459);
 TF1 *f6 = h43sc->GetFunction("gaus");
 Double_t *prm6 = f6->GetParameters();
  fout << prm6[0] << " " << prm6[1] << " " << prm6[2] << endl;
  gROOT->ProcessLine("save");

 file2->Close();
//  gROOT->ProcessLine(".q");
// return;

}else if(refnum==2){
//// Ti
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }

 TFile* file3 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.ti.hist.root");
 if(!file3){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h40ti = (TH1F*)gDirectory->Get("mass_st2_40ti");
TH1F *h41ti = (TH1F*)gDirectory->Get("mass_st2_41ti");
TH1F *h43ti = (TH1F*)gDirectory->Get("mass_st2_43ti");

 h40ti->Fit("gaus","","",1.8164,1.8178);
 TF1 *f7 = h40ti->GetFunction("gaus");
 Double_t *prm7 = f7->GetParameters();
  fout << prm7[0] << " " << prm7[1] << " " << prm7[2] << endl;
  gROOT->ProcessLine("save");
  
 h41ti->Fit("gaus","","",1.8616,1.8630);
 TF1 *f8 = h41ti->GetFunction("gaus");
 Double_t *prm8 = f8->GetParameters();
  fout << prm8[0] << " " << prm8[1] << " " << prm8[2] << endl;
  gROOT->ProcessLine("save");

 h43ti->Fit("gaus","","",1.9518,1.9532);
 TF1 *f9 = h43ti->GetFunction("gaus");
 Double_t *prm9 = f9->GetParameters();
  fout << prm9[0] << " " << prm9[1] << " " << prm9[2] << endl;
  gROOT->ProcessLine("save");

 file3->Close();
//  gROOT->ProcessLine(".q");
// return;

}else if(refnum==3){

//// V
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file4 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.v.hist.root");
 if(!file4){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h43v  = (TH1F*)gDirectory->Get("mass_st2_43v");
TH1F *h44v  = (TH1F*)gDirectory->Get("mass_st2_44v");
TH1F *h45v  = (TH1F*)gDirectory->Get("mass_st2_45v");

 h43v->Fit("gaus","","",1.8674,1.8688);
 TF1 *f10 = h43v->GetFunction("gaus");
 Double_t *prm10 = f10->GetParameters();
  fout << prm10[0] << " " << prm10[1] << " " << prm10[2] << endl;
  gROOT->ProcessLine("save");
  
 h44v->Fit("gaus","","",1.9106,1.9120);
 TF1 *f11 = h44v->GetFunction("gaus");
 Double_t *prm11 = f11->GetParameters();
  fout << prm11[0] << " " << prm11[1] << " " << prm11[2] << endl;
  gROOT->ProcessLine("save");

 h45v->Fit("gaus","","",1.9537,1.9551);
 TF1 *f12 = h45v->GetFunction("gaus");
 Double_t *prm12 = f12->GetParameters();
  fout << prm12[0] << " " << prm12[1] << " " << prm12[2] << endl;
  gROOT->ProcessLine("save");

 file4->Close();
// gROOT->ProcessLine(".q");
// return;

}else if(refnum==4){

//// Cr
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file5 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.cr.hist.root");
 if(!file5){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h44cr = (TH1F*)gDirectory->Get("mass_st2_44cr");
TH1F *h45cr = (TH1F*)gDirectory->Get("mass_st2_45cr");
TH1F *h46cr = (TH1F*)gDirectory->Get("mass_st2_46cr");

 h44cr->Fit("gaus","","",1.8314,1.8328);
 TF1 *f13 = h44cr->GetFunction("gaus");
 Double_t *prm13 = f13->GetParameters();
  fout << prm13[0] << " " << prm13[1] << " " << prm13[2] << endl;
  gROOT->ProcessLine("save");
  
 h45cr->Fit("gaus","","",1.8728,1.8742);
 TF1 *f14 = h45cr->GetFunction("gaus");
 Double_t *prm14 = f14->GetParameters();
  fout << prm14[0] << " " << prm14[1] << " " << prm14[2] << endl;
  gROOT->ProcessLine("save");

 h46cr->Fit("gaus","","",1.9141,1.9155);
 TF1 *f15 = h46cr->GetFunction("gaus");
 Double_t *prm15 = f15->GetParameters();
  fout << prm15[0] << " " << prm15[1] << " " << prm15[2] << endl;
  gROOT->ProcessLine("save");

 file5->Close();
// gROOT->ProcessLine(".q");
// return;

}else if(refnum==5){

//// Mn
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
  }


 TFile* file6 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.mn.hist.root");
 if(!file6){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h46mn = (TH1F*)gDirectory->Get("mass_st2_46mn");
TH1F *h47mn = (TH1F*)gDirectory->Get("mass_st2_47mn");
//TH1F *h48mn = (TH1F*)gDirectory->Get("mass_st2_48mn");
TH1F *h49mn = (TH1F*)gDirectory->Get("mass_st2_49mn");

 h46mn->Fit("gaus","","",1.8382,1.8396);
 TF1 *f16 = h46mn->GetFunction("gaus");
 Double_t *prm16 = f16->GetParameters();
  fout << prm16[0] << " " << prm16[1] << " " << prm16[2] << endl;
  gROOT->ProcessLine("save");
  
 h47mn->Fit("gaus","","",1.8777,1.8791);
 TF1 *f17 = h47mn->GetFunction("gaus");
 Double_t *prm17 = f17->GetParameters();
  fout << prm17[0] << " " << prm17[1] << " " << prm17[2] << endl;
  gROOT->ProcessLine("save");

 h49mn->Fit("gaus","","",1.9174,1.9188);
 TF1 *f18 = h49mn->GetFunction("gaus");
 Double_t *prm18 = f18->GetParameters();
  fout << prm18[0] << " " << prm18[1] << " " << prm18[2] << endl;
  gROOT->ProcessLine("save");

 file6->Close();
// gROOT->ProcessLine(".q");
// return;

}else if(refnum==6){

//// Fe
 ofstream fout(Form("/home/sh13/art_analysis/user/hanai/prm/mass/ref_fitting%d.dat",refnum));
 if(fout.fail()){
	 cout << "Error; Could not open output file.." << endl << endl;
	 gROOT->ProcessLine(".q");
	 return;
   }


 TFile* file7 = TFile::Open("sh13_analysis/hanai/phys/merge/physics.chkmass_st2.170272.fe.hist.root");
 if(!file7){
	 printf("Cannot open the file!\n");
	 gROOT->ProcessLine(".q");
	 return;
 }

 gROOT->ProcessLine("cd 0");

TH1F *h48fe = (TH1F*)gDirectory->Get("mass_st2_48fe");
TH1F *h49fe = (TH1F*)gDirectory->Get("mass_st2_49fe");
TH1F *h50fe = (TH1F*)gDirectory->Get("mass_st2_50fe");

 h48fe->Fit("gaus","","",1.8441,1.8455);
 TF1 *f19 = h48fe->GetFunction("gaus");
 Double_t *prm19 = f19->GetParameters();
  fout << prm19[0] << " " << prm19[1] << " " << prm19[2] << endl;
  gROOT->ProcessLine("save");
  
 h49fe->Fit("gaus","","",1.8823,1.8837);
 TF1 *f20 = h49fe->GetFunction("gaus");
 Double_t *prm20 = f20->GetParameters();
  fout << prm20[0] << " " << prm20[1] << " " << prm20[2] << endl;
  gROOT->ProcessLine("save");

 h50fe->Fit("gaus","","",1.9204,1.9218);
 TF1 *f21 = h50fe->GetFunction("gaus");
 Double_t *prm21 = f21->GetParameters();
  fout << prm21[0] << " " << prm21[1] << " " << prm21[2] << endl;
  gROOT->ProcessLine("save");

 file7->Close();
// gROOT->ProcessLine(".q");
// return;

}else{
	cout << "Error! something wrong." << endl;
}

//}





}
