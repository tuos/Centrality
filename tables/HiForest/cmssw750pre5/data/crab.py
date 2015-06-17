from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'HiForest_for_centrality750pre5Data_v1'

config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_PbPb_DATA_75X.py'
config.JobType.outputFiles = ['HiForestAOD_750pre5_Data.root']

config.section_('Data')
config.Data.inputDBS = 'phys03'
config.Data.inputDataset = '/HIMinBiasUPC/tuos-MB_AOD_DATA750pre5_round3v01-f884d8d44fa079fef73ed78a04ab1ee3/USER'
config.Data.lumiMask = 'lumiInputMB.json'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 2
#config.Data.runRange = '193093-193999'
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
#config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.publication = True
config.Data.publishDataName = 'HiForest_Centrality_5TeV750pre5Data_v1'
config.Data.outLFNDirBase = '/store/user/tuos/Forest/centralityPbPb/energy5TeV/hydjet75X/v2data'

config.section_('Site')
config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'
