
import FWCore.ParameterSet.Config as cms

# use 900GeV PF jet ID parameters
from UACastor.CastorTree.TightPFJetID_Parameters900GeV_cfi import TightPFJetID_Parameters as TightPFJetID_Parameters900GeV_Ref
# use general CaloJet ID parameters
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

	
	'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_10_1_5yQ.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_11_1_vQ7.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_12_1_3lB.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_13_1_Mko.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_14_1_Ipf.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_15_1_JK1.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_16_1_x9k.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_17_1_hbc.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_18_1_oLy.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_19_1_zRT.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_1_1_VOa.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_20_1_hAN.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_21_1_CL7.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_22_1_8NY.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_23_1_ZBD.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_24_1_Syi.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_25_1_tlo.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_26_1_L1b.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_27_1_udT.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_28_1_IxS.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_29_1_tCA.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_2_1_LxB.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_30_1_FTF.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_31_1_cPa.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_32_1_Ecn.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_33_1_Pv1.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_34_1_bRb.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_35_1_Rxp.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_36_1_Mxp.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_37_1_RCI.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_38_1_At1.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_39_1_g8b.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_3_1_OuN.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_40_1_aPJ.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_41_1_OLF.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_42_1_ggL.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_43_2_cS8.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_44_1_Vzx.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_45_1_xRX.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_46_1_YwU.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_47_1_kYk.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_48_1_Z57.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_49_1_hnO.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_4_1_LzT.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_50_1_pGd.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_51_1_PaL.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_52_1_aTo.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_53_1_fQZ.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_54_1_SqB.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_55_1_Lnu.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_56_1_gMW.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_57_1_qML.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_58_1_eEq.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_59_1_33T.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_5_1_yxj.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_60_1_HLc.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_61_1_f6K.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_62_1_Krj.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_63_1_Gzd.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_64_1_sDr.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_65_1_GH2.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_66_1_1Xf.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_67_1_DKR.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_68_1_ZKS.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_69_1_mc8.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_6_1_ysy.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_70_1_6Um.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_71_1_yWN.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_72_1_0bf.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_73_1_WbX.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_74_1_ogC.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_75_1_PWk.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_76_1_Nmc.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_77_1_mwK.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_78_1_dIg.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_79_1_MvE.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_7_1_JQv.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_80_1_ptK.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_81_1_Kl5.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_82_1_MOn.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_83_1_Xwk.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_84_1_2Rn.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_85_1_6U1.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_86_1_rjY.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_87_1_27E.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_88_1_4SQ.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_89_1_iIM.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_8_1_57O.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_90_1_CZ0.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_91_1_e7q.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_92_1_9vd.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_93_1_N1L.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_94_1_lnb.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_95_1_sHf.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_96_1_c2M.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_97_1_Qz4.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_98_1_jdW.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_99_1_Vnh.root',
'/store/user/hvanhaev/MinBias_900GeV_pythia6_cff_py_GEN_SIM_START311_V2_v1/MinBias_900GeV_pythia6_cff_py_Step3_START42_V11_v1/be8c3cd8213bbe72824c2261376ee6b3/STEP2_RAW2DIGI_L1Reco_RECO_9_1_X5T.root',

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
process.TFileService = cms.Service("TFileService",fileName = cms.string("CastorTree_MC_900GeV_42X.root"))

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
                                    
   TightPFJetID_Parameters = TightPFJetID_Parameters900GeV_Ref,
   LooseCaloJetID_Parameters = LooseCaloJetID_Parameters_Ref,
   TightCaloJetID_Parameters = TightCaloJetID_Parameters_Ref,
   JetPtCut = cms.double(8.0), # Jet Pt > 8 GeV at 900 GeV and 2.36 TeV
   JetEtaCut = cms.double(2.5),

   FilterResults = cms.InputTag('TriggerResults','','Analysis'),
   requested_hlt_bits = cms.vstring('HLT_BackwardBSC','HLT_ForwardBSC','HLT_L1Tech_BSC_halo_forPhysicsBackground','HLT_L1_BscMinBiasOR_BeamGas',
	'HLT_L1_BscMinBiasOR_BptxPlusORMinus','HLT_L1_BscMinBiasOR_BptxPlusORMinus_NoBPTX','HLT_MinBiasBSC','HLT_MinBiasBSC_NoBPTX','HLT_MinBiasBSC_OR','HLT_L1_BPTX','HLT_L1_BPTX_MinusOnly','HLT_L1_BPTX_PlusOnly','HLT_ZeroBias'),
   requested_filter_bits = cms.vstring('physDeclpath')          
)

# list of processes
process.physDeclpath = cms.Path(process.physDecl)
process.recotrackjet = cms.Path(process.UEAnalysisTracks*process.ak5TrackJets500)
process.chargedgenjet = cms.Path(process.UEAnalysisParticles*process.ak5ChgGenJets500)
process.ak5PFJetsNew = cms.Path(process.ak5PFJetsPt1GeV)
process.ak5GenJetsNew = cms.Path(process.ak5GenJetsPt1GeV)
process.tree = cms.EndPath(process.castortree)
