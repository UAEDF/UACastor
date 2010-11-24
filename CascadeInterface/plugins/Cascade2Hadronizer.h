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

  struct CASCADE_PARAM {
    int KE;      //-- flavour code of beam1
    int IRES1;   //-- direct or resolved particle 1
    int KP;      //-- flavour code of beam2
    int IRES2;   //-- direct or resolved particle 2
    int NFRAG;   //-- fragmentation (1=on, 0=off)
    int IPST;    //-- to keep track of intermediate state in PS
    int IPSIPOL; //-- polarisation for J/psi (1=on,0=off)
    int I23S;    //-- select 1S, 2S, 3S state for vector meson (0=1S,2=2S,3=3S from version 2.2.03 on)
    int IFPS;    //-- parton shower( 0 = off, 1 = initial, 2 = final, 3 = initial & final state PS)
    int ITIMSHR; //-- swtich for time-like shower in intial state cascade (0=off,1=on)
    int IRAM;    //-- switch for running alphas (0=off,1=on)
    int IQ2;     //-- scale for alphas
    int IPRO;    //-- process number (IPRO = 2 J/psi g, IPRO = 10 q qbar,IPRO = 11 Q Qbar)
    int NFLA;    //-- number of flavors in pdfs
    int INTER;   //-- mode of interaction for ep (photon exchange, Z-echange (not implemented))
    int IHFLA;   //-- flavor code of heavy flavor in IPRO = 11, and for vector meson producutin via IPRO = 2,3
    int IRPA;    //-- switch to select QCD process g* g* -> q qbar via IRPA = 1
    int IRPB;    //-- switch to select QCD process g* g -> g g via IRPB = 1
    int IRPC;    //-- switch to select QCD process g* q -> g q via IRPC = 1
    int ICCF;    //-- select CCFM or DGLAP mode (=1 CCFM, =0 DGLAP)
    int IGLU;    //-- select uPDF (1010 = set A, default)
    int IREM;    //-- switch for p-remnant treatment
    double PLEPIN;  //-- pz of incoming beam 1 (3500)
    double PPIN;    //-- pz of incoming beam 2 (-3500)
    double PT2CUT;  //-- pt2 cut in ME for massless partons
    double ACC1;    //-- accurary requested for grid optimisation step (BASES)
    double ACC2;    //-- accuracy requested for integration step (BASES)
    double SCALFA;  //-- scale factor for scale in alphas
    double SCALFAF; //-- scale factor for final state parton shower scale
    const char* UPDF; //-- path where updf grid files are stored
  };

  class Pythia6Service;
  
  class Cascade2Hadronizer : public BaseHadronizer  {
    
  public:
    Cascade2Hadronizer(edm::ParameterSet const& ps);
    ~Cascade2Hadronizer();

    bool initializeForExternalPartons(); //-- initializer for the LHE input
    bool initializeForInternalPartons();

    //-- Read the parameters and pass them to the common blocks
    bool cascadeReadParameters(const std::string& ParameterString);

    bool declareStableParticles(const std::vector<int>);
    void statistics();

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

     edm::ParameterSet fParameters;
     CASCADE_PARAM fCascade_Para;

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
