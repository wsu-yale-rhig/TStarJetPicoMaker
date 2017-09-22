#ifdef __CINT__
 
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class TStarJetPicoEvent++;
#pragma link C++ class TStarJetPicoEventHeader++;
#pragma link C++ class TStarJetPicoPrimaryTrack++;
#pragma link C++ class TStarJetPicoTower++;
#pragma link C++ class TStarJetPicoV0++;
#pragma link C++ class TStarJetPicoTriggerInfo++;

#pragma link C++ class TStarJetPicoDefinitions;
#pragma link C++ class TStarJetPicoUtils;
#pragma link C++ class TStarJetPicoQAHistograms;

#pragma link C++ class TStarJetPicoV0Cuts++;
#pragma link C++ class TStarJetPicoEventCuts++;
#pragma link C++ class TStarJetPicoTrackCuts++;
#pragma link C++ class TStarJetPicoTowerCuts++;

#pragma link C++ class TStarJetPicoReaderBase;
#pragma link C++ class TStarJetPicoReader;
#pragma link C++ class TStarJetReaderParticleContainer;

#pragma link C++ class TStarJetVector++;
#pragma link C++ class TStarJetVectorJet++;
#pragma link C++ template <T> class TStarJetVectorContainer<T>++;

#pragma link C++ class TStarJetVectorContainer<TStarJetVector>++;
#pragma link C++ class TStarJetVectorContainer<TStarJetVectorJet>++;
#pragma link C++ class TStarJetVectorContainer<TLorentzVector>++;
#pragma link C++ class TStarJetVectorContainer<TObject>++;

#pragma link C++ class TStarJetPicoDemoClass++;
#endif
