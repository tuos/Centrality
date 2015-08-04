import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 10

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_data', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_mc_hi', '')

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("HydjetDrum5")

process.GlobalTag.toGet.extend([
   cms.PSet(record = cms.string("HeavyIonRcd"),
      tag = cms.string("CentralityTable_HFtowers200_HydjetDrum_run1v750x01_mc"),
      connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
      label = cms.untracked.string("HFtowersHydjetDrum5")
   ),
])

process.source = cms.Source("PoolSource",
#                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/006B5968-9F6B-E411-940D-7845C4FC3B33.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/00876729-B46B-E411-ACCD-00A0D1EE8C64.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/00897DC5-AA6B-E411-84FE-00A0D1EEF328.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/009813CB-A56B-E411-9D0A-001D09FDD80D.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0208FDF9-A76B-E411-812D-7845C4FC3A91.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0272700E-A76B-E411-8470-180373FF8DE0.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02811443-AB6B-E411-94FD-008CFA002E80.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02858B2A-C16B-E411-937B-7845C4FC363E.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/028819D9-9F6B-E411-815D-00A0D1EE8DFC.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/028BA254-9D6B-E411-9DEA-848F69FD453B.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/028F4364-B16B-E411-B41E-3417EBE2F553.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/029E76DB-AC6B-E411-9513-00266CF279F8.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02A37814-9A6B-E411-826F-00266CF9AED8.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02ABA33C-A36B-E411-97E4-F04DA275BFE3.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02DBB151-AA6B-E411-A266-7845C4FC35D8.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02EBB657-9E6B-E411-B029-3417EBE2F316.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02EEA2DE-B46B-E411-B755-00A0D1EC3950.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02FC7330-AC6B-E411-8CF9-00266CF253C4.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/02FDE674-AD6B-E411-B2CE-180373FF94D6.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/042C94C3-946B-E411-8E3E-7845C4F90F07.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/042F925D-BD6B-E411-B911-001D09FDD7C8.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/04F6054F-A56B-E411-98DD-848F69FD2961.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/04FB9894-B36B-E411-9DD5-00266CFAE764.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06053750-AD6B-E411-9DC2-00266CFAE228.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/060DABAA-B86B-E411-9B37-3417EBE2F0C7.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0620FFB4-B56B-E411-B841-7845C4F8AF24.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/063B988B-C16B-E411-A70B-008CFA0014EC.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0665461C-B36B-E411-98D3-7845C4FC3638.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/067A04A0-AC6B-E411-8F6E-00266CF9C018.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06808239-AD6B-E411-B69A-00266CFAEB30.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06834335-AC6B-E411-B325-3417EBE2ED22.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06A349DF-A46B-E411-A96E-3417EBE2E9BC.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06A3EB3E-CB6B-E411-A93D-00266CFAE818.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06E494F3-B36B-E411-B772-F04DA275BF11.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/06E791F8-BD6B-E411-8A8A-7845C4FC39B3.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0827C238-B16B-E411-A8DA-008CFA002634.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0835CED1-AD6B-E411-BAB4-3417EBE2F0C7.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0878EAED-A06B-E411-AC03-7845C4F93215.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/087E366F-B46B-E411-9D3C-00266CFAEA48.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/08926ED6-AB6B-E411-BE9B-00A0D1EEFD70.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0A45AD26-AE6B-E411-B2CE-848F69FD2940.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0A4A660B-B66B-E411-914A-7845C4FC3B18.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0A9B8BF7-A86B-E411-BCAB-008CFA008D4C.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0AB09F1A-AD6B-E411-870B-7845C4F915E2.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0AD1FBD6-CD6B-E411-AF63-3417EBE2EC98.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0AEE0C84-986B-E411-8850-7845C4F8AF24.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C023862-AB6B-E411-ABA6-00266CF9AED8.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C30246E-A36B-E411-B5DA-7845C4FC3614.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C6D8B80-A66B-E411-A642-3417EBE46EDF.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C75C431-AF6B-E411-8FB1-001D09FDD7B9.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C904E19-A06B-E411-BD2B-00266CF9BEE4.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0C98D237-916B-E411-BEB2-3417EBE2F094.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E0D44A3-976B-E411-BA75-00266CF9B59C.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E190861-BE6B-E411-A72F-7845C4FC37A9.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E43EC9D-B96B-E411-8751-848F69FD28FE.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E4AEC89-AD6B-E411-A429-008CFA00317C.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E6E5C73-C66B-E411-A1D0-008CFA0027B4.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E75E0EE-B06B-E411-85E1-3417EBE33927.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E7613A7-B06B-E411-8F8B-00A0D1EE8EB4.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0E8DB9D5-B56B-E411-A737-008CFA00210C.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0ECEF57F-9D6B-E411-9043-00266CFAE304.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0EFAB664-AD6B-E411-9CB7-7845C4F9162D.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/0EFBC607-CC6B-E411-A982-00A0D1EE8E94.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10099AED-A86B-E411-B48C-00A0D1EE968C.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/1018C3A2-AC6B-E411-89BA-00266CF25920.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/102101ED-9D6B-E411-B6F3-848F69FD29BE.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/103B0999-9D6B-E411-8B7B-00266CF24ED4.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10932846-B06B-E411-9B03-00A0D1EE8DFC.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10CC7046-C06B-E411-81FB-00A0D1EEAA00.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10EAB8E6-BE6B-E411-8B6A-00266CF9BCAC.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10FA350A-B46B-E411-9200-848F69FD4E41.root',
       '/store/himc/HiFall13DR53X/Hydjet1p8_TuneDrum_Quenched_MinBias_2760GeV/GEN-SIM-RECO/NoPileUp_STARTHI53_LV1-v1/00000/10FF6C43-A36B-E411-A478-3417EBE2F445.root'
))

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_test_MB_2760GeV.root")
)

process.demo = cms.EDAnalyzer('TestAnalysis',
   CentralitySrc    = cms.InputTag("hiCentrality"),
   centralityBinLabel = cms.InputTag("centralityBin","HFtowers"),
   srcTracks = cms.InputTag("hiGeneralTracks"),
   srcVertex= cms.InputTag("hiSelectedVertex"),
   UseQuality = cms.bool(True),
   TrackQuality = cms.string('highPurity'),
   trackEtaCut = cms.double(2.4),
   trackPtCut = cms.double(0.3),
#   srcTracksPixel = cms.InputTag("hiGeneralAndPixelTracks")
   srcTracksPixel = cms.InputTag("hiGeneralTracks")
)


process.p = cms.Path(process.centralityBin * process.demo)


