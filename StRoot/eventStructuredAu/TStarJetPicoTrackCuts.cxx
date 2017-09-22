#include "TStarJetPicoTrackCuts.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoDefinitions.h"

#include <TMath.h>
#include <TString.h>

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// TStarJetPicoTrackCuts                                               //
//                                                                     //
// Default cuts implemented.                                           //
// Lots of virtual functions... so overload in derived classes and     //
// pass to TStarJetPicoReader via TStarJetPicoReader::SetTrackCuts     //
// TStarJetPicoReader::LoadTracks() calls ::IsTrackOK method.          //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoTrackCuts)

TStarJetPicoTrackCuts::TStarJetPicoTrackCuts()
  : TObject()
  , fMaxDCA(1.0)
  , fMinNfit(20)
  , fFitOverMax(0.52)
  , fMaxPt(1000.) // by default, no cut effectively
  , restrictedPhiRanges()
  , fMaxChi2(1000.) // no cut effectively
  , fPCT(kFALSE)
  , fFlagMaxChi2(kFALSE)
{
  __DEBUG(2, "Creating track cuts with default values.");  
}

TStarJetPicoTrackCuts::TStarJetPicoTrackCuts(const TStarJetPicoTrackCuts &t)
  : TObject(t)
  , fMaxDCA(t.fMaxDCA)
  , fMinNfit(t.fMinNfit)
  , fFitOverMax(t.fFitOverMax)
  , fMaxPt(t.fMaxPt)
  , restrictedPhiRanges(t.restrictedPhiRanges)
  , fMaxChi2(t.fMaxChi2)
  , fPCT(t.fPCT)
  , fFlagMaxChi2(t.fFlagMaxChi2)
{
  __DEBUG(2, "Copy track cuts.");  
}

Bool_t TStarJetPicoTrackCuts::IsDCAOK(TStarJetPicoPrimaryTrack *tr)
{
  if (TMath::Abs(tr->GetDCA()) < fMaxDCA)
    {
      __DEBUG(9, Form("Accept. %f < %f", TMath::Abs(tr->GetDCA()), fMaxDCA));
      return kTRUE; 
    }

  __DEBUG(9, Form("Reject. ! %f < %f", TMath::Abs(tr->GetDCA()), fMaxDCA));
  return kFALSE;
}

Bool_t TStarJetPicoTrackCuts::IsMinNFitPointsOK(TStarJetPicoPrimaryTrack *tr)
{
  if (tr->GetNOfFittedHits() > fMinNfit)
    {
      __DEBUG(9, Form("Accept. %d > %d", tr->GetNOfFittedHits(), fMinNfit));
      return kTRUE;
    }

  __DEBUG(9, Form("Reject. ! %d > %d", tr->GetNOfFittedHits(), fMinNfit));
  return kFALSE;
}

Bool_t TStarJetPicoTrackCuts::IsFitOverMaxPointsOK(TStarJetPicoPrimaryTrack *tr)
{
  Double_t ratio = 1.;
  ratio = (ratio * tr->GetNOfFittedHits()) / (ratio * tr->GetNOfPossHits());

  if (ratio > fFitOverMax)
    {
      __DEBUG(9, Form("Accept. %f > %f", ratio, fFitOverMax));
      return kTRUE;
    }
  
  __DEBUG(9, Form("Reject. ! %f > %f", ratio, fFitOverMax));
  return kFALSE;
}

Bool_t TStarJetPicoTrackCuts::IsMaxPtOK(TStarJetPicoPrimaryTrack *tr)
{
  Double_t pt = TMath::Sqrt(tr->GetPx()*tr->GetPx() + tr->GetPy()*tr->GetPy());;
  if (pt < fMaxPt)
    {
      __DEBUG(9, Form("Accept. %f < %f", pt, fMaxPt));
      return kTRUE;
    }
  
  __DEBUG(9, Form("Reject. ! %f < %f", pt, fMaxPt));
  return kFALSE;
}

Bool_t  TStarJetPicoTrackCuts::IsChi2OK(TStarJetPicoPrimaryTrack *tr) {
  if (fFlagMaxChi2==kTRUE) {
    Float_t chi2 = tr->GetChi2PV();
    if (chi2<fMaxChi2) {
      __DEBUG(9, Form("Accept. %f < %f", chi2, fMaxChi2));
      return kTRUE;
    } 
    
    __DEBUG(9, Form("Reject. ! %f < %f",chi2, fMaxChi2));
    return kFALSE;
  }
  else {
    __DEBUG(9, Form("Accept. Not checking chi2 cut!"));
    return kTRUE;
  }
}


Bool_t  TStarJetPicoTrackCuts::IsPCTOK(TStarJetPicoPrimaryTrack *tr) {
  if (fPCT==kTRUE) {
    Int_t flag=tr->GetFlag();
    if (flag<1000) {
      __DEBUG(9, Form("Accept. Track flag < 1000"));
      return kTRUE;
    }

    __DEBUG(9, Form("Reject. Track flag >=1000: PCT track!"));
    return kFALSE;
  }
  else {
    __DEBUG(9, Form("Accept. Track flag not checked."));
    return kTRUE;
  }
}

Bool_t TStarJetPicoTrackCuts::IsPhiOK(TStarJetPicoPrimaryTrack *tr) {
    Double_t phi = tr->GetPhi();
    Double_t min=0, max=0;
    for (unsigned i = 0; i < restrictedPhiRanges.size(); ++i) {
        min = restrictedPhiRanges[i][0];
        max = restrictedPhiRanges[i][1];
        if ( phi >= min && phi <= max ) {
            __DEBUG(9, Form("Reject. %f < %f < %f", min, phi, max) );
            return kFALSE;
        }
    }
    __DEBUG(9, Form("Accept. ! %f < %f < %f", min, phi, max) );
    return kTRUE;
}

Bool_t TStarJetPicoTrackCuts::IsTrackOK(TStarJetPicoPrimaryTrack *tr)
{
  return IsDCAOK(tr) && IsMinNFitPointsOK(tr) && IsFitOverMaxPointsOK(tr) && IsMaxPtOK(tr) && IsChi2OK(tr) && IsPCTOK(tr) && IsPhiOK(tr);
}

Bool_t TStarJetPicoTrackCuts::CheckTrackQA(TStarJetPicoPrimaryTrack *tr)
{
  return IsTrackOK(tr);
}

Bool_t TStarJetPicoTrackCuts::RestrictPhiRange(Double_t min, Double_t max)
{
    // nick elsey: mapping any phi region defined on [-pi, pi], or [0, 2*pi]
    // onto a linear sequence of regions that can be used by IsPhiOk()
    // returns false if the input is defined on [-2*pi, 0], etc
    
    double pi = TMath::Pi();
    //for pairs defined on [-pi, pi]
    if ( min >= -pi && min < pi && max <= pi && max > -pi ) {
        if ( min < max ) {
            AddPhiCut( min, max );
            return kTRUE;
        }
        else if ( min > max ) {
            AddPhiCut( -pi, max );
            AddPhiCut( min, pi );
            return kTRUE;
        }
        else {
            __ERROR( Form("Error: phiMin is equal to phiMax: ambiguous.") );
            return kFALSE;
        }
    }
    else if (min >= 0.0 && min < 2.0*pi && max > 0.0 && max <= 2.0*pi ) {
        if ( min <= pi && max > pi ) {
            AddPhiCut( -pi, max - 2.0*pi );
            AddPhiCut( min, pi );
            return kTRUE;
        }
        else if ( min > pi && max <= pi ) {
            AddPhiCut( min - 2.0*pi, max );
            return kTRUE;
        }
        else if (min >= pi && max >= pi ) {
            if ( min > max ) {
                AddPhiCut( min - 2.0*pi, pi );
                AddPhiCut( -pi, max - 2.0*pi );
                return kTRUE;
            }
            else if ( min < max ) {
                AddPhiCut( min - 2.0*pi, max - 2.0*pi );
                return kTRUE;
            }
        }
        else {
            __ERROR(Form("Error: Couldn't convert phiMin and PhiMax.") );
            return kFALSE;
        }
    }
    else {
        __ERROR( Form("Error: Unrecognized Phi definition.") );
        return kFALSE;
    }
    return kFALSE;
}

Bool_t TStarJetPicoTrackCuts::AddPhiCut(Double_t min, Double_t max) {
    if (!(min >= -TMath::Pi() && min <= TMath::Pi() && max >= -TMath::Pi() && max <= TMath::Pi() )){
        __ERROR(Form("Internal conversion error, apologies") );
        return kFALSE;
    }
    std::vector<double> temp;
    temp.push_back( min );
    temp.push_back( max );
    restrictedPhiRanges.push_back( temp );
    return kTRUE;
}
