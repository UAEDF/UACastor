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
#include "CalibAnalyzer.h"
#include "MCDataComparer.h"

class MainAnalyzer {
	public:
        MainAnalyzer();
		virtual ~MainAnalyzer();
		void makeHistos(TString inputdir, TString regexpstr, bool isData, double cmenergy);
                void makeHistoProfile(TString inputdir, TString regexpstr, bool isData, double cmenergy);
		void makeHistoCalib(TString inputdir, TString regexpstr, double cmenergy);
		void plotSingleHistos(TString outputfile, TString selectname);

		void plotHistos(TString inputdir, TString regexpstr, TString selectname);
		void plotScaleHisto(TString inputdir,TString regexpstr,TString selectname);

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
		CalibAnalyzer calibanalyzer_;
		std::vector<TCanvas*> canvasvector_;
};

#endif
