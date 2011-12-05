#include "MyTrackJet.h"
#include <iostream>

using namespace std;

ClassImp(MyTrackJet)

MyTrackJet::MyTrackJet():MyPart(){
  this->Reset();
}

MyTrackJet::~MyTrackJet(){}

void MyTrackJet::Print(){
  this->MyPart::Print();
  cout<<"number of tracks: "<<this->ntrack<<endl;
  cout<<"jet associated to the hard primary vertex: "<<this->pv<<endl;
}

void MyTrackJet::Reset(){
  this->MyPart::Reset();
  ntrack = 0;
  pv = 0;
}
