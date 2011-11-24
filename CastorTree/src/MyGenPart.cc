
#include "./MyGenPart.h"
#include <iostream>

using namespace std;

ClassImp(MyGenPart)

MyGenPart::MyGenPart() { }

MyGenPart::~MyGenPart() { }

void MyGenPart::Print() {

  this->MyPart::Print();
  cout<<"pdgId: "<<this->pdgId<<endl;
  cout<<"status: "<<this->status<<endl;
  cout<<"name: "<<this->name<<endl;
}
