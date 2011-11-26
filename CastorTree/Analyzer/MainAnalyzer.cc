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

using namespace std;

MainAnalyzer::MainAnalyzer() {
	
	// initialize helper classes
	//reader_ = new FileReader();
	//histogetter_ = new HistoRetriever();
	//treeanalyzer_ = new TreeAnalyzer();

}

MainAnalyzer::~MainAnalyzer() { 
	

}


void MainAnalyzer::makeHistoProfile(TString inputdir, TString regexpstr, bool isData, double cmenergy) {

  TObjArray *files = reader_.getFileList(inputdir,regexpstr);
  profileanalyzer_.Loop(inputdir,files,isData,cmenergy);

}

void MainAnalyzer::makeHistoCalib(TString inputdir, TString regexpstr, double cmenergy) {

  TObjArray *files = reader_.getFileList(inputdir,regexpstr);
  calibanalyzer_.Loop(inputdir,files,cmenergy);

}


void MainAnalyzer::makeHistos(TString inputdir, TString regexpstr, bool isData, double cmenergy) {

	TObjArray *files = reader_.getFileList(inputdir,regexpstr);
	treeanalyzer_.Loop(inputdir,files, isData, cmenergy);

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


void MainAnalyzer::plotScaleHisto(TString inputdir,TString regexpstr,TString selectname) {
  
  //-- reset canvas vector
  canvasvector_.clear();
  
  TObjArray* filelist = reader_.getFileList(inputdir,regexpstr);	
  TIter next(filelist);
  TObjString* itfile = 0;
  
  std::vector<TString> filenamelist;
  std::vector<std::vector<TH1F*> > histolist;
  std::vector<std::vector<double> > entrylist;

  //-- loop over files
  while((itfile = (TObjString*)next())) {
    
    std::vector<TH1F*> histo = histogetter_.getHistos(inputdir+itfile->GetString());
    
    std::vector<TH1F*> selhisto;
    selhisto.clear();
    
    std::vector<double> nentry;
    nentry.clear();
    
    //-- loop to get selected histos
    for (unsigned int i = 0; i < histo.size(); i++) {
      
      TString name = histo[i]->GetTitle();
      
      if (!name.Contains(selectname)) continue;
      
      selhisto.push_back(histo[i]);
      nentry.push_back(histo[i]->GetEntries());
    }
    
    histolist.push_back(selhisto);
    entrylist.push_back(nentry);
    filenamelist.push_back(itfile->GetString());
  }

  //-- compute the weight

  unsigned int ifile_data;
  std::vector<std::vector<double> > weightlist;

  for (unsigned int ifile = 0; ifile <histolist.size(); ifile++) {
    if(filenamelist[ifile].Contains("data")) ifile_data = ifile;
  }

  for (unsigned int ifile = 0; ifile <histolist.size(); ifile++) {
    
    std::vector<double> weight;
    weight.clear();
    
    for (unsigned int ihisto = 0; ihisto < histolist[0].size(); ihisto++) {
      weight.push_back(entrylist[ifile_data][ihisto] / entrylist[ifile][ihisto]);
    }

    weightlist.push_back(weight);
  }

  //-- print some information

  for (unsigned int ifile = 0; ifile <histolist.size(); ifile++) {

    cout<<endl<<"file: "<<filenamelist[ifile].Data()<<endl;

    for (unsigned int ihisto = 0; ihisto < histolist[0].size(); ihisto++) {

      cout<<"histo : "<<histolist[ifile][ihisto]->GetTitle()<<" entries: "<<entrylist[ifile][ihisto]<<" weight: "<<weightlist[ifile][ihisto]<<endl;
    }
  }
  
  //-- scale histograms

  for (unsigned int ifile = 0; ifile <histolist.size(); ifile++) {

    for (unsigned int ihisto = 0; ihisto < histolist[0].size(); ihisto++) {

      histolist[ifile][ihisto]->Scale(weightlist[ifile][ihisto]);

    }
  }

  //-- plot everything

  TCanvas *c[histolist[0].size()];
  setPlotStyle();
  
  //-- loop over histos
  for (unsigned int ihisto = 0; ihisto < histolist[0].size(); ihisto++) { 
    
    double max = 0;
    double min = 10000000;
    
    //-- loop over files to calculate min and max in y
    for (unsigned int ifile = 0; ifile <histolist.size(); ifile++) { 
      double tempmax = histolist[ifile][ihisto]->GetBinContent(histolist[ifile][ihisto]->GetMaximumBin());
      double tempmin = histolist[ifile][ihisto]->GetBinContent(histolist[ifile][ihisto]->GetMinimumBin());
      if (tempmax >= max) max = tempmax;
      if (tempmin <= min) min = tempmin;
    }
	  
    if (max-min > 1000 && min == 0) min = 0.001;
    if (max-min < 1000) min = 0;
    
    // std::cout << "min = " << min << " max = " << max << std::endl;
    
    Char_t cname[50];
    sprintf(cname,"%s",histolist[0][ihisto]->GetName());
    
    c[ihisto] = new TCanvas(cname,histolist[0][ihisto]->GetTitle());
    c[ihisto]->Divide(1,2);
    
    TPad *p1 = (TPad*)c[ihisto]->cd(1);
    p1->SetPad(0.0,0.2,1,1);
    if (max-min > 1000) p1->SetLogy();
	
    //-- loop over files to plot them
    for (unsigned int ifile = 0; ifile < histolist.size(); ifile++) { 
      
      histolist[ifile][ihisto]->GetYaxis()->SetRangeUser(min,max*1.2);
      histolist[ifile][ihisto]->SetLineColor(ifile+1);
      if (ifile==0) histolist[ifile][ihisto]->SetLineWidth(3);
      if (ifile==0) histolist[ifile][ihisto]->Draw("elp");
      if (ifile!=0) histolist[ifile][ihisto]->Draw("elpsame");
    }
		
    //-- get info for legend

    std::vector<TString> initial_title;
    
    //-- loop over files to retrieve initial title
    for (unsigned int ifile = 0; ifile < histolist.size(); ifile++)
      initial_title.push_back(histolist[ifile][ihisto]->GetTitle());
    
    //-- loop over files to set file title to the histo
    for (unsigned int ifile = 0; ifile < histolist.size(); ifile++) 
      histolist[ifile][ihisto]->SetTitle(filenamelist[ifile]);
    
    TPad *p2 = (TPad*)c[ihisto]->cd(2);
    p2->SetPad(0.0,0.0,1,0.2);	
    TLegend *legend = new TLegend(0.1,0.1,0.90,0.90);
    legend->SetMargin(0.1);
    legend->SetFillColor(kWhite);
    
    //-- loop over files to plot the legends
    for (unsigned int ifile = 0; ifile < histolist.size(); ifile++)  
      legend->AddEntry(histolist[ifile][ihisto],histolist[ifile][ihisto]->GetTitle(),"lpf");
    
    legend->Draw();
    
    //-- loop over files to set back initial title
    for (unsigned int ifile = 0; ifile < histolist.size(); ifile++)
      histolist[ifile][ihisto]->SetTitle(initial_title[ifile]);
    
    canvasvector_.push_back(c[ihisto]);
    if(ihisto == histolist[0].size() - 1) c[ihisto]->WaitPrimitive();
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
      TString name = histovector[i]->GetTitle();
      if (name.Contains(selectname)) selectedhistos.push_back(histovector[i]);
    }
    
    allhistovector.push_back(selectedhistos);
    files_string.push_back(fn->GetString());
  }
  
  
  TCanvas *c[allhistovector[0].size()];
  setPlotStyle(); // set plot style

  // plot everything
  for (unsigned int i=0;i<allhistovector[0].size();i++) { // loop over number of histos
    
    double max = 0;
    double min = 10000000;
    for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
      // calculate min and max ranges
      double tempmax = allhistovector[j][i]->GetBinContent(allhistovector[j][i]->GetMaximumBin());
      double tempmin = allhistovector[j][i]->GetBinContent(allhistovector[j][i]->GetMinimumBin());
      if (tempmax >= max) max = tempmax;
      if (tempmin <= min) min = tempmin;
    }
    
    if (max-min > 1000 && min == 0) min = 0.001;
    if (max-min < 1000) min = 0;
    
    //std::cout << "min = " << min << " max = " << max << std::endl;
    
    Char_t cname[50];
    sprintf(cname,"c_%s",allhistovector[0][i]->GetName());
    c[i] = new TCanvas(cname,allhistovector[0][i]->GetTitle());
    c[i]->Divide(1,2);
    TPad *p1 = (TPad*)c[i]->cd(1);
    p1->SetPad(0.0,0.2,1,1);
    if (max-min > 1000) p1->SetLogy();
    
    for (unsigned int j=0;j<allhistovector.size();j++) { // loop over number of files
      allhistovector[j][i]->GetYaxis()->SetRangeUser(min,max*1.2);
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
    if(i == allhistovector[0].size() - 1) c[i]->WaitPrimitive();
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

void MainAnalyzer::saveAllCanvasPDF(TString inputdir,TString name) {
  
  cout<<endl<<"begin to save canvas"<<endl;
  
  TString file_pdf = TString(inputdir) + TString("plot_") + TString(name) + TString(".pdf");
  
  canvasvector_[0]->Print(TString(TString(file_pdf)+TString("[")).Data());

  for (unsigned int i=0;i<canvasvector_.size();i++) {
    TCanvas *c = canvasvector_[i];
    canvasvector_[i]->Print(file_pdf.Data());
    TString cname;
    cname.Append(inputdir);
    cname.Append(c->GetName());
    cname.Append("_");
    cname.Append(name);
    cname.Append(".png");
    c->SaveAs(cname);
  }
  
  canvasvector_[0]->Print(TString(TString(file_pdf)+TString("]")).Data());
  cout<<"canvas saved !"<<endl;
}

void MainAnalyzer::saveAllCanvas(TString inputdir,TString name) {
  
  cout<<"begin to save canvas"<<endl;
  
  TString file_pdf = TString(inputdir) + TString("plot_") + TString(name) + TString(".pdf");
  
  canvasvector_[0]->Print(TString(TString(file_pdf)+TString("[")).Data());
  
  for (unsigned int i=0;i<canvasvector_.size();i++) {
    TCanvas *c = canvasvector_[i];
    canvasvector_[i]->Print(file_pdf.Data());
    TString cname;
    cname.Append(inputdir);
    cname.Append(c->GetName());
    cname.Append("_");
    cname.Append(name);
    cname.Append(".png");
    c->SaveAs(cname);
  }
  
  canvasvector_[0]->Print(TString(TString(file_pdf)+TString("]")).Data());
  cout<<"canvas saved !"<<endl;
}

void MainAnalyzer::setPlotStyle() {

  //-- set plot styles
  gStyle->SetOptStat(111111);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetStatColor(kWhite);
}


void MainAnalyzer::setCMSStyle(){
	
	std::cout << "CMS Style Loaded" << std::endl;
	
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

