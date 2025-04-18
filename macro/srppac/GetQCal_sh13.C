void GetQCal(){

//  printf("set runnumber\n");
//  char runnumber[10];
//  scanf("%s",runnumber);
//  char runnumber2[10];
//  sprintf(runnumber2,"%s",runname);

   gROOT->ProcessLine("hqiddeg1->FitSlicesY()");
   gROOT->ProcessLine("hqiddeg2->FitSlicesY()");
//   gROOT->ProcessLine("hqiddeg3->FitSlicesY()");

  
   TH1D *hqiddeg1_1 = (TH1D*)gROOT->FindObject("hqiddeg1_1"); 
   TH1D *hqiddeg2_1 = (TH1D*)gROOT->FindObject("hqiddeg2_1"); 
//   TH1D *hqiddeg3_1 = (TH1D*)gROOT->FindObject("hqiddeg3_1"); 
   TH1D *hqiddeg1_2 = (TH1D*)gROOT->FindObject("hqiddeg1_2"); 
   TH1D *hqiddeg2_2 = (TH1D*)gROOT->FindObject("hqiddeg2_2"); 
//   TH1D *hqiddeg3_2 = (TH1D*)gROOT->FindObject("hqiddeg3_2"); 

  char filenamesrux[50];
 // sprintf(filenamesrux,"outputtext/run170FeZAQ.dat");
  sprintf(filenamesrux,"outputtext/run170FeSSD2.dat");
  std::ofstream outfilesrux;
  outfilesrux.open(filenamesrux, std::ios::out);


  int n_id_1 = 0;
  double m_1_Mean = 0;
  double m_1[100];
  int id_1[100];
  double mag_1[100];
  double sig_1[100];

 for (int i=1;i<100;i++){
    m_1[i] = hqiddeg1_1->GetBinContent(i);
    id_1[i] = hqiddeg1_1->GetXaxis()->GetBinCenter(i);
    sig_1[i] = hqiddeg1_2->GetBinContent(i);
   
   if (m_1[i] > 0.&& sig_1[i] < 10.){
     n_id_1++;
   }
    
   }


  for(int i=1;i<100;i++){
     if (m_1[i] > 0.&& sig_1[i] < 10.){
       m_1_Mean += m_1[i]/n_id_1;
     }
   }
   

 

  int n_id_2 = 0;
  double m_2_Mean = 0; 
  double m_2[100];
  int id_2[100];
  double mag_2[100];
  double sig_2[100];

 for (int i=1;i<100;i++){
   m_2[i] = hqiddeg2_1->GetBinContent(i);
   id_2[i] = hqiddeg2_1->GetXaxis()->GetBinCenter(i);
   sig_2[i] = hqiddeg1_2->GetBinContent(i);
   if (m_2[i] > 0. && sig_2[i] < 10.){
    n_id_2++;
     }
   }

   for(int i=1;i<100;i++){
       if (m_2[i] > 0.&& sig_2[i] < 10.){
       m_2_Mean += m_2[i]/n_id_2;
      }
    }
 

//  int n_id_3 = 0;
//  double m_3_Mean = 0; 
//  double m_3[100];
//  int id_3[100];
//  double mag_3[100];
//  double sig_3[100];
//
// for (int i=1;i<100;i++){
//   m_3[i] = hqiddeg3_1->GetBinContent(i);
//   id_3[i] = hqiddeg3_1->GetXaxis()->GetBinCenter(i);
//   sig_3[i] = hqiddeg3_2->GetBinContent(i);
//   if (m_3[i] > 0. && sig_3[i] < 10.){
//    n_id_3++;
//     }
//   }
//
//   for(int i=1;i<100;i++){
//       if (m_3[i] > 0.&& sig_3[i] < 10.){
//       m_3_Mean += m_3[i]/n_id_3;
//      }
//    }
 

 double a[100];
 double b[100];

 for (int i=1;i<100;i++){
   a[i] = (m_1_Mean - m_2_Mean) / (m_1[i] - m_2[i]) ;  
   b[i] = m_1_Mean - a[i]*m_1[i];
 }

   outfilesrux << "dE = 227" << "\n";
   outfilesrux << "ID" << "  " << "Charge" << "  " << "Mean" << "  " << "Const" << "  " << "1st" << "\n";
  for(int i=1;i<100;i++){
   outfilesrux << id_1[i] << "  " << m_1[i] << "  " << m_1_Mean << "  " << b[i] << "  " << a[i] << "\n";
  }


   outfilesrux << "dE = 142" << "\n";
   outfilesrux << "ID" << "  " << "Charge" << "  " << "Mean" << "  " << "Const" << "  " << "1st" << "\n";
  for(int i=1;i<100;i++){
   outfilesrux << id_2[i] << "  " << m_2[i] << "  " << m_2_Mean << "  " << b[i] << "  " <<  a[i] << "\n";
   }
 

   outfilesrux.close();
 



}
