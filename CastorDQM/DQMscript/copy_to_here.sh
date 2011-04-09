#!/bin/bash

USAGE="Usage: copy_to_here.sh castordir, with castordir like /castor/cern.ch/.../dir"
if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

numtot=`nsls $1 | grep root -c`
echo -e "will transfer $numtot files\n"
numfile=1

for file in `nsls $1 | grep root`; do
  echo -e "\n"
  echo -e "copy file $file ($numfile/$numtot)\n"
  rfcp $1/$file $file
  ((numfile++))
done
