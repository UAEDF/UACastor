import FWCore.ParameterSet.Config as cms

from GeneratorInterface.CascadeInterface.Cascade2Parameters_cfi import Cascade2Parameters as Cascade2ParametersRef

source = cms.Source("EmptySource")

generator = cms.EDFilter('Cascade2GeneratorFilter',
                         comEnergy = cms.double(7000.0),
                         crossSection = cms.untracked.double(-1),
                         filterEfficiency = cms.untracked.double(1),
                         maxEventsToPrint = cms.untracked.int32(2),
                         pythiaHepMCVerbosity = cms.untracked.bool(False),
                         pythiaPylistVerbosity = cms.untracked.int32(0),
                         Cascade2Parameters = Cascade2ParametersRef
                         )

ProductionFilterSequence = cms.Sequence(generator)