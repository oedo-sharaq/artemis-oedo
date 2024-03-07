#ifndef TDIATIMINGDATAMAPPINGPROCESSOR_H
#define TDIATIMINGDATAMAPPINGPROCESSOR_H

#include <TProcessor.h>

namespace art {
  class TDiaTimingDataMappingProcessor;
  class TCategorizedData;
}

class art::TDiaTimingDataMappingProcessor : public TProcessor {
 public:
  TDiaTimingDataMappingProcessor();
  virtual ~TDiaTimingDataMappingProcessor();

  virtual void Init(TEventCollection *col);
  virtual void Process();

 protected:
  TString            fInputColName;
  TString            fOutputColName;
  TCategorizedData **fCategorizedData;
  TClonesArray      *fOutputArray;

  Int_t fCatID;       // category id
  Int_t fDataTypeID;  // typeid for data

  Bool_t fIsSparse;

 private:
  TDiaTimingDataMappingProcessor(const TDiaTimingDataMappingProcessor&);
  TDiaTimingDataMappingProcessor& operator=(const TDiaTimingDataMappingProcessor&);

  ClassDef(TDiaTimingDataMappingProcessor,0) // simple data mapper
};

#endif //TDIATIMINGDATAMAPPINGPROCESSOR_H
