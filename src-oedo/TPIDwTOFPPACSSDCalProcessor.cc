
#include "TPIDwTOFPPACSSDCalProcessor.h"
#include <TMath.h>
#include <TSRPPACPlaneData.h>
#include <TSRPPACParameter.h>
#include <TTwoSidedPlasticData.h>
#include "TDssdData.h"
#include <TMassData.h>
#include <TTimingChargeData.h>
#include "TDiaTimingData.h"
#include <TClonesArray.h>
#include <deque>

using art::TPIDwTOFPPACSSDCalProcessor;

ClassImp(TPIDwTOFPPACSSDCalProcessor)

namespace {
   class LessByTimestamp {
   public:
      bool operator() (const art::TDataObject* data1, const art::TDataObject *data2) {
         return data1->GetTimestamp() < data2->GetTimestamp();
      }
   };
}
  


TPIDwTOFPPACSSDCalProcessor::TPIDwTOFPPACSSDCalProcessor()
//   : fTOFs(NULL), fOutput(NULL)
{

   Register(fDoCheckTimestamp("DoCheckTimestamp","check timestamp if not 0",0));

   RegisterInputCollection("TofName","name of input tof",fTofName,TString("tof"),
                           &fTOFs,TClonesArray::Class_Name(),TDiaTimingData::Class_Name());
   RegisterProcessorParameter("S0PPAC","output from x position at dispersive focal plane",fS0PPACName,TString("s0ppac"));
                       //     &fX,TClonesArray::Class_Name(),TSRPPACPlaneData::Class_Name());
   RegisterProcessorParameter("S2SSD","output from delta e in ssd",fS2SSDName,TString("s2ssd"));
                 //           &fSSD,TClonesArray::Class_Name(),TDssdData::Class_Name());
   RegisterProcessorParameter("S2PLA","output from charge in s2pla",fS2PLAName,TString("s2pla"));
                 //           &fSSD,TClonesArray::Class_Name(),TDssdData::Class_Name());


   RegisterProcessorParameter("UseChargeDeltaE","use charge information for dE e.g. pla charge",fUseChargeDeltaE,0);

   RegisterProcessorParameter("UseZcoin","use both information dE and Charge",fUseZcoin,0);
   RegisterProcessorParameter("UseMaxZ","Take max value of Z",fUseMaxZ,0);
   
   RegisterOutputCollection("OutputName","name of output pid",fOutputName,TString("mass"),
                            &fOutput,TClonesArray::Class_Name(),TMassData::Class_Name());
//   RegisterOutputCollection("OutputZ","name of output z",fOutputZName,TString("z"),
//                            &fOutputZ,TClonesArray::Class_Name(),TSimpleData::Class_Name());
   RegisterProcessorParameter("Brho0","Brho0 at dispersive focal plane",fBrho0,Double_t(2));
   RegisterProcessorParameter("Length","flight pass lengths",fLength,Double_t(23.2832));
   RegisterProcessorParameter("Dispersion","two dispersions before and after focus",fDispersion,Double_t(0));
   RegisterProcessorParameter("Tofoffset","ToF offset",fTofoffset,Double_t(0));
}

TPIDwTOFPPACSSDCalProcessor::~TPIDwTOFPPACSSDCalProcessor()
{
}

TPIDwTOFPPACSSDCalProcessor::TPIDwTOFPPACSSDCalProcessor(const TPIDwTOFPPACSSDCalProcessor& rhs)
{
}

TPIDwTOFPPACSSDCalProcessor& TPIDwTOFPPACSSDCalProcessor::operator=(const TPIDwTOFPPACSSDCalProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TPIDwTOFPPACSSDCalProcessor::Init(TEventCollection *col)
{

 fS0PPAC = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS0PPACName.Data()));
 if (!fS0PPAC) return;

 fS2SSD = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS2SSDName.Data()));
 if (!fS2SSD) return;

 fS2PLA = reinterpret_cast<TClonesArray**>(col->GetObjectRef(fS2PLAName.Data()));
 if (!fS2PLA) return;



}

void TPIDwTOFPPACSSDCalProcessor::Process()
{
   fOutput->Clear("C");
//   if (!(*fTOFs)->GetEntriesFast() ||
//       !(*fX)->GetEntriesFast() ||
//       !(*fSSD)->GetEntriesFast())  {
//      return;
//   }
//   std::deque<TSRPPACPlaneData*> mwdcHits;
//   std::deque<TDiaTimingData*> tofHits;
//
//   for (Int_t iHit = 0, nHits = (fInput)->GetEntriesFast(); iHit < nHits; ++iHit) {
//      mwdcHits.push_back(static_cast<TSRPPACPlaneData*>((fInput)->UncheckedAt(iHit)));
//   }
//   for (Int_t iTof = 0, nTof = (*fTOFs)->GetEntriesFast(); iTof < nTof; ++iTof) {
//      tofHits.push_back(static_cast<TDiaTimingData*>((*fTOFs)->UncheckedAt(iTof)));
//   }
//
//   std::sort(mwdcHits.begin(),mwdcHits.end(),LessByTimestamp());
//   std::sort(tofHits.begin(),tofHits.end(),LessByTimestamp());
////   Info("Process","");
//   
//   while (mwdcHits.size()) {
//      TSRPPACPlaneData* plane = mwdcHits.front();
//      mwdcHits.pop_front();
//      while (tofHits.size()) {
//         TDiaTimingData* tof = tofHits.front();
//         tofHits.pop_front();
////         printf("%f %f\n",plane->GetTimestamp(),tof->GetTimestamp());
//         if (fDoCheckTimestamp) {
//            if ( tof->GetTimestamp() - plane->GetTimestamp() >
//                 TMath::Limits<Float_t>::Epsilon()) {
//               // skip this mwdc hit if plane timestamp is ealier than tof timestamp
//               break;
//            }
//            if (plane->GetTimestamp() - tof->GetTimestamp() >
//                TMath::Limits<Float_t>::Epsilon()) {
//               // skip this tof hit if tof timestamp is ealier than plane timestamp
//               continue;
//            }
//         }
         
         // found
	//	 TSRPPACPlaneData *const s0ppac = static_cast<TSRPPACPlaneData*>((*fX)->UncheckedAt(0));
	 	 const TSRPPACPlaneData *const s0ppac = static_cast<TSRPPACPlaneData*>((*fS0PPAC)->At(0));
		 if (!s0ppac) return;
//         Double_t x = s0ppac->GetPosition()+49.28;
         Double_t x = s0ppac->GetPosition();
//         printf("%d %f %f\n",plane->GetID(),x, fMWDCParam->GetCellSize());
        // TChargeData *tofdata = (TChargeData*) (*fTofName)->At(0);
//		 TDiaTimingData *const tof = static_cast<TDiaTimingData*>((*fTOFs)->UncheckedAt(0));
		 const TDiaTimingData *const tof = static_cast<TDiaTimingData*>((*fTOFs)->At(0));
         if(!tof) return;
	     Double_t t = tof->GetTiming();


         Double_t Ex,Ex_pla,Ex_ssd; 

//		 TDssdData *const s2ssd = static_cast<TDssdData*>((*fSSD)->UncheckedAt(0));
		 const TDssdData *const s2ssd = static_cast<TDssdData*>((*fS2SSD)->At(0));
		 if (!s2ssd) return;

		 Ex_ssd = s2ssd->GetEx();

//         if (fUseChargeDeltaE){
//		 const TTwoSidedPlasticData *const s2pla = static_cast<TTwoSidedPlasticData*>((*fS2PLA)->At(0));
//		 if(!s2pla) return;
//		  Ex = s2pla->GetCharge();
//		 }else {
//          Ex = s2ssd->GetEx();
//         }

//	     if (fUseZcoin){
//			const TTwoSidedPlasticData *const s2pla = static_cast<TTwoSidedPlasticData*>((*fS2PLA)->At(0));
//		    if(!s2pla) return;
//			Ex_pla = s2pla->GetCharge(); 
//			if( TMath::Abs(Ex_pla - Ex_ssd*1.17 + 15.) < 10.){
//				 Ex = Ex_ssd;
//			}else{
//				return;
//				}
//			}else if (fUseChargeDeltaE){
//			const TTwoSidedPlasticData *const s2pla = static_cast<TTwoSidedPlasticData*>((*fS2PLA)->At(0));
//		    if(!s2pla) return;
// 			Ex_pla = s2pla->GetCharge();
//     	    Ex = Ex_pla;
//			 }else {
//   	       Ex = Ex_ssd;
//   	      }
		 
	     const TTwoSidedPlasticData *const s2pla = static_cast<TTwoSidedPlasticData*>((*fS2PLA)->At(0));
	     if(!s2pla) return;
 	     Ex_pla = s2pla->GetCharge();

         Double_t aq,z; 
//         CalcZAQ(t,x,Ex,z,aq);
         CalcZAQ(t,x,Ex_ssd,Ex_pla,z,aq);
         TMassData *outData = static_cast<TMassData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
         outData->SetAq(aq);
         outData->SetZ(z);
    
	     outData->SetTof(t);
         outData->SetX(x);
         
//         break;
//      }
//   }
}

void TPIDwTOFPPACSSDCalProcessor::CalcZAQ(Double_t t, Double_t x, Double_t Ex_ssd, Double_t Ex_pla,  Double_t& z, Double_t& aq)
{
   const Double_t c = TMath::C()*1e-6;
   const Double_t m = 931.494; // unit nucleus mass 

   // calculate brho
   Double_t B = fBrho0 * ( 1 - x / fDispersion);

   // calculate beta & gamma
  // Double_t toff = -1485.;
   Double_t beta = fLength / (t + fTofoffset) / c;
   Double_t gam = 1. / TMath::Sqrt( 1.- beta * beta);
   
   // calculate aq
   aq = c * B / (gam * beta * m);
   
   // calcuate Z
//   const Double_t e0 = 0.89914182;
//   const Double_t bb = 5907.5; // parameter in Bethe 
//   const Double_t z0 = -0.0513;
//   const Double_t z1 = 7.451;
//   
//   Double_t s2de = e0 * Ex;  //ssd dE
//   Double_t bbconst =  TMath::Log(bb * beta * beta) - TMath::Log(1. - beta * beta) - beta * beta; 


   Double_t beta_pri = fLength / (t - 1543.41) / c;
   Double_t z_pri_ssd = beta_pri *  TMath::Sqrt(Ex_ssd);
   Double_t z_pri_pla = beta_pri *  TMath::Sqrt(Ex_pla);
   Double_t z_tmp,z_ssd_tmp,z_ssd,z_pla_tmp,z_pla,z_max;

   z_ssd_tmp = 8.79324 + 0.179398 * z_pri_ssd + 0.17913 * TMath::Power(z_pri_ssd,2) - 0.00538494 * TMath::Power(z_pri_ssd,3); //see prm/ssd/z_cal.dat
   z_ssd = -0.137841 + 0.691355 * z_ssd_tmp + 0.0292942 * TMath::Power(z_ssd_tmp,2) - 0.000657488 * TMath::Power(z_ssd_tmp,3); //see prm/ssd/z_cal.dat

   z_pla_tmp = 8.14194 + 0.861558 * z_pri_pla + 0.0602123 *TMath::Power(z_pri_pla,2) + 5.40346e-05 *TMath::Power(z_pri_pla,3); //see prm/plastic/z_cal.dat
   z_pla = 1.96348 + 0.598993 * z_pla_tmp + 0.0244441 *TMath::Power(z_pla_tmp,2) - 0.000457376 *TMath::Power(z_pla_tmp,3); //see prm/plastic/z_cal.dat

   z_max = TMath::Max(z_ssd,z_pla);

   if(fUseChargeDeltaE){
	   z = z_pla;
   }else if(fUseMaxZ){
	  z = z_max;
   }else{
	   z = z_ssd;
   }


// if(fUseChargeDeltaE){
//   z_tmp = 8.14194 + 0.861558 * z_pri + 0.0602123 *TMath::Power(z_pri,2) + 5.40346e-05 *TMath::Power(z_pri,3); //see prm/plastic/z_cal.dat
//   z = 1.96348 + 0.598993 * z_tmp + 0.0244441 *TMath::Power(z_tmp,2) - 0.000457376 *TMath::Power(z_tmp,3); //see prm/plastic/z_cal.dat
// }else{
//   z_tmp = 8.79324 + 0.179398 * z_pri + 0.17913 * TMath::Power(z_pri,2) - 0.00538494 * TMath::Power(z_pri,3); //see prm/ssd/z_cal.dat
//   z = -0.137841 + 0.691355 * z_tmp + 0.0292942 * TMath::Power(z_tmp,2) - 0.000657488 * TMath::Power(z_tmp,3); //see prm/ssd/z_cal.dat
//}




}
