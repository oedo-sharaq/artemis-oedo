#include "TQuitProcessor.h"
#include "TROOT.h"
#include "TSystem.h"

ClassImp(art::TQuitProcessor);

art::TQuitProcessor::TQuitProcessor()
{
}
art::TQuitProcessor::~TQuitProcessor()
{
}

void art::TQuitProcessor::Init(TEventCollection *)
{
}

void art::TQuitProcessor::Process()
{
}

void art::TQuitProcessor::PreLoop()
{
}

void art::TQuitProcessor::PostLoop()
{
  Info("PostLoop","Quit from artemis");
  gSystem->Exit(0);
}
