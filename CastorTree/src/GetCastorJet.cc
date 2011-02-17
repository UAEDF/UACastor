//-- Description: Function to retrieve castor jet information (original author: Benoit Roland)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Castor Jet
#include "DataFormats/JetReco/interface/BasicJet.h"
#include "DataFormats/JetReco/interface/CastorJetID.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

bool CastorJetDebug = true;

void CastorTree::GetCastorJet(const edm::Event& iEvent, vector<MyCastorJet>& CastorJetVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  CastorJetVector.clear();
  MyCastorJet mycastorjet;
  
  edm::Handle<edm::View< reco::BasicJet > > basicjetcoll;  //-- uncorrected jets
  iEvent.getByLabel(BasicJet_,basicjetcoll);

  edm::Handle<reco::CastorJetIDValueMap> jetIdMap;
  iEvent.getByLabel(CastorJetID_,jetIdMap);

  if(basicjetcoll.isValid()) {
    
    for(edm::View<reco::BasicJet>::const_iterator ibegin = basicjetcoll->begin(), iend = basicjetcoll->end(), ijet = ibegin; ijet != iend; ++ijet) {
      
      unsigned int idx = ijet - ibegin;
      const BasicJet & basicjet = (*basicjetcoll)[idx];
      
      mycastorjet.energy = basicjet.energy();
      mycastorjet.pt = basicjet.pt();
      mycastorjet.eta = basicjet.eta();
      mycastorjet.phi = basicjet.phi();

      edm::RefToBase<reco::BasicJet> jetRef = basicjetcoll->refAt(idx);
      reco::CastorJetID const & jetId = (*jetIdMap)[jetRef];

      mycastorjet.fem = jetId.fem;
      mycastorjet.eem = jetId.emEnergy;
      mycastorjet.ehad = jetId.hadEnergy;

      mycastorjet.width = jetId.width;
      mycastorjet.depth = jetId.depth;
      mycastorjet.fhot = jetId.fhot;
      mycastorjet.sigmaz = jetId.sigmaz;

      mycastorjet.ntower = jetId.nTowers;

      CastorJetVector.push_back(mycastorjet);
    
      if (CastorJetDebug) mycastorjet.Print();   
    }
  }
}
