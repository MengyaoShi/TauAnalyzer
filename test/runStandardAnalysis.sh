#!/bin/bash

#usage
if [ $# -ne 3 ]
    then
    echo "Usage: ./runStandardAnalysis.sh <version_narrow> <version_normal> <HLT_path>"
    exit 0
fi

#version
versionNarrow=$1
versionNormal=$2
HLTPath=$3

#setup
eval `scramv1 runtime -sh`

#MT bin
iBeg=0
MTBin=( "_highMT" "_lowMT" )
#MTBin=( "_highMT" )
#MTBin=( "_lowMT" )
nMTBins=${#MTBin[@]}
iEndMTBin=`expr $nMTBins - 1`

#run--order matters here!
for iMTBin in `seq $iBeg $iEndMTBin`
  do
  root -l -b -q 'formatDataBkgPlots.C("'${versionNormal}'", "'${versionNormal}'", "'${versionNarrow}'", "'${MTBin[${iMTBin}]}'", 3)'
done

exit 0
