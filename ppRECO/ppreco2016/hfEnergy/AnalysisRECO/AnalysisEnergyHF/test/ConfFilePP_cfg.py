import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'file:/afs/cern.ch/user/t/tuos/work/public/run2015/pprereco/CMSSW_7_5_8_patch4/src/step3pp_FILTER_RAW2DIGI_L1Reco_RECO.root'
),
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("event_data_pp.root"))

process.demo = cms.EDAnalyzer('AnalysisEnergyHF',
                       doPPRECO = cms.bool(True)
)

process.p = cms.Path(process.demo)

