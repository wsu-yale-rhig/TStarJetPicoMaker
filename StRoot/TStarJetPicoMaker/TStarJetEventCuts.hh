/* internal class for TStarJetPicoMaker
 implements quality cuts, as well as physical
 cuts, such as trigger requirements
 */


#ifndef TSTARJETPICOEVENTCUTS__HH
#define TSTARJETPICOEVENTCUTS__HH

#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StPicoEvent/StPicoEvent.h"

#include <vector>

class TStarJetEventCuts : public TObject {
  
public:
  
  TStarJetEventCuts();
  ~TStarJetEventCuts();
  
  /* function called by TStarJetPicoMaker, returns true if 
     event should be accepted based on the defined cuts
   */
  Bool_t AcceptEvent(StMuEvent* event);
  Bool_t AcceptEvent(StPicoEvent* event);
  
  /* there is no default cut value - cuts are turned off 
     until set by the user. Each must be set individually
   */
  Bool_t SetVxRange(Double_t min, Double_t max);
  Bool_t SetVyRange(Double_t min, Double_t max);
  Bool_t SetVzRange(Double_t min, Double_t max);
  Bool_t SetRefMultRange(UInt_t min, UInt_t max);
  void   UsegRefMult(Bool_t use_grefmult);
  
  /* by default all triggers are accepted. Once a trigger is
     added, only those triggers are used
   */
  void AddTrigger(UInt_t trigger);
  void AddTrigger(std::vector<UInt_t> triggers);
  
  std::vector<UInt_t> GetTriggers() { return mTriggers; }
  
  /* print a list of the cuts & triggers used */
  void PrintCuts();
  
  /* print statistics on the number of events rejected. 
     Called in Finish() of TStarJetPicoMaker */
  void PrintStats();
  
private:
  
  /* functions used by AcceptEvent() to determine which
     criteria the event passes or fails. Each give their
     own output & iterate their respective counters
   */
  Bool_t AcceptVx(StMuEvent* event);
  Bool_t AcceptVx(StPicoEvent* event);
  Bool_t AcceptVy(StMuEvent* event);
  Bool_t AcceptVy(StPicoEvent* event);
  Bool_t AcceptVz(StMuEvent* event);
  Bool_t AcceptVz(StPicoEvent* event);
  Bool_t AcceptRefMult(StMuEvent* event);
  Bool_t AcceptRefMult(StPicoEvent* event);
  Bool_t AcceptTrigger(StMuEvent* event);
  Bool_t AcceptTrigger(StPicoEvent* event);

  UInt_t         mNEvents;
  UInt_t         mEventsFailed;
  UInt_t         mEventsFailedVx;
  UInt_t         mEventsFailedVy;
  UInt_t         mEventsFailedVz;
  UInt_t         mEventsFailedRef;
  std::vector<UInt_t> mEventsFailedTrigger;
  UInt_t         mEventsFailedTriggerTotal;
  
  Bool_t    mCheckVx;
  Bool_t    mCheckVy;
  Bool_t    mCheckVz;
  Bool_t    mCheckRefMult;
  Bool_t    mCheckTrigger;
  Bool_t    mUseGrefMult;
  
  Double_t  mMinVx,  mMaxVx;
  Double_t  mMinVy,  mMaxVy;
  Double_t  mMinVz,  mMaxVz;
  UInt_t    mMinRef, mMaxRef;
  
  std::vector<UInt_t> mTriggers;
  
  
  ClassDef(TStarJetEventCuts, 1)
};

#endif /* TStarJetEventCuts */
