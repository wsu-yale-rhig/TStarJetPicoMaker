//////////////////////////////////////////////////////////
//                                                      //
//              TStMuCutEventJet Class                 //
//                                                      //
//////////////////////////////////////////////////////////

#include "StEvent/StEvent.h" 
#include "StEvent/StEventTypes.h" 
#include "StEvent/StEventSummary.h" 
#include "StEvent/StEventInfo.h" 
#include "StEvent/StDetectorState.h" 
#include "StEvent/StL0Trigger.h"

#include "StEventUtilities/StuRefMult.hh"

#include "StarClassLibrary/SystemOfUnits.h"
#include "StarClassLibrary/StTimer.hh"

#include "StarClassLibrary/StThreeVectorD.hh"
#include "StarClassLibrary/StThreeVectorF.hh"

#include "StMuDSTMaker/COMMON/StMuCut.h"
#include "StMuDSTMaker/COMMON/StMuDebug.h"
 
#include "TClonesArray.h"
#include "TObject.h"
#include "TClass.h"

#include <TPaveText.h>
#include <TCutG.h>
#include <TArrayI.h>
#include <TObjArray.h>

#include "TStMuCutEventJet.h"

ClassImp(TStMuCutEventJet)

//______________________________________________________________________________
    TStMuCutEventJet::TStMuCutEventJet():TObject()
{ 
  //
  // Default constructor
  //

  Reset();

}

//______________________________________________________________________________

void TStMuCutEventJet::Reset()
{
  //
  // Resets the cut definition and the counters
  //
    fTRUE         = 1; 
    fFALSE        = 0;
    fVerbose      = fFALSE;
    
    fnumevent     = 0;     
    fnumgoodevent = 0; 

    fFlagVertexIflag = kFALSE;
    fFlagVertexX     = kFALSE;
    fFlagVertexY     = kFALSE;
    fFlagVertexZ     = kFALSE;
    fFlagEVeto       = kFALSE;
    fFlagMult        = kFALSE;
    fFlagL0TriggerWord  = kFALSE;

    fnVertexIflag = 0;
    fnVertexX     = 0;
    fnVertexY     = 0;
    fnVertexZ     = 0;
    fnEVeto       = 0;
    fnMult        = 0;
    fnL0TriggerWord = 0;

    fnallVertexX         = 0;
    fnallVertexY         = 0;
    fnallVertexZ         = 0;
    fnallMult            = 0;
    fnallL0TriggerWord   = 0;
    fAuAuRefCheck        = kFALSE;

}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY11MB(){
// vpd-zdc-mb-protected	
  SetL0TriggerWord(350003,350013,350023,350033,350043,99999,99999,99999,99999,99999);  
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY11HT()
{   // Use NPE trigger. 350502, 350512 for NPE15
//	350503,350513 for NPE18
//	350504,350514 for NPE25
//  SetL0TriggerWord(350502,350512,350503,350513,350504,350514,99999,99999,99999,99999);	// NPE15, NPE18, NPE25
  SetL0TriggerWord(350503,350513,99999,99999,99999,99999,99999,99999,99999,99999);	// NPE18
//  SetL0TriggerWord(350504,350514,99999,99999,99999,99999,99999,99999,99999,99999);	// NPE25
}
 
//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY11L2()
{   //L2 trigger
// #ly not sure what is it, therefore commented out.   fAuAuRefCheck=kTRUE;
  SetL0TriggerWord(20,350069,99999,99999,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY14MB(){
	//monitoring MB trigger
	SetL0TriggerWord(450011,450021,99999,99999,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY14HT1(){
	//HT1-VPDMB-30 trigger
	SetL0TriggerWord(450201,450211,99999,99999,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY14HT2(){
	//HT2-VPDMB-30 trigger
	SetL0TriggerWord(450202,450212,99999,99999,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY14HT3(){
	//HT3 trigger
	SetL0TriggerWord(450203,450213,99999,99999,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
void TStMuCutEventJet::SetStandardCutsAuAuY14HT23(){
	//HT2-VPDMB-30 & HT3 triggers
	SetL0TriggerWord(450202,450212,450203,450213,99999,99999,99999,99999,99999,99999);
}

//______________________________________________________________________________
 Int_t TStMuCutEventJet::CheckEvent(StMuEvent *Event)
{

  if (fVerbose) cout<<"TStMuCutEventJet::CheckEvent"<<endl;

  //Checks whether a given event passes the defined cuts 
 
  StatisticForParticle(Event);
  
  fnumevent++;
    
  
  if(fFlagL0TriggerWord && (Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord) ==0 &&
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord2) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord3) ==0 &&  
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord4) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord5) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord6) ==0 &&
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord7) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord8) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord9) ==0 && 
			    Event->triggerIdCollection().nominal().isTrigger(fL0TriggerWord10) ==0  
			    ))
    {
      if(fVerbose) printf("Event not accepted L0TriggerWord ");
      fnL0TriggerWord++;
      return kFALSE;
    }
  
 


  if(fFlagMult && (GetNumGoodTracks(Event) < fMinMult || GetNumGoodTracks(Event) > fMaxMult) )
    {
      if(fVerbose) printf("Event not accepted  Mult %d. ",GetNumGoodTracks(Event));
      fnMult++;
      return kFALSE;
    }
  
  
   if(fFlagVertexX && (GetVertexX(Event) < fMinVertexX || GetVertexX(Event) > fMaxVertexX) )
     {
       if(fVerbose) printf("Event not accepted  VertexX = %f ",GetVertexX(Event));
       fnVertexX++;
       return kFALSE;
     }
    
    if(fFlagVertexY && (GetVertexY(Event) < fMinVertexY || GetVertexY(Event) > fMaxVertexY) )
    {
      if(fVerbose) printf("Event not accepted  VertexY = %f ",GetVertexY(Event));
      fnVertexY++;
      return kFALSE;
    }
    if(fFlagVertexZ && (GetVertexZ(Event) < fMinVertexZ || GetVertexZ(Event) > fMaxVertexZ ||GetVertexZ(Event) ==0 )  )
    {
      if(fVerbose) printf("Event not accepted  VertexZ = %f ",GetVertexZ(Event));
      fnVertexZ++;
      return kFALSE;
    }
    
    fnumgoodevent++;

    return kTRUE;

}


void TStMuCutEventJet::StatisticForParticle(StMuEvent *Event)
{
  
  //Checks whether a given event passes the defined cuts  
  
    if(fFlagL0TriggerWord && (GetL0TriggerWord(Event)!= fL0TriggerWord))
    {     
      fnallL0TriggerWord++;
    }
 
   
    if(fFlagMult && (GetNumGoodTracks(Event) < fMinMult || GetNumGoodTracks(Event) > fMaxMult) )
    {    
      fnallMult++;    
    }
 
    if(fFlagVertexX && (GetVertexX(Event) < fMinVertexX || GetVertexX(Event) > fMaxVertexX) )
    {      
      fnallVertexX++;     
    }

    if(fFlagVertexY && (GetVertexY(Event) < fMinVertexY || GetVertexY(Event) > fMaxVertexY) )
    {     
      fnallVertexY++;      
    }

    if(fFlagVertexZ && (GetVertexZ(Event) < fMinVertexZ || GetVertexZ(Event) > fMaxVertexZ) )
    {      
      fnallVertexZ++;      
    }     
}

//______________________________________________________________________________
 TPaveText  *TStMuCutEventJet::GetCutList()
{
  //
  // Creates a TPaveText with the defined cuts and the cut-statistics
  //

  TPaveText *pave      = new TPaveText(0,0,1,1);
 
  Char_t         hname[10000]; 

  sprintf(hname,"total number of events : %d ",fnumevent);  
  pave->AddText(hname);

  sprintf(hname,"number of events accepted : %d ",fnumgoodevent);  
  pave->AddText(hname);
   

  if(fFlagL0TriggerWord)
    {   
      sprintf(hname,"SetL0TriggerWord(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d) : %d all: %d ",fL0TriggerWord,fL0TriggerWord2,fL0TriggerWord3,fL0TriggerWord4,fL0TriggerWord5,fL0TriggerWord6,fL0TriggerWord7,fL0TriggerWord8,fL0TriggerWord9,fL0TriggerWord10,fnL0TriggerWord,fnallL0TriggerWord);
      pave->AddText(hname);
    } 

  if(fFlagMult)
    {     
      sprintf(hname,"SetMult(%d,%d) : %d all: %d ", fMinMult, fMaxMult,fnMult,fnallMult);
      pave->AddText(hname);
    } 
  if(fFlagVertexIflag)
    { 
      if(fN2VertexIflag!= 99 && fN3VertexIflag != 99)      
	sprintf(hname,"SetVertexIflag(%d,%d,%d) : %d ",fN1VertexIflag
		,fN2VertexIflag
		,fN3VertexIflag
		,fnVertexIflag);  
      if(fN2VertexIflag!= 99 && fN3VertexIflag == 99)      
	sprintf(hname,"SetVertexIflag(%d,%d) : %d ",fN1VertexIflag
		,fN2VertexIflag
		,fnVertexIflag);  
      if(fN2VertexIflag== 99 && fN3VertexIflag == 99)      
	sprintf(hname,"SetVertexIflag(%d) : %d ",fN1VertexIflag
		,fnVertexIflag);  
      
      pave->AddText(hname);
    }
  if(fFlagVertexX)
    {
      sprintf(hname,"SetVertexX(%f,%f) : %d all: %d  ", fMinVertexX, fMaxVertexX,fnVertexX,fnallVertexX);
      pave->AddText(hname);
    }
  if(fFlagVertexY)
    {
      sprintf(hname,"SetVertexY(%f,%f) : %d all: %d", fMinVertexY, fMaxVertexY,fnVertexY,fnallVertexY);
      pave->AddText(hname);
    }
  if(fFlagVertexZ)
    {
      sprintf(hname,"SetVertexZ(%f,%f) : %d all: %d", fMinVertexZ, fMaxVertexZ, fnVertexZ,fnallVertexZ);
      pave->AddText(hname);
    }
  if(fFlagEVeto)
    {
      sprintf(hname,"SetEVeto(%f,%f) : %d ", fMinEVeto, fMaxEVeto,fnEVeto);
      pave->AddText(hname);
    }
  return pave;
}

//______________________________________________________________________________
 void  TStMuCutEventJet::PrintCutList()
{
  //
  // Prints the defined cuts and the cut-statistic
  //

  GetCutList()->Print();
}



Int_t  TStMuCutEventJet::GetNumTracks(StMuEvent *Event)
{
  StEventSummary &eventsum = Event->eventSummary();
  return eventsum.numberOfTracks();
}

Int_t  TStMuCutEventJet::GetNumGoodTracks(StMuEvent *Event)
{ 

  //  Int_t referencemult = -999;
 
  //if(fAuAuRefCheck) referencemult = Event->grefmult();
  //else referencemult = Event->refMult();
 return fAuAuRefCheck ? Event->grefmult() : Event->refMult();
 //return referencemult;
  
 }


Float_t  TStMuCutEventJet::GetVertexZ(StMuEvent *Event)
{
  StEventSummary &eventsum = Event->eventSummary();
  return (eventsum.primaryVertexPosition()).z() ;   
}


Float_t  TStMuCutEventJet::GetVertexY(StMuEvent *Event)
{
  StEventSummary &eventsum = Event->eventSummary();
  return (eventsum.primaryVertexPosition()).y() ;  
}

Float_t  TStMuCutEventJet::GetVertexX(StMuEvent *Event)
{
  StEventSummary &eventsum = Event->eventSummary();
  return (eventsum.primaryVertexPosition()).x() ;    
}


UInt_t TStMuCutEventJet::GetL0TriggerWord(StMuEvent *Event)
{ 
  StL0Trigger& l0Trigger  = Event->l0Trigger();
  return l0Trigger.triggerWord();
}


Double_t  TStMuCutEventJet::GetReactionPlane(StMuEvent *Event, UShort_t s)
{
  return 0;//Event->reactionPlane(s);
}


Double_t  TStMuCutEventJet::GetReactionPlanePtWgt(StMuEvent *Event, UShort_t s)
{
  return 0;//Event->reactionPlanePtWgt(s); 
}
