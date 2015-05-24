import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )

process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_53_LV6::All'
#process.GlobalTag.globaltag = ' FT_R_53_LV9::All'

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import *
overrideCentrality(process)

process.HeavyIonGlobalParameters = cms.PSet(
    centralityVariable = cms.string("HFtowers"),
    nonDefaultGlauberModel = cms.string(""),
    centralitySrc = cms.InputTag("hiCentrality")
    )

process.source = cms.Source("PoolSource",
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
                            fileNames = cms.untracked.vstring(
'root://xrootd.unl.edu//store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00000/0011854A-F0AD-E311-885B-FA163E32A814.root',
#'root://xrootd.unl.edu//store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00000/0018A8E7-F9AF-E311-ADAB-FA163E565820.root',
#'root://xrootd.unl.edu//store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00000/002456EE-FCAF-E311-87B3-FA163E632CDA.root'
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/54EFDEEF-02B0-E311-9071-FA163EF4B816.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/56191C52-05B0-E311-905C-FA163EB65EAD.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/569F0455-11B0-E311-8635-FA163EEFA8A1.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/56B3243A-FDAF-E311-B6DD-FA163E1088DA.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/58387319-11B0-E311-A5C9-FA163EB286AE.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/583C7D49-FBAF-E311-9675-FA163EF12995.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5855B8D3-FEAF-E311-9601-FA163ED7F036.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/588C2E50-16B0-E311-860D-FA163E764152.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/58A67215-11B0-E311-AD32-FA163E5616D6.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/58E69077-FBAF-E311-99B1-FA163EE8AB28.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5A174C70-00B0-E311-9ABF-FA163E30C3CD.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5A34CDFE-05B0-E311-AB47-FA163EBF49C2.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5A84BAC7-1DB0-E311-AB81-FA163EE35C92.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5A8714E6-1AB0-E311-9260-FA163E8F9CFE.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5A94222B-38B0-E311-B77A-FA163E6CDC07.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5AA2ABED-FCAF-E311-A6C9-FA163E226FAC.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5AE3A354-11B0-E311-947C-FA163EF7B927.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5AFDFFC3-17B0-E311-B562-FA163E1E4EE2.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5C194CF9-04B0-E311-B3E2-FA163EDE4FA5.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5C320C05-FDAF-E311-9D05-FA163EDEC621.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5C7FEDFB-04B0-E311-A45A-FA163E8F3DDE.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5C890319-04B0-E311-AD52-FA163EE62D8D.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5C942E62-11B0-E311-AED0-FA163EB336EF.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5CE4C459-01B0-E311-AD84-FA163EC59FA3.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5CEDFCD5-11B0-E311-A206-FA163E5AD785.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5E10635A-11B0-E311-8243-FA163E0A13B7.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5E3A11DA-FFAF-E311-8836-FA163E379231.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5E903C15-11B0-E311-A030-FA163E5616D6.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5EBD217F-03B0-E311-86F1-FA163E537063.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5EC1A934-03B0-E311-B8BD-FA163E3CB490.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5EC7EDD9-FFAF-E311-B232-FA163E9201BB.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/5EDFD4ED-00B0-E311-9CD8-FA163E44B1FB.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/6052B62E-19B0-E311-BAFE-FA163E88B110.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/606FAA16-11B0-E311-905C-FA163EE4F8B5.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/620FFFDD-1BB0-E311-8690-FA163EFCD9E6.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/624636A3-FCAF-E311-BD15-FA163EBAE513.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/628471D5-19B0-E311-ACE8-FA163E6A840B.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/62A400C8-18B0-E311-8389-FA163E180EF4.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/62AC4BF0-FCAF-E311-B0A5-FA163ED551F2.root',
       '/store/hidata/HIRun2011/HIMinBiasUPC/RECO/14Mar2014-v2/00015/6407955B-1DB0-E311-8512-FA163E341EC6.root'
                           ),
)

process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMinBiasHFOrBSC = process.hltHighLevel.clone()
process.hltMinBiasHFOrBSC.HLTPaths = ["HLT_HIMinBiasHfOrBSC_v1"]

process.TFileService = cms.Service("TFileService",
                                  fileName=cms.string("centralitytest6080.root"))

process.demo = cms.EDAnalyzer('TestAnalyzer'
)

process.p = cms.Path(process.hltMinBiasHFOrBSC * process.collisionEventSelection * process.demo)



