#include "shift.C"

void runShift(int run, int nEvt, const char* name = "Be12") 
{

  gROOT->ProcessLine(Form("add steering/shift.tmpl.yaml NAME=%s NUM=%04d EVTNUM=%d",name,run,nEvt));
  art::TLoopManager::Instance()->GetLoop()->Resume();
  
  shift(run,name);


}
