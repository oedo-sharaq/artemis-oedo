



 Int_t Nrun_2  = 2 * Nrun;
 Int_t Nrun_3  = 3 * Nrun;
 Int_t Nrun_4  = 4 * Nrun;
 Int_t Nrun_5  = 5 * Nrun;
 Int_t Nrun_6  = 6 * Nrun;
 Int_t Nrun_7  = 7 * Nrun;
 Int_t Nrun_8  = 8 * Nrun;
 Int_t Nrun_9  = 9 * Nrun;
 Int_t Nrun_10 = 10 * Nrun;
 Int_t Nrun_11 = 11 * Nrun;
 Int_t Nrun_12 = 12 * Nrun;
 Int_t Nrun_13 = 13 * Nrun;
 Int_t Nrun_14 = 14 * Nrun;
 Int_t Nrun_15 = 15 * Nrun;
 Int_t Nrun_16 = 16 * Nrun;
 Int_t Nrun_17 = 17 * Nrun;
 Int_t Nrun_18 = 18 * Nrun;
 Int_t Nrun_19 = Nrun_18 + Nrun_ni;

 for (int isol = 0; isol < Nevt; isol++){
  h_aq_sol->Fill(b_re[isol]);
	 
	if(0 <= isol && isol  < Nrun){
	 b(isol,1)-Fill(b_re(isol));
 } else if(Nrun <= isol && isol  < Nrun_2){
	 h_39Ca_sol->Fill(b_re(isol));
 } else if(Nrun_2 <= isol && isol  < Nrun_3){
	 h_40Sc_sol->Fill(b_re(isol));
 } else if(Nrun_3 <= isol && isol  < Nrun_4){
	 h_41Sc_sol->Fill(b_re(isol));
 } else if(Nrun_4 <= isol && isol  < Nrun_5){
	 h_40Ti_sol->Fill(b_re(isol));
 } else if(Nrun_5 <= isol && isol  < Nrun_6){
	 h_41Ti_sol->Fill(b_re(isol));
 } else if(Nrun_6 <= isol && isol  < Nrun_7){
	 h_42Ti_sol->Fill(b_re(isol));
 } else if(Nrun_7 <= isol && isol  < Nrun_8){
	 h_43V_sol->Fill(b_re(isol));
 } else if(Nrun_8 <= isol && isol  < Nrun_9){
	 h_44V_sol->Fill(b_re(isol));
 } else if(Nrun_9 <= isol && isol  < Nrun_10){
	 h_44Cr_sol->Fill(b_re(isol));
 } else if(Nrun_10 <= isol && isol  < Nrun_11){
	 h_45Cr_sol->Fill(b_re(isol));
 } else if(Nrun_11 <= isol && isol  < Nrun_12){
	 h_46Cr_sol->Fill(b_re(isol));
 } else if(Nrun_12 <= isol && isol  < Nrun_13){
	 h_46Mn_sol->Fill(b_re(isol));
 } else if(Nrun_13 <= isol && isol  < Nrun_14){
	 h_47Mn_sol->Fill(b_re(isol));
 } else if(Nrun_14 <= isol && isol  < Nrun_15){
	 h_48Mn_sol->Fill(b_re(isol));
 } else if(Nrun_15 <= isol && isol  < Nrun_16){
	 h_48Fe_sol->Fill(b_re(isol));
 } else if(Nrun_16 <= isol && isol  < Nrun_17){
	 h_49Fe_sol->Fill(b_re(isol));
 } else if(Nrun_17 <= isol && isol  < Nrun_18){
	 h_50Co_sol->Fill(b_re(isol));
 } else if(Nrun_18 <= isol && isol  < Nrun_19){
	 h_52Ni_sol->Fill(b_re(isol));
 }












