
#include "TMassCalibrationConverter.h"
#include <TMath.h>
#include <TMatrix.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <TSRPPACPlaneData.h>
#include <TSRPPACParameter.h>
#include <TTwoSidedPlasticData.h>
#include <TMWDCTrackingResult.h>
#include "TDssdData.h"
#include <TMassData.h>
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

using art::TMassCalibrationConverter;

using namespace std;

ClassImp(TMassCalibrationConverter)

namespace {
   class LessByTimestamp {
   public:
      bool operator() (const art::TDataObject* data1, const art::TDataObject *data2) {
         return data1->GetTimestamp() < data2->GetTimestamp();
      }
   };
}
  


TMassCalibrationConverter::TMassCalibrationConverter()
//   : fTOFs(NULL), fOutput(NULL)
{

   Register(fDoCheckTimestamp("DoCheckTimestamp","check timestamp if not 0",0));

   RegisterInputCollection("TofName","name of input tof",fTofName,TString("tof"),
                           &fTOFs,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
   RegisterProcessorParameter("S0PPAC","output from x position at dispersive focal plane",fS0PPACName,TString("s0ppac"));
                       //     &fX,TClonesArray::Class_Name(),TSRPPACPlaneData::Class_Name());
   RegisterProcessorParameter("MWDC1","output from mwdc1",fMWDC1Name,TString("mwdc1"));
   RegisterProcessorParameter("MWDC2","output from mwdc2",fMWDC2Name,TString("mwdc2"));
   RegisterProcessorParameter("S0PPACY","output from y position at dispersive focal plane",fS0PPACYName,TString("s0ppacy"));
   RegisterProcessorParameter("UsetwoMWDCs","use both F3 and S2 MWDCs",fUsetwoMWDCs,0);
   RegisterProcessorParameter("UseS0Y","use y information at S0",fUseS0Y,0);
   RegisterProcessorParameter("CalibOrder","order of matrix",fOrder,(Int_t)3);
   RegisterProcessorParameter("UnitOrientation","type of unit oriantation",fUnitOri,(Int_t)0);

   RegisterProcessorParameter("ParameterFile","file of theta",fFileName,TString("theta.dat"));
                 //           &fSSD,TClonesArray::Class_Name(),TDssdData::Class_Name());
   
   RegisterOutputCollection("OutputName","name of output pid",fOutputName,TString("mass_cor"),
                            &fOutput,TClonesArray::Class_Name(),TMassData::Class_Name());
}

TMassCalibrationConverter::~TMassCalibrationConverter()
{
}

TMassCalibrationConverter::TMassCalibrationConverter(const TMassCalibrationConverter& rhs)
{
}

TMassCalibrationConverter& TMassCalibrationConverter::operator=(const TMassCalibrationConverter& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TMassCalibrationConverter::Init(TEventCollection *col)
{

 fS0PPAC = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS0PPACName.Data()));
 if (!fS0PPAC) return;

 fMWDC1 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fMWDC1Name.Data()));
 if (!fMWDC1) return;

 fMWDC2 = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fMWDC2Name.Data()));
 if (!fMWDC2) return;

 fS0PPACY = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS0PPACYName.Data()));
 if (!fS0PPACY) return;


}

void TMassCalibrationConverter::Process()
{
   fOutput->Clear("C");
   
  double Theta_tmp; 
  std::vector<double> Theta; 
  std::string buff;

   std::ifstream fin(fFileName.Data());
   if (!fin.is_open()) {
      Error("Init", "Cannot open file: %s", fFileName.Data());
      return;
   }
// TString buff;
//   while(buff.ReadLine(fin)) 
 // while(!fin.eof()) {
   while(getline(fin,buff)) {
	   stringstream ss(buff);
//	   fin >> buff;
	   ss >> Theta_tmp;
//       Theta_tmp = std::stod(buff);
       Theta.push_back(Theta_tmp);
	  }
   fin.close();

   Int_t Ntheta = Theta.size();
   Int_t Nprm;
	if(!fUsetwoMWDCs){
     Nprm = 168;
   }else if(!fUseS0Y){
	 Nprm = 1001;
   }else{
     Nprm = 1365;
   }

  if (Ntheta != Nprm) {
      Error("Init", "Number of Parameters do not match");
	  return;
}

    TVectorD Rd(Nprm);

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

	     Double_t x3i = tracku->GetX();
	     Double_t a3i = tracku->GetA() * 1000;
	     Double_t y3i = tracku->GetY();
	     Double_t b3i = tracku->GetB() * 1000;
         Double_t t,x3,a3,y3,b3,x0;
  switch (fUnitOri){ 
	  case 0:
	     t = (ti - 2042.) * 0.25;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i * 0.1;
    	 b3 = b3i * 0.1;
    	 x0 = x0i * 0.1; 
		 break;
	  case 1:
	     t = (ti - 2042.) * 0.125;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i;
    	 b3 = b3i * 0.1 + 1;
    	 x0 = x0i * 0.05; 
         break;
	  case 2:
//	     t = (ti - 2042.) * 0.125;  
	     t = (ti - 2042.) * 0.025;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i + 2;
    	 b3 = b3i * 0.05 + 0.5;
    	 x0 = x0i * 0.015; 
         break;
	  case 3:
	     t = (ti - 2042.) * 0.03125;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1 + 0.2;
   	 	 y3 = y3i + 0.6 + 1.2;
    	 b3 = b3i * 0.05 + 0.5;
    	 x0 = x0i * 0.015; 
         break;
      case 4:
         t = ((ti - 2042.) * 0.025 + 0.35) * 3;  
         x3 = x3i * 0.1; 
         a3 = a3i * 0.1;
         y3 = y3i + 2;
         b3 = b3i * 0.05 + 0.5;
         x0 = x0i * 0.015; 
         break;
	 default:
	     t = (ti - 2042.) * 0.25;  
   		 x3 = x3i * 0.1; 
   		 a3 = a3i * 0.1;
   	 	 y3 = y3i * 0.1;
    	 b3 = b3i * 0.1;
    	 x0 = x0i * 0.1; 
         break;
}
		Double_t sum = 0;

	if(!fUsetwoMWDCs){
		if(fOrder == 3){
            Rd(0) = 1.; 
            Rd(1) = x3;
            Rd(2) = a3;
            Rd(3) = y3;
            Rd(4) = b3;
            Rd(5) = x0;
            Rd(6) = x3 * a3;
            Rd(7) = x3 * y3;
            Rd(8) = x3 * b3;
            Rd(9) = x3 * x0;
            Rd(10) = a3 * y3; 
            Rd(11) = a3 * b3; 
            Rd(12) = a3 * x0; 
            Rd(13) = y3 * b3; 
            Rd(14) = y3 * x0; 
            Rd(15) = b3 * x0; 
            Rd(16) = x3 * x3; 
            Rd(17) = a3 * a3; 
            Rd(18) = y3 * y3; 
            Rd(19) = b3 * b3; 
            Rd(20) = x0 * x0; 
            Rd(21) = x3 * a3 * y3; 
            Rd(22) = x3 * a3 * b3; 
            Rd(23) = x3 * a3 * x0; 
            Rd(24) = x3 * y3 * b3; 
            Rd(25) = x3 * y3 * x0; 
            Rd(26) = x3 * b3 * x0; 
            Rd(27) = a3 * y3 * b3; 
            Rd(28) = a3 * y3 * x0; 
            Rd(29) = a3 * b3 * x0; 
            Rd(30) = y3 * b3 * x0; 
            Rd(31) = x3 * x3 * a3; 
            Rd(32) = x3 * x3 * y3; 
            Rd(33) = x3 * x3 * b3; 
            Rd(34) = x3 * x3 * x0; 
            Rd(35) = a3 * a3 * x3; 
            Rd(36) = a3 * a3 * y3; 
            Rd(37) = a3 * a3 * b3; 
            Rd(38) = a3 * a3 * x0; 
            Rd(39) = y3 * y3 * x3; 
            Rd(40) = y3 * y3 * a3; 
            Rd(41) = y3 * y3 * b3; 
            Rd(42) = y3 * y3 * x0; 
            Rd(43) = b3 * b3 * x3; 
            Rd(44) = b3 * b3 * a3; 
            Rd(45) = b3 * b3 * y3; 
            Rd(46) = b3 * b3 * x0; 
            Rd(47) = x0 * x0 * x3; 
            Rd(48) = x0 * x0 * a3; 
            Rd(49) = x0 * x0 * y3; 
            Rd(50) = x0 * x0 * b3; 
            Rd(51) = x3 * x3 * x3; 
            Rd(52) = a3 * a3 * a3; 
            Rd(53) = y3 * y3 * y3; 
            Rd(54) = b3 * b3 * b3; 
            Rd(55) = x0 * x0 * x0; 
       
            Rd(56) = 1. * t; 
            Rd(57) = x3 * t;
            Rd(58) = a3 * t;
            Rd(59) = y3 * t;
            Rd(60) = b3 * t;
            Rd(61) = x0 * t;
            Rd(62) = x3 * a3 * t;
            Rd(63) = x3 * y3 * t;
            Rd(64) = x3 * b3 * t;
            Rd(65) = x3 * x0 * t;
            Rd(66) = a3 * y3 * t; 
            Rd(67) = a3 * b3 * t; 
            Rd(68) = a3 * x0 * t; 
            Rd(69) = y3 * b3 * t; 
            Rd(70) = y3 * x0 * t; 
            Rd(71) = b3 * x0 * t; 
            Rd(72) = x3 * x3 * t; 
            Rd(73) = a3 * a3 * t; 
            Rd(74) = y3 * y3 * t; 
            Rd(75) = b3 * b3 * t; 
            Rd(76) = x0 * x0 * t; 
            Rd(77) = x3 * a3 * y3 * t; 
            Rd(78) = x3 * a3 * b3 * t; 
            Rd(79) = x3 * a3 * x0 * t; 
            Rd(80) = x3 * y3 * b3 * t; 
            Rd(81) = x3 * y3 * x0 * t; 
            Rd(82) = x3 * b3 * x0 * t; 
            Rd(83) = a3 * y3 * b3 * t; 
            Rd(84) = a3 * y3 * x0 * t; 
            Rd(85) = a3 * b3 * x0 * t; 
            Rd(86) = y3 * b3 * x0 * t; 
            Rd(87) = x3 * x3 * a3 * t; 
            Rd(88) = x3 * x3 * y3 * t; 
            Rd(89) = x3 * x3 * b3 * t; 
            Rd(90) = x3 * x3 * x0 * t; 
            Rd(91) = a3 * a3 * x3 * t; 
            Rd(92) = a3 * a3 * y3 * t; 
            Rd(93) = a3 * a3 * b3 * t; 
            Rd(94) = a3 * a3 * x0 * t; 
            Rd(95) = y3 * y3 * x3 * t; 
            Rd(96) = y3 * y3 * a3 * t; 
            Rd(97) = y3 * y3 * b3 * t; 
            Rd(98) = y3 * y3 * x0 * t; 
            Rd(99) = b3 * b3 * x3 * t; 
            Rd(100) = b3 * b3 * a3 * t; 
            Rd(101) = b3 * b3 * y3 * t; 
            Rd(102) = b3 * b3 * x0 * t; 
            Rd(103) = x0 * x0 * x3 * t; 
            Rd(104) = x0 * x0 * a3 * t; 
            Rd(105) = x0 * x0 * y3 * t; 
            Rd(106) = x0 * x0 * b3 * t; 
            Rd(107) = x3 * x3 * x3 * t; 
            Rd(108) = a3 * a3 * a3 * t; 
            Rd(109) = y3 * y3 * y3 * t; 
            Rd(110) = b3 * b3 * b3 * t; 
            Rd(111) = x0 * x0 * x0 * t; 
       
            Rd(112) = 1. * t * t; 
            Rd(113) = x3 * t * t;
            Rd(114) = a3 * t * t;
            Rd(115) = y3 * t * t;
            Rd(116) = b3 * t * t;
            Rd(117) = x0 * t * t;
            Rd(118) = x3 * a3 * t * t;
            Rd(119) = x3 * y3 * t * t;
            Rd(120) = x3 * b3 * t * t;
            Rd(121) = x3 * x0 * t * t;
            Rd(122) = a3 * y3 * t * t; 
            Rd(123) = a3 * b3 * t * t; 
            Rd(124) = a3 * x0 * t * t; 
            Rd(125) = y3 * b3 * t * t; 
            Rd(126) = y3 * x0 * t * t; 
            Rd(127) = b3 * x0 * t * t; 
            Rd(128) = x3 * x3 * t * t; 
            Rd(129) = a3 * a3 * t * t; 
            Rd(130) = y3 * y3 * t * t; 
            Rd(131) = b3 * b3 * t * t; 
            Rd(132) = x0 * x0 * t * t; 
            Rd(133) = x3 * a3 * y3 * t * t; 
            Rd(134) = x3 * a3 * b3 * t * t; 
            Rd(135) = x3 * a3 * x0 * t * t; 
            Rd(136) = x3 * y3 * b3 * t * t; 
            Rd(137) = x3 * y3 * x0 * t * t; 
            Rd(138) = x3 * b3 * x0 * t * t; 
            Rd(139) = a3 * y3 * b3 * t * t; 
            Rd(140) = a3 * y3 * x0 * t * t; 
            Rd(141) = a3 * b3 * x0 * t * t; 
            Rd(142) = y3 * b3 * x0 * t * t; 
            Rd(143) = x3 * x3 * a3 * t * t; 
            Rd(144) = x3 * x3 * y3 * t * t; 
            Rd(145) = x3 * x3 * b3 * t * t; 
            Rd(146) = x3 * x3 * x0 * t * t; 
            Rd(147) = a3 * a3 * x3 * t * t; 
            Rd(148) = a3 * a3 * y3 * t * t; 
            Rd(149) = a3 * a3 * b3 * t * t; 
            Rd(150) = a3 * a3 * x0 * t * t; 
            Rd(151) = y3 * y3 * x3 * t * t; 
            Rd(152) = y3 * y3 * a3 * t * t; 
            Rd(153) = y3 * y3 * b3 * t * t; 
            Rd(154) = y3 * y3 * x0 * t * t; 
            Rd(155) = b3 * b3 * x3 * t * t; 
            Rd(156) = b3 * b3 * a3 * t * t; 
            Rd(157) = b3 * b3 * y3 * t * t; 
            Rd(158) = b3 * b3 * x0 * t * t; 
            Rd(159) = x0 * x0 * x3 * t * t; 
            Rd(160) = x0 * x0 * a3 * t * t; 
            Rd(161) = x0 * x0 * y3 * t * t; 
            Rd(162) = x0 * x0 * b3 * t * t; 
            Rd(163) = x3 * x3 * x3 * t * t; 
            Rd(164) = a3 * a3 * a3 * t * t; 
            Rd(165) = y3 * y3 * y3 * t * t; 
            Rd(166) = b3 * b3 * b3 * t * t; 
            Rd(167) = x0 * x0 * x0 * t * t; 
 }
 }else{
	   	 const TMWDCTrackingResult *const trackd = static_cast<TMWDCTrackingResult*>((*fMWDC2)->At(0));
         if(!trackd) return;

         Bool_t trackd_ok = trackd->IsGood();
		 if(!trackd_ok) return;

	     Double_t x2i = trackd->GetX(-49.5);
	     Double_t a2i = trackd->GetA() * 1000;
	     Double_t y2i = trackd->GetY(-49.5);
	     Double_t b2i = trackd->GetB() * 1000;
         Double_t x2,a2,y2,b2;
     switch (fUnitOri){
    	 case 0:
    	 	 x2 = x2i * 0.1; 
       		 a2 = a2i * 0.1;
       	 	 y2 = y2i * 0.1;
        	 b2 = b2i * 0.1;
    		 break;
    	 case 1:
    	 	 x2 = x2i * 0.1; 
       		 a2 = a2i * 0.05;
       	 	 y2 = y2i * 0.05 - 1;
        	 b2 = b2i * 0.05 - 0.2;
    		 break;
    	 case 2:
    	 	 x2 = x2i * 0.1; 
       		 a2 = a2i * 0.025;
       	 	 y2 = y2i * 0.05 - 1;
        	 b2 = b2i * 0.05 - 0.2;
             break;
		  case 3:
        	 x2 = x2i * 0.1 + 0.3; 
       		 a2 = a2i * 0.025;
       	 	 y2 = y2i * 0.15 - 3.;
        	 b2 = b2i * 0.15 - 0.6;
             break;
		  case 4:
            x2 = x2i * 0.1; 
            a2 = a2i * 0.025;
            y2 = y2i * 0.05 - 1;
            b2 = b2i * 0.05 - 0.2;
             break;
    	 default:
    	 	 x2 = x2i * 0.1; 
       		 a2 = a2i * 0.1;
    	 	 y2 = y2i * 0.1;
        	 b2 = b2i * 0.1;
             break;
      }

		if(fOrder == 4 && !fUseS0Y){
    	     Rd(0) = 1.; 
// 1st order
             Rd(1)  = t;
             Rd(2)  = x3;
             Rd(3)  = a3;
             Rd(4)  = y3;
             Rd(5)  = b3;
             Rd(6)  = x0;
             Rd(7)  = x2;
             Rd(8)  = a2;
             Rd(9)  = y2;
             Rd(10) = b2;
// 2nd order       
             Rd(11) = t * t;
             Rd(12) = x3 * x3;
             Rd(13) = a3 * a3;
             Rd(14) = y3 * y3;
             Rd(15) = b3 * b3;
             Rd(16) = x0 * x0;
             Rd(17) = x2 * x2;
             Rd(18) = a2 * a2;
             Rd(19) = y2 * y2;
             Rd(20) = b2 * b2;

             Rd(21) = t * x3;
             Rd(22) = t * a3;
             Rd(23) = t * y3;
             Rd(24) = t * b3;
             Rd(25) = t * x0;
             Rd(26) = t * x2;
             Rd(27) = t * a2;
             Rd(28) = t * y2;
             Rd(29) = t * b2;

             Rd(30) = x3 * a3;
             Rd(31) = x3 * y3;
             Rd(32) = x3 * b3;
             Rd(33) = x3 * x0;
             Rd(34) = x3 * x2;
             Rd(35) = x3 * a2;
             Rd(36) = x3 * y2;
             Rd(37) = x3 * b2;

             Rd(38) = a3 * y3;
             Rd(39) = a3 * b3;
             Rd(40) = a3 * x0;
             Rd(41) = a3 * x2;
             Rd(42) = a3 * a2;
             Rd(43) = a3 * y2;
             Rd(44) = a3 * b2;

             Rd(45) = y3 * b3;
             Rd(46) = y3 * x0;
             Rd(47) = y3 * x2;
             Rd(48) = y3 * a2;
             Rd(49) = y3 * y2;
             Rd(50) = y3 * b2;

             Rd(51) = b3 * x0;
             Rd(52) = b3 * x2;
             Rd(53) = b3 * a2;
             Rd(54) = b3 * y2;
             Rd(55) = b3 * b2;

             Rd(56) = x0 * x2;
             Rd(57) = x0 * a2;
             Rd(58) = x0 * y2;
             Rd(59) = x0 * b2;

             Rd(60) = x2 * a2;
             Rd(61) = x2 * y2;
             Rd(62) = x2 * b2;

             Rd(63) = a2 * y2;
             Rd(64) = a2 * b2;

             Rd(65) = y2 * b2;
// 3rd order
             Rd(66) = t * t * t;
             Rd(67) = x3 * x3 * x3;
             Rd(68) = a3 * a3 * a3;
             Rd(69) = y3 * y3 * y3;
             Rd(70) = b3 * b3 * b3;
             Rd(71) = x0 * x0 * x0;
             Rd(72) = x2 * x2 * x2;
             Rd(73) = a2 * a2 * a2;
             Rd(74) = y2 * y2 * y2;
             Rd(75) = b2 * b2 * b2;

             Rd(76) = t * t * x3;
             Rd(77) = t * t * a3;
             Rd(78) = t * t * y3;
             Rd(79) = t * t * b3;
             Rd(80) = t * t * x0;
             Rd(81) = t * t * x2;
             Rd(82) = t * t * a2;
             Rd(83) = t * t * y2;
             Rd(84) = t * t * b2;

             Rd(85) = x3 * x3 * t;
             Rd(86) = x3 * x3 * a3;
             Rd(87) = x3 * x3 * y3;
             Rd(88) = x3 * x3 * b3;
             Rd(89) = x3 * x3 * x0;
             Rd(90) = x3 * x3 * x2;
             Rd(91) = x3 * x3 * a2;
             Rd(92) = x3 * x3 * y2;
             Rd(93) = x3 * x3 * b2;

             Rd(94) = a3 * a3 * t;
             Rd(95) = a3 * a3 * x3;
             Rd(96) = a3 * a3 * y3;
             Rd(97) = a3 * a3 * b3;
             Rd(98) = a3 * a3 * x0;
             Rd(99) = a3 * a3 * x2;
             Rd(100) = a3 * a3 * a2;
             Rd(101) = a3 * a3 * y2;
             Rd(102) = a3 * a3 * b2;

             Rd(103) = y3 * y3 * t;
             Rd(104) = y3 * y3 * x3;
             Rd(105) = y3 * y3 * a3;
             Rd(106) = y3 * y3 * b3;
             Rd(107) = y3 * y3 * x0;
             Rd(108) = y3 * y3 * x2;
             Rd(109) = y3 * y3 * a2;
             Rd(110) = y3 * y3 * y2;
             Rd(111) = y3 * y3 * b2;

             Rd(112) = b3 * b3 * t;
             Rd(113) = b3 * b3 * x3;
             Rd(114) = b3 * b3 * a3;
             Rd(115) = b3 * b3 * y3;
             Rd(116) = b3 * b3 * x0;
             Rd(117) = b3 * b3 * x2;
             Rd(118) = b3 * b3 * a2;
             Rd(119) = b3 * b3 * y2;
             Rd(120) = b3 * b3 * b2;

             Rd(121) = x0 * x0 * t;
             Rd(122) = x0 * x0 * x3;
             Rd(123) = x0 * x0 * a3;
             Rd(124) = x0 * x0 * y3;
             Rd(125) = x0 * x0 * b3;
             Rd(126) = x0 * x0 * x2;
             Rd(127) = x0 * x0 * a2;
             Rd(128) = x0 * x0 * y2;
             Rd(129) = x0 * x0 * b2;

             Rd(130) = x2 * x2 * t;
             Rd(131) = x2 * x2 * x3;
             Rd(132) = x2 * x2 * a3;
             Rd(133) = x2 * x2 * y3;
             Rd(134) = x2 * x2 * b3;
             Rd(135) = x2 * x2 * x0;
             Rd(136) = x2 * x2 * a2;
             Rd(137) = x2 * x2 * y2;
             Rd(138) = x2 * x2 * b2;

             Rd(139) = a2 * a2 * t;
             Rd(140) = a2 * a2 * x3;
             Rd(141) = a2 * a2 * a3;
             Rd(142) = a2 * a2 * y3;
             Rd(143) = a2 * a2 * b3;
             Rd(144) = a2 * a2 * x0;
             Rd(145) = a2 * a2 * x2;
             Rd(146) = a2 * a2 * y2;
             Rd(147) = a2 * a2 * b2;

             Rd(148) = y2 * y2 * t;
             Rd(149) = y2 * y2 * x3;
             Rd(150) = y2 * y2 * a3;
             Rd(151) = y2 * y2 * y3;
             Rd(152) = y2 * y2 * b3;
             Rd(153) = y2 * y2 * x0;
             Rd(154) = y2 * y2 * x2;
             Rd(155) = y2 * y2 * a2;
             Rd(156) = y2 * y2 * b2;

             Rd(157) = b2 * b2 * t;
             Rd(158) = b2 * b2 * x3;
             Rd(159) = b2 * b2 * a3;
             Rd(160) = b2 * b2 * y3;
             Rd(161) = b2 * b2 * b3;
             Rd(162) = b2 * b2 * x0;
             Rd(163) = b2 * b2 * x2;
             Rd(164) = b2 * b2 * a2;
             Rd(165) = b2 * b2 * y2;

             Rd(166) = t * x3 * a3;
             Rd(167) = t * x3 * y3;
             Rd(168) = t * x3 * b3;
             Rd(169) = t * x3 * x0;
             Rd(170) = t * x3 * x2;
             Rd(171) = t * x3 * a2;
             Rd(172) = t * x3 * y2;
             Rd(173) = t * x3 * b2;

             Rd(174) = t * a3 * y3;
             Rd(175) = t * a3 * b3;
             Rd(176) = t * a3 * x0;
             Rd(177) = t * a3 * x2;
             Rd(178) = t * a3 * a2;
             Rd(179) = t * a3 * y2;
             Rd(180) = t * a3 * b2;

             Rd(181) = t * y3 * b3;
             Rd(182) = t * y3 * x0;
             Rd(183) = t * y3 * x2;
             Rd(184) = t * y3 * a2;
             Rd(185) = t * y3 * y2;
             Rd(186) = t * y3 * b2;

             Rd(187) = t * b3 * x0;
             Rd(188) = t * b3 * x2;
             Rd(189) = t * b3 * a2;
             Rd(190) = t * b3 * y2;
             Rd(192) = t * b3 * b2;

             Rd(193) = t * x0 * x2;
             Rd(194) = t * x0 * a2;
             Rd(195) = t * x0 * y2;
             Rd(196) = t * x0 * b2;

             Rd(197) = t * x2 * a2;
             Rd(198) = t * x2 * y2;
             Rd(199) = t * x2 * b2;

             Rd(200) = t * a2 * y2;
             Rd(201) = t * a2 * b2;

             Rd(202) = t * y2 * b2;

             Rd(203) = x3 * a3 * y3;
             Rd(204) = x3 * a3 * b3;
             Rd(205) = x3 * a3 * x0;
             Rd(206) = x3 * a3 * x2;
             Rd(207) = x3 * a3 * a2;
             Rd(208) = x3 * a3 * y2;
             Rd(209) = x3 * a3 * b2;

             Rd(210) = x3 * y3 * b3;
             Rd(211) = x3 * y3 * x0;
             Rd(212) = x3 * y3 * x2;
             Rd(213) = x3 * y3 * a2;
             Rd(214) = x3 * y3 * y2;
             Rd(215) = x3 * y3 * b2;
 
             Rd(216) = x3 * b3 * x0;
             Rd(217) = x3 * b3 * x2;
             Rd(217) = x3 * b3 * a2;
             Rd(218) = x3 * b3 * y2;
             Rd(219) = x3 * b3 * b2;
 
             Rd(220) = x3 * x0 * x2;
             Rd(221) = x3 * x0 * a2;
             Rd(222) = x3 * x0 * y2;
             Rd(223) = x3 * x0 * b2;
                
             Rd(224) = x3 * x2 * a2;
             Rd(225) = x3 * x2 * y2;
             Rd(226) = x3 * x2 * b2;
                
             Rd(227) = x3 * a2 * y2;
             Rd(228) = x3 * a2 * b2;
 
             Rd(229) = x3 * y2 * b2;

             Rd(230) = a3 * y3 * b3;
             Rd(231) = a3 * y3 * x0;
             Rd(232) = a3 * y3 * x2;
             Rd(233) = a3 * y3 * a2;
             Rd(234) = a3 * y3 * y2;
             Rd(235) = a3 * y3 * b2;

             Rd(236) = a3 * b3 * x0;
             Rd(237) = a3 * b3 * x2;
             Rd(238) = a3 * b3 * a2;
             Rd(239) = a3 * b3 * y2;
             Rd(240) = a3 * b3 * b2;

             Rd(241) = a3 * x0 * x2;
             Rd(242) = a3 * x0 * a2;
             Rd(243) = a3 * x0 * y2;
             Rd(244) = a3 * x0 * b2;

             Rd(245) = a3 * x2 * a2;
             Rd(246) = a3 * x2 * y2;
             Rd(247) = a3 * x2 * b2;

             Rd(248) = a3 * a2 * y2;
             Rd(249) = a3 * a2 * b2;

             Rd(250) = a3 * y2 * b2;

             Rd(251) = y3 * b3 * x0;
             Rd(252) = y3 * b3 * x2;
             Rd(253) = y3 * b3 * a2;
             Rd(254) = y3 * b3 * y2;
             Rd(255) = y3 * b3 * b2;

             Rd(256) = y3 * x0 * x2;
             Rd(257) = y3 * x0 * a2;
             Rd(258) = y3 * x0 * y2;
             Rd(259) = y3 * x0 * b2;

             Rd(260) = y3 * x2 * a2;
             Rd(261) = y3 * x2 * y2;
             Rd(262) = y3 * x2 * b2;

             Rd(263) = y3 * a2 * y2;
             Rd(264) = y3 * a2 * b2;

             Rd(265) = y3 * y2 * b2;

             Rd(266) = b3 * x0 * x2;
             Rd(267) = b3 * x0 * a2;
             Rd(268) = b3 * x0 * y2;
             Rd(269) = b3 * x0 * b2;

             Rd(270) = b3 * x2 * a2;
             Rd(271) = b3 * x2 * y2;
             Rd(272) = b3 * x2 * b2;

             Rd(273) = b3 * a2 * y2;
             Rd(274) = b3 * a2 * b2;

             Rd(275) = b3 * y2 * b2;

             Rd(276) = x0 * x2 * a2;
             Rd(277) = x0 * x2 * y2;
             Rd(278) = x0 * x2 * b2;

             Rd(279) = x0 * a2 * y2;
             Rd(280) = x0 * a2 * b2;

             Rd(281) = x0 * y2 * b2;

             Rd(282) = x2 * a2 * y2;
             Rd(283) = x2 * a2 * b2;

             Rd(284) = x2 * y2 * b2;

             Rd(285) = a2 * y2 * b2;
// 4th order

             Rd(286) = t * t * t * t;
             Rd(287) = x3 * x3 * x3 * x3;
             Rd(288) = a3 * a3 * a3 * a3;
             Rd(289) = y3 * y3 * y3 * y3;
             Rd(290) = b3 * b3 * b3 * b3;
             Rd(291) = x0 * x0 * x0 * x0;
             Rd(292) = x2 * x2 * x2 * x2;
             Rd(293) = a2 * a2 * a2 * a2;
             Rd(294) = y2 * y2 * y2 * y2;
             Rd(295) = b2 * b2 * b2 * b2;

             Rd(296) = t * t * t * x3;
             Rd(297) = t * t * t * a3;
             Rd(298) = t * t * t * y3;
             Rd(299) = t * t * t * b3;
             Rd(300) = t * t * t * x0;
             Rd(301) = t * t * t * x2;
             Rd(302) = t * t * t * a2;
             Rd(303) = t * t * t * y2;
             Rd(304) = t * t * t * b2;

             Rd(305) = x3 * x3 * x3 * t;
             Rd(306) = x3 * x3 * x3 * a3;
             Rd(307) = x3 * x3 * x3 * y3;
             Rd(308) = x3 * x3 * x3 * b3;
             Rd(309) = x3 * x3 * x3 * x0;
             Rd(310) = x3 * x3 * x3 * x2;
             Rd(311) = x3 * x3 * x3 * a2;
             Rd(312) = x3 * x3 * x3 * y2;
             Rd(313) = x3 * x3 * x3 * b2;

             Rd(314) = a3 * a3 * a3 * t;
             Rd(315) = a3 * a3 * a3 * x3;
             Rd(316) = a3 * a3 * a3 * y3;
             Rd(317) = a3 * a3 * a3 * b3;
             Rd(318) = a3 * a3 * a3 * x0;
             Rd(319) = a3 * a3 * a3 * x2;
             Rd(320) = a3 * a3 * a3 * a2;
             Rd(321) = a3 * a3 * a3 * y2;
             Rd(322) = a3 * a3 * a3 * b2;

             Rd(323) = y3 * y3 * y3 * t;
             Rd(324) = y3 * y3 * y3 * x3;
             Rd(325) = y3 * y3 * y3 * a3;
             Rd(326) = y3 * y3 * y3 * b3;
             Rd(327) = y3 * y3 * y3 * x0;
             Rd(328) = y3 * y3 * y3 * x2;
             Rd(329) = y3 * y3 * y3 * a2;
             Rd(330) = y3 * y3 * y3 * y2;
             Rd(331) = y3 * y3 * y3 * b2;

             Rd(332) = b3 * b3 * b3 * t;
             Rd(333) = b3 * b3 * b3 * x3;
             Rd(334) = b3 * b3 * b3 * a3;
             Rd(335) = b3 * b3 * b3 * y3;
             Rd(336) = b3 * b3 * b3 * x0;
             Rd(337) = b3 * b3 * b3 * x2;
             Rd(338) = b3 * b3 * b3 * a2;
             Rd(339) = b3 * b3 * b3 * y2;
             Rd(340) = b3 * b3 * b3 * b2;

             Rd(341) = x0 * x0 * x0 * t;
             Rd(342) = x0 * x0 * x0 * x3;
             Rd(343) = x0 * x0 * x0 * a3;
             Rd(344) = x0 * x0 * x0 * y3;
             Rd(345) = x0 * x0 * x0 * b3;
             Rd(346) = x0 * x0 * x0 * x2;
             Rd(347) = x0 * x0 * x0 * a2;
             Rd(348) = x0 * x0 * x0 * y2;
             Rd(349) = x0 * x0 * x0 * b2;

             Rd(350) = x2 * x2 * x2 * t;
             Rd(351) = x2 * x2 * x2 * x3;
             Rd(352) = x2 * x2 * x2 * a3;
             Rd(353) = x2 * x2 * x2 * y3;
             Rd(354) = x2 * x2 * x2 * b3;
             Rd(355) = x2 * x2 * x2 * x0;
             Rd(356) = x2 * x2 * x2 * a2;
             Rd(357) = x2 * x2 * x2 * y2;
             Rd(358) = x2 * x2 * x2 * b2;

             Rd(359) = a2 * a2 * a2 * t;
             Rd(360) = a2 * a2 * a2 * x3;
             Rd(361) = a2 * a2 * a2 * a3;
             Rd(362) = a2 * a2 * a2 * y3;
             Rd(363) = a2 * a2 * a2 * b3;
             Rd(364) = a2 * a2 * a2 * x0;
             Rd(365) = a2 * a2 * a2 * x2;
             Rd(366) = a2 * a2 * a2 * y2;
             Rd(367) = a2 * a2 * a2 * b2;

             Rd(368) = y2 * y2 * y2 * t;
             Rd(369) = y2 * y2 * y2 * x3;
             Rd(370) = y2 * y2 * y2 * a3;
             Rd(371) = y2 * y2 * y2 * y3;
             Rd(372) = y2 * y2 * y2 * b3;
             Rd(373) = y2 * y2 * y2 * x0;
             Rd(374) = y2 * y2 * y2 * x2;
             Rd(375) = y2 * y2 * y2 * a2;
             Rd(376) = y2 * y2 * y2 * b2;

             Rd(377) = b2 * b2 * b2 * t;
             Rd(378) = b2 * b2 * b2 * x3;
             Rd(379) = b2 * b2 * b2 * a3;
             Rd(380) = b2 * b2 * b2 * y3;
             Rd(381) = b2 * b2 * b2 * b3;
             Rd(382) = b2 * b2 * b2 * x0;
             Rd(383) = b2 * b2 * b2 * x2;
             Rd(384) = b2 * b2 * b2 * a2;
             Rd(385) = b2 * b2 * b2 * y2;

             Rd(386) = t * t * x3 * x3;
             Rd(387) = t * t * a3 * a3;
             Rd(388) = t * t * y3 * y3;
             Rd(389) = t * t * b3 * b3;
             Rd(390) = t * t * x0 * x0;
             Rd(391) = t * t * x2 * x2;
             Rd(392) = t * t * a2 * a2;
             Rd(393) = t * t * y2 * y2;
             Rd(394) = t * t * b2 * b2;

             Rd(395) = x3 * x3 * a3 * a3;
             Rd(396) = x3 * x3 * y3 * y3;
             Rd(397) = x3 * x3 * b3 * b3;
             Rd(398) = x3 * x3 * x0 * x0;
             Rd(399) = x3 * x3 * x2 * x2;
             Rd(400) = x3 * x3 * a2 * a2;
             Rd(401) = x3 * x3 * y2 * y2;
             Rd(402) = x3 * x3 * b2 * b2;

             Rd(403) = a3 * a3 * y3 * y3;
             Rd(404) = a3 * a3 * b3 * b3;
             Rd(405) = a3 * a3 * x0 * x0;
             Rd(406) = a3 * a3 * x2 * x2;
             Rd(407) = a3 * a3 * a2 * a2;
             Rd(408) = a3 * a3 * y2 * y2;
             Rd(409) = a3 * a3 * b2 * b2;

             Rd(410) = y3 * y3 * b3 * b3;
             Rd(411) = y3 * y3 * x0 * x0;
             Rd(412) = y3 * y3 * x2 * x2;
             Rd(413) = y3 * y3 * a2 * a2;
             Rd(414) = y3 * y3 * y2 * y2;
             Rd(415) = y3 * y3 * b2 * b2;

             Rd(416) = b3 * b3 * x0 * x0;
             Rd(417) = b3 * b3 * x2 * x2;
             Rd(418) = b3 * b3 * a2 * a2;
             Rd(419) = b3 * b3 * y2 * y2;
             Rd(420) = b3 * b3 * b2 * b2;

             Rd(421) = x0 * x0 * x2 * x2;
             Rd(422) = x0 * x0 * a2 * a2;
             Rd(423) = x0 * x0 * y2 * y2;
             Rd(424) = x0 * x0 * b2 * b2;

             Rd(425) = x2 * x2 * a2 * a2;
             Rd(426) = x2 * x2 * y2 * y2;
             Rd(427) = x2 * x2 * b2 * b2;

             Rd(428) = a2 * a2 * y2 * y2;
             Rd(429) = a2 * a2 * b2 * b2;

             Rd(430) = y2 * y2 * b2 * b2;

             Rd(431) = t * t * x3 * a3;
             Rd(432) = t * t * x3 * y3;
             Rd(433) = t * t * x3 * b3;
             Rd(434) = t * t * x3 * x0;
             Rd(435) = t * t * x3 * x2;
             Rd(436) = t * t * x3 * a2;
             Rd(437) = t * t * x3 * y2;
             Rd(438) = t * t * x3 * b2;

             Rd(439) = t * t * a3 * y3;
             Rd(440) = t * t * a3 * b3;
             Rd(441) = t * t * a3 * x0;
             Rd(442) = t * t * a3 * x2;
             Rd(443) = t * t * a3 * a2;
             Rd(444) = t * t * a3 * y2;
             Rd(445) = t * t * a3 * b2;

             Rd(446) = t * t * y3 * b3;
             Rd(447) = t * t * y3 * x0;
             Rd(448) = t * t * y3 * x2;
             Rd(449) = t * t * y3 * a2;
             Rd(450) = t * t * y3 * y2;
             Rd(451) = t * t * y3 * b2;

             Rd(452) = t * t * b3 * x0;
             Rd(453) = t * t * b3 * x2;
             Rd(454) = t * t * b3 * a2;
             Rd(455) = t * t * b3 * y2;
             Rd(456) = t * t * b3 * b2;

             Rd(457) = t * t * x0 * x2;
             Rd(458) = t * t * x0 * a2;
             Rd(459) = t * t * x0 * y2;
             Rd(460) = t * t * x0 * b2;

             Rd(461) = t * t * x2 * a2;
             Rd(462) = t * t * x2 * y2;
             Rd(463) = t * t * x2 * b2;

             Rd(464) = t * t * a2 * y2;
             Rd(465) = t * t * a2 * b2;

             Rd(466) = t * t * y2 * b2;

             Rd(467) = x3 * x3 * t * a3;
             Rd(468) = x3 * x3 * t * y3;
             Rd(469) = x3 * x3 * t * b3;
             Rd(470) = x3 * x3 * t * x0;
             Rd(471) = x3 * x3 * t * x2;
             Rd(472) = x3 * x3 * t * a2;
             Rd(473) = x3 * x3 * t * y2;
             Rd(474) = x3 * x3 * t * b2;

             Rd(475) = x3 * x3 * a3 * y3;
             Rd(476) = x3 * x3 * a3 * b3;
             Rd(477) = x3 * x3 * a3 * x0;
             Rd(478) = x3 * x3 * a3 * x2;
             Rd(479) = x3 * x3 * a3 * a2;
             Rd(480) = x3 * x3 * a3 * y2;
             Rd(481) = x3 * x3 * a3 * b2;

             Rd(482) = x3 * x3 * y3 * b3;
             Rd(483) = x3 * x3 * y3 * x0;
             Rd(484) = x3 * x3 * y3 * x2;
             Rd(485) = x3 * x3 * y3 * a2;
             Rd(486) = x3 * x3 * y3 * y2;
             Rd(487) = x3 * x3 * y3 * b2;

             Rd(488) = x3 * x3 * b3 * x0;
             Rd(489) = x3 * x3 * b3 * x2;
             Rd(490) = x3 * x3 * b3 * a2;
             Rd(491) = x3 * x3 * b3 * y2;
             Rd(492) = x3 * x3 * b3 * b2;

             Rd(493) = x3 * x3 * x0 * x2;
             Rd(494) = x3 * x3 * x0 * a2;
             Rd(495) = x3 * x3 * x0 * y2;
             Rd(496) = x3 * x3 * x0 * b2;

             Rd(497) = x3 * x3 * x2 * a2;
             Rd(498) = x3 * x3 * x2 * y2;
             Rd(499) = x3 * x3 * x2 * b2;

             Rd(500) = x3 * x3 * a2 * y2;
             Rd(501) = x3 * x3 * a2 * b2;

             Rd(502) = x3 * x3 * y2 * b2;


             Rd(503) = a3 * a3 * t * x3;
             Rd(504) = a3 * a3 * t * y3;
             Rd(505) = a3 * a3 * t * b3;
             Rd(506) = a3 * a3 * t * x0;
             Rd(507) = a3 * a3 * t * x2;
             Rd(508) = a3 * a3 * t * a2;
             Rd(509) = a3 * a3 * t * y2;
             Rd(510) = a3 * a3 * t * b2;

             Rd(511) = a3 * a3 * x3 * y3;
             Rd(512) = a3 * a3 * x3 * b3;
             Rd(513) = a3 * a3 * x3 * x0;
             Rd(514) = a3 * a3 * x3 * x2;
             Rd(515) = a3 * a3 * x3 * a2;
             Rd(516) = a3 * a3 * x3 * y2;
             Rd(517) = a3 * a3 * x3 * b2;

             Rd(518) = a3 * a3 * y3 * b3;
             Rd(519) = a3 * a3 * y3 * x0;
             Rd(520) = a3 * a3 * y3 * x2;
             Rd(521) = a3 * a3 * y3 * a2;
             Rd(522) = a3 * a3 * y3 * y2;
             Rd(523) = a3 * a3 * y3 * b2;

             Rd(524) = a3 * a3 * b3 * x0;
             Rd(525) = a3 * a3 * b3 * x2;
             Rd(526) = a3 * a3 * b3 * a2;
             Rd(527) = a3 * a3 * b3 * y2;
             Rd(528) = a3 * a3 * b3 * b2;

             Rd(529) = a3 * a3 * x0 * x2;
             Rd(530) = a3 * a3 * x0 * a2;
             Rd(531) = a3 * a3 * x0 * y2;
             Rd(532) = a3 * a3 * x0 * b2;

             Rd(533) = a3 * a3 * x2 * a2;
             Rd(534) = a3 * a3 * x2 * y2;
             Rd(535) = a3 * a3 * x2 * b2;

             Rd(536) = a3 * a3 * a2 * y2;
             Rd(537) = a3 * a3 * a2 * b2;

             Rd(538) = a3 * a3 * y2 * b2;

             Rd(539) = y3 * y3 * t * x3;
             Rd(540) = y3 * y3 * t * a3;
             Rd(541) = y3 * y3 * t * b3;
             Rd(542) = y3 * y3 * t * x0;
             Rd(543) = y3 * y3 * t * x2;
             Rd(544) = y3 * y3 * t * a2;
             Rd(545) = y3 * y3 * t * y2;
             Rd(546) = y3 * y3 * t * b2;

             Rd(547) = y3 * y3 * x3 * a3;
             Rd(548) = y3 * y3 * x3 * b3;
             Rd(549) = y3 * y3 * x3 * x0;
             Rd(550) = y3 * y3 * x3 * x2;
             Rd(551) = y3 * y3 * x3 * a2;
             Rd(552) = y3 * y3 * x3 * y2;
             Rd(553) = y3 * y3 * x3 * b2;

             Rd(554) = y3 * y3 * a3 * b3;
             Rd(555) = y3 * y3 * a3 * x0;
             Rd(556) = y3 * y3 * a3 * x2;
             Rd(557) = y3 * y3 * a3 * a2;
             Rd(558) = y3 * y3 * a3 * y2;
             Rd(559) = y3 * y3 * a3 * b2;

             Rd(560) = y3 * y3 * b3 * x0;
             Rd(561) = y3 * y3 * b3 * x2;
             Rd(562) = y3 * y3 * b3 * a2;
             Rd(563) = y3 * y3 * b3 * y2;
             Rd(564) = y3 * y3 * b3 * b2;

             Rd(565) = y3 * y3 * x0 * x2;
             Rd(566) = y3 * y3 * x0 * a2;
             Rd(567) = y3 * y3 * x0 * y2;
             Rd(568) = y3 * y3 * x0 * b2;

             Rd(569) = y3 * y3 * x2 * a2;
             Rd(570) = y3 * y3 * x2 * y2;
             Rd(571) = y3 * y3 * x2 * b2;

             Rd(572) = y3 * y3 * a2 * y2;
             Rd(573) = y3 * y3 * a2 * b2;

             Rd(574) = y3 * y3 * y2 * b2;

             Rd(575) = b3 * b3 * t * x3;
             Rd(576) = b3 * b3 * t * a3;
             Rd(577) = b3 * b3 * t * y3;
             Rd(578) = b3 * b3 * t * x0;
             Rd(579) = b3 * b3 * t * x2;
             Rd(580) = b3 * b3 * t * a2;
             Rd(581) = b3 * b3 * t * y2;
             Rd(582) = b3 * b3 * t * b2;

             Rd(583) = b3 * b3 * x3 * a3;
             Rd(584) = b3 * b3 * x3 * y3;
             Rd(585) = b3 * b3 * x3 * x0;
             Rd(586) = b3 * b3 * x3 * x2;
             Rd(587) = b3 * b3 * x3 * a2;
             Rd(588) = b3 * b3 * x3 * y2;
             Rd(589) = b3 * b3 * x3 * b2;

             Rd(590) = b3 * b3 * a3 * y3;
             Rd(591) = b3 * b3 * a3 * x0;
             Rd(592) = b3 * b3 * a3 * x2;
             Rd(593) = b3 * b3 * a3 * a2;
             Rd(594) = b3 * b3 * a3 * y2;
             Rd(595) = b3 * b3 * a3 * b2;

             Rd(596) = b3 * b3 * y3 * x0;
             Rd(597) = b3 * b3 * y3 * x2;
             Rd(598) = b3 * b3 * y3 * a2;
             Rd(599) = b3 * b3 * y3 * y2;
             Rd(600) = b3 * b3 * y3 * b2;

             Rd(601) = b3 * b3 * x0 * x2;
             Rd(602) = b3 * b3 * x0 * a2;
             Rd(603) = b3 * b3 * x0 * y2;
             Rd(604) = b3 * b3 * x0 * b2;

             Rd(605) = b3 * b3 * x2 * a2;
             Rd(606) = b3 * b3 * x2 * y2;
             Rd(607) = b3 * b3 * x2 * b2;

             Rd(608) = b3 * b3 * a2 * y2;
             Rd(609) = b3 * b3 * a2 * b2;

             Rd(610) = b3 * b3 * y2 * b2;

             Rd(611) = x0 * x0 * t * x3;
             Rd(612) = x0 * x0 * t * a3;
             Rd(613) = x0 * x0 * t * y3;
             Rd(614) = x0 * x0 * t * b3;
             Rd(615) = x0 * x0 * t * x2;
             Rd(616) = x0 * x0 * t * a2;
             Rd(617) = x0 * x0 * t * y2;
             Rd(618) = x0 * x0 * t * b2;

             Rd(619) = x0 * x0 * x3 * a3;
             Rd(620) = x0 * x0 * x3 * y3;
             Rd(621) = x0 * x0 * x3 * b3;
             Rd(622) = x0 * x0 * x3 * x2;
             Rd(623) = x0 * x0 * x3 * a2;
             Rd(624) = x0 * x0 * x3 * y2;
             Rd(625) = x0 * x0 * x3 * b2;

             Rd(626) = x0 * x0 * a3 * y3;
             Rd(627) = x0 * x0 * a3 * b3;
             Rd(628) = x0 * x0 * a3 * x2;
             Rd(629) = x0 * x0 * a3 * a2;
             Rd(630) = x0 * x0 * a3 * y2;
             Rd(631) = x0 * x0 * a3 * b2;

             Rd(632) = x0 * x0 * y3 * b3;
             Rd(633) = x0 * x0 * y3 * x2;
             Rd(634) = x0 * x0 * y3 * a2;
             Rd(635) = x0 * x0 * y3 * y2;
             Rd(636) = x0 * x0 * y3 * b2;

             Rd(637) = x0 * x0 * b3 * x2;
             Rd(638) = x0 * x0 * b3 * a2;
             Rd(639) = x0 * x0 * b3 * y2;
             Rd(640) = x0 * x0 * b3 * b2;

             Rd(641) = x0 * x0 * x2 * a2;
             Rd(642) = x0 * x0 * x2 * y2;
             Rd(643) = x0 * x0 * x2 * b2;

             Rd(644) = x0 * x0 * a2 * y2;
             Rd(645) = x0 * x0 * a2 * b2;

             Rd(646) = x0 * x0 * y2 * b2;

             Rd(647) = x2 * x2 * t * x3;
             Rd(648) = x2 * x2 * t * a3;
             Rd(649) = x2 * x2 * t * y3;
             Rd(650) = x2 * x2 * t * b3;
             Rd(651) = x2 * x2 * t * x0;
             Rd(652) = x2 * x2 * t * a2;
             Rd(653) = x2 * x2 * t * y2;
             Rd(654) = x2 * x2 * t * b2;

             Rd(655) = x2 * x2 * x3 * a3;
             Rd(656) = x2 * x2 * x3 * y3;
             Rd(657) = x2 * x2 * x3 * b3;
             Rd(658) = x2 * x2 * x3 * x0;
             Rd(659) = x2 * x2 * x3 * a2;
             Rd(660) = x2 * x2 * x3 * y2;
             Rd(661) = x2 * x2 * x3 * b2;

             Rd(662) = x2 * x2 * a3 * y3;
             Rd(663) = x2 * x2 * a3 * b3;
             Rd(664) = x2 * x2 * a3 * x0;
             Rd(665) = x2 * x2 * a3 * a2;
             Rd(666) = x2 * x2 * a3 * y2;
             Rd(667) = x2 * x2 * a3 * b2;

             Rd(668) = x2 * x2 * y3 * b3;
             Rd(669) = x2 * x2 * y3 * x0;
             Rd(670) = x2 * x2 * y3 * a2;
             Rd(671) = x2 * x2 * y3 * y2;
             Rd(672) = x2 * x2 * y3 * b2;

             Rd(673) = x2 * x2 * b3 * x0;
             Rd(674) = x2 * x2 * b3 * a2;
             Rd(675) = x2 * x2 * b3 * y2;
             Rd(676) = x2 * x2 * b3 * b2;

             Rd(677) = x2 * x2 * x0 * a2;
             Rd(678) = x2 * x2 * x0 * y2;
             Rd(679) = x2 * x2 * x0 * b2;

             Rd(680) = x2 * x2 * a2 * y2;
             Rd(681) = x2 * x2 * a2 * b2;

             Rd(682) = x2 * x2 * y2 * b2;

             Rd(683) = a2 * a2 * t * x3;
             Rd(684) = a2 * a2 * t * a3;
             Rd(685) = a2 * a2 * t * y3;
             Rd(686) = a2 * a2 * t * b3;
             Rd(687) = a2 * a2 * t * x0;
             Rd(688) = a2 * a2 * t * x2;
             Rd(689) = a2 * a2 * t * y2;
             Rd(691) = a2 * a2 * t * b2;

             Rd(692) = a2 * a2 * x3 * a3;
             Rd(694) = a2 * a2 * x3 * y3;
             Rd(695) = a2 * a2 * x3 * b3;
             Rd(696) = a2 * a2 * x3 * x0;
             Rd(697) = a2 * a2 * x3 * x2;
             Rd(698) = a2 * a2 * x3 * y2;
             Rd(699) = a2 * a2 * x3 * b2;

             Rd(700) = a2 * a2 * a3 * y3;
             Rd(701) = a2 * a2 * a3 * b3;
             Rd(702) = a2 * a2 * a3 * x0;
             Rd(703) = a2 * a2 * a3 * x2;
             Rd(704) = a2 * a2 * a3 * y2;
             Rd(705) = a2 * a2 * a3 * b2;

             Rd(706) = a2 * a2 * y3 * b3;
             Rd(707) = a2 * a2 * y3 * x0;
             Rd(708) = a2 * a2 * y3 * x2;
             Rd(709) = a2 * a2 * y3 * y2;
             Rd(710) = a2 * a2 * y3 * b2;

             Rd(712) = a2 * a2 * b3 * x0;
             Rd(713) = a2 * a2 * b3 * x2;
             Rd(714) = a2 * a2 * b3 * y2;
             Rd(715) = a2 * a2 * b3 * b2;

             Rd(716) = a2 * a2 * x0 * x2;
             Rd(717) = a2 * a2 * x0 * y2;
             Rd(718) = a2 * a2 * x0 * b2;

             Rd(719) = a2 * a2 * x2 * y2;
             Rd(720) = a2 * a2 * x2 * b2;

             Rd(721) = a2 * a2 * y2 * b2;

             Rd(722) = y2 * y2 * t * x3;
             Rd(723) = y2 * y2 * t * a3;
             Rd(724) = y2 * y2 * t * y3;
             Rd(725) = y2 * y2 * t * b3;
             Rd(726) = y2 * y2 * t * x0;
             Rd(727) = y2 * y2 * t * x2;
             Rd(728) = y2 * y2 * t * a2;
             Rd(729) = y2 * y2 * t * b2;

             Rd(730) = y2 * y2 * x3 * a3;
             Rd(731) = y2 * y2 * x3 * y3;
             Rd(732) = y2 * y2 * x3 * b3;
             Rd(733) = y2 * y2 * x3 * x0;
             Rd(734) = y2 * y2 * x3 * x2;
             Rd(735) = y2 * y2 * x3 * a2;
             Rd(736) = y2 * y2 * x3 * b2;

             Rd(737) = y2 * y2 * a3 * y3;
             Rd(734) = y2 * y2 * a3 * b3;
             Rd(735) = y2 * y2 * a3 * x0;
             Rd(736) = y2 * y2 * a3 * x2;
             Rd(737) = y2 * y2 * a3 * a2;
             Rd(738) = y2 * y2 * a3 * b2;

             Rd(739) = y2 * y2 * y3 * b3;
             Rd(740) = y2 * y2 * y3 * x0;
             Rd(741) = y2 * y2 * y3 * x2;
             Rd(742) = y2 * y2 * y3 * a2;
             Rd(743) = y2 * y2 * y3 * b2;

             Rd(744) = y2 * y2 * b3 * x0;
             Rd(745) = y2 * y2 * b3 * x2;
             Rd(746) = y2 * y2 * b3 * a2;
             Rd(747) = y2 * y2 * b3 * b2;

             Rd(748) = y2 * y2 * x0 * x2;
             Rd(749) = y2 * y2 * x0 * a2;
             Rd(750) = y2 * y2 * x0 * b2;

             Rd(751) = y2 * y2 * x2 * a2;
             Rd(752) = y2 * y2 * x2 * b2;

             Rd(753) = y2 * y2 * a2 * b2;

             Rd(754) = b2 * b2 * t * x3;
             Rd(755) = b2 * b2 * t * a3;
             Rd(756) = b2 * b2 * t * y3;
             Rd(757) = b2 * b2 * t * b3;
             Rd(758) = b2 * b2 * t * x0;
             Rd(759) = b2 * b2 * t * x2;
             Rd(760) = b2 * b2 * t * a2;
             Rd(761) = b2 * b2 * t * y2;

             Rd(762) = b2 * b2 * x3 * a3;
             Rd(763) = b2 * b2 * x3 * y3;
             Rd(764) = b2 * b2 * x3 * b3;
             Rd(765) = b2 * b2 * x3 * x0;
             Rd(766) = b2 * b2 * x3 * x2;
             Rd(767) = b2 * b2 * x3 * a2;
             Rd(768) = b2 * b2 * x3 * y2;

             Rd(769) = b2 * b2 * a3 * y3;
             Rd(770) = b2 * b2 * a3 * b3;
             Rd(771) = b2 * b2 * a3 * x0;
             Rd(772) = b2 * b2 * a3 * x2;
             Rd(773) = b2 * b2 * a3 * a2;
             Rd(774) = b2 * b2 * a3 * y2;

             Rd(775) = b2 * b2 * y3 * b3;
             Rd(776) = b2 * b2 * y3 * x0;
             Rd(778) = b2 * b2 * y3 * x2;
             Rd(779) = b2 * b2 * y3 * a2;
             Rd(780) = b2 * b2 * y3 * y2;

             Rd(781) = b2 * b2 * b3 * x0;
             Rd(782) = b2 * b2 * b3 * x2;
             Rd(783) = b2 * b2 * b3 * a2;
             Rd(784) = b2 * b2 * b3 * y2;

             Rd(785) = b2 * b2 * x0 * x2;
             Rd(786) = b2 * b2 * x0 * a2;
             Rd(787) = b2 * b2 * x0 * y2;

             Rd(788) = b2 * b2 * x2 * a2;
             Rd(789) = b2 * b2 * x2 * y2;

             Rd(790) = b2 * b2 * a2 * y2;

             Rd(791) = t * x3 * a3 * y3;
             Rd(792) = t * x3 * a3 * b3;
             Rd(793) = t * x3 * a3 * x0;
             Rd(794) = t * x3 * a3 * x2;
             Rd(795) = t * x3 * a3 * a2;
             Rd(796) = t * x3 * a3 * y2;
             Rd(797) = t * x3 * a3 * b2;

             Rd(798) = t * x3 * y3 * b3;
             Rd(799) = t * x3 * y3 * x0;
             Rd(800) = t * x3 * y3 * x2;
             Rd(801) = t * x3 * y3 * a2;
             Rd(802) = t * x3 * y3 * y2;
             Rd(803) = t * x3 * y3 * b2;

             Rd(804) = t * x3 * b3 * x0;
             Rd(805) = t * x3 * b3 * x2;
             Rd(806) = t * x3 * b3 * a2;
             Rd(807) = t * x3 * b3 * y2;
             Rd(808) = t * x3 * b3 * b2;

             Rd(809) = t * x3 * x0 * x2;
             Rd(810) = t * x3 * x0 * a2;
             Rd(811) = t * x3 * x0 * y2;
             Rd(812) = t * x3 * x0 * b2;

             Rd(813) = t * x3 * x2 * a2;
             Rd(814) = t * x3 * x2 * y2;
             Rd(815) = t * x3 * x2 * b2;
             Rd(816) = t * x3 * a2 * y2;
             Rd(817) = t * x3 * a2 * b2;

             Rd(818) = t * x3 * y2 * b2;

             Rd(819) = t * a3 * y3 * b3;
             Rd(820) = t * a3 * y3 * x0;
             Rd(821) = t * a3 * y3 * x2;
             Rd(822) = t * a3 * y3 * a2;
             Rd(823) = t * a3 * y3 * y2;
             Rd(824) = t * a3 * y3 * b2;

             Rd(825) = t * a3 * b3 * x0;
             Rd(826) = t * a3 * b3 * x2;
             Rd(827) = t * a3 * b3 * a2;
             Rd(828) = t * a3 * b3 * y2;
             Rd(829) = t * a3 * b3 * b2;

             Rd(830) = t * a3 * x0 * x2;
             Rd(831) = t * a3 * x0 * a2;
             Rd(832) = t * a3 * x0 * y2;
             Rd(833) = t * a3 * x0 * b2;

             Rd(834) = t * a3 * x2 * a2;
             Rd(835) = t * a3 * x2 * y2;
             Rd(836) = t * a3 * x2 * b2;

             Rd(837) = t * a3 * a2 * y2;
             Rd(838) = t * a3 * a2 * b2;

             Rd(839) = t * a3 * y2 * b2;

             Rd(840) = t * y3 * b3 * x0;
             Rd(841) = t * y3 * b3 * x2;
             Rd(842) = t * y3 * b3 * a2;
             Rd(843) = t * y3 * b3 * y2;
             Rd(844) = t * y3 * b3 * b2;

             Rd(845) = t * y3 * x0 * x2;
             Rd(846) = t * y3 * x0 * a2;
             Rd(847) = t * y3 * x0 * y2;
             Rd(848) = t * y3 * x0 * b2;

             Rd(849) = t * y3 * x2 * a2;
             Rd(850) = t * y3 * x2 * y2;
             Rd(851) = t * y3 * x2 * b2;

             Rd(852) = t * y3 * a2 * y2;
             Rd(853) = t * y3 * a2 * b2;

             Rd(854) = t * y3 * y2 * b2;

             Rd(855) = t * b3 * x0 * x2;
             Rd(856) = t * b3 * x0 * a2;
             Rd(857) = t * b3 * x0 * y2;
             Rd(858) = t * b3 * x0 * b2;

             Rd(859) = t * b3 * x2 * a2;
             Rd(860) = t * b3 * x2 * y2;
             Rd(861) = t * b3 * x2 * b2;

             Rd(862) = t * b3 * a2 * y2;
             Rd(863) = t * b3 * a2 * b2;

             Rd(864) = t * b3 * y2 * b2;

             Rd(865) = t * x0 * x2 * a2;
             Rd(866) = t * x0 * x2 * y2;
             Rd(867) = t * x0 * x2 * b2;

             Rd(868) = t * x0 * a2 * y2;
             Rd(869) = t * x0 * a2 * b2;

             Rd(870) = t * x0 * y2 * b2;

             Rd(871) = t * x2 * a2 * y2;
             Rd(872) = t * x2 * a2 * b2;

             Rd(873) = t * x2 * y2 * b2;

             Rd(874) = t * a2 * y2 * b2;

             Rd(875) = x3 * a3 * y3 * b3;
             Rd(876) = x3 * a3 * y3 * x0;
             Rd(877) = x3 * a3 * y3 * x2;
             Rd(878) = x3 * a3 * y3 * a2;
             Rd(879) = x3 * a3 * y3 * y2;
             Rd(880) = x3 * a3 * y3 * b2;

             Rd(881) = x3 * a3 * b3 * x0;
             Rd(882) = x3 * a3 * b3 * x2;
             Rd(883) = x3 * a3 * b3 * a2;
             Rd(884) = x3 * a3 * b3 * y2;
             Rd(885) = x3 * a3 * b3 * b2;

             Rd(886) = x3 * a3 * x0 * x2;
             Rd(887) = x3 * a3 * x0 * a2;
             Rd(888) = x3 * a3 * x0 * y2;
             Rd(889) = x3 * a3 * x0 * b2;

             Rd(890) = x3 * a3 * x2 * a2;
             Rd(891) = x3 * a3 * x2 * y2;
             Rd(892) = x3 * a3 * x2 * b2;

             Rd(893) = x3 * a3 * a2 * y2;
             Rd(894) = x3 * a3 * a2 * b2;

             Rd(895) = x3 * a3 * y2 * b2;

             Rd(896) = x3 * y3 * b3 * x0;
             Rd(897) = x3 * y3 * b3 * x2;
             Rd(898) = x3 * y3 * b3 * a2;
             Rd(899) = x3 * y3 * b3 * y2;
             Rd(900) = x3 * y3 * b3 * b2;

             Rd(901) = x3 * y3 * x0 * x2;
             Rd(902) = x3 * y3 * x0 * a2;
             Rd(903) = x3 * y3 * x0 * y2;
             Rd(904) = x3 * y3 * x0 * b2;

             Rd(905) = x3 * y3 * x2 * a2;
             Rd(906) = x3 * y3 * x2 * y2;
             Rd(907) = x3 * y3 * x2 * b2;

             Rd(908) = x3 * y3 * a2 * y2;
             Rd(909) = x3 * y3 * a2 * b2;

             Rd(910) = x3 * y3 * y2 * b2;

             Rd(911) = x3 * b3 * x0 * x2;
             Rd(912) = x3 * b3 * x0 * a2;
             Rd(913) = x3 * b3 * x0 * y2;
             Rd(914) = x3 * b3 * x0 * b2;

             Rd(915) = x3 * b3 * x2 * a2;
             Rd(916) = x3 * b3 * x2 * y2;
             Rd(917) = x3 * b3 * x2 * b2;

             Rd(918) = x3 * b3 * a2 * y2;
             Rd(919) = x3 * b3 * a2 * b2;

             Rd(920) = x3 * b3 * y2 * b2;

             Rd(921) = x3 * x0 * x2 * a2;
             Rd(922) = x3 * x0 * x2 * y2;
             Rd(923) = x3 * x0 * x2 * b2;

             Rd(924) = x3 * x0 * a2 * y2;
             Rd(925) = x3 * x0 * a2 * b2;

             Rd(926) = x3 * x0 * y2 * b2;

             Rd(927) = x3 * x2 * a2 * y2;
             Rd(928) = x3 * x2 * a2 * b2;

             Rd(929) = x3 * x2 * y2 * b2;

             Rd(930) = x3 * a2 * y2 * b2;

             Rd(931) = a3 * y3 * b3 * x0;
             Rd(932) = a3 * y3 * b3 * x2;
             Rd(933) = a3 * y3 * b3 * a2;
             Rd(934) = a3 * y3 * b3 * y2;
             Rd(935) = a3 * y3 * b3 * b2;

             Rd(936) = a3 * y3 * x0 * x2;
             Rd(937) = a3 * y3 * x0 * a2;
             Rd(938) = a3 * y3 * x0 * y2;
             Rd(939) = a3 * y3 * x0 * b2;

             Rd(940) = a3 * y3 * x2 * a2;
             Rd(941) = a3 * y3 * x2 * y2;
             Rd(942) = a3 * y3 * x2 * b2;
             Rd(943) = a3 * y3 * a2 * y2;
             Rd(944) = a3 * y3 * a2 * b2;

             Rd(945) = a3 * y3 * y2 * b2;

             Rd(946) = a3 * b3 * x0 * x2;
             Rd(947) = a3 * b3 * x0 * a2;
             Rd(948) = a3 * b3 * x0 * y2;
             Rd(949) = a3 * b3 * x0 * b2;

             Rd(950) = a3 * b3 * x2 * a2;
             Rd(951) = a3 * b3 * x2 * y2;
             Rd(952) = a3 * b3 * x2 * b2;

             Rd(953) = a3 * b3 * a2 * y2;
             Rd(954) = a3 * b3 * a2 * b2;

             Rd(955) = a3 * b3 * y2 * b2;

             Rd(956) = a3 * x0 * x2 * a2;
             Rd(957) = a3 * x0 * x2 * y2;
             Rd(958) = a3 * x0 * x2 * b2;

             Rd(959) = a3 * x0 * a2 * y2;
             Rd(960) = a3 * x0 * a2 * b2;

             Rd(961) = a3 * x0 * y2 * b2;

             Rd(962) = a3 * x2 * a2 * y2;
             Rd(963) = a3 * x2 * a2 * b2;

             Rd(964) = a3 * x2 * y2 * b2;

             Rd(965) = a3 * a2 * y2 * b2;

             Rd(966) = y3 * b3 * x0 * x2;
             Rd(967) = y3 * b3 * x0 * a2;
             Rd(968) = y3 * b3 * x0 * y2;
             Rd(969) = y3 * b3 * x0 * b2;

             Rd(970) = y3 * b3 * x2 * a2;
             Rd(971) = y3 * b3 * x2 * y2;
             Rd(972) = y3 * b3 * x2 * b2;

             Rd(973) = y3 * b3 * a2 * y2;
             Rd(974) = y3 * b3 * a2 * b2;

             Rd(975) = y3 * b3 * y2 * b2;

             Rd(976) = y3 * x0 * x2 * a2;
             Rd(977) = y3 * x0 * x2 * y2;
             Rd(978) = y3 * x0 * x2 * b2;

             Rd(979) = y3 * x0 * a2 * y2;
             Rd(980) = y3 * x0 * a2 * b2;

             Rd(981) = y3 * x0 * y2 * b2;

             Rd(982) = y3 * x2 * a2 * y2;
             Rd(983) = y3 * x2 * a2 * b2;

             Rd(984) = y3 * x2 * y2 * b2;

             Rd(985) = y3 * a2 * y2 * b2;

             Rd(986) = b3 * x0 * x2 * a2;
             Rd(987) = b3 * x0 * x2 * y2;
             Rd(988) = b3 * x0 * x2 * b2;

             Rd(989) = b3 * x0 * a2 * y2;
             Rd(990) = b3 * x0 * a2 * b2;

             Rd(991) = b3 * x0 * y2 * b2;

             Rd(992) = b3 * x2 * a2 * y2;
             Rd(993) = b3 * x2 * a2 * b2;

             Rd(994) = b3 * x2 * y2 * b2;

             Rd(995) = b3 * a2 * y2 * b2;

             Rd(996) = x0 * x2 * a2 * y2;
             Rd(997) = x0 * x2 * a2 * b2;

             Rd(998) = x0 * x2 * y2 * b2;

             Rd(999) = x0 * a2 * y2 * b2;

             Rd(1000) = x2 * a2 * y2 * b2;
//
		 }else if(fOrder == 4 && fUseS0Y) {
	 	 const TSRPPACPlaneData *const s0ppacy = static_cast<TSRPPACPlaneData*>((*fS0PPACY)->At(0));
		 if (!s0ppacy) return;
         Double_t y0i = s0ppacy->GetPosition();
         Double_t y0 = (y0i - 41) * 0.1; 

         Rd(0)  = 1.; 
         Rd(1)  = t;
         Rd(2)  = x3;
         Rd(3)  = a3;
         Rd(4)  = y3;
         Rd(5)  = b3;
         Rd(6)  = x0;
         Rd(7)  = x2;
         Rd(8)  = a2;
         Rd(9)  = y2;
         Rd(10) = b2;
         Rd(11) = y0;
         Rd(12) = t * t;
         Rd(13) = x3 * x3;
         Rd(14) = a3 * a3;
         Rd(15) = y3 * y3;
         Rd(16) = b3 * b3;
         Rd(17) = x0 * x0;
         Rd(18) = x2 * x2;
         Rd(19) = a2 * a2;
         Rd(20) = y2 * y2;
         Rd(21) = b2 * b2;
         Rd(22) = y0 * y0;
         Rd(23) = t * x3;
         Rd(24) = t * a3;
         Rd(25) = t * y3;
         Rd(26) = t * b3;
         Rd(27) = t * x0;
         Rd(28) = t * x2;
         Rd(29) = t * a2;
         Rd(30) = t * y2;
         Rd(31) = t * b2;
         Rd(32) = t * y0;
         Rd(33) = x3 * a3;
         Rd(34) = x3 * y3;
         Rd(35) = x3 * b3;
         Rd(36) = x3 * x0;
         Rd(37) = x3 * x2;
         Rd(38) = x3 * a2;
         Rd(39) = x3 * y2;
         Rd(40) = x3 * b2;
         Rd(41) = x3 * y0;
         Rd(42) = a3 * y3;
         Rd(43) = a3 * b3;
         Rd(44) = a3 * x0;
         Rd(45) = a3 * x2;
         Rd(46) = a3 * a2;
         Rd(47) = a3 * y2;
         Rd(48) = a3 * b2;
         Rd(49) = a3 * y0;
         Rd(50) = y3 * b3;
         Rd(51) = y3 * x0;
         Rd(52) = y3 * x2;
         Rd(53) = y3 * a2;
         Rd(54) = y3 * y2;
         Rd(55) = y3 * b2;
         Rd(56) = y3 * y0;
         Rd(57) = b3 * x0;
         Rd(58) = b3 * x2;
         Rd(59) = b3 * a2;
         Rd(60) = b3 * y2;
         Rd(61) = b3 * b2;
         Rd(62) = b3 * y0;
         Rd(63) = x0 * x2;
         Rd(64) = x0 * a2;
         Rd(65) = x0 * y2;
         Rd(66) = x0 * b2;
         Rd(67) = x0 * y0;
         Rd(68) = x2 * a2;
         Rd(69) = x2 * y2;
         Rd(70) = x2 * b2;
         Rd(71) = x2 * y0;
         Rd(72) = a2 * y2;
         Rd(73) = a2 * b2;
         Rd(74) = a2 * y0;
         Rd(75) = y2 * b2;
         Rd(76) = y2 * y0;
         Rd(77) = b2 * y0;
         Rd(78) = t * t * t;
         Rd(79) = x3 * x3 * x3;
         Rd(80) = a3 * a3 * a3;
         Rd(81) = y3 * y3 * y3;
         Rd(82) = b3 * b3 * b3;
         Rd(83) = x0 * x0 * x0;
         Rd(84) = x2 * x2 * x2;
         Rd(85) = a2 * a2 * a2;
         Rd(86) = y2 * y2 * y2;
         Rd(87) = b2 * b2 * b2;
         Rd(88) = y0 * y0 * y0;
         Rd(89) = t * t * x3;
         Rd(90) = t * t * a3;
         Rd(91) = t * t * y3;
         Rd(92) = t * t * b3;
         Rd(93) = t * t * x0;
         Rd(94) = t * t * x2;
         Rd(95) = t * t * a2;
         Rd(96) = t * t * y2;
         Rd(97) = t * t * b2;
         Rd(98) = t * t * y0;
         Rd(99) = x3 * x3 * t;
         Rd(100) = x3 * x3 * a3;
         Rd(101) = x3 * x3 * y3;
         Rd(102) = x3 * x3 * b3;
         Rd(103) = x3 * x3 * x0;
         Rd(104) = x3 * x3 * x2;
         Rd(105) = x3 * x3 * a2;
         Rd(106) = x3 * x3 * y2;
         Rd(107) = x3 * x3 * b2;
         Rd(108) = x3 * x3 * y0;
         Rd(109) = a3 * a3 * t;
         Rd(110) = a3 * a3 * x3;
         Rd(111) = a3 * a3 * y3;
         Rd(112) = a3 * a3 * b3;
         Rd(113) = a3 * a3 * x0;
         Rd(114) = a3 * a3 * x2;
         Rd(115) = a3 * a3 * a2;
         Rd(116) = a3 * a3 * y2;
         Rd(117) = a3 * a3 * b2;
         Rd(118) = a3 * a3 * y0;
         Rd(119) = y3 * y3 * t;
         Rd(120) = y3 * y3 * x3;
         Rd(121) = y3 * y3 * a3;
         Rd(122) = y3 * y3 * b3;
         Rd(123) = y3 * y3 * x0;
         Rd(124) = y3 * y3 * x2;
         Rd(125) = y3 * y3 * a2;
         Rd(126) = y3 * y3 * y2;
         Rd(127) = y3 * y3 * b2;
         Rd(128) = y3 * y3 * y0;
         Rd(129) = b3 * b3 * t;
         Rd(130) = b3 * b3 * x3;
         Rd(131) = b3 * b3 * a3;
         Rd(132) = b3 * b3 * y3;
         Rd(133) = b3 * b3 * x0;
         Rd(134) = b3 * b3 * x2;
         Rd(135) = b3 * b3 * a2;
         Rd(136) = b3 * b3 * y2;
         Rd(137) = b3 * b3 * b2;
         Rd(138) = b3 * b3 * y0;
         Rd(139) = x0 * x0 * t;
         Rd(140) = x0 * x0 * x3;
         Rd(141) = x0 * x0 * a3;
         Rd(142) = x0 * x0 * y3;
         Rd(143) = x0 * x0 * b3;
         Rd(144) = x0 * x0 * x2;
         Rd(145) = x0 * x0 * a2;
         Rd(146) = x0 * x0 * y2;
         Rd(147) = x0 * x0 * b2;
         Rd(148) = x0 * x0 * y0;
         Rd(149) = x2 * x2 * t;
         Rd(150) = x2 * x2 * x3;
         Rd(151) = x2 * x2 * a3;
         Rd(152) = x2 * x2 * y3;
         Rd(153) = x2 * x2 * b3;
         Rd(154) = x2 * x2 * x0;
         Rd(155) = x2 * x2 * a2;
         Rd(156) = x2 * x2 * y2;
         Rd(157) = x2 * x2 * b2;
         Rd(158) = x2 * x2 * y0;
         Rd(159) = a2 * a2 * t;
         Rd(160) = a2 * a2 * x3;
         Rd(161) = a2 * a2 * a3;
         Rd(162) = a2 * a2 * y3;
         Rd(163) = a2 * a2 * b3;
         Rd(164) = a2 * a2 * x0;
         Rd(165) = a2 * a2 * x2;
         Rd(166) = a2 * a2 * y2;
         Rd(167) = a2 * a2 * b2;
         Rd(168) = a2 * a2 * y0;
         Rd(169) = y2 * y2 * t;
         Rd(170) = y2 * y2 * x3;
         Rd(171) = y2 * y2 * a3;
         Rd(172) = y2 * y2 * y3;
         Rd(173) = y2 * y2 * b3;
         Rd(174) = y2 * y2 * x0;
         Rd(175) = y2 * y2 * x2;
         Rd(176) = y2 * y2 * a2;
         Rd(177) = y2 * y2 * b2;
         Rd(178) = y2 * y2 * y0;
         Rd(179) = b2 * b2 * t;
         Rd(180) = b2 * b2 * x3;
         Rd(181) = b2 * b2 * a3;
         Rd(182) = b2 * b2 * y3;
         Rd(183) = b2 * b2 * b3;
         Rd(184) = b2 * b2 * x0;
         Rd(185) = b2 * b2 * x2;
         Rd(186) = b2 * b2 * a2;
         Rd(187) = b2 * b2 * y2;
         Rd(188) = b2 * b2 * y0;
         Rd(189) = y0 * y0 * t;
         Rd(190) = y0 * y0 * x3;
         Rd(192) = y0 * y0 * a3;
         Rd(193) = y0 * y0 * y3;
         Rd(194) = y0 * y0 * b3;
         Rd(195) = y0 * y0 * x0;
         Rd(196) = y0 * y0 * x2;
         Rd(197) = y0 * y0 * a2;
         Rd(198) = y0 * y0 * y2;
         Rd(199) = y0 * y0 * b2;
         Rd(200) = t * x3 * a3;
         Rd(201) = t * x3 * y3;
         Rd(202) = t * x3 * b3;
         Rd(203) = t * x3 * x0;
         Rd(204) = t * x3 * x2;
         Rd(205) = t * x3 * a2;
         Rd(206) = t * x3 * y2;
         Rd(207) = t * x3 * b2;
         Rd(208) = t * x3 * y0;
         Rd(209) = t * a3 * y3;
         Rd(210) = t * a3 * b3;
         Rd(211) = t * a3 * x0;
         Rd(212) = t * a3 * x2;
         Rd(213) = t * a3 * a2;
         Rd(214) = t * a3 * y2;
         Rd(215) = t * a3 * b2;
         Rd(216) = t * a3 * y0;
         Rd(217) = t * y3 * b3;
         Rd(217) = t * y3 * x0;
         Rd(218) = t * y3 * x2;
         Rd(219) = t * y3 * a2;
         Rd(220) = t * y3 * y2;
         Rd(221) = t * y3 * b2;
         Rd(222) = t * y3 * y0;
         Rd(223) = t * b3 * x0;
         Rd(224) = t * b3 * x2;
         Rd(225) = t * b3 * a2;
         Rd(226) = t * b3 * y2;
         Rd(227) = t * b3 * b2;
         Rd(228) = t * b3 * y0;
         Rd(229) = t * x0 * x2;
         Rd(230) = t * x0 * a2;
         Rd(231) = t * x0 * y2;
         Rd(232) = t * x0 * b2;
         Rd(233) = t * x0 * y0;
         Rd(234) = t * x2 * a2;
         Rd(235) = t * x2 * y2;
         Rd(236) = t * x2 * b2;
         Rd(237) = t * x2 * y0;
         Rd(238) = t * a2 * y2;
         Rd(239) = t * a2 * b2;
         Rd(240) = t * a2 * y0;
         Rd(241) = t * y2 * b2;
         Rd(242) = t * y2 * y0;
         Rd(243) = t * b2 * y0;
         Rd(244) = x3 * a3 * y3;
         Rd(245) = x3 * a3 * b3;
         Rd(246) = x3 * a3 * x0;
         Rd(247) = x3 * a3 * x2;
         Rd(248) = x3 * a3 * a2;
         Rd(249) = x3 * a3 * y2;
         Rd(250) = x3 * a3 * b2;
         Rd(251) = x3 * a3 * y0;
         Rd(252) = x3 * y3 * b3;
         Rd(253) = x3 * y3 * x0;
         Rd(254) = x3 * y3 * x2;
         Rd(255) = x3 * y3 * a2;
         Rd(256) = x3 * y3 * y2;
         Rd(257) = x3 * y3 * b2;
         Rd(258) = x3 * y3 * y0;
         Rd(259) = x3 * b3 * x0;
         Rd(260) = x3 * b3 * x2;
         Rd(261) = x3 * b3 * a2;
         Rd(262) = x3 * b3 * y2;
         Rd(263) = x3 * b3 * b2;
         Rd(264) = x3 * b3 * y0;
         Rd(265) = x3 * x0 * x2;
         Rd(266) = x3 * x0 * a2;
         Rd(267) = x3 * x0 * y2;
         Rd(268) = x3 * x0 * b2;
         Rd(269) = x3 * x0 * y0;
         Rd(270) = x3 * x2 * a2;
         Rd(271) = x3 * x2 * y2;
         Rd(272) = x3 * x2 * b2;
         Rd(273) = x3 * x2 * y0;
         Rd(274) = x3 * a2 * y2;
         Rd(275) = x3 * a2 * b2;
         Rd(276) = x3 * a2 * y0;
         Rd(277) = x3 * y2 * b2;
         Rd(278) = x3 * y2 * y0;
         Rd(279) = x3 * b2 * y0;
         Rd(280) = a3 * y3 * b3;
         Rd(281) = a3 * y3 * x0;
         Rd(282) = a3 * y3 * x2;
         Rd(283) = a3 * y3 * a2;
         Rd(284) = a3 * y3 * y2;
         Rd(285) = a3 * y3 * b2;
         Rd(286) = a3 * y3 * y0;
         Rd(287) = a3 * b3 * x0;
         Rd(288) = a3 * b3 * x2;
         Rd(289) = a3 * b3 * a2;
         Rd(290) = a3 * b3 * y2;
         Rd(291) = a3 * b3 * b2;
         Rd(292) = a3 * b3 * y0;
         Rd(293) = a3 * x0 * x2;
         Rd(294) = a3 * x0 * a2;
         Rd(295) = a3 * x0 * y2;
         Rd(296) = a3 * x0 * b2;
         Rd(297) = a3 * x0 * y0;
         Rd(298) = a3 * x2 * a2;
         Rd(299) = a3 * x2 * y2;
         Rd(300) = a3 * x2 * b2;
         Rd(301) = a3 * x2 * y0;
         Rd(302) = a3 * a2 * y2;
         Rd(303) = a3 * a2 * b2;
         Rd(304) = a3 * a2 * y0;
         Rd(305) = a3 * y2 * b2;
         Rd(306) = a3 * y2 * y0;
         Rd(307) = a3 * b2 * y0;
         Rd(308) = y3 * b3 * x0;
         Rd(309) = y3 * b3 * x2;
         Rd(310) = y3 * b3 * a2;
         Rd(311) = y3 * b3 * y2;
         Rd(312) = y3 * b3 * b2;
         Rd(313) = y3 * b3 * y0;
         Rd(314) = y3 * x0 * x2;
         Rd(315) = y3 * x0 * a2;
         Rd(316) = y3 * x0 * y2;
         Rd(317) = y3 * x0 * b2;
         Rd(318) = y3 * x0 * y0;
         Rd(319) = y3 * x2 * a2;
         Rd(320) = y3 * x2 * y2;
         Rd(321) = y3 * x2 * b2;
         Rd(322) = y3 * x2 * y0;
         Rd(323) = y3 * a2 * y2;
         Rd(324) = y3 * a2 * b2;
         Rd(325) = y3 * a2 * y0;
         Rd(326) = y3 * y2 * b2;
         Rd(327) = y3 * y2 * y0;
         Rd(328) = y3 * b2 * y0;
         Rd(329) = b3 * x0 * x2;
         Rd(330) = b3 * x0 * a2;
         Rd(331) = b3 * x0 * y2;
         Rd(332) = b3 * x0 * b2;
         Rd(333) = b3 * x0 * y0;
         Rd(334) = b3 * x2 * a2;
         Rd(335) = b3 * x2 * y2;
         Rd(336) = b3 * x2 * b2;
         Rd(337) = b3 * x2 * y0;
         Rd(338) = b3 * a2 * y2;
         Rd(339) = b3 * a2 * b2;
         Rd(340) = b3 * a2 * y0;
         Rd(341) = b3 * y2 * b2;
         Rd(342) = b3 * y2 * y0;
         Rd(343) = b3 * b2 * y0;
         Rd(344) = x0 * x2 * a2;
         Rd(345) = x0 * x2 * y2;
         Rd(346) = x0 * x2 * b2;
         Rd(347) = x0 * x2 * y0;
         Rd(348) = x0 * a2 * y2;
         Rd(349) = x0 * a2 * b2;
         Rd(350) = x0 * a2 * y0;
         Rd(351) = x0 * y2 * b2;
         Rd(352) = x0 * y2 * y0;
         Rd(353) = x0 * b2 * y0;
         Rd(354) = x2 * a2 * y2;
         Rd(355) = x2 * a2 * b2;
         Rd(356) = x2 * a2 * y0;
         Rd(357) = x2 * y2 * b2;
         Rd(358) = x2 * y2 * y0;
         Rd(359) = x2 * b2 * y0;
         Rd(360) = a2 * y2 * b2;
         Rd(361) = a2 * y2 * y0;
         Rd(362) = a2 * b2 * y0;
         Rd(363) = y2 * b2 * y0;
         Rd(364) = t * t * t * t;
         Rd(365) = x3 * x3 * x3 * x3;
         Rd(366) = a3 * a3 * a3 * a3;
         Rd(367) = y3 * y3 * y3 * y3;
         Rd(368) = b3 * b3 * b3 * b3;
         Rd(369) = x0 * x0 * x0 * x0;
         Rd(370) = x2 * x2 * x2 * x2;
         Rd(371) = a2 * a2 * a2 * a2;
         Rd(372) = y2 * y2 * y2 * y2;
         Rd(373) = b2 * b2 * b2 * b2;
         Rd(374) = y0 * y0 * y0 * y0;
         Rd(375) = t * t * t * x3;
         Rd(376) = t * t * t * a3;
         Rd(377) = t * t * t * y3;
         Rd(378) = t * t * t * b3;
         Rd(379) = t * t * t * x0;
         Rd(380) = t * t * t * x2;
         Rd(381) = t * t * t * a2;
         Rd(382) = t * t * t * y2;
         Rd(383) = t * t * t * b2;
         Rd(384) = t * t * t * y0;
         Rd(385) = x3 * x3 * x3 * t;
         Rd(386) = x3 * x3 * x3 * a3;
         Rd(387) = x3 * x3 * x3 * y3;
         Rd(388) = x3 * x3 * x3 * b3;
         Rd(389) = x3 * x3 * x3 * x0;
         Rd(390) = x3 * x3 * x3 * x2;
         Rd(391) = x3 * x3 * x3 * a2;
         Rd(392) = x3 * x3 * x3 * y2;
         Rd(393) = x3 * x3 * x3 * b2;
         Rd(394) = x3 * x3 * x3 * y0;
         Rd(395) = a3 * a3 * a3 * t;
         Rd(396) = a3 * a3 * a3 * x3;
         Rd(397) = a3 * a3 * a3 * y3;
         Rd(398) = a3 * a3 * a3 * b3;
         Rd(399) = a3 * a3 * a3 * x0;
         Rd(400) = a3 * a3 * a3 * x2;
         Rd(401) = a3 * a3 * a3 * a2;
         Rd(402) = a3 * a3 * a3 * y2;
         Rd(403) = a3 * a3 * a3 * b2;
         Rd(404) = a3 * a3 * a3 * y0;
         Rd(405) = y3 * y3 * y3 * t;
         Rd(406) = y3 * y3 * y3 * x3;
         Rd(407) = y3 * y3 * y3 * a3;
         Rd(408) = y3 * y3 * y3 * b3;
         Rd(409) = y3 * y3 * y3 * x0;
         Rd(410) = y3 * y3 * y3 * x2;
         Rd(411) = y3 * y3 * y3 * a2;
         Rd(412) = y3 * y3 * y3 * y2;
         Rd(413) = y3 * y3 * y3 * b2;
         Rd(414) = y3 * y3 * y3 * y0;
         Rd(415) = b3 * b3 * b3 * t;
         Rd(416) = b3 * b3 * b3 * x3;
         Rd(417) = b3 * b3 * b3 * a3;
         Rd(418) = b3 * b3 * b3 * y3;
         Rd(419) = b3 * b3 * b3 * x0;
         Rd(420) = b3 * b3 * b3 * x2;
         Rd(421) = b3 * b3 * b3 * a2;
         Rd(422) = b3 * b3 * b3 * y2;
         Rd(423) = b3 * b3 * b3 * b2;
         Rd(424) = b3 * b3 * b3 * y0;
         Rd(425) = x0 * x0 * x0 * t;
         Rd(426) = x0 * x0 * x0 * x3;
         Rd(427) = x0 * x0 * x0 * a3;
         Rd(428) = x0 * x0 * x0 * y3;
         Rd(429) = x0 * x0 * x0 * b3;
         Rd(430) = x0 * x0 * x0 * x2;
         Rd(431) = x0 * x0 * x0 * a2;
         Rd(432) = x0 * x0 * x0 * y2;
         Rd(433) = x0 * x0 * x0 * b2;
         Rd(434) = x0 * x0 * x0 * y0;
         Rd(435) = x2 * x2 * x2 * t;
         Rd(436) = x2 * x2 * x2 * x3;
         Rd(437) = x2 * x2 * x2 * a3;
         Rd(438) = x2 * x2 * x2 * y3;
         Rd(439) = x2 * x2 * x2 * b3;
         Rd(440) = x2 * x2 * x2 * x0;
         Rd(441) = x2 * x2 * x2 * a2;
         Rd(442) = x2 * x2 * x2 * y2;
         Rd(443) = x2 * x2 * x2 * b2;
         Rd(444) = x2 * x2 * x2 * y0;
         Rd(445) = a2 * a2 * a2 * t;
         Rd(446) = a2 * a2 * a2 * x3;
         Rd(447) = a2 * a2 * a2 * a3;
         Rd(448) = a2 * a2 * a2 * y3;
         Rd(449) = a2 * a2 * a2 * b3;
         Rd(450) = a2 * a2 * a2 * x0;
         Rd(451) = a2 * a2 * a2 * x2;
         Rd(452) = a2 * a2 * a2 * y2;
         Rd(453) = a2 * a2 * a2 * b2;
         Rd(454) = a2 * a2 * a2 * y0;
         Rd(455) = y2 * y2 * y2 * t;
         Rd(456) = y2 * y2 * y2 * x3;
         Rd(457) = y2 * y2 * y2 * a3;
         Rd(458) = y2 * y2 * y2 * y3;
         Rd(459) = y2 * y2 * y2 * b3;
         Rd(460) = y2 * y2 * y2 * x0;
         Rd(461) = y2 * y2 * y2 * x2;
         Rd(462) = y2 * y2 * y2 * a2;
         Rd(463) = y2 * y2 * y2 * b2;
         Rd(464) = y2 * y2 * y2 * y0;
         Rd(465) = b2 * b2 * b2 * t;
         Rd(466) = b2 * b2 * b2 * x3;
         Rd(467) = b2 * b2 * b2 * a3;
         Rd(468) = b2 * b2 * b2 * y3;
         Rd(469) = b2 * b2 * b2 * b3;
         Rd(470) = b2 * b2 * b2 * x0;
         Rd(471) = b2 * b2 * b2 * x2;
         Rd(472) = b2 * b2 * b2 * a2;
         Rd(473) = b2 * b2 * b2 * y2;
         Rd(474) = b2 * b2 * b2 * y0;
         Rd(475) = y0 * y0 * y0 * t;
         Rd(476) = y0 * y0 * y0 * x3;
         Rd(477) = y0 * y0 * y0 * a3;
         Rd(478) = y0 * y0 * y0 * y3;
         Rd(479) = y0 * y0 * y0 * b3;
         Rd(480) = y0 * y0 * y0 * x0;
         Rd(481) = y0 * y0 * y0 * x2;
         Rd(482) = y0 * y0 * y0 * a2;
         Rd(483) = y0 * y0 * y0 * y2;
         Rd(484) = y0 * y0 * y0 * b2;
         Rd(485) = t * t * x3 * x3;
         Rd(486) = t * t * a3 * a3;
         Rd(487) = t * t * y3 * y3;
         Rd(488) = t * t * b3 * b3;
         Rd(489) = t * t * x0 * x0;
         Rd(490) = t * t * x2 * x2;
         Rd(491) = t * t * a2 * a2;
         Rd(492) = t * t * y2 * y2;
         Rd(493) = t * t * b2 * b2;
         Rd(494) = t * t * y0 * y0;
         Rd(495) = x3 * x3 * a3 * a3;
         Rd(496) = x3 * x3 * y3 * y3;
         Rd(497) = x3 * x3 * b3 * b3;
         Rd(498) = x3 * x3 * x0 * x0;
         Rd(499) = x3 * x3 * x2 * x2;
         Rd(500) = x3 * x3 * a2 * a2;
         Rd(501) = x3 * x3 * y2 * y2;
         Rd(502) = x3 * x3 * b2 * b2;
         Rd(503) = x3 * x3 * y0 * y0;
         Rd(504) = a3 * a3 * y3 * y3;
         Rd(505) = a3 * a3 * b3 * b3;
         Rd(506) = a3 * a3 * x0 * x0;
         Rd(507) = a3 * a3 * x2 * x2;
         Rd(508) = a3 * a3 * a2 * a2;
         Rd(509) = a3 * a3 * y2 * y2;
         Rd(510) = a3 * a3 * b2 * b2;
         Rd(511) = a3 * a3 * y0 * y0;
         Rd(512) = y3 * y3 * b3 * b3;
         Rd(513) = y3 * y3 * x0 * x0;
         Rd(514) = y3 * y3 * x2 * x2;
         Rd(515) = y3 * y3 * a2 * a2;
         Rd(516) = y3 * y3 * y2 * y2;
         Rd(517) = y3 * y3 * b2 * b2;
         Rd(518) = y3 * y3 * y0 * y0;
         Rd(519) = b3 * b3 * x0 * x0;
         Rd(520) = b3 * b3 * x2 * x2;
         Rd(521) = b3 * b3 * a2 * a2;
         Rd(522) = b3 * b3 * y2 * y2;
         Rd(523) = b3 * b3 * b2 * b2;
         Rd(524) = b3 * b3 * y0 * y0;
         Rd(525) = x0 * x0 * x2 * x2;
         Rd(526) = x0 * x0 * a2 * a2;
         Rd(527) = x0 * x0 * y2 * y2;
         Rd(528) = x0 * x0 * b2 * b2;
         Rd(529) = x0 * x0 * y0 * y0;
         Rd(530) = x2 * x2 * a2 * a2;
         Rd(531) = x2 * x2 * y2 * y2;
         Rd(532) = x2 * x2 * b2 * b2;
         Rd(533) = x2 * x2 * y0 * y0;
         Rd(534) = a2 * a2 * y2 * y2;
         Rd(535) = a2 * a2 * b2 * b2;
         Rd(536) = a2 * a2 * y0 * y0;
         Rd(537) = y2 * y2 * b2 * b2;
         Rd(538) = y2 * y2 * y0 * y0;
         Rd(539) = b2 * b2 * y0 * y0;
         Rd(540) = t * t * x3 * a3;
         Rd(541) = t * t * x3 * y3;
         Rd(542) = t * t * x3 * b3;
         Rd(543) = t * t * x3 * x0;
         Rd(544) = t * t * x3 * x2;
         Rd(545) = t * t * x3 * a2;
         Rd(546) = t * t * x3 * y2;
         Rd(547) = t * t * x3 * b2;
         Rd(548) = t * t * x3 * y0;
         Rd(549) = t * t * a3 * y3;
         Rd(550) = t * t * a3 * b3;
         Rd(551) = t * t * a3 * x0;
         Rd(552) = t * t * a3 * x2;
         Rd(553) = t * t * a3 * a2;
         Rd(554) = t * t * a3 * y2;
         Rd(555) = t * t * a3 * b2;
         Rd(556) = t * t * a3 * y0;
         Rd(557) = t * t * y3 * b3;
         Rd(558) = t * t * y3 * x0;
         Rd(559) = t * t * y3 * x2;
         Rd(560) = t * t * y3 * a2;
         Rd(561) = t * t * y3 * y2;
         Rd(562) = t * t * y3 * b2;
         Rd(563) = t * t * y3 * y0;
         Rd(564) = t * t * b3 * x0;
         Rd(565) = t * t * b3 * x2;
         Rd(566) = t * t * b3 * a2;
         Rd(567) = t * t * b3 * y2;
         Rd(568) = t * t * b3 * b2;
         Rd(569) = t * t * b3 * y0;
         Rd(570) = t * t * x0 * x2;
         Rd(571) = t * t * x0 * a2;
         Rd(572) = t * t * x0 * y2;
         Rd(573) = t * t * x0 * b2;
         Rd(574) = t * t * x0 * y0;
         Rd(575) = t * t * x2 * a2;
         Rd(576) = t * t * x2 * y2;
         Rd(577) = t * t * x2 * b2;
         Rd(578) = t * t * x2 * y0;
         Rd(579) = t * t * a2 * y2;
         Rd(580) = t * t * a2 * b2;
         Rd(581) = t * t * a2 * y0;
         Rd(582) = t * t * y2 * b2;
         Rd(583) = t * t * y2 * y0;
         Rd(584) = t * t * b2 * y0;
         Rd(585) = x3 * x3 * t * a3;
         Rd(586) = x3 * x3 * t * y3;
         Rd(587) = x3 * x3 * t * b3;
         Rd(588) = x3 * x3 * t * x0;
         Rd(589) = x3 * x3 * t * x2;
         Rd(590) = x3 * x3 * t * a2;
         Rd(591) = x3 * x3 * t * y2;
         Rd(592) = x3 * x3 * t * b2;
         Rd(593) = x3 * x3 * t * y0;
         Rd(594) = x3 * x3 * a3 * y3;
         Rd(595) = x3 * x3 * a3 * b3;
         Rd(596) = x3 * x3 * a3 * x0;
         Rd(597) = x3 * x3 * a3 * x2;
         Rd(598) = x3 * x3 * a3 * a2;
         Rd(599) = x3 * x3 * a3 * y2;
         Rd(600) = x3 * x3 * a3 * b2;
         Rd(601) = x3 * x3 * a3 * y0;
         Rd(602) = x3 * x3 * y3 * b3;
         Rd(603) = x3 * x3 * y3 * x0;
         Rd(604) = x3 * x3 * y3 * x2;
         Rd(605) = x3 * x3 * y3 * a2;
         Rd(606) = x3 * x3 * y3 * y2;
         Rd(607) = x3 * x3 * y3 * b2;
         Rd(608) = x3 * x3 * y3 * y0;
         Rd(609) = x3 * x3 * b3 * x0;
         Rd(610) = x3 * x3 * b3 * x2;
         Rd(611) = x3 * x3 * b3 * a2;
         Rd(612) = x3 * x3 * b3 * y2;
         Rd(613) = x3 * x3 * b3 * b2;
         Rd(614) = x3 * x3 * b3 * y0;
         Rd(615) = x3 * x3 * x0 * x2;
         Rd(616) = x3 * x3 * x0 * a2;
         Rd(617) = x3 * x3 * x0 * y2;
         Rd(618) = x3 * x3 * x0 * b2;
         Rd(619) = x3 * x3 * x0 * y0;
         Rd(620) = x3 * x3 * x2 * a2;
         Rd(621) = x3 * x3 * x2 * y2;
         Rd(622) = x3 * x3 * x2 * b2;
         Rd(623) = x3 * x3 * x2 * y0;
         Rd(624) = x3 * x3 * a2 * y2;
         Rd(625) = x3 * x3 * a2 * b2;
         Rd(626) = x3 * x3 * a2 * y0;
         Rd(627) = x3 * x3 * y2 * b2;
         Rd(628) = x3 * x3 * y2 * y0;
         Rd(629) = x3 * x3 * b2 * y0;
         Rd(630) = a3 * a3 * t * x3;
         Rd(631) = a3 * a3 * t * y3;
         Rd(632) = a3 * a3 * t * b3;
         Rd(633) = a3 * a3 * t * x0;
         Rd(634) = a3 * a3 * t * x2;
         Rd(635) = a3 * a3 * t * a2;
         Rd(636) = a3 * a3 * t * y2;
         Rd(637) = a3 * a3 * t * b2;
         Rd(638) = a3 * a3 * t * y0;
         Rd(639) = a3 * a3 * x3 * y3;
         Rd(640) = a3 * a3 * x3 * b3;
         Rd(641) = a3 * a3 * x3 * x0;
         Rd(642) = a3 * a3 * x3 * x2;
         Rd(643) = a3 * a3 * x3 * a2;
         Rd(644) = a3 * a3 * x3 * y2;
         Rd(645) = a3 * a3 * x3 * b2;
         Rd(646) = a3 * a3 * x3 * y0;
         Rd(647) = a3 * a3 * y3 * b3;
         Rd(648) = a3 * a3 * y3 * x0;
         Rd(649) = a3 * a3 * y3 * x2;
         Rd(650) = a3 * a3 * y3 * a2;
         Rd(651) = a3 * a3 * y3 * y2;
         Rd(652) = a3 * a3 * y3 * b2;
         Rd(653) = a3 * a3 * y3 * y0;
         Rd(654) = a3 * a3 * b3 * x0;
         Rd(655) = a3 * a3 * b3 * x2;
         Rd(656) = a3 * a3 * b3 * a2;
         Rd(657) = a3 * a3 * b3 * y2;
         Rd(658) = a3 * a3 * b3 * b2;
         Rd(659) = a3 * a3 * b3 * y0;
         Rd(660) = a3 * a3 * x0 * x2;
         Rd(661) = a3 * a3 * x0 * a2;
         Rd(662) = a3 * a3 * x0 * y2;
         Rd(663) = a3 * a3 * x0 * b2;
         Rd(664) = a3 * a3 * x0 * y0;
         Rd(665) = a3 * a3 * x2 * a2;
         Rd(666) = a3 * a3 * x2 * y2;
         Rd(667) = a3 * a3 * x2 * b2;
         Rd(668) = a3 * a3 * x2 * y0;
         Rd(669) = a3 * a3 * a2 * y2;
         Rd(670) = a3 * a3 * a2 * b2;
         Rd(671) = a3 * a3 * a2 * y0;
         Rd(672) = a3 * a3 * y2 * b2;
         Rd(673) = a3 * a3 * y2 * y0;
         Rd(674) = a3 * a3 * b2 * y0;
         Rd(675) = y3 * y3 * t * x3;
         Rd(676) = y3 * y3 * t * a3;
         Rd(677) = y3 * y3 * t * b3;
         Rd(678) = y3 * y3 * t * x0;
         Rd(679) = y3 * y3 * t * x2;
         Rd(680) = y3 * y3 * t * a2;
         Rd(681) = y3 * y3 * t * y2;
         Rd(682) = y3 * y3 * t * b2;
         Rd(683) = y3 * y3 * t * y0;
         Rd(684) = y3 * y3 * x3 * a3;
         Rd(685) = y3 * y3 * x3 * b3;
         Rd(686) = y3 * y3 * x3 * x0;
         Rd(687) = y3 * y3 * x3 * x2;
         Rd(688) = y3 * y3 * x3 * a2;
         Rd(689) = y3 * y3 * x3 * y2;
         Rd(691) = y3 * y3 * x3 * b2;
         Rd(692) = y3 * y3 * x3 * y0;
         Rd(694) = y3 * y3 * a3 * b3;
         Rd(695) = y3 * y3 * a3 * x0;
         Rd(696) = y3 * y3 * a3 * x2;
         Rd(697) = y3 * y3 * a3 * a2;
         Rd(698) = y3 * y3 * a3 * y2;
         Rd(699) = y3 * y3 * a3 * b2;
         Rd(700) = y3 * y3 * a3 * y0;
         Rd(701) = y3 * y3 * b3 * x0;
         Rd(702) = y3 * y3 * b3 * x2;
         Rd(703) = y3 * y3 * b3 * a2;
         Rd(704) = y3 * y3 * b3 * y2;
         Rd(705) = y3 * y3 * b3 * b2;
         Rd(706) = y3 * y3 * b3 * y0;
         Rd(707) = y3 * y3 * x0 * x2;
         Rd(708) = y3 * y3 * x0 * a2;
         Rd(709) = y3 * y3 * x0 * y2;
         Rd(710) = y3 * y3 * x0 * b2;
         Rd(712) = y3 * y3 * x0 * y0;
         Rd(713) = y3 * y3 * x2 * a2;
         Rd(714) = y3 * y3 * x2 * y2;
         Rd(715) = y3 * y3 * x2 * b2;
         Rd(716) = y3 * y3 * x2 * y0;
         Rd(717) = y3 * y3 * a2 * y2;
         Rd(718) = y3 * y3 * a2 * b2;
         Rd(719) = y3 * y3 * a2 * y0;
         Rd(720) = y3 * y3 * y2 * b2;
         Rd(721) = y3 * y3 * y2 * y0;
         Rd(722) = y3 * y3 * b2 * y0;
         Rd(723) = b3 * b3 * t * x3;
         Rd(724) = b3 * b3 * t * a3;
         Rd(725) = b3 * b3 * t * y3;
         Rd(726) = b3 * b3 * t * x0;
         Rd(727) = b3 * b3 * t * x2;
         Rd(728) = b3 * b3 * t * a2;
         Rd(729) = b3 * b3 * t * y2;
         Rd(730) = b3 * b3 * t * b2;
         Rd(731) = b3 * b3 * t * y0;
         Rd(732) = b3 * b3 * x3 * a3;
         Rd(733) = b3 * b3 * x3 * y3;
         Rd(734) = b3 * b3 * x3 * x0;
         Rd(735) = b3 * b3 * x3 * x2;
         Rd(736) = b3 * b3 * x3 * a2;
         Rd(737) = b3 * b3 * x3 * y2;
         Rd(734) = b3 * b3 * x3 * b2;
         Rd(735) = b3 * b3 * x3 * y0;
         Rd(736) = b3 * b3 * a3 * y3;
         Rd(737) = b3 * b3 * a3 * x0;
         Rd(738) = b3 * b3 * a3 * x2;
         Rd(739) = b3 * b3 * a3 * a2;
         Rd(740) = b3 * b3 * a3 * y2;
         Rd(741) = b3 * b3 * a3 * b2;
         Rd(742) = b3 * b3 * a3 * y0;
         Rd(743) = b3 * b3 * y3 * x0;
         Rd(744) = b3 * b3 * y3 * x2;
         Rd(745) = b3 * b3 * y3 * a2;
         Rd(746) = b3 * b3 * y3 * y2;
         Rd(747) = b3 * b3 * y3 * b2;
         Rd(748) = b3 * b3 * y3 * y0;
         Rd(749) = b3 * b3 * x0 * x2;
         Rd(750) = b3 * b3 * x0 * a2;
         Rd(751) = b3 * b3 * x0 * y2;
         Rd(752) = b3 * b3 * x0 * b2;
         Rd(753) = b3 * b3 * x0 * y0;
         Rd(754) = b3 * b3 * x2 * a2;
         Rd(755) = b3 * b3 * x2 * y2;
         Rd(756) = b3 * b3 * x2 * b2;
         Rd(757) = b3 * b3 * x2 * y0;
         Rd(758) = b3 * b3 * a2 * y2;
         Rd(759) = b3 * b3 * a2 * b2;
         Rd(760) = b3 * b3 * a2 * y0;
         Rd(761) = b3 * b3 * y2 * b2;
         Rd(762) = b3 * b3 * y2 * y0;
         Rd(763) = b3 * b3 * b2 * y0;
         Rd(764) = x0 * x0 * t * x3;
         Rd(765) = x0 * x0 * t * a3;
         Rd(766) = x0 * x0 * t * y3;
         Rd(767) = x0 * x0 * t * b3;
         Rd(768) = x0 * x0 * t * x2;
         Rd(769) = x0 * x0 * t * a2;
         Rd(770) = x0 * x0 * t * y2;
         Rd(771) = x0 * x0 * t * b2;
         Rd(772) = x0 * x0 * t * y0;
         Rd(773) = x0 * x0 * x3 * a3;
         Rd(774) = x0 * x0 * x3 * y3;
         Rd(775) = x0 * x0 * x3 * b3;
         Rd(776) = x0 * x0 * x3 * x2;
         Rd(778) = x0 * x0 * x3 * a2;
         Rd(779) = x0 * x0 * x3 * y2;
         Rd(780) = x0 * x0 * x3 * b2;
         Rd(781) = x0 * x0 * x3 * y0;
         Rd(782) = x0 * x0 * a3 * y3;
         Rd(783) = x0 * x0 * a3 * b3;
         Rd(784) = x0 * x0 * a3 * x2;
         Rd(785) = x0 * x0 * a3 * a2;
         Rd(786) = x0 * x0 * a3 * y2;
         Rd(787) = x0 * x0 * a3 * b2;
         Rd(788) = x0 * x0 * a3 * y0;
         Rd(789) = x0 * x0 * y3 * b3;
         Rd(790) = x0 * x0 * y3 * x2;
         Rd(791) = x0 * x0 * y3 * a2;
         Rd(792) = x0 * x0 * y3 * y2;
         Rd(793) = x0 * x0 * y3 * b2;
         Rd(794) = x0 * x0 * y3 * y0;
         Rd(795) = x0 * x0 * b3 * x2;
         Rd(796) = x0 * x0 * b3 * a2;
         Rd(797) = x0 * x0 * b3 * y2;
         Rd(798) = x0 * x0 * b3 * b2;
         Rd(799) = x0 * x0 * b3 * y0;
         Rd(800) = x0 * x0 * x2 * a2;
         Rd(801) = x0 * x0 * x2 * y2;
         Rd(802) = x0 * x0 * x2 * b2;
         Rd(803) = x0 * x0 * x2 * y0;
         Rd(804) = x0 * x0 * a2 * y2;
         Rd(805) = x0 * x0 * a2 * b2;
         Rd(806) = x0 * x0 * a2 * y0;
         Rd(807) = x0 * x0 * y2 * b2;
         Rd(808) = x0 * x0 * y2 * y0;
         Rd(809) = x0 * x0 * b2 * y0;
         Rd(810) = x2 * x2 * t * x3;
         Rd(811) = x2 * x2 * t * a3;
         Rd(812) = x2 * x2 * t * y3;
         Rd(813) = x2 * x2 * t * b3;
         Rd(814) = x2 * x2 * t * x0;
         Rd(815) = x2 * x2 * t * a2;
         Rd(816) = x2 * x2 * t * y2;
         Rd(817) = x2 * x2 * t * b2;
         Rd(818) = x2 * x2 * t * y0;
         Rd(819) = x2 * x2 * x3 * a3;
         Rd(820) = x2 * x2 * x3 * y3;
         Rd(821) = x2 * x2 * x3 * b3;
         Rd(822) = x2 * x2 * x3 * x0;
         Rd(823) = x2 * x2 * x3 * a2;
         Rd(824) = x2 * x2 * x3 * y2;
         Rd(825) = x2 * x2 * x3 * b2;
         Rd(826) = x2 * x2 * x3 * y0;
         Rd(827) = x2 * x2 * a3 * y3;
         Rd(828) = x2 * x2 * a3 * b3;
         Rd(829) = x2 * x2 * a3 * x0;
         Rd(830) = x2 * x2 * a3 * a2;
         Rd(831) = x2 * x2 * a3 * y2;
         Rd(832) = x2 * x2 * a3 * b2;
         Rd(833) = x2 * x2 * a3 * y0;
         Rd(834) = x2 * x2 * y3 * b3;
         Rd(835) = x2 * x2 * y3 * x0;
         Rd(836) = x2 * x2 * y3 * a2;
         Rd(837) = x2 * x2 * y3 * y2;
         Rd(838) = x2 * x2 * y3 * b2;
         Rd(839) = x2 * x2 * y3 * y0;
         Rd(840) = x2 * x2 * b3 * x0;
         Rd(841) = x2 * x2 * b3 * a2;
         Rd(842) = x2 * x2 * b3 * y2;
         Rd(843) = x2 * x2 * b3 * b2;
         Rd(844) = x2 * x2 * b3 * y0;
         Rd(845) = x2 * x2 * x0 * a2;
         Rd(846) = x2 * x2 * x0 * y2;
         Rd(847) = x2 * x2 * x0 * b2;
         Rd(848) = x2 * x2 * x0 * y0;
         Rd(849) = x2 * x2 * a2 * y2;
         Rd(850) = x2 * x2 * a2 * b2;
         Rd(851) = x2 * x2 * a2 * y0;
         Rd(852) = x2 * x2 * y2 * b2;
         Rd(853) = x2 * x2 * y2 * y0;
         Rd(854) = x2 * x2 * b2 * y0;
         Rd(855) = a2 * a2 * t * x3;
         Rd(856) = a2 * a2 * t * a3;
         Rd(857) = a2 * a2 * t * y3;
         Rd(858) = a2 * a2 * t * b3;
         Rd(859) = a2 * a2 * t * x0;
         Rd(860) = a2 * a2 * t * x2;
         Rd(861) = a2 * a2 * t * y2;
         Rd(862) = a2 * a2 * t * b2;
         Rd(863) = a2 * a2 * t * y0;
         Rd(864) = a2 * a2 * x3 * a3;
         Rd(865) = a2 * a2 * x3 * y3;
         Rd(866) = a2 * a2 * x3 * b3;
         Rd(867) = a2 * a2 * x3 * x0;
         Rd(868) = a2 * a2 * x3 * x2;
         Rd(869) = a2 * a2 * x3 * y2;
         Rd(870) = a2 * a2 * x3 * b2;
         Rd(871) = a2 * a2 * x3 * y0;
         Rd(872) = a2 * a2 * a3 * y3;
         Rd(873) = a2 * a2 * a3 * b3;
         Rd(874) = a2 * a2 * a3 * x0;
         Rd(875) = a2 * a2 * a3 * x2;
         Rd(876) = a2 * a2 * a3 * y2;
         Rd(877) = a2 * a2 * a3 * b2;
         Rd(878) = a2 * a2 * a3 * y0;
         Rd(879) = a2 * a2 * y3 * b3;
         Rd(880) = a2 * a2 * y3 * x0;
         Rd(881) = a2 * a2 * y3 * x2;
         Rd(882) = a2 * a2 * y3 * y2;
         Rd(883) = a2 * a2 * y3 * b2;
         Rd(884) = a2 * a2 * y3 * y0;
         Rd(885) = a2 * a2 * b3 * x0;
         Rd(886) = a2 * a2 * b3 * x2;
         Rd(887) = a2 * a2 * b3 * y2;
         Rd(888) = a2 * a2 * b3 * b2;
         Rd(889) = a2 * a2 * b3 * y0;
         Rd(890) = a2 * a2 * x0 * x2;
         Rd(891) = a2 * a2 * x0 * y2;
         Rd(892) = a2 * a2 * x0 * b2;
         Rd(893) = a2 * a2 * x0 * y0;
         Rd(894) = a2 * a2 * x2 * y2;
         Rd(895) = a2 * a2 * x2 * b2;
         Rd(896) = a2 * a2 * x2 * y0;
         Rd(897) = a2 * a2 * y2 * b2;
         Rd(898) = a2 * a2 * y2 * y0;
         Rd(899) = a2 * a2 * b2 * y0;
         Rd(900) = y2 * y2 * t * x3;
         Rd(901) = y2 * y2 * t * a3;
         Rd(902) = y2 * y2 * t * y3;
         Rd(903) = y2 * y2 * t * b3;
         Rd(904) = y2 * y2 * t * x0;
         Rd(905) = y2 * y2 * t * x2;
         Rd(906) = y2 * y2 * t * a2;
         Rd(907) = y2 * y2 * t * b2;
         Rd(908) = y2 * y2 * t * y0;
         Rd(909) = y2 * y2 * x3 * a3;
         Rd(910) = y2 * y2 * x3 * y3;
         Rd(911) = y2 * y2 * x3 * b3;
         Rd(912) = y2 * y2 * x3 * x0;
         Rd(913) = y2 * y2 * x3 * x2;
         Rd(914) = y2 * y2 * x3 * a2;
         Rd(915) = y2 * y2 * x3 * b2;
         Rd(916) = y2 * y2 * x3 * y0;
         Rd(917) = y2 * y2 * a3 * y3;
         Rd(918) = y2 * y2 * a3 * b3;
         Rd(919) = y2 * y2 * a3 * x0;
         Rd(920) = y2 * y2 * a3 * x2;
         Rd(921) = y2 * y2 * a3 * a2;
         Rd(922) = y2 * y2 * a3 * b2;
         Rd(923) = y2 * y2 * a3 * y0;
         Rd(924) = y2 * y2 * y3 * b3;
         Rd(925) = y2 * y2 * y3 * x0;
         Rd(926) = y2 * y2 * y3 * x2;
         Rd(927) = y2 * y2 * y3 * a2;
         Rd(928) = y2 * y2 * y3 * b2;
         Rd(929) = y2 * y2 * y3 * y0;
         Rd(930) = y2 * y2 * b3 * x0;
         Rd(931) = y2 * y2 * b3 * x2;
         Rd(932) = y2 * y2 * b3 * a2;
         Rd(933) = y2 * y2 * b3 * b2;
         Rd(934) = y2 * y2 * b3 * y0;
         Rd(935) = y2 * y2 * x0 * x2;
         Rd(936) = y2 * y2 * x0 * a2;
         Rd(937) = y2 * y2 * x0 * b2;
         Rd(938) = y2 * y2 * x0 * y0;
         Rd(939) = y2 * y2 * x2 * a2;
         Rd(940) = y2 * y2 * x2 * b2;
         Rd(941) = y2 * y2 * x2 * y0;
         Rd(942) = y2 * y2 * a2 * b2;
         Rd(943) = y2 * y2 * a2 * y0;
         Rd(944) = y2 * y2 * b2 * y0;
         Rd(945) = b2 * b2 * t * x3;
         Rd(946) = b2 * b2 * t * a3;
         Rd(947) = b2 * b2 * t * y3;
         Rd(948) = b2 * b2 * t * b3;
         Rd(949) = b2 * b2 * t * x0;
         Rd(950) = b2 * b2 * t * x2;
         Rd(951) = b2 * b2 * t * a2;
         Rd(952) = b2 * b2 * t * y2;
         Rd(953) = b2 * b2 * t * y0;
         Rd(954) = b2 * b2 * x3 * a3;
         Rd(955) = b2 * b2 * x3 * y3;
         Rd(956) = b2 * b2 * x3 * b3;
         Rd(957) = b2 * b2 * x3 * x0;
         Rd(958) = b2 * b2 * x3 * x2;
         Rd(959) = b2 * b2 * x3 * a2;
         Rd(960) = b2 * b2 * x3 * y2;
         Rd(961) = b2 * b2 * x3 * y0;
         Rd(962) = b2 * b2 * a3 * y3;
         Rd(963) = b2 * b2 * a3 * b3;
         Rd(964) = b2 * b2 * a3 * x0;
         Rd(965) = b2 * b2 * a3 * x2;
         Rd(966) = b2 * b2 * a3 * a2;
         Rd(967) = b2 * b2 * a3 * y2;
         Rd(968) = b2 * b2 * a3 * y0;
         Rd(969) = b2 * b2 * y3 * b3;
         Rd(970) = b2 * b2 * y3 * x0;
         Rd(971) = b2 * b2 * y3 * x2;
         Rd(972) = b2 * b2 * y3 * a2;
         Rd(973) = b2 * b2 * y3 * y2;
         Rd(974) = b2 * b2 * y3 * y0;
         Rd(975) = b2 * b2 * b3 * x0;
         Rd(976) = b2 * b2 * b3 * x2;
         Rd(977) = b2 * b2 * b3 * a2;
         Rd(978) = b2 * b2 * b3 * y2;
         Rd(979) = b2 * b2 * b3 * y0;
         Rd(980) = b2 * b2 * x0 * x2;
         Rd(981) = b2 * b2 * x0 * a2;
         Rd(982) = b2 * b2 * x0 * y2;
         Rd(983) = b2 * b2 * x0 * y0;
         Rd(984) = b2 * b2 * x2 * a2;
         Rd(985) = b2 * b2 * x2 * y2;
         Rd(986) = b2 * b2 * x2 * y0;
         Rd(987) = b2 * b2 * a2 * y2;
         Rd(988) = b2 * b2 * a2 * y0;
         Rd(989) = b2 * b2 * y2 * y0;
         Rd(990) = y0 * y0 * t * x3;
         Rd(991) = y0 * y0 * t * a3;
         Rd(992) = y0 * y0 * t * y3;
         Rd(993) = y0 * y0 * t * b3;
         Rd(994) = y0 * y0 * t * x0;
         Rd(995) = y0 * y0 * t * x2;
         Rd(996) = y0 * y0 * t * a2;
         Rd(997) = y0 * y0 * t * y2;
         Rd(998) = y0 * y0 * t * b2;
         Rd(999) = y0 * y0 * x3 * a3;
         Rd(1000) = y0 * y0 * x3 * y3;
         Rd(1001) = y0 * y0 * x3 * b3;
         Rd(1002) = y0 * y0 * x3 * x0;
         Rd(1003) = y0 * y0 * x3 * x2;
         Rd(1004) = y0 * y0 * x3 * a2;
         Rd(1005) = y0 * y0 * x3 * y2;
         Rd(1006) = y0 * y0 * x3 * b2;
         Rd(1007) = y0 * y0 * a3 * y3;
         Rd(1008) = y0 * y0 * a3 * b3;
         Rd(1009) = y0 * y0 * a3 * x0;
         Rd(1010) = y0 * y0 * a3 * x2;
         Rd(1011) = y0 * y0 * a3 * a2;
         Rd(1012) = y0 * y0 * a3 * y2;
         Rd(1013) = y0 * y0 * a3 * b2;
         Rd(1014) = y0 * y0 * y3 * b3;
         Rd(1015) = y0 * y0 * y3 * x0;
         Rd(1016) = y0 * y0 * y3 * x2;
         Rd(1017) = y0 * y0 * y3 * a2;
         Rd(1018) = y0 * y0 * y3 * y2;
         Rd(1019) = y0 * y0 * y3 * b2;
         Rd(1020) = y0 * y0 * b3 * x0;
         Rd(1021) = y0 * y0 * b3 * x2;
         Rd(1022) = y0 * y0 * b3 * a2;
         Rd(1023) = y0 * y0 * b3 * y2;
         Rd(1024) = y0 * y0 * b3 * b2;
         Rd(1025) = y0 * y0 * x0 * x2;
         Rd(1026) = y0 * y0 * x0 * a2;
         Rd(1027) = y0 * y0 * x0 * y2;
         Rd(1028) = y0 * y0 * x0 * b2;
         Rd(1029) = y0 * y0 * x2 * a2;
         Rd(1030) = y0 * y0 * x2 * y2;
         Rd(1031) = y0 * y0 * x2 * b2;
         Rd(1032) = y0 * y0 * a2 * y2;
         Rd(1033) = y0 * y0 * a2 * b2;
         Rd(1034) = y0 * y0 * y2 * b2;
         Rd(1035) = t * x3 * a3 * y3;
         Rd(1036) = t * x3 * a3 * b3;
         Rd(1037) = t * x3 * a3 * x0;
         Rd(1038) = t * x3 * a3 * x2;
         Rd(1039) = t * x3 * a3 * a2;
         Rd(1040) = t * x3 * a3 * y2;
         Rd(1041) = t * x3 * a3 * b2;
         Rd(1042) = t * x3 * a3 * y0;
         Rd(1043) = t * x3 * y3 * b3;
         Rd(1044) = t * x3 * y3 * x0;
         Rd(1045) = t * x3 * y3 * x2;
         Rd(1046) = t * x3 * y3 * a2;
         Rd(1047) = t * x3 * y3 * y2;
         Rd(1048) = t * x3 * y3 * b2;
         Rd(1049) = t * x3 * y3 * y0;
         Rd(1050) = t * x3 * b3 * x0;
         Rd(1051) = t * x3 * b3 * x2;
         Rd(1052) = t * x3 * b3 * a2;
         Rd(1053) = t * x3 * b3 * y2;
         Rd(1054) = t * x3 * b3 * b2;
         Rd(1055) = t * x3 * b3 * y0;
         Rd(1056) = t * x3 * x0 * x2;
         Rd(1057) = t * x3 * x0 * a2;
         Rd(1058) = t * x3 * x0 * y2;
         Rd(1059) = t * x3 * x0 * b2;
         Rd(1060) = t * x3 * x0 * y0;
         Rd(1061) = t * x3 * x2 * a2;
         Rd(1062) = t * x3 * x2 * y2;
         Rd(1063) = t * x3 * x2 * b2;
         Rd(1064) = t * x3 * x2 * y0;
         Rd(1065) = t * x3 * a2 * y2;
         Rd(1066) = t * x3 * a2 * b2;
         Rd(1067) = t * x3 * a2 * y0;
         Rd(1068) = t * x3 * y2 * b2;
         Rd(1069) = t * x3 * y2 * y0;
         Rd(1070) = t * x3 * b2 * y0;
         Rd(1071) = t * a3 * y3 * b3;
         Rd(1072) = t * a3 * y3 * x0;
         Rd(1073) = t * a3 * y3 * x2;
         Rd(1074) = t * a3 * y3 * a2;
         Rd(1075) = t * a3 * y3 * y2;
         Rd(1076) = t * a3 * y3 * b2;
         Rd(1077) = t * a3 * y3 * y0;
         Rd(1078) = t * a3 * b3 * x0;
         Rd(1079) = t * a3 * b3 * x2;
         Rd(1080) = t * a3 * b3 * a2;
         Rd(1081) = t * a3 * b3 * y2;
         Rd(1082) = t * a3 * b3 * b2;
         Rd(1083) = t * a3 * b3 * y0;
         Rd(1084) = t * a3 * x0 * x2;
         Rd(1085) = t * a3 * x0 * a2;
         Rd(1086) = t * a3 * x0 * y2;
         Rd(1087) = t * a3 * x0 * b2;
         Rd(1088) = t * a3 * x0 * y0;
         Rd(1089) = t * a3 * x2 * a2;
         Rd(1090) = t * a3 * x2 * y2;
         Rd(1091) = t * a3 * x2 * b2;
         Rd(1092) = t * a3 * x2 * y0;
         Rd(1093) = t * a3 * a2 * y2;
         Rd(1094) = t * a3 * a2 * b2;
         Rd(1095) = t * a3 * a2 * y0;
         Rd(1096) = t * a3 * y2 * b2;
         Rd(1097) = t * a3 * y2 * y0;
         Rd(1098) = t * a3 * b2 * y0;
         Rd(1099) = t * y3 * b3 * x0;
         Rd(1100) = t * y3 * b3 * x2;
         Rd(1101) = t * y3 * b3 * a2;
         Rd(1102) = t * y3 * b3 * y2;
         Rd(1103) = t * y3 * b3 * b2;
         Rd(1104) = t * y3 * b3 * y0;
         Rd(1105) = t * y3 * x0 * x2;
         Rd(1106) = t * y3 * x0 * a2;
         Rd(1107) = t * y3 * x0 * y2;
         Rd(1108) = t * y3 * x0 * b2;
         Rd(1109) = t * y3 * x0 * y0;
         Rd(1110) = t * y3 * x2 * a2;
         Rd(1111) = t * y3 * x2 * y2;
         Rd(1112) = t * y3 * x2 * b2;
         Rd(1113) = t * y3 * x2 * y0;
         Rd(1114) = t * y3 * a2 * y2;
         Rd(1115) = t * y3 * a2 * b2;
         Rd(1116) = t * y3 * a2 * y0;
         Rd(1117) = t * y3 * y2 * b2;
         Rd(1118) = t * y3 * y2 * y0;
         Rd(1119) = t * y3 * b2 * y0;
         Rd(1120) = t * b3 * x0 * x2;
         Rd(1121) = t * b3 * x0 * a2;
         Rd(1122) = t * b3 * x0 * y2;
         Rd(1123) = t * b3 * x0 * b2;
         Rd(1124) = t * b3 * x0 * y0;
         Rd(1125) = t * b3 * x2 * a2;
         Rd(1126) = t * b3 * x2 * y2;
         Rd(1127) = t * b3 * x2 * b2;
         Rd(1128) = t * b3 * x2 * y0;
         Rd(1129) = t * b3 * a2 * y2;
         Rd(1130) = t * b3 * a2 * b2;
         Rd(1131) = t * b3 * a2 * y0;
         Rd(1132) = t * b3 * y2 * b2;
         Rd(1133) = t * b3 * y2 * y0;
         Rd(1134) = t * b3 * b2 * y0;
         Rd(1135) = t * x0 * x2 * a2;
         Rd(1136) = t * x0 * x2 * y2;
         Rd(1137) = t * x0 * x2 * b2;
         Rd(1138) = t * x0 * x2 * y0;
         Rd(1139) = t * x0 * a2 * y2;
         Rd(1140) = t * x0 * a2 * b2;
         Rd(1141) = t * x0 * a2 * y0;
         Rd(1142) = t * x0 * y2 * b2;
         Rd(1143) = t * x0 * y2 * y0;
         Rd(1144) = t * x0 * b2 * y0;
         Rd(1145) = t * x2 * a2 * y2;
         Rd(1146) = t * x2 * a2 * b2;
         Rd(1147) = t * x2 * a2 * y0;
         Rd(1148) = t * x2 * y2 * b2;
         Rd(1149) = t * x2 * y2 * y0;
         Rd(1150) = t * x2 * b2 * y0;
         Rd(1151) = t * a2 * y2 * b2;
         Rd(1152) = t * a2 * y2 * y0;
         Rd(1153) = t * a2 * b2 * y0;
         Rd(1154) = t * y2 * b2 * y0;
         Rd(1155) = x3 * a3 * y3 * b3;
         Rd(1156) = x3 * a3 * y3 * x0;
         Rd(1157) = x3 * a3 * y3 * x2;
         Rd(1158) = x3 * a3 * y3 * a2;
         Rd(1159) = x3 * a3 * y3 * y2;
         Rd(1160) = x3 * a3 * y3 * b2;
         Rd(1161) = x3 * a3 * y3 * y0;
         Rd(1162) = x3 * a3 * b3 * x0;
         Rd(1163) = x3 * a3 * b3 * x2;
         Rd(1164) = x3 * a3 * b3 * a2;
         Rd(1165) = x3 * a3 * b3 * y2;
         Rd(1166) = x3 * a3 * b3 * b2;
         Rd(1167) = x3 * a3 * b3 * y0;
         Rd(1168) = x3 * a3 * x0 * x2;
         Rd(1169) = x3 * a3 * x0 * a2;
         Rd(1170) = x3 * a3 * x0 * y2;
         Rd(1171) = x3 * a3 * x0 * b2;
         Rd(1172) = x3 * a3 * x0 * y0;
         Rd(1173) = x3 * a3 * x2 * a2;
         Rd(1174) = x3 * a3 * x2 * y2;
         Rd(1175) = x3 * a3 * x2 * b2;
         Rd(1176) = x3 * a3 * x2 * y0;
         Rd(1177) = x3 * a3 * a2 * y2;
         Rd(1178) = x3 * a3 * a2 * b2;
         Rd(1179) = x3 * a3 * a2 * y0;
         Rd(1180) = x3 * a3 * y2 * b2;
         Rd(1181) = x3 * a3 * y2 * y0;
         Rd(1182) = x3 * a3 * b2 * y0;
         Rd(1183) = x3 * y3 * b3 * x0;
         Rd(1184) = x3 * y3 * b3 * x2;
         Rd(1185) = x3 * y3 * b3 * a2;
         Rd(1186) = x3 * y3 * b3 * y2;
         Rd(1187) = x3 * y3 * b3 * b2;
         Rd(1188) = x3 * y3 * b3 * y0;
         Rd(1189) = x3 * y3 * x0 * x2;
         Rd(1190) = x3 * y3 * x0 * a2;
         Rd(1191) = x3 * y3 * x0 * y2;
         Rd(1192) = x3 * y3 * x0 * b2;
         Rd(1193) = x3 * y3 * x0 * y0;
         Rd(1194) = x3 * y3 * x2 * a2;
         Rd(1195) = x3 * y3 * x2 * y2;
         Rd(1196) = x3 * y3 * x2 * b2;
         Rd(1197) = x3 * y3 * x2 * y0;
         Rd(1198) = x3 * y3 * a2 * y2;
         Rd(1199) = x3 * y3 * a2 * b2;
         Rd(1200) = x3 * y3 * a2 * y0;
         Rd(1201) = x3 * y3 * y2 * b2;
         Rd(1202) = x3 * y3 * y2 * y0;
         Rd(1203) = x3 * y3 * b2 * y0;
         Rd(1204) = x3 * b3 * x0 * x2;
         Rd(1205) = x3 * b3 * x0 * a2;
         Rd(1206) = x3 * b3 * x0 * y2;
         Rd(1207) = x3 * b3 * x0 * b2;
         Rd(1208) = x3 * b3 * x0 * y0;
         Rd(1209) = x3 * b3 * x2 * a2;
         Rd(1210) = x3 * b3 * x2 * y2;
         Rd(1211) = x3 * b3 * x2 * b2;
         Rd(1212) = x3 * b3 * x2 * y0;
         Rd(1213) = x3 * b3 * a2 * y2;
         Rd(1214) = x3 * b3 * a2 * b2;
         Rd(1215) = x3 * b3 * a2 * y0;
         Rd(1216) = x3 * b3 * y2 * b2;
         Rd(1217) = x3 * b3 * y2 * y0;
         Rd(1218) = x3 * b3 * b2 * y0;
         Rd(1219) = x3 * x0 * x2 * a2;
         Rd(1220) = x3 * x0 * x2 * y2;
         Rd(1221) = x3 * x0 * x2 * b2;
         Rd(1222) = x3 * x0 * x2 * y0;
         Rd(1223) = x3 * x0 * a2 * y2;
         Rd(1224) = x3 * x0 * a2 * b2;
         Rd(1225) = x3 * x0 * a2 * y0;
         Rd(1226) = x3 * x0 * y2 * b2;
         Rd(1227) = x3 * x0 * y2 * y0;
         Rd(1228) = x3 * x0 * b2 * y0;
         Rd(1229) = x3 * x2 * a2 * y2;
         Rd(1230) = x3 * x2 * a2 * b2;
         Rd(1231) = x3 * x2 * a2 * y0;
         Rd(1232) = x3 * x2 * y2 * b2;
         Rd(1233) = x3 * x2 * y2 * y0;
         Rd(1234) = x3 * x2 * b2 * y0;
         Rd(1235) = x3 * a2 * y2 * b2;
         Rd(1236) = x3 * a2 * y2 * y0;
         Rd(1237) = x3 * a2 * b2 * y0;
         Rd(1238) = x3 * y2 * b2 * y0;
         Rd(1239) = a3 * y3 * b3 * x0;
         Rd(1240) = a3 * y3 * b3 * x2;
         Rd(1241) = a3 * y3 * b3 * a2;
         Rd(1242) = a3 * y3 * b3 * y2;
         Rd(1243) = a3 * y3 * b3 * b2;
         Rd(1244) = a3 * y3 * b3 * y0;
         Rd(1245) = a3 * y3 * x0 * x2;
         Rd(1246) = a3 * y3 * x0 * a2;
         Rd(1247) = a3 * y3 * x0 * y2;
         Rd(1248) = a3 * y3 * x0 * b2;
         Rd(1249) = a3 * y3 * x0 * y0;
         Rd(1250) = a3 * y3 * x2 * a2;
         Rd(1251) = a3 * y3 * x2 * y2;
         Rd(1252) = a3 * y3 * x2 * b2;
         Rd(1253) = a3 * y3 * x2 * y0;
         Rd(1254) = a3 * y3 * a2 * y2;
         Rd(1255) = a3 * y3 * a2 * b2;
         Rd(1256) = a3 * y3 * a2 * y0;
         Rd(1257) = a3 * y3 * y2 * b2;
         Rd(1258) = a3 * y3 * y2 * y0;
         Rd(1259) = a3 * y3 * b2 * y0;
         Rd(1260) = a3 * b3 * x0 * x2;
         Rd(1261) = a3 * b3 * x0 * a2;
         Rd(1262) = a3 * b3 * x0 * y2;
         Rd(1263) = a3 * b3 * x0 * b2;
         Rd(1264) = a3 * b3 * x0 * y0;
         Rd(1265) = a3 * b3 * x2 * a2;
         Rd(1266) = a3 * b3 * x2 * y2;
         Rd(1267) = a3 * b3 * x2 * b2;
         Rd(1268) = a3 * b3 * x2 * y0;
         Rd(1269) = a3 * b3 * a2 * y2;
         Rd(1270) = a3 * b3 * a2 * b2;
         Rd(1271) = a3 * b3 * a2 * y0;
         Rd(1272) = a3 * b3 * y2 * b2;
         Rd(1273) = a3 * b3 * y2 * y0;
         Rd(1274) = a3 * b3 * b2 * y0;
         Rd(1275) = a3 * x0 * x2 * a2;
         Rd(1276) = a3 * x0 * x2 * y2;
         Rd(1277) = a3 * x0 * x2 * b2;
         Rd(1278) = a3 * x0 * x2 * y0;
         Rd(1279) = a3 * x0 * a2 * y2;
         Rd(1280) = a3 * x0 * a2 * b2;
         Rd(1281) = a3 * x0 * a2 * y0;
         Rd(1282) = a3 * x0 * y2 * b2;
         Rd(1283) = a3 * x0 * y2 * y0;
         Rd(1284) = a3 * x0 * b2 * y0;
         Rd(1285) = a3 * x2 * a2 * y2;
         Rd(1286) = a3 * x2 * a2 * b2;
         Rd(1287) = a3 * x2 * a2 * y0;
         Rd(1288) = a3 * x2 * y2 * b2;
         Rd(1289) = a3 * x2 * y2 * y0;
         Rd(1290) = a3 * x2 * b2 * y0;
         Rd(1291) = a3 * a2 * y2 * b2;
         Rd(1292) = a3 * a2 * y2 * y0;
         Rd(1293) = a3 * a2 * b2 * y0;
         Rd(1294) = a3 * y2 * b2 * y0;
         Rd(1295) = y3 * b3 * x0 * x2;
         Rd(1296) = y3 * b3 * x0 * a2;
         Rd(1297) = y3 * b3 * x0 * y2;
         Rd(1298) = y3 * b3 * x0 * b2;
         Rd(1299) = y3 * b3 * x0 * y0;
         Rd(1300) = y3 * b3 * x2 * a2;
         Rd(1301) = y3 * b3 * x2 * y2;
         Rd(1302) = y3 * b3 * x2 * b2;
         Rd(1303) = y3 * b3 * x2 * y0;
         Rd(1304) = y3 * b3 * a2 * y2;
         Rd(1305) = y3 * b3 * a2 * b2;
         Rd(1306) = y3 * b3 * a2 * y0;
         Rd(1307) = y3 * b3 * y2 * b2;
         Rd(1308) = y3 * b3 * y2 * y0;
         Rd(1309) = y3 * b3 * b2 * y0;
         Rd(1310) = y3 * x0 * x2 * a2;
         Rd(1311) = y3 * x0 * x2 * y2;
         Rd(1312) = y3 * x0 * x2 * b2;
         Rd(1313) = y3 * x0 * x2 * y0;
         Rd(1314) = y3 * x0 * a2 * y2;
         Rd(1315) = y3 * x0 * a2 * b2;
         Rd(1316) = y3 * x0 * a2 * y0;
         Rd(1317) = y3 * x0 * y2 * b2;
         Rd(1318) = y3 * x0 * y2 * y0;
         Rd(1319) = y3 * x0 * b2 * y0;
         Rd(1320) = y3 * x2 * a2 * y2;
         Rd(1321) = y3 * x2 * a2 * b2;
         Rd(1322) = y3 * x2 * a2 * y0;
         Rd(1323) = y3 * x2 * y2 * b2;
         Rd(1324) = y3 * x2 * y2 * y0;
         Rd(1325) = y3 * x2 * b2 * y0;
         Rd(1326) = y3 * a2 * y2 * b2;
         Rd(1327) = y3 * a2 * y2 * y0;
         Rd(1328) = y3 * a2 * b2 * y0;
         Rd(1329) = y3 * y2 * b2 * y0;
         Rd(1330) = b3 * x0 * x2 * a2;
         Rd(1331) = b3 * x0 * x2 * y2;
         Rd(1332) = b3 * x0 * x2 * b2;
         Rd(1333) = b3 * x0 * x2 * y0;
         Rd(1334) = b3 * x0 * a2 * y2;
         Rd(1335) = b3 * x0 * a2 * b2;
         Rd(1336) = b3 * x0 * a2 * y0;
         Rd(1337) = b3 * x0 * y2 * b2;
         Rd(1338) = b3 * x0 * y2 * y0;
         Rd(1339) = b3 * x0 * b2 * y0;
         Rd(1340) = b3 * x2 * a2 * y2;
         Rd(1341) = b3 * x2 * a2 * b2;
         Rd(1342) = b3 * x2 * a2 * y0;
         Rd(1343) = b3 * x2 * y2 * b2;
         Rd(1344) = b3 * x2 * y2 * y0;
         Rd(1345) = b3 * x2 * b2 * y0;
         Rd(1346) = b3 * a2 * y2 * b2;
         Rd(1347) = b3 * a2 * y2 * y0;
         Rd(1348) = b3 * a2 * b2 * y0;
         Rd(1349) = b3 * y2 * b2 * y0;
         Rd(1350) = x0 * x2 * a2 * y2;
         Rd(1351) = x0 * x2 * a2 * b2;
         Rd(1352) = x0 * x2 * a2 * y0;
         Rd(1353) = x0 * x2 * y2 * b2;
         Rd(1354) = x0 * x2 * y2 * y0;
         Rd(1355) = x0 * x2 * b2 * y0;
         Rd(1356) = x0 * a2 * y2 * b2;
         Rd(1357) = x0 * a2 * y2 * y0;
         Rd(1358) = x0 * a2 * b2 * y0;
         Rd(1359) = x0 * y2 * b2 * y0;
         Rd(1360) = x2 * a2 * y2 * b2;
         Rd(1361) = x2 * a2 * y2 * y0;
         Rd(1362) = x2 * a2 * b2 * y0;
         Rd(1363) = x2 * y2 * b2 * y0;
         Rd(1364) = a2 * y2 * b2 * y0;

      }
	}
        
		for(int i = 0; i < Nprm; i++){
//		for(int i = 0; i < 1001; i++){
			sum += Rd(i) * Theta[i];
//			sum += Rd(i);
		}	

       Double_t mass_cor = TMath::Sqrt(sum);

       TMassData *outData = static_cast<TMassData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
       outData->SetAq(mass_cor);
//  
        outData->SetTof(t);
        outData->SetX(x3);
//  }

//
//         outData->SetZ(theta);
//         outData->SetF3X(x3);
//         outData->SetF3A(a3);
//         outData->SetF3Y(y3);
//         outData->SetF3B(b3);
 
}



