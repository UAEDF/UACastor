
import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/CastorCollisionData/CastorCollisionData_MinimumBias09_RAWRECO_GoodLumiSections_1.root'
        # 'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/ochesanu/PYTHIA6_MinBias_900GeV_redigi_1.root',
         'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/ochesanu/PYTHIA6_MinBias_900GeV_redigi_2.root',
        # 'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/ochesanu/PYTHIA6_MinBias_900GeV_redigi_3.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/ochesanu/MonteCarloProduction/900/pythia6D/TPYTHIA6_MinBias_900GeV_redigi_2.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_3.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_4.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_5.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/ochesanu/MonteCarloProduction/900/pythia6D/TPYTHIA6_MinBias_900GeV_redigi_6.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_7.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_8.root',
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/PYTHIA6_MinBias_900GeV_redigi_9.root',
    )
)

process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.GlobalTag.globaltag = 'START3X_V22A::All'


# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('40 OR 41')

# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)



process.load("JetMETCorrections.Configuration.L2L3Corrections_900GeV_cff")

process.calomonojetSelector = cms.EDProducer('CentralMonoCaloJetProducer',
    CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    CaloJets = cms.InputTag('ak5CaloJets', '', 'RECO'),
    CaloJetId = cms.InputTag('ak5JetID', '', 'RECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RECO')
)

process.calodijetSelector = cms.EDProducer('CentralDiCaloJetProducer',
    CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    CaloJets = cms.InputTag('ak5CaloJets', '', 'RECO'),
    CaloJetId = cms.InputTag('ak5JetID', '', 'RECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RECO')
) 

process.pfmonojetSelector = cms.EDProducer('CentralMonoPFJetProducer',
    PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RECO')
)
           
process.pfdijetSelector = cms.EDProducer('CentralDiPFJetProducer',
    PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
    HLTriggerResults = cms.InputTag('TriggerResults', '', 'HLT' ),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    Vertices = cms.InputTag('offlinePrimaryVertices', '', 'RECO'),
    L1Trigger = cms.InputTag('gtDigis', '', 'RECO')
)

process.treemaker = cms.EDAnalyzer('TreeMaker',
      OutputFileName = cms.string("TreeMaker_MCApril8_MinBias900GeV_2.root"),
      CaloJetCorrector = cms.string('L2L3JetCorrectorAK5Calo'),
      PFJetCorrector = cms.string('L2L3JetCorrectorAK5PF'),
      HLTriggerResults = cms.InputTag( 'TriggerResults','','HLT' ),
      CaloJets = cms.InputTag('ak5CaloJets', '', 'RECO'),
      PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
      L1Trigger = cms.InputTag('gtDigis', '', 'RECO'),
      CastorDigis = cms.InputTag('simCastorDigis', '', 'CastorREDIGI'),
      HepMCColl = cms.InputTag('generator','','HLT'),
      PrimaryVertexColl = cms.InputTag('offlinePrimaryVertices','','RERECO'),
      BeamSpot = cms.InputTag('offlineBeamSpot','','RERECO'),
      GenPartColl = cms.InputTag('genParticles','','HLT')
)

process.TFileService = cms.Service("TFileService",
   fileName = cms.string("CentralJetFilters_MCApril8_MinBias900GeV_2.root")
)


process.p = cms.Path(process.hltLevel1GTSeed*process.oneGoodVertexFilter*(process.calomonojetSelector+process.calodijetSelector+process.pfmonojetSelector+process.pfdijetSelector)*process.treemaker)
