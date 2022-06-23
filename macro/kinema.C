/* $Id:$ */
/**
 * @file   kinema.C
 * @date   Created : Oct 07, 2012 18:07:46 JST
 *   Last Modified : 
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *  
 *  
 *    Copyright (C)2012
 */

//using namespace TArtSystemOfUnit;
void kinema(Int_t a1, Int_t z1,
            Int_t a2, Int_t z2,
            Int_t a3, Int_t z3,
            Double_t energyPerNucleon,
            Double_t exmin,Double_t exmax, Double_t estep
   )
{
   TCatTwoBodyKinematics *relkin = new TCatTwoBodyKinematics(a1,z1,a2,z2,a3,z3);
//   relkin->Print();
   relkin->SetIncidentEnergy(energyPerNucleon);
   Int_t nEx = (exmax-exmin)/estep + 1;
   Int_t nQ = 201;
   Double_t QStep = 0.1;
   Int_t nQLine = (nQ-1)*QStep + 1;
   TGraph **grEx = new TGraph*[nEx];
   TGraph **grTh = new TGraph*[nQLine];
   for (Int_t iq = 0; iq != nQLine; iq++) {
      grTh[iq] = new TGraph(nEx);
   }
   for (Int_t iEx = 0; iEx!=nEx; iEx++) {
      Double_t ex = iEx * estep + exmin;
      ex = (ex>exmax)?exmax:ex;
//      printf("ex = %f\n",ex);
      relkin->SetExcitationEnergy(ex);
//   relkin->Print();
      const TArtParticle *recoil = relkin->GetParticle(3);
      grEx[iEx] = new TGraph(nQ);
      for (Int_t iq=0; iq != nQ; iq++) {
         Double_t theta = iq*QStep;
         relkin->SetTheta(theta*(TMath::Pi()/ 180.));
//   relkin->Print();
         grEx[iEx]->SetPoint(iq,recoil->Theta()/(TMath::Pi()/ 180.),recoil->TKE());
//         printf("%f %f\n",recoil->Theta(), recoil->TKE());
         if (theta == int(theta)) {
            grTh[int(theta)]->SetPoint(iEx,recoil->Theta()/(TMath::Pi()/ 180.),recoil->TKE());
         }
		 if(ex==0&&iq*QStep==5){
			 cout << theta <<" "<< recoil->Theta()/(TMath::Pi()/ 180.) << endl;
			 relkin->Print();
		 }
      }
   }
   if (gDirectory->Get("h")) { delete gDirectory->Get("h") ;}
   TH2F *h2 = new TH2F("h","",180,0.,180.,100,0.,100.);
   h2->SetXTitle("#theta_{lab} (deg)");
   h2->SetYTitle("TKE_{lab} (MeV)");
   h2->GetXaxis()->SetLabelFont(22);
   h2->GetXaxis()->SetTitleFont(22);
   h2->GetYaxis()->SetLabelFont(22);
   h2->GetYaxis()->SetTitleFont(22);

   h2->SetTitle(TString::Format("A=%d,Z=%d+A=%d,Z=%d => A=%d,Z=%d, Ex = %4.1f - %4.1f MeV, Kin = %6.1f MeV/u",
                                a1,z1,a2,z2,a3,z3,exmin,exmax,energyPerNucleon));
   h2->SetStats(kFALSE);
   h2->Draw();
   for (Int_t iEx = 0; iEx < nEx; iEx++) {
      Double_t ex = iEx * estep + exmin;
      ex = (ex>exmax)?exmax:ex;
      if (int(ex/10.) == int(ex)/10.) {
         printf("%d %f\n",int(ex/10.), int(ex)/10.);
         grEx[iEx]->SetLineColor(kBlue);
         grEx[iEx]->SetLineWidth(2);
      }
      grEx[iEx]->Draw("C");
   }
   for (Int_t iq=0; iq<nQLine; iq++) {
      if ((iq%5)==0) {
         grTh[iq]->SetLineColor(kRed);
         grTh[iq]->SetLineWidth(2);
      }
      grTh[iq]->Draw("C");
   }
}   

