#!/bin/bash
rootcint -f eventdict.cc -c -I${PWD}/../../.. \
         -p \
    	    UACastor/CastorTree/interface/MyEvtId.h \
            UACastor/CastorTree/interface/MyL1Trig.h \
            UACastor/CastorTree/interface/MyHLTrig.h \
            UACastor/CastorTree/interface/MyGenKin.h \
            UACastor/CastorTree/interface/MyPart.h \
            UACastor/CastorTree/interface/MyGenPart.h \
            UACastor/CastorTree/interface/MyVertex.h \
            UACastor/CastorTree/interface/MySimVertex.h \
            UACastor/CastorTree/interface/MyBeamSpot.h \
            UACastor/CastorTree/interface/MyCastorDigi.h \
            UACastor/CastorTree/interface/MyCastorRecHit.h \
	    UACastor/CastorTree/interface/MyCastorTower.h \
            UACastor/CastorTree/interface/MyCastorJet.h \
            UACastor/CastorTree/interface/MyJet.h \
            UACastor/CastorTree/interface/MyDiJet.h \
            UACastor/CastorTree/interface/LinkDef.h
