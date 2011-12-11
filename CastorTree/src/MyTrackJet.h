#ifndef __MyTrackJet_H__
#define __MyTrackJet_H__

#include "MyPart.h"

class MyTrackJet : public TObject {

 public :
  MyTrackJet();
  ~MyTrackJet();

  virtual void Print();
  virtual void Reset();

  //-- raw jet variables
  Double_t e_raw,pt_raw,eta_raw,phi_raw,px_raw,py_raw,pz_raw;

  //-- correction - uncertainty
  Double_t jec, jec_unc;

  //-- corrected jet variables
  Double_t e_cal,pt_cal,eta_cal,phi_cal,px_cal,py_cal,pz_cal;

  //-- number of tracks
  Int_t ntrack;

  //-- check jet to be associated to the hard primary vertex
  Bool_t pv;

 private :
  
  ClassDef (MyTrackJet,1)
    };

#endif
