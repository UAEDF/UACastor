#ifndef HistoRetriever_h
#define HistoRetriever_h

#include <TString.h>
#include <TObjArray.h>
#include <TH1F.h>

class HistoRetriever {
	public:
        HistoRetriever();
	virtual ~HistoRetriever();
        std::vector<TH1F*> getHistos(TString inputfile);

	private:
};

#endif
