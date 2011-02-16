import FWCore.ParameterSet.Config as cms

TightCaloJetID_Parameters = cms.PSet(
     
        HPD_CutUp = cms.double(0.98),
        n90hits_CutLow = cms.int32(4),
        RBX_CutUp = cms.double(0.98),
        sigma_eta_CutLow = cms.double(0.01),
        sigma_phi_CutLow = cms.double(0.01),
        fem_CutLow = cms.double(0.01)

)

