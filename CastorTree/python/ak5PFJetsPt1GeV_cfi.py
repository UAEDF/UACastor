import FWCore.ParameterSet.Config as cms

AnomalousCellParameters = cms.PSet(
    maxBadEcalCells         = cms.uint32(9999999),
    maxRecoveredEcalCells   = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxBadHcalCells         = cms.uint32(9999999),
    maxRecoveredHcalCells   = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999)
)

PFJetParameters = cms.PSet(
    src            = cms.InputTag('particleFlow'),
    srcPVs         = cms.InputTag(''),
    jetType        = cms.string('PFJet'),
    doOutputJets   = cms.bool(True),
    jetPtMin       = cms.double(1.0),
    inputEMin      = cms.double(0.0),
    inputEtMin     = cms.double(0.0),
    doPVCorrection = cms.bool(False),
    # pileup with offset correction
    doPUOffsetCorr = cms.bool(False),
    # if pileup is false, these are not read:
    nSigmaPU = cms.double(1.0),
    radiusPU = cms.double(0.5),  
    # fastjet-style pileup     
    doAreaFastjet       = cms.bool( False),
    doRhoFastjet        = cms.bool( False),
    doAreaDiskApprox    = cms.bool( False),
    Active_Area_Repeats = cms.int32(    1),
    GhostArea           = cms.double(0.01),
    Ghost_EtaMax        = cms.double( 5.0),
    Rho_EtaMax          = cms.double( 4.4),
    voronoiRfact        = cms.double(-0.9),
    useDeterministicSeed= cms.bool( True ),
    minSeed             = cms.uint32( 14327 )
)
 
ak5PFJetsPt1GeV = cms.EDProducer("FastjetJetProducer",
     PFJetParameters,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
)
