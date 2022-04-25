//adapted Feb 2020 by Isaac Mooney not to need input from the Geant files. All info obtained from the MuDsts or Minimcs

#include "TStarJetPicoMaker.hh"

#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoTriggerInfo.h"
#include "TDatabasePDG.h"

#include "StRefMultCorr/StRefMultCorr.h"
#include "StRefMultCorr/CentralityMaker.h"

#include "St_base/StMessMgr.h"
#include "StEvent/StBTofHeader.h"
#include "StEvent/StZdcTriggerDetector.h"
#include "StTriggerUtilities/Bemc/StBemcTriggerSimu.h"
#include "StarClassLibrary/StParticleDefinition.hh"

#include "StEmcClusterCollection.h"
#include "StEmcPoint.h"
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
#include "StEmcRawHit.h"
#include "StEmcModule.h"
#include "StEmcDetector.h"
#include "StEmcClusterCollection.h"
#include "StDaqLib/EMC/StEmcDecoder.h"

#include <math.h>

ClassImp(TStarJetPicoMaker)

TStarJetPicoMaker::TStarJetPicoMaker(std::string outFileName, TChain* mcTree,
        inputMode input, std::string name, int nFiles, int trigSet)
: StMaker(name.c_str()), mEventSelector(new TStarJetEventCuts), mV0Selector(new TStarJetV0Cuts),
  mOutFileName(outFileName), mOutFile(nullptr), mTree(nullptr), mMCTree(nullptr),
  mEvent(nullptr), mMCEvent(nullptr), mMuDstMaker(nullptr), mMuDst(nullptr), mMuInputEvent(nullptr),
  mPicoDst(nullptr), mPicoInputEvent(nullptr), mTriggerSimu(nullptr), mStMiniMcEvent(nullptr),
    mEMCPosition(nullptr), mBEMCGeom(nullptr), mEMCFilter(nullptr), mBemcTables(nullptr),
    mBemcMatchedTracks(), mRefMultCorr(nullptr), mGRefMultCorr(nullptr), mCallsToMake(0),
    mNEvents(0), mNAcceptedEvents(0), mMakeV0(kFALSE), mMakeMC(kFALSE), mInputMode(input),
    mVertexMode(VpdOrRank), mTowerStatusMode(AcceptAllTowers), mRefMultCorrMode(FillNone),
    mdVzMax(3.0), mTrackFlagMin(0), mTrackDCAMax(3.0), mTrackEtaMin(-1.5), mTrackEtaMax(1.5),
    mTrackFitPointMin(10), mTowerEnergyMin(0.15) {
  
        if (!LoadTree(mcTree)) {
          LOG_INFO << "load chain failed" << endm;
          LOG_INFO << " No MC Tree, assumed not to use only Dst trees, not MC tress" << endm;
          mRunMode = mode_Dst;
        } else {
          mRunMode = mode_MC;
        }
        mMakeMC = (mRunMode == mode_MC);
        
        current_ = 0;

	    //for later use looking up PDG masses using particle PID
	    if (mMakeMC) pdg = new TDatabasePDG();
    }

TStarJetPicoMaker::~TStarJetPicoMaker() {
  delete mEventSelector;
  delete mV0Selector;
  delete mTree;
  delete mMCTree;
  delete mEvent;
  delete mMCEvent;
}

Int_t TStarJetPicoMaker::Init() {
  if (InitInput() != kStOk) { return kStStop; }
  InitMakers();
  InitOutput();
  return StMaker::Init();
}

void  TStarJetPicoMaker::Clear(Option_t* option) {
  mBemcMatchedTracks.clear();
  StMaker::Clear(option);
}

Int_t TStarJetPicoMaker::Finish() {
  
  mOutFile->cd();
  mTree->Write();
  if (mMakeMC) mMCTree->Write();
  mOutFile->Close();
  
  LOG_INFO << "TStarJetPicoMaker : Wrote tree to file - finished" << endm;
  LOG_INFO << "From " << mCallsToMake << " calls to Make()," <<endm;
  LOG_INFO << "Processed " << mNEvents << " from input, " << endm;
  LOG_INFO << "With " << mNAcceptedEvents << " passing cuts and written to file" << endm;
  
    
  mEventSelector->PrintStats();
  
  return kStOk;
}

bool TStarJetPicoMaker::LoadTree(TChain* chain) {
  if (chain == nullptr) {
    LOG_INFO << "chain does not exist" << endm;
    return false;
  }
  if (mMakeMC) {
      if (chain->GetBranch("StMiniMcEvent") == nullptr) {
        LOG_ERROR << "chain does not contain StMiniMcEvent branch" << endm;
        return false;
      }
      chain_ = chain;
      mStMiniMcEvent = new StMiniMcEvent;
      
      chain_->SetBranchAddress("StMiniMcEvent", &mStMiniMcEvent);
      chain_->GetEntry(0);
  }
  return true;
}

Int_t TStarJetPicoMaker::Make() {
  mCallsToMake++;
    
  if (mMakeMC) {
      if (mStMiniMcEvent == nullptr) {
          LOG_ERROR << "StMiniMcEvent Branch not loaded properly: exiting run loop" << endm;
          return kStFatal;
      }
      // load the matching miniMC event
      if (LoadEvent() == false) {
          LOG_ERROR << "Could not find miniMC event matching muDST event" << endm;
          return kStErr;
      }
  }
  
  if (mInputMode == InputMuDst)
      return MakeMuDst();
  else if (mInputMode == InputPicoDst)
      return MakePicoDst();
  else
      return kStErr;
}

Int_t TStarJetPicoMaker::InitInput() {
  mPicoDstMaker = (StPicoDstMaker*) GetMakerInheritsFrom("StPicoDstMaker");
  mMuDstMaker = (StMuDstMaker*) GetMakerInheritsFrom("StMuDstMaker");
  switch (mInputMode) {
    case NotSet :
      
      if (mPicoDstMaker && mMuDstMaker) {
        LOG_ERROR << "TStarJetPicoMaker: Ambiguous input source. Specify PicoDst or MuDst" << endm;
        return kStStop;
      }
      
      else if (mPicoDstMaker) {
        LOG_DEBUG << "TStarJetPicoMaker: input set to PicoDst" << endm;
        mInputMode = InputPicoDst;
      }
      
      else if (mMuDstMaker) {
        LOG_DEBUG << "TStarJetPicoMaker: input set to MuDst" << endm;
        mInputMode = InputMuDst;
      }
      
      else {
        LOG_ERROR << "TStarJetPicoMaker: No MuDstMaker or PicoDstMaker Found in chain" << endm;
        return kStFatal;
      }
      break;
      
    case InputMuDst :
      if (!mMuDstMaker) { LOG_ERROR << "TStarJetPicoMaker: MuDst specified as input, but no MuDstMaker in chain" << endm; return kStStop;  }
      LOG_INFO << "TStarJetPicoMaker: input set to MuDst" << endm;
      break;
      
    case InputPicoDst :
      if (!mPicoDstMaker) { LOG_ERROR << "TStarJetPicoMaker: PicoDst specified as input, but no PicoDstMaker in chain" << endm; return kStStop; }
      LOG_INFO << "TStarJetPicoMaker: input set to PicoDst" << endm;
      break;
      
  }
  return kStOk;
}

/* initializing makers & finding other makers
   that should be in the chain - not including
   the muDST or picoDST maker 
 */
void TStarJetPicoMaker::InitMakers() {
  
  mEMCPosition  = new StEmcPosition();
  mBEMCGeom     = StEmcGeom::instance("bemc");
  mEMCFilter    = new StEmcFilter();
  mBemcTables   = new StBemcTables();
  
  /* building refmult correction based on what user
     selected for refMultCorrectionMode
   */
  switch (mRefMultCorrMode) {
      
    case FillNone :
      break;
    case FillGRefAndRefMultCorr :
      mRefMultCorr = CentralityMaker::instance()->getRefMultCorr();
      mGRefMultCorr = CentralityMaker::instance()->getgRefMultCorr();
      break;
    case FillGRefMultCorr :
      mGRefMultCorr = CentralityMaker::instance()->getgRefMultCorr();
      break;
    case FillGRefMultCorrP16ID :
      mGRefMultCorr = CentralityMaker::instance()->getgRefMultCorr_P16id();
      mRefMultCorr->setVzForWeight(6, -6.0, 6.0);
      mRefMultCorr->readScaleForWeight("StRoot/StRefMultCorr/macros/weight_grefmult_vpd30_vpd5_Run14_P16id.txt");
      break;
    case FillGRefMultCorrVPDMB30 :
      mGRefMultCorr = CentralityMaker::instance()->getgRefMultCorr_VpdMB30();
      break;
    case FillGRefMultCorrVPDNoVtx :
      mGRefMultCorr = CentralityMaker::instance()->getgRefMultCorr_VpdMBnoVtx();
      break;
    case FillRefMultCorr :
      mRefMultCorr = CentralityMaker::instance()->getRefMultCorr();
      break;
    default :
      LOG_INFO << "TStarJetPicoMaker: Unknown option for Refmult corrections - none will be applied" << endm;
      break;
  }
  
  mTriggerSimu = (StTriggerSimuMaker*) GetMakerInheritsFrom("StTriggerSimuMaker");
  if (mTriggerSimu == nullptr) LOG_INFO << "TStarJetPicoMaker: Trigger Simu Maker not present in chain - trigger objects will not be complete" << endm;
  
  return;
}

void TStarJetPicoMaker::InitOutput() {
  mOutFile = new TFile(mOutFileName.c_str(), "RECREATE");
  LOG_DEBUG << "TStarJetPicomaker : output file created: " << mOutFileName << endm;
  
  mTree=new TTree("JetTree"," Pico Tree for Jet");
  mTree->Branch("PicoJetTree","TStarJetPicoEvent",&mEvent);
  mTree->SetAutoSave(100000);
  
  if(mMakeMC){
    mMCTree=new TTree("JetTreeMc"," Pico Tree for MC Jet");
    mMCTree->Branch("PicoJetTree","TStarJetPicoEvent",&mMCEvent);
    mMCTree->SetAutoSave(100000);
  }
}


Int_t TStarJetPicoMaker::MakeMuDst() {
  /* load input StMuDst & StMuDstEvent, check for
     MC data if requested by user
   */
  if (LoadMuDst() != kStOk) return kStOk;

  /* got the event - count it */
  mNEvents++;
  //LOG_INFO << "MAKER EVENT NUMBER " << mNEvents << endm;
  //LOG_INFO << "MUDST EVENT ID = " << (unsigned) mMuDst->event()->eventId() << " AND RUN ID = " << (unsigned) mMuDst->event()->runId() << endm;
  
    /*LOG_DEBUG*/
  /* selects the primary vertex either by rank,
     or by Vpd - VPD with rank as a backup
     when no VPD match can be found is used as default
   */
  LOG_DEBUG << "selecting vertex"<<endm;
  switch (SelectVertex()) {
    case kStErr :
      return kStOk;
      break;
    case kStFatal :
      return kStFatal;
      break;
    default :
      break;
  }
  
  
  //the commented-out code below just prints out the triggers before the HT2 is added by hand by checking tower ADCs.
  /*
  if (mMuInputEvent) {
  std::vector<unsigned> triggerIds = mMuInputEvent->triggerIdCollection().nominal().triggerIds();
  for(unsigned i = 0; i < triggerIds.size(); i++) {
    //mEvent->GetHeader()->AddTriggerId(triggerIds[i]);
    LOG_INFO << "TRIGGER: " << triggerIds[i] << endm;
  }
  }
*/
  /* checks the event against all active
     event level selectors, possibly including
     vertex position & trigger
     if it doesnt pass, we stop procesing this event
   */
  if (!mEventSelector->AcceptEvent(mMuInputEvent)) return kStOk;
  
  //LOG_INFO << "wisdom: EVENT " << mNEvents << " IS OKAY" << endm;
    /*LOG_DEBUG*/
  /* create new event structures */
  mEvent = new TStarJetPicoEvent();
  
  /* process primary tracks for the selected vertex */
  MuProcessPrimaryTracks();
  
  /* process barrel EMC - does tower/track matching
     as well */
  if (!MuProcessBEMC()) return kStOk;
  
  /* process triggers */
  MuProcessTriggerObjects();
  
  /* fill header information - performs refmult corrections
     if requested by the user
   */
  if (!MuFillHeader()) return kStOk;
  
  /* fill v0 information if requested by user */
  if (mMakeV0) MuProcessV0s();
  
  /* event is complete - fill the trees */
  mTree->Fill();
  
  delete mEvent; mEvent = nullptr;
 
  if (mMakeMC) mMCEvent = new TStarJetPicoEvent();
 
  /*process MC event*/
  if (mMakeMC) MuProcessMCEvent(); 
 
  /* event is complete - fill the trees */
  if (mMakeMC) mMCTree->Fill();
 
  delete mMCEvent; mMCEvent = nullptr;
 
  /* count the successful write & exit */
  mNAcceptedEvents++;

  return kStOk;
}

Int_t TStarJetPicoMaker::MakePicoDst() {
  
  if (LoadPicoDst() != kStOk) return kStOk;
  
  /* a picodst only has a single vertex - we'll
     use what we're given. Next step is to see 
     if the event passes event cuts.
     if not, we stop procesing this event
   */
  if (!mEventSelector->AcceptEvent(mPicoInputEvent)) return kStOk;
  
  /* create new event structures */
  mEvent = new TStarJetPicoEvent();
  
  /* fill header information - performs refmult corrections
   if requested by the user
   */
  if (!PicoFillHeader()) return kStOk;
  return kStOk;
}

Int_t TStarJetPicoMaker::LoadMuDst() {
  
  mMuDst = mMuDstMaker->muDst();
  if (!mMuDst) {
    LOG_ERROR << "TStarJetPicoMaker: No MuDst loaded for this event" << endm;
    return kStErr;
  }
  mMuInputEvent = mMuDst->event();
  if (!mMuInputEvent) {
    LOG_ERROR << "TStarJetPicoMaker: No MuDstEvent loaded for this event" << endm;
    return kStErr;
  }
  /* check for MC data if requested by user */
  if (mMakeMC) {
    //mStMiniMcEvent = (StMiniMcEvent*) GetDataSet("StMiniMcEvent"); //getdataset is for geant not minimcs
    if (!mStMiniMcEvent) {
      LOG_ERROR << "TStarJetPicoMaker: No StMiniMcEvent loaded for this event" << endm;
      return kStErr;
    }
  }
  return kStOk;
}

Int_t TStarJetPicoMaker::LoadPicoDst() {
  
  mPicoDst = mPicoDstMaker->picoDst();
  if (!mPicoDst) {
    LOG_ERROR << "TStarJetPicoMaker: No PicoDst loaded for this event" << endm;
    return kStErr;
  }
  mPicoInputEvent = mPicoDst->event();
  if (!mPicoInputEvent) {
    LOG_ERROR << "TStarJetPicoMaker: No PicoDstEvent loaded for this event" << endm;
    return kStErr;
  }
  return kStOk;
}

Int_t TStarJetPicoMaker::SelectVertex() {
  
  // get # of saved vertices
  Int_t nVertices = mMuDst->numberOfPrimaryVertices();
  if (nVertices == 0) {
    LOG_DEBUG <<"TStarJetPicoMaker: Event has no vertices" << endm;
    return kStErr;
  }

  /* check for MC vertex if processing MC data */
    if (mMakeMC && mStMiniMcEvent->nUncorrectedPrimaries() == 0) {//since primaries mean there is a vertex //!mStMiniMcEvent->primaryVertex()) {
    LOG_DEBUG << "TStarJetPicoMaker: No StMcVertex for this event" << endm;
    return kStErr;
  }
  
  switch (mVertexMode) {
    case TStarJetPicoMaker::VpdOrRank :
      MatchToVpd();
      break;
    case TStarJetPicoMaker::Vpd :
      if (!MatchToVpd()) {
        LOG_DEBUG << "TStarJetPicoMaker: reject event - no vertex match to VPD" << endm;
        return kStErr;
      }
      break;
    case TStarJetPicoMaker::Rank :
      mMuDst->setVertexIndex(0);
      break;
    default :
      LOG_ERROR << "TStarJetPicoMaker: Unrecognized vertex selector option - exiting" << endm;
      return kStFatal;
  }
  return kStOk;
}

Bool_t TStarJetPicoMaker::MatchToVpd() {
  
  Int_t nVertices = mMuDst->numberOfPrimaryVertices();
  Int_t usedVertex = -1;
  StBTofHeader* tofheader = mMuDst->btofHeader();
  if (tofheader) {
    double vpdVz = tofheader->vpdVz(0);
    if (vpdVz == -999) { mMuDst->setVertexIndex(0); return kFALSE; }
    for (Int_t i = 0; i < nVertices; ++i) {
      mMuDst->setVertexIndex(i);
      StThreeVectorF Vposition = mMuDst->event()->primaryVertexPosition();
      Double_t vz = Vposition.z();
      if (fabs(vz-vpdVz) < mdVzMax) {
        usedVertex = i;
        break;
      }
    }
  }
  if (usedVertex != -1) {
    mMuDst->setVertexIndex(usedVertex);
    return kTRUE;
  }
  else {
    mMuDst->setVertexIndex(0);
    return kFALSE;
  }
}

Bool_t TStarJetPicoMaker::MuProcessPrimaryTracks() {
  /* we've already selected the primary vertex - 
     now, we loop over all primary tracks & place 
     them into the event structure. If the track
     is accepted, we look to see if it extends into
     the BEMC for tower matching.
   */
  UInt_t nTracks = mMuDst->primaryTracks()->GetEntries();
  StMuTrack* muTrack;
  TStarJetPicoPrimaryTrack jetTrack;
  UInt_t matchedTracks = 0;
  mBemcMatchedTracks.resize(nTracks);

  for (UInt_t i = 0; i < nTracks; ++i) {
    muTrack = (StMuTrack*) mMuDst->primaryTracks(i);
    
    //TEMP FOR DEBUG (although it shouldn't hurt if you forget to remove this after
    if (muTrack->charge() == -9999 || muTrack->eta() > 10 || muTrack->eta() < -10) {
      continue;
    }

    /* check if track will be saved to event structure */
    if(muTrack->flag() < mTrackFlagMin || muTrack->nHitsFit() <= mTrackFitPointMin ||
        muTrack->dcaGlobal().mag() > mTrackDCAMax || muTrack->eta() > mTrackEtaMax ||
        muTrack->eta() < mTrackEtaMin) continue;
    jetTrack.Clear();
    
    /* fill track information */
    jetTrack.SetPx(muTrack->momentum().x());
    jetTrack.SetPy(muTrack->momentum().y());
    if (/*muTrack->momentum().z() != muTrack->momentum().z()*/ isnan(muTrack->momentum().z())) {
      //LOG_INFO << "UNDEFINED MU PZ (primary track " << (unsigned) i << ") in event " << (unsigned) mMuDst->event()->eventId() << " of run " << (unsigned) mMuDst->event()->runId() << endm;
    }
    jetTrack.SetPz(muTrack->momentum().z());
    if (isnan(jetTrack.GetPz())) {
      //LOG_INFO << "UNDEFINED PICO PZ (primary track " << (unsigned) i << ") in event " << (unsigned) mMuDst->event()->eventId() << " of run " << (unsigned) mMuDst->event()->runId() << endm;
    }
    if (/*mMuDst->event()*/mMuInputEvent->eventId() == 2820 && /*mMuDst->event()*/mMuInputEvent->runId() == 16143009) {
      //LOG_INFO << "WRONG SIDE OF THE TRACKS! primary track " << (unsigned) i << " has mupz " << (unsigned) muTrack->momentum().z() << " and picopz " << (unsigned) jetTrack.GetPz() << endm;
    }
    
    jetTrack.SetDCA(muTrack->dcaGlobal().mag());
    jetTrack.SetdEdx(muTrack->dEdx());
    jetTrack.SetNsigmaPion(muTrack->nSigmaPion());
    jetTrack.SetNsigmaKaon(muTrack->nSigmaKaon());
    jetTrack.SetNsigmaProton(muTrack->nSigmaProton());
    jetTrack.SetNsigmaElectron(muTrack->nSigmaElectron());
    jetTrack.SetCharge(muTrack->charge());
    jetTrack.SetNOfFittedHits(muTrack->nHitsFit());
    jetTrack.SetNOfPossHits(muTrack->nHitsPoss(kTpcId) + 1); // add one for primary vertex
    jetTrack.SetKey(muTrack->id());
    jetTrack.SetChi2(muTrack->chi2xy());
    jetTrack.SetChi2PV(muTrack->chi2z());
    jetTrack.SetFlag(muTrack->flag());
    jetTrack.SetTofTime(muTrack->btofPidTraits().timeOfFlight());
    jetTrack.SetTofBeta(muTrack->btofPidTraits().beta());
    jetTrack.SetTofyLocal(muTrack->btofPidTraits().yLocal());
    jetTrack.SetEtaDiffHitProjected(0);
    jetTrack.SetPhiDiffHitProjected(0);
    
    const StMuTrack* globalTrack = (const StMuTrack*) muTrack->globalTrack();
    StThreeVectorF prVtx = mMuDst->event()->primaryVertexPosition();
    if (globalTrack)
    jetTrack.SetsDCAxy(ComputeXY(prVtx, globalTrack->helix()));
    else {
      jetTrack.SetsDCAxy(-99);
      LOG_ERROR << "TStarJetPicoMaker : primary track without associated global?" << endm;
    }
    
    /* write track to event structure */
    mEvent->AddPrimaryTrack(&jetTrack);
    /* project track to BEMC - used for
       tower/track matching
     */
    Double_t magField = 0.1*mMuInputEvent->runInfo().magneticField(); // in Tesla
    StThreeVectorD momentum, position;
    Int_t module, etaBin, phiBin;
    Bool_t projectToEMC= mEMCPosition->projTrack(&position, &momentum, muTrack, magField);
    if (!projectToEMC) continue;
    Int_t matchToTower = mBEMCGeom->getBin(position.phi(), position.pseudoRapidity(), module ,etaBin, phiBin);
    if (matchToTower == 1 || phiBin < 0) continue;

    /* save track & track BEMC position info */
    mBemcMatchedTracks[matchedTracks] = BemcMatch(i,  mEvent->GetHeader()->GetNOfPrimaryTracks()-1, muTrack->eta(), muTrack->phi(), position.pseudoRapidity(), position.phi());
    matchedTracks++;
  }

  /* shrink-to-fit: remove any unused space */
  mBemcMatchedTracks.resize(matchedTracks);
  
  return kTRUE;
}

Bool_t TStarJetPicoMaker::PicoProcessPrimaryTracks() {
  return kTRUE;
}

Float_t TStarJetPicoMaker::ComputeXY(const StThreeVectorF& pos, const StPhysicalHelixD &helix) {
  // find the distance between the center of the circle and pos.
  // if this greater than the radius of curvature, then call
  // it negative.
  Double_t xCenter = helix.xcenter();
  Double_t yCenter = helix.ycenter();
  Double_t radius  = 1.0/helix.curvature();
  Double_t dPosCenter
  = TMath::Sqrt((pos.x()-xCenter) * (pos.x()-xCenter) +
                 (pos.y()-yCenter) * (pos.y()-yCenter));
  return (Float_t) radius - dPosCenter;
}

Bool_t TStarJetPicoMaker::MuProcessBEMC() {
  /* this is reworked, but a simple reimplementation
     of the old Maker code. It should be updated for
     future use - currently a track is matched to the
     first tower within dR of its BEMC projection
     where it should be matched to the tower
     with the minimum dR. This might require
     a rework of MuProcessPrimaryTracks as well.
   */
  /* define the number of modules in the BEMC */
  UInt_t   mBEMCModules         = 120;
  UInt_t   mBEMCTowPerModule    = 20;
  Int_t    mBEMCSubSections     = 2;
  
  /* and we will count the # of towers/tracks matched, as this
     is saved in the event header. Not sure why 
   */
  Int_t nMatchedTowers = 0;
  Int_t nMatchedTracks = 0;
  
  StEmcCollection* mEmcCollection = (StEmcCollection*) mMuDst->emcCollection();
  StMuEmcCollection* mMuEmcCollection = (StMuEmcCollection*) mMuDst->muEmcCollection();
  mBemcTables->loadTables((StMaker*)this);
  
  /* if no collections are found, exit assuming error */
  if (!mEmcCollection || !mMuEmcCollection) return kFALSE;

  StEmcDetector* mBEMC = mEmcCollection->detector(kBarrelEmcTowerId);
  StSPtrVecEmcPoint& mEmcContainer =  mEmcCollection->barrelPoints();
  
  /* if we can't get the detector exit assuming error */
  if (!mBEMC) return kFALSE;

  /* if there are no hits, continue assuming everything
     is working */
  if(mEmcContainer.size() == 0) return kTRUE;

  TStarJetPicoTower jetTower;
  
  /* loop over all modules */
  for (UInt_t i = 1; i <= mBEMCModules; ++i) {
  
    StSPtrVecEmcRawHit& mEmcTowerHits = mBEMC->module(i)->hits();
    
    /* loop over all hits in the module */
    for (UInt_t j = 0; j < mEmcTowerHits.size(); ++j) {
      
      StEmcRawHit* tow = mEmcTowerHits[j];
      
      if (abs(tow->module()) > mBEMCModules  || abs(tow->eta()) > mBEMCTowPerModule || tow->sub() >  mBEMCSubSections) continue;
      
      Int_t towerID, towerStatus;
      mBEMCGeom->getId((int)tow->module(), (int)tow->eta(), (int)tow->sub(), towerID);
      mBemcTables->getStatus(BTOW, towerID, towerStatus);
      
      if (mTowerStatusMode == RejectBadTowerStatus && towerStatus != 1) continue;
      
      Float_t towerEnergy = tow->energy();
      Float_t towerADC = tow->adc();

      if (towerEnergy < mTowerEnergyMin) continue;
      
      Float_t towerEta, towerPhi;
      mBEMCGeom->getEtaPhi(towerID, towerEta, towerPhi);
      
      /* check for SMD hits in the tower */
      Int_t ehits = MuFindSMDClusterHits(mEmcCollection, towerEta, towerPhi, 2);
      Int_t phits = MuFindSMDClusterHits(mEmcCollection, towerEta, towerPhi, 3);
      
      /* correct eta for Vz position */
      Float_t theta;
      theta = 2 * atan(exp(-towerEta)); /* getting theta from eta */
      Double_t z = 0;
      if(towerEta != 0) z = 231.0 / tan(theta);  /* 231 cm = radius of SMD */
      Double_t zNominal = z - mMuDst->event()->primaryVertexPosition().z(); /* shifted z */
      Double_t thetaCorr = atan2(231.0, zNominal); /* theta with respect to primary vertex */
      Float_t etaCorr =-log(tan(thetaCorr / 2.0)); /* eta with respect to primary vertex */
      
      /* fill tower information */
      jetTower.Clear();
      jetTower.SetPhi(towerPhi);
      jetTower.SetEta(towerEta);
      jetTower.SetId(towerID);
      jetTower.SetEnergy(towerEnergy);
      jetTower.SetADC(towerADC);
      jetTower.SetPhiCorrected(towerPhi); /* not calculated as (x,y) shift of vertex is miniscule */
      jetTower.SetEtaCorrected(etaCorr);
      jetTower.SetSMDClusterP(phits);
      jetTower.SetSMDClusterE(ehits);
      jetTower.SetTowerStatus(towerStatus);

      /* now match tracks to towers */
      for (unsigned k = 0; k < mBemcMatchedTracks.size(); ++k) {
        BemcMatch match = mBemcMatchedTracks[k];
        if (match.globalId == -1) continue;
        
        Double_t halfTowerWidth = 0.025;
        Double_t dEta = match.matchEta - towerEta;
        Double_t dPhi = match.matchPhi - towerPhi;
        while (dPhi > TMath::Pi())  dPhi -= TMath::Pi();
        while (dPhi < -TMath::Pi()) dPhi += TMath::Pi();
        if (fabs(dEta) > halfTowerWidth || fabs(dPhi) > halfTowerWidth) continue;
        nMatchedTracks++;
        mBemcMatchedTracks[k].globalId = -1;
        jetTower.AddMatchedTrack(match.trackId);
        
        /* set dEta & dPhi for the matched track */
        TStarJetPicoPrimaryTrack* matchedTrack = (TStarJetPicoPrimaryTrack*) mEvent->GetPrimaryTracks()->At(match.trackId);
        matchedTrack->SetEtaDiffHitProjected(dEta);
        matchedTrack->SetPhiDiffHitProjected(dPhi);
      }
      
      if (jetTower.GetNAssocTracks() > 0) nMatchedTowers++;
      mEvent->AddTower(&jetTower);
    }
    
  }
  mEvent->GetHeader()->SetNOfMatchedTracks(nMatchedTracks);
  mEvent->GetHeader()->SetNOfMatchedTowers(nMatchedTowers);
  
  return kTRUE;
}

Bool_t TStarJetPicoMaker::PicoProcessBEMC() {
  
  return kTRUE;
}

Int_t TStarJetPicoMaker::MuFindSMDClusterHits(StEmcCollection* coll, Double_t eta, Double_t phi, Int_t detectorID) {
  StEmcCluster* smdCluster = nullptr;
  Float_t dRmin = 9999;
  Float_t dRmin_cut = 0.05;
  StDetectorId id = static_cast<StDetectorId>(detectorID + kBarrelEmcTowerId);
  
  StEmcDetector* detector = coll->detector(id);
  if (!detector) return 0;
  StEmcClusterCollection* clusters = detector->cluster();
  if (!clusters) return 0;
  StSPtrVecEmcCluster& cl=clusters->clusters();
  
  for (unsigned i = 0; i < cl.size(); ++i) {
    Float_t clEta = cl[i]->eta();
    Float_t clPhi = cl[i]->phi();
    Float_t dR = sqrt((eta - clEta) * (eta - clEta) + (phi - clPhi) * (phi - clPhi));
    
    if (dR < dRmin && dR < dRmin_cut) {
      dRmin = dR;
      smdCluster = cl[i];
    }
    
  }
  
  if (smdCluster) return smdCluster->nHits();
  else return 0;
}

void TStarJetPicoMaker::MuProcessTriggerObjects() {
  
  /* fill trigger thresholds in event header */
  for (int i = 0; i < 4; ++i) mEvent->GetHeader()->SetHighTowerThreshold(i, mTriggerSimu->bemc->barrelHighTowerTh(i));
  for (int i = 0; i < 3; ++i) mEvent->GetHeader()->SetJetPatchThreshold(i, mTriggerSimu->bemc->barrelJetPatchTh(i));
  
  /* get trigger thresholds for HT */
  Int_t bht0 = mTriggerSimu->bemc->barrelHighTowerTh(0);
  Int_t bht1 = mTriggerSimu->bemc->barrelHighTowerTh(1);
  Int_t bht2 = mTriggerSimu->bemc->barrelHighTowerTh(2);
  Int_t bht3 = mTriggerSimu->bemc->barrelHighTowerTh(3);
  //LOG_INFO << "wisdom: High Tower trigger thresholds: bht0 " << bht0 << " bht1: " << bht1 << " bht2: " << bht2 << " bht3: " << bht3 << endm;
  /*LOG_DEBUG*/

  TStarJetPicoTriggerInfo trigobj;
  bool count_tows = 0;
  //DEBUG:
  vector<unsigned> adc20(20,0);
  for (unsigned towerId = 1; towerId <= 4800; ++towerId) {
    int status;
    mTriggerSimu->bemc->getTables()->getStatus(BTOW, towerId, status);
    const Int_t adc = mTriggerSimu->bemc->barrelHighTowerAdc(towerId);
    if (adc > 18) {adc20[19] ++;}
    else if (adc >= 0 && adc <= 18){ adc20[adc] ++;}
    //LOG_INFO << "wisdom: ADC: " << (unsigned) adc << endm;
    //HERE WE MANUALLY ADD THE HT2 TRIGGER IF AT LEAST ONE TOWER IS ABOVE THE BHT2 THRESHOLD. NOT IDEAL BUT OH WELL
    if (bht2 > 0 && adc > bht2 && count_tows == 0) {
      //LOG_INFO << "wisdom: ADDING TRIGGERS FOR EVENT " << (unsigned) /*mEvent->GetHeader()->GetEventId()*/mMuInputEvent->eventId() << " of run " << (unsigned) /*mEvent->GetHeader()->GetRunId()*/mMuInputEvent->runId() << " thanks to a tower with ADC " << (unsigned) adc << endm;
      mEvent->GetHeader()->AddTriggerId(500205);
      mEvent->GetHeader()->AddTriggerId(500215);
      count_tows ++;
    }//passed the threshold; added the trigger by hand
    Int_t trigMap = 0;
    Float_t eta, phi;
    mBEMCGeom->getEtaPhi(towerId, eta, phi);
    
    if (bht1 > 0 && adc > bht1) trigMap |= 1 << 1;
    if (bht2 > 0 && adc > bht2) trigMap |= 1 << 2; 
    if (bht3 > 0 && adc > bht3) trigMap |= 1 << 3;
    
    if (trigMap & 0xf) {
      //LOG_INFO << "wisdom: high tower trigger found. ADC: " << adc << endm;
      /*LOG_DEBUG*/
      trigobj.Clear();
      trigobj.SetEta(eta);
      trigobj.SetPhi(phi);
      trigobj.SetId(towerId);
      trigobj.SetADC(adc);
      trigobj.SetBitMap(trigMap);
      
      mEvent->AddTrigObj(&trigobj);
    }
  }
  
  //LOG_INFO << "wisdom: AFTER TOWER LOOP: " << endm;
  //LOG_INFO << "n tows / adc [0 - 19+]" << endm;
  //for(int i = 0; i < adc20.size(); ++i) {
    //LOG_INFO << (unsigned) adc20[i] << " ";
  //}
  //LOG_INFO << endm;

  //JP locations:
  //Jet Patch# Eta Phi Quadrant
  //0 0.5 150 10'
  //1 0.5 90 12'
  //2 0.5 30 2'
  //3 0.5 -30 4'
  //4 0.5 -90 6'
  //5 0.5 -150 8'
  //6 -0.5 150 10'
  //7 -0.5 90 12'
  //8 -0.5 30 2'
  //9 -0.5 -30 4'
  //10 -0.5 -90 6'
  //11 -0.5 -150 8'
  //12 -0.1 150 10'
  //13 -0.1 90 12'
  //14 -0.1 30 2'
  //15 -0.1 -30 4'
  //16 -0.1 -90 6'
  //17 -0.1 -150 8'

  /* get trigger thresholds for JP */
  Int_t jp0  = mTriggerSimu->bemc->barrelJetPatchTh(0);
  Int_t jp1  = mTriggerSimu->bemc->barrelJetPatchTh(1);
  //
  Int_t jp2e = mTriggerSimu->bemc->barrelJetPatchTh(2);
  Int_t jp2m = mTriggerSimu->bemc->barrelJetPatchTh(3);
  Int_t jp2w = mTriggerSimu->bemc->barrelJetPatchTh(4);
  //Int_t jp2  = mTriggerSimu->bemc->barrelJetPatchTh(2);
  //Int_t jp2 = 9999; //TEMP!
  LOG_INFO << "Jet Patch trigger thresholds: jp0 " << jp0 << " jp1: " << jp1 << " jp2e,m,w: " << jp2e << " " << jp2m << " " << jp2w << endm;
  
  /* lookup 12 jet patches & 6 overlap thresholds - no EEMC data saved */
  if (mMakeMC) {
      bool count_patches = 0;
      for (unsigned jp = 0; jp < 18; ++jp) {
          const Int_t jpAdc = mTriggerSimu->bemc->barrelJetPatchAdc(jp);
          //hard-coding this for now, will improve later -- ONLY WORKS FOR pA2015 RIGHT NOW!!
          if (jp >= 0 && jp <=5) {
              if (jp2w > 0 && jpAdc > jp2w && count_patches == 0) {
                  //add triggers
                  mEvent->GetHeader()->AddTriggerId(500401);
                  mEvent->GetHeader()->AddTriggerId(500411);
                  count_patches ++;
              }
          }
          if (jp >=6 && jp <=11) {
              if (jp2e > 0 && jpAdc > jp2e && count_patches == 0) {
                  //add triggers
                  mEvent->GetHeader()->AddTriggerId(500401);
                  mEvent->GetHeader()->AddTriggerId(500411);
                  count_patches ++;
              }
          }
          if (jp >=12 && jp <= 17) {
              if (jp2m > 0 && jpAdc > jp2m && count_patches == 0) {
                  //add triggers
                  mEvent->GetHeader()->AddTriggerId(500401);
                  mEvent->GetHeader()->AddTriggerId(500411);
                  count_patches ++;
              }
          }

    Int_t trigMap = 0;
    
    if (jp0 > 0 && jpAdc > jp0) trigMap |= 1 << 4;
    if (jp1 > 0 && jpAdc > jp1) trigMap |= 1 << 5;
    if (jp >=0 && jp <= 5 && jp2w > 0 && jpAdc > jp2w) {trigMap |= 1 << 6;}
    else if (jp >=6 && jp <= 11 && jp2e > 0 && jpAdc > jp2e) {trigMap |= 1 << 6;}
    else if (jp >= 12 && jp <=17 && jp2m > 0 && jpAdc > jp2m) {trigMap |= 1 << 6;}
    
    if (trigMap & 0x70) {
      LOG_DEBUG << "jet patch trigger found. ADC: " << jpAdc << endm;
      trigobj.Clear();
      trigobj.SetId(jp);
      trigobj.SetADC(jpAdc);
      trigobj.SetBitMap(trigMap);
      
      mEvent->AddTrigObj(&trigobj);
    }
  }
  }
}

void TStarJetPicoMaker::PicoProcessTriggerObjects() {
 
}

Bool_t TStarJetPicoMaker::MuFillHeader() {
  
  /* fill triggers */
  std::vector<unsigned> triggerIds = mMuInputEvent->triggerIdCollection().nominal().triggerIds();
  for(unsigned i = 0; i < triggerIds.size(); i++) {
    mEvent->GetHeader()->AddTriggerId(triggerIds[i]);
  }
    
  /* calculate reaction plane with default primary cuts */
  mEvent->GetHeader()->SetReactionPlaneAngle(MuGetReactionPlane());
  
  /*  fill gRefMult, refMult, and if requested, fill
      gRefMultCorr/refMultCorr, along with weights
   */
  
  /* we will keep rank zero refmult for debugging purposes */
  mEvent->GetHeader()->SetRefMultRank0(mMuInputEvent->refMult(0));
  
  mEvent->GetHeader()->SetReferenceMultiplicity(mMuInputEvent->refMult());
  mEvent->GetHeader()->SetGReferenceMultiplicity(mMuInputEvent->grefmult());
  
  if (mRefMultCorr) {
    mRefMultCorr->init(mMuInputEvent->runId());
    mRefMultCorr->initEvent(mMuInputEvent->refMult(), mMuInputEvent->primaryVertexPosition().z(), mMuInputEvent->runInfo().zdcCoincidenceRate());
    mEvent->GetHeader()->SetReferenceCentrality(mRefMultCorr->getCentralityBin9());
    mEvent->GetHeader()->SetReferenceCentralityWeight(mRefMultCorr->getWeight());
    mEvent->GetHeader()->SetCorrectedReferenceMultiplicity(mRefMultCorr->getRefMultCorr());
  }
  if (mGRefMultCorr) {

    /* first, fill the highest ranked vertex information
     this was only used when testing vertex selection
     with VPD
     */
    mGRefMultCorr->init(mMuInputEvent->runId());
    mGRefMultCorr->initEvent(mMuInputEvent->grefmult(0), mMuInputEvent->primaryVertexPosition().z(), mMuInputEvent->runInfo().zdcCoincidenceRate());
    mEvent->GetHeader()->SetGRefMultCorrRank0(mGRefMultCorr->getRefMultCorr());
    
    mGRefMultCorr->init(mMuInputEvent->runId());
    mGRefMultCorr->initEvent(mMuInputEvent->grefmult(), mMuInputEvent->primaryVertexPosition().z(), mMuInputEvent->runInfo().zdcCoincidenceRate());
    mEvent->GetHeader()->SetGReferenceCentrality(mGRefMultCorr->getCentralityBin9());
    mEvent->GetHeader()->SetGReferenceCentralityWeight(mGRefMultCorr->getWeight());
    mEvent->GetHeader()->SetCorrectedGReferenceMultiplicity(mGRefMultCorr->getRefMultCorr());
  }
  
  /* fill vertex position */
  mEvent->GetHeader()->SetPrimaryVertexX(mMuInputEvent->primaryVertexPosition().x());
  mEvent->GetHeader()->SetPrimaryVertexY(mMuInputEvent->primaryVertexPosition().y());
  mEvent->GetHeader()->SetPrimaryVertexZ(mMuInputEvent->primaryVertexPosition().z());
  mEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(mMuDst->primaryVertex()->meanDip());
  mEvent->GetHeader()->SetPrimaryVertexRanking(mMuDst->primaryVertex()->ranking());
  mEvent->GetHeader()->SetPrimaryVertexID(mMuDst->currentVertexIndex());
  if (mMuDst->btofHeader()) mEvent->GetHeader()->SetvpdVz(mMuDst->btofHeader()->vpdVz());
  else                      mEvent->GetHeader()->SetvpdVz(9999);
  
  /* fill all other event level information */
  mEvent->GetHeader()->SetBTofMult(mMuDst->numberOfBTofHit());

  mEvent->GetHeader()->SetEventId(mMuInputEvent->eventId());
  mEvent->GetHeader()->SetRunId(mMuInputEvent->runId());
  mEvent->GetHeader()->SetNGlobalTracks(mMuDst->numberOfGlobalTracks());
  mEvent->GetHeader()->SetNOfEMCPoints(mMuDst->emcCollection()->barrelPoints().size());
  mEvent->GetHeader()->SetCTBMultiplicity(mMuInputEvent->ctbMultiplicity());
  mEvent->GetHeader()->SetNumberOfVertices(mMuDst->primaryVertices()->GetEntries());
  mEvent->GetHeader()->SetDSMInput(mMuInputEvent->l0Trigger().dsmInput());
  mEvent->GetHeader()->SetTrigMask(mMuInputEvent->eventInfo().triggerMask());
  mEvent->GetHeader()->SetZdcWestRate(mMuInputEvent->runInfo().zdcWestRate());
  mEvent->GetHeader()->SetZdcEastRate(mMuInputEvent->runInfo().zdcEastRate());
  mEvent->GetHeader()->SetZdcCoincidenceRate(mMuInputEvent->runInfo().zdcCoincidenceRate());
  mEvent->GetHeader()->SetBbcWestRate(mMuInputEvent->runInfo().bbcWestRate());
  mEvent->GetHeader()->SetBbcEastRate(mMuInputEvent->runInfo().bbcEastRate());
  mEvent->GetHeader()->SetBbcCoincidenceRate(mMuInputEvent->runInfo().bbcCoincidenceRate());
  mEvent->GetHeader()->SetBbcBlueBackgroundRate(mMuInputEvent->runInfo().bbcBlueBackgroundRate());
  mEvent->GetHeader()->SetBbcYellowBackgroundRate(mMuInputEvent->runInfo().bbcYellowBackgroundRate());
  mEvent->GetHeader()->SetBbcAdcSumEastInner(mMuInputEvent->bbcTriggerDetector().adcSumEast());
  mEvent->GetHeader()->SetBbcAdcSumWestInner(mMuInputEvent->bbcTriggerDetector().adcSumWest());
  mEvent->GetHeader()->SetBbcAdcSumEastOuter(mMuInputEvent->bbcTriggerDetector().adcSumEastLarge());
  mEvent->GetHeader()->SetBbcAdcSumWestOuter(mMuInputEvent->bbcTriggerDetector().adcSumWestLarge());
  mEvent->GetHeader()->SetBbcOfflineVertex(mMuInputEvent->bbcTriggerDetector().zVertex());
  mEvent->GetHeader()->SetBbcOnlineVertex(mMuInputEvent->bbcTriggerDetector().onlineTimeDifference());
  mEvent->GetHeader()->SetRefMultFTPCE(mMuInputEvent->refMultFtpcEast());
  StZdcTriggerDetector &ZDC = mMuInputEvent->zdcTriggerDetector();
  for(Int_t strip=1; strip<9; strip++) {
    mEvent->SetZdcsmd(east, 0, strip, ZDC.zdcSmd(east, 0, strip));
    mEvent->SetZdcsmd(east, 1, strip, ZDC.zdcSmd(east, 1, strip));
    mEvent->SetZdcsmd(west, 0, strip, ZDC.zdcSmd(west, 0, strip));
    mEvent->SetZdcsmd(west, 1, strip, ZDC.zdcSmd(west, 1, strip));
  }

  return kTRUE;
}

Bool_t TStarJetPicoMaker::PicoFillHeader() {
  return kTRUE;
}

Double_t TStarJetPicoMaker::MuGetReactionPlane() {
  
  Double_t mQx=0., mQy=0.;
  Double_t order = 2;
  
  for (int i = 0; i < mMuDst->primaryTracks()->GetEntries(); ++i) {
    const StMuTrack* track = (const StMuTrack*) mMuDst->primaryTracks(i);
    mQx += cos(track->phi() * order);
    mQy += sin(track->phi() * order);
  }
  
  TVector2 mQ(mQx, mQy);
  Double_t psi= mQ.Phi() / order;
  return psi * 180.0 / TMath::Pi();
}

Double_t TStarJetPicoMaker::PicoGetReactionPlane() {
  return 0;
}

void TStarJetPicoMaker::MuProcessMCEvent() {

  //int nCount = 0;
  
  //const StPtrVecMcTrack& mcTracks = mStMiniMcEvent->primaryVertex()->daughters();
  //StMcTrackConstIterator mcTrkIter = mcTracks.begin();
  TClonesArray* mcTracks = mStMiniMcEvent->tracks(MC);
  TIter next(mcTracks);
  
  //const int nTracks = mcTracks.size();
  
  //for (; mcTrkIter != mcTracks.end(); ++mcTrkIter) {
  while (StTinyMcTrack* track = (StTinyMcTrack *) next()) {
    //StMcTrack* track = *mcTrkIter;
    //StTinyMcTrack* track = (StTinyMcTrack*) mcTracks[i];
  
    TStarJetPicoPrimaryTrack mTrack;
    if (!track->isPrimary()) {
      continue;//should effectively remove this non-primary from the event by not adding it to mMCEvent at the end of this for loop.
    }
    
    
    mTrack.SetPx(track->pxMc());
    mTrack.SetPy(track->pyMc());
    mTrack.SetPz(track->pzMc());
    mTrack.SetDCA(0);
    
    mTrack.SetNsigmaPion(0);
    mTrack.SetNsigmaKaon(0);
    mTrack.SetNsigmaProton(0);
    mTrack.SetNsigmaElectron(0);
    
    //if it has a valid GEANT-3 code (https://www.star.bnl.gov/public/comp/simu/newsite/gstar/Manual/particle_id.html), convert this code to PDG ID and save the particle info in mTrack
    if(track->geantId() > 0 && track->geantId() < 51) { //track->particleDefinition()){
      //convert GEANT3 ID to PDG ID:
      int pdg_id = (int) pdg->ConvertGeant3ToPdg(track->geantId());
      mTrack.SetCharge(track->chargeMc());
      mTrack.SetdEdx(pdg_id); //note to self: SetdEdx doesn't actually calculate dE/dx for this particle, it just holds the PDG id without modification.
    }
    else {
      LOG_DEBUG << "Particle with no encoding " << endm;
      mTrack.SetCharge(0);
      mTrack.SetdEdx(0);
    }
    
  
    mTrack.SetNOfFittedHits(track->nHitMc());//tpcHits().size()); //nHitMc should hopefully be # of TPC hits.
    mTrack.SetNOfPossHits(52);
    mTrack.SetKey(track->key());
    mTrack.SetEtaDiffHitProjected(0);
    mTrack.SetPhiDiffHitProjected(0);
    //  nCount++; //this was in the original version of the maker, but its purpose is to hand the SetNOfPrimaryTracks call the number of primaries, while the AddPrimaryTrack function already does that (see TStarJetPicoEvent::AddPrimaryTrack for proof).
    
    mMCEvent->AddPrimaryTrack(&mTrack);
  
  }
  
  
    mMCEvent->GetHeader()->SetEventId(mStMiniMcEvent->eventId());//eventNumber());
    mMCEvent->GetHeader()->SetRunId(mStMiniMcEvent->runId());//runNumber());
    mMCEvent->GetHeader()->SetReferenceMultiplicity(mStMiniMcEvent->centralMult());//eventGeneratorFinalStateTracks());
    //mMCEvent->GetHeader()->SetNPrimaryTracks(nCount);
    mMCEvent->GetHeader()->SetNGlobalTracks(mStMiniMcEvent->nUncorrectedGlobals());//numberOfPrimaryTracks());
    mMCEvent->GetHeader()->SetReactionPlaneAngle(mStMiniMcEvent->impactPhi());//phiReactionPlane());
  
    mMCEvent->GetHeader()->SetPrimaryVertexX(mStMiniMcEvent->mcVertexX()); // this should be mcVertexX rather than VertexX, right? //primaryVertex()->position().x());
    mMCEvent->GetHeader()->SetPrimaryVertexY(mStMiniMcEvent->mcVertexY());//primaryVertex()->position().y());
    mMCEvent->GetHeader()->SetPrimaryVertexZ(mStMiniMcEvent->mcVertexZ());//primaryVertex()->position().z());
  
  mMCEvent->GetHeader()->SetCTBMultiplicity(0);
  mMCEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(0);
  mMCEvent->GetHeader()->SetPrimaryVertexRanking(0);
  mMCEvent->GetHeader()->SetNumberOfVertices(1);
  
  mMCEvent->GetHeader()->SetNOfEMCPoints(0);
  mMCEvent->GetHeader()->SetNOfMatchedTowers(0);
  mMCEvent->GetHeader()->SetNOfTowers(0);
  //mMCEvent->GetHeader()->SetNOfPrimaryTracks(nCount);//see note next to "//nCount++"
  mMCEvent->GetHeader()->SetNOfMatchedTracks(0); //why is this 0?
  
  return;
}

void TStarJetPicoMaker::MuProcessV0s() {
  /* this is depricated - use at your own risk,
     it hasn't been tested by the authors... 
   */
  
  TStarJetPicoV0 jetV0;
  StMuTrack* global;
  bool posGlobalFound, negGlobalFound;
  
  for (int i = 0; i < mMuDst->v0s()->GetEntries(); ++i) {
    StV0MuDst* v0MuDst = (StV0MuDst*) mMuDst->v0s(i);
    
    if(mV0Selector->AcceptV0(mMuDst, v0MuDst)) {
      jetV0.Clear();
      posGlobalFound = kFALSE;
      negGlobalFound = kFALSE;
      
      jetV0.SetPxPos(v0MuDst->momPosX());
      jetV0.SetPyPos(v0MuDst->momPosY());
      jetV0.SetPzPos(v0MuDst->momPosZ());
      jetV0.SetPxNeg(v0MuDst->momNegX());
      jetV0.SetPyNeg(v0MuDst->momNegY());
      jetV0.SetPzNeg(v0MuDst->momNegZ());
      jetV0.SetKeyPos(v0MuDst->keyPos());
      jetV0.SetKeyNeg(v0MuDst->keyNeg());
      jetV0.SetDcapn(v0MuDst->dcaV0Daughters());
      jetV0.SetDcaV0(v0MuDst->dcaV0ToPrimVertex());
      jetV0.SetDcaPos(v0MuDst->dcaPosToPrimVertex());
      jetV0.SetDcaNeg(v0MuDst->dcaNegToPrimVertex());
      jetV0.SetDecayLength(v0MuDst->decayLengthV0());
      jetV0.SetDedxPos(v0MuDst->dedxPos());
      jetV0.SetDedxNeg(v0MuDst->dedxNeg());
      
      for (int j = 0; j < mMuDst->globalTracks()->GetEntries(); ++j) {
        global = mMuDst->globalTracks(j);
        if (global->id() == v0MuDst->keyPos()) {
          posGlobalFound = kTRUE;
          jetV0.SetNSigmaPionPos(global->nSigmaPion());
          jetV0.SetNSigmaProtonPos(global->nSigmaProton());
        }
        else if (global->id() == v0MuDst->keyNeg()) {
          negGlobalFound = kTRUE;
          jetV0.SetNSigmaPionNeg(global->nSigmaPion());
          jetV0.SetNSigmaProtonNeg(global->nSigmaProton());
        }
        if (negGlobalFound && posGlobalFound) break;
      }
      mEvent->AddV0(&jetV0);
    }
  }
}

bool TStarJetPicoMaker::LoadEvent() {
  mMuDst = mMuDstMaker->muDst();
  if (mMuDst == nullptr) {
    LOG_ERROR << "Could not load MuDst" << endm;
    return kStErr;
  }
  mMuInputEvent = mMuDst->event();
  if (mMuInputEvent == nullptr) {
    LOG_ERROR << "Could not load MuDstEvent" << endm;
    return kStErr;
  }
  
  int eventID = mMuInputEvent->eventId();
  int runID = mMuInputEvent->runId();
  
  // now try to match the event to a miniMC event in the chain
  
  int nTries = chain_->GetEntries();
  
  if (mMakeMC) {
      if (mStMiniMcEvent->eventId() == eventID && mStMiniMcEvent->runId() == runID) return true;
      while (nTries >= 0) {
          current_++;
          if (current_ >= chain_->GetEntries())
              current_ = 0;
          nTries--;

          chain_->GetEntry(current_);

          if (mStMiniMcEvent->eventId() == eventID &&
                  mStMiniMcEvent->runId() == runID)
              return true;
      }

      if (nTries < 0) {
          LOG_ERROR << "could not match event to miniMC" << endm;
          return false;
      }
  }
  
  return true;
}
