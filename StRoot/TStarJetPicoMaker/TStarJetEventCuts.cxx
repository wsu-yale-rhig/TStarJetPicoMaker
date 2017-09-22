#include "TStarJetEventCuts.hh"
#include "St_base/StMessMgr.h"

#include <algorithm>
#include <string>
#include <sstream>

template <typename T> string tostr(const T& t) {
  std::ostringstream os;
  os<<t;
  return os.str();
}

ClassImp(TStarJetEventCuts)

TStarJetEventCuts::TStarJetEventCuts()
  : mNEvents(0), mEventsFailed(0), mEventsFailedVx(0),
    mEventsFailedVy(0),  mEventsFailedVz(0),
    mEventsFailedRef(0), mEventsFailedTrigger(),
    mEventsFailedTriggerTotal(0), mCheckVx(kFALSE),
    mCheckVy(kFALSE), mCheckVz(kFALSE), mCheckRefMult(kFALSE),
    mCheckTrigger(kFALSE), mUseGrefMult(kFALSE),
    mMinVx(0),   mMaxVx(0), mMinVy(0),   mMaxVy(0),
    mMinVz(0),   mMaxVz(0), mMinRef(0),  mMaxRef(0),
    mTriggers() {}

TStarJetEventCuts::~TStarJetEventCuts() {
  
}

bool TStarJetEventCuts::AcceptEvent(StMuEvent* event) {
  /* checks all cuts for all events, event if it 
     has already failed one - gives a better idea of 
     relative acceptance rates 
   */
  mNEvents++;
  bool accept_event = kTRUE;
  if (mCheckVx && !AcceptVx(event))           accept_event = kFALSE;
  if (mCheckVy && !AcceptVy(event))           accept_event = kFALSE;
  if (mCheckVz && !AcceptVz(event))           accept_event = kFALSE;
  if (mCheckRefMult && !AcceptRefMult(event)) accept_event = kFALSE;
  if (mCheckTrigger && !AcceptTrigger(event)) accept_event = kFALSE;
  if (accept_event != kTRUE) {mEventsFailed++; LOG_DEBUG << "Event Failed" << endm;}
  else {LOG_DEBUG << "Event Accepted" << endm;}
  return accept_event;
}

Bool_t TStarJetEventCuts::AcceptEvent(StPicoEvent* event) {
  /* checks all cuts for all events, event if it
   has already failed one - gives a better idea of
   relative acceptance rates
   */
  mNEvents++;
  Bool_t accept_event = kTRUE;
  if (mCheckVx && !AcceptVx(event))           accept_event = kFALSE;
  if (mCheckVy && !AcceptVy(event))           accept_event = kFALSE;
  if (mCheckVz && !AcceptVz(event))           accept_event = kFALSE;
  if (mCheckRefMult && !AcceptRefMult(event)) accept_event = kFALSE;
  if (mCheckTrigger && !AcceptTrigger(event)) accept_event = kFALSE;
  if (accept_event != kTRUE) {mEventsFailed++; LOG_DEBUG << "Event Failed" << endm;}
  else {LOG_DEBUG << "Event Accepted" << endm;}
  return accept_event;
}


Bool_t TStarJetEventCuts::AcceptVx(StMuEvent* event) {
  Double_t vx = event->primaryVertexPosition().x();
  if (vx > mMaxVx || vx < mMinVx) {
    LOG_DEBUG << "Fail: Vx=" << vx << " minVx=" << mMinVx << " maxVx=" << mMaxVx << endm;
    mEventsFailedVx++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vx=" << vx << " minVx=" << mMinVx << " maxVx=" << mMaxVx << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::AcceptVx(StPicoEvent* event) {
  Double_t vx = event->primaryVertex().x();
  if (vx > mMaxVx || vx < mMinVx) {
    LOG_DEBUG << "Fail: Vx=" << vx << " minVx=" << mMinVx << " maxVx=" << mMaxVx << endm;
    mEventsFailedVx++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vx=" << vx << " minVx=" << mMinVx << " maxVx=" << mMaxVx << endm;
  return kTRUE;
}


Bool_t TStarJetEventCuts::AcceptVy(StMuEvent* event) {
  Double_t vy = event->primaryVertexPosition().y();
  if (vy > mMaxVy || vy < mMinVy) {
    LOG_DEBUG << "Fail: Vy=" << vy << " minVy=" << mMinVy << " maxVy=" << mMaxVy << endm;
    mEventsFailedVy++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vy=" << vy << " minVy=" << mMinVy << " maxVy=" << mMaxVy << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::AcceptVy(StPicoEvent* event) {
  Double_t vy = event->primaryVertex().y();
  if (vy > mMaxVy || vy < mMinVy) {
    LOG_DEBUG << "Fail: Vy=" << vy << " minVy=" << mMinVy << " maxVy=" << mMaxVy << endm;
    mEventsFailedVy++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vy=" << vy << " minVy=" << mMinVy << " maxVy=" << mMaxVy << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::AcceptVz(StMuEvent* event) {
  Double_t vz = event->primaryVertexPosition().z();
  if (vz > mMaxVz || vz < mMinVz) {
    LOG_DEBUG << "Fail: Vz=" << vz << " minVz=" << mMinVz << " maxVz=" << mMaxVz << endm;
    mEventsFailedVz++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vz=" << vz << " minVz=" << mMinVz << " maxVz=" << mMaxVz << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::AcceptVz(StPicoEvent* event) {
  Double_t vz = event->primaryVertex().z();
  if (vz > mMaxVz || vz < mMinVz) {
    LOG_DEBUG << "Fail: Vz=" << vz << " minVz=" << mMinVz << " maxVz=" << mMaxVz << endm;
    mEventsFailedVz++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: Vz=" << vz << " minVz=" << mMinVz << " maxVz=" << mMaxVz << endm;
  return kTRUE;
}


Bool_t TStarJetEventCuts::AcceptTrigger(StMuEvent* event) {
  Bool_t accept = kFALSE;
  for (unsigned int i = 0; i < mTriggers.size(); ++i) {
    if (event->triggerIdCollection().nominal().isTrigger(mTriggers[i]) == kTRUE) {
      accept = kTRUE;
      LOG_DEBUG << "Pass: trigger accepted=" << mTriggers[i] << endm;
    } else {mEventsFailedTrigger[i]++;}
  }
  if (accept == kFALSE) {mEventsFailedTriggerTotal++; LOG_DEBUG << "Fail: no trigger accepted" << endm;}
  return accept;
}

Bool_t TStarJetEventCuts::AcceptRefMult(StMuEvent* event) {
  UInt_t refmult = mUseGrefMult ? event->grefmult() : event->refMult();
  if (refmult > mMaxRef || refmult < mMinRef) {
    LOG_DEBUG << "Fail: refmult=" << refmult << " min refmult=" << mMinRef << " max refmult=" << mMaxRef << endm;
    mEventsFailedRef++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: refmult=" << refmult << " min refmult=" << mMinRef << " max refmult=" << mMaxRef << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::AcceptRefMult(StPicoEvent* event) {
  UInt_t refmult = mUseGrefMult ? event->grefMult() : event->refMult();
  if (refmult > mMaxRef || refmult < mMinRef) {
    LOG_DEBUG << "Fail: refmult=" << refmult << " min refmult=" << mMinRef << " max refmult=" << mMaxRef << endm;
    mEventsFailedRef++;
    return kFALSE;
  }
  LOG_DEBUG << "Pass: refmult=" << refmult << " min refmult=" << mMinRef << " max refmult=" << mMaxRef << endm;
  return kTRUE;
}

Bool_t TStarJetEventCuts::SetVxRange(Double_t min, Double_t max) {
  mCheckVx = kTRUE;
  mMinVx = min;
  mMaxVx = max;
  return mCheckVx;
}

Bool_t TStarJetEventCuts::SetVyRange(Double_t min, Double_t max) {
  mCheckVy = kTRUE;
  mMinVy = min;
  mMaxVy = max;
  return mCheckVy;
}

Bool_t TStarJetEventCuts::SetVzRange(Double_t min, Double_t max) {
  mCheckVz = kTRUE;
  mMinVz = min;
  mMaxVz = max;
  return mCheckVz;
}

Bool_t TStarJetEventCuts::SetRefMultRange(UInt_t min, UInt_t max) {
  mCheckRefMult = kTRUE;
  mMinRef = min;
  mMaxRef = max;
  return mCheckRefMult;
}

void   TStarJetEventCuts::UsegRefMult(bool use_gref) {
  mUseGrefMult = use_gref;
}

void TStarJetEventCuts::AddTrigger(unsigned int trigger) {
  if(std::find(mTriggers.begin(), mTriggers.end(), trigger) == mTriggers.end()) {
    mCheckTrigger = kTRUE;
    mTriggers.push_back(trigger);
    mEventsFailedTrigger.push_back(0);
  }
}

void TStarJetEventCuts::AddTrigger(std::vector<unsigned int> triggers) {
  for (unsigned id = 0; id < triggers.size(); ++id) {
    UInt_t trigger = triggers[id];
    if(std::find(mTriggers.begin(), mTriggers.end(), trigger) == mTriggers.end()) {
      mCheckTrigger = kTRUE;
      mTriggers.push_back(trigger);
      mEventsFailedTrigger.push_back(0);
    }
  }
}


void TStarJetEventCuts::PrintCuts() {
  LOG_INFO << "// ------------------ TStarJetEventCuts Cuts ------------------ //" << endm;
  LOG_INFO << endm;
  if (mCheckVx || mCheckVy || mCheckVz) {LOG_INFO << "Vertex cuts: " << endm;}
  if (mCheckVx) {LOG_INFO << mMinVx << " < Vx < " << mMaxVx << endm;}
  if (mCheckVy) {LOG_INFO << mMinVy << " < Vy < " << mMaxVy << endm;}
  if (mCheckVz) {LOG_INFO << mMinVz << " < Vz < " << mMaxVz << endm;}
  if (mCheckRefMult) {LOG_INFO << " Refmult Cuts: " << endm;}
  if (mCheckRefMult && mUseGrefMult)  {LOG_INFO << "use grefmult" << endm;
                                          LOG_INFO << mMinRef << " < gRefMult < " << mMaxRef << endm;}
  if (mCheckRefMult && !mUseGrefMult) {LOG_INFO << "use refmult" << endm;
                                          LOG_INFO << mMinRef << " < RefMult < " << mMaxRef << endm;}
  if (mCheckTrigger && mTriggers.size() > 0) {
    std::string trigger_string = "[ " + tostr(mTriggers[0]);
    for (unsigned i = 1; i < mTriggers.size(); ++i) {
      trigger_string += ", " + tostr(mTriggers[i]);
    }
    LOG_INFO << "Using triggers: " << trigger_string << endm;
  }
  LOG_INFO << " // ------------------        End Cuts        ------------------ //" << endm;
}

void  TStarJetEventCuts::PrintStats() {
  LOG_INFO << "// ------------------ TStarJetEventCuts Stats ------------------ //" << endm;
  LOG_INFO << "number of events:   " << mNEvents << endm;
  if (mCheckVx) {LOG_INFO << "events rejected by Vx cut: " << mEventsFailedVx << endm;
                   LOG_INFO << "\t percent loss: " << (Double_t) mEventsFailedVx / mNEvents << endm;}
  if (mCheckVy) {LOG_INFO << "events rejected by Vy cut: " << mEventsFailedVy << endm;
                   LOG_INFO << "\t percent loss: " << (Double_t) mEventsFailedVy / mNEvents << endm;}
  if (mCheckVz) {LOG_INFO << "events rejected by Vz cut: " << mEventsFailedVz << endm;
                   LOG_INFO << "\t percent loss: " << (Double_t) mEventsFailedVz / mNEvents << endm;}
  if (mCheckRefMult) {
    LOG_INFO << "events rejected by RefMult cut: " << mEventsFailedVx << endm;
    LOG_INFO << "\t using grefmult: "; if (mUseGrefMult) {LOG_INFO << "true" << endm;} else {LOG_INFO << "false" << endm;}
    LOG_INFO << "\t percent loss: " << (Double_t) mEventsFailedRef / mNEvents << endm;
 }
  if (mCheckTrigger && mTriggers.size() > 0) {
    std::string trigger_string = "[ " + tostr(mTriggers[0]);
    std::string loss_string = "[ " + tostr(mEventsFailedTrigger[0]);
    for (unsigned i = 1; i < mTriggers.size(); ++i) {
      trigger_string += ", " + tostr(mTriggers[i]);
      loss_string += ", " + tostr(mEventsFailedTrigger[i]);
    }
    trigger_string += " ]"; loss_string += " ]";
    LOG_INFO << "events rejected by triggers: " << endm;
    LOG_INFO << "using triggers: " << trigger_string << endm;
    LOG_INFO << "rejected: " << loss_string << endm;
    LOG_INFO << "total events rejected by trigger: " << mEventsFailedTriggerTotal << endm;
  }
  LOG_INFO << "total number of events rejected: " << mEventsFailed << endm;
  LOG_INFO << "\t percent loss: " << (Double_t) mEventsFailed / mNEvents << endm;
  LOG_INFO << " // ------------------        End Stats        ------------------ //" << endm;
  
}

