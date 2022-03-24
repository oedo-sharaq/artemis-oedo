/**
 * @file   TTOF2BetaProcessor.h
 * @brief  calculate beta from TOF and flight length
 *
 * @date   Created       : 2016-05-26 17:41:43 JST
 *         Last Modified : 2016-06-01 10:37:10 JST (kawase)
 * @author KAWASE Shoichiro <kawase@aees.kyushu-u.ac.jp>
 *
 *    (C) 2016 KAWASE Shoichiro
 */

#ifndef INCLUDE_GUARD_UUID_17B62116_F137_40E5_9909_5C0F3BF21452
#define INCLUDE_GUARD_UUID_17B62116_F137_40E5_9909_5C0F3BF21452

#include "TProcessor.h"
#include <map>

namespace art {
   class TTOF2BetaProcessor;
   template <class K,class V> class TParameterMap;
   typedef TParameterMap<TString,Float_t> PrmMapFloat_t;
}

class art::TTOF2BetaProcessor : public TProcessor {
public:
   TTOF2BetaProcessor();
   virtual ~TTOF2BetaProcessor();

   void Init(TEventCollection*);
   void Process();

protected:
   TString        fInputName;
   TClonesArray **fInput; //! TOF (nsec) in TClonesArray of TTimeDifference

   TString       fOutputName;
   TClonesArray *fOutput;  // output beta collection (TSimpleData)

   TString        fFlightLengthMapName; // name of parameter map for flight length
//   PrmMapFloat_t *fFlightLengthMap; // parameter map for flight length
//   TString        fFlightLengthKey; // key for parameter map
//   const Float_t *fFlightLength;    // flight length (mm)
   Float_t        fFlightLength;

private:
   TTOF2BetaProcessor(const TTOF2BetaProcessor&);
   TTOF2BetaProcessor& operator=(const TTOF2BetaProcessor&);

   ClassDef(TTOF2BetaProcessor,0) // calculate beta from TOF and flight length
};

#endif // INCLUDE_GUARD_UUID_17B62116_F137_40E5_9909_5C0F3BF21452
