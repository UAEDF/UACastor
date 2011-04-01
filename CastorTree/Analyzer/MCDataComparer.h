#ifndef MCDataComparer_h
#define MCDataComparer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>

class MCDataComparer {
	public:
        MCDataComparer();
		virtual ~MCDataComparer();
        void doCompare(std::vector<TH1F*> data_histos, std::vector<TH1F*> mc_histos);
	Double_t getRatioError(TH1F * hMB, TH1F * hQCD);	
        Double_t getRatioError(double a, double b, double errora, double errorb);
	Double_t getMultiError(double a, double b, double errora, double errorb);
	std::vector<std::vector<double> > getConstantsFromFile (const char* filename );
	std::vector<std::string> splitString (const std::string& fLine);

	private:
};

#endif
