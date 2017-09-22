#include "TStarJetV0Cuts.hh"
#include "St_base/StMessMgr.h"

#include <string>

ClassImp(TStarJetV0Cuts)

TStarJetV0Cuts::TStarJetV0Cuts()
  : mNV0s(0), mAcceptedV0s(0),
    mDCAv0ToVtx(0), mDCADaughter(0),
    mDCAPosToVtx(0), mDCANegToVtx(0),
    mHitsPos(0), mHitsNeg(0),
    mDecayLength(0),mNSigma(0) {}

TStarJetV0Cuts::~TStarJetV0Cuts() {}

void   TStarJetV0Cuts::SetDefaultAuAu() {
  mDCAv0ToVtx  = 0.5;
  mDCADaughter = 0.8;
  mDCAPosToVtx = 1.3;
  mDCANegToVtx = 1.3;
  mHitsPos    = 15;
  mHitsNeg    = 15;
  mDecayLength= 0;
  mNSigma     = 2;
}

void   TStarJetV0Cuts::SetDefaultPP() {
  mDCAv0ToVtx  = 0.5;
  mDCADaughter = 0.8;
  mDCAPosToVtx = 1.3;
  mDCANegToVtx = 1.3;
  mHitsPos    = 15;
  mHitsNeg    = 15;
  mDecayLength= 3;
  mNSigma     = 2;
}

Bool_t TStarJetV0Cuts::AcceptV0(StMuDst* mu, StV0MuDst *v0) {
  mNV0s++;
  
  // first do dca & nhit cuts
  Bool_t accept = kTRUE;
  if (v0->topologyMapPos().numberOfHits(kTpcId) < mHitsPos) {accept = kFALSE;}
  if (v0->topologyMapNeg().numberOfHits(kTpcId) < mHitsNeg) {accept = kFALSE;}
  if (v0->decayLengthV0() < mDecayLength)                   {accept = kFALSE;}
  if (v0->dcaV0Daughters() < mDCADaughter)                  {accept = kFALSE;}
  if (v0->dcaPosToPrimVertex() < mDCAPosToVtx)              {accept = kFALSE;}
  if (v0->dcaNegToPrimVertex() < mDCANegToVtx)              {accept = kFALSE;}
  
  // next, pid cut
  UInt_t pos_idx=0;
  UInt_t neg_idx=0;
  UInt_t n_globals = mu->globalTracks()->GetEntries();
  for (UInt_t i = 0; i < n_globals; ++i) {
    if (pos_idx && neg_idx) break;
    
    if (mu->globalTracks(i)->id() == v0->keyNeg()) {
      neg_idx = i;
      if (mu->globalTracks(i)->nSigmaPion() > mNSigma &&
           mu->globalTracks(i)->nSigmaProton() > mNSigma) {
        accept = kFALSE;
      }
    }
    
    if (mu->globalTracks(i)->id() == v0->keyPos()) {
      pos_idx = i;
      
      if (mu->globalTracks(i)->nSigmaPion() > mNSigma &&
           mu->globalTracks(i)->nSigmaProton() > mNSigma) {
        accept = kFALSE;
      }
    }
  }
  if (accept) {
    mAcceptedV0s++;
    return kTRUE;
  }
  else {
    return kFALSE;
  }
}

Bool_t TStarJetV0Cuts::SetDCAV0ToVertex(Double_t dca) {
  mDCAv0ToVtx = dca;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetDCAPosToNeg(Double_t dca) {
  mDCADaughter = dca;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetDCAPosToVertex(Double_t dca) {
  mDCAPosToVtx = dca;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetDCANegToVertex(Double_t dca) {
  mDCANegToVtx = dca;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetNHitsPos(UInt_t hits) {
  mHitsPos = hits;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetNHitsNeg(UInt_t hits) {
  mHitsNeg = hits;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetDecayLength(Double_t len) {
  mDecayLength = len;
  return kTRUE;
}

Bool_t TStarJetV0Cuts::SetNSigma(Double_t nsig) {
  mNSigma = nsig;
  return kTRUE;
}

void TStarJetV0Cuts::PrintStats() {
  
  LOG_INFO << "// ----------------- TStarJetV0Cuts ----------------- //" << endm;
  LOG_INFO << "cuts: " << endm;
  LOG_INFO << " v0 to vertex DCA: " << mDCAv0ToVtx << endm;
  LOG_INFO << " positive daughter to vertex DCA: " << mDCAPosToVtx << endm;
  LOG_INFO << " negative daughter to vertex DCA: " << mDCANegToVtx << endm;
  LOG_INFO << " daughter to daughter DCA: " << mDCADaughter << endm;
  LOG_INFO << " positive daughter nHits in TPC: " << mHitsPos << endm;
  LOG_INFO << " negative daughter nHits in TPC: " << mHitsNeg << endm;
  LOG_INFO << " decay length:  " << mDecayLength << endm;
  LOG_INFO << " NSigma for particle ID: " << mNSigma << endm;
  LOG_INFO << endm;
  LOG_INFO << "results: " << endm;
  LOG_INFO << "number of v0s: " << mNV0s << endm;
  LOG_INFO << "number of accepted v0s: " << mAcceptedV0s << endm;
  LOG_INFO << "fraction accepted: " << (double) mAcceptedV0s / mNV0s << endm;
  LOG_INFO << endm;
  LOG_INFO << "// -----------------       end      ----------------- //" << endm;
  
}




