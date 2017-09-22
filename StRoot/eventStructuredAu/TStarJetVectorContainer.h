#ifndef __TSTARJETVECTORCONTAINER__HH
#define __TSTARJETVECTORCONTAINER__HH

#include <TObject.h>
#include <TRef.h>
#include <TClonesArray.h>
#include <TClass.h>

#include <TArrayI.h>
#include <TArrayD.h>

#include "TStarJetPicoDefinitions.h"

template <class T>
class TStarJetVectorContainer : public TObject
{
 public:
  
  TStarJetVectorContainer();
  TStarJetVectorContainer(const TStarJetVectorContainer<T> &t);
  virtual ~TStarJetVectorContainer();

  void           Clear(Option_t *Option = "");
  void           Reset(Option_t *Option = "");

  TClonesArray  *GetArray() const {return fElements;}
  Int_t          GetEntries() const {return fNEntries;}

  // use those in a consistent way - either one for each instance
  void           Add(T *part);

  void           AddContainer(TStarJetVectorContainer<T> *t);
  void           CopyFeatures(TStarJetVectorContainer<T> *t);

  T              *Get(Int_t n);

  void           PrintAll(Option_t *Option = "");

  void           SetFeature(Double_t val, Int_t what) {fFeatures[what] = val;}
  Double_t       GetFeature(Int_t what) {return fFeatures[what];}

  void           SetRefMult(Int_t val) {fRefMult = val;}
  Int_t          GetRefMult() {return fRefMult;}

 protected:

 private:
  TClonesArray        *fElements; //->array of elements
  //static TClonesArray *fgElements; //!
  Int_t                fNEntries;
  TRef                 fLastElement;

  TArrayD              fFeatures;
  Int_t                fRefMult; //reference multiplicity

  ClassDefT(TStarJetVectorContainer<T>, 1)
};

//----------------------------------------------------------//

template <class T>
TStarJetVectorContainer<T>::TStarJetVectorContainer()
  : TObject()
  , fElements(0)
  , fNEntries(0)
  , fFeatures(_NUMBER_OF_EVENT_FEATURES)
  , fRefMult(0)
{
  if (fElements == 0)
    {
      TString tname = T::Class()->GetName();
      //__INFO(Form("Creating class for %s", tname.Data()));
      fElements = new TClonesArray(tname.Data(), 1000);
    }
  fNEntries = 0;
}

template <class T>
TStarJetVectorContainer<T>::TStarJetVectorContainer(const TStarJetVectorContainer<T> &t)
  : TObject(t)
  , fElements(t.fElements)
  , fNEntries(t.fNEntries)
  , fFeatures(_NUMBER_OF_EVENT_FEATURES)
  , fRefMult(0)
{
  ;
}

template <class T>
TStarJetVectorContainer<T>::~TStarJetVectorContainer()
{
  //Clear();
  Reset();
}

template <class T>
void TStarJetVectorContainer<T>::Clear(Option_t */*Option*/)
{
  // this costs huge mem!
  //fElements->Clear("C"); 
  // delete not...
  fElements->Delete();
  fNEntries = 0;  
  fFeatures.Set(_NUMBER_OF_EVENT_FEATURES);
  fFeatures.Reset(0.0);
  fRefMult = 0;
}

template <class T>
void TStarJetVectorContainer<T>::PrintAll(Option_t *Option)
{
  this->Print(Option);
  for (Int_t i = 0; i < this->GetEntries(); i++)
    {
      T *temp = this->Get(i);
      temp->Print(Option);
    }  
}

template <class T>
void TStarJetVectorContainer<T>::Reset(Option_t */*Option*/)
{
  fElements->Clear("C"); 
  delete fElements;
  fElements = 0;
  fNEntries = 0;  
  fFeatures.Set(_NUMBER_OF_EVENT_FEATURES);
  fFeatures.Reset(0.0);
  fRefMult = 0;
}

template <class T>
void TStarJetVectorContainer<T>::Add(T *obj)
{
  TClonesArray &arr = *fElements;
  new(arr[fNEntries++]) T(*obj);
  //T *newObj = new(arr[fNEntries++]) T(*obj);
  //__INFO(Form("new 0x%x", newObj));
}

template <class T>
void TStarJetVectorContainer<T>::AddContainer(TStarJetVectorContainer<T> *t)
{
  if (t != 0)
    {
      for (Int_t i = 0; i < t->GetEntries(); i++)
	{
	  T *temp = t->Get(i);
	  Add(temp);
	}
    }
}

template <class T>
void TStarJetVectorContainer<T>::CopyFeatures(TStarJetVectorContainer<T> *t)
{
  for (Int_t i = 0; i < fFeatures.GetSize(); i++)
    {
      fFeatures[i] = t->GetFeature(i);
    }
}

template <class T>
T *TStarJetVectorContainer<T>::Get(Int_t n)
{
  if (n < fNEntries)
    {
      return (T *)fElements->At(n);
    }
  return 0;
}

#endif
