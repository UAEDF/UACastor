#!/bin/bash

USAGE="Usage:  runDQMdata inf sup"

if [ $# -ne 2 ] ; then echo $USAGE; exit 1; fi

debug=0

dataset=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/RAW/v4/000
inf=$1
sup=$2

dir=DQMCommissioning10
pythondir=`pwd`/${dir}
storedir=/castor/cern.ch/user/r/roland/DQM2010/Commissioning10

if [ ! -d ${dir} ]; then 
  mkdir ${dir}
fi

./pythonTemplateGenerator.sh $dataset $inf $sup

jobid=$inf

for file in template* ; do

 echo -e "\n"   
 echo Creating job $jobid

 final_file=${file:9:${#file}-9}
 run=${file:38:${#file}-45}
 
 if [ $debug -eq 1 ] ; then echo -e "file ${dir}/${final_file} is created for run ${run}"; read tt; fi 
 
 cat $file | sed "s:NUMOFEVENTS:-1:" > temp1
 cat temp1 | sed "s:OUTPUTDIR:./:" > ${dir}/${final_file} 
 
 rm -f temp1 

 cat submit_template.sh | sed "s:CFGFILE:$final_file:"  > temp1
 cat temp1 | sed "s:PYTHONDIR:$pythondir:" > temp2
 cat temp2 | sed "s:RUN:$run:" > temp3
 cat temp3 | sed "s:STOREDIR:$storedir:"  > ${dir}/submit_$run.sh
 rm -fr temp1
 rm -fr temp2
 rm -fr temp3

 cd $dir
 bsub -q 1nd -J job_$jobid -R "pool>10000" < submit_$run.sh
 cd ..

((jobid++))
done

rm -f template*



