
void GetQcal(){

//  gROOT->ProcessLine("hsrc1q0idxhigh->FitSlicesY()");
//  gROOT->ProcessLine("hsrc1q0idxlow->FitSlicesY()");
//  gROOT->ProcessLine("hsrc1q0idyhigh->FitSlicesY()");
//  gROOT->ProcessLine("hsrc1q0idylow->FitSlicesY()");
//  gROOT->ProcessLine("hsrc2q0idxhigh->FitSlicesY()");
//  gROOT->ProcessLine("hsrc2q0idxlow->FitSlicesY()");
//  gROOT->ProcessLine("hsrc2q0idyhigh->FitSlicesY()");
//  gROOT->ProcessLine("hsrc2q0idylow->FitSlicesY()");

  gROOT->ProcessLine("hsrc1q0idx->FitSlicesY()");
  gROOT->ProcessLine("hsrc1q1idx->FitSlicesY()");
  gROOT->ProcessLine("hsrc1q0idy->FitSlicesY()");
  gROOT->ProcessLine("hsrc1q1idy->FitSlicesY()");
  gROOT->ProcessLine("hsrc2q0idx->FitSlicesY()");
  gROOT->ProcessLine("hsrc2q1idx->FitSlicesY()");
  gROOT->ProcessLine("hsrc2q0idy->FitSlicesY()");
  gROOT->ProcessLine("hsrc2q1idy->FitSlicesY()");


  TH1D *hist_high[4];
  TH1D *hist_low[4];
  TH1D *hist_sigma_high[4];
  TH1D *hist_sigma_low[4];


//  hist_high[0] = (TH1D*)gROOT->FindObject("hsrc1q0idxhigh_1");
//  hist_low[0]  = (TH1D*)gROOT->FindObject("hsrc1q0idxlow_1");
//  hist_high[1] = (TH1D*)gROOT->FindObject("hsrc1q0idyhigh_1");
//  hist_low[1]  = (TH1D*)gROOT->FindObject("hsrc1q0idylow_1");
//  hist_high[2] = (TH1D*)gROOT->FindObject("hsrc2q0idxhigh_1");
//  hist_low[2]  = (TH1D*)gROOT->FindObject("hsrc2q0idxlow_1");
//  hist_high[3] = (TH1D*)gROOT->FindObject("hsrc2q0idyhigh_1");
//  hist_low[3]  = (TH1D*)gROOT->FindObject("hsrc2q0idylow_1");

  hist_high[0] = (TH1D*)gROOT->FindObject("hsrc1q0idx_1");
  hist_low[0]  = (TH1D*)gROOT->FindObject("hsrc1q1idx_1");
  hist_high[1] = (TH1D*)gROOT->FindObject("hsrc1q0idy_1");
  hist_low[1]  = (TH1D*)gROOT->FindObject("hsrc1q1idy_1");
  hist_high[2] = (TH1D*)gROOT->FindObject("hsrc2q0idx_1");
  hist_low[2]  = (TH1D*)gROOT->FindObject("hsrc2q1idx_1");
  hist_high[3] = (TH1D*)gROOT->FindObject("hsrc2q0idy_1");
  hist_low[3]  = (TH1D*)gROOT->FindObject("hsrc2q1idy_1");

//  hist_sigma_high[0] = (TH1D*)gROOT->FindObject("hsrc1q0idxhigh_2");
//  hist_sigma_low[0]  = (TH1D*)gROOT->FindObject("hsrc1q0idxlow_2");
//  hist_sigma_high[1] = (TH1D*)gROOT->FindObject("hsrc1q0idyhigh_2");
//  hist_sigma_low[1]  = (TH1D*)gROOT->FindObject("hsrc1q0idylow_2");
//  hist_sigma_high[2] = (TH1D*)gROOT->FindObject("hsrc2q0idxhigh_2");
//  hist_sigma_low[2]  = (TH1D*)gROOT->FindObject("hsrc2q0idxlow_2");
//  hist_sigma_high[3] = (TH1D*)gROOT->FindObject("hsrc2q0idyhigh_2");
//  hist_sigma_low[3]  = (TH1D*)gROOT->FindObject("hsrc2q0idylow_2");

  hist_sigma_high[0] = (TH1D*)gROOT->FindObject("hsrc1q0idx_2");
  hist_sigma_low[0]  = (TH1D*)gROOT->FindObject("hsrc1q1idx_2");
  hist_sigma_high[1] = (TH1D*)gROOT->FindObject("hsrc1q0idy_2");
  hist_sigma_low[1]  = (TH1D*)gROOT->FindObject("hsrc1q1idy_2");
  hist_sigma_high[2] = (TH1D*)gROOT->FindObject("hsrc2q0idx_2");
  hist_sigma_low[2]  = (TH1D*)gROOT->FindObject("hsrc2q1idx_2");
  hist_sigma_high[3] = (TH1D*)gROOT->FindObject("hsrc2q0idy_2");
  hist_sigma_low[3]  = (TH1D*)gROOT->FindObject("hsrc2q1idy_2");


for(int j = 0; j < 4; j++){
  char *filename;
  filename = new char[32];
  sprintf(filename,"qcalprm_src_%d.dat",j);
  std::ofstream outfile;
  outfile.open(filename, std::ios::out);

   Double_t m_1[100];
   Double_t m_2[100];

   Double_t m_1_Mean = 0;
   Double_t m_2_Mean = 0;

   Int_t id_1[100];
   Int_t id_2[100];

   Int_t n_id_1 = 0;
   Int_t n_id_2 = 0;

   Double_t sig_1[100];
   Double_t sig_2[100];
 
   Int_t nbin_1 = 0;
   Int_t nbin_2 = 0;
   Int_t nbin = 0;

   nbin_1 = hist_high[j]->GetXaxis()->GetNbins();   
   nbin_2 = hist_low[j]->GetXaxis()->GetNbins();   

    if(nbin_1 != nbin_2){
		cout << "Error Something wrong with Number of bins" << endl;
		return;
	}

    nbin = nbin_1;
    cout << nbin_1 << "  "<< nbin_2 << endl;

  for (int k = 0; k < nbin; k++){
     m_1[k]   = hist_high[j]->GetBinContent(k+1);
     id_1[k]  = hist_high[j]->GetXaxis()->GetBinCenter(k+1);
     sig_1[k] = hist_sigma_high[j]->GetBinContent(k+1);

    if (m_1[k] > 0 && sig_1[k] < 15){
      n_id_1++;
     }
    }
 
   for(int l = 0; l < nbin; l++){
      if (m_1[l] > 0 && sig_1[l] < 15){
        m_1_Mean += m_1[l]/n_id_1;
      }
    }


  for (int m = 0; m < nbin; m++){
    m_2[m]   = hist_low[j]->GetBinContent(m+1);
    id_2[m]  = hist_low[j]->GetXaxis()->GetBinCenter(m+1);
    sig_2[m] = hist_sigma_low[j]->GetBinContent(m+1);

    if (m_2[m] > 0 && sig_2[m] < 15){
     n_id_2++;
      }
    }
 
    for(int n = 0; n < nbin; n++){
        if (m_2[n] > 0 && sig_2[n] < 15){
        m_2_Mean += m_2[n]/n_id_2;
       }
     }
 
  Double_t a[100];
  Double_t b[100];

//   outfile << m_1_Mean << "  " << m_2_Mean << endl; 
 
  for (int s = 0; s < nbin; s++){
    if(m_1[s] == 0 || m_2[s] == 0 || sig_1[s] >= 15 || sig_2[s] >= 15){
        outfile << 0 << " " << 1 << endl;
  //      outfile << id_1[s] << "  " << id_2[s] << "  " << m_1[s] << "  " << m_2[s] << "  " << sig_1[s] << "  " << sig_2[s] << "  " << 0 << " " << 1 << endl;
    }else{    
     a[s] = (m_1_Mean - m_2_Mean) / (m_1[s] - m_2[s]) ;  
     b[s] = m_1_Mean - a[s]*m_1[s];
     outfile << a[s] << " " << b[s] << endl;
   //  outfile << id_1[s] << "  " << id_2[s] << "  " << m_1[s] << "  " << m_2[s] << "  " << sig_1[s] << "  " << sig_2[s]  << "  " << a[s] << " " << b[s] << endl;
   }
  }

     outfile.close();
}


}
