import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                fileNames = cms.untracked.vstring(
'file:/afs/cern.ch/user/t/tuos/work/public/run2015/pprereco/CMSSW_7_5_8_patch4/src/step3HI_RAW2DIGI_L1Reco_RECO.root'
),
)

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')
#                                                 75X_dataRun2_PromptHI_v3 and 75X_dataRun2_v6 give the same results

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("event_data_pbpb.root"))

process.demo = cms.EDAnalyzer('AnalysisEnergyHF',
                       doPPRECO = cms.bool(False)
)

process.p = cms.Path(process.demo)

