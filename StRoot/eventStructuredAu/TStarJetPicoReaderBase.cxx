#include "TStarJetPicoReaderBase.h"

#include <TChain.h>
#include <TFile.h>
#include <TList.h>
#include <TStopwatch.h>

#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoTower.h"

#include "TStarJetPicoEvent.h"
#include "TStarJetPicoUtils.h"
#include "TStarJetPicoDefinitions.h"
#include "TStarJetVectorContainer.h"

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// TStarJetPicoReaderBase                                              //
//                                                                     //
// From specified TChain or directory of picoDST files                 //
// read TStarJetPicoEvent.                                             //
// And fill the output vector fOutputContainer:                        //
//   TStarJetVectorContainer<TStarJetVector>.                          // 
//                                                                     //
// DERIVE and IMPLEMENT:                                               //
// TStarJetPicoReaderBase::LoadV0s(),                                  // 
// TStarJetPicoReaderBase::LoadTracks(),                               //
// TStarJetPicoReaderBase::LoadTowers()                                //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoReaderBase)

TStarJetPicoReaderBase::TStarJetPicoReaderBase() 
  : TObject()
  , fOutputContainer(new TStarJetVectorContainer<TStarJetVector>)
  , fEvent(0)
  , fInputTree(0)
  , fBranch(0)
  , fNofEntries(0)
  , fNEntry(0)
  , fNEntryLoaded(-1)
  , fNEntriesAccepted(0)
  , fSelectedTracks(new TList)
  , fSelectedTowers(new TList)
  , fSelectedV0s(new TList)
  , fProcessV0s(kFALSE)
  , fProcessTowers(kTRUE)
  , fUseRejectAnyway(kFALSE)
  , fNEntryStatus(0)
  , fLastRealTime(0)
  , fStopwatch(0)
{
  //
  // Default constructor
  //

  fSelectedTracks->SetOwner(kFALSE);
  fSelectedTowers->SetOwner(kFALSE);
  fSelectedV0s->SetOwner(kFALSE);
}

TStarJetPicoReaderBase::~TStarJetPicoReaderBase()
{
  //
  // Destructor
  //

  delete fEvent;
  fEvent = 0;

  delete fOutputContainer;
  fOutputContainer = 0;

  delete fSelectedTracks;
  fSelectedTracks = 0;

  delete fSelectedTowers;
  fSelectedTowers = 0;

  delete fSelectedV0s;
  fSelectedV0s = 0;

  delete fStopwatch;
  fStopwatch = 0;
}

Bool_t TStarJetPicoReaderBase::IsKeyInArray(Int_t key, TArrayI *arr)
{
  //
  // Check if a "key" is already in the array "arr"
  //

  for (Int_t i = 0; i < arr->GetSize(); i++)
    {
      if (key == arr->At(i))
	{
	  __DEBUG(2, Form("Key %d Found in array at index %d", key, i));
	  return kTRUE;
	}
    }

  return kFALSE;
}

TStarJetVector *TStarJetPicoReaderBase::FindVectorByKey(Int_t key)
{
  //
  // Find vector TStarJetVector with "key" in the output container.
  // Return 0 if not found.
  //

  TStarJetVector *retval = 0;
  for (Int_t i = 0; i < fOutputContainer->GetEntries(); i++)
    {
      TStarJetVector *part = fOutputContainer->Get(i);
      if (part->GetFeatureI(TStarJetVector::_KEY) == key)
	retval = part;
    }

  return retval;
}

void TStarJetPicoReaderBase::LoadDirectory(const char* cdir, const char* treename)
{
  // 
  // Build the input chain from files in the directory "cdir".
  //

  fInputTree = TStarJetPicoUtils::BuildChainFromDirectory(cdir, treename, -1, 0, fInputTree);
}

void TStarJetPicoReaderBase::LoadFilelist(const char *clist, const char* treename)
{
  //
  // Build the input chain from files in the filelist "clist".                                                                                                               
  //
  
  fInputTree = TStarJetPicoUtils::BuildChainFromFileList(clist, treename, -1, 0, fInputTree);
}

void TStarJetPicoReaderBase::Init(Long64_t nevents)
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
  
  fBranch = fInputTree->GetBranch("PicoJetTree");
  
  if (fBranch == 0)
    {
      __ERROR("Unable to get the branch!");
      return;
    }
  
  fBranch->SetAddress(&fEvent);
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

Bool_t TStarJetPicoReaderBase::ProcessEvent()
{
  //
  // Process event and return kTRUE if accepted.
  //

  if (LoadEvent() == kFALSE)
    {
      __DEBUG(2, Form("Event not accepted. Failed on EventCuts."));
      return kFALSE;
    }
  
  TArrayI trackIdsToRemove(fEvent->GetHeader()->GetNOfV0s() * 6);

  if (fProcessV0s)
    {
      if (LoadV0s(&trackIdsToRemove) == kFALSE)
	{
	  __DEBUG(2, Form("Event not accepted. Failed on LoadV0s."));
	  return kFALSE;
	}
    }

  if (LoadTracks(&trackIdsToRemove) == kFALSE)
    {
      __DEBUG(2, Form("Event not accepted. Failed on LoadTracks."));
      return kFALSE;
    }

  if (fProcessTowers)
    {
      if ( LoadTowers() == kFALSE )
	{
	  __DEBUG(2, Form("Event not accepted. Failed on LoadTowers."));
	  return kFALSE;
	}
    }

  if ( fUseRejectAnyway &&  RejectAnyway() ){
    __DEBUG(0, Form("Event not accepted. Failed on RejectAnyway()."));
    return kFALSE;
  }
  
  __DEBUG(2, Form("Current event %lld accepted.", fNEntryLoaded));

  return kTRUE;
}

void TStarJetPicoReaderBase::Clear(Option_t* option)
{
  TObject::Clear(option);

  fOutputContainer->Clear(option);
  fSelectedTracks->Clear(option);
  fSelectedTowers->Clear(option);
  fSelectedV0s->Clear(option);

  fSelectedTracks->Clear(option);
  fSelectedTowers->Clear(option);
  fSelectedV0s->Clear(option);

  ResetEventCounters();
}

Int_t TStarJetPicoReaderBase::ReadEvent(Long64_t ientry)
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
      if (fEvent == 0)
	{
	  __ERROR(Form("Bad event pointer %p", fEvent));
	  return -1;
	}

      fEvent->Clear();
      fInputTree->SetBranchAddress("PicoJetTree", &fEvent, &fBranch);
      
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

  if (fStopwatch != 0)
    fStopwatch->Stop();

  __ERROR(Form("Request for an event %lld outside limits (%lld-%lld). NEntries is %lld", 
	       ientry, 0ll, fNofEntries-1, fNofEntries));

  return -1;
}

Bool_t TStarJetPicoReaderBase::NextEvent()
{
  //
  // Handy method.
  // Use within a while loop for example:
  //
  //  void example()
  //  {
  //    TStarJetPicoReader reader;
  //    TStarJetPicoEventCuts* evCuts = reader.GetEventCuts();
  //    evCuts->SetTriggerSelection("HT"); //All, MB, HT, pp, ppHT, ppJP
  //    reader.LoadDirectory("/some/directory");
  //    reader.Init(); // run for all events - for a fixed number use: reader.Init(10000);
  //    while (reader.NextEvent() == kTRUE)
  //      {
  //        // do something - event is read and OK!
  //        // reader.PrintEventInfo();
  //        // fill QA histograms
  //        TStarJetPicoUtils::FillQAHistogramsFromPicoReader(&reader);
  //
  //        TStarJetVectorContainer<TStarJetVector>* container = reader.GetOutputContainer();
  //        // run jet finder on the container or do anythin' else...
  //
  //        // one can also get the selected (which passed the cuts) tracks or towers or v0s
  //        // TList *towers = reader->GetListOfSelectedTowers();
  //        // TList *tracks = reader->GetListOfSelectedTracks();
  //        // TList *v0s = reader->GetListOfSelectedV0s();
  //
  //        // randomize phi of all output vectors:
  //        TStarJetPicoUtils::RandomizeContainerInPhi(container);
  //        // do something with the randomized event...
  //
  //        reader.PrintStatus(600); // update every 10 minutes
  //      }
  //
  //    reader.PrintStatus();
  //  }

  while (fNEntry < fNofEntries)
    {
      Int_t iret = ReadEvent(fNEntry);

      if (iret < 0)
	break;
      
      ++fNEntry;

      if (iret > 0)
	return kTRUE;
    }

  if (fStopwatch != 0)
    fStopwatch->Stop();

  return kFALSE;
}

void TStarJetPicoReaderBase::PrintStatus(const Int_t tsec)
{
  Int_t tx = tsec;
  PrintStatus(tx, kFALSE);
}

void TStarJetPicoReaderBase::PrintStatus(Int_t &tsec, Bool_t updateETA)
{
  //
  // Print status.
  // Just the event numbers.
  // if tsec > 0 then suppress if last call was before tsec
  //

  if (fStopwatch == 0)
    {
      __INFO("Starting timing measurement.");
      fStopwatch = new TStopwatch;
      fStopwatch->Start();
      fLastRealTime = 0.0;
      fNEntryStatus = fNEntryLoaded;
    }
  else
    {
      fStopwatch->Stop();
      Double_t realtime = fStopwatch->RealTime();
      if ((tsec > 0 && (realtime - fLastRealTime < tsec)) 
	  || fNEntryLoaded == 0)
	{
	  if (fNEntry < fNofEntries)
	    {
	      fStopwatch->Continue();
	    }
	  return;
	}
      fLastRealTime = realtime;
      Long64_t iev = fNEntryLoaded - fNEntryStatus;
      Long64_t ievA = iev * fNEntriesAccepted/fNEntryLoaded;
      if (iev < 0)
	{
	  __INFO("No events read so far.");
	}
      else
	{
	  Double_t evPerSec = iev / realtime;
	  Double_t evPerSecAccepted = ievA / realtime;
	  Long64_t ievLeft = fNofEntries - (fNEntryLoaded + 1);
	  if (evPerSec == 0)
	    evPerSec = -1;
	  Double_t ETAsec = ievLeft / evPerSec;
	  __INFO(Form("Current event number:%7lld\t Events left:%7lld\t Accepted events:%7lld", 
		      fNEntryLoaded, ievLeft, fNEntriesAccepted));
	  __INFO(Form("  Average Event Timing: Any:%5.1f Ev/s\tAccepted:%5.1f Ev/s\tETA:%5.1f min", 
		      evPerSec, evPerSecAccepted, ETAsec/60.));
	  if (updateETA)
	    {
	      tsec = Int_t(ETAsec / 3);
	      if (tsec < 20)
		tsec = 20;
	      __INFO(Form("  Real time is %5.1f s. Next update in %5.1f min.", realtime, tsec / 60.));
	    }
	}

      if (fNEntry < fNofEntries)
	{
	  fStopwatch->Continue();
	}
      else
	{
	  __INFO(Form(" Real time: %5.1f s \t CPU time: %5.1f s", realtime, fStopwatch->CpuTime()));
	}
    }
}

void TStarJetPicoReaderBase::PrintEventInfo()
{
  //
  // Provided for convenience.
  // Calling TStarJetPicoUtils::PrintPicoReaderInfo.
  //

  __INFO("Event info... (calling the utils)");
  TStarJetPicoUtils::PrintPicoReaderInfo(this);
}
// ======================================================
// Added by KK to allow customized rejection for some
// very specific cases
// Original goal was one specific event in Run6 Geant
// with an absurdly high pT track (20 GeV for pThat=4-5)
Bool_t TStarJetPicoReaderBase::RejectAnyway()
{
  // For Run6 Geant. Reject absurdly high pT track (20 GeV for pThat=4-5) event
  // This is a truly dumb method relying on naming schemes.
  // That data is a pain. Very hard to uniquely identify an event
  // So use it carefully!
  TFile *CurrentFile = fInputTree->GetCurrentFile();
  if ( TString(CurrentFile->GetName()).Contains( "picoDst_4_5" )
       &&  (
	    ( TString(fInputTree->GetName()) == "JetTreeMc"
	      && fEvent->GetHeader()->GetRunId() == 0 && fEvent->GetHeader()->GetEventId() == 434
	      && fEvent->GetHeader()->GetReferenceMultiplicity() == 31
	      && fEvent->GetHeader()->GetNGlobalTracks() == 38
	      && fabs( fEvent->GetHeader()->GetPrimaryVertexZ()- 52.65) < 1e-1
	      ) ||
	    ( TString(fInputTree->GetName()) == "JetTree"
	      && fEvent->GetHeader()->GetRunId() == 256 && fEvent->GetHeader()->GetEventId() == 434
	      && fEvent->GetHeader()->GetReferenceMultiplicity() == 2
	      && fEvent->GetHeader()->GetNGlobalTracks() == 16
	      && fabs( fEvent->GetHeader()->GetPrimaryVertexZ()- 52.75) < 1e-1
	      )
	    )
       ) {
    std::cout << fInputTree->GetName() << "  " << fEvent->GetHeader()->GetRunId() << "  " << fEvent->GetHeader()->GetEventId() << std::endl;
    return true;
  }
  
  return false;
}
