#include "HistoRetriever.h"

#include "TObjString.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TList.h"
#include "TKey.h"
#include "TFile.h"

#include <iostream>

HistoRetriever::HistoRetriever() {

}

HistoRetriever::~HistoRetriever() { 

}

std::vector<TH1F*> HistoRetriever::getHistos(TString inputfile) {

	std::vector<TH1F*> histoList;
	
	TFile *file = new TFile(inputfile);
	TList *list = file->GetListOfKeys();
	
	for (int i=0;i<list->GetSize();i++) {		
		TKey *key = (TKey*)list->At(i);
		TH1F *hist = (TH1F*)key->ReadObj();
		histoList.push_back(hist);
	}	
	
	return histoList;

}
