#!/bin/sh

USAGE="Usage:  printrun.sh dataset era"

if [ $# -ne 2 ] ; then echo $USAGE; exit 1; fi

debug=0

dataset=$1
era=$2

if [ $debug -eq 1 ] ; then 
echo -e "dataset: $dataset\n"
fi

# retrieve the Collisions10 run

declare -a RunList

count=0

while read LINE; do
    RunList[$count]=$LINE
    ((count++))
done < Collisions10_Run.txt

numrun=0

for dir in `rfdir $dataset | awk '{ print $9 }'` ; do

for subdir in `rfdir $dataset/$dir | awk '{ print $9 }'` ; do

run_now=$dir$subdir;
selected=0

for run in ${RunList[@]} ; do
if [ $run_now -eq $run ] ; then selected=1; fi 
done

if [ $selected -eq 0 ] ; then continue; fi  
((numrun++)) 
echo -e "run $numrun $dataset/$dir/$subdir" >>  list_run_Collisions10_$2.txt

done
done

echo "number of runs in $dataset: $numrun"

