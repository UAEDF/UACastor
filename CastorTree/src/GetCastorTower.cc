//-- Description: Function to retrieve castor tower information (original author: Benoit Roland - added by Hans Van Haevermaet :p)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Castor Tower
#include "DataFormats/CastorReco/interface/CastorTower.h"

#include "./CastorTree.h"

bool CastorTowerDebug = false;

void CastorTree::GetCastorTower(const edm::Event& iEvent, vector<MyCastorTower>& CastorTowerVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  CastorTowerVector.clear();
  MyCastorTower mycastortower;
  
  edm::Handle<CastorTowerCollection> towercoll;  //-- uncorrected jets
  iEvent.getByLabel(CastorTower_,towercoll);

  if(towercoll.isValid()) {

    nCastorTower = towercoll->size();

    for(unsigned int i=0;i<towercoll->size();i++) {

      const CastorTower & castortower = (*towercoll)[i];

      mycastortower.energy = castortower.energy();
      mycastortower.pt = castortower.pt();
      mycastortower.eta = castortower.eta();
      mycastortower.phi = castortower.phi();

      mycastortower.fem = castortower.fem();
      mycastortower.eem = castortower.emEnergy();
      mycastortower.ehad = castortower.hadEnergy();

      mycastortower.depth = castortower.depth();
      mycastortower.fhot = castortower.fhot();

      mycastortower.ncell = castortower.rechitsSize();

      CastorTowerVector.push_back(mycastortower);
    
      if (CastorTowerDebug) mycastortower.Print();   
    }
  }
}
