/*
 Attempts to load all libraries used in our production
 including the TStarJetPico library & TStarJetPicoMaker
 */

void LoadLibs()
{
  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  
  gROOT->Macro("LoadLogger.C"); //mth
  
  char *clibs[] =
  {
    "St_base",
    "StChain",
    "St_Tables",
    "StUtilities",
    "StIOMaker",
    "StarClassLibrary",
    "StTpcDb",
    "StEvent",
    "StDaqLib",
    "StEmcRawMaker",
    "StEmcADCtoEMaker",
    "StPreEclMaker",
    "StEpcMaker",
    
    "StEventUtilities",
    "StEmcUtil",
    "StStrangeMuDstMaker",
    "StMuDSTMaker",
    
    "StDbLib",
    "StDbBroker",
    "StDetectorDbMaker",
    "St_db_Maker",
    "StEEmcDbMaker",
    "StEEmcUtil",
    "StTriggerUtilities",
    "StPicoDstMaker.so",
    "StPicoEvent.so",
    
    //our libs
    "libs/libTStarJetPico.so",
    "libs/libTStarJetPicoMaker.so",
    NULL
  };
  
  Int_t i = 0;
  while ( clibs[i++] != 0 ) {
    cout << endl;
    cout << "| Attempt to load " << clibs[i-1] << endl;
    ierr = gSystem->Load( clibs[i-1] );
    if ( ierr != 0 ) {
      cerr <<  "-> Unable to load " << clibs[i-1] << endl;
    }
    else {
      cout << "-> " << clibs[i-1] << " loaded." << endl;
    }
  }
  cout << endl;
  cout << " Loading done. " << endl;
}
