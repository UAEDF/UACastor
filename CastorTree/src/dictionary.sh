#!/bin/bash
rootcint -f eventdict.cc -c -I${PWD}/../../.. \
         -p \
    	    ./MyEvtId.h \
            ./MyL1Trig.h \
            ./MyHLTrig.h \
            ./MyGenKin.h \
            ./MyPart.h \
            ./MyGenPart.h \
            ./MyGenJet.h \
            ./MyVertex.h \
            ./MySimVertex.h \
            ./MyBeamSpot.h \
            ./MyCastorDigi.h \
            ./MyCastorRecHit.h \
	    ./MyCastorTower.h \
            ./MyCastorJet.h \
            ./MyJet.h \
            ./MyTrackJet.h \
            ./MyDiJet.h \
            ./MyCaloTower.h \
            ../interface/LinkDef.h
