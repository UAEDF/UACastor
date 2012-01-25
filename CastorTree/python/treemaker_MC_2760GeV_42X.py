
import FWCore.ParameterSet.Config as cms

# use 7TeV PFJetID cuts - yes also for 2760GeV since I didn't found other ones
from UACastor.CastorTree.TightPFJetID_Parameters7TeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters7TeV_Ref
# use general CaloJetID cuts
from UACastor.CastorTree.LooseCaloJetID_Parameters_cfi import LooseCaloJetID_Parameters as LooseCaloJetID_Parameters_Ref
from UACastor.CastorTree.TightCaloJetID_Parameters_cfi import TightCaloJetID_Parameters as TightCaloJetID_Parameters_Ref

process = cms.Process("Analysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

#process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(70000))
process.MessageLogger.cerr.FwkReport.reportEvery = 10000
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(


'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_10_1_CJn.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_22_1_yPL.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_34_1_DZr.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_46_1_I9d.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_11_1_IHX.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_23_1_WSs.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_35_1_NcZ.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_47_1_xHA.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_12_1_04X.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_24_1_LWE.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_36_1_FKy.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_48_1_rpG.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_13_1_0Yc.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_25_1_tmK.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_37_1_w1y.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_49_1_KDr.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_14_1_uJm.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_26_1_WyJ.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_38_1_Lyf.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_4_1_gVI.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_15_1_5il.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_27_1_91h.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_39_1_Jzj.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_5_1_IWy.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_16_1_pX7.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_28_1_4Pz.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_3_1_bnx.root',   
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_6_1_m1q.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_17_1_2BO.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_29_1_BH2.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_40_1_rVW.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_7_1_anO.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_18_1_Sz2.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_2_1_SZF.root',   
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_41_1_F4z.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_8_1_dfZ.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_19_1_yfg.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_30_1_r92.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_42_1_nfq.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_9_1_vaE.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_1_1_JEv.root',   
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_31_1_jCl.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_43_1_n7t.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_20_1_shu.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_32_1_OoJ.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_44_1_DhZ.root',
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_21_1_JTV.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_33_1_nWR.root',  
'/store/user/hvanhaev/MinBias_TuneD6T_2760GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_TuneD6T_2760GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_45_1_fWN.root',

    ))

# magnetic field
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# require physics declared
process.physDecl = cms.EDFilter("PhysDecl",applyfilter = cms.untracked.bool(True),HLTriggerResults = cms.InputTag("TriggerResults"))

# communicate with the DB
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'START42_V11::All' # to be used for reprocessing of 2009 and 2010 data (update JEC to Spring10 V8)

# import the JEC services
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

process.load("Configuration.StandardSequences.RawToDigi_cff")

# track jet
process.load('UACastor.CastorTree.UEAnalysisTracks_cfi')
process.load('UACastor.CastorTree.UEAnalysisJetsAntiKt_cfi')
process.load('QCDAnalysis.UEAnalysis.UEAnalysisParticles_cfi')
 	 
#print "DzTrVtxMax = ",process.ak5TrackJets500.DzTrVtxMax
#print "DxyTrVtxMax = ",process.ak5TrackJets500.DxyTrVtxMax
 
process.ak5TrackJets500.DzTrVtxMax = cms.double(1000)
process.ak5TrackJets500.DxyTrVtxMax = cms.double(1000)
process.chargeParticles.cut = cms.string('charge != 0 & pt > 0.3 & status = 1')

# import ak5PFJets reconstruction with Pt < 1 GeV
process.load('UACastor.CastorTree.ak5PFJetsPt1GeV_cfi')

# import ak5GenJets reconstruction with Pt < 1 GeV
process.load('UACastor.CastorTree.ak5GenJetsPt1GeV_cfi')

# Final Tree
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_MC_2760GeV_42X.root"))

# Event Reconstruction (need to be updated)
process.castortree = cms.EDAnalyzer('CastorTree',

   StoreGenKine = cms.bool(True),                                 
   StoreGenPart = cms.bool(True),
   StoreGenJet = cms.bool(True),
   StoreCastorDigi = cms.bool(False),
   StoreCastorJet = cms.bool(True),                                

   # input tag for L1GtTriggerMenuLite retrieved from provenance
   L1GT_TrigMenuLite_Prov = cms.bool(True),
   # input tag for L1GtTriggerMenuLite explicitly given
   L1GT_TrigMenuLite = cms.InputTag('l1GtTriggerMenuLite'),
  
   L1GT_ObjectMap = cms.InputTag('hltL1GtObjectMap','','HLT'),
                                               
   hepMCColl = cms.InputTag('generator','','SIM'),
   genPartColl = cms.InputTag('genParticles','','HLT'),
   
   CastorTowerColl = cms.InputTag('CastorTowerReco', '','RECO'),                                 
   CastorDigiColl = cms.InputTag('castorDigis', '','RECO'),
   CastorRecHitColl = cms.InputTag('castorreco','','RECO'),
   BasicJet = cms.InputTag('ak7BasicJets','','RECO'),  
   CastorJetID = cms.InputTag('ak7CastorJetID','','RECO'), 

   #PFJetColl = cms.InputTag('ak5PFJets', '', 'RECO'),
   PFJetColl = cms.InputTag('ak5PFJetsPt1GeV', '', 'Analysis'),
   PFJetJEC = cms.string('ak5PFL2L3'),    # L2L3Residual JEC should be applied to data only
   PFJetJECunc = cms.string('AK5PF'),
                                    
   CaloJetColl = cms.InputTag('ak5CaloJets','','RECO'),
   CaloJetId = cms.InputTag('ak5JetID','','RECO'),
   CaloJetJEC = cms.string('ak5CaloL2L3'), # L2L3Residual JEC should be applied to data only 
   CaloJetJECunc = cms.string('AK5Calo'),

   CaloTowerColl = cms.InputTag('towerMaker','','RECO'),
   #GenJetColl = cms.InputTag('ak5GenJets'),
   GenJetColl = cms.InputTag('ak5GenJetsPt1GeV','','Analysis'),
   
   TrackJetColl = cms.InputTag('ak5TrackJets500'),
   TrackJetJEC = cms.string('ak5TrackL2L3'),    # L2L3Residual JEC should be applied to data only
   TrackJetJECunc = cms.string('AK5JPT'),
   
   ChargedGenJetColl = cms.InputTag('ak5ChgGenJets500'),
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters7TeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(8.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV
   JetEtaCut = cms.double(2.5),

   FilterResults = cms.InputTag('TriggerResults','','Analysis'),
   requested_hlt_bits = cms.vstring('HLT_L1BscMinBiasORBptxPlusANDMinus_v1','HLT_ZeroBias_v1'),
   requested_filter_bits = cms.vstring('physDeclpath')          
)

# list of processes
process.physDeclpath = cms.Path(process.physDecl)
process.recotrackjet = cms.Path(process.UEAnalysisTracks*process.ak5TrackJets500)
process.chargedgenjet = cms.Path(process.UEAnalysisParticles*process.ak5ChgGenJets500)
process.ak5PFJetsNew = cms.Path(process.ak5PFJetsPt1GeV)
process.ak5GenJetsNew = cms.Path(process.ak5GenJetsPt1GeV)
process.tree = cms.EndPath(process.castortree)
