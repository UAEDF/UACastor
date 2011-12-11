
#include "./MyBeamSpot.h"
#include "./MyCastorDigi.h"
#include "./MyCastorJet.h"
#include "./MyCastorRecHit.h"
#include "./MyCastorTower.h"
#include "./MyDiJet.h"
#include "./MyEvtId.h"
#include "./MyGenKin.h"
#include "./MyGenPart.h"
#include "./MyGenJet.h"
#include "./MyHLTrig.h"
#include "./MyJet.h"
#include "./MyTrackJet.h"
#include "./MyJetPtSorter.h"
#include "./MyTrackJetPtSorter.h"
#include "./MyL1Trig.h"
#include "./MyPart.h"
#include "./MySimVertex.h"
#include "./MyVertex.h"


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
#pragma link C++ class MyGenJet+;
#pragma link C++ class vector<MyGenJet>+;

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

#pragma link C++ class MyTrackJet+;
#pragma link C++ class vector<MyTrackJet>+;

#pragma link C++ class MyDiJet+;

#endif

