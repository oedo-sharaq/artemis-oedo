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

#define N 103

using std::cout;
using std::endl;


void makeroot_BLD() {

  int runnum[N];
  for (int i=0; i < N; i++){
   runnum[i] = 170 + i;
   }

//  TString steering_template_name = "steering/makeroot_template_back.yaml";
  TString steering_template_name = "steering/BLD.yaml";
  TString steering_current_name = Form("steering/makeroot_last.yaml NUM=%04d",t);
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
   art::TLoopManager::Instance()->GetLoop()->Resume();
   gApplication->Terminate();
 

//   gROOT->ProcessLine(Form("res"));
//   cout << endl;
//   cout << "Now Looping Please wait..." << endl;
//   cout << endl;


}
