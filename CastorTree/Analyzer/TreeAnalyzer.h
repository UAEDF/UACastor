#ifndef TreeAnalyzer_h
#define TreeAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include "../src/MyJet.h"

class TreeAnalyzer {
public:
	TreeAnalyzer();
	virtual ~TreeAnalyzer();
	void Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy);
	Double_t getRatioError(TH1F * hMB, TH1F * hQCD);	
	Double_t getRatioError(double a, double b, double errora, double errorb);
	bool isPFDiJet(std::vector<MyJet> JetVector, bool backtoback, double usedetacut, double usedptcut);
	Double_t deltaPhi2(double phi1, double phi2);
	
private:

	
};

#endif
