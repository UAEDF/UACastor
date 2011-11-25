SHELL = /bin/bash
COMPILER = g++ -g
COMPILERSO = g++ -g +a1 -b
#LIBDIR = /user/hvanhaev/Analysis/Eflow/CMSSW_4_2_7/src/UACastor/CastorTree/Analyzer
#TREEDIR = /user/hvanhaev/Analysis/Eflow/CMSSW_4_2_7/src/UACastor/CastorTree/src
LIBDIR = /user/roland/EflowAnalysis/CMSSW_4_2_7/src/UACastor/CastorTree/Analyzer
TREEDIR = /user/roland/EflowAnalysis/CMSSW_4_2_7/src/UACastor/CastorTree/src
CFLAGS = $(shell root-config --cflags)
LIBS = $(shell root-config --libs) -lPhysics -lThread -lMinuit -lHtml -lVMC -lEG -lGeom -Wl,-rpath -Wl,${LIBDIR} -Wl,-rpath -Wl,${TREEDIR}
ROOT = /sandbox/cmss/slc5_amd64_gcc434/cms/cmssw/CMSSW_4_2_7/external/slc5_amd64_gcc434/bin/root -b -q
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LIBDIR}:${TREEDIR}

.SUFFIXES: .cc .o

all : Run Plot

Run : Run.cc MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so
	${COMPILER} Run.cc -o $@ MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so ${CFLAGS} ${LIBS}

Plot : Plot.cc MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so
	${COMPILER} Plot.cc -o $@ MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so ${CFLAGS} ${LIBS}

MainAnalyzer_cc.so :
	${ROOT} Build.cc+

MainAnalyzer.o : MainAnalyzer.cc MainAnalyzer.h FileReader.cc HistoRetriever.cc MCDataComparer.cc FileReader.h HistoRetriever.h MCDataComparer.h 
	${COMPILER} -c MainAnalyzer.cc FileReader.cc HistoRetriever.cc MCDataComparer.cc ${CFLAGS}

TreeAnalyzer.o : TreeAnalyzer.cc TreeAnalyzer.h
	${COMPILER} -c TreeAnalyzer.cc ${CFLAGS}

ProfileAnalyzer.o : ProfileAnalyzer.cc ProfileAnalyzer.h
	${COMPILER} -c ProfileAnalyzer.cc ${CFLAGS}

CalibAnalyzer.o : CalibAnalyzer.cc CalibAnalyzer.h
	${COMPILER} -c CalibAnalyzer.cc ${CFLAGS}

EflowPlotter.o : EflowPlotter.cc EflowPlotter.h
	${COMPILER} -c EflowPlotter.cc ${CFLAGS}

FileReader.o : FileReader.cc FileReader.h
	${COMPILER} -c FileReader.cc ${CFLAGS}

HistoRetriever.o : HistoRetriever.cc HistoRetriever.h
	${COMPILER} -c HistoRetriever.cc ${CFLAGS}
	
MCDataComparer.o : MCDataComparer.cc MCDataComparer.h
	${COMPILER} -c MCDataComparer.cc ${CFLAGS}

clean :
	rm *.o *.so *_cc.d Run Plot
