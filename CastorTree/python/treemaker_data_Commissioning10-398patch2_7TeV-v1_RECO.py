
import FWCore.ParameterSet.Config as cms

# use 7TeV PFJetID cuts
from UACastor.CastorTree.TightPFJetID_Parameters7TeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters7TeV_Ref
# use general CaloJetID cuts
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2000))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
 #   # replace 'myfile.root' with the source file you want to use
#    fileNames = cms.untracked.vstring(
#              '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/3E78417C-8222-E011-90E2-00E081791891.root',
#       '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/68B2B494-8822-E011-8038-0025B3E0652A.root',
#       '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/306AE6E7-8822-E011-9707-00E08178C071.root',
#      '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/58CC84DB-8F22-E011-99C6-0015170AE6E4.root',
#      '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/DE94526A-8F22-E011-86BA-00151715C60C.root',
#      '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/928BF8A0-8F22-E011-99F5-003048D45FE6.root',
#      '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/4C4AA090-8E22-E011-A653-003048D460B6.root',
#      '/store/data/Run2010A/MinimumBias/RAW-RECO/ValSkim-Dec22Skim_v2/0139/94A5E2BD-8F22-E011-A82D-0025B3E05D44.root',
#
#        
#
#    )#,
#   lumisToProcess = cms.untracked.VLuminosityBlockRange(
#'124009:1-124009:68'
#'124020:12-124020:94',
#'124022:69-124022:160',
#'124023:41-124023:96',
#'124024:2-124024:83',
#'124027:24-124027:39',
#'124030:1-124030:31'
#)

)

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND((40 OR 41) AND NOT (36 OR 37 OR 38 OR 39))')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",applyfilter = cms.untracked.bool(True),HLTriggerResults = cms.InputTag("TriggerResults"))
				
# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# selection on the rate of high purity tracks (scraping events rejection) 
process.noscraping = cms.EDFilter("FilterOutScraping",
   applyfilter = cms.untracked.bool(True),
   debugOn = cms.untracked.bool(False),
   numtrack = cms.untracked.uint32(10),
   thresh = cms.untracked.double(0.25)
)

# communicate with the DB
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_311_V2::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_data_Commissioning10-398patch2_7TeV-v1_RECO.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.bool(False),                                 
   StoreGenPart = cms.bool(False),
   StoreCastorDigi = cms.bool(False),
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
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters7TeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(20.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV and > 20 GeV for 7 TeV
   JetEtaCut = cms.double(2.5),

   requested_hlt_bits = cms.vstring('HLT_L1Tech_BSC_minBias','HLT_L1Tech_BSC_minBias_OR')           
)

# list of processes
process.p = cms.Path(process.physDecl*process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.noscraping*process.castortree)
