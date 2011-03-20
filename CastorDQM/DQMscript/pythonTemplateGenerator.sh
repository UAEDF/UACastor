#!/bin/sh

USAGE="Usage:  pythonTemplateGenerator.sh dataset"

if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

debug=0

dataset=$1

if [ $debug -eq 1 ] ; then 
echo -e "dataset: $dataset\n"
fi

numpython=0

cat castor_dqm_sourceclient_file_template_cfg.py | sed '/FILELIST/,$ d' > castor_dqm_sourceclient_file_templateA_cfg.py
cat castor_dqm_sourceclient_file_template_cfg.py | sed '1,/FILELIST/ d' > castor_dqm_sourceclient_file_templateB_cfg.py

for dir in `rfdir $dataset | awk '{ print $9 }'` ; do

#if [ $debug -eq 1 ] ; then echo -e "$dataset/$dir\n"; read tt; fi

for subdir in `rfdir $dataset/$dir | awk '{ print $9 }'` ; do

if [ $debug -eq 1 ] ; then echo -e "$dataset/$dir/$subdir\n"; fi

python_cfg='template_castor_dqm_sourceclient_file_'$dir$subdir'_cfg.py' 

cat castor_dqm_sourceclient_file_templateA_cfg.py > $python_cfg

nbfile=$(rfdir $dataset/$dir/$subdir | awk '{ print $9 }' | grep "root" -c) 

if [ $debug -eq 1 ] ; then echo -e "$nbfile root files:\n"; fi

filecounter=0

for file in `rfdir $dataset/$dir/$subdir | awk '{ print $9 }'` ; do

filecounter=`expr $filecounter + 1`
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

if [ $debug -eq 1 ] ; then echo 'python file created for run '$dir$subdir': '$python_cfg; read tt; fi

numpython=`expr $numpython + 1`

if [ $debug -eq 1 ] && [ $numpython -eq 10 ] ; then 
rm -f castor_dqm_sourceclient_file_templateA_cfg.py;
rm -f castor_dqm_sourceclient_file_templateB_cfg.py;
exit 1; 
fi 

done

done

rm -f castor_dqm_sourceclient_file_templateA_cfg.py
rm -f castor_dqm_sourceclient_file_templateB_cfg.py


