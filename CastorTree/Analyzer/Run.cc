#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <stdio.h>
#include <cstring>

#include "MainAnalyzer.h"

int main(int argc, char *argv[])
{
	
	//int i;
	//printf("argc = %d\n", argc);
	//for (i = 0; i<argc; i++) printf("argv[%d] = %s\n", i, argv[i]);
	
	std::cout << "Hello Benito !! " << std::endl;
	
	MainAnalyzer* m = new MainAnalyzer();
	
	if (strcmp(argv[1],"data") == 0) {
		if (strcmp(argv[2],"900") == 0) {
			// 900 GeV data
			std::cout << "We'll process the 900GeV data tree now" << std::endl;	
			m->makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/MinimumBias/CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector_v4/34791f187daa558f06237b658f1118e2/","CastorTree_data_MinBias_Commissioning10-07JunReReco_900GeV_RECOwithCorrector_",true,900);
		}
		
		if (strcmp(argv[2],"2760") == 0) {
			// 2.76 TeV data
			std::cout << "We'll process the 2760GeV data tree now" << std::endl;
			// L1 skim tree
			m->makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/AllPhysics2760/CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_L1Skim_v4/23e6ebe1276226ffd08ffaa4bfc0af65/","CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_9",true,2760);
			// allphysics tree
			//m->makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/AllPhysics2760/CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_v4/efe35410948a53c459b6a053694a1ebb/","CastorTree_data_AllPhysics2760_Run2011A-16Jul2011-v1_2760GeV_RECOwithCorrector_95_1_TFt.root",true,2760);
		}
		
		if (strcmp(argv[2],"7000") == 0) {
			// 7 TeV data
			std::cout << "We'll process the 7TeV data tree now" << std::endl;
			m->makeHistos("dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/MinimumBias/CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_v2/93a55823df2f97b4536fc20146386276/","CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector_9",true,7000);
		}	
	}
	
	if (strcmp(argv[1],"MC")==0) {
		if (strcmp(argv[2],"900")==0) {
			// 900 GeV data
			std::cout << "We'll process the 900GeV MC tree now" << std::endl;	
			m->makeHistos("../python/goodcfg/","CastorTree_MC_900GeV_42X_Pythia6_D6T.root",false,900);
		}
		
		if (strcmp(argv[2],"2760")==0) {
			// 2.76 TeV data
			std::cout << "We'll process the 2760GeV MC tree now" << std::endl;
			m->makeHistos("../python/goodcfg/","CastorTree_MC_2760GeV_42X_Pythia6_D6T.root",false,2760);
		}
		
		if (strcmp(argv[2],"7000")==0) {
			// 7 TeV data
			std::cout << "We'll process the 7TeV MC tree now" << std::endl;
			m->makeHistos("../python/goodcfg/","CastorTree_MC_7TeV_42X_Pythia6_D6T.root",false,7000);
		}	
	}
	
	delete m;
	
	return(0);
}

