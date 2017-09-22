/* Author Sevil Salur 2007
   Including Mark's PP study
   updated with TStarJetPico from Mateusz
   #StMuJetAnalysisTreeMaker.h  
*/

#ifndef StMuJetAnalysisTreeMaker_hh     
#define StMuJetAnalysisTreeMaker_hh
//
//  Include files
#include "StMaker.h"
#include <string>
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StEmcUtil/geometry/StEmcGeom.h"
#include "StEmcUtil/filters/StEmcFilter.h"
#include "StEmcUtil/projection/StEmcPosition.h"
#include "StarClassLibrary/StThreeVectorF.hh"
#include "StTriggerUtilities/StTriggerSimuMaker.h"
#include "StMcEvent/StMcEventTypes.hh"
#include "StMcEvent/StMcContainers.hh"
#include "StarClassLibrary/StParticleDefinition.hh"
#include <TH1.h>
#include <TH2.h> 
#include "TObjArray.h"

//  Forward declarations
class StMuTrack;
class StMuV0I;
class TFile;
class TH1D;
//class TStMuEventAna;

class StEmcGeom;
class StEmcFilter;
class StEmcCluster;
class StBemcTables; //v3.14
class StTriggerSimuMaker;
class StV0MuDst;

//Mateusz's class
class TStarJetPicoEvent;
class TStMuCutV0Jet;
class TStMuCutEventJet;
class TStarJetPicoTriggerInfo;
class TStarJetPicoQAHistograms;

#ifndef ST_NO_NAMESPACES
using std::string;
#endif 
//
//  The class declaration. It innherits from StMaker.
class StMuJetAnalysisTreeMaker : public StMaker {
public:

    StMuJetAnalysisTreeMaker(const Char_t *name="muAnalysis");   // constructor
    ~StMuJetAnalysisTreeMaker();                                 // destructor
    
    void     Clear(Option_t *option=""); // called after every event to cleanup
    void     SelectCentrality(int centrality)             {fcentrality = centrality;}  	// #ly 2015.06.18	if -1, all centrality class
    void     setRootFile(const char* filename)             {fFilename = filename;}  
    Int_t    Init();                   // called once at the beginning of your job
    Int_t    Make();                   // invoked for every event
    Int_t    Finish();                 // called once at the end
    void     AddTriggerInfo(StTriggerSimuMaker *simuTrig);
    Int_t    doTowerMatching(); 
    Int_t    doPrimTrks();
    Int_t    doCheckMatchedTracks();
    //  Int_t    GetTowerE(int,int,int);
    void     SetNHits(Int_t nhits){fNHits=nhits;}
    Int_t    GetNHits()const{return fNHits;}
    Int_t    doV0s();
    void     SetDoV0s(Bool_t doit){doV0 = doit;}
    void     SetDoMc(Bool_t doit) {doMc = doit;}
    void    doMcTracks();
    void SetTriggerMapping(TString trigMap);

    void SetSimuTrig(StTriggerSimuMaker *sT){simuTrig=sT;}


    TStMuCutV0Jet*  GetV0Cuts(){return fTCutV0;};
    
    TStMuCutEventJet* GetEventCuts(){return  fTCutEvent;};

    StEmcCluster* findSMDCluster(Float_t,Float_t,Int_t);
    Int_t    SMDHits(Int_t,Int_t);

    void     SetVerbose(bool verb)           {mVerbose = verb;};
    Double_t GetReactionPlane();
   
    inline  Int_t GetMatchedTracks()  {return rMatch;};
    void SetFlagData(Int_t Cut=1);

    // there's no reason to require them, but originally it was done so -> put this for backward compatibility & by default, require them still...
    void SetRequireBarrelPoints(Bool_t require_it) {requireBarrelPoints = require_it;}

    void SetFillAllPV(Bool_t fillit) {FillAllPV = fillit;}

    Int_t GetEventCounter() {return mEventCounter;}
    Int_t GetAllPVEventCounter() {return mAllPVEventCounter;}
    Int_t GetInputEventCounter() {return mInputEventCounter;}

    Float_t  computeXY(const StThreeVectorF&, const StPhysicalHelixD &);
   
    Float_t PrimVertexZ;
    
    virtual const char *GetCVS() const {
      static const char cvs[]="Tag $Name:  $ $Id: StMuJetAnalysisTreeMaker.h,v 1.3 2015/07/12 20:09:12 yili Exp $ built "__DATE__" "__TIME__ ; 
      return cvs;
    }
	
    // nick elsey: set a maximum distance allowed between TPC primary vertex Vz and vpd Vz 
    void    SetMaxdVz(Float_t val) {MaxdVz = val;}
    Float_t GetMaxdVz()		   {return MaxdVz;}
  
 private:

    //Mateusz Class variables;
    TStarJetPicoEvent *MEvent;
    TStarJetPicoEvent *MMcEvent;

    TTree *MTree; 
    TTree *MMcTree;
    TStarJetPicoQAHistograms *QAHist;

    const char *fFilename;     //! Name of root file
    Int_t	 fcentrality;	//! Cut on centrality   	// #ly 2015.06.18
    Int_t        mEventCounter;  //!
    Int_t        mAllPVEventCounter;
    Int_t        mInputEventCounter;
    TFile      *mFile;         //!
    
    // method (a simple track filter)
    StEmcGeom       *mGeom;         
    StEmcCollection *mEmcCol;  
    StEmcFilter     *mFilter;
    StBemcTables    *mTables;
    Int_t    mCounter;
 
    
    Int_t *fMatchTrArr;//!
    Float_t *fMatchTrEtaArr;//!
    Float_t *fMatchTrPhiArr;//!
    Int_t *fPrimIndexArray;//!
    Float_t *fPrimEtaArray;//!
    Float_t *fPrimPhiArray;//!

    bool mVerbose;              
    const StMuTrack* track;  
    const StMuTrack* gltrack;  
    StMuEvent* muEvent;
    Int_t nTracks;
    Int_t nMTracks;

   StMcEvent * mcEvent;
   
    vector<StMuTrack*>mTracks;         

    Int_t   rBarrelPts; 
    Float_t rTowerEnergy; 
    Int_t   rTowerADC; 
    Int_t   clusterid;
    
    Int_t    rMatch; 
    Double_t Bfield;            
    Int_t   nPrimTrks;
    Int_t   nCand;
    Int_t   nFlag;
    Float_t rplane;
    Int_t fNHits;
    Int_t nV0s;
    Bool_t doV0;
    Bool_t doMc;
    Int_t fNTOTMatchedTr;
    Int_t fMatchedTow;
    Bool_t requireBarrelPoints;

    //this fills in events regardless of Primary Vertex existence/position: beyond cut/non-existing: only header&triggers are filled
    Bool_t FillAllPV;

    Float_t PrimaryVertexZmin;
    Float_t PrimaryVertexZmax;
	
    // the maximum distance allowed between a TPC vertex and vpdVz 
    // to be considered for the primary vertex
    Float_t MaxdVz;
	

    /*  TH1D *hEventRefMult;
    TH1D *hEventVertexZ;
    TH1D *hEventNPrim;
    TH1D *hEventNPrimCut;
    TH1D *hEventNTowers; 
    TH1D *hEventNTowersCut;
    
      //Track QA
    TH1D *hTrackNhits;
    TH1D *hTrackNhitsCut;
    TH1D *hTrackDCA;
    TH1D *hTrackEta; 
    TH1D *hTrackPhi;
    TH1D *hTrackPoverE;
    
  
  //Tower QA
  TH1D *hTowerEta;
  TH1D *hTowerEtaC;
  TH1D *hTowerPhi;
  TH1D *hTowerET;
  TH1D *hNMatched;
  
  TH2D *hNMatchedvsRefMult;
  TH2D *hPtvsEtMatched;
  TH2D *hEtaMEtaT;
  TH2D *hPhiMPhiT;
    */

    TString fTrigMap;

    TStMuCutV0Jet  *fTCutV0;        //! V0 cut class
 
    StTriggerSimuMaker* simuTrig;
    StEmcPosition *mPosition;
    
    Int_t nflagData;
    StMuDst* mu;
    
    TStMuCutEventJet  *fTCutEvent;        //! event cut class
    ClassDef(StMuJetAnalysisTreeMaker,5)
};


inline void StMuJetAnalysisTreeMaker::SetFlagData(Int_t Cut){nflagData=Cut;}   
#endif
