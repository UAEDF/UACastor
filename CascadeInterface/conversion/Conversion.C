#include <iostream>

#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>

#include <HepMC/GenEvent.h>
#include <HepMC/IO_GenEvent.h>

using namespace std;

#define debug 1

int main(int argc, char *argv[]){

  TFile* fout = new TFile("cascade.result.root","RECREATE");

  HepMC::IO_GenEvent fin("../CASCADE_HEPMC/bin/example_test_out.dat",std::ios::in);
  
  HepMC::GenEvent* evt = new HepMC::GenEvent;

  TTree *tree = new TTree("tree","cascade result");
  tree->Branch("event",&evt);

  Int_t nevt = 0;

  while (evt = fin.read_next_event() ) {

    nevt++;

    if(debug){ 
      cout<<"nevt: "<<nevt<<endl;
      getchar();
      evt->print();
    }

    tree->Fill();
  }

  tree->Print();

  fout->cd();
  tree->Write();
  fout->Close();
  
  delete fout;

  return(0);  
}
