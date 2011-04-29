
import FWCore.ParameterSet.Config as cms

# use 900GeV PF jet ID parameters
from UACastor.CastorTree.TightPFJetID_Parameters900GeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters900GeV_Ref
# use general CaloJet ID parameters
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(70000))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_9_1_VIc.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_8_1_vQC.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_7_1_vLv.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_6_1_Vap.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_5_1_C2G.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_4_1_CF8.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_3_1_eJX.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_2_1_VAJ.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_25_1_B4D.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_24_1_vng.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_23_1_0SC.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_22_1_1cc.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_21_1_A6W.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_20_1_zmb.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_1_1_15a.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_19_1_aUr.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_18_1_mlR.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_17_1_OBj.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_16_1_cIz.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_15_1_hBG.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_14_1_0Ac.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_13_1_bif.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_12_1_YCu.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_11_1_Jzq.root',
        '/store/user/hvanhaev/Step1_MinBias900GeV_PythiaD6T_3100_Default_v1_250k_1/Step2_MinBias900GeV_PythiaD6T_3100_Default_v1/c59872a80d9c75ba35d2cfada57d4e34/Step2_MinBias900GeV_PythiaD6T_3100_Default_10_1_uyT.root'
        

    ))

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('40 OR 41')
			
# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)


# communicate with the DB
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START311_V2::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.load("Configuration.StandardSequences.RawToDigi_cff")

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_MC_900GeV_3100_Default.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.bool(True),                                 
   StoreGenPart = cms.bool(True),
   StoreCastorDigi = cms.bool(True),
   StoreCastorJet = cms.bool(True),                                

   # input tag for L1GtTriggerMenuLite retrieved from provenance
   L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),
  
   L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),
                                               
   hepMCColl = cms.InputTag('generator','','HLT'),
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

   CaloTowerColl = cms.InputTag('towerMaker','','RECO'),
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters900GeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(8.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV
   JetEtaCut = cms.double(2.5),

   requested_hlt_bits = cms.vstring('')           
)

# list of processes
process.p = cms.Path(process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.castortree)
