//-- Description: Function to retrieve Generated Kinematic (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "./CastorTree.h"

//-- DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETCollection.h"

bool GenKinDebug = false;

void CastorTree::GetGenKin(const edm::Event& iEvent) {

   using namespace std;
   using namespace edm;
   using namespace reco;

   //-- MC Process Id and PtHat 

   Handle<HepMCProduct> hepMCHandle;
   iEvent.getByLabel(hepMCColl_,hepMCHandle);

   const HepMC::GenEvent* GenEvt = hepMCHandle->GetEvent() ;
   GenKin.ProcessId = GenEvt->signal_process_id();
   GenKin.PtHat = GenEvt->event_scale();

   //-- PDF Info

   const HepMC::PdfInfo* pdfInfo = GenEvt->pdf_info();

   GenKin.x1 = pdfInfo->x1();
   GenKin.x2 = pdfInfo->x2();
   GenKin.Q  = pdfInfo->scalePDF(); 
   GenKin.Idparton1 = pdfInfo->id1();
   GenKin.Idparton2 = pdfInfo->id2();

   if(GenKinDebug) GenKin.Print();
}

