#ifndef __MyVertex_H__
#define __MyVertex_H__

#include "TObject.h"

class MyVertex : public TObject {

  public :
    MyVertex();
    virtual ~MyVertex();

    void Print();

    Double_t x,y,z,rho;
    Double_t ex,ey,ez,erho;    

    Bool_t validity;  
    Bool_t fake;

    Double_t chi2n;
    Double_t ndof; 

    Bool_t isGoodVertex;
   
    Int_t  ntracks;  

  private:

  ClassDef (MyVertex,1)
};

#endif

