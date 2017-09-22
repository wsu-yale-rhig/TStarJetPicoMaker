#include "TStarJetVectorContainer.h"

#include "TStarJetVector.h"
#include "TStarJetVectorJet.h"
#include "TLorentzVector.h"

#ifndef __CINT__
//#warning "Defining stuff OK..."
template class TStarJetVectorContainer<TStarJetVector>;
template class TStarJetVectorContainer<TStarJetVectorJet>;
template class TStarJetVectorContainer<TLorentzVector>;
template class TStarJetVectorContainer<TObject>;
#endif

ClassImpT(TStarJetVectorContainer, T)
