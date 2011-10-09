## Set up env to use LCG versions of Python & GCC (and SWIG)

## Set an LCG platform tag if not already defined
test -n "$LCGTAG" || LCGTAG=x86_64-slc5-gcc43-opt

export PATH=/afs/cern.ch/sw/lcg/external/Python/2.6.5/$LCGTAG/bin:$PATH
export LD_LIBRARY_PATH=/afs/cern.ch/sw/lcg/external/Python/2.6.5/$LCGTAG/lib:$LD_LIBRARY_PATH
export PATH=/afs/cern.ch/sw/lcg/external/swig/1.3.40/$LCGTAG/bin:$PATH
source /afs/cern.ch/sw/lcg/contrib/gcc/4.3/$LCGTAG/setup.sh

## Source Prof and Rivet (in that order!)
source /afs/cern.ch/sw/lcg/external/MCGenerators/professor/1.3.0/$LCGTAG/setup.sh
source /afs/cern.ch/sw/lcg/external/MCGenerators_hepmc2.06/rivet/1.6.0/$LCGTAG/rivetenv.sh
source /afs/cern.ch/sw/lcg/external/MCGenerators_hepmc2.06/agile/1.3.0/$LCGTAG/agileenv.sh

export LATEXINPUTS=$LATEXINPUTS:$TEXMFHOME//
export TEXINPUTS=$TEXINPUTS:$TEXMFHOME//
