
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
    
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_10_1_JEu.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_11_1_3lB.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_1_1_XaV.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_12_1_P8i.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_13_1_Pmo.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_14_1_GRA.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_15_1_PwV.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_16_1_sdJ.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_17_1_YYL.root',
    '/store/user/roland/MinBias_TuneD6T_7TeV_pythia6_cff_py_GEN_SIM_START311_V2_goodbeamspot_step1/MinBias_TuneD6T_7TeV_pythia6_cff_py_Step3_START42_V11_step3/8d8cbcc1587a8af4059aaf45490c7623/STEP2_RAW2DIGI_L1Reco_RECO_18_1_bmd.root',
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

# track jet
process.load('UACastor.CastorTree.UEAnalysisTracks_cfi')
process.load('UACastor.CastorTree.UEAnalysisJetsSISCone_cfi')
process.load("QCDAnalysis.UEAnalysis.UEAnalysisParticles_cfi")

#print "DzTrVtxMax = ",process.SisCone5TracksJet500.DzTrVtxMax
#print "DxyTrVtxMax = ",process.SisCone5TracksJet500.DxyTrVtxMax

process.SisCone5TracksJet500.DzTrVtxMax = cms.double(1000)
process.SisCone5TracksJet500.DxyTrVtxMax = cms.double(1000)
process.chargeParticles.cut = cms.string('charge != 0 & pt > 0.5 & status = 1')

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_MC_7TeV_42X_Pythia6_D6T_beamtilt.root"))

# Event Reconstruction 
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

   TrackJetColl = cms.InputTag('SisCone5TracksJet500'),
   ChargedGenJetColl = cms.InputTag('SisCone5ChgGenJet500'),
                                    
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
process.recotrackjet = cms.Path(process.UEAnalysisTracks*process.SisCone5TracksJet500)
process.chargedgenjet = cms.Path(process.UEAnalysisParticles*process.SisCone5ChgGenJet500)
process.tree = cms.EndPath(process.castortree)

