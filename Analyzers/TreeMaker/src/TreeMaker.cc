// -*- C++ -*-
//
// Package:    TreeMaker
// Class:      TreeMaker
// 
/**\class TreeMaker TreeMaker.cc Analyzers/TreeMaker/src/TreeMaker.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  local user
//         Created:  Wed Mar  3 10:32:26 CET 2010
// $Id$
//
//


// system include files
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"


#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimG4CMS/Calo/interface/CaloHit.h"

#include "DataFormats/HcalRecHit/interface/CastorRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalCastorDetId.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/CastorDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/CastorGeometryRecord.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

// trigger includes
#include "FWCore/Framework/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"
#include "L1Trigger/L1ExtraFromDigis/interface/L1ExtraParticleMapProd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

// jet includes
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "HLTriggerOffline/SUSYBSM/interface/PtSorter.h"

#include "CalibFormats/CastorObjects/interface/CastorDbService.h"
#include "CalibFormats/CastorObjects/interface/CastorDbRecord.h"
#include "CalibFormats/CastorObjects/interface/CastorCalibrations.h"
#include "CondFormats/CastorObjects/interface/CastorQIECoder.h"


#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TNtuple.h"
#include <TRandom3.h>
#define debug 0

//
// class declaration
//

class TreeMaker : public edm::EDAnalyzer {
   public:
      explicit TreeMaker(const edm::ParameterSet&);
      ~TreeMaker();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      
        std::string fOutputFileName;
      	std::string CaloJetCorrectionService;
  	std::string PFJetCorrectionService;
      	edm::InputTag hlTriggerResults_;
      	edm::TriggerNames triggerNames_;
  	edm::InputTag m_l1ParticleMap_;
  	edm::InputTag particleMapSource_;
  	edm::InputTag caloJets_;
	edm::InputTag pfJets_;
  	edm::InputTag l1Trigger_;
	edm::InputTag castordigis_;
      
      	TTree* EventTree;
	TFile* fOutputFile;

	int eventNum;
	int lumiBlock;
	int runNumber;
	int bunchCrossing;
	
	int PhysicsDeclared;
	int L1bit0;
  	int L1bit36;
  	int L1bit37;
  	int L1bit38;
  	int L1bit39;
  	int L1bit40;
  	int L1bit41;

	int isCaloInclusive;
  	int isCaloDijet;
  	int nCaloJets;
  
  	int isPFInclusive;
  	int isPFDijet;
  	int nPFJets;

	double sumADC[224];     
	double ADC[224][6];
	double sumfC[224];     
	double fC[224][6];
	int module[224];
	int channel[224];
	int sector[224]; 
	double signal[224];
	double fCsignal[224];
	double pedestal[224]; 
	
	double CaloJetEnergy[4];
	double CaloJetPt[4];
	double CaloJetEta[4];
	double CaloJetPhi[4];   
	double PFJetEnergy[4];
	double PFJetPt[4];
	double PFJetEta[4];
	double PFJetPhi[4];
	
	double pedestal_124009[224];
	double pedestal_124020[224];
	double pedestal_124022[224];
	double pedestal_124023[224];
	double pedestal_124024[224];
	double pedestal_124027[224];
	double pedestal_124030[224];
	double pedestal_124120[224];
	double pedestal_MC[224];
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TreeMaker::TreeMaker(const edm::ParameterSet& iConfig):
fOutputFileName(iConfig.getParameter<std::string>("OutputFileName")),
CaloJetCorrectionService(iConfig.getParameter<std::string>("CaloJetCorrector")),
PFJetCorrectionService(iConfig.getParameter<std::string>("PFJetCorrector")),
hlTriggerResults_(iConfig.getParameter<edm::InputTag>("HLTriggerResults")),
caloJets_(iConfig.getParameter<edm::InputTag>("CaloJets")),
pfJets_(iConfig.getParameter<edm::InputTag>("PFJets")),
l1Trigger_(iConfig.getParameter<edm::InputTag>("L1Trigger")),
castordigis_(iConfig.getParameter<edm::InputTag>("CastorDigis"))

{
   //now do what ever initialization is needed
   
// init run 124009 pedestals   	
pedestal_124009[0] = 4.9315;
pedestal_124009[1] = 4.8316;
pedestal_124009[2] = 4.6518;
pedestal_124009[3] = 4.8010;
pedestal_124009[4] = 4.5158;
pedestal_124009[5] = 4.5824;
pedestal_124009[6] = 4.2603;
pedestal_124009[7] = 4.4092;
pedestal_124009[8] = 3.9796;
pedestal_124009[9] = 4.6018;
pedestal_124009[10] = 0.0000;
pedestal_124009[11] = 0.0000;
pedestal_124009[12] = 4.6417;
pedestal_124009[13] = 4.4500;
pedestal_124009[14] = 4.6774;
pedestal_124009[15] = 4.1499;
pedestal_124009[16] = 4.5805;
pedestal_124009[17] = 4.0380;
pedestal_124009[18] = 4.5933;
pedestal_124009[19] = 4.6087;
pedestal_124009[20] = 4.2202;
pedestal_124009[21] = 4.5926;
pedestal_124009[22] = 5.1108;
pedestal_124009[23] = 4.2476;
pedestal_124009[24] = 4.2166;
pedestal_124009[25] = 4.5933;
pedestal_124009[26] = 4.3826;
pedestal_124009[27] = 4.8657;
pedestal_124009[28] = 4.6937;
pedestal_124009[29] = 4.9460;
pedestal_124009[30] = 4.6678;
pedestal_124009[31] = 4.3123;
pedestal_124009[32] = 4.4375;
pedestal_124009[33] = 4.6576;
pedestal_124009[34] = 4.0984;
pedestal_124009[35] = 4.3076;
pedestal_124009[36] = 4.6646;
pedestal_124009[37] = 4.4912;
pedestal_124009[38] = 4.5737;
pedestal_124009[39] = 4.7507;
pedestal_124009[40] = 4.4056;
pedestal_124009[41] = 5.1287;
pedestal_124009[42] = 4.0776;
pedestal_124009[43] = 4.4569;
pedestal_124009[44] = 4.7381;
pedestal_124009[45] = 4.3789;
pedestal_124009[46] = 4.9051;
pedestal_124009[47] = 4.6048;
pedestal_124009[48] = 5.0457;
pedestal_124009[49] = 4.6545;
pedestal_124009[50] = 4.3825;
pedestal_124009[51] = 4.6235;
pedestal_124009[52] = 4.5287;
pedestal_124009[53] = 5.4599;
pedestal_124009[54] = 4.7605;
pedestal_124009[55] = 4.0938;
pedestal_124009[56] = 4.1317;
pedestal_124009[57] = 4.2013;
pedestal_124009[58] = 4.6981;
pedestal_124009[59] = 4.8915;
pedestal_124009[60] = 4.5258;
pedestal_124009[61] = 4.0839;
pedestal_124009[62] = 4.7176;
pedestal_124009[63] = 4.2526;
pedestal_124009[64] = 4.4191;
pedestal_124009[65] = 4.1896;
pedestal_124009[66] = 4.2982;
pedestal_124009[67] = 4.5049;
pedestal_124009[68] = 4.4206;
pedestal_124009[69] = 4.6096;
pedestal_124009[70] = 3.9382;
pedestal_124009[71] = 4.0218;
pedestal_124009[72] = 4.5289;
pedestal_124009[73] = 4.7354;
pedestal_124009[74] = 4.6508;
pedestal_124009[75] = 4.6665;
pedestal_124009[76] = 4.6320;
pedestal_124009[77] = 4.4279;
pedestal_124009[78] = 4.2984;
pedestal_124009[79] = 4.4017;
pedestal_124009[80] = 3.6134;
pedestal_124009[81] = 4.2743;
pedestal_124009[82] = 4.3191;
pedestal_124009[83] = 4.4295;
pedestal_124009[84] = 4.2402;
pedestal_124009[85] = 4.8869;
pedestal_124009[86] = 4.4575;
pedestal_124009[87] = 4.4846;
pedestal_124009[88] = 4.4793;
pedestal_124009[89] = 4.4239;
pedestal_124009[90] = 4.1509;
pedestal_124009[91] = 4.4298;
pedestal_124009[92] = 4.5140;
pedestal_124009[93] = 3.9498;
pedestal_124009[94] = 4.6502;
pedestal_124009[95] = 8.4728;
pedestal_124009[96] = 4.2853;
pedestal_124009[97] = 4.0426;
pedestal_124009[98] = 4.2998;
pedestal_124009[99] = 4.4637;
pedestal_124009[100] = 4.3601;
pedestal_124009[101] = 4.4774;
pedestal_124009[102] = 4.0750;
pedestal_124009[103] = 4.7143;
pedestal_124009[104] = 4.6796;
pedestal_124009[105] = 4.3409;
pedestal_124009[106] = 4.9886;
pedestal_124009[107] = 4.5197;
pedestal_124009[108] = 4.2884;
pedestal_124009[109] = 5.0177;
pedestal_124009[110] = 4.8592;
pedestal_124009[111] = 5.1629;
pedestal_124009[112] = 4.5857;
pedestal_124009[113] = 4.5494;
pedestal_124009[114] = 4.8464;
pedestal_124009[115] = 4.2002;
pedestal_124009[116] = 4.2803;
pedestal_124009[117] = 4.5082;
pedestal_124009[118] = 4.5135;
pedestal_124009[119] = 7.8888;
pedestal_124009[120] = 4.3060;
pedestal_124009[121] = 4.5450;
pedestal_124009[122] = 4.2123;
pedestal_124009[123] = 4.4403;
pedestal_124009[124] = 4.2785;
pedestal_124009[125] = 4.6375;
pedestal_124009[126] = 4.2899;
pedestal_124009[127] = 4.8257;
pedestal_124009[128] = 4.2894;
pedestal_124009[129] = 4.5865;
pedestal_124009[130] = 4.5749;
pedestal_124009[131] = 5.2224;
pedestal_124009[132] = 4.4840;
pedestal_124009[133] = 4.5599;
pedestal_124009[134] = 4.9663;
pedestal_124009[135] = 4.5670;
pedestal_124009[136] = 4.4966;
pedestal_124009[137] = 4.3491;
pedestal_124009[138] = 4.6441;
pedestal_124009[139] = 4.2750;
pedestal_124009[140] = 3.1107;
pedestal_124009[141] = 4.3729;
pedestal_124009[142] = 4.4447;
pedestal_124009[143] = 4.5874;
pedestal_124009[144] = 4.2747;
pedestal_124009[145] = 4.3777;
pedestal_124009[146] = 4.5518;
pedestal_124009[147] = 5.2174;
pedestal_124009[148] = 4.2474;
pedestal_124009[149] = 4.5515;
pedestal_124009[150] = 4.2744;
pedestal_124009[151] = 4.5807;
pedestal_124009[152] = 4.0360;
pedestal_124009[153] = 4.4106;
pedestal_124009[154] = 4.4394;
pedestal_124009[155] = 4.7448;
pedestal_124009[156] = 4.4451;
pedestal_124009[157] = 4.0526;
pedestal_124009[158] = 4.9375;
pedestal_124009[159] = 4.5095;
pedestal_124009[160] = 4.3487;
pedestal_124009[161] = 4.3276;
pedestal_124009[162] = 5.1675;
pedestal_124009[163] = 4.4591;
pedestal_124009[164] = 4.7149;
pedestal_124009[165] = 4.2348;
pedestal_124009[166] = 4.4189;
pedestal_124009[167] = 4.6634;
pedestal_124009[168] = 4.2155;
pedestal_124009[169] = 4.6809;
pedestal_124009[170] = 4.8076;
pedestal_124009[171] = 4.3678;
pedestal_124009[172] = 4.6872;
pedestal_124009[173] = 4.1070;
pedestal_124009[174] = 4.4417;
pedestal_124009[175] = 4.3194;
pedestal_124009[176] = 4.3492;
pedestal_124009[177] = 4.9030;
pedestal_124009[178] = 4.4486;
pedestal_124009[179] = 4.4185;
pedestal_124009[180] = 4.7715;
pedestal_124009[181] = 4.4245;
pedestal_124009[182] = 4.4115;
pedestal_124009[183] = 4.7559;
pedestal_124009[184] = 4.6576;
pedestal_124009[185] = 4.4753;
pedestal_124009[186] = 4.6347;
pedestal_124009[187] = 4.5191;
pedestal_124009[188] = 4.5609;
pedestal_124009[189] = 4.0802;
pedestal_124009[190] = 4.5588;
pedestal_124009[191] = 4.3844;
pedestal_124009[192] = 5.1913;
pedestal_124009[193] = 4.0935;
pedestal_124009[194] = 4.7193;
pedestal_124009[195] = 5.1773;
pedestal_124009[196] = 4.4273;
pedestal_124009[197] = 4.3158;
pedestal_124009[198] = 4.6074;
pedestal_124009[199] = 4.3240;
pedestal_124009[200] = 4.7945;
pedestal_124009[201] = 4.7703;
pedestal_124009[202] = 4.6662;
pedestal_124009[203] = 4.2414;
pedestal_124009[204] = 4.1464;
pedestal_124009[205] = 4.4377;
pedestal_124009[206] = 4.9585;
pedestal_124009[207] = 4.5004;
pedestal_124009[208] = 4.5831;
pedestal_124009[209] = 4.1342;
pedestal_124009[210] = 4.3030;
pedestal_124009[211] = 4.3187;
pedestal_124009[212] = 4.5529;
pedestal_124009[213] = 4.3414;
pedestal_124009[214] = 4.3200;
pedestal_124009[215] = 4.8364;
pedestal_124009[216] = 4.6864;
pedestal_124009[217] = 4.7250;
pedestal_124009[218] = 4.3671;
pedestal_124009[219] = 4.4104;
pedestal_124009[220] = 4.5563;
pedestal_124009[221] = 4.2060;
pedestal_124009[222] = 4.8437;
pedestal_124009[223] = 4.8498;


pedestal_124020[0] = 4.9216;
pedestal_124020[1] = 4.8408;
pedestal_124020[2] = 4.6604;
pedestal_124020[3] = 4.8100;
pedestal_124020[4] = 4.5133;
pedestal_124020[5] = 4.5989;
pedestal_124020[6] = 4.2450;
pedestal_124020[7] = 4.4140;
pedestal_124020[8] = 4.0104;
pedestal_124020[9] = 4.5988;
pedestal_124020[10] = 0.0000;
pedestal_124020[11] = 0.0000;
pedestal_124020[12] = 4.6243;
pedestal_124020[13] = 4.4517;
pedestal_124020[14] = 4.6808;
pedestal_124020[15] = 4.1425;
pedestal_124020[16] = 4.5720;
pedestal_124020[17] = 4.0268;
pedestal_124020[18] = 4.6114;
pedestal_124020[19] = 4.6160;
pedestal_124020[20] = 4.2116;
pedestal_124020[21] = 4.6007;
pedestal_124020[22] = 5.0780;
pedestal_124020[23] = 4.2454;
pedestal_124020[24] = 4.1986;
pedestal_124020[25] = 4.5826;
pedestal_124020[26] = 4.3946;
pedestal_124020[27] = 4.8439;
pedestal_124020[28] = 4.6704;
pedestal_124020[29] = 4.9529;
pedestal_124020[30] = 4.6467;
pedestal_124020[31] = 4.3034;
pedestal_124020[32] = 4.4476;
pedestal_124020[33] = 4.6390;
pedestal_124020[34] = 4.1060;
pedestal_124020[35] = 4.2901;
pedestal_124020[36] = 4.6658;
pedestal_124020[37] = 4.5069;
pedestal_124020[38] = 4.5825;
pedestal_124020[39] = 4.7453;
pedestal_124020[40] = 4.3972;
pedestal_124020[41] = 5.1555;
pedestal_124020[42] = 4.0628;
pedestal_124020[43] = 4.4524;
pedestal_124020[44] = 4.7182;
pedestal_124020[45] = 4.3719;
pedestal_124020[46] = 4.9229;
pedestal_124020[47] = 4.5986;
pedestal_124020[48] = 5.0505;
pedestal_124020[49] = 4.6523;
pedestal_124020[50] = 4.3904;
pedestal_124020[51] = 4.6257;
pedestal_124020[52] = 4.5053;
pedestal_124020[53] = 5.4502;
pedestal_124020[54] = 4.7515;
pedestal_124020[55] = 4.1256;
pedestal_124020[56] = 4.1530;
pedestal_124020[57] = 4.2044;
pedestal_124020[58] = 4.7077;
pedestal_124020[59] = 4.9060;
pedestal_124020[60] = 4.5405;
pedestal_124020[61] = 4.0771;
pedestal_124020[62] = 4.7216;
pedestal_124020[63] = 4.2459;
pedestal_124020[64] = 4.4161;
pedestal_124020[65] = 4.2057;
pedestal_124020[66] = 4.3057;
pedestal_124020[67] = 4.5219;
pedestal_124020[68] = 4.4245;
pedestal_124020[69] = 4.6216;
pedestal_124020[70] = 3.9167;
pedestal_124020[71] = 4.0164;
pedestal_124020[72] = 4.5104;
pedestal_124020[73] = 4.7215;
pedestal_124020[74] = 4.6695;
pedestal_124020[75] = 4.6971;
pedestal_124020[76] = 4.6382;
pedestal_124020[77] = 4.4375;
pedestal_124020[78] = 4.3027;
pedestal_124020[79] = 4.3995;
pedestal_124020[80] = 3.5933;
pedestal_124020[81] = 4.2796;
pedestal_124020[82] = 4.3214;
pedestal_124020[83] = 4.4431;
pedestal_124020[84] = 4.2255;
pedestal_124020[85] = 4.8927;
pedestal_124020[86] = 4.4528;
pedestal_124020[87] = 4.4775;
pedestal_124020[88] = 4.4838;
pedestal_124020[89] = 4.4255;
pedestal_124020[90] = 4.1455;
pedestal_124020[91] = 4.4212;
pedestal_124020[92] = 4.5263;
pedestal_124020[93] = 3.9388;
pedestal_124020[94] = 4.6558;
pedestal_124020[95] = 8.6943;
pedestal_124020[96] = 4.3047;
pedestal_124020[97] = 4.0295;
pedestal_124020[98] = 4.3154;
pedestal_124020[99] = 4.4633;
pedestal_124020[100] = 4.3436;
pedestal_124020[101] = 4.4842;
pedestal_124020[102] = 4.0699;
pedestal_124020[103] = 4.7172;
pedestal_124020[104] = 4.6894;
pedestal_124020[105] = 4.3419;
pedestal_124020[106] = 4.9684;
pedestal_124020[107] = 4.5447;
pedestal_124020[108] = 4.2926;
pedestal_124020[109] = 5.0148;
pedestal_124020[110] = 4.8606;
pedestal_124020[111] = 5.1704;
pedestal_124020[112] = 4.5952;
pedestal_124020[113] = 4.5640;
pedestal_124020[114] = 4.9538;
pedestal_124020[115] = 4.2004;
pedestal_124020[116] = 4.2713;
pedestal_124020[117] = 4.5059;
pedestal_124020[118] = 4.5159;
pedestal_124020[119] = 7.9151;
pedestal_124020[120] = 4.2963;
pedestal_124020[121] = 4.5593;
pedestal_124020[122] = 4.2025;
pedestal_124020[123] = 4.4343;
pedestal_124020[124] = 4.2894;
pedestal_124020[125] = 4.6438;
pedestal_124020[126] = 4.2974;
pedestal_124020[127] = 4.8244;
pedestal_124020[128] = 4.3088;
pedestal_124020[129] = 4.5659;
pedestal_124020[130] = 4.5806;
pedestal_124020[131] = 5.2308;
pedestal_124020[132] = 4.4812;
pedestal_124020[133] = 4.5677;
pedestal_124020[134] = 4.9581;
pedestal_124020[135] = 4.5752;
pedestal_124020[136] = 4.4788;
pedestal_124020[137] = 4.3533;
pedestal_124020[138] = 4.6619;
pedestal_124020[139] = 4.2937;
pedestal_124020[140] = 3.1094;
pedestal_124020[141] = 4.3648;
pedestal_124020[142] = 4.4247;
pedestal_124020[143] = 4.5839;
pedestal_124020[144] = 4.2790;
pedestal_124020[145] = 4.4110;
pedestal_124020[146] = 4.5599;
pedestal_124020[147] = 5.2185;
pedestal_124020[148] = 4.2385;
pedestal_124020[149] = 4.5850;
pedestal_124020[150] = 4.2704;
pedestal_124020[151] = 4.5914;
pedestal_124020[152] = 4.0114;
pedestal_124020[153] = 4.3967;
pedestal_124020[154] = 4.4477;
pedestal_124020[155] = 4.7538;
pedestal_124020[156] = 4.4554;
pedestal_124020[157] = 4.0487;
pedestal_124020[158] = 4.9413;
pedestal_124020[159] = 4.5395;
pedestal_124020[160] = 4.3477;
pedestal_124020[161] = 4.3516;
pedestal_124020[162] = 5.1719;
pedestal_124020[163] = 4.4593;
pedestal_124020[164] = 4.7301;
pedestal_124020[165] = 4.2409;
pedestal_124020[166] = 4.4248;
pedestal_124020[167] = 4.6629;
pedestal_124020[168] = 4.2161;
pedestal_124020[169] = 4.7147;
pedestal_124020[170] = 4.7969;
pedestal_124020[171] = 4.3653;
pedestal_124020[172] = 4.6739;
pedestal_124020[173] = 4.1087;
pedestal_124020[174] = 4.4539;
pedestal_124020[175] = 4.3148;
pedestal_124020[176] = 4.3469;
pedestal_124020[177] = 4.9177;
pedestal_124020[178] = 4.4187;
pedestal_124020[179] = 4.4136;
pedestal_124020[180] = 4.7804;
pedestal_124020[181] = 4.4376;
pedestal_124020[182] = 4.4060;
pedestal_124020[183] = 4.7274;
pedestal_124020[184] = 4.6631;
pedestal_124020[185] = 4.4753;
pedestal_124020[186] = 4.6210;
pedestal_124020[187] = 4.5399;
pedestal_124020[188] = 4.5566;
pedestal_124020[189] = 4.0710;
pedestal_124020[190] = 4.5574;
pedestal_124020[191] = 4.3850;
pedestal_124020[192] = 5.1810;
pedestal_124020[193] = 4.1147;
pedestal_124020[194] = 4.7235;
pedestal_124020[195] = 5.1949;
pedestal_124020[196] = 4.4288;
pedestal_124020[197] = 4.3117;
pedestal_124020[198] = 4.6162;
pedestal_124020[199] = 4.3408;
pedestal_124020[200] = 4.7910;
pedestal_124020[201] = 4.7540;
pedestal_124020[202] = 4.6564;
pedestal_124020[203] = 4.2263;
pedestal_124020[204] = 4.1663;
pedestal_124020[205] = 4.4553;
pedestal_124020[206] = 4.9586;
pedestal_124020[207] = 4.4919;
pedestal_124020[208] = 4.5568;
pedestal_124020[209] = 4.1446;
pedestal_124020[210] = 4.2826;
pedestal_124020[211] = 4.3435;
pedestal_124020[212] = 4.5581;
pedestal_124020[213] = 4.3326;
pedestal_124020[214] = 4.3009;
pedestal_124020[215] = 4.8238;
pedestal_124020[216] = 4.7057;
pedestal_124020[217] = 4.7111;
pedestal_124020[218] = 4.3589;
pedestal_124020[219] = 4.4054;
pedestal_124020[220] = 4.5736;
pedestal_124020[221] = 4.2137;
pedestal_124020[222] = 4.8408;
pedestal_124020[223] = 4.8437;


pedestal_124022[0] = 4.9244;
pedestal_124022[1] = 4.8372;
pedestal_124022[2] = 4.6589;
pedestal_124022[3] = 4.8117;
pedestal_124022[4] = 4.4991;
pedestal_124022[5] = 4.5960;
pedestal_124022[6] = 4.2672;
pedestal_124022[7] = 4.4229;
pedestal_124022[8] = 4.0134;
pedestal_124022[9] = 4.5680;
pedestal_124022[10] = 0.0000;
pedestal_124022[11] = 0.0000;
pedestal_124022[12] = 4.6106;
pedestal_124022[13] = 4.4700;
pedestal_124022[14] = 4.6762;
pedestal_124022[15] = 4.1508;
pedestal_124022[16] = 4.5130;
pedestal_124022[17] = 4.0229;
pedestal_124022[18] = 4.5833;
pedestal_124022[19] = 4.6123;
pedestal_124022[20] = 4.1791;
pedestal_124022[21] = 4.5825;
pedestal_124022[22] = 5.0672;
pedestal_124022[23] = 4.2584;
pedestal_124022[24] = 4.2034;
pedestal_124022[25] = 4.5817;
pedestal_124022[26] = 4.3668;
pedestal_124022[27] = 4.8489;
pedestal_124022[28] = 4.7073;
pedestal_124022[29] = 4.9289;
pedestal_124022[30] = 4.6907;
pedestal_124022[31] = 4.2918;
pedestal_124022[32] = 4.4027;
pedestal_124022[33] = 4.6611;
pedestal_124022[34] = 4.0984;
pedestal_124022[35] = 4.3386;
pedestal_124022[36] = 4.6560;
pedestal_124022[37] = 4.4876;
pedestal_124022[38] = 4.5601;
pedestal_124022[39] = 4.7181;
pedestal_124022[40] = 4.3765;
pedestal_124022[41] = 5.1029;
pedestal_124022[42] = 4.0547;
pedestal_124022[43] = 4.3963;
pedestal_124022[44] = 4.7257;
pedestal_124022[45] = 4.3726;
pedestal_124022[46] = 4.8927;
pedestal_124022[47] = 4.5933;
pedestal_124022[48] = 5.1008;
pedestal_124022[49] = 4.6469;
pedestal_124022[50] = 4.3816;
pedestal_124022[51] = 4.6234;
pedestal_124022[52] = 4.5174;
pedestal_124022[53] = 5.4533;
pedestal_124022[54] = 4.7577;
pedestal_124022[55] = 4.0691;
pedestal_124022[56] = 4.1388;
pedestal_124022[57] = 4.1735;
pedestal_124022[58] = 4.6818;
pedestal_124022[59] = 4.8796;
pedestal_124022[60] = 4.5011;
pedestal_124022[61] = 4.1195;
pedestal_124022[62] = 4.7008;
pedestal_124022[63] = 4.2041;
pedestal_124022[64] = 4.4006;
pedestal_124022[65] = 4.1957;
pedestal_124022[66] = 4.3368;
pedestal_124022[67] = 4.4597;
pedestal_124022[68] = 4.3601;
pedestal_124022[69] = 4.6182;
pedestal_124022[70] = 3.9480;
pedestal_124022[71] = 4.0261;
pedestal_124022[72] = 4.5000;
pedestal_124022[73] = 4.7142;
pedestal_124022[74] = 4.6395;
pedestal_124022[75] = 4.6715;
pedestal_124022[76] = 4.6424;
pedestal_124022[77] = 4.3937;
pedestal_124022[78] = 4.2897;
pedestal_124022[79] = 4.4666;
pedestal_124022[80] = 3.5900;
pedestal_124022[81] = 4.2738;
pedestal_124022[82] = 4.3070;
pedestal_124022[83] = 4.4142;
pedestal_124022[84] = 4.2489;
pedestal_124022[85] = 4.8934;
pedestal_124022[86] = 4.4387;
pedestal_124022[87] = 4.4731;
pedestal_124022[88] = 4.4696;
pedestal_124022[89] = 4.4258;
pedestal_124022[90] = 4.1726;
pedestal_124022[91] = 4.4149;
pedestal_124022[92] = 4.5211;
pedestal_124022[93] = 3.9482;
pedestal_124022[94] = 4.6491;
pedestal_124022[95] = 8.7256;
pedestal_124022[96] = 4.2705;
pedestal_124022[97] = 4.0238;
pedestal_124022[98] = 4.2862;
pedestal_124022[99] = 4.4655;
pedestal_124022[100] = 4.3145;
pedestal_124022[101] = 4.4647;
pedestal_124022[102] = 4.0545;
pedestal_124022[103] = 4.6863;
pedestal_124022[104] = 4.6280;
pedestal_124022[105] = 4.3348;
pedestal_124022[106] = 4.9593;
pedestal_124022[107] = 4.4795;
pedestal_124022[108] = 4.2845;
pedestal_124022[109] = 5.0103;
pedestal_124022[110] = 4.8665;
pedestal_124022[111] = 5.1891;
pedestal_124022[112] = 4.5454;
pedestal_124022[113] = 4.5086;
pedestal_124022[114] = 4.9166;
pedestal_124022[115] = 4.1703;
pedestal_124022[116] = 4.2878;
pedestal_124022[117] = 4.5287;
pedestal_124022[118] = 4.4956;
pedestal_124022[119] = 7.9130;
pedestal_124022[120] = 4.3112;
pedestal_124022[121] = 4.5097;
pedestal_124022[122] = 4.2072;
pedestal_124022[123] = 4.4129;
pedestal_124022[124] = 4.2419;
pedestal_124022[125] = 4.6777;
pedestal_124022[126] = 4.2930;
pedestal_124022[127] = 4.8064;
pedestal_124022[128] = 4.2443;
pedestal_124022[129] = 4.5945;
pedestal_124022[130] = 4.5678;
pedestal_124022[131] = 5.1810;
pedestal_124022[132] = 4.4425;
pedestal_124022[133] = 4.5244;
pedestal_124022[134] = 4.9345;
pedestal_124022[135] = 4.5831;
pedestal_124022[136] = 4.4776;
pedestal_124022[137] = 4.3469;
pedestal_124022[138] = 4.6370;
pedestal_124022[139] = 4.2567;
pedestal_124022[140] = 3.1038;
pedestal_124022[141] = 4.3590;
pedestal_124022[142] = 4.4303;
pedestal_124022[143] = 4.6022;
pedestal_124022[144] = 4.2891;
pedestal_124022[145] = 4.3618;
pedestal_124022[146] = 4.5432;
pedestal_124022[147] = 5.2356;
pedestal_124022[148] = 4.2187;
pedestal_124022[149] = 4.4452;
pedestal_124022[150] = 4.2855;
pedestal_124022[151] = 4.5852;
pedestal_124022[152] = 3.9963;
pedestal_124022[153] = 4.3700;
pedestal_124022[154] = 4.4611;
pedestal_124022[155] = 4.7550;
pedestal_124022[156] = 4.4431;
pedestal_124022[157] = 4.0623;
pedestal_124022[158] = 4.9447;
pedestal_124022[159] = 4.5357;
pedestal_124022[160] = 4.3455;
pedestal_124022[161] = 4.3275;
pedestal_124022[162] = 5.1593;
pedestal_124022[163] = 4.4409;
pedestal_124022[164] = 4.7459;
pedestal_124022[165] = 4.2082;
pedestal_124022[166] = 4.4500;
pedestal_124022[167] = 4.6706;
pedestal_124022[168] = 4.2110;
pedestal_124022[169] = 4.6736;
pedestal_124022[170] = 4.7975;
pedestal_124022[171] = 4.3616;
pedestal_124022[172] = 4.6747;
pedestal_124022[173] = 4.0953;
pedestal_124022[174] = 4.4431;
pedestal_124022[175] = 4.3009;
pedestal_124022[176] = 4.3505;
pedestal_124022[177] = 4.9115;
pedestal_124022[178] = 4.5003;
pedestal_124022[179] = 4.4096;
pedestal_124022[180] = 4.7803;
pedestal_124022[181] = 4.4000;
pedestal_124022[182] = 4.3524;
pedestal_124022[183] = 4.7631;
pedestal_124022[184] = 4.6496;
pedestal_124022[185] = 4.4379;
pedestal_124022[186] = 4.6258;
pedestal_124022[187] = 4.5439;
pedestal_124022[188] = 4.5263;
pedestal_124022[189] = 4.0996;
pedestal_124022[190] = 4.5542;
pedestal_124022[191] = 4.3618;
pedestal_124022[192] = 5.1852;
pedestal_124022[193] = 4.1084;
pedestal_124022[194] = 4.7351;
pedestal_124022[195] = 5.1526;
pedestal_124022[196] = 4.4185;
pedestal_124022[197] = 4.2861;
pedestal_124022[198] = 4.5997;
pedestal_124022[199] = 4.3336;
pedestal_124022[200] = 4.7345;
pedestal_124022[201] = 4.7722;
pedestal_124022[202] = 4.6578;
pedestal_124022[203] = 4.1867;
pedestal_124022[204] = 4.1830;
pedestal_124022[205] = 4.4792;
pedestal_124022[206] = 4.9279;
pedestal_124022[207] = 4.4681;
pedestal_124022[208] = 4.5990;
pedestal_124022[209] = 4.1507;
pedestal_124022[210] = 4.2914;
pedestal_124022[211] = 4.3139;
pedestal_124022[212] = 4.5637;
pedestal_124022[213] = 4.3531;
pedestal_124022[214] = 4.3085;
pedestal_124022[215] = 4.8385;
pedestal_124022[216] = 4.6527;
pedestal_124022[217] = 4.7117;
pedestal_124022[218] = 4.3833;
pedestal_124022[219] = 4.4148;
pedestal_124022[220] = 4.5481;
pedestal_124022[221] = 4.1728;
pedestal_124022[222] = 4.8384;
pedestal_124022[223] = 4.8423;


pedestal_124023[0] = 4.9238;
pedestal_124023[1] = 4.8565;
pedestal_124023[2] = 4.6002;
pedestal_124023[3] = 4.8107;
pedestal_124023[4] = 4.4485;
pedestal_124023[5] = 4.6018;
pedestal_124023[6] = 4.2651;
pedestal_124023[7] = 4.4188;
pedestal_124023[8] = 4.0087;
pedestal_124023[9] = 4.5690;
pedestal_124023[10] = 0.0000;
pedestal_124023[11] = 0.0000;
pedestal_124023[12] = 4.7084;
pedestal_124023[13] = 4.4803;
pedestal_124023[14] = 4.7534;
pedestal_124023[15] = 4.1658;
pedestal_124023[16] = 4.5232;
pedestal_124023[17] = 4.0308;
pedestal_124023[18] = 4.4767;
pedestal_124023[19] = 4.6167;
pedestal_124023[20] = 4.2159;
pedestal_124023[21] = 4.5964;
pedestal_124023[22] = 5.0583;
pedestal_124023[23] = 4.2473;
pedestal_124023[24] = 4.2039;
pedestal_124023[25] = 4.5693;
pedestal_124023[26] = 4.3795;
pedestal_124023[27] = 4.8472;
pedestal_124023[28] = 4.7834;
pedestal_124023[29] = 4.9072;
pedestal_124023[30] = 4.8579;
pedestal_124023[31] = 4.3936;
pedestal_124023[32] = 4.4146;
pedestal_124023[33] = 4.6664;
pedestal_124023[34] = 4.0876;
pedestal_124023[35] = 4.5362;
pedestal_124023[36] = 4.6983;
pedestal_124023[37] = 4.4822;
pedestal_124023[38] = 4.5559;
pedestal_124023[39] = 4.7235;
pedestal_124023[40] = 4.3765;
pedestal_124023[41] = 5.1103;
pedestal_124023[42] = 4.0732;
pedestal_124023[43] = 4.4067;
pedestal_124023[44] = 4.6993;
pedestal_124023[45] = 4.3740;
pedestal_124023[46] = 4.9440;
pedestal_124023[47] = 4.5329;
pedestal_124023[48] = 5.0930;
pedestal_124023[49] = 4.5857;
pedestal_124023[50] = 4.4854;
pedestal_124023[51] = 4.6409;
pedestal_124023[52] = 4.5185;
pedestal_124023[53] = 5.4436;
pedestal_124023[54] = 4.7470;
pedestal_124023[55] = 4.0775;
pedestal_124023[56] = 4.1399;
pedestal_124023[57] = 4.1754;
pedestal_124023[58] = 4.5019;
pedestal_124023[59] = 4.8139;
pedestal_124023[60] = 4.5137;
pedestal_124023[61] = 4.2933;
pedestal_124023[62] = 4.7014;
pedestal_124023[63] = 4.0323;
pedestal_124023[64] = 4.4052;
pedestal_124023[65] = 4.1569;
pedestal_124023[66] = 4.4127;
pedestal_124023[67] = 4.4748;
pedestal_124023[68] = 4.3726;
pedestal_124023[69] = 4.6194;
pedestal_124023[70] = 3.9487;
pedestal_124023[71] = 4.0321;
pedestal_124023[72] = 4.5051;
pedestal_124023[73] = 4.7234;
pedestal_124023[74] = 4.7197;
pedestal_124023[75] = 4.7372;
pedestal_124023[76] = 4.7083;
pedestal_124023[77] = 4.3996;
pedestal_124023[78] = 4.2927;
pedestal_124023[79] = 4.6287;
pedestal_124023[80] = 3.5904;
pedestal_124023[81] = 4.2781;
pedestal_124023[82] = 4.3209;
pedestal_124023[83] = 4.4171;
pedestal_124023[84] = 4.2454;
pedestal_124023[85] = 4.8751;
pedestal_124023[86] = 4.4323;
pedestal_124023[87] = 4.4669;
pedestal_124023[88] = 4.4644;
pedestal_124023[89] = 4.4528;
pedestal_124023[90] = 4.1551;
pedestal_124023[91] = 4.4191;
pedestal_124023[92] = 4.5189;
pedestal_124023[93] = 4.0665;
pedestal_124023[94] = 4.6627;
pedestal_124023[95] = 8.6137;
pedestal_124023[96] = 4.2435;
pedestal_124023[97] = 4.0560;
pedestal_124023[98] = 4.2300;
pedestal_124023[99] = 4.5743;
pedestal_124023[100] = 4.2431;
pedestal_124023[101] = 4.3678;
pedestal_124023[102] = 4.0681;
pedestal_124023[103] = 4.6284;
pedestal_124023[104] = 4.6360;
pedestal_124023[105] = 4.3619;
pedestal_124023[106] = 4.9655;
pedestal_124023[107] = 4.4068;
pedestal_124023[108] = 4.3873;
pedestal_124023[109] = 4.9964;
pedestal_124023[110] = 5.0356;
pedestal_124023[111] = 5.3155;
pedestal_124023[112] = 4.5317;
pedestal_124023[113] = 4.3909;
pedestal_124023[114] = 4.8689;
pedestal_124023[115] = 4.1057;
pedestal_124023[116] = 4.2761;
pedestal_124023[117] = 4.5046;
pedestal_124023[118] = 4.5009;
pedestal_124023[119] = 7.7906;
pedestal_124023[120] = 4.3063;
pedestal_124023[121] = 4.3718;
pedestal_124023[122] = 4.2092;
pedestal_124023[123] = 4.4081;
pedestal_124023[124] = 4.2425;
pedestal_124023[125] = 4.6786;
pedestal_124023[126] = 4.3013;
pedestal_124023[127] = 4.7874;
pedestal_124023[128] = 4.2409;
pedestal_124023[129] = 4.6483;
pedestal_124023[130] = 4.5831;
pedestal_124023[131] = 5.0474;
pedestal_124023[132] = 4.3792;
pedestal_124023[133] = 4.4896;
pedestal_124023[134] = 4.9377;
pedestal_124023[135] = 4.6167;
pedestal_124023[136] = 4.4792;
pedestal_124023[137] = 4.3481;
pedestal_124023[138] = 4.6424;
pedestal_124023[139] = 4.2212;
pedestal_124023[140] = 3.0666;
pedestal_124023[141] = 4.3637;
pedestal_124023[142] = 4.4676;
pedestal_124023[143] = 4.5417;
pedestal_124023[144] = 4.2647;
pedestal_124023[145] = 4.3708;
pedestal_124023[146] = 4.5892;
pedestal_124023[147] = 5.2416;
pedestal_124023[148] = 4.2150;
pedestal_124023[149] = 4.2800;
pedestal_124023[150] = 4.2783;
pedestal_124023[151] = 4.6315;
pedestal_124023[152] = 4.0317;
pedestal_124023[153] = 4.2544;
pedestal_124023[154] = 4.4559;
pedestal_124023[155] = 4.8108;
pedestal_124023[156] = 4.4542;
pedestal_124023[157] = 4.0696;
pedestal_124023[158] = 4.9434;
pedestal_124023[159] = 4.6141;
pedestal_124023[160] = 4.4594;
pedestal_124023[161] = 4.2711;
pedestal_124023[162] = 5.1565;
pedestal_124023[163] = 4.3720;
pedestal_124023[164] = 4.7406;
pedestal_124023[165] = 4.1179;
pedestal_124023[166] = 4.4443;
pedestal_124023[167] = 4.6013;
pedestal_124023[168] = 4.2276;
pedestal_124023[169] = 4.4962;
pedestal_124023[170] = 4.7859;
pedestal_124023[171] = 4.3898;
pedestal_124023[172] = 4.6918;
pedestal_124023[173] = 4.0673;
pedestal_124023[174] = 4.4342;
pedestal_124023[175] = 4.3728;
pedestal_124023[176] = 4.3111;
pedestal_124023[177] = 4.9042;
pedestal_124023[178] = 4.8866;
pedestal_124023[179] = 4.3574;
pedestal_124023[180] = 4.7778;
pedestal_124023[181] = 4.4189;
pedestal_124023[182] = 4.3708;
pedestal_124023[183] = 4.7252;
pedestal_124023[184] = 4.7390;
pedestal_124023[185] = 4.5178;
pedestal_124023[186] = 4.6441;
pedestal_124023[187] = 4.6484;
pedestal_124023[188] = 4.4307;
pedestal_124023[189] = 4.2952;
pedestal_124023[190] = 4.5555;
pedestal_124023[191] = 4.3468;
pedestal_124023[192] = 5.2022;
pedestal_124023[193] = 4.1514;
pedestal_124023[194] = 4.8143;
pedestal_124023[195] = 5.0969;
pedestal_124023[196] = 4.4207;
pedestal_124023[197] = 4.2947;
pedestal_124023[198] = 4.6126;
pedestal_124023[199] = 4.4526;
pedestal_124023[200] = 4.4838;
pedestal_124023[201] = 4.8552;
pedestal_124023[202] = 4.6003;
pedestal_124023[203] = 4.0878;
pedestal_124023[204] = 4.2929;
pedestal_124023[205] = 4.5688;
pedestal_124023[206] = 4.9296;
pedestal_124023[207] = 4.3143;
pedestal_124023[208] = 4.7138;
pedestal_124023[209] = 4.2119;
pedestal_124023[210] = 4.3909;
pedestal_124023[211] = 4.2470;
pedestal_124023[212] = 4.5032;
pedestal_124023[213] = 4.3173;
pedestal_124023[214] = 4.3487;
pedestal_124023[215] = 4.8422;
pedestal_124023[216] = 4.5813;
pedestal_124023[217] = 4.8513;
pedestal_124023[218] = 4.3661;
pedestal_124023[219] = 4.3805;
pedestal_124023[220] = 4.5593;
pedestal_124023[221] = 4.1622;
pedestal_124023[222] = 4.8473;
pedestal_124023[223] = 4.8566;


pedestal_124024[0] = 4.9197;
pedestal_124024[1] = 4.8498;
pedestal_124024[2] = 4.6139;
pedestal_124024[3] = 4.8005;
pedestal_124024[4] = 4.4525;
pedestal_124024[5] = 4.6054;
pedestal_124024[6] = 4.2687;
pedestal_124024[7] = 4.4271;
pedestal_124024[8] = 4.0085;
pedestal_124024[9] = 4.5870;
pedestal_124024[10] = 0.0000;
pedestal_124024[11] = 0.0000;
pedestal_124024[12] = 4.6991;
pedestal_124024[13] = 4.4806;
pedestal_124024[14] = 4.7516;
pedestal_124024[15] = 4.1746;
pedestal_124024[16] = 4.5379;
pedestal_124024[17] = 4.0401;
pedestal_124024[18] = 4.4852;
pedestal_124024[19] = 4.6198;
pedestal_124024[20] = 4.2222;
pedestal_124024[21] = 4.5950;
pedestal_124024[22] = 5.0654;
pedestal_124024[23] = 4.2420;
pedestal_124024[24] = 4.2118;
pedestal_124024[25] = 4.5835;
pedestal_124024[26] = 4.3705;
pedestal_124024[27] = 4.8443;
pedestal_124024[28] = 4.7924;
pedestal_124024[29] = 4.8965;
pedestal_124024[30] = 4.8406;
pedestal_124024[31] = 4.3877;
pedestal_124024[32] = 4.4203;
pedestal_124024[33] = 4.6634;
pedestal_124024[34] = 4.0804;
pedestal_124024[35] = 4.5285;
pedestal_124024[36] = 4.6890;
pedestal_124024[37] = 4.4867;
pedestal_124024[38] = 4.5751;
pedestal_124024[39] = 4.7377;
pedestal_124024[40] = 4.3875;
pedestal_124024[41] = 5.1183;
pedestal_124024[42] = 4.0542;
pedestal_124024[43] = 4.4154;
pedestal_124024[44] = 4.7187;
pedestal_124024[45] = 4.3659;
pedestal_124024[46] = 4.9336;
pedestal_124024[47] = 4.5316;
pedestal_124024[48] = 5.0844;
pedestal_124024[49] = 4.5755;
pedestal_124024[50] = 4.4774;
pedestal_124024[51] = 4.6277;
pedestal_124024[52] = 4.5145;
pedestal_124024[53] = 5.4551;
pedestal_124024[54] = 4.7540;
pedestal_124024[55] = 4.0922;
pedestal_124024[56] = 4.1297;
pedestal_124024[57] = 4.1743;
pedestal_124024[58] = 4.5062;
pedestal_124024[59] = 4.8096;
pedestal_124024[60] = 4.4989;
pedestal_124024[61] = 4.2937;
pedestal_124024[62] = 4.7026;
pedestal_124024[63] = 4.0428;
pedestal_124024[64] = 4.4126;
pedestal_124024[65] = 4.1602;
pedestal_124024[66] = 4.4065;
pedestal_124024[67] = 4.4806;
pedestal_124024[68] = 4.3722;
pedestal_124024[69] = 4.6199;
pedestal_124024[70] = 3.9370;
pedestal_124024[71] = 4.0263;
pedestal_124024[72] = 4.5133;
pedestal_124024[73] = 4.7252;
pedestal_124024[74] = 4.7151;
pedestal_124024[75] = 4.7386;
pedestal_124024[76] = 4.6979;
pedestal_124024[77] = 4.3963;
pedestal_124024[78] = 4.2916;
pedestal_124024[79] = 4.6375;
pedestal_124024[80] = 3.5874;
pedestal_124024[81] = 4.2795;
pedestal_124024[82] = 4.3094;
pedestal_124024[83] = 4.4195;
pedestal_124024[84] = 4.2399;
pedestal_124024[85] = 4.8799;
pedestal_124024[86] = 4.4383;
pedestal_124024[87] = 4.4756;
pedestal_124024[88] = 4.4795;
pedestal_124024[89] = 4.4531;
pedestal_124024[90] = 4.1602;
pedestal_124024[91] = 4.4216;
pedestal_124024[92] = 4.5119;
pedestal_124024[93] = 4.0481;
pedestal_124024[94] = 4.6605;
pedestal_124024[95] = 8.7168;
pedestal_124024[96] = 4.2234;
pedestal_124024[97] = 4.0436;
pedestal_124024[98] = 4.2303;
pedestal_124024[99] = 4.5777;
pedestal_124024[100] = 4.2540;
pedestal_124024[101] = 4.3663;
pedestal_124024[102] = 4.0685;
pedestal_124024[103] = 4.6259;
pedestal_124024[104] = 4.6457;
pedestal_124024[105] = 4.3639;
pedestal_124024[106] = 4.9701;
pedestal_124024[107] = 4.4047;
pedestal_124024[108] = 4.3855;
pedestal_124024[109] = 4.9991;
pedestal_124024[110] = 5.0300;
pedestal_124024[111] = 5.3003;
pedestal_124024[112] = 4.5372;
pedestal_124024[113] = 4.4077;
pedestal_124024[114] = 4.8866;
pedestal_124024[115] = 4.1127;
pedestal_124024[116] = 4.2911;
pedestal_124024[117] = 4.4932;
pedestal_124024[118] = 4.5035;
pedestal_124024[119] = 7.8446;
pedestal_124024[120] = 4.3093;
pedestal_124024[121] = 4.3693;
pedestal_124024[122] = 4.2034;
pedestal_124024[123] = 4.4135;
pedestal_124024[124] = 4.2279;
pedestal_124024[125] = 4.6680;
pedestal_124024[126] = 4.2994;
pedestal_124024[127] = 4.7804;
pedestal_124024[128] = 4.2421;
pedestal_124024[129] = 4.6440;
pedestal_124024[130] = 4.5831;
pedestal_124024[131] = 5.0496;
pedestal_124024[132] = 4.3709;
pedestal_124024[133] = 4.4928;
pedestal_124024[134] = 4.9355;
pedestal_124024[135] = 4.6056;
pedestal_124024[136] = 4.4852;
pedestal_124024[137] = 4.3423;
pedestal_124024[138] = 4.6418;
pedestal_124024[139] = 4.2124;
pedestal_124024[140] = 3.0804;
pedestal_124024[141] = 4.3722;
pedestal_124024[142] = 4.4668;
pedestal_124024[143] = 4.5516;
pedestal_124024[144] = 4.2611;
pedestal_124024[145] = 4.3626;
pedestal_124024[146] = 4.5857;
pedestal_124024[147] = 5.2294;
pedestal_124024[148] = 4.2255;
pedestal_124024[149] = 4.2777;
pedestal_124024[150] = 4.2784;
pedestal_124024[151] = 4.6274;
pedestal_124024[152] = 4.0377;
pedestal_124024[153] = 4.2591;
pedestal_124024[154] = 4.4549;
pedestal_124024[155] = 4.8178;
pedestal_124024[156] = 4.4561;
pedestal_124024[157] = 4.0602;
pedestal_124024[158] = 4.9353;
pedestal_124024[159] = 4.6056;
pedestal_124024[160] = 4.4509;
pedestal_124024[161] = 4.2621;
pedestal_124024[162] = 5.1463;
pedestal_124024[163] = 4.3820;
pedestal_124024[164] = 4.7474;
pedestal_124024[165] = 4.1152;
pedestal_124024[166] = 4.4410;
pedestal_124024[167] = 4.6147;
pedestal_124024[168] = 4.2389;
pedestal_124024[169] = 4.4910;
pedestal_124024[170] = 4.8035;
pedestal_124024[171] = 4.3879;
pedestal_124024[172] = 4.6798;
pedestal_124024[173] = 4.0704;
pedestal_124024[174] = 4.4376;
pedestal_124024[175] = 4.3591;
pedestal_124024[176] = 4.2962;
pedestal_124024[177] = 4.9087;
pedestal_124024[178] = 4.8844;
pedestal_124024[179] = 4.3502;
pedestal_124024[180] = 4.7960;
pedestal_124024[181] = 4.4050;
pedestal_124024[182] = 4.3751;
pedestal_124024[183] = 4.7134;
pedestal_124024[184] = 4.7286;
pedestal_124024[185] = 4.5207;
pedestal_124024[186] = 4.6296;
pedestal_124024[187] = 4.6510;
pedestal_124024[188] = 4.4421;
pedestal_124024[189] = 4.3006;
pedestal_124024[190] = 4.5514;
pedestal_124024[191] = 4.3377;
pedestal_124024[192] = 5.2064;
pedestal_124024[193] = 4.1611;
pedestal_124024[194] = 4.7980;
pedestal_124024[195] = 5.0893;
pedestal_124024[196] = 4.4249;
pedestal_124024[197] = 4.3013;
pedestal_124024[198] = 4.6128;
pedestal_124024[199] = 4.4499;
pedestal_124024[200] = 4.4992;
pedestal_124024[201] = 4.8840;
pedestal_124024[202] = 4.6085;
pedestal_124024[203] = 4.0955;
pedestal_124024[204] = 4.2911;
pedestal_124024[205] = 4.5484;
pedestal_124024[206] = 4.9366;
pedestal_124024[207] = 4.3075;
pedestal_124024[208] = 4.7178;
pedestal_124024[209] = 4.2114;
pedestal_124024[210] = 4.3766;
pedestal_124024[211] = 4.2443;
pedestal_124024[212] = 4.5119;
pedestal_124024[213] = 4.3345;
pedestal_124024[214] = 4.3431;
pedestal_124024[215] = 4.8448;
pedestal_124024[216] = 4.5872;
pedestal_124024[217] = 4.8488;
pedestal_124024[218] = 4.3664;
pedestal_124024[219] = 4.3997;
pedestal_124024[220] = 4.5606;
pedestal_124024[221] = 4.1379;
pedestal_124024[222] = 4.8497;
pedestal_124024[223] = 4.8435;


pedestal_124027[0] = 4.9824;
pedestal_124027[1] = 4.8183;
pedestal_124027[2] = 4.6065;
pedestal_124027[3] = 4.8103;
pedestal_124027[4] = 4.4474;
pedestal_124027[5] = 4.6155;
pedestal_124027[6] = 4.2588;
pedestal_124027[7] = 4.4194;
pedestal_124027[8] = 4.0188;
pedestal_124027[9] = 4.5736;
pedestal_124027[10] = 0.0000;
pedestal_124027[11] = 0.0000;
pedestal_124027[12] = 4.7140;
pedestal_124027[13] = 4.4829;
pedestal_124027[14] = 4.7830;
pedestal_124027[15] = 4.1728;
pedestal_124027[16] = 4.3743;
pedestal_124027[17] = 4.0964;
pedestal_124027[18] = 4.4635;
pedestal_124027[19] = 4.6183;
pedestal_124027[20] = 4.2081;
pedestal_124027[21] = 4.5873;
pedestal_124027[22] = 5.0451;
pedestal_124027[23] = 4.2555;
pedestal_124027[24] = 4.2024;
pedestal_124027[25] = 4.5929;
pedestal_124027[26] = 4.3791;
pedestal_124027[27] = 4.8581;
pedestal_124027[28] = 4.7884;
pedestal_124027[29] = 4.9034;
pedestal_124027[30] = 4.8444;
pedestal_124027[31] = 4.4180;
pedestal_124027[32] = 4.2888;
pedestal_124027[33] = 4.8279;
pedestal_124027[34] = 4.0704;
pedestal_124027[35] = 4.5499;
pedestal_124027[36] = 4.7024;
pedestal_124027[37] = 4.4879;
pedestal_124027[38] = 4.5530;
pedestal_124027[39] = 4.7111;
pedestal_124027[40] = 4.3828;
pedestal_124027[41] = 5.0938;
pedestal_124027[42] = 4.0518;
pedestal_124027[43] = 4.4015;
pedestal_124027[44] = 4.7068;
pedestal_124027[45] = 4.3748;
pedestal_124027[46] = 4.9510;
pedestal_124027[47] = 4.5294;
pedestal_124027[48] = 5.2012;
pedestal_124027[49] = 4.5948;
pedestal_124027[50] = 4.4816;
pedestal_124027[51] = 4.7704;
pedestal_124027[52] = 4.5233;
pedestal_124027[53] = 5.4496;
pedestal_124027[54] = 4.7645;
pedestal_124027[55] = 4.0632;
pedestal_124027[56] = 4.1353;
pedestal_124027[57] = 4.1835;
pedestal_124027[58] = 4.4802;
pedestal_124027[59] = 4.7987;
pedestal_124027[60] = 4.5085;
pedestal_124027[61] = 4.3036;
pedestal_124027[62] = 4.6129;
pedestal_124027[63] = 4.0336;
pedestal_124027[64] = 4.4252;
pedestal_124027[65] = 4.1704;
pedestal_124027[66] = 4.4133;
pedestal_124027[67] = 4.3499;
pedestal_124027[68] = 4.3447;
pedestal_124027[69] = 4.6394;
pedestal_124027[70] = 3.9433;
pedestal_124027[71] = 4.0305;
pedestal_124027[72] = 4.5158;
pedestal_124027[73] = 4.7404;
pedestal_124027[74] = 4.7301;
pedestal_124027[75] = 4.7501;
pedestal_124027[76] = 4.6313;
pedestal_124027[77] = 4.4013;
pedestal_124027[78] = 4.3443;
pedestal_124027[79] = 4.6466;
pedestal_124027[80] = 3.6040;
pedestal_124027[81] = 4.2793;
pedestal_124027[82] = 4.2986;
pedestal_124027[83] = 4.3340;
pedestal_124027[84] = 4.2504;
pedestal_124027[85] = 4.8808;
pedestal_124027[86] = 4.4493;
pedestal_124027[87] = 4.4696;
pedestal_124027[88] = 4.4810;
pedestal_124027[89] = 4.4732;
pedestal_124027[90] = 4.1587;
pedestal_124027[91] = 4.4359;
pedestal_124027[92] = 4.5284;
pedestal_124027[93] = 4.0545;
pedestal_124027[94] = 4.5879;
pedestal_124027[95] = 8.5442;
pedestal_124027[96] = 4.2275;
pedestal_124027[97] = 4.0595;
pedestal_124027[98] = 4.2286;
pedestal_124027[99] = 4.5912;
pedestal_124027[100] = 4.2342;
pedestal_124027[101] = 4.3772;
pedestal_124027[102] = 4.0562;
pedestal_124027[103] = 4.6261;
pedestal_124027[104] = 4.4533;
pedestal_124027[105] = 4.3592;
pedestal_124027[106] = 5.0183;
pedestal_124027[107] = 4.4083;
pedestal_124027[108] = 4.3964;
pedestal_124027[109] = 4.9764;
pedestal_124027[110] = 5.0529;
pedestal_124027[111] = 5.1849;
pedestal_124027[112] = 4.5433;
pedestal_124027[113] = 4.4114;
pedestal_124027[114] = 4.9104;
pedestal_124027[115] = 4.1313;
pedestal_124027[116] = 4.2975;
pedestal_124027[117] = 4.4834;
pedestal_124027[118] = 4.4856;
pedestal_124027[119] = 7.9794;
pedestal_124027[120] = 4.4079;
pedestal_124027[121] = 4.3753;
pedestal_124027[122] = 4.2592;
pedestal_124027[123] = 4.4065;
pedestal_124027[124] = 4.2432;
pedestal_124027[125] = 4.7052;
pedestal_124027[126] = 4.2938;
pedestal_124027[127] = 4.8026;
pedestal_124027[128] = 4.2483;
pedestal_124027[129] = 4.6498;
pedestal_124027[130] = 4.5848;
pedestal_124027[131] = 5.0455;
pedestal_124027[132] = 4.3763;
pedestal_124027[133] = 4.4995;
pedestal_124027[134] = 4.9330;
pedestal_124027[135] = 4.6244;
pedestal_124027[136] = 4.4823;
pedestal_124027[137] = 4.3351;
pedestal_124027[138] = 4.6557;
pedestal_124027[139] = 4.2221;
pedestal_124027[140] = 3.0737;
pedestal_124027[141] = 4.3969;
pedestal_124027[142] = 4.4669;
pedestal_124027[143] = 4.5936;
pedestal_124027[144] = 4.2586;
pedestal_124027[145] = 4.3672;
pedestal_124027[146] = 4.5953;
pedestal_124027[147] = 5.2296;
pedestal_124027[148] = 4.2164;
pedestal_124027[149] = 4.2973;
pedestal_124027[150] = 4.2899;
pedestal_124027[151] = 4.6328;
pedestal_124027[152] = 4.0424;
pedestal_124027[153] = 4.2532;
pedestal_124027[154] = 4.4769;
pedestal_124027[155] = 4.8225;
pedestal_124027[156] = 4.4580;
pedestal_124027[157] = 4.0654;
pedestal_124027[158] = 4.9436;
pedestal_124027[159] = 4.6141;
pedestal_124027[160] = 4.4415;
pedestal_124027[161] = 4.2693;
pedestal_124027[162] = 5.1560;
pedestal_124027[163] = 4.3810;
pedestal_124027[164] = 4.7545;
pedestal_124027[165] = 4.0984;
pedestal_124027[166] = 4.4661;
pedestal_124027[167] = 4.5902;
pedestal_124027[168] = 4.2411;
pedestal_124027[169] = 4.4814;
pedestal_124027[170] = 4.7237;
pedestal_124027[171] = 4.3826;
pedestal_124027[172] = 4.6950;
pedestal_124027[173] = 4.0654;
pedestal_124027[174] = 4.4249;
pedestal_124027[175] = 4.3675;
pedestal_124027[176] = 4.2968;
pedestal_124027[177] = 4.9162;
pedestal_124027[178] = 4.9064;
pedestal_124027[179] = 4.3574;
pedestal_124027[180] = 4.7824;
pedestal_124027[181] = 4.4248;
pedestal_124027[182] = 4.3529;
pedestal_124027[183] = 4.7074;
pedestal_124027[184] = 4.7429;
pedestal_124027[185] = 4.5368;
pedestal_124027[186] = 4.6872;
pedestal_124027[187] = 4.6492;
pedestal_124027[188] = 4.4345;
pedestal_124027[189] = 4.3186;
pedestal_124027[190] = 4.5474;
pedestal_124027[191] = 4.3427;
pedestal_124027[192] = 5.1833;
pedestal_124027[193] = 4.1223;
pedestal_124027[194] = 4.7301;
pedestal_124027[195] = 5.1496;
pedestal_124027[196] = 4.4262;
pedestal_124027[197] = 4.3020;
pedestal_124027[198] = 4.6089;
pedestal_124027[199] = 4.4648;
pedestal_124027[200] = 4.4892;
pedestal_124027[201] = 4.8740;
pedestal_124027[202] = 4.5901;
pedestal_124027[203] = 4.0835;
pedestal_124027[204] = 4.3119;
pedestal_124027[205] = 4.5380;
pedestal_124027[206] = 4.9881;
pedestal_124027[207] = 4.4649;
pedestal_124027[208] = 4.6092;
pedestal_124027[209] = 4.1543;
pedestal_124027[210] = 4.2783;
pedestal_124027[211] = 4.3073;
pedestal_124027[212] = 4.5011;
pedestal_124027[213] = 4.3235;
pedestal_124027[214] = 4.3365;
pedestal_124027[215] = 4.8314;
pedestal_124027[216] = 4.5219;
pedestal_124027[217] = 4.7920;
pedestal_124027[218] = 4.3512;
pedestal_124027[219] = 4.3797;
pedestal_124027[220] = 4.5717;
pedestal_124027[221] = 4.1560;
pedestal_124027[222] = 4.8685;
pedestal_124027[223] = 4.8471;


pedestal_124030[0] = 4.9537;
pedestal_124030[1] = 4.8171;
pedestal_124030[2] = 4.5927;
pedestal_124030[3] = 4.8088;
pedestal_124030[4] = 4.4549;
pedestal_124030[5] = 4.6064;
pedestal_124030[6] = 4.2668;
pedestal_124030[7] = 4.4256;
pedestal_124030[8] = 4.0059;
pedestal_124030[9] = 4.5676;
pedestal_124030[10] = 0.0000;
pedestal_124030[11] = 0.0000;
pedestal_124030[12] = 4.7017;
pedestal_124030[13] = 4.4591;
pedestal_124030[14] = 4.7631;
pedestal_124030[15] = 4.1492;
pedestal_124030[16] = 4.3707;
pedestal_124030[17] = 4.1014;
pedestal_124030[18] = 4.4733;
pedestal_124030[19] = 4.6252;
pedestal_124030[20] = 4.2030;
pedestal_124030[21] = 4.5958;
pedestal_124030[22] = 5.0662;
pedestal_124030[23] = 4.2517;
pedestal_124030[24] = 4.2104;
pedestal_124030[25] = 4.5832;
pedestal_124030[26] = 4.3656;
pedestal_124030[27] = 4.8316;
pedestal_124030[28] = 4.7761;
pedestal_124030[29] = 4.9036;
pedestal_124030[30] = 4.8416;
pedestal_124030[31] = 4.4007;
pedestal_124030[32] = 4.2775;
pedestal_124030[33] = 4.8216;
pedestal_124030[34] = 4.0729;
pedestal_124030[35] = 4.5392;
pedestal_124030[36] = 4.6941;
pedestal_124030[37] = 4.4817;
pedestal_124030[38] = 4.5639;
pedestal_124030[39] = 4.7279;
pedestal_124030[40] = 4.3851;
pedestal_124030[41] = 5.1022;
pedestal_124030[42] = 4.0560;
pedestal_124030[43] = 4.3961;
pedestal_124030[44] = 4.7126;
pedestal_124030[45] = 4.3689;
pedestal_124030[46] = 4.9349;
pedestal_124030[47] = 4.5297;
pedestal_124030[48] = 5.2207;
pedestal_124030[49] = 4.5814;
pedestal_124030[50] = 4.4941;
pedestal_124030[51] = 4.7617;
pedestal_124030[52] = 4.5140;
pedestal_124030[53] = 5.4389;
pedestal_124030[54] = 4.7501;
pedestal_124030[55] = 4.0647;
pedestal_124030[56] = 4.1376;
pedestal_124030[57] = 4.1939;
pedestal_124030[58] = 4.4938;
pedestal_124030[59] = 4.8223;
pedestal_124030[60] = 4.5122;
pedestal_124030[61] = 4.2904;
pedestal_124030[62] = 4.6307;
pedestal_124030[63] = 4.0349;
pedestal_124030[64] = 4.4188;
pedestal_124030[65] = 4.1793;
pedestal_124030[66] = 4.4123;
pedestal_124030[67] = 4.3539;
pedestal_124030[68] = 4.3693;
pedestal_124030[69] = 4.6195;
pedestal_124030[70] = 3.9435;
pedestal_124030[71] = 4.0301;
pedestal_124030[72] = 4.5101;
pedestal_124030[73] = 4.7309;
pedestal_124030[74] = 4.7189;
pedestal_124030[75] = 4.7459;
pedestal_124030[76] = 4.6325;
pedestal_124030[77] = 4.4008;
pedestal_124030[78] = 4.3371;
pedestal_124030[79] = 4.6332;
pedestal_124030[80] = 3.5935;
pedestal_124030[81] = 4.2809;
pedestal_124030[82] = 4.3171;
pedestal_124030[83] = 4.3387;
pedestal_124030[84] = 4.2554;
pedestal_124030[85] = 4.8863;
pedestal_124030[86] = 4.4401;
pedestal_124030[87] = 4.4694;
pedestal_124030[88] = 4.4626;
pedestal_124030[89] = 4.4682;
pedestal_124030[90] = 4.1636;
pedestal_124030[91] = 4.4203;
pedestal_124030[92] = 4.5212;
pedestal_124030[93] = 4.0656;
pedestal_124030[94] = 4.5726;
pedestal_124030[95] = 8.8236;
pedestal_124030[96] = 4.2364;
pedestal_124030[97] = 4.0553;
pedestal_124030[98] = 4.2340;
pedestal_124030[99] = 4.5773;
pedestal_124030[100] = 4.2502;
pedestal_124030[101] = 4.3677;
pedestal_124030[102] = 4.0716;
pedestal_124030[103] = 4.6289;
pedestal_124030[104] = 4.4436;
pedestal_124030[105] = 4.3684;
pedestal_124030[106] = 5.0018;
pedestal_124030[107] = 4.4117;
pedestal_124030[108] = 4.3899;
pedestal_124030[109] = 4.9806;
pedestal_124030[110] = 5.0373;
pedestal_124030[111] = 5.1793;
pedestal_124030[112] = 4.5462;
pedestal_124030[113] = 4.3863;
pedestal_124030[114] = 4.9231;
pedestal_124030[115] = 4.1149;
pedestal_124030[116] = 4.2843;
pedestal_124030[117] = 4.4956;
pedestal_124030[118] = 4.4909;
pedestal_124030[119] = 7.8579;
pedestal_124030[120] = 4.4116;
pedestal_124030[121] = 4.3700;
pedestal_124030[122] = 4.2569;
pedestal_124030[123] = 4.4263;
pedestal_124030[124] = 4.2418;
pedestal_124030[125] = 4.7026;
pedestal_124030[126] = 4.3036;
pedestal_124030[127] = 4.8038;
pedestal_124030[128] = 4.2414;
pedestal_124030[129] = 4.6430;
pedestal_124030[130] = 4.5821;
pedestal_124030[131] = 5.0537;
pedestal_124030[132] = 4.3603;
pedestal_124030[133] = 4.4815;
pedestal_124030[134] = 4.9266;
pedestal_124030[135] = 4.6207;
pedestal_124030[136] = 4.4799;
pedestal_124030[137] = 4.3498;
pedestal_124030[138] = 4.6566;
pedestal_124030[139] = 4.2245;
pedestal_124030[140] = 3.0813;
pedestal_124030[141] = 4.3958;
pedestal_124030[142] = 4.4809;
pedestal_124030[143] = 4.6046;
pedestal_124030[144] = 4.2569;
pedestal_124030[145] = 4.3772;
pedestal_124030[146] = 4.5870;
pedestal_124030[147] = 5.2250;
pedestal_124030[148] = 4.2238;
pedestal_124030[149] = 4.2921;
pedestal_124030[150] = 4.2843;
pedestal_124030[151] = 4.6387;
pedestal_124030[152] = 4.0419;
pedestal_124030[153] = 4.2498;
pedestal_124030[154] = 4.4676;
pedestal_124030[155] = 4.8297;
pedestal_124030[156] = 4.4532;
pedestal_124030[157] = 4.0748;
pedestal_124030[158] = 4.9367;
pedestal_124030[159] = 4.6124;
pedestal_124030[160] = 4.4588;
pedestal_124030[161] = 4.2696;
pedestal_124030[162] = 5.1538;
pedestal_124030[163] = 4.3679;
pedestal_124030[164] = 4.7458;
pedestal_124030[165] = 4.0915;
pedestal_124030[166] = 4.4440;
pedestal_124030[167] = 4.6086;
pedestal_124030[168] = 4.2245;
pedestal_124030[169] = 4.4840;
pedestal_124030[170] = 4.7218;
pedestal_124030[171] = 4.3820;
pedestal_124030[172] = 4.6881;
pedestal_124030[173] = 4.0634;
pedestal_124030[174] = 4.4225;
pedestal_124030[175] = 4.3641;
pedestal_124030[176] = 4.2963;
pedestal_124030[177] = 4.9106;
pedestal_124030[178] = 4.9035;
pedestal_124030[179] = 4.3469;
pedestal_124030[180] = 4.7765;
pedestal_124030[181] = 4.4153;
pedestal_124030[182] = 4.3624;
pedestal_124030[183] = 4.7174;
pedestal_124030[184] = 4.7419;
pedestal_124030[185] = 4.5269;
pedestal_124030[186] = 4.6877;
pedestal_124030[187] = 4.6486;
pedestal_124030[188] = 4.4362;
pedestal_124030[189] = 4.3059;
pedestal_124030[190] = 4.5539;
pedestal_124030[191] = 4.3500;
pedestal_124030[192] = 5.1814;
pedestal_124030[193] = 4.1086;
pedestal_124030[194] = 4.7271;
pedestal_124030[195] = 5.1498;
pedestal_124030[196] = 4.4185;
pedestal_124030[197] = 4.3017;
pedestal_124030[198] = 4.6087;
pedestal_124030[199] = 4.4594;
pedestal_124030[200] = 4.4918;
pedestal_124030[201] = 4.8744;
pedestal_124030[202] = 4.6172;
pedestal_124030[203] = 4.0902;
pedestal_124030[204] = 4.3111;
pedestal_124030[205] = 4.5539;
pedestal_124030[206] = 4.9823;
pedestal_124030[207] = 4.4723;
pedestal_124030[208] = 4.6001;
pedestal_124030[209] = 4.1424;
pedestal_124030[210] = 4.2890;
pedestal_124030[211] = 4.3224;
pedestal_124030[212] = 4.4970;
pedestal_124030[213] = 4.3182;
pedestal_124030[214] = 4.3559;
pedestal_124030[215] = 4.8452;
pedestal_124030[216] = 4.5085;
pedestal_124030[217] = 4.7865;
pedestal_124030[218] = 4.3509;
pedestal_124030[219] = 4.3818;
pedestal_124030[220] = 4.5696;
pedestal_124030[221] = 4.1616;
pedestal_124030[222] = 4.8806;
pedestal_124030[223] = 4.8564;


pedestal_124120[0] = 4.9658;
pedestal_124120[1] = 4.8339;
pedestal_124120[2] = 4.6349;
pedestal_124120[3] = 4.8136;
pedestal_124120[4] = 4.4227;
pedestal_124120[5] = 4.6335;
pedestal_124120[6] = 4.2844;
pedestal_124120[7] = 4.2640;
pedestal_124120[8] = 4.0631;
pedestal_124120[9] = 4.5795;
pedestal_124120[10] = 4.5396;
pedestal_124120[11] = 4.4252;
pedestal_124120[12] = 4.5562;
pedestal_124120[13] = 4.4753;
pedestal_124120[14] = 4.6442;
pedestal_124120[15] = 4.1464;
pedestal_124120[16] = 4.3826;
pedestal_124120[17] = 4.0561;
pedestal_124120[18] = 4.5038;
pedestal_124120[19] = 4.6302;
pedestal_124120[20] = 4.1787;
pedestal_124120[21] = 4.5973;
pedestal_124120[22] = 4.9318;
pedestal_124120[23] = 4.4080;
pedestal_124120[24] = 4.1861;
pedestal_124120[25] = 4.5896;
pedestal_124120[26] = 4.3399;
pedestal_124120[27] = 4.8645;
pedestal_124120[28] = 4.7825;
pedestal_124120[29] = 4.8507;
pedestal_124120[30] = 4.7709;
pedestal_124120[31] = 4.2826;
pedestal_124120[32] = 4.3456;
pedestal_124120[33] = 4.7374;
pedestal_124120[34] = 4.1261;
pedestal_124120[35] = 4.4355;
pedestal_124120[36] = 4.6372;
pedestal_124120[37] = 4.4806;
pedestal_124120[38] = 4.4376;
pedestal_124120[39] = 4.7839;
pedestal_124120[40] = 4.3376;
pedestal_124120[41] = 4.8654;
pedestal_124120[42] = 4.1207;
pedestal_124120[43] = 4.2955;
pedestal_124120[44] = 4.6770;
pedestal_124120[45] = 4.3757;
pedestal_124120[46] = 4.8635;
pedestal_124120[47] = 4.5702;
pedestal_124120[48] = 5.1316;
pedestal_124120[49] = 4.5914;
pedestal_124120[50] = 4.3466;
pedestal_124120[51] = 4.6212;
pedestal_124120[52] = 4.5424;
pedestal_124120[53] = 5.4040;
pedestal_124120[54] = 4.8730;
pedestal_124120[55] = 4.3117;
pedestal_124120[56] = 4.2175;
pedestal_124120[57] = 4.1305;
pedestal_124120[58] = 4.6471;
pedestal_124120[59] = 4.8401;
pedestal_124120[60] = 4.4413;
pedestal_124120[61] = 4.1996;
pedestal_124120[62] = 4.6532;
pedestal_124120[63] = 4.1210;
pedestal_124120[64] = 4.3352;
pedestal_124120[65] = 4.1753;
pedestal_124120[66] = 4.3566;
pedestal_124120[67] = 4.3360;
pedestal_124120[68] = 4.0588;
pedestal_124120[69] = 4.6522;
pedestal_124120[70] = 4.0830;
pedestal_124120[71] = 4.1038;
pedestal_124120[72] = 4.6010;
pedestal_124120[73] = 4.7179;
pedestal_124120[74] = 4.6081;
pedestal_124120[75] = 4.6701;
pedestal_124120[76] = 4.6356;
pedestal_124120[77] = 4.2990;
pedestal_124120[78] = 4.2860;
pedestal_124120[79] = 4.6066;
pedestal_124120[80] = 3.5169;
pedestal_124120[81] = 4.2737;
pedestal_124120[82] = 4.3416;
pedestal_124120[83] = 4.3924;
pedestal_124120[84] = 4.3886;
pedestal_124120[85] = 4.4981;
pedestal_124120[86] = 4.4433;
pedestal_124120[87] = 4.5143;
pedestal_124120[88] = 4.5408;
pedestal_124120[89] = 4.3858;
pedestal_124120[90] = 4.2069;
pedestal_124120[91] = 4.4049;
pedestal_124120[92] = 4.5167;
pedestal_124120[93] = 3.9761;
pedestal_124120[94] = 4.6356;
pedestal_124120[95] = 8.6164;
pedestal_124120[96] = 4.2229;
pedestal_124120[97] = 4.0205;
pedestal_124120[98] = 4.2512;
pedestal_124120[99] = 4.4826;
pedestal_124120[100] = 4.2125;
pedestal_124120[101] = 4.3798;
pedestal_124120[102] = 4.0871;
pedestal_124120[103] = 4.6152;
pedestal_124120[104] = 4.4744;
pedestal_124120[105] = 4.3639;
pedestal_124120[106] = 4.9369;
pedestal_124120[107] = 4.3607;
pedestal_124120[108] = 4.3042;
pedestal_124120[109] = 5.0162;
pedestal_124120[110] = 4.8755;
pedestal_124120[111] = 5.2273;
pedestal_124120[112] = 4.4813;
pedestal_124120[113] = 4.4335;
pedestal_124120[114] = 4.8344;
pedestal_124120[115] = 4.1422;
pedestal_124120[116] = 4.3123;
pedestal_124120[117] = 4.5484;
pedestal_124120[118] = 4.6981;
pedestal_124120[119] = 7.9210;
pedestal_124120[120] = 4.3303;
pedestal_124120[121] = 4.3963;
pedestal_124120[122] = 4.2231;
pedestal_124120[123] = 4.3369;
pedestal_124120[124] = 4.1448;
pedestal_124120[125] = 4.7504;
pedestal_124120[126] = 4.2726;
pedestal_124120[127] = 4.7671;
pedestal_124120[128] = 4.1711;
pedestal_124120[129] = 4.6645;
pedestal_124120[130] = 4.5485;
pedestal_124120[131] = 5.1467;
pedestal_124120[132] = 4.3344;
pedestal_124120[133] = 4.3864;
pedestal_124120[134] = 4.7992;
pedestal_124120[135] = 4.5793;
pedestal_124120[136] = 4.5071;
pedestal_124120[137] = 4.3778;
pedestal_124120[138] = 4.6240;
pedestal_124120[139] = 4.1693;
pedestal_124120[140] = 3.1088;
pedestal_124120[141] = 4.3536;
pedestal_124120[142] = 4.4424;
pedestal_124120[143] = 4.6292;
pedestal_124120[144] = 4.2806;
pedestal_124120[145] = 4.2581;
pedestal_124120[146] = 4.4951;
pedestal_124120[147] = 5.2315;
pedestal_124120[148] = 4.1539;
pedestal_124120[149] = 4.1503;
pedestal_124120[150] = 4.4004;
pedestal_124120[151] = 4.5479;
pedestal_124120[152] = 3.9481;
pedestal_124120[153] = 4.3288;
pedestal_124120[154] = 4.4919;
pedestal_124120[155] = 4.7515;
pedestal_124120[156] = 4.4257;
pedestal_124120[157] = 4.0673;
pedestal_124120[158] = 4.9388;
pedestal_124120[159] = 4.5421;
pedestal_124120[160] = 4.3706;
pedestal_124120[161] = 4.2953;
pedestal_124120[162] = 5.1387;
pedestal_124120[163] = 4.3676;
pedestal_124120[164] = 4.7865;
pedestal_124120[165] = 4.1599;
pedestal_124120[166] = 4.8068;
pedestal_124120[167] = 4.6607;
pedestal_124120[168] = 4.1650;
pedestal_124120[169] = 4.5772;
pedestal_124120[170] = 4.7302;
pedestal_124120[171] = 4.3479;
pedestal_124120[172] = 4.6753;
pedestal_124120[173] = 4.0855;
pedestal_124120[174] = 4.3808;
pedestal_124120[175] = 4.2686;
pedestal_124120[176] = 4.3318;
pedestal_124120[177] = 4.8804;
pedestal_124120[178] = 4.6814;
pedestal_124120[179] = 4.4025;
pedestal_124120[180] = 4.7755;
pedestal_124120[181] = 4.3264;
pedestal_124120[182] = 4.3876;
pedestal_124120[183] = 4.8336;
pedestal_124120[184] = 4.6772;
pedestal_124120[185] = 4.3616;
pedestal_124120[186] = 4.6462;
pedestal_124120[187] = 4.5913;
pedestal_124120[188] = 4.4793;
pedestal_124120[189] = 4.1970;
pedestal_124120[190] = 4.5448;
pedestal_124120[191] = 4.3577;
pedestal_124120[192] = 5.1626;
pedestal_124120[193] = 4.1242;
pedestal_124120[194] = 4.7805;
pedestal_124120[195] = 5.0642;
pedestal_124120[196] = 4.4972;
pedestal_124120[197] = 4.5605;
pedestal_124120[198] = 4.6480;
pedestal_124120[199] = 4.3443;
pedestal_124120[200] = 4.5768;
pedestal_124120[201] = 4.8030;
pedestal_124120[202] = 4.6675;
pedestal_124120[203] = 4.0932;
pedestal_124120[204] = 4.2175;
pedestal_124120[205] = 4.4608;
pedestal_124120[206] = 4.8788;
pedestal_124120[207] = 4.4023;
pedestal_124120[208] = 4.7030;
pedestal_124120[209] = 4.1526;
pedestal_124120[210] = 4.2621;
pedestal_124120[211] = 4.2349;
pedestal_124120[212] = 4.5874;
pedestal_124120[213] = 4.4112;
pedestal_124120[214] = 4.2844;
pedestal_124120[215] = 4.9314;
pedestal_124120[216] = 4.5702;
pedestal_124120[217] = 4.6958;
pedestal_124120[218] = 4.4483;
pedestal_124120[219] = 4.4503;
pedestal_124120[220] = 4.4958;
pedestal_124120[221] = 4.0600;
pedestal_124120[222] = 4.8553;
pedestal_124120[223] = 4.8510;


pedestal_MC[0] = 4.9267;
pedestal_MC[1] = 4.8398;
pedestal_MC[2] = 4.6314;
pedestal_MC[3] = 4.7958;
pedestal_MC[4] = 4.5238;
pedestal_MC[5] = 4.6678;
pedestal_MC[6] = 4.2678;
pedestal_MC[7] = 4.3512;
pedestal_MC[8] = 4.0073;
pedestal_MC[9] = 4.6230;
pedestal_MC[10] = 4.6230;
pedestal_MC[11] = 4.6230;
pedestal_MC[12] = 4.7232;
pedestal_MC[13] = 4.4597;
pedestal_MC[14] = 4.7950;
pedestal_MC[15] = 4.1887;
pedestal_MC[16] = 4.5191;
pedestal_MC[17] = 4.0909;
pedestal_MC[18] = 4.5670;
pedestal_MC[19] = 4.6046;
pedestal_MC[20] = 4.2282;
pedestal_MC[21] = 4.6312;
pedestal_MC[22] = 5.0197;
pedestal_MC[23] = 4.3280;
pedestal_MC[24] = 4.2464;
pedestal_MC[25] = 4.5875;
pedestal_MC[26] = 4.3708;
pedestal_MC[27] = 4.9195;
pedestal_MC[28] = 4.7081;
pedestal_MC[29] = 4.9566;
pedestal_MC[30] = 4.7560;
pedestal_MC[31] = 4.4067;
pedestal_MC[32] = 4.3554;
pedestal_MC[33] = 4.7488;
pedestal_MC[34] = 4.0852;
pedestal_MC[35] = 4.4235;
pedestal_MC[36] = 4.7088;
pedestal_MC[37] = 4.4753;
pedestal_MC[38] = 4.5325;
pedestal_MC[39] = 4.7846;
pedestal_MC[40] = 4.4702;
pedestal_MC[41] = 5.0254;
pedestal_MC[42] = 4.1348;
pedestal_MC[43] = 4.4740;
pedestal_MC[44] = 4.7454;
pedestal_MC[45] = 4.3801;
pedestal_MC[46] = 4.9483;
pedestal_MC[47] = 4.5426;
pedestal_MC[48] = 5.1223;
pedestal_MC[49] = 4.6331;
pedestal_MC[50] = 4.5030;
pedestal_MC[51] = 4.7565;
pedestal_MC[52] = 4.5271;
pedestal_MC[53] = 5.3974;
pedestal_MC[54] = 4.7998;
pedestal_MC[55] = 4.2497;
pedestal_MC[56] = 4.1731;
pedestal_MC[57] = 4.2411;
pedestal_MC[58] = 4.5611;
pedestal_MC[59] = 4.8442;
pedestal_MC[60] = 4.5572;
pedestal_MC[61] = 4.1929;
pedestal_MC[62] = 4.6805;
pedestal_MC[63] = 4.1569;
pedestal_MC[64] = 4.4761;
pedestal_MC[65] = 4.1850;
pedestal_MC[66] = 4.3582;
pedestal_MC[67] = 4.4890;
pedestal_MC[68] = 4.3084;
pedestal_MC[69] = 4.6255;
pedestal_MC[70] = 3.9945;
pedestal_MC[71] = 4.0757;
pedestal_MC[72] = 4.5616;
pedestal_MC[73] = 4.7363;
pedestal_MC[74] = 4.7405;
pedestal_MC[75] = 4.7430;
pedestal_MC[76] = 4.6734;
pedestal_MC[77] = 4.5020;
pedestal_MC[78] = 4.3546;
pedestal_MC[79] = 4.4693;
pedestal_MC[80] = 3.6545;
pedestal_MC[81] = 4.2928;
pedestal_MC[82] = 4.3106;
pedestal_MC[83] = 4.3771;
pedestal_MC[84] = 4.2803;
pedestal_MC[85] = 4.7001;
pedestal_MC[86] = 4.4699;
pedestal_MC[87] = 4.5006;
pedestal_MC[88] = 4.5488;
pedestal_MC[89] = 4.4818;
pedestal_MC[90] = 4.1377;
pedestal_MC[91] = 4.4358;
pedestal_MC[92] = 4.5111;
pedestal_MC[93] = 4.0435;
pedestal_MC[94] = 4.6019;
pedestal_MC[95] = 4.6427;
pedestal_MC[96] = 4.2975;
pedestal_MC[97] = 4.0629;
pedestal_MC[98] = 4.2918;
pedestal_MC[99] = 4.5311;
pedestal_MC[100] = 4.3631;
pedestal_MC[101] = 4.4486;
pedestal_MC[102] = 4.0985;
pedestal_MC[103] = 4.7082;
pedestal_MC[104] = 4.6304;
pedestal_MC[105] = 4.3241;
pedestal_MC[106] = 5.0347;
pedestal_MC[107] = 4.5283;
pedestal_MC[108] = 4.3628;
pedestal_MC[109] = 4.9560;
pedestal_MC[110] = 5.0085;
pedestal_MC[111] = 5.2307;
pedestal_MC[112] = 4.6235;
pedestal_MC[113] = 4.4992;
pedestal_MC[114] = 5.1412;
pedestal_MC[115] = 4.1601;
pedestal_MC[116] = 4.2857;
pedestal_MC[117] = 4.4840;
pedestal_MC[118] = 4.5964;
pedestal_MC[119] = 10.3635;
pedestal_MC[120] = 4.3941;
pedestal_MC[121] = 4.4954;
pedestal_MC[122] = 4.2513;
pedestal_MC[123] = 4.4847;
pedestal_MC[124] = 4.3304;
pedestal_MC[125] = 4.6146;
pedestal_MC[126] = 4.3282;
pedestal_MC[127] = 4.8168;
pedestal_MC[128] = 4.3316;
pedestal_MC[129] = 4.5745;
pedestal_MC[130] = 4.6030;
pedestal_MC[131] = 5.1141;
pedestal_MC[132] = 4.4860;
pedestal_MC[133] = 4.6198;
pedestal_MC[134] = 4.8934;
pedestal_MC[135] = 4.6021;
pedestal_MC[136] = 4.3572;
pedestal_MC[137] = 4.3408;
pedestal_MC[138] = 4.6746;
pedestal_MC[139] = 4.3197;
pedestal_MC[140] = 3.0826;
pedestal_MC[141] = 4.4304;
pedestal_MC[142] = 4.4753;
pedestal_MC[143] = 4.5247;
pedestal_MC[144] = 4.2663;
pedestal_MC[145] = 4.4541;
pedestal_MC[146] = 4.6193;
pedestal_MC[147] = 5.2135;
pedestal_MC[148] = 4.2507;
pedestal_MC[149] = 4.6279;
pedestal_MC[150] = 4.3397;
pedestal_MC[151] = 4.6465;
pedestal_MC[152] = 4.1089;
pedestal_MC[153] = 4.3336;
pedestal_MC[154] = 4.4331;
pedestal_MC[155] = 4.8046;
pedestal_MC[156] = 4.4805;
pedestal_MC[157] = 4.0374;
pedestal_MC[158] = 4.9214;
pedestal_MC[159] = 4.6088;
pedestal_MC[160] = 4.4234;
pedestal_MC[161] = 4.3098;
pedestal_MC[162] = 5.1656;
pedestal_MC[163] = 4.4431;
pedestal_MC[164] = 4.7445;
pedestal_MC[165] = 4.1729;
pedestal_MC[166] = 4.5465;
pedestal_MC[167] = 4.6090;
pedestal_MC[168] = 4.2728;
pedestal_MC[169] = 4.6148;
pedestal_MC[170] = 4.7741;
pedestal_MC[171] = 4.3973;
pedestal_MC[172] = 4.6820;
pedestal_MC[173] = 4.0804;
pedestal_MC[174] = 4.4674;
pedestal_MC[175] = 4.3914;
pedestal_MC[176] = 4.3435;
pedestal_MC[177] = 4.9273;
pedestal_MC[178] = 4.6719;
pedestal_MC[179] = 4.3792;
pedestal_MC[180] = 4.8484;
pedestal_MC[181] = 4.4897;
pedestal_MC[182] = 4.4556;
pedestal_MC[183] = 4.6582;
pedestal_MC[184] = 4.7177;
pedestal_MC[185] = 4.6004;
pedestal_MC[186] = 4.6754;
pedestal_MC[187] = 4.5959;
pedestal_MC[188] = 4.5039;
pedestal_MC[189] = 4.1941;
pedestal_MC[190] = 4.5826;
pedestal_MC[191] = 4.3669;
pedestal_MC[192] = 5.1847;
pedestal_MC[193] = 4.1280;
pedestal_MC[194] = 4.7566;
pedestal_MC[195] = 5.1588;
pedestal_MC[196] = 4.4325;
pedestal_MC[197] = 4.4613;
pedestal_MC[198] = 4.5884;
pedestal_MC[199] = 4.4372;
pedestal_MC[200] = 4.6722;
pedestal_MC[201] = 4.8211;
pedestal_MC[202] = 4.5947;
pedestal_MC[203] = 4.2182;
pedestal_MC[204] = 4.2384;
pedestal_MC[205] = 4.5361;
pedestal_MC[206] = 5.0347;
pedestal_MC[207] = 4.3862;
pedestal_MC[208] = 4.6050;
pedestal_MC[209] = 4.1828;
pedestal_MC[210] = 4.4056;
pedestal_MC[211] = 4.3361;
pedestal_MC[212] = 4.4813;
pedestal_MC[213] = 4.2606;
pedestal_MC[214] = 4.3733;
pedestal_MC[215] = 4.8744;
pedestal_MC[216] = 4.6194;
pedestal_MC[217] = 4.7778;
pedestal_MC[218] = 4.2992;
pedestal_MC[219] = 4.3721;
pedestal_MC[220] = 4.6180;
pedestal_MC[221] = 4.2646;
pedestal_MC[222] = 4.8790;
pedestal_MC[223] = 4.8489;


	

}


TreeMaker::~TreeMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
  
   if(debug) cout<< " Run = " << iEvent.id().run() << " Event = " << iEvent.id().event();
   if(debug) cout<<""<<endl;
   eventNum      = iEvent.id().event() ;
   runNumber     = iEvent.id().run() ;
   lumiBlock     = iEvent.luminosityBlock() ;
   bunchCrossing = iEvent.bunchCrossing();
  
   /////////////////////////
   // start CASTOR digi part
   /////////////////////////
  
   Handle<CastorDigiCollection> digiCollection;
   const CastorDigiCollection* castordigis = 0;
   //iEvent.getByLabel("castorDigis", digiCollection);
   iEvent.getByLabel(castordigis_, digiCollection);
   
   ESHandle<CastorDbService> conditions;
   iSetup.get<CastorDbRecord>().get(conditions);
   
   const CastorQIEShape* shape = conditions->getCastorShape();

   for (int i = 0 ; i < 224; i++) {
     sumADC[i]=0;
     sumfC[i]=0;
     signal[i] =0;
     fCsignal[i]=0;
     pedestal[i]=0;
     module[i]=0;
     sector[i]=0;
     channel[i]=0;
     for(Int_t j = 0; j < 6; j++) {
       ADC[i][j]=0;
       fC[i][j]=0;
     }
   }
	
   
   if(digiCollection.isValid()){
   	castordigis = digiCollection.product();

   	for (unsigned int digiItr=0; digiItr<digiCollection->size(); ++digiItr) { //loop over 224 channels
 
     		CastorDataFrame castordf=(*castordigis)[digiItr];
     		int nrSamples = castordf.size();
     		HcalCastorDetId castorid = castordf.id();
     		Int_t channel_nb = 16*(castorid.module()-1) + castorid.sector();
     		Int_t channel_id = channel_nb - 1;

     		module[channel_id] = castorid.module();
     		sector[channel_id] = castorid.sector();
     		channel[channel_id]= channel_nb;
		
		// linearize ADC
		const CastorCalibrations& calibrations = conditions->getCastorCalibrations(castordf.id().rawId());
		const CastorQIECoder* coder = conditions->getCastorCoder(castordf.id().rawId());
    
    		//if (runNumber != 1) {
    		// data
		//cout << "====== This is data =======" << endl;
     		for (int sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
       			HcalQIESample mySample = castordf[sample];
       			ADC[channel_id][sample]=(mySample.adc());
			fC[channel_id][sample] = coder->charge(*shape,mySample.adc(),mySample.capid()); 
       			if(sample > 1) sumADC[channel_id]+=ADC[channel_id][sample]; // sum 4 last time slices
			if(sample > 1) sumfC[channel_id]+=fC[channel_id][sample]; // sum 4 last time slices
     		}
		//}
		
		/*
		if (runNumber == 1) {
			// MC
			//cout << "====== This is MC =======" << endl;
     			for (int sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
       				HcalQIESample mySample = castordf[sample];
       				ADC[channel_id][sample]=(mySample.adc());
       				if(sample > 1) sumADC[channel_id]+=ADC[channel_id][sample]; // sum 4 last time slices
     			}
			for (int sample = 0 ; sample < nrSamples; ++sample) { //loop over 6 time slices
       				HcalQIESample mySample = castordf[sample];
				// fC
				if (sample < 3) fC[channel_id][sample] = coder->charge(*shape,mySample.adc(),mySample.capid());
				if (sample == 3) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][3]*0.6,mySample.capid());
				if (sample == 4) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][sample]+ADC[channel_id][3]*0.3,mySample.capid());
				if (sample == 5) fC[channel_id][sample] = coder->charge(*shape,ADC[channel_id][sample]+ADC[channel_id][3]*0.1,mySample.capid());
				if(sample > 1) sumfC[channel_id]+=fC[channel_id][sample]; // sum 4 last time slices
     			}
		}
		*/
   
   	} 
  
         /*
    	for (int i = 0 ; i < 224; i++) {
      		if(debug) cout<<"array entry: "<<i <<", module: "<<module[i]<<", sector: "<<sector[i]<<" ,channel: "<<channel[i] <<", 4 last time slices: "<<sumADC[i]<<endl;
     		getchar();
  	}
	
	*/

	// copy pedestals into tree 
	if (runNumber == 124009) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124009[k];
		}
	}
	else if (runNumber == 124020) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124020[k];
		}
	}
	else if (runNumber == 124022) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124022[k];
		}
	}
	else if (runNumber == 124023) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124023[k];
		}
	}
	else if (runNumber == 124024) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124024[k];
		}
	}
	else if (runNumber == 124027) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124027[k];
		}
	}
	else if (runNumber == 124030) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124030[k];
		}
	}
	else if (runNumber == 124120) {
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_124120[k];
		}
	}
	else {
		//cout << "using MC pedestals" << endl;
		for (int k=0;k<224;k++) {
			pedestal[k] = pedestal_MC[k];
		}
	}
	
	
	
	
	// reconstruct ADC signal for first 80 channels
	for (int j=0;j<224;j++) {
		signal[j] = sumADC[j] - 4*pedestal[j];
		fCsignal[j] = sumfC[j] - 4*2.6*pedestal[j];
	}
	
	
  } else {
  	LogError("CastorDigiError") << "Failed to get CASTOR digis - skipping this part";
  }
  
  ///////////////////////
  // end CASTOR digi part
  ///////////////////////
  
  
  //////////////////////
  // start Trigger part
  //////////////////////
  
  PhysicsDeclared = 0;
  L1bit0 = 0;
  L1bit36 = 0;
  L1bit37 = 0;
  L1bit38 = 0;
  L1bit39 = 0;
  L1bit40 = 0;
  L1bit41 = 0;
  
  Handle<TriggerResults> hlTriggers;
  iEvent.getByLabel(hlTriggerResults_, hlTriggers);
  Handle<L1GlobalTriggerReadoutRecord> L1GTRR;
  Handle<L1GlobalTriggerObjectMapRecord> L1GTOMRec;
  iEvent.getByLabel(l1Trigger_, L1GTRR);
  
  // HLT
  if(hlTriggers.failedToGet()) {
    LogError("HLTriggerError") << "Failed to get trigger results - skipping this part";
  }
  else {
    TriggerNames triggerName;
    triggerName.init(*hlTriggers);
    
    unsigned short int trigpos = 0;
    const unsigned short int numTriggers = triggerName.size();
    if(debug) cout << "Number of HLTriggers: " << numTriggers << std::endl;
    for(unsigned short int trig = 0; trig < numTriggers; ++trig) {
          if(debug) cout << "trigger found at position " << trig << "with name " << triggerName.triggerName(trig) << std::endl;
	  if ( triggerName.triggerName(trig) == "HLT_PhysicsDeclared") {
	  trigpos = trig;
	  if(debug) cout << "HLT_PhysicsDeclared trigger found at position " << trigpos << std::endl;
	  }
    }
    
    if(triggerName.triggerName(trigpos) == "HLT_PhysicsDeclared") {
      bool trigAccept = hlTriggers.product()->accept(trigpos);
      if(trigAccept == true)
	{PhysicsDeclared = 1;}
      else
	{PhysicsDeclared = 0;}
    }
    else {
      if (runNumber == 1) {
      	//cout << "this is MC, don't need HLT_PhysicsDeclared" << endl;
	PhysicsDeclared = 0;
      } else {
      LogError("HLTriggerError") << "Wrong assignment of trigger postion to HLT_PhyscisDeclared";
      PhysicsDeclared = 0;
      LogError("HLTriggerError") << "Put HLT_PhyscisDeclared result to 0";
      }
      
    } // end else
  } // end trigger.failedToGet()


    // L1
    int L1TechnicalTriggers[64];
    
    for (int i=0;i<64;i++) {
    	L1TechnicalTriggers[i] = 0;
    }
  
    iEvent.getByLabel(InputTag("hltL1GtObjectMap::HLT"), L1GTOMRec);
    if (L1GTRR.isValid()) {
      DecisionWord gtDecisionWord = L1GTRR->decisionWord();
      const TechnicalTriggerWord&  technicalTriggerWordBeforeMask = L1GTRR->technicalTriggerWord();
      const unsigned int numberTechnicalTriggerBits(technicalTriggerWordBeforeMask.size());
      for (unsigned int iBit = 0; iBit < numberTechnicalTriggerBits; ++iBit) {
	int techTrigger = (int) technicalTriggerWordBeforeMask.at(iBit);
	L1TechnicalTriggers[iBit] = techTrigger;
      }
    } 
    else {
      LogError("L1Debug") << "Trigger L1 is not valid: " << L1GTRR.isValid() << " - skipping this part";
    }

    L1bit0 = L1TechnicalTriggers[0];
    L1bit36 = L1TechnicalTriggers[36];
    L1bit37 = L1TechnicalTriggers[37];
    L1bit38 = L1TechnicalTriggers[38];
    L1bit39 = L1TechnicalTriggers[39];
    L1bit40 = L1TechnicalTriggers[40];
    L1bit41 = L1TechnicalTriggers[41];
  
  
  ///////////////////
  // end Trigger part
  ///////////////////
  
  /////////////////////////
  // start central jet part
  /////////////////////////
  
  isCaloInclusive = 0;
  isCaloDijet = 0;
  nCaloJets = 0;
 
  for (int i=0;i<4;i++) { 
  	CaloJetEnergy[i] = 0;
  	CaloJetPt[i] = 0;
  	CaloJetEta[i] = 0;
  	CaloJetPhi[i] = 0;
  }
  
  isPFInclusive = 0;
  isPFDijet = 0;
  nPFJets = 0;
  
  for (int i=0;i<4;i++) { 
  	PFJetEnergy[i] = 0;
  	PFJetPt[i] = 0;
  	PFJetEta[i] = 0;
  	PFJetPhi[i] = 0;
  }
  
  // CaloJets
  
  Handle<reco::CaloJetCollection> ak5CaloJets;
  iEvent.getByLabel(caloJets_, ak5CaloJets);

  const JetCorrector* caloJetCorrector = JetCorrector::getJetCorrector(CaloJetCorrectionService,iSetup);
  
  if (ak5CaloJets.isValid()) {
  	nCaloJets = ak5CaloJets->size();
	
	CaloJetCollection correctedJets;
	// do the jet energy scale correction
	for(CaloJetCollection::const_iterator jet = ak5CaloJets->begin(); jet < ak5CaloJets->end(); ++jet) {
        	CaloJet correctedJet = *jet; // copy orignial jet
      		double scale = caloJetCorrector->correction(jet->p4());  //calculate the correction
      		correctedJet.scaleEnergy(scale); // apply correction
		//cout << "corrected jet pt = " << correctedJet.pt() << endl;
		correctedJets.push_back(correctedJet);
	}
	
	// sort on pt
	CaloJetCollection sortedJets = correctedJets;
	stable_sort(sortedJets.begin(),sortedJets.end(), PtSorter());
	
	// fill all variables
	for(int p=0;p<nCaloJets;++p) {
        	if (p<4) {
			CaloJetEnergy[p] = sortedJets[p].energy();
			CaloJetPt[p] = sortedJets[p].pt();
			CaloJetEta[p] = sortedJets[p].eta();
			CaloJetPhi[p] = sortedJets[p].phi();
		}
	}
  } else {
  	LogError("CentralJetError") << "Failed to get CaloJet collection - skipping this part";
  }
  
  /*
  for (int i=0;i<4;i++) { 
  	cout << "" << endl;
  	cout << "CaloJet energy = " << CaloJetEnergy[i] << endl;
  	cout << "CaloJet pt = " <<CaloJetPt[i] << endl;
  	cout << "CaloJet eta = " <<CaloJetEta[i] <<endl;
  	cout << "CaloJet phi = " <<CaloJetPhi[i] <<endl;
  }
  */
  
  // PFJets
  
  Handle<reco::PFJetCollection> ak5PFJets;
  iEvent.getByLabel(pfJets_, ak5PFJets);

  const JetCorrector* pfJetCorrector = JetCorrector::getJetCorrector(PFJetCorrectionService,iSetup);
  
  if (ak5PFJets.isValid()) {
  	nPFJets = ak5PFJets->size();
	
	PFJetCollection correctedJets;
	// do the jet energy scale correction
	for(PFJetCollection::const_iterator jet = ak5PFJets->begin(); jet < ak5PFJets->end(); ++jet) {
        	PFJet correctedJet = *jet; // copy orignial jet
      		double scale = pfJetCorrector->correction(jet->p4());  //calculate the correction
      		correctedJet.scaleEnergy(scale); // apply correction
		//cout << "corrected jet pt = " << correctedJet.pt() << endl;
		correctedJets.push_back(correctedJet);
	}
	
	// sort on pt
	PFJetCollection sortedJets = correctedJets;
	stable_sort(sortedJets.begin(),sortedJets.end(), PtSorter());
	
	// fill all variables
	for(int p=0;p<nPFJets;++p) {
        	if (p<4) {
			PFJetEnergy[p] = sortedJets[p].energy();
			PFJetPt[p] = sortedJets[p].pt();
			PFJetEta[p] = sortedJets[p].eta();
			PFJetPhi[p] = sortedJets[p].phi();
		}
	}
  } else {
  	LogError("CentralJetError") << "Failed to get PFJet collection - skipping this part";
  }
  
  /*
  for (int i=0;i<4;i++) { 
  	cout << "" << endl;
  	cout << "PFJet energy = " << PFJetEnergy[i] << endl;
  	cout << "PFJet pt = " <<PFJetPt[i] << endl;
  	cout << "PFJet eta = " <<PFJetEta[i] <<endl;
  	cout << "PFJet phi = " <<PFJetPhi[i] <<endl;
  }
  */
  
  
  Handle<bool> CaloDijet;
  iEvent.getByLabel("calodijetSelector","dijet", CaloDijet);
  Handle<bool> CaloInclusive;
  iEvent.getByLabel("calomonojetSelector","inclusive", CaloInclusive);
  
  if (*CaloInclusive) isCaloInclusive = 1;
  if (*CaloDijet) isCaloDijet = 1;
  
  
  Handle<bool> PFDijet;
  iEvent.getByLabel("pfdijetSelector","dijet", PFDijet);
  Handle<bool> PFInclusive;
  iEvent.getByLabel("pfmonojetSelector","inclusive", PFInclusive);
  
  if (*PFInclusive) isPFInclusive = 1;
  if (*PFDijet) isPFDijet = 1;
  
  
  
  // fill the tree
  EventTree->Fill(); 



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TreeMaker::beginJob()
{

//edm::Service<TFileService> fs;
//EventTree = fs->make<TTree>();

fOutputFile = new TFile(fOutputFileName.c_str(),"RECREATE") ;

EventTree = new TTree("CastorDigi","CastorDigi");


EventTree->Branch("ADC",ADC,"ADC[224][6]/D");
EventTree->Branch("sumADC",sumADC,"sumADC[224]/D");
EventTree->Branch("fC",fC,"fC[224][6]/D");
EventTree->Branch("sumfC",sumfC,"sumfC[224]/D");

EventTree->Branch("module",module,"module[224]/I");
EventTree->Branch("sector",sector,"sector[224]/I");
EventTree->Branch("channel",channel,"channel[224]/I");
EventTree->Branch("signal",signal,"signal[224]/D");
EventTree->Branch("fCsignal",fCsignal,"fCsignal[224]/D");
EventTree->Branch("pedestal",pedestal,"pedestal[224]/D");

EventTree->Branch("eventNum",&eventNum,"eventNum/I");
EventTree->Branch("lumiBlock",&lumiBlock,"lumiBlock/I");
EventTree->Branch("runNumber",&runNumber,"runNumber/I");
EventTree->Branch("bunchCrossing",&bunchCrossing,"bunchCrossing/I");

EventTree->Branch("PhysicsDeclared",&PhysicsDeclared,"PhysicsDeclared/I");
EventTree->Branch("L1bit0",&L1bit0,"L1bit0/I");
EventTree->Branch("L1bit36",&L1bit36,"L1bit36/I");
EventTree->Branch("L1bit37",&L1bit37,"L1bit37/I");
EventTree->Branch("L1bit38",&L1bit38,"L1bit38/I");
EventTree->Branch("L1bit39",&L1bit39,"L1bit39/I");
EventTree->Branch("L1bit40",&L1bit40,"L1bit40/I");
EventTree->Branch("L1bit41",&L1bit41,"L1bit41/I");

EventTree->Branch("nCaloJets",&nCaloJets,"nCaloJets/I");
EventTree->Branch("nPFJets",&nPFJets,"nPFJets/I");
EventTree->Branch("isCaloInclusive",&isCaloInclusive,"isCaloInclusive/I");
EventTree->Branch("isPFInclusive",&isPFInclusive,"isPFInclusive/I");
EventTree->Branch("isCaloDijet",&isCaloDijet,"isCaloDijet/I");
EventTree->Branch("isPFDijet",&isPFDijet,"isPFDijet/I");

EventTree->Branch("CaloJetEnergy",CaloJetEnergy,"CaloJetEnergy[4]/D");
EventTree->Branch("CaloJetPt",CaloJetPt,"CaloJetPt[4]/D");
EventTree->Branch("CaloJetEta",CaloJetEta,"CaloJetEta[4]/D");
EventTree->Branch("CaloJetPhi",CaloJetPhi,"CaloJetPhi[4]/D");
EventTree->Branch("PFJetEnergy",PFJetEnergy,"PFJetEnergy[4]/D");
EventTree->Branch("PFJetPt",PFJetPt,"PFJetPt[4]/D");
EventTree->Branch("PFJetEta",PFJetEta,"PFJetEta[4]/D");
EventTree->Branch("PFJetPhi",PFJetPhi,"PFJetPhi[4]/D");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeMaker::endJob() {
fOutputFile->Write() ;
fOutputFile->Close() ;
 return ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeMaker);
