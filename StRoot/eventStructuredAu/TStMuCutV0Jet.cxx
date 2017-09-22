//////////////////////////////////////////////////////////
//                                                      //
//              TStMuCutV0Jet Class                 //
//                                                      //
//////////////////////////////////////////////////////////



#include <iostream>


#include "TStMuCutV0Jet.h"
#include "StStrangeMuDstMaker/StV0MuDst.hh"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
ClassImp(TStMuCutV0Jet)

//______________________________________________________________________________
    TStMuCutV0Jet::TStMuCutV0Jet():TObject()
{ 
  //
  // Default constructor
  //

  Reset();

}

//______________________________________________________________________________

void TStMuCutV0Jet::Reset()
{
  //
  // Resets the cut definition and the counters
  //
  fVerbose      = kFALSE;
  cutV0dcaV0Vertex= 999; // > cut
  cutV0dcaPosVertex = -999; //< cut
  cutV0dcaNegVertex = -999;  // < cut
  cutV0dcaPosNeg = 999; //> cut
  cutV0PosHits = 0; // < cut
  cutV0NegHits = 0; // < cut
  cutV0DecayLength = 999; // < cut
  cutV0NSigma = 999; // < cut
  
}

//______________________________________________________________________________
void TStMuCutV0Jet::SetStandardCutsAuAu()
{   
  cutV0dcaV0Vertex= 0.5; // > cut
  cutV0dcaPosVertex = 1.3; //< cut
  cutV0dcaNegVertex = 1.3;  // < cut
  cutV0dcaPosNeg = 0.8; //> cut
  cutV0PosHits = 15; // < cut
  cutV0NegHits = 15; // < cut
  cutV0DecayLength = 0; // < cut
  cutV0NSigma = 2; // < cut
  }

//______________________________________________________________________________
void TStMuCutV0Jet::SetStandardCutspp()
{   
  cutV0dcaV0Vertex= 0.5; // > cut
  cutV0dcaPosVertex = 1.3; //< cut
  cutV0dcaNegVertex = 1.3;  // < cut
  cutV0dcaPosNeg = 0.8; //> cut
  cutV0PosHits = 15; // < cut
  cutV0NegHits = 15; // < cut
  cutV0DecayLength = 3; // < cut
  cutV0NSigma = 2; // < cut
 }

//______________________________________________________________________________
Int_t TStMuCutV0Jet::CheckV0(StV0MuDst *V0, StMuDst *Mu)
{

  if (fVerbose) cout<<"TStMuCutV0Jet::CheckV0"<<endl;

  //Checks whether a given event passes the defined cuts 
 
  if( V0->topologyMapPos().numberOfHits(kTpcId) < cutV0PosHits){
    if(fVerbose) printf("Event not accepted nHitsPos %d. ", V0->topologyMapPos().numberOfHits(kTpcId));
    return kFALSE;
  }

  if( V0->topologyMapNeg().numberOfHits(kTpcId) < cutV0NegHits){
    if(fVerbose) printf("Event not accepted nHitsNeg %d. ",V0->topologyMapNeg().numberOfHits(kTpcId));
    return kFALSE;
  }
  
  if( V0->decayLengthV0() < cutV0DecayLength) {
    if(fVerbose) printf("Event not accepted decaylength %f. ",V0->decayLengthV0());
    return kFALSE;
  }
  
  if( V0->dcaV0Daughters() > cutV0dcaPosNeg){
    if(fVerbose) printf("Event not accepted dcaPosNeg %f. ",V0->dcaV0Daughters());
    return kFALSE;
  }
  
  if( V0->dcaV0ToPrimVertex() > cutV0dcaV0Vertex ) {
    if(fVerbose) printf("Event not accepted dcaV0Vertex %f. ",V0->dcaV0ToPrimVertex());
    return kFALSE;
  }

  if( V0->dcaPosToPrimVertex() < cutV0dcaPosVertex ){
    if(fVerbose) printf("Event not accepted dcaPosVertex %f. ",V0->dcaPosToPrimVertex());
    return kFALSE;
  }
  
  if( V0->dcaNegToPrimVertex() < cutV0dcaNegVertex ){
    if(fVerbose) printf("Event not accepted dcaNegVertex %f. ",V0->dcaNegToPrimVertex());
   return kFALSE;
  }
  
  // dEdx Cut

  int iPos=0;
  int iNeg=0;

  int nGlobals = Mu->globalTracks()->GetEntries();

  for( int i=0; i<nGlobals; i++){
    if( iPos && iNeg) return kTRUE;
    if( Mu->globalTracks(i)->id() == V0->keyNeg()){
      iNeg = 1;
      if( Mu->globalTracks(i)->nSigmaPion() > cutV0NSigma &&
	  Mu->globalTracks(i)->nSigmaProton() > cutV0NSigma){
	if(fVerbose) printf("Event not accepted nSigma Neg");
	return kFALSE;
      }
    }
    if( Mu->globalTracks(i)->id() == V0->keyPos()){
      iPos = 1;
      if( Mu->globalTracks(i)->nSigmaPion() > cutV0NSigma &&
	  Mu->globalTracks(i)->nSigmaProton() > cutV0NSigma){
	if(fVerbose) printf("Event not accepted nSigma Pos");
	return kFALSE;
      }
    }
  }
  return kTRUE;

}

//______________________________________________________________________________
 void  TStMuCutV0Jet::PrintCutList()
{
  //
  // Prints the defined cuts 
  //
  cout << endl;

  cout << "Pico Jet Cuts: "<< endl;
  cout << " V0 dca to primary vertex " << GetV0dcaV0Vertex() << endl;
  cout << " Pos track dca to primary vertex " << GetV0dcaPosVertex() << endl;
  cout << " Neg track dca to primary vertex " << GetV0dcaNegVertex() << endl;
  cout << " dca between daughters " << GetV0dcaPosNeg() << endl;
  cout << " Number of Pos track hits " << GetV0PosHits() << endl;
  cout << " Number of Neg track hits" << GetV0NegHits() << endl;
  cout << " V0decay length " << GetV0DecayLength() << endl;
  cout << " NSigma of tracks from pion and proton band " << GetV0NSigma() << endl;

}



