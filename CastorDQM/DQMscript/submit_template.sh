#!/bin/sh

debug=0

source /afs/cern.ch/cms/sw/cmsset_default.sh
farmdir=`pwd`
pythondir=PYTHONDIR 
storedir=STOREDIR
cfgfile=CFGFILE
run=RUN

if [ $debug -eq 1 ] ; then echo "farm dir: $farmdir";
echo "python dir: $pythondir";
echo -e "store dir: $storedir\n";
fi

cd ${pythondir}
export SCRAM_ARCH=slc5_amd64_gcc434;
cmsenv;

cp ${cfgfile} ${farmdir}
cd ${farmdir}

logfile=${cfgfile:0:${#cfgfile}-3}.log 
outputfile=DQM_V0001_Castor_R000$run.root

if [ $debug -eq 1 ] ; then echo "config file: ${cfgfile}";
echo "log file: ${logfile}";
echo -e "output file: ${outputfile}\n";
fi

cmsRun $cfgfile > $logfile 2>&1
return_val=$?

if [ $return_val -eq 0 ]; then
  rfcp $cfgfile ${storedir}/
  rfcp $outputfile ${storedir}/
  rfcp $logfile ${storedir}/
fi


