#!/bin/bash

USAGE="Usage: stager.sh castordir, with castordir like /castor/cern.ch/.../dir"
if [ $# -ne 1 ] ; then echo $USAGE; exit 1; fi

for file in `nsls $1 | grep root`; do
  stager_get -M $1/$file
  stager_qry -M $1/$file
done

