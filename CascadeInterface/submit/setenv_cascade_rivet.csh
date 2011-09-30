setenv LD_LIBRARY_PATH
setenv LD_LIBRARY_PATH '$LD_LIBRARY_PATH:/afs/cern.ch/sw/lcg/external/MCGenerators/cascade/2.2.0/slc4_amd64_gcc34/lib'
setenv PATH /afs/cern.ch/sw/lcg/external/Python/2.6.5/x86_64-slc5-gcc43-opt/bin:${PATH}
setenv LD_LIBRARY_PATH /afs/cern.ch/sw/lcg/external/Python/2.6.5/x86_64-slc5-gcc43-opt/lib:${LD_LIBRARY_PATH}
setenv PATH /afs/cern.ch/sw/lcg/external/swig/1.3.40/x86_64-slc5-gcc43-opt/bin:${PATH}

source /afs/cern.ch/sw/lcg/contrib/gcc/4.3/x86_64-slc5-gcc43-opt/setup.csh
source /afs/cern.ch/sw/lcg/external/MCGenerators/rivet/1.6.0/x86_64-slc5-gcc43-opt/rivetenv.csh
source /afs/cern.ch/sw/lcg/external/MCGenerators/agile/1.2.2/x86_64-slc5-gcc43-opt/agileenv.csh

setenv RIVET_ANALYSIS_PATH $PWD
