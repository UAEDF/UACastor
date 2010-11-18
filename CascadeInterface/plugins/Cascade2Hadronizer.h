#ifndef gen_Cascade2Hadronizer_h
#define gen_Cascade2Hadronizer_h

#include <memory>

#include <boost/shared_ptr.hpp>

#include "FWCore/ParameterSet/interface/ParameterSetfwd.h"

#include "GeneratorInterface/Core/interface/BaseHadronizer.h"

namespace HepMC
{
class GenEvent;
}

namespace CLHEP
{
  class HepRandomEngine;
}

namespace gen
{
  class Pythia6Service;
  
  class JetMatching;

  class Cascade2Hadronizer : public BaseHadronizer
  {
    
  public:
    Cascade2Hadronizer(edm::ParameterSet const& ps);
    ~Cascade2Hadronizer();

    // bool generatePartons();
    bool generatePartonsAndHadronize();
    bool hadronize(); //-- hadronizer for the LHE input   
    bool decay();
    bool residualDecay();
    bool initializeForExternalPartons(); //-- initializer for the LHE input 
    bool initializeForInternalPartons();
    bool declareStableParticles( const std::vector<int> );
     
    static JetMatching* getJetMatching() { return fJetMatching; }
          
    void finalizeEvent();

    void statistics();

    const char* classname() const;
     
  private:
  
    //-- methods
    
     void flushTmpStorage();
     void fillTmpStorage();
     void imposeProperTime();  //-- to correctly treat particle decay

     
     //-- data members
     
     Pythia6Service* fPy6Service;
     CLHEP::HepRandomEngine* frandomEngine;


     //-- the following 3 params are common for all generators(interfaces)
     //-- probably better to wrap them up in a class and reuse ?
     //-- (the event/run pointers are already moved to BaseHadronizer)
     
     double fCOMEnergy ;  //-- this one is irrelevant for setting py6 as hadronizer
                          //-- or if anything, it should be picked up from LHERunInfoProduct !
     bool            fHepMCVerbosity;
     unsigned int    fMaxEventsToPrint ;

     static JetMatching* fJetMatching; 

     //-- this is the only one specific to Pythia6
     
     unsigned int    fPythiaListVerbosity ;
     bool            fDisplayPythiaBanner;
     bool            fDisplayPythiaCards;
     
     //-- conversion of Py6 PID's into PDG convention 
     bool fConvertToPDG;
     
  };
}

#endif
