
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
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/hvanhaev/CastorCollisionData/CastorCollisionData_MinimumBias09_RAWRECO_GoodLumiSections_1.root'
                '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/144C9D9C-F809-DF11-A127-0026189438C2.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/F6FBE10D-B609-DF11-B3DD-0026189438B9.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/9AB142AB-B309-DF11-9DD8-002618943984.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/A24C858F-F809-DF11-951D-0026189438F4.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/C2E8DF18-B809-DF11-B546-0026189438D2.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/F08301C3-B409-DF11-82B9-002618943821.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/E2E7CEA4-B409-DF11-BA24-002618943943.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/C2D05EA0-B509-DF11-9768-002618943971.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/B2368A0A-B609-DF11-8780-002618943858.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/A42C8652-B209-DF11-AF33-00261894397D.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/9EA31688-F809-DF11-9920-002618B27F8A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/B6578F54-BA09-DF11-9391-002618943933.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/76524E2C-B909-DF11-B97B-0026189438F5.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/D4EE6FA2-B309-DF11-A93C-00261894389A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/9608FC29-B509-DF11-BC3C-002618943958.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/88891A4B-B709-DF11-A232-00261894388B.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/3C59BF00-B609-DF11-9766-002618943885.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/3268AC4D-B309-DF11-87EA-00261894389E.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/2E097909-B609-DF11-9F75-0026189438DA.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/1404784B-B709-DF11-8597-00261894382A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/0E1D25C5-B409-DF11-A1C0-00261894392B.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/0A34CEA5-B309-DF11-8F8F-0026189438BA.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/065A0459-B709-DF11-81BD-00261894398A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/92E7B756-BA09-DF11-A33A-00261894397D.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/56E8961E-B809-DF11-A90C-00261894389F.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/D6A66F04-B609-DF11-95E5-002618943876.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/C2B5A330-B509-DF11-B804-002618943870.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/B6155EC3-B409-DF11-BACA-00261894396A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/8234EE0A-B609-DF11-9FB1-002618943947.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/7874B64B-B309-DF11-801D-00261894393C.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/4A0228C4-B409-DF11-A4C6-002618943916.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/3E3309A6-B309-DF11-9F6B-002618943951.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/B2E13698-F809-DF11-BF76-002618943966.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/BCBB4746-BA09-DF11-B0E9-0026189438BA.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/A83F444B-B709-DF11-80B5-002618943856.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/9290C6E5-B409-DF11-8C68-002618943865.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/8E3A4501-B609-DF11-B804-002618943964.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/8A743BE8-B609-DF11-B300-00261894386A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/324A45ED-B609-DF11-B52B-0026189438DC.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/462518A3-F809-DF11-B40F-002618B27F8A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/5CD48032-B909-DF11-8094-002618943811.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/54F6FB25-B809-DF11-9E97-0026189437FC.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/EA0A909F-B409-DF11-93C2-00261894391D.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/C4E6B6EA-B409-DF11-87D8-0026189438D8.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/BAA00BB4-B409-DF11-B80F-0026189438E3.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/A897DB5B-B209-DF11-8EA5-002618943976.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/88DD9CA0-B309-DF11-A761-002618943916.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/66386C09-B609-DF11-BB59-00261894384F.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/3E4316E5-B609-DF11-8D15-002618943981.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/30BC4717-B109-DF11-9D25-002618943821.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/307DF94A-B009-DF11-82F4-00261894397A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/02635E00-B609-DF11-ADB6-0026189438A9.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/007657A1-B509-DF11-AAAB-00261894396A.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0015/5A962FA7-F809-DF11-93A7-0026189438BF.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0014/98A7C34B-B709-DF11-93CA-002618943838.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/9EC45AA2-B509-DF11-960E-00261894392B.root',
        '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/BSCNOBEAMHALO-Jan23Skim-v1/0013/78D1C2EF-B409-DF11-8A74-002618943921.root'

    ),
   lumisToProcess = cms.untracked.VLuminosityBlockRange(
'124009:1-124009:68'
#'124020:12-124020:94',
#'124022:69-124022:160',
#'124023:41-124023:96',
#'124024:2-124024:83',
#'124027:24-124027:39',
#'124030:1-124030:31'
)

)

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# configure HLT
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND((40 OR 41) AND NOT (36 OR 37 OR 38 OR 39))')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",applyfilter = cms.untracked.bool(True))
				
# require primary vertex
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
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
process.GlobalTag.globaltag = 'GR_R_310_V2::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# I guess I should not use this old staff
# process.load("JetMETCorrections.Configuration.L2L3Corrections_900GeV_cff")

# data reconstruction starts from raw
process.load("Configuration.StandardSequences.RawToDigi_cff")         //-- redo digi from raw data (digi not kept)
process.load("Configuration.StandardSequences.Reconstruction_cff")    //-- redo rechit

process.castorDigis.InputLabel = 'source'

process.load("RecoLocalCalo.Castor.CastorCellReco_cfi")    //-- redo cell
process.load("RecoLocalCalo.Castor.CastorTowerReco_cfi")   //-- redo tower
process.load("RecoJets.JetProducers.ak7CastorJets_cfi")    //-- redo jet  
process.load("RecoJets.JetProducers.ak7CastorJetID_cfi")   //-- redo jetid

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("Castor_900GeV_data_124009.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.untracked.bool(True),                                 
   StoreGenPart = cms.untracked.bool(True),
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
   CastorDigiColl = cms.InputTag('castorDigis', '','Analysis'),
   CastorRecHitColl = cms.InputTag('castorreco','','Analysis'),
   BasicJet = cms.InputTag('ak7BasicJets','','Analysis'),  
   CastorJetID = cms.InputTag('ak7CastorJetID','','Analysis'), 

   PFJetColl = cms.InputTag('ak5PFJets', '', 'RECO'),
   PFJetJEC = cms.string('ak5PFL2L3Residual'),    # L2L3Residual JEC should be applied to data only
   PFJetJECunc = cms.string('AK5PF'),
                                    
   CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
   CaloJetId = cms.InputTag('ak5JetID','','RECO'),
   CaloJetJEC = cms.string('ak5CaloL2L3Residual'), # L2L3Residual JEC should be applied to data only 
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
process.p = cms.Path(process.physDecl*process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.noscraping
                     *process.castorDigis*process.castorreco*process.CastorCellReco*process.CastorTowerReco*process.ak7BasicJets*process.ak7CastorJetID
                     *(process.pfinclusivejetSelector+process.pfdijetSelector)*process.castortree)
