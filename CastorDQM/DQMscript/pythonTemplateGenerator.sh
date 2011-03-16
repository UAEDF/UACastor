#!/bin/sh

USAGE="Usage:  pythonTemplateGenerator.sh inputdir outputdir nbevt"

if [ $# -ne 3 ] ; then echo $USAGE; exit 1; fi

debug=1

inputdir=$1
outputdir=$2
nbevt=$3

if [ $debug -eq 1 ] ; then 
echo "inputdir: $inputdir"
echo "outputdir: $outputdir"
echo -e "nbevt: $nbevt\n"
fi

rm -f DQMpython/template*

numpython=0

cat castor_dqm_sourceclient_file_template_cfg.py | sed '/FILELIST/,$ d' > castor_dqm_sourceclient_file_templateA_cfg.py
cat castor_dqm_sourceclient_file_template_cfg.py | sed '1,/FILELIST/ d' > castor_dqm_sourceclient_file_templateB_cfg.py

for dir in `rfdir $inputdir | awk '{ print $9 }'` ; do

if [ $debug -eq 1 ] ; then echo -e "$inputdir/$dir\n"; read tt; fi

for subdir in `rfdir $inputdir/$dir | awk '{ print $9 }'` ; do

if [ $debug -eq 1 ] ; then echo -e "$inputdir/$dir/$subdir\n"; fi

python_cfg='DQMpython/template_'$dir$subdir'_castor_dqm_sourceclient_file_cfg.py' 

cat castor_dqm_sourceclient_file_templateA_cfg.py > python_cfg_temp1

nbfile=$(rfdir $inputdir/$dir/$subdir | awk '{ print $9 }' | grep "root" -c) 

if [ $debug -eq 1 ] ; then echo -e "$nbfile root files:\n"; fi

filecounter=0

for file in `rfdir $inputdir/$dir/$subdir | awk '{ print $9 }'` ; do

filecounter=`expr $filecounter + 1`
filename=$inputdir'/'$dir'/'$subdir'/'$file

if [ $debug -eq 1 ] && [ $filecounter -ne $nbfile ] ; then echo $filename; fi
if [ $debug -eq 1 ] && [ $filecounter -eq $nbfile ] ; then echo -e "$filename\n"; fi

if [ $filecounter -ne $nbfile ] ; then
echo \'rfio:$filename\', >> python_cfg_temp1
else 
echo \'rfio:$filename\' >> python_cfg_temp1
fi
  
done

cat castor_dqm_sourceclient_file_templateB_cfg.py >> python_cfg_temp1
cat python_cfg_temp1 | sed "s:NUMOFEVENTS:$nbevt:" > python_cfg_temp2
cat python_cfg_temp2 | sed "s:OUTPUTDIR:$outputdir:" > $python_cfg

if [ $debug -eq 1 ] ; then echo 'python file created for run '$dir$subdir': ' $python_cfg; read tt; fi

numpython=`expr $numpython + 1`

if [ $debug -eq 1 ] && [ $numpython -eq 5 ] ; then 
rm -f castor_dqm_sourceclient_file_templateA_cfg.py;
rm -f castor_dqm_sourceclient_file_templateB_cfg.py;
rm -f python_cfg_temp1;
rm -f python_cfg_temp2;
exit 1; 
fi 

done

done

rm -f castor_dqm_sourceclient_file_templateA_cfg.py
rm -f castor_dqm_sourceclient_file_templateB_cfg.py
rm -f python_cfg_temp1;
rm -f python_cfg_temp2;


