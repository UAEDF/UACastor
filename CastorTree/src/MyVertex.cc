
#include "UACastor/CastorTree/interface/MyVertex.h"
#include <iostream>

using namespace std;

ClassImp(MyVertex)

MyVertex::MyVertex() { }

MyVertex::~MyVertex() { }

void MyVertex::Print() {

  cout<<"vertex information: "<<endl;

  cout<<"x: "<<this->x<<endl;
  cout<<"y: "<<this->y<<endl;
  cout<<"z: "<<this->z<<endl;

  cout<<"error x: "<<this->ex<<endl;
  cout<<"error y: "<<this->ey<<endl;
  cout<<"error z: "<<this->ez<<endl;

  cout<<"validity: "<<this->validity<<endl;
  cout<<"fake: "<<this->fake<<endl;
  cout<<"chi2n: "<<this->chi2n<<endl;

  cout<<"ntracks: "<<this->ntracks<<endl;
}

