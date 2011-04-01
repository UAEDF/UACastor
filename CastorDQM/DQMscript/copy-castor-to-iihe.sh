#!/bin/sh

debug=0

USAGE="Usage: copy-castor-to-iihe.sh castordir, with castordir like /castor/cern.ch/.../dir"
if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

lcgdir=$1
echo -e "copy root files from castor directory $lcgdir to iihe\n"

if [ `echo $1 | grep 'srm://' -c` -eq 0 ] ; then
  lcgdir='srm://srm-cms.cern.ch:8443'$1
  if [ $debug -eq 1 ] ; then echo -e "full srm path for castor directory: $lcgdir\n"; fi 
fi

basedir=$(echo $lcgdir | sed "s:^.*`whoami`/::")

if [ $debug -eq 1 ] ; then echo -e "base directory (will be automatically created at iihe): $basedir\n"; fi

for file in `lcg-ls $lcgdir` ; do 

  if [ $debug -eq 1 ] ; then echo -e "will transfer file: $file\n"; fi

  barefilename=$(echo $file | sed "s:^.*/::")
  if [ $debug -eq 1 ] ; then echo -e "file name (will be automatically created at iihe): $barefilename\n"; fi   

  if [ $debug -eq 0 ] ; then lcg-cp -v srm://srm-cms.cern.ch:8443$file srm://maite.iihe.ac.be:8443/pnfs/iihe/cms/store/user/`whoami`/$basedir/$barefilename; fi
done


