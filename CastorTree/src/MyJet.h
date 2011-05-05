#ifndef __MyJet_H__
#define __MyJet_H__

#include <vector>
#include "TObject.h"
#include "MyPart.h"

class MyJet : public TObject {

  public :
    MyJet();
    ~MyJet();

    void Print();

    //-- raw jet variables
    Double_t e_raw,pt_raw,eta_raw,phi_raw,px_raw,py_raw,pz_raw;

    //-- correction - uncertainty
    Double_t jec, jec_unc;

    //-- corrected jet variables
    Double_t e_cal,pt_cal,eta_cal,phi_cal,px_cal,py_cal,pz_cal;

    //-- estimators (PFjet only)
    Double_t fhad_ch;    //-- chargedHadronEnergyFraction()  
    Double_t fhad_ne;    //-- neutralHadronEnergyFraction() 

    Double_t fem_ch;     //-- chargedEmEnergyFraction() 
    Double_t fem_ne;     //-- neutralEmEnergyFraction() 

    Int_t multi_ch;      //-- chargedMultiplicity() 
    Int_t multi_ne;      //-- neutralMultiplicity() 

    Int_t multi_ch_had;  //-- chargedHadronMultiplicity() 
    Int_t multi_ne_had;  //-- neutralHadronMultiplicity() 

    Int_t multi_gamma;  //-- photonMultiplicity() 
    Int_t multi_ele;    //-- electronMultiplicity() 
    Int_t multi_mu;     //-- muonMultiplicity() 

    //-- estimators (Calojet only)
    Double_t fem;        //-- emEnergyFraction() (for PFJet: fem_ch + fem_ne)
    Double_t eem_EB;     //-- emEnergyInEB()
    Double_t eem_EE;     //-- emEnergyInEE()
    Double_t eem_HF;     //-- emEnergyInHF()

    Double_t fhad;      //-- energyFractionHadronic()  (for PFjet: fhad_ch + fhad_ne)
    Double_t ehad_HB;   //-- hadEnergyInHB()
    Double_t ehad_HE;   //-- hadEnergyInHE()
    Double_t ehad_HF;   //-- hadEnergyInHF()
    Double_t ehad_HO;   //-- hadEnergyInHO()

    Int_t n60;  //-- n60()
    Int_t n90;  //-- n90()

    Double_t emax_ecal; //-- maxEInEmTowers()
    Double_t emax_hcal; //-- maxEInHadTowers() 

    Int_t n90hits;
    Double_t HPD;
    Double_t RBX;
    Double_t sigma_eta;
    Double_t sigma_phi;

    //-- number of constituents (PFObject for PFjet, CaloTower for Calojet)
    UInt_t nconstituent; 

    //-- number of tracks (PFjet only)
    Int_t ntrack;       

    //-- jet ID
    Bool_t TightPFJetId;   
    Bool_t LooseCaloJetId;  
    Bool_t TightCaloJetId;

  private:

  ClassDef (MyJet,1)
};

#endif
