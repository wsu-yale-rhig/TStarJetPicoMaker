#include "TStarJetPicoV0Cuts.h"

#include "TStarJetPicoV0.h"
#include "TStarJetPicoDefinitions.h"

#include <TMath.h>

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// TStarJetPicoV0Cuts                                                  //
//                                                                     //
// Default cuts implemented.                                           //
// Lots of virtual functions... so overload in derived classes and     //
// pass to TStarJetPicoReader via TStarJetPicoReader::SetV0Cuts        //
// TStarJetPicoReader::LoadV0s() calls ::DoXXXPID() methods.           //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoV0Cuts)

TStarJetPicoV0Cuts::TStarJetPicoV0Cuts()
  : TObject()
  , fLambdaMassRange(0.05)
  , fLambdaDcapn(999.) // < cut
  , fLambdaDcaV0(999.) // < cut
  , fLambdaDcaPos(0.)// > cut
  , fLambdaDcaNeg(0.) // > cut
  , fLambdaDecayLength(0.) // > cut
  , fLambdaNSigmaPos(999.) // < cut
  , fLambdaNSigmaNeg(999.)  // < cut

  , fAntiLambdaMassRange(0.05)
  , fAntiLambdaDcapn(999.) // < cut
  , fAntiLambdaDcaV0(999.) // < cut
  , fAntiLambdaDcaPos(0.)// > cut
  , fAntiLambdaDcaNeg(0.) // > cut
  , fAntiLambdaDecayLength(0.) // > cut
  , fAntiLambdaNSigmaPos(999.) // < cut
  , fAntiLambdaNSigmaNeg(999.)  // < cut

  , fK0sMassRange(0.05)
  , fK0sDcapn(999.) // < cut
  , fK0sDcaV0(999.) // < cut
  , fK0sDcaPos(0.)// > cut
  , fK0sDcaNeg(0.) // > cut
  , fK0sDecayLength(0.) // > cut
  , fK0sNSigmaPos(999.) // < cut
  , fK0sNSigmaNeg(999.)  // < cut

  , fK0Mass(__STARJETPICO_MASS_K0)
  , fLambdaMass(__STARJETPICO_MASS_LAMBDA)

  , fAcceptLambdas(kTRUE)
  , fAcceptAntiLambdas(kTRUE)
  , fAcceptK0s(kTRUE)
{
  __DEBUG(2, "Creating V0 cuts with default values.");
}

TStarJetPicoV0Cuts::TStarJetPicoV0Cuts(const TStarJetPicoV0Cuts &t)
  : TObject(t)
  , fLambdaMassRange(t.fLambdaMassRange)
  , fLambdaDcapn(t.fLambdaDcapn) // < cut
  , fLambdaDcaV0(t.fLambdaDcaV0) // < cut
  , fLambdaDcaPos(t.fLambdaDcaPos)// > cut
  , fLambdaDcaNeg(t.fLambdaDcaNeg) // > cut
  , fLambdaDecayLength(t.fLambdaDecayLength) // > cut
  , fLambdaNSigmaPos(t.fLambdaNSigmaPos) // < cut
  , fLambdaNSigmaNeg(t.fLambdaNSigmaNeg)  // < cut

  , fAntiLambdaMassRange(t.fAntiLambdaMassRange)
  , fAntiLambdaDcapn(t.fAntiLambdaDcapn) // < cut
  , fAntiLambdaDcaV0(t.fAntiLambdaDcaV0) // < cut
  , fAntiLambdaDcaPos(t.fAntiLambdaDcaPos)// > cut
  , fAntiLambdaDcaNeg(t.fAntiLambdaDcaNeg) // > cut
  , fAntiLambdaDecayLength(t.fAntiLambdaDecayLength) // > cut
  , fAntiLambdaNSigmaPos(t.fAntiLambdaNSigmaPos) // < cut
  , fAntiLambdaNSigmaNeg(t.fAntiLambdaNSigmaNeg)  // < cut

  , fK0sMassRange(t.fK0sMassRange)
  , fK0sDcapn(t.fK0sDcapn) // < cut
  , fK0sDcaV0(t.fK0sDcaV0) // < cut
  , fK0sDcaPos(t.fK0sDcaPos)// > cut
  , fK0sDcaNeg(t.fK0sDcaNeg) // > cut
  , fK0sDecayLength(t.fK0sDecayLength) // > cut
  , fK0sNSigmaPos(t.fK0sNSigmaPos) // < cut
  , fK0sNSigmaNeg(t.fK0sNSigmaNeg)  // < cut

  , fK0Mass(t.fK0Mass)
  , fLambdaMass(t.fLambdaMass)

  , fAcceptLambdas(kTRUE)
  , fAcceptAntiLambdas(kTRUE)
  , fAcceptK0s(kTRUE)
{
  __DEBUG(2, "Copy V0 cuts.");
}

Int_t TStarJetPicoV0Cuts::DoLambdaPID(TStarJetPicoV0 *mv0)
{
  // Reject cases where it could be Lambda OR K0s

  if( mv0->GetMassLambda() > fLambdaMass - fLambdaMassRange && 
      mv0->GetMassLambda() < fLambdaMass + fLambdaMassRange
      &&  (mv0->GetMassK0s() < fK0Mass - fK0sMassRange || 
	   mv0->GetMassK0s() > fK0Mass + fK0sMassRange))
    {
      if(mv0->GetDcapn() > fLambdaDcapn) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaV0() > fLambdaDcaV0) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaPos() < fLambdaDcaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaNeg() < fLambdaDcaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDecayLength() < fLambdaDecayLength) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaProtonPos()) > fLambdaNSigmaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaPionNeg()) > fLambdaNSigmaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;
      
      return __STARJETPICO_LAMBDA_PID;
    }
  
  return __STARJETPICO_FALSE_RETURN_PID;
}

Int_t TStarJetPicoV0Cuts::DoAntiLambdaPID(TStarJetPicoV0 *mv0)
{
  // Reject cases where it could be AntiLambda OR K0s

  if( mv0->GetMassAntiLambda() > fLambdaMass - fAntiLambdaMassRange && 
      mv0->GetMassAntiLambda() < fLambdaMass + fAntiLambdaMassRange
      &&  (mv0->GetMassK0s() < fK0Mass - fK0sMassRange || 
	   mv0->GetMassK0s() > fK0Mass + fK0sMassRange))
    {
      if(mv0->GetDcapn() > fAntiLambdaDcapn) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaV0() > fAntiLambdaDcaV0) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaPos() < fAntiLambdaDcaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaNeg() < fAntiLambdaDcaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDecayLength() < fAntiLambdaDecayLength) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaProtonNeg()) > fAntiLambdaNSigmaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaPionPos()) > fAntiLambdaNSigmaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;
      
      return __STARJETPICO_ANTILAMBDA_PID;
    }
  
  return __STARJETPICO_FALSE_RETURN_PID;
}

Int_t TStarJetPicoV0Cuts::DoK0sPID(TStarJetPicoV0 *mv0)
{
  // Reject cases where it could be (Anti)Lambda OR K0s

  if( mv0->GetMassK0s() > fK0Mass - fK0sMassRange && 
      mv0->GetMassK0s() < fK0Mass + fK0sMassRange
      &&  (mv0->GetMassLambda() < fLambdaMass - fLambdaMassRange || 
	   mv0->GetMassLambda() > fLambdaMass + fLambdaMassRange)
      &&  (mv0->GetMassAntiLambda() < fLambdaMass - fAntiLambdaMassRange || 
	   mv0->GetMassAntiLambda() > fLambdaMass + fAntiLambdaMassRange)
      )
    {
      if(mv0->GetDcapn() > fK0sDcapn) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaV0() > fK0sDcaV0) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaPos() < fK0sDcaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDcaNeg() < fK0sDcaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if(mv0->GetDecayLength() < fK0sDecayLength) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaPionNeg()) > fK0sNSigmaNeg) 
	return __STARJETPICO_FALSE_RETURN_PID;

      if( TMath::Abs(mv0->GetNSigmaPionPos()) > fK0sNSigmaPos) 
	return __STARJETPICO_FALSE_RETURN_PID;
      
      return __STARJETPICO_K0_PID;
    }
  
  return __STARJETPICO_FALSE_RETURN_PID;
}
