
import FWCore.ParameterSet.Config as cms

from UACastor.CastorTree.TightPFJetID_Parameters_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters_Ref
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(2000))
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

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
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# communicate with the DB
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START310_V3::All'

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# I guess I should not use this old staff
# process.load("JetMETCorrections.Configuration.L2L3Corrections_900GeV_cff")

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("Castor_900GeV_moca.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.untracked.bool(True),
   StoreGenPart= cms.untracked.bool(True),                                 
   StoreCastorDigi = cms.untracked.bool(True),
   StoreCastorJet = cms.untracked.bool(True),

   # input tag for L1GtTriggerMenuLite retrieved from provenance
   L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),

   L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),                                 
                                    
   hepMCColl = cms.InputTag('generator','','HLT'),
   genPartColl = cms.InputTag('genParticles','','HLT'),

   CastorTowerColl = cms.InputTag('CastorTowerReco', '','Analysis'),
   CastorDigiColl = cms.InputTag('simCastorDigis', '', 'HLT'),
   CastorRecHitColl = cms.InputTag('castorreco','','RECO'),
   BasicJet = cms.InputTag('ak7BasicJets','','RECO'),
   CastorJetID = cms.InputTag('ak7CastorJetID','','RECO'),

   PFJetColl = cms.InputTag('ak5PFJets','','RECO'),
   PFJetJEC = cms.string('ak5PFL2L3'), # L2L3Residual JEC should be applied to data only, here moca                                 
   PFJetJECunc = cms.string('AK5PF'),

   CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
   CaloJetId = cms.InputTag('ak5JetID','','RECO'),
   CaloJetJEC = cms.string('ak5CaloL2L3'), # L2L3Residual JEC should be applied to data only, here moca
   CaloJetJECunc = cms.string('AK5Calo'),

   CaloTowerColl = cms.InputTag('towerMaker','','RECO'),

   TightPFJetID_Parameters = TightPFJetID_Parameters_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,                                    
   JetPtCut = cms.double(8.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV
   JetEtaCut = cms.double(2.5)

   //c requested_hlt_bits                                  
)

# list of processes
process.p = cms.Path(process.hltLevel1GTSeed*process.oneGoodVertexFilter*(process.pfinclusivejetSelector+process.pfdijetSelector)*process.castortree)
