#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TStyle.h>
#include <TH1.h>
#include <TH2.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TRegexp.h>
#include <TExec.h>
#include <TSystem.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include <cassert>

#include "DQMAnalyze.h"

using namespace std;

int main(int argc, char *argv[]) {

  Int_t debug = 0;
  Int_t debug_choice2 = 0;

  SetStyle();

  if (argc != 3) {
    cout<<"This program was called with "<<argv[0]<<endl;
    cout<<""<<endl;
    cout<<"dataset = 1: Commissioning10"<<endl;
    cout<<"dataset = 2: Run210A"<<endl;
    cout<<"dataset = 3: Run210B"<<endl;
    cout<<""<<endl;
    cout<<"choice = 1: Castor reportSummaryMap"<<endl;
    cout<<"choice = 2: Castor ChannelSummaryMap"<<endl;
    cout<<"choice = 3: Castor AllDigiValues"<<endl;
    cout<<"choice = 4: Info reportSummaryMap (HV)"<<endl;
    return(0);
  }
  
  Int_t dataset = atoi(argv[1]);
  Int_t choice = atoi(argv[2]);

  //-- retrieve the DQM files
 
  TString dirname = "/home/roland/Castor/CastorStudy/RunSelection2010/DQMfiles/"; 
  if(dataset == 1) dirname+="Commissioning10/";
  if(dataset == 2) dirname+="Run2010A/";
  if(dataset == 3) dirname+="Run2010B/";

  if(choice == 1 || choice == 2 || choice == 3) dirname+="DQMCastor/";
  if(choice == 4)  dirname+="DQMInfo/";

  void *dir = gSystem->OpenDirectory(dirname);
       
  if (!dir) {
    cout <<  "couldn't open directory" << endl;
    return 0;
  }
		
  TObjArray*  fileList = new TObjArray;
  const char* name;
  TString     fileName;
	
  TRegexp regexp_DQM("DQM");
  TRegexp regexp_Castor("Castor");
  TRegexp regexp_Info("Info");

  while (name = gSystem->GetDirEntry(dir)) {		
    fileName = name;
    if (!fileName.CompareTo(".") || !fileName.CompareTo("..")) continue;
    if (fileName.Index(regexp_DQM) != kNPOS) fileList->Add(new TObjString(fileName));
  }  
  
  gSystem->FreeDirectory(dir);

  //-- define the array of canvas

  Int_t nbfile = fileList->GetEntries();
  Int_t nbcan = nbfile;
  TCanvas* c[nbcan];
  
  TString cname; 
  TString ctitle;
  TString epsname;

  //-- define the choice 
  
  Bool_t DQMCastor = false;
  Bool_t DQMInfo = false;

  if(choice == 1 || choice == 2 || choice == 3) DQMCastor = true;
  if(choice == 4) DQMInfo = true;

  //-- define the output files

  FILE* file_Castor_reportSummaryMap;
  FILE* file_Castor_ChannelSummaryMap;
  FILE* file_Castor_AllDigiValues;

  FILE* file_Info_reportSummaryMap;
  FILE* file_Info_reportSummaryMap_LS;

  if(dataset == 1) { 
    if(choice == 1) file_Castor_reportSummaryMap = fopen("Decision/Castor_Commissioning10_reportSummaryMap.txt","w+");  
    if(choice == 2) file_Castor_ChannelSummaryMap = fopen("Decision/Castor_Commissioning10_ChannelSummaryMap.txt","w+");
    if(choice == 3) file_Castor_AllDigiValues = fopen("Decision/Castor_Commissioning10_AllDigiValues.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap = fopen("Decision/Info_Commissioning10_reportSummaryMap.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap_LS = fopen("Decision/Info_Commissioning10_reportSummaryMap_LS.txt","w+");

    if(choice == 1) fprintf(file_Castor_reportSummaryMap,"%d  %d\n",135149,1);
    if(choice == 1) fprintf(file_Castor_reportSummaryMap,"%d  %d\n",135445,1);

    if(choice == 2) fprintf(file_Castor_ChannelSummaryMap,"%d  %d\n",135149,1);
    if(choice == 2) fprintf(file_Castor_ChannelSummaryMap,"%d  %d\n",135445,1);

    if(choice == 3) fprintf(file_Castor_AllDigiValues,"%d  %d\n",135149,1);
    if(choice == 3) fprintf(file_Castor_AllDigiValues,"%d  %d\n",135445,1);      
  }
  
  if(dataset == 2) { 
    if(choice == 1) file_Castor_reportSummaryMap = fopen("Decision/Castor_Run2010A_reportSummaryMap.txt","w+");  
    if(choice == 2) file_Castor_ChannelSummaryMap = fopen("Decision/Castor_Run2010A_ChannelSummaryMap.txt","w+");
    if(choice == 3) file_Castor_AllDigiValues = fopen("Decision/Castor_Run2010A_AllDigiValues.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap = fopen("Decision/Info_Run2010A_reportSummaryMap.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap_LS = fopen("Decision/Info_Run2010A_reportSummaryMap_LS.txt","w+");
  }
  
  if(dataset == 3) { 
    if(choice == 1) file_Castor_reportSummaryMap = fopen("Decision/Castor_Run2010B_reportSummaryMap.txt","w+");  
    if(choice == 2) file_Castor_ChannelSummaryMap = fopen("Decision/Castor_Run2010B_ChannelSummaryMap.txt","w+");
    if(choice == 3) file_Castor_AllDigiValues = fopen("Decision/Castor_Run2010B_AllDigiValues.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap = fopen("Decision/Info_Run2010B_reportSummaryMap.txt","w+");
    if(choice == 4) file_Info_reportSummaryMap_LS = fopen("Decision/Info_Run2010B_reportSummaryMap_LS.txt","w+");
  }

  //-- define the legend

  TLegend* leg = new TLegend(0.54,0.96,0.75,0.98);
  SetStyle(leg);
  TLegendEntry* entry;
  
  //-- loop over the DQM files

  cout<<""<<endl;
  cout<<"Retrieve "<<nbfile<<endl;
  cout<<"Start to loop over them\n"<<endl;

  TIter next(fileList); 
  TObjString* fn = 0;
  Int_t ican = 0;

  TApplication* rootapp = new TApplication("app",&argc, argv);

  Int_t nhisto1_missing = 0;
  Int_t nhisto2_missing = 0;
  Int_t nhisto3_missing = 0;
  Int_t nhisto4_missing = 0;

  Bool_t is_histo1 = false;
  Bool_t is_histo2 = false;  //-- histo2 not present in some file !!
  Bool_t is_histo3 = false;
  Bool_t is_histo4 = false;

  Int_t idfile_castor=0;
  Int_t idfile_info=0;

  while(fn = (TObjString*) next()) { 
    
    //-- retrieve the DQM files

    TFile* file = TFile::Open(dirname + fn->GetString()); 
    if (!file) continue; 
    
    //-- retrieve the run number
    
    TString run = fn->GetString();
    run.Remove(0,run.Length()-11);
    run.Remove(6,5);
    
    //-- loop over the DQM Castor files

    if ((TString(fn->GetString())).Index(regexp_Castor) != kNPOS && DQMCastor == true) {

      idfile_castor++;
      cout<<""<<endl;
      cout<<"open the file: "<<fn->GetString()<<" ("<<idfile_castor<<"/"<<nbfile<<") "<<endl;
      cout<<"run: "<<atoi(run.Data())<<"\n"<<endl;

      TString histoname = "DQMData/Run " + run + "/Castor/Run summary/";
      TString histoname1;
      TString histoname2;

      //-- Castor reportSummaryMap

      if(choice == 1) {

	Int_t ngreen1 = 0;
	Double_t ratio1 = 0;
	Int_t decision1 = 0;

	histoname+="EventInfo/reportSummaryMap";
	TH2F* histo1 = (TH2F*) file->Get(histoname.Data());

	is_histo1 = false;
	if(!histo1) nhisto1_missing++;
	if(!histo1 && !debug) fprintf(file_Castor_reportSummaryMap,"%d  %d \n",atoi(run),decision1); 
	if(!histo1 && debug) fprintf(file_Castor_reportSummaryMap,"%d  %d (histo not present)\n",atoi(run),decision1); 
	if(!histo1) continue;
	is_histo1 = true;

	if(dataset == 1) cname = "Castor_Commissioning10_reportSummaryMap";
	if(dataset == 2) cname = "Castor_Run2010A_reportSummaryMap";
	if(dataset == 3) cname = "Castor_Run2010B_reportSummaryMap";

	if(dataset == 1) ctitle = "Castor Commissioning10 reportSummaryMap";
	if(dataset == 2) ctitle = "Castor Run2010A reportSummaryMap";
	if(dataset == 3) ctitle = "Castor Run2010B reportSummaryMap";

	epsname = "DQMPlot/" + cname + ".pdf";	
	cname+= "_" + run;
	ctitle+= " " + run;
	
	c[ican] = new TCanvas(cname.Data(),ctitle.Data());
	c[ican]->Divide(1,1);
	
	TPad* pad = (TPad*) c[ican]->cd(1);
	preDrawCastorTH2(pad,histo1);
	histo1->Draw();

	GetDecision_reportSummaryMap(histo1,ngreen1,ratio1,decision1);
	fprintf(file_Castor_reportSummaryMap,"%d  %d\n",atoi(run),decision1);
      }

      //-- Castor ChannelSummaryMap
     
      if(choice == 2) {

	Int_t ngreen2 = 0;
	Int_t ncyan2 = 0;
	Double_t ratio2 = 0;
	Int_t decision2 = 0;

	histoname+="CastorPSMonitor/CASTOR Digi ChannelSummaryMap";
	TH2F* histo2temp = (TH2F*) file->Get(histoname.Data());
	
	is_histo2 = false;
	if(!histo2temp) nhisto2_missing++;
	if(!histo2temp && !debug) fprintf(file_Castor_ChannelSummaryMap,"%d  %d\n",atoi(run),decision2);
	if(!histo2temp && debug) fprintf(file_Castor_ChannelSummaryMap,"%d  %d (histo not present)\n",atoi(run),decision2);
	if(!histo2temp) continue;
	is_histo2 = true;

	TH2F* histo2 = (TH2F*) histo2temp->Clone("histo2");
	histo2->SetName(histoname.Data());

	histo2->GetXaxis()->SetRange(0,14);
	histo2->GetYaxis()->SetRange(0,16);

	for (int xbin = 1; xbin < 15; xbin++) {
	  for (int ybin = 1; ybin < 17; ybin++) {
	    histo2->SetBinContent(xbin,ybin,histo2temp->GetBinContent(xbin,ybin));
	  }
	}

	if(dataset == 1) cname = "Castor_Commissioning10_ChannelSummaryMap";
	if(dataset == 2) cname = "Castor_Run2010A_ChannelSummaryMap";
	if(dataset == 3) cname = "Castor_Run2010B_ChannelSummaryMap";

	if(dataset == 1) ctitle = "Castor Commissioning10 ChannelSummaryMap";
	if(dataset == 2) ctitle = "Castor Run2010A ChannelSummaryMap";
	if(dataset == 3) ctitle = "Castor Run2010B ChannelSummaryMap";

	epsname = "DQMPlot/" + cname + ".pdf";
	cname+= "_" + run;
	ctitle+= " " + run;
	
	c[ican] = new TCanvas(cname.Data(),ctitle.Data());
	if(debug_choice2 == 0) c[ican]->Divide(1,1);
	if(debug_choice2 == 1) c[ican]->Divide(2,1);

	TPad* pad1 = (TPad*) c[ican]->cd(1);
	preDrawCastorTH2(pad1,histo2);
	histo2->Draw();

	if(debug_choice2 == 1) {
	  TPad* pad2 = (TPad*) c[ican]->cd(2);
	  preDrawCastorTH2(pad2,histo2temp);
	  histo2temp->Draw();
	}

	GetDecision_ChannelSummaryMap(histo2,ngreen2,ncyan2,ratio2,decision2);
	fprintf(file_Castor_ChannelSummaryMap,"%d  %d\n",atoi(run),decision2);
      }

      //-- Castor AllDigiValues

      if(choice == 3) {

	Double_t mean3 = 0;
	Int_t decision3 = 0;

	histoname+="CastorDigiMonitor/Castor All Digi Values";
	TH1F* histo3 = (TH1F*) file->Get(histoname.Data());
	
	is_histo3 = false;
	if(!histo3) nhisto3_missing++;
	if(!histo3 && !debug) fprintf(file_Castor_AllDigiValues,"%d  %d\n",atoi(run),decision3);
	if(!histo3 && debug) fprintf(file_Castor_AllDigiValues,"%d  %d (histo not present)\n",atoi(run),decision3);
	if(!histo3) continue;
	is_histo3 = true;

	if(dataset == 1) cname = "Castor_Commissioning10_AllDigiValues";
	if(dataset == 2) cname = "Castor_Run2010A_AllDigiValues";
	if(dataset == 3) cname = "Castor_Run2010B_AllDigiValues";

	if(dataset == 1) ctitle = "Castor Commissioning10 All Digi Values";
	if(dataset == 2) ctitle = "Castor Run2010A All Digi Values";
	if(dataset == 3) ctitle = "Castor Run2010B All Digi Values";

	epsname = "DQMPlot/" + cname + ".pdf";
	cname+= "_" + run;
	ctitle+= " " + run;
	
	c[ican] = new TCanvas(cname.Data(),ctitle.Data());
	c[ican]->Divide(1,1);
	
	TPad* pad = (TPad*) c[ican]->cd(1);
	histo3->Draw();

	GetDecision_AllDigiValues(histo3,mean3,decision3);
	fprintf(file_Castor_AllDigiValues,"%d  %d\n",atoi(run),decision3);
      }

      if((choice == 1 && is_histo1 == false) || (choice == 2 && is_histo2 == false) || (choice == 3 && is_histo3 == false)) continue;

      leg->Clear();
      entry = leg->AddEntry("",run.Data(),"");
      SetStyle(entry);
      leg->Draw("same");
     
      c[ican]->Update();
      
      if(ican == 0) c[ican]->Print(TString(TString(epsname)+TString("[")).Data());   // No actual print, just open file
      c[ican]->Print(epsname.Data());  // actually print canvas to file 
      if(choice == 1 && ican == nbcan -1 -nhisto1_missing) c[ican]->Print(TString(TString(epsname)+TString("]")).Data()); // No actual print, just close file
      if(choice == 2 && ican == nbcan -1 -nhisto2_missing) c[ican]->Print(TString(TString(epsname)+TString("]")).Data()); // No actual print, just close file
      if(choice == 3 && ican == nbcan -1 -nhisto3_missing) c[ican]->Print(TString(TString(epsname)+TString("]")).Data()); // No actual print, just close file

      if(debug == 1) c[ican]->WaitPrimitive();
      if(debug == 0 && choice == 1 && ican == nbcan -1 -nhisto1_missing) c[ican]->WaitPrimitive();
      if(debug == 0 && choice == 2 && ican == nbcan -1 -nhisto2_missing) c[ican]->WaitPrimitive();
      if(debug == 0 && choice == 3 && ican == nbcan -1 -nhisto3_missing) c[ican]->WaitPrimitive();

      ican++;
    } //-- end loop over the DQM Castor files

    //-- loop over the DQM Info files
    
    if ((TString(fn->GetString())).Index(regexp_Info) != kNPOS && DQMInfo == true) {
      
      idfile_info++;
      cout<<""<<endl;
      cout<<"open the file: "<<fn->GetString()<<" ("<<idfile_info<<"/"<<nbfile<<") "<<endl;
      cout<<"run: "<<atoi(run.Data())<<"\n"<<endl;
      
      TString histoname = "DQMData/Run " + run + "/Info/Run summary/";

      vector<Int_t> list_LS_min;
      vector<Int_t> list_LS_max;
      list_LS_min.clear();
      list_LS_max.clear();
      Int_t decision4 = 0;

      histoname+="EventInfo/reportSummaryMap";
      TH2F* histo4 = (TH2F*) file->Get(histoname.Data());

      is_histo4 = false;
      if(!histo4) nhisto4_missing++;
      if(!histo4 && !debug) fprintf(file_Info_reportSummaryMap,"%d  %d\n",atoi(run),decision4);
      if(!histo4 && debug) fprintf(file_Info_reportSummaryMap,"%d  %d (histo not present)\n",atoi(run),decision4);
      if(!histo4) continue;
      is_histo4 = true;

      if(dataset == 1) cname = "Info_Commissioning10_reportSummaryMap";
      if(dataset == 2) cname = "Info_Run2010A_reportSummaryMap";
      if(dataset == 3) cname = "Info_Run2010B_reportSummaryMap";

      if(dataset == 1) ctitle = "Info Commissioning10 reportSummaryMap";
      if(dataset == 2) ctitle = "Info Run2010A reportSummaryMap";
      if(dataset == 3) ctitle = "Info Run2010B reportSummaryMap";

      epsname = "DQMPlot/" + cname + ".pdf";
      cname+= "_" + run;
      ctitle+= " " + run;
	
      c[ican] = new TCanvas(cname.Data(),ctitle.Data());
      c[ican]->Divide(1,1);
	
      TPad* pad = (TPad*) c[ican]->cd(1);
      preDrawInfoTH2(pad,histo4);
      histo4->Draw();

      GetDecision_HVBeamStatus(histo4,list_LS_min,list_LS_max,atoi(run),decision4);
      fprintf(file_Info_reportSummaryMap,"%d  %d\n",atoi(run),decision4);
      
      fprintf(file_Info_reportSummaryMap_LS,"%d  %d  %d",atoi(run),decision4,int (list_LS_min.size()));
      for(int i = 0; i < list_LS_min.size(); i++) {
	fprintf(file_Info_reportSummaryMap_LS,"  %d  %d",list_LS_min.at(i),list_LS_max.at(i));
	if(i == list_LS_min.size() -1) fprintf(file_Info_reportSummaryMap_LS,"\n");
      }

      leg->Clear();
      entry = leg->AddEntry("",run.Data(),"");
      SetStyle(entry);
      leg->Draw("same");
      
      c[ican]->Update();
      
      if(ican == 0) c[ican]->Print(TString(TString(epsname)+TString("[")).Data());   // No actual print, just open file
      c[ican]->Print(epsname.Data());  // actually print canvas to file 
      if(ican == nbcan -1 -nhisto4_missing) c[ican]->Print(TString(TString(epsname)+TString("]")).Data()); // No actual print, just close file
      
      if(debug == 1) c[ican]->WaitPrimitive();
      if(debug == 0 && ican == nbcan -1 -nhisto4_missing) c[ican]->WaitPrimitive();

      ican++;
    }  //-- end loop over the DQM Info files

  }  //-- end loop over the DQM files

  if(choice == 1) fclose(file_Castor_reportSummaryMap);
  if(choice == 2) fclose(file_Castor_ChannelSummaryMap);
  if(choice == 3) fclose(file_Castor_AllDigiValues);
  if(choice == 4) fclose(file_Info_reportSummaryMap);
  if(choice == 4) fclose(file_Info_reportSummaryMap_LS);

  return(0);
}
