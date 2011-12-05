/********************************************************************
* eventdict.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error eventdict.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "G__ci.h"
#include "FastAllocString.h"
extern "C" {
extern void G__cpp_setup_tagtableeventdict();
extern void G__cpp_setup_inheritanceeventdict();
extern void G__cpp_setup_typetableeventdict();
extern void G__cpp_setup_memvareventdict();
extern void G__cpp_setup_globaleventdict();
extern void G__cpp_setup_memfunceventdict();
extern void G__cpp_setup_funceventdict();
extern void G__set_cpp_environmenteventdict();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "./MyEvtId.h"
#include "./MyL1Trig.h"
#include "./MyHLTrig.h"
#include "./MyGenKin.h"
#include "./MyPart.h"
#include "./MyGenPart.h"
#include "./MyGenJet.h"
#include "./MyVertex.h"
#include "./MySimVertex.h"
#include "./MyBeamSpot.h"
#include "./MyCastorDigi.h"
#include "./MyCastorRecHit.h"
#include "./MyCastorTower.h"
#include "./MyCastorJet.h"
#include "./MyJet.h"
#include "./MyTrackJet.h"
#include "./MyDiJet.h"
#include "./MyCaloTower.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__eventdictLN_TClass;
extern G__linked_taginfo G__eventdictLN_TBuffer;
extern G__linked_taginfo G__eventdictLN_TMemberInspector;
extern G__linked_taginfo G__eventdictLN_TObject;
extern G__linked_taginfo G__eventdictLN_vectorlEdoublecOallocatorlEdoublegRsPgR;
extern G__linked_taginfo G__eventdictLN_string;
extern G__linked_taginfo G__eventdictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_MyEvtId;
extern G__linked_taginfo G__eventdictLN_maplEstringcOdoublecOlesslEstringgRcOallocatorlEpairlEconstsPstringcOdoublegRsPgRsPgR;
extern G__linked_taginfo G__eventdictLN_MyL1Trig;
extern G__linked_taginfo G__eventdictLN_maplEstringcOunsignedsPintcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOunsignedsPintgRsPgRsPgR;
extern G__linked_taginfo G__eventdictLN_MyHLTrig;
extern G__linked_taginfo G__eventdictLN_maplEstringcOboolcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOboolgRsPgRsPgR;
extern G__linked_taginfo G__eventdictLN_MyGenKin;
extern G__linked_taginfo G__eventdictLN_TMatrixTBaselEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTBaselEdoublegR;
extern G__linked_taginfo G__eventdictLN_TVectorTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TVectorTlEdoublegR;
extern G__linked_taginfo G__eventdictLN_TElementActionTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TElementPosActionTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTRow_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTRowlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTDiag_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTColumn_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTFlat_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSub_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseRow_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseDiag_constlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTColumnlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTDiaglEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTFlatlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSublEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseRowlEfloatgR;
extern G__linked_taginfo G__eventdictLN_TMatrixTSparseDiaglEfloatgR;
extern G__linked_taginfo G__eventdictLN_TLorentzVector;
extern G__linked_taginfo G__eventdictLN_MyPart;
extern G__linked_taginfo G__eventdictLN_MyGenPart;
extern G__linked_taginfo G__eventdictLN_MyGenJet;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyGenPartcOallocatorlEMyGenPartgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_MyVertex;
extern G__linked_taginfo G__eventdictLN_MySimVertex;
extern G__linked_taginfo G__eventdictLN_MyBeamSpot;
extern G__linked_taginfo G__eventdictLN_MyCastorDigi;
extern G__linked_taginfo G__eventdictLN_MyCastorRecHit;
extern G__linked_taginfo G__eventdictLN_MyCastorTower;
extern G__linked_taginfo G__eventdictLN_MyCastorJet;
extern G__linked_taginfo G__eventdictLN_MyJet;
extern G__linked_taginfo G__eventdictLN_MyTrackJet;
extern G__linked_taginfo G__eventdictLN_MyDiJet;
extern G__linked_taginfo G__eventdictLN_MyCaloTower;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyGenJetcOallocatorlEMyGenJetgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyVertexcOallocatorlEMyVertexgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyVertexcOallocatorlEMyVertexgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyVertexcOallocatorlEMyVertexgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorDigicOallocatorlEMyCastorDigigRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorDigicOallocatorlEMyCastorDigigRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyCastorDigicOallocatorlEMyCastorDigigRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorRecHitcOallocatorlEMyCastorRecHitgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorRecHitcOallocatorlEMyCastorRecHitgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyCastorRecHitcOallocatorlEMyCastorRecHitgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorTowercOallocatorlEMyCastorTowergRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorTowercOallocatorlEMyCastorTowergRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyCastorTowercOallocatorlEMyCastorTowergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorJetcOallocatorlEMyCastorJetgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCastorJetcOallocatorlEMyCastorJetgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyCastorJetcOallocatorlEMyCastorJetgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyJetcOallocatorlEMyJetgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyJetcOallocatorlEMyJetgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyJetcOallocatorlEMyJetgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyTrackJetcOallocatorlEMyTrackJetgRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyTrackJetcOallocatorlEMyTrackJetgRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyTrackJetcOallocatorlEMyTrackJetgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCaloTowercOallocatorlEMyCaloTowergRsPgR;
extern G__linked_taginfo G__eventdictLN_vectorlEMyCaloTowercOallocatorlEMyCaloTowergRsPgRcLcLiterator;
extern G__linked_taginfo G__eventdictLN_reverse_iteratorlEvectorlEMyCaloTowercOallocatorlEMyCaloTowergRsPgRcLcLiteratorgR;

/* STUB derived class for protected member access */
typedef vector<MyGenPart,allocator<MyGenPart> > G__vectorlEMyGenPartcOallocatorlEMyGenPartgRsPgR;
typedef vector<MyGenJet,allocator<MyGenJet> > G__vectorlEMyGenJetcOallocatorlEMyGenJetgRsPgR;
typedef vector<MyVertex,allocator<MyVertex> > G__vectorlEMyVertexcOallocatorlEMyVertexgRsPgR;
typedef vector<MyCastorDigi,allocator<MyCastorDigi> > G__vectorlEMyCastorDigicOallocatorlEMyCastorDigigRsPgR;
typedef vector<MyCastorRecHit,allocator<MyCastorRecHit> > G__vectorlEMyCastorRecHitcOallocatorlEMyCastorRecHitgRsPgR;
typedef vector<MyCastorTower,allocator<MyCastorTower> > G__vectorlEMyCastorTowercOallocatorlEMyCastorTowergRsPgR;
typedef vector<MyCastorJet,allocator<MyCastorJet> > G__vectorlEMyCastorJetcOallocatorlEMyCastorJetgRsPgR;
typedef vector<MyJet,allocator<MyJet> > G__vectorlEMyJetcOallocatorlEMyJetgRsPgR;
typedef vector<MyTrackJet,allocator<MyTrackJet> > G__vectorlEMyTrackJetcOallocatorlEMyTrackJetgRsPgR;
typedef vector<MyCaloTower,allocator<MyCaloTower> > G__vectorlEMyCaloTowercOallocatorlEMyCaloTowergRsPgR;
