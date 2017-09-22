 /*
  Author: Sevil Salur 2007
  Analysis code for the tree reconstruction for Jets...
  Added Mark's request April 2008
  Updated with Matuesz's "user friendly" classes See (TStarJetPico*) April 2008
*/

//
//  Include header files. 
#include "TFile.h"
#include "TTree.h"

#include "StMessMgr.h"
#include "TH1.h"
#include "TH2.h"
#include <TVector2.h>

//StEmc
#include "StEmcClusterCollection.h"
#include "StEmcPoint.h"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/others/emcDetectorName.h"
#include "StEmcADCtoEMaker/StBemcData.h"
#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"

#include "StEmcRawMaker/StBemcRaw.h"
#include "StEmcRawMaker/StBemcTables.h"
#include "StEmcRawMaker/StEmcRawMaker.h"
#include "StEmcRawMaker/defines.h"

#include "tables/St_emcStatus_Table.h"
#include "tables/St_smdStatus_Table.h"


#include "StMuDSTMaker/COMMON/StMuEmcCollection.h" 
#include "StEmcCollection.h"
#include "StEmcCluster.h"
#include "StMuDSTMaker/COMMON/StMuEmcPoint.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StEmcUtil/filters/StEmcFilter.h" 
//
#include "StEmcRawHit.h" 
#include "StEmcModule.h"  
#include "StEmcDetector.h" 
#include "StEmcClusterCollection.h"  
#include "StDaqLib/EMC/StEmcDecoder.h"

#include "tables/St_emcStatus_Table.h"
#include "tables/St_smdStatus_Table.h"

#include "StMuDSTMaker/COMMON/StMuEmcCollection.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
#include "StMuDSTMaker/COMMON/StMuPrimaryVertex.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StEvent/StTriggerId.h"
#include "StTriggerUtilities/StTriggerSimuMaker.h"
#include "StTriggerUtilities/StTriggerSimuResult.h"
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"
#include "StTriggerUtilities/L2Emulator/StL2TriggerSimu.h"

#include "StStrangeMuDstMaker/StV0MuDst.hh"

// btofheader for vpdvz
#include "StBTofHeader.h"

// east, west .. variables
#include "StEnumerations.h"	//#ly

// include StRefMultCorr for centrality
#include "StRoot/StRefMultCorr/StRefMultCorr.h"
#include "StRoot/StRefMultCorr/CentralityMaker.h"

#include "StMuJetAnalysisTreeMaker.h"

#include "TStMuCutEventJet.h"
#include "TStMuCutV0Jet.h"
//#include "eventStructure/TParticleTow.h"

#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoTriggerInfo.h"

#include "TStarJetPicoDefinitions.h"
#include "TStarJetPicoQAHistograms.h"

#include "TStarJetPicoUtils.h"

//  Prototype 
void muEventInfo(StMuEvent&, const Int_t&);
ClassImp(StMuJetAnalysisTreeMaker)
  
  // The constructor. Initialize data members here.
  StMuJetAnalysisTreeMaker::StMuJetAnalysisTreeMaker(const Char_t *name) : StMaker(name)
{ 
  mEventCounter = 0;   
  mAllPVEventCounter = 0;
  mInputEventCounter = 0;
  mFile = 0; 
  fNHits=12;
  mGeom = StEmcGeom::instance("bemc");
  mFilter   = new StEmcFilter();  
  mTables   = new StBemcTables(); 
  rMatch    = 0; //counter for matched
  fMatchTrArr = 0;
  fMatchTrEtaArr = 0;
  fMatchTrPhiArr = 0;
  fPrimIndexArray = 0;
  fPrimEtaArray = 0;
  fPrimPhiArray = 0;
  MaxdVz = 6.0;


  doV0 = kTRUE;
  doMc = kFALSE;
  nV0s = 0;
  fTCutV0       = new TStMuCutV0Jet();
  //#ly fTCutV0->SetVerbose(0); 
  fNTOTMatchedTr=0;
  fMatchedTow=0;
  fTrigMap="2006-2008";
  requireBarrelPoints = kTRUE;
  FillAllPV = kFALSE;

  //moved here from Init: enable setting Verbose in macro
  fTCutEvent       = new TStMuCutEventJet();
  //#ly fTCutEvent->SetVerbose(1); 
}

StMuJetAnalysisTreeMaker::~StMuJetAnalysisTreeMaker() { /* noop */ }
//
//  Called once at the beginning.
Int_t StMuJetAnalysisTreeMaker::Init()
{
 
  QAHist = TStarJetPicoQAHistograms::Instance();

  cout << "open a root ouput file " << endl;
  mFile = new TFile(fFilename,"RECREATE","HistoFile");
 
  //fTCutEvent       = new TStMuCutEventJet();
  //fTCutEvent->SetVerbose(1); 

  /*  //QA Plots 

  // hEventRefMult =new TH1D("RefMult","",700,0,700);
 hEventVertexZ =new TH1D("VertexZ","",100,-50,50);
 hEventNPrim=new TH1D("NPrim","",700,0,700);
 hEventNPrimCut=new TH1D("NPrimCut","",700,0,700);
 hEventNTowers=new TH1D("NTowers","",1000,0,5000);
 hEventNTowersCut=new TH1D("NTowersCut","",1000,0,5000);
 //Track QA
 
 hTrackNhits=new TH1D("PNhits","",50,0,50);
 hTrackNhitsCut=new TH1D("PNhitsCut","",50,0,50);
 hTrackDCA=new TH1D("PDCA","",50,-5,5);
 hTrackEta=new TH1D("PEta","",40,-2,2);
 hTrackPhi=new TH1D("PPhi","",40,-4,4);
 hTrackPoverE=new TH1D("PpoverE","",40,0,10);
 //Tower QA
 hTowerEta=new TH1D("TEta","",40,-2,2);
 hTowerEtaC=new TH1D("TEtaC","",40,-2,2);
 hTowerPhi=new TH1D("TPhi","",40,-4,4);
 hTowerET=new TH1D("TEneryT","",100,0,50);
 hNMatched=new TH1D("NMatched","",100,0,500);

 hNMatchedvsRefMult=new TH2D("NMatchedvsRefMult","",100,0,500,70,0,700);
 hPtvsEtMatched=new TH2D("PtvsEtMatched","",100,0,50,100,0,50);
 hEtaMEtaT=new TH2D("EtaMEtaT","",40,-2,2,40,-2,2);
 hPhiMPhiT=new TH2D("PhiMPhiT","",40,-2,2,40,-2,2);

  */


	if(nflagData==9){
    //AuAu Y11 200 GeV L2Gamma
    fTCutEvent->SetStandardCutsAuAuY11L2();
    fTCutEvent->SetMult(0,7000);
    fTCutEvent->SetVertexZ(-30,30);
  }

 if(nflagData==10){
    //AuAu Y11 200 GeV HT
    fTCutEvent->SetStandardCutsAuAuY11HT();
    fTCutEvent->SetMult(0,7000);
    fTCutEvent->SetVertexZ(-30,30);
  }


 if(nflagData==11){
    //AuAu Y11 200 GeV MB
    fTCutEvent->SetStandardCutsAuAuY11MB();
    fTCutEvent->SetMult(0,7000);
    fTCutEvent->SetVertexZ(-30,30);
 }
	
 if(nflagData==140){
   //AuAu Y14 200 GeV MB
   fTCutEvent->SetStandardCutsAuAuY14MB();
   fTCutEvent->SetMult(0, 7000);
   fTCutEvent->SetVertexZ(-30,30);
   // fTCutEvent->SetVertexVpdCut(6); // cm
 }
 
	if(nflagData==141){
		//AuAu Y14 200 GeV HT1
		fTCutEvent->SetStandardCutsAuAuY14HT1();
		fTCutEvent->SetMult(0, 7000);
		fTCutEvent->SetVertexZ(-30,30);
	}
	
	if(nflagData==142){
		//AuAu Y14 200 GeV HT2
		fTCutEvent->SetStandardCutsAuAuY14HT2();
		fTCutEvent->SetMult(0, 7000);
		fTCutEvent->SetVertexZ(-30,30);
	}
	
	if(nflagData==143){
		//AuAu Y14 200 GeV HT3
		fTCutEvent->SetStandardCutsAuAuY14HT3();
		fTCutEvent->SetMult(0, 7000);
		fTCutEvent->SetVertexZ(-30,30);
	}
	
	if(nflagData==144){
		//AuAu Y14 200 GeV HT2 & HT3
		fTCutEvent->SetStandardCutsAuAuY14HT23();
		fTCutEvent->SetMult(0, 7000);
		fTCutEvent->SetVertexZ(-30,30);
	}

  if (FillAllPV) { // cuts on vertex won't be done by event cut!
    PrimaryVertexZmin = fTCutEvent->GetVertexZmin();
    PrimaryVertexZmax = fTCutEvent->GetVertexZmax();
    fTCutEvent->SetVertexZCutOff();
  }

  simuTrig = dynamic_cast<StTriggerSimuMaker*>(GetMaker("StarTrigSimu")); assert(simuTrig); //#ly
  cout<<"******** doing Init  **********"<<endl; 
  MEvent =0;  
  MMcEvent = 0;
  mFile->cd();
  MTree=new TTree("JetTree"," Pico Tree for Jet");
  MTree->Branch("PicoJetTree","TStarJetPicoEvent",&MEvent);//,64000,2);
  MTree->SetAutoSave(100000);
  cout<<"******** end of Init Stage **********"<<endl; 
  if( doMc){
    MMcTree=new TTree("JetTreeMc"," Pico Tree for MC Jet");
    MMcTree->Branch("PicoJetTree","TStarJetPicoEvent",&MMcEvent);//,64000,2);
    MMcTree->SetAutoSave(100000);
  }
  //__DEBUG(2, Form("hkgfkutd %d", 5));

  mPosition = new StEmcPosition();	//#ly

  return StMaker::Init();
}
//
//  Called every event after Make(). 
void StMuJetAnalysisTreeMaker::Clear(Option_t *opt)
{
  delete [] fMatchTrArr;fMatchTrArr=0;
  delete [] fMatchTrEtaArr;fMatchTrEtaArr=0;
  delete [] fMatchTrPhiArr;fMatchTrPhiArr=0;
  delete [] fPrimIndexArray; fPrimIndexArray=0;
  delete [] fPrimEtaArray; fPrimEtaArray=0;
  delete [] fPrimPhiArray; fPrimPhiArray=0;
  StMaker::Clear();
}
//
//  Called once at the end.
Int_t StMuJetAnalysisTreeMaker::Finish()
{
  //  Summarize the run.
  if (mVerbose) {
  	cout << "StMuJetAnalysisTreeMaker::Finish()\n";
  	cout << "\tProcessed " << mEventCounter << " events." << endl;
  	cout << "\tWithout PV cuts: "<< mAllPVEventCounter << " events"<<endl;
  	cout << "\tInput events: "<<mInputEventCounter<<endl;
  }
    
  mFile->cd();

  //  Write histos to file and close it.
  if( mFile){
    QAHist->WriteHistogramsToFile(mFile);
    mFile->Write();  
    mFile->Close();
  }

  if (mVerbose) cout<<"End of StMuJetAnalysisTreeMaker::Finish"<<endl;

  return kStOK;
}
//
//  This method is called every event.
Int_t StMuJetAnalysisTreeMaker::Make()
{
  //  cout<<"EVENT = "<<mEventCounter<<endl;
  //   mEventCounter++;  // increase counter

  ++mInputEventCounter;

  DEBUGVALUE2(mEventCounter);
  //  Get MuDst
  
  mu =  (StMuDst*) GetInputDS("MuDst"); 
  DEBUGVALUE2(mu);
  
  if (!mu){
    gMessMgr->Warning() << "StMuJetAnalysisTreeMaker::Make : No MuDst" << endm;
    return kStOK;        // if no event, we're done
  }
  //
  //  Check StMuEvent branch
 
  muEvent = (StMuEvent*) mu->event();
  
  if (!muEvent) {
    cout << "ReadStMuEvent() -- no event class???" << endl;
    return kStOK;
  }


//event cuts

  //// check event
  if(fTCutEvent->CheckEvent(muEvent) != 1) {
    if (mVerbose)cout<<" ### event not taken ### "<<endl;
    return kStOK;  

  }   
  // initialize StRefMultCorr
  StRefMultCorr* refmultCorrUtil = 0;
  
  StRefMultCorr* refmultCorrUtilRank0 = 0;

  // kk: Changed to reflect code picked up somewhere else :-/
  if ( nflagData == 140 || nflagData == 141 || nflagData == 142 || nflagData == 143 || nflagData == 144 ) {
    refmultCorrUtil = CentralityMaker::instance()->getgRefMultCorr_VpdMB30();
    refmultCorrUtilRank0 = CentralityMaker::instance()->getgRefMultCorr_VpdMB30();
  } else {
    refmultCorrUtil = CentralityMaker::instance()->getgRefMultCorr_VpdMB30();
  }  
  
  if ( refmultCorrUtil -> isBadRun(muEvent->runId()) ) {		// Bad run list in StRefMultCorr
    cerr << "Died because of (non-existent!) bad run list" << endl;
    return kStOK; 
  }

  Bool_t PVok = kTRUE;

  // Get The rank 0 vertex refmult
  // This is being used for y14 comparing high lumi/low lumi data sets
  mu->setVertexIndex(0);
  int rank0RefMult = 0;
  double rank0GRefMult = 0;
  if ( refmultCorrUtilRank0 ) {
    rank0RefMult = muEvent->refMult();
    StThreeVectorF rank0Pos = muEvent->primaryVertexPosition();
    double rank0Pz = rank0Pos.z();
    // find corrected grefmult for rank 0
    refmultCorrUtilRank0->init( muEvent->runId() );		// #ly 2015.06.18
    refmultCorrUtilRank0->initEvent(muEvent->grefmult(),rank0Pz,muEvent->runInfo().zdcCoincidenceRate());			// #ly 2015.06.18
    rank0GRefMult = refmultCorrUtilRank0->getRefMultCorr(); 
  }

  // choose a good vertex near the vpd vz
  StMuPrimaryVertex* fprimaryVertex = 0; //mu->primaryVertex();
  
  int fNVertices = mu->numberOfPrimaryVertices();
  int fUsedVertex=0;
	
  if( fNVertices==0 ) {
    cerr << "No vertex found. " << endl;
    return kStOK;
  }
	
  StThreeVectorF Vposition = muEvent->primaryVertexPosition();
  double fVpdVz = -999;
  double fVz = -999;
  StBTofHeader* tofheader = mu->btofHeader();
  int bestVertexIndex = -999;
  double bestVertexDistance = 9999.99;
  if ( tofheader   )  fVpdVz = tofheader->vpdVz(0);
	
	// Find the best vertex near the VpdVz -- if no vpd info is available assume everything's okay
  if ( fVpdVz!=-999 ) {
    Bool_t FoundVertex=false;
    int verti;
    for (verti = 0; verti<fNVertices ; ++verti){
      mu->setVertexIndex(verti);
      Vposition = muEvent->primaryVertexPosition();
      fVz=Vposition.z();
      if ( fabs(fVz-fVpdVz) < MaxdVz ){
	FoundVertex=true;
	if ( fabs(fVz-fVpdVz) < fabs(bestVertexDistance) ) {
	  bestVertexDistance = fVz-fVpdVz;
	  bestVertexIndex = verti;
	}
      }
    }
    if (!FoundVertex){
      cerr << "No acceptable vertex found. " << endl;
      return kStOK;
    }
    verti = bestVertexIndex;
    mu->setVertexIndex(verti);
    fprimaryVertex = mu->primaryVertex();
    fUsedVertex=verti;
    cout << " ----------------------------------> Using primary vertex # " << verti << " <-----------------------------------" << endl;
  }

  if (!fprimaryVertex) {
    if (mVerbose) cout << "StMuJetAnalysisTreeMaker::ReadStMuEvent() -- no PV ???" << endl;
    PVok = kFALSE;
    PrimVertexZ=-999;
    if (!FillAllPV)
      return kStOK;
  } else
    PrimVertexZ=fprimaryVertex->position().z(); //for tower Eta correction due to z shift of the primary vertex

  if (FillAllPV && fprimaryVertex) { // do the cut on PV z position!
    if (PrimVertexZ < PrimaryVertexZmin || PrimVertexZ > PrimaryVertexZmax)
      PVok = kFALSE;
  }
     
  //StRefMultCorr		// #ly 2015.06.18
  /////////////////////////////////////////////////////////FIXME; // gRefmultCorr stuff
  refmultCorrUtil->init(muEvent->runId());		// #ly 2015.06.18
  refmultCorrUtil->initEvent(muEvent->grefmult(),PrimVertexZ,muEvent->runInfo().zdcCoincidenceRate());			// #ly 2015.06.18
  if(fcentrality>=0) {
    if((refmultCorrUtil->getCentralityBin9())!=fcentrality)
      return kStOK;
  }

  if (PVok) { 
    //cout<<"PRIMARY VERTEX = "<<fprimaryVertex->position().x()<<"  "<<fprimaryVertex->position().y()<<"  "<<fprimaryVertex->position().z()<<"  "<<endl;

    //backward compatibility
    if(mVerbose)cout<<"EVENT = "<<mEventCounter<<endl;
    mEventCounter++;  // increase counter
  }
  
  if(mVerbose)cout<<"EVENT (all PV) = "<<mAllPVEventCounter<<endl;
  mAllPVEventCounter++;  // increase counter

 if( doMc){
    mcEvent =  (StMcEvent*) GetDataSet("StMcEvent"); 
    // DEBUGVALUE2(mcEvent);
    
    if (!mcEvent){
      gMessMgr->Warning() << "StMuJetAnalysisMcTreeMaker::Make : No McEvent" << endm;
      return kStOK;        // if no event, we're done
    }
    if (!mcEvent->primaryVertex()) {
      cout << "StMuJetAnalysisMcTreeMaker::ReadStMcEvent() -- no PV ???" << endl;
      return kStOK;
    }
   if(mVerbose) cout<<"MC PRIMARY VERTEX = "<< mcEvent->primaryVertex()->position().x()<<"  "	<< mcEvent->primaryVertex()->position().y()<<"  "<< mcEvent->primaryVertex()->position().z()<<"  "<<endl;

  }

  MEvent=new TStarJetPicoEvent();


  if(nflagData==9){
    if(mVerbose) cout<<"Au+Au run11 200 GeV set L2gamma"<<endl;
    //L2gamma
    if(muEvent->triggerIdCollection().nominal().isTrigger(350069)==1) MEvent->GetHeader()->AddTriggerId(350069);
  }
  if(nflagData==10 || nflagData==11){
    if(mVerbose) cout<<"Au+Au run11 200 GeV set HT || MB"<<endl;
    vector<unsigned int> triggerIds = muEvent->triggerIdCollection().nominal().triggerIds();
    for(unsigned itrgid = 0; itrgid < triggerIds.size(); itrgid++) {
	    MEvent->GetHeader()->AddTriggerId(triggerIds.at(itrgid));
    }
    ////NPE11	currently not in use for ht trigger
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350505)==1) MEvent->GetHeader()->AddTriggerId(350505);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350515)==1) MEvent->GetHeader()->AddTriggerId(350515);
    ////NPE15
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350502)==1) MEvent->GetHeader()->AddTriggerId(350502);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350512)==1) MEvent->GetHeader()->AddTriggerId(350512);
    ////NPE18
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350503)==1) MEvent->GetHeader()->AddTriggerId(350503);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350513)==1) MEvent->GetHeader()->AddTriggerId(350513);
    ////NPE25
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350504)==1) MEvent->GetHeader()->AddTriggerId(350504);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350514)==1) MEvent->GetHeader()->AddTriggerId(350514);
    ////MB	vpd-zdc-mb-protected
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350003)==1) MEvent->GetHeader()->AddTriggerId(350003);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350013)==1) MEvent->GetHeader()->AddTriggerId(350013);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350023)==1) MEvent->GetHeader()->AddTriggerId(350023);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350033)==1) MEvent->GetHeader()->AddTriggerId(350033);
    //if(muEvent->triggerIdCollection().nominal().isTrigger(350043)==1) MEvent->GetHeader()->AddTriggerId(350043);

  }
	
  if ( nflagData == 140 ) {
    if(muEvent->triggerIdCollection().nominal().isTrigger(450011)==1) MEvent->GetHeader()->AddTriggerId(450011);
    if(muEvent->triggerIdCollection().nominal().isTrigger(450021)==1) MEvent->GetHeader()->AddTriggerId(450021);
  }
	
  if( nflagData == 141 || nflagData == 142 || nflagData == 143 || nflagData == 144 ) {
    if(mVerbose) cout<<"Au+Au run14 200 GeV set HT || MB"<<endl;
    vector<unsigned int> triggerIds = muEvent->triggerIdCollection().nominal().triggerIds();
    for(unsigned itrgid = 0; itrgid < triggerIds.size(); itrgid++) {
      MEvent->GetHeader()->AddTriggerId(triggerIds.at(itrgid));
    }
  }
	
  Bfield  = 0.1*muEvent->runInfo().magneticField(); //this is in tesla,ie 0.1*kilogauss
  // cout<<"     ***** B Field = "<<Bfield<<endl;
  StEventSummary &eventsum = muEvent->eventSummary();
  


// when filling all events, towers, V0 and tracks only filled for events satisfying the PV cuts!!
  if (PVok) {
    if(!mu->muEmcCollection()) return kStOk;      
  
    //cout<<"MEvent Test "<<MEvent<<endl;

    nPrimTrks=doPrimTrks();  

    //Barrel Time
    mEmcCol = (StEmcCollection*)mu->emcCollection();
    rBarrelPts = mEmcCol->barrelPoints().size();
    fNTOTMatchedTr=0;
    doCheckMatchedTracks();
    fMatchedTow=0;


    //if(mVerbose) cout<<"rBarrelPts = "<<rBarrelPts<<"\trequireBarrelPoints = "<<requireBarrelPoints<<endl;	// #ly
    //if(mVerbose) cout<<"barrelPts.begin = "<<mEmcCol->barrelPoints().begin()<<"\tbarrelPts.end = "<<mEmcCol->barrelPoints().end()<<endl;	// #ly
  
    if (rBarrelPts >0 || requireBarrelPoints==kFALSE) {
      nFlag = doTowerMatching();
    }
    else {
      nCand=0;
      nFlag=0;
    }  
 
    if(doV0) nV0s = doV0s();
  
    mTables->loadTables((StMaker*)this);
  
    //  cout<<" reaction plane  "<<GetReactionPlane()<<endl;
    rplane = GetReactionPlane();
  } //PVok
  else 
  {  
    fNTOTMatchedTr = 0;
    rBarrelPts = 0;
    rplane=0.;
    fMatchedTow=0;
  }


    //---------------------- QA Histos -------------------------//
  if(nflagData==140 || nflagData==141 || nflagData==142 || nflagData==143 || nflagData==144)
    {
      QAHist->hEventRefMult->Fill(muEvent->grefmult());
      QAHist->hNMatchedvsRefMult->Fill(fNTOTMatchedTr,muEvent->grefmult());
    }
  
  else{
    QAHist->hEventRefMult->Fill(muEvent->refMult());
    QAHist->hNMatchedvsRefMult->Fill(fNTOTMatchedTr,muEvent->refMult());
  }
  
  
  QAHist->hEventVertexZ->Fill(PrimVertexZ);
  QAHist->hEventNPrim->Fill(mu->numberOfPrimaryTracks());
  QAHist->hEventNPrimCut->Fill(MEvent->GetPrimaryTracks()->GetEntriesFast());
  QAHist->hEventNTowers->Fill(rBarrelPts);
  QAHist->hNMatched->Fill(fNTOTMatchedTr);
    
  

  //---eventlevel tree variables
  MEvent->GetHeader()->SetEventId(static_cast<Int_t>(muEvent->eventId()));
  MEvent->GetHeader()->SetRunId(static_cast<Int_t>(muEvent->runId()));
  MEvent->GetHeader()->SetReferenceMultiplicity(static_cast<Int_t>(muEvent->refMult()));
  MEvent->GetHeader()->SetGReferenceMultiplicity(static_cast<Int_t>(muEvent->grefmult()));
  MEvent->GetHeader()->SetNGlobalTracks(static_cast<Int_t>(mu->numberOfGlobalTracks()));
  MEvent->GetHeader()->SetReactionPlaneAngle(static_cast<Float_t>(rplane));
  MEvent->GetHeader()->SetNOfMatchedTowers(fMatchedTow);
  
  MEvent->GetHeader()->SetGReferenceCentrality(refmultCorrUtil->getCentralityBin9());		// // #ly 2015.06.18
  MEvent->GetHeader()->SetGReferenceCentralityWeight(refmultCorrUtil->getWeight());		// #ly 2015.06.18
  //cout<<refmultCorrUtil->getRefMultCorr()<<" --> "<<(static_cast<Int_t>(refmultCorrUtil->getRefMultCorr()))<<endl;	// #ly

  MEvent->GetHeader()->SetCorrectedGReferenceMultiplicity(static_cast<Int_t>(refmultCorrUtil->getRefMultCorr()));			// #ly 2015.06.18
  
  MEvent->GetHeader()->SetRefMultRank0( static_cast<Int_t>(rank0RefMult) );
  
  MEvent->GetHeader()->SetGRefMultCorrRank0( static_cast<Double_t>(rank0GRefMult) );
  
  //MEvent->GetHeader()->SetNOfTowers(MEvent->GetTowers()->GetEntriesFast());	// note by #ly: It is automatically done when AddTower()
  //MEvent->GetHeader()->SetNOfPrimaryTracks(MEvent->GetPrimaryTracks()->GetEntriesFast());
  
  MEvent->GetHeader()->SetNOfMatchedTracks(fNTOTMatchedTr);

  //nofV0 -->Filled in TStarJetPicoEvent::AddV0
  //nofTrigObj-->Filled in TStarJetPicoEvent::AddTrig
  
  MEvent->GetHeader()->SetNOfEMCPoints(static_cast<Int_t>(rBarrelPts));
  MEvent->GetHeader()->SetPrimaryVertexX(static_cast<Float_t>((eventsum.primaryVertexPosition()).x()));  
  MEvent->GetHeader()->SetPrimaryVertexY(static_cast<Float_t>((eventsum.primaryVertexPosition()).y()));  
  MEvent->GetHeader()->SetPrimaryVertexZ(static_cast<Float_t>(PrimVertexZ));
  if (mu->btofHeader())  {
    MEvent->GetHeader()->SetvpdVz(static_cast<Float_t>(mu->btofHeader()->vpdVz()));  
  }
  else {
    MEvent->GetHeader()->SetvpdVz(-999.);  
  }
  MEvent->GetHeader()->SetCTBMultiplicity(muEvent->ctbMultiplicity());      
  if (fprimaryVertex) {
    MEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(fprimaryVertex->meanDip());
    MEvent->GetHeader()->SetPrimaryVertexRanking(fprimaryVertex->ranking());
		MEvent->GetHeader()->SetPrimaryVertexID(bestVertexIndex);
  } else {
    MEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(-99);
    MEvent->GetHeader()->SetPrimaryVertexRanking(-99);
  }
  MEvent->GetHeader()->SetNumberOfVertices(mu->primaryVertices()->GetEntries());
  MEvent->GetHeader()->SetDSMInput(muEvent->l0Trigger().dsmInput());
  MEvent->GetHeader()->SetTrigMask(muEvent->eventInfo().triggerMask());
  //  MEvent->Dump();

  //cut variables for dAu year 8
  MEvent->GetHeader()->SetZdcWestRate(static_cast<Float_t>(muEvent->runInfo().zdcWestRate()));
  MEvent->GetHeader()->SetZdcEastRate(static_cast<Float_t>(muEvent->runInfo().zdcEastRate()));
  MEvent->GetHeader()->SetZdcCoincidenceRate(static_cast<Float_t>(muEvent->runInfo().zdcCoincidenceRate()));
  StZdcTriggerDetector &ZDC = muEvent->zdcTriggerDetector(); // #ly
  for(int strip=1; strip<9; strip++) {			// #ly
	  MEvent->SetZdcsmd(east,0,strip,ZDC.zdcSmd(east,0,strip));		// 0 for vertical		//#ly
	  MEvent->SetZdcsmd(east,1,strip,ZDC.zdcSmd(east,1,strip));		// 1 for horizontal		//#ly
	  MEvent->SetZdcsmd(west,0,strip,ZDC.zdcSmd(west,0,strip));		// 0 for vertical		//#ly
	  MEvent->SetZdcsmd(west,1,strip,ZDC.zdcSmd(west,1,strip));		// 1 for horizontal		//3ly
  }	//#ly
  MEvent->GetHeader()->SetBbcWestRate(static_cast<Float_t>(muEvent->runInfo().bbcWestRate()));
  MEvent->GetHeader()->SetBbcEastRate(static_cast<Float_t>(muEvent->runInfo().bbcEastRate()));
  MEvent->GetHeader()->SetBbcCoincidenceRate(static_cast<Float_t>(muEvent->runInfo().bbcCoincidenceRate()));
  MEvent->GetHeader()->SetBbcBlueBackgroundRate(static_cast<Float_t>(muEvent->runInfo().bbcBlueBackgroundRate()));
  MEvent->GetHeader()->SetBbcYellowBackgroundRate(static_cast<Float_t>(muEvent->runInfo().bbcYellowBackgroundRate()));
  MEvent->GetHeader()->SetBbcAdcSumEast(static_cast<Int_t>(muEvent->bbcTriggerDetector().adcSumEast()));

  MEvent->GetHeader()->SetBbcOfflineVertex(static_cast<Float_t>(muEvent->bbcTriggerDetector().zVertex()));
  MEvent->GetHeader()->SetBbcOnlineVertex(static_cast<Int_t>(muEvent->bbcTriggerDetector().onlineTimeDifference()));

  MEvent->GetHeader()->SetRefMultFTPCE(static_cast<Int_t>(muEvent->refMultFtpcEast()));

 if( doMc) {
    MMcEvent=new TStarJetPicoEvent();
  }

  //#ly StTriggerSimuMaker *simuTrig = (StTriggerSimuMaker*)GetMaker("StarTrigSimu");
  if(simuTrig)AddTriggerInfo(simuTrig);

  MTree->Fill();

  if( doMc){
    doMcTracks();
    //   for( int i=0;i<MMcEvent->GetHeader()->GetNOfPrimaryTracks();i++){
    //    cout << MMcEvent->GetPrimaryTrack(i)->GetPx() << endl;
    // }
    MMcTree->Fill();
    delete MMcEvent;
  }

  delete MEvent;
  return kStOK;

}
void StMuJetAnalysisTreeMaker::AddTriggerInfo(StTriggerSimuMaker *simuTrig){

  StMuTriggerIdCollection trig = muEvent -> triggerIdCollection();
  StTriggerId l1trig = trig.nominal();
  TStarJetPicoTriggerInfo trigobj;
  for (Int_t i_trig=0; i_trig<20; i_trig++) { 
    if (l1trig.triggerId(i_trig)!=0)
      if (mVerbose) cout << "test i trig   "<<i_trig<<"    "<<l1trig.triggerId(i_trig) << " (v " << l1trig.version(i_trig)<< ") "<<endl;
  }
  Int_t indHT=-1,nTrIds=-1;
  Int_t trId[10]={-999,-999,-999,-999,-999,-999,-999,-999,-999,-999};

  
  if(nflagData==9){//AuAu Y11 L2
    
    trId[0]=350069;//L2gamma		

    nTrIds=1;//n. of elem in trId array
    indHT=0;//index of last HT trigger id in the trId array
  }
  
  if(nflagData==10){//AuAu Y11 HT
    
    trId[0]=350502;	//NPE15		
    trId[1]=350512;	//NPE15		
    trId[2]=350503;	//NPE18
    trId[3]=350513;	//NPE18		
    trId[4]=350504;	//NPE25
    trId[5]=350514;	//NPE25

    nTrIds=6;//n. of elem in trId array
    indHT=5;//index of last HT trigger id in the trId array
  }
	
	if(nflagData==140){
		trId[0]=450011;	//MB-mon
		trId[1]=450021;	//MB-mon
		
		nTrIds=2;//n. of elem in trId array
		indHT=-1;//index of last HT trigger id in the trId array
	}

	if(nflagData==141){
		trId[0]=450201;	//HT1*VPDMB-30
		trId[1]=450211;	//HT1*VPDMB-30
		
		nTrIds=2;//n. of elem in trId array
		indHT=1;//index of last HT trigger id in the trId array
	}

	if(nflagData==142){
		trId[0]=450202;	//HT2*VPDMB-30
		trId[1]=450212;	//HT2*VPDMB-30
		
		nTrIds=2;//n. of elem in trId array
		indHT=1;//index of last HT trigger id in the trId array
	}

	if(nflagData==143){
		trId[0]=450203;	//HT3
		trId[1]=450213;	//HT3
		
		nTrIds=2;//n. of elem in trId array
		indHT=1;//index of last HT trigger id in the trId array
	}

	if(nflagData==144){
		trId[0]=450202;	//HT2*VPDMB-30
		trId[1]=450212;	//HT2*VPDMB-30
		trId[2]=450203;	//HT3
		trId[3]=450213;	//HT3

		nTrIds=4;//n. of elem in trId array
		indHT=3;//index of last HT trigger id in the trId array
	}

	
  Int_t doneBBC=0;		//#ly note: the flag to clear trigobj for the new trigger id
  for(Int_t id=0;id<nTrIds;id++){
    Int_t trigId=l1trig.isTrigger(trId[id]);
    if (mVerbose) cout<<trId[id]<<" l1trig.isTrigger = "<<trigId<<endl;
    StTriggerSimuResult trigResult = simuTrig->detailedResult(trId[id]);
    Float_t etaTow,phiTow;
    if (mVerbose) cout<<"simuTrig.isTrig = "<<simuTrig->isTrigger(trId[id])<<" BEMC="<<simuTrig->bemc->triggerDecision(trId[id])<<" "<<"trigResult.bemcDecision()= "<<trigResult.bemcDecision()<<endl;
    if (trigResult.bbcDecision()==1 && doneBBC==0){		// #ly note: each trigger id obj is separated by this (content 0 & flag 5) entry
      doneBBC=1;
      trigobj.Clear();
      trigobj.SetEta(0);
      trigobj.SetPhi(0);
      trigobj.SetTriggerFlag(5);
      trigobj.SetId(0);
      trigobj.SetADC(0);
      MEvent->AddTrigObj(&trigobj);
      if( doMc) MMcEvent->AddTrigObj(&trigobj);
    }
    // #ly  function trigResult.highTowerIds() is not updated in STAR simu maker. We need to manually set the bemc trigger adc threshold and figure out the tower id
    int BarrelHighTowerTh = 0;		//#ly
    int BarrelHighTowerName = 0;	//#ly
    if(nflagData==10 && (trId[id]==350502 || trId[id]==350512)) {BarrelHighTowerTh = 1;BarrelHighTowerName=115;}	//#ly NPE15
    if(nflagData==10 && (trId[id]==350503 || trId[id]==350513)) {BarrelHighTowerTh = 2;BarrelHighTowerName=118;}	//#ly NPE18
    if(nflagData==10 && (trId[id]==350504 || trId[id]==350514)) {BarrelHighTowerTh = 3;BarrelHighTowerName=125;}	//#ly NPE25
		// NE: copying Li's work for y14
		if(nflagData==141 && (trId[id]==450201 || trId[id]==450211)) {BarrelHighTowerTh = 1;BarrelHighTowerName=115;}	//#NE BHT1
		if(nflagData==142 && (trId[id]==450202 || trId[id]==450212)) {BarrelHighTowerTh = 2;BarrelHighTowerName=118;}	//#NE BHT2
		if(nflagData==143 && (trId[id]==450203 || trId[id]==450213)) {BarrelHighTowerTh = 3;BarrelHighTowerName=125;}	//#NE BHT3
		if(nflagData==144 && (trId[id]==450202 || trId[id]==450212)) {BarrelHighTowerTh = 2;BarrelHighTowerName=118;}	//#NE BHT2
		if(nflagData==144 && (trId[id]==450203 || trId[id]==450213)) {BarrelHighTowerTh = 3;BarrelHighTowerName=125;}	//#NE BHT3

    // #ly note StTriggerUtilities/StVirtualTriggerSimu.h : enum StTriggerSimuDecision { kNo, kYes, kDoNotCare };
    if ( (nflagData==10 || nflagData==141 || nflagData==142 || nflagData==143 ||nflagData==144) && simuTrig->isTrigger(trId[id]) && trigResult.bbcDecision() == 1) {	// #ly the previous method of trigResult.bemcDecision() is not used in run 11 for simumaker
	    vector<short> towerId;
	    for(int itwd = 1; itwd<=4800; itwd++) { 		// loop over simumaker to figure out which tower is fired.
	    	if((simuTrig->bemc->getHT6bitAdc(itwd))>(simuTrig->bemc->barrelHighTowerTh(BarrelHighTowerTh))) {	// #ly the simu maker functions highTowerIds & highTowerAdcs are not updated. we have to manually set the high tower level, compare and get the result
				towerId.push_back(itwd);
				}
	    }
	    for (unsigned i=0; i<towerId.size(); i++) {
	      if (mVerbose)cout<<" HT ********  LO Trigger BEMC Tower="<<towerId[i]<<" adc="<<mu->muEmcCollection()->getTowerADC(towerId[i])<<endl;
	      mGeom->getEtaPhi(towerId[i],etaTow,phiTow);
	      //cout<<"etaTow = "<<etaTow<<" phiTow = "<<phiTow<<endl;	// #ly
	      //TStarJetPicoTriggerInfo trigobj;
	      trigobj.Clear();
	      //trigobj.SetTriggerType("HTL0");
	      trigobj.SetEta(etaTow);
	      trigobj.SetPhi(phiTow);
	      //trigobj.SetTriggerFlag(1);
	      trigobj.SetTriggerFlag(BarrelHighTowerName);	//2015.08.05 #ly
	      trigobj.SetId((towerId[i]));
	      //trigobj.SetADC(mu->muEmcCollection()->getTowerADC(towerId[i]));	// #ly before 2015.07.15, ADC and Id are exchanged by mistake
	      trigobj.SetADC(simuTrig->bemc->getHT6bitAdc(towerId[i]));	// #ly before 2015.07.31, ADC of Mudst was filled instead of the trigger simu maker one ( highest 6 bits, can directly compared with 15, 18, 25 in NPE15, NPE18, NPE25) 
	      MEvent->AddTrigObj(&trigobj);
	      if( doMc) MMcEvent->AddTrigObj(&trigobj);
	      //build the TRIGGER OBJECT for HT L0
	      }
    }
		
    if (trigResult.bemcDecision()==1 && trigResult.bbcDecision() == 1){
      if(id<=indHT && trigId==1 ){
	vector<short> towerId = trigResult.highTowerIds();
	for (unsigned i=0; i<towerId.size(); i++) {
	  if (mVerbose)cout<<" HT ********  LO Trigger BEMC Tower="<<towerId[i]<<" adc="<<trigResult.highTowerAdc(towerId[i])<<endl;
	  mGeom->getEtaPhi(towerId[i],etaTow,phiTow);
	  //cout<<"etaTow = "<<etaTow<<" phiTow = "<<phiTow<<endl;	// #ly
	  //TStarJetPicoTriggerInfo trigobj;
	  trigobj.Clear();
	  //trigobj.SetTriggerType("HTL0");
	  trigobj.SetEta(etaTow);
	  trigobj.SetPhi(phiTow);
	  trigobj.SetTriggerFlag(1);
	  trigobj.SetId(towerId[i]);
	  trigobj.SetADC(trigResult.highTowerAdc(towerId[i]));
	  MEvent->AddTrigObj(&trigobj);
	  if( doMc) MMcEvent->AddTrigObj(&trigobj);
	  //build the TRIGGER OBJECT for HT L0
	  }
      }
      if(id>indHT && trigId==1 ){
	vector<short> towerId = trigResult.jetPatchIds();
	Float_t angle=-999;
	
	for (unsigned i=0; i<towerId.size(); i++) {
	  if(mVerbose)cout<<" JP ********  LO Trigger BEMC Tower="<<towerId[i]<<" adc="<<trigResult.jetPatchAdc(towerId[i])<<endl;
	  mGeom->getEtaPhi(towerId[i],etaTow,phiTow);
	  //cout<<"etaTow = "<<etaTow<<" phiTow = "<<phiTow<<endl;	// #ly
	  //TStarJetPicoTriggerInfo trigobj;
	  trigobj.Clear();
	  // trigobj.SetTriggerType("JPL0");
	  if(fTrigMap.Contains("2006-2008")){
	    if(towerId[i]<6){//WEST PART OF THE BEMC
	      angle=TMath::Pi()*5/6-TMath::Pi()/3*towerId[i];
	      if(angle<0)angle+=TMath::Pi()*2;
	      etaTow=0.5;
	    }
	    else{//EAST PART OF THE bemc
	      Int_t aux=towerId[i];
	      aux-=6;
	      angle=TMath::Pi()*5/6-TMath::Pi()/3*aux;
	      if(angle<0)angle+=TMath::Pi()*2;
	      etaTow=-0.5;
	    }
	  }
	  phiTow=angle;
	  //cout<<" --- > phi,eta = "<<phiTow<<"  "<<etaTow<<endl;
	  trigobj.SetEta(etaTow);
	  trigobj.SetPhi(phiTow);
	  trigobj.SetTriggerFlag(2);
	  trigobj.SetId(towerId[i]);
	  trigobj.SetADC(trigResult.jetPatchAdc(towerId[i]));
	  MEvent->AddTrigObj(&trigobj);
	  if( doMc) MMcEvent->AddTrigObj(&trigobj);
	  //build the TRIGGER OBJECT for HT L0
	}
      }
      
    }
      
      
    if (trigResult.l2Decision()==1){ //L2 decision=1 means true
      if(id<=indHT&& trigId==1){
	vector<short> towerId = trigResult.highTowerIds();
	for (unsigned i=0; i<towerId.size(); i++) {
	  if(mVerbose)cout<<" HT ********  L2 Trigger BEMC Tower="<<towerId[i]<<" adc="<<trigResult.highTowerAdc(towerId[i])<<endl;
	  mGeom->getEtaPhi(towerId[i],etaTow,phiTow);
	  trigobj.Clear();
	  //trigobj.SetTriggerType("HTL2");
	  trigobj.SetEta(etaTow);
	  trigobj.SetPhi(phiTow);
	  trigobj.SetTriggerFlag(3);
	  trigobj.SetId(towerId[i]);
	  trigobj.SetADC(trigResult.highTowerAdc(towerId[i]));
	  MEvent->AddTrigObj(&trigobj);
	  if( doMc) MMcEvent->AddTrigObj(&trigobj);
	  //build the TRIGGER OBJECT for HT L2
	}
      }
      if(id>indHT && trigId==1){
	vector<short> towerId = trigResult.jetPatchIds();
	Float_t angle=-999;
	for (unsigned i=0; i<towerId.size(); i++) {
	  if(mVerbose)cout<<" JP ********  L2 Trigger BEMC Tower="<<towerId[i]<<" adc="<<trigResult.jetPatchAdc(towerId[i])<<endl;
	  mGeom->getEtaPhi(towerId[i],etaTow,phiTow);
	  //TStarJetPicoTriggerInfo trigobj;
	  trigobj.Clear();
	  //trigobj.SetTriggerType("JPL2");
	  if(fTrigMap.Contains("2006-2008")){
	    if(towerId[i]<6){//WEST PART OF THE BEMC
	      angle=TMath::Pi()*5/6-TMath::Pi()/3*towerId[i];
	      etaTow=-0.5;
	    }
	    else{//EAST PART OF THE bemc
	      Int_t aux=towerId[i];
	      aux-=6;
	      angle=TMath::Pi()*5/6-TMath::Pi()/3*aux;
	      etaTow=0.5;
	    }
	  }
	  phiTow=angle;
	  trigobj.SetEta(etaTow);
	  trigobj.SetPhi(phiTow);
	  trigobj.SetTriggerFlag(4);
	  trigobj.SetId(towerId[i]);
	  trigobj.SetADC(trigResult.jetPatchAdc(towerId[i]));
	  MEvent->AddTrigObj(&trigobj);
	  if( doMc) MMcEvent->AddTrigObj(&trigobj);
	  //build the TRIGGER OBJECT for HT L0
	  
	}

      }
    }
    
    
  }

  // MTree->Fill();

  //delete MEvent;//moved here from Make
}
Int_t StMuJetAnalysisTreeMaker::doPrimTrks(){
  
  TStarJetPicoPrimaryTrack MpTrack;
  
  Float_t eta,  phi;
  Int_t flagval; 
  nTracks= mu->primaryTracks()->GetEntries();


  // nMTracks=fmtracklist->GetEntries();
  
  //muEvent = (StMuEvent*) mu->event();
  //StThreeVectorF vertex=muEvent->primaryVertexPosition();
 
  Int_t PrimTrks=0; 
  Int_t ncHit;
  //  Int_t keyC;
  // Int_t matchflag;

  fPrimIndexArray=new Int_t[nTracks];
 
  
  for (Int_t l=0; l<nTracks; l++) { 
    track =  (const StMuTrack*) mu->primaryTracks(l); 
    //    if(track->dcaGlobal().mag()<1.5 && track->eta()<1.5 && track->eta()>-1.5 &&  track->flag() >= 0)
    //cout<<"track=  "<<l<<"  "<<fMatchTrArr[l]<<endl;    
    //    if(fMatchTrArr[l]==3)continue; //track is matched to EMC

    fPrimIndexArray[l]=-10;

    eta=track->eta();
    phi=track->phi();
    flagval=track->flag();
    ncHit=track->nHitsFit();
    QAHist->hTrackNhits->Fill(ncHit);
      
    //      if(flagval >=0 && ncHit>fNHits && matchflag==0){
    if(flagval >=0 && ncHit>fNHits && track->dcaGlobal().mag()<2 && track->eta()<1.5 && track->eta()>-1.5){
      if(mVerbose) cout<<"        "<<eta<<"  "<<phi<<"  "<<flagval<<"  "<<ncHit<<endl;

      QAHist->hTrackNhitsCut->Fill(ncHit);
      QAHist->hTrackDCA->Fill(track->dcaGlobal().mag());
      QAHist->hTrackEta->Fill(eta);
      QAHist->hTrackPhi->Fill(phi);
      

      MpTrack.Clear();
      MpTrack.SetPx(static_cast<Float_t>(track->momentum().x()));      
      MpTrack.SetPy(static_cast<Float_t>(track->momentum().y()));      
      MpTrack.SetPz(static_cast<Float_t>(track->momentum().z())); 
	
      MpTrack.SetDCA(static_cast<Float_t>(track->dcaGlobal().mag()));
      MpTrack.SetdEdx(static_cast<Float_t>(track->dEdx()));
	
      MpTrack.SetNsigmaPion(static_cast<Float_t>(track->nSigmaPion()));
      MpTrack.SetNsigmaKaon(static_cast<Float_t>(track->nSigmaKaon()));
      MpTrack.SetNsigmaProton(static_cast<Float_t>(track->nSigmaProton()));
      MpTrack.SetNsigmaElectron(static_cast<Float_t>(track->nSigmaElectron()));
	
      MpTrack.SetCharge(static_cast<Int_t>(track->charge()));
      MpTrack.SetNOfFittedHits(static_cast<Int_t>(track->nHitsFit()));
      MpTrack.SetNOfPossHits(static_cast<Int_t>(track->nHitsPoss()));
      MpTrack.SetKey(static_cast<Int_t>(track->id()));

      MpTrack.SetChi2(static_cast<Float_t>(track->chi2xy())); // chi2/ndf of the final fit
      MpTrack.SetChi2PV(static_cast<Float_t>(track->chi2z())); //extra chi2 when Primary Vertex is included into the fit

      MpTrack.SetFlag(flagval);

      MpTrack.SetTofTime(track->btofPidTraits().timeOfFlight());	//#ly timing for PID
      MpTrack.SetTofBeta(track->btofPidTraits().beta());		//#ly
      MpTrack.SetTofyLocal(track->btofPidTraits().yLocal());		//#ly

      //signed DCAxy
      gltrack = track->globalTrack();
      StThreeVectorF prVtx = muEvent->primaryVertexPosition();
      if (gltrack) 
	MpTrack.SetsDCAxy(computeXY(prVtx,gltrack->helix()));
      else {
	MpTrack.SetsDCAxy(-99);
	cout<<"Error: Track without associated global track!"<<endl;
      }

      fPrimIndexArray[PrimTrks]=l;
      MEvent->AddPrimaryTrack(&MpTrack);
      PrimTrks++;
    }
      
  }
  return PrimTrks;
}

Int_t StMuJetAnalysisTreeMaker::doCheckMatchedTracks(){
  
  if (mVerbose)cout << "----------- In doCheckMatchedTracks() -----------------" << endl;
  
    //before looping on all the towers: create an array with the index of tracks which have a projection to the BEMC
  
  Int_t nhitcheck,flagval;
  Int_t nTr=MEvent->GetHeader()->GetNOfPrimaryTracks();

 //  nTracks= mu->primaryTracks()->GetEntries(); 
 //  const Int_t nTr=nTracks;
  
  fMatchTrArr=new Int_t[nTr];
  fMatchTrEtaArr=new Float_t[nTr];
  fMatchTrPhiArr=new Float_t[nTr];
  fPrimEtaArray=new Float_t[nTr];
  fPrimPhiArray=new Float_t[nTr];

  for(Int_t i=0;i<nTr;i++){
    fMatchTrArr[i]=-10;
    fMatchTrEtaArr[i]=-10.;
    fMatchTrPhiArr[i]=-10.;
    fPrimEtaArray[i]=-10.;
    fPrimPhiArray[i]=-10.;
  }


  Int_t nMatched=0,n1=0,n2=0,n3=0;

  //cout<<"Number of tracks = "<<nTr<<endl;	// test #ly
  for(Int_t tr =0; tr<nTr; tr++) 
    {//loop over tracks
      Int_t l=fPrimIndexArray[tr];
      track =  (const StMuTrack*)mu->primaryTracks(l); 

    // int id = -1;	// #ly
    // int adc0; float ee[5]; float dist[4]; int nhit[2]; int ntow[3];	//#ly
    // getBEMC(track, &id, &adc0, ee, dist, nhit, ntow);	//#ly

 
      nhitcheck=track->nHitsFit();
      StThreeVectorD momentum,position;
      //#ly StEmcPosition *mPosition = new StEmcPosition();
      flagval=track->flag();

      nhitcheck=track->nHitsFit();
      n1++;   
      if(flagval<0 || nhitcheck<fNHits+1) {
	//delete mPosition;	// test #ly
	continue;
      }
      n2++;

      bool proj_ok= mPosition->projTrack(&position,&momentum,track,(Double_t) Bfield); 
      
      Float_t z,eta,phi;
      eta =position.pseudoRapidity(); 
      phi =position.phi();
      z   =position.z();
      Int_t m,e,s;
      Int_t okbin=mGeom->getBin(phi,eta,m,e,s);
      if (s <0 || okbin==1) {
	//delete mPosition;		// test #ly
	continue;
      }
      n3++;
      
      if (proj_ok){
	fMatchTrArr[tr]=1;
	fMatchTrEtaArr[tr]=eta;
	fMatchTrPhiArr[tr]=phi;
	fPrimEtaArray[tr]=track->eta();
	fPrimPhiArray[tr]=track->phi();
	nMatched++;
      }

      // delete mPosition;		// test #ly
    }


  if(mVerbose)printf("Primary track # = %d and projected to BEMC # = %d \n",nTracks, nMatched);
  if(mVerbose)cout<<"n1,n2,n3="<<n1<<"  "<<n2<<"  "<<n3<<endl;

  return nMatched;
}

Int_t StMuJetAnalysisTreeMaker::doV0s(){

  TStarJetPicoV0 MpV0;
  StV0MuDst *v0MuDst;
  StMuTrack *globTrk;
  Int_t v0=0;
  Int_t posFound, negFound;

  Int_t nV0sMuDst = mu->v0s()->GetEntries();
  
  for (Int_t l=0; l<nV0sMuDst; l++) { 
    v0MuDst =  (StV0MuDst*) mu->v0s(l); 

    if( fTCutV0->CheckV0(v0MuDst, mu) == 1){
      MpV0.Clear();
      MpV0.SetPxPos(static_cast<Float_t>(v0MuDst->momPosX()));
      MpV0.SetPyPos(static_cast<Float_t>(v0MuDst->momPosY()));
      MpV0.SetPzPos(static_cast<Float_t>(v0MuDst->momPosZ()));
      MpV0.SetPxNeg(static_cast<Float_t>(v0MuDst->momNegX()));
      MpV0.SetPyNeg(static_cast<Float_t>(v0MuDst->momNegY()));
      MpV0.SetPzNeg(static_cast<Float_t>(v0MuDst->momNegZ()));
      MpV0.SetKeyPos(static_cast<Int_t>(v0MuDst->keyPos()));
      MpV0.SetKeyNeg(static_cast<Int_t>(v0MuDst->keyNeg()));
      MpV0.SetDcapn(static_cast<Int_t>(v0MuDst->dcaV0Daughters()));
      MpV0.SetDcaV0(static_cast<Float_t>(v0MuDst->dcaV0ToPrimVertex()));
      MpV0.SetDcaPos(static_cast<Float_t>(v0MuDst->dcaPosToPrimVertex()));
      MpV0.SetDcaNeg(static_cast<Float_t>(v0MuDst->dcaNegToPrimVertex()));
      MpV0.SetDecayLength(static_cast<Float_t>(v0MuDst->decayLengthV0()));
      MpV0.SetDedxPos(static_cast<Float_t>(v0MuDst->dedxPos()));
      MpV0.SetDedxNeg(static_cast<Float_t>(v0MuDst->dedxNeg()));

      posFound = 0;
      negFound = 0;
      for(Int_t glob=0; glob<mu->globalTracks()->GetEntries(); glob++){
	globTrk =  mu->globalTracks(glob);
	if( globTrk->id() == v0MuDst->keyPos()){
	  posFound = 1;
	  MpV0.SetNSigmaPionPos(static_cast<Float_t>(globTrk->nSigmaPion()));
	  MpV0.SetNSigmaProtonPos(static_cast<Float_t>(globTrk->nSigmaProton()));
	}
	if( globTrk->id() == v0MuDst->keyNeg()){
	  negFound = 1;
	  MpV0.SetNSigmaPionNeg(static_cast<Float_t>(globTrk->nSigmaPion()));
	  MpV0.SetNSigmaProtonNeg(static_cast<Float_t>(globTrk->nSigmaProton()));
	}
	if( negFound==1 && posFound ==1) break;
      }

      MEvent->AddV0(&MpV0);
      v0++;
    }
  }

  if(mVerbose)cout << "saving " << v0 << " out of " << nV0sMuDst << endl;
  return v0;  

}

Double_t StMuJetAnalysisTreeMaker::GetReactionPlane()
{ 
 if(mVerbose)cout << "----------- In GetReactionPlane() -----------------" << endl;
 TVector2 mQ;
 Double_t mQx=0., mQy=0.;
 Double_t order = 2; Int_t n,i;
 n=mu->primaryTracks()->GetEntries();
 for (i=0; i<n; i++) {
   track = (const StMuTrack*) mu->primaryTracks(i);   // get pointer to primary track
   Float_t phi = track->phi();
   mQx += cos(phi * order);
   mQy += sin(phi * order);
 }
 
 mQ.Set(mQx, mQy);
 Double_t psi= mQ.Phi() / order;
 Float_t pi=TMath::Pi();
 return psi*180/pi;
}


Int_t StMuJetAnalysisTreeMaker::doTowerMatching(){

  if(mVerbose) cout << "----------- In doTowerMatching() -----------------" << endl;
  StBemcTables* tables = mTables;
  assert(tables);
  
  Int_t flag=0;
  mEmcCol = (StEmcCollection*)mu->emcCollection();
  StMuEmcCollection* muEmcCol = mu->muEmcCollection();
  
  if(!mEmcCol || !muEmcCol)
    {
      printf("\n***-- no EMC Collection was found --***\n"); 
      return 1;
    }
    
  StSPtrVecEmcPoint& container =  mEmcCol->barrelPoints();

  if((mEmcCol->barrelPoints().size()==0 || container.size()==0) && requireBarrelPoints==kTRUE){
    cout<<"In doTrack Matching no container or no size"<<endl;
    return -1;
  }
  //cout<<"size barrelPoints = "<<mEmcCol->barrelPoints().size()<<endl;	// #ly
  TStarJetPicoTower allTower;
  TStarJetPicoPrimaryTrack mTrack;
  //  allTower.SetObjArray();

  rBarrelPts = mEmcCol->barrelPoints().size();
    
  StEmcDetector* detector;
  
  detector=mEmcCol->detector(kBarrelEmcTowerId);
 

  Float_t etaTower, phiTower;
  if(detector) {
    Int_t mm = 0, ee = 0, ss = 0;	 
    Int_t statusAll  =-99;
    Int_t towerId = 0;
    fMatchedTow=0;

    // cout<<" counts   "<<fmtowerlist->GetEntries()<<endl;

    for (UInt_t i = 1; i < 121; i++){
      StSPtrVecEmcRawHit& emcTowerHits = detector->module(i)->hits();

      for (UInt_t j = 0; j < emcTowerHits.size(); j++){
	mm = (Int_t)emcTowerHits[j]->module();
	ee = (Int_t)emcTowerHits[j]->eta();
	ss = emcTowerHits[j]->sub();
	
	if(abs(mm)<=120&&abs(ee)<=20&&ss<=2)	 {
	  
	  mGeom->getId(mm, ee, ss, towerId);
	  tables->getStatus(BTOW, towerId, statusAll);
	  
	  if(statusAll==1){
	
	    //  Int_t matchflagtow;
	    Float_t energyTowerAll=emcTowerHits[j]->energy();
	    Float_t ADCTower=emcTowerHits[j]->adc();
	  
	    if(energyTowerAll<0.15)continue;//added new Fri Oct31 08
	    mGeom->getEtaPhi(towerId,etaTower,phiTower);
	    
	    // 	    if(matchflagtow==1 || energyTowerAll<=0.) continue;
	    //   if(energyTowerAll<=0) continue;
	    Int_t didT=towerId;
	    

	    if(nflagData==0 || nflagData==1){ //cout<<"Twr Id Check for hot towers"<<endl;
	    
	      if(didT==1433||didT==3407||didT==3711||didT==3720||didT==3840||didT==1130||didT==1132||didT==114||didT==1197||didT==1257||didT==1274 ||didT==1278 ||didT==1294||didT==1300||didT==1319||didT==1348||didT==1350||didT==1428||didT==1537||didT==1666||didT==1709||didT==1791||didT==1871||didT==1909||didT==2066||didT==2313||didT==308 ||didT==3364||didT==3375||didT==3420||didT==3428||didT==3740||didT==4132||didT==4152||didT==4262||didT==4422||didT==4453||didT==4498||didT==4691||didT==509||didT==576||didT==59||didT==591||didT==636||didT==707||didT==740||didT==762||didT==779 ||didT==830||didT==887 ||didT==899||didT==972) 
		continue;
	    }
	    
	    Int_t ehits,phits;
	    StEmcCluster* closeclust1 = findSMDCluster(etaTower,phiTower,2);//SmdE
	    if (closeclust1 !=NULL) {
	      ehits = SMDHits(2,clusterid);
	    }
	    StEmcCluster* closeclust2 = findSMDCluster(etaTower,phiTower,3);//smdP
	    if (closeclust2 !=NULL) {
	      phits = SMDHits(3,clusterid);
	    }

	    //Correction of PVZ shift
 
	    Float_t etaC, T1;
	    T1=2*atan(exp(-etaTower));
	    Double_t zNew;
	    if(etaTower!=0){zNew=231/tan(T1);} //231 cm = radius SMD
	    if(etaTower==0){zNew=0;}
	    Double_t zNom=zNew-PrimVertexZ;
	    Double_t THETA=atan2(231,zNom);
	    etaC=-log(tan(THETA/2));

	    //cout<<"phiTower = "<<phiTower<<" etaTower = "<<etaTower<<endl;	// test #ly

	    allTower.Clear();
	    allTower.SetPhi(static_cast<Float_t>(phiTower));
	    allTower.SetEta(static_cast<Float_t>(etaTower));
	    allTower.SetId(static_cast<Int_t>(towerId));
	    allTower.SetEnergy(static_cast<Float_t>(energyTowerAll));
	    allTower.SetADC(static_cast<Int_t>(ADCTower));
	    allTower.SetPhiCorrected(static_cast<Float_t>(phiTower)); //Not really corrected as no change is expected
	    allTower.SetEtaCorrected(static_cast<Float_t>(etaC));
	 
	    allTower.SetSMDClusterP(static_cast<Int_t>(phits));
	    allTower.SetSMDClusterE(static_cast<Int_t>(ehits));
   	    allTower.SetTowerStatus(static_cast<Int_t>(statusAll));
	    Double_t ettower=energyTowerAll/TMath::CosH(etaC);

	    QAHist->hTowerEta->Fill(etaTower);
	    QAHist->hTowerPhi->Fill(phiTower);
	    
	    QAHist->hTowerEtaC->Fill(etaC);
	    QAHist->hTowerET->Fill(ettower);
	   
	    
	    Int_t count=0;
	    Int_t Nofprim=MEvent->GetHeader()->GetNOfPrimaryTracks();

	    
	    for(Int_t tr =0; tr<Nofprim; tr++) //this is nCand
	      {
		if(fMatchTrArr[tr]==1){

		  Float_t etaE,phiE,eta,phi;
		  etaE=fMatchTrEtaArr[tr];
		  phiE=fMatchTrPhiArr[tr];
		  eta=fPrimEtaArray[tr];
		  phi=fPrimPhiArray[tr];

 		  Float_t dphi = phiE - phiTower;
 		  Float_t deta = etaE - etaTower;

		  QAHist->hDeltaEtaDeltaPhiProj->Fill(deta,dphi);

		  //cout<< " dphi  "<<dphi<<"  deta  "<<deta<<endl;	//#ly
		  if (fabs(dphi) > 0.025) continue;
		  if (fabs(deta) > 0.025) continue;
		  QAHist->hDeltaEtaDeltaPhiProjAcc->Fill(deta,dphi);

		  Int_t l=fPrimIndexArray[tr];
		  track =  (const StMuTrack*) mu->primaryTracks(l); 
		  
		  Double_t trackorphi=track->phi();
		  Double_t trackoreta=track->eta();
		  Double_t diffeta=trackoreta-eta;
		  Double_t diffphi=trackorphi-phi;


		  if(diffeta!=0 || diffphi!=0) {
		    cout<<"==== DoTowerMatching ==== Sanity Check: Problem with the matched index "<<endl;
		    QAHist->hEtaDiff->Fill(diffeta);
		    QAHist->hPhiDiff->Fill(diffphi);

		  }
		  

		  Double_t pttrack=track->pt();
		  //Float_t POverE=-99;
		  
		  //POverE=TStarJetPicoUtils::GetTowerPoverE(MEvent,&allTower,tr);
		  //mTrack.Clear();
		  //mTrack.SetPx(track->momentum().x());
		  //mTrack.SetPy(track->momentum().y());
		  //mTrack.SetPz(track->momentum().z());
		  //POverE=TStarJetPicoUtils::GetTowerPoverE(&allTower,&mTrack);
		  
		  Float_t Pz=track->momentum().z();
		  Float_t POverE=TMath::Sqrt(pttrack*pttrack+Pz*Pz)/energyTowerAll;
		  //cout<<"POverE   "<<POverE<<"    "<<POverEMine<<endl;
		  QAHist->hTrackPoverE->Fill(POverE);
		  QAHist->hPtvsEtMatched->Fill(pttrack,ettower);
		  QAHist->hEtaMEtaT->Fill(eta,etaTower);
		  QAHist->hPhiMPhiT->Fill(phi,phiTower);
		  QAHist->hEtaDeltaEta->Fill(eta,deta);
		  QAHist->hPhiDeltaPhi->Fill(phi,dphi);
		  
		    
		  // mTrack.SetEtaDiffHitProjected(static_cast<Float_t>(deta));
		  // mTrack.SetPhiDiffHitProjected(static_cast<Float_t>(dphi));
		  
		  count++;
		  fNTOTMatchedTr++;
		  allTower.AddMatchedTrack(tr); 
		  //cout<<"Add MatchedTraks : "<<fNTOTMatchedTr<<endl; // #ly
		  fMatchTrArr[tr]=3;
		  //delete mPosition;
		}
	      }
	    MEvent->AddTower(&allTower);
	    flag++;
	    // cout<<"Tower added"<<endl; 	// #ly
	    if(allTower.GetNAssocTracks()>0) fMatchedTow++;
	  }
	}
      }
    }
  }
  
  else {
    printf("no detector in EMC collection id \n");
  }
  
  if(mVerbose)cout<<"number of total associated tracks in the event = "<<fNTOTMatchedTr<<"  N of Towers with at least 1 matched track = "<<fMatchedTow<<endl;
  if(mVerbose)printf("Out StMuJetAnalysisTreeMaker:doMatchedTower \n");
  return flag;
}


StEmcCluster* StMuJetAnalysisTreeMaker::findSMDCluster(Float_t eta, Float_t phi,Int_t det)
{
  if(mVerbose==1)cout << "----------- In findSMDCluster() -----------------" << endl;
  //looking for corresponding cluster in SMD detector (det=2 SMDe, det=3 SMDp) with eta,phi of
  // TPC track
  StEmcCluster *clusterSMD = NULL;
  clusterid = -1;
  Float_t dmin = 9999;
  Float_t dmin_cut = 0.05; //this is cut on difference of SMD cluster eta,phi difference from TPC eta,phi 
  
  StDetectorId id = static_cast<StDetectorId>(det+kBarrelEmcTowerId);
  if(mVerbose) cout<<"kBarrelEmcTowerId = "<<kBarrelEmcTowerId<<" detectorid = "<<id<<endl; 	//#ly
  StEmcDetector* detector=mEmcCol->detector(id);
  if(!detector) { cout<<"no SMD"<<endl; } 	// #ly
  if(detector) {
    StEmcClusterCollection* clusters = detector->cluster();
    if(clusters) {
      StSPtrVecEmcCluster& cl=clusters->clusters();
      //if(mVerbose) printf("number of SMD det %i clusters %i\n",det,cl.size());
      if(cl.size()>0) {
	for(Int_t i=0;i<(Int_t)cl.size();i++) if(cl[i]) { 
	  //going over all cluster
	  Float_t ETA = cl[i]->eta();
	  Float_t PHI = cl[i]->phi();
	  Float_t d = sqrt((eta-ETA)*(eta-ETA)+(phi-PHI)*(phi-PHI));
	  
	  if(d<dmin) {
	    //storing clusters with up to now best matching
	    dmin = d;
	    clusterid = i; 
	  }
	}//loop over clusters    
      }

      if(mVerbose==1)cout << "the minimum tower and smd cluster is "<<dmin<<endl;//#ly
      
      if(dmin<dmin_cut && clusterid!=-1) {
	clusterSMD = cl[clusterid];
	if(mVerbose==1)cout <<"Found SMD cluster for detector "<<det<<"\t distance="<< dmin << endl;
      
      }
    }//if clusters !NULL
  }//if detector !NULL
  
  return clusterSMD;
}


Int_t  StMuJetAnalysisTreeMaker::SMDHits(Int_t det, Int_t clustid)
{
  //looking for corresponding cluster in SMD detector (det=2 SMDe, det=3 SMDp) with eta,phi of
  Int_t nhits=0;
  StDetectorId id = static_cast<StDetectorId>(det+kBarrelEmcTowerId);
  StEmcDetector* detector=mEmcCol->detector(id);
  if(detector) {
    StEmcClusterCollection* clusters = detector->cluster();
    if(clusters) {
      StSPtrVecEmcCluster& cl=clusters->clusters();
      nhits = cl[clustid]->nHits();
    }    
  }
  return nhits;
}


// same math as in $STAR/StRoot/StMiniMcMaker/StMiniMcMaker.cxx
Float_t StMuJetAnalysisTreeMaker::computeXY(const StThreeVectorF& pos, const StPhysicalHelixD &helix)
{
  // find the distance between the center of the circle and pos.                                                              
  // if this greater than the radius of curvature, then call                                                                                                           
  // it negative.                                                                                                                                                    
                                                                                                                                                                        
  double xCenter = helix.xcenter();
  double yCenter = helix.ycenter();
  double radius  = 1.0/helix.curvature();

  double dPosCenter
    = TMath::Sqrt( (pos.x()-xCenter) * (pos.x()-xCenter) +
                   (pos.y()-yCenter) * (pos.y()-yCenter));

  return (Float_t) radius - dPosCenter;
}

void StMuJetAnalysisTreeMaker::doMcTracks(){
  
  int nCount = 0;
  
  const StPtrVecMcTrack& mcTracks = mcEvent->primaryVertex()->daughters();
  StMcTrackConstIterator mcTrkIter = mcTracks.begin();
  
  for ( ; mcTrkIter != mcTracks.end(); ++mcTrkIter) {
    StMcTrack* track = *mcTrkIter;
    TStarJetPicoPrimaryTrack mTrack;
    
    // cout << track->parent() << endl;
    // if( track->parent() != 0) continue;
    // cout << "Saving track " << endl;
    mTrack.SetPx(static_cast<float>(track->momentum().x()));	  
    mTrack.SetPy(static_cast<float>(track->momentum().y()));	  
    mTrack.SetPz(static_cast<float>(track->momentum().z()));	  
    mTrack.SetDCA(0); 
    //   mTrack.SetdEdx(static_cast<float>(track->pdgId()));
    
    mTrack.SetNsigmaPion(0);
    mTrack.SetNsigmaKaon(0);
    mTrack.SetNsigmaProton(0);
    mTrack.SetNsigmaElectron(0);
    
    if( track->particleDefinition()){
      mTrack.SetCharge(static_cast<int>(track->particleDefinition()->charge()));
      mTrack.SetdEdx(static_cast<int>(track->particleDefinition()->pdgEncoding()));
    }
    else{
      cout << "Particle with no encoding " << endl;
      mTrack.SetCharge(0);
      mTrack.SetdEdx(0);
    }
    //mTrack.SetNOfFittedHits(10);
    //mTrack.SetNOfPossHits(10);
    mTrack.SetNOfFittedHits(static_cast<int>(track->tpcHits().size()));
    mTrack.SetNOfPossHits(52);
    mTrack.SetKey(static_cast<int>(track->key()));
    mTrack.SetEtaDiffHitProjected(0);
    mTrack.SetPhiDiffHitProjected(0);
    nCount++;
    //cout<<mTrack.GetPx()<<"  "<<mTrack.GetPy()<<"  "<<mTrack.GetPz()<<"  "<<endl;

    MMcEvent->AddPrimaryTrack(&mTrack); //not sure
   
  }


  MMcEvent->GetHeader()->SetEventId(static_cast<int>(mcEvent->eventNumber()));
  MMcEvent->GetHeader()->SetRunId(static_cast<int>(mcEvent->runNumber()));
  MMcEvent->GetHeader()->SetReferenceMultiplicity(static_cast<int>(mcEvent->eventGeneratorFinalStateTracks()));
  MMcEvent->GetHeader()->SetNPrimaryTracks(static_cast<int>(nCount));
  MMcEvent->GetHeader()->SetNGlobalTracks(static_cast<int>(mcEvent->numberOfPrimaryTracks()));		// #ly 2015.08.07 note: why not Global tracks??
  MMcEvent->GetHeader()->SetReactionPlaneAngle(mcEvent->phiReactionPlane());
  
  MMcEvent->GetHeader()->SetPrimaryVertexX(static_cast<float>(mcEvent->primaryVertex()->position().x()));  
  MMcEvent->GetHeader()->SetPrimaryVertexY(static_cast<float>(mcEvent->primaryVertex()->position().y()));
  MMcEvent->GetHeader()->SetPrimaryVertexZ(static_cast<float>(mcEvent->primaryVertex()->position().z()));


  MMcEvent->GetHeader()->SetCTBMultiplicity(0);      
  MMcEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(0);
  MMcEvent->GetHeader()->SetPrimaryVertexRanking(0);
  MMcEvent->GetHeader()->SetNumberOfVertices(1);

  MMcEvent->GetHeader()->SetNOfEMCPoints(0);
  MMcEvent->GetHeader()->SetNOfMatchedTowers(0);
  MMcEvent->GetHeader()->SetNOfTowers(0);
  MMcEvent->GetHeader()->SetNOfPrimaryTracks(nCount);
  MMcEvent->GetHeader()->SetNOfMatchedTracks(0);

  return;
}


