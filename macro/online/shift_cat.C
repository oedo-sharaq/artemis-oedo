#include <fstream>
#include <stdlib.h>
#include <TROOT.h>
#include <TString.h>
#include <iostream>
#include <TSystem.h>
#include <TPaveLabel.h>
#include <TDatime.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TTree.h>

using std::cout;
using std::endl;


void shift_cat(int runnum, const char *runname) {
   TString steering_template_name ="steering/shift_cat.template.yaml";
   TString steering_current_name = "steering/shift_cat.last.yaml";
   TString ridf1 = Form("ridf/%s/CAT1_%s%04d.ridf",runname,runname,runnum);
   TString ridf2 = Form("ridf/%s/CAT2_%s%04d.ridf",runname,runname,runnum);
   TString test = ridf1;
   if (!(gSystem->FindFile(".",test))) {
      printf("Error in <shift_cat>: file not found: %s\n",ridf1.Data());
      return;
   }
   test = ridf2;
   if (!gSystem->FindFile(".",test)) {
      printf("Error in <shift_cat>: file not found: %s\n",ridf2.Data());
      return;
   }
   TString anchor = "anchor:\n";
   anchor.Append(Form("  - &ridf1 %s\n",ridf1.Data()));
   anchor.Append(Form("  - &ridf2 %s\n",ridf2.Data()));
   ifstream fin(steering_template_name);
   TString tempyaml;
   tempyaml.ReadFile(fin);
   fin.close();
   TString yaml = anchor + tempyaml;
   FILE *fp = fopen(steering_current_name.Data(),"w");
   yaml.Puts(fp);
   fclose(fp);


   gROOT->ProcessLine(Form("add %s",steering_current_name.Data()));

   TTree *tree = (TTree*)gDirectory->Get("tree");
   if (!tree) {
      printf("Error in <shift_cat>: TTree named 'tree' is not found. Please use 'tree' as the name of output tree.\n");
      return;
   }

   gROOT->ProcessLine(Form("res"));
   cout << endl;
   cout << "Please wait 10 seconds..." << endl;
   cout << endl;
   gSystem->Sleep(9000);
   gROOT->ProcessLine(Form("sus"));
   gSystem->Sleep(1000);
   cout << endl;
   cout << "Drawing the histogram..." << endl;
   cout << endl;
   
   gROOT->cd();
   TString name = TString::Format("%s%d (%d events)",runname,runnum,tree->GetEntries());
   TDatime now;
   TPaveLabel* title = new TPaveLabel(0.1,0.96,0.9,0.99,name);
   TPaveLabel* date = new TPaveLabel(0.7,0.01,0.9,0.03,now.AsString());
TDirectory *dir = (TDirectory*) gDirectory->FindObject("cat");
   if (!dir) {
      printf("Error in <shift_cat>: unexpected error. Directory cat should exist.");
      return;
   }
   const char *hnames[6] = { "ID", "ChargeIDWhole", "ChargeIDLow", "OffsetID", "OffsetIDFocus" , "Multiplicity"};
   TCanvas *cmain =new TCanvas("cmain","cat",1200,800);
   title->Draw();
   date->Draw();
   TPad* c = new TPad("Graphs","Graphs",0.05,0.05,0.95,0.95);   
   c->Draw();
   c->Divide(3,2);
   for (Int_t i=0; i!=6; ++i) {
      c->cd(i+1);
      TH1* obj = dynamic_cast<TH1*>(dir->Get(hnames[i]));
      if (!obj) {
         printf("Error in <shift_cat>: unexpected error. hist '%s' should exist",hnames[i]);
         printf("ask Tokieda\n");
         return;
      }
      if (obj->InheritsFrom("TH2")) {
         c->SetLogz();
         obj->Draw("colz");
      } else {
         obj->Draw();
      }
   }
   cmain->SaveAs(Form("Online/CAT_%s%04d.pdf",runname,runnum));
   gROOT->ProcessLine(Form(".! lpr Online/CAT_%s%04d.pdf",runname,runnum));
   cout << endl;
   gROOT->cd();
}
