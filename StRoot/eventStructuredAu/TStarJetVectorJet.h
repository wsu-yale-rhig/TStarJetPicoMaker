#ifndef __TSTARJETVECTORJET_HH
#define __TSTARJETVECTORJET_HH

#include "TStarJetVector.h"
//#include <TLorentzVector.h>
#include <TArrayD.h>
#include <TArrayI.h>

#include <valarray>

class TStarJetVectorJet : public TStarJetVector
{
 public:

  enum FEATURESD
  {
    _AREA = 0,
    _PTCORR = 1,
    _MEDIAN_PT = 2,
    _MEDIAN_PT_4VECT = 3,
    
    _NEUTRAL_PT = 4,
    _TOTAL_PT = 5
  };

  TStarJetVectorJet();  
  TStarJetVectorJet(const TStarJetVectorJet &v);  
  TStarJetVectorJet(const TStarJetVector &v);
  virtual ~TStarJetVectorJet();

  const TArrayI *GetIndexes() const {return &fConstituentIndexes;}
  Int_t          GetNIndexes() const {return fConstituentIndexes.GetSize();}

  Int_t          GetIndex(Int_t i);
  Int_t          GetNOfConstituents() const {return fNConstituents;} 
  void           AddIndex(Int_t idx);

  void           SetArea(Double_t val) {fFeaturesD[_AREA] = val;}
  Double_t       GetArea() const       {return fFeaturesD[_AREA];}

  Double_t       GetSumConstituentsPt() const {return fFeaturesD[_TOTAL_PT];}
  Double_t       GetNeutralConstituentsPt() const {return fFeaturesD[_NEUTRAL_PT];}

  Double_t       GetNeutralFractionPt() const 
  {
    if (fFeaturesD[_TOTAL_PT] != 0)
      return fFeaturesD[_NEUTRAL_PT] / fFeaturesD[_TOTAL_PT];
    else
      return -1;
  }

  void           SetSumConstituentsPt(Double_t val) {fFeaturesD[_TOTAL_PT] = val;}
  void           SetNeutralConstituentsPt(Double_t val) {fFeaturesD[_NEUTRAL_PT] = val;}

  void           SetArea4Vector(Double_t v0, Double_t v1, Double_t v2, Double_t v3)
  {
    fArea4Vector[0] = v0;
    fArea4Vector[1] = v1;
    fArea4Vector[2] = v2;
    fArea4Vector[3] = v3;
  }

  void           SetArea4Vector(const std::valarray< double >& v)
  {
    fArea4Vector[0] = v[0];
    fArea4Vector[1] = v[1];
    fArea4Vector[2] = v[2];
    fArea4Vector[3] = v[3];
  }

  void Clear(const Option_t* option = "");

  TArrayD       *GetArea4Vector() {return &fArea4Vector;};
  
  void AddVector(TStarJetVector *vector);
  void AddVector(TStarJetVectorJet *vector, Double_t weight = 1.);

  TStarJetVectorJet& operator=(const TStarJetVectorJet& v);
  TStarJetVectorJet& operator+=(const TStarJetVectorJet& v);
  TStarJetVectorJet  operator+(const TStarJetVectorJet& v) const;
  TStarJetVectorJet& operator-=(const TStarJetVectorJet& v);
  TStarJetVectorJet  operator-(const TStarJetVectorJet& v) const;

  bool operator==(const TStarJetVectorJet &obj) const;
  bool operator!=(const TStarJetVectorJet &obj) const;
  
  TStarJetVectorJet(const TStarJetVector &v,
		    const TArrayI &ConstituentIndexes,
		    const Int_t   &NConstituents,					 
		    const TArrayD &Features,
		    const TArrayD &Area4Vector,
		    const Double_t leadPt,
		    const Int_t leadIndex);

  void SetLeadingParticle(Int_t idx, Double_t pt)
    {
      fLeadingPt = pt;
      fLeadingIndex = idx;
    }

  Int_t    GetLeadingIndex() { return fLeadingIndex; }
  Double_t GetLeadingPt()    { return fLeadingPt; }

 private:

  TArrayI fConstituentIndexes;
  Int_t   fNConstituents;
  TArrayD fArea4Vector;

  Double_t fLeadingPt; // leading constituent pt
  Int_t    fLeadingIndex; // leading constit index

  ClassDef(TStarJetVectorJet, 1)
};

#endif
