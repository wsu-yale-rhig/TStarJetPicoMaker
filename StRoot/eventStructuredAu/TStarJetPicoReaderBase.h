#ifndef __TSTARJETPICOREADERBASE_HH
#define __TSTARJETPICOREADERBASE_HH

#include <TObject.h>
#include <TString.h>
#include "TStarJetVectorContainer.h"
#include "TStarJetVector.h"

class TChain;
class TBranch;
class TArrayI;
class TList;
class TStopwatch;

class TStarJetPicoEvent;

class TStarJetPicoReaderBase : public TObject
{
 public:

  TStarJetPicoReaderBase();
  virtual ~TStarJetPicoReaderBase();

  TStarJetVectorContainer<TStarJetVector> *GetOutputContainer() 
    {
      return fOutputContainer;
    }

  virtual void Clear(Option_t* option = "");

  virtual Bool_t IsKeyInArray(Int_t id, TArrayI *arr);
  TStarJetVector *FindVectorByKey(Int_t key);

  virtual void SetInputChain(TChain *ch) {fInputTree = ch;}
  TChain* GetInputChain() {return fInputTree;}

  virtual void LoadDirectory(const char* cdir, const char* treename = "JetTree");
  virtual void LoadFilelist(const char* clist, const char* treename = "JetTree");

  virtual void ResetEventCounters()
  {
    //
    // Simple reset of all event related counters.    
    //
    fNofEntries = 0; 
    fNEntry = 0;
    fNEntryLoaded = -1; // nothing loaded
    fNEntriesAccepted = 0;
  }

  // must be called before NextEvent() or LoadEvent()
  // best call after setting up the chain
  // specify number of events to run; -1 is all available
  virtual void Init(Long64_t nevents = -1);

  // Read an event with return codes: -1 == error; 0 == event loaded but not passed cuts; 1 == OK!
  // overload in the derived class, if very necessary
  virtual Int_t  ReadEvent(Long64_t ientry); 
  // overload in the derived class, if very necessary
  virtual Bool_t NextEvent(); // true as long as next event is available

  virtual TStarJetPicoEvent* GetEvent() {return fEvent;}

  virtual Long64_t GetNOfEvents()         {return fNofEntries;}
  virtual Long64_t GetNOfCurrentEvent()   {return fNEntryLoaded;}
  virtual Long64_t GetNOfAcceptedEvents() {return fNEntriesAccepted;}

  TList*  GetListOfSelectedTracks() {return fSelectedTracks;}
  TList*  GetListOfSelectedTowers() {return fSelectedTowers;}
  TList*  GetListOfSelectedV0s()    {return fSelectedV0s;}   
  
  virtual void    PrintStatus(const Int_t tsec = 0);
  virtual void    PrintStatus(Int_t& tsec, Bool_t updateETA);
  virtual void    PrintEventInfo();

  virtual void    SetProcessV0s(Bool_t val = kTRUE) {fProcessV0s = val;}
  // Added by KK
  // Reasoning: Geant MC data uses "tracks" only but towers are filled
  // This is not per se an issue b/c Ntowers is set to 0
  // However, using this method makes it more explicit and transparent
  virtual void    SetProcessTowers(Bool_t val = kTRUE) {fProcessTowers = val;}
  // Added by KK to allow customized rejection for some
  // very specific cases
  // Original goal was one specific event in Run6 Geant
  // with an absurdly high pT track (20 GeV for pThat=4-5)
  // Checked in ProcessEvents();
  virtual void    SetUseRejectAnyway(Bool_t val = kTRUE) {fUseRejectAnyway = val;}

  TStopwatch*     GetStopWatch() {return fStopwatch;}

 protected:

  // Overload in the derived class if necessary
  // Hint is that it should not be necessary
  virtual Bool_t ProcessEvent();

  virtual Bool_t LoadEvent() = 0;
  virtual Bool_t LoadV0s(TArrayI *trackIdsToRemove) = 0;
  virtual Bool_t LoadTracks(TArrayI *trackIdsToRemove) = 0;
  virtual Bool_t LoadTowers() = 0;

  Bool_t RejectAnyway();
  
  TStarJetVectorContainer<TStarJetVector>* fOutputContainer;//! output vectors

  // input data
  TStarJetPicoEvent* fEvent; //! input event
  TChain*            fInputTree; //! input tree
  TBranch*           fBranch; //! input branch
  Long64_t           fNofEntries; // number of entries in the intput tree
  Long64_t           fNEntry; // counter entry
  Long64_t           fNEntryLoaded; // current entry in memory
  Long64_t           fNEntriesAccepted; // n of accepted entries

  TList*             fSelectedTracks;//! tracks passed cuts
  TList*             fSelectedTowers;//! towers passed cuts
  TList*             fSelectedV0s;//! v0s passed cuts

  Bool_t             fProcessV0s;// flag whether to process V0s
  Bool_t             fProcessTowers;// flag whether to process Towers

  Bool_t             fUseRejectAnyway; // flag whether to check for a custom rejection method

 private:

  Long64_t           fNEntryStatus; // counter entry when first status called
  Double_t           fLastRealTime; // last real time status
  TStopwatch*        fStopwatch; //! stop watch for event stats
  
  ClassDef(TStarJetPicoReaderBase, 1)
};

#endif
