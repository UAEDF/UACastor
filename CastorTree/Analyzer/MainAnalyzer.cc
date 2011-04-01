#include "MainAnalyzer.h"

#include <TROOT.h>
#include "TObjString.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TList.h"
#include "TKey.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TSystem.h"
#include <TStyle.h>

#include <iostream>

MainAnalyzer::MainAnalyzer() {
	
	// initialize helper classes
	//reader_ = new FileReader();
	//histogetter_ = new HistoRetriever();
	//treeanalyzer_ = new TreeAnalyzer();

}

MainAnalyzer::~MainAnalyzer() { 
	

}

void MainAnalyzer::makeHistos(TString inputdir, TString regexpstr) {

	TObjArray *files = reader_.getFileList(inputdir,regexpstr);
	treeanalyzer_.Loop(inputdir,files);

}

void MainAnalyzer::plotSingleHistos(TString outputfile, TString selectname) {
	
	// reset canvas vector
	canvasvector_.clear();
	
	std::vector<TH1F*> histovector = histogetter_.getHistos(outputfile);
	std::vector<TH1F*> selectedhistos;
	selectedhistos.clear();
	
	for (unsigned int i=0;i<histovector.size();i++) {
		TString name = histovector[i]->GetName();
		if (name.Contains(selectname)) selectedhistos.push_back(histovector[i]);
	}
	
	TCanvas *c[selectedhistos.size()];
	
	// set plot styles
	gStyle->SetOptStat(111111);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetStatColor(kWhite);
	
	for (unsigned int i=0;i<selectedhistos.size();i++) {
		Char_t cname[50];
		sprintf(cname,"c_%s",selectedhistos[i]->GetName());
		
		c[i] = new TCanvas(cname,selectedhistos[i]->GetTitle());
		c[i]->Divide(1,1);
		c[i]->cd(1);
		selectedhistos[i]->Draw("elp");
		canvasvector_.push_back(c[i]);
	}
}

void MainAnalyzer::plotHistos(TString inputdir,TString regexpstr, TString selectname) {
	
	// reset canvas vector
	canvasvector_.clear();
	
	TObjArray *files = reader_.getFileList(inputdir,regexpstr);
	
	std::vector<std::vector<TH1F*> > allhistovector;
	
	TIter       next(files); 
	TObjString* fn = 0;
	std::vector<TString> files_string;
	
	while((fn = (TObjString*)next())) {
		std::vector<TH1F*> histovector = histogetter_.getHistos(inputdir+fn->GetString());
		std::vector<TH1F*> selectedhistos;
		selectedhistos.clear();
		
		for (unsigned int i=0;i<histovector.size();i++) {
			TString name = histovector[i]->GetName();
			if (name.Contains(selectname)) selectedhistos.push_back(histovector[i]);
		}
		
		allhistovector.push_back(selectedhistos);
		files_string.push_back(fn->GetString());
	}
	
	
	TCanvas *c[allhistovector[0].size()];
	
	// set plot styles
	gStyle->SetOptStat(111111);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetStatColor(kWhite);
	
	// plot everything
	for (unsigned int i=0;i<allhistovector[0].size();i++) { // loop over number of histos
		
		double max = 1;
		double min = 0.1;
		for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
			// calculate min and max ranges
			double tempmax = allhistovector[j][i]->GetBinContent(allhistovector[j][i]->GetMaximumBin());
			double tempmin = allhistovector[j][i]->GetBinContent(allhistovector[j][i]->GetMinimumBin());
			if (tempmax >= max) max = tempmax;
			if (tempmin <= min) min = tempmin;
		}
		if (min == 0) min = 0.1;
		//std::cout << "min = " << min << " max = " << max << std::endl;
		
		Char_t cname[50];
		sprintf(cname,"c_%s",allhistovector[0][i]->GetName());
		c[i] = new TCanvas(cname,allhistovector[0][i]->GetTitle());
		c[i]->Divide(1,2);
		TPad *p1 = (TPad*)c[i]->cd(1);
		p1->SetPad(0.0,0.2,1,1);
		if (max-min > 1000. && min > 0) p1->SetLogy();
		
		for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
			allhistovector[j][i]->GetYaxis()->SetRangeUser(min-(min/5),max+(max/5));
			allhistovector[j][i]->SetLineColor(j+1);
			if (j==0) allhistovector[j][i]->SetLineWidth(3);
			if (j==0) allhistovector[j][i]->Draw("elp");
			if (j!=0) allhistovector[j][i]->Draw("elpsame");
		}
		
		// get info for legend
		TString initial_title = allhistovector[0][i]->GetTitle();
		for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
			allhistovector[j][i]->SetTitle(files_string[j]);
		}
		
		TPad *p2 = (TPad*)c[i]->cd(2);
		p2->SetPad(0.0,0.0,1,0.2);	
		TLegend *legend = new TLegend(0.1,0.1,0.90,0.90);
		legend->SetMargin(0.1);
		legend->SetFillColor(kWhite);
		
		for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
			legend->AddEntry(allhistovector[j][i],allhistovector[j][i]->GetTitle(),"lpf");
		}
		legend->Draw();
		
		// set back initial title to first histogram
		allhistovector[0][i]->SetTitle(initial_title);
		
		canvasvector_.push_back(c[i]);
	}
	
}

void MainAnalyzer::compareMCData(TString inputdir,TString regexpstr, TString selectname) {
	// reset canvas vector
	canvasvector_.clear();
	
	TObjArray *files = reader_.getFileList(inputdir,regexpstr);
	
	std::vector<std::vector<TH1F*> > allhistovector;
	
	TIter       next(files); 
	TObjString* fn = 0;
	std::vector<TString> files_string;
	
	while((fn = (TObjString*)next())) {
		std::vector<TH1F*> histovector = histogetter_.getHistos(inputdir+fn->GetString());
		std::vector<TH1F*> selectedhistos;
		selectedhistos.clear();
		
		for (unsigned int i=0;i<histovector.size();i++) {
			TString name = histovector[i]->GetName();
			if (name.Contains(selectname)) selectedhistos.push_back(histovector[i]);
		}
		
		allhistovector.push_back(selectedhistos);
		std::cout << "pushed back file " << fn->GetString() << std::endl;
		files_string.push_back(fn->GetString());
	}
	
	if (allhistovector.size() > 2) std::cout << " WARNING: there are more then 2 files found, will only use the first 2 ones..." << std::endl;
	
	// compare data and MC, data always first !
	MCDataComparer comp;
	if (files_string[0].Contains("data") && files_string[1].Contains("MC")) comp.doCompare(allhistovector[0],allhistovector[1]);
	if (files_string[0].Contains("MC") && files_string[1].Contains("data")) comp.doCompare(allhistovector[1],allhistovector[0]);
	
}

void MainAnalyzer::saveAllCanvas(TString inputdir, TString name) {
	
	for (unsigned int i=0;i<canvasvector_.size();i++) {
		TCanvas *c = canvasvector_[i];
		TString cname;
		cname.Append(inputdir);
		cname.Append(c->GetName());
		cname.Append("_");
		cname.Append(name);
		cname.Append(".pdf");
		c->SaveAs(cname);
	}
	
}

