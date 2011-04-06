//-- Description: Function to retrieve Generated particles from HEPEVT (original author: Xavier Janssen)

//-- system include files
#include <memory>
#include <string>
#include <iostream>
   
//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- DataFormats
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

bool GenPartDebug = true;

void CastorTree::GetGenPart(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace std;
  using namespace edm;
  using namespace reco;

  //-- Clear GenPart List
  GenPart.clear();

  //-- Handle to access PDG data from iSetup
  ESHandle <ParticleDataTable> pdt;
  iSetup.getData(pdt);

   //-- Handle to access GenParticleCollection
   Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel(genPartColl_, genParticles);
  
   if (!genParticles.isValid()) {
     cerr << "CastorTree::GetGenPart] Error: non valid GenParticleCollection " << endl;
     return;
   }

   //-- position of the simulated primary vertex
   math::XYZPoint PosPVsim = (*genParticles)[2].vertex();

   simVertex.x = PosPVsim.X();
   simVertex.y = PosPVsim.Y();
   simVertex.z = PosPVsim.Z();

   if(GenPartDebug) simVertex.Print();

   //-- Loop on generated particle and store if status = 1
   if(GenPartDebug) cout << "number of gen particles: "<<genParticles->size()<<endl;
   
   for(GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++ p) {
     
     int st = p->status();
     MyGenPart genpart;

     genpart.SetPxPyPzE(p->px(),p->py(),p->pz(),p->energy());
     genpart.charge  = p->charge();

     genpart.pdgId   = p->pdgId();
     genpart.status  = p->status();
     genpart.name    = (pdt->particle(p->pdgId()))->name();

     //-- store if status = 1
     if(st==1) GenPart.push_back(genpart);
     if(st==1 && GenPartDebug) genpart.Print();
   }
}

