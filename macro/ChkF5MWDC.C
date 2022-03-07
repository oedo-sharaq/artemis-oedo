/* Made by Yuto HIJIKATA
 * @data 2021.05.20 19:17
 */
void ChkF5MWDC() {

  gROOT->ProcessLine("zone 2 2");
  gROOT->ProcessLine("ht 3/0,3/2,4/0,4/2 colz");
  gROOT->ProcessLine("save");
  gROOT->ProcessLine("pri");

}
