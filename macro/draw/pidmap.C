#include <vector>
#include <fstream>

void pidmap() {


  vector<Double_t> Ref_aq, Ref_z, Unk_aq, Unk_z, Iso_aq, Iso_z;  

  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();
  Ref_aq.push_back();

  Ref_z.push_back(20);
  Ref_z.push_back(20);
  Ref_z.push_back(21);
  Ref_z.push_back(21);
  Ref_z.push_back(22);
  Ref_z.push_back(22);
  Ref_z.push_back(22);
  Ref_z.push_back(23);
  Ref_z.push_back(23);
  Ref_z.push_back(24);
  Ref_z.push_back(24);
  Ref_z.push_back(24);
  Ref_z.push_back(24);
  Ref_z.push_back(25);
  Ref_z.push_back(25);
  Ref_z.push_back(25);
  Ref_z.push_back(26);
  Ref_z.push_back(26);
  Ref_z.push_back(27);
  Ref_z.push_back(28);


  Double_t* Ref_aq_nspointer = &(Ref_aq.at(0));
  Double_t* Ref_z_MeVpointer = &(Ref_z.at(0));


  Unk_aq.push_back(377.6);
  Unk_aq.push_back(398.5);
  Unk_aq.push_back(414);
  Unk_aq.push_back(422.9);
  Unk_aq.push_back(445.8);

  Unk_z.push_back(80.8);
  Unk_z.push_back(98.5);
  Unk_z.push_back(107.5);
  Unk_z.push_back(117);
  Unk_z.push_back(138.3);


  Double_t* Unk_aq_nspointer = &(Unk_aq.at(0));
  Double_t* Unk_z_MeVpointer = &(Unk_z.at(0));





  TGraphErrors* ref = new TGraphErrors(dEpla_ns.size(), dEpla_nspointer, dEpla_MeVpointer, 0, 0);
  TGraphErrors* unk = new TGraphErrors(dEpla_ns.size(), dEpla_nspointer, dEpla_MeVpointer, 0, 0);
  TGraphErrors* iso = new TGraphErrors(dEpla_ns.size(), dEpla_nspointer, dEpla_MeVpointer, 0, 0);
  

  TCanvas *c1 = new TCanvas("c1","c1");
  c1 -> cd();
  c1->SetTickx(); c1->SetTicky();

  g ->SetTitle(0);
  g -> GetXaxis() -> SetTitle("#DeltaE_{pla} (ns)");
  g -> GetYaxis() -> SetTitle("#DeltaE_{pla} (MeV)");
  g->SetMarkerStyle(20);
  g->GetXaxis()->SetTitleOffset(0.95);
  g->GetXaxis()->SetLabelSize(0.05);
  g->GetXaxis()->SetTitleSize(0.05);
  g->GetYaxis()->SetLabelSize(0.05);
  g->GetYaxis()->SetTitleSize(0.05);
  g -> Draw("AP");
  fitfun->SetLineColor(kRed);
  fitfun->SetLineStyle(9);
  fitfun->Draw("same");

//  TCanvas *c2 = new TCanvas("c2","c2");
//  c2 -> cd();
//  c2->SetTickx(); c2->SetTicky();
//
//  g_res ->SetTitle(0);
//  g_res -> GetXaxis() -> SetTitle("#DeltaE_{pla} (ns)");
//  g_res -> GetYaxis() -> SetTitle("Residual (MeV)");
//  g_res->SetMarkerStyle(20);
//  g_res->SetMinimum(-2.0); g_res->SetMaximum(2.0);
//  g_res->GetXaxis()->SetTitleOffset(0.95);
//  g_res->GetXaxis()->SetLabelSize(0.05);
//  g_res->GetXaxis()->SetTitleSize(0.05);
//  g_res->GetYaxis()->SetLabelSize(0.05);
//  g_res->GetYaxis()->SetTitleSize(0.05);
//  g_res -> Draw("AP");

  return;
}
