#include <vector>
#include <fstream>

void massdiff_plsnoref() {


  vector<Double_t> Aq, Massdiff, StatE, LitE, width;
  vector<Double_t> Aq_noref, Massdiff_noref, StatE_noref, LitE_noref, width_noref;

  Aq.push_back(1.89927);
  Aq.push_back(1.94799);
  Aq.push_back(1.90317);
  Aq.push_back(1.95037);
  Aq.push_back(1.8172);
  Aq.push_back(1.86232);
  Aq.push_back(1.90732);
  Aq.push_back(1.86818);
  Aq.push_back(1.91138);
  Aq.push_back(1.83219);
  Aq.push_back(1.87358);
  Aq.push_back(1.9148);
  Aq.push_back(1.83892);
  Aq.push_back(1.87848);
  Aq.push_back(1.91819);
  Aq.push_back(1.84486);
  Aq.push_back(1.88305);
  Aq.push_back(1.8506);
  Aq.push_back(1.85573);

  Aq_noref.push_back(1.95624);
  Aq_noref.push_back(1.95783732);
  Aq_noref.push_back(1.88725476);

  Massdiff.push_back(13.22);
  Massdiff.push_back(11.2);
  Massdiff.push_back(11.07);
  Massdiff.push_back(-10.4);
  Massdiff.push_back(6.9036);
  Massdiff.push_back(9.966);
  Massdiff.push_back(-6.8377);
  Massdiff.push_back(-7.096895);
  Massdiff.push_back(7.589455);
  Massdiff.push_back(0.88521);
  Massdiff.push_back(6.6094);
  Massdiff.push_back(-0.33614);
  Massdiff.push_back(8.4346);
  Massdiff.push_back(-1.9432);
  Massdiff.push_back(-9.1443);
  Massdiff.push_back(-4.44204);
  Massdiff.push_back(-7.33105);
  Massdiff.push_back(-8.47877);
  Massdiff.push_back(-6.79416);

  Massdiff_noref.push_back(10.503);
  Massdiff_noref.push_back(2.3156);
  Massdiff_noref.push_back(8.723);

  StatE.push_back(2.1732);
  StatE.push_back(0.3944);
  StatE.push_back(0.6427);
  StatE.push_back(0.56806);
  StatE.push_back(3.9067);
  StatE.push_back(0.5121);
  StatE.push_back(0.38322);
  StatE.push_back(0.555);
  StatE.push_back(0.3041);
  StatE.push_back(0.95412);
  StatE.push_back(0.32244);
  StatE.push_back(0.37244);
  StatE.push_back(0.9198);
  StatE.push_back(0.6245);
  StatE.push_back(0.6595);
  StatE.push_back(0.8632);
  StatE.push_back(1.10672);
  StatE.push_back(2.48024);
  StatE.push_back(25.037);

  StatE_noref.push_back(0.4102);
  StatE_noref.push_back(0.8952);
  StatE_noref.push_back(3.0153);

  LitE.push_back(0.0095);
  LitE.push_back(0.03);
  LitE.push_back(0.133);
  LitE.push_back(0.0038);
  LitE.push_back(0.01227);
  LitE.push_back(1.2727);
  LitE.push_back(3.1818);
  LitE.push_back(0.30434);
  LitE.push_back(1.7391);
  LitE.push_back(0.4583);
  LitE.push_back(1.666);
  LitE.push_back(2.0833);
  LitE.push_back(3.6);
  LitE.push_back(1.2);
  LitE.push_back(0.28);
  LitE.push_back(0.923);
  LitE.push_back(3.4615);
  LitE.push_back(4.8148);
  LitE.push_back(2.8571);

  LitE_noref.push_back(0.208);
  LitE_noref.push_back(0.088);
  LitE_noref.push_back(1.8518);

  width.push_back(1);  
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);
  width.push_back(1);

  width_noref.push_back(1);
  width_noref.push_back(1);
  width_noref.push_back(1);


  Double_t* Aq_pointer = &(Aq.at(0));
  Double_t* Massdiff_pointer = &(Massdiff.at(0));
  Double_t* StatE_pointer = &(StatE.at(0));
  Double_t* LitE_pointer = &(LitE.at(0));
  Double_t* width_pointer = &(width.at(0));

  Double_t* Aq_noref_pointer = &(Aq_noref.at(0));
  Double_t* Massdiff_noref_pointer = &(Massdiff_noref.at(0));
  Double_t* StatE_noref_pointer = &(StatE_noref.at(0));
  Double_t* LitE_noref_pointer = &(LitE_noref.at(0));
  Double_t* width_noref_pointer = &(width_noref.at(0));


  TGraphMultiErrors* aq = new TGraphMultiErrors("aq","aq",Aq.size(), Aq_pointer, Massdiff_pointer,0,0,StatE_pointer,StatE_pointer);


  TGraphMultiErrors* aq_noref = new TGraphMultiErrors("aq_noref","aq_noref",Aq_noref.size(), Aq_noref_pointer, Massdiff_noref_pointer,0,0,StatE_noref_pointer,StatE_noref_pointer);


  TCanvas *c1 = new TCanvas("c1","c1");
  c1 -> cd();
  c1->SetTickx(); c1->SetTicky();

  
  aq->AddYError(Aq.size(),LitE_pointer,LitE_pointer);
  aq ->SetTitle(0);
  aq -> GetXaxis() -> SetTitle("#DeltaE_{pla} (ns)");
  aq -> GetYaxis() -> SetTitle("#DeltaE_{pla} (MeV)");
  aq->SetMarkerStyle(20);
  aq->GetAttLine(0)->SetLineColor(kRed);
  aq->GetAttLine(1)->SetLineColor(kBlue);
  aq->GetAttFill(1)->SetFillStyle(0);
  aq->GetXaxis()->SetTitleOffset(0.95);
  aq->GetXaxis()->SetLabelSize(0.05);
  aq->GetXaxis()->SetTitleSize(0.05);
  aq->GetYaxis()->SetLabelSize(0.05);
  aq->GetYaxis()->SetTitleSize(0.05);
//  aq -> Draw("APS");

  aq_noref->AddYError(Aq_noref.size(),LitE_noref_pointer,LitE_noref_pointer);
  aq_noref ->SetTitle(0);
  aq_noref->SetMarkerStyle(24);
  aq_noref->GetAttLine(0)->SetLineColor(kRed);
  aq_noref->GetAttLine(1)->SetLineColor(kBlue);
  aq_noref->GetAttFill(1)->SetFillStyle(0);
  aq_noref->GetXaxis()->SetTitleOffset(0.95);
  aq_noref->GetXaxis()->SetLabelSize(0.05);
  aq_noref->GetXaxis()->SetTitleSize(0.05);
  aq_noref->GetYaxis()->SetLabelSize(0.05);
  aq_noref->GetYaxis()->SetTitleSize(0.05);
//  aq_noref -> Draw("SMAE APS");

 TMultiGraph *mg = new TMultiGraph();
 mg->Add(aq);
 mg->Add(aq_noref);
 mg->Draw("APS");


  TGraph *graph = new TGraph(4);

  Int_t ci;
  ci = TColor::GetColor("#ffcccc");
//  graph->SetFillColor(ci);
  graph->SetPoint(0,1.8,11.2);
  graph->SetPoint(1,1.96,11.2);
  graph->SetPoint(2,1.8,-11.2);
  graph->SetPoint(3,1.96,-11.2);
  graph->SetMarkerStyle(20);
  graph -> Draw("same");


  return c1;
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
