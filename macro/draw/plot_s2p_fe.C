#include <vector>
#include <fstream>

void plot_s2p_fe() {

  TCanvas *c1 = new TCanvas("c1","c1");
  c1 -> cd();
  c1->SetTickx(); c1->SetTicky();



 TGraphErrors* g1 = new TGraphErrors(5);
 g1->SetMarkerSize(1);
 g1->SetMarkerStyle(27);
 g1->SetMarkerColor(kRed);
 g1->SetLineColor(kRed);
 g1->SetPoint(0,45,-2.8);
 g1->SetPointError(0,0,3.2);
 g1->SetPoint(1,46,-0.26);
 g1->SetPointError(1,0,0.6);
 g1->SetPoint(2,47,1.24);
 g1->SetPointError(2,0,0.39);
 g1->SetPoint(3,48,3.19);
 g1->SetPointError(3,0,0.39);
 g1->SetPoint(4,49,4.92);
 g1->SetPointError(4,0,0.29);





 TGraphErrors* g2 = new TGraphErrors(5);
 g2->SetMarkerStyle(21);
 g2->SetMarkerSize(1);
 g2->SetMarkerColor(kBlack);
 g2->SetLineColor(kBlack);
 g2->SetPoint(0,45,-1.800);
 g2->SetPointError(0,0,0.2);
 g2->SetPoint(1,46,-0.050);
 g2->SetPointError(1,0,0.3);
 g2->SetPoint(2,47,2.19);
 g2->SetPointError(2,0,0.5);
 g2->SetPoint(3,48,3.11);
 g2->SetPointError(3,0,0.09);
 g2->SetPoint(4,49,4.766);
 g2->SetPointError(4,0,0.025);



 TMultiGraph* mg = new TMultiGraph();

 mg->Add(g1);
 mg->Add(g2);

 mg->Draw("APl");









}
