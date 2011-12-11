import FWCore.ParameterSet.Config as cms

# use 7TeV PFJetID cuts
from UACastor.CastorTree.TightPFJetID_Parameters7TeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters7TeV_Ref
# use general CaloJetID cuts
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(20000))
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
    # take json from grid
    )
)

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",applyfilter = cms.untracked.bool(True),HLTriggerResults = cms.InputTag("TriggerResults"))

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
process.GlobalTag.globaltag = 'GR_R_42_V20::All' 

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

# import Castor tower and jet reconstruction
process.load('RecoLocalCalo.Castor.Castor_cff')

# construct the module which executes the RechitCorrector for data reconstructed in releases>= 4.2.X
process.rechitcorrector = cms.EDProducer("RecHitCorrector",
       rechitLabel = cms.InputTag("castorreco","","RECO"), # choose the original RecHit collection
       revertFactor = cms.double(1), # this is the factor to go back to the original fC - not needed when data is already intercalibrated
       doInterCalib = cms.bool(False) # don't do intercalibration, RecHitCorrector will only correct the EM response and remove BAD channels
)

# tell to the CastorTower reconstruction that he should use the new corrected rechits
process.CastorTowerReco.inputprocess = "rechitcorrector"

process.castorInvalidDataFilter = cms.EDFilter("CastorInvalidDataFilter")

#  track jet
process.load('UACastor.CastorTree.UEAnalysisTracks_cfi')
process.load('UACastor.CastorTree.UEAnalysisJetsAntiKt_cfi')
process.load("QCDAnalysis.UEAnalysis.UEAnalysisParticles_cfi")

#print "DzTrVtxMax = ",process.SisCone5TracksJet500.DzTrVtxMax
#print "DxyTrVtxMax = ",process.SisCone5TracksJet500.DxyTrVtxMax

process.ak5TrackJets500.DzTrVtxMax = cms.double(1000)
process.ak5TrackJets500.DxyTrVtxMax = cms.double(1000)
process.chargeParticles.cut = cms.string('charge != 0 & pt > 0.5 & status = 1')

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_data_MinBias_Commissioning10-May19ReReco-v1_7TeV_RECOwithCorrector.root"))

# Event Reconstruction 
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.bool(False),                                 
   StoreGenPart = cms.bool(False),
   StoreGenJet = cms.bool(False),
   StoreCastorDigi = cms.bool(False),
   StoreCastorJet = cms.bool(True),                                

   # input tag for L1GtTriggerMenuLite retrieved from provenance
   L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),
  
   L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),
                                               
   hepMCColl = cms.InputTag('generator','','HLT'),
   genPartColl = cms.InputTag('genParticles','','HLT'),
   
   CastorTowerColl = cms.InputTag('CastorTowerReco', '','Analysis'),                                 
   CastorDigiColl = cms.InputTag('castorDigis', '','RECO'),
   CastorRecHitColl = cms.InputTag('rechitcorrector','','Analysis'),
   BasicJet = cms.InputTag('ak7BasicJets','','Analysis'),  
   CastorJetID = cms.InputTag('ak7CastorJetID','','Analysis'), 

   PFJetColl = cms.InputTag('ak5PFJets', '', 'RECO'),
   PFJetJEC = cms.string('ak5PFL2L3Residual'),    # L2L3Residual JEC should be applied to data only
   PFJetJECunc = cms.string('AK5PF'),
                                    
   CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
   CaloJetId = cms.InputTag('ak5JetID','','RECO'),
   CaloJetJEC = cms.string('ak5CaloL2L3Residual'), # L2L3Residual JEC should be applied to data only 
   CaloJetJECunc = cms.string('AK5Calo'),

   GenJetColl = cms.InputTag('ak5GenJets','','HLT'),
                                    
   TrackJetColl = cms.InputTag('ak5TrackJets500'),
   TrackJetJEC = cms.string('ak5TrackL2L3Residual'),    # L2L3Residual JEC should be applied to data only
   TrackJetJECunc = cms.string('AK5JPT'),
      
   ChargedGenJetColl = cms.InputTag('ak5ChgGenJets500'),                                 
                                    
   CaloTowerColl = cms.InputTag('towerMaker','','RECO'),
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters7TeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(8.0), 
   JetEtaCut = cms.double(2.5),

   FilterResults = cms.InputTag('TriggerResults','','Analysis'),
   requested_hlt_bits = cms.vstring('HLT_L1Tech_BSC_halo_forPhysicsBackground','HLT_L1_BptxXOR_BscMinBiasOR','HLT_L1_BscMinBiasOR_BptxPlusORMinus','HLT_MinBiasBSC','HLT_MinBiasBSC_NoBPTX'),
   requested_filter_bits = cms.vstring('physDeclpath','noscrapingpath','castorInvalidDataFilterpath')           
)

# list of processes
process.physDeclpath = cms.Path(process.physDecl)
process.noscrapingpath = cms.Path(process.noscraping)
process.castorInvalidDataFilterpath = cms.Path(process.castorInvalidDataFilter)
process.recotrackjet = cms.Path(process.UEAnalysisTracks*process.ak5TrackJets500)
process.recopath = cms.Path(process.rechitcorrector*process.CastorFullReco)
process.tree = cms.EndPath(process.castortree)
