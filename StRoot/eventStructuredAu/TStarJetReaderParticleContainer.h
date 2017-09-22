#ifndef __TSTARJETREADERPARTICLECONTAINER_HH
#define __TSTARJETREADERPARTICLECONTAINER_HH

#include <TString.h>

#include "TStarJetPicoReaderBase.h"

class TStarJetReaderParticleContainer : public TStarJetPicoReaderBase
{
 public:

  TStarJetReaderParticleContainer();
  virtual ~TStarJetReaderParticleContainer();

  virtual void Init(Long64_t nevents = -1);

  virtual Int_t ReadEvent(Long64_t ientry);

  virtual void SetBranchName(const char *str) { fBranchName = str; }

 protected:

  virtual Bool_t ProcessEvent() {return kTRUE;}
  virtual Bool_t LoadEvent() {return kTRUE;}
  virtual Bool_t LoadV0s(TArrayI */*trackIdsToRemove*/) {return kTRUE;}
  virtual Bool_t LoadTracks(TArrayI */*trackIdsToRemove*/) {return kTRUE;}
  virtual Bool_t LoadTowers() {return kTRUE;}

  TString fBranchName;

 private:

  ClassDef(TStarJetReaderParticleContainer, 1)
};

#endif
