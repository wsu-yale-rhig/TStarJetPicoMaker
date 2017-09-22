#ifndef __TSTARJETPICOEVENTCUTS__HH
#define __TSTARJETPICOEVENTCUTS__HH

#include <TObject.h>
#include <TString.h>
#include <TChain.h>

class TStarJetPicoEvent;

class TStarJetPicoEventCuts : public TObject
{
 public:
  TStarJetPicoEventCuts();
  TStarJetPicoEventCuts(const TStarJetPicoEventCuts &t);
  virtual ~TStarJetPicoEventCuts() {;} //nothing to delete here

  virtual Bool_t IsEventOK(TStarJetPicoEvent *mEv, TChain *fInputTree);  // kTRUE if OK; kFALSE otherwise
  virtual Bool_t CheckEvent(TStarJetPicoEvent *mEv, TChain *fInputTree); // kTRUE if OK; kFALSE otherwise

  virtual Bool_t IsTriggerIdOK(Int_t mTrigId);
  virtual Bool_t IsTriggerIdOK(TStarJetPicoEvent *mEv);
  virtual Bool_t IsRefMultOK(TStarJetPicoEvent *mEv);
  virtual Bool_t IsRefCentOK(TStarJetPicoEvent *mEv, TChain *fInputTree);
  virtual Bool_t IsVertexZOK(TStarJetPicoEvent *mEv);
  virtual Bool_t IsVertexZDiffOK(TStarJetPicoEvent *mEv);
  virtual Bool_t IsPVRankingOK(TStarJetPicoEvent *mEv);
  
  //the following are added (by Jan Kapitan) for dAu (run8) and are only checked for corresponding run numbers (backward compatibility)
  virtual Bool_t IsBbceOK(TStarJetPicoEvent *mEv);
  virtual Bool_t IsScalersOK(TStarJetPicoEvent *mEv);

  // Added by Kolja Kauder to reject events with unphysical tracks or towers
  virtual Bool_t IsHighestPtOK( Float_t mPt );  // kTRUE if OK; kFALSE otherwise
  virtual Bool_t IsHighestEtOK( Float_t mEt );  // kTRUE if OK; kFALSE otherwise
  virtual Bool_t IsHighTowerOk( Float_t mEt );  // kTRUE if OK; kFALSE otherwise

  virtual void   SetTriggerSelection(const char *str) {fTrigSel = str;}
  virtual void   SetVertexZCut(Float_t val) {fVzCut = val;}
  virtual void   SetVertexZDiffCut(Float_t val) {fVzDiffCut = val;}
  virtual void   SetRefMultCut(Int_t valmin, Int_t valmax = 99999) 
  {
    fRefMultCutMin = valmin; 
    fRefMultCutMax = valmax;
  }
  virtual void   SetBbceCut(Int_t valmin, Int_t valmax = 99999) 
  {
    fBbceCutMin = valmin; 
    fBbceCutMax = valmax;
  }
    
    //nick elsey: for use with centrality definitions given here... TENTATIVE - check the definition
    //nick elsey: always returns true if the corresponding leaf doesn't exist
    // 8 : 0-5%
    // 7 : 5-10%
    // 5 : 10-20%
    // 4 : 20-30%
    // 3 : 30-40%
    // 2 : 40-50%
    // 1 : 50-60%
    // 0 : 60-80%
  virtual Bool_t   SetReferenceCentralityCut(Int_t min, Int_t max);
    
  virtual void   SetPVRankingCut(Float_t val) {fFlagPVRankingCut=kTRUE; fPVRankingCut = val;}
  virtual void   SetPVRankingCutOff() {fFlagPVRankingCut=kFALSE;}

  virtual void SetMaxEventPtCut( Float_t val)     { fMaxEventPt = val;}
  virtual void SetMaxEventEtCut( Float_t val)     { fMaxEventEt = val;}
  virtual void SetMinEventEtCut( Float_t val)     { fMinEventEt = val;}
  // Use hadronic correction for soft HT cut?
  virtual void SetUseRawForMinEventEtCut( Bool_t val)     { fUseRawForMinEventEtCut = val;}
      
  virtual Int_t  GetReferenceMultiplicity(TStarJetPicoEvent *mEv);

  TString GetTriggerSelection() {return fTrigSel;}
  Float_t GetVertexZCut()       {return fVzCut;}
  Float_t GetVertexZDiffCut()   {return fVzDiffCut;}
  Int_t   GetRefMultCutMin()    {return fRefMultCutMin;}
  Int_t   GetRefMultCutMax()    {return fRefMultCutMax;}
  Int_t   GetBbceCutMin() {return fBbceCutMin;}
  Int_t   GetBbceCutMax() {return fBbceCutMax;}
  Float_t GetPVRankingCut() {return fPVRankingCut;}

  Float_t GetMaxEventPtCut()     {return fMaxEventPt;}
  Float_t GetMaxEventEtCut()     {return fMaxEventEt;}
  Float_t GetMinEventEtCut()     {return fMinEventEt;}
  Bool_t  GetUseRawForMinEventEtCut()     { return fUseRawForMinEventEtCut;}
    
  Int_t   GetRefCentMin()       {return fRefCentCutMin;}
  Int_t   GetRefCentMax()       {return fRefCentCutMax;}

 private:

  TString fTrigSel; // All,HT,MB,pp,dAu_mb,dAu_ht_all,dAu_ht0,dAu_ht1,dAu_ht2,dAu_ht4, y8p+p_ht0,y8p+p_ht1,y8p+p_ht2  
  Float_t fVzCut; // accept all events with vz: Abs(vz) < fVzCut - // Default STAR high-pt cuts == 50.
  Float_t fVzDiffCut; // accept all events with Abs(vzTPC - vzVPD) <  fVzDiffCut. Mainly for good TOF PID purposes

  Int_t   fRefMultCutMin; // accept all events with refmult: refmult > fRefMultCutMin && refmult < fRefMultCutMax
  Int_t   fRefMultCutMax;  // accept all events with refmult: refmult > fRefMultCutMin && refmult < fRefMultCutMax
  Int_t   fRefCentCutMin;
  Int_t   fRefCentCutMax;
  Int_t   fBbceCutMin;
  Int_t   fBbceCutMax;
  Float_t fPVRankingCut;
  Bool_t  fFlagPVRankingCut;
  
  Float_t fMaxEventPt;
  Float_t fMaxEventEt;
  Float_t fMinEventEt;
  Bool_t  fUseRawForMinEventEtCut;
  
  ClassDef(TStarJetPicoEventCuts, 3)
};

#endif
