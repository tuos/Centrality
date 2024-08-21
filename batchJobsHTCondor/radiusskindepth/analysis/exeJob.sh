#!/bin/sh
export SCRAM_ARCH=slc6_amd64_gcc630
cd /afs/cern.ch/user/t/tuos/work/private/CMSSW_10_1_5/src
#cmsenv
eval `scramv1 runtime -sh`
path="/afs/cern.ch/user/t/tuos/work/private/Glauber2016/version3/code/v31/pbpb/default/5360/radiusskindepth/analysis"
jbi=jb0
cd $path/$jbi 

$ROOTSYS/bin/root -l -b <<EOF
{ 
  gROOT->ProcessLine(".x /afs/cern.ch/user/t/tuos/work/private/Glauber2016/version3/code/v31/pbpb/default/5360/radiusskindepth/analysis/jb0/findGlauberValues.C");
}
EOF

echo "Done!"




