#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <TApplication.h>
#include "MainAnalyzer.h"

int main(int argc, char *argv[]) {
	
  using namespace std;

  printf("argc = %d\n", argc);
  for (int i = 0; i<argc; i++){
    static int k = 0;
    printf("argv[%d] = %s\n", k, argv[k]);
    k++;
  }

  TString rootfile = argv[1];
  TString title = argv[2];
  TString globalname = argv[3];

  cout<<"I will look in data and MC files "<<rootfile.Data()<<" for the histos with title "<<title.Data()<<endl;
  cout<<"All canvas will be saved with the global name: "<<globalname.Data()<<endl;

  TApplication* rootapp = new TApplication("app",&argc, argv);

  MainAnalyzer* m = new MainAnalyzer();

  m->plotHistos("../Result/",rootfile,title);
  m->saveAllCanvas("../Plot/",globalname);

  delete m;
  
  return(0);
}

