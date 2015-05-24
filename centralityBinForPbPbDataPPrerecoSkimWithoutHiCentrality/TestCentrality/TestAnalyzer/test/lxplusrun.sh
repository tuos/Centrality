#!/bin/bash
cd /afs/cern.ch/user/t/tuos/work/public/centralitytest5320/CMSSW_5_3_20/src
#cmsenv
eval `scramv1 runtime -sh`

cd /afs/cern.ch/user/t/tuos/work/public/centralitytest5320/CMSSW_5_3_20/src/TestCentrality/TestAnalyzer/test

bsub -R "pool>5000" -M 3000000 -q 2nd -J job01 </afs/cern.ch/user/t/tuos/work/public/centralitytest5320/CMSSW_5_3_20/src/TestCentrality/TestAnalyzer/test/cmsrun.sh


