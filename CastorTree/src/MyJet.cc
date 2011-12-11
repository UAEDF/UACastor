
#include "./MyJet.h"
#include <iostream>

using namespace std;

ClassImp(MyJet)

MyJet::MyJet() { }

MyJet::~MyJet() { }

void MyJet::Print() {

  cout<<endl<<"central jet information: "<<endl;

  cout<<"raw jet variables: "<<endl;
  cout<<"energy: "<<this->e_raw<<endl;
  cout<<"pt: "<<this->pt_raw<<endl;
  cout<<"eta: "<<this->eta_raw<<endl;
  cout<<"phi: "<<this->phi_raw<<endl;
  cout<<"px: "<<this->px_raw<<endl;
  cout<<"py: "<<this->py_raw<<endl;
  cout<<"pz: "<<this->pz_raw<<endl;

  cout<<"correction - uncertainty: "<<endl;
  cout<<"jec: "<<this->jec<<endl;
  cout<<"jec_unc: "<<this->jec_unc<<endl;

  cout<<"corrected jet variables: "<<endl;
  cout<<"energy cal: "<<this->e_cal<<endl;
  cout<<"pt cal: "<<this->pt_cal<<endl;
  cout<<"eta cal: "<<this->eta_cal<<endl;
  cout<<"phi cal: "<<this->phi_cal<<endl;
  cout<<"px cal: "<<this->px_cal<<endl;
  cout<<"py cal: "<<this->py_cal<<endl;
  cout<<"pz cal: "<<this->pz_cal<<endl;

  cout<<"estimators: "<<endl;
  cout<<"charged hadron energy fraction: "<<this->fhad_ch<<endl;
  cout<<"neutral hadron energy fraction: "<<this->fhad_ne<<endl;

  cout<<"charged em energy fraction: "<<this->fem_ch<<endl;
  cout<<"neutral em energy fraction: "<<this->fem_ne<<endl;

  cout<<"charged multiplicity: "<<this->multi_ch<<endl;
  cout<<"neutral multiplicity: "<<this->multi_ne<<endl;

  cout<<"charged hadron multiplicity: "<<this->multi_ch_had<<endl;
  cout<<"neutral hadron multiplicity: "<<this->multi_ne_had<<endl;

  cout<<"photon multiplicity: "<<this->multi_gamma<<endl;
  cout<<"electron multiplicity: "<<this->multi_ele<<endl;
  cout<<"muon multiplicity: "<<this->multi_mu<<endl;

  cout<<"em energy fraction: "<<this->fem<<endl;
  cout<<"em energy in EB: "<<this->eem_EB<<endl;
  cout<<"em energy in EE: "<<this->eem_EE<<endl;
  cout<<"em energy in HF: "<<this->eem_HF<<endl;

  cout<<"had energy fraction: "<<this->fhad<<endl;
  cout<<"hadEnergyInHB: "<<this->ehad_HB<<endl;
  cout<<"hadEnergyInHE: "<<this->ehad_HE<<endl;
  cout<<"hadEnergyInHF: "<<this->ehad_HF<<endl;
  cout<<"hadEnergyInHO: "<<this->ehad_HO<<endl;

  cout<<"n60: "<<this->n60<<endl;
  cout<<"n90: "<<this->n90<<endl;

  cout<<"max energy in em towers: "<<this->emax_ecal<<endl;
  cout<<"max energy in had towers: "<<this->emax_hcal<<endl;

  cout<<"n90hits: "<<this->n90hits<<endl;  
  cout<<"HPD: "<<this->HPD<<endl;	    
  cout<<"RBX: "<<this->RBX<<endl;	    
  cout<<"sigma_eta: "<<this->sigma_eta<<endl;
  cout<<"sigma_phi: "<<this->sigma_phi<<endl;

  cout<<"nconstituent: "<<this->nconstituent<<endl;
  cout<<"ntrack: "<<this->ntrack<<endl;

  cout<<"Tight PF Jet Id: "<<this->TightPFJetId<<endl;
  cout<<"Loose Calo Jet Id: "<<this->LooseCaloJetId<<endl;
  cout<<"Tight Calo Jet Id: "<<this->TightCaloJetId<<endl;
}

