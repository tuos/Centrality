#!/bin/sh

nJobs=100
path="/afs/cern.ch/user/t/tuos/work/private/Glauber2016/version3/code/v31/pbpb/radiusskindepth/analysis"
for i in `seq 0 $(($nJobs-1))`
do
  cd $path 
  jbi=jb$i
  mkdir $jbi
  runjb="findGlauberValues.C"
  cp $runjb $jbi/$runjb
  cp exeJob.sh $jbi
  cd $path/$jbi
  sed -i "s/jb0/${jbi}/g" $runjb
  sed -i "s/jb0/${jbi}/g" exeJob.sh

done



