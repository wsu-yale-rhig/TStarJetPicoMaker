/*       
    ******** UNSUPPORTED *********
    kept for backward compatibility
 
          TStarJetV0Cuts.hh
   internal class for TStarJetPicoMaker
   defines quality cuts for selection of
   secondary vertices based on the
   daughters & event data
 */

#ifndef TSTARJETV0CUTS__HH
#define TSTARJETV0CUTS__HH

#include "TObject.h"
#include "StMuDSTMaker/COMMON/StMuTypes.hh"
#include "StStrangeMuDstMaker/StV0MuDst.hh"

class TStarJetV0Cuts : public TObject {
  
public:

  TStarJetV0Cuts();
  ~TStarJetV0Cuts();
  
  /* sets default values for the collision species.
     only support AuAu, p+p so far
   */
  void   SetDefaultAuAu();
  void   SetDefaultPP();
  
  /* function used by TStarJetPicoMaker to check the V0
   against cuts
   */
  bool AcceptV0(StMuDst* mu, StV0MuDst *v0);
  
  
  Bool_t SetDCAV0ToVertex(Double_t dca);
  Bool_t SetDCAPosToNeg(Double_t dca);
  Bool_t SetDCAPosToVertex(Double_t dca);
  Bool_t SetDCANegToVertex(Double_t dca);
  Bool_t SetNHitsPos(UInt_t hits);
  Bool_t SetNHitsNeg(UInt_t hits);
  Bool_t SetDecayLength(Double_t len);
  Bool_t SetNSigma(Double_t nsig);
  
  /* print statistics on the number of v0s accepted.
   Called in Finish() of TStarJetPicoMaker
   */
  void  PrintStats();
  
private:
  
  UInt_t    mNV0s;
  UInt_t    mAcceptedV0s;
  
  Double_t   mDCAv0ToVtx;
  Double_t   mDCADaughter;
  Double_t   mDCAPosToVtx;
  Double_t   mDCANegToVtx;
  UInt_t     mHitsPos;
  UInt_t     mHitsNeg;
  Double_t   mDecayLength;
  Double_t   mNSigma;
  
  ClassDef(TStarJetV0Cuts,1)
};

#endif /* TStarJetV0Cuts */
