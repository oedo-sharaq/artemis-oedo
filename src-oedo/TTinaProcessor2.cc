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
   static double thetaconv[] =
   {
     170.8, 169.8, 168.8, 167.8,
     166.7, 165.7, 164.6, 163.5,
     162.3, 161.2, 160.0, 158.9,
     157.7, 156.5, 154.2, 154.0
   };
   //static double phiconv[] =
   //{
   //   75.0, 135.0, 195.0, 255.0, 315.0, 375.0
   //};
   static double phiconv[] =
   {
      90.0, 30.0, 330.0, 270.0, 210.0, 150.0
   };
   // angular coverage tables
   static double thetacoverage[] =
   {
     1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.1, 1.1,
     1.1, 1.1, 1.2, 1.2,
     1.2, 1.2, 1.2, 1.2
   };
   //static double phicoverage[] =
   //{
   //   60.0, 60.0, 60.0, 60.0, 60.0, 60.0
   //};
   static double phicoverage[] =
   {
      42.0, 42.0, 42.0, 42.0, 42.0, 42.0
   };

   fOutput->Clear("C");

   // look for si max
   if ((*fSi)->GetEntriesFast() == 0) return;

   //   std::vector<Double_t> siarr(6*16, 0);
      std::vector<data_t> siarr(6*16);

       for(int i = 0 ; i < 96; i++ ){
     siarr[i].ex_pos = i;
     siarr[i].val = 0.;
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
    

   if(siarr[0].ex_pos < 0.5) return;

   TTinaData2* out = static_cast<TTinaData2*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
   out->SetDeltaE(siarr[0].val);
   out->SetEnergy(siarr[0].val);
   Int_t stripid = siarr[0].ex_pos%16;
   Int_t detid = siarr[0].ex_pos/16;
   out->SetTiming(tinatarr[detid]);
   out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   out->SetPhi(phiconv[detid]+(gRandom->Uniform()-0.5)*phicoverage[detid]);
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
