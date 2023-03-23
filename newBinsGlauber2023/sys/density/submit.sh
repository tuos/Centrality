#!/bin/bash

bash setupJob.sh
path=$PWD
cd /afs/cern.ch/user/t/tuos/work/private/CMSSW_10_1_5/src
#cmsenv
eval `scramv1 runtime -sh`

#nJobs in setupJob.sh also need to change
nJobs=100
for i in `seq 0 $(($nJobs-1))`
do
  jbi=jb$i
  cd $path/$jbi

  bsub -R "pool>5000" -M 3000000 -q 1nd -J $jbi < $path/$jbi/exeJob.sh

done


