#include "TDiaStripTimingProcessor.h"
#include <TClonesArray.h>
#include "TDiaStripData.h"
#include "TDiaPadData.h"
#include "TDiaData.h"
#include <TTimingChargeData.h>

#include "constant.h"

using art::TDiaStripTimingProcessor;

ClassImp(TDiaStripTimingProcessor)

#define N_MAX_STRIP 6 // number of max diamond strips. In SHARAQ03, we used 6 strip in total (2+4=6).

TDiaStripTimingProcessor::TDiaStripTimingProcessor()
{
  const IntVec_t defDetIDRange(2,1); // [1,1]
  IntVec_t defTDiffGateRange;
  defTDiffGateRange.push_back(-1000000);
  defTDiffGateRange.push_back( 1000000);

  RegisterInputCollection("InputCollection1","name of input collection (dia strip)",fInputColName1,TString("input1"),
			  &fInput1,TClonesArray::Class_Name(),TDiaStripData::Class_Name());
  RegisterInputCollection("InputCollection2","name of input collection (dia pad)",fInputColName2,TString("input2"),
			  &fInput2,TClonesArray::Class_Name(),TDiaPadData::Class_Name());
  RegisterInputCollection("QTCStripL","QTC in Strip L",fQTCStripLName,TString("qtc_strip_l"),
			  &fQTCStripL,TClonesArray::Class_Name(),TTimingChargeData::Class_Name());
  RegisterInputCollection("QTCStripR","QTC in Strip R",fQTCStripRName,TString("qtc_strip_r"),
			  &fQTCStripR,TClonesArray::Class_Name(),TTimingChargeData::Class_Name());
  RegisterOutputCollection("OutputCollection","name of output collection",fOutputColName,TString("output"),
			   &fOutput,TClonesArray::Class_Name(),TDiaData::Class_Name());
  RegisterProcessorParameter("DetIDRange_Strip","range of detector ID (dia strip)",
			     fDetIDRange_strip,defDetIDRange);
  RegisterProcessorParameter("DetID_Pad","detector ID (dia pad)",
			     fDetID_pad,0);
  RegisterProcessorParameter("UseTDiffStripPadGate",
  			     "enables TDiffStripPad gate. If non-zero, strip timing does not filled to *.fTiming (e.g. dia_t_f3.fTiming).",
  			     fUseTDiffStripPadGate,0);

  RegisterProcessorParameter("MultiStripAnalysis","analyze events where more than 1 strip is fired if fMultiStripAnalysis==1 (default: 0).",
			     fMultiStripAnalysis,0);

  RegisterProcessorParameter("UseTDiffStripGate","enables TDiffStrip gate if fnHitStrip==1.",
			     fUseTDiffStripGate,0);
  RegisterProcessorParameter("TDiffStrip1","Valid range of TDiffStripGate in Strip1.",
			     fTDiffStrip1,defTDiffGateRange);
  RegisterProcessorParameter("TDiffStrip2","Valid range of TDiffStripGate in Strip2.",
			     fTDiffStrip2,defTDiffGateRange);
  RegisterProcessorParameter("TDiffStrip3","Valid range of TDiffStripGate in Strip3.",
			     fTDiffStrip3,defTDiffGateRange);
  RegisterProcessorParameter("TDiffStrip4","Valid range of TDiffStripGate in Strip4.",
			     fTDiffStrip4,defTDiffGateRange);


  RegisterProcessorParameter("UseQGate","enables QTC gate if fnHitStrip==1.",
			     fUseQGate,0);
  RegisterProcessorParameter("QminStrip1","Minimum value of Qgate in Strip1. If Q > QminStrip, QGate is true.",
			     fQminStrip1,(Float_t)-100000.);
  RegisterProcessorParameter("QminStrip2","Minimum value of Qgate in Strip2. If Q > QminStrip, QGate is true.",
			     fQminStrip2,(Float_t)-100000.);
  RegisterProcessorParameter("QminStrip3","Minimum value of Qgate in Strip3. If Q > QminStrip, QGate is true.",
			     fQminStrip3,(Float_t)-100000.);
  RegisterProcessorParameter("QminStrip4","Minimum value of Qgate in Strip4. If Q > QminStrip, QGate is true.",
			     fQminStrip4,(Float_t)-100000.);
}

TDiaStripTimingProcessor::~TDiaStripTimingProcessor()
{
}

TDiaStripTimingProcessor::TDiaStripTimingProcessor(const TDiaStripTimingProcessor& rhs)
{
}

TDiaStripTimingProcessor& TDiaStripTimingProcessor::operator=(const TDiaStripTimingProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}

void TDiaStripTimingProcessor::Init(TEventCollection *col)
{
   Info("Init","(%s,%s) => %s",
	fInputColName1.Data(),fInputColName2.Data(),fOutputColName.Data());

   Info("Init","QTC: %s, %s",
	fQTCStripLName.Data(),fQTCStripRName.Data());

   fNDet = fDetIDRange_strip[1] - fDetIDRange_strip[0] + 1;
   if (fNDet>0) {
      Info("Init","ID range: [%d:%d], ndet = %d",fDetIDRange_strip[0],fDetIDRange_strip[1],fNDet);
   } else {
      SetStateError("invalid ID range!");
      return;
   }
   
   /*   
   if (fUseTDiffStripPadGate) {
     Info("Init","TDiffStripPadGate is applied. Strip timing is selected to be filled.");
   } else {
     Info("Init","TDiffStripPadGate is not applied. All of strip timings are filled.");
   }
   */

   if (fUseTDiffStripGate) {
     Info("Init","TDiffStripGate is applied. Strip timing is selected to be filled.");
   } else {
     Info("Init","TDiffStripGate is not applied. All of strip timings are filled.");
   }

   if (fMultiStripAnalysis) {
     if (!fUseTDiffStripGate && !fUseQGate) {
       SetStateError("invalid! If fMultiStripAnalysis==1, at least one of fUseTDiffStripGate and fUseQGate should be 1.");
       return;
     } else {
       Info("Init","Analyze events where more than one strip is hit.");
     }
   } else {
     Info("Init","Analyze events where only one strip is hit.");
   }
   
   if ( !((fDetIDRange_strip[0]==0)&&(fDetIDRange_strip[1]==1)) && !((fDetIDRange_strip[0]==2)&&(fDetIDRange_strip[1]==5)) ) { // !!
      SetStateError("invalid ID range! DetIDRange should be [0,1] or [2,5] in SHARAQ03 analysis");
      return;
   }

   if ( fDetIDRange_strip[0] == 0 && fDetIDRange_strip[1] == 1 ) { // F3DiaStrip
     fTDiffGateMin.push_back(fTDiffStrip2[0]);
     fTDiffGateMin.push_back(fTDiffStrip3[0]);

     fTDiffGateMax.push_back(fTDiffStrip2[1]);
     fTDiffGateMax.push_back(fTDiffStrip3[1]);

     fQGateMin.push_back(fQminStrip2);
     fQGateMin.push_back(fQminStrip3);
   } else if ( fDetIDRange_strip[0] == 2 && fDetIDRange_strip[1] == 5 ) { //S2DiaStrip
     fTDiffGateMin.push_back(0);
     fTDiffGateMin.push_back(0);
     fTDiffGateMin.push_back(fTDiffStrip1[0]);
     fTDiffGateMin.push_back(fTDiffStrip2[0]);
     fTDiffGateMin.push_back(fTDiffStrip3[0]);
     fTDiffGateMin.push_back(fTDiffStrip4[0]);

     fTDiffGateMax.push_back(0);
     fTDiffGateMax.push_back(0);
     fTDiffGateMax.push_back(fTDiffStrip1[1]);
     fTDiffGateMax.push_back(fTDiffStrip2[1]);
     fTDiffGateMax.push_back(fTDiffStrip3[1]);
     fTDiffGateMax.push_back(fTDiffStrip4[1]);

     fQGateMin.push_back(0);
     fQGateMin.push_back(0);
     fQGateMin.push_back(fQminStrip1);
     fQGateMin.push_back(fQminStrip2);
     fQGateMin.push_back(fQminStrip3);
     fQGateMin.push_back(fQminStrip4);
   }
}


void TDiaStripTimingProcessor::Process()
{
   fOutput->Clear("C");
   Int_t nHit1 = (*fInput1)->GetEntriesFast();
   Int_t nHit2 = (*fInput2)->GetEntriesFast();

   Double_t t_strip_each[nHit1], t_strip_each_val[nHit1], t_strip = kInvalidD, t_pad = kInvalidD;
   Double_t tdiff_strip_each[nHit1];
   Int_t nHitStrip = 0;
   Int_t iHitStripID_last = 0;

   Double_t t_min = 1.e5;
   Int_t id_min = -0.5;

   Double_t TDiffStripPad[2] = {-100, 100};
   const Double_t TDiffStripPad_F3[2] = {-2.0, -0.5}; // !!
   const Double_t TDiffStripPad_S2[2] = {-2.0, -0.5}; // !!
   if (fDetIDRange_strip[0] == 0) { // F3
     for(int i=0; i<2; i++) TDiffStripPad[i] = TDiffStripPad_F3[i];
   } else if (fDetIDRange_strip[0] == 2) { // S2
     for(int i=0; i<2; i++) TDiffStripPad[i] = TDiffStripPad_S2[i];
   }
   

   for (Int_t icount=0; icount<nHit1; icount++){
     t_strip_each[icount] = kInvalidD;
     tdiff_strip_each[icount] = kInvalidD;
   }
   
   for (Int_t iHit = fDetIDRange_strip[0]; iHit <= fDetIDRange_strip[1]; iHit++) {
     TDiaStripData *data1 = (TDiaStripData*) (*fInput1)->At(iHit);
     t_strip_each[iHit] = data1->GetTiming(); // !! 
     tdiff_strip_each[iHit] = data1->GetTDiff(); // !! 
  
    if ( tdiff_strip_each[iHit] > fTDiffGateMin[iHit] && tdiff_strip_each[iHit] < fTDiffGateMax[iHit] ){
       t_strip_each_val[iHit] = t_strip_each[iHit]; // !! 
       iHitStripID_last = iHit;
       nHitStrip++;
     }else {
       continue; 
	 }
    }

   TDiaData *out  = (TDiaData*) fOutput->ConstructedAt(fOutput->GetEntriesFast());
   if(nHitStrip==1){
       t_strip = t_strip_each_val[iHitStripID_last];   
       out -> SetTiming(t_strip);
       out -> SetIDHitStrip(iHitStripID_last);
       out -> ValidateOneStripHit();
   } else {
	for(int i = fDetIDRange_strip[0]; i <= fDetIDRange_strip[1]; i++) {
     if (t_min > t_strip_each_val[i]) {
	  t_min = t_strip_each_val[i];
	  id_min = i;
	  }
     }
      out -> SetTiming(t_min);
      out -> SetIDHitStrip(id_min);
     
   }
//   TDiaPadData *data2 = (TDiaPadData*) (*fInput2)->At(fDetID_pad);
//   Bool_t IsHitPad = false;
//   if (data2->IsHitPad()){
//     t_pad = (data2->GetTiming()); // !! 
//     IsHitPad = true;
//   }
   
//   Double_t q_strip_l[N_MAX_STRIP], q_strip_r[N_MAX_STRIP], q_strip_mean[N_MAX_STRIP];
//   for (Int_t k = 0; k < N_MAX_STRIP; ++k) {
//     q_strip_l[k]    = TMath::QuietNaN();
//     q_strip_r[k]    = TMath::QuietNaN();
//     q_strip_mean[k] = TMath::QuietNaN();
//   }
//
//   Int_t id;
//   //   printf("[strip_l entry = %d, strip_r entry = %d]\n", (*fQTCStripL)->GetEntriesFast(), (*fQTCStripR)->GetEntriesFast());
//   for (Int_t iHit = 0; iHit < (*fQTCStripL)->GetEntriesFast() ; ++iHit) {
//     TTimingChargeData *data_qtc_strip_l = (TTimingChargeData*) (*fQTCStripL)->At(iHit);
//
//     //     printf("id = %d: ", data_qtc_strip_l->GetDetID());
//     id = data_qtc_strip_l->GetDetID();
//     if ( id  >= 0) {
//       q_strip_l[id] = data_qtc_strip_l -> GetCharge();
//     }
//   }
//   for (Int_t iHit = 0; iHit < (*fQTCStripR)->GetEntriesFast() ; ++iHit) {
//     TTimingChargeData *data_qtc_strip_r = (TTimingChargeData*) (*fQTCStripR)->At(iHit);
//
//     id = data_qtc_strip_r->GetDetID();
//     if ( id >= 0) {
//       q_strip_r[id] = data_qtc_strip_r -> GetCharge();
//     }
//   }
//   for (id = 0; id < N_MAX_STRIP; ++id) {
//     q_strip_mean[id] = TMath::Sqrt(q_strip_l[id]*q_strip_r[id]);
//   }
//
//   TDiaData *out  = (TDiaData*) fOutput->ConstructedAt(fOutput->GetEntriesFast());
//   if (IsHitPad) {
//     out -> ValidatePadHit();
//   }
//   out -> SetPadTiming(t_pad);          
//
//   if( nHitStrip == 1 ) {
//     t_strip = t_strip_each[iHitStripID_last];
//
//     /*     
//     if ( t_strip-t_pad > TDiffStripPad[0] && t_strip-t_pad < TDiffStripPad[1] ) {
//       out -> ValidateGoodTDiffStripPad();
//     }
//     if ( !(fUseTDiffStripPadGate && !out->IsGoodTDiffStripPad()) ) {
//       out -> SetTiming(t_strip);
//     }
//     */
     
//     if (fUseTDiffStripGate) {
//       for (id = fDetIDRange_strip[0]; id <= fDetIDRange_strip[1]; ++id) {
//	 if ( tdiff_strip_each[id] > fTDiffGateMin[id] && tdiff_strip_each[id] < fTDiffGateMax[id] ) { // TDiffMin < TDiff < TDiffMax
//	   out -> SetTiming(t_strip);
//	   out -> SetIDHitStrip(iHitStripID_last);
//	   out -> ValidateOneStripHit();
//	   out -> SetTDiffStripPad(t_strip - t_pad);
//	 }
//       } 
//     } else { // fUseTDiffStripGate==0
//       out -> SetTiming(t_strip);
//       out -> SetIDHitStrip(iHitStripID_last);
//       out -> ValidateOneStripHit();
//       out -> SetTDiffStripPad(t_strip - t_pad);
//     }
//
//   } else if ( nHitStrip > 1 && fMultiStripAnalysis ) { // nHitStrip>1 && fMultiStripAnalysis==1
//     Int_t nValidHitStrip = 0;
//     Int_t iValidHitStripID_last = 0;
//
//     if ( fUseTDiffStripGate && !fUseQGate) {
//       for (id = fDetIDRange_strip[0]; id <= fDetIDRange_strip[1]; ++id) {
//	 if ( tdiff_strip_each[id] > fTDiffGateMin[id] && tdiff_strip_each[id] < fTDiffGateMax[id] ) {
//	   iValidHitStripID_last = id;
//	   ++nValidHitStrip;
//	 }
//       }
//       if (nValidHitStrip == 1) {
//	 t_strip = t_strip_each[iValidHitStripID_last];
//	 out -> SetTiming(t_strip);
//	 out -> SetIDHitStrip(iValidHitStripID_last);
//	 //	 out -> ValidateOneStripHit();
//	 out -> SetTDiffStripPad(t_strip - t_pad);
//       }
//     } else if ( !fUseTDiffStripGate && fUseQGate) {
//       for (id = fDetIDRange_strip[0]; id <= fDetIDRange_strip[1]; ++id) {
//	 if ( q_strip_mean[id] > fQGateMin[id] ) {
//	   iValidHitStripID_last = id;
//	   ++nValidHitStrip;
//	 }
//       }
//       if (nValidHitStrip == 1) {
//	 t_strip = t_strip_each[iValidHitStripID_last];
//	 out -> SetTiming(t_strip);
//	 out -> SetIDHitStrip(iValidHitStripID_last);
//	 //	 out -> ValidateOneStripHit();
//	 out -> SetTDiffStripPad(t_strip - t_pad);
//       }
//     } else if ( fUseTDiffStripGate && fUseQGate) {
//       for (id = fDetIDRange_strip[0]; id <= fDetIDRange_strip[1]; ++id) {
//	 if ( tdiff_strip_each[id] > fTDiffGateMin[id] && tdiff_strip_each[id] < fTDiffGateMax[id] 
//	      && q_strip_mean[id] > fQGateMin[id] ) {
//	   iValidHitStripID_last = id;
//	   ++nValidHitStrip;
//	 }
//       }
//       if (nValidHitStrip == 1) {
//	 t_strip = t_strip_each[iValidHitStripID_last];
//	 out -> SetTiming(t_strip);
//	 out -> SetIDHitStrip(iValidHitStripID_last);
//	 //	 out -> ValidateOneStripHit();
//	 out -> SetTDiffStripPad(t_strip - t_pad);
//       }
//     }
//     
//   }
   out -> SetnHitStrip(nHitStrip);

}
