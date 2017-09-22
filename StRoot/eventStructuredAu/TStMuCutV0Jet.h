#ifndef _TStMuCutV0Jet_INCLUDED_
#define _TStMuCutV0Jet_INCLUDED_

#include "TObject.h"

#include "StStrangeMuDstMaker/StStrangeMuDst.hh"

class StV0MuDst;
class StMuDst;
class TStMuCutV0Jet : public TObject
{

 public:

  TStMuCutV0Jet();  
  virtual   ~TStMuCutV0Jet() {};

  void      Reset();
  void      SetStandardCutsAuAu();
  void      SetStandardCutspp();
  void      PrintCutList();
  void      SetVerbose(Int_t n){ fVerbose = n; }
 
  Int_t     CheckV0(StV0MuDst *v0, StMuDst *mu); 
  
  void     SetV0dcaV0Vertex(Float_t value){cutV0dcaV0Vertex = value;}
  void     SetV0dcaPosVertex(Float_t value){cutV0dcaPosVertex = value;}
  void     SetV0dcaNegVertex(Float_t value){cutV0dcaNegVertex = value;}
  void     SetV0dcaPosNeg(Float_t value){cutV0dcaPosNeg = value;}
  void     SetV0PosHits(UInt_t value){cutV0PosHits = value;}
  void     SetV0NegHits(UInt_t value){cutV0NegHits = value;}
  void     SetV0DecayLength(Float_t value){cutV0DecayLength = value;}
  void     SetV0NSigma(Float_t value){cutV0NSigma = value;}
  
  Float_t    GetV0dcaV0Vertex(){return cutV0dcaV0Vertex;}
  Float_t     GetV0dcaPosVertex(){return cutV0dcaPosVertex;}
  Float_t     GetV0dcaNegVertex(){return cutV0dcaNegVertex;}
  Float_t     GetV0dcaPosNeg(){return cutV0dcaPosNeg;}
  Int_t       GetV0PosHits(){return cutV0PosHits;}
  Int_t       GetV0NegHits(){return cutV0NegHits;}
  Float_t     GetV0DecayLength(){return cutV0DecayLength;}
  Float_t     GetV0NSigma(){return cutV0NSigma;}  


 protected:
  
  Float_t cutV0dcaV0Vertex;
  Float_t cutV0dcaPosVertex;
  Float_t cutV0dcaNegVertex;
  Float_t cutV0dcaPosNeg; 
  UInt_t cutV0PosHits;
  UInt_t cutV0NegHits;
  Float_t cutV0DecayLength;
  Float_t cutV0NSigma; 
  
  Int_t       fVerbose;                      //  Control debugging output
  
  ClassDef(TStMuCutV0Jet,1)                    //  Event cuts
    
    }; 

#endif
