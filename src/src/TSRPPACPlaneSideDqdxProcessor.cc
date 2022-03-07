/**
 * @file   TSRPPACPlaneDqdxProcessor.cc
 * @brief  sr-ppac plane processor with dqdx
 *
 * @date   Created       : 2019-08-30 19:38:25 JST
 *         Last Modified :
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2019 Shinsuke OTA
 */

#include "TSRPPACPlaneSideDqdxProcessor.h"
#include "TMonotoneTableConverter.h"
#include "TMath.h"

using art::TSRPPACPlaneSideDqdxProcessor;

ClassImp(TSRPPACPlaneSideDqdxProcessor)

TSRPPACPlaneSideDqdxProcessor::TSRPPACPlaneSideDqdxProcessor()
{
//   Regi:vndssterInputInfo("Converter","name of dqdx converter",fConverterName,"srppac_xc0",
//                      &fConverter, "art::TMonotoneTableConverter");
   RegisterInputInfo("Converter1","name of dqdx converter1",fConverterName1,"srppac_xcl",&fConverter1,"art::TMonotoneTableConverter");
   RegisterInputInfo("Converter2","name of dqdx converter2",fConverterName2,"srppac_xcr",&fConverter2,"art::TMonotoneTableConverter");
//   RegisterInputInfo("Converter3","name of dqdx converter3",fConverterName2,"srppac_xcr",&fConverter3,"art::TMonotoneTableConverter");
//   RegisterInputInfo("Converter4","name of dqdx converter4",fConverterName2,"srppac_xcr",&fConverter4,"art::TMonotoneTableConverter");
   RegisterProcessorParameter("Combination","type of combination: 0 => ID0-IDl, 1 => ID1-IDr",fCombination,0);
}

TSRPPACPlaneSideDqdxProcessor::~TSRPPACPlaneSideDqdxProcessor()
{
}

void TSRPPACPlaneSideDqdxProcessor::Process()
{
   (fOutput)->Clear("C");

   double pos = 0.;
   double c0 = 0.;
   double cl = 0.;
   double cr = 0.;
   int id0 = 0;
   int idl = 0;
   int idr = 0;
 
//   printf("%p\n",*fConverter);
   const Int_t nData = (*fInput)->GetEntriesFast();
  
   Int_t id[nData];
   Double_t charge[nData];
   
   for (Int_t iData = 0; iData != nData; ++iData) {
      const TTimingChargeData *const inData = static_cast<TTimingChargeData*>((*fInput)->At(iData));
      id[iData] = inData->GetID();
      charge[iData] = inData->GetCharge();
   }

   id0 = id[0];
   c0 =  charge[0];

   for (int i=1; i != nData; ++i){
    if (id[i] == id[0]+1){
        idl = id[i]; 
        cl = charge[i];
        break;
      }
    }

   for (int j=1; j != nData; ++j){
    if (id[j] == id[0]-1){
        idr = id[j];
        cr = charge[j];
        break;
      }
    }


   if (fCombination == 0 && nData > 2) {
      if (TMath::IsNaN(c0) || TMath::IsNaN(cl) || TMath::IsNaN(cr) || cl < 1 || cr < 1 ) return;
      if ( (c0-cl)/(c0+cl) < 0.04 && nData > 2 ){
      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter1)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset);
     } else if ( (c0-cr)/(c0+cr) < 0.04 && nData > 2){
      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter2)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset);
     } else {
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter1)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.506329 + (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter2)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.493671;
      double cll = pow(c0-cl,2);
      double crr = pow(c0-cr,2);
      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter1)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset)*(crr / (cll + crr)) + (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter2)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset)*(cll / (cll +crr));
     }} else {
         return;
      }


//   if (fCombination == 0 && nData > 2) {
//      if (TMath::IsNaN(c0) || TMath::IsNaN(cl) || TMath::IsNaN(cr) || cl < 1 || cr < 1 ) return;
//      if ( id0!=29 ) {
//
//      if ( (c0-cl)/(c0+cl) < 0.04 && nData > 2 ){
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter1)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset);
//     } else if ( (c0-cr)/(c0+cr) < 0.04 && nData > 2){
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter2)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset);
//     } else {
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter1)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.506329 + (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter2)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.493671;
//     }}
//      else {    
//      if ( (c0-cl)/(c0+cl) < 0.04 && nData > 2 ){
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter3)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset);
//     } else if ( (c0-cr)/(c0+cr) < 0.04 && nData > 2){
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter4)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset);
//     } else {
//      pos = (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter3)->Convert((c0 - cl)/(c0 + cl))) * ( 1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.506329 + (fTurned ? -1 : 1)  * ((id0 - fCenter + (0.5 - (*fConverter4)->Convert((c0 - cr)/(c0 + cr))) * ( -1.0 ) * 1.0) * fStripWidth  - fDetOffset)*0.493671;
//     }}} else {
//         return;
//      }


//   TSRPPACPlaneData *outData = static_cast<TSRPPACPlaneData*>(fOutput->ConstructedAt(0));
//   outData->SetID(idl);
//   outData->SetCharge(cl);
//   outData->SetPosition(pos);
//   outData->SetProcessed(kTRUE);
 
  Int_t ID[3] = {id0, idl, idr};
  Double_t CHARGE[3] = {c0, cl, cr};
  
  for (int i = 0; i != 3; ++i){  
   TSRPPACPlaneData *outData = static_cast<TSRPPACPlaneData*>(fOutput->ConstructedAt(i));
   outData->SetID(ID[i]);
   outData->SetCharge(CHARGE[i]);
   outData->SetPosition(pos);
   outData->SetProcessed(kTRUE);
 }

}

