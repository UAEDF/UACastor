#ifndef EflowPlotter_h
#define EflowPlotter_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include <TFile.h>

class EflowPlotter {
	public:
        EflowPlotter();
		virtual ~EflowPlotter();
        void plotRatios();
		void plotEflow(TString name);
		Double_t getRatioError(TH1F * hMB, TH1F * hQCD);	
        Double_t getRatioError(double a, double b, double errora, double errorb);
		Double_t getMultiError(double a, double b, double errora, double errorb);
		std::vector<std::vector<double> > getConstantsFromFile (const char* filename );
		std::vector<std::string> splitString (const std::string& fLine);
		TH1F* getHisto(TFile* file, TString name);

	private:
};

#endif