#ifndef __TSTARJETPICOQAHISTOGRAMS_HH
#define __TSTARJETPICOQAHISTOGRAMS_HH

class TH1F;
class TH1D;
class TH2D;
class TDirectory;
class TFile;

#include <TNamed.h>

class TStarJetPicoQAHistograms : public TNamed
{
 public:
  static TStarJetPicoQAHistograms* Instance();  
  virtual void Delete(Option_t* option);

  virtual ~TStarJetPicoQAHistograms();

  Int_t  WriteHistograms();
  Int_t  WriteHistogramsToFile(TFile *fin);
  Int_t  WriteHistogramsToFile(const char* fname);

  // watch this! we make histo stuff public for convenience!
  // this is tough to swallow ;(

  TH1F *hEventRefMult;//!
  TH1D *hEventVertexZ;//!
  TH1D *hEventNPrim;//!
  TH1D *hEventNPrimCut;//!
  TH1D *hEventNTowers;//!
  TH1D *hEventNTowersCut;//!
 
  TH2D *hEventNVpdHitsEastvsWest;//!
  TH2D *hyLocalvsTrackPhi;//!
  TH2D *hyLocalvsTrackEta;//!
  TH2D *hTofTrackEtavsPhi;//!
  TH2D *hTrackEtavsPhi;//!
 
  //Track QA
  TH1D *hTrackNhits;//!
  TH1D *hTrackNhitsCut;//!
  TH1D *hTrackDCA;//!
  TH1D *hTrackEta;//!
  TH1D *hTrackPhi;//!
  TH1D *hTrackPoverE;//!
  
  // positive eta FTPC
  TH1D* hFtpcTrackNhitsCut1;//!
  TH1D* hFtpcTrackDCA1;//!
  TH1D* hFtpcTrackEta1;//!
  TH1D* hFtpcTrackPhi1;//!
  TH2D* hFtpcTrackEtavsPhi1;//!
  // negative eta FTPC
  TH1D* hFtpcTrackNhitsCut2;//!
  TH1D* hFtpcTrackDCA2;//!
  TH1D* hFtpcTrackEta2;//!
  TH1D* hFtpcTrackPhi2;//!
  TH2D* hFtpcTrackEtavsPhi2;//!

  TH2D* hZdcStrip;//!

  //Tower QA
  TH1D *hTowerEta;//!
  TH1D *hTowerEtaC;//!
  TH1D *hTowerPhi;//!
  TH1D *hTowerET;//!
  TH1D *hNMatched;//!
  TH1D *hEtaDiff;//!
  TH1D *hPhiDiff;//!

  TH2D *hNMatchedvsRefMult;//!
  TH2D *hPtvsEtMatched;//!
  TH2D *hEtaMEtaT;//!
  TH2D *hPhiMPhiT;//!
  TH2D *hEtaDeltaEta;//!
  TH2D *hPhiDeltaPhi;//!

  TH2D *hDeltaEtaDeltaPhiProj;//!
  TH2D *hDeltaEtaDeltaPhiProjAcc;//!


 private:  

  TStarJetPicoQAHistograms(const char *name, const char *title);
  TStarJetPicoQAHistograms();

  TDirectory *fDir;//!

  static TStarJetPicoQAHistograms* fInstance;//!

  void Init();

  ClassDef(TStarJetPicoQAHistograms, 0)
};

#endif
