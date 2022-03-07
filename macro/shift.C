
void shift(int run, const char* name = "Be12")
{

  gStyle->SetPalette(1);

  TString filename = Form("shift/%s%04d/%s%04d.pdf",name,run,name,run);
  gSystem->mkdir(TString(gSystem->DirName(filename)),kTRUE);
  gROOT->ProcessLine("zone 2 2");
  TCanvas *artcanvas = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("artcanvas");
  
  gROOT->ProcessLine("cd");
  //F5 corr
  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("cd f5");
  gROOT->ProcessLine("ht f5_x_y,f5_a_x,f5_b_y,f5_a_b colz");
  artcanvas->SaveAs(filename+"(");
  
  gROOT->ProcessLine("cd ..");
  gROOT->ProcessLine("zone 2 4");

  //F5_mwdc
  gROOT->ProcessLine("cd dc51");
  gROOT->ProcessLine("ht id,id_charge,traw_charge colz");
  gROOT->ProcessLine("pcd 4");
  gROOT->ProcessLine("cd ..");
  gROOT->ProcessLine("cd dc52");
  gROOT->ProcessLine("ht id,id_charge,traw_charge colz");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("zone 3 3");
  gROOT->ProcessLine("cd ..");

  gROOT->ProcessLine("cd dc51");
  gROOT->ProcessLine("ht x1_dt,x2_dt,x3_dt,u1_dt,u2_dt,u3_dt,v1_dt,v2_dt,v3_dt");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("zone 1 2"); 
  gROOT->ProcessLine("cd ..");

  //F52pla
  gROOT->ProcessLine("cd f52_plastic");
  gROOT->ProcessLine("ht f52_ql,f52_tl");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("zone 2 3");
  gROOT->ProcessLine("cd ..");

  //F71pla
  gROOT->ProcessLine("cd f71_plastic");
  gROOT->ProcessLine("ht f71_ql,f71_qr,f71_tl,f71_tr,f71_q_lr,f71_t_lr colz");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("zone 2 3");
  
  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd f71_plastic");
  TH1* f71_ql = (TH1*)gDirectory->Get("f71_ql");
  double hit71pla = f71_ql->GetEntries();
  gROOT->ProcessLine("cd ..");


<<<<<<< Updated upstream
  //F72pla
  gROOT->ProcessLine("cd f72_plastic");
  gROOT->ProcessLine("ht f72_ql,f72_qr,f72_tl,f72_tr,f72_q_lr,f72_t_lr colz");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("cd ..");

  //F8ppac image
  gROOT->ProcessLine("cd f8ppac");
  gROOT->ProcessLine("ht f8track,f8track_cut colz");
  artcanvas->SaveAs(filename);
  
  gROOT->ProcessLine("cd f8_plastic");
  gROOT->ProcessLine("ht f8_ql,f8_qr,f8_tl,f8_tr,f8_q_lr,f8_t_lr colz");
  artcanvas->SaveAs(filename);

  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("cd ..");

  gROOT->ProcessLine("cd dali2hist");
  gROOT->ProcessLine("ht acal_id,tcal_tid,acal,tcal colz");
  artcanvas->SaveAs(filename);

  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("cd ..");

  gROOT->ProcessLine("cd dali2hist_cf7trg");
  gROOT->ProcessLine("ht acal_id,tcal_tid,acal,tcal colz");
  artcanvas->SaveAs(filename+")");  
  /***********************************************************************/
  gROOT->ProcessLine("cd");
  art::TAnalysisInfo *analysisInfo = (art::TAnalysisInfo*)gROOT->Get("analysisInfo");
  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd coin");
  TH1* coinPhys = (TH1*) gDirectory->Get("hCoinPhys");
  TH1* coinF5 = (TH1*) gDirectory->Get("hCoinF5");
  TH1* coinDALI = (TH1*) gDirectory->Get("hCoinDALI");
  int nEvents = coinPhys->GetEntries();


  printf("\n===== Event number profile =====\n");
  printf("total event (including scaler/comment blocks)\n");
  printf("              = %10d\n",nEvents);
  printf("total phys    = %10.0f\n",coinPhys->GetBinContent(2));
  printf("total DS-F5   = %10.0f\n",coinF5->GetBinContent(2));
  printf("total DS-DALI = %10.0f\n",coinDALI->GetBinContent(2));


  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("cd f8ppac");
  TH1* f8track = (TH1*) gDirectory->Get("f8track");
  TH1* f8track_cut = (TH1*) gDirectory->Get("f8track_cut");
  double f8event = f8track->GetEntries();
  double f8event_cut = f8track_cut->GetEntries();
  double rate = f8event/hit71pla;
  double rate_cut = f8event_cut/hit71pla;
  

  cout <<  "# ---  F8 transmission rate  --- #" << endl;
  
  printf("total events      : %10.0f\n", hit71pla);
  printf("f8track           : %10.0f\n", f8event);
  printf("f8track with veto : %10.0f\n", f8event_cut);
  printf("rate              : %10.2f\n", f8event/hit71pla);
  printf("rate_cut          : %10.2f\n", f8event_cut/hit71pla);
  /***********************************************************************/

  gROOT->ProcessLine(Form(".! evince shift/%s%04d/%s%04d.pdf",name,run,name,run));


}
