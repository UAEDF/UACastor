#!/bin/bash

USAGE="Usage: submitBatch.csh file.py"

if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

FILE=$1
LENGTH=${#FILE}
LENGTH_INPUT=$((LENGTH-13))
POSITION=0
INPUT=${FILE:POSITION:LENGTH_INPUT}

#echo $FILE
#echo $LENGTH
#echo $LENGTH_INPUT
#echo $POSITION
#echo $INPUT

# directory where the job is run or submitted
if [ "${LS_SUBCWD+set}" = set ]; then
   LK_WKDIR="${LS_SUBCWD}" # directory where you submit in case of bsub
   WWDIR="${WORKDIR}"
else
   LK_WKDIR=`pwd`          # directory where you run locally otherwise
   WWDIR=`pwd`
fi

LOCAL_CFGFILE=${LK_WKDIR}/${INPUT}_rivet_cfg.py
CFGFILE=${WWDIR}/${INPUT}.cmssw.py
POOLOUTPUTFILE=${WWDIR}/${INPUT}.cmssw.aida
LOGFILE=${WWDIR}/${INPUT}.cmssw.log

#echo $LOCAL_CFGFILE
#echo $CFGFILE
#echo $POOLOUTPUTFILE
#echo $LOGFILE

CASTOR_DIR="/castor/cern.ch/user/r/roland/Cascade2_CMS_FWD_10_011_cmssw"

if [ -e $CFGFILE ]; then
   echo "The cfg file $CFGFILE already exists. Stopping here!"
   exit 1;
fi


DIR_WHERE_TO_EVAL="/afs/cern.ch/user/r/roland/scratch0/Cascade_Validation_4_4_X/CMSSW_4_4_0/src"

cat $LOCAL_CFGFILE  > $CFGFILE

cd $DIR_WHERE_TO_EVAL; eval `scramv1 runtime -sh`; cd -;
cmsRun $CFGFILE > $LOGFILE 2>&1
return_val=$?

if [ $return_val -eq 0 ]; then
  rfcp $CFGFILE $CASTOR_DIR/
  rfcp $POOLOUTPUTFILE $CASTOR_DIR/
  rfcp $LOGFILE $CASTOR_DIR/
fi

