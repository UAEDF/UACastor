//-- Description: Function to retrieve PF Jet information (original author: Benoit Roland)

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
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "./CastorTree.h"
#include "./MyJetPtSorter.h"

bool PFJetDebug = false;

void CastorTree::GetRecoPFJet(const edm::Event& iEvent, const edm::EventSetup& iSetup, vector<MyJet>& JetVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  JetVector.clear();
  
  Handle<PFJetCollection> PFJetcoll;
  iEvent.getByLabel(PFJetColl_,PFJetcoll);
  
  const JetCorrector* PFJetcorrector = JetCorrector::getJetCorrector(PFJetJEC_,iSetup); 

  JetCorrectionUncertainty *PFJetCorUnc(0);

  ESHandle<JetCorrectorParametersCollection> PFJetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get(PFJetJECunc_,PFJetCorParColl);

  JetCorrectorParameters const & PFJetCorPar = (*PFJetCorParColl)["Uncertainty"];
  PFJetCorUnc = new JetCorrectionUncertainty(PFJetCorPar);
  
  for (PFJetCollection::const_iterator jet = PFJetcoll->begin(); jet != PFJetcoll->end(); jet++) {    

    MyJet myjet;

    //-- raw jet variables
    myjet.e_raw = jet->energy();
    myjet.pt_raw  = jet->pt();
    myjet.eta_raw = jet->eta();
    myjet.phi_raw = jet->phi();
    myjet.px_raw  = jet->px();
    myjet.py_raw  = jet->py();
    myjet.pz_raw  = jet->pz();

    //-- correction 
    PFJet corrected_jet = *jet;                            //-- copy orignial jet
    Double_t jec = PFJetcorrector->correction(jet->p4());  //-- calculate correction 
    corrected_jet.scaleEnergy(jec);                        //-- apply correction
    myjet.jec = jec;

    //-- uncertainty (function of the CORRECTED jet)
    PFJetCorUnc->setJetEta(corrected_jet.eta());
    PFJetCorUnc->setJetPt(corrected_jet.pt());    
    myjet.jec_unc = PFJetCorUnc->getUncertainty(true);

    //-- corrected jet variables
    myjet.e_cal = corrected_jet.energy();
    myjet.pt_cal  = corrected_jet.pt();
    myjet.eta_cal = corrected_jet.eta();
    myjet.phi_cal = corrected_jet.phi();
    myjet.px_cal  = corrected_jet.px();
    myjet.py_cal  = corrected_jet.py();
    myjet.pz_cal  = corrected_jet.pz();

    //-- estimators (PFjet only)
    myjet.fhad_ch = jet->chargedHadronEnergyFraction();
    myjet.fhad_ne = jet->neutralHadronEnergyFraction();

    myjet.fem_ch = jet->chargedEmEnergyFraction();
    myjet.fem_ne = jet->neutralEmEnergyFraction();

    myjet.multi_ch = jet->chargedMultiplicity();
    myjet.multi_ne = jet->neutralMultiplicity();
  
    myjet.multi_ch_had = jet->chargedHadronMultiplicity();
    myjet.multi_ne_had = jet->neutralHadronMultiplicity();
  
    myjet.multi_gamma = jet->photonMultiplicity();
    myjet.multi_ele = jet->electronMultiplicity();
    myjet.multi_mu = jet->muonMultiplicity();

    //-- estimators (Calojet only)
    myjet.fem = myjet.fem_ch + myjet.fem_ne;
    myjet.eem_EB = 0;
    myjet.eem_EE = 0;
    myjet.eem_HF = 0;

    myjet.fhad = myjet.fhad_ch + myjet.fhad_ne;
    myjet.ehad_HB = 0;
    myjet.ehad_HE = 0;
    myjet.ehad_HF = 0;
    myjet.ehad_HO = 0;

    myjet.n60 = 0;
    myjet.n90 = 0;

    myjet.emax_ecal = 0;
    myjet.emax_hcal = 0;

    myjet.n90hits = 0;
    myjet.HPD = 0;
    myjet.RBX = 0;
    myjet.sigma_eta = 0;
    myjet.sigma_phi = 0;

    //-- number of constituents (PFObject for PFjet, CaloTower for Calojet)
    myjet.nconstituent = jet->getPFConstituents().size();

    //-- number of tracks (PFjet only)
    if(jet->getTrackRefs().isAvailable()){
      reco::TrackRefVector vtracks = jet->getTrackRefs();
      myjet.ntrack = vtracks.size();
    }

    //-- jet ID
    myjet.TightPFJetId = GetTightPFJetId(myjet);
    myjet.LooseCaloJetId = false;
    myjet.TightCaloJetId = false;

    if(PFJetDebug) myjet.Print();
    JetVector.push_back(myjet);
  }

  if(PFJetDebug) {
    cout<<endl<<"unsorted jets collection: "<<endl;
    cout<<"number of jets: "<<JetVector.size()<<endl<<endl;
    CheckPtSorting(JetVector);
  }

  //-- sort on pt_cal
  stable_sort(JetVector.begin(),JetVector.end(),MyJetPtSorter());

  if(PFJetDebug) {
    cout<<endl<<"sorted jets collection (pt_cal): "<<endl;
    cout<<"number of jets: "<<JetVector.size()<<endl<<endl;
    CheckPtSorting(JetVector);
  }
	
	delete PFJetCorUnc;

}

Bool_t CastorTree::GetTightPFJetId(const MyJet& myjet) {

  using namespace std;
  using namespace edm;
  using namespace reco;

  //-- parameters for the selection

  double fhad_ne_CutUp;
  double fem_ne_CutUp;

  double fhad_ch_CutLow;
  double fem_ch_CutUp;

  unsigned int nconstituent_CutLow;
  int multi_ch_CutLow;

  //-- retrieve the parameters

  fhad_ne_CutUp = ParaSetTightPFJetID_.getParameter<double>("fhad_ne_CutUp");
  fem_ne_CutUp = ParaSetTightPFJetID_.getParameter<double>("fem_ne_CutUp");

  fhad_ch_CutLow = ParaSetTightPFJetID_.getParameter<double>("fhad_ch_CutLow");
  fem_ch_CutUp = ParaSetTightPFJetID_.getParameter<double>("fem_ch_CutUp");

  nconstituent_CutLow = ParaSetTightPFJetID_.getParameter<int>("nconstituent_CutLow");
  multi_ch_CutLow = ParaSetTightPFJetID_.getParameter<int>("multi_ch_CutLow");

  //-- thight selection for PF jet

  Bool_t accept = false;

  //-- selection depends on f_nh, f_ne and nconstituent
  if(myjet.fhad_ne < fhad_ne_CutUp && myjet.fem_ne < fem_ne_CutUp && myjet.nconstituent > nconstituent_CutLow) {

    //-- inside tracker acceptance, selection depends on f_ce, f_ch and multi_c
    if(fabs(myjet.eta_cal) < 2.4) {
      if(myjet.fem_ch < fem_ch_CutUp && myjet.fhad_ch > fhad_ch_CutLow && myjet.multi_ch > multi_ch_CutLow)
	accept = true;
    }

    //-- outside tracker acceptance, jet accepted without f_ce, f_ch and multi_c
    else accept = true;
  }

  return(accept);
}
