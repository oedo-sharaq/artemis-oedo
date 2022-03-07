/**
 * @file   TCatTpcHitClusterProcessor.cc
 * @brief  make cluster of tpc hits
 *
 * @date   Created       : 2016-04-17 04:46:27 JST
 *         Last Modified : 2019-07-04 21:59:25 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    (C) 2016 Shinsuke OTA
 */

#include "TCatTpcHitClusterProcessor.h"

#include <TClonesArray.h>

#include <TCatReadoutPadArray.h>
#include <TCatReadoutPad.h>
#include <TCatPulseShape.h>
#include <TCatTrackResult.h>
#include <TCatTrackResultPulse.h>
#include <vector>
#include <list>
#include <TCatTpcTrack.h>
#include <TMath.h>
#include <TArtSystemOfUnit.h>
using art::TCatTpcHitClusterProcessor;

ClassImp(TCatTpcHitClusterProcessor)


namespace {
   // typedef's for container
   typedef std::vector<art::TCatPulseShape*> pulseVec_t;
   typedef std::vector<pulseVec_t> clusterVec_t;
   typedef std::list<pulseVec_t> clusterList_t;

   template <class T>
   bool compare_size(std::vector<T> &first,std::vector<T> &second) {
      return (first.size() > second.size());
   }

   bool concatClusters(clusterVec_t &clusters, Double_t radZX, Double_t radY) {
      Bool_t found = kFALSE;
      const clusterVec_t::iterator end = clusters.end();
      clusterVec_t::iterator it1 = clusters.begin();
      clusterVec_t::iterator it2;
      for (; it1 < end; ++it1) {
         for (it2 = it1 + 1;  it2 < end; ++it2) {
            for (pulseVec_t::iterator it3 = (*it1).begin(), end3 = (*it1).end();  it3 != end3; ++it3) {
               for (pulseVec_t::iterator it4 = (*it2).begin(), end4 = (*it2).end();  it4 != end4; ++it4) {
                  art::TCatPulseShape *p1 = *it3;
                  art::TCatPulseShape *p2 = *it4;
                  TVector3 diff = p1->GetPos() - p2->GetPos();
                  if (TMath::Sqrt(diff.X()*diff.X() + diff.Z() * diff.Z()) < radZX &&
                      TMath::Abs(diff.Y()) < radY) {
                     found = kTRUE;
                     break;
                  }
               }
               if (found) break;
            }
            if (found) break;
         }
         if (found) break;
      }
      if (!found) return kFALSE;
      pulseVec_t &cls1 = (*it1);
      pulseVec_t &cls2 = (*it2);
      std::copy(cls2.begin(),cls2.end(),std::back_inserter(cls1));
      clusters.erase(it2);
      concatClusters(clusters,radZX,radY);
      return kTRUE;
   }
}

TCatTpcHitClusterProcessor::TCatTpcHitClusterProcessor()
: fInputName(""), fInput(NULL), fOutputName(""), fOutput(NULL), fReadoutPadArrayName(""), fReadoutPadArray(NULL)
{

   DoubleVec_t defClusterRadius;
   defClusterRadius.push_back(8.1);
   defClusterRadius.push_back(21);
   DoubleVec_t defPulseLength(2);
   defPulseLength[0] = 0;
   defPulseLength[1] = 100;

   RegisterInputCollection("InputCollection","input pulse collection (for a specific region)",fInputName,TString("atpulse"),
                           &fInput,TClonesArray::Class_Name(),TCatPulseShape::Class_Name());
   RegisterOutputCollection("OutputCollection","output pulse collection as a candidate of recoil track",fOutputName,TString("atcluster"),
                           &fOutput,TClonesArray::Class_Name(),TCatTpcTrack::Class_Name());
   RegisterInputInfo("ReadoutPad","Name of readout pad array",fReadoutPadArrayName,TString("readoutPad"),
                     &fReadoutPadArray,TCatReadoutPadArray::Class_Name());
   RegisterProcessorParameter("ClusterRadius","radius of cluster",fClusterRadius,defClusterRadius);
   RegisterProcessorParameter("MinClusterSize","required minimum cluster size ",fMinClusterSize,5.);
   RegisterProcessorParameter("IsSingle","select maximum size cluster if 1 (default: 0)",fIsSingle,kTRUE);
   RegisterProcessorParameter("MinHeight","minimum pulse height",fMinHeight,0.);
   RegisterProcessorParameter("PulseLengthRange","range of pulse length [start,end]. ([0,100])",fPulseLengthRange,defPulseLength);
   RegisterProcessorParameter("SelectIf","select all if 0, inside if 1 and outside if 2. The region is indicated by SelectedRegion",
                              fSelectIf,0);
   RegisterProcessorParameter("SelectedRegion","selected region defined by box [x1,y1,x2,y2]",fSelectedRegion,DoubleVec_t(4,0.));
   RegisterProcessorParameter("ReadoutPadType","select readout pad type 2 if 2 (default: 2)",fReadoutPadType,2);
   RegisterProcessorParameter("DoTrackUpdate","flag for updating track",fDoTrackUpdate,kFALSE);
   RegisterHelper(&fTrackUpdateHelper);
   fTrackUpdateHelper.SetUpdateTracks(&fOutput);
   RegisterProcessorParameter("ChargeWeightPower","order of power of weighted charge",fChargeWeightPower,1.);
   RegisterProcessorParameter("DriftVelocity", "drift velocity (cm/us)",fDriftVelocity,1.);
}

TCatTpcHitClusterProcessor::~TCatTpcHitClusterProcessor()
{
}

TCatTpcHitClusterProcessor::TCatTpcHitClusterProcessor(const TCatTpcHitClusterProcessor& rhs)
{
}

TCatTpcHitClusterProcessor& TCatTpcHitClusterProcessor::operator=(const TCatTpcHitClusterProcessor& rhs)
{
   if (this != &rhs) {

   }
   return *this;
}


void TCatTpcHitClusterProcessor::Init(TEventCollection *col)
{
   //======================================================================
   // check the type of readout pad aray
   Int_t id = (*fReadoutPadArray)->GetUniqueID() ;
Info("Init","Readout Pad Type = %d",id);

   //======================================================================
   // cluster radii for XZ and Y, respectively
   if (fClusterRadius.size() != 2) {
      SetStateError(Form("ClusterRadius has %d components while ClusterRadius should have two values for ZX plane and Y direction, respectively\n",(Int_t)fClusterRadius.size()));
      return;
   }


   //======================================================================
   // cluster radii for XZ and Y, respectively
   if (fSelectIf) {
      if (fSelectedRegion.size() != 4) {
         SetStateError(Form("SelectedRegion should be defined by box [x1,y1,x2,y2] (size = %d)\n",(Int_t)fSelectedRegion.size()));
      }
      if (fSelectedRegion[0] > fSelectedRegion[2]) {
         Double_t tmp = fSelectedRegion[0] ;
         fSelectedRegion[0] = fSelectedRegion[2];
         fSelectedRegion[2] = tmp;
      }
      if (fSelectedRegion[1] > fSelectedRegion[3]) {
         Double_t tmp = fSelectedRegion[1] ;
         fSelectedRegion[1] = fSelectedRegion[3];
         fSelectedRegion[3] = tmp;
      }
   }

   fDriftVelocity *= (TArtSystemOfUnit::cm / TArtSystemOfUnit::us);
}

void TCatTpcHitClusterProcessor::Process()
{
   // clear 
   fOutput->Clear("C");

   // initialize local variables
   pulseVec_t input;
   clusterVec_t cluster;

   Int_t nHits = (*fInput)->GetEntriesFast();
   TCatPulseShape::SetSortType(TCatPulseShape::kID);
   TCatPulseShape::SetSortOrder(TCatPulseShape::kASC);
   (*fInput)->Sort();
   (*fInput)->Compress();
   

   // ignore beam particle and bad pads
   for (Int_t iHit = 0; iHit != nHits; iHit++) {
      TCatPulseShape *pulse = (TCatPulseShape*) (*fInput)->UncheckedAt(iHit);
      TCatReadoutPad *pad = static_cast<TCatReadoutPad*>((*fReadoutPadArray)->UncheckedAt(pulse->GetID()));
      if (pad->IsBad()) continue;
      
      Bool_t doUse = kTRUE;
      if (fSelectIf) {
         // judge if pad is inside region
         Double_t padx = pulse->GetX();
         Double_t pady = pulse->GetZ();
         Double_t isInside = kTRUE;
         if (padx < fSelectedRegion[0] || fSelectedRegion[2] < padx ||
             pady < fSelectedRegion[1] || fSelectedRegion[3] < pady) {
            // outside region
            isInside = kFALSE;
         }
         switch (fSelectIf) {
         case 1:
            if (!isInside) doUse = kFALSE;
            break;
         case 2:
            if (isInside) doUse = kFALSE;
            break;
         default:
            break;
         }
      }            
             
      if (!doUse) continue;
      input.push_back(pulse);
      
   }

   for (pulseVec_t::iterator it1 = input.begin(), itend = input.end(); it1 != itend; ++it1) {
      Bool_t used = kFALSE;      
      for (clusterVec_t::iterator itCluster = cluster.begin(), itClusterEnd = cluster.end();
           itCluster != itClusterEnd;
           ++itCluster) {
         for (pulseVec_t::iterator itHitInCls = (*itCluster).begin(), itEndHitInCls = (*itCluster).end();
              itHitInCls != itEndHitInCls;
              ++itHitInCls) {

            TVector3 p1 = (*it1)->GetPos();
            TVector3 p2 = (*itHitInCls)->GetPos();
            Double_t y1 = p1.Y(); p1.SetY(0);
            Double_t y2 = p2.Y(); p2.SetY(0);

            if ((p1-p2).Mag() < fClusterRadius[0] && TMath::Abs(y1-y2) < fClusterRadius[1]) {
               (*itCluster).push_back(*it1);
               used = kTRUE;
               break;
            }
         }
         if (used) break;
      }
      if (!used) {
         cluster.resize(cluster.size() + 1);
         cluster.back().push_back(*it1);
      }
   }

   // find the neighbor clusters
   concatClusters(cluster,fClusterRadius[0],fClusterRadius[1]);
   
   clusterList_t candidates;
   for (clusterVec_t::iterator itCluster = cluster.begin(), itClusterEnd = cluster.end();
        itCluster != itClusterEnd; ++itCluster) {
//      printf("cluster[%d] size = %d\n",distance(itCluster,cluster.begin()),(*itCluster).size());
      if ((*itCluster).size() > fMinClusterSize) {
         candidates.push_back((*itCluster));
      }
   }

   candidates.sort(compare_size<TCatPulseShape*>);
   Int_t clusterID = 0;
   for (clusterList_t::iterator itc = candidates.begin(), itcEnd = candidates.end(); itc != itcEnd; ++itc,++clusterID) {
      TCatTpcTrack *track = static_cast<TCatTpcTrack*>(fOutput->ConstructedAt(fOutput->GetEntriesFast()));
      track->Init();
      track->SetChargeWeight(fChargeWeightPower);
   
      track->EstimateFromHits(*itc);
      track->SetID(clusterID);
      track->SetTimestamp(track->Y() / fDriftVelocity);
      if (fIsSingle) break;
   }

   fTrackUpdateHelper.StartCloseToOrigin();
   
   if (fDoTrackUpdate) {
      fTrackUpdateHelper.SetUpdateType(0,TCatTpcTrackUpdateHelper::kExtrapolateToOrigin);
      fTrackUpdateHelper.SetUpdateType(1,TCatTpcTrackUpdateHelper::kExtrapolateToOrigin);
      fTrackUpdateHelper.SetUpdateType(2,TCatTpcTrackUpdateHelper::kExtrapolateToOrigin);
      fTrackUpdateHelper.ExtrapolateToOrigin();
      fTrackUpdateHelper.SetUpdateType(0,TCatTpcTrackUpdateHelper::kNone);
      fTrackUpdateHelper.SetUpdateType(1,TCatTpcTrackUpdateHelper::kOffsetToOrigin);
      fTrackUpdateHelper.SetUpdateType(2,TCatTpcTrackUpdateHelper::kNone);
      fTrackUpdateHelper.OffsetToOrigin();
   }
#if 0
   for (Int_t i = 0, n = fOutput->GetEntriesFast(); i < n; ++i) {
      TCatTpcTrack *track = static_cast<TCatTpcTrack*>(fOutput->UncheckedAt(i));
      track->SetResults(track->GetHits(),track->GetStartPoint(),track->GetEndPoint(),&fChargeResponseHelper);
   }
#endif   
}
