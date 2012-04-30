#ifndef MainAnalyzer_h
#define MainAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TCanvas.h>

#include "FileReader.h"
#include "HistoRetriever.h"
#include "TreeAnalyzer.h"
#include "ProfileAnalyzer.h"
#include "EflowAnalyzer.h"
#include "GeometryAnalyzer.h"
#include "ShowerAnalyzer.h"
#include "CalibAnalyzer.h"
#include "ModulationAnalyzer.h"
#include "TriggerAnalyzer.h"
#include "ThresholdAnalyzer.h"
#include "SignalCutAnalyzer.h"
#include "CutHadronLevelAnalyzer.h"
#include "MCDataComparer.h"

class MainAnalyzer {
	public:
        MainAnalyzer();
		virtual ~MainAnalyzer();
		void makeHistos(TString inputdir, TString regexpstr, bool isData, double cmenergy);
                void makeHistoProfile(TString inputdir, TString regexpstr, bool isData, double cmenergy);
		void makeHistoEflow(TString inputdir, TString regexpstr, TString type, double cmenergy, bool dosubsample);
		void makeHistoGeometry(TString inputdir, TString regexpstr, TString type, double cmenergy);
                void makeHistoShower(TString inputdir, TString regexpstr, TString type, double cmenergy);
		void makeHistoCalib(TString inputdir, TString regexpstr, double cmenergy);
		void makeHistoModulation(TString inputdir, TString regexpstr, double cmenergy);
                void makeHistoTrigger(TString inputdir, TString regexpstr, bool isData, double cmenergy, int subsample);
		void makeHistoThreshold(TString inputdir, TString regexpstr, bool isData, double cmenergy);
		void makeHistoCutHadronLevel(TString inputdir, TString regexpstr, double cmenergy);
		void makeHistoSignalCut(TString inputdir, TString regexpstr, bool isData, double cmenergy);
		void plotSingleHistos(TString outputfile, TString selectname);

		void plotHistos(TString inputdir, TString regexpstr, TString selectname);
		void plotScaleHisto(TString inputdir,TString regexpstr,TString selectname, double weight_manual);

		void compareMCData(TString inputdir,TString regexpstr, TString selectname);

		void saveAllCanvas(TString inputdir, TString name);
		void saveAllCanvasPDF(TString inputdir,TString name);

		void setPlotStyle();
		void setCMSStyle(); 

	private:
		FileReader reader_;
		HistoRetriever histogetter_;
		TreeAnalyzer treeanalyzer_;
                ProfileAnalyzer profileanalyzer_;
		EflowAnalyzer eflowanalyzer_;
		GeometryAnalyzer geometryanalyzer_;
                ShowerAnalyzer showeranalyzer_;
		CalibAnalyzer calibanalyzer_;
		ModulationAnalyzer modanalyzer_;
                TriggerAnalyzer triggeranalyzer_;
		ThresholdAnalyzer thresholdanalyzer_;
		SignalCutAnalyzer signalcutanalyzer_;
		CutHadronLevelAnalyzer cuthadronlevelanalyzer_;
		std::vector<TCanvas*> canvasvector_;
};

#endif
