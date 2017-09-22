#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TSystem.h>
#include <TRandom.h>
#include <TStopwatch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>

#include "TStarJetPicoEvent.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoTower.h"

#include "TStarJetPicoDefinitions.h"

#include <iostream>
using namespace std;

#define __NTRACKS 5
#define __NTOWERS  5
#define __NMATCHED 5

void makeTree(Int_t nevents = 100)
{
  TFile *outFile = TFile::Open("outFileMP.root", "RECREATE");
  outFile->cd();

  TTree *outT = new TTree("jettyTree", "STAR Pico Jetty Tree");
  //Int_t split = 99;
  Int_t split = 2;
  Int_t bsize = 64000;  
  TStarJetPicoEvent *event = 0;

  outT->Branch("Jetty", "TStarJetPicoEvent", &event, bsize, split);
 
  TStarJetPicoPrimaryTrack pTrack;
  //TStarJetPicoMatchedTower mTower;
  TStarJetPicoTower        emcalTower;

  TRandom rndm;
  cout << "Events to be written: " << nevents << endl;

  Int_t ntracks = 0;
  Int_t ntowers = 0;
  for (Int_t iev = 0; iev < nevents; iev++)
    {
      event = new TStarJetPicoEvent();

      __DEBUG_FUNCTION(2, Form("Event %d", iev));

      // set the stuff for the event header
      event->GetHeader()->SetEventId(iev);
      event->GetHeader()->AddTriggerId(iev);
      event->GetHeader()->AddTriggerId(iev+1);
      event->GetHeader()->AddTriggerId(iev-1);
      // get the primary tracks filled
      //ntracks = Int_t(rndm.Rndm() * 100);      
      ntracks = __NTRACKS + __NTOWERS * __NMATCHED;
      //ntracks = __NTRACKS + __NMATCHED;
      ntracks = Int_t(rndm.Rndm() * ntracks);      
      for (Int_t it = 0; it < ntracks; it++)
	{
	  pTrack.Clear();
	  //pTrack.SetPx(ntracks / 100.);
	  //pTrack.SetPx((1.*iev)/nevents);
	  pTrack.SetPx(it * 0.1 + iev * 1.0);
	  event->AddPrimaryTrack(&pTrack);
	}

      // fill the all emcal towers and randomize matches
      //ntowers = Int_t(rndm.Rndm() * 100);
      ntowers = __NTOWERS;
      ntowers = Int_t(rndm.Rndm() * ntowers);
      for (Int_t it = 0; it < ntowers; it++)
	{
	  emcalTower.Clear();
	  emcalTower.SetId(it);
	  emcalTower.SetEnergy(ntowers / 100.);
	  //Int_t nmtracks = Int_t(rndm.Rndm() * 6);
	  Int_t nmtracks = __NMATCHED;
	  if (nmtracks > ntracks)
	    nmtracks = ntracks;
	  nmtracks = Int_t(rndm.Rndm() * nmtracks);
	  for (Int_t imt = 0; imt < nmtracks; imt++)
	    {
	      //emcalTower.AddMatchedTrack(imt);
	      //OR
	      emcalTower.AddMatchedTrackIndex(imt);

	      TStarJetPicoPrimaryTrack *atrack = event->GetPrimaryTrack(imt);
	      __DEBUG_FUNCTION(2, Form("Write: tower: %d Tidx: %d Matched Track px : %1.1f", 
				       it, imt, atrack->GetPx()));

	    }
	  __DEBUG_FUNCTION(2, Form("Number of assoc tracks %d (%d) for tower %d", 
				   emcalTower.GetNAssocTracks(), nmtracks, it));
	  event->AddTower(&emcalTower);
	}
      
      outT->Fill();
      //TStarJetPicoEvent::Reset();
      delete event;
    }

  outT->Write();
  outFile->cd();
  outFile->Close();
  delete outFile;
  outFile = 0;
}

void readTree(Int_t nevents = 100, Int_t isaveHist = 0)
{
  TFile *inFile = TFile::Open("outFileMP.root");
  inFile->cd();
  TTree *outT = (TTree*)inFile->Get("jettyTree");

  TStarJetPicoEvent *event = new TStarJetPicoEvent();
  TBranch *branch = outT->GetBranch("Jetty");
  branch->SetAddress(&event);
  
  Int_t ievents = outT->GetEntries();

  TH1F *hpxPT = new TH1F("hpxPT", "hpxPT;px;counts", 100, 0, 1);
  TH1F *hpxPT_matched = new TH1F("hpxPT_matched", "hpxPT matched;px;counts", 100, 0, 100);
  TH1F *hpxEMCT = new TH1F("hpxEMCT", "hpxEMCT;px;counts", 100, 0, 1);
  TH2F *hMTidxes = new TH2F("hMTidxes", "hMTidxes;Tower;Track", 
			    100, 0, 100, 100, 0, 100);
  
  TProfile *profAvNMatched = new TProfile("profAvNMatched", "profAvNMatched; index of a tower; average number of matched tracks to a tower", 100, 0, 100); 
  
  if (ievents < nevents)
    {
      nevents = ievents;
    }

  for (Int_t i = 0; i<nevents; i++)
    {
      outT->GetEvent(i);

      __DEBUG_FUNCTION(2, Form("Event %d", i));

      for (Int_t tid = 0;
	   tid < event->GetHeader()->GetNOfTriggerIds();
	   tid++)
	{
	  __DEBUG_FUNCTION(2,Form("Trigger id %d : %d ", tid, event->GetHeader()->GetTriggerId(tid)));
	}
      
      for (Int_t ntrack = 0; 
	   ntrack < event->GetHeader()->GetNOfPrimaryTracks(); 
	   ntrack++)
	{
	  TStarJetPicoPrimaryTrack *ptrack = event->GetPrimaryTrack(ntrack);
	  hpxPT->Fill(ptrack->GetPx());
	}

      // now handle the matched towers
      for (Int_t ntower = 0; 
	   ntower < event->GetHeader()->GetNOfTowers(); 
	   ntower++)
	{
	  TStarJetPicoTower *tower = event->GetTower(ntower);
	  hpxEMCT->Fill(tower->GetEnergy());
	  Int_t nmtracks = tower->GetNAssocTracks();
	  //cout << nmtracks << endl;
	  profAvNMatched->Fill(ntower, nmtracks);
	  __DEBUG_FUNCTION(2, Form("Number of assoc tracks %d for tower %d", 
				   tower->GetNAssocTracks(), ntower));
	  for (Int_t it = 0; it < nmtracks; it++)
	    {
	      Int_t imtidx = tower->GetMatchedTrackIndex(it);
	      Int_t tindex = tower->GetMatchedTracks()->At(it);

	      if (imtidx != tindex)
		__ERROR_FUNCTION("HUGE BUG NO1!");		

	      TStarJetPicoPrimaryTrack *pTrack = event->GetPrimaryTrack(tindex);
	      TStarJetPicoPrimaryTrack *pTrack1 = event->GetMatchedPrimaryTrack(ntower, it);
	      TStarJetPicoPrimaryTrack *pTrack2 = event->GetMatchedPrimaryTrack(tower, it);

	      if (pTrack != pTrack1 || pTrack1 != pTrack2 || pTrack != pTrack2)
		__ERROR_FUNCTION("HUGE BUG NO2!");

	      hpxPT_matched->Fill(pTrack->GetPx());
	      __DEBUG_FUNCTION(2, Form("Read: tower: %d Tidx: %d Matched Track px : %1.1f %1.1f %1.1f", 
				       ntower, it, pTrack->GetPx(), pTrack1->GetPx(), pTrack2->GetPx()));
	      hMTidxes->Fill(ntower, it);
	    }
	}
      
      event->Clear();
    }

  delete event;

  if (isaveHist)
    {
      TFile *histout = new TFile("houtMP.root", "RECREATE");
      histout->cd();
      hpxPT->Write();
      hpxPT_matched->Write();
      hpxEMCT->Write();
      hMTidxes->Write();
      profAvNMatched->Write();
      histout->Close();
      delete histout;      
    }
}

void demoNewMP()
{
  TStarJetPicoDefinitions::SetDebugLevel(3);

  Int_t nevents = 10;

  TString sf = "outFileMP.root";
  const char *found = gSystem->FindFile("./", sf);
  if (found == 0)
    {
      __INFO_FUNCTION("Generating...");
      TStopwatch st1;
      st1.Start();
      //makeTree(10000);
      makeTree(nevents);
      st1.Stop();
      st1.Print();
    }
  else
    {
      __INFO_FUNCTION(Form("File found: %s . Generation skipped.", found));
      __INFO_FUNCTION(Form("Remove %s to trigger generation.", found));
    }

  __INFO_FUNCTION("Reading...");
  TStopwatch st2;
  st2.Start();
  //readTree(10000, 1);
  readTree(nevents, 1);
  st2.Stop();
  st2.Print();
}

int main()
{
  demoNewMP();
}
