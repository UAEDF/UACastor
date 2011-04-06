#ifndef __MyGenPart_H__
#define __MyGenPart_H__

#include <string>
#include "TObject.h"
#include "./MyPart.h"

class MyGenPart : public TObject {
  
 public :
  MyGenPart();
  virtual ~MyGenPart();

  void Print();
  
  MyPart      Part;
  Int_t       pdgId,status;
  std::string name;

  private:

  ClassDef (MyGenPart,1)
};

#endif

