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

all : Run Plot Systematic FitEfficiency FitEfficiencyPAS Threshold SignalNoise SignalNoisePAS EfficiencyComparison EfficiencyComparisonPAS CastorControlPlotPAS CastorControlPlotPAS_noHerwig Decalibration ReweightEflow Eflow900_no_physic_bit

Systematic : Systematic.cc       
	${COMPILER} Systematic.cc -o $@ ${CFLAGS} ${LIBS}

Run : Run.cc MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so EflowAnalyzer.o EflowAnalyzer_cc.so GeometryAnalyzer.o GeometryAnalyzer_cc.so ShowerAnalyzer.o ShowerAnalyzer_cc.so SignalCutAnalyzer.o SignalCutAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so ModulationAnalyzer.o ModulationAnalyzer_cc.so TriggerAnalyzer.o TriggerAnalyzer_cc.so ThresholdAnalyzer.o ThresholdAnalyzer_cc.so CutHadronLevelAnalyzer.o CutHadronLevelAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so
	${COMPILER} Run.cc -o $@ MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so EflowAnalyzer.o EflowAnalyzer_cc.so GeometryAnalyzer.o GeometryAnalyzer_cc.so ShowerAnalyzer.o ShowerAnalyzer_cc.so SignalCutAnalyzer.o SignalCutAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so ModulationAnalyzer.o ModulationAnalyzer_cc.so TriggerAnalyzer.o TriggerAnalyzer_cc.so ThresholdAnalyzer.o ThresholdAnalyzer_cc.so CutHadronLevelAnalyzer.o CutHadronLevelAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so ${CFLAGS} ${LIBS}

Plot : Plot.cc MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so EflowAnalyzer.o EflowAnalyzer_cc.so GeometryAnalyzer.o GeometryAnalyzer_cc.so ShowerAnalyzer.o ShowerAnalyzer_cc.so SignalCutAnalyzer.o SignalCutAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so ModulationAnalyzer.o ModulationAnalyzer_cc.so TriggerAnalyzer.o TriggerAnalyzer_cc.so ThresholdAnalyzer.o ThresholdAnalyzer_cc.so CutHadronLevelAnalyzer.o CutHadronLevelAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so
	${COMPILER} Plot.cc -o $@ MainAnalyzer.o MainAnalyzer_cc.so TreeAnalyzer.o TreeAnalyzer_cc.so ProfileAnalyzer.o ProfileAnalyzer_cc.so EflowAnalyzer.o EflowAnalyzer_cc.so GeometryAnalyzer.o GeometryAnalyzer_cc.so ShowerAnalyzer.o ShowerAnalyzer_cc.so SignalCutAnalyzer.o SignalCutAnalyzer_cc.so CalibAnalyzer.o CalibAnalyzer_cc.so ModulationAnalyzer.o ModulationAnalyzer_cc.so TriggerAnalyzer.o TriggerAnalyzer_cc.so ThresholdAnalyzer.o ThresholdAnalyzer_cc.so CutHadronLevelAnalyzer.o CutHadronLevelAnalyzer_cc.so EflowPlotter.o EflowPlotter_cc.so FileReader.o FileReader_cc.so HistoRetriever.o HistoRetriever_cc.so MCDataComparer.o MCDataComparer_cc.so ${TREEDIR}/*.so ${CFLAGS} ${LIBS}

FitEfficiency : FitEfficiency.cc
	${COMPILER} FitEfficiency.cc -o $@ ${CFLAGS} ${LIBS}

FitEfficiencyPAS : FitEfficiencyPAS.cc
	${COMPILER} FitEfficiencyPAS.cc -o $@ ${CFLAGS} ${LIBS}

Threshold : Threshold.cc       
	${COMPILER} Threshold.cc -o $@ ${CFLAGS} ${LIBS}

SignalNoise : SignalNoise.cc
	${COMPILER} SignalNoise.cc -o $@ ${CFLAGS} ${LIBS}

SignalNoisePAS : SignalNoisePAS.cc
	${COMPILER} SignalNoisePAS.cc -o $@ ${CFLAGS} ${LIBS}

EfficiencyComparison : EfficiencyComparison.cc
	${COMPILER} EfficiencyComparison.cc -o $@ ${CFLAGS} ${LIBS}

EfficiencyComparisonPAS : EfficiencyComparisonPAS.cc
	${COMPILER} EfficiencyComparisonPAS.cc -o $@ ${CFLAGS} ${LIBS}

CastorControlPlotPAS : CastorControlPlotPAS.cc
	${COMPILER} CastorControlPlotPAS.cc -o $@ ${CFLAGS} ${LIBS}

CastorControlPlotPAS_noHerwig : CastorControlPlotPAS_noHerwig.cc
	${COMPILER} CastorControlPlotPAS_noHerwig.cc -o $@ ${CFLAGS} ${LIBS}

Eflow900_no_physic_bit : Eflow900_no_physic_bit.cc
	${COMPILER} Eflow900_no_physic_bit.cc -o $@ ${CFLAGS} ${LIBS}

Decalibration : Decalibration.cc
	${COMPILER} Decalibration.cc -o $@ ${CFLAGS} ${LIBS}

ReweightEflow : ReweightEflow.cc
	${COMPILER} ReweightEflow.cc -o $@ ${CFLAGS} ${LIBS}

MainAnalyzer_cc.so :
	${ROOT} Build.cc+

MainAnalyzer.o : MainAnalyzer.cc MainAnalyzer.h FileReader.cc HistoRetriever.cc MCDataComparer.cc FileReader.h HistoRetriever.h MCDataComparer.h 
	${COMPILER} -c MainAnalyzer.cc FileReader.cc HistoRetriever.cc MCDataComparer.cc ${CFLAGS}

TreeAnalyzer.o : TreeAnalyzer.cc TreeAnalyzer.h
	${COMPILER} -c TreeAnalyzer.cc ${CFLAGS}

SignalCutAnalyzer.o : SignalCutAnalyzer.cc SignalCutAnalyzer.h
	${COMPILER} -c SignalCutAnalyzer.cc ${CFLAGS}

ProfileAnalyzer.o : ProfileAnalyzer.cc ProfileAnalyzer.h
	${COMPILER} -c ProfileAnalyzer.cc ${CFLAGS}

EflowAnalyzer.o : EflowAnalyzer.cc EflowAnalyzer.h
	${COMPILER} -c EflowAnalyzer.cc ${CFLAGS}

GeometryAnalyzer.o : GeometryAnalyzer.cc GeometryAnalyzer.h
	${COMPILER} -c GeometryAnalyzer.cc ${CFLAGS}

ShowerAnalyzer.o : ShowerAnalyzer.cc ShowerAnalyzer.h
	${COMPILER} -c ShowerAnalyzer.cc ${CFLAGS}

CalibAnalyzer.o : CalibAnalyzer.cc CalibAnalyzer.h
	${COMPILER} -c CalibAnalyzer.cc ${CFLAGS}

ModulationAnalyzer.o : ModulationAnalyzer.cc ModulationAnalyzer.h
	${COMPILER} -c ModulationAnalyzer.cc ${CFLAGS}

TriggerAnalyzer.o : TriggerAnalyzer.cc TriggerAnalyzer.h
	${COMPILER} -c TriggerAnalyzer.cc ${CFLAGS}

ThresholdAnalyzer.o : ThresholdAnalyzer.cc ThresholdAnalyzer.h
	${COMPILER} -c ThresholdAnalyzer.cc ${CFLAGS}

CutHadronLevelAnalyzer.o : CutHadronLevelAnalyzer.cc CutHadronLevelAnalyzer.h
	${COMPILER} -c CutHadronLevelAnalyzer.cc ${CFLAGS}

EflowPlotter.o : EflowPlotter.cc EflowPlotter.h
	${COMPILER} -c EflowPlotter.cc ${CFLAGS}

FileReader.o : FileReader.cc FileReader.h
	${COMPILER} -c FileReader.cc ${CFLAGS}

HistoRetriever.o : HistoRetriever.cc HistoRetriever.h
	${COMPILER} -c HistoRetriever.cc ${CFLAGS}
	
MCDataComparer.o : MCDataComparer.cc MCDataComparer.h
	${COMPILER} -c MCDataComparer.cc ${CFLAGS}

clean :
	rm *.o *.so *_cc.d Run Plot Systematic FitEfficiency FitEfficiencyPAS Threshold SignalNoise SignalNoisePAS EfficiencyComparison EfficiencyComparisonPAS CastorControlPlotPAS CastorControlPlotPAS_noHerwig Eflow900_no_physic_bit Decalibration ReweightEflow
