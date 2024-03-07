
void 2psearaption(){

 const Double_t m_p = 938.27270621 //[MeV]


 const err_sys = ; //[MeV/q]
 
 

// 2p separation energy in Cr isotopes

 Sp2_42cr = - (m_42cr - m_40ti - 2*m_p);  
 Sp2_43cr = - (m_43cr - m_41ti - 2*m_p);  
 Sp2_44cr = - (m_44cr - m_42ti - 2*m_p);  

 errS2p_42cr = err_42cr + err_40ti;  
 errS2p_43cr = err_43cr + err_41ti;  
 errS2p_44cr = err_44cr + err_42ti;  


// 2p separation energy in Fe isotopes

 Sp2_45fe = - (m_45fe - m_43cr - 2*m_p);  
 Sp2_46fe = - (m_46fe - m_44cr - 2*m_p);  
 Sp2_47fe = - (m_47fe - m_45cr - 2*m_p);  
 Sp2_48fe = - (m_48fe - m_46cr - 2*m_p);  

 errSp2_45fe = err_45fe + err_43cr;  
 errSp2_46fe = err_46fe + err_44cr;  
 errSp2_47fe = err_47fe + err_45cr;  
 errSp2_48fe = err_48fe + err_46cr;  


// 2p separation energy in Ni isotopes

 Sp2_49ni = - (m_49ni - m_47fe - 2*m_p);  
 Sp2_50ni = - (m_50ni - m_48fe - 2*m_p);  
 Sp2_51ni = - (m_51ni - m_49fe - 2*m_p);  
 Sp2_52ni = - (m_52ni - m_50fe - 2*m_p);  

 errSp2_49ni = err_49ni + err_47fe;  
 errSp2_50ni = err_50ni + err_48fe;  
 errSp2_51ni = err_51ni + err_49fe;  
 errSp2_52ni = err_52ni + err_50fe;  











}
