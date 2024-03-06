{
  for (int i = 0; i<6; i++){
    tree->Draw(Form("tinat%d.fTiming>>yyt%d(200,0,2000)",i+1,i+1),"coins0");
  }
}
