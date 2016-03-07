import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'/store/hidata/HIRun2015/HIMinimumBias2/AOD/PromptReco-v1/000/262/656/00000/3ECF02D6-67A7-E511-A5FD-02163E013845.root'
),
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag

process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v6', '')

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("event_data.root"))

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

process.demo = cms.EDAnalyzer('FindEdges',
   centralitySrc    = cms.InputTag("hiCentrality"),
   centralityBinSrc = cms.InputTag("centralityBin","HFtowers")
)

process.p = cms.Path(process.collisionEventSelectionAOD * process.centralityBin * process.demo)

