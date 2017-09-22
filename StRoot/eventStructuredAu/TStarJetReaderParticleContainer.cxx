#include "TStarJetReaderParticleContainer.h"

#include <TChain.h>
#include <TList.h>
#include <TStopwatch.h>

#include "TStarJetPicoUtils.h"
#include "TStarJetPicoDefinitions.h"
#include "TStarJetVectorContainer.h"

ClassImp(TStarJetReaderParticleContainer)

TStarJetReaderParticleContainer::TStarJetReaderParticleContainer() 
  : TStarJetPicoReaderBase()
  , fBranchName("Particles")
{
  //
  // Default constructor
  //
}

TStarJetReaderParticleContainer::~TStarJetReaderParticleContainer()
{
  //
  // Destructor
  //
}

Int_t TStarJetReaderParticleContainer::ReadEvent(Long64_t ientry)
{
  //
  // Load an event with return codes: 
  // -1 == error; 
  //  0 == event loaded but not passed cuts; 
  //  1 ==  OK!
  //  Calling ProcessEvent().
  //

  fOutputContainer->Clear();
  fSelectedTracks->Clear();
  fSelectedTowers->Clear();
  fSelectedV0s->Clear();

  if (ientry < fNofEntries && ientry >= 0)
    {
      if (fOutputContainer == 0)
	{
	  __ERROR(Form("Bad output container pointer %p", fOutputContainer));
	  return -1;
	}

      fInputTree->SetBranchAddress(fBranchName.Data(), &fOutputContainer, &fBranch);
      
      //Long64_t centry = fInputTree->LoadTree(ientry);      
      Long64_t centrybytes = fInputTree->GetEvent(ientry);      
      if (centrybytes < 0)
	{
	  __ERROR(Form("Unable to load entry %lld", ientry));
	  return -1;
	}
      else
	{
	  fNEntry = ientry;
	  fNEntryLoaded = ientry;
	  Bool_t isaccept = ProcessEvent();
	  if (isaccept == kTRUE)
	    {
	      fNEntriesAccepted++;
	      __DEBUG(3, Form("Events accepted %lld.", fNEntriesAccepted));
	      return 1;
	    }
	  else
	    {
	      return 0;
	    }
	}
    }

  if (GetStopWatch() != 0)
    GetStopWatch()->Stop();

  __ERROR(Form("Request for an event outside limits (%lld-%lld). NEntries is %lld", 
	       0ll, fNofEntries-1, fNofEntries));

  return -1;
}

void TStarJetReaderParticleContainer::Init(Long64_t nevents)
{
  //
  // Initialize. Must be called before NextEvent() or ReadEvent().
  //

  __INFO("INIT");
  // do some more init here! with the current chain... or the input is
  if (fInputTree == 0)
    {
      __ERROR("Chain not initialized! SetInput first.");      
    }
  
  fBranch = fInputTree->GetBranch(fBranchName.Data());
  
  if (fBranch == 0)
    {
      __ERROR("Unable to get the branch!");
      return;
    }
  
  fBranch->SetAddress(&fOutputContainer);
  fNofEntries = fInputTree->GetEntries();
  __INFO(Form("Number of events in the chain %lld", fNofEntries));
  if (nevents > -1)
    {
      if (nevents < fNofEntries)
	{
	  fNofEntries = nevents;
	}
    }
  __INFO(Form("Run set for %lld events.", fNofEntries));
  fNEntry = 0;
}
