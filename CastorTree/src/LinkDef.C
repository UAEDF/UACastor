
#include "UACastor/CastorTree/interface/MyBeamSpot.h"
#include "UACastor/CastorTree/interface/MyCastorDigi.h"
#include "UACastor/CastorTree/interface/MyCastorJet.h"
#include "UACastor/CastorTree/interface/MyCastorRecHit.h"
#include "UACastor/CastorTree/interface/MyCastorTower.h"
#include "UACastor/CastorTree/interface/MyDiJet.h"
#include "UACastor/CastorTree/interface/MyEvtId.h"
#include "UACastor/CastorTree/interface/MyGenKin.h"
#include "UACastor/CastorTree/interface/MyGenPart.h"
#include "UACastor/CastorTree/interface/MyHLTrig.h"
#include "UACastor/CastorTree/interface/MyJet.h"
#include "UACastor/CastorTree/interface/MyJetPtSorter.h"
#include "UACastor/CastorTree/interface/MyL1Trig.h"
#include "UACastor/CastorTree/interface/MyPart.h"
#include "UACastor/CastorTree/interface/MySimVertex.h"
#include "UACastor/CastorTree/interface/MyVertex.h"


#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class MyPart+;

#pragma link C++ class MyEvtId+;
#pragma link C++ class MyL1Trig+;
#pragma link C++ class MyHLTrig+;

#pragma link C++ class MyGenKin+;
#pragma link C++ class MyGenPart+;
#pragma link C++ class vector<MyGenPart>+;

#pragma link C++ class MyBeamSpot+;

#pragma link C++ class MyVertex+;
#pragma link C++ class vector<MyVertex>+;

#pragma link C++ class MySimVertex+;

#pragma link C++ class MyCastorDigi+;
#pragma link C++ class vector<MyCastorDigi>+;

#pragma link C++ class MyCastorRecHit+;
#pragma link C++ class vector<MyCastorRecHit>+;

#pragma link C++ class MyCastorJet+;
#pragma link C++ class vector<MyCastorJet>+;

#pragma link C++ class MyCastorTower+;
#pragma link C++ class vector<MyCastorTower>+;

#pragma link C++ class MyJet+;
#pragma link C++ class vector<MyJet>+;

#pragma link C++ class MyDiJet+;

#endif

