#ifndef MainAnalyzer_h
#define MainAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TCanvas.h>

#include "FileReader.h"
#include "HistoRetriever.h"
#include "TreeAnalyzer.h"
#include "MCDataComparer.h"

class MainAnalyzer {
	public:
        MainAnalyzer();
		virtual ~MainAnalyzer();
        void makeHistos(TString inputdir, TString regexpstr);
		void plotSingleHistos(TString outputfile, TString selectname);
		void plotHistos(TString inputdir, TString regexpstr, TString selectname);
		void compareMCData(TString inputdir,TString regexpstr, TString selectname);
		void saveAllCanvas(TString inputdir, TString name);

	private:
		FileReader reader_;
		HistoRetriever histogetter_;
		TreeAnalyzer treeanalyzer_;
		std::vector<TCanvas*> canvasvector_;
};

#endif