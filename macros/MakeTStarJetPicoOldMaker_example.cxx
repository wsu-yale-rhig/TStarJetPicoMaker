 /* STAR Collaboration - Nick Elsey
  
    Example of how to use StMuJetAnalysisPicoMaker to produce
    a tree of TStarJetPicoEvents
  
    this macro produces TStarJetPicoEvents from STAR muDSTs.
    Requires the STAR libraries & muDST files. Defaults 
    are set to use a test.list file which must be filled by
    the user
  
    arguments -- 
    nEvents:    number of events to reproduce
    filelist:   list of filenames & paths to muDSTs
    nametag:    identifier used in output file name
    nFiles:     number of files to accept from the file list
    centrality: collision centrality [0,8], -1 for all centralities     Added 2015 - li yi
                centrality definition comes from StRefMultCorr
                8 is most central
                0 is least central
    trig_flag:  pre-defined sets of triggers & event cuts located in
                in the maker
  
*/

void MakeTStarJetPicoOldMaker_example(int nEvents = 1e3,
                 const char* filelist = "test.list",
                 const char* nametag  = "test",
                 int nFiles = 8,
                 int centrality = -1,
                 int trig_flag  = 144
                  )
{
  // load STAR libraries
  gROOT->Macro( "LoadLogger.C" );
  gROOT->Macro( "loadMuDst.C" );
  
  gSystem->Load( "StarMagField.so" );
  gSystem->Load( "StMagF" );
  gSystem->Load( "StDetectorDbMaker" );
  gSystem->Load( "StTpcDb" );
  gSystem->Load( "St_db_Maker" );
  gSystem->Load( "StDbUtilities" );
  gSystem->Load( "StMcEvent" );
  gSystem->Load( "StMcEventMaker" );
  gSystem->Load( "StDaqLib" );
  gSystem->Load( "StEmcRawMaker" );
  gSystem->Load( "StEmcADCtoEMaker" );
  gSystem->Load( "StEpcMaker" );
  gSystem->Load( "StTriggerUtilities" );
  gSystem->Load( "StDbBroker" );
  gSystem->Load( "libgeometry_Tables" );
  gSystem->Load( "StEEmcUtil" );
  gSystem->Load( "StEEmcDbMaker" );
  gSystem->Load( "StPreEclMaker" );
  gSystem->Load( "StEpcMaker" );
  // load local StRefMultCorr
  gSystem->Load( "libStRefMultCorr.so" );
  // load local TStarJetPico library & its maker
  gSystem->Load( "libTStarJetPico.so" );
  gSystem->Load( "libJetPicoMaker.so" );
	
  StChain* chain           = new StChain( "StChain" );
	
  StMuDstMaker* muDstMaker = new StMuDstMaker( 0, 0, "", filelist, "", nFiles );
  St_db_Maker *dbMaker     = new St_db_Maker( "StarDb", "MySQL:StarDb" );
  StEEmcDbMaker* eemcb     = new StEEmcDbMaker( "eemcDb" );
  StEmcADCtoEMaker *adc    = new StEmcADCtoEMaker();
  StPreEclMaker *pre_ecl   = new StPreEclMaker();
  StEpcMaker *epc          = new StEpcMaker();

  // get control table so we can turn off BPRS zero-suppression and save hits from "bad" caps
  controlADCtoE_st* control_table  = adc->getControlTable();
  control_table->CutOff[1]         = -1;
  control_table->CutOffType[1]     = 0;
  control_table->DeductPedestal[1] = 2;
  adc->saveAllStEvent( kTRUE );
  
  // simulates a trigger response based on an ADC value & trigger definitions
  StTriggerSimuMaker* trigsim = new StTriggerSimuMaker();
  trigsim->setMC( false );
  trigsim->useBemc();
  trigsim->useEemc();
  trigsim->useBbc();
  trigsim->useOnlineDB();
  trigsim->bemc->setConfig( StBemcTriggerSimu::kOffline );
  
  // builds the TStarJetPicoDST
  StMuJetAnalysisTreeMaker *ana = new StMuJetAnalysisTreeMaker;
  ana->SetVerbose( 0 );
  ana->SetFlagData( trig_flag );
  ana->SetDoV0s( kFALSE );
  ana->SelectCentrality( centrality );
  if( centrality>=0 ) { ana->setRootFile( Form( "AuAu14Pico_Cent%d_%s.root", centrality, nametag ) ); }
  else                { ana->setRootFile( Form( "AuAu14Pico_%s.root", nametag ) ); }
  
  // for each event, print the memory usage
  // helpful for debugging
  StMemStat memory;
  memory.PrintMem( NULL );
	
  chain->Init();
  cout << "chain initialized" << endl;
	
  TStopwatch total;
  TStopwatch timer;
	
  int i=0;
  while ( i < nEvents && chain->Make() == kStOk ) {
    if ( i % 500 == 0 ) {
      cout<<"done with event "<<i;
      cout<<"\tcpu: "<<timer.CpuTime()<<"\treal: "<<timer.RealTime()<<"\tratio: "<<timer.CpuTime()/timer.RealTime();//<<endl;
      timer.Start();
      memory.PrintMem( NULL );
    }
    i++;
    chain->Clear();
  }
  
  chain->ls( 3 );
  chain->Finish();
  printf( "my macro processed %i events in %s", i, nametag );
  cout << "\tcpu: " << total.CpuTime() << "\treal: " << total.RealTime() << "\tratio: " << total.CpuTime() / total.RealTime() << endl;

  cout << endl;
  cout << "-------------" << endl;
  cout << "(-: Done :-) " << endl;
  cout << "-------------" << endl;
  cout << endl;
}

