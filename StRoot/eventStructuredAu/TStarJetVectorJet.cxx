#include "TStarJetVectorJet.h"
#include "TStarJetPicoDefinitions.h"
#include "TStarJetVector.h"

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// TStarJetPicoVectorJet                                                   //
//                                                                         //
// TLorentzVector->TStarJetPicoVector with "Features" and "Constituents"   //
//                                                                         //
// - to be used to store ouput jets from the jet finders                   //
// -- implements area4vector and new enums from TStarJetPicoVector         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

ClassImp(TStarJetVectorJet)

#include <iostream>

using namespace std;

#define __INITIAL_NUMBER_OF_JET_CONSTITUENTS 1
#define __AREA4VECTOR_N 4

TStarJetVectorJet::TStarJetVectorJet()
  : TStarJetVector()
  , fConstituentIndexes(__INITIAL_NUMBER_OF_JET_CONSTITUENTS)
  , fNConstituents(0)
  , fArea4Vector(__AREA4VECTOR_N)
  , fLeadingPt(0.0)
  , fLeadingIndex(-1)
{
  Clear();
}

TStarJetVectorJet::TStarJetVectorJet(const TStarJetVectorJet &v)
  : TStarJetVector(v)
  , fConstituentIndexes(v.fConstituentIndexes)
  , fNConstituents(v.fNConstituents)
  , fArea4Vector(v.fArea4Vector)
  , fLeadingPt(v.fLeadingPt)
  , fLeadingIndex(v.fLeadingIndex)
{
  ;
}

TStarJetVectorJet::TStarJetVectorJet(const TStarJetVector &v)
  : TStarJetVector(v)
  , fConstituentIndexes(__INITIAL_NUMBER_OF_JET_CONSTITUENTS)
  , fNConstituents(0)
  , fArea4Vector(__AREA4VECTOR_N)
  , fLeadingPt(0.0)
  , fLeadingIndex(-1)
{
  ;
}

TStarJetVectorJet::TStarJetVectorJet(const TStarJetVector &v,
				     const TArrayI &ConstituentIndexes,
				     const Int_t   &NConstituents,					 
				     const TArrayD &Features,
				     const TArrayD &Area4Vector,
				     const Double_t leadPt,
				     const Int_t leadIndex)
  : TStarJetVector(v)
  , fConstituentIndexes(ConstituentIndexes)
  , fNConstituents(NConstituents)
  , fArea4Vector(Area4Vector)
  , fLeadingPt(leadPt)
  , fLeadingIndex(leadIndex)
{
  // override featuresD
  fFeaturesD = Features;
}

TStarJetVectorJet::~TStarJetVectorJet()
{
  ;
}

Int_t TStarJetVectorJet::GetIndex(Int_t i)
{ 
  if ( i >= fNConstituents )
    {
      __WARNING(Form("Asking index %d but number of filled constituents is %d.", i, fNConstituents));
    }

  return fConstituentIndexes.At(i);
}

void TStarJetVectorJet::Clear(const Option_t *option)
{
  TStarJetVector::Clear(option);
  fConstituentIndexes.Set(__INITIAL_NUMBER_OF_JET_CONSTITUENTS);
  fConstituentIndexes.Reset(-1);
  fNConstituents = 0;
  fArea4Vector.Set(__AREA4VECTOR_N);
  fArea4Vector.Reset(0.0);
  fLeadingPt = 0.0;
  fLeadingIndex = -1;
}

void TStarJetVectorJet::AddIndex(Int_t idx)
{
  if (fNConstituents < fConstituentIndexes.GetSize())
    {
      fConstituentIndexes[fNConstituents++] = idx;
    }
  else
    {
      //Int_t inewsize = fConstituentIndexes.GetSize() * 2;
      Int_t inewsize = fConstituentIndexes.GetSize() + 1; //save mem and disk space
      fConstituentIndexes.Set(inewsize);
      AddIndex(idx);
    }
}

void TStarJetVectorJet::AddVector(TStarJetVector *vector)
{
  TLorentzVector &vec = *((TLorentzVector*)this);
  TLorentzVector &vec2 = *((TLorentzVector*)vector);
  vec += vec2;
}

void TStarJetVectorJet::AddVector(TStarJetVectorJet *vector, Double_t weight)
{
  TLorentzVector &vec = *((TLorentzVector*)this);
  TLorentzVector &vec2 = *((TLorentzVector*)vector);
  vec += weight * vec2;
}

TStarJetVectorJet& TStarJetVectorJet::operator=(const TStarJetVectorJet& v)
{
  if (this != &v)
    {
      this->TLorentzVector::operator=(v);
      this->fConstituentIndexes = v.fConstituentIndexes;
      this->fNConstituents = v.fNConstituents;      
      this->fArea4Vector = v.fArea4Vector;

      this->fFeaturesD = v.fFeaturesD;
      this->fFeaturesI = v.fFeaturesI;

      this->fLeadingPt = v.fLeadingPt;
      this->fLeadingIndex = v.fLeadingIndex;
    }
  return *this;
}

TStarJetVectorJet& TStarJetVectorJet::operator+=(const TStarJetVectorJet& v)
{
  this->TLorentzVector::operator+=(v);

  for (Int_t i = 0; i < v.fNConstituents; i++)
    {
      AddIndex(v.fConstituentIndexes[i]);
    }
  this->fNConstituents += v.fNConstituents;      

  SetArea4Vector(this->fArea4Vector[0] + v.fArea4Vector[0],
		 this->fArea4Vector[1] + v.fArea4Vector[1],
		 this->fArea4Vector[2] + v.fArea4Vector[2],
		 this->fArea4Vector[3] + v.fArea4Vector[3]);
  return *this;
}

TStarJetVectorJet& TStarJetVectorJet::operator-=(const TStarJetVectorJet& v)
{
  this->TLorentzVector::operator-=(v);

  for (Int_t i = 0; i < v.fNConstituents; i++)
    {
      AddIndex(v.fConstituentIndexes[i]);
    }
  this->fNConstituents += v.fNConstituents;      

  SetArea4Vector(this->fArea4Vector[0] + v.fArea4Vector[0],
		 this->fArea4Vector[1] + v.fArea4Vector[1],
		 this->fArea4Vector[2] + v.fArea4Vector[2],
		 this->fArea4Vector[3] + v.fArea4Vector[3]);
  return *this;
}

TStarJetVectorJet TStarJetVectorJet::operator+(const TStarJetVectorJet& v) const
{
  TStarJetVectorJet a(*this);
  return TStarJetVectorJet(a += v);
}

TStarJetVectorJet TStarJetVectorJet::operator-(const TStarJetVectorJet& v) const
{
  TStarJetVectorJet a(*this);
  return TStarJetVectorJet(a -= v);
}

bool TStarJetVectorJet::operator==(const TStarJetVectorJet &v) const
{
  if (this->TLorentzVector::operator!=(v))
    {
      return false;
    }

  if (this->fNConstituents != v.fNConstituents)
    {
      return false;
    }

  for (Int_t i = 0; i < this->fConstituentIndexes.GetSize(); i++)
    {
      if (this->fConstituentIndexes[i] != v.fConstituentIndexes[i])
	{
	  return false;
	}
    }

  if (this->fFeaturesD.GetSize() != v.fFeaturesD.GetSize())
    {
      return false;
    }
   
  if (this->fArea4Vector[0] != v.fArea4Vector[0] ||
      this->fArea4Vector[1] != v.fArea4Vector[1] ||
      this->fArea4Vector[2] != v.fArea4Vector[2] ||
      this->fArea4Vector[3] != v.fArea4Vector[3])
    {
      return false;
    }
  
  return true;
}

bool TStarJetVectorJet::operator!=(const TStarJetVectorJet &obj) const
{
  return !(*this == obj);
}
