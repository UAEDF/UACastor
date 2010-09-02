import FWCore.ParameterSet.Config as cms

process = cms.Process("CastorShowerLibraryMaker")

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.MagneticField_0T_cff')

process.load("SimGeneral.HepPDTESSource.pdt_cfi")
process.load("IOMC.EventVertexGenerators.VtxSmearedGauss_cfi")

process.load('Configuration.StandardSequences.Generator_cff')
process.load("SimG4Core.Application.g4SimHits_cfi")
process.load("SimG4CMS.Forward.castorGeometryXML_cfi")


process.load('SimCalorimetry.EcalTrigPrimProducers.ecalTrigPrimESProducer_cff')

process.load("Configuration.StandardSequences.SimulationRandomNumberGeneratorSeeds_cff")
#process.RandomNumberGeneratorService.generator.initialSeed = 12346
#process.RandomNumberGeneratorService.VtxSmeared.initialSeed = 12345
#process.RandomNumberGeneratorService.g4SimHits.initialSeed = 12345
#process.RandomNumberGeneratorService.mix.initialSeed = 12345


#process.load("FWCore.MessageService.test.Services_cff")

# Here is the configuration of the MessgeLogger Service:

#process.MessageLogger = cms.Service("MessageLogger",
#    destinations = cms.untracked.vstring('LogInfo'),
#    debugModules = cms.untracked.vstring("CastorShowerLibraryMaker"),
#    LogInfo = cms.untracked.PSet(
#        threshold = cms.untracked.string('INFO')
#    )
#)



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    #splitLevel = cms.untracked.int32(0),
    #outputCommands = process.RAWSIMEventContent.outputCommands, #+cms.untracked.vstring('keep *_simCastorDigis_*_*'),
    fileName = cms.untracked.string('CastorSim_GEN-SIM_PGun_Electron5GeV_FullSim_10000events_etaphirange.root')
    #dataset = cms.untracked.PSet(
    #    dataTier = cms.untracked.string('GEN-SIM-RAW'),
    #    filterName = cms.untracked.string('')
    #),
    #SelectEvents = cms.untracked.PSet(
    #    SelectEvents = cms.vstring('generation_step')
    #)
)


common_pgun_particleID = cms.PSet(
        #PartID = cms.vint32(11,211)
        PartID = cms.vint32(11)
)

process.generator = cms.EDProducer("FlatRandomEGunProducer",
    PGunParameters = cms.PSet(
        common_pgun_particleID,
        MinEta = cms.double(-6.6),
        MaxEta = cms.double(-5.2),
        MinPhi = cms.double(-3.14159265),
        MaxPhi = cms.double(3.14159265), # PI/4 = 0.7854
        MinE = cms.double(4.99),
        MaxE = cms.double(5.01)
    ),
    AddAntiParticle = cms.bool(False),
    Verbosity = cms.untracked.int32(False)
)


process.ProductionFilterSequence = cms.Sequence(process.generator)

# shifted/smeared vertex according to data taking

#from IOMC.EventVertexGenerators.VtxSmearedParameters_cfi import *

process.common_maximum_timex = cms.PSet( # need to be localy redefined
   MaxTrackTime  = cms.double(500.0),  # need to be localy redefined
   MaxTimeNames  = cms.vstring(), # need to be localy redefined
   MaxTrackTimes = cms.vdouble()  # need to be localy redefined
)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.VtxSmeared*process.g4SimHits)
process.out_step = cms.EndPath(process.output)





# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step)
#process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq





process.g4SimHits.Generator.ApplyEtaCuts = False
process.g4SimHits.UseMagneticField = False

process.g4SimHits.StackingAction = cms.PSet(
   process.common_heavy_suppression,
   process.common_maximum_timex,        # need to be localy redefined
   TrackNeutrino = cms.bool(False),
   KillHeavy     = cms.bool(False),
   KillDeltaRay  = cms.bool(True),
   SaveFirstLevelSecondary = cms.untracked.bool(True),
   SavePrimaryDecayProductsAndConversionsInTracker = cms.untracked.bool(True),
   SavePrimaryDecayProductsAndConversionsInCalo    = cms.untracked.bool(True),
   SavePrimaryDecayProductsAndConversionsInMuon    = cms.untracked.bool(True)
)

process.g4SimHits.SteppingAction = cms.PSet(
   process.common_maximum_timex, # need to be localy redefined
   KillBeamPipe            = cms.bool(True),
   CriticalEnergyForVacuum = cms.double(2.0),
   CriticalDensity         = cms.double(1e-15),
   EkinNames               = cms.vstring(),
   EkinThresholds          = cms.vdouble(),
   EkinParticles           = cms.vstring(),
   Verbosity               = cms.untracked.int32(0)
)




process.g4SimHits.CastorSD.useShowerLibrary = False

