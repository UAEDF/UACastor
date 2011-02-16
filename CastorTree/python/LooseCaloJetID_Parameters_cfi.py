import FWCore.ParameterSet.Config as cms

LooseCaloJetID_Parameters = cms.PSet(
     
        HPD_CutUp = cms.double(0.98),
        n90hits_CutLow = cms.int32(1),
        fem_CutLow = cms.double(0.01)
        
)

