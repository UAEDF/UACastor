COMPILER = g++ -g
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs) -lPhysics -lThread -lMinuit -lHtml -lVMC -lEG -lGeom 

CERN=/afs/cern.ch/sw/lcg/external
SYSNAME=slc4_amd64_gcc34
VERSION=2.03.11
HEPMC=${CERN}/HepMC/${VERSION}/${SYSNAME}

.SUFFIXES: .C .o

Conversion : Conversion.C EventDico.C   
	${COMPILER} EventDico.C Conversion.C -o $@ ${CFLAGS} ${LIBS} -I${HEPMC}/include ${HEPMC}/lib/libHepMC.a ${HEPMC}/lib/libHepMCfio.a


EventDico.C:
	rootcint -f EventDico.C -c -p -I${HEPMC}/include -I${ROOTSYS}/include Classes.h LinkDef.h


