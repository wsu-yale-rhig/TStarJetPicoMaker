#include "TStarJetPicoV0.h"
#include <math.h>
#include <Riostream.h>

#define  M_LAMBDA           1.115684         /* mass     in GeV */
#define  M_KAON_0_SHORT     0.497672         /* mass     in GeV */
#define  M_PROTON           0.9382723128     /* mass     in GeV */
#define  M_PION_PLUS        0.1395700        /* mass     in GeV */
#define  M_PION_MINUS       0.1395700        /* mass     in GeV */
#define  M_ANTIPROTON       0.9382723128     /* mass     in GeV */

static const Float_t M_LAMBDA_2 = ::pow(M_LAMBDA,2);
static const Float_t M_KAON_0_S_2 = ::pow(M_KAON_0_SHORT,2);
static const Float_t M_PROTON_2 = ::pow(M_PROTON,2);
static const Float_t M_ANTIPROTON_2 = ::pow(M_ANTIPROTON,2);
static const Float_t M_PION_PLUS_2 = ::pow(M_PION_PLUS,2);
static const Float_t M_PION_MINUS_2 = ::pow(M_PION_MINUS,2);

ClassImp(TStarJetPicoV0)

TStarJetPicoV0::TStarJetPicoV0()
  : TObject()
  , fKeyPos(0) 
  , fKeyNeg(0) 
  , fPxPos(0)             
  , fPyPos(0)             
  , fPzPos(0)
  , fPxNeg(0)             
  , fPyNeg(0)             
  , fPzNeg(0)
  , fDcapn(0)
  , fDcaV0(0)
  , fDcap(0)
  , fDcan(0)
  , fDLength(0)
  , fDedxPos(0)
  , fDedxNeg(0) 
  , fNSigmaProtonPos(0)
  , fNSigmaProtonNeg(0) 
  , fNSigmaPionPos(0)
  , fNSigmaPionNeg(0)                
{
  ;
}
//____________________________________________________________
TStarJetPicoV0::TStarJetPicoV0(const TStarJetPicoV0 &t)
  : TObject(t)
  , fKeyPos(t.fKeyPos)
  , fKeyNeg(t.fKeyNeg)           
  , fPxPos(t.fPxPos)             
  , fPyPos(t.fPyPos)             
  , fPzPos(t.fPzPos)   
  , fPxNeg(t.fPxNeg)             
  , fPyNeg(t.fPyNeg)             
  , fPzNeg(t.fPzNeg) 
  , fDcapn(t.fDcapn)
  , fDcaV0(t.fDcaV0)
  , fDcap(t.fDcap)
  , fDcan(t.fDcan)
  , fDLength(t.fDLength)
  , fDedxPos(t.fDedxPos)
  , fDedxNeg(t.fDedxNeg) 
  , fNSigmaProtonPos(t.fNSigmaProtonPos)
  , fNSigmaProtonNeg(t.fNSigmaProtonNeg) 
  , fNSigmaPionPos(t.fNSigmaPionPos)
  , fNSigmaPionNeg(t.fNSigmaPionNeg)  
             
{
  ;
}

//____________________________________________________________
TStarJetPicoV0::~TStarJetPicoV0()
{
  ;
}

//____________________________________________________________
Float_t TStarJetPicoV0::GetMassLambda(){
  return sqrt(pow(ePosProton()+eNegPion(),2)-Ptot2V0());
}

//____________________________________________________________
Float_t TStarJetPicoV0::GetMassAntiLambda() {
  return sqrt(pow(eNegProton()+ePosPion(),2)-Ptot2V0());
}

//____________________________________________________________
Float_t TStarJetPicoV0::GetMassK0s() {
  return sqrt(pow(ePosPion()+eNegPion(),2)-Ptot2V0());
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetPhi(){
  return atan2(GetPy(),GetPx());
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetEta(){
  return atanh(GetPz()/sqrt(Ptot2V0()));
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetRapidityLambda(){
  return 0.5*log((GetELambda()+GetPz())/(GetELambda()-GetPz()));

}
//____________________________________________________________
Float_t TStarJetPicoV0::GetRapidityAntiLambda(){
  return 0.5*log((GetEAntiLambda()+GetPz())/(GetEAntiLambda()-GetPz()));
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetRapidityK0s(){
 
  return 0.5*log((GetEK0s()+GetPz())/(GetEK0s()-GetPz()));
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetELambda() {
  return sqrt(Ptot2V0()+M_LAMBDA_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetEAntiLambda() {
  return sqrt(Ptot2V0()+M_LAMBDA_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::GetEK0s() {
  return sqrt(Ptot2V0()+M_KAON_0_S_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::ePosProton() {
  return sqrt(Ptot2Pos()+M_PROTON_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::eNegProton() {
  return sqrt(Ptot2Neg()+M_ANTIPROTON_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::ePosPion() {
  return sqrt(Ptot2Pos()+M_PION_PLUS_2);
}
//____________________________________________________________
Float_t TStarJetPicoV0::eNegPion() {
  return sqrt(Ptot2Neg()+M_PION_MINUS_2);
}

//____________________________________________________________
Float_t TStarJetPicoV0::Ptot2Pos() {
     return (pow(GetPxPos(),2) + pow(GetPyPos(),2) + pow(GetPzPos(),2));
}
//____________________________________________________________
Float_t TStarJetPicoV0::Ptot2Neg() {
     return (pow(GetPxNeg(),2) + pow(GetPyNeg(),2) + pow(GetPzNeg(),2));
}
//____________________________________________________________
Float_t TStarJetPicoV0::Pt2V0() {
  return (pow(GetPx(),2) + pow(GetPy(),2));
}

//____________________________________________________________
Float_t TStarJetPicoV0::Ptot2V0() {
     return (Pt2V0() + pow(GetPz(),2));
}


//____________________________________________________________
void TStarJetPicoV0::Clear(Option_t */*Option*/)
{
  fKeyPos = 0;  
  fKeyNeg = 0; 
  fPxPos = 0;             
  fPyPos = 0;             
  fPzPos = 0;
  fPxNeg = 0;             
  fPyNeg = 0;             
  fPzNeg = 0; 
  fDcapn = 0;
  fDcaV0 = 0;
  fDcap = 0;
  fDcan = 0;
  fDLength = 0;
  fDedxPos = 0;
  fDedxNeg = 0;
  fNSigmaProtonPos = 0;
  fNSigmaProtonNeg = 0;
  fNSigmaPionPos = 0;
  fNSigmaPionNeg = 0;         

}
