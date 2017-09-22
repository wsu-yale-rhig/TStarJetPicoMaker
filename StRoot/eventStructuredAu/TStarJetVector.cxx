#include "TStarJetVector.h"
#include "TStarJetPicoDefinitions.h"

#include <TMath.h>
#include <TVector2.h>
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// TStarJetPicoVector                                                      //
//                                                                         //
// TLorentzVector with "Features"                                          //
//                                                                         //
// - stores extra Int_t or Double_t information in TArrays                 //
//                                                                         //
// - enums help to navigate through features                               //
// -- see TStarJetPicoReader::LoadV0s(), LoadTracks(), LoadTowers(),       //
//                                                                         //
// - some methods provided for convenience - setters and getters           //
// -- see SetPID() and GetPID() for example                                //
//                                                                         //
// - implements some extra functions for better compatibility with fastjet //
//                                                                         //
// - can be used to store ouput jets from the jet finders!                 //
// -- within a derived class implement area4vector and redefine few enums  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetVector)

#define __TStarJetVector_NfeaturesD 7
#define __TStarJetVector_NfeaturesI 6

// #define __TStarJetVector_NfeaturesD 0
// #define __TStarJetVector_NfeaturesI 0


TStarJetVector::TStarJetVector()
  : TLorentzVector()
  , fFeaturesD(__TStarJetVector_NfeaturesD)
  , fFeaturesI(__TStarJetVector_NfeaturesI)
  , fTrigger(kFALSE)
{

  Clear();
}

TStarJetVector::TStarJetVector(const TStarJetVector &v)
  : TLorentzVector(v)
  , fFeaturesD(v.fFeaturesD)
  , fFeaturesI(v.fFeaturesI)
  , fTrigger(kFALSE)
{
  ;
}

TStarJetVector::TStarJetVector(const TLorentzVector &lv)
  : TLorentzVector(lv)
  , fFeaturesD(__TStarJetVector_NfeaturesD)
  , fFeaturesI(__TStarJetVector_NfeaturesI)
  , fTrigger(kFALSE)
{
  Clear();
}


TStarJetVector::~TStarJetVector()
{  
  ;
}

void TStarJetVector::SetFeature(Int_t idx, Double_t value)
{
  fFeaturesD[idx] = value;
}

void TStarJetVector::SetFeature(Int_t idx, Int_t value)
{
  fFeaturesI[idx] = value;
}

void TStarJetVector::SetFeatureD(Int_t idx, Double_t value)
{
  fFeaturesD[idx] = value;
}

void TStarJetVector::SetFeatureI(Int_t idx, Int_t value)
{
  fFeaturesI[idx] = value;
}

void TStarJetVector::Clear(Option_t *option)
{
  TLorentzVector::Clear(option);
  fFeaturesD.Set(__TStarJetVector_NfeaturesD);
  fFeaturesI.Set(__TStarJetVector_NfeaturesI);
  fFeaturesD.Reset(0.0);
  fFeaturesI.Reset(0);
  fFeaturesI[_MATCH] = -1; // KK
  fTrigger = kFALSE;
}

double TStarJetVector::phi() const 
{
  //
  // This is for fastjet: range 0 - 2pi
  //
  return TVector2::Phi_0_2pi(Phi());
}

Bool_t TStarJetVector::IsChargedHadron()
{
  if (fFeaturesI[_CHARGE] == _NEUTRAL) 
    return kFALSE;
  else
    if (fFeaturesI[_PID] == __STARJETPICO_ELECTRON_PID)
      return kFALSE;
    else
      return kTRUE;
}  
