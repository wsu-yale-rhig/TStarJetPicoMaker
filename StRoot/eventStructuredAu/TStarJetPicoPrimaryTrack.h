#ifndef __TSTARJETPICOPRIMARYTRACK_HH
#define __TSTARJETPICOPRIMARYTRACK_HH

#include "TMath.h"
#include <TObject.h>

class TStarJetPicoPrimaryTrack : public TObject
{
 public:
  TStarJetPicoPrimaryTrack();
  TStarJetPicoPrimaryTrack(const TStarJetPicoPrimaryTrack &t);

  virtual ~TStarJetPicoPrimaryTrack();

  void    Clear(Option_t *Option = "");

  Int_t   GetCharge()        const {return fCharge;}
  Int_t   GetNOfFittedHits() const {return fNFittedHits;}
  Int_t   GetNOfPossHits()   const {return fNHitsPoss;}
  Int_t   GetKey()           const {return fKey;}
  
  Float_t GetPx()            const {return fPx;} 
  Float_t GetPy()            const {return fPy;} 
  Float_t GetPz()            const {return fPz;} 

  Float_t GetPt()            const {return sqrt(fPx*fPx + fPy*fPy);} 

  Float_t GetEta(); 
  Float_t GetPhi()           const {return TMath::ATan2(fPy,fPx);} 
  Float_t GetDCA()           const {return fDCA;} 
  Float_t GetdEdx()          const {return fdEdx;} 
  Float_t GetdEdxPoints()          const {return fdEdxPoints;} 
  
  Float_t GetNsigmaPion()    const {return fNsigmaPion;}
  Float_t GetNsigmaKaon()    const {return fNsigmaKaon;}
  Float_t GetNsigmaProton()  const {return fNsigmaProton;}
  Float_t GetNsigmaElectron()  const {return fNsigmaElectron;}

  Float_t GetEtaDiffHitProjected() const {return fEtaDiffHitProjected;} // difference between projected and tower hit
  Float_t GetPhiDiffHitProjected() const {return fPhiDiffHitProjected;} // difference between projected and tower hit

  Float_t GetsDCAxy()        const {return fsDCAxy;}
  Float_t GetChi2()          const {return fChi2;}
  Float_t GetChi2PV()        const {return fChi2PV;}

  Int_t   GetFlag()          const {return fFlag;}
  Bool_t   GetBemcMatchFlag()          const {return fBemcMatchFlag;}
  Bool_t   GetTofMatchFlag()          const {return fTofMatchFlag;}

  Float_t GetTofTime()       const {return fTofTime;}
  Float_t GetTofBeta()       const {return fTofBeta;}
  Float_t GetTofyLocal()     const {return fTofyLocal;}

  Int_t GetidTruth()         const {return fidTruth;}
  Int_t GetqaTruth()         const {return fqaTruth;}

  // SETTERS  

  void SetCharge(Int_t val)          {fCharge = val;}
  void SetNOfFittedHits(Int_t val)   {fNFittedHits = val;}
  void SetNOfPossHits(Int_t val)     {fNHitsPoss = val;}
  void SetKey(Int_t val)             {fKey = val;}
  
  void SetPx(Float_t val)            {fPx = val;} 
  void SetPy(Float_t val)            {fPy = val;} 
  void SetPz(Float_t val)            {fPz = val;} 
  
  void SetDCA(Float_t val)           {fDCA = val;} 
  void SetdEdx(Float_t val)          {fdEdx = val;} 
  void SetdEdxPoints(Float_t val)          {fdEdxPoints = val;} 
  
  void SetNsigmaPion(Float_t val)    {fNsigmaPion = val;}
  void SetNsigmaKaon(Float_t val)    {fNsigmaKaon = val;}
  void SetNsigmaProton(Float_t val)  {fNsigmaProton = val;}
  void SetNsigmaElectron(Float_t val) {fNsigmaElectron = val;}

  void SetEtaDiffHitProjected(Float_t val) {fEtaDiffHitProjected=val;} 
  void SetPhiDiffHitProjected(Float_t val) {fPhiDiffHitProjected=val;} 

  void SetsDCAxy(Float_t val)        {fsDCAxy = val;}
  void SetChi2(Float_t val)          {fChi2 = val;}
  void SetChi2PV(Float_t val)        {fChi2PV = val;}

  void SetFlag(Int_t val) {fFlag = val;}
  void SetBemcMatchFlag(Bool_t val)          { fBemcMatchFlag = val;}
  void SetTofMatchFlag(Bool_t val)          { fTofMatchFlag = val;}

  void SetTofTime(Float_t val)       {fTofTime = val;}
  void SetTofBeta(Float_t val)       {fTofBeta = val;}
  void SetTofyLocal(Float_t val)       {fTofyLocal = val;}

  void SetidTruth(Int_t val)         {fidTruth = val;}
  void SetqaTruth(Int_t val)         {fqaTruth = val;}

 protected:
 private:

  Int_t           fCharge;      // was PrimCharge[2056];   //[nPrimTrks]
  Int_t           fNFittedHits; // was PrimNhitsFit[2056];   //[nPrimTrks]
  Int_t           fNHitsPoss;   // was PrimNhitsPoss[2056];   //[nPrimTrks]
  Int_t           fKey;         // was PrimKey[2056];   //[nPrimTrks]	       
  Float_t         fPx;          // was PrimPx[2056];   //[nPrimTrks] 	       
  Float_t         fPy;          // was PrimPy[2056];   //[nPrimTrks] 	       
  Float_t         fPz;          // was PrimPz[2056];   //[nPrimTrks] 	     
  Float_t         fDCA;         // was PrimDca[2056];   //[nPrimTrks] 	       
  Float_t         fdEdx;        // was PrimDedx[2056];   //[nPrimTrks] 	       
  Float_t         fdEdxPoints;        //    //[nPrimTrks] 	       
  Float_t         fNsigmaPion;  // was PrimNsigmaPi[2056];   //[nPrimTrks]     
  Float_t         fNsigmaKaon;  // was PrimNsigmaKaon[2056];   //[nPrimTrks]   
  Float_t         fNsigmaProton;// was PrimNsigmaProton[2056];   //[nPrimTrks]
  Float_t         fNsigmaElectron;// was PrimNsigmaProton[2056];   //[nPrimTrks]

  Float_t         fEtaDiffHitProjected; // difference between projected and tower hit
  Float_t         fPhiDiffHitProjected; // difference between projected and tower hit

  Float_t         fsDCAxy; // signed DCAxy
  Float_t         fChi2; // from StMuTrack::chi2xy - it's overall chi2/ndf of the fit, NOT chi2 in xy direction!!
  Float_t         fChi2PV;  // from StMuTrack::chi2z - it's extra chi2 when Primary Vertex is included into the fit, NOT chi2 in z direction!!

  Int_t           fFlag;
  Bool_t           fBemcMatchFlag;
  Bool_t           fTofMatchFlag;

  Float_t        fTofTime;
  Float_t        fTofBeta;
  Float_t        fTofyLocal;

  Int_t          fidTruth;		// #ly for matching to McTrack in embedding data: the id(STAR MuDst)/key(Yale Pico) for the largest contributor McTrack
  Int_t          fqaTruth;		// #ly for matching to McTrack in embedding data: percentage of hits contributed by the McTrack
  

  // this comment is for reference to original code by Sevil
/*   Int_t           fCharge; // was PrimCharge[2056];   //[nPrimTrks] */
/*   Int_t          fNhits; PrimNhitsFit[2056];   //[nPrimTrks] */
/*   Int_t           PrimNhitsPoss[2056];   //[nPrimTrks] */
/*   Int_t           PrimKey[2056];   //[nPrimTrks] */
/*   Float_t         PrimPx[2056];   //[nPrimTrks] */
/*   Float_t         PrimPy[2056];   //[nPrimTrks] */
/*   Float_t         PrimPz[2056];   //[nPrimTrks] */
/*   Float_t         PrimEta[2056];   //[nPrimTrks] */
/*   Float_t         PrimPhi[2056];   //[nPrimTrks] */
/*   Float_t         PrimDca[2056];   //[nPrimTrks] */
/*   Float_t         PrimDedx[2056];   //[nPrimTrks] */
/*   Float_t         PrimNsigmaPi[2056];   //[nPrimTrks] */
/*   Float_t         PrimNsigmaKaon[2056];   //[nPrimTrks] */
/*   Float_t         PrimNsigmaProton[2056];   //[nPrimTrks] */


   ClassDef(TStarJetPicoPrimaryTrack, 7)

};

#endif
