void makeTree(Int_t nevents = 100)
{
  TFile *outFile = TFile::Open("outFile.root", "RECREATE");
  outFile->cd();

  TTree *outT = new TTree("jettyTree", "STAR Pico Jetty Tree");
  //Int_t split = 99;
  Int_t split = 2;
  Int_t bsize = 64000;  
  TStarJetPicoEvent *event = 0;

  outT->Branch("Jetty", "TStarJetPicoEvent", &event, bsize, split);
 
  TStarJetPicoPrimaryTrack pTrack;
  TStarJetPicoMatchedTower mTower;
  TStarJetPicoTower        emcalTower;

  TRandom rndm;

  Int_t ntracks = 0;
  for (Int_t iev = 0; iev < nevents; iev++)
    {
      event = new TStarJetPicoEvent();

      // set the stuff for the event header
      event->GetHeader()->SetEventId(iev);

      // get the primary tracks filled
      ntracks = rndm.Rndm() * 100;      
      //for (Int_t it = 0; it < ntracks; it++)
      //for (Int_t it = 0; it < 5; it++)
      for (Int_t it = 0; it < ntracks; it++)
	{
	  //pTrack.SetPx(ntracks / 100.);
	  pTrack.SetPx((1.*iev)/nevents);
	  event->AddPrimaryTrack(&pTrack);
	}

      // fill the matched towers
      ntracks = rndm.Rndm() * 1000;      
      for (Int_t it = 0; it < ntracks; it++)
	{
	  //mTower.SetPx(ntracks / 100.);
	  mTower.SetPx(rndm.Rndm() * 10.);
	  mTower.SetPy(rndm.Rndm() * 10.);
	  mTower.SetPz(rndm.Rndm() * 10.);
	  mTower.SetTowerEnergy(rndm.Rndm() * 10.);
	  event->AddMatchedTower(&mTower);
	}

      // fill the all emcal towers
      ntracks = rndm.Rndm() * 100;      
      for (Int_t it = 0; it < ntracks; it++)
	{
	  emcalTower.SetId(ntracks);
	  emcalTower.SetEnergy(ntracks / 100.);
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

void readTree(Int_t nevents = 100)
{
  TFile *inFile = TFile::Open("outFile.root");
  inFile->cd();
  TTree *outT = inFile->Get("jettyTree");

  TStarJetPicoEvent *event = new TStarJetPicoEvent();
  TBranch *branch = outT->GetBranch("Jetty");
  branch->SetAddress(&event);
  
  Int_t ievents = outT->GetEntries();

  TStarJetPicoPrimaryTrack *pTrack = 0;
  TStarJetPicoMatchedTower *mTower = 0;
  TStarJetPicoTower        *emcalTower = 0;

  TH1F *hpxPT = new TH1F("hpxPT", "hpxPT;px;counts", 100, 0, 1);
  TH1F *hpxMT = new TH1F("hpxMT", "hpxMT;px;counts", 100, 0, 1);
  TH1F *hpxEMCT = new TH1F("hpxEMCT", "hpxEMCT;px;counts", 100, 0, 1);
  
  for (Int_t i = 0; i<ievents; i++)
    {
      outT->GetEvent(i);
      
      for (Int_t ntrack = 0; 
	   ntrack < event->GetHeader()->GetNOfPrimaryTracks(); 
	   ntrack++)
	{
	  TStarJetPicoPrimaryTrack *ptrack = event->GetPrimaryTrack(ntrack);
	  hpxPT->Fill(ptrack->GetPx());
	}

      for (Int_t ntrack = 0; 
	   ntrack < event->GetHeader()->GetNOfMatchedTowers(); 
	   ntrack++)
	{
	  TStarJetPicoMatchedTower *mtower = event->GetMatchedTower(ntrack);
	  hpxMT->Fill(mtower->GetPx());
	}

      for (Int_t ntrack = 0; 
	   ntrack < event->GetHeader()->GetNOfEMCALTowers(); 
	   ntrack++)
	{
	  TStarJetPicoTower *tower = event->GetTower(ntrack);
	  hpxEMCT->Fill(tower->GetEnergy());
	}
      
      event->Clear();
    }

  delete event;

  TCanvas *tc = new TCanvas("tc", "tc");
  tc->Divide(2,2);
  tc->cd(1);
  hpxPT->Draw();

  tc->cd(2);
  hpxMT->Draw();

  tc->cd(3);
  hpxEMCT->Draw();
}

void readTreeAnother(Int_t nevents = 100)
{
  TFile *inFile = TFile::Open("outFile.root");
  inFile->cd();
  TTree *outT = inFile->Get("jettyTree");

  TStarJetPicoEvent *event = new TStarJetPicoEvent();
  TBranch *branch = outT->GetBranch("Jetty");
  branch->SetAddress(&event);
  
  Int_t ievents = outT->GetEntries();

  TStarJetPicoPrimaryTrack *pTrack = 0;
  TStarJetPicoMatchedTower *mTower = 0;
  TStarJetPicoTower        *emcalTower = 0;

  TH1F *hpxPT = new TH1F("hpxPT", "hpxPT;px;counts", 100, 0, 1);
  TH1F *hpxMT = new TH1F("hpxMT", "hpxMT;px;counts", 100, 0, 1);
  TH1F *hpxEMCT = new TH1F("hpxEMCT", "hpxEMCT;px;counts", 100, 0, 1);
  
  for (Int_t i = 0; i<ievents; i++)
    {
      outT->GetEvent(i);

      Int_t iptrack = 0;
      TStarJetPicoPrimaryTrack *ptrack = 0;
      while ((ptrack = event->GetPrimaryTrack(iptrack++)) != 0)
	{
	  hpxPT->Fill(ptrack->GetPx());
	}

      Int_t imtower = 0;
      TStarJetPicoMatchedTower *mtower = 0;
      while ((mtower = event->GetMatchedTower(imtower++)) != 0)
	{
	  hpxMT->Fill(mtower->GetPx());
	}

      Int_t itower = 0;
      TStarJetPicoTower *tower = 0;
      while ((tower = event->GetTower(itower++)) != 0)
	{
	  hpxEMCT->Fill(tower->GetEnergy());
	}
      
      event->Clear();
    }

  delete event;

  TCanvas *tc = new TCanvas("tc_2", "tc_2");
  tc->Divide(2,2);
  tc->cd(1);
  hpxPT->Draw();

  tc->cd(2);
  hpxMT->Draw();

  tc->cd(3);
  hpxEMCT->Draw();
}
