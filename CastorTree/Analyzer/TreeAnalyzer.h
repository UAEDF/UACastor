#ifndef TreeAnalyzer_h
#define TreeAnalyzer_h

#include <TString.h>
#include <TRegexp.h>
#include <TObjArray.h>
#include <TH1.h>
#include "../src/MyJet.h"
#include "../src/MyGenJet.h"
#include "../src/MyTrackJet.h"

class TreeAnalyzer {
public:
	TreeAnalyzer();
	virtual ~TreeAnalyzer();
	void Loop(TString inputdir, TObjArray* filelist, bool isData, double cmenergy);
	Double_t getRatioError(TH1D * hMB, TH1D * hQCD);	
	Double_t getRatioError(double a, double b, double errora, double errorb);
	bool isPFDiJet(std::vector<MyJet> JetVector, bool backtoback, double usedetacut, double usedptcut);
	bool isPFDiJet(std::vector<MyJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean);
	bool isGenDiJet(std::vector<MyGenJet> JetVector, bool backtoback, double usedetacut, double usedptcut);
	bool isGenDiJet(std::vector<MyGenJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean);
        bool isTrackDiJet(std::vector<MyTrackJet> JetVector, bool backtoback, double usedetacut, double lowptcut, double highptcut, bool mean);
	Double_t deltaPhi2(double phi1, double phi2);
	void checkFlow(TH1D *histo);
	int posLeadingGenJet(std::vector<MyGenJet> JetVector,double etacut,double minptcut);
	int posLeadingTrackJet(std::vector<MyTrackJet> JetVector,double etacut,double minptcut);
        int rad2Sector(double radians);
        int AddSector(int sector,int add);
        int SubtractSector(int sector,int sub);
	
private:

	
};

#endif
