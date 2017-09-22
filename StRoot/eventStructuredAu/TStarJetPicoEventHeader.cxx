#include "TStarJetPicoEventHeader.h"

#include "TStarJetPicoDefinitions.h"
#include <TString.h>
#include <math.h>

ClassImp(TStarJetPicoEventHeader)

#define __INITIAL_NUMBER_OF_TID 1

// -----------------------------------------------------------------------------
TStarJetPicoEventHeader::TStarJetPicoEventHeader()
  : TObject()
  , fEventId(0)
  , fRunId(0)
  , fRefMult(0)
  , fRefMultRank0(0)
  , fGRefMult(0)
  , fRefCent(-1)
  , fGRefCent(-1)
  , fRefCentWeight(0)
  , fGRefCentWeight(0)
  , fCorRefMult(0)
  , fCorGRefMult(0)
  , fGRefMultCorrRank0(0)
  , fNOfGlobalTracks(0)
  , fReactionPlaneAngle(0)
  , fNOfTriggerIds(0)
  , fTriggerIdArray(__INITIAL_NUMBER_OF_TID)
  , fNOfTowerTrackMatched(0)
  , fNOfTowers(0)
  , fNOfPrimaryTracks(0)
  , fNOfMatchedTracks(0)
  , fNOfFtpcPrimaryTracks(0)
  , fNOfV0s(0)
  , fNOfEMCPoints(0)
  , fPVx(-999.)
  , fPVy(-999.)
  , fPVz(-999.)
  , fvpdVz(-999.)
  , fCTBmult(0)
  , fMeanDip(0)
  , fRank(0)
  , fVertID(0)
  , fNOfVertices(0)   
  , fNOfTrigObjs(0) 
  , fDSMInput(0)
  , fTrigMask(0)
  , fHighTowerThreshold{}
  , fJetPatchThreshold{}
  , fZdcWestRate(0)
  , fZdcEastRate(0)
  , fZdcCoincidenceRate(0)
  , fBbcWestRate(0)
  , fBbcEastRate(0)
  , fBbcCoincidenceRate(0)
  , fBbcBlueBackgroundRate(0)
  , fBbcYellowBackgroundRate(0)
  , fBbcAdcSumEast(0)
  , fBbcOnlineVertex(0)
  , fBbcOfflineVertex(0)
  , fRefMultFTPCE(0)
  , fnumberOfVpdEastHits(0)
  , fnumberOfVpdWestHits(0)
{
  fTriggerIdArray.Reset(0);
}

// -----------------------------------------------------------------------------
TStarJetPicoEventHeader::TStarJetPicoEventHeader(const TStarJetPicoEventHeader &t)
  : TObject(t)
  , fEventId(t.fEventId)
  , fRunId(t.fRunId)
  , fRefMult(t.fRefMult)
  , fRefMultRank0(t.fRefMultRank0)
  , fGRefMult(t.fGRefMult)
  , fRefCent(t.fRefCent)
  , fGRefCent(t.fGRefCent)
  , fRefCentWeight(t.fRefCentWeight)
  , fGRefCentWeight(t.fGRefCentWeight)
  , fCorRefMult(t.fCorRefMult)
  , fCorGRefMult(t.fCorGRefMult)
  , fGRefMultCorrRank0(t.fGRefMultCorrRank0)    
  , fNOfGlobalTracks(t.fNOfGlobalTracks)
  , fReactionPlaneAngle(t.fReactionPlaneAngle)
  , fNOfTriggerIds(t.fNOfTriggerIds)
  , fTriggerIdArray(t.fTriggerIdArray)
  , fNOfTowerTrackMatched(t.fNOfTowerTrackMatched)
  , fNOfTowers(t.fNOfTowers)
  , fNOfPrimaryTracks(t.fNOfPrimaryTracks)
  , fNOfMatchedTracks(t.fNOfMatchedTracks)
  , fNOfFtpcPrimaryTracks(t.fNOfFtpcPrimaryTracks)
  , fNOfV0s(t.fNOfV0s)
  , fNOfEMCPoints(t.fNOfEMCPoints)
  , fPVx(t.fPVx)
  , fPVy(t.fPVy)
  , fPVz(t.fPVz)
  , fvpdVz(t.fvpdVz)
  , fCTBmult(t.fCTBmult)
  , fMeanDip(t.fMeanDip)
  , fRank(t.fRank)
  , fVertID(t.fVertID)
  , fNOfVertices(t.fNOfVertices) 
  , fNOfTrigObjs(t.fNOfTrigObjs)  
  , fDSMInput(t.fDSMInput)
  , fTrigMask(t.fTrigMask)
  , fZdcWestRate(t.fZdcWestRate)
  , fZdcEastRate(t.fZdcEastRate)
  , fZdcCoincidenceRate(t.fZdcCoincidenceRate)
  , fBbcWestRate(t.fBbcWestRate)
  , fBbcEastRate(t.fBbcEastRate)
  , fBbcCoincidenceRate(t.fBbcCoincidenceRate)
  , fBbcBlueBackgroundRate(t.fBbcBlueBackgroundRate)
  , fBbcYellowBackgroundRate(t.fBbcYellowBackgroundRate)
  , fBbcAdcSumEast(t.fBbcAdcSumEast)
  , fBbcOnlineVertex(t.fBbcOnlineVertex)
  , fBbcOfflineVertex(t.fBbcOfflineVertex)
  , fRefMultFTPCE(t.fRefMultFTPCE)
  , fnumberOfVpdEastHits(t.fnumberOfVpdEastHits)
  , fnumberOfVpdWestHits(t.fnumberOfVpdWestHits)
{
  for ( int i = 0; i < 4; ++i ) fHighTowerThreshold[i] = t.fHighTowerThreshold[i];
  for ( int i = 0; i < 3; ++i ) fJetPatchThreshold[i] = t.fJetPatchThreshold[i];
}

// -----------------------------------------------------------------------------
TStarJetPicoEventHeader::~TStarJetPicoEventHeader()
{
  ;
}

// -----------------------------------------------------------------------------
void TStarJetPicoEventHeader::Clear(Option_t */*Option*/)
{
  fEventId = 0;              
  fRunId = 0;                
  fRefMult = 0;
  fRefMultRank0 = 0;
  fGRefMult = 0;
  fRefCent = 0;
  fGRefCent = 0;
  fRefCentWeight = 0;
  fGRefCentWeight = 0;
  fCorRefMult = 0;
  fCorGRefMult = 0;
  fGRefMultCorrRank0 = 0;
  fNOfGlobalTracks = 0;      
  fReactionPlaneAngle = 0;   
  fNOfTriggerIds = 0;            
  fTriggerIdArray.Set(__INITIAL_NUMBER_OF_TID);
  fTriggerIdArray.Reset(0);    
  fNOfTowerTrackMatched = 0; 
  fNOfTowers = 0;         
  
  fNOfPrimaryTracks = 0; 
  fNOfMatchedTracks = 0;  
  fNOfFtpcPrimaryTracks = 0;   
  fNOfV0s = 0;  
  fNOfEMCPoints = 0;         
  fPVx = -999.;                  
  fPVy = -999.;                  
  fPVz = -999.;                  
  fvpdVz = -999.;
  fCTBmult = 0;              
  fMeanDip = 0;              
  fRank = 0;
  fVertID = 0;                 
  fNOfVertices = 0;          
  fNOfTrigObjs = 0;
  fDSMInput = 0;
  fTrigMask = 0;
  for ( int i = 0; i < 4; ++i ) fHighTowerThreshold[i] = 0;
  for ( int i = 0; i < 3; ++i ) fJetPatchThreshold[i] = 0;
  fZdcWestRate = 0;
  fZdcEastRate = 0;
  fZdcCoincidenceRate = 0;
  fBbcWestRate = 0;
  fBbcEastRate = 0;
  fBbcCoincidenceRate = 0;
  fBbcBlueBackgroundRate = 0;
  fBbcYellowBackgroundRate = 0;
  fBbcAdcSumEast = 0;
  fBbcOnlineVertex = 0;
  fBbcOfflineVertex = 0;
  fRefMultFTPCE = 0;
    
  fnumberOfVpdEastHits = 0;
  fnumberOfVpdWestHits = 0;
}

// -----------------------------------------------------------------------------
void TStarJetPicoEventHeader::AddTriggerId(Int_t id)
{
  //
  // Add new trigger id
  // Resize the array if necessary
  //
  if ( fNOfTriggerIds < fTriggerIdArray.GetSize() )
    {
      fTriggerIdArray[fNOfTriggerIds++] = id;
    }
  else
    {
      Int_t newsize = fTriggerIdArray.GetSize() + 1;
      __DEBUG(3, Form("Resizing trigger ids array from %d to %d", 
		      fTriggerIdArray.GetSize(), newsize));
      fTriggerIdArray.Set(newsize);
      AddTriggerId(id);
    }
}

// -----------------------------------------------------------------------------
Bool_t TStarJetPicoEventHeader::HasTriggerId ( const Int_t id ) const{
  for ( int i=0; i< fTriggerIdArray.GetSize() ; ++i){
    // std::cout << fTriggerIdArray[i] << " == " << id << "? "<< std::endl;
    if ( fTriggerIdArray[i] == id ) {
      // std::cout << " yes!" << std::endl;      
      return true;
    }
  }

  return false;
}



// -----------------------------------------------------------------------------
/// KK: Selects Refmult, GRefmult, CorRefmult as appropriate
Double_t TStarJetPicoEventHeader::GetProperReferenceMultiplicity(){
  // There are multiple ways to do this. 
  // 1 - select based on trigger ID
  // 2 - select based on trigger selection string (that's pretty bad)
  // 3 - select based on RunId. That's pretty good, but I prefer
  // 4 - select assuming that RefmultCorr is better than gRefmult is better than refmult.
  //     Let's use 4.
  
  Double_t ret; 
  ret=GetCorrectedReferenceMultiplicity();
  if ( fabs(ret)>1e-6 ){

    return ret;
  }

  ret=GetGReferenceMultiplicity();
  if ( fabs(ret)>1e-6 ) {
    __DEBUG(1, "Using GRefMult");
    return ret;
  }
 
  __DEBUG(1, "Using RefMult");
  return GetReferenceMultiplicity();
  
}

