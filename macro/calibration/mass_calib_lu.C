#include <TMatrix.h>
#include <TMatrixD.h>
#include <TMath.h>
#include <TROOT.h>
#include <TTree.h>
#include <TDecompLU.h>
#include <TDecompChol.h>
#include <TString.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


void mass_calib_lu(){

  Int_t Nrun = 1500;  //the number of runs
  Int_t Nref =   26;  // the number of species for reference
  Int_t Nevt =  Nref * Nrun;  // the number of events
  Int_t Nprm =   56;  //the number of parameters

  
 TTree *tree = dynamic_cast<TTree*>(gDirectory->Get("tree"));
 if(!tree){
	 printf("No tree named 'tree' exists\n");
	 return;
 }

 TClonesArray *mass = NULL;
 TClonesArray *tracku = NULL;
 TClonesArray *s0 = NULL;
 tree->SetBranchAddress("mass",&mass);
 tree->SetBranchAddress("f3",&tracku);
 tree->SetBranchAddress("sr0_xcw",&s0);

 TMatrixD A(Nevt,Nprm):
 TMatrixD At = A.T();
 TVectorD b(Nevt,1);


// Load a input file
 vector<string> Tag;
 vector<Double_t> Tag, Ref_m, Z_low, Z_up, Aq_low, Aq_up;

 ifstream fin("/home/sh13/art_analysis/user/sh13/prm/mass/input.dat");
 if (fin.fail()){
	 cout << "Error; inputfile" << "" << "is not found." << endl << endl;
	 return;
  }

  int i = 0;
  string come;
  while(getline(fin,come)){
	  if(come[0]=='#'){
		  continue;
	  }else{
	    fin >> Tag[i] >> Ref_m[i] >> Z_low[i]  >> Z_up[i] >> Aq_low[i] >> Aq_up[i];
		i++;
		}
  }
 fin.close();

   if(i != Nref){
	 cout << "The nuber of events is" << i << "Not equal to" << Nref << endl;
 }
 

// Fill date  
for (int iref = 0; iref < Nref; iref++){
  for (int irun = 0; irun < Nrun; irun++){
    Int_t nData = tree->GetEntries();
    vector<Int_t> irandm;
    int tmp = 0;
	int n_tmp = 0;

  for(int i = 0, i < nData; i++){
   if(Z_low[iref] < mass->GetZ(tmp) && mass->GetZ(tmp) < Z_up[iref] 
  	 && Aq_low[iref] < mass->GetAq(tmp) && mass->GetAq(tmp) < Aq_up[iref])
   {
     irandm = tmp;
	 tmp++;
   }else {
	   continue;
   }
    n_tmp++;
   }

     int j = gRandom->Uniform(0,n_tmp)
     tree->GetEntry(j);
     
     Double_t t = mass->GetToF(j);
     Double_t x3 = tracku->GetX(j);
     Double_t a3 = tracku->GetA(j) * 1000.;
     Double_t y3 = tracku->GetY(j);
     Double_t b3 = tracku->GetB(j) * 1000.;
     Double_t x0 = s0->GetPosition(j);
  
     int ievt = 0;
  
     A[ievt][0] = 1
     A[ievt][1] = x3
     A[ievt][2] = a3
     A[ievt][3] = y3
     A[ievt][4] = b3
     A[ievt][5] = x0
     A[ievt][6] = x3 * a3
     A[ievt][7] = x3 * y3
     A[ievt][8] = x3 * b3
     A[ievt][9] = x3 * x0
     A[ievt][10] = a3 * y3
     A[ievt][11] = a3 * b3
     A[ievt][12] = a3 * x0
     A[ievt][13] = y3 * b3
     A[ievt][14] = y3 * x0
     A[ievt][15] = b3 * x0
     A[ievt][16] = x3 * x3
     A[ievt][17] = a3 * a3
     A[ievt][18] = y3 * y3
     A[ievt][19] = b3 * b3
     A[ievt][20] = x0 * x0
     A[ievt][21] = x3 * a3 * y3
     A[ievt][22] = x3 * a3 * b3
     A[ievt][23] = x3 * a3 * x0
     A[ievt][24] = x3 * y3 * b3
     A[ievt][25] = x3 * y3 * x0
     A[ievt][26] = x3 * b3 * x0
     A[ievt][27] = a3 * y3 * b3
     A[ievt][28] = a3 * y3 * x0
     A[ievt][29] = a3 * b3 * x0
     A[ievt][30] = y3 * b3 * x0
     A[ievt][31] = x3 * x3 * a3
     A[ievt][32] = x3 * x3 * y3
     A[ievt][33] = x3 * x3 * b3
     A[ievt][34] = x3 * x3 * x0
     A[ievt][35] = a3 * a3 * x3
     A[ievt][36] = a3 * a3 * y3
     A[ievt][37] = a3 * a3 * b3
     A[ievt][38] = a3 * a3 * x0
     A[ievt][39] = y3 * y3 * x3
     A[ievt][40] = y3 * y3 * a3
     A[ievt][41] = y3 * y3 * b3
     A[ievt][42] = y3 * y3 * x0
     A[ievt][43] = b3 * b3 * x3
     A[ievt][44] = b3 * b3 * a3
     A[ievt][45] = b3 * b3 * y3
     A[ievt][46] = b3 * b3 * x0
     A[ievt][47] = x0 * x0 * x3
     A[ievt][48] = x0 * x0 * a3
     A[ievt][49] = x0 * x0 * y3
     A[ievt][50] = x0 * x0 * b3
     A[ievt][51] = x3 * x3 * x3
     A[ievt][52] = a3 * a3 * a3
     A[ievt][53] = y3 * y3 * y3
     A[ievt][54] = b3 * b3 * b3
     A[ievt][55] = x0 * x0 * x0
  
     b[ievt][0] = Ref_m[iref];
  
     ievt++:
       }else{
      	 continue;
       }
 }

}
 if(ievt != Nevt){
	 cout << "The nuber of events is" << ievt << "Not equal to" << Nevt << endl;
 }
 

// Set Matrix
//
  TMatrixD Cov();
  Cov.Mult(At,A);

  TMatrixD Atb();
  Atb.Mult(At,b);

// Solve Normal Equation

  TDecompLU lu(Cov);
  Bool_t ok;

  TVectorD Theta = lu.Solve(Atb,ok);


// Save the results of LU decompose
  Double_t d1, d2;
  lu.Det(d1,d2);
  cout << "cond: " << lu.Condition() << endl;
  cout << "det: "  << d1*TMath::Power(2, d2) << endl;
  cout << "tol: " << lu.GetTol() << endl;
  Theta.Print();

   char foutname[50];
   sprintf(foutname, "output/mass/lu_out.dat");
   std::oftream fout;
   fout.open(foutname, std::ios::out);
   fout << "cond: " << lu.Condition() << endl;
   fcout << "det: "  << d1*TMath::Power(2, d2) << endl;
   fout << "tol: " << lu.GetTol() << endl;
   fout << Theta.Print() << endl;

   fout.close();

// AoQ cor
   vector<Double_t> Aq_cor;
    



// Output

 TH1D *41Ca = new TH1D("41Ca", "41Ca", , ); 
 TH1D *42Ca = new TH1D("42Ca", "42Ca", , );
 TH1D *43Ca = new TH1D("43Ca", "43Ca", , );
 TH1D *44Ca = new TH1D("44Ca", "44Ca", , );
                                    
 TH1D *44Sc = new TH1D("44Sc", "44Sc", , );
 TH1D *44Sc = new TH1D("44Sc", "44Sc", , );
 TH1D *44Sc = new TH1D("44Sc", "44Sc", , );
 TH1D *44Sc = new TH1D("44Sc", "44Sc", , );
                                    
 TH1D *44Ti = new TH1D("44Ti", "44Ti", , );
 TH1D *44Ti = new TH1D("44Ti", "44Ti", , );
 TH1D *44Ti = new TH1D("44Ti", "44Ti", , );
 TH1D *44Ti = new TH1D("44Ti", "44Ti", , );
                                    
 TH1D *44V  = new TH1D("44V ", "44V ", , );
 TH1D *44V  = new TH1D("44V ", "44V ", , );
 TH1D *44V  = new TH1D("44V ", "44V ", , );
 TH1D *44V  = new TH1D("44V ", "44V ", , );
                                    
 TH1D *44Cr = new TH1D("44Cr", "44Cr", , );
 TH1D *44Cr = new TH1D("44Cr", "44Cr", , );
 TH1D *44Cr = new TH1D("44Cr", "44Cr", , );
 TH1D *44Cr = new TH1D("44Cr", "44Cr", , );
                                    
 TH1D *44Mn = new TH1D("44Mn", "44Mn", , );
 TH1D *44Mn = new TH1D("44Mn", "44Mn", , );
 TH1D *44Mn = new TH1D("44Mn", "44Mn", , );
 TH1D *44Mn = new TH1D("44Mn", "44Mn", , );
                                    
 TH1D *44Fe = new TH1D("44Fe", "44Fe", , );
 TH1D *44Fe = new TH1D("44Fe", "44Fe", , );
 TH1D *44Fe = new TH1D("44Fe", "44Fe", , );
 TH1D *44Fe = new TH1D("44Fe", "44Fe", , );
                                    
 TH1D *44Co = new TH1D("44Co", "44Co", , );
 TH1D *44Co = new TH1D("44Co", "44Co", , );
 TH1D *44Co = new TH1D("44Co", "44Co", , );
 TH1D *44Co = new TH1D("44Co", "44Co", , );
                                    
 TH1D *44Ni = new TH1D("44Ni", "44Ni", , );
 TH1D *44Ni = new TH1D("44Ni", "44Ni", , );
 TH1D *44Ni = new TH1D("44Ni", "44Ni", , );
 TH1D *44Ni = new TH1D("44Ni", "44Ni", , );














}






