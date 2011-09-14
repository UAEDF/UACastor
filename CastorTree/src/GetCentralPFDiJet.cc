//-- Description: Function to retrieve central PF Di Jet information (original author: Alexander FlossDorf)

//--  system include files
#include <iostream>
#include <vector>

//-- user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

//--DataFormats
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include "./CastorTree.h"

bool CentralPFDiJetDebug = false;

void CastorTree::GetCentralPFDiJet(const vector<MyJet>& JetVector, MyDiJet& dijet) {

  using namespace std;
  using namespace edm;
  using namespace reco;
      
  //-- collection to save information

  dijet.Reset();

  //-- central jet selection

  bool accept = false;
  
  short int posJet1 = -1;
  short int posJet2 = -1;

  double refPt1 = 0;
  double refPt2 = 0;

  //-- find the two highest pt jets (corrected pt)

  for(vector<MyJet>::const_iterator jet = JetVector.begin(); jet < JetVector.end(); ++jet) {

    Double_t ptcal = jet->pt_cal;

    if(ptcal > refPt1) {
      refPt2 = refPt1;
      posJet2 = posJet1;      
      refPt1 = ptcal;
      posJet1 = jet - JetVector.begin();
    }

    else if(ptcal > refPt2) {
      refPt2 = ptcal;
      posJet2 = jet - JetVector.begin();
    }

  } 

  //-- apply the thight selection to them
  
  if(posJet1 >= 0 && posJet2 >= 0) {
    
    bool accept_jet1 = false;
    bool accept_jet2 = false;
    
    MyJet jet1 = JetVector.at(posJet1);
    MyJet jet2 = JetVector.at(posJet2);
    
    //-- jet 1 selection
    if(jet1.pt_cal > jetPtCut_ && fabs(jet1.eta_cal) < jetEtaCut_ && jet1.TightPFJetId == true) accept_jet1 = true;
    
    //-- jet 2 selection
    if(jet2.pt_cal > jetPtCut_ && fabs(jet2.eta_cal) < jetEtaCut_ && jet2.TightPFJetId == true) accept_jet2 = true;
    
    //-- final selection (back-to-back)
    
    if(accept_jet1 == true && accept_jet2 == true) {
      double deltaPhi = fabs(reco::deltaPhi(jet1.phi_cal, jet2.phi_cal));
      if (fabs(deltaPhi - M_PI) < 1.0) accept = true;
    }
    
    if(accept == true) {
      dijet.isDiJet = true;
      dijet.posJet1 = posJet1;
      dijet.posJet2 = posJet2;
    }
    
  } //-- posJet1 >= 0 && posJet2 >= 0
  
  if(CentralPFDiJetDebug) dijet.Print();
  
}

