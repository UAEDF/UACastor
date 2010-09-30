import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
              
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource")

# magnetic field configuration
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# HLT configuration
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND((40 OR 41) AND NOT (36 OR 37 OR 38 OR 39))')

# physics declared requirement
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'
				
# primary vertex requirement
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# GT - RawToDigi - Castor Digi
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.GlobalTag.globaltag = 'GR10_P_V4::All'
process.castorDigis.InputLabel = 'source'

process.TFileService = cms.Service("TFileService",fileName = cms.string("TreeMaker_7TeV_MinimumBias_Commissioning10-GOODCOLL-v8_132599.root"))

# scraping events rejection
process.noscraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25))

# PFJet Dijet Selection
process.pfdijetSelector7TeV = cms.EDProducer('CentralDiPFJetProducer7TeV',
    PFJetCorrector = cms.string('ak5PFL2L3'),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    NHFCutUp = cms.double(0.9),
    NEFCutUp = cms.double(0.9),
    CHFCutLow = cms.double(0.0),
    CEFCutUp = cms.double(1.0),
    NumConstituentsCutLow = cms.int32(0),
    ChargedMultiplicityCutLow = cms.int32(0),
    JetPtCut = cms.double(5),
    JetEtaCut = cms.double(2.5))

# PFJet Inclusive Selection
process.pfmonojetSelector7TeV = cms.EDProducer('CentralMonoPFJetProducer7TeV',
    PFJetCorrector = cms.string('ak5PFL2L3'),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    NHFCutUp = cms.double(0.9),
    NEFCutUp = cms.double(0.9),
    CHFCutLow = cms.double(0.0),
    CEFCutUp = cms.double(1.0),
    NumConstituentsCutLow = cms.int32(0),
    ChargedMultiplicityCutLow = cms.int32(0),
    JetPtCut = cms.double(5),
    JetEtaCut = cms.double(2.5))

# final tree
process.treemaker7TeV = cms.EDAnalyzer('TreeMaker7TeV',
      PFJetCorrector = cms.string('ak5PFL2L3'),
      HLTriggerResults = cms.InputTag('TriggerResults','','HLT'),
      PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
      L1Trigger = cms.InputTag('gtDigis', '', 'RECO'),
      CastorDigis = cms.InputTag('castorDigis', '', 'TreeMaker'),
      HepMCColl = cms.InputTag('generator','','HLT'),
      PrimaryVertexColl = cms.InputTag('offlinePrimaryVertices','','RECO'),
      BeamSpot = cms.InputTag('offlineBeamSpot','','RECO'),
      GenPartColl = cms.InputTag('genParticles','','HLT'))

process.p = cms.Path(process.hltPhysicsDeclared*process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.noscraping*process.castorDigis*(process.pfmonojetSelector7TeV+process.pfdijetSelector7TeV)*process.treemaker7TeV)

