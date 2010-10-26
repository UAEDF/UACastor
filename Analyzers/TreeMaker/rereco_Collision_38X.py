# Auto generated configuration file
# using: 
# Revision: 1.222 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: reco -s RAW2DIGI,L1Reco,RECO --data --magField AutoFromDBCurrent --scenario pp --datatier RECO --eventcontent RECO --customise Configuration/GlobalRuns/reco_TLR_38X.py --cust_function customisePPData --python_filename=rereco_Collision_38X.py --conditions auto:com10 --process RERECO --filein dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/roland/MinimumBias/Run2010B-v1/RAW/04FE5838-08C9-DF11-B14D-000423D9890C.root -n 1000 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RERECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.222 $'),
    annotation = cms.untracked.string('reco nevts:1000'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(1000)
     input = cms.untracked.int32(200)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('dcap://maite.iihe.ac.be/pnfs/iihe/cms/store/user/roland/MinimumBias/Run2010B-v1/RAW/04FE5838-08C9-DF11-B14D-000423D9890C.root'),
    lumisToProcess = cms.untracked.VLuminosityBlockRange('146644:1034-146644:2179')
)

# selection on the rate of high purity tracks (scraping events rejection)
process.noscraping = cms.EDFilter("FilterOutScraping",
       applyfilter = cms.untracked.bool(True),
       debugOn = cms.untracked.bool(False),
       numtrack = cms.untracked.uint32(10),
       thresh = cms.untracked.double(0.25))

# good primary vertex selection
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 24 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
    filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
  )


# Trigger
import copy
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = copy.deepcopy(hltHighLevel)
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltFilter.HLTPaths = ['HLT_L1Tech_BSC_minBias','HLT_L1Tech_BSC_minBias_OR','HLT_MinBiasPixel_SingleTrack','HLT_ZeroBias','HLT_ZeroBiasPixel_SingleTrack']
process.hltFilter.throw = cms.bool(False) # it won't crash if one of the triggers is missing

# Jet Selection
# process.TFileService = cms.Service("TFileService",fileName = cms.string("rereco_Central_Jet.root"))

# Disable the use of CondDB in your configuration file (during the transition period, the txt files are still in CVS)
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False

# PFJet Dijet Selection
process.pfdijetSelector7TeV = cms.EDProducer('CentralDiPFJetProducer7TeV',
                                             DoTree = cms.untracked.bool(False),
                                             PFJetCorrector = cms.string('ak5PFL2L3'),
                                             PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),
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
                                               DoTree = cms.untracked.bool(False),
                                               PFJetCorrector = cms.string('ak5PFL2L3'),
                                               PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),
                                               NHFCutUp = cms.double(0.9),
                                               NEFCutUp = cms.double(0.9),
                                               CHFCutLow = cms.double(0.0),
                                               CEFCutUp = cms.double(1.0),
                                               NumConstituentsCutLow = cms.int32(0),
                                               ChargedMultiplicityCutLow = cms.int32(0),
                                               JetPtCut = cms.double(5),
                                               JetEtaCut = cms.double(2.5))

# GT - RawToDigi - Castor Digi
process.castorDigis.InputLabel = 'source'

# final tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("rereco_CASTOR_Central_Jet.root"))

process.treemaker7TeVRun2010 = cms.EDAnalyzer('TreeMaker7TeVRun2010',
     L1Trigger = cms.InputTag('gtDigis', '', 'RERECO'),
     HLTriggerResults = cms.InputTag('TriggerResults','','HLT'),
     HLTMenuLabel = cms.string('HLT'),                       
                                              
     PFJetCorrector = cms.string('ak5PFL2L3'),
     PFJets = cms.InputTag('ak5PFJets', '', 'RERECO'),

     CastorDigis = cms.InputTag('castorDigis', '', 'RERECO'),
     PrimaryVertexColl = cms.InputTag('offlinePrimaryVertices','','RERECO'),
     BeamSpot = cms.InputTag('offlineBeamSpot','','RERECO'),

     HepMCColl = cms.InputTag('generator','','HLT'),
     GenPartColl = cms.InputTag('genParticles','','HLT'),

     Grid = cms.untracked.bool(False),
     CentralInfo = cms.untracked.bool(False),
     TriggerInfo = cms.untracked.bool(True),                                         
     MCInfo = cms.untracked.bool(False)
)

# Output definition
process.RECOoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('rereco_RAW2DIGI_L1Reco_RECO.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('RECO')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'GR_R_38X_V13::All'

# Path and EndPath definitions
#process.raw2digi_step = cms.Path(process.RawToDigi)
#process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstruction)
#process.endjob_step = cms.Path(process.endOfProcess)
#process.RECOoutput_step = cms.EndPath(process.RECOoutput)

# Schedule definition

#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOoutput_step)


process.p = cms.Path(process.RawToDigi*process.L1Reco*process.reconstruction*
                     process.hltFilter*process.oneGoodVertexFilter*process.noscraping*
                     process.pfdijetSelector7TeV*process.pfmonojetSelector7TeV*
                     process.endOfProcess*process.treemaker7TeVRun2010)
                   # process.endOfProcess*process.RECOoutput)


# Automatic addition of the customisation function

def customiseCommon(process):
    
    #####################################################################################################
    ####
    ####  Top level replaces for handling strange scenarios of early collisions
    ####

    ## TRACKING:
    ## Skip events with HV off
    process.newSeedFromTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
    process.newSeedFromPairs.ClusterCheckPSet.MaxNumberOfCosmicClusters=20000
    process.secTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
    process.fifthSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters = 20000
    process.fourthPLSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters=20000
    process.thTripletsA.ClusterCheckPSet.MaxNumberOfPixelClusters = 5000
    process.thTripletsB.ClusterCheckPSet.MaxNumberOfPixelClusters = 5000

    ###### FIXES TRIPLETS FOR LARGE BS DISPLACEMENT ######

    ### prevent bias in pixel vertex
    process.pixelVertices.useBeamConstraint = False
    
    ### pixelTracks
    #---- new parameters ----
    process.pixelTracks.RegionFactoryPSet.RegionPSet.nSigmaZ  = 4.06
    process.pixelTracks.RegionFactoryPSet.RegionPSet.originHalfLength = cms.double(40.6)

    ### 0th step of iterative tracking
    #---- new parameters ----
    process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ   = cms.double(4.06)  
    process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.originHalfLength = 40.6

    ### 2nd step of iterative tracking
    #---- new parameters ----
    process.secTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.47)  
    process.secTriplets.RegionFactoryPSet.RegionPSet.originHalfLength = 44.7

    ## ECAL 
    process.ecalRecHit.ChannelStatusToBeExcluded = [ 1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 14, 78, 142 ]

    ###
    ###  end of top level replacements
    ###
    ###############################################################################################

    return (process)


##############################################################################
def customisePPData(process):
    process= customiseCommon(process)

    ## particle flow HF cleaning
    process.particleFlowRecHitHCAL.LongShortFibre_Cut = 30.
    process.particleFlowRecHitHCAL.ApplyPulseDPG = True

    ## HF cleaning for data only
    process.hcalRecAlgos.SeverityLevels[3].RecHitFlags.remove("HFDigiTime")
    process.hcalRecAlgos.SeverityLevels[4].RecHitFlags.append("HFDigiTime")

    ##beam-halo-id for data only
    process.CSCHaloData.ExpectedBX = cms.int32(3)

    ## hcal hit flagging
    process.hfreco.PETstat.flagsToSkip  = 2
    process.hfreco.S8S1stat.flagsToSkip = 18
    process.hfreco.S9S1stat.flagsToSkip = 26
    
    return process


##############################################################################
def customisePPMC(process):
    process=customiseCommon(process)
    
    return process

##############################################################################
def customiseCosmicData(process):

    return process

##############################################################################
def customiseCosmicMC(process):
    
    return process
        
##############################################################################
def customiseVALSKIM(process):
    process= customisePPData(process)
    process.reconstruction.remove(process.lumiProducer)
    return process
                
##############################################################################
def customiseExpress(process):
    process= customisePPData(process)

    import RecoVertex.BeamSpotProducer.BeamSpotOnline_cfi
    process.offlineBeamSpot = RecoVertex.BeamSpotProducer.BeamSpotOnline_cfi.onlineBeamSpotProducer.clone()
    
    return process

##############################################################################
def customisePrompt(process):
    process= customisePPData(process)

    import RecoVertex.BeamSpotProducer.BeamSpotOnline_cfi
    process.offlineBeamSpot = RecoVertex.BeamSpotProducer.BeamSpotOnline_cfi.onlineBeamSpotProducer.clone()
    
    return process


# End of customisation function definition

process = customisePPData(process)
