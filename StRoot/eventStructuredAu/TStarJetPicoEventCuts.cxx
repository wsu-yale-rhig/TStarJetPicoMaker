#include "TStarJetPicoEventCuts.h"
#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoDefinitions.h"
#include "TMath.h"
#include "TChain.h"

/////////////////////////////////////////////////////////////////////////
//                                                                     //
// TStarJetPicoEventCuts                                               //
//                                                                     //
// Default cuts implemented.                                           //
// Lots of virtual functions... so overload in derived classes and     //
// pass to TStarJetPicoReader via TStarJetPicoReader::SetEventCuts     //
// TStarJetPicoReader calls IsEventOK.                                 //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoEventCuts)

TStarJetPicoEventCuts::TStarJetPicoEventCuts()
  : TObject()
  , fTrigSel("All")
  , fVzCut(50.)
  , fVzDiffCut(6.)
  , fRefMultCutMin(0)
  , fRefMultCutMax(99999)
  , fRefCentCutMin(0)
  , fRefCentCutMax(8)
  , fBbceCutMin(0)
  , fBbceCutMax(99999)
  , fPVRankingCut(-10.) 
  , fFlagPVRankingCut(kFALSE) //reasonable value of PV Ranking Cut depends on PV finder & dataset used -> off by default!
  , fMaxEventPt ( 99999 )
  , fMaxEventEt ( 99999 )
  , fMinEventEt( -1 ) // software HT trigger
  , fUseRawForMinEventEtCut( true ) 
{
  __DEBUG(2, "Creating event cuts with default values.");
}

TStarJetPicoEventCuts::TStarJetPicoEventCuts(const TStarJetPicoEventCuts &t)
  : TObject(t)
  , fTrigSel(t.fTrigSel)
  , fVzCut(t.fVzCut)
  , fVzDiffCut(t.fVzDiffCut)
  , fRefMultCutMin(t.fRefMultCutMin)
  , fRefMultCutMax(t.fRefMultCutMax)
  , fRefCentCutMin(t.fRefCentCutMin)
  , fRefCentCutMax(t.fRefCentCutMax)
  , fBbceCutMin(t.fBbceCutMin)
  , fBbceCutMax(t.fBbceCutMax)
  , fPVRankingCut(t.fPVRankingCut)
  , fFlagPVRankingCut(t.fFlagPVRankingCut)
  , fMaxEventPt( t.fMaxEventPt )
  , fMaxEventEt( t.fMaxEventEt )
  , fMinEventEt( t.fMinEventEt )
  , fUseRawForMinEventEtCut( t.fUseRawForMinEventEtCut )

{
  __DEBUG(2, "Copy event cuts.");  
}

Bool_t TStarJetPicoEventCuts::IsTriggerIdOK(Int_t mTrigId)
{
  // ORDER IS IMPORTANT!
  // Scanning a string here, so check and completely evaluate things like
  // Contains("HT3") before Contains("HT")
  __DEBUG(2, Form("mTrigId = %d TrigSel = %s", mTrigId, fTrigSel.Data()));

  //  -------------------- Run 14 HT3
  if (fTrigSel.Contains("HT3") && !fTrigSel.Contains("pp")){
    if ( mTrigId==450203 || mTrigId==450213 ) { // HT3*VPDMB-30 
      __DEBUG(2, "HT3, Trigger for Au+Au  run 14 ok");
      return kTRUE;
    } else {
      __DEBUG(2, "HT3, Trigger for Au+Au  run 14 NOT ok");
      return kFALSE;
    }
  }
  //  -------------------- Run 14 HT2
  if (fTrigSel.Contains("HT2") && !fTrigSel.Contains("pp")){
    if ( mTrigId==450202 || mTrigId==450212 ) { // HT3*VPDMB-30 
      __DEBUG(2, "HT2, Trigger for Au+Au  run 14 ok");
      return kTRUE;
    } else {
      __DEBUG(2, "HT2, Trigger for Au+Au  run 14 NOT ok");
      return kFALSE;
    }
  }
  
  if (fTrigSel.Contains("pp"))
    {
      // include different pp triggers, MB,HT and JP ...
      if (fTrigSel.Contains("ppHT"))
	{
	  if (mTrigId==117211 || mTrigId==117212 || 
	      mTrigId==127212 || mTrigId==127213 || 
	      mTrigId==137213)
	    {
	      __DEBUG(2, "HT Trigger p+p events selected");
	      return kTRUE;
	    }
	  else if (mTrigId==240530 || mTrigId==240540 || mTrigId==240550 || mTrigId==240560 ||
		   mTrigId==240570)
	    {
	      __DEBUG(2, "HT Trigger p+p events run 9 selected");
	      return kTRUE;
	    }
	  else if (mTrigId==370541 || mTrigId==370542 || mTrigId==370351 )		// BHT0*BBCMB*TOF0, BHT0*BBCMB*TOF0, MTD*BHT3
	    {
	      __DEBUG(2, "HT Trigger p+p events run 12 selected");
	      return kTRUE;
	    }
	  else 
	    {
	      __DEBUG(2, "Reject ppHT trigger.");
	      return kFALSE;
	    }
	}
      else if (fTrigSel.Contains("ppJP"))
	{
	  if (fTrigSel.Contains("ppJP2")) {					// test
	    if (mTrigId==370621)		//  JP2				// test
	      {								// test
		__DEBUG(2, "JP2 Trigger p+p events run 12 selected");		// test
		return kTRUE;							// test
	      }								// test
	    else return kFALSE;						// test
	  }									// test
	  else if (mTrigId==117221 || mTrigId==127221 || 
		   mTrigId==137221 || mTrigId==137222)
	    {
	      __DEBUG(2,"JP Trigger p+p events selected"); 
	      return kTRUE;
	    }
	  else if (mTrigId==240410 || mTrigId==240411 || mTrigId==240650 || mTrigId==240651 ||
		   mTrigId==240652)
	    {
	      __DEBUG(2, "JP Trigger p+p events run 9 selected");
	      return kTRUE;
	    }
	  else if (mTrigId==370601 || mTrigId==370611 || mTrigId==370621)		// JP0, JP1, JP2
	    {
	      __DEBUG(2, "JP Trigger p+p events run 12 selected");
	      return kTRUE;
	    }
	  else
	    return kFALSE;
	}
      else if (fTrigSel.Contains("ppMB"))
	{
	  if (mTrigId==370011)
	    {
	      __DEBUG(2,"MB Trigger p+p events run 12 selected"); 
	      return kTRUE;
	    }
	  else
	    return kFALSE;
	}	
      else if (fTrigSel.Contains("ppHM"))
	{
	  if (mTrigId==370341)
	    {
	      __DEBUG(2,"High-multiplicity Trigger p+p events run 12 selected"); 
	      return kTRUE;
	    }
	}
      else
	{
	  __DEBUG(2, "Reject pp trigger.");
	  return kFALSE;
	}
    } //pp selection

  if (fTrigSel.Contains("HT") && !fTrigSel.Contains("pp"))
    {
      if (mTrigId==200620 || mTrigId==200621 || mTrigId==200211 || 
	  mTrigId==200212 || mTrigId==200220 || mTrigId==200221 || 
	  mTrigId==200222)
	{
	  __DEBUG(2, "HT trigger for Au+Au ok.");
	  return kTRUE;
	}
        else if (mTrigId==260504 || mTrigId==260514 || mTrigId==260524)
	{
	  __DEBUG(2, "HT Trigger for Au+Au  run 10 ok");
	  return kTRUE;
	}
        else if (mTrigId==350512 || mTrigId==350502 || // NPE15
		 mTrigId==350513 || mTrigId==350503 || // NPE18
		 mTrigId==350514 || mTrigId==350504 ) // NPE25
	{
	  __DEBUG(2, "HT Trigger for Au+Au  run 11 ok");
	  return kTRUE;
	}
        else if (mTrigId==450201 || mTrigId==450211 || // HT1*VPDMB-30
		 mTrigId==450202 || mTrigId==450212 || // HT2*VPDMB-30
		 mTrigId==450203 || mTrigId==450213 )  // HT3*VPDMB-30
	{
	  __DEBUG(2, "HT1, HT2, HT3, Trigger for Au+Au  run 14 ok");
	  return kTRUE;
	}

	else
	{
	  __DEBUG(2, "Reject HT trigger for Au+Au.");
	  return kFALSE;	
	}
    } // auau HT

   if (fTrigSel.Contains("MB") && !fTrigSel.Contains("pp"))
     {
      if (mTrigId==200001 || mTrigId==200003 || mTrigId==200013)
	{
	  __DEBUG(2, "Accept MB trigger for Au+Au.");
	  return kTRUE;
	}
      else if (mTrigId==200001 || mTrigId==200003 || mTrigId==200013)
	{
	  __DEBUG(2, "Accept MB trigger for Au+Au run 11.");
	  return kTRUE;	  
	}
      else
	{
	  __DEBUG(2, "Reject MB trigger for Au+Au.");
	  return kFALSE;
	}
     } // auau mb
   
   if (fTrigSel.Contains("wide") && !fTrigSel.Contains("pp"))
     {
       if (mTrigId==320000 || mTrigId==320001 || mTrigId==320011 || mTrigId==320021)
	 {
	   __DEBUG(1, "Accept MB trigger for Au+Au.");
	  return kTRUE;
	 } 
       else
	 {
	   __DEBUG(2, "Reject MB trigger for Au+Au.");
	   return kFALSE;
	 }
     } // auau mb, wide vz cut
   
   
   // dAu year 2008, triggersel options: dAu_mb,dAu_ht_all,dAu_ht0,dAu_ht1,dAu_ht2,dAu_ht4
   if (fTrigSel.Contains("dAu_mb")) {
     if (mTrigId==210020) {
       __DEBUG(2, "dAu_mb trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("dAu_ht_all")) {
     if (mTrigId==210500 || mTrigId==210501 || mTrigId==210510 || mTrigId==210511 || mTrigId==210520 || mTrigId==210521 || mTrigId==210541) {
       __DEBUG(2, "dAu_ht_all trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("dAu_ht0")) {
     if (mTrigId==210500 || mTrigId==210501) {
       __DEBUG(2, "dAu_ht0 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("dAu_ht1")) {
     if (mTrigId==210510 || mTrigId==210511) {
       __DEBUG(2, "dAu_ht1 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("dAu_ht2")) {
     if (mTrigId==210520 || mTrigId==210521) {
       __DEBUG(2, "dAu_ht2 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("dAu_ht4")) {
     if (mTrigId==210541) {
       __DEBUG(2, "dAu_ht4 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }


   // p+p year8 trigger selection: y8p+p_ht0,y8p+p_ht1,y8p+p_ht2,y8p+p_mb
   if (fTrigSel.Contains("y8p+p_ht0")) {
     if (mTrigId==220500) {
       __DEBUG(2, "y8p+p_ht0 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("y8p+p_ht1")) {
     if (mTrigId==220510) {
       __DEBUG(2, "y8p+p_ht1 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }
   if (fTrigSel.Contains("y8p+p_ht2")) {
     if (mTrigId==220520) {
       __DEBUG(2, "y8p+p_ht2 trigger ok.");
       return kTRUE;
     } else {
       return kFALSE;
     }
   }

   if (fTrigSel.Contains("y8p+p_mb")) {
 	if (mTrigId==220000) {
 	__DEBUG(2, "y8p+p_mb trigger ok.");
 	return kTRUE;
        } else {
 	return kFALSE;
 	}
    }    
 
   if (fTrigSel.Contains("y4mb")) {
 	if (mTrigId==15007) {
 	__DEBUG(2, "y4mb trigger ok.");
 	return kTRUE;
        } else {
 	return kFALSE;
 	}
    }   

   __WARNING(Form("Unrecognized trigger selection! %s", fTrigSel.Data()));
   
   return kFALSE;
}

Bool_t TStarJetPicoEventCuts::IsTriggerIdOK(TStarJetPicoEvent *mEv)
{
  Bool_t retval = kFALSE;
  if (fTrigSel.Contains("All") || fTrigSel.Contains("all") )
    {
      __DEBUG(2, "All events taken, no Trigger selection"); 
      return kTRUE;
    }

  for (Int_t id = 0; id < mEv->GetHeader()->GetNOfTriggerIds(); id++)
    {
      Int_t TrigId = mEv->GetHeader()->GetTriggerId(id);
      if ( IsTriggerIdOK(TrigId) == kTRUE )
	{
	  retval = kTRUE;
	  break;
	}
    }

  if ( !retval ) __DEBUG(1, Form("Reject. No suitable trigger.") );
  return retval;
}

Bool_t TStarJetPicoEventCuts::IsVertexZDiffOK(TStarJetPicoEvent *mEv)
{
Float_t Vz    =mEv->GetHeader()->GetPrimaryVertexZ();
Float_t VpdVz =mEv->GetHeader()->GetVpdVz();

if(TMath::Abs(Vz-VpdVz)<fVzDiffCut)
  {
   __DEBUG(1,Form("Accept. %f<%f",TMath::Abs(Vz-VpdVz),fVzDiffCut));
   return kTRUE;
  }

 __DEBUG(1,Form("Reject. %f<%f",TMath::Abs(Vz-VpdVz),fVzDiffCut));
 return kFALSE;

}

Int_t TStarJetPicoEventCuts::GetReferenceMultiplicity(TStarJetPicoEvent *mEv)
{
  __ERROR ( "Deprecated, don't use");
  throw (-1);

  Int_t RefMult = mEv->GetHeader()->GetReferenceMultiplicity();
  if ((fTrigSel.Contains("HT") || fTrigSel.Contains("MB")) &&
      (!fTrigSel.Contains("pp")) )
    {
      __DEBUG(1, Form("Switching to GRefMult cut for AuAu data. Trigger is %s",
		      fTrigSel.Data()));
      RefMult = mEv->GetHeader()->GetGReferenceMultiplicity();
    }
  return RefMult;
}

Bool_t TStarJetPicoEventCuts::IsRefMultOK(TStarJetPicoEvent *mEv )
{
  // KK: Simplified
  Double_t RefMult = mEv->GetHeader()->GetProperReferenceMultiplicity();

  // Int_t RefMult = mEv->GetHeader()->GetReferenceMultiplicity();
  // Int_t run     = mEv->GetHeader()->GetRunId();
  // if(run < 11002120 || run > 11147025)//exclude Run 10 AuAu all energies
  //  if ((fTrigSel.Contains("HT") || fTrigSel.Contains("MB")) &&
  //      (!fTrigSel.Contains("pp")) )
  //    {
  //      __DEBUG(1, Form("Switching to GRefMult cut for AuAu data. Trigger is %s",
  // 		      fTrigSel.Data()));
  //      RefMult = mEv->GetHeader()->GetGReferenceMultiplicity();
  //    }
    
  //   TString triggerSel = fTrigSel;
  //   triggerSel.ToUpper();
    
  //   //nick elsey: overriding this for run 11: using CorRefMult if its present
  //   if ( ( ( (run-run%1000000)/1000000 ) == 12 ) && fInputTree->FindLeaf("fEventHeader.fCorRefMult") ) {
  //       if ( triggerSel.Contains("HT") || triggerSel.Contains("MB") || triggerSel.Contains("ALL") ) {
  //           RefMult = mEv->GetHeader()->GetCorrectedReferenceMultiplicity();
  //       __DEBUG(1, Form("Switching to CorRefMult cut for y11 data. Trigger is %s",
  //                       triggerSel.Data()));
  //       }
  //   }

  if (( RefMult > fRefMultCutMin) &&
      ( RefMult < fRefMultCutMax) )
    {
      __DEBUG(1, Form("Accept. %d < %.1f < %d", 
		      fRefMultCutMin, RefMult, fRefMultCutMax));
      return kTRUE;
    }  
  
  __DEBUG(1, Form("Reject. %d < %.1f < %d", 
		  fRefMultCutMin, RefMult, fRefMultCutMax));
  return kFALSE;  
}

Bool_t TStarJetPicoEventCuts::IsRefCentOK(TStarJetPicoEvent *mEv, TChain *fInputTree)
{
    if (fRefCentCutMin == 0 && fRefCentCutMax == 8) {
        __DEBUG(1, Form("No Reference Centrality selected. "));
        return kTRUE;
    }
    if ( !fInputTree->FindLeaf("fEventHeader.fRefCent") ) {
        __ERROR("Reference centrality cut defined, but the leaf wasn't found. ")
        return kFALSE;
    }
    Int_t refCent = mEv->GetHeader()->GetReferenceCentrality();
    if ( (refCent >= fRefCentCutMin) && (refCent <= fRefCentCutMax) ) {
      __DEBUG(1, Form("Accept. %d < %d < %d",
		      fRefCentCutMin, refCent, fRefCentCutMax));
      return kTRUE;
    }
    __DEBUG(1, Form("Reject. %d < %d < %d",
                    fRefCentCutMin, refCent, fRefCentCutMax));
    return kFALSE;
}

Bool_t TStarJetPicoEventCuts::IsVertexZOK(TStarJetPicoEvent *mEv)
{
  Float_t Vz    = mEv->GetHeader()->GetPrimaryVertexZ();
  
  if ( TMath::Abs(Vz) < fVzCut )
    {
      __DEBUG(1, Form("Accept. %f < %f", TMath::Abs(Vz), fVzCut));
      return kTRUE;
    }

  __DEBUG(1, Form("Reject. %f < %f", TMath::Abs(Vz), fVzCut));
  return kFALSE;
}


Bool_t TStarJetPicoEventCuts::IsPVRankingOK(TStarJetPicoEvent *mEv)
{
  Float_t ranking = mEv->GetHeader()->GetPrimaryVertexRanking();
  if (ranking>fPVRankingCut){
    __DEBUG(1, Form("Accept. %f > %f",ranking,fPVRankingCut));
    return kTRUE;
  }

  __DEBUG(1, Form("Reject. ! %f > %f",ranking,fPVRankingCut));
  return kFALSE;
}


Bool_t TStarJetPicoEventCuts::IsBbceOK(TStarJetPicoEvent *mEv)
{
  Int_t Bbce = mEv->GetHeader()->GetBbcAdcSumEast();

  if (( Bbce > fBbceCutMin) &&
      ( Bbce < fBbceCutMax) )
    {
      __DEBUG(1, Form("Accept. %d < %d < %d", 
		      fBbceCutMin, Bbce, fBbceCutMax));
      return kTRUE;
    }  
  
  __DEBUG(1, Form("Reject. ! %d < %d < %d", 
		  fBbceCutMin, Bbce, fBbceCutMax));
  return kFALSE;  
}


Bool_t TStarJetPicoEventCuts::IsScalersOK(TStarJetPicoEvent *mEv)
{
  Bool_t retval=kTRUE;

  //taken from StRoot/StMuAnalysisMaker/StMuScalerCutter.cxx, version 1.1
  Int_t run = mEv->GetHeader()->GetRunId();
  Float_t zdce = mEv->GetHeader()->GetZdcEastRate();
  Float_t zdcw = mEv->GetHeader()->GetZdcWestRate();
  Float_t zdcx = mEv->GetHeader()->GetZdcCoincidenceRate();
  Float_t bbcw = mEv->GetHeader()->GetBbcWestRate();
  Float_t bbcx = mEv->GetHeader()->GetBbcCoincidenceRate();
  Float_t bbcbb = mEv->GetHeader()->GetBbcBlueBackgroundRate();

  // zdcx check
  if (zdcx/bbcx > 0.42 || zdcx/zdcw > 0.35) retval=kFALSE;
    
  // zdce check
  if (run > 8361110 && run < 8363032) {
    if (zdce/bbcx > 2.9 ||
	zdce/zdcw > 1.8) retval=kFALSE;
  } else {
    if (zdce/bbcx > 1.9 ||
	zdce/zdcw > 1.8) retval=kFALSE;
  }

  // bbcbb check (for 1-second scalers)
  Double_t R1 = 1.4923e-3*TMath::Power(zdcw,-2.57818)*TMath::Power(bbcw,3.6488);
  Double_t R2 = bbcbb/R1;
  if ( ( R2 > 0.2 && R2 < 0.72 ) ||
       ( R2 > 1.4 && R2 < 4.6  )   ) retval=kFALSE;
  
  if (retval==kTRUE) {
    __DEBUG(1, Form("Accept. Corrupt scalers cut ok."));
    return kTRUE;
  }

  __DEBUG(1, Form("Reject. Corrupt scalers cut NOT ok."));
  return kFALSE;
}


Bool_t TStarJetPicoEventCuts::CheckEvent(TStarJetPicoEvent *mEv, TChain *fInputTree)
{
  return IsEventOK(mEv, fInputTree);
}

Bool_t TStarJetPicoEventCuts::IsEventOK(TStarJetPicoEvent *mEv, TChain *fInputTree)
{
  Bool_t retval;
  retval = (IsRefMultOK(mEv) && IsRefCentOK(mEv, fInputTree) && IsVertexZOK(mEv) && IsTriggerIdOK(mEv) && (fFlagPVRankingCut==kFALSE || IsPVRankingOK(mEv)) );
  
  //cuts for dAu2008
  Int_t run = mEv->GetHeader()->GetRunId();
  if (run > 8313000 && run < 9029000) { // Run 8 dAu cuts
    if (IsBbceOK(mEv)==kFALSE)
      retval = kFALSE;
    if (IsScalersOK(mEv)==kFALSE)
      retval = kFALSE;
  }
  //extra vzVPD-vzTPC cut for Run9 & 10, pp and AuAu
  if(run > 10085112 && run < 11147025){
    if(IsVertexZDiffOK(mEv)==kFALSE)
       retval = kFALSE;
   }
  return retval;
}

Bool_t TStarJetPicoEventCuts::IsHighestPtOK( Float_t mPt )
{
  if ( mPt>fMaxEventPt ) {
    __DEBUG(1,Form("Reject. %f>%f",mPt,fMaxEventPt));
    return kFALSE;
  }

  __DEBUG(6,Form("Accept. %f<%f",mPt,fMaxEventPt));
  return kTRUE;
}

Bool_t TStarJetPicoEventCuts::IsHighestEtOK( Float_t mEt )
{
  if ( mEt>fMaxEventEt ) {
    __DEBUG(1,Form("Reject. %f>%f",mEt,fMaxEventEt));
    return kFALSE;
  }
  
  __DEBUG(6,Form("Accept. %f<%f",mEt,fMaxEventEt));
  return kTRUE;
}

Bool_t TStarJetPicoEventCuts::IsHighTowerOk( Float_t mEt )
{
  if ( fMinEventEt > 0 && mEt<fMinEventEt ) {
    __DEBUG(1,Form("Reject. High tower %f<%f",mEt,fMinEventEt));
    return kFALSE;
  }

  __DEBUG(6,Form("Accept. High tower %f>%f",mEt,fMinEventEt));
  return kTRUE;
}


Bool_t TStarJetPicoEventCuts::SetReferenceCentralityCut(Int_t min, Int_t max)
{
    if (min > max) {
        __ERROR("Reference centrality minimum set greater than maximum. Using Defaults.");
        return kFALSE;
    }
    if (min < 0) {
        __ERROR("Reference centrality minimum set less than zero. Using Defaults");
        return kFALSE;
    }
    if (max > 8) {
        __ERROR("Reference centrality minimum set greater than eight. Using Defaults.");
        return kFALSE;
    }
    
    fRefCentCutMax = max;
    fRefCentCutMin = min;
    return kTRUE;
    
}

