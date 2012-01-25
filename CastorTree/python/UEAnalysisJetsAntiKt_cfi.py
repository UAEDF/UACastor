# Make the jets

import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.FastjetParameters_cfi import *
from RecoJets.JetProducers.ak5GenJets_cfi import ak5GenJets
from RecoJets.JetProducers.ak5TrackJets_cfi import ak5TrackJets

FastjetWithAreaPU = cms.PSet(
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    UE_Subtraction = cms.string('no')
)

# MC charged gen jet

ak5ChgGenJets500 = ak5GenJets.clone( 
src = cms.InputTag("chargeParticles"),
jetPtMin       = cms.double(0.3),
inputEtMin     = cms.double(0.3)
)


# DATA and MC reco track jet

ak5TrackJets500 = ak5TrackJets.clone(
src = cms.InputTag("goodTracks"),
jetPtMin       = cms.double(0.3),
inputEtMin     = cms.double(0.3)
)

UEAnalysisNeededJets = cms.Sequence(ak5ChgGenJets500*ak5TrackJets500)
