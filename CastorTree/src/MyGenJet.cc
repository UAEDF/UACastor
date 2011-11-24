#include "./MyGenJet.h"
#include <iostream>

using namespace std;

ClassImp(MyGenJet)
  
MyGenJet::MyGenJet():MyPart() {
    this->Reset();
  }

MyGenJet::~MyGenJet(){}

void MyGenJet::Print() {

  
  cout<<endl<<"MyGenJet::Print()"<<endl;
  this->MyPart::Print(); 
  cout<<"npart: "<<npart<<endl<<endl;
  getchar();
  int ipart = 0;
  for(vector<MyGenPart>::iterator it = JetPart.begin() ;it != JetPart.end() ;++it,++ipart) {
    cout<<"particule: "<<ipart+1<<endl;
    it->Print();
    cout<<endl;
  }
}

void MyGenJet::Reset(){
  
  this->MyPart::Reset();
  npart = 0;
  JetPart.clear();  
}
