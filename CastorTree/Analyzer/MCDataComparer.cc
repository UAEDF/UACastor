#include "MCDataComparer.h"

#include "TObjString.h"
#include "TSystem.h"
#include "TCanvas.h"
#include <TStyle.h>
#include <TF1.h>
#include <TFile.h>

#include <iostream>
#include <fstream>

MCDataComparer::MCDataComparer() {

}

MCDataComparer::~MCDataComparer() { 

}

void MCDataComparer::doCompare(std::vector<TH1F*> data_histos, std::vector<TH1F*> mc_histos) {

	// set plot styles
	gStyle->SetOptStat(111111);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetTitleFillColor(kWhite);
	gStyle->SetStatColor(kWhite);
	
	// make MC/data ratios
	TH1F *hRatios = new TH1F("hRatios","MC/data ratio for each channel",80,1,81);
	TH1F *hRatios_dist = new TH1F("hRatios_dist","Distribution of MC/data ratios",100,-5,10);
	
	TH1F *hdata_eflow_channels = NULL;
	TH1F *hmc_eflow_channels = NULL;
	
	TH1F *hdata_eflow_modules_IntNorm = NULL;
	TH1F *hmc_eflow_modules_IntNorm = NULL;
	TH1F *hdata_eflow_sectors_IntNorm = NULL;
	TH1F *hmc_eflow_sectors_IntNorm = NULL;
	TH1F *hRatios_modules = new TH1F("hRatios_modules","MC/data ratio per module",5,1,6);
	
	for (unsigned int i=0; i<data_histos.size();i++) {
		TString dataname(data_histos[i]->GetName());
		TString mcname(mc_histos[i]->GetName());
		if (dataname.Contains("eflow_channels") && mcname.Contains("eflow_channels")) {
			hdata_eflow_channels = data_histos[i];
			hmc_eflow_channels = mc_histos[i];
			// read from files to correct the errors with the gainwidths
			const char* gainsfile("DumpCastorCondGains_Run134721.txt");
			const char* gainwidthsfile("DumpCastorCondGainWidths_Run134721.txt");
			std::vector<std::vector<double> > gains = getConstantsFromFile(gainsfile);
			std::vector<std::vector<double> > gainwidths = getConstantsFromFile(gainwidthsfile);
			std::cout << " gains vector size = " << gains.size() << " gainwidths vector size = " << gainwidths.size() << std::endl;
			int module = 1;
			int sector = 0;
			int counter = 0;
			for (unsigned int ibin=0;ibin<80;ibin++) {
				counter++;
				sector++;
				for (unsigned int ig=0;ig<gains.size();ig++) {
					if ( gains[ig][0] == sector &&  gains[ig][1] == module) {
						std::cout << " sector = " << gains[ig][0] << " module = " << gains[ig][1] << " gain = " << gains[ig][2] << " +- " << gainwidths[ig][2] << std::endl;
						if (gains[ig][2] != 0) hdata_eflow_channels->SetBinError(ibin+1,getMultiError(hdata_eflow_channels->GetBinContent(ibin+1)/gains[ig][2],gains[ig][2],hdata_eflow_channels->GetBinError(ibin+1),gainwidths[ig][2]));
					}
				}
				if (counter == 16) {module++; counter = 0;}
				if (sector == 16) sector = 0;
			}
			for (int ibin=0;ibin<80;ibin++) {
				if (hdata_eflow_channels->GetBinContent(ibin+1) !=0) 
				{hRatios->SetBinContent(ibin+1,hmc_eflow_channels->GetBinContent(ibin+1)/hdata_eflow_channels->GetBinContent(ibin+1));}
				if (hdata_eflow_channels->GetBinContent(ibin+1) !=0) 
				{hRatios->SetBinError(ibin+1,getRatioError(hmc_eflow_channels->GetBinContent(ibin+1),hdata_eflow_channels->GetBinContent(ibin+1),hmc_eflow_channels->GetBinError(ibin+1),hdata_eflow_channels->GetBinError(ibin+1)));}
			}
		}
		// get the original module and sector profiles
		if (dataname.Contains("eflow_modules") && mcname.Contains("eflow_modules")) {
			data_histos[i]->Scale(1./data_histos[i]->Integral());
			mc_histos[i]->Scale(1./mc_histos[i]->Integral());
			hdata_eflow_modules_IntNorm = data_histos[i];
			hmc_eflow_modules_IntNorm = mc_histos[i];
			for (int ibin=0;ibin<5;ibin++) {
				if (data_histos[i]->GetBinContent(ibin+1) != 0) hRatios_modules->SetBinContent(ibin+1,mc_histos[i]->GetBinContent(ibin+1)/data_histos[i]->GetBinContent(ibin+1));
				if (data_histos[i]->GetBinContent(ibin+1) != 0) hRatios_modules->SetBinError(ibin+1,getRatioError(mc_histos[i]->GetBinContent(ibin+1),data_histos[i]->GetBinContent(ibin+1),mc_histos[i]->GetBinError(ibin+1),data_histos[i]->GetBinError(ibin+1)));
			}
		}
	}
	
	// fill distribution of ratios
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hRatios->GetBinContent(ibin+1) != 0) hRatios_dist->Fill(hRatios->GetBinContent(ibin+1));
	}
	
	// draw them
	TCanvas *c = new TCanvas("c","Ratios MC/data");
	c->Divide(2,1);
	c->cd(1);
	hRatios->Draw();
	c->cd(2);
	hRatios_dist->Draw();
	hRatios_dist->Fit("gaus","EM","",-5,10);
	TF1 *myfit = hRatios_dist->GetFunction("gaus");
	std::cout << "Mean of the fit = " << myfit->GetParameter(1) << std::endl;
	std::cout << "Sigma of the fit = " << myfit->GetParameter(2) << std::endl;
	std::cout << "chi2/ndf = " << myfit->GetChisquare()/myfit->GetNDF() << std::endl;
	
	// replot the channels profile
	TH1F *heflow_channels_corrMC = new TH1F("heflow_channels_corrMC","corrected MC channel profile",80,1,81);
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hmc_eflow_channels->GetBinContent(ibin+1) != 0) heflow_channels_corrMC->SetBinContent(ibin+1,hmc_eflow_channels->GetBinContent(ibin+1)/myfit->GetParameter(1));
		if (hmc_eflow_channels->GetBinContent(ibin+1) != 0) heflow_channels_corrMC->SetBinError(ibin+1,getRatioError(hmc_eflow_channels->GetBinContent(ibin+1),myfit->GetParameter(1),hmc_eflow_channels->GetBinError(ibin+1),myfit->GetParError(1)));
	}
	
	// draw corrected MC with data
	TCanvas *cChannels = new TCanvas("cChannels","Channel profile");
	cChannels->cd(1);
	/*
	// normalize to first channel
	TH1F *heflow_channels_corrMC_norm = new TH1F(*heflow_channels_corrMC);
	TH1F *hdata_eflow_channels_norm = new TH1F(*hdata_eflow_channels);
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (heflow_channels_corrMC->GetBinContent(ibin+1) != 0) heflow_channels_corrMC_norm->SetBinContent(ibin+1,heflow_channels_corrMC->GetBinContent(ibin+1)/heflow_channels_corrMC->GetBinContent(1));
		if (heflow_channels_corrMC->GetBinContent(ibin+1) != 0) heflow_channels_corrMC_norm->SetBinError(ibin+1,getRatioError(heflow_channels_corrMC->GetBinContent(ibin+1),heflow_channels_corrMC->GetBinContent(1),
									 heflow_channels_corrMC->GetBinError(ibin+1),heflow_channels_corrMC->GetBinError(1)));
	}
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hdata_eflow_channels->GetBinContent(ibin+1) != 0) hdata_eflow_channels_norm->SetBinContent(ibin+1,hdata_eflow_channels->GetBinContent(ibin+1)/hdata_eflow_channels->GetBinContent(1));
		if (hdata_eflow_channels->GetBinContent(ibin+1) != 0) hdata_eflow_channels_norm->SetBinError(ibin+1,getRatioError(hdata_eflow_channels->GetBinContent(ibin+1),hdata_eflow_channels->GetBinContent(1),
									 hdata_eflow_channels->GetBinError(ibin+1),hdata_eflow_channels->GetBinError(1)));
	}
	*/
	heflow_channels_corrMC->SetFillColor(kGray);
	heflow_channels_corrMC->Draw("HIST");
	hdata_eflow_channels->Draw("same");
	
	// make corrected modules profile - corr is for the moment NOT corrected but norm.
	TH1F *hdata_eflow_modules = new TH1F("hdata_eflow_modules","module profile from data",5,1,6);
	TH1F *hmc_eflow_modules_corr = new TH1F("hmc_eflow_modules_corr","modules profile from MC corrected",5,1,6);
	for (unsigned int ibin=0;ibin<5;ibin++) {
		double average = 0;
		double error = 0;
		for (unsigned int icha=0+ibin*16;icha<16+ibin*16;icha++) {
			average += hdata_eflow_channels->GetBinContent(icha+1);
			error += hdata_eflow_channels->GetBinError(icha+1)*hdata_eflow_channels->GetBinError(icha+1);
		}
		hdata_eflow_modules->SetBinContent(ibin+1,average/16);
		if (ibin == 0) hdata_eflow_modules->SetBinContent(ibin+1,average/14);
		hdata_eflow_modules->SetBinError(ibin+1,sqrt(error)/16);
		if (ibin == 0) hdata_eflow_modules->SetBinError(ibin+1,sqrt(error)/14);
		// and now for MC
		average = 0;
		error = 0;
		for (unsigned int icha=0+ibin*16;icha<16+ibin*16;icha++) { // take it currently from non-corrected channels
			average += hmc_eflow_channels->GetBinContent(icha+1);
			error += hmc_eflow_channels->GetBinError(icha+1)*hmc_eflow_channels->GetBinError(icha+1);
		}
		hmc_eflow_modules_corr->SetBinContent(ibin+1,average/16);
		if (ibin == 0) hmc_eflow_modules_corr->SetBinContent(ibin+1,average/14);
		hmc_eflow_modules_corr->SetBinError(ibin+1,sqrt(error)/16);
		if (ibin == 0) hmc_eflow_modules_corr->SetBinError(ibin+1,sqrt(error)/14);
	}
	
	// make corrected sectors profile - corr is for the moment NOT corrected but norm.
	TH1F *hdata_eflow_sectors = new TH1F("hdata_eflow_sectors","sectors profile from data",16,1,17);
	TH1F *hmc_eflow_sectors_corr = new TH1F("hmc_eflow_sectors_corr","sectors profile from MC corrected",16,1,17);
	for (unsigned int ibin=0;ibin<16;ibin++) {
		double average = 0;
		double error = 0;
		for (unsigned int icha=ibin;icha<80;icha+=16) {
			average += hdata_eflow_channels->GetBinContent(icha+1);
			error += hdata_eflow_channels->GetBinError(icha+1)*hdata_eflow_channels->GetBinError(icha+1);
		}
		hdata_eflow_sectors->SetBinContent(ibin+1,average/5);
		hdata_eflow_sectors->SetBinError(ibin+1,sqrt(error)/5);
		if (ibin == 4 || ibin==5) hdata_eflow_sectors->SetBinContent(ibin+1,0);
		if (ibin == 4 || ibin==5) hdata_eflow_sectors->SetBinError(ibin+1,0);
		// and now for MC
		average = 0;
		error = 0;
		for (unsigned int icha=ibin;icha<80;icha+=16) { // take it currently from non-corrected channels
			average += hmc_eflow_channels->GetBinContent(icha+1);
			error += hmc_eflow_channels->GetBinError(icha+1)*hmc_eflow_channels->GetBinError(icha+1);
		}
		hmc_eflow_sectors_corr->SetBinContent(ibin+1,average/5);
		hmc_eflow_sectors_corr->SetBinError(ibin+1,sqrt(error)/5);
		if (ibin == 4 || ibin==5) hmc_eflow_sectors_corr->SetBinContent(ibin+1,0);
		if (ibin == 4 || ibin==5) hmc_eflow_sectors_corr->SetBinError(ibin+1,0);
	}
	
	TCanvas *cModules = new TCanvas("cModules","Modules and Sectors");
	cModules->Divide(2,1);
	cModules->cd(1);
	/*
	// normalize to first channel
	TH1F *hmc_eflow_modules_corr_norm = new TH1F(*hmc_eflow_modules_corr);
	TH1F *hdata_eflow_modules_norm = new TH1F(*hdata_eflow_modules);
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hmc_eflow_modules_corr->GetBinContent(ibin+1) != 0) hmc_eflow_modules_corr_norm->SetBinContent(ibin+1,hmc_eflow_modules_corr->GetBinContent(ibin+1)/hmc_eflow_modules_corr->GetBinContent(1));
		if (hmc_eflow_modules_corr->GetBinContent(ibin+1) != 0) hmc_eflow_modules_corr_norm->SetBinError(ibin+1,getRatioError(hmc_eflow_modules_corr->GetBinContent(ibin+1),hmc_eflow_modules_corr->GetBinContent(1),
									 hmc_eflow_modules_corr->GetBinError(ibin+1),hmc_eflow_modules_corr->GetBinError(1)));
	}
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hdata_eflow_modules->GetBinContent(ibin+1) != 0) hdata_eflow_modules_norm->SetBinContent(ibin+1,hdata_eflow_modules->GetBinContent(ibin+1)/hdata_eflow_modules->GetBinContent(1));
		if (hdata_eflow_modules->GetBinContent(ibin+1) != 0) hdata_eflow_modules_norm->SetBinError(ibin+1,getRatioError(hdata_eflow_modules->GetBinContent(ibin+1),hdata_eflow_modules->GetBinContent(1),
									 hdata_eflow_modules->GetBinError(ibin+1),hdata_eflow_modules->GetBinError(1)));
	}
	*/
	hmc_eflow_modules_corr->Scale(1./hmc_eflow_modules_corr->Integral());
	hmc_eflow_modules_corr->SetFillColor(kGray);
	hmc_eflow_modules_corr->Draw("HIST");
	hdata_eflow_modules->Scale(1./hdata_eflow_modules->Integral());
	hdata_eflow_modules->Draw("same");
	cModules->cd(2);
	/*
	// normalize to first channel
	TH1F *hmc_eflow_sectors_corr_norm = new TH1F(*hmc_eflow_sectors_corr);
	TH1F *hdata_eflow_sectors_norm = new TH1F(*hdata_eflow_sectors);
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hmc_eflow_sectors_corr->GetBinContent(ibin+1) != 0) hmc_eflow_sectors_corr_norm->SetBinContent(ibin+1,hmc_eflow_sectors_corr->GetBinContent(ibin+1)/hmc_eflow_sectors_corr->GetBinContent(1));
		if (hmc_eflow_sectors_corr->GetBinContent(ibin+1) != 0) hmc_eflow_sectors_corr_norm->SetBinError(ibin+1,getRatioError(hmc_eflow_sectors_corr->GetBinContent(ibin+1),hmc_eflow_sectors_corr->GetBinContent(1),
									 hmc_eflow_sectors_corr->GetBinError(ibin+1),hmc_eflow_sectors_corr->GetBinError(1)));
	}
	for (unsigned int ibin=0;ibin<80;ibin++) {
		if (hdata_eflow_sectors->GetBinContent(ibin+1) != 0) hdata_eflow_sectors_norm->SetBinContent(ibin+1,hdata_eflow_sectors->GetBinContent(ibin+1)/hdata_eflow_sectors->GetBinContent(1));
		if (hdata_eflow_sectors->GetBinContent(ibin+1) != 0) hdata_eflow_sectors_norm->SetBinError(ibin+1,getRatioError(hdata_eflow_sectors->GetBinContent(ibin+1),hdata_eflow_sectors->GetBinContent(1),
									 hdata_eflow_sectors->GetBinError(ibin+1),hdata_eflow_sectors->GetBinError(1)));
	}
	*/
	hmc_eflow_sectors_corr->Scale(1./hmc_eflow_sectors_corr->Integral());
	hmc_eflow_sectors_corr->SetFillColor(kGray);
	hmc_eflow_sectors_corr->Draw("HIST");
	hdata_eflow_sectors->Scale(1./hdata_eflow_sectors->Integral());
	hdata_eflow_sectors->Draw("same");
	
	
	// module ratios
	TCanvas *cRatios_modules = new TCanvas("cRatios_modules","Ratios MC/data per module");
	cRatios_modules->Divide(1,2);
	cRatios_modules->cd(1);
	hmc_eflow_modules_IntNorm->SetFillColor(kGray);
	hmc_eflow_modules_IntNorm->Draw("HIST");
	hdata_eflow_modules_IntNorm->Draw("same");
	cRatios_modules->cd(2);
	hRatios_modules->Draw();
	
	// save all histos in a root file
	string filename;
	getline(cin, filename);
        std::cout << "You entered: " << filename << endl << endl;
	const char * tfilename = filename.c_str();
	TFile* output = new TFile(tfilename,"RECREATE");
	output->cd();
	
	hdata_eflow_channels->Write();
	hmc_eflow_channels->Write();
	hdata_eflow_modules->Write();
	hdata_eflow_sectors->Write();
	hmc_eflow_modules_corr->Write();
	hmc_eflow_sectors_corr->Write();
	heflow_channels_corrMC->Write();
	hRatios->Write();
	hRatios_dist->Write();
	
	output->Close();
	

}

Double_t MCDataComparer::getRatioError(TH1F * hMB, TH1F * hQCD) {
	
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

Double_t MCDataComparer::getRatioError(double	a, double b, double errora, double errorb) {
	
	Double_t error = 0;
	Double_t ratio = a/b;
	
	error = ratio*ratio*((errora*errora)/(a*a) + (errorb*errorb)/(b*b));
	error = sqrt(error);
	return error;
	
}

Double_t MCDataComparer::getMultiError(double	a, double b, double errora, double errorb) {
	
	Double_t error = 0;
	
	error = (a*a)*(errorb*errorb) + (errora*errora)*(b*b);
	error = sqrt(error);
	return error;
	
}

std::vector<std::vector<double> > MCDataComparer::getConstantsFromFile (const char* filename ) {
	
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

std::vector<std::string> MCDataComparer::splitString (const std::string& fLine) {
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


