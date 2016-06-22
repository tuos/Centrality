# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: RECO --process ppRECO --repacked --conditions 75X_dataRun2_PromptHI_v3 -s FILTER:RecoHI/Configuration/peripheralHLTFilter_cff.peripheralHLTFilterSequence,RAW2DIGI,L1Reco,RECO --datatier AOD --customise Configuration/DataProcessing/RecoTLR.customiseDataRun2Common_50nsRunsAfter253000,RecoHI/Configuration/customise_PPwithHI.customisePPwithHI --data --scenario pp --nThreads=4 --eventcontent AOD --filein /store/hidata/HIRun2015/HIMinimumBias5/RAW/v1/000/263/233/00000/02463ECA-329A-E511-B6EA-02163E0146E0.root -n 500 --python_filename=reco_HIRun2015_HIPeriph.py --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('ppRECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(500)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/hidata/HIRun2015/HIMinimumBias5/RAW/v1/000/263/233/00000/02463ECA-329A-E511-B6EA-02163E0146E0.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('RECO nevts:500'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.AODoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('filtering_step')
    ),
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AOD'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    fileName = cms.untracked.string('RECO_FILTER_RAW2DIGI_L1Reco_RECO.root'),
    outputCommands = process.AODEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

process.hltPerhiphHI = cms.EDFilter("HLTHighLevel",
    HLTPaths = cms.vstring('HLT_HISinglePhoton*_Eta*_Cent50_100_*', 
        'HLT_HISinglePhoton*_Eta*_Cent30_100_*', 
        'HLT_HIFullTrack*_L1Centrality30100_*', 
        'HLT_HIPuAK4CaloJet*_Eta5p1_Cent50_100_v*', 
        'HLT_HIPuAK4CaloJet*_Eta5p1_Cent30_100_v*', 
        'HLT_HIDmesonHITrackingGlobal_Dpt*_Cent50_100_v*', 
        'HLT_HIDmesonHITrackingGlobal_Dpt*_Cent30_100_v*', 
        'HLT_HIL1Centralityext30100MinimumumBiasHF*', 
        'HLT_HIL1Centralityext50100MinimumumBiasHF*', 
        'HLT_HIQ2*005_Centrality3050_v*', 
        'HLT_HIQ2*005_Centrality5070_v*', 
        'HLT_HICastor*', 
        'HLT_HIL1Castor*', 
        'HLT_HIUPC*'),
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    andOr = cms.bool(True),
    eventSetupPathsKey = cms.string(''),
    throw = cms.bool(False)
)


process.peripheralHLTFilterSequence = cms.Sequence(process.hltPerhiphHI)

# Path and EndPath definitions
process.filtering_step = cms.Path(process.peripheralHLTFilterSequence)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODoutput_step = cms.EndPath(process.AODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.filtering_step,process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.AODoutput_step)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(4)
process.options.numberOfStreams=cms.untracked.uint32(0)
# filter all path with the production filter sequence
for path in process.paths:
	if not path in ['raw2digi_step', 'L1Reco_step', 'reconstruction_step', 'endjob_step']: continue
	getattr(process,path)._seq = process.peripheralHLTFilterSequence * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customiseDataRun2Common_50nsRunsAfter253000 

#call to customisation function customiseDataRun2Common_50nsRunsAfter253000 imported from Configuration.DataProcessing.RecoTLR
process = customiseDataRun2Common_50nsRunsAfter253000(process)

# Automatic addition of the customisation function from RecoHI.Configuration.customise_PPwithHI
from RecoHI.Configuration.customise_PPwithHI import customisePPwithHI 

#call to customisation function customisePPwithHI imported from RecoHI.Configuration.customise_PPwithHI
process = customisePPwithHI(process)

# End of customisation functions

from Configuration.Applications.ConfigBuilder import MassReplaceInputTag
MassReplaceInputTag(process)

