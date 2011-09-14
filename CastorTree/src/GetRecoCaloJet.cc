//-- Description: Function to retrieve Calo Jet information (original author: Benoit Roland)

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
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "DataFormats/JetReco/interface/JetID.h"
#include "DataFormats/Common/interface/ValueMap.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "./CastorTree.h"
#include "./MyJetPtSorter.h"

bool CaloJetDebug = false;

void CastorTree::GetRecoCaloJet(const edm::Event& iEvent, const edm::EventSetup& iSetup, vector<MyJet>& JetVector) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  
  JetVector.clear();
  
  Handle<CaloJetCollection> CaloJetcoll;
  iEvent.getByLabel(CaloJetColl_,CaloJetcoll);

  Handle<reco::JetIDValueMap> CaloJetId;
  iEvent.getByLabel(CaloJetId_,CaloJetId);
  reco::JetIDValueMap jetid = *CaloJetId;

  const JetCorrector* CaloJetcorrector = JetCorrector::getJetCorrector(CaloJetJEC_,iSetup); 

  JetCorrectionUncertainty *CaloJetCorUnc(0);

  ESHandle<JetCorrectorParametersCollection> CaloJetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get(CaloJetJECunc_,CaloJetCorParColl);

  JetCorrectorParameters const & CaloJetCorPar = (*CaloJetCorParColl)["Uncertainty"];
  CaloJetCorUnc = new JetCorrectionUncertainty(CaloJetCorPar);
  
  for (CaloJetCollection::const_iterator jet = CaloJetcoll->begin(); jet != CaloJetcoll->end(); jet++) {    
    
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
    CaloJet corrected_jet = *jet;                            //-- copy orignial jet
    Double_t jec = CaloJetcorrector->correction(jet->p4());  //-- calculate correction 
    corrected_jet.scaleEnergy(jec);                          //-- apply correction
    myjet.jec = jec;

    //-- uncertainty (function of the CORRECTED jet)
    CaloJetCorUnc->setJetEta(corrected_jet.eta());
    CaloJetCorUnc->setJetPt(corrected_jet.pt());    
    myjet.jec_unc = CaloJetCorUnc->getUncertainty(true);

    //-- corrected jet variables
    myjet.e_cal = corrected_jet.energy();
    myjet.pt_cal  = corrected_jet.pt();
    myjet.eta_cal = corrected_jet.eta();
    myjet.phi_cal = corrected_jet.phi();
    myjet.px_cal  = corrected_jet.px();
    myjet.py_cal  = corrected_jet.py();
    myjet.pz_cal  = corrected_jet.pz();

    //-- estimators (PFjet only)
    myjet.fhad_ch = 0;
    myjet.fhad_ne = 0;

    myjet.fem_ch = 0;
    myjet.fem_ne = 0;

    myjet.multi_ch = 0;
    myjet.multi_ne = 0;
  
    myjet.multi_ch_had = 0;
    myjet.multi_ne_had = 0;
  
    myjet.multi_gamma = 0;
    myjet.multi_ele = 0;
    myjet.multi_mu = 0;

    //-- estimators (Calojet only)
    myjet.fem = jet->emEnergyFraction(); 
    myjet.eem_EB = jet->emEnergyInEB();
    myjet.eem_EE = jet->emEnergyInEE();
    myjet.eem_HF = jet->emEnergyInHF();

    myjet.fhad = jet->energyFractionHadronic();
    myjet.ehad_HB = jet->hadEnergyInHB();
    myjet.ehad_HE = jet->hadEnergyInHE();
    myjet.ehad_HF = jet->hadEnergyInHF();
    myjet.ehad_HO = jet->hadEnergyInHO();

    myjet.n60 = jet->n60();
    myjet.n90 = jet->n90();

    myjet.emax_ecal = jet->maxEInEmTowers();
    myjet.emax_hcal = jet->maxEInHadTowers();

    short int jetpos = jet - CaloJetcoll->begin();
    reco::CaloJetRef jetref(CaloJetcoll,jetpos);

    myjet.n90hits = jetid[jetref].n90Hits;
    myjet.HPD = jetid[jetref].fHPD;
    myjet.RBX = jetid[jetref].fRBX;
    myjet.sigma_eta = sqrt(corrected_jet.etaetaMoment());
    myjet.sigma_phi = sqrt(corrected_jet.phiphiMoment());

    //-- number of constituents (PFObject for PFjet, CaloTower for Calojet)
    myjet.nconstituent = jet->getCaloConstituents().size();

    //-- number of tracks (PFjet only)
    myjet.ntrack = 0;
   
    //-- jet ID
    myjet.TightPFJetId = false;
    myjet.LooseCaloJetId = GetLooseCaloJetId(myjet);
    myjet.TightCaloJetId = GetTightCaloJetId(myjet);

    if(CaloJetDebug) myjet.Print();
    JetVector.push_back(myjet);
  }

  if(CaloJetDebug) {
    cout<<"unsorted jets collection: "<<endl;
    CheckPtSorting(JetVector);
  }  

  //-- sort on pt_cal
  stable_sort(JetVector.begin(),JetVector.end(),MyJetPtSorter());

  if(CaloJetDebug) {
    cout<<"sorted jets collection (pt_cal): "<<endl;
    CheckPtSorting(JetVector);
  }
	
	delete CaloJetCorUnc;

}

Bool_t CastorTree::GetLooseCaloJetId(const MyJet& myjet) {

  using namespace std;
  using namespace edm;
  using namespace reco;

  //-- parameters for the selection

  Double_t HPD_CutUp;
  Int_t n90hits_CutLow;
  Double_t fem_CutLow;

  //-- retrieve the parameters

  HPD_CutUp = ParaSetLooseCaloJetID_.getParameter<double>("HPD_CutUp");
  n90hits_CutLow = ParaSetLooseCaloJetID_.getParameter<int>("n90hits_CutLow");
  fem_CutLow = ParaSetLooseCaloJetID_.getParameter<double>("fem_CutLow");

  //-- loose selection for Calo jet

  Bool_t accept = false;

  //-- loose jet id
  if(myjet.HPD < HPD_CutUp && myjet.n90hits > n90hits_CutLow) {
    
    //-- inside tracker acceptance depends on fem
    if(fabs(myjet.eta_cal) < 2.4) {
      if(myjet.fem > fem_CutLow) accept = true; 
    }
    
    //-- outside tracker acceptance, jet accepted without fem
    else accept = true;
  }

  return(accept);
}

Bool_t CastorTree::GetTightCaloJetId(const MyJet& myjet) {

  using namespace std;
  using namespace edm;
  using namespace reco;

  //-- parameters for the selection

  Double_t HPD_CutUp;
  Int_t n90hits_CutLow;
  Double_t RBX_CutUp;
  Double_t sigma_eta_CutLow;
  Double_t sigma_phi_CutLow;
  Double_t fem_CutLow;

  //-- retrieve the parameters

  HPD_CutUp = ParaSetTightCaloJetID_.getParameter<double>("HPD_CutUp");
  n90hits_CutLow = ParaSetTightCaloJetID_.getParameter<int>("n90hits_CutLow");
  RBX_CutUp = ParaSetTightCaloJetID_.getParameter<double>("RBX_CutUp");
  sigma_eta_CutLow = ParaSetTightCaloJetID_.getParameter<double>("sigma_eta_CutLow");
  sigma_phi_CutLow = ParaSetTightCaloJetID_.getParameter<double>("sigma_phi_CutLow");
  fem_CutLow = ParaSetTightCaloJetID_.getParameter<double>("fem_CutLow");

  //-- tight selection for Calo jet

  Bool_t accept = false;

  //-- tight jet id
  if(myjet.HPD < HPD_CutUp && myjet.n90hits > n90hits_CutLow && myjet.RBX < RBX_CutUp 
     && myjet.sigma_eta > sigma_eta_CutLow && myjet.sigma_phi > sigma_phi_CutLow) {
    
    //-- inside tracker acceptance depends on fem
    if(fabs(myjet.eta_cal) < 2.4) {
      if(myjet.fem > fem_CutLow) accept = true;
    }
    
    //-- outside tracker acceptance, jet accepted without fem
    else accept = true;
  }
  
  return(accept);
}

void CastorTree::CheckPtSorting(vector<MyJet>& JetVector) {
  int ijet = 1;
  for (vector<MyJet>::const_iterator jet = JetVector.begin(); jet != JetVector.end(); jet++)
    cout<<"jet: "<<++ijet<<" pt cal: "<<jet->pt_cal<<" e cal: "<<jet->e_cal<<endl;
}
