
#include "./MyCastorTower.h"
#include <iostream>

using namespace std;

ClassImp(MyCastorTower)

MyCastorTower::MyCastorTower() { }

MyCastorTower::~MyCastorTower() { }

void MyCastorTower::Print() {

  cout<<"castor tower information: "<<endl;

  cout<<"energy: "<<this->energy<<endl;
  cout<<"pt: "<<this->pt<<endl;
  cout<<"eta: "<<this->eta<<endl;
  cout<<"phi: "<<this->phi<<endl;
  
  cout<<"fem: "<<this->fem<<endl;
  cout<<"eem: "<<this->eem<<endl;
  cout<<"ehad: "<<this->ehad<<endl;

  cout<<"depth: "<<this->depth<<endl;
  cout<<"fhot: "<<this->fhot<<endl;
  
  cout<<"ncell: "<<this->ncell<<endl;
}

