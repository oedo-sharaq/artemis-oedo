#include "TDaliProcessor.h"
#include "TDaliData.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include <fstream>
#include <sstream>


#include <TMath.h>
#include <TClonesArray.h>
#include <TRandom.h>

#include <TSimpleData.h>
#include <ICharge.h>

using art::TDaliProcessor;

// for sorting energy deposit keeping ID
struct data_t {
     int ex_pos;
     Double_t val;
     bool operator<( const data_t& right ) const {
       return val == right.val ? ex_pos < right.ex_pos : val > right.val;
     }
};

// for reading geometry
std::vector<std::string> split(std::string str, char del) {
  int first = 0;
  int last = str.find_first_of(del);
  std::vector<std::string> result;
  while (first < str.size()) {
    std::string subStr(str, first, last - first);
    result.push_back(subStr);
    first = last + 1;
    last = str.find_first_of(del, first);
    if (last == std::string::npos) {
      last = str.size();
    }
  }
  return result;
}






ClassImp(TDaliProcessor)

TDaliProcessor::TDaliProcessor()
  : fOutput(NULL)
{
   RegisterInputCollection("DaliName","name of input collection for NaI",
			   fDaliName,TString("daliAcal"),
			   &fDali,TClonesArray::Class_Name(),art::ICharge::Class_Name());
   RegisterOutputCollection("OutputName","name of output collection",
			    fOutputName,TString("dali"),
			    &fOutput,TClonesArray::Class_Name(),art::TDaliData::Class_Name());
}

TDaliProcessor::~TDaliProcessor()
{
}



void TDaliProcessor::Process()
{
   // id-angle conversion tables
   static double thetaconv[] =
   {
     9.19, 10.18, 11.19, 12.21,
     13.26, 14.33,15.42, 16.52,
     17.65,18.79,19.95,21.13,
     22.32,23.54,24.77,26.00
   };

   /*
     // angular coverage tables
   static double thetacoverage[] =
   {
     1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.1, 1.1,
     1.1, 1.1, 1.2, 1.2,
     1.2, 1.2, 1.2, 1.2
   };
   */
  
   fOutput->Clear("C");

   // sort dali A
   if ((*fDali)->GetEntriesFast() == 0) return;

   double Addback;
   Addback=0.;
   std::vector<data_t> dali_arr(256);



   for(int i = 0 ; i < 256; i++ ){
     dali_arr[i].ex_pos = i; 
   }

   std::vector<Double_t> daliarr(256, 0);
   for(Int_t i = 0, n = (*fDali)->GetEntriesFast(); i!=n; ++i) {
     const Int_t id = dynamic_cast<art::TDataObject*>((*fDali)->At(i))->GetID();
      if(id < 256){
	 const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fDali)->At(i));
	 daliarr[id] = ic->GetCharge();
	 dali_arr[id].val = ic->GetCharge();
	 Addback = Addback + daliarr[id];
      }
   }
   if (daliarr.empty()) return;

   //std::sort(v.begin(), v.end(), std::greater<int>() );
   //   std::vector<Double_t>::iterator dalimaxit = std::max_element(daliarr.begin(), daliarr.end());
   //   Int_t dalimaxidx = std::distance(daliarr.begin(), dalimaxit);
   std::sort(daliarr.begin(), daliarr.end(), std::greater<Double_t>());
   std::sort(dali_arr.begin(), dali_arr.end());

   //   std::cout<< Addback <<std::endl;

   //   Int_t dalimaxidx = std::distance(daliarr.begin(), dalimaxit);

   //   if(*dalimaxit < 0.5) return;
   //   if(*dalimaxit < 0.1) return;

   TDaliData* out = static_cast<TDaliData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
//   out->SetEnergy1(daliarr[0]);
//   out->SetEnergy2(daliarr[1]);
   out->SetEnergy1(dali_arr[0].val);
   out->SetEnergy2(dali_arr[1].val);
   out->SetPos1(dali_arr[0].ex_pos);
   out->SetPos2(dali_arr[1].ex_pos);
   //   Int_t stripid = dalimaxidx%16;
   //   Int_t detid = dalimaxidx/16;
   //   out->SetTheta(thetaconv[stripid]+(gRandom->Uniform()-0.5)*thetacoverage[stripid]);
   out->SetTheta(thetaconv[0]);
   out->SetTotalE(Addback);
}
