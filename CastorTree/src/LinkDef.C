
#include "../interface/MyBeamSpot.h"
#include "../interface/MyCastorDigi.h"
#include "../interface/MyCastorJet.h"
#include "../interface/MyCastorRecHit.h"
#include "../interface/MyCastorTower.h"
#include "../interface/MyDiJet.h"
#include "../interface/MyEvtId.h"
#include "../interface/MyGenKin.h"
#include "../interface/MyGenPart.h"
#include "../interface/MyHLTrig.h"
#include "../interface/MyJet.h"
#include "../interface/MyJetPtSorter.h"
#include "../interface/MyL1Trig.h"
#include "../interface/MyPart.h"
#include "../interface/MySimVertex.h"
#include "../interface/MyVertex.h"


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

