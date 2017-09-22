#ifndef __TSTARJETPICOUTILS_HH
#define __TSTARJETPICOUTILS_HH

#include <TObject.h>
#include <TString.h>

class TStarJetPicoEvent;
class TStarJetPicoTower;
class TStarJetPicoPrimaryTrack;
class TStarJetPicoReaderBase;
class TChain;
class TStarJetVector;

#include "TStarJetVectorContainer.h"

class TStarJetPicoUtils : public TObject
{
 public:

  static Float_t GetTowerPoverE(TStarJetPicoTower *tower, TStarJetPicoPrimaryTrack *track);
  static Float_t GetTowerPoverE(TStarJetPicoEvent *event, TStarJetPicoTower *tower, Int_t trackindex);
  static Bool_t IsElectron(TStarJetPicoTower *tower, TStarJetPicoPrimaryTrack *track);
  static Bool_t IsElectron(TStarJetPicoEvent *event, TStarJetPicoTower *tower, Int_t trackindex);

  static TChain* BuildChainFromDirectory(const char *dirPath, 
					 const char *treeName = "JetTree",
					 Int_t nFiles = -1,
					 Int_t nSkipFiles = 0,
					 TChain *chain = 0);

  static TChain* BuildChainFromDirectoryWithPattern(const char *dirPath, 
						    const char *treeName = "JetTree",
						    const char *pattern = ".root",
						    Int_t nFiles = -1,
						    Int_t nSkipFiles = 0,
						    TChain *chain = 0);

  static TChain* BuildChainFromFileList(const char *clist, 
					const char *treeName = "JetTree",
					Int_t nFiles = -1,
					Int_t nSkipFiles = 0,
					TChain *chain = 0);
  
  static TString GetTriggerIdsString(TStarJetPicoEvent *ev);

  static void PrintPicoReaderInfo(TStarJetPicoReaderBase *reader);

  static void RandomizeContainerInPhi(TStarJetVectorContainer<TStarJetVector>* cont);
  static void    RotateContainerInPhi(TStarJetVectorContainer<TStarJetVector>* cont, Double_t phi);

  static void FillQAHistogramsFromPicoReader(TStarJetPicoReaderBase *reader);

 private:

  TStarJetPicoUtils() : TObject() {;}
  virtual ~TStarJetPicoUtils() {;}
  
  ClassDef(TStarJetPicoUtils, 0)
};

#endif
