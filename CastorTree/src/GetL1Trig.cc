//-- Description: Function to retrieve L1 Trigger information (original author: Benoit Roland)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Trigger Includes
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenuFwd.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GtTriggerMenuLite.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"

#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"

#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

#include "./CastorTree.h"

bool L1TrigDebug = false;

void CastorTree::GetL1Trig(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using namespace std;
  using namespace edm;

  L1Trig.Reset();

   //-- L1 Global Trigger Utility

  L1GtUtils *L1GTUtility = new L1GtUtils();
  L1GTUtility->retrieveL1EventSetup(iSetup);

  //-- input tag for L1GtTriggerMenuLite retrieved from provenance
  if (L1GT_TrigMenuLite_Prov_) L1GTUtility->retrieveL1GtTriggerMenuLite(iEvent);

  //-- input tag for L1GtTriggerMenuLite explicitly given
  else L1GTUtility->retrieveL1GtTriggerMenuLite(iEvent,L1GT_TrigMenuLite_);

  ESHandle< L1GtTriggerMenu > L1GTTM;
  iSetup.get< L1GtTriggerMenuRcd >().get(L1GTTM);

  const AlgorithmMap L1Phys(L1GTTM->gtAlgorithmMap());
  const AlgorithmMap L1Tech(L1GTTM->gtTechnicalTriggerMap());
 
  //-- L1 Physical Trigger (Algo Trigger)

  for (AlgorithmMap::const_iterator iphys = L1Phys.begin(); iphys != L1Phys.end(); ++iphys) {
    
    if (iphys->second.algoBitNumber() > 127 ) {
      cout<<"error L1 Physical Trigger "<<iphys->second.algoName()<<" has bit number "<<iphys->second.algoBitNumber()<<" > 127 \n"<<"Skipping";
      continue;
    }

    L1GtUtils::TriggerCategory category;
    int bit;

    if (!L1GTUtility->l1AlgoTechTrigBitNumber(iphys->second.algoName(),category,bit)) {
      cout<<"error L1 Physical Trigger "<<iphys->second.algoName()<<" not found in the L1 menu \n"<<"Skipping";
      continue;
    }
    
    bool decisionBeforeMask;
    bool decisionAfterMask;
    int  prescale;
    int  mask;
    int errorcode = -1;

    errorcode = L1GTUtility->l1Results(iEvent,iphys->second.algoName(),decisionBeforeMask,decisionAfterMask,prescale,mask);
    if (errorcode) {
      cout<<"error L1 Physical Trigger " <<iphys->second.algoName()<<" decision has error code "<<errorcode<<" from L1GtUtils \n"<<"Skipping";
      continue;
    }

    L1Trig.SetPhys(iphys->second.algoName(),(unsigned) bit,(bool) mask,decisionBeforeMask,decisionAfterMask,(unsigned) prescale,iphys->second.algoAlias());
  }

  //-- L1 Technical Trigger 

  for (AlgorithmMap::const_iterator itech = L1Tech.begin(); itech != L1Tech.end(); ++itech) {

    if (itech->second.algoBitNumber() > 127 ) {
      cout<<"error L1 Technical Trigger "<<itech->second.algoName()<<" has bit number "<<itech->second.algoBitNumber()<<" > 127 \n"<<"Skipping";
      continue;
    }

    L1GtUtils::TriggerCategory category;
    int bit;

    if (!L1GTUtility->l1AlgoTechTrigBitNumber(itech->second.algoName(),category,bit)) {
      cout<<"error L1 Technical Trigger "<<itech->second.algoName()<<" not found in the L1 menu \n"<<"Skipping";
      continue;
    }

    bool decisionBeforeMask;
    bool decisionAfterMask;
    int  prescale;
    int  mask;
    int errorcode = -1;

    errorcode = L1GTUtility->l1Results(iEvent,itech->second.algoName(),decisionBeforeMask,decisionAfterMask,prescale,mask);
    if (errorcode) {
      cout<<"error L1 Technical Trigger " <<itech->second.algoName()<<" decision has error code "<<errorcode<<" from L1GtUtils \n"<<"Skipping";
      continue;
    }

    L1Trig.SetTech(itech->second.algoName(),(unsigned) bit,(bool) mask,decisionBeforeMask,decisionAfterMask,(unsigned) prescale,itech->second.algoAlias());
  }

  if(L1TrigDebug) L1Trig.Print();
	
	delete L1GTUtility;

}

