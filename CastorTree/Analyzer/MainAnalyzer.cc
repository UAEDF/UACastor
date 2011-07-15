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

void MainAnalyzer::setCMSStyle(){
	
	cout << "CMS Style Loaded" << endl;
	
	TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
	
	// For the canvas:
	tdrStyle->SetCanvasBorderMode(0);
	tdrStyle->SetCanvasColor(kWhite);
	// tdrStyle->SetCanvasDefH(200); //Height of canvas
	//tdrStyle->SetCanvasDefW(200); //Width of canvas
	tdrStyle->SetCanvasDefX(0);   //POsition on screen
	tdrStyle->SetCanvasDefY(0);
	
	// For the Pad:
	tdrStyle->SetPadBorderMode(0);
	tdrStyle->SetPadBorderSize(0);
	tdrStyle->SetPadColor(kWhite);
	//   tdrStyle->SetPadGridX(false);
	//   tdrStyle->SetPadGridY(false);
	//   tdrStyle->SetGridColor(0);
	//   tdrStyle->SetGridStyle(3);
	//   tdrStyle->SetGridWidth(1);
	
	// For the frame:
	tdrStyle->SetFrameBorderMode(0);
	tdrStyle->SetFrameBorderSize(0);
	tdrStyle->SetFrameFillColor(0);
	tdrStyle->SetFrameFillStyle(0);
	tdrStyle->SetFrameLineColor(1);
	tdrStyle->SetFrameLineStyle(1);
	tdrStyle->SetFrameLineWidth(1);
	
	// For the histo:
	// tdrStyle->SetHistFillColor(1);
	// tdrStyle->SetHistFillStyle(0);
	tdrStyle->SetHistLineColor(1);
	tdrStyle->SetHistLineStyle(0);
	tdrStyle->SetHistLineWidth(1);
	// tdrStyle->SetLegoInnerR(Float_t rad =3D 0.5);
	// tdrStyle->SetNumberContours(Int_t number =3D 20);
	
	tdrStyle->SetEndErrorSize(2);
	//tdrStyle->SetErrorMarker(20);
	//tdrStyle->SetErrorX(0.);
	
	tdrStyle->SetMarkerStyle(20);
	
	//For the fit/function:
	tdrStyle->SetOptFit(0);
	tdrStyle->SetFitFormat("5.4g");
	tdrStyle->SetFuncColor(2);
	tdrStyle->SetFuncStyle(1);
	tdrStyle->SetFuncWidth(1);
	
	//For the date:
	tdrStyle->SetOptDate(0);
	// tdrStyle->SetDateX(Float_t x =3D 0.01);
	// tdrStyle->SetDateY(Float_t y =3D 0.01);
	
	// For the statistics box:
	//  tdrStyle->SetOptFile(0);
	tdrStyle->SetOptStat(0); // To display the mean and RMS:   = SetOptStat("mr");
	tdrStyle->SetStatColor(kWhite);
	tdrStyle->SetStatFont(42);
	tdrStyle->SetStatFontSize(0.025);
	tdrStyle->SetStatTextColor(kBlack);
	tdrStyle->SetStatFormat("6.4g");
	tdrStyle->SetStatBorderSize(0);
	tdrStyle->SetStatH(0.1);
	tdrStyle->SetStatW(0.15);
	// tdrStyle->SetStatStyle(Style_t style =3D 1001);
	// tdrStyle->SetStatX(Float_t x =3D 0);
	// tdrStyle->SetStatY(Float_t y =3D 0);
	
	// Margins:
	tdrStyle->SetPadTopMargin(0.05);
	tdrStyle->SetPadBottomMargin(0.13);
	tdrStyle->SetPadLeftMargin(0.13);
	tdrStyle->SetPadRightMargin(0.05);
	
	// For the Global title:
	
	tdrStyle->SetOptTitle(0);
	tdrStyle->SetTitleFont(42);
	tdrStyle->SetTitleColor(1);
	tdrStyle->SetTitleTextColor(kWhite);
	tdrStyle->SetTitleFillColor(kWhite);
	tdrStyle->SetTitleFontSize(0.05);
	// tdrStyle->SetTitleH(0); // Set the height of the title box
	// tdrStyle->SetTitleW(0); // Set the width of the title box
	// tdrStyle->SetTitleX(0); // Set the position of the title box
	// tdrStyle->SetTitleY(0.985); // Set the position of the title box
	// tdrStyle->SetTitleStyle(Style_t style =3D 1001);
	// tdrStyle->SetTitleBorderSize(2);
	
	// For the axis titles:
	
	tdrStyle->SetTitleColor(1, "XYZ");
	tdrStyle->SetTitleFont(42, "XYZ");
	tdrStyle->SetTitleSize(0.06, "XYZ");
	// tdrStyle->SetTitleXSize(Float_t size =3D 0.02); // Another way to = set the size?
	// tdrStyle->SetTitleYSize(Float_t size =3D 0.02);
	tdrStyle->SetTitleXOffset(0.9);
	tdrStyle->SetTitleYOffset(1.05);
	// tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the = Offset
	
	// For the axis labels:
	
	tdrStyle->SetLabelColor(1, "XYZ");
	tdrStyle->SetLabelFont(42, "XYZ");
	tdrStyle->SetLabelOffset(0.007, "XYZ");
	tdrStyle->SetLabelSize(0.05, "XYZ");
	
	// For the axis:
	
	tdrStyle->SetAxisColor(1, "XYZ");
	tdrStyle->SetStripDecimals(kTRUE);
	tdrStyle->SetTickLength(0.03, "XYZ");
	tdrStyle->SetNdivisions(510, "XYZ");
	tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side = of the frame
	tdrStyle->SetPadTickY(1);
	
	// Change for log plots:
	//   tdrStyle->SetOptLogx(0);
	//   tdrStyle->SetOptLogy(0);
	//   tdrStyle->SetOptLogz(0);
	
	// Postscript options:
	//  tdrStyle->SetPaperSize(7.5,7.5);
	// tdrStyle->SetLineScalePS(Float_t scale =3D 3);
	// tdrStyle->SetLineStyleString(Int_t i, const char* text);
	// tdrStyle->SetHeaderPS(const char* header);
	// tdrStyle->SetTitlePS(const char* pstitle);
	
	// tdrStyle->SetBarOffset(Float_t baroff =3D 0.5);
	// tdrStyle->SetBarWidth(Float_t barwidth =3D 0.5);
	// tdrStyle->SetPaintTextFormat(const char* format =3D "g");
	// tdrStyle->SetPalette(Int_t ncolors =3D 0, Int_t* colors =3D 0);
	// tdrStyle->SetTimeOffset(Double_t toffset);
	// tdrStyle->SetHistMinimumZero(kTRUE);
	
	tdrStyle->cd();
	// gSystem->Load("libRooStats");
	// using namespace RooFit;
	
}

