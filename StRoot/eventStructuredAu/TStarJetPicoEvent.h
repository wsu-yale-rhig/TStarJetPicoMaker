#ifndef __TSTARJETPICOEVENT_HH
#define __TSTARJETPICOEVENT_HH

#include <TObject.h>
#include <TRef.h>
#include "TStarJetPicoEventHeader.h"

class TClonesArray;
class TStarJetPicoPrimaryTrack;
class TStarJetPicoTower;
class TStarJetPicoV0;
class TStarJetPicoTriggerInfo;
class TStarJetPicoEvent : public TObject
{
 public:
  TStarJetPicoEvent();
  virtual ~TStarJetPicoEvent();

  void Clear(Option_t *Option = "");
  static void Reset(Option_t *Option = "");

  void AddPrimaryTrack(TStarJetPicoPrimaryTrack *t);
  void AddFtpcPrimaryTrack(TStarJetPicoPrimaryTrack *t);
  void AddTower(TStarJetPicoTower *t);
  void AddV0(TStarJetPicoV0 *t);
  void AddTrigObj(TStarJetPicoTriggerInfo *t);


  TClonesArray  *GetPrimaryTracks() const {return fPrimaryTracks;}
  TClonesArray  *GetFtpcPrimaryTracks() const {return fFtpcPrimaryTracks;}
  TClonesArray  *GetTowers() const {return fTowers;}
  TClonesArray  *GetV0s() const {return fV0s;}
  TClonesArray  *GetTrigObjs() const {return fTrigObjs;}

  TStarJetPicoPrimaryTrack *GetPrimaryTrack(Int_t n);
  TStarJetPicoPrimaryTrack *GetFtpcPrimaryTrack(Int_t n);
  TStarJetPicoTower *GetTower(Int_t n);
  TStarJetPicoV0        *GetV0(Int_t n);
  TStarJetPicoTriggerInfo  *GetTrigObj(Int_t n);

  TStarJetPicoPrimaryTrack *GetMatchedPrimaryTrack(Int_t nTower, Int_t nTrack);
  TStarJetPicoPrimaryTrack *GetMatchedPrimaryTrack(TStarJetPicoTower *tower, Int_t nTrack);

  TStarJetPicoEventHeader  *GetHeader() { return &fEventHeader; }

  Float_t GetZdcsmd(Int_t eastwest,Int_t verthori,Int_t strip) {return fZdcsmd[eastwest][verthori][strip-1];}
  void SetZdcsmd(Int_t eastwest,Int_t verthori,Int_t strip, Float_t x) {fZdcsmd[eastwest][verthori][strip-1]=x;}

 protected:
 private:

  TStarJetPicoEventHeader fEventHeader;

  // DATA Containers:
  TClonesArray  *fPrimaryTracks; //->array with primary tracks
  TClonesArray  *fFtpcPrimaryTracks; //->array with primary tracks in FTPC
  TClonesArray  *fTowers; //->array with towers
  TClonesArray  *fV0s; //->array with V0S
  TClonesArray  *fTrigObjs; //->array with TrigObj 

  static TClonesArray *fgPrimaryTracks;//!
  static TClonesArray *fgFtpcPrimaryTracks;//!
  static TClonesArray *fgTowers;//!
  static TClonesArray *fgV0s;//!
  static TClonesArray *fgTrigObjs;//!

  TRef   fLastPrimaryTrack; //ref to the last primary track
  TRef   fLastFtpcPrimaryTrack; //ref to the last primary track in FTPC
  TRef   fLastTower; //ref to the last primary track
  TRef   fLastV0; //ref to the last primary track
  TRef   fLastTrigObj; //ref to the last trigger obj

  Double_t fZdcsmd[2][2][8];

  ClassDef(TStarJetPicoEvent, 4)
};

#endif
