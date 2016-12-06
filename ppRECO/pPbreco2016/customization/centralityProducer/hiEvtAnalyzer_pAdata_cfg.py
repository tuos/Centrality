import FWCore.ParameterSet.Config as cms

process = cms.Process('EvtAna')

process.load('FWCore.MessageService.MessageLogger_cfi')
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
			    fileNames = cms.untracked.vstring(
#'file:/afs/cern.ch/work/t/tuos/private/run2016/centralitySoftware/CMSSW_8_1_0_pre7/src/step2_RAW2DIGI_L1Reco_RECO.root'
#'file:/afs/cern.ch/user/t/tuos/work/private/run2016/centralitySoftware/CMSSW_7_5_8_patch4/src/step2_RAW2DIGI_L1Reco_RECO.root'
'file:/afs/cern.ch/user/t/tuos/work/private/run2016/centralitySoftware/CMSSW_7_5_8_patch4/src/10k/job/step2_RAW2DIGI_L1Reco_RECO.root'
),
)

process.maxEvents = cms.untracked.PSet(
            input = cms.untracked.int32(-1))

#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#process.GlobalTag.globaltag = 'GR_P_V43D::All'

#from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
#overrideCentrality(process)

#process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi") 
process.load('RecoHI.HiCentralityAlgos.pACentrality_cfi')
process.load('RecoHI.HiEvtPlaneAlgos.HiEvtPlane_cfi')

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("eventtree_filtered_data.root"))


process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.hiEvtAnalyzer.doMC          = cms.bool(False)
#process.hiEvtAnalyzer.doCentrality     = cms.bool(False)
process.hiEvtAnalyzer.CentralitySrc          = cms.InputTag("pACentrality")
#process.hiEvtAnalyzer.CentralityBinSrc = cms.InputTag("centralityBin","HFtowersTrunc")
process.hiEvtAnalyzer.Vertex = cms.InputTag("offlinePrimaryVertices")

#process.p = cms.Path(process.centralityBin * process.hiEvtAnalyzer)
process.p = cms.Path(process.pACentrality * process.hiEvtPlane * process.hiEvtAnalyzer)


