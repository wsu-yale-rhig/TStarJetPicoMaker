#include "TStarJetPicoQAHistograms.h"
#include "TStarJetPicoDefinitions.h"

#include <TDirectory.h>
#include <TFile.h>
#include <TFolder.h>
#include <TList.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2D.h>

////////////////////////////////////////////////////////////////
//                                                            //
// TStarJetPicoQAHistograms                                   //
//                                                            //
// QA histograms for STAR jetty picoDSTs.                     //
// We make histograms public on purpose. ;(                   //
//                                                            //
////////////////////////////////////////////////////////////////

ClassImp(TStarJetPicoQAHistograms)

TStarJetPicoQAHistograms *TStarJetPicoQAHistograms::fInstance = 0;

void TStarJetPicoQAHistograms::Init()
{
  //
  // Create directory and initialize the histograms.
  //

  TString pwd = gDirectory->GetPath();
  gDirectory->cd("");

  fDir = new TDirectory("StarJetQAPlots_globaldir", "StarJetQAPlots_globaldir");
  fDir->cd();

  hEventRefMult    = new TH1F("RefMult","RefMult;RefMult;counts",700,0,700);
  hEventVertexZ    = new TH1D("VertexZ","VertexZ;VertexZ (cm);counts",100,-50,50);
  hEventNPrim      = new TH1D("NPrim","NPrim;NPrim;counts",1000,0,1000);
  hEventNPrimCut   = new TH1D("NPrimCut","NPrimCut;NPrimCut;counts",1000,0,1000);
  hEventNTowers    = new TH1D("NTowers","NTowers;NTowers;counts",1000,0,5000);
  hEventNTowersCut = new TH1D("NTowersCut","NTowersCut;NTowersCut;counts",1000,0,5000);
  
  hEventNVpdHitsEastvsWest= new TH2D("hEventVpdEastvsWest","VpdHits;VpdEastHits;VpdWestHits",21,-0.5,21-0.5,21,-0.5,21-0.5);
  hyLocalvsTrackPhi= new TH2D("hyLocalvsTrackPhi","TrackCounts;TrackPhi;TofTraityLocal",80,-4,4,200,-10,10);
  hyLocalvsTrackEta= new TH2D("hyLocalvsTrackEta","TrackCounts;TrackEta;TofTraityLocal",90,-1.5,1.5,200,-10,10);
  hTofTrackEtavsPhi= new TH2D("hTofTrackEtavsPhi","GoodTofTrackCounts;TrackPhi;TrackEta",80,-4,4,90,-1.5,1.5);
  hTrackEtavsPhi   = new TH2D("hTrackEtavsPhi","TrackCounts;TrackPhi;TrackEta",80,-4,4,90,-1.5,1.5);

  //Track QA
  hTrackNhits     = new TH1D("PNhits","PNhits;PNhits;counts",50,0,50);
  hTrackNhitsCut  = new TH1D("PNhitsCut","PNhitsCut;PNhitsCut;counts",50,0,50);
  hTrackDCA       = new TH1D("PDCA","PDCA;PDCA;counts",30,0,3);
  hTrackEta       = new TH1D("PEta","PEta;PEta;counts",30,-1.5,1.5);
  hTrackPhi       = new TH1D("PPhi","PPhi;PPhi;counts",40,-4,4);
  hTrackPoverE    = new TH1D("PpoverE","PpoverE;PpoverE;counts",50,0,10);

  // positive eta FTPC
  hFtpcTrackNhitsCut1  = new TH1D("PNhitsCutFtpc1","PNhitsCutFtpc;PNhitsCutFtpc;counts",50,0,50);
  hFtpcTrackDCA1       = new TH1D("PDCAFtpc1","PDCAFtpc;PDCAFtpc;counts",30,0,3);
  hFtpcTrackEta1       = new TH1D("PEtaFtpc1","PEtaFtpc;PEtaFtpc;counts",30,2.0,4.5);
  hFtpcTrackPhi1       = new TH1D("PPhiFtpc1","PPhiFtpc;PPhiFtpc;counts",40,-4,4);
  hFtpcTrackEtavsPhi1  = new TH2D("hFtpcTrackEtavsPhi1","FtpcTrackCounts;TrackPhi;TrackEta",80,-4,4,90,2.0,4.5);
  // negative eta FTPC
  hFtpcTrackNhitsCut2  = new TH1D("PNhitsCutFtpc2","PNhitsCutFtpc;PNhitsCutFtpc;counts",50,0,50);
  hFtpcTrackDCA2       = new TH1D("PDCAFtpc2","PDCAFtpc;PDCAFtpc;counts",30,0,3);
  hFtpcTrackEta2       = new TH1D("PEtaFtpc2","PEtaFtpc;PEtaFtpc;counts",30,-4.5,-2.0);
  hFtpcTrackPhi2       = new TH1D("PPhiFtpc2","PPhiFtpc;PPhiFtpc;counts",40,-4,4);
  hFtpcTrackEtavsPhi2  = new TH2D("hFtpcTrackEtavsPhi2","FtpcTrackCounts;TrackPhi;TrackEta",80,-4,4,90,-4.5,-2.0);

  hZdcStrip  = new TH2D("hZdcStrip","ZdcStrip;Strip;ADC",32,4.5,36.5,122,-2,120);

  
  //Tower QA
  hTowerEta       = new TH1D("TEta","TEta;TEta;counts",30,-1.5,1.5);
  hTowerEtaC      = new TH1D("TEtaC","TEtaC;TEtaC;counts",30,-1.5,1.5);
  hTowerPhi       = new TH1D("TPhi","TPhi;TPhi;counts",40,-4,4);
  hTowerET        = new TH1D("TEneryT","TEneryT;TEneryT;counts",100,0,50);
  hNMatched       = new TH1D("NMatched","NMatched;NMatched;counts",100,0,500);
  
  hEtaDiff        = new TH1D("EtaDiff","EtaDiff;EtaDiff;counts",100,-1,1);
  hPhiDiff        = new TH1D("PhiDiff","PhiDiff;PhiDiff;counts",100,-10,10);

  hEtaMEtaT  = new TH2D("EtaMEtaT","EtaMEtaT;EtaMatched;EtaTower",90,-1.5,1.5,90,-1.5,1.5);
  hPhiMPhiT  = new TH2D("PhiMPhiT","PhiMPhiT;PhiMatched;PhiTower",100,-4,4,100,-4,4);

  hEtaDeltaEta  = new TH2D("EtaDeltaEta","EtaDeltaEta;Eta;DeltaEta",90,-1.5,1.5,100,-0.05,0.05);
  hPhiDeltaPhi = new TH2D("PhiDeltaPhi","PhiDeltaPhi;Phi;DeltaPhi",100,-4,4,100,-0.05,0.05);

  hPtvsEtMatched  = new TH2D("PtvsEtMatched","PtvsEtMatched;PtvsEtMatched;counts",100,0,50,100,0,50);
  
  hNMatchedvsRefMult = new TH2D("NMatchedvsRefMult","NMatchedvsRefMult;NMatchedvsRefMult;counts",100,0,1000,70,0,700);

  hDeltaEtaDeltaPhiProj=new TH2D("DeltaEtaDeltaPhiProj","DeltaPhiEta;DeltaPhi;DeltaEta",100,-2,2,100,-10,10);
  hDeltaEtaDeltaPhiProjAcc=new TH2D("DeltaEtaDeltaPhiProjAcc","DeltaPhiEtaAcc;DeltaPhiAcc;DeltaEtaAcc",100,-0.1,0.1,100,-0.1,0.1);



  __INFO(Form("Init %s at %p.", this->GetName(), this));

  gDirectory->cd(pwd.Data());

}

TStarJetPicoQAHistograms::TStarJetPicoQAHistograms()
  : TNamed()
  , hEventRefMult(0)
  , hEventVertexZ(0)
  , hEventNPrim(0)
  , hEventNPrimCut(0)
  , hEventNTowers(0)
  , hEventNTowersCut(0)
  , hEventNVpdHitsEastvsWest(0)
  , hyLocalvsTrackPhi(0)
  , hyLocalvsTrackEta(0)
  , hTofTrackEtavsPhi(0)
  , hTrackEtavsPhi(0)
  , hTrackNhits(0)
  , hTrackNhitsCut(0)
  , hTrackDCA(0)
  , hTrackEta(0)
  , hTrackPhi(0)
  , hTrackPoverE(0)
  , hFtpcTrackNhitsCut1(0)
  , hFtpcTrackDCA1(0)
  , hFtpcTrackEta1(0)  
  , hFtpcTrackPhi1(0) 
  , hFtpcTrackEtavsPhi1(0)
  , hFtpcTrackNhitsCut2(0)
  , hFtpcTrackDCA2(0)
  , hFtpcTrackEta2(0)  
  , hFtpcTrackPhi2(0) 
  , hFtpcTrackEtavsPhi2(0)
  , hTowerEta(0)
  , hTowerEtaC(0)
  , hTowerPhi(0)
  , hTowerET(0)
  , hNMatched(0)
  , hEtaDiff(0)
  , hPhiDiff(0)
  , hNMatchedvsRefMult(0)
  , hPtvsEtMatched(0)
  , hEtaMEtaT(0)
  , hPhiMPhiT(0)
  , hEtaDeltaEta(0)
  , hPhiDeltaPhi(0)
  , hDeltaEtaDeltaPhiProj(0)
  , hDeltaEtaDeltaPhiProjAcc(0)

  , fDir(0)
{
  //
  // Default constructor. Calls Init()
  //
  this->SetName("StarJetQAPlotsSingleton");
  this->SetTitle("StarJetQAPlotsSingleton");
  Init();
}

TStarJetPicoQAHistograms::~TStarJetPicoQAHistograms()
{
  //
  // directory should own the histograms...
  //
  delete fDir;
  fDir = 0;
}

TStarJetPicoQAHistograms::TStarJetPicoQAHistograms(const char *name, const char *title)
  : TNamed(name, title)
  , hEventRefMult(0)
  , hEventVertexZ(0)
  , hEventNPrim(0)
  , hEventNPrimCut(0)
  , hEventNTowers(0)
  , hEventNTowersCut(0)
  , hEventNVpdHitsEastvsWest(0)
  , hyLocalvsTrackPhi(0)
  , hyLocalvsTrackEta(0)
  , hTofTrackEtavsPhi(0)
  , hTrackEtavsPhi(0)
  , hTrackNhits(0)
  , hTrackNhitsCut(0)
  , hTrackDCA(0)
  , hTrackEta(0)
  , hTrackPhi(0)
  , hTrackPoverE(0)
  , hFtpcTrackNhitsCut1(0)
  , hFtpcTrackDCA1(0)
  , hFtpcTrackEta1(0)  
  , hFtpcTrackPhi1(0) 
  , hFtpcTrackEtavsPhi1(0)
  , hFtpcTrackNhitsCut2(0)
  , hFtpcTrackDCA2(0)
  , hFtpcTrackEta2(0)  
  , hFtpcTrackPhi2(0) 
  , hFtpcTrackEtavsPhi2(0)
  , hTowerEta(0)
  , hTowerEtaC(0)
  , hTowerPhi(0)
  , hTowerET(0)
  , hNMatched(0)
  , hEtaDiff(0)
  , hPhiDiff(0)
  , hNMatchedvsRefMult(0)
  , hPtvsEtMatched(0)
  , hEtaMEtaT(0)
  , hPhiMPhiT(0)
  , hEtaDeltaEta(0)
  , hPhiDeltaPhi(0)
  , hDeltaEtaDeltaPhiProj(0)
  , hDeltaEtaDeltaPhiProjAcc(0)
  
  , fDir(0)
{
  //
  // Contructor with name and title. Calls Init()
  //

  Init();
}

TStarJetPicoQAHistograms *TStarJetPicoQAHistograms::Instance()
{
  //
  // Return the singleton instance of the class.
  // Create the object if necessary.
  //

  if (TStarJetPicoQAHistograms::fInstance == 0)
    {
      __INFO_FUNCTION(Form("Creating new because singleton TStarJetPicoQAHistograms is %p", 
			   TStarJetPicoQAHistograms::fInstance));
      TStarJetPicoQAHistograms::fInstance = 
	new TStarJetPicoQAHistograms("StarJetQAPlotsSingleton", "StarJetQAPlotsSingleton");

      __INFO_FUNCTION(Form("Creating new %s at %p.", 
			   TStarJetPicoQAHistograms::fInstance->GetName(), 
			   TStarJetPicoQAHistograms::fInstance));
    }

  return TStarJetPicoQAHistograms::fInstance;
}

void TStarJetPicoQAHistograms::Delete(Option_t *option)
{
  //
  // Delete the singleton instance TStarJetPicoQAHistograms::fInstance .
  //

  delete TStarJetPicoQAHistograms::fInstance;
  TStarJetPicoQAHistograms::fInstance = 0;
  TNamed::Delete(option);
}

Int_t TStarJetPicoQAHistograms::WriteHistograms()
{
  //
  // Write histograms into the current directory.
  // Puts the histograms into a TFolder.
  //

  TString pwd = gDirectory->GetPath();
  __INFO(Form("Current path is %s", pwd.Data()));
  Int_t cbytes = -1;
  TObject *obj = 0;
  TIter it(fDir->GetList());
  TFolder *folder = new TFolder("StarJetQAPlots", "StarJetQAPlots");
  while ((obj = it.Next()) != 0)
    {
      //cbytes += obj->Write();
      folder->Add(obj);
    }
  
  cbytes += folder->Write();

  __INFO(Form("Histograms written to %s. Bytes: %d.", gDirectory->GetPath(), cbytes));

  gDirectory->cd(pwd.Data());

  return cbytes;
}

Int_t TStarJetPicoQAHistograms::WriteHistogramsToFile(TFile *fin)
{
  //
  // Write histograms into the specified TFile.
  // Calling WriteHistograms()
  //

  Int_t cbytes = -1;
  if (fin != 0)
    {
      fin->cd();
      cbytes = WriteHistograms();
      __INFO(Form("Histograms written to file %s. Bytes: %d.", fin->GetName(), cbytes));
    }
  else
    {
      __ERROR(Form("Unable to write to file. File pointer is %p", fin));
    }
  return cbytes;
}

Int_t TStarJetPicoQAHistograms::WriteHistogramsToFile(const char* fname)
{
  //
  // Write histograms into a TFile.
  // Open file with path "fname" in a RECREATE mode.
  // Calling WriteHistogramsToFile()
  //

  Int_t retval = 0;
  TString pwd = gDirectory->GetPath();
  gDirectory->cd();
  TFile *fout = new TFile(fname, "RECREATE");
  if (fout != 0)
    {
      if (fout->IsOpen() == kTRUE)
	{
	  retval = WriteHistogramsToFile(fout);
	}
    }
  gDirectory->cd(pwd.Data());  

  return retval;
}
