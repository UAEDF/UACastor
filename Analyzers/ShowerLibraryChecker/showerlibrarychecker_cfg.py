
import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
	duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       
'file:../../../../CMSSW_3_7_0/src/SimG4CMS/ShowerLibraryProducer/test/python/CastorSim_GEN-SIM_PGun_Pion20-30GeV_SL_10000events_withSL1-30ME.root'
#'file:../../../../CMSSW_3_7_0/src/testSL/goodcfg/pions/CastorSim_GEN-SIM_PGun_Pion20-50GeV_FullSim_2800.root'
    )
)

process.demo = cms.EDAnalyzer('ShowerLibraryChecker'
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('./goodfiles/SLTree_Pion20-30GeV_SL_10000_withSL1-30ME.root')
)

process.p = cms.Path(process.demo)
