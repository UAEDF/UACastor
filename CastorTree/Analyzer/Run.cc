#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <stdio.h>
#include <cstring>

#include "MainAnalyzer.h"

int main(int argc, char *argv[]) {

  using namespace std;

  printf("argc = %d\n", argc);
  for (int i = 0; i<argc; i++){
    static int k = 0;
    printf("argv[%d] = %s\n", k, argv[k]);
    k++;
  }

  if(argc < 4) {
    cout<<"example usage: "<<"./Run \"type\" \"energy\" \"analysis\" "<<endl;
    cout<<"type: data - PYTHIA6Z2 - PYTHIA84C - HERWIGpp24"<<endl;
    cout<<"energy: 900 - 2760 - 7000"<<endl;
    cout<<"analysis: ana - eflow - eflowsubsample - geometry - shower - profile - calib - modulation - trigger - triggersubsample - threshold - signalcut - cuthadronlevel"<<endl;
    return(0);
  }

  TString type = TString(argv[1]);
  TString energy = TString(argv[2]);
  TString analysis = TString(argv[3]);

  bool ana = false;
  bool eflow = false;
  bool eflowsubsample = false;
  bool geometry = false;
  bool shower = false;
  bool profile = false;
  bool calib = false;
  bool modulation = false;
  bool trigger = false;
  bool triggersubsample = false;
  bool threshold = false;
  bool signalcut = false;
  bool cuthadronlevel = false;
  
  if(strcmp(analysis,"ana") == 0) ana = true;
  if(strcmp(analysis,"eflow") == 0) eflow = true;
  if(strcmp(analysis,"eflowsubsample") == 0) eflowsubsample = true;
  if(strcmp(analysis,"geometry") == 0) geometry = true;
  if(strcmp(analysis,"shower") == 0) shower = true;
  if(strcmp(analysis,"profile") == 0) profile = true;
  if(strcmp(analysis,"calib") == 0) calib = true;
  if(strcmp(analysis,"modulation") == 0) modulation = true;
  if(strcmp(analysis,"trigger") == 0) trigger = true;
  if(strcmp(analysis,"triggersubsample") == 0) triggersubsample = true;
  if(strcmp(analysis,"threshold") == 0) threshold = true;
  if(strcmp(analysis,"signalcut") == 0) signalcut = true;
  if(strcmp(analysis,"cuthadronlevel") == 0) cuthadronlevel = true;

  TString storagehome_hans = "dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/";
  TString storagehome_ben = "dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/roland/";
  TString dir_ben = "/user/roland/EflowAnalysis/CMSSW_4_2_7/src/UACastor/CastorTree/Result/";

  MainAnalyzer* m = new MainAnalyzer();
	
  if (strcmp(type,"data") == 0) {
    
    //-- 900 GeV data
    
    TString subdir_data_MB_900 = "MinimumBias/CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector_v7/73f71e7897ec23c1b2bf056fb952105f/";
    TString dir_data_MB_900 = storagehome_hans + subdir_data_MB_900;

    TString subdir_data_ZB_900 = "ZeroBias/CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_900GeV_RECOwithCorrector_v4/995e07837d460c2a00f3dfbda1d76e33/";
    TString dir_data_ZB_900 = storagehome_hans + subdir_data_ZB_900;

    TString dir_triggersubsample_900 = dir_ben + TString("TriggerSubsample/900GeV/");

    TString dir_eflowsubsample_data_900 = storagehome_ben + TString("EflowSubsample/900GeV/data/");

    if (strcmp(energy,"900") == 0) {
      
      cout<<"We'll process the 900 GeV data tree now"<<endl;	
      if(ana) m->makeHistos(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector_",true,900);
      if(profile) m->makeHistoProfile(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector",true,900);
      if(calib) m->makeHistoCalib(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector_",900);
      if(signalcut) m->makeHistoSignalCut(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector",true,900);
      if(eflow) m->makeHistoEflow(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector",type,900,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_data_900,"CastorTree_eflow_subsample",type,900,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_data_900,"CastorTree_eflow_subsample",type,900);
      if(geometry) m->makeHistoGeometry(dir_data_MB_900,"CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector",type,900);

      //-- ZeroBias data
      if(trigger) m->makeHistoTrigger(dir_data_ZB_900,"CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_900GeV_RECOwithCorrector",true,900,0);
      if(triggersubsample) m->makeHistoTrigger(dir_triggersubsample_900,"trigger.subsample.900GeV",true,900,1);
      if(threshold) m->makeHistoThreshold(dir_data_ZB_900,"CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_900GeV_RECOwithCorrector_",true,900);      
    }
    
    //-- data 2760 GeV
    
    TString subdir_data_AllPhysics_2760 = "AllPhysics2760/CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_v9/55561db7062b943bceb45be69d97b57a/";
    TString dir_data_AllPhysics_2760 = storagehome_hans + subdir_data_AllPhysics_2760;

    TString dir_triggersubsample_2760 = dir_ben + TString("TriggerSubsample/2760GeV/");

    TString dir_eflowsubsample_data_2760 = storagehome_ben + TString("EflowSubsample/2760GeV/data/");

    if (strcmp(energy,"2760") == 0) {
      
      cout<<"We'll process the 2760 GeV data tree now"<<endl;
      
      //-- allphysics tree (includes ZeroBias data)
      if(ana) m->makeHistos(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",true,2760);
      if(profile) m->makeHistoProfile(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",true,2760);
      if(calib) m->makeHistoCalib(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",2760);   
      if(signalcut) m->makeHistoSignalCut(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",true,2760);
      if(eflow) m->makeHistoEflow(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",type,2760,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_data_2760,"CastorTree_eflow_subsample",type,2760,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_data_2760,"CastorTree_eflow_subsample",type,2760);
      if(geometry) m->makeHistoGeometry(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",type,2760);

      if(trigger) m->makeHistoTrigger(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector",true,2760,0);
      if(triggersubsample) m->makeHistoTrigger(dir_triggersubsample_2760,"trigger.subsample.2760GeV",true,2760,1);
      if(threshold) m->makeHistoThreshold(dir_data_AllPhysics_2760,"CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_1",true,2760);
    }
    	
    //-- data 7000 GeV

    TString subdir_data_MB_7000 = "MinimumBias/CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_v6/311aeaa893378600647aa0fa9675a48e/";
    TString dir_data_MB_7000 = storagehome_hans + subdir_data_MB_7000;

    TString subdir_data_ZB_7000 = "ZeroBias/CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_v4/d5cc4c077bc0d1021fcb3b9f8cab4c07/";
    TString dir_data_ZB_7000 = storagehome_hans + subdir_data_ZB_7000;
   
    TString dir_triggersubsample_7000 = dir_ben + TString("TriggerSubsample/7TeV/");

    TString dir_eflowsubsample_data_7000 = storagehome_ben + TString("EflowSubsample/7TeV/data/");

    if (strcmp(energy,"7000") == 0) {
      
      cout<<"We'll process the 7 TeV data tree now"<<endl;

      //-- Minimum Bias data
      if(ana) m->makeHistos(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",true,7000);
      if(profile) m->makeHistoProfile(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",true,7000);
      if(calib) m->makeHistoCalib(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",7000);
      if(signalcut) m->makeHistoSignalCut(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_1",true,7000);
      if(eflow) m->makeHistoEflow(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",type,7000,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_data_7000,"CastorTree_eflow_subsample",type,7000,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_data_7000,"CastorTree_eflow_subsample",type,7000);
      if(geometry) m->makeHistoGeometry(dir_data_MB_7000,"CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",type,7000);

      //-- Zero Bias data
      if(trigger) m->makeHistoTrigger(dir_data_ZB_7000,"CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",true,7000,0);
      if(triggersubsample) m->makeHistoTrigger(dir_triggersubsample_7000,"trigger.subsample.7TeV",true,7000,1);
      if(threshold) m->makeHistoThreshold(dir_data_ZB_7000,"CastorTree_data_ZeroBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector",true,7000);
    }	
  }
	

  if (strcmp(type,"PYTHIA6Z2")==0) {

    //-- moca 900 GeV

    TString subdir_MC_900 = "MinBias_TuneZ2_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_Dec11_v2/CastorTree_MC_MinBias_TuneZ2_900GeV_pythia6_cff_py_Step3_START42_V11_Dec11_v3/ab9a53788d13cfa8c855cda83f795fbe/";
    TString dir_MC_900 = storagehome_hans + subdir_MC_900;

    TString dir_eflowsubsample_MC_900 = storagehome_ben + TString("EflowSubsample/900GeV/PYTHIA6Z2/");

    if (strcmp(energy,"900")==0) {
	
      cout<<"We'll process the 900 GeV MC tree now"<<endl;	
      if(ana) m->makeHistos(dir_MC_900,"CastorTree_MC_900GeV_42X",false,900);
      if(profile) m->makeHistoProfile(dir_MC_900,"CastorTree_MC_900GeV_42X",false,900);
      if(trigger) m->makeHistoTrigger(dir_MC_900,"CastorTree_MC_900GeV_42X",false,900,0);
      if(threshold) m->makeHistoThreshold(dir_MC_900,"CastorTree_MC_900GeV_42X",false,900);
      if(cuthadronlevel) m->makeHistoCutHadronLevel(dir_MC_900,"CastorTree_MC_900GeV_42X_1",900);

      if(eflow) m->makeHistoEflow(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_900,"CastorTree_eflow_subsample",type,900,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_MC_900,"CastorTree_eflow_subsample",type,900);
      if(geometry) m->makeHistoGeometry(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900);
      if(shower) m->makeHistoShower(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900);
    }
		
    
    //-- moca 2760 GeV

    TString subdir_MC_2760 = "MinBias_TuneZ2_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_Dec11_v2/CastorTree_MC_MinBias_TuneZ2_2760GeV_pythia6_cff_py_Step3_START42_V11_Dec11_v2/95b3059532ea3303b5c4c023bcc2a5dd/";
    TString dir_MC_2760 = storagehome_hans + subdir_MC_2760;

    TString dir_eflowsubsample_MC_2760 = storagehome_ben + TString("EflowSubsample/2760GeV/PYTHIA6Z2/");

    if (strcmp(energy,"2760")==0) {
	
      cout<<"We'll process the 2760 GeV MC tree now"<<endl;
      if(ana) m->makeHistos(dir_MC_2760,"CastorTree_MC_2760GeV_42X",false,2760);
      if(profile) m->makeHistoProfile(dir_MC_2760,"CastorTree_MC_2760GeV_42X",false,2760);
      if(trigger) m->makeHistoTrigger(dir_MC_2760,"CastorTree_MC_2760GeV_42X",false,2760,0);
      if(cuthadronlevel) m->makeHistoCutHadronLevel(dir_MC_2760,"CastorTree_MC_2760GeV_42X_",2760);

      if(eflow) m->makeHistoEflow(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_2760,"CastorTree_eflow_subsample",type,2760,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_MC_2760,"CastorTree_eflow_subsample",type,2760);
      if(geometry) m->makeHistoGeometry(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760);
      if(shower) m->makeHistoShower(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760);
    }
	
    //-- moca 7000 GeV
    
    TString subdir_MC_7000 = "MinBias_TuneZ2_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_Dec11_v2/CastorTree_MC_MinBias_TuneZ2_7TeV_pythia6_cff_py_Step3_START42_V11_Dec11_v3/3f4f40e814ef79ae1fb43e4fdf4c6377/";
    TString dir_MC_7000 = storagehome_hans + subdir_MC_7000;

    TString dir_eflowsubsample_MC_7000 = storagehome_ben + TString("EflowSubsample/7TeV/PYTHIA6Z2/");

    if (strcmp(energy,"7000")==0) {

      cout<<"We'll process the 7 TeV MC tree now"<<endl;

      if(ana) m->makeHistos(dir_MC_7000,"CastorTree_MC_7TeV_42X",false,7000);
      if(profile) m->makeHistoProfile(dir_MC_7000,"CastorTree_MC_7TeV_42X",false,7000);

      if(eflow) m->makeHistoEflow(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_7000,"CastorTree_eflow_subsample",type,7000,false);
      //-- if(geometry) m->makeHistoGeometry(dir_eflowsubsample_MC_7000,"CastorTree_eflow_subsample",type,7000);
      if(geometry) m->makeHistoGeometry(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000);
      if(shower) m->makeHistoShower(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000);
    
      //-- if(profile) m->makeHistoProfile("/user/hvanhaev/Analysis/Eflow/CMSSW_4_2_7/src/UACastor/CastorTree/python/goodcfg/","CastorTree_MC_7TeV_42X_Pythia6_D6T_onlyEM.root",false,7000);
      //-- if(profile) m->makeHistoProfile("/user/hvanhaev/Analysis/Eflow/CMSSW_4_2_7/src/UACastor/CastorTree/python/goodcfg/","CastorTree_MC_7TeV_42X_Pythia6_D6T_onlyHAD.root",false,7000);
      //-- if(profile) m->makeHistoProfile("/user/roland/EflowAnalysis/CMSSW_4_2_7/src/UACastor/CastorTree/MCTree/","CastorTree_MC_7TeV_42X_Pythia6_D6T_beamtilt.root",false,7000);

      if(modulation) m->makeHistoModulation(dir_MC_7000,"CastorTree_MC_7TeV_42X",7000);
      if(trigger) m->makeHistoTrigger(dir_MC_7000,"CastorTree_MC_7TeV_42X",false,7000,0);
      if(threshold) m->makeHistoThreshold(dir_MC_7000,"CastorTree_MC_7TeV_42X",false,7000);
      if(cuthadronlevel) m->makeHistoCutHadronLevel(dir_MC_7000,"CastorTree_MC_7TeV_42X_1",7000);
    }	
  }

  if (strcmp(type,"PYTHIA84C")==0) {

    //-- moca 900 GeV

    TString subdir_MC_900 = "MinBias_Tune4C_900GeV_pythia8_cff_py_GEN_SIM_START311_V2_Dec11_v2/CastorTree_MC_MinBias_Tune4C_900GeV_pythia8_cff_py_Step3_START42_V11_Dec11_v2/ab9a53788d13cfa8c855cda83f795fbe/";
    TString dir_MC_900 = storagehome_hans + subdir_MC_900;

    TString dir_eflowsubsample_MC_900 = storagehome_ben + TString("EflowSubsample/900GeV/PYTHIA84C/");

    if (strcmp(energy,"900")==0) {
      cout<<"We'll process the 900 GeV MC tree now"<<endl;	
      if(eflow) m->makeHistoEflow(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_900,"CastorTree_eflow_subsample",type,900,false);
       if(shower) m->makeHistoShower(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900);
    }
		
    //-- moca 2760 GeV

    TString subdir_MC_2760 = "MinBias_Tune4C_2760GeV_pythia8_cff_py_GEN_SIM_START311_V2_Dec11_v1/CastorTree_MC_MinBias_Tune4C_2760GeV_pythia8_cff_py_Step3_START42_V11_Dec11_v2/95b3059532ea3303b5c4c023bcc2a5dd/";
    TString dir_MC_2760 = storagehome_hans + subdir_MC_2760;

    TString dir_eflowsubsample_MC_2760 = storagehome_ben + TString("EflowSubsample/2760GeV/PYTHIA84C/");

    if (strcmp(energy,"2760")==0) {
      cout<<"We'll process the 2760 GeV MC tree now"<<endl;
      if(eflow) m->makeHistoEflow(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_2760,"CastorTree_eflow_subsample",type,2760,false);
      if(shower) m->makeHistoShower(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760);
    }
	
    //-- moca 7000 GeV
    
    TString subdir_MC_7000 = "MinBias_Tune4C_7TeV_pythia8_cff_py_GEN_SIM_START311_V2_Dec11_v1/CastorTree_MC_MinBias_Tune4C_7TeV_pythia8_cff_py_Step3_START42_V11_Dec11_v2/3f4f40e814ef79ae1fb43e4fdf4c6377/";
    TString dir_MC_7000 = storagehome_hans + subdir_MC_7000;

    TString dir_eflowsubsample_MC_7000 = storagehome_ben + TString("EflowSubsample/7TeV/PYTHIA84C/");
    
    if (strcmp(energy,"7000")==0) {
      cout<<"We'll process the 7 TeV MC tree now"<<endl;
      if(eflow) m->makeHistoEflow(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_7000,"CastorTree_eflow_subsample",type,7000,false);
      if(shower) m->makeHistoShower(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000);
    }	
  }

  if (strcmp(type,"HERWIGpp24")==0) {

    //-- moca 900 GeV

    TString subdir_MC_900 = "MinBias_900GeV_Herwig_cff_py_GEN_SIM_New/CastorTree_MC_MinBias_900GeV_Herwig_cff_py_Step3_START42_V11_Dec11_v3/ab9a53788d13cfa8c855cda83f795fbe/";	      
    TString dir_MC_900 = storagehome_hans + subdir_MC_900;

    TString dir_eflowsubsample_MC_900 = storagehome_ben + TString("EflowSubsample/900GeV/HERWIGpp24/");

    if (strcmp(energy,"900")==0) {
      cout<<"We'll process the 900 GeV MC tree now"<<endl;	
      if(eflow) m->makeHistoEflow(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_900,"CastorTree_eflow_subsample",type,900,false);
      if(shower) m->makeHistoShower(dir_MC_900,"CastorTree_MC_900GeV_42X",type,900);
    }
		
    //-- moca 2760 GeV

    TString subdir_MC_2760 = "MinBias_2760GeV_Herwig_cff_py_GEN_SIM_good/CastorTree_MC_MinBias_2760GeV_Herwig_cff_py_Step3_START42_V11_Dec11_v3/95b3059532ea3303b5c4c023bcc2a5dd/";					 
    TString dir_MC_2760 = storagehome_hans + subdir_MC_2760;

    TString dir_eflowsubsample_MC_2760 = storagehome_ben + TString("EflowSubsample/2760GeV/HERWIGpp24/");

    if (strcmp(energy,"2760")==0) {
      cout<<"We'll process the 2760 GeV MC tree now"<<endl;
      if(eflow) m->makeHistoEflow(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_2760,"CastorTree_eflow_subsample",type,2760,false);
      if(shower) m->makeHistoShower(dir_MC_2760,"CastorTree_MC_2760GeV_42X",type,2760);
    }
	
    //-- moca 7000 GeV
    
    TString subdir_MC_7000 = "MinBias_7TeV_Herwig_cff_py_GEN_SIM_New/CastorTree_MC_MinBias_7TeV_Herwig_cff_py_Step3_START42_V11_Dec11_v3/3f4f40e814ef79ae1fb43e4fdf4c6377/";					   
    TString dir_MC_7000 = storagehome_hans + subdir_MC_7000;

    TString dir_eflowsubsample_MC_7000 = storagehome_ben + TString("EflowSubsample/7TeV/HERWIGpp24/");

    if (strcmp(energy,"7000")==0) {
      cout<<"We'll process the 7 TeV MC tree now"<<endl;
      if(eflow) m->makeHistoEflow(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000,true);
      if(eflowsubsample) m->makeHistoEflow(dir_eflowsubsample_MC_7000,"CastorTree_eflow_subsample",type,7000,false);
      if(shower) m->makeHistoShower(dir_MC_7000,"CastorTree_MC_7TeV_42X",type,7000);
    }	
  }
	
  delete m;
  
  return(0);
}


