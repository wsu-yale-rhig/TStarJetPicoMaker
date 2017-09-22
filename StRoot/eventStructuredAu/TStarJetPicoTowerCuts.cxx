#include "TStarJetPicoTowerCuts.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoEvent.h"
#include "TStarJetPicoUtils.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoTrackCuts.h"
#include "TStarJetPicoDefinitions.h"
#include <TString.h>
#include <TMath.h>

#include <sstream>
#include <fstream>


/////////////////////////////////////////////////////////////////////////
//                                                                     //
// TStarJetPicoTowerCuts                                               //
//                                                                     //
// Default cuts implemented.                                           //
// Lots of virtual functions... so overload in derived classes and     //
// pass to TStarJetPicoReader via TStarJetPicoReader::SetTrackCuts     //
// TStarJetPicoReader::LoadTowers() calls ::IsTowerOK method.          //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoTowerCuts)

TStarJetPicoTowerCuts::TStarJetPicoTowerCuts()
  : TObject()
  , fMaxEt(1000.)// by default, no cut effectively
  , restrictedPhiRanges()
  , y8PythiaCut(kFALSE)
  , useTowerStatus(kTRUE)
{
  __DEBUG(2, "Creating tower cuts with default values.");
}

TStarJetPicoTowerCuts::TStarJetPicoTowerCuts(const TStarJetPicoTowerCuts &t)
  : TObject(t)
  , fMaxEt(t.fMaxEt)
  , restrictedPhiRanges(t.restrictedPhiRanges)
  , y8PythiaCut(t.y8PythiaCut)
{
  __DEBUG(2, "Copy tower cuts.");  
}

// KK: Replacement for IsTowerOK(Int_t mTowId, Int_t mTrigId)
Bool_t TStarJetPicoTowerCuts::IsTowerOK( Int_t mTowId ){
  if ( badTowers.size()==0 ){
    __ERROR("TStarJetPicoTowerCuts::IsTowerOK: WARNING: You're trying to run without a bad tower list. If you know what you're doing, deactivate this throw and recompile.");
    throw ( -1 );
  }
  if ( badTowers.count( mTowId )>0 ){
    __DEBUG(9, Form("Reject. Tower ID: %d", mTowId));
    return false;
  } else {
    __DEBUG(9, Form("Accept. Tower ID: %d", mTowId));
    return true;
  }    
}

Bool_t TStarJetPicoTowerCuts::IsTowerOK(Int_t mTowId, Int_t mTrigId)
{
  __ERROR("TStarJetPicoTowerCuts::IsTowerOK: Deprecated. Don't use.");
  throw ( -1 );
  
  // Orig: MB only!
  // if (   mTrigId == 200001 || mTrigId == 200003 || mTrigId == 200013){
  // KK: Fixed, 08/23/15: Include HT triggers
  if ( mTrigId == 200001 || mTrigId == 200003 || mTrigId == 200013 ||
       mTrigId == 200620 || mTrigId == 200621 || mTrigId == 200211 || mTrigId == 200212 || mTrigId == 200220 || mTrigId == 200221 || mTrigId == 200222
       ) {
    if( mTowId ==    6 || mTowId ==   46 || mTowId ==  124 || mTowId ==  181 || 
	mTowId ==  201 || mTowId ==  301 || mTowId ==  304 || mTowId ==  324 || 
	mTowId ==  403 || mTowId ==  428 || mTowId ==  582 || mTowId ==  585 || 
	mTowId ==  783 || mTowId ==  948 || mTowId == 1041 || mTowId == 1042 || 
	mTowId == 1469 || mTowId == 1569 || mTowId == 1722 || mTowId == 1749 || 
	mTowId == 1827 || mTowId == 1864 || mTowId == 2004 || mTowId == 2031 ||
	mTowId == 2255 || mTowId == 2483 || mTowId == 2505 || mTowId == 2667 || 
	mTowId == 2681 || mTowId == 2781 || mTowId == 2783 || mTowId == 2861 ||
	mTowId == 2883 || mTowId == 2902 || mTowId == 3083 || mTowId == 3105 || 
	mTowId == 3283 || mTowId == 3407 || mTowId == 3671 || mTowId == 3763 ||
	mTowId == 3842 || mTowId == 3902 || mTowId == 3963 || mTowId == 4070 || 
	mTowId == 4264 || mTowId == 4364 || mTowId == 4483 || mTowId == 4562 ||
	mTowId == 4606 || mTowId ==   80 || mTowId ==   95 || mTowId ==  180 || 
	mTowId ==  200 || mTowId ==  308 || mTowId ==  359 || mTowId ==  439 ||
	mTowId ==  509 || mTowId ==  520 || mTowId ==  580 || mTowId ==  591 || 
	mTowId ==  600 || mTowId ==  636 || mTowId ==  640 || mTowId ==  680 ||
	mTowId ==  714 || mTowId ==  740 || mTowId ==  775 || mTowId ==  779 || 
	mTowId ==  800 || mTowId ==  899 || mTowId ==  915 || mTowId ==  920 ||
	mTowId == 1020 || mTowId == 1040 || mTowId == 1130 || mTowId == 1132 || 
	mTowId == 1197 || mTowId == 1257 || mTowId == 1294 || mTowId == 1300 ||
	mTowId == 1319 || mTowId == 1320 || mTowId == 1340 || mTowId == 1348 || 
	mTowId == 1380 || mTowId == 1400 || mTowId == 1460 || mTowId == 1480 ||
	mTowId == 1500 || mTowId == 1537 || mTowId == 1600 || mTowId == 1620 || 
	mTowId == 1760 || mTowId == 1780 || mTowId == 1800 || mTowId == 1820 ||
	mTowId == 1860 || mTowId == 1871 || mTowId == 1899 || mTowId == 1909 || 
	mTowId == 2060 || mTowId == 2079 || mTowId == 2200 || mTowId == 2240 ||
	mTowId == 2294 || mTowId == 2296 || mTowId == 2398 || mTowId == 2420 || 
	mTowId == 2520 || mTowId == 2559 || mTowId == 2560 || mTowId == 2600 ||
	mTowId == 2640 || mTowId == 2740 || mTowId == 2760 || mTowId == 2880 || 
	mTowId == 2980 || mTowId == 3000 || mTowId == 3180 || mTowId == 3200 ||
	mTowId == 3240 || mTowId == 3280 || mTowId == 3359 || mTowId == 3360 || 
	mTowId == 3420 || mTowId == 3460 || mTowId == 3480 || mTowId == 3518 ||
	mTowId == 3540 || mTowId == 3559 || mTowId == 3560 || mTowId == 3711 || 
	mTowId == 3720 || mTowId == 3759 || mTowId == 3760 || mTowId == 3780 ||
	mTowId == 3800 || mTowId == 3840 || mTowId == 3880 || mTowId == 4039 || 
	mTowId == 4119 || mTowId == 4200 || mTowId == 4220 || mTowId == 4260 ||
	mTowId == 4280 || mTowId == 4340 || mTowId == 4380 || mTowId == 4400 || 
	mTowId == 4420 || mTowId == 4460 || mTowId == 4480 || mTowId == 4498 ||
	mTowId == 4500 || mTowId == 4539 || mTowId == 4540 || mTowId == 4600 || 
	mTowId == 4640 || mTowId == 4740) { 
      __DEBUG(9, Form("Reject. Tower ID: %d", mTowId));	    
      return kFALSE;
    } else  {
      __DEBUG(9, Form("Accept. Tower ID: %d", mTowId));	    
      return kTRUE;
    }
  }


  //dAu & pp year8, cuts for new calibration, eta rings 1-19
  else if ( mTrigId==210020 || mTrigId==210500 || mTrigId==210501 || mTrigId==210510 || mTrigId==210511 || mTrigId==210520 || mTrigId==210521 || mTrigId==210541 || mTrigId==220500 || mTrigId==220510 || mTrigId==220520) {
    
    if ( mTowId==66 || mTowId==104 || mTowId==224 || mTowId==269 || mTowId==371 || mTowId==579 || mTowId==636 || mTowId==751 || mTowId==758 || mTowId==759 || mTowId==801 || mTowId==830 || mTowId==835 || mTowId==897 || mTowId==899 || mTowId==972 || mTowId==1045 || mTowId==1075 || mTowId==1130 || mTowId==1131 || mTowId==1132 || mTowId==1144 || mTowId==1156 || mTowId==1173 || mTowId==1179 || mTowId==1187 || mTowId==1197 || mTowId==1204 || mTowId==1233 || mTowId==1274 || mTowId==1306 || mTowId==1310 || mTowId==1312 || mTowId==1387 || mTowId==1388 || mTowId==1394 || mTowId==1510 || mTowId==1524 || mTowId==1721 || mTowId==1748 || mTowId==1759 || mTowId==1871 || mTowId==1904 || mTowId==1984 || mTowId==2037 || mTowId==2063 || mTowId==2066 || mTowId==2103 || mTowId==2162 || mTowId==2171 || mTowId==2192 || mTowId==2290 || mTowId==2299 || mTowId==2366 || mTowId==2459 || mTowId==2512 || mTowId==3094 || mTowId==3407 || mTowId==3423 || mTowId==3692 || mTowId==3838 || mTowId==3861 || mTowId==4013 || mTowId==4047 || mTowId==4273 || mTowId==4364 || mTowId==4422 || mTowId==4498 ) 
    
      {
        __DEBUG(9, Form("Reject. Tower ID: %d", mTowId));
        return kFALSE;
      }
    else
      {
        __DEBUG(9, Form("Accept. Tower ID: %d", mTowId));
        return kTRUE;
      }
  }
  else 
    {
      __DEBUG(9, Form("Accept. Tower ID: %d. TriggerID %d is OK.", mTowId, mTrigId));	    
      return kTRUE;
    }
}

Bool_t TStarJetPicoTowerCuts::IsTowerOK(TStarJetPicoTower *tw, TStarJetPicoEvent *mEv)
{
  Bool_t retval = kTRUE;
  Int_t towerId = tw->GetId();
    
  if ( !IsTowerOK(towerId) ) {
    retval = kFALSE;
  }
  
  // if requested, check tower status
  if ( useTowerStatus && tw->GetTowerStatus() != 1) {
    retval = kFALSE;
    __DEBUG(9, Form("reject: tower status = %u", tw->GetTowerStatus() ));
  }
  else __DEBUG(9, Form("accept: useTowerStatus = %d, tower status = %u", useTowerStatus, tw->GetTowerStatus()  ) );

  for (Int_t id = 0; id < mEv->GetHeader()->GetNOfTriggerIds(); id++){
    Int_t TrigId = mEv->GetHeader()->GetTriggerId(id);    
    if ( TrigId==210020 || TrigId==210500 || TrigId==210501 || 
	 TrigId==210510 || TrigId==210511 || TrigId==210520 || 
	 TrigId==210521 || TrigId==210541 ||
	 TrigId==220500 || TrigId==220510 || TrigId==220520)  {
      __ERROR ( "TStarJetPicoTowerCuts::IsTowerOK: You're trying to run8/run 9 data. You should properly implement an eta cut first." );
      throw ( -1 );
      //cut out two outermost eta rings for dAu 2009, as suggested in emc2 discussion-february 2009
      //and also for p+p year 8!
      // if (TMath::Abs(tw->GetEta())>0.95) {
      // 	retval = kFALSE;
      // 	__DEBUG(9, Form("Reject. In the outermost eta ring!"));
      // 	break;
      // }
    }
  }

  // Eta cuts
  // --------
  Double_t et = tw->GetEnergy()/TMath::CosH(tw->GetEtaCorrected());
  if (et < fMaxEt) {
    __DEBUG(9, Form("Accept. %f < %f", et, fMaxEt));
  } 
  else {
    __DEBUG(9, Form("Reject. ! %f < %f", et, fMaxEt));
    retval = kFALSE;
  }

  Double_t phi = tw->GetPhi();
  Double_t min, max;
  for (unsigned i = 0; i < restrictedPhiRanges.size(); ++i) {
    min = restrictedPhiRanges[i][0];
    max = restrictedPhiRanges[i][1];
    if ( phi >= min && phi <= max ) {
        __DEBUG(9, Form("Reject. %f < %f < %f", min, phi, max) );
        retval = kFALSE;
    }
    else
        __DEBUG(9, Form("Accept. ! %f < %f < %f", min, phi, max) );
  }

  
  return retval;
}

Bool_t TStarJetPicoTowerCuts::CheckTowerQA(TStarJetPicoTower *tw, TStarJetPicoEvent *mEv){
  return IsTowerOK(tw, mEv);
}

// KK: Clear bad tower list
void TStarJetPicoTowerCuts::ResetBadTowerList( ){
  badTowers.clear();
}

// KK: Add bad towers from comma separated values file
// Can be split into arbitrary many lines
// Lines starting with # will be ignored
Bool_t TStarJetPicoTowerCuts::AddBadTowers(TString csvfile){  
  // open infile
  std::string line;
  std::ifstream inFile ( csvfile );

  __DEBUG(2, Form("Loading bad towers from %s", csvfile.Data()) );
	  
  if ( !inFile.good() ) {
    __WARNING(Form("Can't open %s", csvfile.Data()) );
    return false;
  }
  
  while (std::getline (inFile, line) ){
    if ( line.size()==0 ) continue; // skip empty lines
    if ( line[0] == '#' ) continue; // skip comments

    std::istringstream ss( line );
    while( ss ){
      std::string entry;
      std::getline( ss, entry, ',' );
      int ientry = atoi(entry.c_str());
      if (ientry) {
	badTowers.insert( ientry );
	__DEBUG(2, Form("Added bad tower # %d", ientry));
      }
    }
  }
  
  return true;
  
}


// From Mark based on SPIN pp jet-finder !!!
// TODO: Check. Currently, I see 0.264 instead of 0.261
Double_t TStarJetPicoTowerCuts::TowerEnergyMipCorr(TStarJetPicoTower *mTower)
{
  Double_t mTowE = mTower->GetEnergy();

   // MIP corr see SPIN !!!
  Double_t theta = 2.*atan(exp(mTower->GetEta()));
  Double_t MipE  = 0.261*(1.+0.056*mTower->GetEta()*mTower->GetEta())/sin(theta); //GeV
  Int_t    nTr   = mTower->GetNAssocTracks();
  Double_t Ecorr = mTowE - nTr * MipE;

  return Ecorr;
}

Double_t TStarJetPicoTowerCuts::HadronicCorrection(TStarJetPicoTower *mTower,
						   TStarJetPicoEvent *mEvent,
						   TStarJetPicoTrackCuts *trackQA,
						   Double_t frac)
{
  Double_t Ecorr = mTower->GetEnergy();

  // check the associated tracks
  for (Int_t ntrack = 0; ntrack < mTower->GetNAssocTracks(); ntrack++) {  // is electron
    Int_t idx = mTower->GetMatchedTrackIndex(ntrack);
    TStarJetPicoPrimaryTrack *ptrack = mEvent->GetPrimaryTrack(idx);

    if (trackQA->IsTrackOK(ptrack) == kTRUE) {
      Double_t pel2 = 
	ptrack->GetPx() * ptrack->GetPx() + 
	ptrack->GetPy() * ptrack->GetPy() + 
	ptrack->GetPz() * ptrack->GetPz();
      
      Ecorr -= frac * TMath::Sqrt(pel2);
    } // track is OK
  } // loop over associated tracks
  return Ecorr;
}

Bool_t TStarJetPicoTowerCuts::RestrictPhiRange(Double_t min, Double_t max)
{
    // nick elsey: mapping any phi region defined on [-pi, pi], or [0, 2*pi]
    // onto a linear sequence of regions that can be used by IsTowerOK()
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

Bool_t TStarJetPicoTowerCuts::AddPhiCut(Double_t min, Double_t max) {
    if (!(min >= -TMath::Pi() && min <= TMath::Pi() && max >= -TMath::Pi() && max <= TMath::Pi() )){
        __ERROR("internal conversion error, apologies");
        return kFALSE;
    }
    std::vector<double> temp;
    temp.push_back( min );
    temp.push_back( max );
    restrictedPhiRanges.push_back( temp );
    return kTRUE;
}
