//-- Description: Function to retrieve CaloTower

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"

#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

Bool_t CaloTowerDebug = false;

void CastorTree::GetCaloTower(const edm::Event& iEvent, vector<MyCaloTower>& CaloTowerVector) {

  using namespace std;
  using namespace edm;
  using namespace reco;

  CaloTowerVector.clear();

  Handle<CaloTowerCollection> CaloTowerColl;
  try { iEvent.getByLabel(CaloTower_,CaloTowerColl); }
  catch ( ... ) { cout << "[CastorTree::GetCaloTower] Can't find the collection " << CaloTower_ << endl; }
     
  CaloTowerVector.assign(CaloTowerColl->size(),MyCaloTower());

  Int_t i = 0;
  for (CaloTowerCollection::const_iterator iCT = CaloTowerColl->begin() ; iCT != CaloTowerColl->end() ; ++iCT , ++i) {
     
    CaloTowerVector[i].SetPxPyPzE(iCT->px(),iCT->py(),iCT->pz(),iCT->energy());
    CaloTowerVector[i].emEnergy = iCT->emEnergy();
    CaloTowerVector[i].hadEnergy = iCT->hadEnergy();

    //-- loop over CaloTower constituents
    for(size_t iconst = 0; iconst < iCT->constituentsSize(); iconst++) {
     
      DetId detId = iCT->constituent(iconst);

      if(detId.det()==DetId::Ecal) {
	EcalSubdetector ecalSubDet = (EcalSubdetector)detId.subdetId();
	if(ecalSubDet == EcalBarrel) CaloTowerVector[i].hasEB = true;
	else if(ecalSubDet == EcalEndcap) CaloTowerVector[i].hasEE = true;
      }

      else if(detId.det()==DetId::Hcal) {
	HcalDetId hcalDetId(detId);
	if(hcalDetId.subdet()==HcalBarrel) CaloTowerVector[i].hasHB = true;
	else if(hcalDetId.subdet()==HcalEndcap) CaloTowerVector[i].hasHE = true;
	else if(hcalDetId.subdet()==HcalForward) CaloTowerVector[i].hasHF = true;
      } 

    }

    CaloTowerVector[i].zside = iCT->zside();

    if(CaloTowerDebug) CaloTowerVector[i].Print();

  } // end for CaloTowerCollection 

}
