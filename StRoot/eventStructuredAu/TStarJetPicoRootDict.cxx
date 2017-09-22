// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TStarJetPicoRootDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TStarJetPicoDefinitions.h"
#include "TStarJetPicoDemoClass.h"
#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventCuts.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoQAHistograms.h"
#include "TStarJetPicoReader.h"
#include "TStarJetPicoReaderBase.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoTowerCuts.h"
#include "TStarJetPicoTrackCuts.h"
#include "TStarJetPicoTriggerInfo.h"
#include "TStarJetPicoUtils.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoV0Cuts.h"
#include "TStarJetVector.h"
#include "TStarJetVectorContainer.h"
#include "TStarJetVectorJet.h"
#include "TStarJetReaderParticleContainer.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void streamer_TStarJetPicoDefinitions(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoDefinitions*)
   {
      ::TStarJetPicoDefinitions *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoDefinitions >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoDefinitions", ::TStarJetPicoDefinitions::Class_Version(), "TStarJetPicoDefinitions.h", 22,
                  typeid(::TStarJetPicoDefinitions), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoDefinitions::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetPicoDefinitions) );
      instance.SetStreamerFunc(&streamer_TStarJetPicoDefinitions);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoDefinitions*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoDefinitions*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoDefinitions*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoTrackCuts(void *p = 0);
   static void *newArray_TStarJetPicoTrackCuts(Long_t size, void *p);
   static void delete_TStarJetPicoTrackCuts(void *p);
   static void deleteArray_TStarJetPicoTrackCuts(void *p);
   static void destruct_TStarJetPicoTrackCuts(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoTrackCuts*)
   {
      ::TStarJetPicoTrackCuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoTrackCuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoTrackCuts", ::TStarJetPicoTrackCuts::Class_Version(), "TStarJetPicoTrackCuts.h", 8,
                  typeid(::TStarJetPicoTrackCuts), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoTrackCuts::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoTrackCuts) );
      instance.SetNew(&new_TStarJetPicoTrackCuts);
      instance.SetNewArray(&newArray_TStarJetPicoTrackCuts);
      instance.SetDelete(&delete_TStarJetPicoTrackCuts);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoTrackCuts);
      instance.SetDestructor(&destruct_TStarJetPicoTrackCuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoTrackCuts*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoTrackCuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoTrackCuts*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoDemoClass(void *p = 0);
   static void *newArray_TStarJetPicoDemoClass(Long_t size, void *p);
   static void delete_TStarJetPicoDemoClass(void *p);
   static void deleteArray_TStarJetPicoDemoClass(void *p);
   static void destruct_TStarJetPicoDemoClass(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoDemoClass*)
   {
      ::TStarJetPicoDemoClass *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoDemoClass >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoDemoClass", ::TStarJetPicoDemoClass::Class_Version(), "TStarJetPicoDemoClass.h", 6,
                  typeid(::TStarJetPicoDemoClass), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoDemoClass::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoDemoClass) );
      instance.SetNew(&new_TStarJetPicoDemoClass);
      instance.SetNewArray(&newArray_TStarJetPicoDemoClass);
      instance.SetDelete(&delete_TStarJetPicoDemoClass);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoDemoClass);
      instance.SetDestructor(&destruct_TStarJetPicoDemoClass);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoDemoClass*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoDemoClass*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoDemoClass*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoEventHeader(void *p = 0);
   static void *newArray_TStarJetPicoEventHeader(Long_t size, void *p);
   static void delete_TStarJetPicoEventHeader(void *p);
   static void deleteArray_TStarJetPicoEventHeader(void *p);
   static void destruct_TStarJetPicoEventHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoEventHeader*)
   {
      ::TStarJetPicoEventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoEventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoEventHeader", ::TStarJetPicoEventHeader::Class_Version(), "TStarJetPicoEventHeader.h", 9,
                  typeid(::TStarJetPicoEventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoEventHeader::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoEventHeader) );
      instance.SetNew(&new_TStarJetPicoEventHeader);
      instance.SetNewArray(&newArray_TStarJetPicoEventHeader);
      instance.SetDelete(&delete_TStarJetPicoEventHeader);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoEventHeader);
      instance.SetDestructor(&destruct_TStarJetPicoEventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoEventHeader*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoEventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoEventHeader*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoEvent(void *p = 0);
   static void *newArray_TStarJetPicoEvent(Long_t size, void *p);
   static void delete_TStarJetPicoEvent(void *p);
   static void deleteArray_TStarJetPicoEvent(void *p);
   static void destruct_TStarJetPicoEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoEvent*)
   {
      ::TStarJetPicoEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoEvent", ::TStarJetPicoEvent::Class_Version(), "TStarJetPicoEvent.h", 13,
                  typeid(::TStarJetPicoEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoEvent::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoEvent) );
      instance.SetNew(&new_TStarJetPicoEvent);
      instance.SetNewArray(&newArray_TStarJetPicoEvent);
      instance.SetDelete(&delete_TStarJetPicoEvent);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoEvent);
      instance.SetDestructor(&destruct_TStarJetPicoEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoEvent*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoEventCuts(void *p = 0);
   static void *newArray_TStarJetPicoEventCuts(Long_t size, void *p);
   static void delete_TStarJetPicoEventCuts(void *p);
   static void deleteArray_TStarJetPicoEventCuts(void *p);
   static void destruct_TStarJetPicoEventCuts(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoEventCuts*)
   {
      ::TStarJetPicoEventCuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoEventCuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoEventCuts", ::TStarJetPicoEventCuts::Class_Version(), "TStarJetPicoEventCuts.h", 10,
                  typeid(::TStarJetPicoEventCuts), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoEventCuts::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoEventCuts) );
      instance.SetNew(&new_TStarJetPicoEventCuts);
      instance.SetNewArray(&newArray_TStarJetPicoEventCuts);
      instance.SetDelete(&delete_TStarJetPicoEventCuts);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoEventCuts);
      instance.SetDestructor(&destruct_TStarJetPicoEventCuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoEventCuts*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoEventCuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoEventCuts*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoPrimaryTrack(void *p = 0);
   static void *newArray_TStarJetPicoPrimaryTrack(Long_t size, void *p);
   static void delete_TStarJetPicoPrimaryTrack(void *p);
   static void deleteArray_TStarJetPicoPrimaryTrack(void *p);
   static void destruct_TStarJetPicoPrimaryTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoPrimaryTrack*)
   {
      ::TStarJetPicoPrimaryTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoPrimaryTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoPrimaryTrack", ::TStarJetPicoPrimaryTrack::Class_Version(), "TStarJetPicoPrimaryTrack.h", 7,
                  typeid(::TStarJetPicoPrimaryTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoPrimaryTrack::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoPrimaryTrack) );
      instance.SetNew(&new_TStarJetPicoPrimaryTrack);
      instance.SetNewArray(&newArray_TStarJetPicoPrimaryTrack);
      instance.SetDelete(&delete_TStarJetPicoPrimaryTrack);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoPrimaryTrack);
      instance.SetDestructor(&destruct_TStarJetPicoPrimaryTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoPrimaryTrack*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoPrimaryTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoPrimaryTrack*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TStarJetPicoQAHistograms(void *p);
   static void deleteArray_TStarJetPicoQAHistograms(void *p);
   static void destruct_TStarJetPicoQAHistograms(void *p);
   static void streamer_TStarJetPicoQAHistograms(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoQAHistograms*)
   {
      ::TStarJetPicoQAHistograms *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoQAHistograms >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoQAHistograms", ::TStarJetPicoQAHistograms::Class_Version(), "TStarJetPicoQAHistograms.h", 12,
                  typeid(::TStarJetPicoQAHistograms), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoQAHistograms::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetPicoQAHistograms) );
      instance.SetDelete(&delete_TStarJetPicoQAHistograms);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoQAHistograms);
      instance.SetDestructor(&destruct_TStarJetPicoQAHistograms);
      instance.SetStreamerFunc(&streamer_TStarJetPicoQAHistograms);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoQAHistograms*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoQAHistograms*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoQAHistograms*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *TStarJetVectorContainerlETStarJetVectorgR_Dictionary();
   static void TStarJetVectorContainerlETStarJetVectorgR_TClassManip(TClass*);
   static void *new_TStarJetVectorContainerlETStarJetVectorgR(void *p = 0);
   static void *newArray_TStarJetVectorContainerlETStarJetVectorgR(Long_t size, void *p);
   static void delete_TStarJetVectorContainerlETStarJetVectorgR(void *p);
   static void deleteArray_TStarJetVectorContainerlETStarJetVectorgR(void *p);
   static void destruct_TStarJetVectorContainerlETStarJetVectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVectorContainer<TStarJetVector>*)
   {
      ::TStarJetVectorContainer<TStarJetVector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVectorContainer<TStarJetVector> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVectorContainer<TStarJetVector>", ::TStarJetVectorContainer<TStarJetVector>::Class_Version(), "TStarJetVectorContainer.h", 15,
                  typeid(::TStarJetVectorContainer<TStarJetVector>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TStarJetVectorContainerlETStarJetVectorgR_Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVectorContainer<TStarJetVector>) );
      instance.SetNew(&new_TStarJetVectorContainerlETStarJetVectorgR);
      instance.SetNewArray(&newArray_TStarJetVectorContainerlETStarJetVectorgR);
      instance.SetDelete(&delete_TStarJetVectorContainerlETStarJetVectorgR);
      instance.SetDeleteArray(&deleteArray_TStarJetVectorContainerlETStarJetVectorgR);
      instance.SetDestructor(&destruct_TStarJetVectorContainerlETStarJetVectorgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVectorContainer<TStarJetVector>*)
   {
      return GenerateInitInstanceLocal((::TStarJetVectorContainer<TStarJetVector>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TStarJetVectorContainerlETStarJetVectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0)->GetClass();
      TStarJetVectorContainerlETStarJetVectorgR_TClassManip(theClass);
   return theClass;
   }

   static void TStarJetVectorContainerlETStarJetVectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TStarJetVectorContainerlETObjectgR_Dictionary();
   static void TStarJetVectorContainerlETObjectgR_TClassManip(TClass*);
   static void *new_TStarJetVectorContainerlETObjectgR(void *p = 0);
   static void *newArray_TStarJetVectorContainerlETObjectgR(Long_t size, void *p);
   static void delete_TStarJetVectorContainerlETObjectgR(void *p);
   static void deleteArray_TStarJetVectorContainerlETObjectgR(void *p);
   static void destruct_TStarJetVectorContainerlETObjectgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVectorContainer<TObject>*)
   {
      ::TStarJetVectorContainer<TObject> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVectorContainer<TObject> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVectorContainer<TObject>", ::TStarJetVectorContainer<TObject>::Class_Version(), "TStarJetVectorContainer.h", 15,
                  typeid(::TStarJetVectorContainer<TObject>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TStarJetVectorContainerlETObjectgR_Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVectorContainer<TObject>) );
      instance.SetNew(&new_TStarJetVectorContainerlETObjectgR);
      instance.SetNewArray(&newArray_TStarJetVectorContainerlETObjectgR);
      instance.SetDelete(&delete_TStarJetVectorContainerlETObjectgR);
      instance.SetDeleteArray(&deleteArray_TStarJetVectorContainerlETObjectgR);
      instance.SetDestructor(&destruct_TStarJetVectorContainerlETObjectgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVectorContainer<TObject>*)
   {
      return GenerateInitInstanceLocal((::TStarJetVectorContainer<TObject>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TStarJetVectorContainerlETObjectgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0)->GetClass();
      TStarJetVectorContainerlETObjectgR_TClassManip(theClass);
   return theClass;
   }

   static void TStarJetVectorContainerlETObjectgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TStarJetVectorContainerlETLorentzVectorgR_Dictionary();
   static void TStarJetVectorContainerlETLorentzVectorgR_TClassManip(TClass*);
   static void *new_TStarJetVectorContainerlETLorentzVectorgR(void *p = 0);
   static void *newArray_TStarJetVectorContainerlETLorentzVectorgR(Long_t size, void *p);
   static void delete_TStarJetVectorContainerlETLorentzVectorgR(void *p);
   static void deleteArray_TStarJetVectorContainerlETLorentzVectorgR(void *p);
   static void destruct_TStarJetVectorContainerlETLorentzVectorgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVectorContainer<TLorentzVector>*)
   {
      ::TStarJetVectorContainer<TLorentzVector> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVectorContainer<TLorentzVector> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVectorContainer<TLorentzVector>", ::TStarJetVectorContainer<TLorentzVector>::Class_Version(), "TStarJetVectorContainer.h", 15,
                  typeid(::TStarJetVectorContainer<TLorentzVector>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TStarJetVectorContainerlETLorentzVectorgR_Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVectorContainer<TLorentzVector>) );
      instance.SetNew(&new_TStarJetVectorContainerlETLorentzVectorgR);
      instance.SetNewArray(&newArray_TStarJetVectorContainerlETLorentzVectorgR);
      instance.SetDelete(&delete_TStarJetVectorContainerlETLorentzVectorgR);
      instance.SetDeleteArray(&deleteArray_TStarJetVectorContainerlETLorentzVectorgR);
      instance.SetDestructor(&destruct_TStarJetVectorContainerlETLorentzVectorgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVectorContainer<TLorentzVector>*)
   {
      return GenerateInitInstanceLocal((::TStarJetVectorContainer<TLorentzVector>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TStarJetVectorContainerlETLorentzVectorgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0)->GetClass();
      TStarJetVectorContainerlETLorentzVectorgR_TClassManip(theClass);
   return theClass;
   }

   static void TStarJetVectorContainerlETLorentzVectorgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *TStarJetVectorContainerlETStarJetVectorJetgR_Dictionary();
   static void TStarJetVectorContainerlETStarJetVectorJetgR_TClassManip(TClass*);
   static void *new_TStarJetVectorContainerlETStarJetVectorJetgR(void *p = 0);
   static void *newArray_TStarJetVectorContainerlETStarJetVectorJetgR(Long_t size, void *p);
   static void delete_TStarJetVectorContainerlETStarJetVectorJetgR(void *p);
   static void deleteArray_TStarJetVectorContainerlETStarJetVectorJetgR(void *p);
   static void destruct_TStarJetVectorContainerlETStarJetVectorJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVectorContainer<TStarJetVectorJet>*)
   {
      ::TStarJetVectorContainer<TStarJetVectorJet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVectorContainer<TStarJetVectorJet> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVectorContainer<TStarJetVectorJet>", ::TStarJetVectorContainer<TStarJetVectorJet>::Class_Version(), "TStarJetVectorContainer.h", 15,
                  typeid(::TStarJetVectorContainer<TStarJetVectorJet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TStarJetVectorContainerlETStarJetVectorJetgR_Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVectorContainer<TStarJetVectorJet>) );
      instance.SetNew(&new_TStarJetVectorContainerlETStarJetVectorJetgR);
      instance.SetNewArray(&newArray_TStarJetVectorContainerlETStarJetVectorJetgR);
      instance.SetDelete(&delete_TStarJetVectorContainerlETStarJetVectorJetgR);
      instance.SetDeleteArray(&deleteArray_TStarJetVectorContainerlETStarJetVectorJetgR);
      instance.SetDestructor(&destruct_TStarJetVectorContainerlETStarJetVectorJetgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVectorContainer<TStarJetVectorJet>*)
   {
      return GenerateInitInstanceLocal((::TStarJetVectorContainer<TStarJetVectorJet>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TStarJetVectorContainerlETStarJetVectorJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0)->GetClass();
      TStarJetVectorContainerlETStarJetVectorJetgR_TClassManip(theClass);
   return theClass;
   }

   static void TStarJetVectorContainerlETStarJetVectorJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetVector(void *p = 0);
   static void *newArray_TStarJetVector(Long_t size, void *p);
   static void delete_TStarJetVector(void *p);
   static void deleteArray_TStarJetVector(void *p);
   static void destruct_TStarJetVector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVector*)
   {
      ::TStarJetVector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVector", ::TStarJetVector::Class_Version(), "TStarJetVector.h", 8,
                  typeid(::TStarJetVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetVector::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVector) );
      instance.SetNew(&new_TStarJetVector);
      instance.SetNewArray(&newArray_TStarJetVector);
      instance.SetDelete(&delete_TStarJetVector);
      instance.SetDeleteArray(&deleteArray_TStarJetVector);
      instance.SetDestructor(&destruct_TStarJetVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVector*)
   {
      return GenerateInitInstanceLocal((::TStarJetVector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_TStarJetPicoReaderBase(void *p);
   static void deleteArray_TStarJetPicoReaderBase(void *p);
   static void destruct_TStarJetPicoReaderBase(void *p);
   static void streamer_TStarJetPicoReaderBase(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoReaderBase*)
   {
      ::TStarJetPicoReaderBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoReaderBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoReaderBase", ::TStarJetPicoReaderBase::Class_Version(), "TStarJetPicoReaderBase.h", 17,
                  typeid(::TStarJetPicoReaderBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoReaderBase::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetPicoReaderBase) );
      instance.SetDelete(&delete_TStarJetPicoReaderBase);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoReaderBase);
      instance.SetDestructor(&destruct_TStarJetPicoReaderBase);
      instance.SetStreamerFunc(&streamer_TStarJetPicoReaderBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoReaderBase*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoReaderBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoReaderBase*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoReader(void *p = 0);
   static void *newArray_TStarJetPicoReader(Long_t size, void *p);
   static void delete_TStarJetPicoReader(void *p);
   static void deleteArray_TStarJetPicoReader(void *p);
   static void destruct_TStarJetPicoReader(void *p);
   static void streamer_TStarJetPicoReader(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoReader*)
   {
      ::TStarJetPicoReader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoReader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoReader", ::TStarJetPicoReader::Class_Version(), "TStarJetPicoReader.h", 26,
                  typeid(::TStarJetPicoReader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoReader::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetPicoReader) );
      instance.SetNew(&new_TStarJetPicoReader);
      instance.SetNewArray(&newArray_TStarJetPicoReader);
      instance.SetDelete(&delete_TStarJetPicoReader);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoReader);
      instance.SetDestructor(&destruct_TStarJetPicoReader);
      instance.SetStreamerFunc(&streamer_TStarJetPicoReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoReader*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoReader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoReader*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoTower(void *p = 0);
   static void *newArray_TStarJetPicoTower(Long_t size, void *p);
   static void delete_TStarJetPicoTower(void *p);
   static void deleteArray_TStarJetPicoTower(void *p);
   static void destruct_TStarJetPicoTower(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoTower*)
   {
      ::TStarJetPicoTower *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoTower >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoTower", ::TStarJetPicoTower::Class_Version(), "TStarJetPicoTower.h", 8,
                  typeid(::TStarJetPicoTower), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoTower::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoTower) );
      instance.SetNew(&new_TStarJetPicoTower);
      instance.SetNewArray(&newArray_TStarJetPicoTower);
      instance.SetDelete(&delete_TStarJetPicoTower);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoTower);
      instance.SetDestructor(&destruct_TStarJetPicoTower);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoTower*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoTower*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoTower*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoTowerCuts(void *p = 0);
   static void *newArray_TStarJetPicoTowerCuts(Long_t size, void *p);
   static void delete_TStarJetPicoTowerCuts(void *p);
   static void deleteArray_TStarJetPicoTowerCuts(void *p);
   static void destruct_TStarJetPicoTowerCuts(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoTowerCuts*)
   {
      ::TStarJetPicoTowerCuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoTowerCuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoTowerCuts", ::TStarJetPicoTowerCuts::Class_Version(), "TStarJetPicoTowerCuts.h", 12,
                  typeid(::TStarJetPicoTowerCuts), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoTowerCuts::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoTowerCuts) );
      instance.SetNew(&new_TStarJetPicoTowerCuts);
      instance.SetNewArray(&newArray_TStarJetPicoTowerCuts);
      instance.SetDelete(&delete_TStarJetPicoTowerCuts);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoTowerCuts);
      instance.SetDestructor(&destruct_TStarJetPicoTowerCuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoTowerCuts*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoTowerCuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoTowerCuts*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoTriggerInfo(void *p = 0);
   static void *newArray_TStarJetPicoTriggerInfo(Long_t size, void *p);
   static void delete_TStarJetPicoTriggerInfo(void *p);
   static void deleteArray_TStarJetPicoTriggerInfo(void *p);
   static void destruct_TStarJetPicoTriggerInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoTriggerInfo*)
   {
      ::TStarJetPicoTriggerInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoTriggerInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoTriggerInfo", ::TStarJetPicoTriggerInfo::Class_Version(), "TStarJetPicoTriggerInfo.h", 28,
                  typeid(::TStarJetPicoTriggerInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoTriggerInfo::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoTriggerInfo) );
      instance.SetNew(&new_TStarJetPicoTriggerInfo);
      instance.SetNewArray(&newArray_TStarJetPicoTriggerInfo);
      instance.SetDelete(&delete_TStarJetPicoTriggerInfo);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoTriggerInfo);
      instance.SetDestructor(&destruct_TStarJetPicoTriggerInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoTriggerInfo*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoTriggerInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoTriggerInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void streamer_TStarJetPicoUtils(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoUtils*)
   {
      ::TStarJetPicoUtils *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoUtils >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoUtils", ::TStarJetPicoUtils::Class_Version(), "TStarJetPicoUtils.h", 16,
                  typeid(::TStarJetPicoUtils), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoUtils::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetPicoUtils) );
      instance.SetStreamerFunc(&streamer_TStarJetPicoUtils);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoUtils*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoUtils*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoUtils*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoV0(void *p = 0);
   static void *newArray_TStarJetPicoV0(Long_t size, void *p);
   static void delete_TStarJetPicoV0(void *p);
   static void deleteArray_TStarJetPicoV0(void *p);
   static void destruct_TStarJetPicoV0(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoV0*)
   {
      ::TStarJetPicoV0 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoV0 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoV0", ::TStarJetPicoV0::Class_Version(), "TStarJetPicoV0.h", 6,
                  typeid(::TStarJetPicoV0), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoV0::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoV0) );
      instance.SetNew(&new_TStarJetPicoV0);
      instance.SetNewArray(&newArray_TStarJetPicoV0);
      instance.SetDelete(&delete_TStarJetPicoV0);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoV0);
      instance.SetDestructor(&destruct_TStarJetPicoV0);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoV0*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoV0*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoV0*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetPicoV0Cuts(void *p = 0);
   static void *newArray_TStarJetPicoV0Cuts(Long_t size, void *p);
   static void delete_TStarJetPicoV0Cuts(void *p);
   static void deleteArray_TStarJetPicoV0Cuts(void *p);
   static void destruct_TStarJetPicoV0Cuts(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetPicoV0Cuts*)
   {
      ::TStarJetPicoV0Cuts *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetPicoV0Cuts >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetPicoV0Cuts", ::TStarJetPicoV0Cuts::Class_Version(), "TStarJetPicoV0Cuts.h", 7,
                  typeid(::TStarJetPicoV0Cuts), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetPicoV0Cuts::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetPicoV0Cuts) );
      instance.SetNew(&new_TStarJetPicoV0Cuts);
      instance.SetNewArray(&newArray_TStarJetPicoV0Cuts);
      instance.SetDelete(&delete_TStarJetPicoV0Cuts);
      instance.SetDeleteArray(&deleteArray_TStarJetPicoV0Cuts);
      instance.SetDestructor(&destruct_TStarJetPicoV0Cuts);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetPicoV0Cuts*)
   {
      return GenerateInitInstanceLocal((::TStarJetPicoV0Cuts*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetPicoV0Cuts*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetVectorJet(void *p = 0);
   static void *newArray_TStarJetVectorJet(Long_t size, void *p);
   static void delete_TStarJetVectorJet(void *p);
   static void deleteArray_TStarJetVectorJet(void *p);
   static void destruct_TStarJetVectorJet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetVectorJet*)
   {
      ::TStarJetVectorJet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetVectorJet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetVectorJet", ::TStarJetVectorJet::Class_Version(), "TStarJetVectorJet.h", 11,
                  typeid(::TStarJetVectorJet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetVectorJet::Dictionary, isa_proxy, 4,
                  sizeof(::TStarJetVectorJet) );
      instance.SetNew(&new_TStarJetVectorJet);
      instance.SetNewArray(&newArray_TStarJetVectorJet);
      instance.SetDelete(&delete_TStarJetVectorJet);
      instance.SetDeleteArray(&deleteArray_TStarJetVectorJet);
      instance.SetDestructor(&destruct_TStarJetVectorJet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetVectorJet*)
   {
      return GenerateInitInstanceLocal((::TStarJetVectorJet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetVectorJet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TStarJetReaderParticleContainer(void *p = 0);
   static void *newArray_TStarJetReaderParticleContainer(Long_t size, void *p);
   static void delete_TStarJetReaderParticleContainer(void *p);
   static void deleteArray_TStarJetReaderParticleContainer(void *p);
   static void destruct_TStarJetReaderParticleContainer(void *p);
   static void streamer_TStarJetReaderParticleContainer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TStarJetReaderParticleContainer*)
   {
      ::TStarJetReaderParticleContainer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TStarJetReaderParticleContainer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TStarJetReaderParticleContainer", ::TStarJetReaderParticleContainer::Class_Version(), "TStarJetReaderParticleContainer.h", 8,
                  typeid(::TStarJetReaderParticleContainer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TStarJetReaderParticleContainer::Dictionary, isa_proxy, 16,
                  sizeof(::TStarJetReaderParticleContainer) );
      instance.SetNew(&new_TStarJetReaderParticleContainer);
      instance.SetNewArray(&newArray_TStarJetReaderParticleContainer);
      instance.SetDelete(&delete_TStarJetReaderParticleContainer);
      instance.SetDeleteArray(&deleteArray_TStarJetReaderParticleContainer);
      instance.SetDestructor(&destruct_TStarJetReaderParticleContainer);
      instance.SetStreamerFunc(&streamer_TStarJetReaderParticleContainer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TStarJetReaderParticleContainer*)
   {
      return GenerateInitInstanceLocal((::TStarJetReaderParticleContainer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TStarJetReaderParticleContainer*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoDefinitions::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoDefinitions::Class_Name()
{
   return "TStarJetPicoDefinitions";
}

//______________________________________________________________________________
const char *TStarJetPicoDefinitions::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDefinitions*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoDefinitions::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDefinitions*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoDefinitions::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDefinitions*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoDefinitions::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDefinitions*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoTrackCuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoTrackCuts::Class_Name()
{
   return "TStarJetPicoTrackCuts";
}

//______________________________________________________________________________
const char *TStarJetPicoTrackCuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTrackCuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoTrackCuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTrackCuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoTrackCuts::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTrackCuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoTrackCuts::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTrackCuts*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoDemoClass::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoDemoClass::Class_Name()
{
   return "TStarJetPicoDemoClass";
}

//______________________________________________________________________________
const char *TStarJetPicoDemoClass::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDemoClass*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoDemoClass::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDemoClass*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoDemoClass::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDemoClass*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoDemoClass::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoDemoClass*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoEventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoEventHeader::Class_Name()
{
   return "TStarJetPicoEventHeader";
}

//______________________________________________________________________________
const char *TStarJetPicoEventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoEventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoEventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoEventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoEvent::Class_Name()
{
   return "TStarJetPicoEvent";
}

//______________________________________________________________________________
const char *TStarJetPicoEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoEventCuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoEventCuts::Class_Name()
{
   return "TStarJetPicoEventCuts";
}

//______________________________________________________________________________
const char *TStarJetPicoEventCuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventCuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoEventCuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventCuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoEventCuts::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventCuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoEventCuts::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoEventCuts*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoPrimaryTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoPrimaryTrack::Class_Name()
{
   return "TStarJetPicoPrimaryTrack";
}

//______________________________________________________________________________
const char *TStarJetPicoPrimaryTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoPrimaryTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoPrimaryTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoPrimaryTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoPrimaryTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoPrimaryTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoPrimaryTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoPrimaryTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoQAHistograms::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoQAHistograms::Class_Name()
{
   return "TStarJetPicoQAHistograms";
}

//______________________________________________________________________________
const char *TStarJetPicoQAHistograms::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoQAHistograms*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoQAHistograms::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoQAHistograms*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoQAHistograms::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoQAHistograms*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoQAHistograms::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoQAHistograms*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr TStarJetVectorContainer<TStarJetVector>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TStarJetVector>::Class_Name()
{
   return "TStarJetVectorContainer<TStarJetVector>";
}

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TStarJetVector>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int TStarJetVectorContainer<TStarJetVector>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TStarJetVector>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TStarJetVector>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVector>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr TStarJetVectorContainer<TObject>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TObject>::Class_Name()
{
   return "TStarJetVectorContainer<TObject>";
}

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TObject>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int TStarJetVectorContainer<TObject>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TObject>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TObject>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TObject>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr TStarJetVectorContainer<TLorentzVector>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TLorentzVector>::Class_Name()
{
   return "TStarJetVectorContainer<TLorentzVector>";
}

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TLorentzVector>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int TStarJetVectorContainer<TLorentzVector>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TLorentzVector>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TLorentzVector>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TLorentzVector>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr TStarJetVectorContainer<TStarJetVectorJet>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TStarJetVectorJet>::Class_Name()
{
   return "TStarJetVectorContainer<TStarJetVectorJet>";
}

//______________________________________________________________________________
template <> const char *TStarJetVectorContainer<TStarJetVectorJet>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int TStarJetVectorContainer<TStarJetVectorJet>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TStarJetVectorJet>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *TStarJetVectorContainer<TStarJetVectorJet>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorContainer<TStarJetVectorJet>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetVector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetVector::Class_Name()
{
   return "TStarJetVector";
}

//______________________________________________________________________________
const char *TStarJetVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoReaderBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoReaderBase::Class_Name()
{
   return "TStarJetPicoReaderBase";
}

//______________________________________________________________________________
const char *TStarJetPicoReaderBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReaderBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoReaderBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReaderBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoReaderBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReaderBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoReaderBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReaderBase*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoReader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoReader::Class_Name()
{
   return "TStarJetPicoReader";
}

//______________________________________________________________________________
const char *TStarJetPicoReader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoReader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoReader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoReader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoReader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoTower::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoTower::Class_Name()
{
   return "TStarJetPicoTower";
}

//______________________________________________________________________________
const char *TStarJetPicoTower::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTower*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoTower::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTower*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoTower::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTower*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoTower::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTower*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoTowerCuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoTowerCuts::Class_Name()
{
   return "TStarJetPicoTowerCuts";
}

//______________________________________________________________________________
const char *TStarJetPicoTowerCuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTowerCuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoTowerCuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTowerCuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoTowerCuts::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTowerCuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoTowerCuts::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTowerCuts*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoTriggerInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoTriggerInfo::Class_Name()
{
   return "TStarJetPicoTriggerInfo";
}

//______________________________________________________________________________
const char *TStarJetPicoTriggerInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTriggerInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoTriggerInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTriggerInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoTriggerInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTriggerInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoTriggerInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoTriggerInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoUtils::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoUtils::Class_Name()
{
   return "TStarJetPicoUtils";
}

//______________________________________________________________________________
const char *TStarJetPicoUtils::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoUtils*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoUtils::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoUtils*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoUtils::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoUtils*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoUtils::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoUtils*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoV0::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoV0::Class_Name()
{
   return "TStarJetPicoV0";
}

//______________________________________________________________________________
const char *TStarJetPicoV0::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoV0::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoV0::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoV0::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetPicoV0Cuts::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetPicoV0Cuts::Class_Name()
{
   return "TStarJetPicoV0Cuts";
}

//______________________________________________________________________________
const char *TStarJetPicoV0Cuts::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0Cuts*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetPicoV0Cuts::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0Cuts*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetPicoV0Cuts::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0Cuts*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetPicoV0Cuts::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetPicoV0Cuts*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetVectorJet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetVectorJet::Class_Name()
{
   return "TStarJetVectorJet";
}

//______________________________________________________________________________
const char *TStarJetVectorJet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorJet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetVectorJet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorJet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetVectorJet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorJet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetVectorJet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetVectorJet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TStarJetReaderParticleContainer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TStarJetReaderParticleContainer::Class_Name()
{
   return "TStarJetReaderParticleContainer";
}

//______________________________________________________________________________
const char *TStarJetReaderParticleContainer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetReaderParticleContainer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TStarJetReaderParticleContainer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TStarJetReaderParticleContainer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TStarJetReaderParticleContainer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetReaderParticleContainer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TStarJetReaderParticleContainer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TStarJetReaderParticleContainer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TStarJetPicoDefinitions::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoDefinitions.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetPicoDefinitions(TBuffer &buf, void *obj) {
      ((::TStarJetPicoDefinitions*)obj)->::TStarJetPicoDefinitions::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetPicoDefinitions

//______________________________________________________________________________
void TStarJetPicoTrackCuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoTrackCuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoTrackCuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoTrackCuts::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoTrackCuts(void *p) {
      return  p ? new(p) ::TStarJetPicoTrackCuts : new ::TStarJetPicoTrackCuts;
   }
   static void *newArray_TStarJetPicoTrackCuts(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoTrackCuts[nElements] : new ::TStarJetPicoTrackCuts[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoTrackCuts(void *p) {
      delete ((::TStarJetPicoTrackCuts*)p);
   }
   static void deleteArray_TStarJetPicoTrackCuts(void *p) {
      delete [] ((::TStarJetPicoTrackCuts*)p);
   }
   static void destruct_TStarJetPicoTrackCuts(void *p) {
      typedef ::TStarJetPicoTrackCuts current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoTrackCuts

//______________________________________________________________________________
void TStarJetPicoDemoClass::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoDemoClass.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoDemoClass::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoDemoClass::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoDemoClass(void *p) {
      return  p ? new(p) ::TStarJetPicoDemoClass : new ::TStarJetPicoDemoClass;
   }
   static void *newArray_TStarJetPicoDemoClass(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoDemoClass[nElements] : new ::TStarJetPicoDemoClass[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoDemoClass(void *p) {
      delete ((::TStarJetPicoDemoClass*)p);
   }
   static void deleteArray_TStarJetPicoDemoClass(void *p) {
      delete [] ((::TStarJetPicoDemoClass*)p);
   }
   static void destruct_TStarJetPicoDemoClass(void *p) {
      typedef ::TStarJetPicoDemoClass current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoDemoClass

//______________________________________________________________________________
void TStarJetPicoEventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoEventHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoEventHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoEventHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoEventHeader(void *p) {
      return  p ? new(p) ::TStarJetPicoEventHeader : new ::TStarJetPicoEventHeader;
   }
   static void *newArray_TStarJetPicoEventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoEventHeader[nElements] : new ::TStarJetPicoEventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoEventHeader(void *p) {
      delete ((::TStarJetPicoEventHeader*)p);
   }
   static void deleteArray_TStarJetPicoEventHeader(void *p) {
      delete [] ((::TStarJetPicoEventHeader*)p);
   }
   static void destruct_TStarJetPicoEventHeader(void *p) {
      typedef ::TStarJetPicoEventHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoEventHeader

//______________________________________________________________________________
void TStarJetPicoEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoEvent(void *p) {
      return  p ? new(p) ::TStarJetPicoEvent : new ::TStarJetPicoEvent;
   }
   static void *newArray_TStarJetPicoEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoEvent[nElements] : new ::TStarJetPicoEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoEvent(void *p) {
      delete ((::TStarJetPicoEvent*)p);
   }
   static void deleteArray_TStarJetPicoEvent(void *p) {
      delete [] ((::TStarJetPicoEvent*)p);
   }
   static void destruct_TStarJetPicoEvent(void *p) {
      typedef ::TStarJetPicoEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoEvent

//______________________________________________________________________________
void TStarJetPicoEventCuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoEventCuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoEventCuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoEventCuts::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoEventCuts(void *p) {
      return  p ? new(p) ::TStarJetPicoEventCuts : new ::TStarJetPicoEventCuts;
   }
   static void *newArray_TStarJetPicoEventCuts(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoEventCuts[nElements] : new ::TStarJetPicoEventCuts[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoEventCuts(void *p) {
      delete ((::TStarJetPicoEventCuts*)p);
   }
   static void deleteArray_TStarJetPicoEventCuts(void *p) {
      delete [] ((::TStarJetPicoEventCuts*)p);
   }
   static void destruct_TStarJetPicoEventCuts(void *p) {
      typedef ::TStarJetPicoEventCuts current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoEventCuts

//______________________________________________________________________________
void TStarJetPicoPrimaryTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoPrimaryTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoPrimaryTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoPrimaryTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoPrimaryTrack(void *p) {
      return  p ? new(p) ::TStarJetPicoPrimaryTrack : new ::TStarJetPicoPrimaryTrack;
   }
   static void *newArray_TStarJetPicoPrimaryTrack(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoPrimaryTrack[nElements] : new ::TStarJetPicoPrimaryTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoPrimaryTrack(void *p) {
      delete ((::TStarJetPicoPrimaryTrack*)p);
   }
   static void deleteArray_TStarJetPicoPrimaryTrack(void *p) {
      delete [] ((::TStarJetPicoPrimaryTrack*)p);
   }
   static void destruct_TStarJetPicoPrimaryTrack(void *p) {
      typedef ::TStarJetPicoPrimaryTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoPrimaryTrack

//______________________________________________________________________________
void TStarJetPicoQAHistograms::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoQAHistograms.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TStarJetPicoQAHistograms(void *p) {
      delete ((::TStarJetPicoQAHistograms*)p);
   }
   static void deleteArray_TStarJetPicoQAHistograms(void *p) {
      delete [] ((::TStarJetPicoQAHistograms*)p);
   }
   static void destruct_TStarJetPicoQAHistograms(void *p) {
      typedef ::TStarJetPicoQAHistograms current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetPicoQAHistograms(TBuffer &buf, void *obj) {
      ((::TStarJetPicoQAHistograms*)obj)->::TStarJetPicoQAHistograms::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetPicoQAHistograms

//______________________________________________________________________________
template <> void TStarJetVectorContainer<TStarJetVector>::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVectorContainer<TStarJetVector>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVectorContainer<TStarJetVector>::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVectorContainer<TStarJetVector>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVectorContainerlETStarJetVectorgR(void *p) {
      return  p ? new(p) ::TStarJetVectorContainer<TStarJetVector> : new ::TStarJetVectorContainer<TStarJetVector>;
   }
   static void *newArray_TStarJetVectorContainerlETStarJetVectorgR(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVectorContainer<TStarJetVector>[nElements] : new ::TStarJetVectorContainer<TStarJetVector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVectorContainerlETStarJetVectorgR(void *p) {
      delete ((::TStarJetVectorContainer<TStarJetVector>*)p);
   }
   static void deleteArray_TStarJetVectorContainerlETStarJetVectorgR(void *p) {
      delete [] ((::TStarJetVectorContainer<TStarJetVector>*)p);
   }
   static void destruct_TStarJetVectorContainerlETStarJetVectorgR(void *p) {
      typedef ::TStarJetVectorContainer<TStarJetVector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVectorContainer<TStarJetVector>

//______________________________________________________________________________
template <> void TStarJetVectorContainer<TObject>::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVectorContainer<TObject>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVectorContainer<TObject>::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVectorContainer<TObject>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVectorContainerlETObjectgR(void *p) {
      return  p ? new(p) ::TStarJetVectorContainer<TObject> : new ::TStarJetVectorContainer<TObject>;
   }
   static void *newArray_TStarJetVectorContainerlETObjectgR(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVectorContainer<TObject>[nElements] : new ::TStarJetVectorContainer<TObject>[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVectorContainerlETObjectgR(void *p) {
      delete ((::TStarJetVectorContainer<TObject>*)p);
   }
   static void deleteArray_TStarJetVectorContainerlETObjectgR(void *p) {
      delete [] ((::TStarJetVectorContainer<TObject>*)p);
   }
   static void destruct_TStarJetVectorContainerlETObjectgR(void *p) {
      typedef ::TStarJetVectorContainer<TObject> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVectorContainer<TObject>

//______________________________________________________________________________
template <> void TStarJetVectorContainer<TLorentzVector>::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVectorContainer<TLorentzVector>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVectorContainer<TLorentzVector>::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVectorContainer<TLorentzVector>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVectorContainerlETLorentzVectorgR(void *p) {
      return  p ? new(p) ::TStarJetVectorContainer<TLorentzVector> : new ::TStarJetVectorContainer<TLorentzVector>;
   }
   static void *newArray_TStarJetVectorContainerlETLorentzVectorgR(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVectorContainer<TLorentzVector>[nElements] : new ::TStarJetVectorContainer<TLorentzVector>[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVectorContainerlETLorentzVectorgR(void *p) {
      delete ((::TStarJetVectorContainer<TLorentzVector>*)p);
   }
   static void deleteArray_TStarJetVectorContainerlETLorentzVectorgR(void *p) {
      delete [] ((::TStarJetVectorContainer<TLorentzVector>*)p);
   }
   static void destruct_TStarJetVectorContainerlETLorentzVectorgR(void *p) {
      typedef ::TStarJetVectorContainer<TLorentzVector> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVectorContainer<TLorentzVector>

//______________________________________________________________________________
template <> void TStarJetVectorContainer<TStarJetVectorJet>::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVectorContainer<TStarJetVectorJet>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVectorContainer<TStarJetVectorJet>::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVectorContainer<TStarJetVectorJet>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVectorContainerlETStarJetVectorJetgR(void *p) {
      return  p ? new(p) ::TStarJetVectorContainer<TStarJetVectorJet> : new ::TStarJetVectorContainer<TStarJetVectorJet>;
   }
   static void *newArray_TStarJetVectorContainerlETStarJetVectorJetgR(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVectorContainer<TStarJetVectorJet>[nElements] : new ::TStarJetVectorContainer<TStarJetVectorJet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVectorContainerlETStarJetVectorJetgR(void *p) {
      delete ((::TStarJetVectorContainer<TStarJetVectorJet>*)p);
   }
   static void deleteArray_TStarJetVectorContainerlETStarJetVectorJetgR(void *p) {
      delete [] ((::TStarJetVectorContainer<TStarJetVectorJet>*)p);
   }
   static void destruct_TStarJetVectorContainerlETStarJetVectorJetgR(void *p) {
      typedef ::TStarJetVectorContainer<TStarJetVectorJet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVectorContainer<TStarJetVectorJet>

//______________________________________________________________________________
void TStarJetVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVector::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVector(void *p) {
      return  p ? new(p) ::TStarJetVector : new ::TStarJetVector;
   }
   static void *newArray_TStarJetVector(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVector[nElements] : new ::TStarJetVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVector(void *p) {
      delete ((::TStarJetVector*)p);
   }
   static void deleteArray_TStarJetVector(void *p) {
      delete [] ((::TStarJetVector*)p);
   }
   static void destruct_TStarJetVector(void *p) {
      typedef ::TStarJetVector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVector

//______________________________________________________________________________
void TStarJetPicoReaderBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoReaderBase.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fNofEntries;
      R__b >> fNEntry;
      R__b >> fNEntryLoaded;
      R__b >> fNEntriesAccepted;
      R__b >> fProcessV0s;
      R__b >> fProcessTowers;
      R__b >> fUseRejectAnyway;
      R__b >> fNEntryStatus;
      R__b >> fLastRealTime;
      R__b.CheckByteCount(R__s, R__c, TStarJetPicoReaderBase::IsA());
   } else {
      R__c = R__b.WriteVersion(TStarJetPicoReaderBase::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fNofEntries;
      R__b << fNEntry;
      R__b << fNEntryLoaded;
      R__b << fNEntriesAccepted;
      R__b << fProcessV0s;
      R__b << fProcessTowers;
      R__b << fUseRejectAnyway;
      R__b << fNEntryStatus;
      R__b << fLastRealTime;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_TStarJetPicoReaderBase(void *p) {
      delete ((::TStarJetPicoReaderBase*)p);
   }
   static void deleteArray_TStarJetPicoReaderBase(void *p) {
      delete [] ((::TStarJetPicoReaderBase*)p);
   }
   static void destruct_TStarJetPicoReaderBase(void *p) {
      typedef ::TStarJetPicoReaderBase current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetPicoReaderBase(TBuffer &buf, void *obj) {
      ((::TStarJetPicoReaderBase*)obj)->::TStarJetPicoReaderBase::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetPicoReaderBase

//______________________________________________________________________________
void TStarJetPicoReader::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoReader.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TStarJetPicoReaderBase::Streamer(R__b);
      {
         vector<Int_t> &R__stl =  fMaskedRuns;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            int R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> fRejectTowerElectrons;
      R__b >> fApplyMIPCorrection;
      R__b >> fApplyFractionHadronicCorrection;
      R__b >> fFractionHadronicCorrection;
      R__b >> HadronicResult;
      R__b.CheckByteCount(R__s, R__c, TStarJetPicoReader::IsA());
   } else {
      R__c = R__b.WriteVersion(TStarJetPicoReader::IsA(), kTRUE);
      TStarJetPicoReaderBase::Streamer(R__b);
      {
         vector<Int_t> &R__stl =  fMaskedRuns;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<Int_t>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << fRejectTowerElectrons;
      R__b << fApplyMIPCorrection;
      R__b << fApplyFractionHadronicCorrection;
      R__b << fFractionHadronicCorrection;
      R__b << (TObject*)HadronicResult;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoReader(void *p) {
      return  p ? new(p) ::TStarJetPicoReader : new ::TStarJetPicoReader;
   }
   static void *newArray_TStarJetPicoReader(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoReader[nElements] : new ::TStarJetPicoReader[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoReader(void *p) {
      delete ((::TStarJetPicoReader*)p);
   }
   static void deleteArray_TStarJetPicoReader(void *p) {
      delete [] ((::TStarJetPicoReader*)p);
   }
   static void destruct_TStarJetPicoReader(void *p) {
      typedef ::TStarJetPicoReader current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetPicoReader(TBuffer &buf, void *obj) {
      ((::TStarJetPicoReader*)obj)->::TStarJetPicoReader::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetPicoReader

//______________________________________________________________________________
void TStarJetPicoTower::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoTower.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoTower::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoTower::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoTower(void *p) {
      return  p ? new(p) ::TStarJetPicoTower : new ::TStarJetPicoTower;
   }
   static void *newArray_TStarJetPicoTower(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoTower[nElements] : new ::TStarJetPicoTower[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoTower(void *p) {
      delete ((::TStarJetPicoTower*)p);
   }
   static void deleteArray_TStarJetPicoTower(void *p) {
      delete [] ((::TStarJetPicoTower*)p);
   }
   static void destruct_TStarJetPicoTower(void *p) {
      typedef ::TStarJetPicoTower current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoTower

//______________________________________________________________________________
void TStarJetPicoTowerCuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoTowerCuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoTowerCuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoTowerCuts::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoTowerCuts(void *p) {
      return  p ? new(p) ::TStarJetPicoTowerCuts : new ::TStarJetPicoTowerCuts;
   }
   static void *newArray_TStarJetPicoTowerCuts(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoTowerCuts[nElements] : new ::TStarJetPicoTowerCuts[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoTowerCuts(void *p) {
      delete ((::TStarJetPicoTowerCuts*)p);
   }
   static void deleteArray_TStarJetPicoTowerCuts(void *p) {
      delete [] ((::TStarJetPicoTowerCuts*)p);
   }
   static void destruct_TStarJetPicoTowerCuts(void *p) {
      typedef ::TStarJetPicoTowerCuts current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoTowerCuts

//______________________________________________________________________________
void TStarJetPicoTriggerInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoTriggerInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoTriggerInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoTriggerInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoTriggerInfo(void *p) {
      return  p ? new(p) ::TStarJetPicoTriggerInfo : new ::TStarJetPicoTriggerInfo;
   }
   static void *newArray_TStarJetPicoTriggerInfo(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoTriggerInfo[nElements] : new ::TStarJetPicoTriggerInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoTriggerInfo(void *p) {
      delete ((::TStarJetPicoTriggerInfo*)p);
   }
   static void deleteArray_TStarJetPicoTriggerInfo(void *p) {
      delete [] ((::TStarJetPicoTriggerInfo*)p);
   }
   static void destruct_TStarJetPicoTriggerInfo(void *p) {
      typedef ::TStarJetPicoTriggerInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoTriggerInfo

//______________________________________________________________________________
void TStarJetPicoUtils::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoUtils.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetPicoUtils(TBuffer &buf, void *obj) {
      ((::TStarJetPicoUtils*)obj)->::TStarJetPicoUtils::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetPicoUtils

//______________________________________________________________________________
void TStarJetPicoV0::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoV0.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoV0::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoV0::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoV0(void *p) {
      return  p ? new(p) ::TStarJetPicoV0 : new ::TStarJetPicoV0;
   }
   static void *newArray_TStarJetPicoV0(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoV0[nElements] : new ::TStarJetPicoV0[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoV0(void *p) {
      delete ((::TStarJetPicoV0*)p);
   }
   static void deleteArray_TStarJetPicoV0(void *p) {
      delete [] ((::TStarJetPicoV0*)p);
   }
   static void destruct_TStarJetPicoV0(void *p) {
      typedef ::TStarJetPicoV0 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoV0

//______________________________________________________________________________
void TStarJetPicoV0Cuts::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetPicoV0Cuts.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetPicoV0Cuts::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetPicoV0Cuts::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetPicoV0Cuts(void *p) {
      return  p ? new(p) ::TStarJetPicoV0Cuts : new ::TStarJetPicoV0Cuts;
   }
   static void *newArray_TStarJetPicoV0Cuts(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetPicoV0Cuts[nElements] : new ::TStarJetPicoV0Cuts[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetPicoV0Cuts(void *p) {
      delete ((::TStarJetPicoV0Cuts*)p);
   }
   static void deleteArray_TStarJetPicoV0Cuts(void *p) {
      delete [] ((::TStarJetPicoV0Cuts*)p);
   }
   static void destruct_TStarJetPicoV0Cuts(void *p) {
      typedef ::TStarJetPicoV0Cuts current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetPicoV0Cuts

//______________________________________________________________________________
void TStarJetVectorJet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetVectorJet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TStarJetVectorJet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TStarJetVectorJet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetVectorJet(void *p) {
      return  p ? new(p) ::TStarJetVectorJet : new ::TStarJetVectorJet;
   }
   static void *newArray_TStarJetVectorJet(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetVectorJet[nElements] : new ::TStarJetVectorJet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetVectorJet(void *p) {
      delete ((::TStarJetVectorJet*)p);
   }
   static void deleteArray_TStarJetVectorJet(void *p) {
      delete [] ((::TStarJetVectorJet*)p);
   }
   static void destruct_TStarJetVectorJet(void *p) {
      typedef ::TStarJetVectorJet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TStarJetVectorJet

//______________________________________________________________________________
void TStarJetReaderParticleContainer::Streamer(TBuffer &R__b)
{
   // Stream an object of class TStarJetReaderParticleContainer.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TStarJetPicoReaderBase::Streamer(R__b);
      fBranchName.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, TStarJetReaderParticleContainer::IsA());
   } else {
      R__c = R__b.WriteVersion(TStarJetReaderParticleContainer::IsA(), kTRUE);
      TStarJetPicoReaderBase::Streamer(R__b);
      fBranchName.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TStarJetReaderParticleContainer(void *p) {
      return  p ? new(p) ::TStarJetReaderParticleContainer : new ::TStarJetReaderParticleContainer;
   }
   static void *newArray_TStarJetReaderParticleContainer(Long_t nElements, void *p) {
      return p ? new(p) ::TStarJetReaderParticleContainer[nElements] : new ::TStarJetReaderParticleContainer[nElements];
   }
   // Wrapper around operator delete
   static void delete_TStarJetReaderParticleContainer(void *p) {
      delete ((::TStarJetReaderParticleContainer*)p);
   }
   static void deleteArray_TStarJetReaderParticleContainer(void *p) {
      delete [] ((::TStarJetReaderParticleContainer*)p);
   }
   static void destruct_TStarJetReaderParticleContainer(void *p) {
      typedef ::TStarJetReaderParticleContainer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TStarJetReaderParticleContainer(TBuffer &buf, void *obj) {
      ((::TStarJetReaderParticleContainer*)obj)->::TStarJetReaderParticleContainer::Streamer(buf);
   }
} // end of namespace ROOT for class ::TStarJetReaderParticleContainer

namespace ROOT {
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 458,
                  typeid(vector<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<double> >*)0x0)->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete ((vector<vector<double> >*)p);
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] ((vector<vector<double> >*)p);
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 458,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 458,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *setlEintgR_Dictionary();
   static void setlEintgR_TClassManip(TClass*);
   static void *new_setlEintgR(void *p = 0);
   static void *newArray_setlEintgR(Long_t size, void *p);
   static void delete_setlEintgR(void *p);
   static void deleteArray_setlEintgR(void *p);
   static void destruct_setlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<int>*)
   {
      set<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<int>));
      static ::ROOT::TGenericClassInfo 
         instance("set<int>", -2, "set", 400,
                  typeid(set<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &setlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(set<int>) );
      instance.SetNew(&new_setlEintgR);
      instance.SetNewArray(&newArray_setlEintgR);
      instance.SetDelete(&delete_setlEintgR);
      instance.SetDeleteArray(&deleteArray_setlEintgR);
      instance.SetDestructor(&destruct_setlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const set<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *setlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const set<int>*)0x0)->GetClass();
      setlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void setlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<int> : new set<int>;
   }
   static void *newArray_setlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<int>[nElements] : new set<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEintgR(void *p) {
      delete ((set<int>*)p);
   }
   static void deleteArray_setlEintgR(void *p) {
      delete [] ((set<int>*)p);
   }
   static void destruct_setlEintgR(void *p) {
      typedef set<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<int>

namespace ROOT {
   static TClass *bitsetlE32gR_Dictionary();
   static void bitsetlE32gR_TClassManip(TClass*);
   static void *new_bitsetlE32gR(void *p = 0);
   static void *newArray_bitsetlE32gR(Long_t size, void *p);
   static void delete_bitsetlE32gR(void *p);
   static void deleteArray_bitsetlE32gR(void *p);
   static void destruct_bitsetlE32gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const bitset<32>*)
   {
      bitset<32> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(bitset<32>));
      static ::ROOT::TGenericClassInfo 
         instance("bitset<32>", 2, "bitset", 661,
                  typeid(bitset<32>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bitsetlE32gR_Dictionary, isa_proxy, 0,
                  sizeof(bitset<32>) );
      instance.SetNew(&new_bitsetlE32gR);
      instance.SetNewArray(&newArray_bitsetlE32gR);
      instance.SetDelete(&delete_bitsetlE32gR);
      instance.SetDeleteArray(&deleteArray_bitsetlE32gR);
      instance.SetDestructor(&destruct_bitsetlE32gR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback<Internal::TStdBitsetHelper< bitset<32> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const bitset<32>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bitsetlE32gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const bitset<32>*)0x0)->GetClass();
      bitsetlE32gR_TClassManip(theClass);
   return theClass;
   }

   static void bitsetlE32gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_bitsetlE32gR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) bitset<32> : new bitset<32>;
   }
   static void *newArray_bitsetlE32gR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) bitset<32>[nElements] : new bitset<32>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bitsetlE32gR(void *p) {
      delete ((bitset<32>*)p);
   }
   static void deleteArray_bitsetlE32gR(void *p) {
      delete [] ((bitset<32>*)p);
   }
   static void destruct_bitsetlE32gR(void *p) {
      typedef bitset<32> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class bitset<32>

namespace {
  void TriggerDictionaryInitialization_TStarJetPicoRootDict_Impl() {
    static const char* headers[] = {
"TStarJetPicoDefinitions.h",
"TStarJetPicoDemoClass.h",
"TStarJetPicoEvent.h",
"TStarJetPicoEventCuts.h",
"TStarJetPicoEventHeader.h",
"TStarJetPicoPrimaryTrack.h",
"TStarJetPicoQAHistograms.h",
"TStarJetPicoReader.h",
"TStarJetPicoReaderBase.h",
"TStarJetPicoTower.h",
"TStarJetPicoTowerCuts.h",
"TStarJetPicoTrackCuts.h",
"TStarJetPicoTriggerInfo.h",
"TStarJetPicoUtils.h",
"TStarJetPicoV0.h",
"TStarJetPicoV0Cuts.h",
"TStarJetVector.h",
"TStarJetVectorContainer.h",
"TStarJetVectorJet.h",
"TStarJetReaderParticleContainer.h",
0
    };
    static const char* includePaths[] = {
"/usr/local/root/include",
"/Users/nick/physics/software/eventStructuredAu/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TStarJetPicoRootDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TStarJetPicoDefinitions.h")))  TStarJetPicoDefinitions;
class __attribute__((annotate("$clingAutoload$TStarJetPicoTrackCuts.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoDemoClass.h")))  TStarJetPicoTrackCuts;
class __attribute__((annotate("$clingAutoload$TStarJetPicoDemoClass.h")))  TStarJetPicoDemoClass;
class __attribute__((annotate("$clingAutoload$TStarJetPicoEventHeader.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoEvent.h")))  TStarJetPicoEventHeader;
class __attribute__((annotate("$clingAutoload$TStarJetPicoEvent.h")))  TStarJetPicoEvent;
class __attribute__((annotate("$clingAutoload$TStarJetPicoEventCuts.h")))  TStarJetPicoEventCuts;
class __attribute__((annotate("$clingAutoload$TStarJetPicoPrimaryTrack.h")))  TStarJetPicoPrimaryTrack;
class __attribute__((annotate("$clingAutoload$TStarJetPicoQAHistograms.h")))  TStarJetPicoQAHistograms;
class __attribute__((annotate("$clingAutoload$TStarJetVector.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoReader.h")))  TStarJetVector;
template <class T> class __attribute__((annotate("$clingAutoload$TStarJetVectorContainer.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoReader.h")))  TStarJetVectorContainer;

class __attribute__((annotate("$clingAutoload$TObject.h")))  TObject;
class __attribute__((annotate("$clingAutoload$TLorentzVector.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoReader.h")))  TLorentzVector;
class __attribute__((annotate("$clingAutoload$TStarJetVectorJet.h")))  TStarJetVectorJet;
class __attribute__((annotate("$clingAutoload$TStarJetPicoReaderBase.h")))  __attribute__((annotate("$clingAutoload$TStarJetPicoReader.h")))  TStarJetPicoReaderBase;
class __attribute__((annotate("$clingAutoload$TStarJetPicoReader.h")))  TStarJetPicoReader;
class __attribute__((annotate("$clingAutoload$TStarJetPicoTower.h")))  TStarJetPicoTower;
class __attribute__((annotate("$clingAutoload$TStarJetPicoTowerCuts.h")))  TStarJetPicoTowerCuts;
class __attribute__((annotate("$clingAutoload$TStarJetPicoTriggerInfo.h")))  TStarJetPicoTriggerInfo;
class __attribute__((annotate("$clingAutoload$TStarJetPicoUtils.h")))  TStarJetPicoUtils;
class __attribute__((annotate("$clingAutoload$TStarJetPicoV0.h")))  TStarJetPicoV0;
class __attribute__((annotate("$clingAutoload$TStarJetPicoV0Cuts.h")))  TStarJetPicoV0Cuts;
class __attribute__((annotate("$clingAutoload$TStarJetReaderParticleContainer.h")))  TStarJetReaderParticleContainer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TStarJetPicoRootDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TStarJetPicoDefinitions.h"
#include "TStarJetPicoDemoClass.h"
#include "TStarJetPicoEvent.h"
#include "TStarJetPicoEventCuts.h"
#include "TStarJetPicoEventHeader.h"
#include "TStarJetPicoPrimaryTrack.h"
#include "TStarJetPicoQAHistograms.h"
#include "TStarJetPicoReader.h"
#include "TStarJetPicoReaderBase.h"
#include "TStarJetPicoTower.h"
#include "TStarJetPicoTowerCuts.h"
#include "TStarJetPicoTrackCuts.h"
#include "TStarJetPicoTriggerInfo.h"
#include "TStarJetPicoUtils.h"
#include "TStarJetPicoV0.h"
#include "TStarJetPicoV0Cuts.h"
#include "TStarJetVector.h"
#include "TStarJetVectorContainer.h"
#include "TStarJetVectorJet.h"
#include "TStarJetReaderParticleContainer.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TStarJetPicoDefinitions", payloadCode, "@",
"TStarJetPicoDemoClass", payloadCode, "@",
"TStarJetPicoEvent", payloadCode, "@",
"TStarJetPicoEventCuts", payloadCode, "@",
"TStarJetPicoEventHeader", payloadCode, "@",
"TStarJetPicoPrimaryTrack", payloadCode, "@",
"TStarJetPicoQAHistograms", payloadCode, "@",
"TStarJetPicoReader", payloadCode, "@",
"TStarJetPicoReaderBase", payloadCode, "@",
"TStarJetPicoTower", payloadCode, "@",
"TStarJetPicoTowerCuts", payloadCode, "@",
"TStarJetPicoTrackCuts", payloadCode, "@",
"TStarJetPicoTriggerInfo", payloadCode, "@",
"TStarJetPicoUtils", payloadCode, "@",
"TStarJetPicoV0", payloadCode, "@",
"TStarJetPicoV0Cuts", payloadCode, "@",
"TStarJetReaderParticleContainer", payloadCode, "@",
"TStarJetVector", payloadCode, "@",
"TStarJetVectorContainer<TLorentzVector>", payloadCode, "@",
"TStarJetVectorContainer<TObject>", payloadCode, "@",
"TStarJetVectorContainer<TStarJetVector>", payloadCode, "@",
"TStarJetVectorContainer<TStarJetVectorJet>", payloadCode, "@",
"TStarJetVectorJet", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TStarJetPicoRootDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TStarJetPicoRootDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TStarJetPicoRootDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TStarJetPicoRootDict() {
  TriggerDictionaryInitialization_TStarJetPicoRootDict_Impl();
}
