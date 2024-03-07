#include <vector>
#include <fstream>

void plot_s2n_fe() {


  vector<Double_t> dEpla_ns, dEpla_MeV;  
//  dEpla_ns.push_back(176.1);
//  dEpla_ns.push_back(202.5);
//  dEpla_ns.push_back(227.6);
//  dEpla_ns.push_back(242.3);
//  dEpla_ns.push_back(286.9);

  dEpla_ns.push_back(377.6);
  dEpla_ns.push_back(398.5);
  dEpla_ns.push_back(414);
  dEpla_ns.push_back(422.9);
  dEpla_ns.push_back(445.8);

//  dEpla_MeV.push_back(147.5);
//  dEpla_MeV.push_back(180);
//  dEpla_MeV.push_back(196);
//  dEpla_MeV.push_back(214);
//  dEpla_MeV.push_back(252);

  dEpla_MeV.push_back(80.8);
  dEpla_MeV.push_back(98.5);
  dEpla_MeV.push_back(107.5);
  dEpla_MeV.push_back(117);
  dEpla_MeV.push_back(138.3);


  Double_t* dEpla_nspointer = &(dEpla_ns.at(0));
  Double_t* dEpla_MeVpointer = &(dEpla_MeV.at(0));

  TGraphErrors* g = new TGraphErrors(dEpla_ns.size(), dEpla_nspointer, dEpla_MeVpointer, 0, 0);
//  TF1 *fitfun = new TF1("fitfun","0.9253*x-12.221",170,300);
  TF1 *fitfun = new TF1("fitfun","0.8309*x-233.7",370,500);
  

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
