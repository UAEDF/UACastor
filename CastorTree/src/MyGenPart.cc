
#include "../interface/MyGenPart.h"
#include <iostream>

using namespace std;

ClassImp(MyGenPart)

MyGenPart::MyGenPart() { }

MyGenPart::~MyGenPart() { }

void MyGenPart::Print() {

  cout<<"px: "<<this->Part.v.Px()<<endl;
  cout<<"py: "<<this->Part.v.Py()<<endl;
  cout<<"pz: "<<this->Part.v.Pz()<<endl;
  cout<<"E: "<<this->Part.v.E()<<endl;
  cout<<"charge: "<<this->Part.charge<<endl;

  cout<<"pdgId: "<<this->pdgId<<endl;
  cout<<"status: "<<this->status<<endl;
  cout<<"name: "<<this->name<<endl;
}
