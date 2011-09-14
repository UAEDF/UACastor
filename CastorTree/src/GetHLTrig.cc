//-- Description: Function to retrieve HLT Trigger information (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Trigger Includes
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "./CastorTree.h"

bool HLTDebug = false;

void CastorTree::GetHLTrig(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  using namespace std;
  using namespace edm;

  //-- Find HLT Data Object Name
 
  edm::InputTag srcTriggerResults_("TriggerResults"); 
 
  if (srcTriggerResults_.process().empty()) {
 
    edm::InputTag srcTriggerEvent("hltTriggerSummaryAOD");
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByLabel(srcTriggerEvent,triggerEvent);
   
    string hltProcName = triggerEvent.provenance()->processName();
    if(HLTDebug) cout<<"HLT process = "<<hltProcName<<endl;
    srcTriggerResults_ = edm::InputTag(srcTriggerResults_.label()+"::"+hltProcName);
  }

  if(HLTDebug) cout<< "The used collection is: " << srcTriggerResults_<<endl;
 
  //-- Fetch HLT Data Object
 
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByLabel(srcTriggerResults_,trigResults);
 
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
 
  //-- Loop on triggers requested by user (config file)

  for(vector<string>::iterator hlt_name = hlt_bits.begin(); hlt_name != hlt_bits.end(); hlt_name++) {

    HLTrig.HLTmap[*hlt_name]= hasFired(*hlt_name,trigNames,*trigResults);
    HLTrig.HLTprescale[*hlt_name]= hltConfig.prescaleValue(iEvent,iSetup,*hlt_name);

    if(HLTDebug) cout<<(*hlt_name).c_str()<<" = "<<hasFired(*hlt_name,trigNames,*trigResults)<<endl;
  }
	
	
	// fetch the collection for the filter results
	edm::Handle<edm::TriggerResults> filterResults;
	try {
		iEvent.getByLabel(FilterResults_,filterResults);
		
		const edm::TriggerNames& filterNames = iEvent.triggerNames(*filterResults);
		
		// Loop on filter results requested by user (config file)
		for(vector<string>::iterator filter_name = filter_bits.begin(); filter_name != filter_bits.end(); filter_name++) {
			
			HLTrig.HLTmap[*filter_name]= hasFired(*filter_name,filterNames,*filterResults);
			HLTrig.HLTprescale[*filter_name]= hltConfig.prescaleValue(iEvent,iSetup,*filter_name);
			
			if(HLTDebug) cout<<(*filter_name).c_str()<<" = "<<hasFired(*filter_name,filterNames,*filterResults)<<endl;
		}
		
	}
	catch (cms::Exception& ex) {
		std::cout << "GetHLTTrig module: Input tag " << FilterResults_ << " not found";
	}
	
	
}

bool CastorTree::hasFired(const std::string& triggerName, const edm::TriggerNames& trigNames, const edm::TriggerResults& trigResults) const {

  unsigned index = trigNames.triggerIndex(triggerName);

  if (index>=trigNames.size()) {
    if(HLTDebug) cout<<"CastorTree::hasFired() ERROR: unknown trigger name"<<triggerName<<endl;
    return false;
  }

  return trigResults.accept(index);
}


