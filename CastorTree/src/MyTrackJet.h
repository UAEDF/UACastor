#ifndef __MyTrackJet_H__
#define __MyTrackJet_H__

#include "MyPart.h"

class MyTrackJet : public MyPart {

 public :
  MyTrackJet();
  ~MyTrackJet();

  virtual void Print();
  virtual void Reset();

  //-- number of tracks
  Int_t ntrack;

  //-- check jet to be associated to the hard primary vertex
  Bool_t pv;

 private :
  
  ClassDef (MyTrackJet,1)
    };

#endif
