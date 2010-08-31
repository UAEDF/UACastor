   
// -*- C++ -*-

#include "Cascade2Hadronizer.h"

#include "HepMC/GenEvent.h"
#include "HepMC/PdfInfo.h"
//-- #include "HepMC/PythiaWrapper6_2.h"
//-- #include "CascadeWrapper.h"  //-- should be put in HepMC /afs/cern.ch/sw/lcg/external/HepMC
#include "HepMC/HEPEVT_Wrapper.h"
#include "HepMC/IO_HEPEVT.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "GeneratorInterface/Core/interface/FortranCallback.h"
#include "GeneratorInterface/LHEInterface/interface/LHERunInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "GeneratorInterface/PartonShowerVeto/interface/JetMatching.h"

HepMC::IO_HEPEVT conv;

#include "HepPID/ParticleIDTranslations.hh"

// NOTE: here a number of Pythia6 routines are declared,
// plus some functionalities to pass around Pythia6 params

#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Service.h"
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Declarations.h"

namespace gen
{

extern "C" {
  
  // these two are NOT part of Pythi6 core code but are "custom" add-ons
  // we keep them interfaced here, rather than in GenExtensions, because
  // they tweak not at the ME level, but a step further, at the framgmentation
  
  // stop-hadrons
  void pystrhad_();   // init stop-hadrons (id's, names, charges...)
  //void pystfr_(int&); // tweaks fragmentation, fragments the string near to a stop, 
                      // to form stop-hadron by producing a new q-qbar pair
  
  // gluino/r-hadrons
  //void pyglrhad_();
  //void pyglfr_();   // tweaks fragmentation, fragment the string near to a gluino,
                    // to form gluino-hadron, either by producing a new g-g pair,
                    // or two new q-qbar ones
} // extern "C"
  
struct {
  int n, npad, k[5][pyjets_maxn];
  double p[5][pyjets_maxn], v[5][pyjets_maxn];
} pyjets_local;
  
Cascade2Hadronizer::Cascade2Hadronizer(edm::ParameterSet const& ps) 
  : BaseHadronizer(ps),
    //-- fPy6Service(new Pythia6ServiceWithCallback(ps) ), // this will store py6 params for further settings
    fCOMEnergy(ps.getParameter<double>("comEnergy")),
    fHepMCVerbosity(ps.getUntrackedParameter<bool>("pythiaHepMCVerbosity",false)),
    fMaxEventsToPrint(ps.getUntrackedParameter<int>("maxEventsToPrint", 0)),
    fPythiaListVerbosity(ps.getUntrackedParameter<int>("pythiaPylistVerbosity", 0)),
    fDisplayPythiaBanner(ps.getUntrackedParameter<bool>("displayPythiaBanner",false)),
    fDisplayPythiaCards(ps.getUntrackedParameter<bool>("displayPythiaCards",false))
{ 
  
  // J.Y.: the following 4 params are "hacked", in the sense 
  // that they're tracked but get in optionally;
  // this will be fixed once we update all applications
  
  fStopHadronsEnabled = false;
  if ( ps.exists( "stopHadrons" ) )
    fStopHadronsEnabled = ps.getParameter<bool>("stopHadrons") ;
  
  fGluinoHadronsEnabled = false;
  if ( ps.exists( "gluinoHadrons" ) )
    fGluinoHadronsEnabled = ps.getParameter<bool>("gluinoHadrons");

  fImposeProperTime = false;
  if ( ps.exists( "imposeProperTime" ) )
    fImposeProperTime = ps.getParameter<bool>("imposeProperTime");
  
  fConvertToPDG = false;
  if ( ps.exists( "doPDGConvert" ) )
    fConvertToPDG = ps.getParameter<bool>("doPDGConvert");
  
  // first of all, silence Pythia6 banner printout, unless display requested
  if ( !fDisplayPythiaBanner )
    {
      if (!call_pygive("MSTU(12)=12345")) 
	{
	  throw edm::Exception(edm::errors::Configuration,"PythiaError") 
	    <<" Pythia did not accept MSTU(12)=12345";
	}
    }
  
  // silence printouts from PYGIVE, unless display requested
  if ( ! fDisplayPythiaCards )
    {
      if (!call_pygive("MSTU(13)=0")) 
	{
	  throw edm::Exception(edm::errors::Configuration,"PythiaError") 
	    <<" Pythia did not accept MSTU(13)=0";
	}
    }
  
  // tmp stuff to deal with EvtGen corrupting pyjets
  // NPartsBeforeDecays = 0;
  flushTmpStorage();
}
  
Cascade2Hadronizer::~Cascade2Hadronizer()
{
  if ( fPy6Service != 0 ) delete fPy6Service;
}

void Cascade2Hadronizer::flushTmpStorage()
{

  pyjets_local.n = 0 ;
  pyjets_local.npad = 0 ;
   for ( int ip=0; ip<pyjets_maxn; ip++ )
   {
      for ( int i=0; i<5; i++ )
      {
         pyjets_local.k[i][ip] = 0;
	 pyjets_local.p[i][ip] = 0.;
	 pyjets_local.v[i][ip] = 0.;
      }
   }
   return;

}

void Cascade2Hadronizer::fillTmpStorage()
{

   pyjets_local.n = pyjets.n;
   pyjets_local.npad = pyjets.npad;
   for ( int ip=0; ip<pyjets_maxn; ip++ )
   {
      for ( int i=0; i<5; i++ )
      {
         pyjets_local.k[i][ip] = pyjets.k[i][ip];
	 pyjets_local.p[i][ip] = pyjets.p[i][ip];
	 pyjets_local.v[i][ip] = pyjets.v[i][ip];
      }
   }
   
   return ;

}

void Cascade2Hadronizer::finalizeEvent()
{
   // Do we need this for CASCADE ?????
   
   bool lhe = lheEvent() != 0;

   HepMC::PdfInfo pdf;

   // if we are in hadronizer mode, we can pass on information 
   // from the LHE input
   if (lhe)
     {
       lheEvent()->fillEventInfo( event().get() );
       lheEvent()->fillPdfInfo( &pdf );
     }

   // filling in factorization "Q scale" now! pthat moved to binningValues()

   //   if (!lhe || event()->signal_process_id() < 0) event()->set_signal_process_id( pypars.msti[0] );
   //   if (!lhe || event()->event_scale() < 0)       event()->set_event_scale( pypars.pari[22] );
   //   if (!lhe || event()->alphaQED() < 0)          event()->set_alphaQED( pyint1.vint[56] );
   //   if (!lhe || event()->alphaQCD() < 0)          event()->set_alphaQCD( pyint1.vint[57] );
   
   // get pdf info directly from Pythia6 and set it up into HepMC::GenEvent
   // S. Mrenna: Prefer vint block
   
   //   if (!lhe || pdf.id1() < 0)      pdf.set_id1( pyint1.mint[14] == 21 ? 0 : pyint1.mint[14] );
   //   if (!lhe || pdf.id2() < 0)      pdf.set_id2( pyint1.mint[15] == 21 ? 0 : pyint1.mint[15] );
   //   if (!lhe || pdf.x1() < 0)       pdf.set_x1( pyint1.vint[40] );
   //   if (!lhe || pdf.x2() < 0)       pdf.set_x2( pyint1.vint[41] );
   //   if (!lhe || pdf.pdf1() < 0)     pdf.set_pdf1( pyint1.vint[38] / pyint1.vint[40] );
   //   if (!lhe || pdf.pdf2() < 0)     pdf.set_pdf2( pyint1.vint[39] / pyint1.vint[41] );
   //   if (!lhe || pdf.scalePDF() < 0) pdf.set_scalePDF( pyint1.vint[50] );

   event()->set_pdf_info( pdf ) ;

   // this is "standard" Py6 event weight (corresponds to PYINT1/VINT(97)
   
   // if (lhe && std::abs(lheRunInfo()->getHEPRUP()->IDWTUP) == 4)
   // translate mb to pb (CMS/Gen "convention" as of May 2009)
   // event()->weights().push_back( pyint1.vint[96] * 1.0e9 );
   // else
   // event()->weights().push_back( pyint1.vint[96] );
  
   // this is event weight as 1./VINT(99) (PYINT1/VINT(99) is returned by the PYEVWT) 
   
   // event()->weights().push_back( 1./(pyint1.vint[98]) );

   // now create the GenEventInfo product from the GenEvent and fill
   // the missing pieces

   eventInfo().reset( new GenEventInfoProduct( event().get() ) );

   // in Pythia6 pthat is used to subdivide samples into different bins
   // in LHE mode the binning is done by the external ME generator
   // which is likely not pthat, so only filling it for Py6 internal mode
   if (!lhe)
   {
     //  eventInfo()->setBinningValues( std::vector<double>(1, pypars.pari[16]) );
   }

   // here we treat long-lived particles
   //
   if ( fImposeProperTime || pydat1.mstj[21]==3 || pydat1.mstj[21]==4 ) imposeProperTime();

   // convert particle IDs Py6->PDG, if requested
   if ( fConvertToPDG ) {
      for ( HepMC::GenEvent::particle_iterator part = event()->particles_begin(); 
                                               part != event()->particles_end(); ++part) {
         (*part)->set_pdg_id(HepPID::translatePythiatoPDT((*part)->pdg_id()));
      }
   }
   
   // service printouts, if requested
   //
   if (fMaxEventsToPrint > 0) 
   {
      fMaxEventsToPrint--;
      if (fPythiaListVerbosity) call_pylist(fPythiaListVerbosity);
      if (fHepMCVerbosity) 
      {
	//         std::cout << "Event process = " << pypars.msti[0] << std::endl 
	std::cout << "Event process (from CASCADE to come) = " << std::endl 
		  << "----------------------" << std::endl;
	event()->print();
      }
   }
   
   return;
}

bool Cascade2Hadronizer::generatePartonsAndHadronize()
{
   Pythia6Service::InstanceWrapper guard(fPy6Service);	// grab Py6 instance

   FortranCallback::getInstance()->resetIterationsPerEvent();
      
   // generate event with Pythia6
   //
   
   if ( fStopHadronsEnabled || fGluinoHadronsEnabled )
   {
      // call_pygive("MSTJ(1)=-1");
      call_pygive("MSTJ(14)=-1");
   }
   
   //-- call_event();
   
   /*
   if ( fStopHadronsEnabled || fGluinoHadronsEnabled )
   {
      // call_pygive("MSTJ(1)=1");
      call_pygive("MSTJ(14)=1");
      int ierr=0;
     
      if ( fStopHadronsEnabled ) 
      {
         pystfr_(ierr);
	 if ( ierr != 0 ) // skip failed events
	 {
	    event().reset();
	    return false;
	 }
      }
      if ( fGluinoHadronsEnabled ) pyglfr_();
   }
   */

   if ( pyint1.mint[50] != 0 ) // skip event if py6 considers it bad
   {
      event().reset();
      return false;
   }
   
   call_pyhepc(1);
   event().reset( conv.read_next_event() );
   
   // this is to deal with post-gen tools & residualDecay() that may reuse PYJETS
   //
   flushTmpStorage();
   fillTmpStorage();
      
   return true;
}

bool Cascade2Hadronizer::initializeForExternalPartons()
{
   Pythia6Service::InstanceWrapper guard(fPy6Service);	// grab Py6 instance

   // note: CSA mode is NOT supposed to woirk with external partons !!!
   
   fPy6Service->setGeneralParams();
   fPy6Service->setPYUPDAParams(false);

   FortranCallback::getInstance()->setLHERunInfo( lheRunInfo() );

   
   //--initialise CASCADE parameters
   call_casini();

   //--read steering file
   //    call_steer();
   //-- change standard parameters of CASCADE
   //    call_cascha();
   //-- change standard parameters of JETSET/PYTHIA
   //    call_pytcha();
  
   //-- set up for running CASCADE  
   //call_cascade();
   //-- print result from integration
   //call_caend(1);   

   return true;
}

void Cascade2Hadronizer::imposeProperTime()
{

  // this is practically a copy/paste of the original code by J.Alcaraz,
  // taken directly from PythiaSource

  int dumm=0;
  HepMC::GenEvent::vertex_const_iterator vbegin = event()->vertices_begin();
  HepMC::GenEvent::vertex_const_iterator vend = event()->vertices_end();
  HepMC::GenEvent::vertex_const_iterator vitr = vbegin;
  for (; vitr != vend; ++vitr )
    {
      HepMC::GenVertex::particle_iterator pbegin = (*vitr)->particles_begin(HepMC::children);
      HepMC::GenVertex::particle_iterator pend = (*vitr)->particles_end(HepMC::children);
      HepMC::GenVertex::particle_iterator pitr = pbegin;
      for (; pitr != pend; ++pitr)
	{
	  if ((*pitr)->end_vertex()) continue;
	  if ((*pitr)->status()!=1) continue;

	  int pdgcode= abs((*pitr)->pdg_id());
	  // Do nothing if the particle is not expected to decay
	  if ( pydat3.mdcy[0][pycomp_(pdgcode)-1] !=1 ) continue;

	  double ctau = pydat2.pmas[3][pycomp_(pdgcode)-1];
	  HepMC::FourVector mom = (*pitr)->momentum();
	  HepMC::FourVector vin = (*vitr)->position();
	  double x = 0.;
	  double y = 0.;
	  double z = 0.;
	  double t = 0.;
	  bool decayInRange = false;
	  while (!decayInRange)
	    {
	      double unif_rand = fPy6Service->call(pyr_, &dumm);
	      // Value of 0 is excluded, so following line is OK
	      double proper_length = - ctau * log(unif_rand);
	      double factor = proper_length/mom.m();
	      x = vin.x() + factor * mom.px();
	      y = vin.y() + factor * mom.py();
	      z = vin.z() + factor * mom.pz();
	      t = vin.t() + factor * mom.e();
	      // Decay must be happen outside a cylindrical region
	      if (pydat1.mstj[21]==4) {
		if (std::sqrt(x*x+y*y)>pydat1.parj[72] || fabs(z)>pydat1.parj[73]) decayInRange = true;
		// Decay must be happen outside a given sphere
	      }
	      else if (pydat1.mstj[21]==3) {
		if (std::sqrt(x*x+y*y+z*z)>pydat1.parj[71]) decayInRange = true;
	      }
	      // Decay is always OK otherwise
	      else {
		decayInRange = true;
	      }
	    }

	  HepMC::GenVertex* vdec = new HepMC::GenVertex(HepMC::FourVector(x,y,z,t));
	  event()->add_vertex(vdec);
	  vdec->add_particle_in((*pitr));
	}
    }

  return;

}


const char* Cascade2Hadronizer::classname() const
{
   return "gen::Cascade2Hadronizer";
}

} // namespace gen
