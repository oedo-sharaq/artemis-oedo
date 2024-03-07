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


void BLD(int runnumber) {

   gROOT->ProcessLine(Form("add steering/BLD.yaml NUM=%04d",runnumber));
   art::TLoopManager::Instance()->GetLoop()->Resume();
   gApplication->Terminate();


}
