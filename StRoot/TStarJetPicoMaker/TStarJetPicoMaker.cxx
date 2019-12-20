#include "TStarJetPicoMaker.hh"

#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoTriggerInfo.h"

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


ClassImp(TStarJetPicoMaker)

TStarJetPicoMaker::TStarJetPicoMaker(std::string outFileName, inputMode input, std::string name)
  : StMaker(name.c_str()), mEventSelector(new TStarJetEventCuts), mV0Selector(new TStarJetV0Cuts),
    mOutFileName(outFileName), mOutFile(nullptr), mTree(nullptr), mMCTree(nullptr),
    mEvent(nullptr), mMCEvent(nullptr), mMuDst(nullptr), mMuInputEvent(nullptr),
    mPicoDst(nullptr), mPicoInputEvent(nullptr), mTriggerSimu(nullptr), mStMCEvent(nullptr),
    mEMCPosition(nullptr), mBEMCGeom(nullptr), mEMCFilter(nullptr), mBemcTables(nullptr),
    mBemcMatchedTracks(), mRefMultCorr(nullptr), mGRefMultCorr(nullptr), mCallsToMake(0),
    mNEvents(0), mNAcceptedEvents(0), mMakeV0(kFALSE), mMakeMC(kFALSE), mInputMode(input),
    mVertexMode(VpdOrRank), mTowerStatusMode(AcceptAllTowers), mRefMultCorrMode(FillNone),
    mdVzMax(3.0), mTrackFlagMin(0), mTrackDCAMax(3.0), mTrackEtaMin(-1.5), mTrackEtaMax(1.5),
    mTrackFitPointMin(10), mTowerEnergyMin(0.15) { }

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
  delete mMCEvent; mMCEvent = nullptr;
  delete mEvent; mEvent = nullptr;
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

Int_t TStarJetPicoMaker::Make() {
  mCallsToMake++;
  
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

  /* checks the event against all active
     event level selectors, possibly including
     vertex position & trigger
     if it doesnt pass, we stop procesing this event
   */
  if (!mEventSelector->AcceptEvent(mMuInputEvent)) return kStOk;
  
  /* create new event structures */
  mEvent = new TStarJetPicoEvent();
  if (mMakeMC) mMCEvent = new TStarJetPicoEvent();

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
  if (mMakeMC) mMCTree->Fill();
  
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
    mStMCEvent =  (StMcEvent*) GetDataSet("StMcEvent");
    if (!mStMCEvent) {
      LOG_ERROR << "TStarJetPicoMaker: No StMcEvent loaded for this event" << endm;
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
  if (mMakeMC && !mStMCEvent->primaryVertex()) {
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
    /* check if track will be saved to event structure */
    if(muTrack->flag() < mTrackFlagMin || muTrack->nHitsFit() <= mTrackFitPointMin ||
        muTrack->dcaGlobal().mag() > mTrackDCAMax || muTrack->eta() > mTrackEtaMax ||
        muTrack->eta() < mTrackEtaMin) continue;
    
    jetTrack.Clear();
    
    /* fill track information */
    jetTrack.SetPx(muTrack->momentum().x());
    jetTrack.SetPy(muTrack->momentum().y());
    jetTrack.SetPz(muTrack->momentum().z());
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
  LOG_DEBUG << "High Tower trigger thresholds: bht0 " << bht0 << " bht1: " << bht1 << " bht2: " << bht2 << " bht3: " << bht3 << endm;
  
  TStarJetPicoTriggerInfo trigobj;
  for (unsigned towerId = 1; towerId <= 4800; ++towerId) {
    int status;
    mTriggerSimu->bemc->getTables()->getStatus(BTOW, towerId, status);
    const Int_t adc = mTriggerSimu->bemc->barrelHighTowerAdc(towerId);
    Int_t trigMap = 0;
    Float_t eta, phi;
    mBEMCGeom->getEtaPhi(towerId, eta, phi);
    
    if (bht1 > 0 && adc > bht1) trigMap |= 1 << 1;
    if (bht2 > 0 && adc > bht2) trigMap |= 1 << 2;
    if (bht3 > 0 && adc > bht3) trigMap |= 1 << 3;
    
    if (trigMap & 0xf) {
      LOG_DEBUG << "high tower trigger found. ADC: " << adc << endm;
      
      trigobj.Clear();
      trigobj.SetEta(eta);
      trigobj.SetPhi(phi);
      trigobj.SetId(towerId);
      trigobj.SetADC(adc);
      trigobj.SetBitMap(trigMap);
      
      mEvent->AddTrigObj(&trigobj);
    }
  }
  
  /* get trigger thresholds for JP */
  Int_t jp0  = mTriggerSimu->bemc->barrelJetPatchTh(0);
  Int_t jp1  = mTriggerSimu->bemc->barrelJetPatchTh(1);
  Int_t jp2  = mTriggerSimu->bemc->barrelJetPatchTh(2);
  LOG_DEBUG << "Jet Patch trigger thresholds: jp0 " << jp0 << " jp1: " << jp1 << " jp2: " << jp2 << endm;
  
  /* lookup 12 jet patches & 6 overlap thresholds - no EEMC data saved */
  for (unsigned jp = 0; jp < 18; ++jp) {
    const Int_t jpAdc = mTriggerSimu->bemc->barrelJetPatchAdc(jp);
    Int_t trigMap = 0;
    
    if (jp0 > 0 && jpAdc > jp0) trigMap |= 1 << 4;
    if (jp1 > 0 && jpAdc > jp1) trigMap |= 1 << 5;
    if (jp2 > 0 && jpAdc > jp2) trigMap |= 1 << 6;
    
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

void TStarJetPicoMaker::PicoProcessTriggerObjects() {
 
}

Bool_t TStarJetPicoMaker::MuFillHeader() {
  
  /* fill triggers */
  std::vector<unsigned> triggerIds = mMuInputEvent->triggerIdCollection().nominal().triggerIds();
  for(unsigned i = 0; i < triggerIds.size(); i++)
    mEvent->GetHeader()->AddTriggerId(triggerIds[i]);
    
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
  int nCount = 0;
  
  const StPtrVecMcTrack& mcTracks = mStMCEvent->primaryVertex()->daughters();
  StMcTrackConstIterator mcTrkIter = mcTracks.begin();
  
  for (; mcTrkIter != mcTracks.end(); ++mcTrkIter) {
    StMcTrack* track = *mcTrkIter;
    TStarJetPicoPrimaryTrack mTrack;
    
    mTrack.SetPx(track->momentum().x());
    mTrack.SetPy(track->momentum().y());
    mTrack.SetPz(track->momentum().z());
    mTrack.SetDCA(0);
    
    mTrack.SetNsigmaPion(0);
    mTrack.SetNsigmaKaon(0);
    mTrack.SetNsigmaProton(0);
    mTrack.SetNsigmaElectron(0);
    
    if(track->particleDefinition()){
      mTrack.SetCharge(track->particleDefinition()->charge());
      mTrack.SetdEdx(track->particleDefinition()->pdgEncoding());
    }
    else{
      LOG_DEBUG << "Particle with no encoding " << endm;
      mTrack.SetCharge(0);
      mTrack.SetdEdx(0);
    }
    
    mTrack.SetNOfFittedHits(track->tpcHits().size());
    mTrack.SetNOfPossHits(52);
    mTrack.SetKey(track->key());
    mTrack.SetEtaDiffHitProjected(0);
    mTrack.SetPhiDiffHitProjected(0);
    nCount++;
    
    mMCEvent->AddPrimaryTrack(&mTrack);
    
  }
  
  
  mMCEvent->GetHeader()->SetEventId(mStMCEvent->eventNumber());
  mMCEvent->GetHeader()->SetRunId(mStMCEvent->runNumber());
  mMCEvent->GetHeader()->SetReferenceMultiplicity(mStMCEvent->eventGeneratorFinalStateTracks());
  mMCEvent->GetHeader()->SetNPrimaryTracks(nCount);
  mMCEvent->GetHeader()->SetNGlobalTracks(mStMCEvent->numberOfPrimaryTracks());
  mMCEvent->GetHeader()->SetReactionPlaneAngle(mStMCEvent->phiReactionPlane());
  
  mMCEvent->GetHeader()->SetPrimaryVertexX(mStMCEvent->primaryVertex()->position().x());
  mMCEvent->GetHeader()->SetPrimaryVertexY(mStMCEvent->primaryVertex()->position().y());
  mMCEvent->GetHeader()->SetPrimaryVertexZ(mStMCEvent->primaryVertex()->position().z());
  
  mMCEvent->GetHeader()->SetCTBMultiplicity(0);
  mMCEvent->GetHeader()->SetPrimaryVertexMeanDipAngle(0);
  mMCEvent->GetHeader()->SetPrimaryVertexRanking(0);
  mMCEvent->GetHeader()->SetNumberOfVertices(1);
  
  mMCEvent->GetHeader()->SetNOfEMCPoints(0);
  mMCEvent->GetHeader()->SetNOfMatchedTowers(0);
  mMCEvent->GetHeader()->SetNOfTowers(0);
  mMCEvent->GetHeader()->SetNOfPrimaryTracks(nCount);
  mMCEvent->GetHeader()->SetNOfMatchedTracks(0);
  
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
