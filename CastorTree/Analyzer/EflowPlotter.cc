#include "EflowPlotter.h"
#include "FileReader.h"
#include "HistoRetriever.h"

#include "TObjString.h"
#include "TSystem.h"
#include "TCanvas.h"
#include <TStyle.h>
#include <TF1.h>
#include <TFile.h>
#include <TList.h>
#include <TKey.h>
#include <TGraphErrors.h>

#include <iostream>
#include <fstream>

EflowPlotter::EflowPlotter() {

}

EflowPlotter::~EflowPlotter() { 

}

void EflowPlotter::plotRatios() {

	// set plot styles
	gStyle->SetOptStat(111111);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetStatColor(kWhite);
	
	// define wanted files
	TFile *f900GeVdata = new TFile();
	TFile *f900GeVMC = new TFile();
	TFile *f2760GeVdata = new TFile();
	TFile *f2760GeVMC = new TFile();
	TFile *f7TeVdata = new TFile();
	TFile *f7TeVMC = new TFile();
	std::cout << "debug 1" << std::endl;
	// get list of all files in this directory
	FileReader reader;
	TString inputdir = "./";
	TObjArray *files = reader.getFileList(inputdir,"output_all_");
	std::cout << "debug 2" << std::endl;
	// process list of files
	TIter       next(files);
	TObjString* fn = 0;
	TString currentfile = "";
	while((fn = (TObjString*)next())) {
        
		currentfile.Clear();
		currentfile = fn->GetString();
        
		if (currentfile.Contains("900") && currentfile.Contains("data")) f900GeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("900") && currentfile.Contains("MC")) f900GeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		if (currentfile.Contains("2760") && currentfile.Contains("data")) f2760GeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("2760") && currentfile.Contains("MC")) f2760GeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		if (currentfile.Contains("7TeV") && currentfile.Contains("data")) f7TeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("7TeV") && currentfile.Contains("MC")) f7TeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		// do what ever
		std::cout << "opened " << fn->GetString() << std::endl;     
	}
	std::cout << "debug 3" << std::endl;
	// graph for data
	Double_t y1data = 0;
	Double_t y2data = 0;
	Double_t y3data = 0;
	Double_t y1data_error = 0;
	Double_t y2data_error = 0;
	Double_t y3data_error = 0;
	if (f900GeVdata->GetSize() > 0) y1data  = getHisto(f900GeVdata,"heflow_DijetRatio")->GetBinContent(1);
	if (f2760GeVdata->GetSize() > 0) y2data = getHisto(f2760GeVdata,"heflow_DijetRatio")->GetBinContent(1);
	if (f7TeVdata->GetSize() > 0) y3data = getHisto(f7TeVdata,"heflow_DijetRatio")->GetBinContent(1);
	if (f900GeVdata->GetSize() > 0) y1data_error= getHisto(f900GeVdata,"heflow_DijetRatio")->GetBinError(1);
	if (f2760GeVdata->GetSize() > 0) y2data_error= getHisto(f2760GeVdata,"heflow_DijetRatio")->GetBinError(1);
	if (f7TeVdata->GetSize() > 0) y3data_error= getHisto(f7TeVdata,"heflow_DijetRatio")->GetBinError(1);
	
	Double_t xdata[3] = {900,2760,7000};
	Double_t xdata_error[3] = {0,0,0};
	Double_t ydata[3] = {y1data, y2data , y3data };
	Double_t ydata_error[3] = {y1data_error, y2data_error, y3data_error };
	TGraphErrors *graph_data = new TGraphErrors(3,xdata,ydata ,xdata_error,ydata_error);
	
	// graph for MC
	Double_t y1MC = 0;
	Double_t y2MC = 0;
	Double_t y3MC = 0;
	Double_t y1MC_error = 0;
	Double_t y2MC_error = 0;
	Double_t y3MC_error = 0;
	if (f900GeVMC->GetSize() > 0) y1MC  = getHisto(f900GeVMC,"heflow_DijetRatio")->GetBinContent(1);
	if (f2760GeVMC->GetSize() > 0) y2MC = getHisto(f2760GeVMC,"heflow_DijetRatio")->GetBinContent(1);
	if (f7TeVMC->GetSize() > 0) y3MC = getHisto(f7TeVMC,"heflow_DijetRatio")->GetBinContent(1);
	if (f900GeVMC->GetSize() > 0) y1MC_error= getHisto(f900GeVMC,"heflow_DijetRatio")->GetBinError(1);
	if (f2760GeVMC->GetSize() > 0) y2MC_error= getHisto(f2760GeVMC,"heflow_DijetRatio")->GetBinError(1);
	if (f7TeVMC->GetSize() > 0) y3MC_error= getHisto(f7TeVMC,"heflow_DijetRatio")->GetBinError(1);
	
	Double_t xMC[3] = {900,2760,7000};
	Double_t xMC_error[3] = {0,0,0};
	Double_t yMC[3] = {y1MC, y2MC , y3MC };
	Double_t yMC_error[3] = {y1MC_error, y2MC_error, y3MC_error };
	TGraphErrors *graph_MC = new TGraphErrors(3,xMC,yMC ,xMC_error,yMC_error);
	
	
	TCanvas *c = new TCanvas("c","Canvas");
	c->cd(1);
	graph_MC->SetTitle("Energy flow dijet ratio's in CASTOR");
	graph_MC->GetXaxis()->SetTitle("Center of Mass energy (GeV)");
	graph_MC->GetYaxis()->SetTitle("Energy flow ratio (<E>_dijet/<E>_minbias)");
	graph_MC->SetMarkerStyle(7);
	graph_MC->SetMarkerColor(kBlack);
	graph_MC->SetFillColor(kAzure+1);
	//graph_MC->Draw("AP3");
	//graph_MC->Draw("psame");
	graph_MC->Draw("AP");
	graph_data->SetMarkerStyle(20);
	graph_data->Draw("sameP");
	graph_data->Fit("pol1","","",900,7000);
	
	graph_MC->SetTitle("MC");
	graph_data->SetTitle("data");
	
	c->BuildLegend();
	
	
	graph_MC->SetTitle("Energy flow dijet ratio's in CASTOR");
		

}

void EflowPlotter::plotEflow(TString name ) {
	
	// set plot styles
	gStyle->SetOptStat(111111);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetStatColor(kWhite);
	
	// define wanted files
	TFile *f900GeVdata = new TFile();
	TFile *f900GeVMC = new TFile();
	TFile *f2760GeVdata = new TFile();
	TFile *f2760GeVMC = new TFile();
	TFile *f7TeVdata = new TFile();
	TFile *f7TeVMC = new TFile();
	std::cout << "debug 1" << std::endl;
	// get list of all files in this directory
	FileReader reader;
	TString inputdir = "./";
	TObjArray *files = reader.getFileList(inputdir,"output_all_");
	std::cout << "debug 2" << std::endl;
	// process list of files
	TIter       next(files);
	TObjString* fn = 0;
	TString currentfile = "";
	while((fn = (TObjString*)next())) {
        
		currentfile.Clear();
		currentfile = fn->GetString();
        
		if (currentfile.Contains("900") && currentfile.Contains("data")) f900GeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("900") && currentfile.Contains("MC")) f900GeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		if (currentfile.Contains("2760") && currentfile.Contains("data")) f2760GeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("2760") && currentfile.Contains("MC")) f2760GeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		if (currentfile.Contains("7TeV") && currentfile.Contains("data")) f7TeVdata = TFile::Open(inputdir+fn->GetString(),"READ");
		if (currentfile.Contains("7TeV") && currentfile.Contains("MC")) f7TeVMC = TFile::Open(inputdir+fn->GetString(),"READ");
		
		// do what ever
		std::cout << "opened " << fn->GetString() << std::endl;     
	}
	std::cout << "debug 3" << std::endl;
	
	// graph for data
	Double_t y1data = 0;
	Double_t y2data = 0;
	Double_t y3data = 0;
	Double_t y1data_error = 0;
	Double_t y2data_error = 0;
	Double_t y3data_error = 0;
	if (f900GeVdata->GetSize() > 0) y1data  = getHisto(f900GeVdata,name)->GetMean(1);
	if (f2760GeVdata->GetSize() > 0) y2data = getHisto(f2760GeVdata,name)->GetMean(1);
	if (f7TeVdata->GetSize() > 0) y3data = getHisto(f7TeVdata,name)->GetMean(1);
	if (f900GeVdata->GetSize() > 0) y1data_error= getHisto(f900GeVdata,name)->GetMeanError(1);
	if (f2760GeVdata->GetSize() > 0) y2data_error= getHisto(f2760GeVdata,name)->GetMeanError(1);
	if (f7TeVdata->GetSize() > 0) y3data_error= getHisto(f7TeVdata,name)->GetMeanError(1);
	
	// graph for MC
	Double_t y1MC = 0;
	Double_t y2MC = 0;
	Double_t y3MC = 0;
	Double_t y1MC_error = 0;
	Double_t y2MC_error = 0;
	Double_t y3MC_error = 0;
	if (f900GeVMC->GetSize() > 0) y1MC  = getHisto(f900GeVMC,name)->GetMean(1);
	if (f2760GeVMC->GetSize() > 0) y2MC = getHisto(f2760GeVMC,name)->GetMean(1);
	if (f7TeVMC->GetSize() > 0) y3MC = getHisto(f7TeVMC,name)->GetMean(1);
	if (f900GeVMC->GetSize() > 0) y1MC_error= getHisto(f900GeVMC,name)->GetMeanError(1);
	if (f2760GeVMC->GetSize() > 0) y2MC_error= getHisto(f2760GeVMC,name)->GetMeanError(1);
	if (f7TeVMC->GetSize() > 0) y3MC_error= getHisto(f7TeVMC,name)->GetMeanError(1);
	
	
	Double_t xdata[3] = {900,2760,7000};
	Double_t xdata_error[3] = {0,0,0};
	TGraphErrors *graph_data;
	if (y2data == 0 && y2MC != 0){
		Double_t ydata[3] = {y1data/y1data, y2data/y1data , y3data/y1data };
		Double_t ydata_error[3] = {getRatioError(y1data,y1data,y1data_error,y1data_error),getRatioError(y2data,y1data,y2data_error,y1data_error) ,getRatioError(y3data,y1data,y3data_error,y1data_error) };
		graph_data = new TGraphErrors(3,xdata,ydata ,xdata_error,ydata_error);
	} else {
		Double_t ydata[3] = {y1data, y2data , y3data };
		Double_t ydata_error[3] = {y1data_error, y2data_error, y3data_error };
		graph_data = new TGraphErrors(3,xdata,ydata ,xdata_error,ydata_error);
	}
	
	Double_t xMC[3] = {900,2760,7000};
	Double_t xMC_error[3] = {0,0,0};
	TGraphErrors *graph_MC;
	if (y2data == 0 && y2MC != 0){
		Double_t yMC[3] = {y1MC/y1MC, y2MC/y1MC , y3MC/y1MC };
		Double_t yMC_error[3] = {getRatioError(y1MC,y1MC,y1MC_error,y1MC_error),getRatioError(y2MC,y1MC,y2MC_error,y1MC_error) ,getRatioError(y3MC,y1MC,y3MC_error,y1MC_error) };
		graph_MC = new TGraphErrors(3,xMC,yMC ,xMC_error,yMC_error);
	} else {
		Double_t yMC[3] = {y1MC, y2MC , y3MC };
		Double_t yMC_error[3] = {y1MC_error, y2MC_error, y3MC_error };
		graph_MC = new TGraphErrors(3,xMC,yMC ,xMC_error,yMC_error);
	}
	
	
	TCanvas *c = new TCanvas("c","Canvas");
	c->cd(1);
	graph_MC->SetTitle("Energy flow in CASTOR");
	graph_MC->GetXaxis()->SetTitle("Center of Mass energy (GeV)");
	graph_MC->GetYaxis()->SetTitle("Energy flow(<E>)");
	graph_MC->SetMarkerStyle(7);
        graph_MC->SetMarkerColor(kBlack);
        graph_MC->SetFillColor(kAzure+1);
        //graph_MC->Draw("AP3");
        //graph_MC->Draw("psame");
	graph_MC->Draw("AP");
	graph_data->SetMarkerStyle(20);
	graph_data->Draw("sameP");
	graph_data->Fit("pol1","","",900,7000);
	
	graph_MC->SetTitle("MC");
	graph_data->SetTitle("data");
	
	c->BuildLegend();
	
	graph_MC->SetTitle("Energy flow in CASTOR");
	
	
}

Double_t EflowPlotter::getRatioError(TH1F * hMB, TH1F * hQCD) {
	
	Double_t error = 0;
	Double_t ratio = hQCD->GetMean()/hMB->GetMean();
	Double_t QCDmeanerror = hQCD->GetMeanError();
	Double_t MBmeanerror = hMB->GetMeanError();
	Double_t QCDmean = hQCD->GetMean();
	Double_t MBmean = hMB->GetMean();
	
	error = ratio*ratio*((QCDmeanerror*QCDmeanerror)/(QCDmean*QCDmean) + (MBmeanerror*MBmeanerror)/(MBmean*MBmean));
	error = sqrt(error);
	return error;
	
}

Double_t EflowPlotter::getRatioError(double	a, double b, double errora, double errorb) {
	
	Double_t error = 0;
	Double_t ratio = a/b;
	
	error = ratio*ratio*((errora*errora)/(a*a) + (errorb*errorb)/(b*b));
	error = sqrt(error);
	return error;
	
}

Double_t EflowPlotter::getMultiError(double	a, double b, double errora, double errorb) {
	
	Double_t error = 0;
	
	error = (a*a)*(errorb*errorb) + (errora*errora)*(b*b);
	error = sqrt(error);
	return error;
	
}

std::vector<std::vector<double> > EflowPlotter::getConstantsFromFile (const char* filename ) {
	
	std::vector<std::vector<double> > constants;
	string line;
	ifstream myfile (filename);
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			//std::cout << line << std::endl;
			std::vector<std::string> strings = splitString(line);
			//if (strings.size() != 0) std::cout << "strings[4] = " << strings[4] << std::endl;
			std::vector<double> vector;
			if (strings.size() != 0 && strings[0] != "#") vector.push_back(atof(strings[1].c_str()));
			if (strings.size() != 0 && strings[0] != "#") vector.push_back(atof(strings[2].c_str()));
			if (strings.size() != 0 && strings[0] != "#") vector.push_back(atof(strings[4].c_str()));
			if (strings.size() != 0 && strings[0] != "#") constants.push_back(vector);
		}
		myfile.close();
	} else {
		std::cout << "Unable to open file " << filename << std::endl; 
	}
	
	return constants;
}

std::vector<std::string> EflowPlotter::splitString (const std::string& fLine) {
	std::vector <std::string> result;
	int start = 0;
	bool empty = true;
	for (unsigned i = 0; i <= fLine.size (); i++) {
		if (fLine [i] == ' ' || i == fLine.size ()) {
			if (!empty) {
				std::string item (fLine, start, i-start);
				result.push_back (item);
				empty = true;
			}
			start = i+1;
		}
		else {
			if (empty) empty = false;
		}
	}
	return result;
}

TH1F* EflowPlotter::getHisto(TFile* file, TString name) {
	std::cout << "debug 1-1" << std::endl;
	TList *list = file->GetListOfKeys();
	
	std::cout << "debug 1-2" << std::endl;
	
	TH1F *output;
	
	for (int i=0;i<list->GetSize();i++) {
		TKey *key = (TKey*)list->At(i);
		TH1F *hist = (TH1F*)key->ReadObj();
		if (hist->GetName() == name) output = hist;
	}
	return output;
}

/*
m.makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/AllPhysics2760/CastorTree_data_AllPhysics2760_Run2011A-PromptReco-v2_RECOwithCorrector_Run161366/2f213423cfb2070ca412e387d66127e3/","CastorTree_data_AllPhysics2760_Run2011A-PromptReco-v2_RECOwithCorrector_")
m.makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/MinimumBias/CastorTree_data_Commissioning10-398patch2_900GeV-v1_RECOwithCorrector_Run134721/7bbb562cf75d816f94e942c1f7800c1e/","CastorTree_data_Commissioning10-398patch2_900GeV-v1_RECOwithCorrector_")
m.makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/MinimumBias/CastorTree_data_Commissioning10-398patch2_7TeV-v1_RECOwithCorrector_Run132959-132961/2f213423cfb2070ca412e387d66127e3/","CastorTree_data_Commissioning10-398patch2_7TeV-v1_RECOwithCorrector_")
m.makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/Step1_MinBias7TeV_PythiaD6T_3100_Default_v1_100k_1/CastorTree_MC_7TeV_PythiaD6T_3100_Default_v1_1/6f254b9e8eae0fa3deac30f9b8c6fad2/","CastorTree_MC_7TeV_3100_Default")
m.makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/CastorTree_MC_900GeV_PythiaD6T_3100_Default_v1_1/ab8792ebd11566ddc4df12681cd233d9/","CastorTree_MC_900GeV_3100_Default_")
*/
