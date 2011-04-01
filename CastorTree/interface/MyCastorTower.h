#ifndef __MyCastorTower_H__
#define __MyCastorTower_H__

#include "TObject.h"

using namespace std;

class MyCastorTower : public TObject {
  
 public :
  MyCastorTower();
  virtual ~MyCastorTower();
  
  void Print();
  
  Double_t energy, pt, eta, phi;
  Double_t fem, eem, ehad;
  Double_t depth, fhot;
  Int_t ncell;
  
 private:
  
  ClassDef (MyCastorTower,1)
};

#endif

