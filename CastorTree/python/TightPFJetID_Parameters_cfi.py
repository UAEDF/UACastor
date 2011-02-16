import FWCore.ParameterSet.Config as cms

TightPFJetID_Parameters = cms.PSet(
     
        fhad_ne_CutUp = cms.double(0.9),
        fem_ne_CutUp = cms.double(0.9),

        fhad_ch_CutLow = cms.double(0.0),
        fem_ch_CutUp = cms.double(1.0),

        nconstituent_CutLow = cms.int32(0),
        multi_ch_CutLow = cms.int32(0)
        
)

