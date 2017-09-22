#ifndef __TSTARJETPICOTOWERCUTS_HH
#define __TSTARJETPICOTOWERCUTS_HH

#include <TObject.h>

#include <set>

class TStarJetPicoEvent;
class TStarJetPicoTower;
class TStarJetPicoTrackCuts;

class TStarJetPicoTowerCuts : public TObject
{
 public:
  TStarJetPicoTowerCuts();
  TStarJetPicoTowerCuts(const TStarJetPicoTowerCuts &t);
  virtual ~TStarJetPicoTowerCuts() {;} // nothing to delete

  virtual Bool_t IsTowerOK(TStarJetPicoTower *tw, TStarJetPicoEvent *mEv);
  virtual Bool_t CheckTowerQA(TStarJetPicoTower *tw, TStarJetPicoEvent *mEv);

  // KK: Use one set to reject bad towers
  void ResetBadTowerList( );
  Bool_t AddBadTowers(TString csvfile);

    

  virtual Double_t TowerEnergyMipCorr(TStarJetPicoTower *mTower);

  virtual Double_t HadronicCorrection(TStarJetPicoTower *mTower,
			      TStarJetPicoEvent *mEvent,
			      TStarJetPicoTrackCuts *trackQA,
			      Double_t frac);

  virtual Int_t    DoPID(TStarJetPicoTower */*tw*/) {return 0;}

  void SetMaxEtCut(Double_t val) {fMaxEt = val;}
  Double_t GetMaxEtCut() {return fMaxEt;}
    
  // nick elsey: can reject particles in phi bands
  Bool_t RestrictPhiRange(Double_t min, Double_t max);

  void Sety8PythiaCut(Bool_t val) {y8PythiaCut = val;}
  Bool_t Gety8PythiaCut() {return y8PythiaCut;}

  /* nick elsey: starting with y14 data, all towers 
     are saved regardless of tower status. Default 
     behavior is to reject towers with status != 1
     To accept all towers, set to false
  */
  void UseTowerStatusRejection(Bool_t val) {useTowerStatus=val;}
  Bool_t GetTowerStatusRejection() {return useTowerStatus;}

 private:
  /// KK: Replacement for IsTowerOK(Int_t mTowId, Int_t mTrigId)
  Bool_t IsTowerOK( Int_t mTowId );

  /// The other method of this name has extra checks, this one shouldn't be used by itself
  virtual Bool_t IsTowerOK(Int_t mTowId, Int_t mTrigId);
    
  // Used by RestrictPhiRange()
  Bool_t AddPhiCut(Double_t min, Double_t max);

  Double_t fMaxEt;
  
  std::vector<std::vector<double> > restrictedPhiRanges;
  
  Bool_t y8PythiaCut;
    
  // KK: Just use one set of rejected towers
  std::set<Int_t> badTowers; 

  Bool_t useTowerStatus;

  ClassDef(TStarJetPicoTowerCuts, 3)
};

#endif
