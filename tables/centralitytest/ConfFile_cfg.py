import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 200

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_data', '')

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")
process.centralityBin.nonDefaultGlauberModel = cms.string("HydjetDrum5")

process.GlobalTag.toGet.extend([
   cms.PSet(record = cms.string("HeavyIonRcd"),
      tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5_v750x02_mc"),
      connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
      label = cms.untracked.string("HFtowersHydjetDrum5")
   ),
])

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
'/store/user/tuos/HIAOD2015/round3/June01/HydjetMB/Hydjet_Quenched_MinBias_5020GeV/HydjetMB_AOD_750pre5_round3v01/150601_223002/0000/step2_RAW2DIGI_L1Reco_MB_AODSIM_329.root'
))

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_test_MB_AOD.root")
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
   srcTracksPixel = cms.InputTag("hiGeneralAndPixelTracks")
)

process.p = cms.Path(process.centralityBin * process.demo)


