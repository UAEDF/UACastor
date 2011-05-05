#ifndef __MyPart_H__
#define __MyPart_H__

#include "TLorentzVector.h"

class MyPart : public TLorentzVector {
  
 public :
  MyPart();
  virtual ~MyPart();

  virtual void Reset();
  virtual void Print();
  
  Double_t charge;
  
 private:
  
  ClassDef (MyPart,1)
};

#endif



