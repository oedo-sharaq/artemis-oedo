/**
 * @file		TS1IonChamberProcessor.cc
 * @brief		S1 IC analysis
 *
 * @date		Created				: 2016-10-16 (nakano)
 *
 * 					Last Modified : 2017-06-13 15:48 JST (nakano)
 *
 * @author NAKANO Keita <knakano@aees.kyushu-u.ac.jp>
 *
 */

#include "TS1IonChamberProcessor.h"

#include <TClonesArray.h>
#include <ICharge.h>
#include <TSimpleData.h>

using art::TS1IonChamberProcessor;

ClassImp(TS1IonChamberProcessor)

TS1IonChamberProcessor::TS1IonChamberProcessor()
 : fInput(NULL), fOutput(NULL) {
	RegisterInputCollection("Input", "name of input collection for ic",
	fInputName, TString("f11ic_raw"),
	&fInput, TClonesArray::Class_Name(),
	art::ICharge::Class_Name());
//	RegisterProcessorParameter("Calib", "0: output non calibrated data, 1: output calibrated data",
//	fCalib, 0);
	RegisterProcessorParameter("DoSubtraction", "0: Summation, 1: Subtraction",
	fDoSubtraction, 0);
	RegisterProcessorParameter("NumChannel", "number of channel of F11IC",
	fNumCh, 30);
	RegisterOutputCollection("Output", "name of output collection",
	fOutputName, TString("f11ic"),
	&fOutput, TClonesArray::Class_Name(),
	art::TSimpleData::Class_Name());
}

TS1IonChamberProcessor::~TS1IonChamberProcessor()
{
}
/*
void TS1IonChamberProcessor::Init(TEventCollection* )
{
// q_cor[ch] = a[ch][1] * q[ch] +	a[ch][0]
				a[0][0] = 0.;				a[0][1]	= 1.;		
				a[1][0] = 0.;				a[1][1]	= 1.;		
				a[2][0] = 0.;				a[2][1]	= 1.;		
				a[3][0] = 0.;				a[3][1]	= 1.;		
				a[4][0] = 0.;				a[4][1]	= 1.;		
				a[5][0] = 0.;				a[5][1]	= 1.;		
				a[6][0] = 0.;				a[6][1]	= 1.;		
				a[7][0] = 0.;				a[7][1]	= 1.;		
				a[8][0] = 0.;				a[8][1]	= 1.;		
				a[9][0] = 0.;				a[9][1]	= 1.;		
				a[10][0] = 0.;				a[10][1]	= 1.;		
				a[11][0] = 0.;				a[11][1]	= 1.;		
				a[12][0] = 0.;				a[12][1]	= 1.;		
				a[13][0] = 0.;				a[13][1]	= 1.;		
				a[14][0] = 0.;				a[14][1]	= 1.;		
				a[15][0] = 0.;				a[15][1]	= 1.;		
				a[16][0] = 0.;				a[16][1]	= 1.;		
				a[17][0] = 0.;				a[17][1]	= 1.;		
				a[18][0] = 0.;				a[18][1]	= 1.;		
				a[19][0] = 0.;				a[19][1]	= 1.;		
				a[20][0] = 0.;				a[20][1]	= 1.;		
				a[21][0] = 0.;				a[21][1]	= 1.;		
				a[22][0] = 0.;				a[22][1]	= 1.;		
				a[23][0] = 0.;				a[23][1]	= 1.;		
				a[24][0] = 0.;				a[24][1]	= 1.;		
				a[25][0] = 0.;				a[25][1]	= 1.;		
				a[26][0] = 0.;				a[26][1]	= 1.;		
				a[27][0] = 0.;				a[27][1]	= 1.;		
				a[28][0] = 0.;				a[28][1]	= 1.;		
				a[29][0] = 0.;				a[29][1]	= 1.;		
}
*/

void TS1IonChamberProcessor::Process()
{
	fOutput->Clear("C");
	if ((*fInput)->GetEntriesFast() == 0) return;

	std::vector<Double_t> array(fNumCh,0);

	for(Int_t i = 0, n = (*fInput)->GetEntriesFast(); i!=n; ++i){
		const Int_t id = dynamic_cast<art::TDataObject*>((*fInput)->At(i))->GetID();
		if(id < fNumCh){
			const art::ICharge* const ic = dynamic_cast<art::ICharge*>((*fInput)->At(i));
			array[id] = ic->GetCharge();
		}
	}

	if (array.empty()) return;

/*
	if(fCalib){
		for(Int_t j = 0; j!=fNumCh; ++j){
			array[j] = array[j] * a[j][1] + a[j][0];
		}
	}
*/

	for(Int_t i = 0; i!=(0.5*fNumCh); ++i){

		output_t *const out = static_cast<TSimpleData*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
		const Double_t sum = fDoSubtraction
		? array[i*2] - array[i*2+1] : array[i*2] + array[i*2+1];
		out->SetID(i);
		out->SetValue(sum);
	}
}
