cd /afs/cern.ch/user/t/tuos/work/public/centralitytest5320/CMSSW_5_3_20/src
#cmsenv
eval `scramv1 runtime -sh`

cd /afs/cern.ch/user/t/tuos/work/public/centralitytest5320/CMSSW_5_3_20/src/TestCentrality/TestAnalyzer/test

cmsRun testanalyzer_cfi.py &> job01out.log

