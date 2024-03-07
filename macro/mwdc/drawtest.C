void drawtest(){

// TString *str = "\""tree->Draw("dc31_x1.fTiming>>dc31_x1_dtdl(260,-53,0)","abs(dc31_x1.fCharge-500)<=500")\""
// TString s = "\"tree->Draw("dc31_x1.fTiming>>dc31_x1_dtdl(260,-53,0)\"";
//
//
//   TString ch = "\"abs(dc31_x1.fCharge-500)<=500\")";
//   TString com = ",";
//
//   s += com;
//   s += ch;


// gROOT->ProcessLine(Form("\"tree->Draw(\"dc31_x1.fTiming>>dc31_x1_dtdl(260,-53,0)\",\"abs(dc31_x1.fCharge-500)<=500\")\""));
 gROOT->ProcessLine("tree->Draw(\"dc31_x1.fTiming>>dc31_x1_dtdl(260,-53,0)\",\"abs(dc31_x1.fCharge-500)<=500\")");


}
