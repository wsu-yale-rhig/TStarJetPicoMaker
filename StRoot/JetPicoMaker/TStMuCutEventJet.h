#ifndef _TStMuCutEventJet_INCLUDED_
#define _TStMuCutEventJet_INCLUDED_

#include "TObject.h"

#include "StEvent/StEventInfo.h"
#include "StEvent/StRunInfo.h"
#include "StEvent/StEventSummary.h"
#include "StEvent/StCtbTriggerDetector.h"
#include "StEvent/StZdcTriggerDetector.h"
#include "StEvent/StBbcTriggerDetector.h"
#include "StEvent/StFpdCollection.h"
#include "StEvent/StL0Trigger.h"
#include "StEvent/StDetectorState.h"
#include "StStrangeMuDstMaker/StStrangeMuDst.hh"
#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StThreeVectorF.hh"

class TPaveText;
class StEvent;

#include "StMuDSTMaker/COMMON/StMuEvent.h"


class TStMuCutEventJet : public TObject
{

 public:

  TStMuCutEventJet();  
  virtual   ~TStMuCutEventJet() {};

  void      Reset();

  void	    SetStandardCutsAuAuY11MB();

  void      SetStandardCutsAuAuY11HT();
  void      SetStandardCutsAuAuY11L2();
	
	void 			SetStandardCutsAuAuY14MB();
	
	void      SetStandardCutsAuAuY14HT1();
	void			SetStandardCutsAuAuY14HT2();
	void			SetStandardCutsAuAuY14HT3();
	void			SetStandardCutsAuAuY14HT23();

  Int_t     CheckEvent(StMuEvent *Event); 

  void      StatisticForParticle(StMuEvent *Event);

  TPaveText *GetCutList();
  void      PrintCutList();
  void      SetVerbose(Int_t n)                      { fVerbose = n; }
  void      SetVertexIflag(Int_t n1,Int_t n2=99,Int_t n3=99) 
    { fFlagVertexIflag = kTRUE; 
    fN1VertexIflag   = n1; 
    fN2VertexIflag   = n2;
    fN3VertexIflag   = n3; }
  
  void      SetVertexX(Double_t x, Double_t y)   { fFlagVertexX = kTRUE; 
  fMinVertexX = x; 
  fMaxVertexX = y; }
  void      SetVertexY(Double_t x, Double_t y)   { fFlagVertexY = kTRUE; 
  fMinVertexY = x; 
  fMaxVertexY = y; }
  void      SetVertexZ(Double_t x, Double_t y)   { fFlagVertexZ = kTRUE; 
  fMinVertexZ = x; 
  fMaxVertexZ = y; }
  void      SetEVeto(Double_t x, Double_t y)     { fFlagEVeto = kTRUE; 
  fMinEVeto = x; 
  fMaxEVeto = y; }
  void      SetMult(Int_t x, Int_t y)            { fFlagMult = kTRUE; 
  fMinMult = x; 
  fMaxMult = y; }
  void      SetL0TriggerWord(UInt_t x,UInt_t y=0,UInt_t z=0,UInt_t w=0,UInt_t q=0,UInt_t r=0,UInt_t l=0,UInt_t k=0,UInt_t m=0,UInt_t n=0) { fFlagL0TriggerWord= kTRUE; 
  fL0TriggerWord = x; fL0TriggerWord2= y;
  fL0TriggerWord3 = z; fL0TriggerWord4= w; 
  fL0TriggerWord5 = q; fL0TriggerWord6= r; 
  fL0TriggerWord7 = l; fL0TriggerWord8= k;
  fL0TriggerWord9 = m; fL0TriggerWord10= n;

}
  void      SetVertexIflagCutOff()               { fFlagVertexIflag = kFALSE; }
  void      SetVertexXCutOff()                   { fFlagVertexX = kFALSE; }
  void      SetVertexYCutOff()                   { fFlagVertexY = kFALSE; }
  void      SetVertexZCutOff()                   { fFlagVertexZ = kFALSE; }
  void      SetEVetoCutOff()                     { fFlagEVeto = kFALSE; }
  void      SetMultCutOff()                      { fFlagMult = kFALSE; }
  
  Float_t   GetVertexX(StMuEvent *Event);
  Float_t   GetVertexY(StMuEvent *Event);
  Float_t   GetVertexZ(StMuEvent *Event);
  Int_t     GetNumGoodTracks(StMuEvent *Event);
  Int_t     GetNumTracks(StMuEvent *Event);
  UInt_t    GetL0TriggerWord(StMuEvent *Event);
  Double_t  GetReactionPlane(StMuEvent *Event,UShort_t s);
  Double_t  GetReactionPlanePtWgt(StMuEvent *Event,UShort_t s);

  
  Float_t   GetVertexZmin() {return fMinVertexZ;}
  Float_t   GetVertexZmax() {return fMaxVertexZ;}
  
  
 protected:
  
  Int_t       fTRUE;
  Int_t       fFALSE;
  Int_t       fVerbose;                      //  Control debugging output
  Int_t       fnumevent;                     //  number of events
  Int_t       fnumgoodevent;                 //  number of accepted events
  Int_t       fFlagVertexIflag;              //  flag of cut
  Int_t       fnVertexIflag;                 //  number of not accepted events due to this cut 
  Int_t       fMinVertexIflag;               //  vertex iflag to cut Pb (usually fVertexIflag == 0)
  Int_t       fMaxVertexIflag;               //  in pp (usually fVertexIflag == 0,1)
  Int_t       fN1VertexIflag;                //  accepted vertex flag
  Int_t       fN2VertexIflag;                //  accepted vertex flag
  Int_t       fN3VertexIflag;                //  accepted vertex flag
  Int_t       fFlagVertexX;                  //  flag of cut 
  Int_t       fnVertexX;                     //  number of not accepted events due to this cut 
  Int_t       fnallVertexX;                     //  number of not accepted events due to this cut 
  Double_t    fMinVertexX;                   //  Minimum X vertex position
  Double_t    fMaxVertexX;                   //  Maximum X vertex position
  Int_t       fFlagVertexY;                  //  flag of cut  
  Int_t       fnVertexY;                     //  number of not accepted events due to this cut 
  Int_t       fnallVertexY;                     //  number of not accepted events due to this cut 
  Double_t    fMinVertexY;                   //  Minimum Y vertex position
  Double_t    fMaxVertexY;                   //  Maximum Y vertex position
  Int_t       fFlagVertexZ;                  //  flag of cut 
  Int_t       fnVertexZ;                     //  number of not accepted events due to this cut 
  Int_t       fnallVertexZ;                     //  number of not accepted events due to this cut 
  Double_t    fMinVertexZ;                   //  Minimum Z vertex position
  Double_t    fMaxVertexZ;                   //  Maximum Z vertex position
  Int_t       fFlagEVeto;                    //  flag of cut   
  Int_t       fnEVeto;                       //  number of not accepted events due to this cut 
  Double_t    fMinEVeto;                     //  Minimum veto calorimeter energy
  Double_t    fMaxEVeto;                     //  Maximum veto calorimeter energy
  Int_t       fFlagMult;                     //  flag of cut 
  Int_t       fnMult;                        //  number of not accepted events due to this cut 
  Int_t       fnallMult;                     //  number of not accepted events due to this cut 
  Int_t       fMinMult;                      //  Minimum multiplicity
  Int_t       fMaxMult;                      //  Maximum multiplicity
  Int_t       fFlagL0TriggerWord;            //  flag of cut 
  Int_t       fnL0TriggerWord;               //  number of not accepted events due to this cut 
  Int_t       fnallL0TriggerWord;            //  number of not accepted events due to this cut 
  Int_t       fAuAuRefCheck;                 //  Check for the grefmult vs refmult for AuAu
  UInt_t      fL0TriggerWord;                //  triggerword
  UInt_t      fL0TriggerWord2;               //  triggerword
  UInt_t      fL0TriggerWord3;               //  triggerword
  UInt_t      fL0TriggerWord4;               //  triggerword
  UInt_t      fL0TriggerWord5;               //  triggerword
  UInt_t      fL0TriggerWord6;               //  triggerword
  UInt_t      fL0TriggerWord7;               //  triggerword
  UInt_t      fL0TriggerWord8;               //  triggerword 
  UInt_t      fL0TriggerWord9;               //  triggerword
  UInt_t      fL0TriggerWord10;              
//  triggerword

  ClassDef(TStMuCutEventJet,3)                    //  Event cuts

    }; 

#endif
