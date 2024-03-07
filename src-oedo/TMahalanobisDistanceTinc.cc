#include "TMahalanobisDistanceTinc.h"
#include <TMath.h>
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TSRPPACPlaneData.h>
#include <TSRPPACParameter.h>
#include <TTwoSidedPlasticData.h>
#include <TMWDCTrackingResult.h>
#include "TDssdData.h"
#include <TMahalaData.h>
#include <TTimingChargeData.h>
#include "TDiaTimingData.h"
#include <TClonesArray.h>
#include <TClass.h>
#include <deque>
#include "TParameterArrayLoader.h"
#include <TClass.h>
#include <TParameterObject.h>

#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>


//#include "MassCalibrationMatrix.h"

using art::TMahalanobisDistanceTinc;

using namespace std;

ClassImp(TMahalanobisDistanceTinc)

namespace {
   class LessByTimestamp {
   public:
      bool operator() (const art::TDataObject* data1, const art::TDataObject *data2) {
         return data1->GetTimestamp() < data2->GetTimestamp();
      }
   };
}
  


TMahalanobisDistanceTinc::TMahalanobisDistanceTinc()
//   : fTOFs(NULL), fOutput(NULL)
{

   Register(fDoCheckTimestamp("DoCheckTimestamp","check timestamp if not 0",0));

   RegisterInputCollection("TofName","name of input tof",fTofName,TString("tof"),
                           &fTOFs,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
   RegisterProcessorParameter("S0PPAC","output from x position at dispersive focal plane",fS0PPACName,TString("s0ppac"));
                       //     &fX,TClonesArray::Class_Name(),TSRPPACPlaneData::Class_Name());
   RegisterProcessorParameter("MWDC1","output from mwdc1",fMWDC1Name,TString("mwdc1"));
   RegisterProcessorParameter("MWDC2","output from mwdc2",fMWDC2Name,TString("mwdc2"));
   RegisterProcessorParameter("UnitOrientation","type of unit oriantation",fUnitOri,(Int_t)0);

   RegisterProcessorParameter("ParameterFile","file of theta",fFileName,TString("theta.dat"));
                 //           &fSSD,TClonesArray::Class_Name(),TDssdData::Class_Name());
   
   RegisterOutputCollection("OutputName","name of output mahala",fOutputName,TString("mahala"),
                            &fOutput,TClonesArray::Class_Name(),TMahalaData::Class_Name());
}

TMahalanobisDistanceTinc::~TMahalanobisDistanceTinc()
{
}

TMahalanobisDistanceTinc::TMahalanobisDistanceTinc(const TMahalanobisDistanceTinc& rhs)
{
}

TMahalanobisDistanceTinc& TMahalanobisDistanceTinc::operator=(const TMahalanobisDistanceTinc& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TMahalanobisDistanceTinc::Init(TEventCollection *col)
{

 fS0PPAC = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS0PPACName.Data()));
 if (!fS0PPAC) return;

 fMWDC1 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fMWDC1Name.Data()));
 if (!fMWDC1) return;

 fMWDC2 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fMWDC2Name.Data()));
 if (!fMWDC2) return;


}

void TMahalanobisDistanceTinc::Process()
{
   fOutput->Clear("C");
   
  int Nrow = 10;
  int Ncol = 10;
  int Nopt = 10;
  int k_fact = 10;

  double r_array[Nrow][Ncol];

   std::ifstream fin(fFileName.Data());
   if (!fin.is_open()) {
      Error("Init", "Cannot open file: %s", fFileName.Data());
      return;
   }
  for(int r = 0; r < Nrow; r++) {
	  for(int c = 0; c < Ncol; c++){
	   fin >> r_array[r][c];
	  }
  }
   fin.close();

  TMatrixD Ri(Nrow,Ncol);
  for(int r = 0; r < Nrow; r++){
	  for(int c = 0; c < Ncol; c++){
		  Ri(r,c) = r_array[r][c];
		  }
  }


  TMatrixD tgt(Nopt,1);

         if((*fS0PPAC)->GetEntriesFast() == 0 || (*fTOFs)->GetEntriesFast() == 0 ||  (*fMWDC1)->GetEntriesFast() == 0 || (*fMWDC2)->GetEntriesFast() == 0) return;

	 	 const TSRPPACPlaneData *const s0ppac = static_cast<TSRPPACPlaneData*>((*fS0PPAC)->At(0));
		 if (!s0ppac) return;
         Double_t x0i = s0ppac->GetPosition();

		 const TDiaTimingData *const tof = static_cast<TDiaTimingData*>((*fTOFs)->At(0));
         if(!tof) return;
	     Double_t ti = tof->GetTiming();

		 const TMWDCTrackingResult *const tracku = static_cast<TMWDCTrackingResult*>((*fMWDC1)->At(0));
         if(!tracku) return;

         Bool_t tracku_ok = tracku->IsGood();
		 if(!tracku_ok) return;

	   	 const TMWDCTrackingResult *const trackd = static_cast<TMWDCTrackingResult*>((*fMWDC2)->At(0));
         if(!trackd) return;

         Bool_t trackd_ok = trackd->IsGood();
		 if(!trackd_ok) return;


	     Double_t x3i = tracku->GetX();
	     Double_t a3i = tracku->GetA() * 1000;
	     Double_t y3i = tracku->GetY();
	     Double_t b3i = tracku->GetB() * 1000;
         Double_t t,x3,a3,y3,b3,x0;

	     Double_t x2i = trackd->GetX(-49.5);
	     Double_t a2i = trackd->GetA() * 1000;
	     Double_t y2i = trackd->GetY(-49.5);
	     Double_t b2i = trackd->GetB() * 1000;
         Double_t x2,a2,y2,b2;

  switch (fUnitOri){ 
	  case 0:
	     t = (ti - 2042.) * 0.25;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i * 0.1;
    	 b3 = b3i * 0.1;
    	 x0 = x0i * 0.1; 
         x2 = x2i * 0.1; 
         a2 = a2i * 0.1;
         y2 = y2i * 0.1;
         b2 = b2i * 0.1;
		 break;
	  case 1:
	     t = (ti - 2042.) * 0.125;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i;
    	 b3 = b3i * 0.1 + 1;
    	 x0 = x0i * 0.05; 
         x2 = x2i * 0.1; 
         a2 = a2i * 0.05;
         y2 = y2i * 0.05 - 1;
         b2 = b2i * 0.05 - 0.2;
         break;
	  case 2:
//	     t = (ti - 2042.) * 0.125;  
	     t = (ti - 2042.) * 0.025;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i + 2;
    	 b3 = b3i * 0.05 + 0.5;
    	 x0 = x0i * 0.015;
     	 x2 = x2i * 0.1; 
     	 a2 = a2i * 0.025;
      	 y2 = y2i * 0.05 - 1;
      	 b2 = b2i * 0.05 - 0.2;
         break;
	  case 3:
	     t = (ti - 2042.) * 0.03125;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1 + 0.2;
   	 	 y3 = y3i + 0.6 + 1.2;
    	 b3 = b3i * 0.05 + 0.5;
    	 x0 = x0i * 0.015; 
     	 x2 = x2i * 0.1 + 0.3; 
     	 a2 = a2i * 0.025;
      	 y2 = y2i * 0.15 - 3.;
      	 b2 = b2i * 0.15 - 0.6;
         break;
      case 4:
         t = ((ti - 2042.) * 0.025 + 0.35) * 3;  
         x3 = x3i * 0.1; 
         a3 = a3i * 0.1;
         y3 = y3i + 2;
         b3 = b3i * 0.05 + 0.5;
         x0 = x0i * 0.015; 
         x2 = x2i * 0.1; 
         a2 = a2i * 0.025;
         y2 = y2i * 0.05 - 1;
         b2 = b2i * 0.05 - 0.2;
         break;
	 default:
	     t = (ti - 2042.) * 0.25;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i * 0.1;
    	 b3 = b3i * 0.1;
    	 x0 = x0i * 0.1; 
   	 	 x2 = x2i * 0.1; 
   		 a2 = a2i * 0.1;
   	 	 y2 = y2i * 0.1;
       	 b2 = b2i * 0.1;
         break;
 }


         tgt(0,0) = t;
         tgt(1,0) = x3;
         tgt(2,0) = a3;
         tgt(3,0) = y3;
         tgt(4,0) = b3;
         tgt(5,0) = x0;
         tgt(6,0) = x2;
         tgt(7,0) = a2;
         tgt(8,0) = y2;
         tgt(9,0) = b2;

  TMatrixD tgtt(1,Nopt);
           tgtt.Transpose(tgt);

 TMatrixD D_tmp_t(tgtt,TMatrixD::kMult,Ri);
 TMatrixD D_tmp(D_tmp_t,TMatrixD::kMult,tgt);
 Double_t Md;

  Int_t nrow = D_tmp.GetNrows();
  Int_t ncol = D_tmp.GetNcols();
 if( nrow != 1 || ncol != 1 ){
   cout << "Error! Something wrong in matrix calculation tgt" << endl;
  return;
 }else{
  Double_t D = D_tmp(0,0) / k_fact;
           Md = TMath::Sqrt(D);
 }

       TMahalaData *outData = static_cast<TMahalaData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
       outData->SetMd(Md);
//  
//  }

//
//         outData->SetZ(theta);
//         outData->SetF3X(x3);
//         outData->SetF3A(a3);
//         outData->SetF3Y(y3);
//         outData->SetF3B(b3);
 
}



