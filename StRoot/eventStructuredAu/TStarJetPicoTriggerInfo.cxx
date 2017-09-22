#include "TStarJetPicoTriggerInfo.h"
#include "Riostream.h"
ClassImp(TStarJetPicoTriggerInfo)

//____________________________________________________
TStarJetPicoTriggerInfo::TStarJetPicoTriggerInfo()
 : TObject()
   , fEta(0)
   , fPhi(0)
   , fId(0)
   , fADC(0)
   , fBitMap{}
   , fTrigFlag(0)
{}
//____________________________________________________
TStarJetPicoTriggerInfo::TStarJetPicoTriggerInfo(const TStarJetPicoTriggerInfo &t)
: TObject(t)
  , fEta(t.fEta)
  , fPhi(t.fPhi)
  , fId(t.fId)
  , fADC(t.fADC)
  , fBitMap(t.fBitMap)
  , fTrigFlag(t.fTrigFlag)
{}

//____________________________________________________
TStarJetPicoTriggerInfo::~TStarJetPicoTriggerInfo(){
  //destructor
}
//____________________________________________________
void TStarJetPicoTriggerInfo::Clear(Option_t */*Option*/){
  fEta=0;
  fPhi=0;
  fId=0;
  fADC=0;
  fBitMap.reset();
  fTrigFlag=0;
}

/***************** Depricated functions ***************/
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isJPL0(){
  if(fTrigFlag==2)return 1;
  else return 0;
}
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isJPL2(){
  if(fTrigFlag==4)return 1;
  else return 0;
}
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isJPS(){
  if(fTrigFlag==6)return 1;
  else return 0;
}
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isHTL0(){
  if(fTrigFlag==1)return 1;
  else return 0;
}
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isHTL2(){
  if(fTrigFlag==3)return 1;
  else return 0;
}
//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isHTS(){
  if(fTrigFlag==7)return 1;
  else return 0;
}

//____________________________________________________
Int_t TStarJetPicoTriggerInfo::isBBC(){
  if(fTrigFlag==5)return 1;
  else return 0;
}
//____________________________________________________
void TStarJetPicoTriggerInfo::PrintInfo(){
  std::cout<<"=============== Trigger Info =============="<<std::endl;
  if(fTrigFlag==1)std::cout<<"HTL0;  eta="<<fEta<<"   phi="<<fPhi<<"   id="<<fId<<"   ADC="<<fADC<<std::endl;
  if(fTrigFlag==2)std::cout<<"JPL0;  eta="<<fEta<<"   phi="<<fPhi<<"   id="<<fId<<"   ADC="<<fADC<<std::endl;
  if(fTrigFlag==3)std::cout<<"HTL2;  eta="<<fEta<<"   phi="<<fPhi<<"   id="<<fId<<"   ADC="<<fADC<<std::endl;
  if(fTrigFlag==4)std::cout<<"JPL2;  eta="<<fEta<<"   phi="<<fPhi<<"   id="<<fId<<"   ADC="<<fADC<<std::endl;
  std::cout<<"=========================================="<<std::endl;
}
