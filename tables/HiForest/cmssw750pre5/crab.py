from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'HiForest_for_centrality750pre5_v1'

config.section_('JobType')
config.JobType.psetName = 'runForest_PbPb_MC_75XAOD.py'
config.JobType.pluginName = 'ANALYSIS'
config.JobType.outputFiles = ['hiForest_HydjetMB5TeV75X.root']

config.section_('Data')
config.Data.inputDBS = 'phys03'
#config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV/tuos-HydjetMB_AOD_750pre5_round3v01-81dd8ce0064b5342f0d7e3ef953b6d47/USER'
config.Data.inputDataset = '/Hydjet_Quenched_MinBias_5020GeV/mnguyen-HydjetMB_740pre8_MCHI2_74_V3_53XBS_RECO_v5-fa4d7cedb51d6196cc0424fd90debe3f/USER'
config.Data.publication = True
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
#NJOBS = 50  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
#config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
config.Data.publishDataName = 'HiForest_Centrality_HydjetMB5TeV750pre5_v1'
config.Data.outLFNDirBase = '/store/user/tuos/Forest/centralityPbPb/energy5TeV/hydjet75X/v1'

config.section_('Site')
#config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'
