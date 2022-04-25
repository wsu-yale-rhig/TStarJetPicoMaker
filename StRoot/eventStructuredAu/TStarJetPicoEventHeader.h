//marks bugfix.

#ifndef __TSTARJETPICOEVENTHEADER_HH
#define __TSTARJETPICOEVENTHEADER_HH

#include <TObject.h>
#include <TArrayI.h>

class TStarJetPicoEventHeader : public TObject
{
 public:
  TStarJetPicoEventHeader();
  TStarJetPicoEventHeader(const TStarJetPicoEventHeader &t);

  virtual ~TStarJetPicoEventHeader();

  void    Clear(Option_t *Option = "");

  Int_t   GetEventId()                   const {return fEventId;}
  Int_t   GetRunId()                     const {return fRunId;}

  /// KK: Selects Refmult, GRefmult, CorRefmult as appropriate
  Double_t   GetProperReferenceMultiplicity(); 

  Int_t   GetReferenceMultiplicity()     const {return fRefMult;}
  Int_t   GetRefMultRank0()              const {return fRefMultRank0;}
  Int_t   GetGReferenceMultiplicity()    const {return fGRefMult;}
  Int_t   GetReferenceCentrality()     const {return fRefCent;}
  Int_t   GetGReferenceCentrality()    const {return fGRefCent;}
  Double_t   GetReferenceCentralityWeight()     const {return fRefCentWeight;}
  Double_t   GetGReferenceCentralityWeight()    const {return fGRefCentWeight;}
  Double_t   GetCorrectedReferenceMultiplicity()     const {return fCorRefMult;}
  Double_t   GetCorrectedGReferenceMultiplicity()    const {return fCorGRefMult;}
  Double_t   GetGRefMultCorrRank0()             const {return fGRefMultCorrRank0;}
  Int_t   GetNGlobalTracks()             const {return fNOfGlobalTracks;}
  Float_t GetReactionPlaneAngle()        const {return fReactionPlaneAngle;}
  Int_t   GetTriggerId(Int_t ic)         const {return fTriggerIdArray.At(ic);}
  Int_t   GetNOfTriggerIds()             const {return fNOfTriggerIds;}
  const TArrayI* GetTriggerIdArray()     const {return &fTriggerIdArray;}

  /// KK: Convenience lookup for individual trigger IDs, mainly to plot directly from the tree
  Bool_t HasTriggerId ( const Int_t id ) const;

  //IM: Added BTOF multiplicity for use in AA
  unsigned int   GetBTofMult()           const {return fBTofMult;}

  // These next three are the multiplicities of the branches...
  Int_t   GetNOfMatchedTowers()          const {return fNOfTowerTrackMatched;}
  Int_t   GetNOfTowers()                 const {return fNOfTowers;}
  Int_t   GetNOfPrimaryTracks()          const {return fNOfPrimaryTracks;}
  Int_t   GetNOfFtpcPrimaryTracks()      const {return fNOfFtpcPrimaryTracks;}
  Int_t   GetNOfMatchedTracks()          const {return fNOfMatchedTracks;}
  Int_t   GetNOfV0s()                    const {return fNOfV0s;}
  Int_t   GetNOfTrigObjs()               const {return fNOfTrigObjs;}
  Int_t   GetNOfEMCPoints()              const {return fNOfEMCPoints;}

  Float_t GetPrimaryVertexX()            const {return fPVx;}
  Float_t GetPrimaryVertexY()            const {return fPVy;}
  Float_t GetPrimaryVertexZ()            const {return fPVz;}
 
  Float_t GetVpdVz()                     const{return fvpdVz;}
  Float_t GetvpdVz()                     const{return GetVpdVz();} // kept for legacy code
  
  Float_t GetCTBMultiplicity()           const {return fCTBmult;}
  Float_t GetPrimaryVertexMeanDipAngle() const {return fMeanDip;}
  Float_t GetPrimaryVertexRanking()      const {return fRank;}
  Int_t   GetPrimaryVertexID()           const {return fVertID;}
  Int_t   GetNumberOfVertices()          const {return fNOfVertices;}
  Int_t   GetDSMInput()                  const {return fDSMInput;}
  Int_t   GetTrigMask()                  const {return fTrigMask;}
  
  /* trigger thresholds for the run: barrel high tower 0-3, jet patch 0-2
     returns an ADC value. This is the same value that is used by the
     StTriggerSimuMaker for the TStarJetPicoTriggerInfo objects
   */
  UInt_t GetHighTowerThreshold( UInt_t i ) const {return fHighTowerThreshold[i];}
  UInt_t GetJetPatchThreshold( UInt_t i )  const {return fJetPatchThreshold[i];}

  //cut variables for dAu year 8
  Float_t GetZdcWestRate()                  const {return fZdcWestRate;}
  Float_t GetZdcEastRate()                  const {return fZdcEastRate;}
  Float_t GetZdcCoincidenceRate()           const {return fZdcCoincidenceRate;}
  Float_t GetBbcWestRate()                  const {return fBbcWestRate;}
  Float_t GetBbcEastRate()                  const {return fBbcEastRate;}
  Float_t GetBbcCoincidenceRate()           const {return fBbcCoincidenceRate;}
  Float_t GetBbcBlueBackgroundRate()        const {return fBbcBlueBackgroundRate;}
  Float_t GetBbcYellowBackgroundRate()      const {return fBbcYellowBackgroundRate;}
  Int_t   GetBbcAdcSumEast()                const {return GetBbcAdcSumEastInner();}
  Int_t   GetBbcAdcSumEastInner()           const {return fBbcAdcSumEast;}
  Int_t   GetBbcAdcSumEastOuter()           const {return fBbcAdcSumEastOuter;}
  Int_t   GetBbcAdcSumWest()                const {return GetBbcAdcSumWestInner();}
  Int_t   GetBbcAdcSumWestInner()           const {return fBbcAdcSumWest;}
  Int_t   GetBbcAdcSumWestOuter()           const {return fBbcAdcSumWestOuter;}
  
  Int_t   GetnumberOfVpdEastHits()          const {return fnumberOfVpdEastHits;}
  Int_t   GetnumberOfVpdWestHits()          const {return fnumberOfVpdWestHits;}
  // pp vertex cut info
  Int_t  GetBbcOnlineVertex()               const {return fBbcOnlineVertex;}
  Float_t  GetBbcOfflineVertex()            const {return fBbcOfflineVertex;}

  // d+Au centrality through FTPC East
  Int_t GetRefMultFTPCE()                   const {return fRefMultFTPCE;}

  // SETTERS
  void SetEventId(Int_t val)                     {fEventId = val;}
  void SetRunId(Int_t val)                       {fRunId = val;}
  void SetReferenceMultiplicity(Int_t val)       {fRefMult = val;}
  void SetRefMultRank0(Int_t val)                {fRefMultRank0 = val;}
  void SetGReferenceMultiplicity(Int_t val)      {fGRefMult = val;}
  void SetReferenceCentrality(Int_t val)       {fRefCent = val;}
  void SetGReferenceCentrality(Int_t val)      {fGRefCent = val;}
  void SetReferenceCentralityWeight(Double_t val)       {fRefCentWeight = val;}
  void SetGReferenceCentralityWeight(Double_t val)      {fGRefCentWeight = val;}
  void SetCorrectedReferenceMultiplicity(Double_t val)       {fCorRefMult = val;}
  void SetCorrectedGReferenceMultiplicity(Double_t val)      {fCorGRefMult = val;}
  void SetGRefMultCorrRank0(Double_t val)               {fGRefMultCorrRank0 = val;}

  void SetNPrimaryTracks(Int_t val)              {fNOfPrimaryTracks = val;}
  void SetNFtpcPrimaryTracks(Int_t val)          {fNOfFtpcPrimaryTracks = val;}

  void SetNGlobalTracks(Int_t val)               {fNOfGlobalTracks = val;}
  void SetReactionPlaneAngle(Float_t val)        {fReactionPlaneAngle = val;}
  void AddTriggerId(Int_t tid);
  
  void SetBTofMult(unsigned int val)             {fBTofMult = val;}

  // These next three are the multiplicities of the branches...
  void SetNOfMatchedTowers(Int_t val)            {fNOfTowerTrackMatched = val;}
  void SetNOfTowers(Int_t val)                   {fNOfTowers = val;}
  void SetNOfPrimaryTracks(Int_t val)            {fNOfPrimaryTracks = val;}
  void SetNOfMatchedTracks(Int_t val)            {fNOfMatchedTracks = val;}
  void SetNOfFtpcPrimaryTracks(Int_t val)        {fNOfFtpcPrimaryTracks = val;}
  void SetNOfV0s(Int_t val)                      {fNOfV0s = val;}
  void SetNOfTrigObjs(Int_t val)                 {fNOfTrigObjs = val;}
  
  void SetNOfEMCPoints(Int_t val)                {fNOfEMCPoints = val;}
  
  void SetPrimaryVertexX(Float_t val)            {fPVx = val;}
  void SetPrimaryVertexY(Float_t val)            {fPVy = val;}
  void SetPrimaryVertexZ(Float_t val)            {fPVz = val;}
  
  void SetvpdVz(Float_t val)                     {fvpdVz = val;}

  void SetCTBMultiplicity(Float_t val)           {fCTBmult = val;}
  void SetPrimaryVertexMeanDipAngle(Float_t val) {fMeanDip = val;}
  void SetPrimaryVertexRanking(Float_t val)      {fRank = val;}
  void SetPrimaryVertexID(Int_t val)             {fVertID = val;}
  void SetNumberOfVertices(Int_t val)            {fNOfVertices = val;}
  void SetDSMInput(Int_t val)                    {fDSMInput = val;}
  void SetTrigMask(Int_t val)                    {fTrigMask = val;}
  
  void SetHighTowerThreshold( UInt_t i, UInt_t val ) {fHighTowerThreshold[i] = val;}
  void SetJetPatchThreshold( UInt_t i, UInt_t val )  {fJetPatchThreshold[i] = val;}

  
  //cut variables for dAu year 8
  void SetZdcWestRate(Float_t val)               {fZdcWestRate = val;}
  void SetZdcEastRate(Float_t val)               {fZdcEastRate = val;}
  void SetZdcCoincidenceRate(Float_t val)        {fZdcCoincidenceRate = val;}
  void SetBbcWestRate(Float_t val)               {fBbcWestRate = val;}
  void SetBbcEastRate(Float_t val)               {fBbcEastRate = val;}
  void SetBbcCoincidenceRate(Float_t val)        {fBbcCoincidenceRate = val;}
  void SetBbcBlueBackgroundRate(Float_t val)     {fBbcBlueBackgroundRate = val;}
  void SetBbcYellowBackgroundRate(Float_t val)   {fBbcYellowBackgroundRate = val;}
  void SetBbcAdcSumEast(Int_t val)               {SetBbcAdcSumEastInner(val);}
  void SetBbcAdcSumEastInner(Int_t val)          {fBbcAdcSumEast = val;}
  void SetBbcAdcSumEastOuter(Int_t val)          {fBbcAdcSumEastOuter = val;}
  void SetBbcAdcSumWest(Int_t val)               {SetBbcAdcSumWestInner(val);}
  void SetBbcAdcSumWestInner(Int_t val)          {fBbcAdcSumWest = val;}
  void SetBbcAdcSumWestOuter(Int_t val)          {fBbcAdcSumWestOuter = val;}
  void SetnumberOfVpdEastHits(Int_t val)         {fnumberOfVpdEastHits = val;}
  void SetnumberOfVpdWestHits(Int_t val)         {fnumberOfVpdWestHits = val;}
 // pp vertex cut info
  void  SetBbcOnlineVertex(Int_t val)             {fBbcOnlineVertex = val;}
  void  SetBbcOfflineVertex(Float_t val)          {fBbcOfflineVertex = val;}
  //d+Au FTPC East centrality
  void SetRefMultFTPCE(Int_t val)                 {fRefMultFTPCE = val;}
  

 protected:
 private:

  // EVENT variables
  Int_t           fEventId;              // was evid;  // event ID
  Int_t           fRunId;                // was runid; // run ID
  Int_t           fRefMult;              // reference multiplicity
  Int_t           fRefMultRank0;         // reference multiplicity of zeroth-ranked vertex
  Int_t           fGRefMult;             // reference multiplicity for AuAu07
  Int_t           fRefCent;              // StRefMultCorr centrality9
  Int_t           fGRefCent;             // StRefMultCorr grefmult centrality9
  Double_t        fRefCentWeight;        // StRefMultCorr event weight for trigger effiency
  Double_t        fGRefCentWeight;       // StRefMultCorr event weight for trigger effiency
  Double_t        fCorRefMult;           // StRefMultCorr Corrected refmult 
  Double_t        fCorGRefMult;          // StRefMultCorr Corrected grefmult
  Int_t           fGRefMultCorrRank0;        // GReference multiplicty of zeroth-ranked vertex
  Int_t           fNOfGlobalTracks;      // was gtracks;    // number of global tracks
  Float_t         fReactionPlaneAngle;   // rplane;     // reaction plane orientation
  Int_t           fNOfTriggerIds;        // number of trigger ids 
  TArrayI         fTriggerIdArray;       // array of the trigger ids
  Int_t           fNOfTowerTrackMatched; // nCand;      //  number of all towers fired
  Int_t           fNOfTowers;            // nFlag;      // number of all towers fired
  unsigned int    fBTofMult;             // BTOF multiplicity
  
  Int_t           fNOfPrimaryTracks;     // number of primary tracks not matched to towers (used in Jet Finder)
  Int_t           fNOfMatchedTracks;     // number of primary tracks matched to towers(used in Jet Finder)
  Int_t           fNOfFtpcPrimaryTracks; // number of primary tracks in FTPC

  Int_t           fNOfV0s;               // no of v0s
  Int_t           fNOfEMCPoints;         // EmcPoints;  // number of EMC points
  Float_t         fPVx;                  // primary vertex X coord
  Float_t         fPVy;                  // primary vertex Y coord
  Float_t         fPVz;                  // primary vertex Z coord
  Float_t         fvpdVz;                // vpd Z 
  Float_t         fCTBmult;              // entral barrel multiplicity 
  Float_t         fMeanDip;              // primary vertex mean dip angle
  Float_t         fRank;                 // ranking of the vertex
  Int_t           fVertID;               // ID of chosen vertex
  Int_t           fNOfVertices;          // number of vertices
  Int_t           fNOfTrigObjs;          // no of trigger objects
  Int_t           fDSMInput;             // trigger: DSM
  Int_t           fTrigMask;             // trigger: Mask
  UInt_t          fHighTowerThreshold[4];// trigger thresholds for barrel EMC triggers: BHT 0, 1, 2, 3
  UInt_t          fJetPatchThreshold[3]; // trigger thresholds for jet patch triggers: JP 0, 1, 2

  //cut variables for dAu year 8
  Float_t  fZdcWestRate;
  Float_t  fZdcEastRate;
  Float_t  fZdcCoincidenceRate;
  Float_t  fBbcWestRate;
  Float_t  fBbcEastRate;
  Float_t  fBbcCoincidenceRate;
  Float_t  fBbcBlueBackgroundRate;
  Float_t  fBbcYellowBackgroundRate;
  Int_t    fBbcAdcSumEast;
  Int_t    fBbcAdcSumEastOuter;
  Int_t    fBbcAdcSumWest;
  Int_t    fBbcAdcSumWestOuter;

 // pp vertex cut info
  Int_t   fBbcOnlineVertex;
  Float_t fBbcOfflineVertex;

  Int_t   fRefMultFTPCE;

  Int_t    fnumberOfVpdEastHits;
  Int_t    fnumberOfVpdWestHits;

  ClassDef(TStarJetPicoEventHeader, 10)
};

#endif
