void demoReadNewPicoDST()
{
  TStarJetPicoReader reader;
  
  TStarJetPicoV0Cuts*    v0Cuts = reader.GetV0Cuts();
  reader.SetV0Cuts(new TStarJetPicoV0Cuts);

  TStarJetPicoTrackCuts* trackCuts = reader.GetTrackCuts();
  //reader.SetTrackCuts(new TStarJetPicoTrackCuts);
  TStarJetPicoDemoClass newTrackCuts;
  reader.SetTrackCuts(&newTrackCuts);

  TStarJetPicoTowerCuts* towerCuts = reader.GetTowerCuts();

  TStarJetPicoEventCuts* evCuts = reader.GetEventCuts();
  evCuts->SetTriggerSelection("HT"); //All, MB, HT, pp, ppHT, ppJP
  //evCuts->SetTriggerSelection("MB"); //All, MB, HT, pp, ppHT, ppJP
  //evCuts->SetVertexZCut(5.);
  //evCuts->SetRefMultCut(441);

  //const char *sInputDir = "/star/u/ploskon/lbldisk/picoDSTs";
  //const char *sInputDir = "/data1/picoDSTs";
  const char *sInputDir = "/Users/ploskon/data/star/picoDSTsSample2";

  //reader.LoadDirectory(sInputDir);
  // or:
  // build a chain with 5 files: 20-30 and 3 files: 100-160 -> total 8 files.
  TChain *chain = TStarJetPicoUtils::BuildChainFromDirectory(sInputDir, "JetTree", 5, 20);
  // TChain *chain = TStarJetPicoUtils::BuildChainFromDirectory(sInputDir, "JetTree", 3, 100, chain);
  reader.SetInputChain(chain);
  
  //reader.Init(1000);
  reader.Init();
  reader.PrintStatus();

  while(reader.NextEvent())
    {
      reader.PrintStatus(600); // show status every 10 min.

      // if (reader.GetEvent()->GetHeader()->GetNOfTriggerIds() > 1)
      //   {
      //     TStarJetPicoUtils::PrintPicoReaderInfo(&reader);
      //   }

      // show some info
      // TStarJetPicoUtils::PrintPicoReaderInfo(&reader);
      // or handy
      // reader.PrintEventInfo();

      // fill QA histograms
      TStarJetPicoUtils::FillQAHistogramsFromPicoReader(&reader);

      TStarJetVectorContainer<TStarJetVector>* container = reader.GetOutputContainer();
      // run jet finder on the container or do anythin' else...

      // one can also get the selected (which passed the cuts) tracks or towers or v0s
      // TList *towers = reader->GetListOfSelectedTowers();
      // TList *tracks = reader->GetListOfSelectedTracks();
      // TList *v0s = reader->GetListOfSelectedV0s();

      // randomize phi of all output vectors:
      TStarJetPicoUtils::RandomizeContainerInPhi(container);
    }

  reader.PrintStatus();
  
  // another way of looping through the events:
  // for (Int_t i = 0; i < 2; i++)
  //   {
  //     if (reader.LoadEvent(i) > 0)
  //       {
  //         do your stuff
  //       }
  //   }

  // save the QA histograms
  TStarJetPicoQAHistograms *qa = TStarJetPicoQAHistograms::Instance();
  qa->WriteHistogramsToFile("qaHisto.root");
}
