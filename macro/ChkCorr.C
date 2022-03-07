/* Made by RTsuji
 *@data 2021.05.22
 *
 */
void ChkCorr() {
  gROOT->ProcessLine("cd");
  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("ht 0/4,0/5,0/6,0/7 colz");
  gROOT->ProcessLine("save");
  gROOT->ProcessLine("pri");
  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("ht 2/4,2/5,2/6,2/7 colz");
  gROOT->ProcessLine("save");
  gROOT->ProcessLine("pri");
  gROOT->ProcessLine("zone");
  gROOT->ProcessLine("ht 0/8");
  gROOT->ProcessLine("save");
  gROOT->ProcessLine("pri");
  
}
