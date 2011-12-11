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

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "./CastorTree.h"
#include "./MyTrackJetPtSorter.h"

bool TrackJetDebug = false;

void CastorTree::GetRecoTrackJet(const edm::Event& iEvent, const edm::EventSetup& iSetup, vector<MyTrackJet>& JetVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  JetVector.clear();
  
  Handle<TrackJetCollection> TrackJetcoll;
  iEvent.getByLabel(TrackJetColl_,TrackJetcoll);
  
  const JetCorrector* TrackJetcorrector = JetCorrector::getJetCorrector(TrackJetJEC_,iSetup); 

  JetCorrectionUncertainty *TrackJetCorUnc(0);
  
  ESHandle<JetCorrectorParametersCollection> TrackJetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get(TrackJetJECunc_,TrackJetCorParColl);

  JetCorrectorParameters const & TrackJetCorPar = (*TrackJetCorParColl)["Uncertainty"];
  TrackJetCorUnc = new JetCorrectionUncertainty(TrackJetCorPar);
  
  for (TrackJetCollection::const_iterator jet = TrackJetcoll->begin(); jet != TrackJetcoll->end(); jet++) {    

    MyTrackJet myjet;

    //-- raw jet variables
    myjet.e_raw = jet->energy();
    myjet.pt_raw  = jet->pt();
    myjet.eta_raw = jet->eta();
    myjet.phi_raw = jet->phi();
    myjet.px_raw  = jet->px();
    myjet.py_raw  = jet->py();
    myjet.pz_raw  = jet->pz();

    //-- correction 
    TrackJet corrected_jet = *jet;                            //-- copy orignial jet
    Double_t jec = TrackJetcorrector->correction(jet->p4());  //-- calculate correction 
    corrected_jet.scaleEnergy(jec);                           //-- apply correction
    myjet.jec = jec;

    //-- uncertainty (function of the CORRECTED jet)
    TrackJetCorUnc->setJetEta(corrected_jet.eta());
    TrackJetCorUnc->setJetPt(corrected_jet.pt());    
    myjet.jec_unc = TrackJetCorUnc->getUncertainty(true);

    //-- corrected jet variables
    myjet.e_cal = corrected_jet.energy();
    myjet.pt_cal  = corrected_jet.pt();
    myjet.eta_cal = corrected_jet.eta();
    myjet.phi_cal = corrected_jet.phi();
    myjet.px_cal  = corrected_jet.px();
    myjet.py_cal  = corrected_jet.py();
    myjet.pz_cal  = corrected_jet.pz();

    //-- number of tracks
    myjet.ntrack = jet->numberOfTracks();
    
    //-- check jet to be associated to the hard primary vertex 
    myjet.pv = jet->fromHardVertex(); 

    if(TrackJetDebug) myjet.Print();
    JetVector.push_back(myjet);
  }

  if(TrackJetDebug) {
    cout<<endl<<"unsorted jets collection: "<<endl;
    cout<<"number of jets: "<<JetVector.size()<<endl<<endl;
    CheckPtSorting(JetVector);
  }
  
  //-- sort on pt_cal
  stable_sort(JetVector.begin(),JetVector.end(),MyTrackJetPtSorter());
  
  if(TrackJetDebug) {
    cout<<endl<<"sorted jets collection (pt_cal): "<<endl;
    cout<<"number of jets: "<<JetVector.size()<<endl<<endl;
    CheckPtSorting(JetVector);
  }
  
  delete TrackJetCorUnc;

}


void CastorTree::CheckPtSorting(vector<MyTrackJet>& JetVector) {
  int ijet = 0;
  for (vector<MyTrackJet>::const_iterator jet = JetVector.begin(); jet != JetVector.end(); jet++)
    cout<<"jet: "<<++ijet<<" pt cal: "<<jet->pt_cal<<" e cal: "<<jet->e_cal<<endl;
}


