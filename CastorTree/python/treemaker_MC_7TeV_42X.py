
import FWCore.ParameterSet.Config as cms

# use 7TeV PFJetID cuts
from UACastor.CastorTree.TightPFJetID_Parameters7TeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters7TeV_Ref
# use general CaloJetID cuts
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(5000))
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
 

'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_10_1_hsD.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_14_1_62I.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_2_1_Cju.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_6_1_6UA.root',
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_11_1_CfW.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_15_1_zwZ.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_3_1_7Dp.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_7_1_Q7e.root',
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_12_1_Ny3.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_16_1_CkH.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_4_1_BVo.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_8_1_EFd.root',
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_13_1_Nwn.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_1_1_fRJ.root',   
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_5_1_5jx.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_onlyEM_v1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_onlyEM_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_9_1_m8w.root',
    ))

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",applyfilter = cms.untracked.bool(True),HLTriggerResults = cms.InputTag("TriggerResults"))

# communicate with the DB
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V11::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.load("Configuration.StandardSequences.RawToDigi_cff")

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_MC_7TeV_42X_Pythia6_D6T_onlyEM.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.bool(True),                                 
   StoreGenPart = cms.bool(True),
   StoreGenJet = cms.bool(True),                                    
   StoreCastorDigi = cms.bool(False),
   StoreCastorJet = cms.bool(True),                                

   # input tag for L1GtTriggerMenuLite retrieved from provenance
   L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),
  
   L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),
                                               
   hepMCColl = cms.InputTag('generator','','SIM'),
   genPartColl = cms.InputTag('genParticles','','HLT'),
   
   CastorTowerColl = cms.InputTag('CastorTowerReco', '','RECO'),                                 
   CastorDigiColl = cms.InputTag('castorDigis', '','RECO'),
   CastorRecHitColl = cms.InputTag('castorreco','','RECO'),
   BasicJet = cms.InputTag('ak7BasicJets','','RECO'),  
   CastorJetID = cms.InputTag('ak7CastorJetID','','RECO'), 

   PFJetColl = cms.InputTag('ak5PFJets', '', 'RECO'),
   PFJetJEC = cms.string('ak5PFL2L3Residual'),    # L2L3Residual JEC should be applied to data only
   PFJetJECunc = cms.string('AK5PF'),
                                    
   CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
   CaloJetId = cms.InputTag('ak5JetID','','RECO'),
   CaloJetJEC = cms.string('ak5CaloL2L3Residual'), # L2L3Residual JEC should be applied to data only 
   CaloJetJECunc = cms.string('AK5Calo'),

   GenJetColl = cms.InputTag('ak5GenJets','','HLT'),
                                    
   CaloTowerColl = cms.InputTag('towerMaker','','RECO'),
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters7TeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(8.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV
   JetEtaCut = cms.double(2.5),

   FilterResults = cms.InputTag('TriggerResults','','Analysis'),
   requested_hlt_bits = cms.vstring(''),
   requested_filter_bits = cms.vstring('physDeclpath')          
)

# list of processes
process.physDeclpath = cms.Path(process.physDecl)

process.tree = cms.EndPath(process.castortree)

