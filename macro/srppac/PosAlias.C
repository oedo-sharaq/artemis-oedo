{
   tree->SetAlias("Aangle","(-srppacu_xcw[0].fPosition+srppacd_xcw[0].fPosition)/466");
   tree->SetAlias("xmean","(srppacu_xcw[0].fPosition+srppacd_xcw[0].fPosition)/2");


   tree->SetAlias("Bangle","(-srppacu_ycw[0].fPosition+srppacd_ycw[0].fPosition)/466");
   tree->SetAlias("ymean","(srppacu_ycw[0].fPosition+srppacd_ycw[0].fPosition)/2");

  
   tree->SetAlias("xtpc","xmean+Aangle*958");
   tree->SetAlias("ytpc","ymean+Bangle*958");

   tree->SetAlias("xxe","xmean+angle*1520");
   tree->SetAlias("yxe","ymean+angle*1520");


}
