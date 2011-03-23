#!/bin/sh

USAGE="Usage:  pythonTemplateGenerator.sh dataset inf sup"

if [ $# -ne 3 ] ; then echo $USAGE; exit 1; fi

debug=0

dataset=$1
inf=$2
sup=$3

if [ $debug -eq 1 ] ; then 
echo "dataset: $dataset"
echo "inf: $inf"
echo -e "sup: $sup\n"
fi

# retrieve the Collisions10 run

declare -a RunList

count=0

while read LINE; do
    RunList[$count]=$LINE
    ((count++))
done < Collisions10_Run.txt

if [ $debug -eq 1 ] ; then
echo -e "number of runs: ${#RunList[@]}\n"
echo -e "${RunList[@]}\n"
read tt;
fi

numpython=1

cat castor_dqm_sourceclient_file_template_cfg.py | sed '/FILELIST/,$ d' > castor_dqm_sourceclient_file_templateA_cfg.py
cat castor_dqm_sourceclient_file_template_cfg.py | sed '1,/FILELIST/ d' > castor_dqm_sourceclient_file_templateB_cfg.py

for dir in `rfdir $dataset | awk '{ print $9 }'` ; do

for subdir in `rfdir $dataset/$dir | awk '{ print $9 }'` ; do

if [ $debug -eq 1 ] ; then echo -e "$dataset/$dir/$subdir\n"; fi

run_now=$dir$subdir;
selected=0

for run in ${RunList[@]} ; do
if [ $run_now -eq $run ] ; then selected=1; fi 
done

if [ $debug -eq 1 ] ; then echo -e "run $run_now selected: $selected\n"; fi
if [ $selected -eq 0 ] ; then continue; fi  

python_cfg='template_castor_dqm_sourceclient_file_'$dir$subdir'_cfg.py' 

cat castor_dqm_sourceclient_file_templateA_cfg.py > $python_cfg

nbfile=$(rfdir $dataset/$dir/$subdir | awk '{ print $9 }' | grep "root" -c) 

if [ $debug -eq 1 ] ; then echo -e "$nbfile root files:\n"; fi

filecounter=0

for file in `rfdir $dataset/$dir/$subdir | awk '{ print $9 }'` ; do

((filecounter++))
filename=$dataset'/'$dir'/'$subdir'/'$file

if [ $debug -eq 1 ] && [ $filecounter -ne $nbfile ] ; then echo $filename; fi
if [ $debug -eq 1 ] && [ $filecounter -eq $nbfile ] ; then echo -e "$filename\n"; fi

if [ $filecounter -ne $nbfile ] ; then
echo \'rfio:$filename\', >> $python_cfg
else 
echo \'rfio:$filename\' >> $python_cfg
fi
  
done

cat castor_dqm_sourceclient_file_templateB_cfg.py >> $python_cfg

if [ $numpython -ge $inf ] && [ $numpython -le $sup ] ; then
if [ $debug -eq 1 ] ; then echo 'python file created for run '$dir$subdir': '$python_cfg; read tt; fi
echo 'python file created for run '$dir$subdir': '$python_cfg;
fi

if [ $numpython -lt $inf ] ; then rm -f $python_cfg; fi 
if [ $numpython -gt $sup ] ; then rm -f $python_cfg; fi
if [ $numpython -gt $sup ] ; then 
rm -f castor_dqm_sourceclient_file_templateA_cfg.py;
rm -f castor_dqm_sourceclient_file_templateB_cfg.py;
exit 1;
fi

if [ $debug -eq 1 ] && [ $numpython -eq 5 ] ; then 
rm -f castor_dqm_sourceclient_file_templateA_cfg.py;
rm -f castor_dqm_sourceclient_file_templateB_cfg.py;
exit 1; 
fi 

((numpython++))

done

done

rm -f castor_dqm_sourceclient_file_templateA_cfg.py
rm -f castor_dqm_sourceclient_file_templateB_cfg.py


