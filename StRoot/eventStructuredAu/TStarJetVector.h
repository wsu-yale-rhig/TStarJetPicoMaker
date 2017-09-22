#ifndef __TSTARJETVECTOR_HH
#define __TSTARJETVECTOR_HH

#include <TLorentzVector.h>
#include <TArrayD.h>
#include <TArrayI.h>

class TStarJetVector : public TLorentzVector
{
 public:
  TStarJetVector();  
  TStarJetVector(const TStarJetVector &v);  
  TStarJetVector(const TLorentzVector &lv);
  virtual ~TStarJetVector();

  Double_t        GetFeatureD(Int_t i) const {return fFeaturesD[i];}
  const TArrayD  *GetFeaturesD() const {return &fFeaturesD;};
  Int_t           GetNofFeaturesD() const {return fFeaturesD.GetSize();}

  Int_t           GetFeatureI(Int_t i) const {return fFeaturesI[i];}
  const TArrayI  *GetFeaturesI() const {return &fFeaturesI;};
  Int_t           GetNofFeaturesI() const {return fFeaturesI.GetSize();}

  void            SetFeature(Int_t idx, Double_t value);
  void            SetFeature(Int_t idx, Int_t value);

  void            SetFeatureD(Int_t idx, Double_t value);
  void            SetFeatureI(Int_t idx, Int_t value);

  virtual void    Clear(Option_t *option = "");

  // THIS is for FASTJET usage
  //double E() const ; // returns the energy component - already in TLorentzVector
  Double_t e() const {return E();} // returns the energy component 
  Double_t px() const {return Px();} // returns the x momentum component 
  Double_t py() const {return Py();} // returns the y momentum component 
  Double_t pz() const {return Pz();} // returns the z momentum component 
  Double_t phi() const;  // returns the azimuthal angle in range 0 . . . 2pi
  Double_t phi_std() const {return Phi();} // returns the azimuthal angle in range -pi ... pi
  Double_t rap() const {return Rapidity();} // returns the rapidity 
  Double_t rapidity() const {return Rapidity();} // returns the rapidity 
  Double_t pseudorapidity() const {return Eta();} // returns the pseudo-rapidity 
  Double_t eta() const {return Eta();} // returns the pseudo-rapidity 
  Double_t kt2() const {return Perp2();} // returns the squared transverse momentum 
  Double_t perp2() const {return Perp2();}; // returns the squared transverse momentum 
  Double_t perp() const {return Perp();}; // returns the transverse momentum 
  Double_t m2() const {return M2();} // returns squared invariant mass 
  Double_t m() const {return M();} // returns invariant mass ( 
  Double_t mperp2() const {return Mt2();} // returns the squared transverse mass = k2 
  Double_t mperp() const {return Mt();} // returns the transverse mass 
  //double operator[] (int i) const; // returns component i - already in TLorentzVector
  //double operator() (int i) const; // returns component i - already in TLorentzVector

  // THE ENUMS AND FUNCTIONS BELOW
  // ARE FOR CONVENIENCE ONLY

  // indexes for TArrays
  enum _FEATUREINDEX_D
    {
      _P_OVER_E      = 0,
      _MASS          = 1,
      _NSIGMA_PION   = 2,
      _NSIGMA_KAON   = 3,      
      _NSIGMA_PROTON = 4,
      _NSIGMA_ELECTRON = 5,
      _DEDX          = 6
    };

  enum _FEATUREINDEX_I 
    {
      _PID = 0,     // used with data or pythia - integer!
      _TID_REF = 1, // tower id or track id
      _CHARGE = 2,  // integer charge : usually _NEUTRAL or _CHARGED
      _TYPE = 3,    // data? pythia? etc
      _KEY = 4,     // used with data
      _STATUS = 4,  // used with pythia
      _MATCH = 5,   // KK: use to match link to a different particle
    };

  // markers - bit mode 
  // bitwise or can be applied
  enum _CUSTOMTYPE
    {
      _TRACK       = 1,
      _MATCHED     = 1 << 1,
      _TOWER       = 1 << 2,
      _EMC_CLUSTER = 1 << 3,
      _V0          = 1 << 4,

      _PYTHIA      = 1 << 5, // or any other MC
      _RANDOMBG    = 1 << 6
    };

  enum _CHARGETYPE
    {
      _NEUTRAL = 0,
      _CHARGED = 1,
    };

  void            SetPID(Int_t pid) {fFeaturesI[_PID] = pid;}
  Int_t           GetPID() const {return fFeaturesI[_PID];}

  void            SetTrackID(Int_t id) {fFeaturesI[_TID_REF] = id;}
  Int_t           GetTrackID() const {return fFeaturesI[_TID_REF];}

  void            SetTowerID(Int_t id) {fFeaturesI[_TID_REF] = id;}
  Int_t           GetTowerID() const {return fFeaturesI[_TID_REF];}

  void            SetCharge(Int_t id) {fFeaturesI[_CHARGE] = id;}
  Int_t           GetCharge() {return fFeaturesI[_CHARGE];}

  void            SetChargeStatus(Int_t id) {fFeaturesI[_CHARGE] = id;}
  Int_t           GetChargeStatus() {return fFeaturesI[_CHARGE];}

  Int_t           GetType() {return fFeaturesI[_TYPE];}
  void            SetType(Int_t type) {fFeaturesI[_TYPE] = type;}
    
  Bool_t          IsTrigger() {return fTrigger;}
  void            SetTriggerStatus(Bool_t value) {fTrigger = value;}

  // KK
  void            SetMatch(Int_t id) {fFeaturesI[_MATCH] = id;}
  Int_t           GetMatch() const {return fFeaturesI[_MATCH];}

  Bool_t          IsCharged()
  {
    if (fFeaturesI[_CHARGE] == _NEUTRAL) 
      return kFALSE;
    else
      return kTRUE;
  }  

  Bool_t          IsChargedHadron();

  Bool_t          IsV0()
  {
    if (fFeaturesI[_TYPE] == _V0) 
      return kTRUE;
    else
      return kFALSE;
  }  

  void            SetPoverE(Double_t val) {fFeaturesD[_P_OVER_E] = val;}
  Double_t        GetPoverE() {return fFeaturesD[_P_OVER_E];}

  // duplication when using TLorentzVector! - but ok.
  void            SetPicoMass(Double_t val) {fFeaturesD[_MASS] = val;}
  Double_t        GetPicoMass() {return fFeaturesD[_MASS];}

 protected:
  TArrayD fFeaturesD;
  TArrayI fFeaturesI;
  Bool_t  fTrigger;

  ClassDef(TStarJetVector, 1)
};

#endif
