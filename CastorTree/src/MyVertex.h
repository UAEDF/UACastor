#ifndef __MyVertex_H__
#define __MyVertex_H__

#include "TObject.h"

class MyVertex : public TObject {

  public :
    MyVertex();
    virtual ~MyVertex();

    void Print();

    Double_t x,y,z;
    Double_t ex,ey,ez;    

    Bool_t validity;  
    Bool_t fake;
    Double_t chi2n;
   
    Int_t  ntracks;  

  private:

  ClassDef (MyVertex,1)
};

#endif

