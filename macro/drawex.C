{
  tree->Draw("tke2:theta>>ang1(100,90,180,100,0,20)", "coins0&&pid9&&tinaxy&&tgate&&pgate1&&pid1", "colz");
  tree->Draw("ex2>>ex1(100,-20,30)", "coins0&&tinaxy&&pid9&&tgate&&pgate1&&pid1");
  tree->Draw("tke2:theta>>ang2(100,90,180,100,0,20)", "coins0&&pid9&&tinaxy&&tgate&&pgate2&&pid1", "colz");
  tree->Draw("ex2>>ex2(100,-20,30)", "coins0&&tinaxy&&pid9&&tgate&&pgate2&&pid1");
  tree->Draw("tke2:theta>>ang(100,90,180,100,0,20)", "coins0&&pid9&&tinaxy&&tgate&&pgate&&pid1", "colz");
  tree->Draw("ex2>>ex(100,-20,30)", "coins0&&tinaxy&&pid9&&tgate&&pgate&&pid1");
}
