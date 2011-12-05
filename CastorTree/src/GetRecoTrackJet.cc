//-- Description: Function to retrieve Track Jet information (original author: Benoit Roland)

//--  system include files
#include <iostream>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//--DataFormats
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/TrackJet.h"
#include "DataFormats/JetReco/interface/TrackJetCollection.h"

#include "./CastorTree.h"

bool TrackJetDebug = false;

void CastorTree::GetRecoTrackJet(const edm::Event& iEvent, vector<MyTrackJet>& JetVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  JetVector.clear();
  
  Handle<TrackJetCollection> TrackJetcoll;
  iEvent.getByLabel(TrackJetColl_,TrackJetcoll);

  for (TrackJetCollection::const_iterator jet = TrackJetcoll->begin(); jet != TrackJetcoll->end(); jet++) {    
    
    MyTrackJet myjet;

    //-- 4 vector
    myjet.SetPxPyPzE(jet->px(),jet->py(),jet->pz(),jet->energy());

    //-- number of tracks
    myjet.ntrack = jet->numberOfTracks();
    
    //-- check jet to be associated to the hard primary vertex 
    myjet.pv = jet->fromHardVertex(); 

    if(TrackJetDebug) myjet.Print();
    JetVector.push_back(myjet);
  }

}

