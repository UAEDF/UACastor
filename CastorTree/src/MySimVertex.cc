
#include "UACastor/CastorTree/interface/MySimVertex.h"
#include <iostream>

using namespace std;

ClassImp(MySimVertex)

MySimVertex::MySimVertex() { }

MySimVertex::~MySimVertex() { }

void MySimVertex::Print() {

  cout<<"simulated vertex information: "<<endl;

  cout<<"x: "<<this->x<<endl;
  cout<<"y: "<<this->y<<endl;
  cout<<"z: "<<this->z<<endl;

}
