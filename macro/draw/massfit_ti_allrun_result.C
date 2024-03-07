

void massfit_ti_allrun_result(){

gROOT->Reset();


//TGraphErrors *g1 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.40ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
TGraphErrors *g1 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip2/ref_fitting_3step.40ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
g1->SetMarkerColor(kRed);
g1->SetMarkerSize(10000.);
g1->SetLineColor(kRed);


//TGraphErrors *g2 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.41ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
TGraphErrors *g2 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip2/ref_fitting_3step.41ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
g2->SetMarkerColor(kBlue);
g2->SetMarkerSize(10000.);
g2->SetLineColor(kBlue);

//TGraphErrors *g3 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip1/ref_fitting_3step.43ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
TGraphErrors *g3 = new TGraphErrors("/home/sh13/art_analysis/user/hanai/prm/mass/strip2/ref_fitting_3step.43ti_aq.170272.dat","%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %*lg");
g3->SetMarkerColor(kGreen);
g3->SetMarkerSize(10000.);
g3->SetLineColor(kGreen);

gROOT->ProcessLine("zone");

TMultiGraph *mg = new TMultiGraph();

mg->Add(g1);
mg->Add(g2);
mg->Add(g3);
//mg->SetTitle("Run dependence;RunNumber;m_exp - m_ref [keV]");
mg->SetTitle("Run dependence;RunNumber;tof_exp - tof_ref [ps]");


mg->Draw("apl");

 TLegend *lg = new TLegend(0.67,0.7,0.85,0.88);
 lg->AddEntry(g1,"40Ti","lp");
 lg->AddEntry(g2,"41Ti","lp");
 lg->AddEntry(g3,"43Ti","lp");
 lg->SetBorderSize(0);
 lg->SetTextSize(0.05);
 lg->SetTextFont(12);
 lg->SetFillStyle(0);
 lg->SetFillColor(0);
 lg->Draw();



}
