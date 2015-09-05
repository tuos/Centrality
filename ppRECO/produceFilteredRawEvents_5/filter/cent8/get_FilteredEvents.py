import FWCore.ParameterSet.Config as cms

process = cms.Process('FILTER')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50)
)

# Input source
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#'file:/store/user/tuos/tmp/ppReco/step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_100_1_nRy.root'
#),
#    secondaryFileNames = cms.untracked.vstring()
#)
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(),
                            duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)
import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('filelist.txt')
for fname in mylist:
 process.source.fileNames.append('%s' % (fname))

process.load("Analysis.EventIDFilter.EventIDFilter_cfi")
process.eventIDFilter.selectedBins = [8];
# Output definition

process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/store/user/tuos/tmp/ppReco/slurm/v2_50evts/filter/cent8/step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_jb0filter.root'),
    outputCommands = cms.untracked.vstring(
      'keep *'
    ),
    SelectEvents = cms.untracked.PSet(
	SelectEvents = cms.vstring('p'),
    ),
)

process.p = cms.Path(process.eventIDFilter)
process.out = cms.EndPath(process.output)

