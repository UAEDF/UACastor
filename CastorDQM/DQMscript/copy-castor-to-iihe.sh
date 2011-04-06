#!/bin/sh

debug=0

USAGE="Usage: copy-castor-to-iihe.sh castordir, with castordir like /castor/cern.ch/.../dir"
if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

lcgdir=$1

if [ `echo $1 | grep 'srm://' -c` -eq 0 ] ; then
  lcgdir='srm://srm-cms.cern.ch:8443'$1
fi

basedir=$(echo $lcgdir | sed "s:^.*`whoami`/::")

printinfo=0

for file in `lcg-ls $lcgdir` ; do 
 
  if [ `echo $file | grep 'root' -c` -eq 0 ] ; then continue; fi

  barefilename=$(echo $file | sed "s:^.*/::")
  
  if [ $printinfo -eq 0 ] ; then echo -e "transfer from $lcgdir to srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/`whoami`/$basedir\n"; fi
  echo -e "transfer file $barefilename\n";  

  if [ $debug -eq 0 ] ; then lcg-cp -v $lcgdir/$barefilename srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/`whoami`/$basedir/$barefilename; fi 

  ((printinfo++))

done


