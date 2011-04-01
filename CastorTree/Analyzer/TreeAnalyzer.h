#ifndef TreeAnalyzer_h
#define TreeAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>

class TreeAnalyzer {
	public:
        TreeAnalyzer();
		virtual ~TreeAnalyzer();
        void Loop(TString inputdir, TObjArray* filelist);
	Double_t getRatioError(TH1F * hMB, TH1F * hQCD);	
        Double_t getRatioError(double a, double b, double errora, double errorb);

	private:
};

#endif
