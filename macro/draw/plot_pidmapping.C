#include <vector>
#include <fstream>

void plot_pidmapping() {


  vector<Double_t> aoq_ref, z_ref, aoq_iso, z_iso, aoq_new, z_new;  

  aoq_ref.push_back(1.89826838);
  aoq_ref.push_back(1.94798796);
  aoq_ref.push_back(1.90316521);
  aoq_ref.push_back(1.95036921);
  aoq_ref.push_back(1.81719569);
  aoq_ref.push_back(1.86232290);
  aoq_ref.push_back(1.90731844);
  aoq_ref.push_back(1.86818142);
  aoq_ref.push_back(1.91138485);
  aoq_ref.push_back(1.83218575);
  aoq_ref.push_back(1.87358000);
  aoq_ref.push_back(1.91480106);
  aoq_ref.push_back(1.83891945);
  aoq_ref.push_back(1.87848359);
  aoq_ref.push_back(1.91819472);
  aoq_ref.push_back(1.84486307);
  aoq_ref.push_back(1.88304627);
  aoq_ref.push_back(1.85060539);
  aoq_ref.push_back(1.85573090);

  z_ref.push_back(20);
  z_ref.push_back(20);
  z_ref.push_back(21);
  z_ref.push_back(21);
  z_ref.push_back(22);
  z_ref.push_back(22);
  z_ref.push_back(22);
  z_ref.push_back(23);
  z_ref.push_back(23);
  z_ref.push_back(24);
  z_ref.push_back(24);
  z_ref.push_back(24);
  z_ref.push_back(25);
  z_ref.push_back(25);
  z_ref.push_back(25);
  z_ref.push_back(26);
  z_ref.push_back(26);
  z_ref.push_back(27);
  z_ref.push_back(28);


  aoq_iso.push_back(1.95256747);
  aoq_iso.push_back(1.95448605);

  z_iso.push_back(22);
  z_iso.push_back(23);


  aoq_new.push_back(1.77230183);
  aoq_new.push_back(1.79103125);
  aoq_new.push_back(1.74976851);
  aoq_new.push_back(1.80685077);
  aoq_new.push_back(1.76873359);
  aoq_new.push_back(1.73081708);
  aoq_new.push_back(1.82043492);
  aoq_new.push_back(1.78503464);
  aoq_new.push_back(1.74978006);

  z_new.push_back(22);
  z_new.push_back(24);
  z_new.push_back(24);
  z_new.push_back(26);
  z_new.push_back(26);
  z_new.push_back(26);
  z_new.push_back(28);
  z_new.push_back(28);
  z_new.push_back(28);


  Double_t* aoqref_pointer = &(aoq_ref.at(0));
  Double_t* zref_pointer = &(z_ref.at(0));

  Double_t* aoqiso_pointer = &(aoq_iso.at(0));
  Double_t* ziso_pointer = &(z_iso.at(0));

  Double_t* aoqnew_pointer = &(aoq_new.at(0));
  Double_t* znew_pointer = &(z_new.at(0));



  TGraphErrors* g1 = new TGraphErrors(aoq_ref.size(), aoqref_pointer, zref_pointer, 0, 0);
  TGraphErrors* g2 = new TGraphErrors(aoq_iso.size(), aoqiso_pointer, ziso_pointer, 0, 0);
  TGraphErrors* g3 = new TGraphErrors(aoq_new.size(), aoqnew_pointer, znew_pointer, 0, 0);
//  TF1 *fitfun = new TF1("fitfun","0.9253*x-12.221",170,300);
//  TF1 *fitfun = new TF1("fitfun","0.8309*x-233.7",370,500);
  

//  TCanvas *c1 = new TCanvas("c1","c1");
//  c1 -> cd();
//  c1->SetTickx(); c1->SetTicky();

//  g ->SetTitle(0);
//  g -> GetXaxis() -> SetTitle("#DeltaE_{pla} (ns)");
//  g -> GetYaxis() -> SetTitle("#DeltaE_{pla} (MeV)");
//  g1->SetMarkerStyle(20);
//  g1->GetXaxis()->SetTitleOffset(0.95);
//  g1->GetXaxis()->SetLabelSize(0.05);
//  g1->GetXaxis()->SetTitleSize(0.05);
//  g1->GetYaxis()->SetLabelSize(0.05);
//  g1->GetYaxis()->SetTitleSize(0.05);
//  g1-> Draw("P");

 g1->SetMarkerStyle(20);
 g1->SetMarkerColor(1);
 g1->SetMarkerSize(1.5);
// g1->Draw("AP");
 g2->SetMarkerStyle(21);
 g2->SetMarkerColor(4);
 g2->SetMarkerSize(1.5);

 g3->SetMarkerStyle(110);
 g3->SetMarkerColor(2);
 g3->SetMarkerSize(1.5);

 TMultiGraph *mg = new TMultiGraph();
 mg->Add(g1);
 mg->Add(g2);
 mg->Add(g3);

 mg->GetHistogram()->GetXaxis()->SetLimits(1.7,1.96);

 mg->Draw("AP");

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

//  return;
}
