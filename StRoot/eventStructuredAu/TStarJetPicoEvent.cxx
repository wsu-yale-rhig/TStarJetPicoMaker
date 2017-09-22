#include "TStarJetPicoEvent.h"

#include <TClonesArray.h>

#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoTriggerInfo.h"

#include "TStarJetPicoDefinitions.h"

ClassImp(TStarJetPicoEvent)

TClonesArray *TStarJetPicoEvent::fgPrimaryTracks = 0;
TClonesArray *TStarJetPicoEvent::fgFtpcPrimaryTracks = 0;
TClonesArray *TStarJetPicoEvent::fgTowers = 0;
TClonesArray *TStarJetPicoEvent::fgV0s   = 0;
TClonesArray *TStarJetPicoEvent::fgTrigObjs   = 0;

TStarJetPicoEvent::TStarJetPicoEvent()
  : TObject()
  , fPrimaryTracks(0)
  , fFtpcPrimaryTracks(0)
  , fTowers(0)
  , fV0s(0)
  , fTrigObjs(0)
{

  fEventHeader.Clear();

  if (fgPrimaryTracks == 0)
    {
      fgPrimaryTracks = new TClonesArray("TStarJetPicoPrimaryTrack", 5000);
    }

  fPrimaryTracks = fgPrimaryTracks;

  if (fgFtpcPrimaryTracks == 0)
    {
      fgFtpcPrimaryTracks = new TClonesArray("TStarJetPicoPrimaryTrack", 5000);
    }

  fFtpcPrimaryTracks = fgFtpcPrimaryTracks;

  if (fgTowers == 0)
    {
      fgTowers = new TClonesArray("TStarJetPicoTower", 5000);
    }
  
  fTowers = fgTowers;

  
  if (fgV0s == 0)
    {
      fgV0s = new TClonesArray("TStarJetPicoV0", 5000);      

    }

  fV0s = fgV0s;

 if (fgTrigObjs == 0)
    {
      fgTrigObjs = new TClonesArray("TStarJetPicoTriggerInfo", 5000);      

    }

  fTrigObjs = fgTrigObjs;

  for(Int_t strip = 0; strip < 8; strip++)
    {
      fZdcsmd[0][0][strip] = -1;
      fZdcsmd[0][1][strip] = -1;
      fZdcsmd[1][0][strip] = -1;
      fZdcsmd[1][1][strip] = -1;
    }

}

//______________________________________________________________________________
TStarJetPicoEvent::~TStarJetPicoEvent()
{
  Clear();
}

//______________________________________________________________________________
void TStarJetPicoEvent::Clear(Option_t *Option)
{
  fPrimaryTracks->Clear("C"); 
  fFtpcPrimaryTracks->Clear("C"); 
  fTowers->Clear("C"); 
  fV0s->Clear("C"); 
  __DEBUG(5, Form("Clear called with option: \"%s\"", Option));
  fTrigObjs->Clear("C"); 

  for(Int_t strip = 0; strip < 8; strip++)
    {
      fZdcsmd[0][0][strip] = -1;
      fZdcsmd[0][1][strip] = -1;
      fZdcsmd[1][0][strip] = -1;
      fZdcsmd[1][1][strip] = -1;
    }
}

//______________________________________________________________________________
void TStarJetPicoEvent::Reset(Option_t */*Option*/)
{
  delete fgPrimaryTracks;
  fgPrimaryTracks = 0;
  delete fgFtpcPrimaryTracks;
  fgFtpcPrimaryTracks = 0;
  delete fgTowers;
  fgTowers = 0;
  delete fgV0s;
  fgV0s = 0;
  delete fgTrigObjs;
  fgTrigObjs = 0;

}
//______________________________________________________________________________
void TStarJetPicoEvent::AddPrimaryTrack(TStarJetPicoPrimaryTrack *t)
{
  TClonesArray &tracks = *fPrimaryTracks;
  Int_t fNtrack = fEventHeader.GetNOfPrimaryTracks();
  // Use ConstructedAt!! new defeats the purpose of tclonesarray (and swamps the memory)
  // TStarJetPicoPrimaryTrack *track = new(tracks[fNtrack++]) TStarJetPicoPrimaryTrack(*t);
  TStarJetPicoPrimaryTrack *track = (TStarJetPicoPrimaryTrack*) tracks.ConstructedAt(fNtrack++);
  *track = *t;
  fEventHeader.SetNOfPrimaryTracks(fNtrack);
  fLastPrimaryTrack = track;
  __DEBUG(4, Form("Primary Track added. Current number is %d", fPrimaryTracks->GetEntriesFast()));
}

//______________________________________________________________________________
void TStarJetPicoEvent::AddFtpcPrimaryTrack(TStarJetPicoPrimaryTrack *t)
{
  TClonesArray &tracks = *fFtpcPrimaryTracks;
  Int_t fNtrack = fEventHeader.GetNOfFtpcPrimaryTracks();
  // Use ConstructedAt!! new defeats the purpose of tclonesarray (and swamps the memory)
  // TStarJetPicoPrimaryTrack *track = new(tracks[fNtrack++]) TStarJetPicoPrimaryTrack(*t);
  // TStarJetPicoPrimaryTrack *track = new(tracks[fNtrack++]) TStarJetPicoPrimaryTrack(*t);
  TStarJetPicoPrimaryTrack *track = (TStarJetPicoPrimaryTrack*) tracks.ConstructedAt(fNtrack++);
  *track = *t;
  fEventHeader.SetNOfFtpcPrimaryTracks(fNtrack);
  fLastFtpcPrimaryTrack = track;
  __DEBUG(4, Form("FTPC Primary Track added. Current number is %d", fFtpcPrimaryTracks->GetEntriesFast()));
}

//______________________________________________________________________________
void TStarJetPicoEvent::AddTower(TStarJetPicoTower *t)
{
  TClonesArray &towers = *fTowers;
  Int_t fNtower = fEventHeader.GetNOfTowers();
  // Use ConstructedAt!! new defeats the purpose of tclonesarray (and swamps the memory)
  //TStarJetPicoTower *tower = new(towers[fNtower++]) TStarJetPicoTower(*t);
  
  TStarJetPicoTower *tower = (TStarJetPicoTower*) towers.ConstructedAt(fNtower++);
  *tower = *t;
  fEventHeader.SetNOfTowers(fNtower);
  fLastTower = tower;
  __DEBUG(4, Form("Tower added. Current number is %d", fTowers->GetEntriesFast()));
}

//______________________________________________________________________________
void TStarJetPicoEvent::AddV0(TStarJetPicoV0 *t)
{
  __DEBUG(4, Form("Adding V0. Current number is %d", fV0s->GetEntriesFast()));
  TClonesArray &V0s = *fV0s;
  Int_t fNV0 = fEventHeader.GetNOfV0s();
  
  // FIXME: Use ConstructedAt!! new defeats the purpose of tclonesarray (and swamps the memory)
  // FIXME: Needs a copy constructor
  TStarJetPicoV0 *V0 = new(V0s[fNV0++]) TStarJetPicoV0(*t);
  // TStarJetPicoV0 *V0 = (TStarJetPicoV0*) V0s.ConstructedAt(fNV0++);
  // *V0 = t;
  fEventHeader.SetNOfV0s(fNV0);
  fLastV0 = V0;
  __DEBUG(4, Form("V0 added. Current number is %d", fV0s->GetEntriesFast()));
}
//______________________________________________________________________________
void TStarJetPicoEvent::AddTrigObj(TStarJetPicoTriggerInfo *t)
{
  TClonesArray &trigobj = *fTrigObjs;
  Int_t fNtrig = fEventHeader.GetNOfTrigObjs();
  TStarJetPicoTriggerInfo *trig = new(trigobj[fNtrig++]) TStarJetPicoTriggerInfo(*t);
  fEventHeader.SetNOfTrigObjs(fNtrig);
  fLastTrigObj = trig;
  __DEBUG(4, Form("Adding trigger object. Current number is %d (counter) %d(::GetEntries", 
		  fNtrig, fTrigObjs->GetEntriesFast()));
}
//______________________________________________________________________________
TStarJetPicoPrimaryTrack *TStarJetPicoEvent::GetPrimaryTrack(Int_t n)
{
  if ( n < fEventHeader.GetNOfPrimaryTracks() )
    {
      return (TStarJetPicoPrimaryTrack *)fPrimaryTracks->At(n);
    }
  else
    {
      __ERROR(Form("Request for track with index %d. Event contains %d tracks.", 
		   n, fEventHeader.GetNOfPrimaryTracks()));
    }
  return 0;
}

//______________________________________________________________________________
TStarJetPicoPrimaryTrack *TStarJetPicoEvent::GetFtpcPrimaryTrack(Int_t n)
{
  if ( n < fEventHeader.GetNOfFtpcPrimaryTracks() )
    {
      return (TStarJetPicoPrimaryTrack *)fFtpcPrimaryTracks->At(n);
    }
  else
    {
      __ERROR(Form("Request for FTPC track with index %d. Event contains %d tracks.", 
		   n, fEventHeader.GetNOfFtpcPrimaryTracks()));
    }
  return 0;
}

//______________________________________________________________________________
TStarJetPicoTower *TStarJetPicoEvent::GetTower(Int_t n)
{
  if ( n < fEventHeader.GetNOfTowers() )
    {
      return (TStarJetPicoTower *)fTowers->At(n);
    }
  else
    {
      __ERROR(Form("Request for tower with index %d. Event contains %d towers.", 
		   n, fEventHeader.GetNOfTowers()));
    }

  return 0;
}

//______________________________________________________________________________
TStarJetPicoPrimaryTrack *TStarJetPicoEvent::GetMatchedPrimaryTrack(Int_t nTower, Int_t nTrack)
{
  TStarJetPicoPrimaryTrack *track = 0;
  TStarJetPicoTower *tower = GetTower(nTower);  
  if (tower)
    {
      Int_t tindex = tower->GetMatchedTrackIndexes()->At(nTrack);
      track = this->GetPrimaryTrack(tindex);	      
    }
  
  if (track == 0) {
    __ERROR(Form("Unable to get track matched with index %d to tower %d", nTrack, nTower));
  }

  return track;
}

//______________________________________________________________________________
TStarJetPicoPrimaryTrack *TStarJetPicoEvent::GetMatchedPrimaryTrack(TStarJetPicoTower *tower, Int_t nTrack)
{
  TStarJetPicoPrimaryTrack *track = 0;
  Int_t tindex = tower->GetMatchedTrackIndexes()->At(nTrack);
  track = this->GetPrimaryTrack(tindex);	      

  if (track == 0) {
    __ERROR(Form("Unable to get track matched with index %d matched to tower 0x%x", nTrack, tower->GetId()));
  }

  return track;
}

//______________________________________________________________________________
TStarJetPicoV0 *TStarJetPicoEvent::GetV0(Int_t n)
{
  if ( n < fEventHeader.GetNOfV0s() )
    {
      return (TStarJetPicoV0 *)fV0s->At(n);
    }
  else
    {
      __ERROR(Form("Request for V0 with index %d. Event contains %d V0s.", 
		   n, fEventHeader.GetNOfV0s()));
    }
  
  return 0;
}
//______________________________________________________________________________
TStarJetPicoTriggerInfo *TStarJetPicoEvent::GetTrigObj(Int_t n)
{
  if ( n < fEventHeader.GetNOfTrigObjs() )
    {
      return (TStarJetPicoTriggerInfo *)fTrigObjs->At(n);
    }
  else
    {
      __ERROR(Form("Request for TriggerObject with index %d. Event contains %d TOs.", 
		   n, fEventHeader.GetNOfTrigObjs()));
    }
  
  return 0;
}
