//-- Description: Function to retrieve Evt Id information (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"

#include "./CastorTree.h"

bool EvtIdDebug = false;

void CastorTree::GetEvtId(const edm::Event& iEvent) {
	
	using namespace std;
	
	EvtId.Reset();
	
	EvtId.Run       = iEvent.id().run() ;   
	EvtId.Evt       = iEvent.id().event() ;
	EvtId.LumiBlock  = iEvent.luminosityBlock();
	
	edm::Timestamp Time = iEvent.time();
	
	EvtId.Time      = Time.value(); 
	EvtId.IsData    = iEvent.isRealData();
	EvtId.ExpType   = iEvent.experimentType();
	EvtId.Bunch     = iEvent.bunchCrossing();
	EvtId.Orbit     = iEvent.orbitNumber();
	
	if (iEvent.isRealData()) {
		// Get instantanious lumi information
		edm::LuminosityBlock const& lumiBlock = iEvent.getLuminosityBlock();
		edm::Handle<LumiSummary> lumiSummary;
		edm::Handle<LumiDetails> d;
		lumiBlock.getByLabel("lumiProducer",d);
		lumiBlock.getByLabel("lumiProducer", lumiSummary);
		const LumiSummary *lumi=lumiSummary.product();
		const float istlumi=lumi->avgInsDelLumi();
		const float istlumierr=d->lumiError(LumiDetails::kOCC1,iEvent.bunchCrossing());
		EvtId.IstLumi = istlumi;
		EvtId.IstLumiErr = istlumierr;
		
		// This is the call to get the lumi per bx:
		double istlumiPerBX=d->lumiValue(LumiDetails::kOCC1,iEvent.bunchCrossing());
		EvtId.IstLumiPerBX = istlumiPerBX;
	}
	
	if(EvtIdDebug) EvtId.Print();
}
