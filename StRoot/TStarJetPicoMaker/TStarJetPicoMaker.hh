/*        TStarJetPicoMaker
   Produces TStarJetPicoEvent trees from STAR muDSTs,
   given a set of event parameters and quality cuts.
   Capable of producing both daq streams and MC streams.
 
   The output trees include:
   - event & run environment information
   - one primary vertex (selection criteria below)
   - primary tracks with respect to primary vertex
   - EMCal tower hits
   - EMCal trigger information
 */

#ifndef TSTARJETPICOMAKER__HH
#define TSTARJETPICOMAKER__HH

#include "TFile.h"
#include "TTree.h"

#include "StMaker.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StPicoDstMaker/StPicoDstMaker.h"
#include "StPicoEvent/StPicoDst.h"
#include "StPicoEvent/StPicoEvent.h"
#include "StTriggerUtilities/StTriggerSimuMaker.h"
#include "StMcEvent/StMcEventTypes.hh"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/filters/StEmcFilter.h"
#include "StEmcUtil/projection/StEmcPosition.h"

#include "TStarJetEventCuts.hh"
#include "TStarJetV0Cuts.hh"

#include <string>
#include <vector>


class TStarJetPicoEvent;
class StRefMultCorr;
class StBemcTables;
class StEmcCollection;
class StEmcCluster;

/*  Used to store track & tower matching 
    information between computation steps
 */
struct BemcMatch {
  Int_t globalId;
  Int_t trackId;
  Double_t trackEta;
  Double_t trackPhi;
  Double_t matchEta;
  Double_t matchPhi;
  
  BemcMatch() : globalId(-1), trackId(-1), trackEta(0.0), trackPhi(0.0), matchEta(0.0), matchPhi(0.0) {};
  BemcMatch(int id, int trkId, double trackEta, double trackPhi, double matchEta, double matchPhi) :
  globalId(id), trackId(trkId), trackEta(trackEta), trackPhi(trackPhi), matchEta(matchEta), matchPhi(matchPhi) {};
  
};

class TStarJetPicoMaker : public StMaker {
  
public:
  enum inputMode{NotSet=0, InputMuDst=1, InputPicoDst=2};
  enum vertexMode{VpdOrRank=0, Vpd=1, Rank=2};
  enum towerMode{AcceptAllTowers=0, RejectBadTowerStatus=1};
  enum refMultCorrectionMode{FillNone=0, FillGRefAndRefMultCorr=1, FillGRefMultCorr=2, FillGRefMultCorrP16ID=3, FillGRefMultCorrVPDMB30=4, FillGRefMultCorrVPDNoVtx=5, FillRefMultCorr=6};
  
  /* if input mode is not set by user, the reader will search the chain
     for a muDst or picoDst - if both are present for some
     reason, it will error out.
   */
  TStarJetPicoMaker(std::string outFileName, inputMode input = NotSet, std::string name = "TStarJetPicoMaker");
  ~TStarJetPicoMaker();
  
  /* the default methods called by the StChain. 
     Init(): called once to initialize before Make() is called
     Make(): called for each event, produces output TStarJetPicoEvent
             data structures for every event that passes event cuts
     Clear(): called after each Make() to reset for next event
     Finish(): called once at the end to save data to disk and clean up.
   */
  Int_t Init();
  Int_t Make();
  void  Clear(Option_t* option = "");
  Int_t Finish();
  
  /* WARNING: I have not had an opportunity to test this, it is merely
     copied from the old Maker.
     If true, maker expects input to have both monte-carlo & GEANT data,
     and will produce a TTree for each. Currently only works for muDst
   */
  void ProcessMC(bool flag) {mMakeMC = flag;}
  
  /*  *********DEPRICATED USE WITH CAUTION*********
        included for backwards compatibility, but
        has not been tested by us.
   */
  void ProcessV0s(bool flag) {mMakeV0 = flag;}
   
  /* returns pointer to TStarJetEventCuts intstance to allow
     direct setting of cut parameters by user.
   */
  TStarJetEventCuts* EventCuts() {return mEventSelector;}
  
  /* returns pointer to TStarJetv0Cuts instance to allow direct
     setting of cut parameters by user.
   */
  TStarJetV0Cuts*    V0Cuts() {return mV0Selector;}
  
  /* defines the input source (currently muDst or picoDst).
     If its not set, the reader will attempt to find the 
     source at Init() time
   */
  void SetInputSource(inputMode input) {mInputMode = input;}
  
  /* defines how a primary vertex is selected if using
     muDst input. PicoDsts only have one vertex.
     Default uses VPD if available, highest rank otherwise.
   */
  void SetVertexSelector(vertexMode vtx) {mVertexMode = vtx;}
  
  /* define if tower status should be used to reject towers, or if all
   towers should be accepted - default is to accept all towers, then
   generate a bad tower list for the entire data set.
   */
  void SetTowerAcceptMode(towerMode mode) {mTowerStatusMode = mode;}
  
  
  /* sets whether to do refmult/grefmult corrections for
   the reproduction. Be careful - the lookup is done only
   by run number, so if there are multiple productions of
   the same data, it can't discriminate and its possible
   StRefMultCorr will use a bad correction parameterization.
   Also - some runs have different parameterizations depending
   on trigger selection.
   */
  void SetStRefMultCorrMode(refMultCorrectionMode corrMode) {mRefMultCorrMode = corrMode;}
  
  /* if selecting vertices with the Vpd, can change the
     dVz requirement used from 3 cm
   */
  void SetVertexdVz(double dVz) {mdVzMax = dVz;}
  
  /* set minimum track flag value for primary tracks (default = 0) */
  void SetTrackFlagMin(int mMin) {mTrackFlagMin = mMin;}
  
  /* set maximum track DCA for primary tracks (default = 3) */
  void SetTrackDCAMax(double mMax) {mTrackDCAMax = mMax;}
  
  /* set eta range for primary tracks (default = -1.5, 1.5) */
  void SetTrackEtaRange(double mMin, double mMax) {mTrackEtaMin = mMin; mTrackEtaMax = mMax;}
  
  /* set minimum number of fit points required for a track
     (default = 10) 
   */
  void SetTrackFitPointMin(int mMin) {mTrackFitPointMin = mMin;}
  
  /* set the minimum tower energy to be reconstructed (default = 0.15) */
  void SetTowerEnergyMin(double mMin) {mTowerEnergyMin = mMin;}
  
  private:
  
  Int_t  InitInput();
  void   InitMakers();
  void   InitOutput();
  
  Int_t MakeMuDst();
  Int_t MakePicoDst();
  
  Int_t LoadMuDst();
  Int_t LoadPicoDst();
  
  Int_t  SelectVertex();
  Bool_t MatchToVpd();
  
  Bool_t  MuProcessPrimaryTracks();
  Bool_t  PicoProcessPrimaryTracks();
  Float_t ComputeXY(const StThreeVectorF& pos, const StPhysicalHelixD &helix);
  
  Bool_t MuProcessBEMC();
  Bool_t PicoProcessBEMC();
  Int_t  MuFindSMDClusterHits(StEmcCollection* coll, Double_t eta, Double_t phi, Int_t detectorID);
  
  void MuProcessTriggerObjects();
  void PicoProcessTriggerObjects();
  
  Bool_t MuFillHeader();
  Bool_t PicoFillHeader();
  
  Double_t MuGetReactionPlane();
  Double_t PicoGetReactionPlane();
  
  void MuProcessMCEvent();
  
  void MuProcessV0s();
  
  /* selects events on data quality and physical 
     characteristics, such as centrality
   */
  TStarJetEventCuts* mEventSelector;
  
  /* selects secondary vertices based on data quality
     and daughter selection from global tracks
   */
  TStarJetV0Cuts* mV0Selector;
  
  std::string mOutFileName;
  TFile* mOutFile;
  
  /* output TTrees, only attempts to fill mMCTree
     if mMakeMC flag is set
   */
  TTree* mTree;
  TTree* mMCTree;
  TStarJetPicoEvent* mEvent;
  TStarJetPicoEvent* mMCEvent;
  
  StMuDstMaker*       mMuDstMaker;
  StMuDst*            mMuDst;
  StMuEvent*          mMuInputEvent;
  StPicoDstMaker*     mPicoDstMaker;
  StPicoDst*          mPicoDst;
  StPicoEvent*        mPicoInputEvent;
  StTriggerSimuMaker* mTriggerSimu;
  StMcEvent*          mStMCEvent;
  
  StEmcPosition*         mEMCPosition;
  StEmcGeom*             mBEMCGeom;
  StEmcFilter*           mEMCFilter;
  StBemcTables*          mBemcTables;
  std::vector<BemcMatch> mBemcMatchedTracks;
  
  StRefMultCorr*      mRefMultCorr;
  StRefMultCorr*      mGRefMultCorr;
  
  unsigned mCallsToMake, mNEvents, mNAcceptedEvents;
  
  bool   mMakeV0;
  bool   mMakeMC;
  
  inputMode  mInputMode;
  
  vertexMode mVertexMode;
  
  towerMode  mTowerStatusMode;
  
  refMultCorrectionMode mRefMultCorrMode;
  
  Double_t mdVzMax;
  Int_t    mTrackFlagMin;
  Double_t mTrackDCAMax;
  Double_t mTrackEtaMin;
  Double_t mTrackEtaMax;
  Int_t    mTrackFitPointMin;
  Double_t mTowerEnergyMin;
  
  ClassDef(TStarJetPicoMaker,1)
};

#endif /* TStarJetPicoMaker */
