#ifndef __TSTARJETPICOV0CUTS__HH
#define __TSTARJETPICOV0CUTS__HH

#include <TObject.h>
class TStarJetPicoV0;

class TStarJetPicoV0Cuts : public TObject
{
 public:
  TStarJetPicoV0Cuts();
  TStarJetPicoV0Cuts(const TStarJetPicoV0Cuts &t);
  virtual ~TStarJetPicoV0Cuts() {;} //nothing to delete here

  virtual Int_t DoLambdaPID(TStarJetPicoV0 *mv0);
  virtual Int_t DoAntiLambdaPID(TStarJetPicoV0 *mv0);
  virtual Int_t DoK0sPID(TStarJetPicoV0 *mv0);

  // V0 cuts
  void SetLambdaMassRange(Float_t value) { fLambdaMassRange = value;}
  void SetLambdaDcapn(Float_t value) { fLambdaDcapn = value;}
  void SetLambdaDcaV0(Float_t value) { fLambdaDcaV0 = value;}
  void SetLambdaDcaPos(Float_t value) { fLambdaDcaPos = value;}
  void SetLambdaDcaNeg(Float_t value) { fLambdaDcaNeg = value;}
  void SetLambdaDecayLength(Float_t value) { fLambdaDecayLength = value;}
  void SetLambdaNSigmaPos(Float_t value) { fLambdaNSigmaPos = value;}
  void SetLambdaNSigmaNeg(Float_t value) { fLambdaNSigmaNeg = value;}

  void SetAntiLambdaMassRange(Float_t value) { fAntiLambdaMassRange = value;}
  void SetAntiLambdaDcapn(Float_t value) { fAntiLambdaDcapn = value;}
  void SetAntiLambdaDcaV0(Float_t value) { fAntiLambdaDcaV0 = value;}
  void SetAntiLambdaDcaPos(Float_t value) { fAntiLambdaDcaPos = value;}
  void SetAntiLambdaDcaNeg(Float_t value) { fAntiLambdaDcaNeg = value;}
  void SetAntiLambdaDecayLength(Float_t value) { fAntiLambdaDecayLength = value;}
  void SetAntiLambdaNSigmaPos(Float_t value) { fAntiLambdaNSigmaPos = value;}
  void SetAntiLambdaNSigmaNeg(Float_t value) { fAntiLambdaNSigmaNeg = value;}


  void SetK0sMassRange(Float_t value) { fK0sMassRange = value;}
  void SetK0sDcapn(Float_t value) { fK0sDcapn = value;}
  void SetK0sDcaV0(Float_t value) { fK0sDcaV0 = value;}
  void SetK0sDcaPos(Float_t value) { fK0sDcaPos = value;}
  void SetK0sDcaNeg(Float_t value) { fK0sDcaNeg = value;}
  void SetK0sDecayLength(Float_t value) { fK0sDecayLength = value;}
  void SetK0sNSigmaPos(Float_t value) { fK0sNSigmaPos = value;}
  void SetK0sNSigmaNeg(Float_t value) { fK0sNSigmaNeg = value;}

  // V0 cuts

  Float_t GetLambdaDcapn() {return fLambdaDcapn;}
  Float_t GetLambdaDcaV0() {return fLambdaDcaV0;}
  Float_t GetLambdaDcaPos() {return fLambdaDcaPos;}
  Float_t GetLambdaDcaNeg() {return fLambdaDcaNeg;}
  Float_t GetLambdaDecayLength() {return fLambdaDecayLength;}
  Float_t GetLambdaNSigmaPos() {return fLambdaNSigmaPos;}
  Float_t GetLambdaNSigmaNeg() {return fLambdaNSigmaNeg;}

  Float_t GetAntiLambdaDcapn() {return fAntiLambdaDcapn;}
  Float_t GetAntiLambdaDcaV0() {return fAntiLambdaDcaV0;}
  Float_t GetAntiLambdaDcaPos() {return fAntiLambdaDcaPos;}
  Float_t GetAntiLambdaDcaNeg() {return fAntiLambdaDcaNeg;}
  Float_t GetAntiLambdaDecayLength() {return fAntiLambdaDecayLength;}
  Float_t GetAntiLambdaNSigmaPos() {return fAntiLambdaNSigmaPos;}
  Float_t GetAntiLambdaNSigmaNeg() {return fAntiLambdaNSigmaNeg;}

  Float_t GetK0sDcapn() {return fK0sDcapn;}
  Float_t GetK0sDcaV0() {return fK0sDcaV0;}
  Float_t GetK0sDcaPos() {return fK0sDcaPos;}
  Float_t GetK0sDcaNeg() {return fK0sDcaNeg;}
  Float_t GetK0sDecayLength() {return fK0sDecayLength;}
  Float_t GetK0sNSigmaPos() {return fK0sNSigmaPos;}
  Float_t GetK0sNSigmaNeg() {return fK0sNSigmaNeg;}

  Float_t GetLambdaMassRange() {return fLambdaMassRange;}
  Float_t GetAntiLambdaMassRange() {return fAntiLambdaMassRange;}
  Float_t GetK0sMassRange() {return fK0sMassRange;}

  void    SetAcceptLambdas(Bool_t val) { fAcceptLambdas = val; }
  Bool_t  AcceptLambdas() { return fAcceptLambdas; }

  void    SetAcceptAntiLambdas(Bool_t val) { fAcceptAntiLambdas = val; }
  Bool_t  AcceptAntiLambdas() { return fAcceptAntiLambdas; }

  void    SetAcceptK0s(Bool_t val) { fAcceptK0s = val; }
  Bool_t  AcceptK0s() { return fAcceptK0s; }

 private:

  // V0 Cuts
  Float_t fLambdaMassRange;
  Float_t fLambdaDcapn;
  Float_t fLambdaDcaV0;
  Float_t fLambdaDcaPos;
  Float_t fLambdaDcaNeg;
  Float_t fLambdaDecayLength;
  Float_t fLambdaNSigmaPos;
  Float_t fLambdaNSigmaNeg;

  Float_t fAntiLambdaMassRange;
  Float_t fAntiLambdaDcapn;
  Float_t fAntiLambdaDcaV0;
  Float_t fAntiLambdaDcaPos;
  Float_t fAntiLambdaDcaNeg;
  Float_t fAntiLambdaDecayLength;
  Float_t fAntiLambdaNSigmaPos;
  Float_t fAntiLambdaNSigmaNeg;

  Float_t fK0sMassRange;
  Float_t fK0sDcapn;
  Float_t fK0sDcaV0;
  Float_t fK0sDcaPos;
  Float_t fK0sDcaNeg;
  Float_t fK0sDecayLength;
  Float_t fK0sNSigmaPos;
  Float_t fK0sNSigmaNeg;

  Double_t fK0Mass;
  Double_t fLambdaMass;

  Bool_t   fAcceptLambdas; // flag whether to calculate PIDs for Lambdas
  Bool_t   fAcceptAntiLambdas; // flag whether to calculate PIDs for AntiLambdas
  Bool_t   fAcceptK0s; // flag whether to calculate PIDs for K0s
  
  ClassDef(TStarJetPicoV0Cuts, 1)
};

#endif
