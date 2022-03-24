/**
 * @file	TS1IonChamberProcessor.h
 * @brief	S1 IC analysis
 *
 * @date	Created				:	2016-10-16 (nakano)
 *
 * 				Last Modified : 2016-10-13 15:49 JST (nakano)
 *
 * @author NAKANO Keita <knakano@aees.kyushu-u.ac.jp>
 *
 */

#ifndef TS1IONCHAMBERPROCESSOR_H
#define TS1IONCHAMBERPROCESSOR_H  

#include "TProcessor.h"

namespace art	{
	class TS1IonChamberProcessor;
	class TSimpleData;
}

class art::TS1IonChamberProcessor : public TProcessor {
public:
	TS1IonChamberProcessor();
	virtual ~TS1IonChamberProcessor();

//	virtual void Init(TEventCollection *col);

	void Process();

protected:
//	typedef					art::ICharge input_t;
	typedef					TSimpleData output_t;

	TString					fInputName;
	TClonesArray  **fInput;

	Int_t						fNumCh;
	Int_t						fDoSubtraction;
//	Int_t						fCalib;

//	Double_t				a[30][2];

	TString					fOutputName;
	TClonesArray	 *fOutput;

private:
	TS1IonChamberProcessor(const TS1IonChamberProcessor&);
	TS1IonChamberProcessor& operator=(const TS1IonChamberProcessor&);

	ClassDef(TS1IonChamberProcessor,0)
};

#endif // TS1IONCHAMBERPROCESSOR_H  
