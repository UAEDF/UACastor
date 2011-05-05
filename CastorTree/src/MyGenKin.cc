
#include "./MyGenKin.h"
#include <iostream>

using namespace std;

ClassImp(MyGenKin)

MyGenKin::MyGenKin() { }

MyGenKin::~MyGenKin() { }

void MyGenKin::Reset() {
 ProcessId = 0;
 PtHat = 0;
 x1 = 0;
 x2 = 0;
 Q = 0;
 Idparton1 = 0;
 Idparton2 = 0;
}

void MyGenKin::Print() {
  cout<<"ProcessId: "<<this->ProcessId<<endl;
  cout<<"PtHat: "<<this->PtHat<<endl;
  cout<<"x1: "<<this->x1<<endl;
  cout<<"x2: "<<this->x2<<endl;
  cout<<"Q: "<<this->Q<<endl;
  cout<<"Idparton1: "<<this->Idparton1<<endl;
  cout<<"Idparton2: "<<this->Idparton2<<endl;
}
