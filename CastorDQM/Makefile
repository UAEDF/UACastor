SHELL = /bin/bash
COMPILER = g++ -g
COMPILERSO = g++ -g +a1 -b
LIBDIR = /home/benoit/Castor/CastorStudy/RunSelection2010/DQMAnalyze
CFLAGS = $(shell root-config --cflags)
LIBS   = $(shell root-config --libs) -lPhysics -lThread -lMinuit -lHtml -lVMC -lEG -lGeom 
ROOT = /opt/root/bin/root -b -q 

.SUFFIXES: .C .o

DQMAnalyze : DQMAnalyze.C DQMAnalyze.h     
	${COMPILER} DQMAnalyze.C -o $@ ${CFLAGS} ${LIBS}

