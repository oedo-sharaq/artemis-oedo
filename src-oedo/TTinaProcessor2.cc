#include "TTinaProcessor2.h"
#include "TTinaData2.h"

#include <algorithm>
#include <numeric>
#include <functional>

#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>
#include <ITiming.h>

#include <TVector3.h>
#include "TSRPPACPlaneData.h"

using art::TTinaProcessor2;

// for sorting energy deposit keeping ID
struct data_t {
     int ex_pos;
     Double_t val;
     bool operator<( const data_t& right ) const {
       return val == right.val ? ex_pos < right.ex_pos : val > right.val;
     }
};


ClassImp(TTinaProcessor2)

TTinaProcessor2::TTinaProcessor2()
  : fOutput(NULL)
{
   RegisterInputCollection("SiName","name of input collection for Si",
			   fSiName,TString("tinasi"),
			   &fSi,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("CsIName","name of input collection for CsI",
			   fCsIName,TString("tinacsi"),
			   &fCsI,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("TinaTName","name of input collection for TinaT",
			   fTinaTName,TString("tinat"),
			   &fTinaT,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterInputCollection("X1Name","name of input collection for X1",
               fX1Name,TString("x1"),
               &fX1,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("Y1Name","name of input collection for Y1",
               fY1Name,TString("y1"),
               &fY1,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("X2Name","name of input collection for X2",
               fX2Name,TString("x2"),
               &fX2,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());
   RegisterInputCollection("Y2Name","name of input collection for Y2",
               fY2Name,TString("y2"),
               &fY2,TClonesArray::Class_Name(),art::TSRPPACPlaneData::Class_Name());           
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("tina2"),
			    &fOutput,TClonesArray::Class_Name(),art::TTinaData2::Class_Name());
}

TTinaProcessor2::~TTinaProcessor2()
{
}

void TTinaProcessor2::Process()
{
//ch    strip   theta   coverage 
//15	0   	150.6	3.4	
//13	1   	147.1	3.5	
//11	2   	143.6	3.6	
//9   	3   	140 	3.5	
//14	4   	136.5	3.6	
//12	5   	133 	3.5	
//10	6   	129.5	3.4	
//8 	7   	126.1	3.4	
//6 	8   	122.8	3.2	
//4 	9   	119.6	3.2	
//2 	10  	116.5	3.0	
//0 	11  	113.6	2.8	
//7 	12   	110.8	2.7	
//5 	13  	108.1	2.6	
//3 	14  	105.6	2.5	
//1 	15  	103.3	2.2	
   // id-angle conversion tables
  //  static double thetaconv[] =
  //  {
  //    170.8, 169.8, 168.8, 167.8,
  //    166.7, 165.7, 164.6, 163.5,
  //    162.3, 161.2, 160.0, 158.9,
  //    157.7, 156.5, 155.2, 154.0
  //  };
   //static double phiconv[] =
   //{
   //   75.0, 135.0, 195.0, 255.0, 315.0, 375.0
   //};
   static double phiconv[] =
   {
      90.0, 30.0, 330.0, 270.0, 210.0, 150.0
   };
   // angular coverage tables
  //  static double thetacoverage[] =
  //  {
  //    1.0, 1.0, 1.0, 1.0,
  //    1.0, 1.0, 1.1, 1.1,
  //    1.1, 1.1, 1.2, 1.2,
  //    1.2, 1.2, 1.2, 1.2
  //  };
   static double phicoverage[] =
   {
      60.0, 60.0, 60.0, 60.0, 60.0, 60.0
   };

   fOutput->Clear("C");

   // look for si max
   if ((*fSi)->GetEntriesFast() == 0) return;

   //   std::vector<Double_t> siarr(6*16, 0);
      std::vector<data_t> siarr(6*16);

       for(int i = 0 ; i < 96; i++ ){
     siarr[i].ex_pos = i;
     //siarr[i].val = 0.;
     siarr[i].val = -1000.;
   }
       
   for(Int_t i = 0, n = (*fSi)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fSi)->At(i))->GetID();
      if(id < 6*16){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fSi)->At(i));
	 siarr[id].val = ic->GetCharge();
      }
   }
   if (siarr.empty()) return;

  std::vector<Double_t> tinatarr(96, -10000.);
   for(Int_t i = 0, n = (*fTinaT)->GetEntriesFast(); i!=n; ++i) {
     const Int_t id = dynamic_cast<art::TDataObject*>((*fTinaT)->At(i))->GetID();
      if(id < 96){
         const art::ITiming* const it = dynamic_cast<art::ITiming*>((*fTinaT)->At(i));
         tinatarr[id] = it->GetTiming();
      }
   }

   
   //   std::vector<Double_t>::iterator simaxit = std::max_element(siarr.begin(), siarr.end());
   //   Int_t simaxidx = std::distance(siarr.begin(), simaxit);
   std::sort(siarr.begin(), siarr.end());
    

   //if(siarr[0].ex_pos < 0.5) return;
   if(siarr[0].val < 0.) return;

   TTinaData2* out = static_cast<TTinaData2*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   out->SetDeltaE(siarr[0].val);
   out->SetEnergy(siarr[0].val);
   Int_t stripid = siarr[0].ex_pos%16;
   Int_t detid = siarr[0].ex_pos/16;
   out->SetTiming(tinatarr[detid]);

   Double_t colx = 0.;
   Double_t coly = 0.;
   Double_t colz = 0.;

   //collision point at taraget by tracking from fe12
   if((*fX1)->GetEntriesFast() == 0) return;
   if((*fY1)->GetEntriesFast() == 0) return;
   if((*fX2)->GetEntriesFast() == 0) return;
   if((*fY2)->GetEntriesFast() == 0) return;

   Double_t x1 = (dynamic_cast<art::TSRPPACPlaneData*>((*fX1)->At(0)))->GetPosition();
   Double_t y1 = (dynamic_cast<art::TSRPPACPlaneData*>((*fY1)->At(0)))->GetPosition();
   // Double_t z1 = -1962.;
   Double_t z1 = -2017.; // 55 mm
   Double_t x2 = (dynamic_cast<art::TSRPPACPlaneData *>((*fX2)->At(0)))->GetPosition();
   Double_t y2 = (dynamic_cast<art::TSRPPACPlaneData*>((*fY2)->At(0)))->GetPosition();
   // Double_t z2 = -1462;
   Double_t z2 = -1517.; // 55 mm

   colx = (-z1*x2 + z2*x1)/(z2-z1);
   coly = (-z1*(y2-30.) + z2*(y1-30.))/(z2-z1);
   colz = 0.;
   out->SetX(colx);
   out->SetY(coly);

   //hit point at YY1, strip pitch 0.5 mm
   Double_t hitx = 0.;
   Double_t hity = 0.;
   Double_t hitz = 0.;

   const Double_t PI = 4.0*atan(1.0);
   const Double_t a = 50.*PI/180.; // YY1 tilt from beam axis
   const Double_t z_90 = 224.39; // target to YY1 center at r = 90 mm
   //Double_t h_90 = 90*sin(a); // hight from beam axis

   // Double_t r = (stripid+gRandom->Uniform())*5.0+50.;
   // Double_t r = 0;
   // if(stripid==0) r = (1+gRandom->Uniform())*5.0+50.;
   // if(stripid==1) r = (5+gRandom->Uniform())*5.0+50.;
   // if(stripid==2) r = (0+gRandom->Uniform())*5.0+50.;
   // if(stripid==3) r = (4+gRandom->Uniform())*5.0+50.;
   // if(stripid==4) r = (3+gRandom->Uniform())*5.0+50.;
   // if(stripid==5) r = (7+gRandom->Uniform())*5.0+50.;
   // if(stripid==6) r = (2+gRandom->Uniform())*5.0+50.;
   // if(stripid==7) r = (6+gRandom->Uniform())*5.0+50.;
   // if(stripid==8) r = (10+gRandom->Uniform())*5.0+50.;
   // if(stripid==9) r = (14+gRandom->Uniform())*5.0+50.;
   // if(stripid==10) r = (11+gRandom->Uniform())*5.0+50.;
   // if(stripid==11) r = (15+gRandom->Uniform())*5.0+50.;
   // if(stripid==12) r = (8+gRandom->Uniform())*5.0+50.;
   // if(stripid==13) r = (12+gRandom->Uniform())*5.0+50.;
   // if(stripid==14) r = (9+gRandom->Uniform())*5.0+50.;
   // if(stripid==15) r = (13+gRandom->Uniform())*5.0+50.;
   // printf("before id: %d\n",stripid);
   if(stripid==0) stripid=1;
   else if(stripid==1) stripid=5;
   else if(stripid==2) stripid=0;
   else if(stripid==3) stripid=4;
   else if(stripid==4) stripid=3;
   else if(stripid==5) stripid=7;
   else if(stripid==6) stripid=2;
   else if(stripid==7) stripid=6;
   else if(stripid==8) stripid=10;
   else if(stripid==9) stripid=14;
   else if(stripid==10) stripid=11;
   else if(stripid==11) stripid=15;
   else if(stripid==12) stripid=8;
   else if(stripid==13) stripid=12;
   else if(stripid==14) stripid=9;
   else stripid=13;
   Double_t r = (stripid+gRandom->Uniform())*5.0+50.;
   Double_t h = r * sin(a);
   Double_t z = z_90-(r-90)*cos(a);

   Double_t R = sqrt(h*h+z*z); // distance from target center to YY1 hit strip
   Double_t theta = 180-atan(h/z)/PI*180.;
   Double_t phi = phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid];

   hitx = R*sin(theta*PI/180.)*cos(phi*PI/180.);
   hity = R*sin(theta*PI/180.)*sin(phi*PI/180.);
   hitz = R*cos(theta*PI/180.);

   TVector3 vsrc(x2-x1,y2-y1,z2-z1);
   TVector3 vcol(colx,coly,colz);
   TVector3 vhit(hitx,hity,hitz);
   TVector3 v0(0,0,1);

   Double_t scat= vsrc.Angle(vhit-vcol)/PI*180.;
   out->SetTheta(scat);
   out->SetPhi(phi);
   // printf("theta: %f, scat: %f, sfter id: %d\n",theta,scat,stripid);
   
   //Double_t scat0 = v0.Angle(vhit-vcol)/PI*180.;
   //Double_t scat1 = thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid];
   //Double_t Phi; 
   //if(hity-coly>=0){
     //out->SetPhi(atan2(hity-coly,hitx-colx)/PI*180.);
     //Phi = atan2(hity-coly,hitx-colx)/PI*180.;
   //}else{
     //out->SetPhi(atan2(hity-coly,hitx-colx)/PI*180.+360.);
     //Phi = atan2(hity-coly,hitx-colx)/PI*180.+360.;
   //}

   //printf("theta: %f, scat: %f, scat0: %f, scat1: %f, phi: %f, Phi: %f\n",theta,scat,scat0,scat1,phi,Phi);

   //out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   //out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);
   out->SetDeid(siarr[0].ex_pos);

   //   // get rid of ID=40 less than 1 MeV  2021/08/28
   //   if (siarr[0].ex_pos==40&&siarr[0].val<1.0) return;
   
   // look for csi max
   if ((*fCsI)->GetEntriesFast() == 0) return;

   std::vector<Double_t> csiarr(16, 0);
   for(Int_t i = 0, n = (*fCsI)->GetEntriesFast(); i!=n; ++i) {
      const Int_t id = dynamic_cast<art::TDataObject*>((*fCsI)->At(i))->GetID();
      if(id >= 16){
	    const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fCsI)->At(i));
	    csiarr[id-16] = ic->GetCharge();
      }
   }
   if (csiarr.empty()) return;

   std::vector<Double_t>::iterator csimaxit = std::max_element(csiarr.begin(), csiarr.end());
   Int_t csimaxidx = std::distance(csiarr.begin(), csimaxit);

   if(*csimaxit > 4000) return;

   out->SetEnergy(siarr[0].val + *csimaxit);
   out->SetEid(csimaxidx+16);
}
