{


 gROOT->ProcessLine("tree->SetAlias("sr9.fX","(345*sr91_xc0.fPosition+100*sr92_xc0.fPosition)/(100+345)")");
 gROOT->ProcessLine("tree->SetAlias("sr9.fY","(345*sr91_yc0.fPosition+100*sr92_yc0.fPosition)/(100+345)")");

 gROOT->ProcessLine("tree->SetAlias("sr9.fA","445./TMath::Abs(sr91_xc0.fPosition-sr92_xc0.fPosition)")");
 gROOT->ProcessLine("tree->SetAlias("sr9.fB","445./TMath::Abs(sr91_yc0.fPosition-sr92_yc0.fPosition)")");
 
 gROOT->ProcessLine("tree->SetAlias("tof:","f3pla.fTiming-f2pla.fTiming")");


tree->SetAlias("sr9.fX","(345*sr91_xc0.fPosition+100*sr92_xc0.fPosition)/(100+345)")
tree->SetAlias("sr9.fY","(345*sr91_yc0.fPosition+100*sr92_yc0.fPosition)/(100+345)")

tree->SetAlias("sr9.fA","445./TMath::Abs(sr91_xc0.fPosition-sr92_xc0.fPosition)")
tree->SetAlias("sr9.fB","445./TMath::Abs(sr91_yc0.fPosition-sr92_yc0.fPosition)")

tree->SetAlias("tof","f3pla.fTiming-f2pla.fTiming")




}

