import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'/store/user/davidlw/ppRECO_run263233/part1000_std_50nsTestPromptGT_v2/160226_212234/0000/step2ppPromptGT50ns_RAW2DIGI_L1Reco_RECO_1.root'
),
)

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

process.demo = cms.EDAnalyzer('TestSolution'
)

process.p = cms.Path(process.demo)
