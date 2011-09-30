#!/bin/bash

pwd=`pwd`
echo $pwd

CASTOR_DIR="/castor/cern.ch/user/r/roland/Cascade2_CMS_FWD_10_011_standalone"

name=Cascade2_CMS_FWD_10_011.standalone
echo ' after set name' ${name} 

source /afs/cern.ch/sw/lcg/external/MCGenerators/rivet/1.6.0/x86_64-slc5-gcc43-opt/rivetenv.sh
source /afs/cern.ch/sw/lcg/external/MCGenerators/agile/1.2.2/x86_64-slc5-gcc43-opt/agileenv.sh

export PATH=/afs/cern.ch/sw/lcg/external/Python/2.6.5/x86_64-slc5-gcc43-opt/bin:$PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/Python/2.6.5/x86_64-slc5-gcc43-opt/lib:$LD_LIBRARY_PATH
export PATH=/afs/cern.ch/sw/lcg/external/swig/1.3.40/x86_64-slc5-gcc43-opt/bin:$PATH

source /afs/cern.ch/sw/lcg/contrib/gcc/4.3/x86_64-slc5-gcc43-opt/setup.sh

export LD_LIBRARY_PATH="/afs/cern.ch/sw/lcg/external/MCGenerators/cascade/2.2.04/slc4_amd64_gcc34/lib":$LD_LIBRARY_PATH

cp -rp /afs/cern.ch/user/r/roland/scratch0/Cascade_Validation_Standalone/cascade-rivet/bin/cascade .
cp -rp /afs/cern.ch/user/r/roland/scratch0/Cascade_Validation_Standalone/cascade-rivet/bin/steer_CMS_FWD_10_011 .

mkdir data
cp -r /afs/cern.ch/user/r/roland/scratch0/Cascade_Validation_Standalone/cascade-rivet/bin/data/* data/.
echo ' after copy : ls -rtl'
ls -rtl
echo ' after copy : ls -rtl data'
ls -rtl data

cp -rp /afs/cern.ch/user/r/roland/scratch0/Cascade_Validation_Standalone/cascade-rivet/bin/RivetMyTest.so .
export RIVET_ANALYSIS_PATH=$PWD

echo ' after copy  ' 
ls -rtl

echo ' before running cascade '
outfile=/tmp/roland/${name}.fifo
echo ' HEPMC output file = ' ${outfile}
export HEPMCOUT=${outfile}
mkfifo ${outfile}

cascade < steer_CMS_FWD_10_011 > ${name}.log & 
rivet -x 0.3048E11 -a CMS_FWD_10_011 ${outfile} > ${name}.rivet.log 
return_val=$?

echo ' after the job finished '
echo ' ls -rtl /tmp/roland '
ls -rtl /tmp/roland/
rm ${outfile}
echo ' after remove of outfile '
ls -rtl /tmp/roland/
echo $pwd
ls -rtl
echo ' jobname ' ${name} 

if [ $return_val -eq 0 ]; then
rfcp ${name}.log $CASTOR_DIR/
rfcp ${name}.rivet.log $CASTOR_DIR/

mv Rivet.aida ${name}.aida
rfcp ${name}.aida $CASTOR_DIR/

mv steer_CMS_FWD_10_011 ${name}.steer
rfcp ${name}.steer $CASTOR_DIR/
fi