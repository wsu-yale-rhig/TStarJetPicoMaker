#ifndef __TSTARJETPICOV0_HH
#define __TSTARJETPICOV0_HH

#include <TObject.h>

class TStarJetPicoV0 : public TObject
{
 public:
  TStarJetPicoV0();
  TStarJetPicoV0(const TStarJetPicoV0 &t);

  virtual ~TStarJetPicoV0();

  void    Clear(Option_t *Option = "");

  Int_t   GetKeyPos()           const {return fKeyPos;}
  Int_t   GetKeyNeg()           const {return fKeyNeg;}
  
  Float_t GetPx()            const {return fPxPos+fPxNeg;} 
  Float_t GetPy()            const {return fPyPos+fPyNeg;} 
  Float_t GetPz()            const {return fPzPos+fPzNeg;} 
  Float_t GetPxPos()            const {return fPxPos;} 
  Float_t GetPyPos()            const {return fPyPos;} 
  Float_t GetPzPos()            const {return fPzPos;} 
  Float_t GetPxNeg()            const {return fPxNeg;} 
  Float_t GetPyNeg()            const {return fPyNeg;} 
  Float_t GetPzNeg()            const {return fPzNeg;} 


  Float_t GetEta();
  Float_t GetPhi();

  Float_t GetMassLambda();
  Float_t GetMassAntiLambda();
  Float_t GetMassK0s();

  Float_t GetRapidityLambda();
  Float_t GetRapidityAntiLambda();
  Float_t GetRapidityK0s();

  Float_t GetELambda();
  Float_t GetEAntiLambda();
  Float_t GetEK0s();

  Float_t GetDcapn()            {return fDcapn ;}
  Float_t GetDcaV0()            {return fDcaV0 ;}
  Float_t GetDcaPos()            {return fDcap ;}
  Float_t GetDcaNeg()            {return fDcan ;}
  Float_t GetDecayLength()            {return fDLength ;}
  Float_t GetDedxPos()            {return fDedxPos ;}
  Float_t GetDedxNeg()            {return fDedxNeg ;}
  Float_t GetNSigmaProtonPos()            {return fNSigmaProtonPos ;}
  Float_t GetNSigmaProtonNeg()            {return fNSigmaProtonNeg ;}
  Float_t GetNSigmaPionPos()            {return fNSigmaPionPos ;}
  Float_t GetNSigmaPionNeg()            {return fNSigmaPionNeg ;}


 // SETTERS  

  void SetKeyPos(Int_t val)             {fKeyPos = val;}
  void SetKeyNeg(Int_t val)             {fKeyNeg = val;}
  void SetPxPos(Float_t val)            {fPxPos = val;} 
  void SetPyPos(Float_t val)            {fPyPos = val;} 
  void SetPzPos(Float_t val)            {fPzPos = val;}
  void SetPxNeg(Float_t val)            {fPxNeg = val;} 
  void SetPyNeg(Float_t val)            {fPyNeg = val;} 
  void SetPzNeg(Float_t val)            {fPzNeg = val;}
  void SetDcapn(Float_t val)            {fDcapn = val;}
  void SetDcaV0(Float_t val)            {fDcaV0 = val;}
  void SetDcaPos(Float_t val)            {fDcap = val;}
  void SetDcaNeg(Float_t val)            {fDcan = val;}
  void SetDecayLength(Float_t val)            {fDLength = val;}
  void SetDedxPos(Float_t val)            {fDedxPos = val;}
  void SetDedxNeg(Float_t val)            {fDedxNeg = val;}
  void SetNSigmaProtonPos(Float_t val)            {fNSigmaProtonPos = val;}
  void SetNSigmaProtonNeg(Float_t val)            {fNSigmaProtonNeg = val;}
  void SetNSigmaPionPos(Float_t val)            {fNSigmaPionPos = val;}
  void SetNSigmaPionNeg(Float_t val)            {fNSigmaPionNeg = val;}
 
  
 protected:


 private:

  Float_t ePosProton();
  Float_t eNegProton();
  Float_t ePosPion();
  Float_t eNegPion();
  Float_t Ptot2Pos();
  Float_t Ptot2Neg();
  Float_t Pt2V0();
  Float_t Ptot2V0();
  

  Int_t           fKeyPos;
  Int_t           fKeyNeg;

  Float_t         fPxPos;   
  Float_t         fPyPos;  
  Float_t         fPzPos; 
  Float_t         fPxNeg;   
  Float_t         fPyNeg;  
  Float_t         fPzNeg; 
  Float_t         fDcapn;
  Float_t         fDcaV0;
  Float_t         fDcap;
  Float_t         fDcan;
  Float_t         fDLength;
  Float_t         fDedxPos;
  Float_t         fDedxNeg;
  Float_t         fNSigmaProtonPos;
  Float_t         fNSigmaProtonNeg;
  Float_t         fNSigmaPionPos;
  Float_t         fNSigmaPionNeg;


   ClassDef(TStarJetPicoV0, 2)
};

#endif
