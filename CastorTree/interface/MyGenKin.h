#ifndef __MyGenKin_H__
#define __MyGenKin_H__

#include "TObject.h"

class MyGenKin : public TObject {

  public :
  MyGenKin();
  virtual ~MyGenKin();

  void Reset();
  void Print();

  //-- General Info
  Int_t    ProcessId;   
  Double_t PtHat;

  //-- Pdf Info
  Double_t x1;   //-- fraction of beam momentum carried by first parton 
  Double_t x2;   //-- fraction of beam momentum carried by second parton
  Double_t Q;    //-- Q-scale used in evaluation of PDFs (in GeV)
  Int_t Idparton1;  //-- flavour code of first parton
  Int_t Idparton2;  //-- flavour code of second parton

  private:

  ClassDef (MyGenKin,1)
};

#endif
