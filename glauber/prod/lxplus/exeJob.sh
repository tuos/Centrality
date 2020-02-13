#!/bin/bash
export SCRAM_ARCH=slc6_amd64_gcc630
cd /afs/cern.ch/user/t/tuos/work/private/CMSSW_10_1_5/src
#cmsenv
eval `scramv1 runtime -sh`

echo "start exe"

cd /afs/cern.ch/user/t/tuos/work/private/Glauber2016/version3/code/v31/ppb/default

$ROOTSYS/bin/root -l -b <<EOF
{
  gSystem->Load("libMathMore");
  gROOT->ProcessLine(".L /afs/cern.ch/user/t/tuos/work/private/Glauber2016/version3/code/v31/ppb/default/runglauber_v3.1.C+");
  runAndSaveNtuple(1000000,"p","Pbpnrw",72.5,-1,0.4,-1,-1,"glauber_pPbpnrw_default_1M.root");
}
EOF

echo "Running!"




