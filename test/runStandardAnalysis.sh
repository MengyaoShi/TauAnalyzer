#!/bin/bash

#usage
if [ $# -ne 1 ]
    then
    echo "Usage: ./runStandardAnalysis.sh <version_normal>"
    exit 0
fi

#version
versionNormal=$1

#setup
eval `scramv1 runtime -sh`

#MT bin
iBeg=0
MTBin="_MTBin"

#run--order matters here!
root -l -b -q 'formatDataBkgPlots.C("'${versionNormal}'", "'${versionNormal}'", "'${MTBin}'")'

exit 0
