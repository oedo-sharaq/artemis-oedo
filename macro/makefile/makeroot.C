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

#define N 26
//#define N 25
//#define N 51
//#define N 52
//#define N 103

using std::cout;
using std::endl;


void makeroot() {

  int runnum[N];
  for (int i=0; i < N; i++){
 //  runnum[i] = 170 + i;
  // runnum[i] = 222 + i;
   runnum[i] = 247 + i;
   }

//  TString steering_template_name = "steering/makeroot_template_back.yaml";
  TString steering_template_name = "steering/makeroot_template.yaml";
  TString steering_current_name = "steering/makeroot_last.yaml";
  TString anchor = "anchor:\n";
 
  for(int j=0; j < N; j++){
  int t = runnum[j];
  TString ridf = Form("ridf/physics%04d.ridf",t);
  TString temple = ridf;
   if (!(gSystem->FindFile(".",temple))) {
      printf("Error in <makeroot>: file not found: %s\n",ridf.Data());
      return;
   }

   anchor.Append(Form("  - &ridf%d %s\n",j,ridf.Data()));
   }
   ifstream fin(steering_template_name);
   TString tempyaml;
   tempyaml.ReadFile(fin);
   fin.close();
   TString yaml = anchor + tempyaml;
   FILE *fp = fopen(steering_current_name.Data(),"w");
   yaml.Puts(fp);
   fclose(fp);

  
   gROOT->ProcessLine(Form("add %s",steering_current_name.Data()));
   gROOT->ProcessLine(Form("res"));
   cout << endl;
   cout << "Now Looping Please wait..." << endl;
   cout << endl;


}
