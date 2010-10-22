#ifndef gen_Cascade2Hadronizer_h
#define gen_Cascade2Hadronizer_h

// -*- C++ -*-

// class Pythia6Hadronizer is an example of a class that models the
// Hadronizer concept.

#include <memory>

#include <boost/shared_ptr.hpp>

#include "FWCore/ParameterSet/interface/ParameterSetfwd.h"

#include "GeneratorInterface/Core/interface/BaseHadronizer.h"

namespace lhef
{
class LHERunInfo;
class LHEEvent;
}

class LHEEventProduct;

namespace HepMC
{
class GenEvent;
}


namespace gen
{

class Pythia6Service;
//-- class JetMatching;

  class Cascade2Hadronizer : public BaseHadronizer
  {
  
  public:
     Cascade2Hadronizer(edm::ParameterSet const& ps);
     ~Cascade2Hadronizer();

     bool generatePartonsAndHadronize();
    
     //-- bool hadronize();
     //-- bool decay();
     //-- bool residualDecay();
     
     bool initializeForExternalPartons();
     
     //-- bool initializeForInternalPartons();
     //-- bool declareStableParticles( const std::vector<int> );
     
     //-- static JetMatching* getJetMatching() { return fJetMatching; }
          
     void finalizeEvent();

     //-- void statistics();

     const char* classname() const;
     
  private:
     // methods
     
     void flushTmpStorage();
     void fillTmpStorage();
     
     void imposeProperTime();
     
     // data members
          
     Pythia6Service* fPy6Service;

     // the following 3 params are common for all generators(interfaces)
     // probably better to wrap them up in a class and reuse ?
     // (the event/run pointers are already moved to BaseHadronizer)
     //
    
     double fCOMEnergy ;  // this one is irrelevant for setting py6 as hadronizer
                          // or if anything, it should be picked up from LHERunInfoProduct !

     //-- static JetMatching* fJetMatching; 

     bool            fHepMCVerbosity;
     unsigned int    fMaxEventsToPrint ;
           
     // this is the only one specific to Pythia6
     //
     unsigned int    fPythiaListVerbosity ;
     bool            fDisplayPythiaBanner;
     bool            fDisplayPythiaCards;
     
     // these two params control stop- and r-hadron features,
     // that are "custom" add-ons to Py6; 
     // I doubt they should drag along Py6Int main library...
     
     bool fStopHadronsEnabled;
     bool fGluinoHadronsEnabled;
     
     // this is a "trick" to generate enriched mu-samples and the likes
     bool fImposeProperTime;
     
     // and final touch - conversion of Py6 PID's into PDG convension 
     bool fConvertToPDG;
  };
}

#endif