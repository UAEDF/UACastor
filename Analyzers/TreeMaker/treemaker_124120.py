
import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/CastorCollisionData/CastorCollisionData_MinimumBias09_RAWRECO_GoodLumiSections_1.root'
               '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/7CB0BA85-F809-DF11-9521-002618943962.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/FA76C909-B809-DF11-BDB3-002618943970.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/A05A600B-B409-DF11-81C2-00261894397D.root'
    ),
   lumisToProcess = cms.untracked.VLuminosityBlockRange(
#'124009:1-124009:68'
#'124020:12-124020:94'
#'124022:69-124022:160'
#'124023:41-124023:96'
#'124024:2-124024:83'
#'124027:24-124027:39'
#'124030:1-124030:31'
'124120:1-124120:9999'
)

)

process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND((40 OR 41) AND NOT (36 OR 37 OR 38 OR 39))')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",
                                applyfilter = cms.untracked.bool(True)
                                )
				
# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)



#process.load("EventFilter.CastorRawToDigi.CastorRawToDigi_cff")
#CastorDbProducer = cms.ESProducer("CastorDbProducer")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.GlobalTag.globaltag = 'GR09_R_35X_V1::All'
process.castorDigis.InputLabel = 'source'

process.TFileService = cms.Service("TFileService",
   fileName = cms.string("CentralJetFilters_Jan23RawReco_Run124120.root")
)


# Jet Corrections
process.load("JetMETCorrections.Configuration.L2L3Corrections_2360GeV_cff")

process.noscraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.calomonojetSelector = cms.EDProducer('CentralMonoCaloJetProducer',
    CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    CaloJets = cms.InputTag('ak5CaloJets', '', 'RERECO'),
    CaloJetId = cms.InputTag('ak5JetID', '', 'RERECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RERECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RERECO')
)

process.calodijetSelector = cms.EDProducer('CentralDiCaloJetProducer',
    CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    CaloJets = cms.InputTag('ak5CaloJets', '', 'RERECO'),
    CaloJetId = cms.InputTag('ak5JetID', '', 'RERECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RERECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RERECO')
) 

process.pfmonojetSelector = cms.EDProducer('CentralMonoPFJetProducer',
    PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RERECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RERECO')
)
           
process.pfdijetSelector = cms.EDProducer('CentralDiPFJetProducer',
    PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RERECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RERECO')
)


process.treemaker = cms.EDAnalyzer('TreeMaker',
      OutputFileName = cms.string("TreeMaker_Jan23RawReco_Run124120.root"),
      CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
      PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
      HLTriggerResults = cms.InputTag( 'TriggerResults','','HLT' ),
      CaloJets = cms.InputTag('ak5CaloJets', '', 'RERECO'),
      PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),
      L1Trigger = cms.InputTag('gtDigis', '', 'RERECO'),
      CastorDigis = cms.InputTag('castorDigis', '', 'TreeMaker')
)


process.p = cms.Path(process.physDecl*process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.noscraping*process.castorDigis*(process.calomonojetSelector+process.calodijetSelector+process.pfmonojetSelector+process.pfdijetSelector)*process.treemaker)
