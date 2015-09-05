import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 10

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc_hi', '')

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
                            fileNames = cms.untracked.vstring(),
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)
import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('filelistAll.txt')
for fname in mylist:
 process.source.fileNames.append('file:%s' % (fname))


process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("histogram_testMB_5020GeV.root")
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
