#include "TStarJetPicoUtils.h"
#include "TStarJetPicoEvent.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoDefinitions.h"
#include "TStarJetPicoReaderBase.h"
#include "TStarJetPicoQAHistograms.h"

#include <TString.h>
#include <TFile.h> 
#include <TClass.h> 
#include <TChain.h>
#include <TUnixSystem.h>
#include <TRandom.h>
#include <TMessageHandler.h>

#include <TH1D.h>
#include <TH2D.h>

#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////
//                                                            //
// TStarJetPicoUtils                                          //
//                                                            //
// Only static functions helping to do stuff.                 //
//                                                            //
////////////////////////////////////////////////////////////////

#define __INFOF    __INFO_FUNCTION
#define __WARNINGF __WARNING_FUNCTION
#define __ERRORF   __ERROR_FUNCTION

ClassImp(TStarJetPicoUtils)

Float_t TStarJetPicoUtils::GetTowerPoverE(TStarJetPicoTower *tower, TStarJetPicoPrimaryTrack *track)
{
  //
  // Calculate P/E for a given tower and track presumably pointing to it.
  // TStarJetPicoTower, TStarJetPicoPrimaryTrack
  //

  Float_t Px=track->GetPx();
  Float_t Py=track->GetPy();
  Float_t Pz=track->GetPz();
  
  Float_t P=TMath::Sqrt(Px*Px+Py*Py+Pz*Pz);
  return P / tower->GetEnergy();    
}


Float_t TStarJetPicoUtils::GetTowerPoverE(TStarJetPicoEvent *event, TStarJetPicoTower *tower, Int_t trackindex)
{
  //
  // Calculate P/E for a given tower and track pointing to it.
  // TStarJetPicoEvent, TStarJetPicoTower, TStarJetPicoPrimaryTrack
  // Here we call the P/E calculation only for the first track pointint to the tower.
  //

  TStarJetPicoPrimaryTrack *track = event->GetPrimaryTrack(trackindex);
  
  if (tower->GetNAssocTracks() > 1)
    {
      __WARNINGF(Form("Using only matched track with index %d to calculate P/E. This tower has %d tracks matched.",
			      trackindex, tower->GetNAssocTracks()));
    }
  
  if (trackindex >= tower->GetNAssocTracks())
    {
      __ERRORF(Form("Matched track with index %d does not exist. This tower has %d tracks matched.",
			    trackindex, tower->GetNAssocTracks()));	
      return -1.;
    }
  return GetTowerPoverE(tower, track);
}
  
  
Bool_t TStarJetPicoUtils::IsElectron(TStarJetPicoTower *tower, TStarJetPicoPrimaryTrack *track)
{  
  //
  // Return kTRUE if the tower-track match is an electrion.
  // TStarJetPicoTower, TStarJetPicoPrimaryTrack
  // Return kFALSE otherwise.
  // Calling: TStarJetPicoUtils::GetTowerPoverE

  if ( 
       (tower->GetSMDClusterE() * tower->GetSMDClusterP() > 4.0) && 
       (tower->GetSMDClusterE() * tower->GetSMDClusterP() < 100) &&
       GetTowerPoverE(tower, track) < 2.0 
       && (track->GetdEdx() > 3.5e-6 && track->GetdEdx() < 4.2e-6)   
       // && (track->GetdEdx() > 3.0e-6 && track->GetdEdx() < 4.2e-6))
       )
    {      
      return kTRUE;
    }
  else
    {
      return kFALSE;
    }
}
  
Bool_t TStarJetPicoUtils::IsElectron(TStarJetPicoEvent *event, TStarJetPicoTower *tower, Int_t trackindex)
{
  //
  // Return kTRUE if the tower-track match is an electrion. (TStarJetPicoTower)
  // Return kFALSE otherwise.
  // Calculation only for the first track pointing to the tower
  // within an event TStarJetPicoEvent.
  //

  TStarJetPicoPrimaryTrack *track = event->GetPrimaryTrack(trackindex);
  
  if (tower->GetNAssocTracks() > 1)
    {
      __WARNINGF(Form("Using only matched track with index %d to calculate P/E. This tower has %d tracks matched.",
			      trackindex, tower->GetNAssocTracks()));
    }
  
  if (trackindex >= tower->GetNAssocTracks())
    {
      __ERRORF(Form("Matched track with index %d does not exist. This tower has %d tracks matched.",
			    trackindex, tower->GetNAssocTracks()));	
      return kFALSE;
    }    
  return IsElectron(tower, track);
}

TChain *TStarJetPicoUtils::BuildChainFromDirectory(const char *dirPath, 
						   const char *treeName,
						   Int_t nFiles,
						   Int_t nSkipFiles,
						   TChain *chain)
{
  // 
  // Return TChain build from files in the directory. 
  // Reuse TChain if "chain" specified - add files to it.
  // Search for "treeName" trees in the files.
  // Add "nFiles" to the chain starting after skipping "nSkipFiles" in the directory "dirPath".
  //

  void *pdir = gSystem->OpenDirectory(dirPath);
  Int_t i = 0;
  char modif[20];

  if (chain == 0)
    {
      chain = new TChain(treeName);
    }

  while (1)
    {
      if (i >= nFiles && nFiles > 0)
	{
	  break;
	}
      TString sfileX = gSystem->GetDirEntry(pdir);
      if (sfileX.Length() <= 0)
        break;
      TString sfile = dirPath;
      sfile += "/";
      sfile += sfileX;
      //__INFOF(Form("Entry : %s", sfile.Data()));
      if (sfile.Contains(".root"))
        {
          //__INFOF(Form("File : %s", sfile.Data()));
          sprintf(modif, "_%d", i);
          if (nSkipFiles > 0)
            {
              //__INFOF("Skipped.");
              nSkipFiles--;
            }
          else
            {
              __INFOF(Form("Adding file : %s", sfile.Data()));
              chain->AddFile(sfile.Data());
              i++;
            }
        }
    }
  
  return chain;
}

TChain* TStarJetPicoUtils::BuildChainFromDirectoryWithPattern(const char *dirPath, 
							      const char *treeName,
							      const char *pattern,
							      Int_t nFiles,
							      Int_t nSkipFiles,
							      TChain *chain)
{
  // 
  // Return TChain build from files in the directory. 
  // Reuse TChain if "chain" specified - add files to it.
  // Search for "treeName" trees in the files.
  // Add "nFiles" to the chain starting after skipping "nSkipFiles" in the directory "dirPath".
  // Add files according to patter to be contained in the file.
  //

  void *pdir = gSystem->OpenDirectory(dirPath);
  Int_t i = 0;
  char modif[20];

  if (chain == 0)
    {
      chain = new TChain(treeName);
    }

  while (1)
    {
      if (i >= nFiles && nFiles > 0)
	{
	  break;
	}
      TString sfileX = gSystem->GetDirEntry(pdir);
      if (sfileX.Length() <= 0)
        break;
      TString sfile = dirPath;
      sfile += "/";
      sfile += sfileX;
      //__INFOF(Form("Entry : %s", sfile.Data()));
      if (sfile.Contains(".root") && sfile.Contains(pattern))
        {
          //__INFOF(Form("File : %s", sfile.Data()));
          sprintf(modif, "_%d", i);
          if (nSkipFiles > 0)
            {
              //__INFOF("Skipped.");
              nSkipFiles--;
            }
          else
            {
              __INFOF(Form("Adding file : %s", sfile.Data()));
              chain->AddFile(sfile.Data());
              i++;
            }
        }
    }
  
  return chain;  
}

TChain* TStarJetPicoUtils::BuildChainFromFileList(const char *clist, 
						   const char *treeName,
						   Int_t nFiles,
						   Int_t nSkipFiles,
						   TChain *chain)
{
  // 
  // Return TChain build from files in the filelist. 
  // Reuse TChain if "chain" specified - add files to it.
  // Search for "treeName" trees in the files.
  // Add "nFiles" to the chain starting after skipping "nSkipFiles" in the filelist "clist".
  //
  
  if (chain == 0)
    {
      chain = new TChain(treeName);
    }

  Int_t i = 0;
  Int_t iactualFiles = 0;
  std::ifstream input_list;//(clist, std::ifstream::in);
  input_list.open(clist);
  if (!input_list.is_open())
    {
      __ERRORF(Form("Unable to open file %s", clist));
      return chain;
    }

  TMessageHandler mh(TFile::Class());
  Int_t oldCount = mh.GetMessageCount(1001); // count the warnings!
  char listfile[512];
  __INFOF(Form("File : %s", clist));
  //__INFOF(Form("File : %d", input_list.good()));
  while (input_list.good())
    {
      if (i >= nFiles && nFiles > 0)
	{
	  break;
	}
      input_list.getline(listfile,512);
      //__INFOF(Form("line : %s", listfile));
      if(input_list.good()) {
	if (nSkipFiles > 0)
	  {
	    //__INFOF("Skipped.");
	    nSkipFiles--;
	  }
	else
	  {
	    TFile ftmp(listfile);
	    ftmp.Close();
	    if (oldCount < mh.GetMessageCount(1001))
	      {
		__INFOF(Form("File skipped W!: %s", listfile));
	      }
	    else
	      {
		__INFOF(Form("Adding file : %s", listfile));
		chain->AddFile(listfile);
		iactualFiles++;
	      }
	    i++; //count files/lines independent if the file was loaded!
	    oldCount = mh.GetMessageCount(1001);
	  }
      }
    }
  input_list.close();

  __INFOF(Form("TStarJetPicoUtils::BuildChainFromFileList - chained %d files from %d lines read",
	       iactualFiles, i));
	
  return chain;
}


TString TStarJetPicoUtils::GetTriggerIdsString(TStarJetPicoEvent *ev)
{
  //
  // Build a TString from all the trigger ids in the event (TStarJetPicoEvent)
  //

  TString retval = "";
  for (Int_t i = 0; i < ev->GetHeader()->GetNOfTriggerIds(); i++)
    {
      retval += Form("%7d ", ev->GetHeader()->GetTriggerId(i));
    }
  return retval;
}

void TStarJetPicoUtils::PrintPicoReaderInfo(TStarJetPicoReaderBase *reader)
{
  //
  // Dump some basic infos about the event to the stdout.
  // Info taken from TStarJetPicoReader.
  //

  __INFOF(Form("Reader at: %p\t of %s\t Event at %p", 
	       reader, reader->IsA()->GetName(), reader->GetEvent()));
  TFile *fin = reader->GetInputChain()->GetCurrentFile();
  __INFOF(Form(" Current file: %s", fin->GetName()));
  
  Int_t iev = reader->GetNOfCurrentEvent();
  Int_t ievA = reader->GetNOfAcceptedEvents();
  __INFOF(Form(" Current event number: %7d\t Accepted events: %7d ", iev, ievA));
  
  TString str = TStarJetPicoUtils::GetTriggerIdsString(reader->GetEvent());
  __INFOF(Form(" Triggers in the event: %s", str.Data()));
  
  Int_t refm = reader->GetEvent()->GetHeader()->GetReferenceMultiplicity();
  __INFOF(Form(" Reference multiplicity: %5d", refm));

  Float_t Vz = reader->GetEvent()->GetHeader()->GetPrimaryVertexZ();
  __INFOF(Form(" Vertex Z: %5.3f", Vz));
  
  Int_t noutv       = reader->GetOutputContainer()->GetEntries();
  Int_t noftowers   = reader->GetEvent()->GetHeader()->GetNOfTowers();
  Int_t noftowersA  = reader->GetListOfSelectedTowers()->GetEntries();
  Int_t noftracks   = reader->GetEvent()->GetHeader()->GetNOfPrimaryTracks();
  Int_t noftracksA  = reader->GetListOfSelectedTracks()->GetEntries();
  Int_t nofv0s      = reader->GetEvent()->GetHeader()->GetNOfV0s();
  Int_t nofv0sA     = reader->GetListOfSelectedV0s()->GetEntries();
  
  __INFOF(Form(" Input towers: %5d\t Accepted towers: %5d", noftowers, noftowersA));
  __INFOF(Form(" Input tracks: %5d\t Accepted tracks: %5d", noftracks, noftracksA));
  __INFOF(Form(" Input v0s   : %5d\t Accepted v0s   : %5d", nofv0s, nofv0sA));
  __INFOF(Form(" Total number of output vectors: %5d", noutv));
}

void TStarJetPicoUtils::RandomizeContainerInPhi(TStarJetVectorContainer<TStarJetVector>* cont)
{
  //
  // Randomize all the vectors (TStarJetVector) in 
  // the TStarJetVectorContainer<TStarJetVector> 
  // container in azimuth.
  //

  for (Int_t i = 0; i < cont->GetEntries(); i++)
    {
      Double_t newPhi = gRandom->Uniform(-TMath::Pi(),TMath::Pi());
      TStarJetVector *vec = cont->Get(i);
      vec->SetPhi(newPhi);
    }
}

void TStarJetPicoUtils::RotateContainerInPhi(TStarJetVectorContainer<TStarJetVector>* cont, Double_t phi)
{
  //
  // Rotate all the vectors (TStarJetVector) in 
  // the TStarJetVectorContainer<TStarJetVector> 
  // container in azimuth by phi.
  //

  for (Int_t i = 0; i < cont->GetEntries(); i++)
    {
      TStarJetVector *vec = cont->Get(i);
      Double_t newPhi = vec->Phi() + phi;
      vec->SetPhi(newPhi);
    }
}

void TStarJetPicoUtils::FillQAHistogramsFromPicoReader(TStarJetPicoReaderBase *reader)
{
  //
  // Fill the TStarJetPicoQAHistograms singleton with information 
  // from the pico structure reader TStarJetPicoReader
  // and current event TStarJetPicoEvent used within the reader.
  //
  
  TStarJetPicoQAHistograms *qa = TStarJetPicoQAHistograms::Instance();
  if (qa == 0)
    {
      __ERRORF("Unable to get the QA histograms instance!");
      return;
    }

  if (reader == 0)
    {
      __ERRORF("Reader pointer ZERO!");
      return;
    }

  Int_t refMult = reader->GetEvent()->GetHeader()->GetReferenceMultiplicity();
  Float_t Vz = reader->GetEvent()->GetHeader()->GetPrimaryVertexZ();

  //Int_t noutv       = reader->GetOutputContainer()->GetEntries();
  Int_t noftowers   = reader->GetEvent()->GetHeader()->GetNOfTowers();
  Int_t noftowersA  = reader->GetListOfSelectedTowers()->GetEntries();
  Int_t noftracks   = reader->GetEvent()->GetHeader()->GetNOfPrimaryTracks();
  Int_t noftracksA  = reader->GetListOfSelectedTracks()->GetEntries();
  //Int_t nofv0s      = reader->GetEvent()->GetHeader()->GetNOfV0s();
  //Int_t nofv0sA     = reader->GetListOfSelectedV0s()->GetEntries();

  qa->hEventRefMult->Fill(refMult);
  qa->hEventVertexZ->Fill(Vz);
  qa->hEventNPrim->Fill(noftracks);
  qa->hEventNPrimCut->Fill(noftracks);
  qa->hEventNTowers->Fill(noftowers);
  qa->hEventNTowersCut->Fill(noftowersA);
  
  //Track QA
  for (Int_t i = 0; i < noftracks; i++)
    {
      TStarJetPicoPrimaryTrack *ptrack = reader->GetEvent()->GetPrimaryTrack(i);

      qa->hTrackNhits->Fill(ptrack->GetNOfFittedHits());
      qa->hTrackDCA->Fill(ptrack->GetDCA());
      qa->hTrackEta->Fill(ptrack->GetEta());
      qa->hTrackPhi->Fill(ptrack->GetPhi());
      qa->hTrackPoverE->Fill(0.0); //????
      
      if (i < noftracksA)
	{
	  ptrack = (TStarJetPicoPrimaryTrack *)reader->GetListOfSelectedTracks()->At(i);
	  qa->hTrackNhitsCut->Fill(ptrack->GetNOfFittedHits());
	}
    }

  Int_t matchedTowersPerEvent = 0;
  //Tower QA
  for (Int_t i = 0; i < noftowers; i++)
    {
      TStarJetPicoTower *ptower = reader->GetEvent()->GetTower(i);

      // what to fill ? not corrected
      //       hTowerEta->Fill(ptower->GetEta()); 
      //       hTowerPhi->Fill(ptower->GetPhi()); 

      qa->hTowerEta->Fill(ptower->GetEtaCorrected()); 
      qa->hTowerPhi->Fill(ptower->GetPhiCorrected()); 

      Double_t mEt = ptower->GetEnergy() / TMath::CosH(ptower->GetEtaCorrected());
      qa->hTowerET->Fill(mEt); 

      Int_t nassoc = ptower->GetNAssocTracks();
      qa->hNMatched->Fill(nassoc); 
      if (nassoc > 0)
	++matchedTowersPerEvent;

      for (Int_t it = 0; it < nassoc; it++)
	{
	  Int_t idx = ptower->GetMatchedTrackIndex(it);
	  TStarJetPicoPrimaryTrack *ptrack = reader->GetEvent()->GetPrimaryTrack(idx);

	  Double_t diffeta = ptrack->GetEta() - ptower->GetEtaCorrected();
	  Double_t diffphi = ptrack->GetPhi() - ptower->GetPhiCorrected();
	  
	  if( diffeta != 0 || diffphi != 0 ) 
	    {
	      qa->hEtaDiff->Fill(diffeta);
	      qa->hPhiDiff->Fill(diffphi);
	    }
	  
	  Double_t pt = TMath::Sqrt(ptrack->GetPx()*ptrack->GetPx() 
				    + ptrack->GetPy()*ptrack->GetPy());

	  Double_t deta = ptrack->GetEta() - ptower->GetEtaCorrected();
	  Double_t dphi = ptrack->GetPhi() - ptower->GetPhiCorrected();

	  qa->hPtvsEtMatched->Fill(pt, mEt);
	  qa->hEtaMEtaT->Fill(ptrack->GetEta(), ptower->GetEtaCorrected());
	  qa->hPhiMPhiT->Fill(ptrack->GetPhi(), ptower->GetPhiCorrected());
	  qa->hEtaDeltaEta->Fill(ptower->GetEtaCorrected(), deta);
	  qa->hPhiDeltaPhi->Fill(ptower->GetPhiCorrected(), dphi);
	  
	}

      if (i < noftowersA)
	{
	  ptower = (TStarJetPicoTower *)reader->GetListOfSelectedTowers()->At(i);
	  qa->hTowerEtaC->Fill(ptower->GetEtaCorrected()); 
	}
    }
  
  qa->hNMatchedvsRefMult->Fill(matchedTowersPerEvent, refMult);  
}
