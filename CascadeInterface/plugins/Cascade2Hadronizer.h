#ifndef gen_Cascade2Hadronizer_h
#define gen_Cascade2Hadronizer_h

#include <memory>

#include <boost/shared_ptr.hpp>

#include "FWCore/ParameterSet/interface/ParameterSetfwd.h"
#include "GeneratorInterface/Core/interface/ParameterCollector.h"
#include "GeneratorInterface/Core/interface/BaseHadronizer.h"

namespace HepMC {
  class GenEvent;
}

namespace CLHEP {
  class HepRandomEngine;
}

namespace gen {
  class Pythia6Service;
  
  class Cascade2Hadronizer : public BaseHadronizer  {
    
  public:
    Cascade2Hadronizer(edm::ParameterSet const& ps);
    ~Cascade2Hadronizer();

    bool initializeForExternalPartons(); //-- initializer for the LHE input
    bool initializeForInternalPartons();

    bool declareStableParticles(const std::vector<int>);
    void statistics();

    // bool generatePartons();
  
    bool generatePartonsAndHadronize();
    bool hadronize(); //-- hadronizer for the LHE input   
    bool decay();
    bool residualDecay();
    void finalizeEvent();

    const char* classname() const;
          
  private:
  
    //-- methods
    
     void flushTmpStorage();
     void fillTmpStorage();
     void imposeProperTime();  //-- to correctly treat particle decay

     
     //-- data members

     gen::ParameterCollector parameters;

     Pythia6Service* fPy6Service;
     CLHEP::HepRandomEngine* frandomEngine;

     double fComEnergy ;  //-- irrelevant for setting py6 as hadronizer (or if anything, it should be picked up from LHERunInfoProduct)
     double fCrossSection;
     double fFilterEfficiency;

     unsigned int    fMaxEventsToPrint ;
     bool            fHepMCVerbosity;
     unsigned int    fPythiaListVerbosity ; //-- p6 specific

     bool            fDisplayPythiaBanner;  //-- p6 specific
     bool            fDisplayPythiaCards;   //-- p6 specific

     bool fConvertToPDG; //-- conversion of Py6 PID's into PDG convention
     
  };
}

#endif
