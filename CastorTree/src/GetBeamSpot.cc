//-- Description: Function to retrieve beam spot information (original author: Benoit Roland)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Beam Spot
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "./CastorTree.h"

bool BeamSpotDebug = false;

void CastorTree::GetBeamSpot(const edm::Event& iEvent) {

   using namespace std;
   using namespace edm;
   using namespace reco;

   Handle<reco::BeamSpot> BShandle;
   iEvent.getByLabel("offlineBeamSpot",BShandle);

   const reco::BeamSpot* BS = BShandle.product();

   beamSpot.x           = BS->position().x();    
   beamSpot.y           = BS->position().y();    
   beamSpot.z           = BS->position().z();    

   beamSpot.ex          = BS->x0Error();
   beamSpot.ey          = BS->y0Error();
   beamSpot.ez          = BS->z0Error();

   beamSpot.sigmaZ      = BS->sigmaZ();
   beamSpot.dxdz        = BS->dxdz();
   beamSpot.dydz        = BS->dydz();

   beamSpot.esigmaZ     = BS->sigmaZ0Error();
   beamSpot.edxdz       = BS->dxdzError();
   beamSpot.edydz       = BS->dydzError();

   beamSpot.BeamWidthX  = BS->BeamWidthX() ;
   beamSpot.BeamWidthY  = BS->BeamWidthY() ;

   beamSpot.eBeamWidthX = BS->BeamWidthXError();
   beamSpot.eBeamWidthY = BS->BeamWidthYError();

   if(BeamSpotDebug) beamSpot.Print();
}

