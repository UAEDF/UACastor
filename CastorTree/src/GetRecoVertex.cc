//-- Description: Function to retrieve vertex information (original author: Xavier Janssen)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//-- Vertex
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "UACastor/CastorTree/interface/CastorTree.h"

bool RecoVtxDebug = true;

void CastorTree::GetRecoVertex(const edm::Event& iEvent, const char VertexCollName[60], vector<MyVertex>& VertexVector) {

   using namespace std;
   using namespace edm;
   using namespace reco;

   VertexVector.clear();
   MyVertex myvertex;

   Handle<reco::VertexCollection> vtxcoll;
   iEvent.getByLabel(VertexCollName,vtxcoll);

   if (RecoVtxDebug) cout<<"name of the requested vertex collection: "<<VertexCollName<<endl;

   for(VertexCollection::const_iterator pv = vtxcoll->begin(); pv!= vtxcoll->end(); ++pv)
   {
     myvertex.x         = pv->x();
     myvertex.y         = pv->y();
     myvertex.z         = pv->z();

     myvertex.ex        = pv->xError();
     myvertex.ey        = pv->yError();
     myvertex.ez        = pv->zError();

     myvertex.validity  = pv->isValid();
     myvertex.fake      = pv->isFake();

      if(!myvertex.fake) myvertex.chi2n = pv->normalizedChi2();
      else myvertex.chi2n = -99.;

      myvertex.ntracks = pv->tracksSize() ;

      VertexVector.push_back(myvertex);

      if (RecoVtxDebug) myvertex.Print();
   }   
}

