# Import configurations

import FWCore.ParameterSet.Config as cms

process = cms.Process('MERGEFILES')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')


# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'

process.source = cms.Source("PoolSource",
#    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),  
    fileNames = cms.untracked.vstring(
     
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_1.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_2.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_3.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_4.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_5.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_6.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_7.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_8.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_9.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_10.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_11.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_12.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_13.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_14.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_15.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_16.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_17.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_18.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_19.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_20.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_21.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_22.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_23.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_24.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_25.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_26.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_27.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_28.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_29.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_30.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_31.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_32.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_33.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_34.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_35.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_36.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_37.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_38.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_39.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_40.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_41.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_42.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_43.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_44.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_45.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_46.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_47.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_48.GEN_SIM_DIGI_L1_Pythia6DT_900.root',
'rfio:/castor/cern.ch/user/o/ochesanu/900GeV_const/pythia6DT/redigi/step2.step2.output_200_49.GEN_SIM_DIGI_L1_Pythia6DT_900.root'
      
                      )
)
# copy 20 events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )


process.out = cms.OutputModule("PoolOutputModule",
    verbose = cms.untracked.bool(False),
    #outputCommands = cms.untracked.vstring('keep *','drop recoGenJets_*_*_*','drop recoGenMETs_*_*_*',
    fileName = cms.untracked.string('/tmp/PYTHIA6_MinBias_900GeV_080410.root')
)

process.outpath = cms.EndPath(process.out)
