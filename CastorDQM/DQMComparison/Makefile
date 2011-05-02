SHELL = /bin/bash
COMPILER = g++ -g
COMPILERSO = g++ -g +a1 -b
LIBDIR = /home/benoit/Castor/CastorStudy/RunSelection2010/DQMComparison
CFLAGS = $(shell root-config --cflags)
LIBS   = $(shell root-config --libs) -lPhysics -lThread -lMinuit -lHtml -lVMC -lEG -lGeom 
ROOT = /opt/root/bin/root -b -q 

.SUFFIXES: .C .o

CompareRun : CompareRun.C    
	${COMPILER} CompareRun.C -o $@ ${CFLAGS} ${LIBS}