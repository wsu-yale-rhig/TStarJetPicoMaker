#ifndef __TSTARJETPICOTRIGGERINFO_HH
#define __TSTARJETPICOTRIGGERINFO_HH

#include <TObject.h>
#include <TString.h>

#include <bitset>

/* currently supports barrel HT triggers
   as well as jet patch triggers. 
   HT triggers will have ADC, tower ID,
   eta, phi & trigger bits given by 
   StTriggerSimuMaker.
 
   Jet patch triggers only have trigger bits,
   ADC, and jet patch ID. No eta or phi
 
   bitmap layout:
   bit 1: barrel high tower 1
   bit 2: barrel high tower 2
   bit 3: barrel high tower 3
   bit 4: jet patch 0
   bit 5: jet patch 1
   bit 6: jet patch 2
   bit 7-31: open
 */

class TStarJetPicoTriggerInfo : public TObject
{
 public:
  TStarJetPicoTriggerInfo();
  TStarJetPicoTriggerInfo(const TStarJetPicoTriggerInfo &t);
  virtual ~TStarJetPicoTriggerInfo();

  void    Clear(Option_t *Option = "");

  //Setters
  void SetEta(Float_t eta) {fEta=eta;}
  void SetPhi(Float_t phi) {fPhi=phi;}
  void SetId(Int_t id)     {fId=id;}
  void SetADC(Int_t ADC)   {fADC=ADC;}
  
  void SetBitMap(Int_t map )           {fBitMap = map;}
  void SetBitMap(std::bitset<32> map ) {fBitMap = map;}
  void SetBit(Int_t bit, Bool_t flag ) {fBitMap.set( bit, flag );}
  
  //Getters
  Float_t GetEta()            const {return fEta;}
  Float_t GetPhi()            const {return fPhi;}
  Int_t   GetId()             const {return fId;} // tower ID or jet patch ID
  Int_t   GetADC()            const {return fADC;}
  Bool_t  GetBit(Int_t bit)   const {return fBitMap[bit];}
  std::bitset<32> GetBitMap() const {return fBitMap;}
  
  Bool_t isBHT1() const {return fBitMap[1];}
  Bool_t isBHT2() const {return fBitMap[2];}
  Bool_t isBHT3() const {return fBitMap[3];}
  Bool_t  isJP0() const {return fBitMap[4];}
  Bool_t  isJP1() const {return fBitMap[5];}
  Bool_t  isJP2() const {return fBitMap[6];}
  
  
  /* ************* depricated ************* 
     list of data sets produced using fTrigFlag
     instead of fBitMap
     Au+Au y7, y11
     p+p   y6, y12
   */
  void  SetTriggerFlag(Int_t flag) {fTrigFlag=flag;}
  Int_t GetTriggerFlag() const     {return fTrigFlag;}
  Int_t isJPL0();
  Int_t isJPL2(); 
  Int_t isJPS();
  Int_t isHTL0();
  Int_t isHTL2();
  Int_t isHTS();
  Int_t isBBC();
  void  PrintInfo();


 private:
  Float_t fEta; // eta of the tower/patch in the reference frame 0,0,0
  Float_t fPhi; // phi of the tower/patch in the reference frame 0,0,0
  Int_t   fId;  // id of the tower that fired this trigger
  Int_t   fADC; // its ADC value
  
  std::bitset<32>  fBitMap;
  
  /****** depricated *****/
  Int_t fTrigFlag;//1=HTL0, 2=JPL0, 3=HTL2, 4=JPL2
  

 ClassDef(TStarJetPicoTriggerInfo, 3)
   };

#endif
