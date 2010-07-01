import FWCore.ParameterSet.Config as cms

process = cms.Process("TreeMaker")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
              
process.MessageLogger.cerr.FwkReport.reportEvery = 500
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000))
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(  
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0015/CCE2D6AF-3671-DF11-A700-003048679214.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0015/4A99AB75-A371-DF11-AF19-002618943948.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/E4B41212-A471-DF11-B2DC-0018F3D0965E.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/A0C2617F-BE71-DF11-82C5-0018F3D09698.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/922B2904-3671-DF11-A9B1-003048D15D04.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/8C578672-BC71-DF11-BC26-00261894387D.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/68D9CD7D-4871-DF11-90B2-00248C55CC3C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/2CA4510E-5F71-DF11-B819-001A92810A92.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0014/0473B3E6-7371-DF11-A4F9-003048678F84.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0013/7281ADDA-8171-DF11-9415-002354EF3BE0.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0013/381A9C9D-4E71-DF11-841F-003048678B0E.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/F037003A-6471-DF11-B40A-001A92971BCA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/EAEE33B1-3571-DF11-A4E8-0026189438EA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/E090DC26-4871-DF11-AF1A-001A92971B28.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/DE175D8A-C071-DF11-94C6-002618943809.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/BEDF7CF7-3171-DF11-8E5D-001BFCDBD100.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/A85D73E1-6171-DF11-956C-0026189437F8.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/98A4B578-7E71-DF11-8D23-003048678B3C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/98083618-8271-DF11-922E-001A92971B0C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/96A83DC8-AE71-DF11-9572-001BFCDBD184.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/947CB634-6B71-DF11-ABBE-001A92971B30.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/922F8BFB-5F71-DF11-A770-00261894387C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/8A6E8F12-4F71-DF11-ADEB-003048D15DCA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/66C1BDFB-4471-DF11-B686-003048678CA2.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/64CB0E50-A171-DF11-84B6-00304867C136.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/50060E63-5E71-DF11-A1DE-0026189438C0.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/0EB524B3-A871-DF11-8ED3-001A92971BDC.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0012/08695F94-9D71-DF11-9321-003048678E92.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/CAC65818-5671-DF11-B792-001A92811724.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/AA7D04B4-A471-DF11-BF2D-00261894386E.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/9C2BB071-2D71-DF11-8B10-002618943949.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/7AAC8CD8-7B71-DF11-B7EB-0026189438B8.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/704EABBA-BF71-DF11-8D84-0018F3C3E3A6.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0011/60D737ED-7871-DF11-A23D-001BFCDBD1B6.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0010/1601FBDB-5071-DF11-A1F0-0026189438B4.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0009/FA9DC780-3671-DF11-B396-003048678A7E.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0009/D6A3A108-A771-DF11-83FE-00304867902C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0009/BEEBD640-B971-DF11-B842-001A92810A9E.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0009/3AF25FCE-8471-DF11-B954-003048678FDE.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/FE7F6CC9-3F71-DF11-8F83-001A92971B7C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/DAC6F142-B971-DF11-BD2B-002618943811.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/CECE2152-6571-DF11-9127-003048678BAA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/90311DBA-4171-DF11-A719-003048678D86.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/84E55938-B171-DF11-92B1-00261894383C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/722D01FC-7471-DF11-B429-001A928116FA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/323CBE28-9971-DF11-9412-0018F3D096CA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/322A44F7-A671-DF11-BB63-003048678E2A.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/1E1B1F71-7071-DF11-B2F3-001A92971B9C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/0AD34802-5D71-DF11-AC3C-0026189438FA.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0008/04ED9C23-6F71-DF11-8EA3-0018F3D09630.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0007/8A5F1C7D-A771-DF11-A4BF-00304867C034.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0007/62BBC362-8771-DF11-BDC4-0026189438BC.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0007/005099CD-3771-DF11-A02F-00304867BFA8.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0006/8AACD55C-AD71-DF11-8BE0-00304867BFC6.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0006/8471436E-9C71-DF11-B1FD-002618943918.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0006/5249CC8A-9C71-DF11-AE8A-0026189438A0.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0006/36CC529E-BE71-DF11-845A-002618943852.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0006/14E49279-6C71-DF11-900D-00304867900C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0003/E09E2E7B-5271-DF11-93DA-003048678B1C.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0003/887B416E-5971-DF11-B582-003048679214.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0002/ECE2588C-AD71-DF11-8309-001A92810ADC.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0002/AA566E71-6871-DF11-B648-003048678DD6.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0002/40C92030-BC71-DF11-9F10-003048678C62.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0001/72F6D75A-5D71-DF11-8E48-003048D42D92.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0000/60D980DE-5F71-DF11-8B6C-0018F3D09664.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0000/1E290F65-5B71-DF11-9372-001A92810AE2.root',
    '/store/data/Commissioning10/MinimumBias/RAW-RECO/GOODCOLL-May27thSkim_v5/0000/049DD254-AD71-DF11-8E0B-003048678E80.root'
    ),
   lumisToProcess = cms.untracked.VLuminosityBlockRange(
   '132599:1-132599:379',
   '132599:381-132599:437'
    )
)

# magnetic field configuration
process.load('Configuration.StandardSequences.MagneticField_38T_cff')

# HLT configuration
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')
process.hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
process.hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('0 AND((40 OR 41) AND NOT (36 OR 37 OR 38 OR 39))')

# physics declared requirement
process.load('HLTrigger.special.hltPhysicsDeclared_cfi')
process.hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'
				
# primary vertex requirement
process.oneGoodVertexFilter = cms.EDFilter("VertexSelector",
   src = cms.InputTag("offlinePrimaryVertices"),
   cut = cms.string("!isFake && ndof >= 5 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
   filter = cms.bool(True),   # otherwise it won't filter the events, just produce an empty vertex collection.
)

# GT - RawToDigi - Castor Digi
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.StandardSequences.RawToDigi_cff")
process.GlobalTag.globaltag = 'GR10_P_V4::All'
process.castorDigis.InputLabel = 'source'

process.TFileService = cms.Service("TFileService",fileName = cms.string("CentralJetFilters_7000GeV_May27Skim_Run132599.root"))

# scraping events rejection
process.noscraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25))

# PFJet Dijet Selection
process.pfdijetSelector7TeV = cms.EDProducer('CentralDiPFJetProducer7TeV',
    PFJetCorrector = cms.string('ak5PFL2L3'),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    NHFCutUp = cms.double(0.9),
    NEFCutUp = cms.double(0.9),
    CHFCutLow = cms.double(0.0),
    CEFCutUp = cms.double(1.0),
    NumConstituentsCutLow = cms.int32(0),
    ChargedMultiplicityCutLow = cms.int32(0),
    JetPtCut = cms.double(5),
    JetEtaCut = cms.double(2.5))

# PFJet Inclusive Selection
process.pfmonojetSelector7TeV = cms.EDProducer('CentralMonoPFJetProducer7TeV',
    PFJetCorrector = cms.string('ak5PFL2L3'),
    PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
    NHFCutUp = cms.double(0.9),
    NEFCutUp = cms.double(0.9),
    CHFCutLow = cms.double(0.0),
    CEFCutUp = cms.double(1.0),
    NumConstituentsCutLow = cms.int32(0),
    ChargedMultiplicityCutLow = cms.int32(0),
    JetPtCut = cms.double(5),
    JetEtaCut = cms.double(2.5))

# final tree
process.treemaker7TeV = cms.EDAnalyzer('TreeMaker7TeV',
      OutputFileName = cms.string("TreeMaker_7000GeV_May27Skim_Run132599.root"),
      PFJetCorrector = cms.string('ak5PFL2L3'),
      HLTriggerResults = cms.InputTag('TriggerResults','','HLT'),
      PFJets = cms.InputTag('ak5PFJets', '', 'RECO'),
      L1Trigger = cms.InputTag('gtDigis', '', 'RECO'),
      CastorDigis = cms.InputTag('castorDigis', '', 'TreeMaker'),
      HepMCColl = cms.InputTag('generator','','HLT'),
      PrimaryVertexColl = cms.InputTag('offlinePrimaryVertices','','RECO'),
      BeamSpot = cms.InputTag('offlineBeamSpot','','RECO'),
      GenPartColl = cms.InputTag('genParticles','','HLT'))

process.p = cms.Path(process.hltPhysicsDeclared*process.hltLevel1GTSeed*process.oneGoodVertexFilter*process.noscraping*process.castorDigis*(process.pfmonojetSelector7TeV+process.pfdijetSelector7TeV)*process.treemaker7TeV)

